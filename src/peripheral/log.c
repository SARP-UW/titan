/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @file peripheral/log.c
 * @authors Mahir Emran
 * @brief Flash-backed error logging implementation.
 *
 * Flash commands used (S25FL064L / compatible SPI NOR):
 *   0x06  WREN  – Write Enable (no address, no data)
 *   0x02  PP    – Page Program (3-byte address, up to 256 B data)
 *   0x20  SE    – 4 KB Sector Erase (3-byte address, no data)
 *
 * After every PP or SE, qspi_poll_status_blk() waits for WIP bit to clear.
 *
 * Reentrancy guard: a module-level flag prevents log writes from recursing
 * if the QSPI peripheral itself encounters an error while we are logging.
 */

#include "log.h"
#include "qspi.h"
#include <stdint.h>
#include <stdbool.h>

/**************************************************************************************************
 * @section Private constants
 **************************************************************************************************/

/** @brief S25FL064L instruction: Write Enable. */
#define LOG_CMD_WREN   0x06U

/** @brief S25FL064L instruction: Page Program (3-byte address). */
#define LOG_CMD_PP     0x02U

/** @brief S25FL064L instruction: 4 KB Sector Erase (3-byte address). */
#define LOG_CMD_SE     0x20U

/** @brief S25FL064L instruction: Fast Read (used to scan for next free slot). */
#define LOG_CMD_READ   0x0BU

/** @brief NOR flash erased byte value. */
#define LOG_ERASED_BYTE 0xFFU

/** @brief Total number of log entries that fit in the log region. */
#define LOG_ENTRY_COUNT  (TI_LOG_FLASH_SIZE / TI_LOG_ENTRY_SIZE)

/** @brief Number of log entries per 4 KB sector. */
#define LOG_ENTRIES_PER_SECTOR  (TI_LOG_SECTOR_SIZE / TI_LOG_ENTRY_SIZE)

/**************************************************************************************************
 * @section Module state
 **************************************************************************************************/

static bool     s_initialized = false;

/**
 * @brief Byte offset within the log region where the next entry will be written.
 * Ranges from 0 to TI_LOG_FLASH_SIZE - TI_LOG_ENTRY_SIZE.
 */
static uint32_t s_write_offset = 0;

/**
 * @brief Reentrancy guard: set true while a log write is in progress.
 * Prevents recursion if QSPI itself tries to log an error.
 */
static volatile bool s_log_busy = false;

/**************************************************************************************************
 * @section Private helpers
 **************************************************************************************************/

/**
 * @brief Send a Write-Enable command to the flash.
 *
 * Must be called before every PP or SE command.  The flash automatically
 * clears the write-enable latch after each programmed/erased operation.
 */
static void log_flash_wren(void) {
    qspi_cmd_t cmd = {
        .instruction      = LOG_CMD_WREN,
        .instruction_mode = QSPI_MODE_SINGLE,
        .address_mode     = QSPI_MODE_NONE,
        .address          = 0,
        .address_size     = 0,
        .dummy_cycles     = 0,
        .data_mode        = QSPI_MODE_NONE,
        .data_size        = 0,
    };
    qspi_send_cmd(&cmd, (void*)0, false);
    /* No status poll needed — WREN is immediate. */
}

/**
 * @brief Erase the 4 KB sector that contains the given flash address.
 *
 * Blocks until the erase completes via qspi_poll_status_blk().
 *
 * @param abs_addr Absolute flash address (within the sector to erase).
 */
static void log_flash_erase_sector(uint32_t abs_addr) {
    log_flash_wren();
    qspi_cmd_t cmd = {
        .instruction      = LOG_CMD_SE,
        .instruction_mode = QSPI_MODE_SINGLE,
        .address          = abs_addr & ~(TI_LOG_SECTOR_SIZE - 1U), /* sector-align */
        .address_mode     = QSPI_MODE_SINGLE,
        .address_size     = 2,   /* 24-bit (value 2 → ADSIZE = 0b10 in QUADSPI_CCR) */
        .dummy_cycles     = 0,
        .data_mode        = QSPI_MODE_NONE,
        .data_size        = 0,
    };
    qspi_send_cmd(&cmd, (void*)0, false);
    qspi_poll_status_blk();
}

/**
 * @brief Write up to 128 bytes to flash using Page Program.
 *
 * The caller must ensure that the write does not cross a 256-byte page
 * boundary (guaranteed here because TI_LOG_ENTRY_SIZE = 128 and entries are
 * always aligned to 128-byte boundaries starting from TI_LOG_FLASH_START).
 *
 * Blocks until the program operation completes.
 *
 * @param abs_addr Absolute flash address (must be page-aligned or at least
 *                 not cross a page boundary when combined with size).
 * @param data     Pointer to the data to write.
 * @param size     Number of bytes to write (≤ TI_LOG_ENTRY_SIZE).
 */
static void log_flash_write_page(uint32_t abs_addr, const uint8_t *data, uint32_t size) {
    log_flash_wren();
    qspi_cmd_t cmd = {
        .instruction      = LOG_CMD_PP,
        .instruction_mode = QSPI_MODE_SINGLE,
        .address          = abs_addr,
        .address_mode     = QSPI_MODE_SINGLE,
        .address_size     = 2,   /* 24-bit */
        .dummy_cycles     = 0,
        .data_mode        = QSPI_MODE_SINGLE,
        .data_size        = size,
    };
    qspi_send_cmd(&cmd, (uint8_t*)data, false);
    qspi_poll_status_blk();
}

