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
 * @brief SPI DMA Config structure.
 *
 * Exact copy of spi_dma_config_t, but w/o the request_id field.
 * The driver should be able to figure out request_id based on the SPI instance.
 */
typedef struct {
    dma_instance_t   instance;      // DMA1, DMA2, MDMA, BDMA
    dma_stream_t     stream;        // Specific stream/channel (0-7 for DMA1/2)
    dma_direction_t  direction;
    dma_data_size_t  src_data_size; // Source data width
    dma_data_size_t  dest_data_size; // Destination data width
    bool             src_inc_enabled; // Source address increment
    bool             dest_inc_enabled; // Destination address increment
    dma_priority_t   priority;
    bool             fifo_enabled;    // For DMA1/2
    uint32_t         fifo_threshold; // FIFO threshold for DMA1/2 (e.g., DMA_FIFO_THRESHOLD_FULL)
    dma_callback_t   callback;
} spi_dma_config_t;

/**
 * @brief Enumeration of the four standard SPI modes.
 *
 * Each mode is a unique combination of CPOL and CPHA settings.
 */
typedef enum {
    SPI_MODE_0 = 0, // CPOL=0, CPHA=0
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
typedef enum {
    SPI1 = 0,
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
typedef enum {
    SPI_DATA_SIZE_8BIT = 0, // 8 bits per transfer
    SPI_DATA_SIZE_16BIT,    // 16 bits per transfer
    SPI_DATA_SIZE_COUNT
} spi_data_size_t;

/**
 * @brief Enumeration for the SPI baudrate prescaler.
 *
 * This divides the SPI clock source to achieve the desired baudrate.
 * The resulting baudrate is F_SPI / prescaler_value.
 */
typedef enum {
    SPI_BAUDRATE_PRESCALER_2 = 0,
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
typedef enum {
    SPI_FIRST_BIT_MSB = 0, // Most Significant Bit first
    SPI_FIRST_BIT_LSB,     // Least Significant Bit first
    SPI_FIRST_BIT_COUNT
} spi_first_bit_t;

// SPI configuration structure
typedef struct {
    spi_instance_t instance;
    spi_mode_t mode;     
    spi_data_size_t data_size; 
    spi_baudrate_prescaler_t baudrate_prescaler; // Controls communication speed
    spi_first_bit_t first_bit;                   // Whether the first bit is sent first or last
} spi_config_t;

// Struct for specifying SPI transfer parameters
typedef struct {
    spi_instance_t instance; // SPI instance to use
    dma_instance_t rx_instance; // DMA instance for receive
    dma_instance_t tx_instance; // DMA instance for transmit
    dma_stream_t tx_stream;  // DMA stream for transmit
    dma_stream_t rx_stream;  // DMA stream for receive  
    uint8_t *tx_data; // Pointer to transmit data buffer
    uint8_t *rx_data; // Pointer to receive data buffer
    size_t length;    // Length of data to transfer
} spi_transfer_t;

/**************************************************************************************************
 * @section Function Definitions
 **************************************************************************************************/
/**
 * @brief Initialize an SPI instance. This instance will connected to a single CS pin. Allowing for
 * only one device to be connected to the SPI instance at a time. This function also sets up the
 * DMA for the SPI instance.
 * @param flag Pointer to the flag structure
 * @param spi_callback Callback function to be called on SPI events
 * @param config Pointer to the SPI configuration structure
 * @return true if initialization was successful, false otherwise.
 */
 bool spi_init(tal_flag_t *flag, spi_config_t *config, 
              dma_config_t *tx_stream, dma_config_t *out_stream);

/**
 * @brief Transmit data over SPI, receives a command through tx_data, and stores the response in rx_data.
 * @param flag Pointer to the flag structure
 * @param instance The SPI instance to use
 * @param tx_data Pointer to the data to transmit
 * @param rx_data Pointer to the buffer for received data
 * @param length The length of the data to transmit
 */
 void spi_transmit(tal_flag_t *flag, spi_transfer_t *transfer);
