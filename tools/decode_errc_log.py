#!/usr/bin/env python3
"""Decode Titan errc flash log dumps into readable entries."""

from __future__ import annotations

import argparse
import struct
from pathlib import Path

TI_LOG_MAGIC = 0xD1A60001
TI_LOG_ENTRY_SIZE = 128

ERRC_NAMES = {
    0: "TI_ERRC_NONE",
    1: "TI_ERRC_UNKNOWN",
    2: "TI_ERRC_INVALID_ARG",
    3: "TI_ERRC_BUSY",
    4: "TI_ERRC_TIMEOUT",
    5: "TI_ERRC_OVERFLOW",
    6: "TI_ERRC_NOT_FOUND",
    7: "TI_ERRC_INTERNAL",
    8: "TI_ERRC_DEVICE",
    9: "TI_ERRC_BUS",
    10: "TI_ERRC_CHECKSUM",
    11: "TI_ERRC_PROTOCOL",
}


def cstr(buf: bytes) -> str:
    return buf.split(b"\x00", 1)[0].decode("utf-8", errors="replace")


def decode_entry(entry: bytes) -> tuple[int, int, int, str, str, str]:
    magic = struct.unpack_from("<I", entry, 0)[0]
    errc = entry[4]
    line = struct.unpack_from("<I", entry, 8)[0]
    func = cstr(entry[12:40])
    file = cstr(entry[40:80])
    msg = cstr(entry[80:128])
    return (magic, errc, line, func, file, msg)

# Ex command
# ./build.sh test_errc
# openocd -f interface/stlink.cfg -f target/stm32h7x_dual_bank.cfg -c "init; reset halt; dump_image errc_log.bin 0x081E0000 0x20000; shutdown"
# python3 tools/decode_errc_log.py errc_log.bin --limit 20
def main() -> int:
    parser = argparse.ArgumentParser(description="Decode Titan errc_log.bin")
    parser.add_argument("bin_file", type=Path, help="Path to errc_log.bin")
    parser.add_argument("--base", default="0x081E0000", help="Flash base address for display")
    parser.add_argument("--limit", type=int, default=32, help="Max entries to print")
    args = parser.parse_args()

    base_addr = int(args.base, 0)
    data = args.bin_file.read_bytes()

    printed = 0
    for offset in range(0, len(data), TI_LOG_ENTRY_SIZE):
        entry = data[offset : offset + TI_LOG_ENTRY_SIZE]
        if len(entry) < TI_LOG_ENTRY_SIZE:
            break

        magic, errc, line, func, file, msg = decode_entry(entry)

        if magic == 0xFFFFFFFF:
            continue
        if magic != TI_LOG_MAGIC:
            continue

        errc_name = ERRC_NAMES.get(errc, f"UNKNOWN({errc})")
        abs_addr = base_addr + offset
        print(
            f"0x{abs_addr:08X}  {errc_name:<18} line={line:<5} "
            f"file={file:<20} func={func:<24} msg={msg}"
        )
        printed += 1
        if printed >= args.limit:
            break

    if printed == 0:
        print("No valid log entries found (magic mismatch or region empty).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
