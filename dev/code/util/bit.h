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
 * @file src/util/bit.h
 * @authors Aaron McBride
 * @brief Bit manipulation and inspection utilities.
 * @note - API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Bit Manipulation Utilities
   ************************************************************************************************/

  /**
   * @defgroup @b bit_rot_x
   * @brief Determines the bitwise rotation of a value.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @param n (int32_t) The number of bits to rotate by (positive = msb, negative = lsb).
   * @returns (unsigned integer denoted by suffix) The result of rotating @p [value] by @p [n] bits.
   * @{
   */
  inline uint8_t bit_rot_8(uint8_t value, int32_t n);
  inline uint16_t bit_rot_16(uint16_t value, int32_t n);
  inline uint32_t bit_rot_32(uint32_t value, int32_t n);
  inline uint64_t bit_rot_64(uint64_t value, int32_t n);
  /** @} */

  /**
   * @defgroup @b bit_rev_x
   * @brief Determines the bitwise reversal of a value.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @param n (int32_t) The size of the blocks of bits to reverse. 
   * @returns (unsigned integer denoted by suffix) @p [value] with the order of every @p [n] bits reversed.
   * @note - If @p [n] <= zero, this function returns @p [value].
   * @note - If @p [n] >= width of the value type, this function returns @p [value].
   * @{
   */
  inline uint8_t bit_rev_8(uint8_t value, int32_t n);
  inline uint16_t bit_rev_16(uint16_t value, int32_t n);
  inline uint32_t bit_rev_32(uint32_t value, int32_t n);
  inline uint64_t bit_rev_64(uint64_t value, int32_t n);
  /** @} */

  /************************************************************************************************
   * Bit Inspection Utilities
   ************************************************************************************************/

  /**
   * @defgroup @b clz_x
   * @brief Determines the number of leading zeros in a value.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @return (int32_t) The number of leading zeros in @p [value].
   * @note - The leading bits of a value are the most significant bits.
   * @{
   */
  inline int32_t clz_8(uint8_t value);
  inline int32_t clz_16(uint16_t value);
  inline int32_t clz_32(uint32_t value);
  inline int32_t clz_64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b ctz_x
   * @brief Determines the number of trailing zeros in a value.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @return (int32_t) The number of trailing zeros in @p [value].
   * @note - The trailing bits of a value are the least significant bits.
   * @{
   */
  inline int32_t ctz_8(uint8_t value);
  inline int32_t ctz_16(uint16_t value);
  inline int32_t ctz_32(uint32_t value);
  inline int32_t ctz_64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b popcnt_x
   * @brief Determines the number of set bits in a value.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @return (int32_t) The number of set bits in @p [value].
   * @{
   */
  inline int32_t popcnt_8(uint8_t value);
  inline int32_t popcnt_16(uint16_t value);
  inline int32_t popcnt_32(uint32_t value);
  inline int32_t popcnt_64(uint64_t value);
  /** @} */

  /************************************************************************************************
   * Uncategorised Bit Utilities
   ************************************************************************************************/

  /**
   * @defgroup @b msk_x
   * @brief Generates a bit mask.
   * @param pos (int32_t) The position of the first set bit (from lsb).
   * @param width (int32_t) The number of consecutive set bits.
   * @returns (unsigned integer denoted by suffix) The specified bit mask.
   * @{
   */
  inline uint8_t msk_8(int32_t pos, int32_t width);
  inline uint16_t msk_16(int32_t pos, int32_t width);
  inline uint32_t msk_32(int32_t pos, int32_t width);
  inline uint64_t msk_64(int32_t pos, int32_t width);
  /** @} */

  /**
   * @brief Performs a bitwise cast of a value.
   * @param dst_t (token) The destination type.
   * @param src_t (token) The source type.
   * @param value (src_t) The value to cast.
   * @returns (dst_t) The bits of @p [value] cast to @p [dst_t].
   * @note - The bits of @p [value] are aligned to the lsb of the result.
   */
  #define BIT_CAST(dst_t, src_t, value)

  /**
   * @brief Gets the size of a value/type in bits.
   * @param x (expression/token) The target value/type.
   * @returns The size of @p [x] in bits.
   */
  #define BIT_SIZE(x)

  /************************************************************************************************
   * Implementation of Bit Manipulation Utilities
   ************************************************************************************************/

  /**** bit_rot_x ****/

  uint8_t bit_rot_8(uint8_t value, int32_t n) {
    static const int32_t bit_size = 8;
    const int32_t r = n % bit_size;
    if (n < 0) { return (value << (bit_size + r)) | (value >> -r); } 
    if (n > 0) { return (value << r) | (value >> (bit_size - r));  }
    return value;
  }  

  uint16_t bit_rot_16(uint16_t value, int32_t n) {
    static const int32_t bit_size = 16;
    const int32_t r = n % bit_size;
    if (n < 0) { return (value << (bit_size + r)) | (value >> -r); } 
    if (n > 0) { return (value << r) | (value >> (bit_size - r));  }
    return value;
  }

  uint32_t bit_rot_32(uint32_t value, int32_t n) {
    static const int32_t bit_size = 32;
    const int32_t r = n % bit_size;
    if (n < 0) { return (value << (bit_size + r)) | (value >> -r); } 
    if (n > 0) { return (value << r) | (value >> (bit_size - r));  }
    return value;
  }

  uint64_t bit_rot_64(uint64_t value, int32_t n) {
    static const int32_t bit_size = 64;
    const int32_t r = n % bit_size;
    if (n < 0) { return (value << (bit_size + r)) | (value >> -r); } 
    if (n > 0) { return (value << r) | (value >> (bit_size - r));  }
    return value;
  }

  /**** bit_rev_x ****/

  uint8_t bit_rev_8(uint8_t value, int32_t n) {
    static const int32_t bit_size = 8;
    if ((n <= 0) || (n >= bit_size)) { return value; }
    uint8_t result = 0;
    for (int32_t i = 0; i < bit_size; i += n) {
      const uint8_t blk_val = (value >> i) & msk_8(0, n);
      result |= blk_val << ((bit_size - n) - i);
    }
    return result;
  }

  uint16_t bit_rev_16(uint16_t value, int32_t n) {
    static const int32_t bit_size = 16;
    if ((n <= 0) || (n >= bit_size)) { return value; }
    uint16_t result = 0;
    for (int32_t i = 0; i < bit_size; i += n) {
      const uint16_t blk_val = (value >> i) & msk_16(0, n);
      result |= blk_val << ((bit_size - n) - i);
    }
    return result;
  }

  uint32_t bit_rev_32(uint32_t value, int32_t n) {
    static const int32_t bit_size = 32;
    if ((n <= 0) || (n >= bit_size)) { return value; }
    uint32_t result = 0;
    for (int32_t i = 0; i < bit_size; i += n) {
      const uint32_t blk_val = (value >> i) & msk_32(0, n);
      result |= blk_val << ((bit_size - n) - i);
    }
    return result;
  }

  uint64_t bit_rev_64(uint64_t value, int32_t n) {
    static const int32_t bit_size = 64;
    if ((n <= 0) || (n >= bit_size)) { return value; }
    uint64_t result = 0;
    for (int32_t i = 0; i < bit_size; i += n) {
      const uint64_t blk_val = (value >> i) & msk_64(0, n);
      result |= blk_val << ((bit_size - n) - i);
    }
    return result;
  }

  /************************************************************************************************
   * Implementation of Bit Inspection Utilities
   ************************************************************************************************/

  /**** clz_x ****/

  int32_t clz_8(uint8_t value) {
    static const int32_t bit_size = 8;
    for (int32_t i = bit_size - 1; i >= 0; i--) {
      if (value & msk_8(i, 1)) { return (bit_size - i) - 1; }
    }
    return bit_size;
  }

  int32_t clz_16(uint16_t value) {
    static const int32_t bit_size = 16;
    for (int32_t i = bit_size - 1; i >= 0; i--) {
      if (value & msk_16(i, 1)) { return (bit_size - i) - 1; }
    }
    return bit_size;
  }

  int32_t clz_32(uint32_t value) {
    static const int32_t bit_size = 32;
    for (int32_t i = bit_size - 1; i >= 0; i--) {
      if (value & msk_32(i, 1)) { return (bit_size - i) - 1; }
    }
    return bit_size;
  }

  int32_t clz_64(uint64_t value) {
    static const int32_t bit_size = 64;
    for (int32_t i = bit_size - 1; i >= 0; i--) {
      if (value & msk_64(i, 1)) { return (bit_size - i) - 1; }
    }
    return bit_size;
  }

  /**** ctz_x ****/

  int32_t ctz_8(uint8_t value) {
    static const int32_t bit_size = 8;
    for (int32_t i = 0; i < bit_size; i++) {
      if (value & msk_8(i, 1)) { return i; }
    }
    return bit_size;
  }

  int32_t ctz_16(uint16_t value) {
    static const int32_t bit_size = 16;
    for (int32_t i = 0; i < bit_size; i++) {
      if (value & msk_16(i, 1)) { return i; }
    }
    return bit_size;
  }

  int32_t ctz_32(uint32_t value) {
    static const int32_t bit_size = 32;
    for (int32_t i = 0; i < bit_size; i++) {
      if (value & msk_32(i, 1)) { return i; }
    }
    return bit_size;
  }

  int32_t ctz_64(uint64_t value) {
    static const int32_t bit_size = 64;
    for (int32_t i = 0; i < bit_size; i++) {
      if (value & msk_64(i, 1)) { return i; }
    }
    return bit_size;
  }

  /**** popcnt_x ****/

  int32_t popcnt_8(uint8_t value) {
    static const int32_t bit_size = 8;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      if (value & msk_8(i, 1)) { result++; }
    }
    return result;
  }

  int32_t popcnt_16(uint16_t value) {
    static const int32_t bit_size = 16;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      if (value & msk_16(i, 1)) { result++; }
    }
    return result;
  }

  int32_t popcnt_32(uint32_t value) {
    static const int32_t bit_size = 32;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      if (value & msk_32(i, 1)) { result++; }
    }
    return result;
  }

  int32_t popcnt_64(uint64_t value) {
    static const int32_t bit_size = 64;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      if (value & msk_64(i, 1)) { result++; }
    }
    return result;
  }

  /************************************************************************************************
   * Implementation of Uncategorised Bit Utilities
   ************************************************************************************************/

  /**** msk_x ****/

  uint8_t msk_8(int32_t pos, int32_t width) {
    return ((UINT8_C(1) << width) - 1U) << pos;
  }

  uint16_t msk_16(int32_t pos, int32_t width) {
    return ((UINT16_C(1) << width) - 1U) << pos;
  }

  uint32_t msk_32(int32_t pos, int32_t width) {
    return ((UINT32_C(1) << width) - 1U) << pos;
  }

  uint64_t msk_64(int32_t pos, int32_t width) {
    return ((UINT64_C(1) << width) - 1U) << pos;
  }

  /**** Other ****/

  #undef BIT_CAST
  #define BIT_CAST(dst_t, src_t, value) ( \
    (union { dst_t dst; src_t src; }){ .src = (value) }.dst \
  )

  #undef BIT_SIZE
  #define BIT_SIZE(x) ( \
    (int32_t)sizeof(x) * CHAR_BIT \
  )

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */