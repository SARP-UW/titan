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
 * @file src/port/STM32H745_CM7/internal/sys_util.h
 * @authors Aaron McBride
 * @brief System utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/port/STM32H745_CM7/internal/compat.h"

COMPAT_FILE

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Critical Section Control
   ************************************************************************************************/

  /**
   * @brief Enters a critical section.
   * @returns (bool) A flag value to pass to @ref exit_critical.
   * @note - In a critical section, execution can only be preempted by faults.
   */
  __attribute__((warn_unused_result)) bool enter_critical(void);

  /**
   * @brief Exits a critical section.
   * @param entry_state (bool) The flag value returned by the corresponding
   *        call to @ref enter_critical.
   */
  void exit_critical(bool entry_state);

  /**
   * @brief Determines if execution is in a critical section.
   * @returns (bool) True if execution is in a critical section, or false otherwise.
   */
  bool is_critical(void);
  
  /************************************************************************************************
   * Uncategorized System Utilities
   ************************************************************************************************/

  /**
   * @brief Gets the number of the active exception.
   * @return (int32_t) The number of the active exception, or -1 otherwise.
   */
  int32_t get_active_exception(void);

  /************************************************************************************************
   * Implementation of Critical Section Control
   ************************************************************************************************/

  bool enter_critical(void) {
    if (is_critical()) { 
      return false;
    }
    TI_VOLATILE_ASM ("CPSID i");
    return true;
  }

  void exit_critical(bool entry_state) {
    if (entry_state) {
      TI_VOLATILE_ASM ("CPSIE i");
    }
  }

  bool is_critical(void) {
    uint32_t primsk_value;
    TI_VOLATILE_ASM (
      "MRS %0, PRIMASK" 
      : "=r" (primsk_value)
    );
    return primsk_value & 1U;
  }

  /************************************************************************************************
   * Implementation of Uncategorized Utilities
   ************************************************************************************************/

  int32_t get_active_exception(void) {
    int32_t exc_num;
    TI_VOLATILE_ASM(
      "MRS %0, IPSR" 
      : "=r" (exc_num)
    );
    return (exc_num == 0) ? -1 : exc_num;
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */