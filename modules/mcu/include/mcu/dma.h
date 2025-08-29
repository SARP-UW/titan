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
 * @file modules/mcu/include/mcu/dma.h
 * @authors Charles Faisandier
 * @brief DMA Public Interface.
 */
#pragma once

#include <stdint.h>
#include "util/errc.h"
#include <stdbool.h>

/**************************************************************************************************
 * @section Macros
 **************************************************************************************************/
#define DMA_INSTANCE_COUNT 2
#define DMA_STREAM_COUNT 8

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/
// Enum for transfer direction
typedef enum {
    PERIPH_TO_MEM,
    MEM_TO_PERIPH,
} dma_direction_t;

// Enum for FIFO threshold
typedef enum {
    DMA_FIFO_THRESHOLD_FULL,
    DMA_FIFO_THRESHOLD_THREEQUARTERS, 
    DMA_FIFO_THRESHOLD_HALF, 
    DMA_FIFO_THRESHOLD_QUARTER, 
} dma_fifo_threshold_t;

// Callback function type for DMA events
typedef void (*dma_callback_t)(bool success, void *context);

/**
 * @brief DMA transfer config
 * 
 * Specifies all necessary parameters for dma transfer.
 */
typedef struct {
    uint32_t request_id;
    dma_direction_t direction;
    uint8_t src_data_size;
    uint8_t dest_data_size;
    uint8_t priority; // 0-3 Incrementing priority
    bool fifo_enabled;
    dma_fifo_threshold_t fifo_threshold;
    dma_callback_t callback;
    const void *src;
    void *dest;
    size_t size;
    void *context;
    bool mem_inc; // Useful for dummy spi transactions
} dma_transfer_t;

typedef struct {
    uint8_t instance;
    uint32_t blocking_timeout; // How many time to poll 
} dma_config_t;

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
/**
 * @brief Initializes the DMA subsystem (enables clocks for all DMA controllers).
 * Should be called once during system boot.
 */
void dma_init(void);

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
int dma_start_transfer(dma_transfer_t *dma_transfer);
