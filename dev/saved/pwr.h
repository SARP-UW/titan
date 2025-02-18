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
 * @file src/STM32H745_CM7/subsys/pwr.h
 * @authors Aaron McBride
 * @brief Power system initialization and management.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "STM32H745/resource/mmio.h"
#include "STM32H745/resource/interrupt.h"
#include "STM32H745/subsys/clk.h"
#include "STM32H745/tmp_config.h" // TEMP

#ifdef __IAR_SYSTEMS_ICC__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Internal Reference Constants
   ************************************************************************************************/

  // SMPS external voltage level register values.
  #define _PWR_SDLEVEL_25_REGVAL 2U
  #define _PWR_SDLEVEL_18_REGVAL 1U

  // VOS level set on system reset.
  #define _PWR_RST_VOS_LEVEL 3

  // VOS level for which overdrive is required.
  #define _PWR_VOS_OVERDRIVE_LEVEL 0

  // Maximum frequency for different VOS levels
  #define _PWR_VOS_0_MAX_SYS_FREQ 480000000
  #define _PWR_VOS_1_MAX_SYS_FREQ 400000000
  #define _PWR_VOS_2_MAX_SYS_FREQ 200000000
  #define _PWR_VOS_3_MAX_SYS_FREQ 100000000

  // Register value for VOS levels
  #define _PWR_VOS_0_REGVAL 0b11U
  #define _PWR_VOS_1_REGVAL 0b11U
  #define _PWR_VOS_2_REGVAL 0b10U
  #define _PWR_VOS_3_REGVAL 0b01U

  // Determine minimum VOS level / register value from sys freq.
  #if SYS_FREQ <= _PWR_VOS_3_MAX_SYS_FREQ
    #define _PWR_VOS_REGVAL _PWR_VOS_3_REGVAL
    #define _PWR_VOS_LEVEL 3
  #elif SYS_FREQ <= _PWR_VOS_2_MAX_SYS_FREQ
    #define _PWR_VOS_REGVAL _PWR_VOS_2_REGVAL
    #define _PWR_VOS_LEVEL 2
  #elif SYS_FREQ <= _PWR_VOS_1_MAX_SYS_FREQ
    #define _PWR_VOS_REGVAL _PWR_VOS_1_REGVAL
    #define _PWR_VOS_LEVEL 1
  #elif SYS_FREQ <= _PWR_VOS_0_MAX_SYS_FREQ
    #define _PWR_VOS_REGVAL _PWR_VOS_0_REGVAL
    #define _PWR_VOS_LEVEL 0
  #endif

  /************************************************************************************************
   * External Reference Constants
   ************************************************************************************************/

  // Voltage output scaling level
  #define VOS_LEVEL _PWR_VOS_LEVEL

  /// @todo

  /************************************************************************************************
   * Power System Initialization
   ************************************************************************************************/

  // Initializes power system
  void init_pwr(void) {

    // Save local copy of power supply config register.
    uint32_t tmp_pwr_cr3 = *PWR_CR3;

    // If SMPS enabled, ensure it is implemented on device (default = enabled).
    #if defined(TI_PCFG_PWR_SMPS_ENABLE) && (TI_PCFG_PWR_SMPS_ENABLE)
      if (!IS_FIELD_SET(&tmp_pwr_cr3, PWR_CR3_SDEN)) {
        __asm__ volatile ("bkpt #0");
      }
      // Enable external SMPS supply if specified.
      #if defined(TI_PCFG_PWR_SMPS_EXTERN) && (TI_PCFG_PWR_SMPS_EXTERN)
        SET_FIELD(&tmp_pwr_cr3, PWR_CR3_SDEXTHP);
      #endif

      // Set SMPS voltage level to specified value (1.8v or 2.5v) (default = none)
      #if defined(TI_PCFG_PWR_SMPS_LEVEL) && (TI_PCFG_PWR_SMPS_LEVEL) == 25
        WRITE_FIELD(&tmp_pwr_cr3, PWR_CR3_SDLEVEL, _PWR_SDLEVEL_25_REGVAL);
      #else
        WRITE_FIELD(&tmp_pwr_cr3, PWR_CR3_SDLEVEL, _PWR_SDLEVEL_18_REGVAL);
      #endif

    #else // Disable SMPS if not enabled.
      CLR_FIELD(&tmp_pwr_cr3, PWR_CR3_SDEN);
    #endif

    // Disable LDO if specified (default = enabled).
    #if !defined(TI_PCFG_PWR_LDO_ENABLE) || !(TI_PCFG_PWR_LDO_ENABLE)
      CLR_FIELD(&tmp_pwr_cr3, PWR_CR3_LDOEN);
    #endif

    // Enable power supply bypass if LDO and SMPS disabled.
    #if (!defined(TI_PCFG_PWR_LDO_ENABLE) || !(TI_PCFG_PWR_LDO_ENABLE)) && \
        (!defined(TI_PCFG_PWR_SMPS_ENABLE) || !(TI_PCFG_PWR_SMPS_ENABLE))
      SET_FIELD(&tmp_pwr_cr3, PWR_CR3_BYPASS);
    #endif

    // Update power supply config register with local copy.
    *PWR_CR3 = tmp_pwr_cr3;

    // Wait for voltage level to stabilize if not in bypass mode
    #if (defined(TI_PCFG_PWR_SMPS_ENABLE) && (TI_PCFG_PWR_SMPS_ENABLE)) || \
        (defined(TI_PCFG_PWR_LDO_ENABLE) && (TI_PCFG_PWR_LDO_ENABLE))
      while (!IS_FIELD_SET(PWR_CSR1, PWR_CSR1_ACTVOSRDY));
    #endif

    // Wait for SMPS external supply to stabilize if enabled
    #if defined(TI_PCFG_PWR_SMPS_ENABLE) && (TI_PCFG_PWR_SMPS_ENABLE) && \
        defined(TI_PCFG_PWR_SMPS_EXTERN) && (TI_PCFG_PWR_SMPS_EXTERN)
      while (!IS_FIELD_SET(PWR_CR3, PWR_CR3_SDEXTRDY));
    #endif

    // Save new local copies of power control registers.
    uint32_t tmp_pwr_cr2 = *PWR_CR2;
    uint32_t tmp_pwr_cr3 = *PWR_CR3;

    // Enable USB voltage level monitor
    SET_FIELD(&tmp_pwr_cr3, PWR_CR3_USB33DEN);

    // Enable USB voltage regulator and wait for ready if specified
    #if defined(TI_PCFG_PWR_USB_REG_ENABLE) && (TI_PCFG_PWR_USB_REG_ENABLE)
      WRITE_FIELD(&tmp_pwr_cr3, PWR_CR3_USB33DEN);
      while (!IS_FIELD_SET(&tmp_pwr_cr3, PWR_CR3_USB33RDY));
    #endif

    // Enable battery supply and monitor then wait for ready if specified
    #if defined(TI_PCFG_PWR_BAT_ENABLE) && (TI_PCFG_PWR_BAT_ENABLE)
      SET_FIELD(&tmp_pwr_cr2, PWR_CR2_MONEN);
      SET_FIELD(&tmp_pwr_cr2, PWR_CR2_BREN);
      while(!IS_FIELD_SET(&tmp_pwr_cr2, PWR_CR2_BRRDY));

      // Enable charging of battery if specified
      #if defined(TI_PCFG_PWR_BAT_CHARGING) && (TI_PCFG_PWR_BAT_CHARGING)
        SET_FIELD(&tmp_pwr_cr3, PWR_CR3_VBE);

        // Set charge resistor to 1.5k if specified (default = 5k)
        #if defined(TI_PCFG_PWR_BAT_RESISTOR) && (TI_PCFG_PWR_BAT_RESISTOR) == 1500
          SET_FIELD(&tmp_pwr_cr3, PWR_CR3_VBRS);
        #endif
      #endif
    #endif

    // Update power control registers with local copies
    *PWR_CR2 = tmp_pwr_cr2;
    *PWR_CR3 = tmp_pwr_cr3;
    
    // Set VOS level and wait for ready (if not already set).
    #if _PWR_VOS_LEVEL != _PWR_RST_VOS_LEVEL
      WRITE_FIELD(PWR_D3CR, PWR_D3CR_VOS, _PWR_VOS_REGVAL);
      while (!IS_FIELD_SET(PWR_CSR1, PWR_CSR1_ACTVOSRDY));

      // If required, enable overdrive mode.
      #if _PWR_VOS_LEVEL == _PWR_VOS_OVERDRIVE_LEVEL
        SET_FIELD(SYSCFG_PWRCR, SYSCFG_PWRCR_ODEN);
      #endif 
    #endif
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */