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
 * @note API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "src/common/attributes.h" // for inline attribute.
#include "include/tal/numeric.h" // For saturating arithmetic.
#include "include/tal/tmp.h" // For to_addr__

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
   * @param err (bool*) The error flag. Accessed and set true if the result 
   *            of the operation overflows, or an internal error occurs.
   * @returns (integer type denoted by suffix) The result of raising 'base' to
   *          the power of 'exp', clamped to the range of the suffix type, or
   *          0 if a non-overflow error occurs.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_pow_i8(const int8_t base, 
      const int32_t exp, bool* const err);
  tal_fn_attr_inline inline int16_t tal_pow_i16(const int16_t base, 
      const int32_t exp, bool* const err);
  tal_fn_attr_inline inline int32_t tal_pow_i32(const int32_t base, 
      const int32_t exp, bool* const err);
  tal_fn_attr_inline inline int64_t tal_pow_i64(const int64_t base, 
      const int32_t exp, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_pow_u8(const uint8_t base, 
      const int32_t exp, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_pow_u16(const uint16_t base, 
      const int32_t exp, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_pow_u32(const uint32_t base, 
      const int32_t exp, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_pow_u64(const uint64_t base, 
      const int32_t exp, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_root
   * @brief Gets the nth root of the given radicand (integer only).
   * @param radicand (integer type denoted by suffix) The radicand's value.
   * @param index (int32_t) The index of the root -> (e.g. sqrt -> index = 2).
   * @param err (bool*) The error flag. Accessed and set true if the result of 
   *            the operation is undefined or complex (refer to provided link), 
   *            or an internal error occurs.
   * @returns (integer type denoted by suffix) The 'index' root of 'radicand',
   *          or 0 if an error occurs.
   * @see https://en.wikipedia.org/wiki/Nth_root
   * @{
   */
  tal_fn_attr_inline inline tal_pair_i8t tal_root_i8(const int8_t radicand, 
      const int32_t index, bool* const err);
  tal_fn_attr_inline inline tal_pair_i16t tal_root_i16(const int16_t radicand, 
      const int32_t index, bool* const err);
  tal_fn_attr_inline inline tal_pair_i32t tal_root_i32(const int32_t radicand, 
      const int32_t index, bool* const err);
  tal_fn_attr_inline inline tal_pair_i64t tal_root_i64(const int64_t radicand, 
      const int32_t index, bool* const err);

  tal_fn_attr_inline inline tal_pair_u8t tal_root_u8(const uint8_t radicand, 
      const int32_t index, bool* const err);
  tal_fn_attr_inline inline tal_pair_u16t tal_root_u16(const uint16_t radicand, 
      const int32_t index, bool* const err);
  tal_fn_attr_inline inline tal_pair_u32t tal_root_u32(const uint32_t radicand, 
      const int32_t index, bool* const err);
  tal_fn_attr_inline inline tal_pair_u64t tal_root_u64(const uint64_t radicand, 
      const int32_t index, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_log
   * @brief Gets the base n logarithm of a given value (integer only).
   * @param value (integer type denoted by suffix) The value to take the log of.
   * @param base (int32_t) The base of the logarithm.
   * @param err (bool*) The error flag. Accessed and set true if the result of
   *            the operation is undefined ('value' <= 0 or 'base' <= 1), or an
   *            internal error occurs.
   * @returns (integer type denoted by suffix) The 'base' n logarithm of 'value',
   *          or 0 if an error occurs.
   * @{
   */
  tal_fn_attr_inline inline tal_pair_i8t tal_log_i8(const int8_t value, 
      const int32_t base, bool* const err);
  tal_fn_attr_inline inline tal_pair_i16t tal_log_i16(const int16_t value, 
      const int32_t base, bool* const err);
  tal_fn_attr_inline inline tal_pair_i32t tal_log_i32(const int32_t value, 
      const int32_t base, bool* const err);
  tal_fn_attr_inline inline tal_pair_i64t tal_log_i64(const int64_t value, 
      const int32_t base, bool* const err);

  tal_fn_attr_inline inline tal_pair_u8t tal_log_u8(const uint8_t value, 
      const int32_t base, bool* const err);
  tal_fn_attr_inline inline tal_pair_u16t tal_log_u16(const uint16_t value, 
      const int32_t base, bool* const err);
  tal_fn_attr_inline inline tal_pair_u32t tal_log_u32(const uint32_t value, 
      const int32_t base, bool* const err);
  tal_fn_attr_inline inline tal_pair_u64t tal_log_u64(const uint64_t value, 
      const int32_t base, bool* const err);
  /** @} */

  /**************************************************************************************************
   * @section Integer Rounding Utilities
   **************************************************************************************************/

  /**
   * @defgroup integer tal_floor
   * @brief Rounds a value down to a given multiple (integer only).
   * @param value (integer type denoted by suffix) The value to floor.
   * @param multiple (integer type denoted by suffix) The multiple to floor to.
   * @param err (bool*) The error flag. Accessed and set true if 'multiple' is 
   *            less than or equal to 0, the operation overflows, or an internal
   *            error occurs.
   * @returns (integer type denoted by suffix) 'value' rounded to the greatest
   *          multiple of 'multiple' that is less than or equal to it, if no
   *          such multiple exists the nearest in-bounds multiple is returned,
   *          or 0 if a non-overflow error occurs.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_floor_i8(const int8_t value, 
      const int8_t multiple, bool* const err);
  tal_fn_attr_inline inline int16_t tal_floor_i16(const int16_t value, 
      const int16_t multiple, bool* const err);
  tal_fn_attr_inline inline int32_t tal_floor_i32(const int32_t value, 
      const int32_t multiple, bool* const err);
  tal_fn_attr_inline inline int64_t tal_floor_i64(const int64_t value, 
      const int64_t multiple, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_floor_u8(const uint8_t value, 
      const uint8_t multiple, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_floor_u16(const uint16_t value, 
      const uint16_t multiple, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_floor_u32(const uint32_t value, 
      const uint32_t multiple, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_floor_u64(const uint64_t value, 
      const uint64_t multiple, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_ceil
   * @brief Rounds a value up to a given multiple (integer only).
   * @param value (integer type denoted by suffix) The value to round.
   * @param multiple (integer type denoted by suffix) The multiple to round up to.
   * @param err (bool*) The error flag. Accessed and set true if 'multiple' is 
   *            less than or equal to 0, the operation overflows, or an internal
   *            error occurs.
   * @returns (integer type denoted by suffix) 'value' rounded to the smallest
   *          multiple of 'multiple' that is greater than or equal to it, 0 if
   *          'multiple' is out of bounds, the saturated result if an overflow 
   *          occurs, or 0 if a non-overflow error occurs.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_ceil_i8(const int8_t value, 
      const int8_t multiple, bool* const err);
  tal_fn_attr_inline inline int16_t tal_ceil_i16(const int16_t value, 
      const int16_t multiple, bool* const err);
  tal_fn_attr_inline inline int32_t tal_ceil_i32(const int32_t value, 
      const int32_t multiple, bool* const err);
  tal_fn_attr_inline inline int64_t tal_ceil_i64(const int64_t value, 
      const int64_t multiple, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_ceil_u8(const uint8_t value, 
      const uint8_t multiple, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_ceil_u16(const uint16_t value, 
      const uint16_t multiple, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_ceil_u32(const uint32_t value, 
      const uint32_t multiple, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_ceil_u64(const uint64_t value, 
      const uint64_t multiple, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_round
   * @brief Rounds a value to the nearest given multiple (integer only).
   * @param value (integer type denoted by suffix) The value to round.
   * @param multiple (integer type denoted by suffix) The multiple to round to.
   * @param err (bool*) The error flag. Accessed and set true if 'multiple' is 
   *            less than or equal to 0, the operation overflows, or an internal
   *            error occurs.
   * @returns (integer type denoted by suffix) 'value' rounded to the nearest 
   *          in-bounds multiple of 'multiple' or 0 if an error occurs.
   * @note - If 'value' is equidistant from two multiples, the greater multiple
   *         is choosen (unless only one of those multiples is in bounds).
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_round_i8(const int8_t value, 
      const int8_t multiple, bool* const err);
  tal_fn_attr_inline inline int16_t tal_round_i16(const int16_t value, 
      const int16_t multiple, bool* const err);
  tal_fn_attr_inline inline int32_t tal_round_i32(const int32_t value, 
      const int32_t multiple, bool* const err);
  tal_fn_attr_inline inline int64_t tal_round_i64(const int64_t value, 
      const int64_t multiple, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_round_u8(const uint8_t value, 
      const uint8_t multiple, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_round_u16(const uint16_t value, 
      const uint16_t multiple, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_round_u32(const uint32_t value, 
      const uint32_t multiple, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_round_u64(const uint64_t value, 
      const uint64_t multiple, bool* const err);
  /** @} */ 

  /**************************************************************************************************
   * @section Miscellaneous Integer Math Utilities
   **************************************************************************************************/

  /**
   * @defgroup integer tal_gcd
   * @brief Gets the greatest common divisor of a set of values (integer only).
   * @param values (pointer to integer type denoted by suffix), array of values
   *               to find the greatest common divisor of.
   * @param n (int32_t) The number of values in the given set.
   * @param err (bool*) The error flag. Accessed and set true if 'n' or any of 
   *            'values' is negative, 'values' is null, or an internal error occurs.
   * @returns (integer type denoted by suffix) The greatest common divisor of
   *          all values in the given set, or 0 if an error occurs.
   * @note - Values equal to 0 are ignored when determining the GCD.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_gcd_i8(const int8_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int16_t tal_gcd_i16(const int16_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int32_t tal_gcd_i32(const int32_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int64_t tal_gcd_i64(const int64_t* const values, 
      const int32_t n, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_gcd_u8(const uint8_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_gcd_u16(const uint16_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_gcd_u32(const uint32_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_gcd_u64(const uint64_t* const values, 
      const int32_t n, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_lcm
   * @brief Gets the least common multiple of a set of values (integer only).
   * @param values (pointer to integer type denoted by suffix), array of values
   *               to find the least common multiple of.
   * @param n (int32_t) The number of values in the given set.
   * @param err (bool*) The error flag. Accessed and set true if 'n' or any of 
   *            'values' is negative, 'values' is null, the operation overflows,
   *            or an internal error occurs.
   * @returns (integer type denoted by suffix) The least common multiple of all
   *          values in the given set, the saturated result if an overflow occurs,
   *          or 0 if a non-overflow error occurs.
   * @note - If any value in the given set equals 0, the LCM will also be 0.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_lcm_i8(const int8_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int16_t tal_lcm_i16(const int16_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int32_t tal_lcm_i32(const int32_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int64_t tal_lcm_i64(const int64_t* const values, 
      const int32_t n, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_lcm_u8(const uint8_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_lcm_u16(const uint16_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_lcm_u32(const uint32_t* const values, 
      const int32_t n, bool* const err); 
  tal_fn_attr_inline inline uint64_t tal_lcm_u64(const uint64_t* const values, 
      const int32_t n, bool* const err);
  /** @} */

  /**************************************************************************************************
   * @internal Implementation of Exponentiation Utilities
   **************************************************************************************************/

  int8_t tal_pow_i8(const int8_t base, const int32_t exp, 
      bool* const err) {
    if (exp < 0) { 
      if (base == 0) { *err = true; }
      return 0; 
    }
    if (exp == 0) { return 1; }
    int8_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_mul_i8(result, base, err);
    }
    return result;
  }

  int16_t tal_pow_i16(const int16_t base, const int32_t exp, 
      bool* const err) {
    if (exp < 0) { 
      if (base == 0) { *err = true; }
      return 0; 
    }
    if (exp == 0) { return 1; }
    int16_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_mul_i16(result, base, err);
    }
    return result;
  }

  int32_t tal_pow_i32(const int32_t base, const int32_t exp, 
      bool* const err) {
    if (exp < 0) { 
      if (base == 0) { *err = true; }
      return 0; 
    }
    if (exp == 0) { return 1; }
    int32_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_mul_i32(result, base, err);
    }
    return result;
  }

  int64_t tal_pow_i64(const int64_t base, const int32_t exp, 
      bool* const err) {
    if (exp < 0) { 
      if (base == 0) { *err = true; }
      return 0; 
    }
    if (exp == 0) { return 1; }
    int64_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_mul_i64(result, base, err);
    }
    return result;
  }

  uint8_t tal_pow_u8(const uint8_t base, const int32_t exp, 
      bool* const err) {
    if (exp == 0) { return 1u; }
    uint8_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_mul_u8(result, base, err);
    }
    return result;
  }

  uint16_t tal_pow_u16(const uint16_t base, const int32_t exp, 
      bool* const err) {
    if (exp == 0) { return 1u; }
    uint16_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_mul_i8(result, base, err);
    }
    return result;
  }

  uint32_t tal_pow_u32(const uint32_t base, const int32_t exp, 
      bool* const err) {
    if (exp == 0) { return 1u; }
    uint32_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_mul_u32(result, base, err);
    }
    return result;
  }

  uint64_t tal_pow_u64(const uint64_t base, const int32_t exp, 
      bool* const err) {
    if (exp == 0) { return 1u; }
    uint64_t result = base;
    for (int32_t i = 0; i < (exp - 1); ++i) {
      result = tal_mul_u64(result, base, err);
    }
    return result;
  }

  tal_pair_i8t tal_root_i8(const int8_t radicand, const int32_t index, 
      bool* const err) {
    if (radicand < 0 && index % 2 == 0) {
      *err = true;
      return (tal_pair_i8t){0, 0};
    }
    if (index == 0) {
      if (radicand != 0) { *err = true; }
      return (tal_pair_i8t){0, 0};
    }
    if (index < 0) {
      if (radicand == -1 || radicand == 1) {
        return (tal_pair_i8t){radicand, 0};
      }
      if (radicand == 0) { *err = true; }
      return (tal_pair_i8t){0, 0};
    }
    if (index == 1) {
      return (tal_pair_i8t){radicand, 0};
    }

    int8_t best_root = 0;
    int8_t best_pow = 0;
    int8_t c_root = radicand > 0 ? 1 : -1;
    while (true) {
      int8_t c_pow = c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (radicand > 0) {
          if (c_pow > (INT8_MAX / c_root)) { goto exit; }
          if (tal_abs_i8(radicand - c_pow, NULL) < best_pow) {
            best_pow
          }

        } else {

        }

      }
    }
    exit:



    int8_t c_root = 1;
    while (true) {
      int8_t c_pow = radicand > 0 ? c_root : -c_root;
      for (int32_t i = 0; i < (index - 1); ++i) {
        if (radicand > 0) {
          if (c_pow > (radicand / c_root)) { 
            const int8_t rem = radicand - ((c_root - 1) * (c_root - 1));
            return (tal_pair_i8t){c_root - 1, rem};
          }
        } else {
          if (c_pow < (radicand / c_root)) { 
            const int8_t rem = radicand + ((c_root - 1) * (c_root - 1));
            return (tal_pair_i8t){-c_root + 1, -rem}; 
          }
        }
        c_pow *= c_root;
      }
      ++c_root;
    }
  }

  int16_t tal_root_i16(const int16_t radicand, const int32_t index, 
      bool* const err) {
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
  
  int32_t tal_root_i32(const int32_t radicand, const int32_t index, 
      bool* const err) {
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

  int64_t tal_root_i64(const int64_t radicand, const int32_t index, 
      bool* const err) {
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

  uint8_t tal_root_u8(const uint8_t radicand, const int32_t index, 
      bool* const err) {
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

  uint16_t tal_root_u16(const uint16_t radicand, const int32_t index, 
      bool* const err) {
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

  uint32_t tal_root_u32(const uint32_t radicand, const int32_t index, 
      bool* const err) {
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

  uint64_t tal_root_u64(const uint64_t radicand, const int32_t index, 
      bool* const err) {
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

  int8_t tal_log_i8(const int8_t value, const int32_t base, 
      bool* const err) {
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

  int16_t tal_log_i16(const int16_t value, const int32_t base, 
      bool* const err) {
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

  int32_t tal_log_i32(const int32_t value, const int32_t base, 
      bool* const err) {
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

  int64_t tal_log_i64(const int64_t value, const int32_t base, 
      bool* const err) {
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

  uint8_t tal_log_u8(const uint8_t value, const int32_t base, 
      bool* const err) {
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

  uint16_t tal_log_u16(const uint16_t value, const int32_t base, 
      bool* const err) {
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

  uint32_t tal_log_u32(const uint32_t value, const int32_t base, 
      bool* const err) {
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


  uint64_t tal_log_u64(const uint64_t value, const int32_t base, 
      bool* const err) {
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

  /**************************************************************************************************
   * @internal Implementation of Rounding Utilities
   **************************************************************************************************/

  int8_t tal_floor_i8(const int8_t value, const int8_t multiple, 
      bool* const err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int8_t diff = value % multiple + (value < 0 ? multiple : 0);
    return tal_sub_i8(value, diff, err);
  }

  int16_t tal_floor_i16(const int16_t value, const int16_t multiple, 
      bool* const err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int16_t diff = value % multiple + (value < 0 ? multiple : 0);
    return tal_sub_i16(value, diff, err);
  }

  int32_t tal_floor_i32(const int32_t value, const int32_t multiple, 
      bool* const err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int32_t diff = value % multiple + (value < 0 ? multiple : 0);
    return tal_sub_i32(value, diff, err);
  }

  int64_t tal_floor_i64(const int64_t value, const int64_t multiple, 
      bool* const err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int64_t diff = value % multiple + (value < 0 ? multiple : 0);
    return tal_sub_i64(value, diff, err);
  }
  
  uint8_t tal_floor_u8(const uint8_t value, const uint8_t multiple, 
      bool* const err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_sub_u8(value, value % multiple, err);
  }

  uint16_t tal_floor_u16(const uint16_t value, const uint16_t multiple, 
      bool* const err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_sub_u16(value, value % multiple, err);
  }
  
  uint32_t tal_floor_u32(const uint32_t value, const uint32_t multiple, 
      bool* const err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_sub_u32(value, value % multiple, err);
  }

  uint64_t tal_floor_u64(const uint64_t value, const uint64_t multiple, 
      bool* const err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_sub_u64(value, value % multiple, err);
  }
  
  int8_t tal_ceil_i8(const int8_t value, const int8_t multiple, 
      bool* const err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int8_t diff = (value > 0 ? multiple : 0) - value % multiple;
    return tal_add_i8(value, diff, err);
  }

  int16_t tal_ceil_i16(const int16_t value, const int16_t multiple, 
      bool* const err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int16_t diff = (value > 0 ? multiple : 0) - value % multiple;
    return tal_add_i16(value, diff, err);
  }

  int32_t tal_ceil_i32(const int32_t value, const int32_t multiple, 
      bool* const err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int32_t diff = (value > 0 ? multiple : 0) - value % multiple;
    return tal_add_i32(value, diff, err);
  }

  int64_t tal_ceil_i64(const int64_t value, const int64_t multiple, 
      bool* const err) {
    if (multiple <= 0) {
      *err = true;
      return 0;
    }
    const int64_t diff = (value > 0 ? multiple : 0) - value % multiple;
    return tal_add_i64(value, diff, err);
  }

  uint8_t tal_ceil_u8(const uint8_t value, const uint8_t multiple, 
      bool* const err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_add_u8(value, multiple - (value % multiple), err);
  }

  uint16_t tal_ceil_u16(const uint16_t value, const uint16_t multiple, 
      bool* const err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_add_u16(value, multiple - (value % multiple), err);
  }

  uint32_t tal_ceil_u32(const uint32_t value, const uint32_t multiple, 
      bool* const err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_add_u32(value, multiple - (value % multiple), err);
  }

  uint64_t tal_ceil_u64(const uint64_t value, const uint64_t multiple, 
      bool* const err) {
    if (multiple <= 0u) {
      *err = true;
      return 0u;
    }
    return tal_add_u64(value, multiple - (value % multiple), err);
  }

  int8_t tal_round_i8(const int8_t value, const int8_t multiple, 
      bool* const err) {
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

  int16_t tal_round_i16(const int16_t value, const int16_t multiple, 
      bool* const err) {
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

  int32_t tal_round_i32(const int32_t value, const int32_t multiple, 
      bool* const err) {
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

  int64_t tal_round_i64(const int64_t value, const int64_t multiple, 
      bool* const err) {
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

  uint8_t tal_round_u8(const uint8_t value, const uint8_t multiple, 
      bool* const err) {
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

  uint16_t tal_round_u16(const uint16_t value, const uint16_t multiple, 
      bool* const err) {
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

  uint32_t tal_round_u32(const uint32_t value, const uint32_t multiple, 
      bool* const err) {
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

  uint64_t tal_round_u64(const uint64_t value, const uint64_t multiple, 
      bool* const err) {
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

  /**************************************************************************************************
   * @internal Implementation of Miscellaneous Integer Math Utilities
   **************************************************************************************************/

  int8_t tal_gcd_i8(const int8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int8_t)))) {
      *err = true;
      return 0;
    }
    int8_t gcd = tal_min_i8(values, n, err);
    while (gcd > 1) {
      bool valid_gcd = true;
      for (int32_t i = 0; i < n; ++i) {
        if (values[i] < 0) {
          *err = true;
          return 0;
        }
        if (values[i] != 0 &&values[i] % gcd != 0) {
          valid_gcd = false;
          break;
        }
      }
      if (valid_gcd) { break; }
      --gcd;
    }
    return gcd;
  }

  int16_t tal_gcd_i16(const int16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int16_t)))) {
      *err = true;
      return 0;
    }
    int16_t gcd = tal_min_i16(values, n, err);
    while (gcd > 1) {
      bool valid_gcd = true;
      for (int32_t i = 0; i < n; ++i) {
        if (values[i] < 0) {
          *err = true;
          return 0;
        }
        if (values[i] != 0 &&values[i] % gcd != 0) {
          valid_gcd = false;
          break;
        }
      }
      if (valid_gcd) { break; }
      --gcd;
    }
    return gcd;
  }

  int32_t tal_gcd_i32(const int32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int32_t)))) {
      *err = true;
      return 0;
    }
    int32_t gcd = tal_min_i32(values, n, err);
    while (gcd > 1) {
      bool valid_gcd = true;
      for (int32_t i = 0; i < n; ++i) {
        if (values[i] < 0) {
          *err = true;
          return 0;
        }
        if (values[i] != 0 &&values[i] % gcd != 0) {
          valid_gcd = false;
          break;
        }
      }
      if (valid_gcd) { break; }
      --gcd;
    }
    return gcd;
  }

  int64_t tal_gcd_i64(const int64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int64_t)))) {
      *err = true;
      return 0;
    }
    int64_t gcd = tal_min_i64(values, n, err);
    while (gcd > 1) {
      bool valid_gcd = true;
      for (int32_t i = 0; i < n; ++i) {
        if (values[i] < 0) {
          *err = true;
          return 0;
        }
        if (values[i] != 0 && values[i] % gcd != 0) {
          valid_gcd = false;
          break;
        }
      }
      if (valid_gcd) { break; }
      --gcd;
    }
    return gcd;
  }

  uint8_t tal_gcd_u8(const uint8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint8_t)))) {
      *err = true;
      return 0u;
    }
    uint8_t gcd = tal_min_u8(values, n, err);
    while (gcd > 1u) {
      bool valid_gcd = true;
      for (int32_t i = 0; i < n; ++i) {
        if (values[i] != 0u && values[i] % gcd != 0u) {
          valid_gcd = false;
          break;
        }
      }
      if (valid_gcd) { break; }
      --gcd;
    }
    return gcd;
  }

  uint16_t tal_gcd_u16(const uint16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint16_t)))) {
      *err = true;
      return 0u;
    }
    uint16_t gcd = tal_min_u16(values, n, err);
    while (gcd > 1u) {
      bool valid_gcd = true;
      for (int32_t i = 0; i < n; ++i) {
        if (values[i] != 0u && values[i] % gcd != 0u) {
          valid_gcd = false;
          break;
        }
      }
      if (valid_gcd) { break; }
      --gcd;
    }
    return gcd;
  }

  uint32_t tal_gcd_u32(const uint32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint32_t)))) {
      *err = true;
      return 0u;
    }
    uint32_t gcd = tal_min_u32(values, n, err);
    while (gcd > 1u) {
      bool valid_gcd = true;
      for (int32_t i = 0; i < n; ++i) {
        if (values[i] != 0u &&values[i] % gcd != 0u) {
          valid_gcd = false;
          break;
        }
      }
      if (valid_gcd) { break; }
      --gcd;
    }
    return gcd;
  }

  uint64_t tal_gcd_u64(const uint64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint64_t)))) {
      *err = true;
      return 0u;
    }
    uint64_t gcd = tal_min_u64(values, n, err);
    while (gcd > 1u) {
      bool valid_gcd = true;
      for (int32_t i = 0; i < n; ++i) {
        if (values[i] != 0u && values[i] % gcd != 0u) {
          valid_gcd = false;
          break;
        }
      }
      if (valid_gcd) { break; }
      --gcd;
    }
    return gcd;
  }

  int8_t tal_lcm_i8(const int8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int8_t)))) {
      *err = true;
      return 0;
    }
    int8_t incr = *values;
    int8_t lcm = *values;
    for (int32_t i = 0; i < n; i++) {
      if (values[i] < 0) {
        *err = true;
        return 0;
      }
      if (values[i] == 0) { return 0; }
      if (values[i] < incr) { incr = values[i]; }
      if (values[i] > lcm) { lcm = values[i]; }
    }
    while (lcm <= (INT8_MAX - incr)) {
      bool valid_lcm = true;
      for (int32_t i = 0; i < n; ++i) {
        if (lcm % values[i] != 0) {
          valid_lcm = false;
          break;
        }
      }
      if (valid_lcm) { return lcm; }
      lcm += incr;
    }
    *err = true;
    return INT8_MAX;
  }

  int16_t tal_lcm_i16(const int16_t* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int16_t)))) {
      *err = true;
      return 0;
    }
    int16_t incr = *values;
    int16_t lcm = *values;
    for (int32_t i = 0; i < n; i++) {
      if (values[i] < 0) {
        *err = true;
        return 0;
      }
      if (values[i] == 0) { return 0; }
      if (values[i] < incr) { incr = values[i]; }
      if (values[i] > lcm) { lcm = values[i]; }
    }
    while (lcm <= (INT16_MAX - incr)) {
      bool valid_lcm = true;
      for (int32_t i = 0; i < n; ++i) {
        if (lcm % values[i] != 0) {
          valid_lcm = false;
          break;
        }
      }
      if (valid_lcm) { return lcm; }
      lcm += incr;
    }
    *err = true;
    return INT16_MAX;
  }

  int32_t tal_lcm_i32(const int32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int32_t)))) {
      *err = true;
      return 0;
    }
    int32_t incr = *values;
    int32_t lcm = *values;
    for (int32_t i = 0; i < n; i++) {
      if (values[i] < 0) {
        *err = true;
        return 0;
      }
      if (values[i] == 0) { return 0; }
      if (values[i] < incr) { incr = values[i]; }
      if (values[i] > lcm) { lcm = values[i]; }
    }
    while (lcm <= (INT32_MAX - incr)) {
      bool valid_lcm = true;
      for (int32_t i = 0; i < n; ++i) {
        if (lcm % values[i] != 0) {
          valid_lcm = false;
          break;
        }
      }
      if (valid_lcm) { return lcm; }
      lcm += incr;
    }
    *err = true;
    return INT32_MAX;
  }

  int64_t tal_lcm_i64(const int64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int64_t)))) {
      *err = true;
      return 0;
    }
    int64_t incr = *values;
    int64_t lcm = *values;
    for (int32_t i = 0; i < n; i++) {
      if (values[i] < 0) {
        *err = true;
        return 0;
      }
      if (values[i] == 0) { return 0; }
      if (values[i] < incr) { incr = values[i]; }
      if (values[i] > lcm) { lcm = values[i]; }
    }
    while (lcm <= (INT64_MAX - incr)) {
      bool valid_lcm = true;
      for (int32_t i = 0; i < n; ++i) {
        if (lcm % values[i] != 0) {
          valid_lcm = false;
          break;
        }
      }
      if (valid_lcm) { return lcm; }
      lcm += incr;
    }
    *err = true;
    return INT64_MAX;
  }

  uint8_t tal_lcm_u8(const uint8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint8_t)))) {
      *err = true;
      return 0u;
    }
    int8_t incr = *values;
    int8_t lcm = *values;
    for (int32_t i = 0; i < n; i++) {
      if (values[i] == 0u) { return 0u; }
      if (values[i] < incr) { incr = values[i]; }
      if (values[i] > lcm) { lcm = values[i]; }
    }
    while (lcm <= (UINT8_MAX - incr)) {
      bool valid_lcm = true;
      for (int32_t i = 0; i < n; ++i) {
        if (lcm % values[i] != 0u) {
          valid_lcm = false;
          break;
        }
      }
      if (valid_lcm) { return lcm; }
      lcm += incr;
    }
    *err = true;
    return UINT8_MAX;
  }

  uint16_t tal_lcm_u16(const uint16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint16_t)))) {
      *err = true;
      return 0u;
    }
    uint16_t incr = *values;
    uint16_t lcm = *values;
    for (int32_t i = 0; i < n; i++) {
      if (values[i] == 0u) { return 0u; }
      if (values[i] < incr) { incr = values[i]; }
      if (values[i] > lcm) { lcm = values[i]; }
    }
    while (lcm <= (UINT16_MAX - incr)) {
      bool valid_lcm = true;
      for (int32_t i = 0; i < n; ++i) {
        if (lcm % values[i] != 0u) {
          valid_lcm = false;
          break;
        }
      }
      if (valid_lcm) { return lcm; }
      lcm += incr;
    }
    *err = true;
    return UINT16_MAX;
  }

  uint32_t tal_lcm_u32(const uint32_t* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint32_t)))) {
      *err = true;
      return 0u;
    }
    uint32_t incr = *values;
    uint32_t lcm = *values;
    for (int32_t i = 0; i < n; i++) {
      if (values[i] == 0u) { return 0u; }
      if (values[i] < incr) { incr = values[i]; }
      if (values[i] > lcm) { lcm = values[i]; }
    }
    while (lcm <= (UINT32_MAX - incr)) {
      bool valid_lcm = true;
      for (int32_t i = 0; i < n; ++i) {
        if (lcm % values[i] != 0u) {
          valid_lcm = false;
          break;
        }
      }
      if (valid_lcm) { return lcm; }
      lcm += incr;
    }
    *err = true;
    return UINT32_MAX;
  }

  uint64_t tal_lcm_u64(const uint64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint64_t)))) {
      *err = true;
      return 0u;
    }
    uint64_t incr = *values;
    uint64_t lcm = *values;
    for (int32_t i = 0; i < n; i++) {
      if (values[i] == 0u) { return 0u; }
      if (values[i] < incr) { incr = values[i]; }
      if (values[i] > lcm) { lcm = values[i]; }
    }
    while (lcm <= (UINT64_MAX - incr)) {
      bool valid_lcm = true;
      for (int32_t i = 0; i < n; ++i) {
        if (lcm % values[i] != 0u) {
          valid_lcm = false;
          break;
        }
      }
      if (valid_lcm) { return lcm; }
      lcm += incr;
    }
    *err = true;
    return UINT64_MAX;
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif