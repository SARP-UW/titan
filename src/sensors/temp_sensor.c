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
 * @file src/sensors/temp_sensor.c
 * @authors Charles Faisandier
 * @brief Temperature sensor driver implementation for the ADT7311 digital temperature sensor.
 */

#pragma once
#include "temp_sensor.h"
#include <stdint.h>
#include <stdbool.h>
#include "platform/spi.h"
#include "platform/gpio.h"
#include "tal/error.h"

// Sensor configuration parameters
#define SPI_USED SPI1
#define RX_DMA DMA1
#define TX_DMA DMA1
#define SPI_TX_STREAM DMA_STREAM_0
#define SPI_RX_STREAM DMA_STREAM_1
#define DATA_BUFF_ADDR 0x00 // Placeholder for actual data buffer address

static temp_sensor_callback_t sensor_callback = NULL;
static const char *spi_command = "some command"; // Placeholder for actual SPI command

// SPI Callback
void transfer_complete_callback(bool success) {
    sensor_callback(success);    
}

bool temp_sensor_init(tal_flag_t *flag, temp_sensor_callback_t sensor_callback) {
    sensor_callback = sensor_callback;
    spi_config_t spi_config = {
        .instance = SPI_USED,
        .mode = SPI_MODE_0,
        .data_size = SPI_DATA_SIZE_8BIT,
        .baudrate_prescaler = SPI_BAUDRATE_PRESCALER_16,
        .first_bit = SPI_FIRST_BIT_MSB
    };
    dma_config_t in_stream = {
        .instance = RX_DMA,
        .stream = SPI_RX_STREAM,
        .direction = PERIPH_TO_MEM,
        .src_data_size = DMA_DATA_SIZE_BYTE,
        .dest_data_size = DMA_DATA_SIZE_BYTE,
        .src_inc_enabled = false,
        .dest_inc_enabled = true,
        .priority = DMA_PRIORITY_HIGH,
        .fifo_enabled = false,
        .fifo_threshold = 0, // Not used
        .callback = transfer_complete_callback
    };
    dma_config_t out_stream = {
        .instance = TX_DMA,
        .stream = SPI_TX_STREAM,
        .direction = MEM_TO_PERIPH,
        .src_data_size = DMA_DATA_SIZE_BYTE,
        .dest_data_size = DMA_DATA_SIZE_BYTE,
        .src_inc_enabled = true,
        .dest_inc_enabled = false,
        .priority = DMA_PRIORITY_HIGH,
        .fifo_enabled = false,
        .fifo_threshold = 0, // Not used
        .callback = transfer_complete_callback
    };
    return spi_init(flag, &spi_config, &in_stream, &out_stream);
}

void temp_sensor_read_temperature(tal_flag_t *flag) {
    spi_transfer_t transfer = {
        .instance = SPI_USED,
        .rx_instance = RX_DMA,
        .tx_instance = TX_DMA,
        .rx_stream = SPI_RX_STREAM,
        .tx_stream = SPI_TX_STREAM,
        .tx_data = (uint8_t *)spi_command, // Command to send
        .rx_data = (uint8_t *)DATA_BUFF_ADDR, // Buffer to store received data
        .length = sizeof(spi_command) // Length of the command
    };
    spi_transmit(flag, &transfer);
}

