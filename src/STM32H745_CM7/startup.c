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
 * @file src/STM32H745_CM7/startup.c
 * @authors Aaron McBride
 * @brief Reset handler and program startup code.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/STM32H745_CM7/device_config.h"
#include "src/STM32H745_CM7/mmio.h"
#include "src/STM32H745_CM7/interrupt.h"

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Program Initialization/De-Initalization Routines
   ************************************************************************************************/

  // Initializes .data sections in RAM
  static void init_data(void) {
    extern const uint32_t __data_table_start__;
    extern const uint32_t __data_table_end__;
    typedef struct { uint32_t *src, *dst, *end; } entry_t;
    const entry_t* cur_entry = (entry_t*)&__data_table_start__;
    const entry_t* end_entry = (entry_t*)&__data_table_end__;
    while (cur_entry < end_entry) {
      entry_t entry = *cur_entry++;
      while (entry.src < entry.end) {
        *entry.dst++ = *entry.src++;
      }
    }
  }

  // Initializes .bss sections in RAM
  static void init_bss(void) {
    extern const uint32_t __bss_table_start__;
    extern const uint32_t __bss_table_end__;
    typedef struct { uint32_t *dst, *end; } entry_t;
    const entry_t* cur_entry = (entry_t*)&__bss_table_start__;
    const entry_t* end_entry = (entry_t*)&__bss_table_end__;
    while (cur_entry < end_entry) {
      entry_t entry = *cur_entry++;
      while (entry.dst < entry.end) {
        *entry.dst++ = 0U;
      }
    }
  }

  // Invokes pre-constructor functions
  static void invoke_preinit(void) {
    extern const uint32_t __preinit_array_start__;
    extern const uint32_t __preinit_array_end__;
    typedef void (*elem_t)(void);
    elem_t* current_elem = (elem_t*)&__preinit_array_start__;
    elem_t* end_elem = (elem_t*)&__preinit_array_end__;
    while (current_elem < end_elem) {
      (*current_elem++)();
    }
  }

  // Invokes constructor functions
  static void invoke_init(void) {
    extern const uint32_t __init_array_start__;
    extern const uint32_t __init_array_end__;
    typedef void (*elem_t)(void);
    elem_t* current_elem = (elem_t*)&__init_array_start__;
    elem_t* end_elem = (elem_t*)&__init_array_end__;
    while (current_elem < end_elem) {
      (*current_elem++)();
    }
  }

  // Invokes destructor functions
  static void invoke_fini(void) {
    extern const uint32_t __fini_array_start__;
    extern const uint32_t __fini_array_end__;
    typedef void (*elem_t)(void);
    elem_t* current_elem = (elem_t*)&__fini_array_start__;
    elem_t* end_elem = (elem_t*)&__fini_array_end__;
    while (current_elem < end_elem) {
      (*current_elem++)();
    }
  }

  /************************************************************************************************
   * Reset Handler Implementation
   ************************************************************************************************/

  // Program entry point
  extern void main(void);

  // MCU reset handler
  void reset_exc_handler(void) {
    init_data();
    init_bss();
    invoke_preinit();
    invoke_init();
    main();
    invoke_fini();
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */