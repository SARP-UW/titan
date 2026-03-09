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
 * @file peripheral/log.h
 * @authors Mahir Emran
 * @brief Flash-backed error logging and TI_SET_ERRC macro.
 *
 * Usage
 * -----
 * On startup (after qspi_init), call ti_log_init() once.
 *
 * At every point where an error is *detected* (not propagated), replace:
 *   return TI_ERRC_TIMEOUT;
 * with:
 *   TI_SET_ERRC(NULL, TI_ERRC_TIMEOUT, "human readable description");
 *   return TI_ERRC_TIMEOUT;
 *
 * Or, when the caller passes an errc_out pointer:
 *   TI_SET_ERRC(errc_out, TI_ERRC_TIMEOUT, "description");
 *   return;
 *
 * Do NOT use TI_SET_ERRC when merely propagating an error returned from a
 * callee — the callee already logged it at the source.
 *
 * Flash layout
 * ------------
 * The last TI_LOG_FLASH_SIZE bytes of the S25FL064L flash chip are reserved
 * for the log. Entries are written sequentially; when the region fills up the
 * oldest sector is erased and the writer wraps around (oldest logs lost).
 *
 * Each entry is TI_LOG_ENTRY_SIZE (128) bytes:
 *   [ magic(4) | errc(1) | pad(3) | line(4) | func(28) | file(40) | msg(48) ]
 */

#pragma once
#include <stdint.h>
#include "errc.h"

/**************************************************************************************************
 * @section Flash region configuration
 *
 * Adjust TI_LOG_FLASH_START to point past the end of your firmware image.
 * Default: last 512 KB of an 8 MB (S25FL064L = 64 Mbit) chip.
 **************************************************************************************************/

/** @brief Base address (in flash) of the log region. */
#define TI_LOG_FLASH_START   0x780000U

/** @brief Total size of the log region in bytes. */
#define TI_LOG_FLASH_SIZE    0x080000U

/** @brief Erase granularity of the flash (4 KB sector). */
#define TI_LOG_SECTOR_SIZE   0x001000U

/**************************************************************************************************
 * @section Log entry layout
 **************************************************************************************************/

/** @brief Magic word written in every valid log entry. */
#define TI_LOG_MAGIC         0xD1A60001U

/** @brief Size of each log entry in bytes (must be a multiple of flash page size, 256 B). */
#define TI_LOG_ENTRY_SIZE    128U

/**
 * @brief A single log entry stored in flash.
 *
 * Packed to 128 bytes exactly.  All char arrays are null-terminated and
 * truncated to fit; long paths are right-truncated.
 */
typedef struct __attribute__((packed)) {
  uint32_t magic;    /**< TI_LOG_MAGIC when valid, 0xFFFFFFFF when slot is empty. */
  uint8_t  errc;     /**< The error code (cast to uint8_t). */
  uint8_t  _pad[3];  /**< Reserved / alignment. */
  uint32_t line;     /**< Source line number (__LINE__). */
  char     func[28]; /**< Function name (__func__, truncated). */
  char     file[40]; /**< Source file path (__FILE__, truncated). */
  char     msg[48];  /**< Human-readable description (truncated). */
} ti_log_entry_t;

/* Compile-time size guard */
typedef char _ti_log_entry_size_check[(sizeof(ti_log_entry_t) == TI_LOG_ENTRY_SIZE) ? 1 : -1];

/**************************************************************************************************
 * @section Public API
 **************************************************************************************************/

/**
 * @brief Initialises the log subsystem.
 *
 * Must be called once after qspi_init().  Scans the flash log region to find
 * the next free write slot.  Safe to call multiple times; subsequent calls are
 * no-ops.
 *
 * @return TI_ERRC_NONE on success, TI_ERRC_BUS if the flash scan fails.
 */
enum ti_errc_t ti_log_init(void);

/**
 * @brief Writes one log entry to flash.
 *
 * Best-effort: if the flash is busy or the log subsystem is not initialised the
 * call is silently dropped.  Never calls TI_SET_ERRC internally (no recursion).
 *
 * @param errc  Error code being logged.
 * @param msg   Short descriptive message (truncated to 47 chars).
 * @param func  Function name (pass __func__).
 * @param file  Source file path (pass __FILE__).
 * @param line  Source line number (pass __LINE__).
 */
void ti_log_write(enum ti_errc_t errc, const char *msg,
                  const char *func, const char *file, uint32_t line);

/**************************************************************************************************
 * @section TI_SET_ERRC macro
 *
 * Two-in-one: optionally sets *errc_ptr and logs the error with full source
 * location.  Use this at every point where an error is first *detected*.
 *
 * @param errc_ptr  Pointer to an enum ti_errc_t to set, or NULL.
 * @param code      The TI_ERRC_* code.
 * @param msg       String literal describing what went wrong.
 *
 * Example:
 *   TI_SET_ERRC(NULL, TI_ERRC_TIMEOUT, "Radio CTS polling timed out");
 *   return TI_ERRC_TIMEOUT;
 **************************************************************************************************/
#define TI_SET_ERRC(errc_ptr, code, msg)                                        \
  do {                                                                          \
    if ((errc_ptr) != ((void*)0)) *(enum ti_errc_t *)(errc_ptr) = (code);      \
    ti_log_write((code), (msg), __func__, __FILE__, __LINE__);                  \
  } while (0)
