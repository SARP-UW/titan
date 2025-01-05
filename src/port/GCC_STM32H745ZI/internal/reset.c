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
 * @file src/port/GCC_STM32H745ZI_CM7/internal/reset.c
 * @authors Aaron McBride
 * @brief Reset handler implementation.
 */

#include <stdint.h>
#include "src/port/GCC_STM32H745ZI_CM7/internal/ref.h"
#include "src/port/GCC_STM32H745ZI_CM7/internal/vtable.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /************************************************************************************************
   * @section Program Initialization
   ************************************************************************************************/

  /* initializes stack pointer */
  static void init_stack(void) {
    asm ("lsr sp, =__stack_end");
  }

  /* initializes .data section */
  static void init_data(void) {
    uint32_t* src = &__rodata_start;
    uint32_t* dst = &__data_start;
    while (dst < &__data_end) {
      *dst++ = *src++;
    }
  }

  /* initializes the .bss section */
  static void init_bss(void) {
    uint32_t* bss = &__bss_start;
    while (bss < &__bss_end) {
      *bss++ = UINT32_C(0);
    }
  }

  /************************************************************************************************
   * @section Clock Initialization 
   ************************************************************************************************/

  // RCC base address -> 0x58024400

  // LSI   -> 32    khz 
  // CSI   -> 4     mhz
  // HSI48 -> 48    mhz
  // HSI   -> 64    mhz 
  // PLL1  -> 480   mhz
  // PLL2  -> 400   mhz
  // PLL3  -> 78.64 mhz
 
  /* initializes the MCU clock system */
  static void init_clocks(void) {

    /* RCC registers */
    static volatile uint32_t* const rcc_cr_reg = (uint32_t*)0x58024400;

    

    /* initialize CSI clock */
    static const uint32_t csion_mask = UINT32_C(1) << 7;
    static const uint32_t csirdy_mask = UINT32_C(1) << 8;


    /* initialize HSI48 clock */
    static const uint32_t hsi48on_mask = UINT32_C(1) << 12;
    static const uint32_t hsi48rdy_mask = UINT32_C(1) << 13;

    /* initialize PLL1 */
    static const uint32_t pll1on_mask = UINT32_C(1) << 24;
    static const uint32_t pll1rdy_mask = UINT32_C(1) << 25;

    /* initialize PLL2 */
    static const uint32_t pll2on_mask = UINT32_C(1) << 26;
    static const uint32_t pll2rdy_mask = UINT32_C(1) << 27;

    /* initialize PLL3 */
    static const uint32_t pll3on_mask = UINT32_C(1) << 28;
    static const uint32_t pll3rdy_mask = UINT32_C(1) << 29;

  }

  /************************************************************************************************
   * @section Reset Handler
   ************************************************************************************************/

  void reset_exc_handler(void) {
    init_stack();
    init_data();
    init_bss();
    main();
    for (;;);
  }

#if defined(__cplusplus)
  } /* extern "C" */
#endif