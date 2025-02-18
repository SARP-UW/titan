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
 * @file common/platform/gpio.h
 * @authors Joshua Beard
 * @brief Driver for the GPIO
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
  extern "C" {
#endif

// REMOVE

bool init_gpio(void);

// REMOVE

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param mode: 0 for in, 1 for general purpose output, 2 for alternate function, 3 for analog
*/
void tal_set_mode(int pin, int mode);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param mode: 0 for push pull, 1 for open drain
 */ 
void tal_set_drain(int pin, int drain);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param mode: 0 : Low speed
 *              1 : Medium speed
 *              2 : Fast speed
 *              3 : High speed
 */ 
void tal_set_speed(int pin, int speed);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param pull: -1 for low, 0 for floating, 1 for high
*/
void tal_pull_pin(int pin, int pull);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param value: 0 for off, 1 for on
*/
void tal_set_pin(int pin, int value);

/**
 * Used to configure the alternate mode of the pin if set in alternate modeby #tal_set_mode
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param value: 0000b: AF0
                 0001b: AF1
                 0010b: AF2
                 0011b: AF3
                 0100b: AF4
                 0101b: AF5
                 0110b: AF6
                 0111b: AF7
                 1000b: AF8
                 1001b: AF9
                 1010b: AF10
                 1011b: AF11
                 1100b: AF12
                 1101b: AF13
                 1110b: AF14
                 1111b: AF15
*/
void tal_alternate_mode(int pin, int value);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * 
 * @return true if pin is high, false if pin is low
*/
bool tal_read_pin(int pin);

// add read and write buffer as well

#if defined(__cplusplus)
  }
#endif