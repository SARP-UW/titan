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
 * @file src/port/GCC_STM32H745ZI/internal/reset.c
 * @authors Aaron McBride
 * @brief Reset handler implementation.
 */

#include <stdint.h>
#include "src/port/GCC_STM32H745ZI/internal/interrupt.h"
#include "src/port/GCC_STM32H745ZI/internal/register.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /************************************************************************************************
   * @section Program Initialization Functions
   ************************************************************************************************/

  extern uint32_t _rodata_start_table; /* addresses of start of .rodata sections */
  extern uint32_t _data_start_table;   /* addresses of start of .data sections */
  extern uint32_t _data_end_table;     /* addresses of end of .data sections */
  extern uint32_t _data_table_size;    /* number of .data sections */

  /* initializes .data sections */
  static void __init_data(void) {
    uint32_t data_table_size = (uint32_t)&_data_table_size;
    for (uint32_t i = 0U; i < data_table_size; ++i) {
      const uint32_t* src = (uint32_t*)((&_rodata_start_table)[i]);
      uint32_t* dst = (uint32_t*)((&_data_start_table)[i]);
      uint32_t* const dst_end = (uint32_t*)((&_data_end_table)[i]);
      while (dst < dst_end) {
        *dst++ = *src++;
      }
    }
  }

  extern uint32_t _bss_start_table; /* addresses of start of .bss sections */
  extern uint32_t _bss_end_table;   /* addresses of end of .bss sections */
  extern uint32_t _bss_table_size;  /* number of .bss sections */

  /* initializes .bss sections */
  static void __init_bss(void) {
    uint32_t bss_table_size = (uint32_t)&_bss_table_size;
    for (uint32_t i = 0U; i < bss_table_size; ++i) {
      uint32_t* bss = (uint32_t*)((&_bss_start_table)[i]);
      uint32_t* const bss_end = (uint32_t*)((&_bss_end_table)[i]);
      while (bss < bss_end) {
        *bss++ = 0U;
      }
    }
  }

  /************************************************************************************************
   * @section Peripheral Initialization Functions
   ************************************************************************************************/  
 
  /* initializes MCU power system */
  static void __init_power_sys(void) {

  }

  /* initializes the clock system */
  static void __init_clock_sys(void) {

    /* configure CSI clock */
    _SET(RCC, CR, CSION);              /* turn clock on */
    while (!_IS_SET(RCC, CR, CSIRDY)); /* wait for clock ready */

    /* configure HSI48 clock */
    _SET(RCC, CR, HSI48ON);            /* turn clock on */
    while (!_IS_SET(RCC, CR, HSIRDY)); /* wait for clock ready */

    /* configure PLL #1 - 480Mhz */
    _WRITE(RCC, PLLCKSELR, DIVM1, 4);    /* set pre-divider to 4 */
    _WRITE(RCC, PLL1DIVR, DIVN1, 30);    /* set integer multiplier to 30 */
    _WRITE(RCC, PLL1DIVR, DIVP1, 0);     /* set post-divider "P" to 0 */
    _WRITE(RCC, PLLCFGR, PLL1RGE, 0b11); /* set input freq range to 8-16Mhz */
    _SET(RCC, CR, PLL1ON);               /* turn on PLL */
    while (!_IS_SET(RCC, CR, PLL1RDY));  /* wait for PLL ready */

    /* configure system clocks */
    _WRITE(RCC, D1CFGR, HPRE, 0b1000);     /* set AHB divider to 2 (480->240Mhz) */
    _WRITE(RCC, D1CFGR, D1PPRE, 0b111);    /* set APB3 divider to 16 (240->15Mhz) */
    _WRITE(RCC, D2CFGR, D2PPRE1, 0b100);   /* set APB1 divider to 2 (240->120Mhz) */
    _WRITE(RCC, D2CFGR, D2PPRE2, 0b100);   /* set APB2 divider to 2 (240->120Mhz) */
    _WRITE(RCC, D3CFGR, D3PPRE, 0b100);    /* set APB4 divider to 2 (240->120Mhz) */
    _SET(RCC, CFGR, HRTIMSEL);             /* set HR timers to use the CPU1 clk (480Mhz) */
    _WRITE(RCC, CFGR, SW, 0b11);           /* switch system clock to PLL1 (480Mhz) */
    while (_READ(RCC, CFGR, SWS) != 0b11); /* wait for system clock switch */ 
  }

  /************************************************************************************************
   * @section Reset Handler - CM7 Core
   ************************************************************************************************/

  void _cm7_reset_exc(void) {
    __init_data();
    __init_bss();
    __init_power_sys();
    __init_clock_sys();
    __init_dma();
    main();
    for (;;);
  }

  /************************************************************************************************
   * @section Reset Handler - CM4 Core
   ************************************************************************************************/

  void _cm4_reset_exc(void) {
    for (;;);
  }

#if defined(__cplusplus)
  } /* extern "C" */
#endif