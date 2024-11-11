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
 * @file include/tal/math.h
 * @authors Joshua Beard & Aaron McBride
 * @brief Integer math utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "include/tal/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**
   * @defgroup tal_pow
   * @brief Gets the nth power of an integer.
   * @param value (integer type denoted by suffix) The base value. 
   * @param n (int32_t) The positive exponent value.
   * @returns (integer type denoted by suffix) The result of raising 'base'
   *          to the power of 'n'.
   * @note - If 'n' is negative, this function returns 0.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_pow_i8(const int8_t value, const int32_t n);
  tal_fn_attr_inline inline int16_t tal_pow_i16(const int16_t value, const int32_t n);
  tal_fn_attr_inline inline int32_t tal_pow_i32(const int32_t value, const int32_t n);
  tal_fn_attr_inline inline int64_t tal_pow_i64(const int64_t value, const int32_t n);
  tal_fn_attr_inline inline uint8_t tal_pow_u8(const uint8_t value, const int32_t n);
  tal_fn_attr_inline inline uint16_t tal_pow_u16(const uint16_t value, const int32_t n);
  tal_fn_attr_inline inline uint32_t tal_pow_u32(const uint32_t value, const int32_t n);
  tal_fn_attr_inline inline uint64_t tal_pow_u64(const uint64_t value, const int32_t n);
  /** @} */

  /**
   * @defgroup tal_root
   * @brief Gets the nth root of an integer.
   * @param value (integer type denoted by suffix) The base value.
   * @param n (int32_t) The index of the root (e.g. 2 for square root).
   * @returns (integer type denoted by suffix) The nth root of the given value.
   * @note - If 'value' or 'n' is negative, this function returns 0.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_root_i8(const int8_t value, const int32_t n);
  tal_fn_attr_inline inline int16_t tal_root_i16(const int16_t value, const int32_t n);
  tal_fn_attr_inline inline int32_t tal_root_i32(const int32_t value, const int32_t n);
  tal_fn_attr_inline inline int64_t tal_root_i64(const int64_t value, const int32_t n);
  tal_fn_attr_inline inline uint8_t tal_root_u8(const uint8_t value, const int32_t n);
  tal_fn_attr_inline inline uint16_t tal_root_u16(const uint16_t value, const int32_t n);
  tal_fn_attr_inline inline uint32_t tal_root_u32(const uint32_t value, const int32_t n);
  tal_fn_attr_inline inline uint64_t tal_root_u64(const uint64_t value, const int32_t n);
  /** @} */

  /**
   * @defgroup tal_log
   * @brief Gets the base n logarithm of an integer.
   * @param value (integer type denoted by suffix) The value to take the log of.
   * @param base (int32_t) The base of the logarithm.
   * @returns (integer type denoted by suffix) The base 'base' logarithm of 'value'.
   * @note - If 'value' or 'base' is less then 1, this function returns 0.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_log_i8(const int8_t value, const int32_t base);
  tal_fn_attr_inline inline int16_t tal_log_i16(const int16_t value, const int32_t base);
  tal_fn_attr_inline inline int32_t tal_log_i32(const int32_t value, const int32_t base);
  tal_fn_attr_inline inline int64_t tal_log_i64(const int64_t value, const int32_t base);
  tal_fn_attr_inline inline uint8_t tal_log_u8(const uint8_t value, const int32_t base);
  tal_fn_attr_inline inline uint16_t tal_log_u16(const uint16_t value, const int32_t base);
  tal_fn_attr_inline inline uint32_t tal_log_u32(const uint32_t value, const int32_t base);
  tal_fn_attr_inline inline uint64_t tal_log_u64(const uint64_t value, const int32_t base);
  /** @} */

  /**
   * @defgroup tal_floor
   * @brief Rounds an integer value down to a given multiple.
   * @param value (integer type denoted by suffix) The value to round.
   * @param multiple (integer type denoted by suffix) The multiple to round down to.
   * @returns (integer type denoted by suffix) The given value rounded down to 
   *          the nearest multiple of 'multiple'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_floor_i8(const int8_t value, const int8_t multiple);
  tal_fn_attr_inline inline int16_t tal_floor_i16(const int16_t value, const int16_t multiple);
  tal_fn_attr_inline inline int32_t tal_floor_i32(const int32_t value, const int32_t multiple);
  tal_fn_attr_inline inline int64_t tal_floor_i64(const int64_t value, const int64_t multiple);
  tal_fn_attr_inline inline uint8_t tal_floor_u8(const uint8_t value, const uint8_t multiple);
  tal_fn_attr_inline inline uint16_t tal_floor_u16(const uint16_t value, const uint16_t multiple);
  tal_fn_attr_inline inline uint32_t tal_floor_u32(const uint32_t value, const uint32_t multiple);
  tal_fn_attr_inline inline uint64_t tal_floor_u64(const uint64_t value, const uint64_t multiple);
  /** @} */

  /**
   * @defgroup tal_ceil
   * @brief Rounds an integer value up to a given multiple.
   * @param value (integer type denoted by suffix) The value to round.
   * @param multiple (integer type denoted by suffix) The multiple to round up to.
   * @returns (integer type denoted by suffix) The given value rounded up to
   *          the nearest multiple of 'multiple'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_ceil_i8(const int8_t value, const int8_t multiple);
  tal_fn_attr_inline inline int16_t tal_ceil_i16(const int16_t value, const int16_t multiple);
  tal_fn_attr_inline inline int32_t tal_ceil_i32(const int32_t value, const int32_t multiple);
  tal_fn_attr_inline inline int64_t tal_ceil_i64(const int64_t value, const int64_t multiple);
  tal_fn_attr_inline inline uint8_t tal_ceil_u8(const uint8_t value, const uint8_t multiple);
  tal_fn_attr_inline inline uint16_t tal_ceil_u16(const uint16_t value, const uint16_t multiple);
  tal_fn_attr_inline inline uint32_t tal_ceil_u32(const uint32_t value, const uint32_t multiple);
  tal_fn_attr_inline inline uint64_t tal_ceil_u64(const uint64_t value, const uint64_t multiple);
  /** @} */

  /**
   * @brief Rounds an integer value to a given multiple.
   * @param value (integer type denoted by suffix) The value to round.
   * @param multiple (integer type denoted by suffix) The multiple to round to.
   * @returns (integer type denoted by suffix) The given value rounded to the
   *          nearest multiple of 'multiple'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_round_i8(const int8_t value, const int8_t multiple);
  tal_fn_attr_inline inline int16_t tal_round_i16(const int16_t value, const int16_t multiple);
  tal_fn_attr_inline inline int32_t tal_round_i32(const int32_t value, const int32_t multiple);
  tal_fn_attr_inline inline int64_t tal_round_i64(const int64_t value, const int64_t multiple);
  tal_fn_attr_inline inline uint8_t tal_round_u8(const uint8_t value, const uint8_t multiple);
  tal_fn_attr_inline inline uint16_t tal_round_u16(const uint16_t value, const uint16_t multiple);
  tal_fn_attr_inline inline uint32_t tal_round_u32(const uint32_t value, const uint32_t multiple);
  tal_fn_attr_inline inline uint64_t tal_round_u64(const uint64_t value, const uint64_t multiple);
  /** @} */

  /**
   * @brief Gets the greatest common divisor of two integers.
   * @param value_a (integer type denoted by suffix) The first value.
   * @param value_b (integer type denoted by suffix) The second value.
   * @returns (integer type denoted by suffix) The greatest common divisor of
   *          'value_a' and 'value_b'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_gcd_i8(const int8_t value_a, const int8_t value_b);
  tal_fn_attr_inline inline int16_t tal_gcd_i16(const int16_t value_a, const int16_t value_b);
  tal_fn_attr_inline inline int32_t tal_gcd_i32(const int32_t value_a, const int32_t value_b);
  tal_fn_attr_inline inline int64_t tal_gcd_i64(const int64_t value_a, const int64_t value_b);
  tal_fn_attr_inline inline uint8_t tal_gcd_u8(const uint8_t value_a, const uint8_t value_b);
  tal_fn_attr_inline inline uint16_t tal_gcd_u16(const uint16_t value_a, const uint16_t value_b);
  tal_fn_attr_inline inline uint32_t tal_gcd_u32(const uint32_t value_a, const uint32_t value_b);
  tal_fn_attr_inline inline uint64_t tal_gcd_u64(const uint64_t value_a, const uint64_t value_b);
  /** @} */

  /**
   * @brief Gets the least common multiple of two integers.
   * @param value_a (integer type denoted by suffix) The first value.
   * @param value_b (integer type denoted by suffix) The second value.
   * @returns (integer type denoted by suffix) The least common multiple of
   *          'value_a' and 'value_b'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_lcm_i8(const int8_t value_a, const int8_t value_b);
  tal_fn_attr_inline inline int16_t tal_lcm_i16(const int16_t value_a, const int16_t value_b);
  tal_fn_attr_inline inline int32_t tal_lcm_i32(const int32_t value_a, const int32_t value_b);
  tal_fn_attr_inline inline int64_t tal_lcm_i64(const int64_t value_a, const int64_t value_b);
  tal_fn_attr_inline inline uint8_t tal_lcm_u8(const uint8_t value_a, const uint8_t value_b);
  tal_fn_attr_inline inline uint16_t tal_lcm_u16(const uint16_t value_a, const uint16_t value_b);
  tal_fn_attr_inline inline uint32_t tal_lcm_u32(const uint32_t value_a, const uint32_t value_b); 
  tal_fn_attr_inline inline uint64_t tal_lcm_u64(const uint64_t value_a, const uint64_t value_b);
  /** @} */

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  int8_t tal_pow_i8(const int8_t value, const int32_t n) {
    if (n < 0) { return 0; }
    if (n == 0) { return 1; }
    int8_t result = value;
    for (int32_t i = 0; i < (n - 1); ++i) {
      result *= value;
    }
    return result;
  }

  int16_t tal_pow_i16(const int16_t value, const int32_t n) {
    if (n < 0) { return 0; }
    if (n == 0) { return 1; }
    int16_t result = value;
    for (int32_t i = 0; i < (n - 1); ++i) {
      result *= value;
    }
    return result;
  }

  int32_t tal_pow_i32(const int32_t value, const int32_t n) {
    if (n < 0) { return 0; }
    if (n == 0) { return 1; }
    int32_t result = value;
    for (int32_t i = 0; i < (n - 1); ++i) {
      result *= value;
    }
    return result;
  }

  int64_t tal_pow_i64(const int64_t value, const int32_t n) {
    if (n < 0) { return 0; }
    if (n == 0) { return 1; }
    int64_t result = value;
    for (int32_t i = 0; i < (n - 1); ++i) {
      result *= value;
    }
    return result;
  }

  uint8_t tal_pow_u8(const uint8_t value, const int32_t n) {
    if (n < 0) { return 0u; }
    if (n == 0) { return 1u; }
    uint8_t result = value;
    for (int32_t i = 0; i < (n - 1); ++i) {
      result *= value;
    }
    return result;
  }

  uint16_t tal_pow_u16(const uint16_t value, const int32_t n) {
    if (n < 0) { return 0u; }
    if (n == 0) { return 1u; }
    uint16_t result = value;
    for (int32_t i = 0; i < (n - 1); ++i) {
      result *= value;
    }
    return result;
  }

  uint32_t tal_pow_u32(const uint32_t value, const int32_t n) {
    if (n < 0) { return 0u; }
    if (n == 0) { return 1u; }
    uint32_t result = value;
    for (int32_t i = 0; i < (n - 1); ++i) {
      result *= value;
    }
    return result;
  }

  uint64_t tal_pow_u64(const uint64_t value, const int32_t n) {
    if (n < 0) { return 0u; }
    if (n == 0) { return 1u; }
    uint64_t result = value;
    for (int32_t i = 0; i < (n - 1); ++i) {
      result *= value;
    }
    return result;
  }

  int8_t tal_root_i8(const int8_t value, const int32_t n) {
    if (value <= 0 || n < 0) { return 0; }
    if (n == 0) { return 1; }
    int8_t c_root = 1;
    while (true) {
      int8_t c_pow = c_root;
      for (int32_t i = 0; i < (n - 1); ++i) {
        if (c_pow > (value / c_root)) { return c_root - 1; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  int16_t tal_root_i16(const int16_t value, const int32_t n) {
    if (value <= 0 || n < 0) { return 0; }
    if (n == 0) { return 1; }
    int16_t c_root = 1;
    while (true) {
      int16_t c_pow = c_root;
      for (int32_t i = 0; i < (n - 1); ++i) {
        if (c_pow > (value / c_root)) { return c_root - 1; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }
  
  int32_t tal_root_i32(const int32_t value, const int32_t n) {
    if (value <= 0 || n < 0) { return 0; }
    if (n == 0) { return 1; }
    int32_t c_root = 1;
    while (true) {
      int32_t c_pow = c_root;
      for (int32_t i = 0; i < (n - 1); ++i) {
        if (c_pow > (value / c_root)) { return c_root - 1; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  int64_t tal_root_i64(const int64_t value, const int32_t n) {
    if (value <= 0 || n < 0) { return 0; }
    if (n == 0) { return 1; }
    int64_t c_root = 1;
    while (true) {
      int64_t c_pow = c_root;
      for (int32_t i = 0; i < (n - 1); ++i) {
        if (c_pow > (value / c_root)) { return c_root - 1; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  uint8_t tal_root_u8(const uint8_t value, const int32_t n) {
    if (n < 0) { return 0u; }
    if (n == 0) { return 1u; }
    uint8_t c_root = 1u;
    while (true) {
      uint8_t c_pow = c_root;
      for (int32_t i = 0; i < (n - 1); ++i) {
        if (c_pow > (value / c_root)) { return c_root - 1u; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  uint16_t tal_root_u16(const uint16_t value, const int32_t n) {
    if (n < 0) { return 0u; }
    if (n == 0) { return 1u; }
    uint16_t c_root = 1u;
    while (true) {
      uint16_t c_pow = c_root;
      for (int32_t i = 0; i < (n - 1); ++i) {
        if (c_pow > (value / c_root)) { return c_root - 1u; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  uint32_t tal_root_u32(const uint32_t value, const int32_t n) {
    if (n < 0) { return 0u; }
    if (n == 0) { return 1u; }
    uint32_t c_root = 1u;
    while (true) {
      uint32_t c_pow = c_root;
      for (int32_t i = 0; i < (n - 1); ++i) {
        if (c_pow > (value / c_root)) { return c_root - 1u; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  uint64_t tal_root_u64(const uint64_t value, const int32_t n) {
    if (n < 0) { return 0u; }
    if (n == 0) { return 1u; }
    uint64_t c_root = 1u;
    while (true) {
      uint64_t c_pow = c_root;
      for (int32_t i = 0; i < (n - 1); ++i) {
        if (c_pow > (value / c_root)) { return c_root - 1u; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  int8_t tal_log_i8(const int8_t value, const int32_t base) {
    if (value <= 1 || base <= 1) { return 0; }
    int8_t pow = 1;
    int8_t c_value = base;
    while (c_value < (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  int16_t tal_log_i16(const int16_t value, const int32_t base) {
    if (value <= 1 || base <= 1) { return 0; }
    int16_t pow = 1;
    int16_t c_value = base;
    while (c_value < (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  int32_t tal_log_i32(const int32_t value, const int32_t base) {
    if (value <= 1 || base <= 1) { return 0; }
    int32_t pow = 1;
    int32_t c_value = base;
    while (c_value < (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  int64_t tal_log_i64(const int64_t value, const int32_t base) {
    if (value <= 1 || base <= 1) { return 0; }
    int64_t pow = 1;
    int64_t c_value = base;
    while (c_value < (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  uint8_t tal_log_u8(const uint8_t value, const int32_t base) {
    if (value <= 1u || base <= 1) { return 0u; }
    uint8_t pow = 1;
    uint8_t c_value = base;
    while (c_value < (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  uint16_t tal_log_u16(const uint16_t value, const int32_t base) {
    if (value <= 1u || base <= 1) { return 0u; }
    uint16_t pow = 1;
    uint16_t c_value = base;
    while (c_value < (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  uint32_t tal_log_u32(const uint32_t value, const int32_t base) {
    if (value <= 1u || base <= 1) { return 0u; }
    uint32_t pow = 1;
    uint32_t c_value = base;
    while (c_value < (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  uint64_t tal_log_u64(const uint64_t value, const int32_t base) {
    if (value <= 1u || base <= 1) { return 0u; }
    uint64_t pow = 1;
    uint64_t c_value = base;
    while (c_value < (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  int8_t tal_floor_i8(const int8_t value, const int8_t multiple) {
    return value - (value % multiple);
  }

  int16_t tal_floor_i16(const int16_t value, const int16_t multiple) {
    return value - (value % multiple);
  }

  int32_t tal_floor_i32(const int32_t value, const int32_t multiple) {
    return value - (value % multiple);
  }

  int64_t tal_floor_i64(const int64_t value, const int64_t multiple) {
    return value - (value % multiple);
  }
  
  uint8_t tal_floor_u8(const uint8_t value, const uint8_t multiple) {
    return value - (value % multiple);
  }

  uint16_t tal_floor_u16(const uint16_t value, const uint16_t multiple) {
    return value - (value % multiple);
  }
  
  uint32_t tal_floor_u32(const uint32_t value, const uint32_t multiple) {
    return value - (value % multiple);
  }

  uint64_t tal_floor_u64(const uint64_t value, const uint64_t multiple) {
    return value - (value % multiple);
  }
  
  int8_t tal_ceil_i8(const int8_t value, const int8_t multiple) {
    return tal_floor_i8(value, multiple) + multiple;
  }

  int16_t tal_ceil_i16(const int16_t value, const int16_t multiple) {
    return tal_floor_i16(value, multiple) + multiple;
  }

  int32_t tal_ceil_i32(const int32_t value, const int32_t multiple) {
    return tal_floor_i32(value, multiple) + multiple;
  }

  int64_t tal_ceil_i64(const int64_t value, const int64_t multiple) {
    return tal_floor_i64(value, multiple) + multiple;
  }

  uint8_t tal_ceil_u8(const uint8_t value, const uint8_t multiple) {
    return tal_floor_u8(value, multiple) + multiple;
  }

  uint16_t tal_ceil_u16(const uint16_t value, const uint16_t multiple) {
    return tal_floor_u16(value, multiple) + multiple;
  }

  uint32_t tal_ceil_u32(const uint32_t value, const uint32_t multiple) {
    return tal_floor_u32(value, multiple) + multiple;
  }

  uint64_t tal_ceil_u64(const uint64_t value, const uint64_t multiple) {
    return tal_floor_u64(value, multiple) + multiple;
  }

  int8_t tal_round_i8(const int8_t value, const int8_t multiple) {
    const int8_t diff = value % multiple;
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  int16_t tal_round_i16(const int16_t value, const int16_t multiple) {
    const int16_t diff = value % multiple;
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  int32_t tal_round_i32(const int32_t value, const int32_t multiple) {
    const int32_t diff = value % multiple;
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  int64_t tal_round_i64(const int64_t value, const int64_t multiple) {
    const int64_t diff = value % multiple;
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  uint8_t tal_round_u8(const uint8_t value, const uint8_t multiple) {
    const uint8_t diff = value % multiple;
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  uint16_t tal_round_u16(const uint16_t value, const uint16_t multiple) {
    const uint16_t diff = value % multiple;
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  uint32_t tal_round_u32(const uint32_t value, const uint32_t multiple) {
    const uint32_t diff = value % multiple;
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  uint64_t tal_round_u64(const uint64_t value, const uint64_t multiple) {
    const uint64_t diff = value % multiple;
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  int8_t tal_gcd_i8(const int8_t value_a, const int8_t value_b) {
    int8_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  int16_t tal_gcd_i16(const int16_t value_a, const int16_t value_b) {
    int16_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  int32_t tal_gcd_i32(const int32_t value_a, const int32_t value_b) {
    int32_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  int64_t tal_gcd_i64(const int64_t value_a, const int64_t value_b) {
    int64_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  uint8_t tal_gcd_u8(const uint8_t value_a, const uint8_t value_b) {
    uint8_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  uint16_t tal_gcd_u16(const uint16_t value_a, const uint16_t value_b) {
    uint16_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  uint32_t tal_gcd_u32(const uint32_t value_a, const uint32_t value_b) {
    uint32_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  uint64_t tal_gcd_u64(const uint64_t value_a, const uint64_t value_b) {
    uint64_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  int8_t tal_lcm_i8(const int8_t value_a, const int8_t value_b) {
    return (value_a * value_b) / tal_gcd_i8(value_a, value_b);
  }

  int16_t tal_lcm_i16(const int16_t value_a, const int16_t value_b) {
    return (value_a * value_b) / tal_gcd_i16(value_a, value_b);
  }

  int32_t tal_lcm_i32(const int32_t value_a, const int32_t value_b) {
    return (value_a * value_b) / tal_gcd_i32(value_a, value_b);
  }

  int64_t tal_lcm_i64(const int64_t value_a, const int64_t value_b) {
    return (value_a * value_b) / tal_gcd_i64(value_a, value_b);
  }

  uint8_t tal_lcm_u8(const uint8_t value_a, const uint8_t value_b) {
    return (value_a * value_b) / tal_gcd_u8(value_a, value_b);
  }

  uint16_t tal_lcm_u16(const uint16_t value_a, const uint16_t value_b) {
    return (value_a * value_b) / tal_gcd_u16(value_a, value_b);
  }

  uint32_t tal_lcm_u32(const uint32_t value_a, const uint32_t value_b) {
    return (value_a * value_b) / tal_gcd_u32(value_a, value_b);
  }

  uint64_t tal_lcm_u64(const uint64_t value_a, const uint64_t value_b) {
    return (value_a * value_b) / tal_gcd_u64(value_a, value_b);
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif