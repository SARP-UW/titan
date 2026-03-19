#!/usr/bin/env bash

set -e
set -o pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
rm -rf "$SCRIPT_DIR/build_logs/"
LOG_DIR="$SCRIPT_DIR/build_logs"
mkdir -p "$LOG_DIR"

LOG_FILE="$LOG_DIR/build_$(date +%Y%m%d_%H%M%S).log"
exec > >(tee -a "$LOG_FILE") 2>&1

FW_TARGET="${1:-${FW_TARGET:-titan}}"
FW_TARGETS=(titan test_pwm test_spi test_usart test_oscilloscope)
MAX_ATTEMPTS=3
UPDATE_DEBUG_TARGET=false

for arg in "${@:2}"; do
  case "$arg" in
    --set-debug-target|-d) UPDATE_DEBUG_TARGET=true ;;
  esac
done

# ── Target validation ──────────────────────────────────────────────────────────
case "$FW_TARGET" in
  titan|test_pwm|test_spi|test_usart|test_oscilloscope|commit_check|all|clean|docs)
    ;;
  *)
    echo "Unknown target: $FW_TARGET"
    echo "Valid targets: titan, test_pwm, test_spi, test_usart, test_oscilloscope, commit_check, all, clean, docs"
    exit 4
    ;;
esac

# ── OS detection ───────────────────────────────────────────────────────────────
OS_TYPE=$(uname -s)
case "$OS_TYPE" in
  Darwin)
    USB_RESET_BIN="$SCRIPT_DIR/stm_usb/stm_usb_mac"
    ;;
  Linux)
    USB_RESET_BIN="$SCRIPT_DIR/stm_usb/stm_usb_linux"
    ;;
  MINGW*|MSYS*|CYGWIN*|Windows_NT)
    USB_RESET_BIN="$SCRIPT_DIR/stm_usb/stm_usb_win.exe"
    ;;
  *)
    echo "Unsupported OS: $OS_TYPE"
    exit 1
    ;;
esac

if [ ! -f "$USB_RESET_BIN" ]; then
  echo "USB reset binary not found: $USB_RESET_BIN"
  exit 2
fi

run_usb_reset() {
  echo "Running USB reset ($USB_RESET_BIN)..."
  "$USB_RESET_BIN"
  USB_RC=$?
  if [ $USB_RC -ne 0 ]; then
    echo "USB reset failed (rc=$USB_RC). Aborting."
    exit 3
  fi
}

# ── CLI binary detection (Linux/Windows only) ─────────────────────────────────
find_cli() {
  case "$OS_TYPE" in
    Linux)
      CLI_BIN="$(command -v STM32_Programmer_CLI || true)"
      [ -z "$CLI_BIN" ] && CLI_BIN="/opt/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI"
      ;;
    MINGW*|MSYS*|CYGWIN*|Windows_NT)
      CLI_BIN="$(command -v STM32_Programmer_CLI.exe || true)"
      [ -z "$CLI_BIN" ] && CLI_BIN="/c/Program Files/STMicroelectronics/STM32Cube/STM32CubeProgrammer/bin/STM32_Programmer_CLI.exe"
      ;;
    *)
      CLI_BIN=""
      ;;
  esac
}

# ── Update executable in every launch.json configuration ──────────────────────
update_debug_target() {
  local elf_path="$1"
  local launch="$SCRIPT_DIR/.vscode/launch.json"

  if [ ! -f "$launch" ]; then
    echo "Warning: $launch not found, skipping debug target update."
    return
  fi
  if ! command -v jq &>/dev/null; then
    echo "Warning: jq not installed — cannot update debug target. Install with: brew install jq"
    return
  fi

  jq --arg val "$elf_path" \
    '.configurations = [.configurations[] | .executable = $val]' \
    "$launch" > "$launch.tmp" && mv "$launch.tmp" "$launch"
  echo "Debug target set to: $elf_path"
}

# ── Special targets ────────────────────────────────────────────────────────────
if [ "$FW_TARGET" = "docs" ]; then
  if ! command -v doxygen &>/dev/null; then
    echo "Error: doxygen is not installed. Install with: brew install doxygen"
    exit 5
  fi
  echo "Generating Doxygen documentation..."
  doxygen Doxyfile
  echo "Docs generated in docs/html/"
  exit 0
fi

if [ "$FW_TARGET" = "clean" ]; then
  echo "Cleaning build/ contents..."
  mkdir -p "$SCRIPT_DIR/build"
  find "$SCRIPT_DIR/build" -mindepth 1 -maxdepth 1 -exec rm -rf {} +
  echo "Clean complete."
  exit 0
fi

