/**
* This file is part of the Titan Flight Computer Project
* Copyright (c) 2025 UW SARP
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
* @file peripheral/pwm.h
* @authors Joshua Beard, Aaron Mcbride, Jude Merritt
* @brief Interface for the PWM driver
* */


#pragma once
#include <stdint.h>
#include "peripheral/errc.h"


/**************************************************************************************************
* @section Type Definitions
**************************************************************************************************/

struct ti_pwm_config_t {
    uint8_t channel;      /**< PWM channel number (0-based) */
    uint8_t instance;     /**< PWM hardware instance (0-based) */
    uint32_t freq;        /**< Output frequency in Hz */
    uint32_t duty;        /**< Duty cycle (0-1000 for 0-100%) */
    uint32_t clock_freq;  /**< Source clock frequency in Hz */
};


/**************************************************************************************************
* @section Function Definitions
**************************************************************************************************/

/**
 * @brief Configures a timer and GPIO pin to output PWM at the specified frequency and duty cycle.
 *
 * @param pwm_config Takes information from the pwm_config structure
 * @return ti_errc_t error code
 */
enum ti_errc_t ti_set_pwm(struct ti_pwm_config_t pwm_config);