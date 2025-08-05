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
 * @file src/app/peripheral_config.c
 * @authors Charles Faisandier
 * @brief Main configuration file for all peripherals
 */
#include "platform/spi.h"
#include "sensors/temp_sensor.h"

// Example config
spi_config_t spi1_config = { 
   .instance = SPI1,
    .mode = SPI_MODE_0,
    .data_size = SPI_DATA_SIZE_16BIT,
    .baudrate_prescaler = SPI_BAUDRATE_PRESCALER_128,
    .first_bit = SPI_FIRST_BIT_LSB,
};

// Example config
spi_dma_config_t spi1_dma_tx_config = {
    .instance = DMA1,
    .stream = DMA_STREAM_0,
    .direction = PERIPH_TO_MEM,
    .src_data_size = DMA_DATA_SIZE_WORD,
    .dest_data_size = DMA_DATA_SIZE_WORD,
    .src_inc_enabled = false,
    .dest_inc_enabled = false,
    .priority = DMA_PRIORITY_HIGH,
    .fifo_enabled = false,
    .fifo_threshold = 0,
};

// Example config
spi_dma_config_t spi1_dma_rx_config = {
    .instance = DMA1,
    .stream = DMA_STREAM_1,
    .direction = MEM_TO_PERIPH,
    .src_data_size = DMA_DATA_SIZE_WORD,
    .dest_data_size = DMA_DATA_SIZE_WORD,
    .src_inc_enabled = false,
    .dest_inc_enabled = true,
    .priority = DMA_PRIORITY_HIGH,
    .fifo_enabled = true,
    .fifo_threshold = DMA_FIFO_THRESHOLD_FULL,
};

// Example config
const temp_sensor_config_t temp_sensor_config = {
    .spi_instance = SPI1,
    .ss_gpio = 0,
    .command = "some command",
    .rx_buff = 0x0,
};