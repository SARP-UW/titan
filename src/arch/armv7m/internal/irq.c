/**
 * This file is part of the Titan Flight Computer Project
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
 * @file arch/armv7m/internal/interrupt.c
 * @authors Aaron McBride
 * @brief Implementation of IRQ management facilities.
 */

#include "src/arch/armv7m/internal/irq.h"
#include "src/arch/armv7m/internal/vtable.h"
#include "include/tal/bit.h"
#include "include/tal/numeric.h"
#include "include/tal/tmp.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Constants and Helper Functions/Macros
   **************************************************************************************************/

  // NVIC registers
  #define iser_reg(off) (volatile uint32_t*)(0xE000E100 + (off * 4))
  #define icer_reg(off) (volatile uint32_t*)(0xE000E180 + (off * 4))
  #define ispr_reg(off) (volatile uint32_t*)(0xE000E200 + (off * 4))
  #define icpr_reg(off) (volatile uint32_t*)(0xE000E280 + (off * 4))
  #define iabr_reg(off) (volatile uint32_t*)(0xE000E300 + (off * 4))
  #define ipr_reg(off) (volatile uint32_t*)(0xE000E400 + (off * 4))

  // SCS registers
  #define ictr_reg (volatile uint32_t*)0xE000E004
  #define stir_reg (volatile uint32_t*)0xE000EF00

  // NVIC regval locations (iser, icer, ispr, icpr, iabr)
  #define nvic_idx_div 31 // div = index per reg
  #define nvic_idx_len 1

  // ipr pri_n regval location (set priority - ipr)
  #define ipr_pri_n_div 4 // div = index per reg
  #define ipr_pri_n_len 8

  // intlinesum regval location (impl IRQ count - ictr)
  #define intlinesum_pos 0
  #define intlinesum_len 4

  /**************************************************************************************************
   * @section Helper Functions/Macros
   **************************************************************************************************/

  // Determines if the given IRQ index is valid.
  static bool valid_irq_index(const int32_t index) {
    const int32_t irq_count = get_irq_count();
    tal_assert(irq_count > 0);
    return tal_in_range_i32(index, 0, irq_count);
  }

  /**************************************************************************************************
   * @section Function Implementations
   **************************************************************************************************/

  void init_irq(const int32_t index, bool* const err) {
    set_irq_enabled(index, false, err);
    set_irq_pending(index, false, err);
    set_irq_priority(index, default_irq_priority, err);
  }

  int32_t get_irq_count(void) {
    const uint32_t reg_val = tal_read_bits_u32(*ictr_reg, intlinesum_pos, intlinesum_len, NULL);
    const int32_t raw_cnt = tal_cast_i32u(reg_val, NULL) + 1;
    return tal_min2_i32(raw_cnt, vtable_irq_count);
  }


  void set_irq_enabled(const int32_t index, const bool enabled, bool* const err) {
    if (!valid_irq_index(index)) { 
      *err = true;
      return;
    }
    const int32_t index_pos = index % nvic_idx_div;
    if (enabled) {
      volatile uint32_t* const reg = iser_reg(index / nvic_idx_div);
      *reg = tal_set_bits_u32(true, *reg, index_pos, nvic_idx_len, err);
    } else {
      volatile uint32_t* const reg = icer_reg(index / nvic_idx_div);
      *reg = tal_set_bits_u32(true, *reg, index_pos, nvic_idx_len, err);
    }
  }

  bool get_irq_enabled(const int32_t index, bool* const err) {
    if (!valid_irq_index(index)) {
      *err = true;
      return false;
    }
    const volatile uint32_t* const reg = iser_reg(index / nvic_idx_div);
    const int32_t index_pos = index % nvic_idx_div;
    return tal_get_bits_u32(true, *reg, index_pos, nvic_idx_len, err);
  }

  void set_irq_priority(const int32_t index, const int32_t priority, bool* const err) {
    if (!valid_irq_index(index)) {
      *err = true;
      return;
    }
    volatile uint32_t* const reg = ipr_reg(index / ipr_pri_n_div);
    const int32_t index_pos = index % ipr_pri_n_div;
    const uint32_t ipr_val = tal_cast_u32i(priority, err);
    *reg = tal_write_bits_u32(ipr_val, *reg, index_pos, ipr_pri_n_len, err);
  }

  int32_t get_irq_priority(const int32_t index, bool* const err) {
    if (!valid_irq_index(index)) { 
      *err = true;
      return 0; 
    }
    volatile uint32_t* const reg = ipr_reg(index / ipr_pri_n_div);
    const int32_t index_pos = index % ipr_pri_n_div;
    const uint32_t priority = tal_read_bits_u32(*reg, index_pos, ipr_pri_n_len, err);
    tal_assert(priority <= INT32_MAX);
    return (int32_t)priority;
  }

  void set_irq_pending(const int32_t index, const bool pending, 
      bool* const err) {
    if (!valid_irq_index(index)) { 
      *err = true;
      return;
    }
    const int32_t index_pos = index % nvic_idx_div;
    if (pending) {
      volatile uint32_t* const reg = ispr_reg(index / nvic_idx_div);
      *reg = tal_set_bits_u32(true, *reg, index_pos, nvic_idx_len, err);
    } else {
      volatile uint32_t* const reg = icpr_reg(index / nvic_idx_div);
      *reg = tal_set_bits_u32(true, *reg, index_pos, nvic_idx_len, err);
    }
  }

  bool get_irq_pending(const int32_t index, bool* const err) {
    if (!valid_irq_index(index)) {
      *err = true;
      return false;
    }
    const volatile uint32_t* const reg = ispr_reg(index / nvic_idx_div);
    const int32_t index_pos = index % nvic_idx_div;
    return tal_get_bits_u32(true, *reg, index_pos, nvic_idx_len, err);
  }

  bool get_irq_active(const int32_t index, bool* const err) {
    if (!valid_irq_index(index)) {
      *err = true;
      return false;
    }
    const volatile uint32_t* const reg = iabr_reg(index / nvic_idx_div);
    const int32_t index_pos = index % nvic_idx_div;
    return tal_get_bits_u32(true, *reg, index_pos, nvic_idx_len, err);
  }

#if defined(__cplusplus)
  }
#endif