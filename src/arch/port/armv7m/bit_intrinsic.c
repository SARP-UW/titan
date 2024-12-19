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
 * @file arch/port/armv7m/bit_intrinsic.c
 * @authors Aaron McBride
 * @brief Implementation of intrinsic bit manipulation/inspection 
 *        operations for the ARMv7-M architecture.
 */

#include <limits.h>
#include "src/arch/interface/bit_intrinsic.h" // header
#include "src/arch/common/soft_bit_intrinsic.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  #define bit_size(x) (int32_t)(sizeof(x) * CHAR_BIT)

  uint8_t arch_clz_u8(uint8_t value) {
    uint32_t result = 0u;
    asm (
      "clz %[result_], %[value_]"
      : [result_] "=r" (result)
      : [value_] "r" (value)
    );
    static const int32_t offset = bit_size(value) - bit_size(result);
    return (int32_t)result - offset;
  }

  uint16_t arch_clz_u16(uint16_t value) {
    uint32_t result = 0u;
    asm (
      "clz %[result_], %[value_]"
      : [result_] "=r" (result)
      : [value_] "r" (value)
    );
    static const int32_t offset = bit_size(value) - bit_size(result);
    return (int32_t)result - offset;
  }

  uint32_t arch_clz_u32(uint32_t value) {
    uint32_t result = 0u;
    asm (
      "clz %[result_], %[value_]"
      : [result_] "=r" (result)
      : [value_] "r" (value)
    );
    static const int32_t offset = bit_size(value) - bit_size(result);
    return (int32_t)result - offset;
  }
  
  uint64_t arch_clz_u64(uint64_t value) {
    static const int32_t h_shift = bit_size(value) / 2;
    const int32_t h_result = arch_clz_u32((uint32_t)(value >> h_shift));
    const int32_t l_result = arch_clz_u32((uint32_t)value);
    return h_result + (h_result == bit_size(value) ? l_result : 0);
  }

  uint8_t arch_popcnt_u8(uint8_t value);
  uint16_t arch_popcnt_u16(uint16_t value);
  uint32_t arch_popcnt_u32(uint32_t value);
  uint64_t arch_popcnt_u64(uint64_t value);

  uint8_t arch_bit_rev_u8(uint8_t value);
  uint16_t arch_bit_rev_u16(uint16_t value);
  uint32_t arch_bit_rev_u32(uint32_t value);
  uint64_t arch_bit_rev_u64(uint64_t value);

  uint8_t arch_byte_rev_u16(uint16_t value);
  uint32_t arch_byte_rev_u32(uint32_t value);
  uint64_t arch_byte_rev_u64(uint64_t value);

  uint8_t arch_bit_insert_u8(uint8_t value, uint8_t dst, int32_t pos, int32_t len);
  uint16_t arch_bit_insert_u16(uint16_t value, uint16_t dst, int32_t pos, int32_t len);
  uint32_t arch_bit_insert_u32(uint32_t value, uint32_t dst, int32_t pos, int32_t len);
  uint64_t arch_bit_insert_u64(uint64_t value, uint64_t dst, int32_t pos, int32_t len);

  uint8_t arch_bit_extract_u8(uint8_t value, int32_t pos, int32_t len);
  uint16_t arch_bit_extract_u16(uint16_t value, int32_t pos, int32_t len);
  uint32_t arch_bit_extract_u32(uint32_t value, int32_t pos, int32_t len);
  uint64_t arch_bit_extract_u64(uint64_t value, int32_t pos, int32_t len);
  
#if defined(__cplusplus)
  } // extern "C"
#endif