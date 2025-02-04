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
 * @file src/STM32H745_CM7/shared_mem.h
 * @authors Aaron McBride
 * @brief Definition of shared memory region.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "src/STM32H745_CM7/sys_util.h"

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * Shared Memory Definition
   **********************************************************************************************/

  /** @brief Shared memory region. */
  __attribute__((section(".shared"))) 
  volatile struct {
    int32_t _lock;
    
    /** @brief Core state information. */
    struct {
      bool cm7_running;       /** @brief Indicates if CM7 core is running a program. */
      bool cm4_running;       /** @brief Indicates if CM4 core is running a program. */
      bool periph_init_flag;  /** @brief Indicates if peripherals have been initialized. */
    } core_info;

  } shared_mem;

  /**********************************************************************************************
   * Shared Memory Utilities
   **********************************************************************************************/

  /**
   * @brief Declares a section of code where shared memory is accessed.
   * @param ... The code to be executed in the "shared" section.
   * @note - In a "shared section", the processor has exclusive access to shared memory.
   * @note - Shared section should only contain writes/reads from/to shared memory.
   */
  #define SHARED_SECTION(...) do { \
    CRITICAL_SECTION( \
      while (!shared_mem._lock); \
      shared_mem._lock = 1; \
      __asm__ volatile ("dmb 0xF" ::: "memory"); \
      do { __VA_ARGS__ } while (0); \
      __asm__ volatile ("dmb 0xF" ::: "memory"); \
      shared_mem._lock = 0; \
    ) \
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */