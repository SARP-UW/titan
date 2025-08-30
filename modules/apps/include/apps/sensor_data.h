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
 * @file modules/app/include/app/sensor_data.h.
 * @authors Charles Faisandier
 * @brief Declares sensor data buffers.
 */
#include "devices/gnss.h"
#include "devices/temp_sensor.h"

// Create the type.
struct ti_transmit_packet_t {
    gnss_data_t gnss_data;
    temp_sensor_data_t temp_sens_data;
};

// The actual instance.
struct ti_transmit_packet_t sensor_data;

size_t sensor_data_size;