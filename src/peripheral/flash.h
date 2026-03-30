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
 * @file peripheral/flash.h
 * @authors Mahir Emran
 * @brief General internal flash driver header.
 */
#pragma once
#include <stdint.h>
#include "peripheral/errc.h"

/**************************************************************************************************
 * @section Public API
 **************************************************************************************************/

/**
 * @brief Writes a block of data to internal Flash.
 *
 * Handles unlocking, waiting for busy, and 256-bit word alignment required by H7.
 * Supports both Flash Bank 1 and Bank 2.
 *
 * @param addr  Target flash address (must be 32-byte aligned).
 * @param data  Pointer to data buffer.
 * @param size  Data size in bytes (must be multiple of 32).
 * @return TI_ERRC_NONE on success, error code otherwise.
 */
enum ti_errc_t ti_internal_flash_write(uint32_t addr, const void *data, uint32_t size);

/**
 * @brief Erases a single sector of internal Flash.
 *
 * @param addr  Any address within the target sector.
 * @return TI_ERRC_NONE on success, error code otherwise.
 */
enum ti_errc_t ti_internal_flash_erase_sector(uint32_t addr);