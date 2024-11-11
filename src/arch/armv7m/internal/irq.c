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
#include "include/tal/mask.h"
#include "include/tal/bit.h"
#include "include/tal/numeric.h"

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
   * @section Function Implementations
   **************************************************************************************************/

  // Complete
  int32_t get_irq_count(void) {
    const uint32_t intlinesum_val = tal_read_mask_u32v(
        ictr_reg, intlinesum_pos, intlinesum_len);
    return tal_max_i32((int32_t)intlinesum_val + 1, vtable_irq_count);    
  }

  // Complete
  bool valid_irq_index(const int32_t index) {
    return tal_in_range_i32(index, 0, get_irq_count());
  }

  // Complete
  bool set_irq_enabled(const int32_t index, const bool enabled) {
    if (!valid_irq_index(index)) { return false; }
    if (enabled) {
      tal_set_mask_u32v(iser_reg(index / nvic_idx_div),
          index % nvic_idx_div, nvic_idx_len);
    } else {
      tal_set_mask_u32v(icer_reg(index / nvic_idx_div),
          index % nvic_idx_div, nvic_idx_len);
    }
    return true;
  }

  // Complete
  bool get_irq_enabled(const int32_t index) {
    if (!valid_irq_index(index)) { return false; }
    return tal_is_set_u32v(iser_reg(index / nvic_idx_div),
        index % nvic_idx_div, nvic_idx_len);
  }

  // Complete
  bool set_irq_priority(const int32_t index, const int32_t priority) {
    if (!valid_irq_index(index) || priority < 0 || 
        tal_bit_width_u32((uint32_t)priority) > ipr_pri_n_len) {
      return false; 
    }
    tal_write_mask_u32v((uint32_t)priority, ipr_reg(index / ipr_pri_n_div),
        index % ipr_pri_n_div, ipr_pri_n_len); 
    return true;
  }

  // Complete
  int32_t get_irq_priority(const int32_t index) {
    if (!valid_irq_index(index)) { return -1; }
    return (int32_t)tal_read_mask_u32v(ipr_reg(index / ipr_pri_n_div),
        index % ipr_pri_n_div, ipr_pri_n_len); 
  }

  // Complete
  bool set_irq_pending(const int32_t index, const bool pending) {
    if (!valid_irq_index(index)) { return false; }
    if (pending) {
      tal_set_mask_u32v(ispr_reg(index / nvic_idx_div),
          index % nvic_idx_div, nvic_idx_len);
    } else {
      tal_set_mask_u32v(icpr_reg(index / nvic_idx_div),
          index % nvic_idx_div, nvic_idx_len);
    }
    return true;
  }

  // Complete
  bool get_irq_pending(const int32_t index) {
    if (!valid_irq_index) { return false; }
    return tal_is_set_u32v(ispr_reg(index / nvic_idx_div),
        index % nvic_idx_div, nvic_idx_len);
  }

  // Complete
  bool get_irq_active(const int32_t index) {
    if (!valid_irq_index(index)) { return false; }
    return tal_is_set_u32v(iabr_reg(index / nvic_idx_div),
        index % nvic_idx_div, nvic_idx_len);
  }

#if defined(__cplusplus)
  }
#endif