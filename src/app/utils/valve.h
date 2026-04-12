/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
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
 * @file app/utils/valve.h
 * @authors Joshua Beard, Mahir Emran
 * @brief Utility functions to actuate valves by name
 */

#include "peripheral/errc.h"
#include <stdbool.h>
#include <stdint.h>

struct valve_t {
    int32_t pin_1; // pwm pin if PWM, MOSI if spi
    int32_t pin_2; // nothing if PWM, MISO if spi
    int32_t pin_3; // CS if SPI, nothing if PWM
    bool is_spi; // boolean if spi or pwm
    uint8_t channel; // actuator channel if SPI
};

/**
 * @param valve Valve name to actuate as defined in the Valve enum
 * @param actuated True if providing power to valve, False if unpowering valve
 * @param errc Error code pointer to store any error that occurs
 *
 * @note The actuated parameter is done this way (instead of open/closed) because some
 * valves may have a different default state and it would become confusing in software
 * to need to track which ones need power or a lack of power to reach a commanded state
 */
void set_valve(struct valve_t* valve, bool actuated, enum ti_errc_t* errc);