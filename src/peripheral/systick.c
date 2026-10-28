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
 * @file internal/systick.c
 * @authors Jude Merritt
 * @brief SysTick delay utility
 */

#include <stdint.h>
#include "../internal/mmio.h"
#include "errc.h"
#include "systick.h"

// ((480 * 1,000,000) * 0.001 - 1)
// 1ms countdown
#define DEFAULT_RELOAD_VAL 0x752FF
#define CLOCK_FREQ 480000000

static volatile uint32_t elapsed_ms = 0;

void systick_init() {
    //Program reload value
    WRITE_FIELD(STK_RVR, STK_RVR_RELOAD, DEFAULT_RELOAD_VAL);

    //Set clock source
    SET_FIELD(STK_CSR, STK_CSR_CLKSOURCE);

    //Enable SysTick
    SET_FIELD(STK_CSR, STK_CSR_ENABLE);

    //Clear current time value
    WRITE_FIELD(STK_CVR, STK_CVR_CURRENT, 0U);

    // Enable interrupts
    SET_FIELD(STK_CSR, STK_CSR_TICKINT);
}

void cm7_systick_exc_handler(void) {
    elapsed_ms++;
}

uint32_t systick_now_ms(void) {
    return elapsed_ms;
}

void systick_delay(uint32_t delay_ms) {
    if (delay_ms == 0) return;

    uint32_t start_ms = systick_now_ms();

    while (systick_now_ms() - start_ms <= delay_ms) {
    }

}
