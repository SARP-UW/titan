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
 * @note API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "src/common/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Bit Querying Utilities
   **************************************************************************************************/

  /**
   * @brief Evaluates to the number of bits in @p 'type'.
   * @param type The type to get the bit size of.
   */
  #define tal_bit_size(type) (sizeof(type) * CHAR_BIT)

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
   * @section Bit Manipulation Utilities
   **************************************************************************************************/

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
   * @defgroup tal_rotl
   * @brief Performs a circular left shift on an integer value.
   * @param value (unsigned integer denoted by suffix) The value to rotate.
   * @param shift (int32_t) The number of bits to rotate by.
   * @param err (bool*) Error flag. Accessed and set true if shift is negative. 
   * @returns (unsigned integer denoted by suffix) The result of circularly 
   *          rotating the given value to the left by 'shift' bits.
   * @note - This function performs a "circular shift", meaining that bits
   *         shifted beyond the end of the integer's range wrap around to
   *         the beginning.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_rotl_u8(
      const uint8_t value, const int32_t shift, bool* err);
  tal_fn_attr_inline inline uint16_t tal_rotl_u16(
      const uint16_t value, const int32_t shift, bool* err);
  tal_fn_attr_inline inline uint32_t tal_rotl_u32(
      const uint32_t value, const int32_t shift, bool* err);
  tal_fn_attr_inline inline uint64_t tal_rotl_u64(
      const uint64_t value, const int32_t shift, bool* err);
  /** @} */

  /**
   * @defgroup tal_rotr
   * @brief Performs a circular right shift on an integer value.
   * @param value (unsigned integer denoted by suffix) The value to rotate.
   * @param shift (int32_t) The number of bits to rotate by.
   * @param err (bool*) Error flag. Accessed and set true if shift is negative. 
   * @returns (unsigned integer denoted by suffix) The result of circularly 
   *          rotating the given value to the right by 'shift' bits.
   * @note - This function performs a "circular shift", meaining that bits
   *         shifted beyond the end of the integer's range wrap around to
   *         the beginning.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_rotr_u8(
      const uint8_t value, const int32_t shift, bool* err);
  tal_fn_attr_inline inline uint16_t tal_rotr_u16(
      const uint16_t value, const int32_t shift, bool* err);
  tal_fn_attr_inline inline uint32_t tal_rotr_u32(
      const uint32_t value, const int32_t shift, bool* err);
  tal_fn_attr_inline inline uint64_t tal_rotr_u64(
      const uint64_t value, const int32_t shift, bool* err);
  /** @} */

  /**************************************************************************************************
   * @section Bitmask Utilities
   **************************************************************************************************/

  /**
   * @defgroup tal_mask
   * @brief Creates a mask of contiguous set bits at specific location.
   * @param pos (int32_t) The number of bits between the LSB and the first set bit.
   * @param len (int32_t) The number of contiguous set bits.
   * @param err (bool*) Error flag. Accessed and set true if 'pos' is less than 
   *            0 or 'len' is less than or equal to 0. Accessed and set true if
   *            pos + len is greater than the number of bits in the suffix type.
   * @returns (unsigned integer denoted by suffix) A mask with 'len' contiguous
   *          set bits starting 'pos' bits from the LSB.
   */
  tal_fn_attr_inline inline uint8_t tal_mask_u8(const int32_t pos, 
      const int32_t len, bool* err);
  tal_fn_attr_inline inline uint16_t tal_mask_u16(const int32_t pos, 
      const int32_t len, bool* err);
  tal_fn_attr_inline inline uint32_t tal_mask_u32(const int32_t pos, 
      const int32_t len, bool* err);
  tal_fn_attr_inline inline uint64_t tal_mask_u64(const int32_t pos, 
      const int32_t len, bool* err);

  /**
   * @brief Writes a value to a specific range of bits in another value.
   * @param value (unsigned integer denoted by suffix) The value to write to.
   * @param dest (unsigned integer denoted by suffix) The value to write to.
   * @param pos (int32_t) The position of the range to write to (bits from lsb).
   * @param len (int32_t) The length of the range to write to (bits).
   * @param err (bool*) Error flag. Accessed and set true if 'pos' or 'len' is 
   *            less than 0, or if pos + len is greater than the bit-width of
   *            the suffix type. If set, this function returns 0 and is
   *            guaranteed to have no other side effects.
   * @returns (unsigned integer denoted by suffix) The result of writing 'value'
   *          to the range of bits in 'dest' specified by 'pos' and 'len'.
   */
  tal_fn_attr_inline inline uint8_t tal_write_bits_u8(const uint8_t value, 
      const uint8_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint16_t tal_write_bits_u16(const uint16_t value, 
      const uint16_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint32_t tal_write_bits_u32(const uint32_t value, 
      const uint32_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint64_t tal_write_bits_u64(const uint64_t value, 
      const uint64_t dest, const int32_t pos, const int32_t len, bool* err);

  /**
   * @brief Reads a value from a specific range of bits in another value.
   * @param dest (unsigned integer denoted by suffix) The value to read from.
   * @param pos (int32_t) The position of the range to read from (bits from lsb).
   * @param len (int32_t) The length of the range to read from (bits).
   * @param err (bool*) Error flag. Accessed and set true if 'pos' or 'len' is
   *            less than 0, or if pos + len is greater than the bit-width of
   *            the suffix type. If set, this function returns 0 and is
   *            guaranteed to have no other side effects.
   * @returns (unsigned integer denoted by suffix) The value of the range of bits
   *          in 'dest' specified by 'pos' and 'len'.
   */
  tal_fn_attr_inline inline uint8_t tal_read_bits_u8(const uint8_t dest,
      const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint16_t tal_read_bits_u16(const uint16_t dest,
      const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint32_t tal_read_bits_u32(const uint32_t dest,
      const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint64_t tal_read_bits_u64(const uint64_t dest,
      const int32_t pos, const int32_t len, bool* err);

  /**
   * @brief Sets all bits in a specific range to either 0 or 1.
   * @param value (bool) If true, all bits in the given range are set to 1.
   *              If false, all bits in the given range are set to 0.
   * @param dest (unsigned integer denoted by suffix) The value to modify.
   * @param pos (int32_t) The position of the range to modify (bits from lsb).
   * @param len (int32_t) The length of the range to modify (bits).
   * @param err (bool*) Error flag. Accessed and set true if 'pos' or 'len' is
   *            less than 0, or if pos + len is greater than the bit-width of
   *            the suffix type. If set, this function returns 'value',
   *            unaltered, and is guaranteed to have no other side effects.
   * @returns (unsigned integer denoted by suffix) The result of setting all
   *          bits in the range specified by 'pos' and 'len' to either 1 if
   *          'value' is true, or 0 otherwise.
   */
  tal_fn_attr_inline inline uint8_t tal_set_bits_u8(const bool value,
      const uint8_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint16_t tal_set_bits_u16(const bool value,
      const uint16_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint32_t tal_set_bits_u32(const bool value,
      const uint32_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline uint64_t tal_set_bits_u64(const bool value,
      const uint64_t dest, const int32_t pos, const int32_t len, bool* err);

  /**
   * @brief Determines if all bits in a specific range are set to either 0 or 1.
   * @param value (bool) If true, all bits in the given range are compared to 1.
   *              If false, all bits in the given range are compared to 0.
   * @param dest (unsigned integer denoted by suffix) The value to query.
   * @param pos (int32_t) The position of the range to query (bits from lsb).
   * @param len (int32_t) The length of the range to query (bits).
   * @param err (bool*) Error flag. Accessed and set true if 'pos' or 'len' is
   *            less than 0, or if pos + len is greater than the bit-width of
   *            the suffix type. If set, this function returns false and is
   *            guaranteed to have no other side effects.
   * @returns (bool) True if all bits in the range specified by 'pos' and 'len'
   *          are equal to 'value' (true = 1, false = 0), or false otherwise.
   */
  tal_fn_attr_inline inline bool tal_get_bits_u8(const bool value,
      const uint8_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline bool tal_get_bits_u16(const bool value,
      const uint16_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline bool tal_get_bits_u32(const bool value,
      const uint32_t dest, const int32_t pos, const int32_t len, bool* err);
  tal_fn_attr_inline inline bool tal_get_bits_u64(const bool value,
      const uint64_t dest, const int32_t pos, const int32_t len, bool* err);

  /**************************************************************************************************
   * @internal Implementation Resources
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

  /**************************************************************************************************
   * @internal Implementation for Bit Querying Utilities
   **************************************************************************************************/

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

  /**************************************************************************************************
   * @internal Implementation for Bit Manipulation Utilities
   **************************************************************************************************/

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

  uint8_t tal_bit_ceil_u8(const uint8_t value) {
    if (value <= 1u) { return 1; }
    return (uint8_t)1 << tal_bit_width_u8(value - 1u);
  }

  uint16_t tal_bit_ceil_u16(const uint16_t value) {
    if (value <= 1u) { return 1; }
    return (uint16_t)1 << tal_bit_width_u16(value - 1u);
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

  uint8_t tal_rotl_u8(const uint8_t value, const int32_t shift, bool* err) {
    if (shift < 0) {
      *err = true; 
      return 0; 
    }
    const int32_t diff = shift % tal_uint8_dig__;
    if (diff > 0) {
      return (value << diff) | (value >> (tal_uint8_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotr_u8(value, -shift, err);
    } else {
      return value;
    }
  }

  uint16_t tal_rotl_u16(const uint16_t value, const int32_t shift, bool* err) {
    if (shift < 0) { 
      *err = true; 
      return 0; 
    }
    const int32_t diff = shift % tal_uint16_dig__;
    if (diff > 0) {
      return (value << diff) | (value >> (tal_uint16_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotr_u16(value, -shift, err);
    } else {
      return value;
    }
  }

  uint32_t tal_rotl_u32(const uint32_t value, const int32_t shift, bool* err) {
    if (shift < 0) { 
      *err = true; 
      return 0; 
    }
    const int32_t diff = shift % tal_uint32_dig__;
    if (diff > 0) {
      return (value << diff) | (value >> (tal_uint32_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotr_u32(value, -shift, err);
    } else {
      return value;
    }
  }

  uint64_t tal_rotl_u64(const uint64_t value, const int32_t shift, bool* err) {
    if (shift < 0) { 
      *err = true; 
      return 0; 
    }
    const int32_t diff = shift % tal_uint64_dig__;
    if (diff > 0) {
      return (value << diff) | (value >> (tal_uint64_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotr_u64(value, -shift, err);
    } else {
      return value;
    }
  }

  uint8_t tal_rotr_u8(const uint8_t value, const int32_t shift, bool* err) {
    if (shift < 0u) { 
      *err = true; 
      return 0u;
    }
    const int32_t diff = shift % tal_uint8_dig__;
    if (diff > 0) {
      return (value >> diff) | (value << (tal_uint8_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotl_u8(value, -shift, err);
    } else {
      return value;
    }
  }

  uint16_t tal_rotr_u16(const uint16_t value, const int32_t shift, bool* err) {
    if (shift < 0u) { 
      *err = true; 
      return 0u;
    }
    const int32_t diff = shift % tal_uint16_dig__;
    if (diff > 0) {
      return (value >> diff) | (value << (tal_uint16_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotl_u16(value, -shift, err);
    } else {
      return value;
    }
  }

  uint32_t tal_rotr_u32(const uint32_t value, const int32_t shift, bool* err) {
    if (shift < 0u) { 
      *err = true; 
      return 0u;
    }
    #if defined(TAL_ARCH_ARMV7M)
      uint32_t result = 0;
      asm ("ror %0, %1, %2" : "=rm" (result) : "rm" (value), "rm" (shift));
      return result;
    #else
      const int32_t diff = shift % tal_uint32_dig__;
      if (diff > 0) {
        return (value >> diff) | (value << (tal_uint32_dig__ - diff));
      } else if (diff < 0) {
        return tal_rotl_u32(value, -shift, err);
      } else {
        return value;
      }
    #endif
  }

  uint64_t tal_rotr_u64(const uint64_t value, const int32_t shift, bool* err) {
    if (shift < 0u) { 
      *err = true; 
      return 0u;
    }
    const int32_t diff = shift % tal_uint64_dig__;
    if (diff > 0) {
      return (value >> diff) | (value << (tal_uint64_dig__ - diff));
    } else if (diff < 0) {
      return tal_rotl_u64(value, -shift, err);
    } else {
      return value;
    }
  }

  /**************************************************************************************************
   * @internal Implementation for Bitmask Utilities
   **************************************************************************************************/

  // Determines if a pos/len pair is within the given bit width.
  static bool valid_pos(const int32_t pos, const int32_t len, 
      const int32_t bit_width) {
    return pos >= 0 && len >= 0 && (pos + len) <= bit_width;
  }

  uint8_t tal_mask_u8(const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len, tal_bit_size(uint8_t))) {
      *err = true;
      return 0;
    }
    return (((uint8_t)1 << len) - (uint8_t)1) << pos;
  }

  uint16_t tal_mask_u16(const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len, tal_bit_size(uint16_t))) {
      *err = true;
      return 0;
    }
    return (((uint16_t)1 << len) - (uint16_t)1) << pos;
  }

  uint32_t tal_mask_u32(const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len, tal_bit_size(uint32_t))) {
      *err = true;
      return 0;
    }
    return (((uint32_t)1 << len) - (uint32_t)1) << pos;
  }

  uint64_t tal_mask_u64(const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len, tal_bit_size(uint64_t))) {
      *err = true;
      return 0;
    }
    return (((uint64_t)1 << len) - (uint64_t)1) << pos;
  }

  uint8_t tal_write_bits_u8(const uint8_t value, const uint8_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len, tal_bit_size(uint8_t)) || 
        tal_bit_width_u8(value) > len) {
      *err = true;
      return value;
    } else {
      const uint8_t mask = tal_mask_u8(pos, len, NULL);
      return (dest & ~mask) | (value << pos);
    }
  }

  uint16_t tal_write_bits_u16(const uint16_t value, const uint16_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len, tal_bit_size(uint16_t)) ||
        tal_bit_width_u16(value) > len) {
      *err = true;
      return value;
    } else {
      const uint16_t mask = tal_mask_u16(pos, len, NULL);
      return (dest & ~mask) | (value << pos);
    }
  }

  uint32_t tal_write_bits_u32(const uint32_t value, const uint32_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len, tal_bit_size(uint32_t)) ||
        tal_bit_width_u32(value) > len) {
      *err = true;
      return value;
    } else {
      const uint32_t mask = tal_mask_u32(pos, len, NULL);
      return (dest & ~mask) | (value << pos);
    }
  }

  uint64_t tal_write_bits_u64(const uint64_t value, const uint64_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len, tal_bit_size(uint64_t)) ||
        tal_bit_width_u64(value) > len) {
      *err = true;
      return value;
    } else {
      const uint64_t mask = tal_mask_u64(pos, len, NULL);
      return (dest & ~mask) | (value << pos);
    }
  }

  uint8_t tal_read_bits_u8(const uint8_t dest, const int32_t pos, 
      const int32_t len, bool* err) {
    if (!valid_pos(pos, len, bit_width(uint8_t))) {
      *err = true;
      return 0;
    } else {
      const uint8_t mask = tal_mask_u8(pos, len, NULL);
      return (dest & mask) >> pos;
    }
  }

  uint16_t tal_read_bits_u16(const uint16_t dest, const int32_t pos, 
      const int32_t len, bool* err) {
    if (!valid_pos(pos, len, bit_width(uint16_t))) {
      *err = true;
      return 0;
    } else {
      const uint16_t mask = tal_mask_u16(pos, len, NULL);
      return (dest & mask) >> pos;
    }
  }

  uint32_t tal_read_bits_u32(const uint32_t dest, const int32_t pos, 
      const int32_t len, bool* err) {
    if (!valid_pos(pos, len, bit_width(uint32_t))) {
      *err = true;
      return 0;
    } else {
      const uint32_t mask = tal_mask_u32(pos, len, NULL);
      return (dest & mask) >> pos;
    }
  }

  uint64_t tal_read_bits_u64(const uint64_t dest, const int32_t pos, 
      const int32_t len, bool* err) {
    if (!valid_pos(pos, len, bit_width(uint64_t))) {
      *err = true;
      return 0;
    } else {
      const uint64_t mask = tal_mask_u64(pos, len, NULL);
      return (dest & mask) >> pos;
    }
  }

  uint8_t tal_set_bits_u8(const bool value, const uint8_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len)) {
      *err = true;
      return dest;
    } else {
      const uint8_t mask = tal_mask_u8(pos, len, NULL);
      if (value) {
        return dest | mask;
      } else {
        return dest & ~mask;
      }
    }
  }

  uint16_t tal_set_bits_u16(const bool value, const uint16_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len)) {
      *err = true;
      return dest;
    } else {
      const uint16_t mask = tal_mask_u16(pos, len, NULL);
      if (value) {
        return dest | mask;
      } else {
        return dest & ~mask;
      }
    }
  }

  uint32_t tal_set_bits_u32(const bool value, const uint32_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len)) {
      *err = true;
      return dest;
    } else {
      const uint32_t mask = tal_mask_u32(pos, len, NULL);
      if (value) {
        return dest | mask;
      } else {
        return dest & ~mask;
      }
    }
  }

  uint64_t tal_set_bits_u64(const bool value, const uint64_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len)) {
      *err = true;
      return dest;
    } else {
      const uint64_t mask = tal_mask_u64(pos, len, NULL);
      if (value) {
        return dest | mask;
      } else {
        return dest & ~mask;
      }
    }
  }

  bool tal_get_bits_u8(const bool value, const uint8_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len)) {
      *err = true;
      return false;
    } else {
      const uint8_t mask = tal_mask_u8(pos, len, NULL);
      if (value) {
        return (dest & mask) == mask;
      } else {
        return (dest & mask) == 0u;
      }
    }
  }

  bool tal_get_bits_u16(const bool value, const uint16_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len)) {
      *err = true;
      return false;
    } else {
      const uint16_t mask = tal_mask_u16(pos, len, NULL);
      if (value) {
        return (dest & mask) == mask;
      } else {
        return (dest & mask) == 0u;
      }
    }
  }

  bool tal_get_bits_u32(const bool value, const uint32_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len)) {
      *err = true;
      return false;
    } else {
      const uint32_t mask = tal_mask_u32(pos, len, NULL);
      if (value) {
        return (dest & mask) == mask;
      } else {
        return (dest & mask) == 0u;
      }
    }
  }

  bool tal_get_bits_u64(const bool value, const uint64_t dest, 
      const int32_t pos, const int32_t len, bool* err) {
    if (!valid_pos(pos, len)) {
      *err = true;
      return false;
    } else {
      const uint64_t mask = tal_mask_u64(pos, len, NULL);
      if (value) {
        return (dest & mask) == mask;
      } else {
        return (dest & mask) == 0u;
      }
    }
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif