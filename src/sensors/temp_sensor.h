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
 * @file src/sensors/temp_sensor.h
 * @authors Charles Faisandier
 * @brief Temperature sensor driver interface for the ADT7311 digital temperature sensor.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "platform/spi.h"
#include "platform/gpio.h"
#include "tal/error.h"

// Sensor callback function type
typedef void (*temp_sensor_callback_t)(bool success);

/**
 * @brief Initializes the ADT7311 sensor.
 *
 * This function performs a hardware check and configures the sensor with the
 * provided settings. It allocates a new sensor instance handle and returns it.
 *
 * @param config Pointer to a configuration structure.
 * @param sensor_handle Pointer to a variable where the new sensor instance handle will be stored.
 * @return bool Returns true if the sensor was successfully initialized, false otherwise.
 */
 bool temp_sensor_init(tal_flag_t *flag, temp_sensor_callback_t sensor_callback);

/**
 * @brief Reads the latest temperature measurement from the sensor.
 *
 * This function initiates a temperature conversion if needed and reads the
 * result from the sensor's temperature register. The value is returned
 * in degrees Celsius. The value is timestamped and and transferred to the 
 * configured memory buffer.
 *
 * @param sensor_handle A handle to the initialized sensor instance.
 * @param sensor_callback callback function to handle the sensor data.
 * @return ADT7311_OK on success, or an error code otherwise.
 */
void temp_sensor_read_temperature(tal_flag_t *flag);

