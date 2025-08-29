/**
 * This file is part of the Titan Flight Computer Project
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
 * @file src/platform/i2c.c
 * @authors Charles Faisandier, Joshua Beard
 * @brief I2C driver implementation
 */

#include "tal/error.h"
#include "platform/dma.h"

// This interface only supports a single I2C at a time.
// Only I2C 1-3 are supported.
#define I2C_INSTANCE 1

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/
typedef enum {
    I2C_ADDR_7BIT,
    I2C_ADDR_10BIT,
} i2c_addr_mode_t;

 typedef struct{
    i2c_addr_mode_t addr_mode;
    int32_t timing;
    bool analog_filter;
    uint8_t digital_filter;
    int scl_pin;
    int sda_pin;
    uint32_t timeout;
}i2c_config_t ;

// Callback function type for I2C transactions
typedef void (*i2c_callback_t)(bool success);

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/

/**
 * @brief Initializes the I2C instance defined by I2C_INSTANCE
 * @param flag Errof flag.
 * @param config Configuration structure.
 * @param callback The DMA callback.
 * @param tx_stream DMA configuration for tx stream.
 * @param tx_stream DMA configuration for rx stream.
 */
bool i2c_init(tal_flag_t *flag, i2c_config_t *config, dma_callback_t callback, periph_dma_config_t *tx_stream, periph_dma_config_t *rx_stream);

/**
 * @brief Reads data over I2C from the device with the given address. Asyncronous (DMA-powered) function.
 * @param flag Error flag.
 * @param addr Address of I2C device.
 * @param rx_data Address of data to read.
 * @param size Number of bytes to read.
 * @return Whether the transfer was successful.
 */
bool i2c_read_async(tal_flag_t *flag, uint16_t addr, uint8_t *rx_data, size_t size);

/**
 * @brief Writes data over I2C to the device with the given address. Asyncronous (DMA-powered) function.
 * @param flag Error flag.
 * @param addr Address of I2C device.
 * @param tx_data Address of data to write.
 * @param size Number of bytes to write.
 * @return Whether the transfer was successful.
 */
bool i2c_write_async(tal_flag_t *flag, uint16_t addr, uint8_t *tx_data, size_t size);

/**
 * @brief Reads data over I2C from the device with the given address. Blocking (syncronous) function.
 * @param flag Error flag.
 * @param addr Address of I2C device.
 * @param rx_data Address of data to read.
 * @param size Number of bytes to read.
 * @return Whether the transfer was successful.
 */
bool i2c_read_blocking(tal_flag_t *flag, uint16_t addr, uint8_t *tx_data, size_t size);

/**
 * @brief Writes data over I2C to the device with the given address. Blocking (syncronous) function.
 * @param flag Error flag.
 * @param addr Address of I2C device.
 * @param tx_data Address of data to write.
 * @param size Number of bytes to write.
 * @return Whether the transfer was successful.
 */
bool i2c_write_blocking(tal_flag_t *flag, uint16_t addr, uint8_t *tx_data, size_t size);