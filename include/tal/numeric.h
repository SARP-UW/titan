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
#include "src/common/attributes.h"
#include "src/common/env_info.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Floating-Point Classification Utilities
   **************************************************************************************************/

  /**
   * @defgroup fp tal_is_inf
   * @brief Determines if a floating point value is infinite.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is infinite, or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_is_inf_f(const float value);
  tal_fn_attr_inline inline bool tal_is_inf_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_is_nan
   * @brief Determines if a floating point value is NaN.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is NaN, or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_is_nan_f(const float value);
  tal_fn_attr_inline inline bool tal_is_nan_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_is_finite
   * @brief Determines if a floating point value is finite.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is finite, or false otherwise.
   * @note - A floating-point value is finite if it is not infinite or NaN.
   * @{
   */
  tal_fn_attr_inline inline bool tal_is_finite_f(const float value);
  tal_fn_attr_inline inline bool tal_is_finite_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_is_denorm
   * @brief Determines if a floating point value is denormal (not normalized).
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is a "denormal" number (not zero, NaN, or
   *          infinity), or false otherwise.
   * @note - A denormal number is a floating-point value that is a value too
   *         small to be represented in the normalized format.
   * @{
   */
  tal_fn_attr_inline inline bool tal_is_denorm_f(const float value);
  tal_fn_attr_inline inline bool tal_is_denorm_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_isnorm
   * @brief Determines if a floating point value is normal (not denormalized).
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns True if 'value' is a "normal" number (not zero, NaN or infinity), 
   *          or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_is_norm_f(const float value);
  tal_fn_attr_inline inline bool tal_is_norm_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_sign_bit
   * @brief Determines if a floating-point value is signed (negative).
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is signed (negative), or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_sign_bit_f(const float value);
  tal_fn_attr_inline inline bool tal_sign_bit_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_ulp
   * @brief Gets the unit of least percision for a floating-point value.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (floating point type denoted by suffix) The difference between
   *          'value' and the nearest distinct value of the same type.
   * @note - Epsilon is the ULP of 1.0.
   * @{
   */
  tal_fn_attr_inline inline float tal_ulp_f(const float value);
  tal_fn_attr_inline inline double tal_ulp_d(const double value);
  /** @} */

  /**************************************************************************************************
   * @section Core Numeric Utilities
   **************************************************************************************************/

  tal_fn_attr_inline inline int8_t tal_copy_sign_i8(const int8_t mag,
      const int8_t sign, bool* const err);
  tal_fn_attr_inline inline int16_t tal_copy_sign_i16(const int16_t mag,
      const int16_t sign, bool* const err);
  tal_fn_attr_inline inline int32_t tal_copy_sign_i32(const int32_t mag,
      const int32_t sign, bool* const err);
  tal_fn_attr_inline inline int64_t tal_copy_sign_i64(const int64_t mag,
      const int64_t sign, bool* const err);

  tal_fn_attr_inline inline float tal_copy_sign_f(const float mag,
      const float sign);
  tal_fn_attr_inline inline double tal_copy_sign_d(const double mag,
      const double sign);

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

  tal_fn_attr_inline inline float tal_abs_f(const float value);
  tal_fn_attr_inline inline double tal_abs_d(const double value);

  /**
   * @defgroup integer tal_min
   * @brief Gets the minimum value contained in a set of values.
   * @param values (pointer to integer type denoted by suffix) An array containing
   *               the values to query.
   * @param n (int32_t) The number of values in the given set.
   * @param err (bool*) The error flag. Accessed and set true if 'n' is negative,
   *            'values' is NULL/out of bounds, or an internal error occurs.
   * @returns (integer type denoted by suffix) The minimum value in the given set,
   *          or 0 if an error occurs.
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
  /** @} */

  tal_fn_attr_inline inline float tal_min_f(const float* const values,
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline double tal_min_d(const double* const values,
      const int32_t n, bool* const err);

  /**
   * @defgroup integer tal_min2
   * @brief Gets the minimum of two values.
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

  tal_fn_attr_inline inline float tal_min2_f(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline double tal_min2_d(const double value_a,
      const double value_b, bool* const err);

  /**
   * @defgroup integer tal_max
   * @brief Gets the maximum value contained in a set of values.
   * @param values (pointer to integer type denoted by suffix) An array containing  
   *               the values to query.
   * @param n (int32_t) The number of values in the given set.
   * @param err (bool*) The error flag. Accessed and set true if 'n' is negative,
   *            'values' is NULL/out of bounds, or an internal error occurs.
   * @returns (integer type denoted by suffix) The maximum value in the given set,
   *          or 0 if an error occurs.
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
  /** @} */

  tal_fn_attr_inline inline float tal_max_f(const float* const values,
      const int32_t n, bool* const err);
  tal_fn_attr_inline inline double tal_max_d(const double* const values,
      const int32_t n, bool* const err);

  /**
   * @defgroup integer tal_max2
   * @brief Gets the maximum of two values.
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

  tal_fn_attr_inline inline float tal_max2_f(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline double tal_max2_d(const double value_a,
      const double value_b, bool* const err);

  /**
   * @defgroup integer tal_clamp
   * @brief Clamps an value to a given range.
   * @param value (integer type denoted by suffix) The value to clamp.
   * @param bound_a (integer type denoted by suffix) The first bound of the range.
   * @param bound_b (integer type denoted by suffix) The second bound of the range.
   * @returns (integer type denoted by suffix) If 'value' is less than the
   *          minimum bound, the minimum bound is returned. If 'value' is
   *          greater than the maximum bound, the maximum bound is returned.
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

  tal_fn_attr_inline inline float tal_clamp_f(const float value, 
      const float bound_a, const float bound_b, bool* const err);
  tal_fn_attr_inline inline double tal_clamp_d(const double value,
      const double bound_a, const double bound_b, bool* const err);

  /**
   * @defgroup integer tal_in_range
   * @brief Determines if a value is within a given range.
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

  tal_fn_attr_inline inline bool tal_in_range_f(const float value, 
      const float bound_a, const float bound_b, bool* const err);
  tal_fn_attr_inline inline bool tal_in_range_d(const double value,
      const double bound_a, const double bound_b, bool* const err);

  /**************************************************************************************************
   * @section Safe Numeric Comparison Utilities
   **************************************************************************************************/

  /**
   * @brief Determines if a signed and unsigned integer are equal.
   * @param i_value (int64_t) The signed integer value to compare.
   * @param u_value (uint64_t) The unsigned integer value to compare.
   * @returns True if 'i_value' is equal to 'u_value', or false otherwise.
   * @note - Use this function to safely compare signed and unsigned integers.
   */
  tal_fn_attr_inline inline bool tal_cmpe_iu(const int64_t i_value, 
      const uint64_t u_value);
  tal_fn_attr_inline inline bool tal_cmpe_iu(const int64_t i_value, 
      const uint64_t u_value);

  tal_fn_attr_inline inline bool tal_cmpe_fu(const float f_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_uf(const uint64_t u_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_du(const double d_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_ud(const uint64_t u_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_fi(const float f_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_if(const int64_t i_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_di(const double d_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_id(const int64_t i_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_fd(const float f_value,
      const double d_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_df(const double d_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_ff(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_dd(const double value_a,
      const double value_b, bool* const err);

  /**
   * @brief Determines if a signed integer is less than an unsigned integer.
   * @param i_value (int64_t) The signed integer value to compare.
   * @param u_value (uint64_t) The unsigned integer value to compare.
   * @returns True if 'i_value' is less than 'u_value', or false otherwise.
   * @note - Use this function to safely compare signed and unsigned integers.
   */
  tal_fn_attr_inline inline bool tal_cmpl_iu(const int64_t i_value, 
      const uint64_t u_value);
  tal_fn_attr_inline inline bool tal_cmpl_ui(const uint64_t u_value,
      const int64_t i_value);

  tal_fn_attr_inline inline bool tal_cmpl_fu(const float f_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpl_uf(const uint64_t u_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpl_du(const double d_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpl_ud(const uint64_t u_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpl_fi(const float f_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpl_if(const int64_t i_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpl_di(const double d_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpl_id(const int64_t i_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpl_fd(const float f_value,
      const double d_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpl_df(const double d_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpl_ff(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpl_dd(const double value_a,
      const double value_b, bool* const err);

  /**
   * @brief Determines if a signed integer is greater than an unsigned integer.
   * @param i_value (i_value) The signed integer value to compare.
   * @param u_value (u_value) The unsigned integer value to compare.
   * @returns True if 'i_value' is greater than 'u_value', or false otherwise.
   * @note - Use this function to safely compare signed and unsigned integers.
   */
  tal_fn_attr_inline inline bool tal_cmpg_iu(const int64_t i_value, 
      const uint64_t u_value);
  tal_fn_attr_inline inline bool tal_cmpg_ui(const uint64_t u_value,
      const int64_t i_value);

  tal_fn_attr_inline inline bool tal_cmpg_fu(const float f_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpg_uf(const uint64_t u_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpg_du(const double d_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpg_ud(const float f_value,
      const int64_t i_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpg_fi(const float f_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpg_if(const int64_t i_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpg_di(const double d_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpg_id(const int64_t i_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpg_fd(const float f_value,
      const double d_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpg_df(const double d_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpg_ff(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpg_dd(const double value_a,
      const double value_b, bool* const err);

  /**
   * @brief Determines if a signed integer is less than or equal to an unsigned 
   *        integer.
   * @param i_value (int64_t) The signed integer value to compare.
   * @param u_value (uint64_t) The unsigned integer value to compare.
   * @returns True if 'i_value' is less than or equal to 'u_value', or false 
   *          otherwise.
   * @note - Use this function to safely compare signed and unsigned integers.
   */
  tal_fn_attr_inline inline bool tal_cmple_iu(const int64_t i_value, 
      const uint64_t u_value);
  tal_fn_attr_inline inline bool tal_cmple_ui(const uint64_t u_value,
      const int64_t i_value);
  
  tal_fn_attr_inline inline bool tal_cmple_fu(const float f_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmple_uf(const uint64_t u_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmple_du(const double d_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmple_ud(const uint64_t u_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmple_fi(const float f_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmple_if(const int64_t i_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmple_di(const double d_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmple_id(const int64_t i_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmple_fd(const float f_value,
      const double d_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmple_df(const double d_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmple_ff(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline bool tal_cmple_dd(const double value_a,
      const double value_b, bool* const err);

  /**
   * @brief Determines if a signed integer is greater than or equal to an 
   *        unsigned integer.
   * @param i_value (int64_t) The signed integer value to compare.
   * @param u_value (uint64_t) The unsigned integer value to compare.
   * @returns True if 'i_value' is greater than or equal to 'u_value', or 
   *          false otherwise.
   * @note - Use this function to safely compare signed and unsigned integers.
   */
  tal_fn_attr_inline inline bool tal_cmpge_iu(const int64_t i_value, 
      const uint64_t u_value);

  tal_fn_attr_inline inline bool tal_cmpge_ui(const uint64_t u_value,
      const int64_t i_value);

  tal_fn_attr_inline inline bool tal_cmpge_fu(const float f_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpge_uf(const uint64_t u_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpge_du(const double d_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpge_ud(const uint64_t u_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpge_fi(const float f_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpge_if(const int64_t i_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpge_di(const double d_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpge_id(const int64_t i_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpge_fd(const float f_value,
      const double d_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpge_df(const double d_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpge_ff(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpge_dd(const double value_a,
      const double value_b, bool* const err);

  /**************************************************************************************************
   * @section Checked/Saturating Arithmetic Operations
   **************************************************************************************************/

  /**
   * @defgroup integer tal_neg
   * @brief Checked/saturating negation operation.
   * @param value (signed integer type denoted by suffix) The value to negate.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows.
   * @returns (signed integer type denoted by suffix) The negated value clamped
   *          to the range of its integer type.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_neg_i8(const int8_t value, 
      bool* const err);
  tal_fn_attr_inline inline int16_t tal_neg_i16(const int16_t value, 
      bool* const err);
  tal_fn_attr_inline inline int32_t tal_neg_i32(const int32_t value, 
      bool* const err);
  tal_fn_attr_inline inline int64_t tal_neg_i64(const int64_t value, 
      bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_add
   * @brief Checked/saturating addition operation.
   * @param value_a (integer type denoted by suffix) The first value to add.
   * @param value_b (integer type denoted by suffix) The second value to add.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows.
   * @returns (integer type denoted by suffix) The sum of 'value_a' and 'value_b',
   *          clamped to the range of their integer type.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_add_i8(const int8_t value_a, 
      const int8_t value_b, bool* const err);
  tal_fn_attr_inline inline int16_t tal_add_i16(const int16_t value_a, 
      const int16_t value_b, bool* const err);
  tal_fn_attr_inline inline int32_t tal_add_i32(const int32_t value_a, 
      const int32_t value_b, bool* const err);
  tal_fn_attr_inline inline int64_t tal_add_i64(const int64_t value_a, 
      const int64_t value_b, bool* const err);
  
  tal_fn_attr_inline inline uint8_t tal_add_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_add_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_add_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_add_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_sub
   * @brief Checked/saturating subtraction operation.
   * @param value_a (integer type denoted by suffix) The value to subtract from.
   * @param value_b (integer type denoted by suffix) The value to subtract.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows.
   * @returns (integer type denoted by suffix) The difference between 'value_a'
   *          and 'value_b' clamped to the range of their integer type.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_sub_i8(const int8_t value_a, 
      const int8_t value_b, bool* const err);
  tal_fn_attr_inline inline int16_t tal_sub_i16(const int16_t value_a, 
      const int16_t value_b, bool* const err);
  tal_fn_attr_inline inline int32_t tal_sub_i32(const int32_t value_a, 
      const int32_t value_b, bool* const err);
  tal_fn_attr_inline inline int64_t tal_sub_i64(const int64_t value_a, 
      const int64_t value_b, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_sub_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_sub_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_sub_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_sub_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_mul
   * @brief Checked/saturating multiplication operation.
   * @param value_a (integer type denoted by suffix) The first value to multiply.
   * @param value_b (integer type denoted by suffix) The second value to multiply.
   * @param err (bool*) The error flag. Accessed and set true if the operation
   *            overflows.
   * @returns (integer type denoted by suffix) The product of 'value_a' and 'value_b',
   *          clamped to the range of their integer type.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_mul_i8(const int8_t value_a, 
      const int8_t value_b, bool* const err);
  tal_fn_attr_inline inline int16_t tal_mul_i16(const int16_t value_a, 
      const int16_t value_b, bool* const err);
  tal_fn_attr_inline inline int32_t tal_mul_i32(const int32_t value_a, 
      const int32_t value_b, bool* const err);
  tal_fn_attr_inline inline int64_t tal_mul_i64(const int64_t value_a, 
      const int64_t value_b, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_mul_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_mul_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_mul_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_mul_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_div
   * @brief Checked/saturating division operation.
   * @param num (integer type denoted by suffix) The numerator's value.
   * @param div (integer type denoted by suffix) The denominator's value.
   * @param err (bool*) The error flag. Accessed and set true if 'div' is 
   *            equal to zero.
   * @returns (integer type denoted by suffix) The result of dividing 'num' by
   *          'div', or 0 if 'div' is equal to zero.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_div_i8(const int8_t num, 
      const int8_t div, bool* const err);
  tal_fn_attr_inline inline int16_t tal_div_i16(const int16_t num, 
      const int16_t div, bool* const err);
  tal_fn_attr_inline inline int32_t tal_div_i32(const int32_t num, 
      const int32_t div, bool* const err);
  tal_fn_attr_inline inline int64_t tal_div_i64(const int64_t num, 
      const int64_t div, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_div_u8(const uint8_t num, 
      const uint8_t div, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_div_u16(const uint16_t num, 
      const uint16_t div, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_div_u32(const uint32_t num, 
      const uint32_t div, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_div_u64(const uint64_t num, 
      const uint64_t div, bool* const err);
  /** @} */

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
  tal_fn_attr_inline inline int8_t tal_lshift_i8(const int8_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline int16_t tal_lshift_i16(const int16_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline int32_t tal_lshift_i32(const int32_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline int64_t tal_lshift_i64(const int64_t value, 
      const int32_t shift, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_lshift_u8(const uint8_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_lshift_u16(const uint16_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_lshift_u32(const uint32_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_lshift_u64(const uint64_t value, 
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
  tal_fn_attr_inline inline int8_t tal_rshift_i8(const int8_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline int16_t tal_rshift_i16(const int16_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline int32_t tal_rshift_i32(const int32_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline int64_t tal_rshift_i64(const int64_t value, 
      const int32_t shift, bool* const err);

  tal_fn_attr_inline inline uint8_t tal_rshift_u8(const uint8_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline uint16_t tal_rshift_u16(const uint16_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline uint32_t tal_rshift_u32(const uint32_t value, 
      const int32_t shift, bool* const err);
  tal_fn_attr_inline inline uint64_t tal_rshift_u64(const uint64_t value, 
      const int32_t shift, bool* const err);
  /** @} */

  /**
   * @defgroup integer tal_cast
   * @brief Checked/saturating integer cast operation.
   * @param value (intmax_t/uintmax_t denoted by end of suffix) The value to cast.
   * @param err (bool*) The error flag. Accessed and set true if 'value' is out of
   *            bounds of the destination type.
   * @returns (integer type denoted by suffix) 'value' cast to the destination type,
   *          and clamped to it's min/max range.
   * @note - 'err' is an optional - it may be NULL.
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
  /** @} */

  /**************************************************************************************************
   * @section Aggregate Arithmetic Operations
   **************************************************************************************************/

  /**
   * @defgroup integer tal_summation
   * @brief Checked/saturating summation operation.
   * @param values (pointer to integer type denoted by suffix) Array of values.
   * @param n (int32_t) The number of values (size of array).
   * @param err (bool*) The error flag. Accessed and set true if 'n' is out of bounds,
   *            'values' is NULL/out of bounds, the operation overflows, or an
   *            internal error occurs.
   * @returns (integer type denoted by suffix) The summation of the first 'n' 
   *          values in the given array, clamped to the range of the suffix type,
   *          or 0 if an error occurs.
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
  /** @} */

  /**
   * @brief integer tal_product
   * @param values (pointer to integer type denoted by suffix) Array of values.
   * @param n (int32_t) The number of values (size of array).
   * @param err (bool*) The error flag. Accessed and set if 'n' is out of bounds,
   *            'values' is NULL/out of bounds, the operation overflows, or an
   *            internal error occurs.
   * @returns (integer type denoted by suffix) The product of the first 'n' 
   *          values in the given array, clamped to the range of the suffix type,
   *          or 0 if an error occurs.
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
  /** @} */

  /**************************************************************************************************
   * @section Miscellaneous Floating-Point Utilities
   **************************************************************************************************/

  tal_fn_attr_inline inline float tal_nan_f(void);
  tal_fn_attr_inline inline double tal_nan_d(void);

  tal_fn_attr_inline inline float tal_inf_f(void);
  tal_fn_attr_inline inline double tal_inf_d(void);

  /**************************************************************************************************
   * @internal Implementation of Core Floating Point Utilities
   **************************************************************************************************/

  #if (tal_env_floatrep == tal_floatrep_ieee754_v)

    // float ieee754 (single prec) constants
    static const int32_t flt_mant_bits = (FLT_MANT_DIG) - 1;
    static const int32_t flt_exp_bits = (sizeof(float) * CHAR_BIT) - flt_mant_bits - 1;
    static const uint32_t flt_exp_mask = ((1ull << flt_exp_bits) - 1ull) << flt_mant_bits;
    static const uint32_t flt_mant_mask = (1ull << flt_mant_bits) - 1ull;
    static const uint32_t flt_sign_mask = 1u << ((sizeof(float) * CHAR_BIT) - 1);

    // double ieee754 (double prec) constants
    static const int32_t dbl_mant_bits = (DBL_MANT_DIG) - 1;
    static const int32_t dbl_exp_bits = (sizeof(double) * CHAR_BIT) - dbl_mant_bits - 1;
    static const uint64_t dbl_exp_mask = ((1ull << dbl_exp_bits) - 1ull) << dbl_mant_bits;
    static const uint64_t dbl_mant_mask = (1ull << dbl_mant_bits) - 1ull;
    static const uint64_t dbl_sign_mask = 1ull << ((sizeof(double) * CHAR_BIT) - 1);  


    bool tal_is_inf_f(const float value) {
      union { float f; uint32_t u32; } uni = {.u32 = value};
      return (uni.u32 & flt_exp_mask) == flt_exp_mask && 
          (uni.u32 & flt_mant_mask) == 0u;
    }

    bool tal_is_inf_d(const double value) {
      union { double d; uint64_t u64; } uni = {.u64 = value};
      return (uni.u64 & dbl_exp_mask) == dbl_exp_mask && 
          (uni.u64 & dbl_mant_mask) == 0u;
    }

    bool tal_is_nan_f(const float value) {
      union { float f; uint32_t u32; } uni = {.u32 = value};
      return (uni.u32 & flt_exp_mask) == flt_exp_mask && 
          (uni.u32 & flt_mant_mask) != 0u;
    }

    bool tal_is_nan_d(const double value) {
      union { double d; uint64_t u64; } uni = {.u64 = value};
      return (uni.u64 & dbl_exp_mask) == dbl_exp_mask && 
          (uni.u64 & dbl_mant_mask) != 0u;
    }

    bool tal_is_finite_f(const float value) {
      union { float f; uint32_t u32; } uni = {.u32 = value};
      return (uni.u32 & flt_exp_mask) != flt_exp_mask;
    }

    bool tal_is_finite_d(const double value) {
      union { double d; uint64_t u64; } uni = {.u64 = value};
      return (uni.u64 & dbl_exp_mask) != dbl_exp_mask;
    }

    bool tal_is_denorm_f(const float value) {
      union { float f; uint32_t u32; } uni = {.u32 = value};
      return uni.u32 & flt_exp_mask == 0u && uni.u32 & flt_mant_mask != 0u;
    }

    bool tal_is_denorm_d(const double value) {
      union { double d; uint64_t u64; } uni = {.u64 = value};
      return uni.u64 & dbl_exp_mask == 0u && uni.u64 & dbl_mant_mask != 0u;
    }

    bool tal_is_norm_f(const float value) {
      union { float f; uint32_t u32; } uni = {.u32 = value};
      return uni.u32 & flt_exp_mask != 0u && 
          uni.u32 & flt_exp_mask != flt_exp_mask;
    }

    bool tal_is_norm_d(const double value) {
      union { double d; uint64_t u64; } uni = {.u64 = value};
      return uni.u64 & dbl_exp_mask != 0u && 
          uni.u64 & dbl_exp_mask != dbl_exp_mask;
    }

    bool tal_sign_bit_f(const float value) {
      union { float f; uint32_t u32; } uni = {.u32 = value};
      return (uni.u32 & flt_sign_mask) != 0u;
    }

    bool tal_sign_bit_d(const double value) {
      union { double d; uint64_t u64; } uni = {.u64 = value};
      return (uni.u64 & dbl_sign_mask) != 0u;
    }

    float tal_ulp_f(const float value) {
      union { float f; uint32_t u32; } uni = {.u32 = value};
      ++uni.u32;
      return uni.f - value;
    }

    double tal_ulp_d(const double value) {
      union { double d; uint64_t u64; } uni = {.u64 = value};
      ++uni.u64;
      return uni.d - value;
    }

  #else

    #warning "Floating point utilities are not implemented for current floating point representation."

    bool tal_is_inf_f(const float value) { return false; }
    bool tal_is_inf_d(const double value) { return false; }

    bool tal_is_nan_f(const float value) { return false; }
    bool tal_is_nan_d(const double value) { return false; }

    bool tal_is_finite_f(const float value) { return false; }
    bool tal_is_finite_d(const double value) { return false; }

    bool tal_is_denorm_f(const float value) { return false; }
    bool tal_is_denorm_d(const double value) { return false; }

    bool tal_is_norm_f(const float value) { return false; }
    bool tal_is_norm_d(const double value) { return false; }

    bool tal_sign_bit_f(const float value) { return false; }
    bool tal_sign_bit_d(const double value) { return false; }

    float tal_ulp_f(const float value) { return FLT_EPSILON; }
    double tal_ulp_d(const double value) { return DBL_EPSILON; }

  #endif

  /**************************************************************************************************
   * @internal Implementation of Core Numeric Utilities
   **************************************************************************************************/

  int8_t tal_copy_sign_i8(const int8_t mag, const int8_t sign,
      bool* const err) {
    return sign < 0 != mag < 0 ? tal_neg_i8(mag, err) : mag;
  }

  int16_t tal_copy_sign_i16(const int16_t mag, const int16_t sign,
      bool* const err) {
    return sign < 0 != mag < 0 ? tal_neg_i16(mag, err) : mag;
  }

  int32_t tal_copy_sign_i32(const int32_t mag, const int32_t sign,
      bool* const err) {
    return sign < 0 != mag < 0 ? tal_neg_i32(mag, err) : mag;
  }

  int64_t tal_copy_sign_i64(const int64_t mag, const int64_t sign,
      bool* const err) {
    return sign < 0 != mag < 0 ? tal_neg_i64(mag, err) : mag;
  }

  float tal_copy_sign_f(const float mag, const float sign) {
    const bool sign_sign = tal_sign_bit_f(sign);
    const bool mag_sign = tal_sign_bit_f(mag);
    return sign_sign != mag_sign ? tal_neg_f(mag) : mag;
  }

  double tal_copy_sign_d(const double mag, const double sign) {
    const bool sign_sign = tal_sign_bit_d(sign);
    const bool mag_sign = tal_sign_bit_d(mag);
    return sign_sign != mag_sign ? tal_neg_d(mag) : mag; 
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
      if (!tal_is_nan_f(values[i])) {
        if (tal_is_nan_f(min)) {
          min = values[i];
        } else if (tal_cmpl_ff(values[i], min, NULL)) {
          min = values[i];
        }
      }
    }
    if (tal_is_nan_f(min)) { *err = true; }
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
      if (!tal_is_nan_d(values[i])) {
        if (tal_is_nan_d(min)) {
          min = values[i];
        } else if (tal_cmpl_dd(values[i], min, NULL)) {
          min = values[i];
        }
      }
    }
    if (tal_is_nan_d(min)) { *err = true; }
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
    const bool a_nan = tal_is_nan_f(value_a);
    const bool b_nan = tal_is_nan_f(value_b);
    if (a_nan && b_nan) {
      *err = true;
      return tal_sign_bit_f(value_a) ? value_a : value_b;
    } else if (a_nan) {
      return value_b;
    } else if (b_nan) {
      return value_a;
    } else {
      return tal_cmpl_ff(value_a, value_b, NULL) ? value_a : value_b;
    }
  }

  double tal_min2_d(const double value_a, const double value_b,
      bool* const err) {
    const bool a_nan = tal_is_nan_d(value_a);
    const bool b_nan = tal_is_nan_d(value_b);
    if (a_nan && b_nan) {
      *err = true;
      return tal_sign_bit_d(value_a) ? value_a : value_b;
    } else if (a_nan) {
      return value_b;
    } else if (b_nan) {
      return value_a;
    } else {
      return tal_cmpl_dd(value_a, value_b, NULL) ? value_a : value_b;
    }
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
      if (!tal_is_nan_f(values[i])) {
        if (tal_is_nan_f(max)) {
          max = values[i];
        } else if (tal_cmpg_ff(values[i], max, NULL)) {
          max = values[i];
        }
      }
    }
    if (tal_is_nan_f(max)) { *err = true; }
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
      if (!tal_is_nan_d(values[i])) {
        if (tal_is_nan_d(max)) {
          max = values[i];
        } else if (tal_cmpg_dd(values[i], max, NULL)) {
          max = values[i];
        }
      }
    }
    if (tal_is_nan_d(max)) { *err = true; }
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
    const bool a_nan = tal_is_nan_f(value_a);
    const bool b_nan = tal_is_nan_f(value_b);
    if (a_nan && b_nan) {
      *err = true;
      return tal_sign_bit_f(value_a) ? value_a : value_b;
    } else if (a_nan) {
      return value_b;
    } else if (b_nan) {
      return value_a;
    } else {
      return tal_cmpg_ff(value_a, value_b, NULL) ? value_a : value_b;
    }
  }

  double tal_max2_d(const double value_a, const double value_b,
      bool* const err) {
    const bool a_nan = tal_is_nan_d(value_a);
    const bool b_nan = tal_is_nan_d(value_b);
    if (a_nan && b_nan) {
      *err = true;
      return tal_sign_bit_d(value_a) ? value_a : value_b;
    } else if (a_nan) {
      return value_b;
    } else if (b_nan) {
      return value_a;
    } else {
      return tal_cmpg_dd(value_a, value_b, NULL) ? value_a : value_b;
    }
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
      const bool a_sign = tal_sign_bit_f(bound_a);
      const bool b_sign = tal_sign_bit_f(bound_b);
      return a_sign == b_sign ? bound_a : tal_nan_f();
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
      const bool a_sign = tal_sign_bit_d(bound_a);
      const bool b_sign = tal_sign_bit_d(bound_b);
      return a_sign == b_sign ? bound_a : tal_nan_d();
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
    if (tal_is_nan_f(value) || tal_is_nan_f(bound_a) || 
        tal_is_nan_f(bound_b)) {
      *err = true;
      return false;
    }
    if (tal_cmpl_ff(bound_a, bound_b, NULL)) {
      return tal_cmpl_ff(value, bound_a, NULL) && 
          tal_cmpg_ff(value, bound_b, NULL);
    } else {
      return tal_cmpl_ff(value, bound_b, NULL) && 
          tal_cmpg_ff(value, bound_a, NULL);
    }
  }

  bool tal_in_range_d(const double value, const double bound_a, 
      const double bound_b, bool* const err) {
    if (tal_is_nan_d(value) || tal_is_nan_d(bound_a) || 
        tal_is_nan_d(bound_b)) {
      *err = true;
      return false;
    }
    if (tal_cmpl_dd(bound_a, bound_b, NULL)) {
      return tal_cmpl_dd(value, bound_a, NULL) && 
          tal_cmpg_dd(value, bound_b, NULL);
    } else {
      return tal_cmpl_dd(value, bound_b, NULL) && 
          tal_cmpg_dd(value, bound_a, NULL);
    }
  }

  /**************************************************************************************************
   * @internal Implementation of Safe Numeric Comparison Utilities
   **************************************************************************************************/

  #define tal_cmp_max_ulp (1)

  bool tal_cmpe_iu(const int64_t i_value, const uint64_t u_value) {
    if (i_value < 0) { return false; }
    return (uint64_t)i_value == u_value;
  }
  bool tal_cmpe_ui(const uint64_t u_value, const int64_t i_value) {
    return tal_cmpe_iu(i_value, u_value);
  }

  tal_fn_attr_inline inline bool tal_cmpe_fu(const float f_value,
      const uint64_t u_value, bool* const err) {
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
    return tal_abs_f(f_value - f_u_value) <= 
        (tot_ulp * (float)tal_cmp_max_ulp);
  }

  tal_fn_attr_inline inline bool tal_cmpe_uf(const uint64_t u_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_du(const double d_value,
      const uint64_t u_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_ud(const uint64_t u_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_fi(const float f_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_if(const int64_t i_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_di(const double d_value,
      const int64_t i_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_id(const int64_t i_value,
      const double d_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_fd(const float f_value,
      const double d_value, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_df(const double d_value,
      const float f_value, bool* const err);

  tal_fn_attr_inline inline bool tal_cmpe_ff(const float value_a,
      const float value_b, bool* const err);
  tal_fn_attr_inline inline bool tal_cmpe_dd(const double value_a,
      const double value_b, bool* const err);

  bool tal_cmpl_iu(const int64_t i_value, const uint64_t u_value) {
    if (i_value < 0) { return true; }
    return (uint64_t)i_value < u_value;
  }

  bool tal_cmpg_iu(const int64_t i_value, const uint64_t u_value) {
    if (i_value < 0) { return false; }
    return (uint64_t)i_value > u_value;
  }

  bool tal_cmple_iu(const int64_t i_value, const uint64_t u_value) {
    if (i_value < 0) { return true; }
    return (uint64_t)i_value <= u_value;
  }

  bool tal_cmpge_iu(const int64_t i_value, const uint64_t u_value) {
    if (i_value < 0) { return false; }
    return (uint64_t)i_value >= u_value;
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
    bool sum_err = false;
    int8_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_i8(sum, values[i], &sum_err);
      if (sum_err) {
        *err = true;
        break;
      }
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
    bool sum_err = false;
    int16_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_i16(sum, values[i], &sum_err);
      if (sum_err) {
        *err = true;
        break;
      }
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
    bool sum_err = false;
    int32_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_i32(sum, values[i], &sum_err);
      if (sum_err) {
        *err = true;
        break;
      }
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
    bool sum_err = false;
    int64_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_i64(sum, values[i], &sum_err);
      if (sum_err) {
        *err = true;
        break;
      }
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
    bool sum_err = false;
    uint8_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_u8(sum, values[i], &sum_err);
      if (sum_err) {
        *err = true;
        break;
      }
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
    bool sum_err = false;
    uint16_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_u16(sum, values[i], &sum_err);
      if (sum_err) {
        *err = true;
        break;
      }
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
    bool sum_err = false;
    uint32_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_u32(sum, values[i], &sum_err);
      if (sum_err) {
        *err = true;
        break;
      }
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
    bool sum_err = false;
    uint64_t sum = *values;
    for (int32_t i = 1; i < n; ++i) {
      sum = tal_add_u64(sum, values[i], &sum_err);
      if (sum_err) {
        *err = true;
        break;
      }
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
    bool prod_err = false;
    int8_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_i8(product, values[i], &prod_err);
      if (prod_err) {
        *err = true;
        break;
      }
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
    bool prod_err = false;
    int16_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_i16(product, values[i], &prod_err);
      if (prod_err) {
        *err = true;
        break;
      }
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
    bool prod_err = false;
    int32_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_i32(product, values[i], &prod_err);
      if (prod_err) {
        *err = true;
        break;
      }
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
    bool prod_err = false;
    int64_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_i64(product, values[i], &prod_err);
      if (prod_err) {
        *err = true;
        break;
      }
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
    bool prod_err = false;
    uint8_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_u8(product, values[i], &prod_err);
      if (prod_err) {
        *err = true;
        break;
      }
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
    bool prod_err = false;
    uint16_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_u16(product, values[i], &prod_err);
      if (prod_err) {
        *err = true;
        break;
      }
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
    bool prod_err = false;
    uint32_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_u32(product, values[i], &prod_err);
      if (prod_err) {
        *err = true;
        break;
      }
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
    bool prod_err = false;
    uint64_t product = *values;
    for (int32_t i = 1; i < n; ++i) {
      product = tal_mul_u64(product, values[i], &prod_err);
      if (prod_err) {
        *err = true;
        break;
      }
    }
    return product;
  }

  /**************************************************************************************************
   * @section Implementation of Miscellaneous Floating-Point Utilities
   **************************************************************************************************/

  #if (tal_env_floatrep == tal_floatrep_ieee754_v)

    float tal_nan_f(void) {
      static const union { float f; uint32_t u32; } 
          uni = {.u32 = 0x7FC00000};
      return uni.f;
    }

    double tal_nan_d(void) {
      static const union { double d; uint64_t u64; } 
          uni = {.u64 = 0x7FF8000000000000};
      return uni.d;
    }

    float tal_inf_f(void) {
      static const union { float f; uint32_t u32; } 
          uni = {.u32 = 0x7F800000};
      return uni.f;
    }

    double tal_inf_d(void) {
      static const union { double d; uint64_t u64; } 
          uni = {.u64 = 0x7FF0000000000000};
      return uni.d;
    }

  #else

    #warning "Miscellaneous floating-point utilities are not implemented \
              for the current floating-point representation type."

    float tal_nan_f(void) { return 0.0f; }
    double tal_nan_d(void) { return 0.0f; }

    float tal_inf_f(void) { return 0.0f; }
    double tal_inf_d(void) { return 0.0f; }
    
  #endif

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif