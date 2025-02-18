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
 * @file src/STM32H745_CM7/subsys/shared_mem.h
 * @authors Aaron McBride
 * @brief Shared memory management.
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
   * Internal HSEM Control Functions
   ************************************************************************************************/

  // COREID register values for CM7/CM4 core.
  #define _HSEM_CM4_COREID 0
  #define _HSEM_CM7_COREID 1

  uint32_t _get_coreid(void) {
    

  }

  void _aquire_hsem(int32_t index) {
    while(READ_FIELD(HSEM_RLRx[index], HSEM_RLRx_MASTERID) != _HSEM_CM);
    
  }

  void _release_hsem(int32_t index) {

  }

  /************************************************************************************************
   * ?
   ************************************************************************************************/

#ifdef __cplusplus
  } // extern "C"
#endif