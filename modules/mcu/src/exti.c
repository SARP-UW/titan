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
 * @file modules/mcu/src/exti.c
 * @authors Charles Faisandier
 * @brief EXTI Interrupt Helpers and ISRs Implementation
 */
#include "mcu/exti.h"
#include "kernel/mutex.h"
#include "internal/mmio.h"
#include "util/errc.h"

#define MUTEX_TIMEOUT 1000

// TODO: Potentially add context support

/**************************************************************************************************
 * @section Data Structures
 **************************************************************************************************/
int32_t volatile exti_irq_numbers[PINS] = {
    // EXTI 0-4
    [0] = 6,
    [1] = 7,
    [2] = 8,
    [3] = 9,
    [4] = 10,
    // EXTI9_5 (lines (pins) 5-9)
    [5] = 23,
    [6] = 23,
    [7] = 23,
    [8] = 23,
    [9] = 23,
    // EXTI15_10 (lines (pins 10-15))
    [10] = 40,
    [11] = 40,
    [12] = 40,
    [13] = 40,
    [14] = 40,
    [15] = 40,
};

exti_callback_t exti_callbacks[PINS] = {0};
struct ti_mutex_t exti_mutexes[PINS] = {0};

/**************************************************************************************************
 * @section Private Functions
 **************************************************************************************************/
void irq_handler(uint8_t exti) {
    SET_FIELD(EXTI_CPUPR1, EXTI_CPUPR1_PRx[exti]);
    exti_callbacks[exti]();
}

uint8_t find_irq_num(uint8_t start, uint8_t end) {
    for (int i = start; i <= end; i++) {
        if (READ_FIELD(EXTI_CPUPR1,EXTI_CPUPR1_PRx[i])) {
            return i;
        }
    }
    return 0; // Should never happen
}

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
 int exti_register_isr(uint8_t pin, exti_callback_t *callback, uint32_t priority, bool falling) {
    if (!ti_acquire_mutex(exti_mutexes[pin], MUTEX_TIMEOUT)) {
        return TI_ERRC_MUTEX_LOCKED;
    }

    // Configure the pin
    tal_enable_clock(pin);
    tal_set_speed(pin, 3);
    tal_set_mode(pin, 0);

    // Get the right registers, as well as pin and port numbers
    uint8_t txready_pin_mcu_port = port_index_from_pin[pin] / 100;
    uint8_t txready_pin_mcu_pin = port_index_from_pin[pin] % 100;
    rw_reg32_t syscfg_reg;
    if (txready_pin_mcu_pin >= 0 && txready_pin_mcu_pin <= 3)
        syscfg_reg = SYSCFG_EXTICR1;
    else if (txready_pin_mcu_pin >= 4 && txready_pin_mcu_pin <= 7)
        syscfg_reg = SYSCFG_EXTICR2;
    else if (txready_pin_mcu_pin >= 8 && txready_pin_mcu_pin <= 11)
        syscfg_reg = SYSCFG_EXTICR3;
    else
        syscfg_reg = SYSCFG_EXTICR4;

    // Select the correct input source for the corresponding EXTI 
    WRITE_FIELD(syscfg_reg, SYSCFG_EXTICRx_EXTIx[txready_pin_mcu_pin], txready_pin_mcu_port);

    // Enable the falling/rising trigger.
    if (falling) {
        SET_FIELD(EXTI_FTSR1, EXTI_FTSR1_TRx[txready_pin_mcu_pin]);
    } else {
        SET_FIELD(EXTI_RTSR1, EXTI_RTSR1_TRx[txready_pin_mcu_pin]);
    }
    // 
    
    // Unmask the interrupt request
    SET_FIELD(EXTI_CPUIMR1, EXTI_CxIMRx[txready_pin_mcu_pin]);
    
    // Set the proprity
    set_irq_priority(exti_irq_numbers[pin], priority);

    // Register the callback
    exti_callbacks[pin] = callback;

    return TI_ERRC_NONE;
 }

 int exti_unregister_isr(uint8_t pin) {
    if (!ti_is_mutex_locked(exti_mutexes[pin])) {
        return TI_ERRC_MUTEX_UNLOCKED;
    }

    // Get the right registers, as well as pin and port numbers
    uint8_t txready_pin_mcu_port = port_index_from_pin[pin] / 100;
    uint8_t txready_pin_mcu_pin = port_index_from_pin[pin] % 100;

    // Disable the falling/rising trigger.
    CLR_FIELD(EXTI_FTSR1, EXTI_FTSR1_TRx[txready_pin_mcu_pin]);
    CLR_FIELD(EXTI_RTSR1, EXTI_RTSR1_TRx[txready_pin_mcu_pin]);
    
    // Mask the interrupt request
    CLR_FIELD(EXTI_CPUIMR1, EXTI_CxIMRx[txready_pin_mcu_pin]);
    
    if (!ti_mutex_release(exti_mutexes[pin], MUTEX_TIMEOUT)) {
        return TI_ERRC_MUTEX_TIMEOUT;
    }
    return TI_ERRC_NONE;
 }

/**************************************************************************************************
 * @section Private Functions
 **************************************************************************************************/
 void irq_6_handler(void) { irq_handler(0); }

 void irq_7_handler(void) { irq_handler(0); }

 void irq_8_handler(void) { irq_handler(0); }

 void irq_9_handler(void) { irq_handler(0); }

 void irq_10_handler(void) { irq_handler(0); }

 void irq_23_handler(void) {
   uint8_t irq_num = find_irq_num(5, 9);
   irq_handler(irq_num);
 }

 void irq_40_handler(void) {
   uint8_t irq_num = find_irq_num(10, 15);
   irq_handler(irq_num);
 }