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
 * @file src/STM32H7x5/internal/startup.c
 * @authors Aaron McBride
 * @brief Device startup code.
 */

#include <stdint.h>
#include <src/STM32H7x5/internal/exc.h>
#include <src/STM32H7x5/internal/mmio.h>

#ifdef __ICCARM__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * @section Program Initialization Functions
   **********************************************************************************************/

  // Location of .data section in flash/RAM
  extern uint32_t ram_data_start__;
  extern uint32_t ram_data_end__;
  extern uint32_t data_start__;
  extern uint32_t data_end__;

  // Initializes the .data section in RAM
  static void init_data(void) {
    uint32_t* dst = &ram_data_start__;
    uint32_t* src = &data_start__;
    while (src < &data_end__) {
      *dst++ = *src++;
    }
  }

  // Location of .bss section in RAM
  extern uint32_t bss_start__;
  extern uint32_t bss_end__;

  // Initializes the .bss section in RAM
  static void init_bss(void) {
    uint32_t* ptr = &bss_start__;
    while (ptr < &bss_end__) {
      *ptr++ = 0;
    }
  }

  static void invoke_preinit(void) {

  }

  static void invoke_ctors(void) {

  }

  static void invoke_dtors(void) {

  }

  /**********************************************************************************************
   * @section Reset Handler
   **********************************************************************************************/

  void reset_exc_handler() {
    init_data();
    init_bss();
    invoke_preinit();
    invoke_ctors();
    main();
    invoke_dtors();
  }

#ifdef __cplusplus
  } // extern "C"
#endif