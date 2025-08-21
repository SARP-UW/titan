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
 * @file src/app/dma.h
 * @authors Charles Faisandier
 * @brief DMA Public Interface.
 */
#pragma once

#include <stdint.h>
#include "tal/error.h"

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/

// Enum to identify a specific DMA stream/channel within an instance
// For DMA1/2, typically 0-7. For MDMA/BDMA, might be single or fewer channels.
#define DMA_STREAM_MIN 0
typedef enum {
    MDMA_STREAM_0 = DMA_STREAM_MIN,
    MDMA_STREAM_1,
    MDMA_STREAM_2,
    MDMA_STREAM_3,
    MDMA_STREAM_4,
    MDMA_STREAM_5,
    MDMA_STREAM_6,
    MDMA_STREAM_7,
    MDMA_STREAM_8,
    MDMA_STREAM_9,
    MDMA_STREAM_10,
    MDMA_STREAM_11,
    MDMA_STREAM_COUNT 
} mdma_stream_t;

// EMnum for data transfer size (per item)
#define DMA_DATA_SIZE_MIN 0
typedef enum {
    MDMA_DATA_SIZE_BYTE = DMA_DATA_SIZE_MIN,
    MDMA_DATA_SIZE_HALFWORD,
    MDMA_DATA_SIZE_WORD,    
    MDMA_DATA_SIZE_COUNT
} mdma_data_size_t;

// Enum for DMA priority
#define DMA_PRIORITY_MIN 0
typedef enum {
    MDMA_PRIORITY_LOW = DMA_PRIORITY_MIN,
    MDMA_PRIORITY_MEDIUM,
    MDMA_PRIORITY_HIGH,
    MDMA_PRIORITY_VERY_HIGH,
    MDMA_PRIORITY_COUNT
} mdma_priority_t;

#define DMA_FIFO_THRESHOLD_MIN 0
typedef enum {
    DMA_FIFO_THRESHOLD_FULL = DMA_FIFO_THRESHOLD_MIN, 
    DMA_FIFO_THRESHOLD_THREEQUARTERS, 
    DMA_FIFO_THRESHOLD_HALF, 
    DMA_FIFO_THRESHOLD_QUARTER, 
    DMA_FIFO_THRESHOLD_COUNT
} mdma_fifo_threshold_t;

// Callback function type for DMA events
typedef void (*mdma_callback_t)(bool success, void *context);

// Configuration structure for a DMA stream
typedef struct {
    mdma_stream_t     stream;        // Specific stream/channel (0-7 for DMA1/2)
    mdma_data_size_t  src_data_size; // Source data width
    mdma_data_size_t  dest_data_size; // Destination data width
    mdma_priority_t   priority;
    mdma_callback_t   callback;
} mdma_config_t;

/**************************************************************************************************
* @section Public Functions
**************************************************************************************************/
/**
 * @brief Initializes the DMA subsystem (enables clocks for all DMA controllers).
 * Should be called once during system boot.
 */
tal_err_t *dma_init(void);

/**
 * @brief Configures a specific DMA stream to a specific request ID, and enables it.
 * This allocates and sets up the chosen stream based on the provided configuration.
 * @param config Pointer to the configuration structure.
 * @param flag Pointer to the flag structure for error handling.
 * @return true if the stream was successfully configured, false otherwise.
 */
bool mdma_configure_stream(tal_flag_t *flag, const mdma_config_t* config);

/**
 * @brief Starts a DMA transfer for the specified stream.
 * This function initiates the transfer based on the previously configured settings.
 * @param instance The DMA instance (DMA1, DMA2, MDMA, BDMA).
 * @param stream The specific stream to start.
 * @param src Pointer to the source data buffer.
 * @param dest Pointer to the destination data buffer.
 * @param size Number of bytes to transfer.
 * @return bool, whether the transfer was successfully started.
 */
bool mdma_start_transfer(tal_flag_t *flag, mdma_stream_t stream, const void* src, void* dest, size_t size, void *context);