if [ "$FW_TARGET" = "commit_check" ]; then
  echo "Running local pre-commit check:"
  cmake -S "$SCRIPT_DIR" -B "$SCRIPT_DIR/build" || { echo "cmake configure failed"; exit 20; }
  cd "$SCRIPT_DIR/build" || exit 22
  for target in "${FW_TARGETS[@]}"; do
    echo "Building ${target}.elf"
    make "${target}.elf" || { echo "make failed for ${target}.elf"; exit 21; }
  done
  make test_alloc_target || { echo "make test_alloc failed"; exit 21; }
  echo "Built target test_alloc"
  ctest --output-on-failure || { echo "Unit tests failed"; exit 21; }
  echo "Local CMake check passed. Good to go for committing! :D"
  exit 0
fi

if [ "$FW_TARGET" = "all" ]; then
  echo "Running full build (make all):"
  cmake -S "$SCRIPT_DIR" -B "$SCRIPT_DIR/build" || { echo "cmake configure failed"; exit 20; }
  cd "$SCRIPT_DIR/build" || exit 22
  make all || { echo "make all failed"; exit 21; }
  ctest --output-on-failure || { echo "Unit tests failed"; exit 21; }
  echo "Full build passed."
  exit 0
fi

# ── Build ──────────────────────────────────────────────────────────────────────
run_usb_reset

echo "Running cmake .."
cmake -S "$SCRIPT_DIR" -B "$SCRIPT_DIR/build"
echo "Running make"
cd "$SCRIPT_DIR/build" && make "${FW_TARGET}.elf" || { echo "make failed"; exit 21; }
cd "$SCRIPT_DIR"

ELF_FILE="$SCRIPT_DIR/build/${FW_TARGET}.elf"
echo "ELF path: $ELF_FILE"

if [ ! -f "$ELF_FILE" ]; then
  echo "ELF not found: $ELF_FILE"
  exit 1
fi

if [ "$UPDATE_DEBUG_TARGET" = true ]; then
  update_debug_target "$ELF_FILE"
fi

# ── Flash ──────────────────────────────────────────────────────────────────────
OPENOCD_RC=1
for attempt in $(seq 1 $MAX_ATTEMPTS); do
  echo "Flashing with OpenOCD (attempt ${attempt}/${MAX_ATTEMPTS})..."
  OPENOCD_LOG="$LOG_DIR/openocd_attempt${attempt}.log"

  OPENOCD_CMD="init; reset halt; \
    mww 0x52002014 0xFFFF0000; \
    mww 0x52002114 0xFFFF0000; \
    flash write_image erase \"${ELF_FILE}\"; \
    reset run; shutdown"

  set +e
  openocd \
    -f interface/stlink.cfg \
    -f target/stm32h7x_dual_bank.cfg \
    -c "$OPENOCD_CMD" \
    2>&1 | tee "$OPENOCD_LOG"
  OPENOCD_RC=${PIPESTATUS[0]}
  set -e

  if grep -qiE "(WRPERR|failed erasing|erase time-out|Mass erase operation failed|Programming Failed|timeout waiting for algorithm|checksum mismatch)" "$OPENOCD_LOG"; then
    echo "Flash error detected — running recovery..."

    case "$OS_TYPE" in
      Darwin)
        echo "Open STM32CubeProgrammer app, connect the board, do a full chip erase,"
        echo "then disconnect the board and press Enter to continue."
        read -r -p "Press Enter after full chip erase is complete. "
        run_usb_reset
        echo "Recovery complete — retrying OpenOCD..."
        continue
        ;;

      Linux|MINGW*|MSYS*|CYGWIN*|Windows_NT)
        find_cli
        if [ ! -x "$CLI_BIN" ] && ! command -v "$CLI_BIN" >/dev/null 2>&1; then
          echo "STM32_Programmer_CLI not found at: $CLI_BIN"
          echo "Install STM32CubeProgrammer or add it to PATH, then retry."
          break
        fi

        echo "Found STM32 CLI: $CLI_BIN"

        echo "Setting RDP to Level 1..."
        "$CLI_BIN" -c port=SWD mode=UR reset=HWrst freq=1000 -ob RDP=0xBB || true
        sleep 2

        run_usb_reset
        sleep 8

        echo "Regressing RDP to Level 0 (triggers H7 mass erase)..."
        for rdp_attempt in 1 2 3; do
          if "$CLI_BIN" -c port=SWD mode=UR reset=HWrst freq=1000 -ob RDP=0xAA; then
            echo "RDP regression succeeded."
            break
          fi
          echo "RDP regression attempt $rdp_attempt failed, retrying in 3s..."
          sleep 3
        done

        echo "Waiting 15s for H7 mass erase to complete..."
        sleep 15

        run_usb_reset
        sleep 8

        echo "Recovery complete — retrying OpenOCD..."
        continue
        ;;
    esac
  fi

  if [ "$OPENOCD_RC" -eq 0 ]; then
    echo "Flash successful."
    break
  fi

  echo "OpenOCD failed (exit $OPENOCD_RC), retrying in 1s..."
  sleep 1
done

if [ "$OPENOCD_RC" -ne 0 ]; then
  echo "OpenOCD did not succeed after $MAX_ATTEMPTS attempts."
  exit 32
fi
