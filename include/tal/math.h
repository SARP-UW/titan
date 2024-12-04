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
 * @file include/tal/math.h
 * @authors Aaron McBride
 * @brief Math utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Special Constants
   **************************************************************************************************/

  /**
   * @defgroup @b tal_sq2
   * @brief TODO
   */
  const double tal_sq2 = 0.0;

  /**
   * @defgroup @b tal_pi
   * @brief TODO
   */
  const double tal_pi = 0.0;

  /**
   * @defgroup @b tal_e
   * @brief TODO
   */
  const double tal_e = 0.0;

  /**
   * @defgroup @b tal_i
   * @brief TODO
   */
  const double tal_i = 0.0;

  /**************************************************************************************************
   * @section Factoring Operations
   **************************************************************************************************/

  /**
   * @degroup @b tal_gcd (int)
   * @brief TODO
   * @param err (bool*)
   * @param a (integer type denoted by suffix)
   * @param b (integer type denoted by suffix)
   * @returns (integer type denoted by suffix)
   * @{
   */
  int8_t tal_gcd_i8(bool* err, int8_t a, int8_t b);
  int16_t tal_gcd_i16(bool* err, int16_t a, int16_t b);
  int32_t tal_gcd_i32(bool* err, int32_t a, int32_t b);
  int64_t tal_gcd_i64(bool* err, int64_t a, int64_t b);
  uint8_t tal_gcd_u8(bool* err, uint8_t a, uint8_t b);
  uint16_t tal_gcd_u16(bool* err, uint16_t a, uint16_t b);
  uint32_t tal_gcd_u32(bool* err, uint32_t a, uint32_t b);
  uint64_t tal_gcd_u64(bool* err, uint64_t a, uint64_t b);
  /** @} */

  /**
   * @degroup @b tal_gcd (fp)
   * @brief TODO
   * @param err (bool*)
   * @param a (floating point type denoted by suffix)
   * @param b (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_gcd_f(bool* err, float a, float b);
  double tal_gcd_d(bool* err, double a, double b);
  /** @} */

  /**
   * @degroup @b tal_lcm (int)
   * @brief TODO
   * @param err (bool*)
   * @param ... (integer type denoted by suffix)
   * @returns (integer type denoted by suffix)
   * @{
   */
  int8_t tal_lcm_i8(bool* err, int8_t a, int8_t b);
  int16_t tal_lcm_i16(bool* err, int16_t a, int16_t b);
  int32_t tal_lcm_i32(bool* err, int32_t a, int32_t b);
  int64_t tal_lcm_i64(bool* err, int64_t a, int64_t b);
  uint8_t tal_lcm_u8(bool* err, uint8_t a, uint8_t b);
  uint16_t tal_lcm_u16(bool* err, uint16_t a, uint16_t b);
  uint32_t tal_lcm_u32(bool* err, uint32_t a, uint32_t b);
  uint64_t tal_lcm_u64(bool* err, uint64_t a, uint64_t b);
  /** @} */

  /**
   * @degroup @b tal_lcm (fp)
   * @brief TODO
   * @param err (bool*)
   * @param a (floating point type denoted by suffix)
   * @param b (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_lcm_f(bool* err, float a, float b);
  double tal_lcm_d(bool* err, double a, double b);
  /** @} */

  /**************************************************************************************************
   * @section Exponential Operations
   **************************************************************************************************/

  /**
   * @defgroup @b tal_pow (int)
   * @brief TODO
   * @param err (bool*)
   * @param base (integer type denoted by suffix)
   * @param exp (integer type denoted by suffix)
   * @returns (integer type denoted by suffix)
   * @{
   */
  int8_t tal_pow_i8(bool* err, int8_t base, int8_t exp);
  int16_t tal_pow_i16(bool* err, int16_t base, int16_t exp);
  int32_t tal_pow_i32(bool* err, int32_t base, int32_t exp);
  int64_t tal_pow_i64(bool* err, int64_t base, int64_t exp);
  uint8_t tal_pow_u8(bool* err, uint8_t base, uint8_t exp);
  uint16_t tal_pow_u16(bool* err, uint16_t base, uint16_t exp);
  uint32_t tal_pow_u32(bool* err, uint32_t base, uint32_t exp);
  uint64_t tal_pow_u64(bool* err, uint64_t base, uint64_t exp);
  /** @} */

  /**
   * @defgroup @b tal_pow (fp)
   * @brief TODO
   * @param err (bool*)
   * @param base (floating point type denoted by suffix)
   * @param exp (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_pow_f(bool* err, float base, float exp);
  double tal_pow_d(bool* err, double base, double exp);
  /** @} */

  /**
   * @defgroup @b tal_exp (fp)
   * @brief TODO
   * @param err (bool*)
   * @param pow (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_exp_f(bool* err, float pow);
  double tal_exp_d(bool* err, double pow);
  /** @} */

  /**
   * @defgroup @b tal_log (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @param base (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_log_f(bool* err, float value, float base);
  double tal_log_d(bool* err, double value, double base);
  /** @} */

  /**
   * @defgroup @b tal_ln (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_ln_f(bool* err, float value);
  double tal_ln_d(bool* err, double value);
  /** @} */

  /**************************************************************************************************
   * @section Trigonometric Operations
   **************************************************************************************************/

  /**
   * @defgroup @b tal_sin (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @param rad (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_sin_f(bool* err, float value, bool rad);
  double tal_sin_d(bool* err, double value, bool rad);
  /** @} */

  /**
   * @defgroup @b tal_cos (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @param rad (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_cos_f(bool* err, float value, bool rad);
  double tal_cos_d(bool* err, double value, bool rad);
  /** @} */

  /**
   * @defgroup @b tal_tan (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @param rad (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_tan_f(bool* err, float value, bool rad);
  double tal_tan_d(bool* err, double value, bool rad);
  /** @} */

  /**
   * @defgroup @b tal_asin (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @param rad (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_asin_f(bool* err, float value, bool rad);
  double tal_asin_d(bool* err, double value, bool rad);
  /** @} */

  /**
   * @defgroup @b tal_acos (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @param rad (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_acos_f(bool* err, float value, bool rad);
  double tal_acos_d(bool* err, double value, bool rad);
  /** @} */

  /**
   * @defgroup @b tal_atan (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @param rad (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_atan_f(bool* err, float value, bool rad);
  double tal_atan_d(bool* err, double value, bool rad);
  /** @} */

  /**
   * @defgroup @b tal_atan2 (fp)
   * @brief TODO
   * @param err (bool*)
   * @param y (floating point type denoted by suffix)
   * @param x (floating point type denoted by suffix)
   * @param rad (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_atan2_f(bool* err, float y, float x, bool rad);
  double tal_atan2_d(bool* err, double y, double x, bool rad);
  /** @} */

  /**
   * @defgroup @b tal_to_deg (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_to_deg_f(bool* err, float value);
  double tal_to_deg_d(bool* err, double value);
  /** @} */

  /**
   * @defgroup @b tal_to_rad (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_to_rad_f(bool* err, float value);
  double tal_to_rad_d(bool* err, double value);
  /** @} */

  /**
   * @defgroup @b tal_pythag (fp)
   * @brief TODO
   * @param err (bool*)
   * @param opp (floating point type denoted by suffix)
   * @param adj (floating point type denoted by suffix)
   * @param hyp (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_pythag_f(bool* err, float opp, float adj, float hyp);
  double tal_pythag_d(bool* err, double opp, double adj, double hyp);
  /** @} */

  /**************************************************************************************************
   * @section Algebraic Operations
   **************************************************************************************************/

  /**************************************************************************************************
   * @section Calculus Operations
   **************************************************************************************************/



  /**************************************************************************************************
   * @section Statistical Operations
   **************************************************************************************************/

  /**
   * @defgroup @b tal_avg (int)
   * @brief TODO
   * @param err (bool*)
   * @param data (integer type denoted by suffix)
   * @param len (int32_t)
   * @returns (double)
   * @{
   */
  double tal_avg_i8(bool* err, const int8_t* data, int32_t len);
  double tal_avg_i16(bool* err, const int16_t* data, int32_t len);
  double tal_avg_i32(bool* err, const int32_t* data, int32_t len);
  double tal_avg_i64(bool* err, const int64_t* data, int32_t len);
  double tal_avg_u8(bool* err, const uint8_t* data, int32_t len);
  double tal_avg_u16(bool* err, const uint16_t* data, int32_t len);
  double tal_avg_u32(bool* err, const uint32_t* data, int32_t len);
  double tal_avg_u64(bool* err, const uint64_t* data, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_avg (fp)
   * @brief TODO
   * @param err (bool*)
   * @param data (floating point type denoted by suffix)
   * @param len (int32_t)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_avg_f(bool* err, const float* data, int32_t len);
  double tal_avg_d(bool* err, const double* data, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_stdev (int)
   * @brief TODO
   * @param err (bool*)
   * @param data (integer type denoted by suffix)
   * @param len (int32_t)
   * @param pop (bool)
   * @returns (double)
   * @{
   */
  double tal_stdev_i8(bool* err, const int8_t* data, int32_t len, bool pop);
  double tal_stdev_i16(bool* err, const int16_t* data, int32_t len, bool pop);
  double tal_stdev_i32(bool* err, const int32_t* data, int32_t len, bool pop);
  double tal_stdev_i64(bool* err, const int64_t* data, int32_t len, bool pop);
  double tal_stdev_u8(bool* err, const uint8_t* data, int32_t len, bool pop);
  double tal_stdev_u16(bool* err, const uint16_t* data, int32_t len, bool pop);
  double tal_stdev_u32(bool* err, const uint32_t* data, int32_t len, bool pop);
  double tal_stdev_u64(bool* err, const uint64_t* data, int32_t len, bool pop);
  /** @} */

  /**
   * @defgroup @b tal_stdev (fp - fp)
   * @brief TODO
   * @param err (bool*)
   * @param data (floating point type denoted by suffix)
   * @param len (int32_t)
   * @param pop (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_stdev_f(bool* err, const float* data, int32_t len, bool pop);
  double tal_stdev_d(bool* err, const double* data, int32_t len, bool pop);
  /** @} */

  /**************************************************************************************************
   * @section Vector Operations
   **************************************************************************************************/

  /**
   * @defgroup @b tal_vec_add (fp)
   * @brief TODO
   * @param err (bool*)
   * @param dst (array of floating point type denoted by suffix)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @{
   */
  void tal_vec_add_f(bool* err, float* dst, const float* lhs, 
      const float* rhs, int32_t len);
  void tal_vec_add_d(bool* err, double* dst, const double* lhs,
      const double* rhs, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_sub (fp)
   * @brief TODO
   * @param err (bool*)
   * @param dst (array of floating point type denoted by suffix)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @{
   */
  void tal_vec_sub_f(bool* err, float* dst, const float* lhs, 
      const float* rhs, int32_t len);
  void tal_vec_sub_d(bool* err, double* dst, const double* lhs, 
      const double* rhs, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_mul (fp)
   * @brief TODO
   * @param err (bool*)
   * @param dst (array of floating point type denoted by suffix)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @{
   */
  void tal_vec_mul_f(bool* err, float* dst, const float* lhs, 
      const float* rhs, int32_t len);
  void tal_vec_mul_d(bool* err, double* dst, const double* lhs, 
      const double* rhs, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_smul (fp)
   * @brief TODO
   * @param err (bool*)
   * @param dst (array of floating point type denoted by suffix)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (floating point type denoted by suffix)
   * @param len (int32_t)
   * @{
   */
  void tal_vec_smul_f(bool* err, float* dst, const float* lhs,
      float rhs, int32_t len);
  void tal_vec_smul_d(bool* err, double* dst, const double* lhs,
      double rhs, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_proj (fp)
   * @brief TODO
   * @param err (bool*)
   * @param dst (array of floating point type denoted by suffix)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @{
   */
  void tal_vec_proj_f(bool* err, float* dst, const float* lhs, 
      const float* rhs, int32_t lhs);
  void tal_vec_proj_d(bool* err, double* dst, const double* lhs, 
      const double* rhs, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_rej (fp)
   * @brief TODO
   * @param err (bool*)
   * @param dst (array of floating point type denoted by suffix)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @{
   */
  void tal_vec_rej_f(bool* err, float* dst, const float* lhs, 
      const float* rhs, int32_t len);
  void tal_vec_rej_d(bool* err, double* dst, const double* lhs, 
      const double* rhs, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_norm (fp)
   * @brief TODO
   * @param err (bool*)
   * @param dst (array of floating point type denoted by suffix)
   * @param vec (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @{
   */
  float tal_vec_norm_f(bool* err, float* dst, const float* vec, int32_t len);
  double tal_vec_norm_d(bool* err, double* dst, const double* vec, int32_t len);
  /** @} */

  /**************************************************************************************************
   * @section Vector Properties
   **************************************************************************************************/

  /**
   * @defgroup @b tal_vec_dot (fp)
   * @brief TODO
   * @param err (bool*)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_vec_dot_f(bool* err, const float* lhs, 
      const float* rhs, int32_t len);
  double tal_vec_dot_d(bool* err, const double* lhs, 
      const double* rhs, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_cross (fp)
   * @brief TODO
   * @param err (bool*)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_vec_cross_f(bool* err, const float* lhs, 
      const float* rhs, int32_t len);
  double tal_vec_cross_d(bool* err, const double* lhs, 
      const double* rhs, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_angle (fp)
   * @brief TODO
   * @param err (bool*)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @param rad (bool)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_vec_angle_f(bool* err, const float* lhs, 
      const float* rhs, int32_t len, bool rad);
  double tal_vec_angle_d(bool* err, const double* lhs, 
      const double* rhs, int32_t len, bool rad);
  /** @} */

  /**
   * @defgroup @b tal_vec_mag (fp)
   * @brief TODO
   * @param err (bool*)
   * @param vec (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_vec_mag_f(const float* vec, int32_t len, bool* err);
  double tal_vec_mag_d(const double* vec, int32_t len, bool* err);
  /** @} */

  /**
   * @defgroup @b tal_vec_span (fp)
   * @brief TODO
   * @param err (bool*)
   * @param vec (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @returns (int32_t)
   * @{
   */
  int32_t tal_vec_span_f(bool* err, const float* vec, int32_t len);
  int32_t tal_vec_span_d(bool* err, const double* vec, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_vec_cmp (fp)
   * @brief TODO
   * @param err (bool*)
   * @param lhs (const array of floating point type denoted by suffix)
   * @param rhs (const array of floating point type denoted by suffix)
   * @param len (int32_t)
   * @returns (bool)
   */
  bool tal_vec_cmp_f(bool* err, const float* lhs, const float* rhs, int32_t len);
  bool tal_vec_cmp_d(bool* err, const double* lhs, const double* rhs, int32_t len);
  /** @} */

  /**************************************************************************************************
   * @section Uncategorised Operations
   **************************************************************************************************/

  /**
   * @defgroup @b tal_fact (int)
   * @brief TODO
   * @param err (bool*)
   * @param value (integer type denoted by suffix)
   * @returns (integer type denoted by suffix)
   * @{
   */
  int8_t tal_fact_i8(bool* err, int8_t value);
  int16_t tal_fact_i16(bool* err, int16_t value);
  int32_t tal_fact_i32(bool* err, int32_t value);
  int64_t tal_fact_i64(bool* err, int64_t value);
  uint8_t tal_fact_u8(bool* err, uint8_t value);
  uint16_t tal_fact_u16(bool* err, uint16_t value);
  uint32_t tal_fact_u32(bool* err, uint32_t value);
  uint64_t tal_fact_u64(bool* err, uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_fact (fp)
   * @brief TODO
   * @param err (bool*)
   * @param value (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_fact_f(bool* err, float value);
  double tal_fact_d(bool* err, double value);
  /** @} */

  /**
   * @defgroup @b tal_fmod (int)
   * @brief TODO
   * @param err (bool*)
   * @param lhs (integer type denoted by suffix)
   * @param rhs (integer type denoted by suffix)
   * @returns (double)
   * @{
   */
  float tal_fmod_f(bool* err, float lhs, float rhs);
  double tal_fmod_d(bool* err, double lhs, double rhs);
  /** @} */

#if defined(__cplusplus)
  } // extern "C"
#endif