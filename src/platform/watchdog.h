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
 * @file common/platform/watchdog.h
 * @authors Joshua Beard
 * @brief Driver for the watchdog timer 
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "mask.h"

#if defined(__cplusplus)
  extern "C" {
#endif

/**
 * Enables the Independent Watchdog
 * Doc Page 2047 for an overview
 * @return if enable succeeded.
 */
bool ti_IWDG_enable();

/**
 * Resets the countdown so the board doesn't reset
 */
void ti_IWDG_reset_timer();


volatile int32_t* IWDG_Base = (int32_t*)1476413440; // hex 0x58004800

int32_t IWDG_KR_OFFSET =  0; // doc page 2050
int32_t IWDG_PR_OFFSET =  4; // doc page 2051
int32_t IWDG_RLR_OFFSET = 8; // doc page 2052
int32_t IWDG_SR_OFFSET =  12; // doc page 2053 

int32_t IWDG_START = 52428; // hex 0x0000 CCCC
int32_t REG_ACCESS = 21845;// hex 0x0000 5555
int32_t RESET_RLR = 43690; // hex 0x0000 AAAA
int32_t PRESCALER_DIVIDER = 1; // doc page 2051, can be other values to increase frequency of countdown clock



int32_t RESET_COUNT = 4000; // any 12 bit number

/**
 * Clock is 32 kHz (32,000 clk per second).  Lets say we want a one second delay before reset
 * 
 * 32,000 c/second * (1/8) {PRESCALER_DIVIDER = 1} = 4000 watchdog time decrements
 * Set RESET_COUNT = 4000 to make this exactly one second
 * 
 * Note that with PRESCALER_DIVIDER = 0 it is not possible to make one second delay, because 8000 > 4095
 */

bool ti_IWDG_enable()
{
    ti_write_mask32(IWDG_START, IWDG_Base + IWDG_KR_OFFSET, 0, 16);

    // todo check
    ti_write_mask32(REG_ACCESS, IWDG_Base + IWDG_KR_OFFSET, 0, 16); 
    // I feel like this would overwrite the previous call, but it is what the documentation says to do

    ti_write_mask32(PRESCALER_DIVIDER, IWDG_Base + IWDG_PR_OFFSET, 0, 3); 
    ti_write_mask32(RESET_COUNT, IWDG_Base + IWDG_RLR_OFFSET, 0, 12);


    // Wait for SR to be zeroed? says in doc but idk
    return 1;
}

void ti_IWDG_reset_timer()
{
    ti_write_mask32(RESET_RLR, IWDG_Base + IWDG_KR_OFFSET, 0, 16); 
}

#if defined(__cplusplus)
  }
#endif