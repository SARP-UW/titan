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

#include "util/errc.h"
#include "mcu/dma.h"

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/
typedef enum {
    I2C_ADDR_7BIT,
    I2C_ADDR_10BIT,
} i2c_addr_mode_t;

 typedef struct{
    uint8_t instance; // I2C instance (1-4)
    i2c_addr_mode_t addr_mode;
    int32_t timing;
    bool analog_filter;
    uint8_t digital_filter;
    int scl_pin;
    int sda_pin;
    uint32_t i2c_timeout;
    uint64_t mutex_timeout;
}i2c_config_t ;

struct i2c_device_t {
    uint8_t instance;
    uint16_t address;
};

struct i2c_transfer_sync_t {
    struct i2c_device_t device;
    uint8_t *data;
    size_t size;
};

struct i2c_transfer_async_t {
    struct i2c_device_t device;
    uint8_t *data;
    size_t size;
    uint8_t dma_priority; // 0-3 Incrementing priority
    dma_callback_t callback;
    void *context;
};

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
int i2c_init(i2c_config_t *config);

/**
 * @brief Writes data over I2C to the device with the given address. Asyncronous (DMA-powered) function.
 * @param flag Error flag.
 * @param addr Address of I2C device.
 * @param tx_data Address of data to write.
 * @param size Number of bytes to write.
 * @return Whether the transfer was successful.
 */
int i2c_write_async(struct i2c_transfer_async_t *transfer);

/**
 * @brief Reads data over I2C from the device with the given address. Blocking (syncronous) function.
 * @param flag Error flag.
 * @param addr Address of I2C device.
 * @param rx_data Address of data to read.
 * @param size Number of bytes to read.
 * @return Whether the transfer was successful.
 */
int i2c_read_sync(struct i2c_transfer_sync_t *transfer);

/**
 * @brief Writes data over I2C to the device with the given address. Blocking (syncronous) function.
 * @param flag Error flag.
 * @param addr Address of I2C device.
 * @param tx_data Address of data to write.
 * @param size Number of bytes to write.
 * @return Whether the transfer was successful.
 */
int i2c_write_blocking(struct i2c_transfer_sync_t *transfer);