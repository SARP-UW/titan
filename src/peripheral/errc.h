/**
 * This file is part of the Titan Project.
 * Copyright (c) 2024 UW SARP
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
