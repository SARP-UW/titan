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
 * @file common/platform/spi.h
 * @authors Charles Faisandier
 * @brief Interface for the SPI driver
 */

 #pragma once
 #include "tal/error.h"
 #include "platform/dma.h"

/**************************************************************************************************
 * @section Type definitions
 **************************************************************************************************/
/**
 * @brief Enumeration of the four standard SPI modes.
 *
 * Each mode is a unique combination of CPOL and CPHA settings.
 */
#define SPI_MODE_MIN 0
typedef enum {
    SPI_MODE_0 = SPI_MODE_MIN, // CPOL=0, CPHA=0
    SPI_MODE_1,     // CPOL=0, CPHA=1
    SPI_MODE_2,     // CPOL=1, CPHA=0
    SPI_MODE_3,     // CPOL=1, CPHA=1
    SPI_MODE_COUNT  
} spi_mode_t;

/**
 * @brief Enumeration of SPI instances
 *
 * Each instance is a unique SPI peripheral on the microcontroller.
 */
#define SPI_INSTANCE_MIN 1
typedef enum {
    SPI1 = SPI_INSTANCE_MIN,
    SPI2,
    SPI3,
    SPI4,
    SPI5,
    SPI6,
    SPI_INSTANCE_COUNT
} spi_instance_t;

/**
 * @brief Enumeration of SPI data sizes
 *
 * Each data size represents the number of bits in a single SPI transfer.
 */
#define SPI_DATA_SIZE_MIN 0
typedef enum {
    SPI_DATA_SIZE_8BIT = SPI_DATA_SIZE_MIN, // 8 bits per transfer
    SPI_DATA_SIZE_16BIT,    // 16 bits per transfer
    SPI_DATA_SIZE_COUNT
} spi_data_size_t;

/**
 * @brief Enumeration for the SPI baudrate prescaler.
 *
 * This divides the SPI clock source to achieve the desired baudrate.
 * The resulting baudrate is F_SPI / prescaler_value.
 */
#define SPI_BAUDRATE_PRESCALER_MIN 0
typedef enum {
    SPI_BAUDRATE_PRESCALER_2 = SPI_BAUDRATE_PRESCALER_MIN,
    SPI_BAUDRATE_PRESCALER_4,
    SPI_BAUDRATE_PRESCALER_8,
    SPI_BAUDRATE_PRESCALER_16,
    SPI_BAUDRATE_PRESCALER_32,
    SPI_BAUDRATE_PRESCALER_64,
    SPI_BAUDRATE_PRESCALER_128,
    SPI_BAUDRATE_PRESCALER_256,
    SPI_BAUDRATE_PRESCALER_COUNT
} spi_baudrate_prescaler_t;

/**
 * @brief Enumeration for the SPI first bit configuration.
 *
 * This determines the order in which data bits are transmitted and received.
 * MSB first is the default and most common setting.
 */
#define SPI_FIRST_BIT_MIN 0
typedef enum {
    SPI_FIRST_BIT_MSB = SPI_FIRST_BIT_MIN, // Most Significant Bit first
    SPI_FIRST_BIT_LSB,     // Least Significant Bit first
    SPI_FIRST_BIT_COUNT
} spi_first_bit_t;

/**
 * @brief Description struct for SPI device
 * 
 * Used to describe which SPI instance and CS line to use for SPI transactions
 */
typedef struct {
    spi_instance_t instance;
    int32_t gpio_pin;
} spi_device_t;

/**
 * @brief SPI Config structure.
 *
 * Used to configure the SPI controller specified by the instance field.
 */
typedef struct {
    spi_instance_t instance;
    spi_mode_t mode;     
    spi_data_size_t data_size; 
    spi_baudrate_prescaler_t baudrate_prescaler; // Controls communication speed
    spi_first_bit_t first_bit;                   // Whether the first bit is sent first or last
    uint16_t dev_count;                          // Number of slaves for this spi instance
} spi_config_t;

/**
 * @brief SPI transfer specifier structure.
 *
 * Specifies parameters used to define an SPI transfer.
 */
typedef struct {
    spi_device_t *device; // SPI device to use
    uint8_t *tx_data; // Pointer to transmit data buffer
    uint8_t *rx_data; // Pointer to receive data buffer
    size_t size;    // size of data to transfer 
} spi_transfer_t;

// Passed to DMA streams to un-init the SPI transfer
typedef struct {
    bool *busy;
    spi_device_t *device;
    uint8_t num_complete; // Number of DMA streams complete
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
bool spi_init(tal_flag_t *flag, spi_config_t *config, dma_callback_t callback,
             periph_dma_config_t *tx_stream, periph_dma_config_t *rx_stream);

/**
 * @brief Initialize an SPI Device. This sets up the CS line for the device
 * @param flag Pointer to the flag structure
 * @param device Pointer to the specific SPI device
 * @return true if initialization was successful, false otherwise.
 */
 bool spi_device_init(tal_flag_t *flag, spi_device_t *device);

 /**
  * @brief Writes data over SPI asyncronously
  * @param flag Error flag
  * @param device Spi device to use
  * @param source Pointer to source data
  * @param size Size of source data in bytes
  * @returns Whether the SPI write successfuly started, false if device is busy.
  */
 bool spi_write_async(tal_flag_t *flag, spi_device_t *device, void *source, size_t size);

 /**
  * @brief Writes data over SPI asyncronously
  * @param flag Error flag
  * @param device Spi device to use
  * @param dest Pointer to rx data buffer
  * @param size Size of rx data in bytes
  */
 bool spi_read_async(tal_flag_t *flag, spi_device_t *device, void *dest, size_t size);

 /**
  * @brief Writes data over SPI syncronously 
  * @param flag Error flag
  * @param device Spi device to use
  * @param source Pointer to source data
  * @param size Size of source data in bytes
  */
bool spi_write_blocking(tal_flag_t *flag, spi_device_t *device, void *source, size_t size);

 /**
  * @brief Writes data over SPI syncronously
  * @param flag Error flag
  * @param device Spi device to use
  * @param dest Pointer to rx data buffer
  * @param size Size of rx data in bytes
  */
 bool spi_read_blocking(tal_flag_t *flag, spi_device_t *device, void *dest, size_t size);