/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2025 UW SARP
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
 * @file peripheral/qspi.h
 * @authors Jude Merritt
 * @brief Quad SPI driver for S25FL064LABMFM010 flash memory chip
 */

#include <stdint.h>
#include <stdbool.h>
#include "../internal/mmio.h"
#include "errc.h"

#pragma once

/**************************************************************************************************
 * @section Type definitions
 **************************************************************************************************/

/**
 * @brief Defines the number of data lines being used for a transaction.
 */
typedef enum {
    QSPI_MODE_NONE,   /**< No data lines used */
    QSPI_MODE_SINGLE, /**< Single data line */
    QSPI_MODE_DUAL,   /**< Dual data lines */
    QSPI_MODE_QUAD    /**< Quad data lines */
} qspi_mode_t;

/**
 * @brief Command data
 */
typedef struct {
    uint8_t instruction;
    qspi_mode_t instruction_mode;
    uint32_t address;
    qspi_mode_t address_mode;
    uint8_t address_size;
    uint8_t dummy_cycles;
    qspi_mode_t data_mode;
    uint32_t data_size;
} qspi_cmd_t;

/**************************************************************************************************
 * @section Function Definitions
 **************************************************************************************************/

/**
 * @brief Initializes the Quad SPI peripheral.
 */
void qspi_init();

/**
 * @brief sends a command to flash memory (read or write). Use qspi_poll_status_blk();
 * After calling this function if you expect to call it again shortly after. Memory is NOT
 * treated as internal memory in this mode (indirect mode). To treat memory as internal
 * you must enter memory mapped mode.
 *
 * @param cmd pointer to the qspi_cmd_t structure.
 * @param data pointer to an array of eight bit integer data in memory. Either read or write 
 * data depending on the value of is_read. If is_read is true, data will be used to store the 
 * data read from external flash memory. If is_read is false, data will be used to specify the 
 * data to be written to external flash memory. You should know the size of the data that you're 
 * expecting if you're reading. 
 * @param is_read specifies whether you want to read or write. If you want to read, set
 * is_read to true.
 * @param errc pointer to an error code, TI_ERRC_NONE if no error occurs. 
 */
void qspi_send_cmd(qspi_cmd_t *cmd, uint8_t *data, bool is_read, enum ti_errc_t *errc);

/**
 * @brief status polling mode ensures that the flash memory chip is not busy.
 * This function should be used in junction with qspi_command(). If qspi_command is
 * being called repeatedly, qspi_poll_status_blk() should be called in between each command.
 */
void qspi_poll_status_blk();

/**
 * @brief entering memory mapped mode enables the CPU to treat flash memory as if it were
 * internal. If memory mapped mode is enabled, you CANNOT use the qspi_command() funciton. If you
 * wish to do so, exit memory mapped mode first.
 *
 * @param cmd pointer to the qspi_cmd_t structure
 */
void qspi_enter_memory_mapped(qspi_cmd_t *cmd);

/**
 * @brief exiting memory mapped mode will disallow the CPU from using flash memory
 * as if it were internal memory. However, it enables the user to use qspi in indirect mode --
 * giving them the ability to read and write to external memory through qspi_command().
 */
void qspi_exit_memory_mapped();