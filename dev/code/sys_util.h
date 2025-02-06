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
 * @file src/STM32H745_CM7/sys_util.h
 * @authors Aaron McBride
 * @brief General system utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/STM32H745_CM7/device_config.h"

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Implementation Resources
   ************************************************************************************************/

  // Determines if execution is currently in a critical section.
  static bool _is_critical(void) {
    uint32_t primask_value;
    __asm__ volatile ("mrs %0, primask" : "=r" (primask_value));
    return primask_value;
  }

  /************************************************************************************************
   * System Utilities
   ************************************************************************************************/

  /**
   * @brief Makes a section of code critical.
   * @param ... The code to be executed in the critical section.
   * @note - In a "critical section" all exceptions except for NMI/HardFault are disabled.
   */
  #define CRITICAL_SECTION(...) do { \
    const bool _critical = _is_critical(); \
    if (!_critical) { __asm__ volatile ("cpsid i" ::: "memory"); } \
    do { __VA_ARGS__ } while (0); \
    if (!_critical) { __asm__ volatile ("cpsie i" ::: "memory"); } \
  } while (0);

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */