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
 * @file modules/outouts/src/fan.h
 * @authors Charles Faisandier
 * @brief Fan Driver Interface
 */
#include <stdint.h>
#include "mcu/i2c.h"

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/

struct fan_temp_to_speed_t {
    int32_t temp;
    uint16_t speed;
};

struct fan_config_t {
    struct i2c_device_t device;
    struct fan_temp_to_speed_t *table;
    uint8_t table_size;
    bool polarity; // if true: 0 is 100% 0xFF is 0%
    bool pwm_drive;// if true: PWM drive is push-pull, otherwise open drain
    uint8_t pwm_freq_divide;
    uint8_t min_drive;
};

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/

int fan_init(struct fan_config_t *fan_config);

int fan_update_speed(double temp);