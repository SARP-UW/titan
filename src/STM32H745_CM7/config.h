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
   * Execution Environment Configuration
   ************************************************************************************************/

  // System tick frequency in Hz.
  #define TI_EXEC_TICK_FREQ 100000

  /************************************************************************************************
   * Execution Environment Configuration Verification
   ************************************************************************************************/

  #if (TI_EXEC_TICK_FREQ < 1)
    #error "CONFIG ERROR: TI_EXEC_TICK_FREQ."
  #endif

  /************************************************************************************************
   * Power System Configuration
   ************************************************************************************************/

  // LDO enabled.
  #define TI_PWR_LDO_ENABLED true

  // SMPS converter enabled.
  #define TI_PWR_SMPS_ENABLED true

  // SMPS output voltage.
  // 25 = 2.5V
  // 18 = 1.8V
  #define TI_PWR_SMPS_VOLTAGE 25

  // SMPS high performance mode enabled.
  #define TI_PWR_SMPS_HIGH_PERFORMANCE true

  // Enable charging of VBAT.
  #define TI_PWR_VBAT_CHARGE_ENABLED true

  // Charging resistor selection.
  // 1500 = 1.5 kOhm
  // 5000 = 5.0 kOhm
  #define TI_PWR_VBAT_CHARGE_RESISTOR 1500

  // USB power regulator enabled.
  #define TI_PWR_USB_ENABLED true

  /************************************************************************************************
   * Power System Configuration Verification
   ************************************************************************************************/

  #if (TI_PWR_SMPS_VOLTAGE != 25) && \
      (TI_PWR_SMPS_VOLTAGE != 18)
    #error "CONFIG ERROR: TI_PWR_SMPS_VOLTAGE."
  #endif

  #if (TI_PWR_VBAT_CHARGE_RESISTOR != 1500) && \
      (TI_PWR_VBAT_CHARGE_RESISTOR != 5000)
    #error "CONFIG ERROR: TI_PWR_VBAT_CHARGE_RESISTOR."
  #endif

  /************************************************************************************************
   * Clock System Configuration
   ************************************************************************************************/

  // Frequency of cpu clock in Hz.
  #define TI_CLK_CPU_FREQ 400000000

  /************************************************************************************************
   * Clock System Configuration Verification
   ************************************************************************************************/

  #if (TI_CLK_CPU_FREQ < 1) || (TI_CLK_CPU_FREQ > 480000000)
    #error "CONFIG ERROR: TI_CLK_CPU_FREQ."
  #endif

  #if (TI_EXEC_TICK_FREQ > (TI_CLK_CPU_FREQ / 2))
    #error "CONFIG ERROR: TI_EXEC_TICK_FREQ."
  #endif


#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */