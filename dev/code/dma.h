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
 * @file src/STM32H745_CM7/dma.h
 * @authors Aaron McBride
 * @brief Internal DMA driver.
 */

// Invalidate D-Cache info: https://community.st.com/t5/stm32-mcus/dma-is-not-working-on-stm32h7-devices/ta-p/49498


#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/STM32H745_CM7/mmio.h"
#include "src/STM32H745_CM7/interrupt.h" 

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Implementation Resources
   ************************************************************************************************/

  void _init_dma(void) {
    
  }

  /************************************************************************************************
   * Internal Functions
   ************************************************************************************************/

  /************************************************************************************************
   * DMA Driver Functions
   ************************************************************************************************/



#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */