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
 * @file common/platform/pwm.h
 * @authors Ethan Rad
 * @brief Driver for pulse-width modulation
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>


#if defined(__cplusplus)
  extern "C" {
#endif

/**
 * @param pin: The integer value of the pin
 * @param frequency: The PWM frequency of the pin
 * @param dutyCycle: The duty cycle of the pwm signal on a scale of 0 to 255
*/
void tal_pwm_init(int pin, int frequency, uint8_t dutyCycle, bool* const err);

/**
 * @param pin: The integer value of the pin
 * @param frequency: The PWM frequency of the pin
*/
void tal_pwm_set_freq(int pin, int frequency, bool* const err);

/**
 * @param pin: The integer value of the pin
 * @param dutyCycle: The duty cycle of the pwm signal on a scale of 0 to 255
*/
void tal_pwm_set_duty_cycle(int pin, uint8_t dutyCycle, bool* const err);

/**
 * @param pin: The pin to enable PWM on
*/
void tal_pwm_enable(int pin, bool* const err);

/**
 * @param pin: The pin to disable PWM on
*/
void tal_pwm_disable(int pin, bool* const err);

/**
 * @param pin: The pin which is to be checked if it is running
 *
 * @return: true if pwm on the pin is on, false if it is off 
*/
bool tal_pwm_is_running(int pin, bool* const err);

volatile int32_t* LPTIM1_Base = (int32_t*)1073751040; // hex 0x40002400   
volatile int32_t* LPTIM2_Base = (int32_t*)1476404224; // hex 0x58002400  
volatile int32_t* LPTIM3_Base = (int32_t*)1476405248; // hex 0x58002800  
volatile int32_t* LPTIM4_Base = (int32_t*)1476406272; // hex 0x58002C00  
volatile int32_t* LPTIM5_Base = (int32_t*)1476407296; // hex 0x58003000  

int32_t LPTIM_ISR_OFFSET = 0;
int32_t LPTIM_ICR_OFFSET = 4;
int32_t LPTIM_IER_OFFSET = 8;
int32_t LPTIM_CFGR_OFFSET = 12;
int32_t LPTIM_CR_OFFSET = 16;
int32_t LPTIM_CMP_OFFSET = 20;
int32_t LPTIM_ARR_OFFSET = 24;
int32_t LPTIM_CNT_OFFSET = 28;
int32_t LPTIM_CFGR2_OFFSET = 36;

#if defined(__cplusplus)
  }
#endif