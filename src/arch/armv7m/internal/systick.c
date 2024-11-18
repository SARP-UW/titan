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
#include "include/tal/bit.h"
#include "include/tal/numeric.h"
#include "include/tal/tmp.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Constants
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
  // nanoseconds -> seconds
  #define time_div 1000000000

  /**************************************************************************************************
   * @section Helper Functions/Macros
   **************************************************************************************************/

  // #define cycles_to_duration(cycles) (((uint64_t)cycles) / ((time_div) / (cpu_freq)))

  // #define duration_to_cycles(duration) ((duration) * ((cpu_freq) / (time_div)))
  // reg_val = tal_set_bits_u32(enabled, reg_val, tickint_pos, tickint_len, err);

  /**************************************************************************************************
   * @section Systick Management Implementations
   **************************************************************************************************/

  void init_systick() {
    set_systick_enabled(false, NULL);
    set_systick_interrupt_enabled(false);
    set_systick_interrupt_pending(false);
    set_systick_interrupt_priority(default_systick_interrupt_priority, NULL);
    *csr_reg = tal_set_bits_u32(false, *csr_reg, clksrc_pos, clksrc_len, NULL);
    set_systick_period(default_systick_period, NULL);
    set_systick_duration(0, NULL);
  }

  void set_systick_enabled(const bool enabled, bool* const err) {
    if (enabled && get_systick_period() <= 0) { 
      *err = true;
      return;
    }
    *csr_reg = tal_set_bits_u32(enabled, *csr_reg, ticken_pos, ticken_len, NULL);
  }

  bool get_systick_enabled(void) {
    return tal_get_bits_u32(true, *csr_reg, ticken_pos, ticken_len, NULL);
  }

  void set_systick_period(const int32_t ns, bool* const err) {
    tal_assert(time_div != 0);
    const uint64_t u_ns = tal_cast_u64i(ns, err);
    const uint64_t cycles = tal_mul_u64(u_ns, time_div, err) / cpu_freq;
    const uint32_t reg_val = tal_cast_u32u(cycles, err);
    *rvr_reg = tal_write_bits_u32(reg_val, *rvr_reg, reload_pos, reload_len, err);
  }

  int32_t get_systick_period(void) {
    const uint32_t reg_val = tal_read_bits_u32(*rvr_reg, 
        reload_pos, reload_len, NULL);
    const uint64_t u_ns = tal_mul_u64(u_ns, cpu_freq, NULL) / time_div;
    return tal_cast_i32u(u_ns, NULL);
  }

  void set_systick_duration(const int32_t ns, bool* const err) {
    const uint64_t u_ns = tal_cast_u64i(ns, err);
    const uint64_t cycles = tal_mul_u64(u_ns, time_div, err) / cpu_freq;
    const uint32_t reg_val = tal_cast_u32(cycles, err);
    *cvr_reg = reg_val;
  }

  int32_t get_systick_duration(void) {
    const uint32_t reg_val = *cvr_reg;
    const uint64_t u_ns = tal_mul_u64(reg_val, time_div, NULL) / cpu_freq;
    return tal_cast_i32u(u_ns, NULL);
  }

  void restart_systick(void) {
    *cvr_reg = tal_read_bits(*rvr_reg, reload_pos, reload_len, NULL);
  }

  /**************************************************************************************************
   * @section Interrupt Management Implementations
   **************************************************************************************************/

  void set_systick_interrupt_enabled(const bool enabled) {
    *csr_reg = tal_set_bits_u32(enabled, *csr_reg, tickint_pos, tickint_len, NULL);
  }

  bool get_systick_interrupt_enabled(void) {
    return tal_get_bits_u32(true, *csr_reg, tickint_pos, tickint_len, NULL);
  }

  void set_systick_interrupt_priority(const int32_t priority, bool* const err) {
    const uint32_t reg_val = tal_cast_u32i(priority, err);
    *shpr3_reg = tal_write_bits_u32(reg_val, *shpr3_reg, pri_15_pos, pri_15_len, err);
  }

  int32_t get_systick_interrupt_priority(void) {
    const uint32_t reg_val = tal_read_bits_u32(*shpr3_reg, pri_15_pos, pri_15_len, NULL);
    return tal_cast_i32(reg_val, NULL);
  }

  void set_systick_int_pending(const bool pending) {
    if (pending) {
      *icsr_reg = tal_set_bits_u32(true, *icsr_reg, pendstset_pos, pendstset_len, NULL);
    } else {
      *icsr_reg = tal_set_bits_u32(true, *icsr_reg, pendstclr_pos, pendstclr_len, NULL);
    }
  }

  bool get_systick_int_pending(void) {
    return tal_get_bits_u32(true, *icsr_reg, pendstset_pos, pendstset_len, NULL);
  }

  bool get_systick_int_active(void) {
    return tal_get_bits_u32(true, *shcsr_reg, systickact_pos, systickact_len, NULL);
  }

#if defined(__cplusplus)
  }
#endif