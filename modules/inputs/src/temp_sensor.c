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
 * @file module/inputs/src/temp_sensor.c
 * @authors Charles Faisandier
 * @brief Temperature sensor driver implementation for the ADT7311 digital temperature sensor.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "inputs/temp_sensor.h"
#include "mcu/spi.h"
#include "mcu/gpio.h"
#include "util/errc.h"
#include "app/mem_loc.h"
#include "mcu/rtc.h"

/**************************************************************************************************
 * @section Internal Data Structures
 **************************************************************************************************/
temp_sensor_config_t *config;

static spi_device_t device = {0};

typedef enum {
    REG_SIZE_8 = 1,
    REG_SIZE_16,
} temp_sensor_reg_size_t;

/**************************************************************************************************
 * @section Private Function Implementations
 **************************************************************************************************/
int temp_sensor_write_register(uint8_t reg_addr, uint16_t data, temp_sensor_reg_size_t size) {
    if (reg_addr > 7) { // reg_addr must be 000 to 111
        return TI_ERRC_INVALID_ARG;
    }
    uint8_t command_byte = reg_addr;   
    command_byte = command_byte << 3;
    int errt = spi_write_blocking(device, &command_byte, 1);
    if (!errt) {
        return errt;
    }

    errt = spi_write_blocking(device, &data, size);
    if (!errt) {
        return errt;
    }
    return TI_ERRC_NONE;
}

int temp_sensor_read_register(uint8_t reg_addr, void *dest, temp_sensor_reg_size_t size) {
    if (reg_addr > 7) {
        return TI_ERRC_INVALID_ARG;
    }
    uint8_t command_byte = 8;  // Set it to 1000
    command_byte |= reg_addr;
    command_byte = command_byte << 3;
    int errt = spi_write_blocking(device, &command_byte, 1);
    if (!errt) {
        return errt;
    }
    errt = spi_read_blocking(device, dest, size);
    if (!errt) {
        return errt;
    }
    return TI_ERRC_NONE;
}
/**************************************************************************************************
 * @section Public Function Implementations
 **************************************************************************************************/
int temp_sensor_init(temp_sensor_config_t *temp_sensor_config) {
    // TODO: Check parameters

    // Save config
    config = temp_sensor_config;

    // Save device
    device.instance = temp_sensor_config->spi_instance;
    device.gpio_pin = temp_sensor_config->ss_gpio;

    // Configure temperature sensor
    uint8_t config = 0b00000001; // All default except 16-bit resolution
    int errt = temp_sensor_write_register(0x01, config, REG_SIZE_8);
    if (!errt) {
        return errt;
    }

    // Configure spi device
    errt = spi_device_init(device);
    if (!errt) {
        return errt;
    }

    return TI_ERRC_NONE;
}

int temp_sensor_read_temperature() {
    int16_t temp;
    int errt = temp_sensor_read_register(0x02, &temp, REG_SIZE_16);
    if (!errt)
        return errt;
    temp_sensor_data_buff.temperature = (float) temp / 128.0f;
    temp_sensor_data_buff.timestamp = tal_read_RTC();
}    

