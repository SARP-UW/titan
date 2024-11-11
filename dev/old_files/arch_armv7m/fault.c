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
 * @file src/arch/armv7m/internal/fault.c
 * @authors Aaron McBride
 * @brief Implementation of fault management facilities.
 */

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Constants and Helper Functions/Macros
   **************************************************************************************************/

  // SCS registers
  #define shpr1_reg (volatile uint32_t*)0xE000ED18
  #define shcsr_reg (volatile uint32_t*)0xE000ED24
  #define cfsr_reg (volatile uint32_t*)0xE000ED28
  #define mmfsr_reg (volatile uint8_t*)0xE000ED28
  #define bfsr_reg (volatile uint8_t*)0xE000ED29
  #define ufsr_reg (volatile uint16_t*)0xE000ED2A
  #define hfsr_reg (volatile uint32_t*)0xE000ED2C
  #define mmfar_reg (volatile uint32_t*)0xE000ED34
  #define bfar_reg (volatile uint32_t*)0xE000ED38

  // pri_4 regval location (mem fault - shpr1)
  #define pri_4_pos 0
  #define pri_4_len 8

  // pri_5 regval location (bus fault - shpr1)
  #define pri_5_pos 8
  #define pri_5_len 8

  // pri_6 regval location (usage fault - shpr1)
  #define pri_6_pos 16
  #define pri_6_len 8 

  // memfaultact regval location (mem fault interrupt active - shcsr)
  #define memfaultact_pos 0
  #define memfaultact_len 1

  // busfaultact regval location (bus fault interrupt active - shcsr)
  #define busfaultact_pos 1
  #define busfaultact_len 1

  // usgfaultact regval location (usage fault interrupt active - shcsr)
  #define usgfaultact_pos 3
  #define usgfaultact_len 1

  // usgfaultpended regval location (usage fault interrupt pending - shcsr)
  #define usgfaultpended_pos 12
  #define usgfaultpended_len 1

  // memfaultpended regval location (mem fault interrupt pending - shcsr)
  #define memfaultpended_pos 13
  #define memfaultpended_len 1

  // busfaultpended regval location (bus fault interrupt pending - shcsr)
  #define busfaultpended_pos 14
  #define busfaultpended_len 1

  // memfaultena regval location (enable memfault - shcsr)
  #define memfaultena_pos 16
  #define memfaultena_len 1

  // busfaultena regval location (enable busfault - shcsr)
  #define busfaultena_pos 17
  #define busfaultena_len 1

  // usgfaultena regval location (enable usgfault - shcsr)
  #define usgfaultena_pos 18
  #define usgfaultena_len 1

  // cfsr_mem regval location (mem fault id - cfsr)
  #define cfsr_mem_pos 0
  #define cfsr_mem_len 8

  // cfsr_bus regval location (bus fault id - cfsr)
  #define cfsr_bus_pos 8
  #define cfsr_bus_len 8

  // cfsr_usg regval location (usage fault id - cfsr)
  #define cfsr_usg_pos 16
  #define cfsr_usg_len 16

  // debugevt regval location (hard fault source: debug event - cfsr)
  #define debugevt_pos 31
  #define debugevt_len 1

  // forced regval location (hard fault source: priority escalation - cfsr)
  #define forced_pos 30
  #define forced_len 1

  // vecttbl regval location (hard fault source: vector table read - cfsr)
  #define vecttbl_pos 1
  #define vecttbl_len 1

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

  // ibuserr regval location (bus fault: instruction bus error - bfsr)
  #define ibuserr_pos 0
  #define ibuserr_len 1

  // preciserr regval location (bus fault: precise data bus error - bfsr)
  #define preciserr_pos 1
  #define preciserr_len 1

  // impreciserr regval location (bus fault: imprecise data bus error - bfsr)
  #define impreciserr_pos 2
  #define impreciserr_len 1

  // unstkerr regval location (bus fault: unstacking error - bfsr)
  #define unstkerr_pos 3
  #define unstkerr_len 1

  // stkerr regval location (bus fault: stacking error - bfsr)
  #define stkerr_pos 4
  #define stkerr_len 1

  // lsperr regval location (bus fault: lazy fp state preservation - bfsr)
  #define lsperr_pos 5
  #define lsperr_len 1

  // bfarvalid regval location (bus fault addr valid - bfsr)
  #define bfarvalid_pos 7
  #define bfarvalid_len 1

  // undefinstr regval location (usage fault: undefined instruction - ufsr)
  #define undefinstr_pos 0
  #define undefinstr_len 1

  // invstate regval location (usage fault: invalid state - ufsr)
  #define invstate_pos 1
  #define invstate_len 1

  // invpc regval location (usage fault: invalid pc load - ufsr)
  #define invpc_pos 2
  #define invpc_len 1

  // nocp regval location (usage fault: no coprocessor - ufsr)
  #define nocp_pos 3
  #define nocp_len 1

  // unaligned regval location (usage fault: unaligned access - ufsr)
  #define unaligned_pos 8
  #define unaligned_len 1

  // divbyzero regval location (usage fault: divide by zero - ufsr)
  #define divbyzero_pos 9
  #define divbyzero_len 1

  /**************************************************************************************************
   * @section Function Implementations
   **************************************************************************************************/

  // Complete
  void set_mem_fault_enabled(const bool enabled) {
    tal_write_mask_u32v((uint32_t)enabled, shcsr_reg, 
        memfaultena_pos, memfaultena_len);
  }

  // Complete
  void set_bus_fault_enabled(const bool enabled) {
    tal_write_mask_u32v((uint32_t)enabled, shcsr_reg, 
        busfaultena_pos, busfaultena_len);
  }

  // Complete
  void set_usage_fault_enabled(const bool enabled) {
    tal_write_mask_u32v((uint32_t)enabled, shcsr_reg, 
        usgfaultena_pos, usgfaultena_len);
  }

  // Complete
  bool get_memnmanage_fault_enabled(void) {
    return tal_is_set_u32v(shcsr_reg, memfaultena_pos, memfaultena_len);
  }

  // Complete
  bool get_bus_fault_enabled(void) {
    return tal_is_set_u32v(shcsr_reg, busfaultena_pos, busfaultena_len);
  }

  // Complete
  bool get_usage_fault_enabled(void) {
    return tal_is_set_u32v(shcsr_reg, usgfaultena_pos, usgfaultena_len);
  }

  // Complete
  bool set_mem_fault_priority(const int32_t priority) {
    if (priority < 0 || tal_bit_width_u32((uint32_t)priority) > pri_4_len) {
      return false;
    }
    tal_write_mask_u32v((uint32_t)priority, shpr1_reg, pri_4_pos, pri_4_len);
    return true;
  }

  // Complete
  bool set_bus_fault_priority(const int32_t priority) {
    if (priority < 0 || tal_bit_width_u32((uint32_t)priority) > pri_5_len) {
      return false;
    }
    tal_write_mask_u32v((uint32_t)priority, shpr1_reg, pri_5_pos, pri_5_len);
    return true;
  }

  // Complete
  bool set_usage_fault_priority(const int32_t priority) {
    if (priority < 0 || tal_bit_width_u32((uint32_t)priority) > pri_6_len) {
      return false;
    }
    tal_write_mask_u32v((uint32_t)priority, shpr1_reg, pri_6_pos, pri_6_len);
    return true;
  }

  // Complete
  int32_t get_mem_fault_priority(void) {
    return (int32_t)tal_read_mask_u32v(shpr1_reg, pri_4_pos, pri_4_len);
  }

  // Complete
  int32_t get_bus_fault_priority(void) {
    return (int32_t)tal_read_mask_u32v(shpr1_reg, pri_5_pos, pri_5_len);
  }

  // Complete
  int32_t get_usage_fault_priority(void) {
    return (int32_t)tal_read_mask_u32v(shpr1_reg, pri_6_pos, pri_6_len);
  }

  // Complete
  void set_mem_fault_pending(const bool pending) {
    tal_set_mask_u32v(shcsr_reg, memfaultpended_pos, memfaultpended_len);
  }

  // Complete
  void set_bus_fault_pending(const bool pending) {
    tal_set_mask_u32v(shcsr_reg, busfaultpended_pos, busfaultpended_len);
  }

  // Complete
  void set_usage_fault_pending(const bool pending) {
    tal_set_mask_u32v(shcsr_reg, usgfaultpended_pos, usgfaultpended_len);
  }

  // Complete
  bool get_mem_fault_pending(void) {
    return tal_is_set_u32v(shcsr_reg, memfaultpended_pos, memfaultpended_len);
  }

  // Complete
  bool get_bus_fault_pending(void) {
    return tal_is_set_u32v(shcsr_reg, busfaultpended_pos, busfaultpended_len);
  }

  // Complete
  bool get_usage_fault_pending(void) {
    return tal_is_set_u32v(shcsr_reg, usgfaultpended_pos, usgfaultpended_len);
  }

  // Complete
  bool get_mem_fault_active(void) {
    return tal_is_set_u32v(shcsr_reg, memfaultact_pos, memfaultact_len);
  }

  // Complete
  bool get_bus_fault_active(void) {
    return tal_is_set_u32v(shcsr_reg, busfaultact_pos, busfaultact_len);
  }

  // Complete
  bool get_usage_fault_active(void) {
    return tal_is_set_u32v(shcsr_reg, usgfaultact_pos, usgfaultact_len);
  }

  // Complete
  bool get_hard_fault_active(void) {
    return tal_is_set_u32v(cfsr_reg, debugevt_pos, debugevt_len) ||
        tal_is_set_u32v(cfsr_reg, forced_pos, forced_len) ||
        tal_is_set_u32v(cfsr_reg, vecttbl_pos, vecttbl_len);
  }

  // Complete
  mem_fault_info_t get_mem_fault_info(void) {
    mem_fault_info_t info = {
      .addr_valid = false, 
      .fault_addr = 0, 
      .id = mem_fault_none
    };
    if (get_mem_fault_active()) {
      info.fault_addr = *mmfar_reg;
      info.addr_valid = tal_is_set_u8v(mmfsr_reg, mmar_valid_pos, mmar_valid_len);
      if (tal_is_set_u8v(mmfsr_reg, iaccviol_pos, iaccviol_len)) {
        info.id = mem_fault_instruction;
      } else if (tal_is_set_u8v(mmfsr_reg, daccviol_pos, daccviol_len)) {
        info.id = mem_fault_data;
      } else if (tal_is_set_u8v(mmfsr_reg, munstkerr_pos, munstkerr_len)) {
        info.id = mem_fault_unstacking;
      } else if (tal_is_set_u8v(mmfsr_reg, mlsperr_pos, mlsperr_len)) {
        info.id = mem_fault_fp_state;
      } else if (tal_is_set_u8v(mmfsr_reg, mstkerr_pos, mstkerr_len)) {
        info.id = mem_fault_stacking;
      } else {
        info.id = mem_fault_unknown;
      }
    }
    return info;
  }

  // Complete
  bus_fault_info_t get_bus_fault_info(void) {
    bus_fault_info_t info = {
      .addr_valid = false, 
      .fault_addr = 0, 
      .id = bus_fault_none
    };
    if (get_bus_fault_active()) {
      info.fault_addr = *bfar_reg;
      info.addr_valid = tal_is_set_u8v(bfsr_reg, bfarvalid_pos, bfarvalid_len);
      if (tal_is_set_u8v(bfsr_reg, ibuserr_pos, ibuserr_len)) {
        info.id = bus_fault_instruction;
      } else if (tal_is_set_u8v(bfsr_reg, preciserr_pos, preciserr_len)) {
        info.id = bus_fault_sync_data;
      } else if (tal_is_set_u8v(bfsr_reg, impreciserr_pos, impreciserr_len)) {
        info.id = bus_fault_async_data;
      } else if (tal_is_set_u8v(bfsr_reg, unstkerr_pos, unstkerr_len)) {
        info.id = bus_fault_unstacking;
      } else if (tal_is_set_u8v(bfsr_reg, lsperr_pos, lsperr_len)) {
        info.id = bus_fault_fp_state;
      } else if (tal_is_set_u8v(bfsr_reg, stkerr_pos, stkerr_len)) {
        info.id = bus_fault_stacking;
      } else {
        info.id = bus_fault_unknown;
      }
    }
    return info;
  }

  // Complete
  usage_fault_id_t get_usage_fault_info(void) {
    usage_fault_id_t info_id = usage_fault_none;
    if (get_usage_fault_active()) {
      if (tal_is_set_u16v(ufsr_reg, nocp_pos, nocp_len)) {
        info_id = usage_fault_coprocessor;
      } else if (tal_is_set_u16v(ufsr_reg, undefinstr_pos, undefinstr_len)) {
        info_id = usage_fault_instruction;
      } else if (tal_is_set_u16v(ufsr_reg, invstate_pos, invstate_len)) {
        info_id = usage_fault_state;
      } else if (tal_is_set_u16v(ufsr_reg, invpc_pos, invpc_len)) {
        info_id = usage_fault_return;
      } else if (tal_is_set_u16v(ufsr_reg, unaligned_pos, unaligned_len)) {
        info_id = usage_fault_unaligned;
      } else if (tal_is_set_u16v(ufsr_reg, divbyzero_pos, divbyzero_len)) {
        info_id = usage_fault_division;
      } else {
        info_id = usage_fault_unknown;
      }
    }
    return info_id;
  }

  // Complete
  hard_fault_id_t get_hard_fault_info(void) {
    hard_fault_id_t info_id = hard_fault_none;
    if (get_hard_fault_active()) {
      if (tal_is_set_u32v(hfsr_reg, debugevt_pos, debugevt_len)) {
        info_id = hard_fault_debug;
      } else if (tal_is_set_u32v(hfsr_reg, vecttbl_pos, vecttbl_len)) {
        info_id = hard_fault_vecttbl;
      } else if (tal_is_set_u32v(hfsr_reg, forced_pos, forced_len)) {
        info_id = hard_fault_invalid_prio;
      } else {
        info_id = hard_fault_unknown;
      }
    }
    return info_id;
  }
  
#if defined(__cplusplus)
  }
#endif