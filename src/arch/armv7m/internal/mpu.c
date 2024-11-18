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
 * @file src/arch/armv7m/internal/mpu.c
 * @authors Aaron McBride
 * @brief Implementation of Memory Protection Unit (MPU) management facilities.
 */

#include "src/arch/armv7m/internal/mpu.h"
#include "include/tal/bit.h"
#include "include/tal/numeric.h"
#include "include/tal/tmp.h"
#include "include/tal/math.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Register/Regval Constants
   **************************************************************************************************/

  // MPU registers
  #define dregion_reg (const volatile uint8_t*)0xE000ED91
  #define mpu_ctrl_reg (volatile uint32_t*)0xE000ED94
  #define mpu_rnr_reg (volatile uint8_t*)0xE000ED98
  #define mpu_rbar_reg (volatile uint32_t*)0xE000ED9C
  #define mpu_rasr_reg (volatile uint32_t*)0xE000EDA0

  // Interrupt (Fault) Registers
  #define shpr1_reg (volatile uint32_t*)0xE000ED18
  #define shcsr_reg (volatile uint32_t*)0xE000ED24
  #define mmfsr_reg (volatile uint8_t*)0xE000ED28
  #define mmfar_reg (volatile uint32_t*)0xE000ED34

  // Misc registers
  #define ccr_reg (volatile uint32_t*)0xE000ED14

  // mpu enable regval location (enables mpu - mpu_ctrl)
  #define mpu_enable_pos 0
  #define mpu_enable_len 1

  // hfnmiena regval location (enables universal prilvl 0 access - mpu_ctrl)
  #define hfnmiena_pos 1
  #define hfnmiena_len 1

  // privdefena regval location (enables universal privleged access - mpu_ctrl)
  #define privdefena_pos 2
  #define privdefena_len 1

  // addr regval location (region address - mpu_rbar)
  #define addr_pos 5
  #define addr_len 27

  // rasr_enable regval location (region enable - mpu_rasr)
  #define rasr_enable_pos 0
  #define rasr_enable_len 1

  // size regval location (region size - mpu_rasr)
  #define size_pos 1
  #define size_len 5

  // srd regval location (subregion select - mpu_rasr)
  #define srd_pos 8
  #define srd_len 8

  // tex_scb regval location (memory type attributes - mpu_rasr)
  #define tex_scb_pos 16
  #define tex_scb_len 6

  // ap regval location (access policy region attribte - mpu_rasr)
  #define ap_pos 24
  #define ap_len 3

  // xn regval location (execute never region attribute - mpu_rasr)
  #define xn_pos 28
  #define xn_len 1

  // pri_4 regval location (mem fault - shpr1)
  #define pri_4_pos 0
  #define pri_4_len 8

  // memfaultpended regval location (mem fault interrupt pending - shcsr)
  #define memfaultpended_pos 13
  #define memfaultpended_len 1

  // memfaultact regval location (mem fault interrupt active - shcsr)
  #define memfaultact_pos 0
  #define memfaultact_len 1

  // memfaultena regval location (enable memfault - shcsr)
  #define memfaultena_pos 16
  #define memfaultena_len 1

  // cfsr_mem regval location (mem fault id - cfsr)
  #define cfsr_mem_pos 0
  #define cfsr_mem_len 8

  // iaccviol regval location (mem fault: instruction access violation - mmfsr)
  #define iaccviol_pos 0
  #define iaccviol_len 1

  // daccviol regval location (mem fault: data access violation - mmfsr)
  #define daccviol_pos 1
  #define daccviol_len 1

  // munstkerr regval location (mem fault: unstacking error - mmfsr)
  #define munstkerr_pos 3
  #define munstkerr_len 1

  // mstkerr regval location (mem fault: stacking error - mmfsr)
  #define mstkerr_pos 4
  #define mstkerr_len 1

  // mlsperr regval location (mem fault: lazy fp state preservation - mmfsr)
  #define mlsperr_pos 5
  #define mlsperr_len 1

  // mmar_valid regval location (mem addr valid - mmfsr)
  #define mmar_valid_pos 7
  #define mmar_valid_len 1

  // unalign_trp regval location (unaligned memory trap enabled - ccr)
  #define unalign_trp_pos 3
  #define unalign_trp_len 1

  /**************************************************************************************************
   * @section MPU Reference Maps
   **************************************************************************************************/

  // Mapping from mpu_region_type_t to tex_scb regval
  typedef struct {
    uint32_t tex_scb_value;
    mpu_region_type_t type;
  }tex_scb_ref_t; 

  #define tex_scb_ref_len (sizeof(tex_scb_ref_t) / sizeof(tex_scb_ref_t[0]))
  static const tex_scb_ref_t tex_scb_ref[10] = {
    {.tex_scb_value = 0b000100, .type = {
        .mem_type = mpu_mem_strongly_ordered, 
        .cache_policy = mpu_cache_disabled, 
        .shared = true}},
    {.tex_scb_value = 0b000101, .type = {
        .mem_type = mpu_mem_device, 
        .cache_policy = mpu_cache_disabled, 
        .shared = true}},
    {.tex_scb_value = 0b000010, .type = {
        .mem_type = mpu_mem_normal, 
        .cache_policy = mpu_cache_write_through, 
        .shared = false}},
    {.tex_scb_value = 0b000110, .type = {
        .mem_type = mpu_mem_normal, 
        .cache_policy = mpu_cache_write_through, 
        .shared = true}},
    {.tex_scb_value = 0b000011, .type = {
        .mem_type = mpu_mem_normal, 
        .cache_policy = mpu_cache_write_back, 
        .shared = false}},
    {.tex_scb_value = 0b000111, .type = {
        .mem_type = mpu_mem_normal, 
        .cache_policy = mpu_cache_write_back, 
        .shared = true}},
    {.tex_scb_value = 0b001000, .type = {
        .mem_type = mpu_mem_normal, 
        .cache_policy = mpu_cache_disabled, 
        .shared = false}},
    {.tex_scb_value = 0b001100, .type = {
        .mem_type = mpu_mem_normal, 
        .cache_policy = mpu_cache_disabled, 
        .shared = true}},
    {.tex_scb_value = 0b001011, .type = {
        .mem_type = mpu_mem_normal, 
        .cache_policy = mpu_cache_write_back_alloc, 
        .shared = false}},
    {.tex_scb_value = 0b001111, .type = {
        .mem_type = mpu_mem_normal, 
        .cache_policy = mpu_cache_write_back_alloc, 
        .shared = true}},
    {.tex_scb_value = 0b010000, .type = {
        .mem_type = mpu_mem_device, 
        .cache_policy = mpu_cache_disabled, 
        .shared = false}},
  };

  // Mapping from mpu_region_policy_t to ap regval
  typedef struct {
    uint32_t ap_value;
    mpu_access_t priv_access;
    mpu_access_t npriv_access;
  }ap_ref_t;

  #define ap_ref_len (sizeof(ap_ref) / sizeof(ap_ref_t))
  static const ap_ref_t ap_ref[6] = {
    {.ap_value = 0b000, 
        .priv_access = mpu_access_disabled, 
        .npriv_access = mpu_access_disabled},
    {.ap_value = 0b001, 
        .priv_access = mpu_access_read_write, 
        .npriv_access = mpu_access_disabled},
    {.ap_value = 0b010, 
        .priv_access = mpu_access_read_write, 
        .npriv_access = mpu_access_read_only},
    {.ap_value = 0b011, 
        .priv_access = mpu_access_read_write, 
        .npriv_access = mpu_access_read_write},
    {.ap_value = 0b101, 
        .priv_access = mpu_access_read_only, 
        .npriv_access = mpu_access_disabled},
    {.ap_value = 0b110, 
        .priv_access = mpu_access_read_only, 
        .npriv_access = mpu_access_read_only},
  };

  /**************************************************************************************************
   * @section Helper Functions/Macros
   **************************************************************************************************/

  static bool valid_mpu_region(const int32_t index) {
    return tal_in_range_i32(index, 0, get_mpu_region_count() - 1);
  }

  static bool valid_mpu_region(const int32_t index, 
      const mpu_loc_t loc) {
    tal_assert(mpu_min_region_size > 0);
    if (!tal_in_range_i32(loc.size, mpu_min_region_size, mpu_max_region_size) ||
        loc.size % 2 != 0 || !tal_perfect_root_i32(loc.size, 2, NULL)) {
      return false;
    }
    const int32_t r_size = tal_root_i32(loc.size, 2, NULL);
  }

  /**************************************************************************************************
   * @section MPU Core Management Facilities
   **************************************************************************************************/

  void init_mpu() {
    /// @todo
      // tal_set_mask_u32v(mpu_ctrl_reg, hfnmiena_pos, hfnmiena_len);
      // tal_set_mask_u32v(mpu_ctrl_reg, privdefena_pos, privdefena_len);
  }

  int32_t get_mpu_region_count(void) {
    return (int32_t)(*dregion_reg);
  }

  void set_mpu_enabled(const bool enabled) {
    *mpu_ctrl_reg = tal_set_bits_u32(enabled, *mpu_ctrl_reg, mpu_enable_pos, mpu_enable_len, NULL);
  }

  bool get_mpu_enabled(void) {
    return tal_get_bits_u32(true, *mpu_ctrl_reg, mpu_enable_pos, mpu_enable_len, NULL);
  }

  mpu_access_t query_npriv_policy(const uint64_t addr) {

  }

  mpu_access_t query_priv_policy(const uint64_t addr) {

  }

  bool query_xn_policy(const uint64_t addr) {

  }

  /**************************************************************************************************
   * @section MPU Region Management Facilities
   **************************************************************************************************/

  void set_mpu_region_enabled(const int32_t index, const bool enabled, bool* const err) {
    if (!valid_mpu_region(index)) {
      *err = true;
      return;
    }
    *mpu_rnr_reg = tal_cast_u8i(index, NULL);
    *mpu_rasr_reg = tal_set_bits_u32(enabled, *mpu_rasr_reg, rasr_enable_pos, rasr_enable_len, NULL);
  }

  bool get_mpu_region_enabled(const int32_t index, bool* const err) {
    if (!valid_mpu_region(index)) {
      *err = true;
      return false;
    }
    *mpu_rnr_reg = tal_cast_u8i(index, NULL);
    return tal_get_bits_u32(true, *mpu_rasr_reg, rasr_enable_pos, rasr_enable_len, NULL);
  }

  void set_mpu_region_location(const int32_t index, const mpu_loc_t loc, bool* const err) {
    if (!valid_mpu_region(index) || loc.size <= 0 || 
        !tal_perfect_root_i32(loc.size, 2, NULL)) {
      *err = true;
      return;
    }
    const uint32_t size_pow = 
    const uint32_t size_pow = tal_ctz_u32((uint32_t)loc.size) + 1;
    *mpu_rnr_reg = (uint8_t)index;
    tal_write_mask_u32v((uint32_t)loc.addr, mpu_rbar_reg, addr_pos, addr_len);
    tal_write_mask_u32v(size_pow, mpu_rasr_reg, size_pos, size_len);
    return true;
  }

  mpu_loc_t get_mpu_region_loc(const int32_t index) {
    mpu_loc_t loc = {.addr = 0, .size = -1};
    if (valid_mpu_region(index)) {
      *mpu_rnr_reg = (uint8_t)index;
      const uint32_t size_pow = tal_read_mask_u32v(mpu_rasr_reg, size_pos, size_len);
      loc.size = 
      loc.addr = tal_read_mask_u32v(mpu_rbar_reg, addr_pos, addr_len);
    }
    return loc;
  }
  

  /**************************************************************************************************
   * @section MPU Management Facilities
   **************************************************************************************************/


  // Complete
  bool set_mpu_subregion_enabled(const int32_t index, 
      const int32_t sub_index, const bool enabled) {
    if (!valid_mpu_region(index) || sub_index >= mpu_subregion_cnt) { 
      return false; 
    }
    *mpu_rnr_reg = (uint8_t)index;
    if (enabled) {
      const int32_t r_size = (int32_t)tal_read_mask_u32v(
          mpu_rasr_reg, size_pos, size_len);
      if (r_size < (mpu_min_subregion_size * mpu_subregion_cnt)) { 
        return false; 
      }
      if (sub_index < 0) {
        tal_clear_mask_u32v(mpu_rasr_reg, srd_pos, srd_len);
      } else {
        tal_set_mask_u32v(mpu_rasr_reg, srd_pos + sub_index, 1);
      }
    } else {
      if (sub_index < 0) {
        tal_clear_mask_u32v(mpu_rasr_reg, srd_pos, srd_len);
      } else {
        tal_clear_mask_u32v(mpu_rasr_reg, srd_pos + sub_index, 1);
      }
    }
    return true;
  }

  // Complete
  bool get_mpu_subregion_enabled(const int32_t index, 
      const int32_t sub_index) {
    if (!valid_mpu_region(index) || sub_index < 0 || 
        sub_index >= mpu_subregion_cnt) {
      return false;
    }
    *mpu_rnr_reg = (uint8_t)index;
    return tal_is_set_u32v(mpu_rasr_reg, srd_pos + sub_index, 1);
  }



  // Complete
  mpu_loc_t get_mpu_subregion_loc(const int32_t index, 
      const int32_t sub_index) {
    mpu_loc_t loc;
    if (valid_mpu_region(index) && sub_index >= 0 && 
        sub_index < mpu_subregion_cnt) {
      *mpu_rnr_reg = (uint8_t)index;
      const int32_t r_size = (int32_t)tal_read_mask_u32v(
          mpu_rasr_reg, size_pos, size_len);
      if (r_size >= (mpu_min_subregion_size * mpu_subregion_cnt)) {
        loc.addr = tal_read_mask_u32v(mpu_rbar_reg, addr_pos, addr_len);
        loc.size = tal_read_mask_u32v(mpu_rasr_reg, size_pos, size_len);
      }
    }
    return loc;
  }

  // Complete
  int32_t find_mpu_region(const uint32_t addr) {
    for (int32_t i = 0; i < get_mpu_region_count(); ++i) {
      const mpu_loc_t loc = get_mpu_region_loc(i);
      if (tal_in_range_u32(addr, loc.addr, loc.addr + (uint32_t)loc.size)) {
        return i;
      }
    }
    return -1;
  }

  // Complete
  int32_t find_mpu_subregion(const int32_t index, const uint32_t addr) {
    if (!valid_mpu_region(index)) { return -1; }
    const mpu_loc_t loc = get_mpu_region_loc(index);
    const int32_t sr_size = loc.size / mpu_subregion_cnt;
    if (tal_in_range(addr, loc.addr, loc.addr + (uint32_t)loc.size) ||
        sr_size < mpu_min_subregion_size) {
      return -1; 
    }
    return (int32_t)(addr - loc.addr) / sr_size;    
  }

  // Complete
  bool set_mpu_region_type(const int32_t index, const mpu_region_type_t type) {
    if (!valid_mpu_region(index)) { return false; }
    for (int32_t i = 0; i < tex_scb_ref_len; ++i) {
      if (tex_scb_ref[i].type.mem_type == type.mem_type && 
          tex_scb_ref[i].type.cache_policy == type.cache_policy && 
          tex_scb_ref[i].type.shared == type.shared) {
        *mpu_rnr_reg = (uint8_t)index;
        tal_write_mask_u32_v(tex_scb_ref[i].tex_scb_value, 
            mpu_rasr_reg, tex_scb_pos, tex_scb_len);
        return true;
      }
    }
    return false;
  }

  // Complete
  mpu_region_type_t get_mpu_region_type(const int32_t index) {
    mpu_region_type_t r_type = {
      .mem_type = mpu_mem_null,
      .cache_policy = mpu_cache_null,
      .shared = false,
    };
    if (valid_mpu_region(index)) {
      *mpu_rnr_reg = (uint8_t)index;
      const uint32_t tex_scb_value = tal_read_mask_u32v(
          mpu_rasr_reg, tex_scb_pos, tex_scb_len);
      for (int32_t i = 0; i < tex_scb_ref_len; ++i) {
        if (tex_scb_ref[i].tex_scb_value == tex_scb_value) {
          r_type = tex_scb_ref[i].type;
          break;
        }
      }
    }
    return r_type;
  }

  // Complete
  bool set_mpu_region_policy(const int32_t index, 
      const mpu_region_policy_t policy) {
    if (!valid_mpu_region(index)) { return false; }
    for (int32_t i = 0; i < ap_ref_len; ++i) {
      if (ap_ref[i].priv_access == policy.priv_access && 
          ap_ref[i].npriv_access == policy.npriv_access) {
        *mpu_rnr_reg = (uint8_t)index;
        tal_write_mask_u32v(ap_ref[i].ap_value,
            mpu_rasr_reg, ap_pos, ap_len);
        tal_write_mask_u32v((uint32_t)!policy.exec_enabled, 
            mpu_rasr_reg, xn_pos, xn_len);
        return true;
      }
    }
    return false;
  }

  // Complete
  mpu_region_policy_t get_mpu_region_policy(const int32_t index) {
    mpu_region_policy_t r_pol = {
      .priv_access = mpu_access_null,
      .npriv_access = mpu_access_null,
      .exec_enabled = false,
    };
    if (valid_mpu_region(index)) {
      *mpu_rnr_reg = (uint8_t)index;
      r_pol.exec_enabled = !tal_is_set_u32v(
          mpu_rasr_reg, xn_pos, xn_len);
      const uint32_t ap_value = tal_read_mask_u32v(
          mpu_rasr_reg, ap_pos, ap_len);
      for (int32_t i = 0; i < ap_ref_len; ++i) {
        if (ap_ref[i].ap_value == ap_value) {
          r_pol.priv_access = ap_ref[i].priv_access;
          r_pol.npriv_access = ap_ref[i].npriv_access;
          break;
        }
      }
    }
    return r_pol;
  }

  /**************************************************************************************************
   * @section Fault Management Facilities
   **************************************************************************************************/

  // Complete
  void set_memmange_fault_enabled(const bool enabled) {
    tal_write_mask_u32v((uint32_t)enabled, shcsr_reg, 
        memfaultena_pos, memfaultena_len);
  }

  // Complete
  bool get_memmanage_fault_enabled(void) {
    return tal_is_set_u32v(shcsr_reg, memfaultena_pos, memfaultena_len);
  }

  // Complete
  bool set_memmanage_fault_priority(const int32_t priority) {
    if (priority < 0 || tal_bit_width_u32((uint32_t)priority) > pri_4_len) {
      return false;
    }
    tal_write_mask_u32v((uint32_t)priority, shpr1_reg, pri_4_pos, pri_4_len);
    return true;
  }

  // Complete
  int32_t get_memmanage_fault_priority(void) {
    return (int32_t)tal_read_mask_u32v(shpr1_reg, pri_4_pos, pri_4_len);
  }

  // Complete
  void set_memmanage_fault_pending(const bool pending) {
    if (pending) {
      tal_set_mask_u32v(shcsr_reg, memfaultpended_pos, memfaultpended_len);
    } else {
      tal_clear_mask_u32v(shcsr_reg, memfaultpended_pos, memfaultpended_len);
    }
  }

  // Complete
  bool get_memmanage_fault_pending(void) {
    return tal_is_set_u32v(shcsr_reg, memfaultpended_pos, memfaultpended_len);
  }

  // Complete
  bool get_memmanage_fault_active(void) {
    return tal_is_set_u32v(shcsr_reg, memfaultact_pos, memfaultact_len);
  }

  // Complete
  memmanage_fault_info_t get_memmanage_fault_info(void) {
    memmanage_fault_info_t info = {
      .addr_valid = false, 
      .fault_addr = 0, 
      .id = memmanage_fault_none
    };
    if (get_memmanage_fault_active()) {
      info.fault_addr = *mmfar_reg;
      info.addr_valid = tal_is_set_u8v(mmfsr_reg, mmar_valid_pos, mmar_valid_len);
      if (tal_is_set_u8v(mmfsr_reg, iaccviol_pos, iaccviol_len)) {
        info.id = memmanage_fault_instruction;
      } else if (tal_is_set_u8v(mmfsr_reg, daccviol_pos, daccviol_len)) {
        info.id = memmanage_fault_data;
      } else if (tal_is_set_u8v(mmfsr_reg, munstkerr_pos, munstkerr_len)) {
        info.id = memmanage_fault_unstacking;
      } else if (tal_is_set_u8v(mmfsr_reg, mlsperr_pos, mlsperr_len)) {
        info.id = memmanage_fault_fp_state;
      } else if (tal_is_set_u8v(mmfsr_reg, mstkerr_pos, mstkerr_len)) {
        info.id = memmanage_fault_stacking;
      } else {
        info.id = memmanage_fault_unknown;
      }
    }
    return info;
  }

  // Complete
  void set_unaligned_fault_enabled(const bool enabled) {
    tal_write_mask_u32v((uint32_t)enabled, 
        ccr_reg, unalign_trp_pos, unalign_trp_len);
  }

  // Complete
  bool get_unaligned_fault_enabled(void) {
    return tal_is_set_u32v(ccr_reg, unalign_trp_pos, unalign_trp_len);
  }

#if defined(__cplusplus)
  }
#endif