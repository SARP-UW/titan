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
 * @file peripheral/errc.h
 * @authors Aaron McBride, Mahir Emran
 * @brief Error code definitions.
 */

#pragma once
#include <stddef.h>
#include <stdint.h>

/** @brief Error code enum. */
enum ti_errc_t {
  TI_ERRC_NONE = 0,     /** @brief No error occurred. */
  TI_ERRC_UNKNOWN,      /** @brief Unknown or unclassified error. Use as a last resort. */
  TI_ERRC_INVALID_ARG,  /** @brief Invalid argument passed to function. */
  TI_ERRC_BUSY,         /** @brief Resource or device is currently busy. */
  TI_ERRC_TIMEOUT,      /** @brief Operation timed out before completing. */
  TI_ERRC_OVERFLOW,     /** @brief Buffer or resource capacity exceeded. */
  TI_ERRC_NOT_FOUND,    /** @brief Requested resource or context could not be found. */
  TI_ERRC_INTERNAL,     /** @brief Internal logic error that should not occur given valid inputs.
                         *         Nothing the caller can do; indicates a bug or unexpected state. */
  TI_ERRC_DEVICE,       /** @brief Error communicating with or reported by a specific device.
                         *         The device may be unresponsive, misbehaving, or returning bad data. */
  TI_ERRC_BUS,          /** @brief Error with an entire communication bus (SPI, I2C, UART, etc.).
                         *         The bus may be stuck, not configured, or experiencing electrical issues. */
  TI_ERRC_CHECKSUM,     /** @brief Data integrity check failed (checksum or CRC mismatch). */
  TI_ERRC_PROTOCOL,     /** @brief Protocol violation or unexpected data received from a peer. */
};

/**************************************************************************************************
 * @section Log Configuration & Data Structures
 **************************************************************************************************/

/** @brief Base address (in flash) of the log region (Bank 2, Sector 7). */
#define TI_LOG_FLASH_START   0x081E0000U
/** @brief Total size of the log region in bytes. */
#define TI_LOG_FLASH_SIZE    0x00020000U
/** @brief Erase granularity of the internal flash (128 KB sector). */
#define TI_LOG_SECTOR_SIZE   0x00020000U
/** @brief Magic word written in every valid log entry. */
#define TI_LOG_MAGIC         0xD1A60001U
/** @brief Size of each log entry in bytes (must be a multiple of flash word size, 32 B). */
#define TI_LOG_ENTRY_SIZE    128U

/** @brief A single log entry stored in flash. */
typedef struct __attribute__((packed)) {
  uint32_t magic;    /**< TI_LOG_MAGIC when valid, 0xFFFFFFFF when slot is empty. */
  uint8_t  errc;     /**< The error code (cast to uint8_t). */
  uint8_t  _pad[3];  /**< Reserved / alignment. */
  uint32_t line;     /**< Source line number (__LINE__). */
  char     func[28]; /**< Function name (__func__, truncated). */
  char     file[40]; /**< Source file path (__FILE__, truncated). */
  char     msg[48];  /**< Human-readable description (truncated). */
} ti_log_entry_t;

/**************************************************************************************************
 * @section Public API
 **************************************************************************************************/

/**
 * @brief Initialises the internal flash log subsystem.
 */
enum ti_errc_t ti_log_init(void);

/**
 * @brief Low-level write to the flash log. Use macros instead.
 */
void ti_log_write(enum ti_errc_t errc, const char *msg,
                  const char *func, const char *file, uint32_t line);

/**************************************************************************************************
 * @section Error Macros (Stack Trace Emulation)
 **************************************************************************************************/

/**
 * @brief Sets the output error code and writes to the flash log.
 * 
 * Use this for both initial errors and for "Propagated" entries to build a trace.
 *
 * @param errc_ptr  Pointer to an enum ti_errc_t to set, or NULL.
 * @param code      The TI_ERRC_* code.
 * @param msg       String literal description.
 */
#define TI_SET_ERRC(errc_ptr, code, msg)                                        \
  do {                                                                          \
    if ((errc_ptr) != ((void*)0)) *(enum ti_errc_t *)(errc_ptr) = (code);      \
    ti_log_write((code), (msg), __func__, __FILE__, __LINE__);                  \
  } while (0)
