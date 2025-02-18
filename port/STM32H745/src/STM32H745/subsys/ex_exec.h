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
 * @file src/STM32H745_CM7/subsys/ex_exec.h
 * @authors Aaron McBride
 * @brief Infrastructure for exclusive execution of code.
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
   * Implementation Resources
   ************************************************************************************************/

  // CPUID part number register values for cores.
  #define _EX_EXEC_CM7_PARTNO 0xC27
  #define _EX_EXEC_CM4_PARTNO 0xC24

  // Returns true if caller is executing on the CM7 core.
  static bool _is_exec_cm7(void) {
    return READ_FIELD(SCB_CPUID, SCB_CPUID_PARTNO) == _EX_EXEC_CM7_PARTNO;
  }

  // Returns true if caller is executing on the CM4 core.
  static bool _is_exec_cm4(void) {
    return READ_FIELD(SCB_CPUID, SCB_CPUID_PARTNO) == _EX_EXEC_CM4_PARTNO;
  }

  /************************************************************************************************
   * Interrupt Handlers
   ************************************************************************************************/

  // Signature for exclusive functions
  typedef int32_t (*excl_fn_t)(void*);

  // Shared variables for requests from CM7 -> CM4
  static volatile excl_fn_t _cm7_fn_ptr = NULL;
  static volatile void* _cm7_fn_arg = NULL;
  static volatile int32_t _cm7_fn_ret = 0;

  // Shared variables for requests from CM4 -> CM7
  static volatile excl_fn_t _cm4_fn_ptr = NULL;
  static volatile void* _cm4_fn_arg = NULL;
  static volatile int32_t _cm4_fn_ret = 0;

  // CM4 -> CM7 event interrupt
  void cpu2_sev_irq_handler() {
    if (_cm4_fn_ptr != NULL) {
      _cm4_fn_ret = _cm4_fn_ptr(_cm4_fn_arg);
      _cm4_fn_ptr = NULL;
    }
  }

  // CM7 -> CM4 event interrupt
  void cpu1_sev_irq_handler() {
    if (_cm7_fn_ptr != NULL) {
      _cm7_fn_ret = _cm7_fn_ptr(_cm7_fn_arg);
      _cm7_fn_ptr = NULL;
    }
  }

  /************************************************************************************************
   * System Initialization
   ************************************************************************************************/

  // Priority register value for SEV IRQs
  #define _EX_EXEC_SEV_PRIO_REGVAL 0xFF

  // Register/field for enabling CM7 SEV IRQ
  #define _EX_EXEC_CM7_SEV_EN_REG NVIC_ISERx[2]
  #define _EX_EXEC_CM7_SEV_EN_FIELD MAKE_FIELD(field32_t, 1, 1)

  // Register/field for setting CM7 SEV IRQ priority
  #define _EX_EXEC_CM7_SEV_PRIO_REG NVIC_IPRx[16]
  #define _EX_EXEC_CM7_SEV_PRIO_FIELD MAKE_FIELD(field32_t, 24, 8)

  // Register/field for enabling CM4 SEV IRQ
  #define _EX_EXEC_CM4_SEV_EN_REG NVIC_ISERx[2]
  #define _EX_EXEC_CM4_SEV_EN_FIELD MAKE_FIELD(field32_t, 0, 1)

  // Register/field for setting CM4 SEV IRQ priority
  #define _EX_EXEC_CM4_SEV_PRIO_REG NVIC_IPRx[16]
  #define _EX_EXEC_CM4_SEV_PRIO_FIELD MAKE_FIELD(field32_t, 16, 8)

  // Initializes the exclusive execution system
  void init_ex_exec(void) {

    // Set priority of send event interrupts to maximum value.
    WRITE_FIELD(_EX_EXEC_CM7_SEV_PRIO_REG, _EX_EXEC_CM7_SEV_PRIO_FIELD, _EX_EXEC_SEV_PRIO_REGVAL);
    WRITE_FIELD(_EX_EXEC_CM4_SEV_PRIO_REG, _EX_EXEC_CM4_SEV_PRIO_FIELD, _EX_EXEC_SEV_PRIO_REGVAL);

    // Enable send event interrupts.
    SET_FIELD(_EX_EXEC_CM7_SEV_EN_REG, _EX_EXEC_CM7_SEV_EN_FIELD);
    SET_FIELD(_EX_EXEC_CM4_SEV_EN_REG, _EX_EXEC_CM4_SEV_EN_FIELD);
  }

  /************************************************************************************************
   * Utility Macros
   ************************************************************************************************/

  /**
   * @brief Creates an exclusive function for the CM7 core.
   * @note - This function takes a void pointer (arg) and returns an int32_t.
   * @note - Execution of the code in this function will always occur on the
   *         CM7 core regardless of where the caller is executing.
   * @warning - An exclusive function can never invoke another exclusive function!
   */
  #define CM7_FUNC(name, ...) \
    int32_t name(void* arg) { \
      if (_is_exec_cm4()) { \
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
   * @brief Creates an exclusive function for the CM4 core.
   * @note - This function takes a void pointer (arg) and returns an int32_t.
   * @note - Execution of the code in this function will always occur on the
   *         CM4 core regardless of where the caller is executing.
   * @warning - An exclusive function can never invoke another exclusive function!
   */
  #define CM4_FUNC(name, ...) \
    int32_t name(void* arg) { \
      if (_is_exec_cm7()) { \
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