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
#include "mcu/i2c.h"
#include "outputs/fan.h"

/**************************************************************************************************
 * @section Internal Data Structures
 **************************************************************************************************/
struct fan_config_t *config;

/**************************************************************************************************
 * @section Private functions
 **************************************************************************************************/
// Takes register address and value and sets it
int set_register(uint8_t addr, uint8_t val) {
    struct i2c_transfer_sync_t swl  = {
      .device = {
        .instance = config->device.instance,
        .address = config->device.address,
      },
      .data = {addr, val},
      0x02,
    };
    int errc = i2c_write_blocking(&swl);
    if (errc != TI_ERRC_NONE)
        return errc;
    return TI_ERRC_NONE;
}

// Takes register address and value and sets it
int set_all_register(uint8_t addr, uint8_t val) {
    for (int i = addr; i <= addr + 0x40; i += 0x10) {
        int errc = set_register(i, val);
        if (!errc)
            return errc;
    }
    return TI_ERRC_NONE;
}

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
int fan_init(struct fan_config_t *fan_config) {
    // Store fan config
    config = fan_config;

    set_register(0xef, 0x01); // Disable software lock
    uint8_t polarity = config->polarity ? 0xF1 : 0x00;
    set_register(0x2a, polarity); 
    uint8_t pwm_drive = config->pwm_drive ? 0xF1 : 0x00;
    set_register(0x2b, pwm_drive); 
    // TODO: Maybe change PWM frequency
    set_all_register(0x31, config->pwm_freq_divide);
    set_all_register(0x32, 0x80); // Enable closed loop RPM System
    set_all_register(0x33, 0x40); // Ramp control
    // TODO: Configure GAIN?
    set_all_register(0x38, config->min_drive);
    set_register(0xef, 0x00); // Enable software lock

    return TI_ERRC_NONE;
}

int fan_update_speed(double temp) {
    // Find the correct speed.
    uint16_t speed = 0;
    for (int i = 0; i < config->table_size; i++) {
        if (temp > config->table[i].temp && ((i + 1) == config->table_size || temp < config->table[i + 1].temp))
            speed = config->table[i].speed;
    }

    // Configure the fans to this speed
    for (int addr = 0x3C; addr <= 0x7C; addr += 0x10 ) {
       struct i2c_transfer_sync_t tach_cmd = {
            addr,
            ((uint8_t*)&speed)[1],
            ((uint8_t*)&speed)[0],
       };
       int errc = i2c_write_blocking(&tach_cmd);
       if (!errc) {
            return errc;
       }
    }

    return TI_ERRC_NONE;
}