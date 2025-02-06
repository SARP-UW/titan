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
 * @file src/STM32H745_CM7/config.h
 * @authors Aaron McBride
 * @brief Device configuration macros.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Multi-Threading Configuration
   ************************************************************************************************/

  // Maximum number of concurrent threads
  #define TI_THREAD_MAX_THREADS 32

  // Frequency of system tick in Hz
  #define TI_THREAD_TICK_FREQ 100000

  // Frequency of thread scheduler in Hz
  #define TI_THREAD_SCHED_FREQ 1000

  // Enable execution of threads with non-maximum priority
  #define TI_THREAD_STRICT_PRIORITY false

  // Priority of main (entry point) thread
  #define TI_THREAD_MAIN_PRIORITY 100

  /************************************************************************************************
   * Execution Environment Configuration Verification
   ************************************************************************************************/

  #if (TI_THRD_MAX_THREADS < 1) 
    #error "TI LIB CONFIG ERROR: TI_THRD_MAX_THREADS"
  #endif

  #if (TI_THRD_TICK_FREQ < 1)
    #error "TI LIB CONFIG ERROR: TI_THRD_TICK_FREQ"
  #endif

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */