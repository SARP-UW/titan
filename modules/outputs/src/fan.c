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
 * @file modules/outouts/src/fan.c
 * @authors Charles Faisandier
 * @brief Fan Driver Implementation
 */
#include <stdint.h>
#include "util/errc.h"

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/
struct fan_temp_to_speed_t {
    int32_t temp;
    uint32_t speed;
};

struct fan_config_t {
    struct fan_temp_to_speed_t *table;
    uint8_t table_size;
    uint8_t fan_sel; // Value from 0x00 to 0x1F (bitmask for fans 1-5)
};

/**************************************************************************************************
 * @section Internal Data Structures
 **************************************************************************************************/
struct fan_config_t *config;

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
int fan_init(struct fan_config_t *fan_config) {
    // Store fan config
    config = fan_config;

    // 



    return TI_ERRC_NONE;
}