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
 * @file modules/mcu/include/mcu/exti.h
 * @authors Charles Faisandier
 * @brief EXTI Interrupt Helpers and ISRs Definitions
 */

 #pragma once
 #include "mcu/gpio.h"

/**************************************************************************************************
 * @section Data Structures
 **************************************************************************************************/
volatile int32_t exti_irq_numbers[PINS];

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/
typedef void (*exti_callback_t)(void);

/**************************************************************************************************
 * @section Functions
 **************************************************************************************************/
 bool exti_enable_isr(uint8_t pin, exti_callback_t *callback, uint32_t priority, bool falling);