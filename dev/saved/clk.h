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
 * @file src/STM32H745_CM7/subsys/clk.h
 * @authors Aaron McBride
 * @brief Clock system initialization and management.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "STM32H745/resource/mmio.h"
#include "STM32H745/resource/interrupt.h"
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

  // Default system frequency
  #define _CLK_DEFAULT_SYS_FREQ 400000000

  // PLL3 frequency (comm peripheral clock source)
  #define _CLK_PLL3_FREQ 480000000

  // Frequency of high speed internal oscillator
  #define _CLK_HSI_FREQ 64000000

  // Maximum frequency for PLL input range values.
  #define _CLK_PLL_RANGE_0_MAX 2000000
  #define _CLK_PLL_RANGE_1_MAX 4000000
  #define _CLK_PLL_RANGE_2_MAX 8000000
  #define _CLK_PLL_RANGE_3_MAX 16000000

  // Minimum and maximum PLL numbers/indexes
  #define _CLK_MAX_PLL_NUM 1
  #define _CLK_MIN_PLL_NUM 3

  // Minimum frequency of PLL output when using VCO-high
  #define _CLK_VCOH_MIN 1920000000

  // Register value that sets PLL source to HSE
  #define _CLK_PLLSRC_HSE_REGVAL 0b11U

  // Denominator in equation for fractional PLL multiplier.
  #define _CLK_PLL_FRAC_DIV 8192

  // Register value for setting system clock source to PLL1
  #define _CLK_SW_PLL1_P_REGVAL 0b011U

  // D1CPRE register value for /1 and /2 prescaler
  #define _CLK_D1CPRE_DIV1_REGVAL 0b0000U
  #define _CLK_D1CPRE_DIV2_REGVAL 0b1000U

  // HPRE register value for /2 prescaler
  #define _CLK_HPRE_DIV2_REGVAL 0b1000U

  // D1PPRE register value for /2 prescaler
  #define _CLK_D1PPRE_DIV2_REGVAL 0b1000U

  // D2PPRE1 register value for /2 prescaler
  #define _CLK_D2PPRE1_DIV2_REGVAL 0b1000U

  // D2PPRE2 register value for /2 prescaler
  #define _CLK_D2PPRE2_DIV2_REGVAL 0b1000U

  // D3PPRE register value for /2 prescaler
  #define _CLK_D3PPRE_DIV2_REGVAL 0b1000U

  // Register value for setting system clock source to HSI
  #define _CLK_RTCSEL_LSE_REGVAL 0b01U

  // Register value for setting system clock source to LSI
  #define _CLK_RTCSEL_LSI_REGVAL 0b10U

  // Determine HS oscillator frequency (HSE if enabled, otherwise HSI).
  #if defined(TI_PCFG_CLK_HSE_ENABLE) && (TI_PCFG_CLK_HSE_ENABLE)
    #define _CLK_HS_OSC_FREQ (TI_PCFG_CLK_HSE_FREQ)
  #else
    #define _CLK_HS_OSC_FREQ _CLK_HSI_FREQ
  #endif

  // Determine PLL input frequency (from HS OSC, pre-divided if out of range).
  #if _CLK_HS_OSC_FREQ > _CLK_PLL_RANGE_3_MAX
    #define _CLK_PLL_IN_FREQ (_CLK_HS_OSC_FREQ / (_CLK_HS_OSC_FREQ / _CLK_PLL_RANGE_3_MAX))
  #else
    #define _CLK_PLL_IN_FREQ _CLK_HS_OSC_FREQ
  #endif

  // Get system frequency (default if not specified).
  #if defined(TI_PCFG_CLK_SYS_FREQ)
    #define _CLK_SYS_FREQ (TI_PCFG_CLK_SYS_FREQ)
  #else
    #define _CLK_SYS_FREQ _CLK_DEFAULT_SYS_FREQ
  #endif

  // Determine PLL input range register value.
  #if _CLK_PLL_IN_FREQ <= _CLK_PLL_RANGE_0_MAX
    #define _CLK_PLL_RANGE_REGVAL 0U
  #elif _CLK_PLL_IN_FREQ <= _CLK_PLL_RANGE_1_MAX
    #define _CLK_PLL_RANGE_REGVAL 1U
  #elif _CLK_PLL_IN_FREQ <= _CLK_PLL_RANGE_2_MAX
    #define _CLK_PLL_RANGE_REGVAL 2U
  #elif _CLK_PLL_IN_FREQ <= _CLK_PLL_RANGE_3_MAX
    #define _CLK_PLL_RANGE_REGVAL 3U
  #endif  

  /************************************************************************************************
   * External Reference Constants
   ************************************************************************************************/

  // System frequency
  #define SYS_FREQ _CLK_SYS_FREQ

  /// @todo

  /************************************************************************************************
   * Clock System Initialization
   ************************************************************************************************/

  // Initializes clock system
  void init_clk(void) {

    // Save local copy of primary PLL configuration registers.
    uint32_t tmp_pllcksel_reg = *RCC_PLLCKSELR;
    uint32_t tmp_pllcfg_reg = *RCC_PLLCFGR;

    // If high speed external oscillator enabled...
    #if defined(TI_PCFG_CLK_HSE_ENABLE) && (TI_PCFG_CLK_HSE_ENABLE)

      // Enable hse bypass if specified (for crystal/ceramic resonators)
      #if defined(TI_PCFG_CLK_HSE_BYPASS) && (TI_PCFG_CLK_HSE_BYPASS)
        SET_FIELD(RCC_CR, RCC_CR_HSEBYP);
      #endif

      // Enable HSE oscillator/security system and wait for ready
      SET_FIELD(RCC_CR, RCC_CR_HSEON);
      SET_FIELD(RCC_CR, RCC_CR_HSECSSON);
      while (!IS_FIELD_SET(RCC_CR, RCC_CR_HSERDY));

      // Set PLL input source to HSE oscillator
      WRITE_FIELD(&tmp_pllcksel_reg, RCC_PLLCKSELR_PLLSRC, _CLK_PLLSRC_HSE_REGVAL);
    #endif

    // Iterate through all PLLs and set range based on source freq (HSE/HSI)
    for (int32_t i = _CLK_MIN_PLL_NUM; i <= _CLK_MAX_PLL_NUM; i++) {
      WRITE_FIELD(&tmp_pllcfg_reg, RCC_PLLCFGR_PLLxRGE[i], _CLK_PLL_RANGE_REGVAL);

      // Set PLL pre-divider value (if HS osc freq out of range -> 16Mhz)
      #if (_CLK_HS_OSC_FREQ > _CLK_PLL_RANGE_3_MAX)
        static const uint32_t pll_pre_div = _CLK_HS_OSC_FREQ / _CLK_PLL_RANGE_3_MAX;
        WRITE_FIELD(&tmp_pllcksel_reg, RCC_PLLCKSELR_DIVMx[i], pll_pre_div);
      #endif
    }
    // If system frequency < ~192Mhz, set PLL 1 VCO to low range (default = high range)
    #if _CLK_SYS_FREQ < _CLK_VCOH_MIN
      SET_FIELD(&tmp_pllcfg_reg, RCC_PLLCFGR_PLLxVCOSEL[1]);
    #endif

    // Calculate and set multiplier value for PLL 1 (system frequency)
    static const uint32_t pll1_mul = _CLK_SYS_FREQ / _CLK_PLL_IN_FREQ;
    WRITE_FIELD(RCC_PLL1DIVR, RCC_PLL1DIVR_DIVN1, pll1_mul);

    // If PLL 1 input freq not even, enable, calculate, and set fractional multiplier.
    #if (_CLK_SYS_FREQ % _CLK_PLL_IN_FREQ) != 0
      static const uint32_t pll1_frac = 
          ((_CLK_PLL_FRAC_DIV * _CLK_SYS_FREQ) / _CLK_PLL_IN_FREQ) - 
          (_CLK_PLL_FRAC_DIV * (_CLK_SYS_FREQ / _CLK_PLL_IN_FREQ));
      WRITE_FIELD(RCC_PLL1FRACR, RCC_PLL1FRACR_FRACN1, pll_frac);
    #endif

    // Calculate and set multiplier value for PLL 3 (comm peripheral clock source)
    static const uint32_t pll3_mul = _CLK_PLL3_FREQ / _CLK_PLL_IN_FREQ;
    WRITE_FIELD(RCC_PLL3DIVR, RCC_PLL3DIVR_DIVN3, pll3_mul);

    // If PLL 3 input freq not even, enable, calculate, and set fractional multiplier.
    #if (_CLK_PLL3_FREQ % _CLK_PLL_IN_FREQ) != 0
      static const uint32_t pll3_frac = 
          ((_CLK_PLL_FRAC_DIV * _CLK_PLL3_FREQ) / _CLK_PLL_IN_FREQ) - 
          (_CLK_PLL_FRAC_DIV * (_CLK_PLL3_FREQ / _CLK_PLL_IN_FREQ));
      WRITE_FIELD(RCC_PLL3FRACR, RCC_PLL3FRACR_FRACN3, pll3_frac);
    #endif

    // Update PLL configuration registers with local copies
    *RCC_PLLCKSELR = tmp_pllcksel_reg;
    *RCC_PLLCFGR = tmp_pllcfg_reg;

    // Load fractional value into PLL 1 if applicable
    #if (_CLK_SYS_FREQ % _CLK_PLL_IN_FREQ) != 0
      SET_FIELD(RCC_PLLCFGR, RCC_PLLCFGR_PLLxFRACEN[1]);
    #endif

    // Load fractional value into PLL 3 if applicable
    #if (_CLK_PLL3_FREQ % _CLK_PLL_IN_FREQ) != 0
      SET_FIELD(RCC_PLLCFGR, RCC_PLLCFGR_PLLxFRACEN[3]);
    #endif

    // Configure system clock block prescalers for CPU/busses
    WRITE_FIELD(RCC_D1CFGR, RCC_D1CFGR_HPRE, _CLK_HPRE_DIV2_REGVAL);          // CPU2/busses/peripherals
    WRITE_FIELD(RCC_D1CFGR, RCC_D1CFGR_D1PPRE, _CLK_D1PPRE_DIV2_REGVAL);      // APB3 peripheral clocks
    WRITE_FIELD(RCC_D2CFGR, RCC_D2CFGR_D2PPREx[1], _CLK_D2PPRE1_DIV2_REGVAL); // APB1 peripheral clocks/timers
    WRITE_FIELD(RCC_D2CFGR, RCC_D2CFGR_D2PPREx[2], _CLK_D2PPRE2_DIV2_REGVAL); // APB2 peripheral clocks/timers
    WRITE_FIELD(RCC_D3CFGR, RCC_D3CFGR_D3PPRE, _CLK_D3PPRE_DIV2_REGVAL);      // APB4 peripheral clocks/timers

    // Enable PLL 1 and wait for ready
    SET_FIELD(RCC_CR, RCC_CR_PLLxON[1]);
    while(!IS_FIELD_SET(RCC_CR, RCC_CR_PLLxRDY[1]));

    // Switch system clock source to PLL 1 (channel p) and wait for ready.
    WRITE_FIELD(RCC_CFGR, RCC_CFGR_SW, _CLK_SW_PLL1_P_REGVAL);
    while (READ_FIELD(RCC_CFGR, RCC_CFGR_SWS) != _CLK_SW_PLL1_P_REGVAL);

    // If low speed external oscillator enabled...
    #if defined(TI_PCFG_CLK_LSE_ENABLE) && (TI_PCFG_CLK_LSE_ENABLE)

      // If bypass specified, enable bypass (for crystal/ceramic resonators)
      #if defined(TI_PCFG_CLK_LSE_BYPASS) && (TI_PCFG_CLK_LSE_BYPASS)
        SET_FIELD(RCC_BDCR, RCC_BDCR_LSEBYP);        
      #endif

      // Enable LSE and security system, set drive strength and wait for ready. 
      WRITE_FIELD(RCC_BDCR, RCC_BDCR_LSEDRV, TI_PCFG_CLK_LSE_DRIVE);
      SET_FIELD(RCC_BDCR, RCC_BDCR_LSECSSON);
      SET_FIELD(RCC_BDCR, RCC_BDCR_LSEON);
      while (!IS_FIELD_SET(RCC_BDCR, RCC_BDCR_LSERDY));

      // Set LSE as RTC clock source
      WRITE_FIELD(RCC_BDCR, RCC_BDCR_RTCSRC, _CLK_RTCSEL_LSE_REGVAL);
    #else 
      // Enable LSI (low speed internal oscillator) and wait for ready.
      SET_FIELD(RCC_CSR, RCC_CSR_LSION);
      while(!IS_FIELD_SET(RCC_CSR, RCC_CSR_LSIRDY));

      // Set LSI as RTC clock source
      WRITE_FIELD(RCC_BDCR, RCC_BDCR_RTCSRC, _CLK_RTCSEL_LSI_REGVAL);
    #endif

    // Enable RTC clock.
    SET_FIELD(RCC_BDCR, RCC_BDCR_RTCEN);
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */