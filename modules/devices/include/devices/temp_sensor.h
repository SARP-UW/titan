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
 * @file modules/inputs/include/inputs/temp_sensor.h
 * @authors Charles Faisandier
 * @brief Temperature sensor driver interface for the ADT7311 digital temperature sensor.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "periphs/spi.h"
#include "periphs/gpio.h"
#include "util/errc.h"
#include "periphs/rtc.h"

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/
// Sensor callback function type
typedef void (*temp_sensor_callback_t)(bool success);

// Typedef for sensor configuration
typedef struct {
    uint8_t spi_instance;
    uint32_t ss_gpio;
} temp_sensor_config_t;

typedef struct {
    RTC_datetime timestamp;
    float temperature;
} temp_sensor_data_t;

/**************************************************************************************************
 * @section Function Definitions
 **************************************************************************************************/
/**
 * @brief Initializes the ADT7311 sensor.
 *
 * Initializes the SPI device for the temperature sensor.
 * spi_init for the spi instance must be called before this function.
 *
 * @param config Pointer to a configuration structure.
 * @param flag Error flag
 * @param temp_sensor_config: Sensor configuration
 * @return bool Returns true if the sensor was successfully initialized, false otherwise.
 */
 int temp_sensor_init(temp_sensor_config_t *temp_sensor_config);

/**
 * @brief Reads the latest temperature measurement from the sensor.
 *        Stores the result in rx_buff defined by temp_sensor_config.
 * @param flag: Error flag
 */
int temp_sensor_read_temperature();

