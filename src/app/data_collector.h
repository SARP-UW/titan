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
 * @file src/app/data_collector.h
 * @authors Charles Faisandier
 * @brief Public interface for the data collector subsystem.
 */

#pragma once
#include "tal/error.h"

// Callback function type
typedef void (*data_collector_callback_t)(tal_err_t *err, size_t buffsize);

// Indicates which sensors have successfully transferred data
typedef struct {
    bool temp_sensor; 
} sensor_data_ready_t;

/**
 * @brief Initializes the data collector subsystem.
 *
 * This function sets up the data collector to start collecting data from sensors.
 * It should be called after all sensors have been initialized.
 *
 * @return tal_err_t* Returns a pointer to an error flag if initialization fails, NULL otherwise.
 */
tal_err_t *data_collector_init(data_collector_callback_t logger_callback);

/**
 * @brief Starts the data collection process.
 *
 * This function begins the data collection loop, which will run indefinitely
 * until stopped by the system manager or an error occurs.
 */
void data_collector_start(sensor_data_ready_t *sensor_data_ready);