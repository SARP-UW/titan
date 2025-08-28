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
 * @file modules/mcu/include/mcu/spi.h
 * @authors Charles Faisandier
 * @brief Interface for the SPI driver
 */

 #pragma once
 #include "util/errc.h"
 #include "mcu/dma.h"

/**************************************************************************************************
 * @section Macros
 **************************************************************************************************/
#define IS_VALID_DEVICE(device) ((device.instance > 0) && (device.instance < 7) && device.gpio_pin != 0)
#define SPI_INSTANCE_COUNT 6

/**************************************************************************************************
 * @section Type definitions
 **************************************************************************************************/
/**
 * @brief Description struct for SPI device
 * 
 * Used to describe which SPI instance and CS line to use for SPI transactions
 */
typedef struct {
    uint8_t instance;
    int32_t gpio_pin;
} spi_device_t;

/**
 * @brief SPI Config structure.
 *
 * Used to configure the SPI controller specified by the instance field.
 */
typedef struct {
    uint8_t mode;     
    uint8_t data_size; 
    uint8_t baudrate_prescaler; // Controls communication speed
    uint8_t first_bit; // 0 for LSB 1 for MSB
    uint8_t clk_pin;
    uint8_t miso_pin;
    uint8_t mosi_pin;
    uint8_t priority; // DMA priority
    uint64_t mutex_timeout;
    uint32_t blocking_timeout;
} spi_config_t;

typedef void (*spi_callback_t)(bool success);

// Passed to DMA streams to un-init the SPI transfer
typedef struct {
    spi_device_t device;
    uint8_t num_complete; // Number of DMA streams complete
    spi_callback_t callback;
} spi_context_t;

/**************************************************************************************************
 * @section Function Definitions
 **************************************************************************************************/
/**
 * @brief Initializes an SPI controller. Configures a TX and RX DMA stream for the SPI peripheral. 
 * It's important to choose SPI parameters that are compatible with all devices that will share the
 * controller.
 * 
 * @param flag Flag pointer for error heandling
 * @param config Point to config structure
 * @param tx_stream DMA configuration for TX stream
 * @param rx_stream DMA configuration for RX stream
 */
int spi_init(uint8_t instance, spi_config_t *spi_config);

/**
 * @brief Initialize an SPI Device. This sets up the CS line for the device
 * @param flag Pointer to the flag structure
 * @param device SPI device
 * @return true if initialization was successful, false otherwise.
 */
int spi_device_init(spi_device_t device);

 /**
  * @brief Writes data over SPI asyncronously
  * @param flag Error flag
  * @param device Spi device to use
  * @param source Pointer to source data
  * @param size Size of source data in bytes
  * @returns Whether the SPI write successfuly started, false if device is busy.
  */
 int spi_write_async(spi_device_t device, void *source, size_t size, spi_callback_t callback);

 /**
  * @brief Writes data over SPI asyncronously
  * @param flag Error flag
  * @param device Spi device to use
  * @param dest Pointer to rx data buffer
  * @param size Size of rx data in bytes
  */
int spi_read_async(spi_device_t device, void *dest, size_t size, spi_callback_t callback, uint8_t dest_data_size);

 /**
  * @brief Writes data over SPI syncronously 
  * @param flag Error flag
  * @param device Spi device to use
  * @param source Pointer to source data
  * @param size Size of source data in bytes
  */
int spi_write_blocking(spi_device_t device, void *source, size_t size);

 /**
  * @brief Writes data over SPI syncronously
  * @param flag Error flag
  * @param device Spi device to use
  * @param dest Pointer to rx data buffer
  * @param size Size of rx data in bytes
  */
int spi_read_blocking(spi_device_t device, void *dest, size_t size);
