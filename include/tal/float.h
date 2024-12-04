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
 * @file include/tal/float.h
 * @authors Aaron McBride
 * @brief Floating-point utilities.
 * @note - API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Special Floating Point Values
   **************************************************************************************************/

  /**
   * @defgroup @b tal_nan
   * @brief Generates a NaN floating point value.
   * @returns (floating point type denoted by suffix) A positive NaN 
   *          ("not a number") value of the specified type.
   * @{
   */
  float tal_nan_f(void);
  double tal_nan_d(void);
  /** @} */

  /**
   * @defgroup @b tal_inf
   * @brief Generates an INF floating point value.
   * @returns (floating-point type denoted by suffix) A positive INF
   *          ("infinity") value of the specified type.
   * @{
   */
  float tal_inf_f(void);
  double tal_inf_d(void);
  /** @} */

  /**************************************************************************************************
   * @section Classification Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_is_finite
   * @brief Determines if a floating point value is finite.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if @p [value] is finite - that is, not equal to
   *          positive/negative NaN/INF, or false otherwise.
   * @{
   */
  bool tal_is_finite_f(float value);
  bool tal_is_finite_d(double value);
  /** @} */

  /**
   * @defgroup @b tal_is_nan
   * @brief Determines if a floating point value is NaN.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if @p [value] is equal to positive or negative NaN
   *          ("not a number"), or false otherwise.
   * @{
   */
  bool tal_is_nan_f(float value);
  bool tal_is_nan_d(double value);
  /** @} */

  /**
   * @defgroup @b tal_is_inf
   * @brief Determines if a floating point value is INF.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if @p [value] is equal to positive or negative INF
   *          ("infinity"), or false otherwise.
   * @{
   */
  bool tal_is_inf_f(float value);
  bool tal_is_inf_d(double value);
  /** @} */

  /**
   * @defgroup @b tal_is_normal
   * @brief Determines if a floating point value is normal (not denormalized).
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns True if @p [value] is a "normalized" floating point number or
   *          false otherwise.
   * @note - NaN and INF are not considered normalized floating point numbers.
   * @{
   */
  bool tal_is_normal_f(float value);
  bool tal_is_normal_d(double value);
  /** @} */

  /**
   * @defgroup @b tal_is_denorm
   * @brief Determines if a floating point value is denormalized.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if @p [value] is a denormalized floating point number, 
   *          or false otherwise.
   * @note - Any 32-bit/single-precision floating point value that is less than
   *         1.1754943508222875e-38 and greater than 0 is considered denormalized.
   * @note - Any 64-bit/double-precision floating point value that is less than
   *         2.2250738585072014e-308 and greater than 0 is considered denormalized.
   * @{
   */
  bool tal_is_denorm_f(float value);
  bool tal_is_denorm_d(double value);
  /** @} */

  /**
   * @defgroup @b tal_sign_bit
   * @brief Determines the sign of a floating point value.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if @p [value] is negative, or false otherwise.
   * @{
   */
  bool tal_sign_bit_f(float value);
  bool tal_sign_bit_d(double value);
  /** @} */

  /**************************************************************************************************
   * @section Value Inspection Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_fexp
   * @brief Extracts the exponent from a floating point value.
   * @param err (bool*) The error flag. Accessed and set true if @p [value] is
   *            equal to positive/negative NaN/INF, or an internal error occurs.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (int32_t) The exponent of @p [value], or 0 if an error occured.
   * @note - The exponent of a floating point value denotes the power of 2 that
   *         the mantissa/significand is multiplied by.
   * @see tal_mant
   * @{
   */
  int32_t tal_fexp_f(bool* err, float value);
  int32_t tal_fexp_d(bool* err, double value);
  /** @} */

  /**
   * @defgroup @b tal_mant
   * @brief Extracts the mantissa/significand from a floating point value.
   * @param err (bool*) The error flag. Accessed and set true if @p [value] is
   *            equal to positive/negative NaN/INF, or an internal error occurs.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (floating point type denoted by suffix) The mantissa/significand
   *          of @p [value], or NAN if an error occured.
   * @note - The mantissa/significand of a floating point value is the decimal
   *         component of the value, which is multiplied by 2^exponent.
   * @see tal_exp
   * @{
   */
  float tal_mant_f(bool* err, float value);
  double tal_mant_d(bool* err, double value);
  /** @} */

  /**
   * @defgroup @b tal_max_ulp
   * @brief Gets the maximum ULP (unit of least precision) for the given
   *        floating point value.
   * @param err (bool*) The error flag. Accessed and set true if @p [value] is 
   *            equal to positive/negative NaN, or an internal error occurs.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (floating point type denoted by suffix) The greatest magnitude
   *          between @p [value] and the next representable value of the same
   *          type, INF if 'value' equals positive/negative INF, or NaN if an
   *          error occured.
   * @note - The returned value is always positive.
   * @{
   */
  float tal_max_ulp_f(bool* err, float value);
  double tal_max_ulp_d(bool* err, double value);
  /** @} */

  /**
   * @defgroup @b tal_min_ulp
   * @brief Gets the minimum ULP (unit of least precision) for the given
   *        floating point value.
   * @param value (floating point type denoted by suffix) The value to query.
   * @param err (bool*) The error flag. Accessed and set true if @p [value] is 
   *            equal to positive/negative NaN, or an internal error occurs.
   * @returns (floating point type denoted by suffix) The smallest magnitude
   *          between @p [value] and the next representable value of the same 
   *          type, INF if 'value' equals positive/negative INF, or NaN if an 
   *          error occured.
   * @note - The returned value is always positive.
   * @{
   */
  float tal_min_ulp_f(bool* err, float value);
  double tal_min_ulp_d(bool* err, double value);
  /** @} */

  /**
   * @defgroup @b tal_to_ulp
   * @brief Gets the number of ULPs (unit of least precision) between 0 and the 
   *        given floating point value.
   * @param err (bool*) The error flag. Accessed and set true if @p [value] is
   *        equal to positive/negative NaN/INF, or an internal error occurs.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (signed integer type with bit-width denoted by suffix) The number
   *          of distinct floating point values between @p [value] and 0, or 0 
   *          if an error occured.
   * @note - The returned value is always positive.
   * @{
   */
  int32_t tal_to_ulp_f(bool* err, float value);
  int64_t tal_to_ulp_d(bool* err, double value);
  /** @} */

#if defined(__cplusplus)
  } // extern "C"
#endif