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
 * @file modules/app/src/mem_loc.c
 * @authors Charles Faisandier
 * @brief Defines memory buffers used by data collection system
 */

 #include "app/mem_loc.h"
 #include "inputs/temp_sensor.h"
 #include "inputs/gnss.h"

// Sensor data buffers
temp_sensor_data_t temp_sensor_data_buff = {0};
gnss_data_t gnss_data_buff = {0};
