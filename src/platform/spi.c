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
 * @file common/platform/spi.c
 * @authors Charles Faisandier
 * @brief Implementation of SPI driver interface
 */
#include "platform/spi.h"
#include "tal/error.h"
#include <stdint.h>

bool spi_init(tal_flag_t *flag, spi_config_t *config, dma_config_t *tx_stream, dma_config_t *rx_stream) {
    // TODO: Validate the input parameters
    // TODO: Initialize SPI peripheral with given config sturct

    // Configure TX DMA stream
    dma_configure_stream(flag, tx_stream);
    // Configure RX DMA stream
    dma_configure_stream(flag, rx_stream);
    return true;
}

void spi_transmit(tal_flag_t *flag, spi_transfer_t *transfer) {
    // TODO: Validate the parameters

    // TODO: Figure out the rx and tx registers for the given instance.
    void *rx = 0x0;
    void *tx = 0x0;

    // Start the TX (mem-to-peripheral) transfer.
    dma_start_transfer(flag, transfer->tx_instance, transfer->tx_stream, transfer->tx_data, tx, transfer->length);

    // TODO: Initiate the spi transfer by enabling the SPI peripheral

    // Start the RX (peripheral-to-mem) transfer.
    dma_start_transfer(flag, transfer->rx_instance, transfer->rx_stream, rx, transfer->rx_data, transfer->length);

}