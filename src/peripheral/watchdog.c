
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
 * @file peripheral/watchdog.h
 * @authors Joshua Beard
 * @brief Driver for the watchdog timer
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "peripheral/watchdog.h"
#include "internal/mmio.h"

#ifdef __cplusplus
extern "C" {
#endif

static const int32_t start_key = 0xCCCC;
static const int32_t reg_access = 0x5555;
static const int32_t reset_rlr = 0xAAAA;
static const int32_t prescaler_divider = 1; // doc page 2051, can be other values to increase
                               // frequency of countdown clock

static const int32_t reset_count = 4000; // any 12 bit number

/**
 * Clock is 32 kHz (32,000 clk per second).  Lets say we want a one second delay
 * before reset
 *
 * 32,000 c/second * (1/8) {PRESCALER_DIVIDER = 1} = 4000 watchdog time
 * decrements Set RESET_COUNT = 4000 to make this exactly one second
 *
 * Note that with PRESCALER_DIVIDER = 0 it is not possible to make one second
 * delay, because 8000 > 4095
 */

// NOLINTNEXTLINE(readability-identifier-naming)
bool ti_IWDG_enable() {
  WRITE_FIELD(RCC_APB3ENR, RCC_APB3ENR_WWDG1EN, 1);

  WRITE_FIELD(IWDGx_KR[1], IWDGx_KR_KEY, start_key);

  WRITE_FIELD(IWDGx_KR[1], IWDGx_KR_KEY, reg_access);

  WRITE_FIELD(IWDGx_PR[1], IWDGx_PR_PR, prescaler_divider);

  WRITE_FIELD(IWDGx_RLR[1], IWDGx_RLR_RL, reset_count);
  // Wait for SR to be zeroed? says in doc but idk

  return true;
}

// NOLINTNEXTLINE(readability-identifier-naming)
void ti_IWDG_reset_timer() {
  WRITE_FIELD(IWDGx_KR[1], IWDGx_KR_KEY, reset_rlr);
}

#ifdef __cplusplus
}
#endif
