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

extern temp_sensor_config_t temp_sensor_config;

static spi_device_t device = {0};

bool temp_sensor_init(tal_flag_t *flag) {
    device.instance = temp_sensor_config.spi_instance;
    device.gpio_pin = temp_sensor_config.ss_gpio;
    spi_device_init(flag, &device);
}

void temp_sensor_read_temperature(tal_flag_t *flag) {
    spi_transfer_t transfer = {
        .device = &device,
        .tx_data = (uint8_t *)&temp_sensor_config.command, // Command to send
        .rx_data = (uint8_t *)temp_sensor_config.rx_buff, // Buffer to store received data
        .size = sizeof(temp_sensor_config.command) // size of the command
    };
    spi_transmit(flag, &transfer);
}

