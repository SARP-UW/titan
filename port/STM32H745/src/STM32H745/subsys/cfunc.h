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
 * @file src/STM32H745_CM7/subsys/cfunc.h
 * @authors Aaron McBride
 * @brief Infrastructure for functions that execute on a specific core.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "STM32H745/resource/mmio.h"
#include "STM32H745/resource/interrupt.h"

#ifdef __IAR_SYSTEMS_ICC__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Interrupt Handlers
   ************************************************************************************************/

  // Signature for corespec functions
  typedef int32_t (*cfunc_t)(void*);

  // Shared variables for requests from CM7 -> CM4
  static volatile cfunc_t _cm7_fn_ptr = NULL;
  static volatile void* _cm7_fn_arg = NULL;
  static volatile int32_t _cm7_fn_ret = 0;

  // Shared variables for requests from CM4 -> CM7
  static volatile cfunc_t _cm4_fn_ptr = NULL;
  static volatile void* _cm4_fn_arg = NULL;
  static volatile int32_t _cm4_fn_ret = 0;

  // CM4 -> CM7 event interrupt
  static void cpu2_sev_irq_handler() {
    if (_cm4_fn_ptr != NULL) {
      _cm4_fn_ret = _cm4_fn_ptr(_cm4_fn_arg);
      _cm4_fn_ptr = NULL;
    }
  }

  // CM7 -> CM4 event interrupt
  static void cpu1_sev_irq_handler() {
    if (_cm7_fn_ptr != NULL) {
      _cm7_fn_ret = _cm7_fn_ptr(_cm7_fn_arg);
      _cm7_fn_ptr = NULL;
    }
  }

  /************************************************************************************************
   * System Initialization
   ************************************************************************************************/

  // Priority register value for SEV IRQs
  #define _CFUNC_SEV_PRIO_REGVAL 0xFF

  // Register/field for enabling CM7 SEV IRQ
  #define _CFUNC_CM7_SEV_EN_REG NVIC_ISERx[2]
  #define _CFUNC_CM7_SEV_EN_FIELD MAKE_FIELD(field32_t, 1, 1)

  // Register/field for setting CM7 SEV IRQ priority
  #define _CFUNC_CM7_SEV_PRIO_REG NVIC_IPRx[16]
  #define _CFUNC_CM7_SEV_PRIO_FIELD MAKE_FIELD(field32_t, 24, 8)

  // Register/field for enabling CM4 SEV IRQ
  #define _CFUNC_CM4_SEV_EN_REG NVIC_ISERx[2]
  #define _CFUNC_CM4_SEV_EN_FIELD MAKE_FIELD(field32_t, 0, 1)

  // Register/field for setting CM4 SEV IRQ priority
  #define _CFUNC_CM4_SEV_PRIO_REG NVIC_IPRx[16]
  #define _CFUNC_CM4_SEV_PRIO_FIELD MAKE_FIELD(field32_t, 16, 8)

  // Initializes the cfunc system
  void init_cfunc(void) {

    // Set priority of send event interrupts to maximum value.
    WRITE_FIELD(_CFUNC_CM7_SEV_PRIO_REG, _CFUNC_CM7_SEV_PRIO_FIELD, _CFUNC_SEV_PRIO_REGVAL);
    WRITE_FIELD(_CFUNC_CM4_SEV_PRIO_REG, _CFUNC_CM4_SEV_PRIO_FIELD, _CFUNC_SEV_PRIO_REGVAL);

    // Enable send event interrupts.
    SET_FIELD(_CFUNC_CM7_SEV_EN_REG, _CFUNC_CM7_SEV_EN_FIELD);
    SET_FIELD(_CFUNC_CM4_SEV_EN_REG, _CFUNC_CM4_SEV_EN_FIELD);
  }

  /************************************************************************************************
   * Utility Macros
   ************************************************************************************************/

  /**
   * @brief Creates a function which only executes on the CM7 core.
   * @note - This function takes a void pointer (arg) and returns an int32_t.
   * @note - Execution of the code in this function will always occur on the
   *         CM7 core regardless of where the caller is executing.
   * @warning - The code in this function must not invoke another core-specific function!
   */
  #define CM7_FUNC(name, ...) \
    int32_t name(void* arg) { \
      if (is_exec_cm4()) { \
        __asm__ volatile ("cpsid i"); \
        _cm7_fn_ptr = &name; \
        _cm7_fn_arg = arg; \
        __asm__ volatile ("sev"); \
        while (_cm7_fn_ptr != NULL); \
        const uint32_t retval = _cm7_fn_ret; \
        __asm__ volatile ("cpsie i"); \
        return retval; \
      } else { \
        do { __VA_ARGS__ } while (0); \
      } \
    }
    
  /**
   * @brief Creates a function which only executes on the CM4 core.
   * @note - This function takes a void pointer (arg) and returns an int32_t.
   * @note - Execution of the code in this function will always occur on the
   *         CM4 core regardless of where the caller is executing.
   * @warning - The code in this function must not invoke another core-specific function!
   */
  #define CM4_FUNC(name, ...) \
    int32_t name(void* arg) { \
      if (is_exec_cm7()) { \
        __asm__ volatile ("cpsid i"); \
        _cm4_fn_ptr = &name; \
        _cm4_fn_arg = arg; \
        __asm__ volatile ("sev"); \
        while (_cm4_fn_ptr != NULL); \
        const uint32_t retval = _cm4_fn_ret; \
        __asm__ volatile ("cpsie i"); \
        return retval; \
      } else { \
        do { __VA_ARGS__ } while (0); \
      } \
    }

#ifdef __cplusplus
  } // extern "C"
#endif