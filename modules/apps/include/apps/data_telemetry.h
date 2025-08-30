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
 * @file modules/app/include/app/data_telemetry.h
 * @authors Charles Faisandier
 * @brief Data telemetry module interface.
 */
#include <stdbool.h>
#include "devices/radio.h"


/**************************************************************************************************
 * @section Data Types
 **************************************************************************************************/
 struct ti_data_ready_t {
    gnss_ready;
    temp_sensor_ready;
 };

struct data_telemetry_config_t {
    struct ti_semaphore_t *semaphore;
    uint32_t semaphore_timeout;
    struct ti_data_ready_t *data_ready;
    struct radio_config_t *radio_config;
    uint8_t channel;
    uint32_t thread_prio;
};

/**************************************************************************************************
 * @section Functions
 **************************************************************************************************/
int data_telemetry_start(struct data_telemetry_config_t *config);

void data_telemetry_stop();