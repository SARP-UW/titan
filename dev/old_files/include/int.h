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
 * @file include/tal/int.h
 * @authors Aaron McBride
 * @brief Core Integer Utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Comparison Utilities
   **************************************************************************************************/

  inline bool tal_cmpe_iu(const int64_t lhs, const uint64_t rhs);
  inline bool tal_cmpe_ui(const uint64_t lhs, const int64_t rhs);

  inline bool tal_cmpl_iu(const int64_t lhs, const uint64_t rhs);
  inline bool tal_cmpl_ui(const uint64_t lhs, const int64_t rhs);
  
  inline bool tal_cmpg_iu(const int64_t lhs, const uint64_t rhs);
  inline bool tal_cmpg_ui(const uint64_t lhs, const int64_t rhs);

  inline bool tal_cmple_iu(const int64_t lhs, const uint64_t rhs);
  inline bool tal_cmple_ui(const uint64_t lhs, const int64_t rhs);

  inline bool tal_cmpge_iu(const int64_t lhs, const uint64_t rhs);
  inline bool tal_cmpge_ui(const uint64_t lhs, const int64_t rhs);

  /**************************************************************************************************
   * @section Arithmetic Utilities
   **************************************************************************************************/

  /**
   * @defgroup integer tal_neg
   * @brief Checked/saturating integer negation operation.
   * @param value (signed integer type denoted by suffix) The value to negate.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows, or an internal error occurs.
   * @returns (signed integer type denoted by suffix) The negation of 'value' 
   *          clamped to the range of it's integer type.
   * @{
   */
  inline int8_t tal_neg_i8(const int8_t value, bool* const err);
  inline int16_t tal_neg_i16(const int16_t value, bool* const err);
  inline int32_t tal_neg_i32(const int32_t value, bool* const err);
  inline int64_t tal_neg_i64(const int64_t value, bool* const err);
  /** @} */

  /**
   * @defgroup fp tal_neg
   * @brief Checked/saturating floating-point negation operation.
   * @param value (floating point type denoted by suffix) The value to negate.
   * @returns (floating point type denoted by suffix) The negation of 'value'.
   * @note - If the given value is NAN or INF, the same value with the opposite
   *         sign is returned.
   */
  inline float tal_neg_f(const float value);
  inline double tal_neg_d(const double value);

  /**
   * @defgroup tal_add
   * @brief Checked/saturating addition operation.
   * @param value_a (numeric type denoted by suffix) The first value to add.
   * @param value_b (numeric type denoted by suffix) The second value to add.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows, an IEEE754 floating point exception occurs, or an 
   *            internal error occurs.
   * @returns (numeric type denoted by suffix) The sum of 'value_a' and 
   *          'value_b', clamped to the range of the returned type, or 0/NAN
   *          if a non-overflow error occurs.
   * @{
   */
  inline int8_t tal_add_i8(const int8_t value_a, 
      const int8_t value_b, bool* const err);
  inline int16_t tal_add_i16(const int16_t value_a, 
      const int16_t value_b, bool* const err);
  inline int32_t tal_add_i32(const int32_t value_a, 
      const int32_t value_b, bool* const err);
  inline int64_t tal_add_i64(const int64_t value_a, 
      const int64_t value_b, bool* const err);
  
  inline uint8_t tal_add_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* const err);
  inline uint16_t tal_add_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* const err);
  inline uint32_t tal_add_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* const err);
  inline uint64_t tal_add_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* const err);
  /** @} */

  inline float tal_add_f(const float value_a,
      const float value_b, bool* const err);
  inline double tal_add_d(const double value_a,
      const double value_b, bool* const err);

  /**
   * @defgroup tal_sub
   * @brief Checked/saturating subtraction operation.
   * @param value_a (numeric type denoted by suffix) The value to subtract from.
   * @param value_b (numeric type denoted by suffix) The value to subtract.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows, an IEEE754 floating point exception occurs, or an
   *            internal error occurs.
   * @returns (numeric type denoted by suffix) The difference between 'value_a'
   *          and 'value_b' clamped to the range of the result type, or 0/NAN
   *          if a non-overflow error occurs.
   * @{
   */
  inline int8_t tal_sub_i8(const int8_t value_a, 
      const int8_t value_b, bool* const err);
  inline int16_t tal_sub_i16(const int16_t value_a, 
      const int16_t value_b, bool* const err);
  inline int32_t tal_sub_i32(const int32_t value_a, 
      const int32_t value_b, bool* const err);
  inline int64_t tal_sub_i64(const int64_t value_a, 
      const int64_t value_b, bool* const err);

  inline uint8_t tal_sub_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* const err);
  inline uint16_t tal_sub_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* const err);
  inline uint32_t tal_sub_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* const err);
  inline uint64_t tal_sub_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* const err);
  /** @} */

  inline float tal_sub_f(const float value_a,
      const float value_b, bool* const err);
  inline double tal_sub_d(const double value_a,
      const double value_b, bool* const err);

  /**
   * @defgroup tal_mul
   * @brief Checked/saturating multiplication operation.
   * @param value_a (numeric type denoted by suffix) The first value to multiply.
   * @param value_b (numeric type denoted by suffix) The second value to multiply.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows, an IEEE754 floating point exception occurs, or an
   *            internal error occurs.
   * @returns (numeric type denoted by suffix) The product of 'value_a' and 
   *          'value_b', clamped to the range of the result type, or 0/NAN if 
   *          a non-overflow error occurs.
   * @{
   */
  inline int8_t tal_mul_i8(const int8_t value_a, 
      const int8_t value_b, bool* const err);
  inline int16_t tal_mul_i16(const int16_t value_a, 
      const int16_t value_b, bool* const err);
  inline int32_t tal_mul_i32(const int32_t value_a, 
      const int32_t value_b, bool* const err);
  inline int64_t tal_mul_i64(const int64_t value_a, 
      const int64_t value_b, bool* const err);

  inline uint8_t tal_mul_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* const err);
  inline uint16_t tal_mul_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* const err);
  inline uint32_t tal_mul_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* const err);
  inline uint64_t tal_mul_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* const err);
  /** @} */

  inline float tal_mul_f(const float value_a,
      const float value_b, bool* const err);
  inline double tal_mul_d(const double value_a,
      const double value_b, bool* const err);

  /**
   * @defgroup tal_div
   * @brief Checked/saturating division operation.
   * @param num (numeric type denoted by suffix) The numerator's value.
   * @param div (numeric type denoted by suffix) The denominator's value.
   * @param err (bool*) The error flag. Accessed and set true if 'div' is 
   *            equal to zero, an IEEE754 floating point exception occurs, or
   *            an internal error occurs.
   * @returns (numeric type denoted by suffix) The result of dividing 'num' by
   *          'div' clamped to the range of the result type, or 0/NAN if a
   *          non-overflow error occurs.
   * @{
   */
  inline int8_t tal_div_i8(const int8_t num, 
      const int8_t div, bool* const err);
  inline int16_t tal_div_i16(const int16_t num, 
      const int16_t div, bool* const err);
  inline int32_t tal_div_i32(const int32_t num, 
      const int32_t div, bool* const err);
  inline int64_t tal_div_i64(const int64_t num, 
      const int64_t div, bool* const err);

  inline uint8_t tal_div_u8(const uint8_t num, 
      const uint8_t div, bool* const err);
  inline uint16_t tal_div_u16(const uint16_t num, 
      const uint16_t div, bool* const err);
  inline uint32_t tal_div_u32(const uint32_t num, 
      const uint32_t div, bool* const err);
  inline uint64_t tal_div_u64(const uint64_t num, 
      const uint64_t div, bool* const err);
  /** @} */

  inline float tal_div_f(const float num,
      const float div, bool* const err);
  inline double tal_div_d(const double num,
      const double div, bool* const err);

  /**
   * @defgroup tal_mod
   * @brief Checked/saturating modulo operation.
   * @param num (numeric type denoted by suffix) The numerator's value.
   * @param den (numeric type denoted by suffix) The denominator's value.
   * @param err (bool*) The error flag. Accessed and set true if 'den' is equal
   *            to zero, an IEEE754 floating point exception occurs, or an
   *            internal error occurs.
   * @returns (numeric type denoted by suffix) 'num' mod 'den' clamped to the 
   *          range of the result type, or 0/NAN if a non-overflow error occurs.
   * @{
   */
  inline int8_t tal_mod_i8(const int8_t num,
      const int8_t den, bool* const err);
  inline int16_t tal_mod_i16(const int16_t num,
      const int16_t den, bool* const err);
  inline int32_t tal_mod_i32(const int32_t num,
      const int32_t den, bool* const err);
  inline int64_t tal_mod_i64(const int64_t num,
      const int64_t den, bool* const err);
  
  inline uint8_t tal_mod_u8(const uint8_t num,
      const uint8_t den, bool* const err);
  inline uint16_t tal_mod_u16(const uint16_t num,
      const uint16_t den, bool* const err);
  inline uint32_t tal_mod_u32(const uint32_t num,
      const uint32_t den, bool* const err);
  inline uint64_t tal_mod_u64(const uint64_t num,
      const uint64_t den, bool* const err);
  /** @} */

  inline float tal_mod_f(const float num,
      const float den, bool* const err);
  inline double tal_mod_d(const double num,
      const double den, bool* const err);

  /**
   * @defgroup integer tal_lshift
   * @brief Checked/saturating left bit-shift operation.
   * @param value (integer type denoted by suffix) The value to shift.
   * @param shift (int32_t) The number of bits to shift by.
   * @param err (bool*) The error flag. Accessed and set true if shift is 
   *            negative or if any set bits are shifted beyond the bounds of the 
   *            suffix type.
   * @returns (integer type denoted by suffix) 'value' shifted left by the 
   *          maximum number of bits less than or equal to 'shift' such that no
   *          set bits is shifted beyond the bounds of the suffix type, or 'value' 
   *          unaltered if 'shift' is negative.
   * @{
   */
  inline int8_t tal_lshift_i8(const int8_t value, 
      const int32_t shift, bool* const err);
  inline int16_t tal_lshift_i16(const int16_t value, 
      const int32_t shift, bool* const err);
  inline int32_t tal_lshift_i32(const int32_t value, 
      const int32_t shift, bool* const err);
  inline int64_t tal_lshift_i64(const int64_t value, 
      const int32_t shift, bool* const err);

  inline uint8_t tal_lshift_u8(const uint8_t value, 
      const int32_t shift, bool* const err);
  inline uint16_t tal_lshift_u16(const uint16_t value, 
      const int32_t shift, bool* const err);
  inline uint32_t tal_lshift_u32(const uint32_t value, 
      const int32_t shift, bool* const err);
  inline uint64_t tal_lshift_u64(const uint64_t value, 
      const int32_t shift, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_rshift
   * @brief Checked/saturating right bit-shift operation.
   * @param value (integer type denoted by suffix) The value to shift.
   * @param shift (int32_t) The number of bits to shift by.
   * @param err (bool*) The error flag. Accessed and set true if shift is 
   *            negative or if any set bits are shifted beyond the bounds of 
   *            the suffix type.
   * @returns (integer type denoted by suffix) The result of shifting 'value'
   *          right by the max number of bits less then or equal to 'shift' such 
   *          that no bit is shifted beyond the range of the suffix type, or 'value' 
   *          unaltered if shift is negative.
   * @{
   */
  inline int8_t tal_rshift_i8(const int8_t value, 
      const int32_t shift, bool* const err);
  inline int16_t tal_rshift_i16(const int16_t value, 
      const int32_t shift, bool* const err);
  inline int32_t tal_rshift_i32(const int32_t value, 
      const int32_t shift, bool* const err);
  inline int64_t tal_rshift_i64(const int64_t value, 
      const int32_t shift, bool* const err);

  inline uint8_t tal_rshift_u8(const uint8_t value, 
      const int32_t shift, bool* const err);
  inline uint16_t tal_rshift_u16(const uint16_t value, 
      const int32_t shift, bool* const err);
  inline uint32_t tal_rshift_u32(const uint32_t value, 
      const int32_t shift, bool* const err);
  inline uint64_t tal_rshift_u64(const uint64_t value, 
      const int32_t shift, bool* const err);
  /** @} */

  /**************************************************************************************************
   * @section Casting Utilities
   **************************************************************************************************/

  /** @internal */

  /**************************************************************************************************
   * @section Implementation of Comparison Utilities
   **************************************************************************************************/

  bool tal_cmpe_iu(const int64_t lhs, const uint64_t rhs) {
    if (lhs < 0) { return false; }
    return (uint64_t)lhs == rhs;
  }

  bool tal_cmpe_ui(const uint64_t lhs, const int64_t rhs) {
    if (rhs < 0) { return false; }
    return lhs == (uint64_t)rhs;
  }

  bool tal_cmpl_iu(const int64_t lhs, const uint64_t rhs) {
    if (lhs < 0) { return true; }
    return (uint64_t)lhs < rhs;
  }

  bool tal_cmpl_ui(const uint64_t lhs, const int64_t rhs) {
    if (rhs < 0) { return false; }
    return lhs < (uint64_t)rhs;
  }
  
  bool tal_cmpg_iu(const int64_t lhs, const uint64_t rhs) {
    if (lhs < 0) { return false; }
    return (uint64_t)lhs > rhs;
  }

  bool tal_cmpg_ui(const uint64_t lhs, const int64_t rhs) {
    if (rhs < 0) { return true; }
    return lhs > (uint64_t)rhs;
  }

  bool tal_cmple_iu(const int64_t lhs, const uint64_t rhs) {
    if (lhs < 0) { return true; }
    return (uint64_t)lhs <= rhs;
  }

  bool tal_cmple_ui(const uint64_t lhs, const int64_t rhs) {
    if (rhs < 0) { return false; }
    return lhs <= (uint64_t)rhs;
  }

  bool tal_cmpge_iu(const int64_t lhs, const uint64_t rhs) {
    if (lhs < 0) { return false; }
    return (uint64_t)lhs >= rhs;
  }

  bool tal_cmpge_ui(const uint64_t lhs, const int64_t rhs) {
    if (rhs < 0) { return true; }
    return lhs >= (uint64_t)rhs;
  }



  /** @endinternal */

#if defined(__cplusplus)
  }
#endif