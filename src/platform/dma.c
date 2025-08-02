/**
 * This file is part of the Titan Library.
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
 * @internal
 * @file src/platform/dma.c
 * @authors Charles Faisandier
 * @brief DMA Driver implementation
 */
#include "tal/error.h"
#include "platform/dma.h"
#include "platform/mmio.h"

// Data structure to store DMA callbacks
dma_callback_t dma_callbacks[DMA_INSTANCE_COUNT][DMA_STREAM_COUNT] = {0};

/**
 * @brief Initializes the DMA subsystem (enables clocks for all DMA controllers).
 * Should be called once during system boot.
 */
tal_err_t *dma_init(void) {
    // TODO: DMA Initialization Implementation
}

/**
 * @brief Configures a specific DMA stream to a specific request ID, and enables it.
 * This allocates and sets up the chosen stream based on the provided configuration.
 * @param config Pointer to the configuration structure.
 * @param flag Pointer to the flag structure for error handling.
 */
bool dma_configure_stream(tal_flag_t *flag, const dma_config_t* config) {
    // TODO: Validate the parameters
    // register callback
    dma_callbacks[config->instance][config->stream] = config->callback;
    // TODO: DMA Stream Configuration Implementation
    // Disable the stream
    // Modify CF register values according to config
    // Enable the stream
}

/**
 * @brief Starts a DMA transfer for the specified stream.
 * This function initiates the transfer based on the previously configured settings.
 * @param instance The DMA instance (DMA1, DMA2, MDMA, BDMA).
 * @param stream The specific stream to start.
 * @param src Pointer to the source data buffer.
 * @param dest Pointer to the destination data buffer.
 * @param size Number of bytes to transfer.
 */
bool dma_start_transfer(tal_flag_t *flag, dma_instance_t instance, dma_stream_t stream, const void* src, void* dest, size_t size) {
    // TODO: Validate parameters
    // TODO: dma_start_transfer implementation
}

// THIS IS AN EXAMPLE OF HOW TO HANDLE DMA IRQs
// I'M NOT SURE IF THIS CORRESPONDS TO THE RIGHT DMA STREAM
void irq_9_handler(void) { // Handler for DMA1 Stream 1 (for example)
    dma_callbacks[DMA1][DMA_STREAM_1](true);
}