/**
 * @brief Read 4 bytes from flash at the given absolute address.
 *
 * Used to probe magic words during the init scan.
 *
 * @param abs_addr  Absolute flash address to read from.
 * @param out       Destination buffer (must hold at least 4 bytes).
 * @return TI_ERRC_NONE on success, TI_ERRC_BUS on QSPI error.
 */
static enum ti_errc_t log_flash_read4(uint32_t abs_addr, uint8_t *out) {
    qspi_cmd_t cmd = {
        .instruction      = LOG_CMD_READ,
        .instruction_mode = QSPI_MODE_SINGLE,
        .address          = abs_addr,
        .address_mode     = QSPI_MODE_SINGLE,
        .address_size     = 2,   /* 24-bit */
        .dummy_cycles     = 8,   /* Fast Read requires 8 dummy cycles */
        .data_mode        = QSPI_MODE_SINGLE,
        .data_size        = 4,
    };
    return qspi_send_cmd(&cmd, out, true);
}

/**
 * @brief Null-terminatingly copy at most (dst_size - 1) characters from src
 *        into dst.  If src is longer than dst_size - 1 characters, the tail
 *        is silently truncated.
 */
static void log_strlcpy(char *dst, const char *src, uint32_t dst_size) {
    if (!dst || dst_size == 0) return;
    uint32_t i = 0;
    while (i < dst_size - 1 && src && src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

/**
 * @brief Return a pointer to the basename of a file path (last component).
 *
 * Scans for the last '/' or '\\' in the string.  If none found, returns the
 * original pointer.
 *
 * @param path  Null-terminated file path.
 * @return Pointer to the start of the last path component.
 */
static const char *log_basename(const char *path) {
    if (!path) return "";
    const char *last = path;
    for (const char *p = path; *p; p++) {
        if (*p == '/' || *p == '\\') last = p + 1;
    }
    return last;
}

/**
 * @brief Advance s_write_offset to the next entry slot.
 *
 * Wraps around to 0 when the log region is exhausted.  When wrapping into a
 * new sector, erases that sector first so it is ready to receive new entries.
 */
static void log_advance_offset(void) {
    s_write_offset += TI_LOG_ENTRY_SIZE;
    if (s_write_offset >= TI_LOG_FLASH_SIZE) {
        s_write_offset = 0;
    }

    /* If this slot is the first in its sector, erase the sector. */
    if ((s_write_offset % TI_LOG_SECTOR_SIZE) == 0) {
        log_flash_erase_sector(TI_LOG_FLASH_START + s_write_offset);
    }
}

/**************************************************************************************************
 * @section Public API
 **************************************************************************************************/

enum ti_errc_t ti_log_init(void) {
    if (s_initialized) return TI_ERRC_NONE;

    /*
     * Scan the log region for the first erased slot (magic == 0xFFFFFFFF).
     * That is where we will begin writing.  If every slot is occupied the
     * writer will wrap; log_advance_offset() handles the erase on wrap.
     */
    s_write_offset = 0;
    for (uint32_t i = 0; i < LOG_ENTRY_COUNT; i++) {
        uint8_t buf[4] = {0};
        uint32_t abs_addr = TI_LOG_FLASH_START + s_write_offset;

        enum ti_errc_t rc = log_flash_read4(abs_addr, buf);
        if (rc != TI_ERRC_NONE) {
            /* Flash not responding — give up gracefully. */
            return TI_ERRC_BUS;
        }

        uint32_t magic = ((uint32_t)buf[0] << 24)
                       | ((uint32_t)buf[1] << 16)
                       | ((uint32_t)buf[2] <<  8)
                       |  (uint32_t)buf[3];

        if (magic == 0xFFFFFFFFU) {
            /* Found an erased slot — this is our write position. */
            s_initialized = true;
            return TI_ERRC_NONE;
        }

        s_write_offset += TI_LOG_ENTRY_SIZE;
    }

    /*
     * Log is full.  Wrap to the beginning and erase the first sector so we
     * can start writing again.  The oldest entries are lost.
     */
    s_write_offset = 0;
    log_flash_erase_sector(TI_LOG_FLASH_START);
    s_initialized = true;
    return TI_ERRC_NONE;
}

void ti_log_write(enum ti_errc_t errc, const char *msg,
                  const char *func, const char *file, uint32_t line) {
    /* Reentrancy guard — drop silently if already writing. */
    if (!s_initialized || s_log_busy) return;
    s_log_busy = true;

    /* Build the entry in RAM. */
    ti_log_entry_t entry = {0};

    entry.magic = TI_LOG_MAGIC;
    entry.errc  = (uint8_t)errc;
    entry.line  = line;

    log_strlcpy(entry.func, func ? func : "", sizeof(entry.func));
    log_strlcpy(entry.file, log_basename(file), sizeof(entry.file));
    log_strlcpy(entry.msg,  msg  ? msg  : "", sizeof(entry.msg));

    /* Write to flash, then advance the write pointer. */
    uint32_t abs_addr = TI_LOG_FLASH_START + s_write_offset;
    log_flash_write_page(abs_addr, (const uint8_t *)&entry, TI_LOG_ENTRY_SIZE);
    log_advance_offset();

    s_log_busy = false;
}
