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
 * @file src/STM32H745_CM7/hsem.h
 * @authors Aaron McBride
 * @brief Hardware semaphore driver.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "src/STM32H745_CM7/mmio.h"
#include "src/STM32H745_CM7/interrupt.h"

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * Implementation Resources
   **********************************************************************************************/

  // COREID values for cores.
  static const int32_t _THIS_CORE_ID = 3;
  static const uint64_t _HSEM_TIMEOUT = 100000; 

  void _aquire_hsem(int32_t index)  {
    uint64_t timeout_count = 0;
    while (READ_FIELD(HSEM_Rx[index], HSEM_Rx_COREID) != _THIS_CORE_ID) {
      if (timeout_count++ >= _HSEM_TIMEOUT) {

      }
    }
  }

  // Releases hardware semaphore.
  void release_hsem(int32_t index) {

  }

  /**********************************************************************************************
   * Hardware Semaphore Driver
   **********************************************************************************************/


#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */