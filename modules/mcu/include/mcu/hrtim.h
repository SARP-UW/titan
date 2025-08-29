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
 * @file modules/mcu/include/mcu/timer.h
 * @authors Charles Faisandier
 * @brief STM32H7 timer interface.
 */
#include "stdint.h"

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/
struct hrtim_config_t {
    uint8_t prescaler; // 5: 1, 6: 2, 7: 4 
    uint16_t period; // Repetition period value, 7 bits.
    void (*callback) (void);
    uint8_t priority;
};

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
int hrtim_enable_mrep(struct hrtim_config_t *config);