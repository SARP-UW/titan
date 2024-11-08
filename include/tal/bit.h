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
 * @file include/tal/bit.h
 * @authors Aaron McBride
 * @brief Bit manipulation utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "include/tal/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Bit Manipulation Utilities
   **************************************************************************************************/

  /**
   * @brief Evaluates to the number of bits in @p 'type'.
   * @param type The type to get the bit size of.
   */
  #define tal_bit_size(type) (sizeof(type) * CHAR_BIT)

  /**
   * @defgroup tal_rbit
   * @brief Reverses the bits of an integer.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The given value with the 
   *          order of it's bits reversed.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_rbit_u8(const uint8_t value);
  tal_fn_attr_inline inline uint16_t tal_rbit_u16(const uint16_t value);
  tal_fn_attr_inline inline uint32_t tal_rbit_u32(const uint32_t value);
  tal_fn_attr_inline inline uint64_t tal_rbit_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_rbyte
   * @brief Reverses the bits of an integer.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The given value with the 
   *          order of it's bytes reversed.
   * @{
   */
  tal_fn_attr_inline inline uint16_t tal_rbyte_u16(const uint16_t value);
  tal_fn_attr_inline inline uint32_t tal_rbyte_u32(const uint32_t value);
  tal_fn_attr_inline inline uint64_t tal_rbyte_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_single_bit
   * @brief Determines if an integer is a power of two.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (bool) True if the given value is a power of two, or false otherwise.
   * @note - If an integer is a power of two, it has only one set bit.
   * @{
   */
  tal_fn_attr_inline inline bool tal_single_bit_u8(const uint8_t value);
  tal_fn_attr_inline inline bool tal_single_bit_u16(const uint16_t value);
  tal_fn_attr_inline inline bool tal_single_bit_u32(const uint32_t value);
  tal_fn_attr_inline inline bool tal_single_bit_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_bit_ceil
   * @brief Rounds an integer up to the nearest power of two.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The smallest power 
   *          of two which is greater than or equal to the given value.
   * @note - If an integer is power of two, it has only one set bit.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_bit_ceil_u8(const uint8_t value);
  tal_fn_attr_inline inline uint16_t tal_bit_ceil_u16(const uint16_t value);
  tal_fn_attr_inline inline uint32_t tal_bit_ceil_u32(const uint32_t value);
  tal_fn_attr_inline inline uint64_t tal_bit_ceil_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_bit_floor
   * @brief Rounds an integer down to the nearest power of two.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The greatest power 
   *          of two which is less than or equal to the given value.
   * @note - If an integer is power of two, it has only one set bit.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_bit_floor_u8(const uint8_t value);
  tal_fn_attr_inline inline uint16_t tal_bit_floor_u16(const uint16_t value);
  tal_fn_attr_inline inline uint32_t tal_bit_floor_u32(const uint32_t value);
  tal_fn_attr_inline inline uint64_t tal_bit_floor_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_bit_width
   * @brief Determines the number of bits needed to represent a numeric value.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The minimum number of bits needed to represent the given
   *          value. That is, 1 + log2('value').
   * @note - If the given value is equal to 0, this function returns 0.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_bit_width_u8(const uint8_t value);
  tal_fn_attr_inline inline int32_t tal_bit_width_u16(const uint16_t value);
  tal_fn_attr_inline inline int32_t tal_bit_width_u32(const uint32_t value);
  tal_fn_attr_inline inline int32_t tal_bit_width_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_rotl
   * @brief Performs a circular left shift on an integer value.
   * @param value (unsigned integer denoted by suffix) The value to rotate.
   * @param shift (int32_t) The number of bits to rotate by.
   * @returns (unsigned integer denoted by suffix) The result of circularly 
   *          rotating the given value to the left by 'shift' bits.
   * @note - This function performs a "circular shift", meaining that bits
   *         shifted beyond the end of the integer's range wrap around to
   *         the beginning.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_rotl_u8(
      const uint8_t value, const int32_t shift);
  tal_fn_attr_inline inline uint16_t tal_rotl_u16(
      const uint16_t value, const int32_t shift);
  tal_fn_attr_inline inline uint32_t tal_rotl_u32(
      const uint32_t value, const int32_t shift);
  tal_fn_attr_inline inline uint64_t tal_rotl_u64(
      const uint64_t value, const int32_t shift);
  /** @} */

  /**
   * @defgroup tal_rotr
   * @brief Performs a circular right shift on an integer value.
   * @param value (unsigned integer denoted by suffix) The value to rotate.
   * @param shift (int32_t) The number of bits to rotate by.
   * @returns (unsigned integer denoted by suffix) The result of circularly 
   *          rotating the given value to the right by 'shift' bits.
   * @note - This function performs a "circular shift", meaining that bits
   *         shifted beyond the end of the integer's range wrap around to
   *         the beginning.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_rotr_u8(
      const uint8_t value, const int32_t shift);
  tal_fn_attr_inline inline uint16_t tal_rotr_u16(
      const uint16_t value, const int32_t shift);
  tal_fn_attr_inline inline uint32_t tal_rotr_u32(
      const uint32_t value, const int32_t shift);
  tal_fn_attr_inline inline uint64_t tal_rotr_u64(
      const uint64_t value, const int32_t shift);
  /** @} */

  /**
   * @defgroup tal_clz
   * @brief Counts the number of leading zero bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of leading zero bits in the given value.
   * @note - "Leading" bits are the most significant bits.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_clz_u8(const uint8_t value);
  tal_fn_attr_inline inline int32_t tal_clz_u16(const uint16_t value);
  tal_fn_attr_inline inline int32_t tal_clz_u32(const uint32_t value);
  tal_fn_attr_inline inline int32_t tal_clz_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_clo
   * @brief Counts the number of leading one bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of leading one bits in the given value.
   * @note - "Leading" bits are the most significant bits.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_clo_u8(const uint8_t value);
  tal_fn_attr_inline inline int32_t tal_clo_u16(const uint16_t value);
  tal_fn_attr_inline inline int32_t tal_clo_u32(const uint32_t value);
  tal_fn_attr_inline inline int32_t tal_clo_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_ctz
   * @brief Counts the number of trailing zero bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of trailing zero bits in the given value.
   * @note - "Trailing" bits are the least significant bits.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_ctz_u8(const uint8_t value);
  tal_fn_attr_inline inline int32_t tal_ctz_u16(const uint16_t value);
  tal_fn_attr_inline inline int32_t tal_ctz_u32(const uint32_t value);
  tal_fn_attr_inline inline int32_t tal_ctz_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_cto
   * @brief Counts the number of trailing one bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of trailing one bits in the given value.
   * @note - "Trailing" bits are the least significant bits.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_cto_u8(const uint8_t value);
  tal_fn_attr_inline inline int32_t tal_cto_u16(const uint16_t value);
  tal_fn_attr_inline inline int32_t tal_cto_u32(const uint32_t value);
  tal_fn_attr_inline inline int32_t tal_cto_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup tal_popcount
   * @brief Counts the number of set bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of set bits in the given value.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_popcount_u8(const uint8_t value);
  tal_fn_attr_inline inline int32_t tal_popcount_u16(const uint16_t value);
  tal_fn_attr_inline inline int32_t tal_popcount_u32(const uint32_t value);
  tal_fn_attr_inline inline int32_t tal_popcount_u64(const uint64_t value);
  /** @} */

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  // Denotes the number of binary digits in a numeric type.
  #define tal_uint8_dig__ 3
  #define tal_uint16_dig__ 5
  #define tal_uint32_dig__ 10
  #define tal_uint64_dig__ 20

  // A bit-mask which represents a single byte (unsigned).
  #define tal_byte_mask_u__ ((1u << CHAR_BIT) - 1u)

  // The number of digits in the smallest promoted type (int32_t).
  #define tal_min_prom_dig__ tal_uint32_dig__

  uint8_t tal_rbit_u8(const uint8_t value) {
    uint8_t result = 0;
    for (int32_t i = 0; i < 8; ++i) {
      const uint8_t mask = ((value >> i) & 1u);
      result |= (mask << (8 - 1 - i));
    }
    return result;
  }

  uint16_t tal_rbit_u16(const uint16_t value) {
    uint16_t result = 0;
    for (int32_t i = 0; i < 16; ++i) {
      const uint16_t mask = ((value >> i) & 1u);
      result |= (mask << (16 - 1 - i));
    }
    return result;
  }

  uint32_t tal_rbit_u32(const uint32_t value) {
    uint32_t result = 0;
    for (int32_t i = 0; i < 32; ++i) {
      const uint32_t mask = ((value >> i) & 1u);
      result |= (mask << (32 - 1 - i));
    }
    return result;
  }

  uint64_t tal_rbit_u64(const uint64_t value) {
    uint64_t result = 0;
    for (int32_t i = 0; i < 64; ++i) {
      const uint64_t mask = ((value >> i) & 1u);
      result |= (mask << (64 - 1 - i));
    }
    return result;
  }


  uint16_t tal_rbyte_u16(const uint16_t value) {
    #if defined(TAL_ARCH_ARMV7M)
      uint16_t result;
      asm ("rev16 %0, %1" : "=rm" (result) : "rm" (value));
      return result;
    #else
      uint16_t result = 0;
      for (int32_t i = 0; i < (int32_t)sizeof(uint16_t); ++i) {
        const uint16_t mask = (value >> (i * CHAR_BIT)) & tal_byte_mask_u__;
        result |= (mask << (((int32_t)sizeof(uint16_t) - 1 - i) * CHAR_BIT));
      }
      return result;
    #endif
  }

  uint32_t tal_rbyte_u32(const uint32_t value) {
    #if defined(TAL_ARCH_ARMV7M)
      uint32_t result;
      asm ("rev %0, %1" : "=rm" (result) : "rm" (value));
      return result;
    #else
      uint32_t result = 0;
      for (int32_t i = 0; i < (int32_t)sizeof(uint32_t); ++i) {
        const uint32_t mask = (value >> (i * CHAR_BIT)) & tal_byte_mask_u__;
        result |= (mask << (((int32_t)sizeof(uint32_t) - 1 - i) * CHAR_BIT));
      }
      return result;
    #endif
  }

  uint64_t tal_rbyte_u64(const uint64_t value) {
    uint64_t result = 0;
    for (int32_t i = 0; i < (int32_t)sizeof(uint64_t); ++i) {
      const uint64_t mask = (value >> (i * CHAR_BIT)) & tal_byte_mask_u__;
      result |= (mask << (((int32_t)sizeof(uint64_t) - 1 - i) * CHAR_BIT));
    }
    return result;
  }

  bool tal_single_bit_u8(const uint8_t value) {
    return value && !(value & (value - 1u));
  }

  bool tal_single_bit_u16(const uint16_t value) {
    return value && !(value & (value - 1u));
  }

  bool tal_single_bit_u32(const uint32_t value) {
    return value && !(value & (value - 1u));
  }

  bool tal_single_bit_u64(const uint64_t value) {
    return value && !(value & (value - 1u));
  }

  uint8_t tal_bit_ceil_u8(const uint8_t value) {
    if (value <= 1u) { return 1; }
    const int32_t ovf_offset = (tal_min_prom_dig__) - (tal_uint8_dig__);
    return ((uint8_t)1 << (tal_bit_width_u8(value - 1u) + ovf_offset)) >> ovf_offset;
  }

  uint16_t tal_bit_ceil_u16(const uint16_t value) {
    if (value <= 1u) { return 1; }
    const int32_t ovf_offset = (tal_min_prom_dig__) - (tal_uint16_dig__);
    return ((uint16_t)1 << (tal_bit_width_u16(value - 1u) + ovf_offset)) >> ovf_offset;
  }

  uint32_t tal_bit_ceil_u32(const uint32_t value) {
    if (value <= 1u) { return 1; }
    return (uint32_t)1 << tal_bit_width_u32(value - 1u);
  }

  uint64_t tal_bit_ceil_u64(const uint64_t value) {
    if (value <= 1u) { return 1; }
    return (uint64_t)1 << tal_bit_width_u64(value - 1u);
  }

  uint8_t tal_bit_floor_u8(const uint8_t value) {
    if (value <= 0u) { return 0; }
    return (uint8_t)1 << (tal_bit_width_u8(value - 1u) - 1);
  }

  uint16_t tal_bit_floor_u16(const uint16_t value) {
    if (value <= 0u) { return 0; }
    return (uint16_t)1 << (tal_bit_width_u16(value - 1u) - 1);
  }

  uint32_t tal_bit_floor_u32(const uint32_t value) {
    if (value <= 0u) { return 0; }
    return (uint32_t)1 << (tal_bit_width_u32(value - 1u) - 1);
  }

  uint64_t tal_bit_floor_u64(const uint64_t value) {
    if (value <= 0u) { return 0; }
    return (uint64_t)1 << (tal_bit_width_u64(value - 1u) - 1);
  }

  int32_t tal_bit_width_u8(const uint8_t value) {
    return tal_uint8_dig__ - tal_clz_u8(value);
  }

  int32_t tal_bit_width_u16(const uint16_t value) {
    return tal_uint16_dig__ - tal_clz_u16(value);
  }

  int32_t tal_bit_width_u32(const uint32_t value) {
    return tal_uint32_dig__ - tal_clz_u32(value);
  }

  int32_t tal_bit_width_u64(const uint64_t value) {
    return tal_uint64_dig__ - tal_clz_u64(value);
  }

  uint8_t tal_rotl_u8(const uint8_t value, const int32_t shift) {
    const int32_t diff = shift % tal_uint8_dig__;
    if (shift > 0) {
      return (value << diff) | (value >> (tal_uint8_dig__ - diff));
    } else if (shift < 0) {
      return tal_rotr_u8(value, -shift);
    } else {
      return value;
    }
  }

  uint16_t tal_rotl_u16(const uint16_t value, const int32_t shift) {
    const int32_t diff = shift % tal_uint16_dig__;
    if (shift > 0) {
      return (value << diff) | (value >> (tal_uint16_dig__ - diff));
    } else if (shift < 0) {
      return tal_rotr_u16(value, -shift);
    } else {
      return value;
    }
  }

  uint32_t tal_rotl_u32(const uint32_t value, const int32_t shift) {
    const int32_t diff = shift % tal_uint32_dig__;
    if (shift > 0) {
      return (value << diff) | (value >> (tal_uint32_dig__ - diff));
    } else if (shift < 0) {
      return tal_rotr_u32(value, -shift);
    } else {
      return value;
    }
  }

  uint64_t tal_rotl_u64(const uint64_t value, const int32_t shift) {
    const int32_t diff = shift % tal_uint64_dig__;
    if (shift > 0) {
      return (value << diff) | (value >> (tal_uint64_dig__ - diff));
    } else if (shift < 0) {
      return tal_rotr_u64(value, -shift);
    } else {
      return value;
    }
  }

  uint8_t tal_rotr_u8(const uint8_t value, const int32_t shift) {
    const int32_t diff = shift % tal_uint8_dig__;
    if (diff > 0) {
      return (value >> diff) | (value << (tal_uint8_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotl_u8(value, -shift);
    } else {
      return value;
    }
  }

  uint16_t tal_rotr_u16(const uint16_t value, const int32_t shift) {
    const int32_t diff = shift % tal_uint16_dig__;
    if (diff > 0) {
      return (value >> diff) | (value << (tal_uint16_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotl_u16(value, -shift);
    } else {
      return value;
    }
  }

  uint32_t tal_rotr_u32(const uint32_t value, const int32_t shift) {
    #if defined(TAL_ARCH_ARMV7M)
      uint32_t result = 0;
      asm ("ror %0, %1, %2" : "=rm" (result) : "rm" (value), "rm" (shift));
      return result;
    #else
      const int32_t diff = shift % tal_uint32_dig__;
      if (diff > 0) {
        return (value >> diff) | (value << (tal_uint32_dig__ - diff));
      } else if (diff < 0) {
        return tal_rotl_u32(value, -shift);
      } else {
        return value;
      }
    #endif
  }

  uint64_t tal_rotr_u64(const uint64_t value, const int32_t shift) {
    const int32_t diff = shift % tal_uint64_dig__;
    if (diff > 0) {
      return (value >> diff) | (value << (tal_uint64_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotl_u64(value, -shift);
    } else {
      return value;
    }
  }

  int32_t tal_clz_u8(const uint8_t value) {
    #if defined(TAL_ARCH_ARMV7M)
      const int32_t bit_diff = 32 - 8;
      return tal_clz_u32((uint32_t)value) - bit_diff;
    #else
      int32_t count = 0;
      for (int32_t i = 0; i < 8; ++i) {
        const uint8_t mask = (uint8_t)1 << (8 - 1 - i);
        if ((value & mask) != 0u) { break; }
        ++count;
      }
      return count;
    #endif
  }

  int32_t tal_clz_u16(const uint16_t value) {
    #if defined(TAL_ARCH_ARMV7M)
      const int32_t bit_diff = 32 - 16;
      return tal_clz_u32((uint32_t)value) - bit_diff;
    #else
      int32_t count = 0;
      for (int32_t i = 0; i < 16; ++i) {
        const uint16_t mask = (uint16_t)1 << (16 - 1 - i);
        if ((value & mask) != 0u) { break; }
        ++count;
      }
      return count;
    #endif
  }

  int32_t tal_clz_u32(const uint32_t value) {
    #if defined(TAL_ARCH_ARMV7M)
      int32_t result = 0;
      asm ("clz %0, %1" : "=rm" (result) : "rm" (value));
      return result;
    #else
      int32_t count = 0;
      for (int32_t i = 0; i < 32; ++i) {
        const uint32_t mask = (uint32_t)1 << (32 - 1 - i);
        if ((value & mask) != 0u) { break; }
        ++count;
      }
      return count;
    #endif
  }

  int32_t tal_clz_u64(const uint64_t value) {
    #if defined(TAL_ARCH_ARMV7M)
      const uint32_t high_w = (uint32_t)(value >> (64 / 2));
      const int32_t high_clz = tal_clz_u32(high_w);
      if (high_clz == 32) {
        return 32 + tal_clz_u32((uint32_t)value);
      } else {
        return high_clz;
      }
    #else
      int32_t count = 0;
      for (int32_t i = 0; i < 64; ++i) {
        const uint64_t mask = (uint64_t)1 << (64 - 1 - i);
        if ((value & mask) != 0u) { break; }
        ++count;
      }
      return count;
    #endif
  }

  int32_t tal_clo_u8(const uint8_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 8; ++i) {
      const uint8_t mask = (uint8_t)1 << (8 - 1 - i);
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_clo_u16(const uint16_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 16; ++i) {
      const uint16_t mask = (uint16_t)1 << (16 - 1 - i);
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_clo_u32(const uint32_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 32; ++i) {
      const uint32_t mask = (uint32_t)1 << (32 - 1 - i);
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_clo_u64(const uint64_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 64; ++i) {
      const uint64_t mask = (uint64_t)1 << (64 - 1 - i);
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_ctz_u8(const uint8_t value) {
    int32_t count = 0;
    for (int32_t i= 0; i < 8; ++i) {
      const uint8_t mask = (uint8_t)1 << i;
      if ((value & mask) != 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_ctz_u16(const uint16_t value) {
    int32_t count = 0;
    for (int32_t i= 0; i < 16; ++i) {
      const uint16_t mask = (uint16_t)1 << i;
      if ((value & mask) != 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_ctz_u32(const uint32_t value) {
    int32_t count = 0;
    for (int32_t i= 0; i < 32; ++i) {
      const uint32_t mask = (uint32_t)1 << i;
      if ((value & mask) != 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_ctz_u64(const uint64_t value) {
    int32_t count = 0;
    for (int32_t i= 0; i < 64; ++i) {
      const uint64_t mask = (uint64_t)1 << i;
      if ((value & mask) != 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_cto_u8(const uint8_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 8; ++i) {
      const uint8_t mask = (uint8_t)1 << i;
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_cto_u16(const uint16_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 16; ++i) {
      const uint16_t mask = (uint16_t)1 << i;
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_cto_u32(const uint32_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 32; ++i) {
      const uint32_t mask = (uint32_t)1 << i;
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_cto_u64(const uint64_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 64; ++i) {
      const uint64_t mask = (uint64_t)1 << i;
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_popcount_u8(const uint8_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 8; ++i) {
      const uint8_t mask = (uint8_t)1 << i;
      if ((value & mask) != 0u) { ++count; }
    }
    return count;
  }

  int32_t tal_popcount_u16(const uint16_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 16; ++i) {
      const uint16_t mask = (uint16_t)1 << i;
      if ((value & mask) != 0u) { ++count; }
    }
    return count;
  }

  int32_t tal_popcount_u32(const uint32_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 32; ++i) {
      const uint32_t mask = (uint32_t)1 << i;
      if ((value & mask) != 0u) { ++count; }
    }
    return count;
  }

  int32_t tal_popcount_u64(const uint64_t value) {
    int32_t count = 0;
    for (int32_t i = 0; i < 64; ++i) {
      const uint64_t mask = (uint64_t)1 << i;
      if ((value & mask) != 0u) { ++count; }
    }
    return count;
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif