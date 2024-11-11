/**
 * This file is part of the Titan Avionics Library
 * Copyright (c) 2024 UW SARP
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
 * @file src/arch/armv7m/internal/systick.c
 * @authors Aaron McBride
 * @brief Implementation of systick management facilities.
 */

#include "src/arch/armv7m/internal/systick.h"
#include "src/arch/armv7m/internal/tmp.h"
#include "include/tal/mask.h"
#include "include/tal/bit.h"
#include "include/tal/numeric.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Constants and Helper Functions/Macros
   **************************************************************************************************/

  // Systick block registers
  #define csr_reg (volatile uint32_t*)0xE000E010
  #define rvr_reg (volatile uint32_t*)0xE000E014
  #define cvr_reg (volatile uint32_t*)0xE000E018
  #define calib_reg (volatile uint32_t*)0xE000E01C

  // SCS registers
  #define shpr3_reg (volatile uint32_t*)0xE000ED24
  #define icsr_reg (volatile uint32_t*)0xE000ED04
  #define shcsr_reg (volatile uint32_t*)0xE000ED24

  // ticken regval (enable systick - csr)
  #define ticken_pos 0
  #define ticken_len 1

  // tickint regval (enable interrupt -csr)
  #define tickint_pos 1
  #define tickint_len 1

  // clksource regval (set clock source - csr)
  #define clksrc_pos 2
  #define clksrc_len 1

  // reload value regval (systick reset tick count - rvr)
  #define reload_pos 0
  #define reload_len 24

  // systickact regval (systick counter active - shcsr)
  #define systickact_pos 11
  #define systickact_len 1

  // pendstset regval (set interrupt pending - icsr)
  #define pendstset_pos 26
  #define pendstset_len 1

  // pendstclr regval (clear interrupt pending - icsr)
  #define pendstclr_pos 25
  #define pendstclr_len 1

  // pri_15 regval (systick interrupt priority - shpr3)
  #define pri_15_pos 24
  #define pri_15_len 8

  // Misc constants
  #define time_div 1000000 // microseconds -> seconds

  /**************************************************************************************************
   * @section Systick Utility Implementations
   **************************************************************************************************/

  // Complete
  int64_t systick_value_to_duration(const int64_t systick_value) {
    return systick_value / (cpu_freq / time_div);
  }

  // Complete
  int64_t duration_to_systick_value(const int64_t micros) {
    return micros * (cpu_freq / time_div);
  }

  /**************************************************************************************************
   * @section Systick Management Implementations
   **************************************************************************************************/

  // Complete
  void set_systick_enabled(const bool enabled) {
    if (enabled) {
      tal_set_mask_u32v(csr_reg, ticken_pos, ticken_len);
      tal_set_mask_u32v(csr_reg, tickint_pos, tickint_len);
      tal_set_mask_u32v(csr_reg, clksrc_pos, clksrc_len);
    } else {
      tal_clr_mask_u32v(csr_reg, ticken_pos, ticken_len);
      tal_clr_mask_u32v(csr_reg, tickint_pos, tickint_len);
    }
  }

  // Complete
  bool get_systick_enabled(void) {
    return tal_is_set_u32v(csr_reg, ticken_pos, ticken_len);
  }

  // Complete
  bool set_systick_reload_value(const int64_t value) {
    if (value < 0 || tal_bit_width_u64((uint64_t)value) > reload_len) {
      return false;
    }
    tal_write_mask_u32v((uint32_t)value, rvr_reg, reload_pos, reload_len);
    return true;
  }

  // Complete
  int64_t get_systick_reload_value(void) {
    return (int64_t)tal_read_mask_u32v(rvr_reg, reload_pos, reload_len);
  }

  // Complete
  bool set_systick_value(const int64_t value) {
    if (value < 0 || tal_bit_width_u32((uint64_t)value) > 32) { 
      return false; 
    }
    *cvr_reg = (uint32_t)value;
    return true;
  }

  // Complete
  int64_t get_systick_value(void) {
    return (int64_t)*cvr_reg;
  }

  // Complete
  void reload_systick(void) {
    *cvr_reg = tal_read_mask_u32v(rvr_reg, reload_pos, reload_len);
  }

  /**************************************************************************************************
   * @section Interrupt Management Implementations
   **************************************************************************************************/

  // Complete
  bool set_systick_int_priority(const int32_t priority) {
    if (priority < 0 || tal_bit_width_u32((uint32_t)priority) > pri_15_len) {
      return false;
    }
    tal_write_mask((uint32_t)priority, shpr3_reg, pri_15_pos, pri_15_len);
    return true;
  }

  // Complete
  int32_t get_systick_int_priority(void) {
    return (int32_t)tal_read_mask_u32v(shpr3_reg, pri_15_pos, pri_15_len);
  }

  // Complete
  void set_systick_int_pending(const bool pending) {
    if (pending) {
      tal_set_mask_u32v(icsr_reg, pendstset_pos, pendstset_len);
    } else {
      tal_set_mask_u32v(icsr_reg, pendstclr_pos, pendstclr_len);
    }
  }

  // Complete
  bool get_systick_int_pending(void) {
    return tal_is_set_u32v(icsr_reg, pendstset_pos, pendstset_len);
  }

  // Complete
  bool get_systick_int_active(void) {
    return tal_is_set_u32v(shcsr_reg, systickact_pos, systickact_len);
  }

#if defined(__cplusplus)
  }
#endif