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
 * @file include/tal/numeric.h
 * @authors Aaron McBride
 * @brief Numeric utilities.
 * @note API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#if defined(__cplusplus)
  extern "C" {
#endif




  /**************************************************************************************************
   * @section Core Numeric Utilities
   **************************************************************************************************/

  /**
   * @defgroup integer tal_copy_sign
   * @brief Copies the sign of one integer value to annother.
   * @param mag (signed integer denoted by suffix) The magnitude of the 
   *            returned value.
   * @param sgn (signed integer denoted by suffix) The value whose sign is
   *            copied to the returned value.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows.
   * @returns (signed integer denoted by suffix) The magnitude of 'mag' with
   *          the sign of 'sgn'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_copy_sign_i8(const int8_t mag,
      const int8_t sgn, bool* const err);
  tal_fn_attr_inline inline int16_t tal_copy_sign_i16(const int16_t mag,
      const int16_t sgn, bool* const err);
  tal_fn_attr_inline inline int32_t tal_copy_sign_i32(const int32_t mag,
      const int32_t sgn, bool* const err);
  tal_fn_attr_inline inline int64_t tal_copy_sign_i64(const int64_t mag,
      const int64_t sgn, bool* const err);
  /** @} */

  /**
   * @defgroup fp tal_copy_sign
   * @brief Copies the sign of one floating-point value to annother.
   * @param mag (floating point type denoted by suffix) The magnitude of the
   *            returned value.
   * @param sgn (floating point type denoted by suffix) The value whose sign is
   *            copied to the returned value.
   * @returns (floating point type denoted by suffix) A value with the 
   *          magnitude of 'mag' and the sign of 'sgn'.
   * @{
   */
  tal_fn_attr_inline inline float tal_copy_sign_f(const float mag, 
      const float sgn);
  tal_fn_attr_inline inline double tal_copy_sign_d(const double mag, 
      const double sgn);
  /** @} */

  /**
   * @defgroup integer tal_abs
   * @brief Gets the absolute value of an integer.
   * @param value (signed integer denoted by suffix) The value to modify.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows.
   * @returns (signed integer denoted by suffix) The absolute value of 'value',
   *          clamped to the range of the suffix type.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_abs_i8(const int8_t value, 
      bool* const err);
  tal_fn_attr_inline inline int16_t tal_abs_i16(const int16_t value, 
      bool* const err);
  tal_fn_attr_inline inline int32_t tal_abs_i32(const int32_t value, 
      bool* const err);
  tal_fn_attr_inline inline int64_t tal_abs_i64(const int64_t value, 
      bool* const err);
  /** @} */

  /**
   * @defgroup fp tal_abs
   * @brief Gets the absolute value of a floating-point number.
   * @param value (floating point type denoted by suffix) The value to modify.
   * @returns (floating point type denoted by suffix) The absolute value of 'value'.
   * @{
   */
  tal_fn_attr_inline inline float tal_abs_f(const float value);
  tal_fn_attr_inline inline double tal_abs_d(const double value);
  /** @} */

  /**
   * @defgroup tal_min
   * @brief Gets the minimum value contained in a set of values.
   * @param values (pointer to numeric type denoted by suffix) An array containing
   *               the values to query.
   * @param n (int32_t) The number of values in the given set.
   * @param err (bool*) The error flag. Accessed and set true if 'n' is negative,
   *            'values' is NULL/out of bounds, one of the given values is nan or
   *            an internal error occurs.
   * @returns (integer type denoted by suffix) The minimum value in the given set,
   *          or 0/NAN if an error occurs.
   * @note - If fp, comparisons are done using the ULP of the given values (same
   *         sign only).
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_min_i8(const int8_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int16_t tal_min_i16(const int16_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int32_t tal_min_i32(const int32_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int64_t tal_min_i64(const int64_t* const values, 
      const int32_t n, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_min_u8(const uint8_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_min_u16(const uint16_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_min_u32(const uint32_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_min_u64(const uint64_t* const values, 
      const int32_t n, bool* const err);

  tal_fn_attr_inline inline float tal_min_f(const float* const values,
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline double tal_min_d(const double* const values,
      const int32_t n, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_min2
   * @brief Gets the minimum of two integer values.
   * @param value_a (integer type denoted by suffix) The first value to query.
   * @param value_b (integer type denoted by suffix) The second value to query.
   * @returns (integer type denoted by suffix) The minimum of the two given values.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_min2_i8(const int8_t value_a, 
      const int8_t value_b);
  tal_fn_attr_inline inline int16_t tal_min2_i16(const int16_t value_a, 
      const int16_t value_b);
  tal_fn_attr_inline inline int32_t tal_min2_i32(const int32_t value_a, 
      const int32_t value_b);
  tal_fn_attr_inline inline int64_t tal_min2_i64(const int64_t value_a, 
      const int64_t value_b);

  tal_fn_attr_inline inline uint8_t tal_min2_u8(const uint8_t value_a, 
      const uint8_t value_b);
  tal_fn_attr_inline inline uint16_t tal_min2_u16(const uint16_t value_a,
      const uint16_t value_b);
  tal_fn_attr_inline inline uint32_t tal_min2_u32(const uint32_t value_a, 
      const uint32_t value_b);
  tal_fn_attr_inline inline uint64_t tal_min2_u64(const uint64_t value_a, 
      const uint64_t value_b);
  /** @} */

  /**
   * @defgroup fp tal_min2
   * @brief Gets the minimum of two floating point values.
   * @param value_a (floating point type denoted by suffix) The first value to query.
   * @param value_b (floating point type denoted by suffix) The second value to query.
   * @param err (bool*) The error flag. Accessed and set true if one of the given
   *            values is NAN or an internal error occurs.
   * @returns (floating point type denoted by suffix) The minimum of the two 
   *          given values, or NAN if an error occurs.
   * @note - Comparisons are done using the ULP of the given values (same sign only).
   * @{
   */
  tal_fn_attr_inline inline float tal_min2_f(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline double tal_min2_d(const double value_a,
      const double value_b, bool* const err);
  /** @} */

  /**
   * @defgroup tal_max
   * @brief Gets the maximum value contained in a set of values.
   * @param values (pointer to numeric type denoted by suffix) An array containing
   *               the values to query.
   * @param n (int32_t) The number of values in the given set.
   * @param err (bool*) The error flag. Accessed and set true if 'n' is negative,
   *            'values' is NULL/out of bounds, a value in the given set is NAN, 
   *            or an internal error occurs.
   * @returns (integer type denoted by suffix) The maximum value in the given set,
   *          or 0/NAN if an error occurs.
   * @note - If fp, comparisons are done using the ULP of the given values (same 
   *         sign only).
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_max_i8(const int8_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int16_t tal_max_i16(const int16_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int32_t tal_max_i32(const int32_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline int64_t tal_max_i64(const int64_t* const values, 
      const int32_t n, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_max_u8(const uint8_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_max_u16(const uint16_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_max_u32(const uint32_t* const values, 
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_max_u64(const uint64_t* const values, 
      const int32_t n, bool* const err);

  tal_fn_attr_inline inline float tal_max_f(const float* const values,
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline double tal_max_d(const double* const values,
      const int32_t n, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_max2
   * @brief Gets the maximum of two integer values.
   * @param value_a (integer type denoted by suffix) The first value to query.
   * @param value_b (integer type denoted by suffix) The second value to query.
   * @returns (integer type denoted by suffix) The maximum of the two given values.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_max2_i8(const int8_t value_a, 
      const int8_t value_b);
  tal_fn_attr_inline inline int16_t tal_max2_i16(const int16_t value_a, 
      const int16_t value_b);
  tal_fn_attr_inline inline int32_t tal_max2_i32(const int32_t value_a, 
      const int32_t value_b);
  tal_fn_attr_inline inline int64_t tal_max2_i64(const int64_t value_a, 
      const int64_t value_b);

  tal_fn_attr_inline inline uint8_t tal_max2_u8(const uint8_t value_a, 
      const uint8_t value_b);
  tal_fn_attr_inline inline uint16_t tal_max2_u16(const uint16_t value_a, 
      const uint16_t value_b);
  tal_fn_attr_inline inline uint32_t tal_max2_u32(const uint32_t value_a, 
      const uint32_t value_b);
  tal_fn_attr_inline inline uint64_t tal_max2_u64(const uint64_t value_a, 
      const uint64_t value_b);
  /** @} */

  /**
   * @defgroup fp tal_max2
   * @brief Gets the maximum of two floating point values.
   * @param value_a (floating point type denoted by suffix) The first value to query.
   * @param value_b (floating point type denoted by suffix) The second value to query.
   * @param err (bool*) The error flag. Accessed and set true if one of the given
   *            values is NAN or an internal error occurs.
   * @returns (floating point type denoted by suffix) The maximum of the two
   *          given values, or NAN if an error occurs.
   * @note - Comparisons are done using the ULP of the given values (same sign only).
   * @{
   */
  tal_fn_attr_inline inline float tal_max2_f(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline double tal_max2_d(const double value_a,
      const double value_b, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_clamp
   * @brief Clamps an integer value to a given range.
   * @param value (integer type denoted by suffix) The value to clamp.
   * @param bound_a (integer type denoted by suffix) The first bound of the range.
   * @param bound_b (integer type denoted by suffix) The second bound of the range.
   * @returns (integer type denoted by suffix) If 'value' is less than the
   *          minimum bound, the minimum bound is returned. If 'value' is
   *          greater than the maximum bound, the maximum bound is returned.
   *          Otherwise, 'value' is returned.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_clamp_i8(const int8_t value, 
      const int8_t bound_a, const int8_t bound_b);
  tal_fn_attr_inline inline int16_t tal_clamp_i16(const int16_t value, 
      const int16_t bound_a, const int16_t bound_b);
  tal_fn_attr_inline inline int32_t tal_clamp_i32(const int32_t value, 
      const int32_t bound_a, const int32_t bound_b);
  tal_fn_attr_inline inline int64_t tal_clamp_i64(const int64_t value, 
      const int64_t bound_a, const int64_t bound_b);

  tal_fn_attr_inline inline uint8_t tal_clamp_u8(const uint8_t value, 
      const uint8_t bound_a, const uint8_t bound_b);
  tal_fn_attr_inline inline uint16_t tal_clamp_u16(const uint16_t value, 
      const uint16_t bound_a, const uint16_t bound_b);
  tal_fn_attr_inline inline uint32_t tal_clamp_u32(const uint32_t value, 
      const uint32_t bound_a, const uint32_t bound_b);
  tal_fn_attr_inline inline uint64_t tal_clamp_u64(const uint64_t value, 
      const uint64_t bound_a, const uint64_t bound_b);
  /** @} */

  /**
   * @defgroup fp tal_clamp
   * @brief Clamps a floating-point value to a given range.
   * @param value (floating point type denoted by suffix) The value to clamp.
   * @param bound_a (floating point type denoted by suffix) The first bound of the range.
   * @param bound_b (floating point type denoted by suffix) The second bound of the range.
   * @param err (bool*) The error flag. Accessed and set true if any of the 
   *            given values are NAN or an internal error occurs.
   * @returns (floating point type denoted by suffix) If 'value' is less than the
   *          minimum bound, the minimum bound is returned. If 'value' is
   *          greater than the maximum bound, the maximum bound is returned. If
   *          an error occurs, NAN is returned. Otherwise, 'value' is returned.
   * @note - Comparisons are done using the ULP of the given values (same sign only).
   * @{
   */
  tal_fn_attr_inline inline float tal_clamp_f(const float value, 
      const float bound_a, const float bound_b, bool* const err);
  tal_fn_attr_inline inline double tal_clamp_d(const double value,
      const double bound_a, const double bound_b, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_in_range
   * @brief Determines if an integer value is within a given range.
   * @param value (integer type denoted by suffix) The value to query.
   * @param bound_a (integer type denoted by suffix) The first bound of the range.
   * @param bound_b (integer type denoted by suffix) The second bound of the range.
   * @returns (bool) True if 'value' is greater than or equal to the minimum
   *          bound and less than or equal to the maximum bound, or false
   *          otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_in_range_i8(const int8_t value, 
      const int8_t bound_a, const int8_t bound_b);
  tal_fn_attr_inline inline bool tal_in_range_i16(const int16_t value, 
      const int16_t bound_a, const int16_t bound_b);
  tal_fn_attr_inline inline bool tal_in_range_i32(const int32_t value, 
      const int32_t bound_a, const int32_t bound_b);
  tal_fn_attr_inline inline bool tal_in_range_i64(const int64_t value, 
      const int64_t bound_a, const int64_t bound_b);

  tal_fn_attr_inline inline bool tal_in_range_u8(const uint8_t value, 
      const uint8_t bound_a, const uint8_t bound_b);
  tal_fn_attr_inline inline bool tal_in_range_u16(const uint16_t value, 
      const uint16_t bound_a, const uint16_t bound_b);
  tal_fn_attr_inline inline bool tal_in_range_u32(const uint32_t value, 
      const uint32_t bound_a, const uint32_t bound_b);
  tal_fn_attr_inline inline bool tal_in_range_u64(const uint64_t value, 
      const uint64_t bound_a, const uint64_t bound_b);
  /** @} */

  /**
   * @defgroup fp tal_in_range
   * @brief Determines if a floating-point value is within a given range.
   * @param value (floating point type denoted by suffix) The value to query.
   * @param bound_a (floating point type denoted by suffix) The first bound of the range.
   * @param bound_b (floating point type denoted by suffix) The second bound of the range.
   * @param err (bool*) The error flag. Accessed and set true if any of the given
   *            values are NAN or an internal error occurs.
   * @returns (bool) True if no error occurs and 'value' is greater than or 
   *          equal to the minimum bound and less than or equal to the maximum 
   *          bound, or false otherwise.
   * @note - Comparisons are done using the ULP of the given values (same sign only).
   * @{
   */
  tal_fn_attr_inline inline bool tal_in_range_f(const float value, 
      const float bound_a, const float bound_b, bool* const err);
  tal_fn_attr_inline inline bool tal_in_range_d(const double value,
      const double bound_a, const double bound_b, bool* const err);
  /** @} */

  /**************************************************************************************************
   * @section Rounding Utilities
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

  tal_fn_attr_inline inline float tal_floor_f(const float value,
      const float multiple, bool* const err);
  tal_fn_attr_inline inline double tal_floor_d(const double value,
      const double multiple, bool* const err);

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

  tal_fn_attr_inline inline float tal_ceil_f(const float value,
      const float multiple, bool* const err);
  tal_fn_attr_inline inline double tal_ceil_d(const double value,
      const double multiple, bool* const err);

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

  tal_fn_attr_inline inline float tal_round_f(const float value,
      const float multiple, bool* const err);
  tal_fn_attr_inline inline float tal_round_d(const double value,
      const double multiple, bool* const err);

  tal_fn_attr_inline inline float tal_floorint_f(const float value,
      bool* const err);
  tal_fn_attr_inline inline double tal_floorint_d(const double value,
      bool* const err);

  tal_fn_attr_inline inline float tal_ceilint_f(const float value,
      bool* const err);
  tal_fn_attr_inline inline double tal_ceilint_d(const double value,
      bool* const err);
  
  tal_fn_attr_inline inline float tal_roundint_f(const float value,
      bool* const err);
  tal_fn_attr_inline inline double tal_roundint_d(const double value,
      bool* const err);

  /**************************************************************************************************
   * @section Safe Numeric Comparison Utilities
   **************************************************************************************************/

  /**
   * @defgroup tal_cmpe
   * @brief Safely determines if two numeric values are equal.
   * @param x_value (numeric type denoted by suffix of argument name and first
   *                suffix of function name) The first value to compare.
   * @param x_value (numeric type denoted by suffix of argument name and second
   *                suffix of function name) The second value to compare.
   * @param err (only if comparison involves floating-point type) (bool*) The 
   *            error flag. Accessed and set true if either of the given values 
   *            are NAN, or an internal error occurs
   * @returns True if no error occurs and the first given value is equal to the 
   *          second given value, or false otherwise.
   * @note - If the comparison involves a floating-point value, the two given
   *         values are considered equal if they are within one ULP of each other.
   * @{
   */

  /** @} */

  /**
   * @defgroup tal_cmpl
   * @brief Safely determines if one numeric value is less than another.
   * @param x_value (numeric type denoted by suffix of argument name and first
   *                suffix of function name) The first value to compare.
   * @param x_value (numeric type denoted by suffix of argument name and second
   *                suffix of function name) The second value to compare.
   * @param err (only if comparison involves floating-point type) (bool*) The
   *            error flag. Accessed and set true if either of the given values
   *            are NAN, or an internal error occurs
   * @returns True if no error occurs and the first given value is less than the
   *          second given value, or false otherwise.
   * @note - If the comparison involves a floating-point value, the first value
   *         is considered less than the second value if their difference is
   *         less than one ULP.
   * @{
   */



  /** @} */

  /**
   * @defgroup tal_cmpg
   * @brief Safely determines if one numeric value is greater then another.
   * @param x_value (numeric type denoted by suffix of argument name and first
   *                suffix of function name) The first value to compare.
   * @param x_value (numeric type denoted by suffix of argument name and second
   *                suffix of function name) The second value to compare.
   * @param err (only if comparison involves floating-point type) (bool*) The
   *            error flag. Accessed and set true if either of the given values
   *            are NAN, or an internal error occurs
   * @returns True if no error occurs and the first given value is greater than
   *          the second given value, or false otherwise.
   * @note - If the comparison involves a floating-point value, the first value
   *         is considered greater than the second value if their difference is
   *         greater than one ULP.
   * @{
   */



  /** @} */

  /**
   * @defgroup tal_cmple
   * @brief Safely determines if one numeric value is less than or equal to another.
   * @param x_value (numeric type denoted by suffix of argument name and first
   *                suffix of function name) The first value to compare.
   * @param x_value (numeric type denoted by suffix of argument name and second
   *                suffix of function name) The second value to compare.
   * @param err (only if comparison involves floating-point type) (bool*) The
   *            error flag. Accessed and set true if either of the given values
   *            are NAN, or an internal error occurs
   * @returns True if no error occurs and the first given value is less than or
   *          equal to the second given value, or false otherwise.
   * @note - If the comparison involves a floating-point value, the first value
   *         is considered less than or equal to the second value if their
   *         difference is less than or within one ULP.
   * @{
   */

  
  /** @} */

  /**
   * @defgroup tal_cmpge
   * @brief Safely determines if one numeric value is greater than or equal to another.
   * @param x_value (numeric type denoted by suffix of argument name and first
   *                suffix of function name) The first value to compare.
   * @param x_value (numeric type denoted by suffix of argument name and second
   *                suffix of function name) The second value to compare.
   * @param err (only if comparison involves floating-point type) (bool*) The
   *            error flag. Accessed and set true if either of the given values
   *            are NAN, or an internal error occurs
   * @returns True if no error occurs and the first given value is greater than
   *          or equal to the second given value, or false otherwise.
   * @note - If the comparison involves a floating-point value, the first value
   *         is considered greater than or equal to the second value if their
   *         difference is greater than or within one ULP.
   * @{
   */


  /** @} */

  /**************************************************************************************************
   * @section Checked/Saturating Arithmetic Operations
   **************************************************************************************************/

  /**
   * @paragraph FP Error Handling for Checked/Saturating Operations
   * The following functions (that involve floating point types) 
   * signal errors according to the floating point exceptions listed 
   * in the IEEE754 standard. A list of these exceptions can be found 
   * at the following link: 
   * https://www.gnu.org/software/libc/manual/html_node/FP-Exceptions.html
   */

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

  inline float tal_add_f(const float value_a,
      const float value_b, bool* const err);
  inline double tal_add_d(const double value_a,
      const double value_b, bool* const err);

  inline float tal_sub_f(const float value_a,
      const float value_b, bool* const err);
  inline double tal_sub_d(const double value_a,
      const double value_b, bool* const err);

  inline float tal_mul_f(const float value_a,
      const float value_b, bool* const err);
  inline double tal_mul_d(const double value_a,
      const double value_b, bool* const err);

  inline float tal_div_f(const float num,
      const float div, bool* const err);
  inline double tal_div_d(const double num,
      const double div, bool* const err);

  inline float tal_mod_f(const float num,
      const float den, bool* const err);
  inline double tal_mod_d(const double num,
      const double den, bool* const err);

  /**
   * @defgroup tal_cast
   * @brief Checked/saturating numeric cast operation.
   * @param value (numeric type denoted by END of suffix) The value to cast.
   * @param err (bool*) The error flag. Accessed and set true if 'value' is out of
   *            bounds of the destination type's range, if 'value' cannot be
   *            represented in the destination type (i.e. NAN -> int), or an
   *            internal error occurs. Note, this parameter is not present in
   *            the integer to floating point cast functions, since no error can
   *            occur durring that operation.
   * @returns (numeric type denoted by suffix) 'value' cast to the destination
   *          type, and clamped to it's min/max range, or 0/NAN if a non-overflow
   *          error occurs.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_cast_i8i(const int64_t value, 
      bool* const err);
  tal_fn_attr_inline inline int16_t tal_cast_i16i(const int64_t value, 
      bool* const err);
  tal_fn_attr_inline inline int32_t tal_cast_i32i(const int64_t value, 
      bool* const err);

  tal_fn_attr_inline inline int8_t tal_cast_i8u(const uint64_t value, 
      bool* const err);
  tal_fn_attr_inline inline int16_t tal_cast_i16u(const uint64_t value, 
      bool* const err);
  tal_fn_attr_inline inline int32_t tal_cast_i32u(const uint64_t value, 
      bool* const err);
  tal_fn_attr_inline inline int64_t tal_cast_i64u(const uint64_t value, 
      bool* const err);

  tal_fn_attr_inline inline uint8_t tal_cast_u8i(const int64_t value, 
      bool* const err);
  tal_fn_attr_inline inline uint16_t tal_cast_u16i(const int64_t value, 
      bool* const err);
  tal_fn_attr_inline inline uint32_t tal_cast_u32i(const int64_t value, 
      bool* const err);
  tal_fn_attr_inline inline uint64_t tal_cast_u64i(const int64_t value, 
      bool* const err);

  tal_fn_attr_inline inline uint8_t tal_cast_u8u(const uint64_t value, 
      bool* const err);
  tal_fn_attr_inline inline uint16_t tal_cast_u16u(const uint64_t value, 
      bool* const err);
  tal_fn_attr_inline inline uint32_t tal_cast_u32u(const uint64_t value, 
      bool* const err);

  tal_fn_attr_inline inline uint8_t tal_cast_u8f(const float value, 
      bool* const err);
  tal_fn_attr_inline inline uint16_t tal_cast_u16f(const float value,
      bool* const err);
  tal_fn_attr_inline inline uint32_t tal_cast_u32f(const float value,
      bool* const err);
  tal_fn_attr_inline inline uint64_t tal_cast_u64f(const float value,
      bool* const err);
  
  tal_fn_attr_inline inline int8_t tal_cast_i8f(const float value, 
      bool* const err);
  tal_fn_attr_inline inline int16_t tal_cast_i16f(const float value,
      bool* const err);
  tal_fn_attr_inline inline int32_t tal_cast_i32f(const float value,
      bool* const err);
  tal_fn_attr_inline inline int64_t tal_cast_i64f(const float value,
      bool* const err);
  
  tal_fn_attr_inline inline uint8_t tal_cast_u8d(const double value,
      bool* const err);
  tal_fn_attr_inline inline uint16_t tal_cast_u16d(const double value,
      bool* const err);
  tal_fn_attr_inline inline uint32_t tal_cast_u32d(const double value,
      bool* const err);
  tal_fn_attr_inline inline uint64_t tal_cast_u64d(const double value,
      bool* const err);

  tal_fn_attr_inline inline float tal_cast_fu(const uint64_t value);
  tal_fn_attr_inline inline float tal_cast_fi(const int64_t value);

  tal_fn_attr_inline inline double tal_cast_du(const uint64_t value);
  tal_fn_attr_inline inline double tal_cast_di(const int64_t value);
  /** @} */

  /**************************************************************************************************
   * @section Aggregate Arithmetic Operations
   **************************************************************************************************/

  /**
   * @defgroup tal_summation
   * @brief Checked/saturating summation (aggregate addition) operation.
   * @param values (pointer to numeric type denoted by suffix) Array of values.
   * @param n (int32_t) The number of values to sum (size of given array).
   * @param err (bool*) The error flag. Accessed and set true if 'n' is out of bounds,
   *            'values' is NULL/out of bounds, the operation overflows, an IEEE754
   *            floating point exception occurs, or an internal error occurs.
   * @returns (integer type denoted by suffix) The summation of the first 'n' 
   *          values in the given array, clamped to the range of the suffix type,
   *          or 0/NAN if a non-overflow error occurs.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_summation_i8(
      const int8_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline int16_t tal_summation_i16(
      const int16_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline int32_t tal_summation_i32(
      const int32_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline int64_t tal_summation_i64(
      const int64_t* const values, const int32_t n, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_summation_u8(
      const uint8_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_summation_u16(
      const uint16_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_summation_u32(
      const uint32_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_summation_u64(
      const uint64_t* const values, const int32_t n, bool* const err);

  tal_fn_attr_inline inline float tal_summation_f(
      const float* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline double tal_summation_d(
      const double* const values, const int32_t n, bool* const err);
  /** @} */

  /**
   * @defgroup tal_product
   * @brief Checked/saturating product (aggregate multiplication) operation.
   * @param values (pointer to numeric type denoted by suffix) Array of values.
   * @param n (int32_t) The number of values to multiply (size of given array).
   * @param err (bool*) The error flag. Accessed and set true if 'n' is out of bounds,
   *            'values' is NULL/out of bounds, the operation overflows, an IEEE754
   *            floating point exception occurs, or an internal error occurs.
   * @returns (integer type denoted by suffix) The product of the first 'n' 
   *          values in the given array, clamped to the range of the suffix type,
   *          or 0/NAN if a non-overflow error occurs.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_product_i8(
      const int8_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline int16_t tal_product_i16(
      const int16_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline int32_t tal_product_i32(
      const int32_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline int64_t tal_product_i64(
      const int64_t* const values, const int32_t n, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_product_u8(
      const uint8_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_product_u16(
      const uint16_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_product_u32(
      const uint32_t* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_product_u64(
      const uint64_t* const values, const int32_t n, bool* const err);

  tal_fn_attr_inline inline float tal_product_f(
      const float* const values, const int32_t n, bool* const err);
  tal_fn_attr_inline inline double tal_product_d(
      const double* const values, const int32_t n, bool* const err);
  /** @} */



  /**************************************************************************************************
   * @internal Implementation of Core Numeric Utilities
   **************************************************************************************************/

  int8_t tal_copy_sign_i8(const int8_t mag, const int8_t sgn,
      bool* const err) {
    return sgn < 0 != mag < 0 ? tal_neg_i8(mag, err) : mag;
  }

  int16_t tal_copy_sign_i16(const int16_t mag, const int16_t sgn,
      bool* const err) {
    return sgn < 0 != mag < 0 ? tal_neg_i16(mag, err) : mag;
  }

  int32_t tal_copy_sign_i32(const int32_t mag, const int32_t sgn,
      bool* const err) {
    return sgn < 0 != mag < 0 ? tal_neg_i32(mag, err) : mag;
  }

  int64_t tal_copy_sign_i64(const int64_t mag, const int64_t sgn,
      bool* const err) {
    return sgn < 0 != mag < 0 ? tal_neg_i64(mag, err) : mag;
  }

  float tal_copy_sign_f(const float mag, const float sgn) {
    const bool s_sign = tal_sign_bit_f(sgn);
    const bool m_sign = tal_sign_bit_f(mag);
    return s_sign != m_sign ? tal_neg_f(mag) : mag;
  }

  double tal_copy_sign_d(const double mag, const double sgn) {
    const bool s_sign = tal_sign_bit_d(sgn);
    const bool m_sign = tal_sign_bit_d(mag);
    return s_sign != m_sign ? tal_neg_d(mag) : mag; 
  }

  int8_t tal_abs_i8(const int8_t value, bool* const err) {    
    return value < 0 ? tal_neg_i8(value, err) : value;
  }

  int16_t tal_abs_i16(const int16_t value, bool* const err) { 
    return value < 0 ? tal_neg_i16(value, err) : value;
  }

  int32_t tal_abs_i32(const int32_t value, bool* const err) { 
    return value < 0 ? tal_neg_i32(value, err) : value;
  }

  int64_t tal_abs_i64(const int64_t value, bool* const err) { 
    return value < 0 ? tal_neg_i64(value, err) : value;
  }

  float tal_abs_f(const float value) {
    return tal_sign_bit_f(value) ? tal_neg_f(value) : value;
  }

  double tal_abs_d(const double value) {
    return tal_sign_bit_d(value) ? tal_neg_d(value) : value;
  }

  int8_t tal_min_i8(const int8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0  || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int8_t)))) {
      *err = true;
      return 0;
    }
    int8_t min = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] < min) { min = values[i]; }
    }
    return min;
  }

  int16_t tal_min_i16(const int16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int16_t)))) {
      *err = true;
      return 0;
    }
    int16_t min = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] < min) { min = values[i]; }
    }
    return min;
  }

  int32_t tal_min_i32(const int32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int32_t)))) {
      *err = true;
      return 0;
    }
    int32_t min = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] < min) { min = values[i]; }
    }
    return min;
  }

  int64_t tal_min_i64(const int64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int64_t)))) {
      *err = true;
      return 0;
    }
    int64_t min = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] < min) { min = values[i]; }
    }
    return min;
  }

  uint8_t tal_min_u8(const uint8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint8_t)))) {
      *err = true;
      return 0u;
    }
    uint8_t min = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] < min) { min = values[i]; }
    }
    return min;
  }

  uint16_t tal_min_u16(const uint16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint16_t)))) {
      *err = true;
      return 0u;
    }
    uint16_t min = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] < min) { min = values[i]; }
    }
    return min;
  }

  uint32_t tal_min_u32(const uint32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint32_t)))) {
      *err = true;
      return 0u;
    }
    uint32_t min = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] < min) { min = values[i]; }
    }
    return min;
  }

  uint64_t tal_min_u64(const uint64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint64_t)))) {
      *err = true;
      return 0u;
    }
    uint64_t min = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] < min) { min = values[i]; }
    }
    return min;
  }

  float tal_min_f(const float* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(float)))) {
      *err = true;
      return tal_nan_f();
    }
    float min = tal_nan_f();
    for (int32_t i = 0; i < n; ++i) {
      if (tal_is_nan_f(min) || tal_cmpl_ff(values[i], min, err)) {
        min = values[i];
      }
    }
    return min;
  }

  double tal_min_d(const double* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(float)))) {
      *err = true;
      return tal_nan_d();
    }
    double min = tal_nan_d();
    for (int32_t i = 0; i < n; ++i) {
      if (tal_is_nan_d(min) || tal_cmpl_dd(values[i], min, err)) {
        min = values[i];
      }
    }
    return min;
  }

  int8_t tal_min2_i8(const int8_t value_a, const int8_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  int16_t tal_min2_i16(const int16_t value_a, const int16_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  int32_t tal_min2_i32(const int32_t value_a, const int32_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  int64_t tal_min2_i64(const int64_t value_a, const int64_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  uint8_t tal_min2_u8(const uint8_t value_a, const uint8_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  uint16_t tal_min2_u16(const uint16_t value_a, const uint16_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  uint32_t tal_min2_u32(const uint32_t value_a, const uint32_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  uint64_t tal_min2_u64(const uint64_t value_a, const uint64_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  float tal_min2_f(const float value_a, const float value_b,
      bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b)) {
      *err = true;
      return tal_nan_f();
    }
    return tal_cmpl_ff(value_a, value_b, NULL) ? value_a : value_b;
  }

  double tal_min2_d(const double value_a, const double value_b,
      bool* const err) {
    if (tal_is_nan_d(value_a) || tal_is_nan_d(value_b)) {
      *err = true;
      return tal_nan_d();
    }
    return tal_cmpl_dd(value_a, value_b, NULL) ? value_a : value_b;
  }

  int8_t tal_max_i8(const int8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int8_t)))) {
      *err = true;
      return 0;
    }
    int8_t max = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] > max) { max = values[i]; }
    }
    return max;
  }

  int16_t tal_max_i16(const int16_t* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int16_t)))) {
      *err = true;
      return 0;
    }
    int16_t max = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] > max) { max = values[i]; }
    }
    return max;
  }

  int32_t tal_max_i32(const int32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int32_t)))) {
      *err = true;
      return 0;
    }
    int32_t max = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] > max) { max = values[i]; }
    }
    return max;
  }

  int64_t tal_max_i64(const int64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int64_t)))) {
      *err = true;
      return 0;
    }
    int64_t max = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] > max) { max = values[i]; }
    }
    return max;
  }

  uint8_t tal_max_u8(const uint8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint8_t)))) {
      *err = true;
      return 0u;
    }
    uint8_t max = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] > max) { max = values[i]; }
    }
    return max;
  }

  uint16_t tal_max_u16(const uint16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint16_t)))) {
      *err = true;
      return 0u;
    }
    uint16_t max = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] > max) { max = values[i]; }
    }
    return max;
  }

  uint32_t tal_max_u32(const uint32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint32_t)))) {
      *err = true;
      return 0u;
    }
    uint32_t max = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] > max) { max = values[i]; }
    }
    return max;
  }

  uint64_t tal_max_u64(const uint64_t* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint64_t)))) {
      *err = true;
      return 0u;
    }
    uint64_t max = *values;
    for (int32_t i = 1; i < n; ++i) {
      if (values[i] > max) { max = values[i]; }
    }
    return max;
  }

  float tal_max_f(const float* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(float)))) {
      *err = true;
      return tal_nan_f();
    }
    float max = tal_nan_f();
    for (int32_t i = 0; i < n; ++i) {
      if (tal_is_nan_f(max) || tal_cmpg_ff(values[i], max, err)) {
        max = values[i];
      }
    }
    return max;
  }

  double tal_max_d(const double* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(double)))) {
      *err = true;
      return tal_nan_d();
    }
    double max = tal_nan_d();
    for (int32_t i = 0; i < n; ++i) {
      if (tal_is_nan_d(max) || tal_cmpg_dd(values[i], max, err)) {
        max = values[i];
      }
    }
    return max;
  }

  int8_t tal_max2_i8(const int8_t value_a, const int8_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  int16_t tal_max2_i16(const int16_t value_a, const int16_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  int32_t tal_max2_i32(const int32_t value_a, const int32_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  int64_t tal_max2_i64(const int64_t value_a, const int64_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  uint8_t tal_max2_u8(const uint8_t value_a, const uint8_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  uint16_t tal_max2_u16(const uint16_t value_a, const uint16_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  uint32_t tal_max2_u32(const uint32_t value_a, const uint32_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  uint64_t tal_max2_u64(const uint64_t value_a, const uint64_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  float tal_max2_f(const float value_a, const float value_b,
      bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b)) {
      *err = true;
      return tal_nan_f();
    }
    return tal_cmpg_ff(value_a, value_b, NULL) ? value_a : value_b;
  }

  double tal_max2_d(const double value_a, const double value_b,
      bool* const err) {
    if (tal_is_nan_d(value_a) || tal_is_nan_d(value_b)) {
      *err = true;
      return tal_nan_d();
    }
    return tal_cmpg_dd(value_a, value_b, NULL) ? value_a : value_b;
  }

  int8_t tal_clamp_i8(const int8_t value, const int8_t bound_a, 
      const int8_t bound_b) {
    if (bound_a > bound_b) {
      if (value > bound_a) { return bound_a; } 
      if (value < bound_b) { return bound_b; }
    } else {
      if (value > bound_b) { return bound_b; }
      if (value < bound_a) { return bound_a; }
    }
    return value;
  }

  int16_t tal_clamp_i16(const int16_t value, const int16_t bound_a,
      const int16_t bound_b) {
    if (bound_a > bound_b) {
      if (value > bound_a) { return bound_a; } 
      if (value < bound_b) { return bound_b; }
    } else {
      if (value > bound_b) { return bound_b; }
      if (value < bound_a) { return bound_a; }
    }
    return value;
  }

  int32_t tal_clamp_i32(const int32_t value, const int32_t bound_a, 
      const int32_t bound_b) {
    if (bound_a > bound_b) {
      if (value > bound_a) { return bound_a; } 
      if (value < bound_b) { return bound_b; }
    } else {
      if (value > bound_b) { return bound_b; }
      if (value < bound_a) { return bound_a; }
    }
    return value;
  }

  int64_t tal_clamp_i64(const int64_t value, const int64_t bound_a, 
      const int64_t bound_b) {
    if (bound_a > bound_b) {
      if (value > bound_a) { return bound_a; } 
      if (value < bound_b) { return bound_b; }
    } else {
      if (value > bound_b) { return bound_b; }
      if (value < bound_a) { return bound_a; }
    }
    return value;
  }

  uint8_t tal_clamp_u8(const uint8_t value, const uint8_t bound_a, 
      const uint8_t bound_b) {
    if (bound_a > bound_b) {
      if (value > bound_a) { return bound_a; } 
      if (value < bound_b) { return bound_b; }
    } else {
      if (value > bound_b) { return bound_b; }
      if (value < bound_a) { return bound_a; }
    }
    return value;
  }

  uint16_t tal_clamp_u16(const uint16_t value, const uint16_t bound_a, 
      const uint16_t bound_b) {
    if (bound_a > bound_b) {
      if (value > bound_a) { return bound_a; } 
      if (value < bound_b) { return bound_b; }
    } else {
      if (value > bound_b) { return bound_b; }
      if (value < bound_a) { return bound_a; }
    }
    return value;
  }

  uint32_t tal_clamp_u32(const uint32_t value, const uint32_t bound_a, 
      const uint32_t bound_b) {
    if (bound_a > bound_b) {
      if (value > bound_a) { return bound_a; } 
      if (value < bound_b) { return bound_b; }
    } else {
      if (value > bound_b) { return bound_b; }
      if (value < bound_a) { return bound_a; }
    }
    return value;
  }

  uint64_t tal_clamp_u64(const uint64_t value, const uint64_t bound_a, 
      const uint64_t bound_b) {
    if (bound_a > bound_b) {
      if (value > bound_a) { return bound_a; } 
      if (value < bound_b) { return bound_b; }
    } else {
      if (value > bound_b) { return bound_b; }
      if (value < bound_a) { return bound_a; }
    }
    return value;
  }

  float tal_clamp_f(const float value, const float bound_a,
      const float bound_b, bool* const err) {
    if (tal_is_nan_f(bound_a) || tal_is_nan_f(bound_b) ||
        tal_is_nan_f(value)) {
      *err = true;
      return tal_nan_f();
    }
    if (tal_cmpl_ff(bound_a, bound_b, NULL)) {
      if (tal_cmpl_ff(value, bound_a, NULL)) { return bound_a; }
      if (tal_cmpg_ff(value, bound_b, NULL)) { return bound_b; }
    } else {
      if (tal_cmpl_ff(value, bound_b, NULL)) { return bound_b; }
      if (tal_cmpg_ff(value, bound_a, NULL)) { return bound_a; }
    }
    return value;
  }

  double tal_clamp_d(const double value, const double bound_a,
      const double bound_b, bool* const err) {
    if (tal_is_nan_d(bound_a) || tal_is_nan_d(bound_b) ||
        tal_is_nan_d(value)) {
      *err = true;
      return tal_nan_d();
    }
    if (tal_cmpl_dd(bound_a, bound_b, NULL)) {
      if (tal_cmpl_dd(value, bound_a, NULL)) { return bound_a; }
      if (tal_cmpg_dd(value, bound_b, NULL)) { return bound_b; }
    } else {
      if (tal_cmpl_dd(value, bound_b, NULL)) { return bound_b; }
      if (tal_cmpg_dd(value, bound_a, NULL)) { return bound_a; }
    }
    return value;
  }

  bool tal_in_range_i8(const int8_t value, const int8_t bound_a, 
      const int8_t bound_b) {
    if (bound_a > bound_b) {
      return value <= bound_a && value >= bound_b;
    } else {
      return value <= bound_b && value >= bound_a;
    }
  }

  bool tal_in_range_i16(const int16_t value, const int16_t bound_a, 
      const int16_t bound_b) {
    if (bound_a > bound_b) {
      return value <= bound_a && value >= bound_b;
    } else {
      return value <= bound_b && value >= bound_a;
    }
  }

  bool tal_in_range_i32(const int32_t value, const int32_t bound_a, 
      const int32_t bound_b) {
    if (bound_a > bound_b) {
      return value <= bound_a && value >= bound_b;
    } else {
      return value <= bound_b && value >= bound_a;
    }
  }

  bool tal_in_range_i64(const int64_t value, const int64_t bound_a, 
      const int64_t bound_b) {
    if (bound_a > bound_b) {
      return value <= bound_a && value >= bound_b;
    } else {
      return value <= bound_b && value >= bound_a;
    }
  }

  bool tal_in_range_u8(const uint8_t value, const uint8_t bound_a, 
      const uint8_t bound_b) {
    if (bound_a > bound_b) {
      return value <= bound_a && value >= bound_b;
    } else {
      return value <= bound_b && value >= bound_a;
    }
  }

  bool tal_in_range_u16(const uint16_t value, const uint16_t bound_a, 
      const uint16_t bound_b) {
    if (bound_a > bound_b) {
      return value <= bound_a && value >= bound_b;
    } else {
      return value <= bound_b && value >= bound_a;
    }
  }

  bool tal_in_range_u32(const uint32_t value, const uint32_t bound_a, 
      const uint32_t bound_b) {
    if (bound_a > bound_b) {
      return value <= bound_a && value >= bound_b;
    } else {
      return value <= bound_b && value >= bound_a;
    }
  }

  bool tal_in_range_u64(const uint64_t value, const uint64_t bound_a, 
      const uint64_t bound_b) {
    if (bound_a > bound_b) {
      return value <= bound_a && value >= bound_b;
    } else {
      return value <= bound_b && value >= bound_a;
    }
  }

  bool tal_in_range_f(const float value, const float bound_a, 
      const float bound_b, bool* const err) {
    if (tal_cmpl_ff(bound_a, bound_b, err)) {
      return tal_cmpl_ff(value, bound_a, err) && 
          tal_cmpg_ff(value, bound_b, err);
    } else {
      return tal_cmpl_ff(value, bound_b, err) && 
          tal_cmpg_ff(value, bound_a, err);
    }
  }

  bool tal_in_range_d(const double value, const double bound_a, 
      const double bound_b, bool* const err) {
    if (tal_cmpl_dd(bound_a, bound_b, err)) {
      return tal_cmpl_dd(value, bound_a, err) && 
          tal_cmpg_dd(value, bound_b, err);
    } else {
      return tal_cmpl_dd(value, bound_b, err) && 
          tal_cmpg_dd(value, bound_a, err);
    }
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
   * @internal Implementation of Safe Numeric Comparison Utilities
   **************************************************************************************************/

  bool tal_cmpe_iu(const int64_t i_value, const uint64_t u_value) {
    if (i_value < 0) { return false; }
    return (uint64_t)i_value == u_value;
  }
  
  bool tal_cmpe_ui(const uint64_t u_value, const int64_t i_value) {
    return tal_cmpe_iu(i_value, u_value);
  }

  bool tal_cmpe_fu(const float f_value, const uint64_t u_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value)) { 
      *err = true;
      return false; 
    }
    if (tal_is_inf_f(f_value)) { 
      return false; 
    }
    if (tal_sign_bit_f(f_value)) {
      return u_value == 0 && f_value == 0.0f;
    }
    const float f_u_value = (float)u_value;
    const float tot_ulp = tal_ulp_f(f_u_value) + tal_ulp_f(f_value);
    return tal_abs_f(f_value - f_u_value) <= tot_ulp;
  }

  bool tal_cmpe_uf(const uint64_t u_value, const float f_value, 
      bool* const err) {
    return tal_cmpe_fu(f_value, u_value, err);
  }

  bool tal_cmpe_du(const double d_value, const uint64_t u_value, 
      bool* const err) {
    if (tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_d(d_value)) {
      return false;
    }
    if (tal_sign_bit_d(d_value)) {
      return u_value == 0 && d_value == 0.0f;
    }
    const double d_u_value = (double)u_value;
    const double tot_ulp = tal_ulp_d(d_u_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_value - d_u_value) <= tot_ulp;
  }

  bool tal_cmpe_ud(const uint64_t u_value, const double d_value, 
      bool* const err) {
    return tal_cmpe_du(d_value, u_value, err);
  }

  bool tal_cmpe_fi(const float f_value, const int64_t i_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(f_value)) {
      return false;
    }
    if (tal_sign_bit(i_value) != (i_value < 0)) {
      return false;
    }
    const float f_i_value = (float)i_value;
    const float tot_ulp = tal_ulp_f(f_i_value) + tal_ulp_f(f_value);
    return tal_abs_f(f_value - f_i_value) <= tot_ulp;
  }

  bool tal_cmpe_if(const int64_t i_value, const float f_value, 
      bool* const err) {
    return tal_cmpe_fi(f_value, i_value, err);
  }

  bool tal_cmpe_di(const double d_value, const int64_t i_value, 
      bool* const err) {
    if (tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_d(d_value)) {
      return false;
    }
    if (tal_sign_bit(i_value) != (i_value < 0)) {
      return false;
    }
    const double d_i_value = (double)i_value;
    const double tot_ulp = tal_ulp_d(d_i_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_value - d_i_value) <= tot_ulp;
  }

  bool tal_cmpe_id(const int64_t i_value, const double d_value, 
      bool* const err) {
    return tal_cmpe_di(d_value, i_value, err);
  }

  bool tal_cmpe_fd(const float f_value, const double d_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value) || tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(f_value) || tal_is_inf_d(d_value)) {
      return f_value == d_value;
    }
    if (tal_sign_bit_f(f_value) != tal_sign_bit_d(d_value)) {
      return false;
    }
    const double d_f_value = (double)f_value;
    const double tot_ulp = tal_ulp_d(d_f_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_value - d_f_value) <= tot_ulp;
  }

  bool tal_cmpe_df(const double d_value, const float f_value, 
      bool* const err) {
    return tal_cmpe_fd(f_value, d_value, err);
  }

  bool tal_cmpe_ff(const float value_a, const float value_b, 
      bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(value_a) || tal_is_inf_f(value_b)) {
      return value_a == value_b;
    }
    if (tal_sign_bit_f(value_a) != tal_sign_bit_f(value_b)) {
      return false;
    }
    const float tot_ulp = tal_ulp_f(value_a) + tal_ulp_f(value_b);
    return tal_abs_f(value_a - value_b) <= tot_ulp;
  }

  bool tal_cmpe_dd(const double value_a, const double value_b, 
      bool* const err) {
    if (tal_is_nan_d(value_a) || tal_is_nan_d(value_b)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_d(value_a) || tal_is_inf_d(value_b)) {
      return value_a == value_b;
    }
    if (tal_sign_bit_d(value_a) != tal_sign_bit_d(value_b)) {
      return false;
    }
    const double tot_ulp = tal_ulp_d(value_a) + tal_ulp_d(value_b);
    return tal_abs_d(value_a - value_b) <= tot_ulp;
  }

  bool tal_cmpl_iu(const int64_t i_value, const uint64_t u_value) {
    if (i_value < 0) { return true; }
    return (uint64_t)i_value < u_value;
  }

  bool tal_cmpl_ui(const uint64_t u_value, const int64_t i_value) {
    if (i_value < 0) { return false; }
    return u_value < (uint64_t)i_value;
  }

  bool tal_cmpl_fu(const float f_value, const uint64_t u_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(f_value)) {
      return tal_sign_bit_f(f_value);
    }
    if (tal_sign_bit_f(f_value)) {
      return false;
    }
    const float f_u_value = (float)u_value;
    const float tot_ulp = tal_ulp_f(f_u_value) + tal_ulp_f(f_value);
    return tal_abs_f(f_u_value - f_value) >= tot_ulp;
    
  }

  bool tal_cmpl_uf(const uint64_t u_value, const float f_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(f_value)) {
      return !tal_sign_bit_f(f_value);
    }
    if (tal_sign_bit_f(f_value)) {
      return true;
    }
    const float f_u_value = (float)u_value;
    const float tot_ulp = tal_ulp_f(f_u_value) + tal_ulp_f(f_value);
    return tal_abs_f(f_value - f_u_value) >= tot_ulp;
  }

  bool tal_cmpl_du(const double d_value, const uint64_t u_value, 
      bool* const err) {
    if (tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_d(d_value)) {
      return tal_sign_bit(d_value);
    }
    if (tal_sign_bit_d(d_value)) {
      return false;
    }
    const double d_u_value = (double)u_value;
    const double tot_ulp = tal_ulp_d(d_u_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_u_value - d_value) >= tot_ulp;
  }

  bool tal_cmpl_ud(const uint64_t u_value, const double d_value, 
      bool* const err) {
    if (tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_d(d_value)) {
      return !tal_sign_bit_d(d_value);
    }
    if (tal_sign_bit_d(d_value)) {
      return true;
    }
    const double d_u_value = (double)u_value;
    const double tot_ulp = tal_ulp_d(d_u_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_value - d_u_value) >= tot_ulp;
  }

  bool tal_cmpl_fi(const float f_value, const int64_t i_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(f_value)) {
      return tal_sign_bit_f(f_value);
    }
    if (tal_sign_bit_f(f_value) != (i_value < 0)) {
      return tal_sign_bit_f(f_value);
    }
    const float f_i_value = (float)i_value;
    const float tot_ulp = tal_ulp_f(f_i_value) + tal_ulp_f(f_value);
    return tal_abs_f(f_i_value - f_value) >= tot_ulp;
  }

  bool tal_cmpl_if(const int64_t i_value, const float f_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(f_value)) {
      return !tal_sign_bit_f(f_value);
    }
    if (tal_sign_bit_f(f_value) != (i_value < 0)) {
      return !tal_sign_bit_f(f_value);
    }
    const float f_i_value = (float)i_value;
    const float tot_ulp = tal_ulp_f(f_i_value) + tal_ulp_f(f_value);
    return tal_abs_f(f_value - f_i_value) >= tot_ulp;
  }

  bool tal_cmpl_di(const double d_value, const int64_t i_value, 
      bool* const err) {
    if (tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_d(d_value)) {
      return tal_sign_bit_d(d_value);
    }
    if (tal_sign_bit_d(d_value) != (i_value < 0)) {
      return tal_sign_bit_d(d_value);
    }
    const double d_i_value = (double)i_value;
    const double tot_ulp = tal_ulp_d(d_i_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_i_value - d_value) >= tot_ulp;
  }

  bool tal_cmpl_id(const int64_t i_value, const double d_value, 
      bool* const err) {
    if (tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_d(d_value)) {
      return !tal_sign_bit_d(d_value);
    }
    if (tal_sign_bit_d(d_value) != (i_value < 0)) {
      return !tal_sign_bit_d(d_value);
    }
    const double d_i_value = (double)i_value;
    const double tot_ulp = tal_ulp_d(d_i_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_value - d_i_value) >= tot_ulp;
  }

  bool tal_cmpl_fd(const float f_value, const double d_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value) || tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(f_value) || tal_is_inf_d(d_value)) {
      return f_value < d_value;
    }
    if (tal_sign_bit_f(f_value) != tal_sign_bit_d(d_value)) {
      return tal_sign_bit_f(f_value);
    }
    const double d_f_value = (double)f_value;
    const double tot_ulp = tal_ulp_d(d_f_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_f_value - d_value) >= tot_ulp;
  }

  bool tal_cmpl_df(const double d_value, const float f_value, 
      bool* const err) {
    if (tal_is_nan_f(f_value) || tal_is_nan_d(d_value)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(f_value) || tal_is_inf_d(d_value)) {
      return d_value < f_value;
    }
    if (tal_sign_bit_f(f_value) != tal_sign_bit_d(d_value)) {
      return tal_sign_bit_d(d_value);
    }
    const double d_f_value = (double)f_value;
    const double tot_ulp = tal_ulp_d(d_f_value) + tal_ulp_d(d_value);
    return tal_abs_d(d_value - d_f_value) >= tot_ulp;
  }

  bool tal_cmpl_ff(const float value_a, const float value_b, 
      bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(value_a) || tal_is_inf_f(value_b)) {
      return value_a < value_b;
    }
    if (tal_sign_bit_f(value_a) != tal_sign_bit_f(value_b)) {
      return tal_sign_bit_f(value_a);
    }
    const double tot_ulp = tal_ulp_f(value_a) + tal_ulp_f(value_b);
    return tal_abs_f(value_a - value_b) >= tot_ulp;
  }

  bool tal_cmpl_dd(const double value_a, const double value_b, 
      bool* const err) {
    if (tal_is_nan_d(value_a) || tal_is_nan_d(value_b)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_d(value_a) || tal_is_inf_d(value_b)) {
      return value_a < value_b;
    }
    if (tal_sign_bit_d(value_a) != tal_sign_bit_d(value_b)) {
      return tal_sign_bit_d(value_a);
    }
    const double tot_ulp = tal_ulp_d(value_a) + tal_ulp_d(value_b);
    return tal_abs_d(value_a - value_b) >= tot_ulp;
  }

  bool tal_cmpg_iu(const int64_t i_value, const uint64_t u_value) {
    return tal_cmpl_ui(u_value, i_value);
  }

  bool tal_cmpg_ui(const uint64_t u_value, const int64_t i_value) {
    return tal_cmpl_iu(i_value, u_value);
  }

  bool tal_cmpg_fu(const float f_value, const uint64_t u_value, 
      bool* const err) {
    return tal_cmpl_uf(u_value, f_value, err);
  }

  bool tal_cmpg_uf(const uint64_t u_value, const float f_value, 
      bool* const err) {
    return tal_cmpl_fu(f_value, u_value, err);
  }

  bool tal_cmpg_du(const double d_value, const uint64_t u_value, 
      bool* const err) {
    return tal_cmpl_ud(u_value, d_value, err);
  }

  bool tal_cmpg_ud(const uint64_t u_value, const double d_value, 
      bool* const err) {
    return tal_cmpl_du(d_value, u_value, err);
  }

  bool tal_cmpg_fi(const float f_value, const int64_t i_value, 
      bool* const err) {
    return tal_cmpl_if(i_value, f_value, err);
  }

  bool tal_cmpg_if(const int64_t i_value, const float f_value, 
      bool* const err) {
    return tal_cmpl_fi(f_value, i_value, err);
  }

  bool tal_cmpg_di(const double d_value, const int64_t i_value, 
      bool* const err) {
    return tal_cmpg_id(i_value, d_value, err);
  }

  bool tal_cmpg_id(const int64_t i_value, const double d_value, 
      bool* const err) {
    return tal_cmpg_di(d_value, i_value, err);
  }

  bool tal_cmpg_fd(const float f_value, const double d_value, 
      bool* const err) {
    return tal_cmpg_df(d_value, f_value, err);
  }

  bool tal_cmpg_df(const double d_value, const float f_value, 
      bool* const err) {
    return tal_cmpl_fd(f_value, d_value, err);
  }

  bool tal_cmpg_ff(const float value_a, const float value_b, 
      bool* const err) {
    return tal_cmpg_ff(value_b, value_a, err);
  }

  bool tal_cmpg_dd(const double value_a, const double value_b, 
      bool* const err) {
    return tal_cmpg_dd(value_b, value_a, err);
  }

  bool tal_cmple_iu(const int64_t i_value, const uint64_t u_value) {
    return !tal_cmpl_ui(u_value, i_value);
  }

  bool tal_cmple_ui(const uint64_t u_value, const int64_t i_value) {
    return !tal_cmpl_iu(i_value, u_value);
  } 
  
  bool tal_cmple_fu(const float f_value, const uint64_t u_value, 
      bool* const err) {
    return !tal_cmpl_uf(u_value, f_value, err);
  }

  bool tal_cmple_uf(const uint64_t u_value, const float f_value, 
      bool* const err) {
    return !tal_cmpl_fu(f_value, u_value, err);
  }

  bool tal_cmple_du(const double d_value, const uint64_t u_value, 
      bool* const err) {
    return !tal_cmpl_ud(u_value, d_value, err);
  }

  bool tal_cmple_ud(const uint64_t u_value, const double d_value, 
      bool* const err) {
    return !tal_cmpl_du(d_value, u_value, err);
  }

  bool tal_cmple_fi(const float f_value, const int64_t i_value, 
      bool* const err) {
    return !tal_cmpl_if(i_value, f_value, err);
  }

  bool tal_cmple_if(const int64_t i_value, const float f_value, 
      bool* const err) {
    return !tal_cmpl_fi(f_value, i_value, err);
  }

  bool tal_cmple_di(const double d_value, const int64_t i_value, 
      bool* const err) {
    return !tal_cmpl_id(i_value, d_value, err);
  }

  bool tal_cmple_id(const int64_t i_value, const double d_value, 
      bool* const err) {
    return !tal_cmpl_di(d_value, i_value, err);
  }

  bool tal_cmple_fd(const float f_value, const double d_value, 
      bool* const err) {
    return !tal_cmpl_df(d_value, f_value, err);
  }

  bool tal_cmple_df(const double d_value, const float f_value, 
      bool* const err) {
    return !tal_cmpl_fd(f_value, d_value, err);
  }

  bool tal_cmple_ff(const float value_a, const float value_b, 
      bool* const err) {
    return !tal_cmpg_ff(value_b, value_a, err);
  }

  bool tal_cmple_dd(const double value_a, const double value_b, 
      bool* const err) {
    return !tal_cmpg_dd(value_b, value_a, err);
  }

  bool tal_cmpge_iu(const int64_t i_value, const uint64_t u_value) {
    return !tal_cmpl_iu(i_value, u_value);
  }

  bool tal_cmpge_ui(const uint64_t u_value, const int64_t i_value) {
    return !tal_cmpl_ui(u_value, i_value);
  }

  bool tal_cmpge_fu(const float f_value, const uint64_t u_value, 
      bool* const err) {
    return !tal_cmpl_fu(f_value, u_value, err);        
  }

  bool tal_cmpge_uf(const uint64_t u_value, const float f_value, 
      bool* const err) {
    return !tal_cmpl_uf(u_value, f_value, err);
  }

  bool tal_cmpge_du(const double d_value, const uint64_t u_value, 
      bool* const err) {
    return !tal_cmpl_du(d_value, u_value, err);
  }

  bool tal_cmpge_ud(const uint64_t u_value, const double d_value, 
      bool* const err) {
    return !tal_cmpl_ud(u_value, d_value, err);
  }

  bool tal_cmpge_fi(const float f_value, const int64_t i_value, 
      bool* const err) {
    return !tal_cmpl_fi(f_value, i_value, err);
  }

  bool tal_cmpge_if(const int64_t i_value, const float f_value, 
      bool* const err) {
    return !tal_cmpl_if(i_value, f_value, err);
  }

  bool tal_cmpge_di(const double d_value, const int64_t i_value, 
      bool* const err) {
    return !tal_cmpl_di(d_value, i_value, err);
  }

  bool tal_cmpge_id(const int64_t i_value, const double d_value, 
      bool* const err) {
    return !tal_cmpl_id(i_value, d_value, err);
  }

  bool tal_cmpge_fd(const float f_value, const double d_value, 
      bool* const err) {
    return !tal_cmpl_fd(f_value, d_value, err);
  }

  bool tal_cmpge_df(const double d_value, const float f_value, 
      bool* const err) {
    return !tal_cmpl_df(d_value, f_value, err);
  }

  bool tal_cmpge_ff(const float value_a, const float value_b, 
      bool* const err) {
    return !tal_cmpl_ff(value_a, value_b, err);
  }

  bool tal_cmpge_dd(const double value_a, const double value_b, 
      bool* const err) {
    return !tal_cmpl_dd(value_a, value_b, err);
  }

  /**************************************************************************************************
   * @internal Implementation of Checked/Saturating Arithmetic Operations
   **************************************************************************************************/

  int8_t tal_neg_i8(const int8_t value, bool* const err) {
    #if (tal_env_signrep == tal_signrep_2compl_v)
      if (value == INT8_MIN) {
        *err = true;
        return INT8_MIN;
      }
    #elif (tal_env_signrep == tal_signrep_2compl_v)
      if (value == INT8_MAX) {
        *err = true;
        return INT8_MAX;
      }
    #endif
    return -value;
  }

  int16_t tal_neg_i16(const int16_t value, bool* const err) {
    #if (tal_env_signrep == tal_signrep_2compl_v)
      if (value == INT16_MIN) {
        *err = true;
        return INT16_MIN;
      }
    #elif (tal_env_signrep == tal_signrep_2compl_v)
      if (value == INT16_MAX) {
        *err = true;
        return INT16_MAX;
      }
    #endif
    return -value;
  }

  int32_t tal_neg_i32(const int32_t value, bool* const err) {
    #if (tal_env_signrep == tal_signrep_2compl_v)
      if (value == INT32_MIN) {
        *err = true;
        return INT32_MIN;
      }
    #elif (tal_env_signrep == tal_signrep_2compl_v)
      if (value == INT32_MAX) {
        *err = true;
        return INT32_MAX;
      }
    #endif
    return -value;
  }

  int64_t tal_neg_i64(const int64_t value, bool* const err) {
    #if (tal_env_signrep == tal_signrep_2compl_v)
      if (value == INT64_MIN) {
        *err = true;
        return INT64_MIN;
      }
    #elif (tal_env_signrep == tal_signrep_2compl_v)
      if (value == INT64_MAX) {
        *err = true;
        return INT64_MAX;
      }
    #endif
    return -value;
  }

  float tal_neg_f(const float value) {
    return -value;
  }

  double tal_neg_d(const double value) {
    return -value;
  }
  
  int8_t tal_add_i8(const int8_t value_a, const int8_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT8_MAX - value_b)) {
        *err = true;
        return INT8_MAX;
      }
    } else if (value_a < 0 && value_b < 0) {
      if (value_a < (INT8_MIN + value_b)) {
        *err = true;
        return INT8_MIN;
      }
    }
    return value_a + value_b;
  }

  int16_t tal_add_i16(const int16_t value_a, const int16_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT16_MAX - value_b)) {
        *err = true;
        return INT16_MAX;
      }
    } else if (value_a < 0 && value_b < 0) {
      if (value_a < (INT16_MIN + value_b)) {
        *err = true;
        return INT16_MIN;
      }
    }
    return value_a + value_b;
  }

  int32_t tal_add_i32(const int32_t value_a, const int32_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT32_MAX - value_b)) {
        *err = true;
        return INT32_MAX;
      }
    } else if (value_a < 0 && value_b < 0) {
      if (value_a < (INT32_MIN + value_b)) {
        *err = true;
        return INT32_MIN;
      }
    }
    return value_a + value_b;
  }

  int64_t tal_add_i64(const int64_t value_a, const int64_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT64_MAX - value_b)) {
        *err = true;
        return INT64_MAX;
      }
    } else if (value_a < 0 && value_b < 0) {
      if (value_a < (INT64_MIN + value_b)) {
        *err = true;
        return INT64_MIN;
      }
    }
    return value_a + value_b;
  }
  
  uint8_t tal_add_u8(const uint8_t value_a, const uint8_t value_b, 
      bool* const err) {
    if (value_a > (UINT8_MAX - value_b)) {
      *err = true;
      return UINT8_MAX;
    }
    return value_a + value_b;
  }

  uint16_t tal_add_u16(const uint16_t value_a, const uint16_t value_b, 
      bool* const err) {
    if (value_a > (UINT16_MAX - value_b)) {
      *err = true;
      return UINT16_MAX;
    }
    return value_a + value_b;
  }

  uint32_t tal_add_u32(const uint32_t value_a, const uint32_t value_b, 
      bool* const err) {
    if (value_a > (UINT32_MAX - value_b)) {
      *err = true;
      return UINT32_MAX;
    }
    return value_a + value_b;
  }

  uint64_t tal_add_u64(const uint64_t value_a, const uint64_t value_b, 
      bool* const err) {
    if (value_a > (UINT64_MAX - value_b)) {
      *err = true;
      return UINT64_MAX;
    }
    return value_a + value_b;
  }

  float tal_add_f(const float value_a, const float value_b,
      bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b) ||
        (tal_is_inf_f(value_a) && tal_is_inf_f(value_b) && 
        tal_sign_bit_f(value_a) != tal_is_inf_f(value_b))) { 
      *err = true;
      return tal_nan_f();
    }
    if (tal_sign_bit_f(value_a) && tal_sign_bit_f(value_b)) {
      if (tal_cmpg_ff(value_a, FLT_MAX - value_b, err)) {
        *err = true;
        return tal_inf_f();
      }
    }
    if (!tal_sign_bit_f(value_a) && !tal_sign_bit_f(value_b)) {
      if (tal_cmpl_ff(value_a, -FLT_MAX - value_b, err)) {
        *err = true;
        return -tal_inf_f();
      }
    }
    if (tal_cmpl_ff(tal_ulp_f(value_a) / 2.0f, value_b, err)) {
      *err = true;
      return value_a + tal_ulp_f(value_a);
    }
    return value_a + value_b;
  }

  double tal_add_d(const double value_a, const double value_b,
      bool* const err) {
    if (tal_is_nan_d(value_a) || tal_is_nan_d(value_b) ||
        (tal_is_inf_d(value_a) && tal_is_inf_d(value_b) &&
        tal_sign_bit_d(value_a) != tal_is_inf_d(value_b))) { 
      *err = true;
      return tal_nan_d();
    }
    if (tal_sign_bit_d(value_a) && tal_sign_bit_d(value_b) &&
        tal_cmpg_dd(value_a, DBL_MAX - value_b, err)) {
      *err = true;
      return tal_inf_d();
    }
    if (!tal_sign_bit_d(value_a) && !tal_sign_bit_d(value_b) &&
        tal_cmpl_dd(value_a, -DBL_MAX - value_b, err)) {
        *err = true;
        return -tal_inf_d();
    }
    if (tal_is_denorm_f(value_b) && tal_cmpl_dd(
        tal_ulp_d(value_a) / 2.0, tal_abs_d(value_b), err)) {
      *err = true;
      if (tal_sign_bit_d(value_a)) {
        return value_a - tal_ulp_d(value_a);
      } else {
        return value_a + tal_ulp_d(value_a);
      }
    }
    if (tal_is_denorm_d(value_a) && tal_cmpl_dd(
        tal_ulp_d(value_b) / 2.0, tal_abs_d(value_a), err)) {
      *err = true;
      if (tal_sign_bit_d(value_b)) {
        return value_b - tal_ulp_d(value_b);
      } else {
        return value_b + tal_ulp_d(value_b);
      }
    }

    return value_a + value_b;
  }

  int8_t tal_sub_i8(const int8_t value_a, const int8_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b < 0) {
      if (value_a > (INT8_MAX + value_b)) { 
        *err = true;
        return INT8_MAX;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT8_MIN + value_b)) {
        *err = true;
        return INT8_MIN;
      }
    }
    return value_a - value_b;
  }

  int16_t tal_sub_i16(const int16_t value_a, const int16_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b < 0) {
      if (value_a > (INT16_MAX + value_b)) { 
        *err = true;
        return INT16_MAX;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT16_MIN + value_b)) {
        *err = true;
        return INT16_MIN;
      }
    }
    return value_a - value_b;
  }

  int32_t tal_sub_i32(const int32_t value_a, const int32_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b < 0) {
      if (value_a > (INT32_MAX + value_b)) { 
        *err = true;
        return INT32_MAX;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT32_MIN + value_b)) {
        *err = true;
        return INT32_MIN;
      }
    }
    return value_a - value_b;
  }

  int64_t tal_sub_i64(const int64_t value_a, const int64_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b < 0) {
      if (value_a > (INT64_MAX + value_b)) { 
        *err = true;
        return INT64_MAX;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT64_MIN + value_b)) {
        *err = true;
        return INT64_MIN;
      }
    }
    return value_a - value_b;
  }

  uint8_t tal_sub_u8(const uint8_t value_a, const uint8_t value_b, 
      bool* const err) {
    if (value_a < value_b) {
      *err = true;
      return 0;
    }
    return value_a - value_b;
  }

  uint16_t tal_sub_u16(const uint16_t value_a, const uint16_t value_b, 
      bool* const err) {
    if (value_a < value_b) {
      *err = true;
      return 0;
    }
    return value_a - value_b;
  }

  uint32_t tal_sub_u32(const uint32_t value_a, const uint32_t value_b, 
      bool* const err) {
    if (value_a < value_b) {
      *err = true;
      return 0;
    }
    return value_a - value_b;
  }

  uint64_t tal_sub_u64(const uint64_t value_a, const uint64_t value_b, 
      bool* const err) {
    if (value_a < value_b) {
      *err = true;
      return 0;
    }
    return value_a - value_b;
  }

  float tal_sub_f(const float value_a, const float value_b,
      bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b) ||
        (tal_is_inf_f(value_a) && tal_is_inf_f(value_b) &&
        tal_sign_bit(value_a) == tal_sign_bit(value_b))) { 
      *err = true; 
      return tal_nan_f();
    }
    if (tal_sign_bit_f(value_a) && !tal_sign_bit_f(value_b) &&
        tal_cmpl_ff(value_a, FLT_MAX + value_b, err)) {
      *err = true;
      return tal_inf_f();
    }
    if (!tal_sign_bit_f(value_a) && tal_sign_bit_f(value_b) &&
        tal_cmpg_ff(value_a, -FLT_MAX - value_b, err)) {
      *err = true;
      return -tal_inf_f();
    }
    if (tal_is_denorm_f(value_b) && tal_cmpl_ff(
        tal_ulp_f(value_a) / 2.0f, value_b, err)) {
      *err = true;
    }
    

    return value_a - value_b;
  }

  double tal_sub_d(const double value_a, const double value_b,
      bool* const err) {
    if (tal_is_nan_d(value_a) || tal_is_nan_d(value_b) ||
        (tal_is_inf_d(value_a) && tal_is_inf_d(value_b) &&
        tal_sign_bit(value_a) == tal_sign_bit(value_b))) {
      *err = true;
      return tal_nan_d();
    }
    return value_a - value_b;
  }

  int8_t tal_mul_i8(const int8_t value_a, const int8_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT8_MAX / value_b)) {
        *err = true;
        return INT8_MAX;
      }
    } else if (value_a > 0) {
      if (value_b < (INT8_MIN / value_a)) {
        *err = true;
        return INT8_MIN;
      }
    } else if (value_b > 0) {
      if (value_a < (INT8_MIN / value_b)) {
        *err = true;
        return INT8_MIN;
      }
    } else {
      #if (tal_env_signrep == tal_signrep_2compl_v)
        if (value_b == -1) {
          if (value_a == INT8_MIN) {
            *err = true;
            return INT8_MAX;
          } else {
            return -value_a;
          }
        }
      #endif
      if (value_a < (INT8_MAX / value_b)) {
        *err = true;
        return INT8_MAX;
      }
    }
    return value_a * value_b;
  }

  int16_t tal_mul_i16(const int16_t value_a, const int16_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT16_MAX / value_b)) {
        *err = true;
        return INT16_MAX;
      }
    } else if (value_a > 0) {
      if (value_b < (INT16_MIN / value_a)) {
        *err = true;
        return INT16_MIN;
      }
    } else if (value_b > 0) {
      if (value_a < (INT16_MIN / value_b)) {
        *err = true;
        return INT16_MIN;
      }
    } else {
      #if (tal_env_signrep == tal_signrep_2compl_v)
        if (value_b == -1) {
          if (value_a == INT16_MIN) {
            *err = true;
            return INT16_MAX;
          } else {
            return -value_a;
          }
        }
      #endif
      if (value_a < (INT16_MAX / value_b)) {
        *err = true;
        return INT16_MAX;
      }
    }
    return value_a * value_b;
  }

  int32_t tal_mul_i32(const int32_t value_a, const int32_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT32_MAX / value_b)) {
        *err = true;
        return INT32_MAX;
      }
    } else if (value_a > 0) {
      if (value_b < (INT32_MIN / value_a)) {
        *err = true;
        return INT32_MIN;
      }
    } else if (value_b > 0) {
      if (value_a < (INT32_MIN / value_b)) {
        *err = true;
        return INT32_MIN;
      }
    } else {
      #if (tal_env_signrep == tal_signrep_2compl_v)
        if (value_b == -1) {
          if (value_a == INT32_MIN) {
            *err = true;
            return INT32_MAX;
          } else {
            return -value_a;
          }
        }
      #endif
      if (value_a < (INT32_MAX / value_b)) {
        *err = true;
        return INT32_MAX;
      }
    }
    return value_a * value_b;
  }

  int64_t tal_mul_i64(const int64_t value_a, const int64_t value_b, 
      bool* const err) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT64_MAX / value_b)) {
        *err = true;
        return INT64_MAX;
      }
    } else if (value_a > 0) {
      if (value_b < (INT64_MIN / value_a)) {
        *err = true;
        return INT64_MIN;
      }
    } else if (value_b > 0) {
      if (value_a < (INT64_MIN / value_b)) {
        *err = true;
        return INT64_MIN;
      }
    } else {
      #if (tal_env_signrep == tal_signrep_2compl_v)
        if (value_b == -1) {
          if (value_a == INT64_MIN) {
            *err = true;
            return INT64_MAX;
          } else {
            return -value_a;
          }
        }
      #endif
      if (value_a < (INT64_MAX / value_b)) {
        *err = true;
        return INT64_MAX;
      }
    }
    return value_a * value_b;
  }

  uint8_t tal_mul_u8(const uint8_t value_a, const uint8_t value_b, 
      bool* const err) {
    if (value_a > (UINT8_MAX / value_b)) {
      *err = true;
      return UINT8_MAX;
    }
    return value_a * value_b;
  }
  
  uint16_t tal_mul_u16(const uint16_t value_a, const uint16_t value_b, 
      bool* const err) {
    if (value_a > (UINT16_MAX / value_b)) {
      *err = true;
      return UINT16_MAX;
    }
    return value_a * value_b;
  }

  uint32_t tal_mul_u32(const uint32_t value_a, const uint32_t value_b, 
      bool* const err) {
    if (value_a > (UINT32_MAX / value_b)) {
      *err = true;
      return UINT32_MAX;
    }
    return value_a * value_b;
  }

  uint64_t tal_mul_u64(const uint64_t value_a, const uint64_t value_b, 
      bool* const err) {
    if (value_a > (UINT64_MAX / value_b)) {
      *err = true;
      return UINT64_MAX;
    }
    return value_a * value_b;
  }

  float tal_mul_f(const float value_a, const float value_b, 
      bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b) ||
        (tal_is_inf_f(value_a) && value_b == 0.0f) ||
        (tal_is_inf_f(value_b) && value_a == 0.0f)) {
      *err = true;
      return tal_nan_f();
    }
    return value_a * value_b;
  }

  double tal_mul_d(const double value_a, const double value_b,
      bool* const err) {
    if (tal_is_nan_d(value_a) || tal_is_nan_d(value_b) ||
        (tal_is_inf_d(value_a) && value_b == 0.0f) ||
        (tal_is_inf_d(value_b) && value_a == 0.0f)) {
      *err = true;
      return tal_nan_d();
    }
    return value_a * value_b;
  }

  int8_t tal_div_i8(const int8_t num, const int8_t div, 
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num / div;
  }
  
  int16_t tal_div_i16(const int16_t num, const int16_t div, 
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num / div;
  }
  
  int32_t tal_div_i32(const int32_t num, const int32_t div, 
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num / div;
  }
  
  int64_t tal_div_i64(const int64_t num, const int64_t div, 
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num / div;
  }
  
  uint8_t tal_div_u8(const uint8_t num, const uint8_t div, 
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num / div;
  }

  uint16_t tal_div_u16(const uint16_t num, const uint16_t div, 
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num / div;
  }

  uint32_t tal_div_u32(const uint32_t num, const uint32_t div, 
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num / div;
  }

  uint64_t tal_div_u64(const uint64_t num, const uint64_t div, 
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num / div;
  }

  float tal_div_f(const float value_a, const float value_b,
      bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b) ||
        (tal_is_inf_f(value_a) && tal_is_inf_f(value_b)) ||
        (value_a == 0.0f && value_b == 0.0f)) { 
      *err = true;
      return tal_nan_f();
    } else if ((tal_is_finite_f(value_a) && value_b == 0.0f) ||
        (tal_is_finite_f(value_b) && value_a == 0.0f)) {
      *err = true;
      if (tal_sign_bit_f(value_a) == tal_sign_bit_f(value_b)) {
        return tal_inf_f();
      } else {
        return -tal_inf_f();
      }
    }
    return value_a / value_b;
  }

  double tal_div_d(const double value_a, const double value_b,
      bool* const err) {
    if (tal_is_nan_d(value_a) || tal_is_nan_d(value_b) ||
        (tal_is_inf_d(value_a) && tal_is_inf_d(value_b)) ||
        (value_a == 0.0 && value_b == 0.0)) {
      *err = true;
      return tal_nan_d();
    } else if ((tal_is_finite_d(value_a) && value_b == 0.0) ||
        (tal_is_finite_d(value_b) && value_a == 0.0)) {
      *err = true;
      if (tal_sign_bit_d(value_a) == tal_sign_bit_d(value_b)) {
        return tal_inf_d();
      } else {
        return -tal_inf_d();
      }
    }
    return value_a / value_b;
  }

  int8_t tal_mod_i8(const int8_t num, const int8_t div,
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num % div;
  }

  int16_t tal_mod_i16(const int16_t num, const int16_t div,
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num % div;
  }

  int32_t tal_mod_i32(const int32_t num, const int32_t div,
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num % div;
  }

  int64_t tal_mod_i64(const int64_t num, const int64_t div,
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0;
    }
    return num % div;
  }

  uint8_t tal_mod_u8(const uint8_t num, const uint8_t div,
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0u;
    }
    return num % div;
  }

  uint16_t tal_mod_u16(const uint16_t num, const uint16_t div,
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0u;
    }
    return num % div;
  }

  uint32_t tal_mod_u32(const uint32_t num, const uint32_t div,
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0u;
    }
    return num % div;
  }

  uint64_t tal_mod_u64(const uint64_t num, const uint64_t div,
      bool* const err) {
    if (div == 0) {
      *err = true;
      return 0u;
    }
    return num % div;
  }

  float tal_mod_f(const float num, const float div,
      bool* const err) {
    if (tal_is_nan_f(num) || tal_is_nan_f(div) ||
        tal_is_inf_f(num) || div <= 0.0f) {
      *err = true;
      return tal_nan_f();
    }
    const float a_div = tal_abs_f(div);
    float c_num = num;
    if (num > 0) {
      while (c_num >= a_div) {
        c_num -= a_div;
      }
      return a_div - c_num;
    } else {
      while (c_num <= -a_div) {
        c_num += a_div;
      }
      return -a_div - c_num;
    }
  }

  double tal_mod_d(const double num, const double div,
      bool* const err) {
    if (tal_is_nan_d(num) || tal_is_nan_d(div) ||
        tal_is_inf_d(num) || div == 0.0f) {
      *err = true;
      return tal_nan_d();
    }
    const double a_div = tal_abs_d(div);
    double c_num = num;
    if (num > 0) {
      while (c_num >= a_div) {
        c_num -= a_div;
      }
      return a_div - c_num;
    } else {
      while (c_num <= -a_div) {
        c_num += a_div;
      }
      return -a_div - c_num;
    }
  }

  int8_t tal_lshift_i8(const int8_t value, const int32_t shift, 
      bool* const err) {
    for (int32_t i = 0; i < shift; ++i) {
      const int8_t mask = (int8_t)1 << (8 - 1 - i);
      if ((value & mask) != 0) {
        *err = true;
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  int16_t tal_lshift_i16(const int16_t value, const int32_t shift, 
      bool* const err) {
    for (int32_t i = 0; i < shift; ++i) {
      const int16_t mask = (int16_t)1 << (16 - 1 - i);
      if ((value & mask) != 0) {
        *err = true;
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  int32_t tal_lshift_i32(const int32_t value, const int32_t shift, 
      bool* const err) {
    for (int32_t i = 0; i < shift; ++i) {
      const int32_t mask = (int32_t)1 << (32 - 1 - i);
      if ((value & mask) != 0) {
        *err = true;
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  int64_t tal_lshift_i64(const int64_t value, const int32_t shift, 
      bool* const err) {
    for (int32_t i = 0; i < shift; ++i) {
      const int64_t mask = (int64_t)1 << (64 - 1 - i);
      if ((value & mask) != 0) {
        *err = true;
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  uint8_t tal_lshift_u8(const uint8_t value, const int32_t shift, 
      bool* const err) {
    for (int32_t i = 0; i < shift; ++i) {
      const uint8_t mask = (uint8_t)1 << (8 - 1 - i);
      if ((value & mask) != 0u) {
        *err = true;
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  uint16_t tal_lshift_u16(const uint16_t value, const int32_t shift, 
      bool* const err) {
    for (int32_t i = 0; i < shift; ++i) {
      const uint16_t mask = (uint16_t)1 << (16 - 1 - i);
      if ((value & mask) != 0u) {
        *err = true;
        return value << (i - 1);
      }
    }
    return value << shift;
  }
  
  uint32_t tal_lshift_u32(const uint32_t value, const int32_t shift, 
      bool* const err) {
    for (int32_t i = 0; i < shift; ++i) {
      const uint32_t mask = (uint32_t)1 << (32 - 1 - i);
      if ((value & mask) != 0u) {
        *err = true;
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  uint64_t tal_lshift_u64(const uint64_t value, const int32_t shift, 
      bool* const err) {
    for (int32_t i = 0; i < shift; ++i) {
      const uint64_t mask = (uint64_t)1 << (64 - 1 - i);
      if ((value & mask) != 0u) {
        *err = true;
        return value << (i - 1);
      }
    }
    return value << shift;
  }


  int8_t tal_rshift_i8(const int8_t value, const int32_t shift, 
      bool* const err) {
    for (int i = 0; i < shift; ++i) {
      const int8_t mask = (int8_t)1 << i;
      if ((value & mask) != 0) {
        *err = true;
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  int16_t tal_rshift_i16(const int16_t value, const int32_t shift, 
      bool* const err) {
    for (int i = 0; i < shift; ++i) {
      const int16_t mask = (int16_t)1 << i;
      if ((value & mask) != 0) {
        *err = true;
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  int32_t tal_rshift_i32(const int32_t value, const int32_t shift, 
      bool* const err) {
    for (int i = 0; i < shift; ++i) {
      const int32_t mask = (int32_t)1 << i;
      if ((value & mask) != 0) {
        *err = true;
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  int64_t tal_rshift_i64(const int64_t value, const int32_t shift, 
      bool* const err) {
    for (int i = 0; i < shift; ++i) {
      const int64_t mask = (int64_t)1 << i;
      if ((value & mask) != 0) {
        *err = true;
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  uint8_t tal_rshift_u8(const uint8_t value, const int32_t shift, 
      bool* const err) {
    for (int i = 0; i < shift; ++i) {
      const uint8_t mask = (uint8_t)1 << i;
      if ((value & mask) != 0) {
        *err = true;
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  uint16_t tal_rshift_u16(const uint16_t value, const int32_t shift, 
      bool* const err) {
    for (int i = 0; i < shift; ++i) {
      const uint16_t mask = (uint16_t)1 << i;
      if ((value & mask) != 0) {
        *err = true;
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  uint32_t tal_rshift_u32(const uint32_t value, const int32_t shift, 
      bool* const err) {
    for (int i = 0; i < shift; ++i) {
      const uint32_t mask = (uint32_t)1 << i;
      if ((value & mask) != 0) {
        *err = true;
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  uint64_t tal_rshift_u64(const uint64_t value, const int32_t shift, 
      bool* const err) {
    for (int i = 0; i < shift; ++i) {
      const uint64_t mask = (uint64_t)1 << i;
      if ((value & mask) != 0) {
        *err = true;
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  int8_t tal_cast_i8i(const int64_t value, bool* const err) {
    if (value < INT8_MIN) {
      *err = true;
      return INT8_MIN;
    }
    if (value > INT8_MAX) {
      *err = true;
      return INT8_MAX;
    }
    return (int8_t)value;
  }

  int16_t tal_cast_i16i(const int64_t value, bool* const err) {
    if (value < INT16_MIN) {
      *err = true;
      return INT16_MIN;
    }
    if (value > INT16_MAX) {
      *err = true;
      return INT16_MAX;
    }
    return (int16_t)value;
  }

  int32_t tal_cast_i32i(const int64_t value, bool* const err) {
    if (value < INT32_MIN) {
      *err = true;
      return INT32_MIN;
    }
    if (value > INT32_MAX) {
      *err = true;
      return INT32_MAX;
    }
    return (int32_t)value;
  }

  int8_t tal_cast_i8u(const uint64_t value, bool* const err) {
    if (value > (uint64_t)INT8_MAX) {
      *err = true;
      return INT8_MAX;
    }
    return (int8_t)value;
  }

  int16_t tal_cast_i16u(const uint64_t value, bool* const err) {
    if (value > (uint64_t)INT16_MAX) {
      *err = true;
      return INT16_MAX;
    }
    return (int16_t)value;
  }

  int32_t tal_cast_i32u(const uint64_t value, bool* const err) {
    if (value > (uint64_t)INT32_MAX) {
      *err = true;
      return INT32_MAX;
    }
    return (int32_t)value;
  }

  int64_t tal_cast_i64u(const uint64_t value, bool* const err) {
    if (value > (uint64_t)INT64_MAX) {
      *err = true;
      return INT64_MAX;
    }
    return (int64_t)value;
  }

  uint8_t tal_cast_u8i(const int64_t value, bool* const err) {
    if (value < 0) {
      *err = true;
      return 0u;
    }
    if ((uint8_t)value > UINT8_MAX) {
      *err = true;
      return UINT8_MAX;
    }
    return (uint8_t)value;
  }

  uint16_t tal_cast_u16i(const int64_t value, bool* const err) {
    if (value < 0) {
      *err = true;
      return 0u;
    }
    if ((uint16_t)value > UINT16_MAX) {
      *err = true;
      return UINT16_MAX;
    }
    return (uint16_t)value;
  }

  uint32_t tal_cast_u32i(const int64_t value, bool* const err) {
    if (value < 0) {
      *err = true;
      return 0u;
    }
    if ((uint32_t)value > UINT32_MAX) {
      *err = true;
      return UINT32_MAX;
    }
    return (uint32_t)value;
  }

  uint64_t tal_cast_u64i(const int64_t value, bool* const err) {
    if (value < 0) {
      *err = true;
      return 0u;
    }
    return (uint64_t)value;
  }

  uint8_t tal_cast_u8u(const uint64_t value, bool* const err) {
    if (value > UINT8_MAX) {
      *err = true;
      return UINT8_MAX;
    }
    return (uint8_t)value;
  }

  uint16_t tal_cast_u16u(const uint64_t value, bool* const err) {
    if (value > UINT16_MAX) {
      *err = true;
      return UINT16_MAX;
    }
    return (uint16_t)value;
  }

  uint32_t tal_cast_u32u(const uint64_t value, bool* const err) {
    if (value > UINT32_MAX) {
      *err = true;
      return UINT32_MAX;
    }
    return (uint32_t)value;
  }

  uint8_t tal_cast_u8f(const float value, bool* const err) {
    if (tal_is_inf_f(value)) {
      *err = true;
      return UINT8_MAX;
    }
    if (tal_is_nan_f(value)) {
      *err = true;
      return 0u;
    }
    if (tal_cmpg_fu(value, UINT8_MAX, NULL)) {
      *err = true;
      return UINT8_MAX;
    }
    if (tal_cmpl_fu(value, 0, NULL)) {
      *err = true;
      return 0u;
    }
    return (uint8_t)value;
  }

  uint16_t tal_cast_u16f(const float value, bool* const err) {
    if (tal_is_inf_f(value)) {
      *err = true;
      return UINT16_MAX;
    }
    if (tal_is_nan_f(value)) {
      *err = true;
      return 0u;
    }
    if (tal_cmpg_fu(value, UINT16_MAX, NULL)) {
      *err = true;
      return UINT16_MAX;
    }
    if (tal_cmpl_fu(value, 0, NULL)) {
      *err = true;
      return 0u;
    }
    return (uint16_t)value;
  }

  uint32_t tal_cast_u32f(const float value, bool* const err) {
    if (tal_is_inf_f(value)) {
      *err = true;
      return UINT32_MAX;
    }
    if (tal_is_nan_f(value)) {
      *err = true;
      return 0u;
    }
    if (tal_cmpg_fu(value, UINT32_MAX, NULL)) {
      *err = true;
      return UINT32_MAX;
    }
    if (tal_cmpl_fu(value, 0, NULL)) {
      *err = true;
      return 0u;
    }
    return (uint32_t)value;
  }

  uint64_t tal_cast_u64f(const float value, bool* const err) {
    if (tal_is_inf_f(value)) {
      *err = true;
      return UINT64_MAX;
    }
    if (tal_is_nan_f(value)) {
      *err = true;
      return 0u;
    }
    if (tal_cmpg_fu(value, UINT64_MAX, NULL)) {
      *err = true;
      return UINT64_MAX;
    }
    if (tal_cmpl_fu(value, 0, NULL)) {
      *err = true;
      return 0u;
    }
    return (uint64_t)value;
  }
  
  int8_t tal_cast_i8f(const float value, bool* const err) {
    if (tal_is_inf_f(value)) {
      *err = true;
      return INT8_MAX;
    }
    if (tal_is_nan_f(value)) {
      *err = true;
      return 0;
    }
    if (tal_cmpg_fi(value, INT8_MAX, NULL)) {
      *err = true;
      return INT8_MAX;
    }
    if (tal_cmpl_fi(value, INT8_MIN, NULL)) {
      *err = true;
      return INT8_MIN;
    }
    return (int8_t)value;
  }

  int16_t tal_cast_i16f(const float value, bool* const err) {
    if (tal_is_inf_f(value)) {
      *err = true;
      return INT16_MAX;
    }
    if (tal_is_nan_f(value)) {
      *err = true;
      return 0;
    }
    if (tal_cmpg_fi(value, INT16_MAX, NULL)) {
      *err = true;
      return INT16_MAX;
    }
    if (tal_cmpl_fi(value, INT16_MIN, NULL)) {
      *err = true;
      return INT16_MIN;
    }
    return (int16_t)value;
  }

  int32_t tal_cast_i32f(const float value, bool* const err) {
    if (tal_is_inf_f(value)) {
      *err = true;
      return INT32_MAX;
    }
    if (tal_is_nan_f(value)) {
      *err = true;
      return 0;
    }
    if (tal_cmpg_fi(value, INT32_MAX, NULL)) {
      *err = true;
      return INT32_MAX;
    }
    if (tal_cmpl_fi(value, INT32_MIN, NULL)) {
      *err = true;
      return INT32_MIN;
    }
    return (int32_t)value;
  }

  int64_t tal_cast_i64f(const float value, bool* const err) {
    if (tal_is_inf_f(value)) {
      *err = true;
      return INT64_MAX;
    }
    if (tal_is_nan_f(value)) {
      *err = true;
      return 0;
    }
    if (tal_cmpg_fi(value, INT64_MAX, NULL)) {
      *err = true;
      return INT64_MAX;
    }
    if (tal_cmpl_fi(value, INT64_MIN, NULL)) {
      *err = true;
      return INT64_MIN;
    }
    return (int64_t)value;
  }

  uint8_t tal_cast_u8d(const double value, bool* const err) {
    if (tal_is_inf_d(value)) {
      *err = true;
      return UINT8_MAX;
    }
    if (tal_is_nan_d(value)) {
      *err = true;
      return 0u;
    }
    if (tal_cmpg_du(value, UINT8_MAX, NULL)) {
      *err = true;
      return UINT8_MAX;
    }
    if (tal_cmpl_du(value, 0, NULL)) {
      *err = true;
      return 0u;
    }
    return (uint8_t)value;
  }

  uint16_t tal_cast_u16d(const double value, bool* const err) {
    if (tal_is_inf_d(value)) {
      *err = true;
      return UINT16_MAX;
    }
    if (tal_is_nan_d(value)) {
      *err = true;
      return 0u;
    }
    if (tal_cmpg_du(value, UINT16_MAX, NULL)) {
      *err = true;
      return UINT16_MAX;
    }
    if (tal_cmpl_du(value, 0, NULL)) {
      *err = true;
      return 0u;
    }
    return (uint16_t)value;
  }

  uint32_t tal_cast_u32d(const double value, bool* const err) {
    if (tal_is_inf_d(value)) {
      *err = true;
      return UINT32_MAX;
    }
    if (tal_is_nan_d(value)) {
      *err = true;
      return 0u;
    }
    if (tal_cmpg_du(value, UINT32_MAX, NULL)) {
      *err = true;
      return UINT32_MAX;
    }
    if (tal_cmpl_du(value, 0, NULL)) {
      *err = true;
      return 0u;
    }
    return (uint32_t)value;
  }

  uint64_t tal_cast_u64d(const double value, bool* const err) {
    if (tal_is_inf_d(value)) {
      *err = true;
      return UINT64_MAX;
    }
    if (tal_is_nan_d(value)) {
      *err = true;
      return 0u;
    }
    if (tal_cmpg_du(value, UINT64_MAX, NULL)) {
      *err = true;
      return UINT64_MAX;
    }
    if (tal_cmpl_du(value, 0, NULL)) {
      *err = true;
      return 0u;
    }
    return (uint64_t)value;
  }

  float tal_cast_fu(const uint64_t value) {
    return (float)value;
  }

  float tal_cast_fi(const int64_t value) {
    return (float)value;
  }

  double tal_cast_du(const uint64_t value) {
    return (double)value;
  }

  double tal_cast_di(const int64_t value) {
    return (double)value;
  }

  /**************************************************************************************************
   * @section Aggregate Arithmetic Operations
   **************************************************************************************************/

  int8_t tal_summation_i8(const int8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int8_t)))) {
      *err = true;
      return 0;
    }
    int8_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_i8(sum, values[i], err);
    }
    return sum;
  }

  int16_t tal_summation_i16(const int16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int16_t)))) {
      *err = true;
      return 0;
    }
    int16_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_i16(sum, values[i], err);
    }
    return sum;
  }

  int32_t tal_summation_i32(const int32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int32_t)))) {
      *err = true;
      return 0;
    }
    int32_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_i32(sum, values[i], err);
    }
    return sum;
  }

  int64_t tal_summation_i64(const int64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int64_t)))) {
      *err = true;
      return 0;
    }
    int64_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_i64(sum, values[i], err);
    }
    return sum;
  }

  uint8_t tal_summation_u8(const uint8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint8_t)))) {
      *err = true;
      return 0u;
    }
    uint8_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_u8(sum, values[i], err);
    }
    return sum;
  }

  uint16_t tal_summation_u16(const uint16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint16_t)))) {
      *err = true;
      return 0u;
    }
    uint16_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_u16(sum, values[i], err);
    }
    return sum;
  }

  uint32_t tal_summation_u32(const uint32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint32_t)))) {
      *err = true;
      return 0u;
    }
    uint32_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_u32(sum, values[i], err);
    }
    return sum;
  }

  uint64_t tal_summation_u64(const uint64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint64_t)))) {
      *err = true;
      return 0u;
    }
    uint64_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_u64(sum, values[i], err);
    }
    return sum;
  }

  float tal_summation_f(const float* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX -
        ((uint32_t)n * sizeof(float)))) {
      *err = true;
      return tal_nan_f();
    }
    float sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_f(sum, values[i], err);
    }
    return sum;
  }
  
  double tal_summation_d(const double* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX -
        ((uint32_t)n * sizeof(double)))) {
      *err = true;
      return tal_nan_d();
    }
    double sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_d(sum, values[i], err);
    }
    return sum;
  }

  int8_t tal_product_i8(const int8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int8_t)))) {
      *err = true;
      return 0;
    }
    int8_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_i8(product, values[i], err);
    }
    return product;
  }

  int16_t tal_product_i16(const int16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int16_t)))) {
      *err = true;
      return 0;
    }
    int16_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_i16(product, values[i], err);
    }
    return product;
  }

  int32_t tal_product_i32(const int32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int32_t)))) {
      *err = true;
      return 0;
    }
    int32_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_i32(product, values[i], err);
    }
    return product;
  }

  int64_t tal_product_i64(const int64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(int64_t)))) {
      *err = true;
      return 0;
    }
    int64_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_i64(product, values[i], err);
    }
    return product;
  }

  uint8_t tal_product_u8(const uint8_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint8_t)))) {
      *err = true;
      return 0u;
    }
    uint8_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_u8(product, values[i], err);
    }
    return product;
  }

  uint16_t tal_product_u16(const uint16_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint16_t)))) {
      *err = true;
      return 0u;
    }
    uint16_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_u16(product, values[i], err);
    }
    return product;
  }

  uint32_t tal_product_u32(const uint32_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint32_t)))) {
      *err = true;
      return 0u;
    }
    uint32_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_u32(product, values[i], err);
    }
    return product;
  }

  uint64_t tal_product_u64(const uint64_t* const values, const int32_t n, 
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX - 
        ((uint32_t)n * sizeof(uint64_t)))) {
      *err = true;
      return 0u;
    }
    uint64_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_u64(product, values[i], err);
    }
    return product;
  }

  float tal_product_f(const float* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX -
        ((uint32_t)n * sizeof(float)))) {
      *err = true;
      return tal_nan_f();
    }
    float product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_f(product, values[i], err);
    }
    return product;
  }

  double tal_product_d(const double* const values, const int32_t n,
      bool* const err) {
    if (!values || n < 0 || (uintptr_t)values > (UINTPTR_MAX -
        ((uint32_t)n * sizeof(double)))) {
      *err = true;
      return tal_nan_d();
    }
    double product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_d(product, values[i], err);
    }
    return product;
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif