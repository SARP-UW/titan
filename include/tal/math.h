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
 * @brief Math utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "src/common/attributes.h"
#include "include/tal/numeric.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Integer Exponentiation Utilities
   **************************************************************************************************/

  /**
   * @defgroup integer tal_pow
   * @brief Gets the nth power of the given base (integer only).
   * @param base (integer type denoted by suffix) The base's value.
   * @param exp (int32_t) The exponent value.
   * @param err (bool*) The error flag. Set if the result of the operation
   *            would overflow. If set, this function returns the saturated
   *            result of the operation and is guaranteed to have no other
   *            side effects.
   * @returns (integer type denoted by suffix) The saturated result of raising 
   *          'base' to the power of 'exp'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_pow_i8(const int8_t base, 
      const int32_t exp, bool* err);
  tal_fn_attr_inline inline int16_t tal_pow_i16(const int16_t base, 
      const int32_t exp, bool* err);
  tal_fn_attr_inline inline int32_t tal_pow_i32(const int32_t base, 
      const int32_t exp, bool* err);
  tal_fn_attr_inline inline int64_t tal_pow_i64(const int64_t base, 
      const int32_t exp, bool* err);

  tal_fn_attr_inline inline uint8_t tal_pow_u8(const uint8_t base, 
      const int32_t exp, bool* err);
  tal_fn_attr_inline inline uint16_t tal_pow_u16(const uint16_t base, 
      const int32_t exp, bool* err);
  tal_fn_attr_inline inline uint32_t tal_pow_u32(const uint32_t base, 
      const int32_t exp, bool* err);
  tal_fn_attr_inline inline uint64_t tal_pow_u64(const uint64_t base, 
      const int32_t exp, bool* err);
  /** @} */

  /**
   * @defgroup integer tal_root
   * @brief Gets the nth root of the given radicand (integer only).
   * @param radicand (integer type denoted by suffix) The radicand's value.
   * @param index (int32_t) The index of the root -> (e.g. sqrt -> index = 2).
   * @param err (bool*) The error flag. Set if the result of the operation
   *            is undefined or complex (refer to provided link). If set, 
   *            this function returns 0 and is guaranteed to have no other 
   *            side effects.
   * @returns (integer type denoted by suffix) The 'index' root of 'radicand'.
   * @see https://en.wikipedia.org/wiki/Nth_root
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_root_i8(const int8_t radicand, 
      const int32_t index, bool* err);
  tal_fn_attr_inline inline int16_t tal_root_i16(const int16_t radicand, 
      const int32_t index, bool* err);
  tal_fn_attr_inline inline int32_t tal_root_i32(const int32_t radicand, 
      const int32_t index, bool* err);
  tal_fn_attr_inline inline int64_t tal_root_i64(const int64_t radicand, 
      const int32_t index, bool* err);

  tal_fn_attr_inline inline uint8_t tal_root_u8(const uint8_t radicand, 
      const int32_t index, bool* err);
  tal_fn_attr_inline inline uint16_t tal_root_u16(const uint16_t radicand, 
      const int32_t index, bool* err);
  tal_fn_attr_inline inline uint32_t tal_root_u32(const uint32_t radicand, 
      const int32_t index, bool* err);
  tal_fn_attr_inline inline uint64_t tal_root_u64(const uint64_t radicand, 
      const int32_t index, bool* err);
  /** @} */

  /**
   * @defgroup integer tal_log
   * @brief Gets the base n logarithm of a given value (integer only).
   * @param value (integer type denoted by suffix) The value to take the log of.
   * @param base (int32_t) The base of the logarithm.
   * @param err (bool*) The error flag. Set if 'value' is less than or equal to 0,
   *            or if 'base' is less than or equal to 1 (result is undefined). If
   *            set, this function returns 0 and is guaranteed to have no other
   *            side effects.
   * @returns (integer type denoted by suffix) The 'base' n logarithm of 'value'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_log_i8(const int8_t value, 
      const int32_t base, bool* err);
  tal_fn_attr_inline inline int16_t tal_log_i16(const int16_t value, 
      const int32_t base, bool* err);
  tal_fn_attr_inline inline int32_t tal_log_i32(const int32_t value, 
      const int32_t base, bool* err);
  tal_fn_attr_inline inline int64_t tal_log_i64(const int64_t value, 
      const int32_t base, bool* err);

  tal_fn_attr_inline inline uint8_t tal_log_u8(const uint8_t value, 
      const int32_t base, bool* err);
  tal_fn_attr_inline inline uint16_t tal_log_u16(const uint16_t value, 
      const int32_t base, bool* err);
  tal_fn_attr_inline inline uint32_t tal_log_u32(const uint32_t value, 
      const int32_t base, bool* err);
  tal_fn_attr_inline inline uint64_t tal_log_u64(const uint64_t value, 
      const int32_t base, bool* err);
  /** @} */

  /**************************************************************************************************
   * @section Integer Rounding Utilities
   **************************************************************************************************/

  /**
   * @defgroup integer tal_floor
   * @brief Rounds a value down to a given multiple (integer only).
   * @param value (integer type denoted by suffix) The value to floor.
   * @param multiple (integer type denoted by suffix) The multiple to floor to.
   * @param err (bool*) The error flag. Set if 'multiple' is less than or
   *            equal to 0 or if the operation overflows. If set, this function 
   *            returns 0, or the saturated result and is guaranteed to have no 
   *            other side effects.
   * @returns (integer type denoted by suffix) 'value' rounded to the greatest
   *          multiple of 'multiple' that is less than or equal to it.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_floor_i8(const int8_t value, 
      const int8_t multiple, bool* err);
  tal_fn_attr_inline inline int16_t tal_floor_i16(const int16_t value, 
      const int16_t multiple, bool* err);
  tal_fn_attr_inline inline int32_t tal_floor_i32(const int32_t value, 
      const int32_t multiple, bool* err);
  tal_fn_attr_inline inline int64_t tal_floor_i64(const int64_t value, 
      const int64_t multiple, bool* err);

  tal_fn_attr_inline inline uint8_t tal_floor_u8(const uint8_t value, 
      const uint8_t multiple, bool* err);
  tal_fn_attr_inline inline uint16_t tal_floor_u16(const uint16_t value, 
      const uint16_t multiple, bool* err);
  tal_fn_attr_inline inline uint32_t tal_floor_u32(const uint32_t value, 
      const uint32_t multiple, bool* err);
  tal_fn_attr_inline inline uint64_t tal_floor_u64(const uint64_t value, 
      const uint64_t multiple, bool* err);
  /** @} */

  /**
   * @defgroup integer tal_ceil
   * @brief Rounds a value up to a given multiple (integer only).
   * @param value (integer type denoted by suffix) The value to round.
   * @param multiple (integer type denoted by suffix) The multiple to round up to.
   * @param err (bool*) The error flag. Set if 'multiple' is less than or
   *            equal to 0 or if the operation overflows. If set, this function 
   *            returns 0, or the saturated result and is guaranteed to have no 
   *            other side effects.
   * @returns (integer type denoted by suffix) 'value' rounded to the smallest
   *          multiple of 'multiple' that is greater than or equal to it.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_ceil_i8(const int8_t value, 
      const int8_t multiple, bool* err);
  tal_fn_attr_inline inline int16_t tal_ceil_i16(const int16_t value, 
      const int16_t multiple, bool* err);
  tal_fn_attr_inline inline int32_t tal_ceil_i32(const int32_t value, 
      const int32_t multiple, bool* err);
  tal_fn_attr_inline inline int64_t tal_ceil_i64(const int64_t value, 
      const int64_t multiple, bool* err);

  tal_fn_attr_inline inline uint8_t tal_ceil_u8(const uint8_t value, 
      const uint8_t multiple, bool* err);
  tal_fn_attr_inline inline uint16_t tal_ceil_u16(const uint16_t value, 
      const uint16_t multiple, bool* err);
  tal_fn_attr_inline inline uint32_t tal_ceil_u32(const uint32_t value, 
      const uint32_t multiple, bool* err);
  tal_fn_attr_inline inline uint64_t tal_ceil_u64(const uint64_t value, 
      const uint64_t multiple, bool* err);
  /** @} */

  /**
   * @defgroup integer tal_round
   * @brief Rounds a value to the nearest given multiple (integer only).
   * @param value (integer type denoted by suffix) The value to round.
   * @param multiple (integer type denoted by suffix) The multiple to round to.
   * @param err (bool*) The error flag. Set if 'multiple' is less than or
   *            equal to 0, or if the operation overflows. If set, this function
   *            returns 0, or the nearest valid multiple and is guaranteed to
   *            have no other side effects.
   * @returns (integer type denoted by suffix) 'value' rounded to the nearest 
   *          multiple of 'multiple'.
   * @note - If 'value' is equidistant from two multiples, the greater multiple
   *         is always choosen (even when 'value' is negative).
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_round_i8(const int8_t value, 
      const int8_t multiple, bool* err);
  tal_fn_attr_inline inline int16_t tal_round_i16(const int16_t value, 
      const int16_t multiple, bool* err);
  tal_fn_attr_inline inline int32_t tal_round_i32(const int32_t value, 
      const int32_t multiple, bool* err);
  tal_fn_attr_inline inline int64_t tal_round_i64(const int64_t value, 
      const int64_t multiple, bool* err);

  tal_fn_attr_inline inline uint8_t tal_round_u8(const uint8_t value, 
      const uint8_t multiple, bool* err);
  tal_fn_attr_inline inline uint16_t tal_round_u16(const uint16_t value, 
      const uint16_t multiple, bool* err);
  tal_fn_attr_inline inline uint32_t tal_round_u32(const uint32_t value, 
      const uint32_t multiple, bool* err);
  tal_fn_attr_inline inline uint64_t tal_round_u64(const uint64_t value, 
      const uint64_t multiple, bool* err);
  /** @} */ 

  /**************************************************************************************************
   * @section Miscellaneous Integer Utilities
   **************************************************************************************************/

  /**
   * @brief Gets the greatest common divisor of two integers.
   * @param value_a (integer type denoted by suffix) The first value.
   * @param value_b (integer type denoted by suffix) The second value.
   * @returns (integer type denoted by suffix) The greatest common divisor of
   *          'value_a' and 'value_b'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_gcd_i8(const int8_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline int16_t tal_gcd_i16(const int16_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline int32_t tal_gcd_i32(const int32_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline int64_t tal_gcd_i64(const int64_t* values, 
      const int32_t n, bool* err);

  tal_fn_attr_inline inline uint8_t tal_gcd_u8(const uint8_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline uint16_t tal_gcd_u16(const uint16_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline uint32_t tal_gcd_u32(const uint32_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline uint64_t tal_gcd_u64(const uint64_t* values, 
      const int32_t n, bool* err);
  /** @} */

  /**
   * @brief Gets the least common multiple of two integers.
   * @param value_a (integer type denoted by suffix) The first value.
   * @param value_b (integer type denoted by suffix) The second value.
   * @returns (integer type denoted by suffix) The least common multiple of
   *          'value_a' and 'value_b'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_lcm_i8(const int8_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline int16_t tal_lcm_i16(const int16_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline int32_t tal_lcm_i32(const int32_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline int64_t tal_lcm_i64(const int64_t* values, 
      const int32_t n, bool* err);

  tal_fn_attr_inline inline uint8_t tal_lcm_u8(const uint8_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline uint16_t tal_lcm_u16(const uint16_t* values, 
      const int32_t n, bool* err);
  tal_fn_attr_inline inline uint32_t tal_lcm_u32(const uint32_t* values, 
      const int32_t n, bool* err); 
  tal_fn_attr_inline inline uint64_t tal_lcm_u64(const uint64_t* values, 
      const int32_t n, bool* err);
  /** @} */

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  int8_t tal_pow_i8(const int8_t base, const int32_t exp, bool* err) {
    if (exp < 0) { 
      if (base == 0) { *err = true; }
      return 0; 
    }
    if (exp == 0) { return 1; }
    int8_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_smul_i8(result, base, err);
    }
    return result;
  }

  int16_t tal_pow_i16(const int16_t base, const int32_t exp, bool* err) {
    if (exp < 0) { 
      if (base == 0) { *err = true; }
      return 0; 
    }
    if (exp == 0) { return 1; }
    int16_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_smul_i16(result, base, err);
    }
    return result;
  }

  int32_t tal_pow_i32(const int32_t base, const int32_t exp, bool* err) {
    if (exp < 0) { 
      if (base == 0) { *err = true; }
      return 0; 
    }
    if (exp == 0) { return 1; }
    int32_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_smul_i32(result, base, err);
    }
    return result;
  }

  int64_t tal_pow_i64(const int64_t base, const int32_t exp, bool* err) {
    if (exp < 0) { 
      if (base == 0) { *err = true; }
      return 0; 
    }
    if (exp == 0) { return 1; }
    int64_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_smul_i64(result, base, err);
    }
    return result;
  }

  uint8_t tal_pow_u8(const uint8_t base, const int32_t exp, bool* err) {
    if (exp == 0) { return 1u; }
    uint8_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_smul_u8(result, base, err);
    }
    return result;
  }

  uint16_t tal_pow_u16(const uint16_t base, const int32_t exp, bool* err) {
    if (exp == 0) { return 1u; }
    uint16_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_smul_i8(result, base, err);
    }
    return result;
  }

  uint32_t tal_pow_u32(const uint32_t base, const int32_t exp, bool* err) {
    if (exp == 0) { return 1u; }
    uint32_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_smul_u32(result, base, err);
    }
    return result;
  }

  uint64_t tal_pow_u64(const uint64_t base, const int32_t exp, bool* err) {
    if (exp == 0) { return 1u; }
    uint64_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_smul_u64(result, base, err);
    }
    return result;
  }

  int8_t tal_root_i8(const int8_t radicand, const int32_t index, bool* err) {
    if (radicand < 0 && index % 2 == 0) {
      *err = true;
      return 0;
    }
    if (index == 0) {
      if (radicand != 0) { *err = true; }
      return 0;
    }
    if (index < 0) {
      if (radicand == 0) { *err = true; }
      if (radicand == -1 || radicand == 1) { return radicand; }
      return 0;      
    }
    if (index == 1) { return radicand; }
    int8_t c_root = 1;
    while (true) {
      int8_t c_pow = radicand > 0 ? c_root : -c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (radicand > 0) {
          if (c_pow > (radicand / c_root)) { return c_root - 1; }
        } else {
          if (c_pow < (radicand / c_root)) { return -c_root + 1; }
        }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  int16_t tal_root_i16(const int16_t radicand, const int32_t index, bool* err) {
    if (radicand < 0 && index % 2 == 0) {
      *err = true;
      return 0;
    }
    if (index == 0) {
      if (radicand != 0) { *err = true; }
      return 0;
    }
    if (index < 0) {
      if (radicand == 0) { *err = true; }
      if (radicand == -1 || radicand == 1) { return radicand; }
      return 0;      
    }
    if (index == 1) { return radicand; }
    int16_t c_root = 1;
    while (true) {
      int16_t c_pow = radicand > 0 ? c_root : -c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (radicand > 0) {
          if (c_pow > (radicand / c_root)) { return c_root - 1; }
        } else {
          if (c_pow < (radicand / c_root)) { return -c_root + 1; }
        }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }
  
  int32_t tal_root_i32(const int32_t radicand, const int32_t index, bool* err) {
    if (radicand < 0 && index % 2 == 0) {
      *err = true;
      return 0;
    }
    if (index == 0) {
      if (radicand != 0) { *err = true; }
      return 0;
    }
    if (index < 0) {
      if (radicand == 0) { *err = true; }
      if (radicand == -1 || radicand == 1) { return radicand; }
      return 0;      
    }
    if (index == 1) { return radicand; }
    int32_t c_root = 1;
    while (true) {
      int32_t c_pow = radicand > 0 ? c_root : -c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (radicand > 0) {
          if (c_pow > (radicand / c_root)) { return c_root - 1; }
        } else {
          if (c_pow < (radicand / c_root)) { return -c_root + 1; }
        }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  int64_t tal_root_i64(const int64_t radicand, const int32_t index, bool* err) {
    if (radicand < 0 && index % 2 == 0) {
      *err = true;
      return 0;
    }
    if (index == 0) {
      if (radicand != 0) { *err = true; }
      return 0;
    }
    if (index < 0) {
      if (radicand == 0) { *err = true; }
      if (radicand == -1 || radicand == 1) { return radicand; }
      return 0;      
    }
    if (index == 1) { return radicand; }
    int64_t c_root = 1;
    while (true) {
      int64_t c_pow = radicand > 0 ? c_root : -c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (radicand > 0) {
          if (c_pow > (radicand / c_root)) { return c_root - 1; }
        } else {
          if (c_pow < (radicand / c_root)) { return -c_root + 1; }
        }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  uint8_t tal_root_u8(const uint8_t radicand, const int32_t index, bool* err) {
    if (index == 0) {
      if (radicand != 0u) { *err = true; }
      return 0u;
    }
    if (index < 0) {
      if (radicand == 0u) { *err = true; }
      if (radicand == 1u) { return radicand; }
      return 0;
    }
    if (index == 1) { return radicand; }
    int8_t c_root = 1u;
    while (true) {
      int8_t c_pow = c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (c_pow > (radicand / c_root)) { return c_root - 1u; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  uint16_t tal_root_u16(const uint16_t radicand, const int32_t index, bool* err) {
    if (index == 0) {
      if (radicand != 0u) { *err = true; }
      return 0u;
    }
    if (index < 0) {
      if (radicand == 0u) { *err = true; }
      if (radicand == 1u) { return radicand; }
      return 0;
    }
    if (index == 1) { return radicand; }
    int16_t c_root = 1u;
    while (true) {
      int16_t c_pow = c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (c_pow > (radicand / c_root)) { return c_root - 1u; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  uint32_t tal_root_u32(const uint32_t radicand, const int32_t index, bool* err) {
    if (index == 0) {
      if (radicand != 0u) { *err = true; }
      return 0u;
    }
    if (index < 0) {
      if (radicand == 0u) { *err = true; }
      if (radicand == 1u) { return radicand; }
      return 0;
    }
    if (index == 1) { return radicand; }
    int32_t c_root = 1u;
    while (true) {
      int32_t c_pow = c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (c_pow > (radicand / c_root)) { return c_root - 1u; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  uint64_t tal_root_u64(const uint64_t radicand, const int32_t index, bool* err) {
    if (index == 0) {
      if (radicand != 0u) { *err = true; }
      return 0u;
    }
    if (index < 0) {
      if (radicand == 0u) { *err = true; }
      if (radicand == 1u) { return radicand; }
      return 0;
    }
    if (index == 1) { return radicand; }
    int64_t c_root = 1u;
    while (true) {
      int64_t c_pow = c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (c_pow > (radicand / c_root)) { return c_root - 1u; }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  int8_t tal_log_i8(const int8_t value, const int32_t base, bool* err) {
    if (base <= 1 || value <= 0) {
      *err = true;
      return 0;
    }
    if (value <= base) { return 1; }
    int8_t pow = 1;
    int8_t c_value = base;
    while (c_value <= (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  int16_t tal_log_i16(const int16_t value, const int32_t base, bool* err) {
    if (base <= 1 || value <= 0) {
      *err = true;
      return 0;
    }
    if (value < base) { return 0; }
    int16_t pow = 1;
    int16_t c_value = base;
    while (c_value <= (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  int32_t tal_log_i32(const int32_t value, const int32_t base, bool* err) {
    if (base <= 1 || value <= 0) {
      *err = true;
      return 0;
    }
    if (value < base) { return 0; }
    int32_t pow = 1;
    int32_t c_value = base;
    while (c_value <= (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  int64_t tal_log_i64(const int64_t value, const int32_t base, bool* err) {
    if (base <= 1 || value <= 0) {
      *err = true;
      return 0;
    }
    if (value < base) { return 0; }
    int64_t pow = 1;
    int64_t c_value = base;
    while (c_value <= (value / base)) {
      c_value *= base;
      ++pow;
    }
    return pow;
  }

  uint8_t tal_log_u8(const uint8_t value, const int32_t base, bool* err) {
    if (base <= 1 || value <= 0u) {
      *err = true;
      return 0u;
    }
    if (tal_cmpl(value, base)) { return 0u; }
    uint8_t pow = 1u;
    uint8_t c_value = base;
    while (c_value <= (value / (uint8_t)base)) {
      c_value *= (uint8_t)base;
      ++pow;
    }
    return pow;
  }

  uint16_t tal_log_u16(const uint16_t value, const int32_t base, bool* err) {
    if (base <= 1 || value <= 0u) {
      *err = true;
      return 0u;
    }
    if (tal_cmpl(value, base)) { return 0u; }
    uint16_t pow = 1u;
    uint16_t c_value = base;
    while (c_value <= (value / (uint32_t)base)) {
      c_value *= (uint16_t)base;
      ++pow;
    }
    return pow;
  }

  uint32_t tal_log_u32(const uint32_t value, const int32_t base, bool* err) {
    if (base <= 1 || value <= 0u) {
      *err = true;
      return 0u;
    }
    if (tal_cmpl(value, base)) { return 0u; }
    uint32_t pow = 1u;
    uint32_t c_value = base;
    while (c_value <= (value / (uint32_t)base)) {
      c_value *= (uint32_t)base;
      ++pow;
    }
    return pow;
  }


  uint64_t tal_log_u64(const uint64_t value, const int32_t base, bool* err) {
    if (base <= 1 || value <= 0u) {
      *err = true;
      return 0u;
    }
    if (tal_cmpl(value, base)) { return 0u; }
    uint64_t pow = 1u;
    uint64_t c_value = base;
    while (c_value <= (value / (uint64_t)base)) {
      c_value *= (uint64_t)base;
      ++pow;
    }
    return pow;
  }

  int8_t tal_floor_i8(const int8_t value, const int8_t multiple, bool* err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int8_t diff = value % multiple + (value < 0 ? multiple : 0);
    return tal_ssub_i8(value, diff, err);
  }

  int16_t tal_floor_i16(const int16_t value, const int16_t multiple, bool* err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int16_t diff = value % multiple + (value < 0 ? multiple : 0);
    return tal_ssub_i16(value, diff, err);
  }

  int32_t tal_floor_i32(const int32_t value, const int32_t multiple, bool* err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int32_t diff = value % multiple + (value < 0 ? multiple : 0);
    return tal_ssub_i32(value, diff, err);
  }

  int64_t tal_floor_i64(const int64_t value, const int64_t multiple, bool* err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int64_t diff = value % multiple + (value < 0 ? multiple : 0);
    return tal_ssub_i64(value, diff, err);
  }
  
  uint8_t tal_floor_u8(const uint8_t value, const uint8_t multiple, bool* err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_ssub_u8(value, value % multiple, err);
  }

  uint16_t tal_floor_u16(const uint16_t value, const uint16_t multiple, bool* err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_ssub_u16(value, value % multiple, err);
  }
  
  uint32_t tal_floor_u32(const uint32_t value, const uint32_t multiple, bool* err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_ssub_u32(value, value % multiple, err);
  }

  uint64_t tal_floor_u64(const uint64_t value, const uint64_t multiple, bool* err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_ssub_u64(value, value % multiple, err);
  }
  
  int8_t tal_ceil_i8(const int8_t value, const int8_t multiple, bool* err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int8_t diff = (value > 0 ? multiple : 0) - value % multiple;
    return tal_sadd_i8(value, diff, err);
  }

  int16_t tal_ceil_i16(const int16_t value, const int16_t multiple, bool *err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int16_t diff = (value > 0 ? multiple : 0) - value % multiple;
    return tal_sadd_i16(value, diff, err);
  }

  int32_t tal_ceil_i32(const int32_t value, const int32_t multiple, bool* err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int32_t diff = (value > 0 ? multiple : 0) - value % multiple;
    return tal_sadd_i32(value, diff, err);
  }

  int64_t tal_ceil_i64(const int64_t value, const int64_t multiple, bool* err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int64_t diff = (value > 0 ? multiple : 0) - value % multiple;
    return tal_sadd_i64(value, diff, err);
  }

  uint8_t tal_ceil_u8(const uint8_t value, const uint8_t multiple, bool* err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_sadd_u8(value, multiple - (value % multiple), err);
  }

  uint16_t tal_ceil_u16(const uint16_t value, const uint16_t multiple, bool* err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_sadd_u16(value, multiple - (value % multiple), err);
  }

  uint32_t tal_ceil_u32(const uint32_t value, const uint32_t multiple, bool* err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_sadd_u32(value, multiple - (value % multiple), err);
  }

  uint64_t tal_ceil_u64(const uint64_t value, const uint64_t multiple, bool* err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_sadd_u64(value, multiple - (value % multiple), err);
  }

  int8_t tal_round_i8(const int8_t value, const int8_t multiple, bool* err) {
   if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int8_t diff = value % multiple;
    if (value > 0) {
      if (value > INT8_MAX - multiple) {
        *err = true;
        return value - diff;
      }
      if (diff < (multiple / 2)) {
        return value - diff;
      } else {
        return value + (multiple - diff);
      }
    } else {
      if (value < INT8_MIN + multiple) {
        *err = true;
        return value - diff;
      }
      if ((multiple + diff) < (multiple / 2)) {
        return value - (multiple + diff);
      } else {
        return value - diff;
      }
    }
  }

  int16_t tal_round_i16(const int16_t value, const int16_t multiple, bool* err) {
   if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int16_t diff = value % multiple;
    if (value > 0) {
      if (value > INT16_MAX - multiple) {
        *err = true;
        return value - diff;
      }
      if (diff < (multiple / 2)) {
        return value - diff;
      } else {
        return value + (multiple - diff);
      }
    } else {
      if (value < INT16_MIN + multiple) {
        *err = true;
        return value - diff;
      }
      if ((multiple + diff) < (multiple / 2)) {
        return value - (multiple + diff);
      } else {
        return value - diff;
      }
    }
  }

  int32_t tal_round_i32(const int32_t value, const int32_t multiple, bool* err) {
   if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int32_t diff = value % multiple;
    if (value > 0) {
      if (value > INT32_MAX - multiple) {
        *err = true;
        return value - diff;
      }
      if (diff < (multiple / 2)) {
        return value - diff;
      } else {
        return value + (multiple - diff);
      }
    } else {
      if (value < INT32_MIN + multiple) {
        *err = true;
        return value - diff;
      }
      if ((multiple + diff) < (multiple / 2)) {
        return value - (multiple + diff);
      } else {
        return value - diff;
      }
    }
  }

  int64_t tal_round_i64(const int64_t value, const int64_t multiple, bool* err) {
   if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int64_t diff = value % multiple;
    if (value > 0) {
      if (value > INT64_MAX - multiple) {
        *err = true;
        return value - diff;
      }
      if (diff < (multiple / 2)) {
        return value - diff;
      } else {
        return value + (multiple - diff);
      }
    } else {
      if (value < INT64_MIN + multiple) {
        *err = true;
        return value - diff;
      }
      if ((multiple + diff) < (multiple / 2)) {
        return value - (multiple + diff);
      } else {
        return value - diff;
      }
    }
  }

  uint8_t tal_round_u8(const uint8_t value, const uint8_t multiple, bool* err) {
   if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    const uint8_t diff = value % multiple;
    if (value > UINT8_MAX - multiple) {
      *err = true;
      return value - diff;
    }
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  uint16_t tal_round_u16(const uint16_t value, const uint16_t multiple, bool* err) {
   if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    const uint16_t diff = value % multiple;
    if (value > UINT16_MAX - multiple) {
      *err = true;
      return value - diff;
    }
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  uint32_t tal_round_u32(const uint32_t value, const uint32_t multiple, bool* err) {
   if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    const uint32_t diff = value % multiple;
    if (value > UINT32_MAX - multiple) {
      *err = true;
      return value - diff;
    }
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  uint64_t tal_round_u64(const uint64_t value, const uint64_t multiple, bool* err) {
   if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    const uint64_t diff = value % multiple;
    if (value > UINT64_MAX - multiple) {
      *err = true;
      return value - diff;
    }
    if (diff < (multiple / 2)) {
      return value - diff;
    } else {
      return value + (multiple - diff);
    }
  }

  int8_t tal_gcd_i8(const int8_t value_a, const int8_t value_b, bool* err) {
    if (value_a < 0 || value_b < 0) {
      *err = true;
      return 0;
    }
    if (value_a == 0) { return value_b; }
    if (value_b == 0) { return value_a; }
    int8_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  int8_t tal_gcd_i8(const int8_t* values, const int32_t n, bool* err) {
    if (!values || n < 0) {
      *err = true;
      return 0;
    }
    int8_t gcd = tal_min_i8(values, n, err);
    while ()

  }

  int16_t tal_gcd_i16(const int16_t* values, const int32_t n, bool* err) {

  }

  int32_t tal_gcd_i32(const int32_t* values, const int32_t n, bool* err) {

  }

  int64_t tal_gcd_i64(const int64_t* values, const int32_t n, bool* err) {

  }

  uint8_t tal_gcd_u8(const uint8_t* values, const int32_t n, bool* err) {

  }

  uint16_t tal_gcd_u16(const uint16_t* values, const int32_t n, bool* err) {

  }

  uint32_t tal_gcd_u32(const uint32_t* values, const int32_t n, bool* err) {

  }

  uint64_t tal_gcd_u64(const uint64_t* values, const int32_t n, bool* err) {

  }



  int16_t tal_gcd_i16(const int16_t value_a, const int16_t value_b, bool* err) {
    if (value_a < 0 || value_b < 0) {
      *err = true;
      return 0;
    }
    if (value_a == 0) { return value_b; }
    if (value_b == 0) { return value_a; }
    int16_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  int32_t tal_gcd_i32(const int32_t value_a, const int32_t value_b, bool* err) {
    if (value_a < 0 || value_b < 0) {
      *err = true;
      return 0;
    }
    if (value_a == 0) { return value_b; }
    if (value_b == 0) { return value_a; }
    int32_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0 && value_b % gcd == 0) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  int64_t tal_gcd_i64(const int64_t value_a, const int64_t value_b, bool* err) {
    if (value_a < 0 || value_b < 0) {
      *err = true;
      return 0;
    }
    if (value_a == 0) { return value_b; }
    if (value_b == 0) { return value_a; }
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
    if (value_a == 0u) { return value_b; }
    if (value_b == 0u) { return value_a; }
    uint8_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0u && value_b % gcd == 0u) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  uint16_t tal_gcd_u16(const uint16_t value_a, const uint16_t value_b) {
    if (value_a == 0u) { return value_b; }
    if (value_b == 0u) { return value_a; }
    uint16_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0u && value_b % gcd == 0u) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  uint32_t tal_gcd_u32(const uint32_t value_a, const uint32_t value_b) {
    if (value_a == 0u) { return value_b; }
    if (value_b == 0u) { return value_a; }
    uint32_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0u && value_b % gcd == 0u) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  uint64_t tal_gcd_u64(const uint64_t value_a, const uint64_t value_b) {
    if (value_a == 0u) { return value_b; }
    if (value_b == 0u) { return value_a; }
    uint64_t gcd = value_a < value_b ? value_a : value_b;
    while (gcd > 1) {
      if (value_a % gcd == 0u && value_b % gcd == 0u) {
        return gcd;
      }
      --gcd;
    }
    return gcd;
  }

  int8_t tal_lcm_i8(const int8_t value_a, const int8_t value_b, bool* err) {
    bool gcd_err = false;
    const int8_t gcd = tal_gcd_i8(value_a, value_b, &gcd_err);
    if (!gcd_err) {
      *err = true;
      return 0;
    }
    return (value_a * value_b) / gcd;
  }

  int16_t tal_lcm_i16(const int16_t value_a, const int16_t value_b, bool* err) {
    bool gcd_err = false;
    const int16_t gcd = tal_gcd_i16(value_a, value_b, &gcd_err);
    if (!gcd_err) {
      *err = true;
      return 0;
    }
    return (value_a * value_b) / gcd;
  }

  int32_t tal_lcm_i32(const int32_t value_a, const int32_t value_b, bool* err) {
    bool gcd_err = false;
    const int32_t gcd = tal_gcd_i32(value_a, value_b, &gcd_err);
    if (!gcd_err) {
      *err = true;
      return 0;
    }
    return (value_a * value_b) / gcd;
  }

  int64_t tal_lcm_i64(const int64_t value_a, const int64_t value_b, bool* err) {
    bool gcd_err = false;
    const int64_t gcd = tal_gcd(value_a, value_b, &gcd_err);
    if (!gcd_err) {
      *err = true;
      return 0;
    }
    return (value_a * value_b) / gcd;
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