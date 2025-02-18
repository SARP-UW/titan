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
 * @file src/STM32H745_CM7/subsys/sys_util.h
 * @authors Aaron McBride
 * @brief Core system utilities.
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

  // CPU-ID part number for the CM7 core.
  #define _SYSUTIL_CM7_PARTNO 0xC27

  /************************************************************************************************
   * Execution State Utilities
   ************************************************************************************************/

  /** @brief Denotes the ID of a core. */
  typedef enum {
    CORE_NULL = 0, /** @brief Invalid/unknown core. */
    CORE_CM7 = 1,  /** @biref Cortex-M7 core. */
    CORE_CM4 = 2   /** @biref Cortex-M4 core. */
  } core_id_t;

  /**
   * @brief Determines which core the function is executing on.
   * @returns (core_id_t) - The ID of the core executing the function.
   * @note - This function will never return CORE_NULL.
   */
  core_id_t get_active_core(void) {
    const uint32_t partno_value = READ_FIELD(SCB_CPUID, SCB_CPUID_PARTNO);
    return partno_value == _SYSUTIL_CM7_PARTNO ? CORE_CM7 : CORE_CM4;
  }

  /**
   * @brief Determines the index of the executing exception.
   * @returns (int32_t) The index of the active exception, or 0 otherwise.
   * @note - The exception number of an IRQ is its IRQ number minus 16.
   */
  bool get_active_exc(void) {
    uint32_t ipsr_value;
    __asm__ volatile ("mrs %0, ipsr" : "=r"(ipsr_value) : : );
    return ipsr_value;
  }

  /************************************************************************************************
   * Critical Section Utilities
   ************************************************************************************************/

  /**
   * @brief Determines if execution is in a critical section.
   * @returns (bool) True if execution is in a critical section, or false otherwise.
   */
  bool is_crit(void) {
    uint32_t primask_value;
    __asm__ volatile ("mrs %0, primask" : "=r"(primask_value) : : );
    return primask_value;
  }

  /**
   * @brief Declares a scope in which interrupts are disabled.
   * @param ... (tokens) The contents of the critical section/scope.
   * @note - Hard faults and NMI exceptions are not disabled by this macro.
   * @note - Faults that occur within a critical section are escalated hard faults.
   */
  #define CRIT_SECTION(...) do { \
    const bool __crit_state = is_crit(); \
    __asm__ volatile ("cpsid i"); \
    do { __VA_ARGS__ } while (0); \
    if (!__crit_state) { \
      __asm__ volatile ("cpsie i"); \
    } \
  } while (0);

  /**
   * @brief Determines if execution is in a faultless critical section.
   * @returns (bool) True if execution is in a faultless critical section, or false otherwise.
   */
  bool is_fcrit(void) {
    uint32_t faultmask_value;
    __asm__ volatile ("mrs %0, faultmask" : "=r"(faultmask_value) : : );
    return faultmask_value;
  }

  /**
   * @brief Declares a scope in which interrupts and faults are disabled.
   * @param ... (tokens) The contents of the faultless, critical section/scope.
   * @note - Faults that occur within this scope/section will be handled
   *         after the end of the section.
   */
  #define FCRIT_SECTION(...) do { \
    const bool __fcrit_state = is_fcrit(); \
    __asm__ volatile ("cpsid f"); \
    do { __VA_ARGS__ } while (0); \
    if (!__fcrit_state) { \
      __asm__ volatile ("cpsie f"); \
    } \
  } while (0);

#ifdef __cplusplus
  } // extern "C"
#endif