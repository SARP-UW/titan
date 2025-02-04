/**
 * This file is part of the Titan HAL
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
 * @internal
 * @file src/STM32H745_CM7/internal/startup.c
 * @authors Aaron McBride
 * @brief Reset handler for the STM32H745_CM7.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/STM32H745_CM7/internal/mmio.h"
#include "src/STM32H745_CM7/internal/interrupt.h"

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Program Initialization Functions
   ************************************************************************************************/

  // Data segment location - defined in linker script
  extern uint32_t __data_start__;
  extern uint32_t __data_end__;
  extern uint32_t __data_load__;

  // Copy data segment from flash to RAM
  static void init_data(void) {
    uint32_t* src = &__data_load__;
    uint32_t* dst = &__data_start__;
    while (src < (uint32_t*)&__data_end__) { 
      *dst++ = *src++;
    }    
  }

  // BSS segment location - defined in linker script
  extern uint32_t __bss_start__;
  extern uint32_t __bss_end__;

  // Initialize BSS segment to zero
  static void init_bss(void) {
    uint32_t* dst = &__bss_start__;
    while (dst < (uint32_t*)&__bss_end__) {
      *dst++ = 0U;
    }
  }

  /************************************************************************************************
   * Peripheral Initialization Functions
   ************************************************************************************************/

  void init_clock() {



  }

  /// @todo

  /************************************************************************************************
   * Reset Handler
   ************************************************************************************************/

  // Main function
  extern void main(void);

  // Reset handler
  void reset_exc_handler(void) {
    init_data();
    init_bss();
    main();
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */