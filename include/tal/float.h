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
 * @brief Floating-Point Utilities.
 */

#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Bit-Width Floating Point Types
   **************************************************************************************************/

  /** @brief 32-bit floating point type - "single precision" */
  typedef float tal_float32_t;

  /** @brief 64-bit floating point type - "double precision" */
  typedef double tal_float64_t;

  /**************************************************************************************************
   * @section Value Generation Utilities
   **************************************************************************************************/

  /**
   * @brief Generates a NaN (not a number) floating-point value.
   * @returns (max-width floating-point type) A positive, NaN value.
   * @note - TAL does not distinguish between signaling and quiet NaN values.
   */
  inline tal_float64_t tal_nan(void);

  /**
   * @brief Generates an INF (infinity) floating-point value.
   * @returns (max-width floating-point type) A positive INF value.
   */
  inline tal_float64_t tal_inf(void);

  /**************************************************************************************************
   * @section Classification Utilities
   **************************************************************************************************/

  /**
   * @defgroup fp tal_is_inf
   * @brief Determines if a floating point value is infinite.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is infinite, or false otherwise.
   * @{
   */
  inline bool tal_is_inf_f(const float value);
  inline bool tal_is_inf_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_is_nan
   * @brief Determines if a floating point value is NaN.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is NaN, or false otherwise.
   * @{
   */
  inline bool tal_is_nan_f(const float value);
  inline bool tal_is_nan_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_is_finite
   * @brief Determines if a floating point value is finite.
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is finite, or false otherwise.
   * @note - A floating point value is finite if it is not infinite or NaN.
   * @{
   */
  inline bool tal_is_finite_f(const float value);
  inline bool tal_is_finite_d(const double value);
  /** @} */

  /**
   * @defgroup fp tal_is_denormal
   * @brief Determines if a floating point value is denormal (not normalized).
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is a "denormal" number (not zero, NaN, or
   *          infinity), or false otherwise.
   * @note - A denormal number is a floating point value that is a value too
   *         small to be represented in the normalized format.
   * @{
   */
  inline bool tal_is_denormal_f(const float value);
  inline bool tal_is_denormal_d(const double value);
  /** @} */

  /**
   * @defgroup tal_is_normal
   * @brief Determines if a floating point value is normal (not denormalized).
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns True if 'value' is a "normal" number (not zero, NaN or infinity), 
   *          or false otherwise.
   * @{
   */
  inline bool tal_is_normal_f(const float value);
  inline bool tal_is_normal_d(const double value);
  /** @} */

  /**
   * @defgroup tal_sign_bit
   * @brief Determines if a floating point value is signed (negative).
   * @param value (floating point type denoted by suffix) The value to query.
   * @returns (bool) True if 'value' is signed (negative), or false otherwise.
   * @{
   */
  inline bool tal_sign_bit_f(const float value);
  inline bool tal_sign_bit_d(const double value);
  /** @} */

  /**
   * @defgroup tal_max_ulp
   * @brief Gets the maximum ULP (unit of leas precision) for the given 
   *        floating point value.
   * @param value (floating point type denoted by suffix) The value to query.
   * @param err (bool*) The error flag. Accessed and set true if 'value' is NaN,
   *            or an internal error occurs.
   * @returns (floating point type denoted by suffix) The greatest distance
   *          between 'value' and the next representable value of the same type,
   *          INF if 'value' is infinite, or NaN if an error occurs.
   * @note - The returned value is always positive.
   * @{
   */
  inline float tal_max_ulp_f(const float value, 
      bool* const err);
  inline double tal_max_ulp_d(const double value, 
      bool* const err);
  /** @} */

  /**
   * @defgroup fp tal_min_ulp
   * @brief Gets the minimum ULP (unit of least precision) for the given
   *        floating point value.
   * @param value (floating point type denoted by suffix) The value to query.
   * @param err (bool*) The error flag. Accessed and set true if 'value' is NaN,
   *            or an internal error occurs.
   * @returns (floating point type denoted by suffix) The smallest distance
   *          between 'value' and the next representable value of the same type,
   *          INF if 'value' is infinite, or NaN if an error occurs.
   * @note - The returned value is always positive.
   * @{
   */
  inline float tal_min_ulp_f(const float value, 
      bool* const err);
  inline double tal_min_ulp_d(const double value, 
      bool* const err);
  /** @} */

  /**
   * @defgroup tal_exp
   * @brief Extracts an exponent from a floating point value.
   * @param value (floating point type denoted by suffix) The value to query.
   * @param err (bool*) The error flag. Accessed and set true if 'value' is not
   *            finite (NAN/INF) or an internal error occurs.
   * @returns (int32_t) The exponent of 'value', or 0 if an error occurs.
   * @note - The exponent of a floating point value denotes the power of 2
   *         that the mantissa/significand is multiplied by.
   * @see tal_mant
   * @{
   */
  inline int32_t tal_exp_f(const float value,
      bool* const err);
  inline int32_t tal_exp_d(const double value,
      bool* const err);
  /** @} */

  /**
   * @defgroup tal_mant
   * @brief Extracts the mantissa/significand from a floating point value.
   * @param value (floating point type denoted by suffix) The value to query.
   * @param err (bool*) The error flag. Accessed and set true if 'value' is not
   *            finite (i.e. NAN/INF) or an internal error occurs.
   * @returns (floating point type denoted by suffix) The mantissa/significand
   *          of 'value', or NAN if an error occurs.
   * @note - The mantissa/significand of a floating point value is multiplied by
   *         a power of 2 (the exponent) to get the final value.
   * @see tal_exp
   * @{
   */
  inline float tal_mant_f(const float value, 
      bool* const err);
  inline double tal_mant_d(const double value, 
      bool* const err);
  /** @} */

  /**************************************************************************************************
   * @section Comparison Utilities
   **************************************************************************************************/

  inline bool tal_cmpe_f(const float value_a,
      const float value_b, const float rel, bool* const err);
  inline bool tal_cmpe_d(const double value_a,
      const double value_b, const double rel, bool* const err);

  inline bool tal_cmpl_f(const float value_a,
      const float value_b, const float rel, bool* const err);
  inline bool tal_cmpl_d(const double value_a,
      const double value_b, const double rel, bool* const err);

  inline bool tal_cmpg_f(const float value_a,
      const float value_b, const float rel, bool* const err);
  inline bool tal_cmpg_d(const double value_a,
      const double value_b, const double rel, bool* const err);
  
  inline bool tal_cmple_f(const float value_a,
      const float value_b, const float rel, bool* const err);
  inline bool tal_cmple_d(const double value_a,
      const double value_b, const double rel, bool* const err);
  
  inline bool tal_cmpge_f(const float value_a,
      const float value_b, const float rel, bool* const err);
  inline bool tal_cmpge_d(const double value_a,
      const double value_b, const double rel, bool* const err);

  /**************************************************************************************************
   * @section Arithmetic Utilities
   **************************************************************************************************/

  inline tal_neg_f(const float value, 
      bool* const err);
  inline tal_neg_d(const double value,
      bool* const err);

  inline tal_add_f(const float value_a, 
      const float value_b, bool* const err);
  inline tal_add_d(const double value_a,
      const double value_b, bool* const err);
  
  inline tal_sub_f(const float value_a,
      const float value_b, bool* const err);
  inline tal_sub_d(const double value_a,
      const double value_b, bool* const err);
  
  inline tal_mul_f(const float value_a,
      const float value_b, bool* const err);
  inline tal_mul_d(const double value_a,
      const double value_b, bool* const err);
  
  inline tal_div_f(const float value_a,
      const float value_b, bool* const err);
  inline tal_div_d(const double value_a,
      const double value_b, bool* const err);  

  inline tal_mod_f(const float value_a,
      const float value_b, bool* const err);
  inline tal_mod_d(const double value_a,
      const double value_b, bool* const err);

  /**************************************************************************************************
   * @section Casting Utilities
   **************************************************************************************************/

  inline float tal_cast_ff(const double value,
      bool* const err);

  inline int8_t tal_cast_i8d(const double value,
      bool* const err);
  inline int16_t tal_cast_i16f(const double value,
      bool* const err);
  inline int32_t tal_cast_i32f(const double value,
      bool* const err);
  inline int64_t tal_cast_i64f(const double value,
      bool* const err);

  inline uint8_t tal_cast_u8f(const double value,
      bool* const err);
  inline uint16_t tal_cast_u16f(const double value,
      bool* const err);
  inline uint32_t tal_cast_u32f(const double value,
      bool* const err);
  inline uint64_t tal_cast_u64f(const double value,
      bool* const err);
  

  /** @internal */

  /**************************************************************************************************
   * @section Implementation of Value Generation Utilities
   **************************************************************************************************/

  #if (tal_env_floatrep == tal_floatrep_ieee754_v)

    // Integer representation for IEEE754 INF/NAN
    static const uint32_t flt_inf_value = 0x7F800000;
    static const uint64_t dbl_inf_value = 0x7FF0000000000000;
    static const uint32_t flt_nan_value = 0x7FC00000;
    static const uint64_t dbl_nan_value = 0x7FF8000000000000;

    float tal_nan_f(void) {
      static const union { float f; uint32_t u32; } 
          uni = {.u32 = flt_nan_value};
      return uni.f;
    }

    double tal_nan_d(void) {
      static const union { double d; uint64_t u64; } 
          uni = {.u64 = dbl_nan_value};
      return uni.d;
    }

    float tal_inf_f(void) {
      static const union { float f; uint32_t u32; } 
          uni = {.u32 = flt_inf_value};
      return uni.f;
    }

    double tal_inf_d(void) {
      static const union { double d; uint64_t u64; } 
          uni = {.u64 = dbl_inf_value};
      return uni.d;
    }
    
  #endif

  /**************************************************************************************************
   * @section Implementation of Floating-Point Classification Utilities
   **************************************************************************************************/

  #if (tal_env_floatrep == tal_floatrep_ieee754_v)

    // float ieee754 (single prec) constants
    static const int32_t flt_mant_bits = (FLT_MANT_DIG) - 1;
    static const int32_t flt_exp_bits = (sizeof(float) * CHAR_BIT) - flt_mant_bits - 1;
    static const uint32_t flt_exp_mask = ((1ull << flt_exp_bits) - 1ull) << flt_mant_bits;
    static const uint32_t flt_mant_mask = (1ull << flt_mant_bits) - 1ull;
    static const uint32_t flt_sign_mask = 1u << ((sizeof(float) * CHAR_BIT) - 1);
    static const int32_t flt_exp_offset = 127;

    // double ieee754 (double prec) constants
    static const int32_t dbl_mant_bits = (DBL_MANT_DIG) - 1;
    static const int32_t dbl_exp_bits = (sizeof(double) * CHAR_BIT) - dbl_mant_bits - 1;
    static const uint64_t dbl_exp_mask = ((1ull << dbl_exp_bits) - 1ull) << dbl_mant_bits;
    static const uint64_t dbl_mant_mask = (1ull << dbl_mant_bits) - 1ull;
    static const uint64_t dbl_sign_mask = 1ull << ((sizeof(double) * CHAR_BIT) - 1);
    static const int32_t dbl_exp_offset = 1023;

    // Union types for bit manipulation of flt/dbl values
    typedef union { float f; uint32_t u32; } tal_flt_uni_t__;
    typedef union { double d; uint64_t u64; } tal_dbl_uni_t__;

    bool tal_is_inf_f(const float value) {
      tal_flt_uni_t__ uni = {.f = value};
      return (uni.u32 & flt_exp_mask) == flt_exp_mask && 
          (uni.u32 & flt_mant_mask) == 0u;
    }

    bool tal_is_inf_d(const double value) {
      tal_dbl_uni_t__ uni = {.d = value};
      return (uni.u64 & dbl_exp_mask) == dbl_exp_mask && 
          (uni.u64 & dbl_mant_mask) == 0u;
    }

    bool tal_is_nan_f(const float value) {
      tal_flt_uni_t__ uni = {.f = value};
      return (uni.u32 & flt_exp_mask) == flt_exp_mask && 
          (uni.u32 & flt_mant_mask) != 0u;
    }

    bool tal_is_nan_d(const double value) {
      tal_dbl_uni_t__ uni = {.d = value};
      return (uni.u64 & dbl_exp_mask) == dbl_exp_mask && 
          (uni.u64 & dbl_mant_mask) != 0u;
    }

    bool tal_is_finite_f(const float value) {
      tal_flt_uni_t__ uni = {.f = value};
      return (uni.u32 & flt_exp_mask) != flt_exp_mask;
    }

    bool tal_is_finite_d(const double value) {
      tal_dbl_uni_t__ uni = {.d = value};
      return (uni.u64 & dbl_exp_mask) != dbl_exp_mask;
    }

    bool tal_is_denormal_f(const float value) {
      tal_flt_uni_t__ uni = {.f = value};
      return uni.u32 & flt_exp_mask == 0u && 
          uni.u32 & flt_mant_mask != 0u;
    }

    bool tal_is_denormal_d(const double value) {
      tal_dbl_uni_t__ uni = {.d = value};
      return uni.u64 & dbl_exp_mask == 0u && 
          uni.u64 & dbl_mant_mask != 0u;
    }

    bool tal_is_normal_f(const float value) {
      tal_flt_uni_t__ uni = {.f = value};
      return uni.u32 & flt_exp_mask != 0u && 
          uni.u32 & flt_exp_mask != flt_exp_mask;
    }

    bool tal_is_normal_d(const double value) {
      tal_dbl_uni_t__ uni = {.d = value};
      return uni.u64 & dbl_exp_mask != 0u && 
          uni.u64 & dbl_exp_mask != dbl_exp_mask;
    }

    bool tal_sign_bit_f(const float value) {
      tal_flt_uni_t__ uni = {.f = value};
      return (uni.u32 & flt_sign_mask) != 0u;
    }

    bool tal_sign_bit_d(const double value) {
      tal_dbl_uni_t__ uni = {.d = value};
      return (uni.u64 & dbl_sign_mask) != 0u;
    }

    float tal_max_ulp_f(const float value, bool* const err) {
      if (tal_is_nan_f(value)) {
        *err = true;
        return tal_nan_f();
      }
      if (tal_is_inf_f(value)) {
        return tal_inf_f();
      }
      tal_flt_uni_t__ uni = {.f = value};
      if (tal_sign_bit_f(value)) {
        --uni.u32;
      } else {
        ++uni.u32;
      }
      return uni.f - value;
    }

    double tal_max_ulp_d(const double value, bool* const err) {
      if (tal_is_nan_d(value)) {
        *err = true;
        return tal_nan_d();
      }
      if (tal_is_inf_d(value)) {
        return tal_inf_d();
      }
      tal_dbl_uni_t__ uni = {.d = value};
      if (tal_sign_bit_d(value)) {
        --uni.u64;
      } else {
        ++uni.u64;
      }
      return uni.d - value;
    }

    float tal_min_ulp_f(const float value, bool* const err) {
      if (tal_is_nan_f(value)) {
        *err = true;
        return tal_nan_f();
      }
      if (tal_is_inf_f(value)) {
        return tal_inf_f();
      }
      tal_flt_uni_t__ uni = {.f = value};
      if (tal_sign_bit_f(value)) {
        ++uni.u32;
      } else {
        --uni.u32;
      }
      return value - uni.f;
    }

    double tal_min_ulp_d(const double value, bool* const err) {
      if (tal_is_nan_d(value)) {
        *err = true;
        return tal_nan_d();
      }
      if (tal_is_inf_d(value)) {
        return tal_inf_d();
      }
      tal_dbl_uni_t__ uni = {.d = value};
      if (tal_sign_bit_d(value)) {
        ++uni.u64;
      } else {
        --uni.u64;
      }
      return value - uni.d;
    }

    int32_t tal_exp_f(const float value, bool* const err) {
      if (!tal_is_finite_f(value)) {
        *err = true;
        return 0;
      }
      tal_flt_uni_t__ uni = {.f = value};
      const uint32_t exp_value = (uni.u32 & flt_exp_mask) >> flt_mant_bits;
      return (int32_t)exp_value - flt_exp_offset;
    }

    int32_t tal_exp_d(const double value, bool* const err) {
      if (!tal_is_finite_d(value)) {
        *err = true;
        return 0;
      }
      tal_dbl_uni_t__ uni = {.d = value};
      const uint64_t exp_value = (uni.u64 & dbl_exp_mask) >> dbl_mant_bits;
      return (int32_t)exp_value - dbl_exp_offset;
    }

    float tal_mant_f(const float value, bool* const err) {
      if (!tal_is_finite_f(value)) {
        *err = true;
        return 0.0f;
      }
      tal_flt_uni_t__ uni = {.f = value};
      uni.u32 &= flt_mant_mask;
      uni.u32 |= (uint32_t)flt_exp_offset << flt_mant_bits;
      return uni.f;
    }

    double tal_mant_d(const double value, bool* const err) {
      if (!tal_is_finite_d(value)) {
        *err = true;
        return 0.0;
      }
      tal_dbl_uni_t__ uni = {.d = value};
      uni.u64 &= dbl_mant_mask;
      uni.u64 |= (uint64_t)dbl_exp_offset << dbl_mant_bits;
      return uni.d;
    }

  #endif

  /**************************************************************************************************
   * @section Implementation of Comparison Utilities
   **************************************************************************************************/

  static float abs_f__(const float value) {
    return tal_sign_bit_f(value) ? -value : value;
  }

  static double abs_d__(const double value) {
    return tal_sign_bit_d(value) ? -value : value;
  }

  static float max_abs_f__(const float value_a, const float value_b) {
    const float abs_a = abs_f__(value_a);
    const float abs_b = abs_f__(value_b);
    return abs_a > abs_b ? abs_a : abs_b;
  }

  static double max_abs_d__(const double value_a, const double value_b) {
    const double abs_a = abs_d__(value_a);
    const double abs_b = abs_d__(value_b);
    return abs_a > abs_b ? abs_a : abs_b;
  }

  bool tal_cmpe_f(const float value_a, const float value_b, 
      const float rel, bool* const err) {
    if (tal_is_nan_f(value_a) || tal_is_nan_f(value_b) ||
        tal_is_nan_f(rel)) {
      *err = true;
      return false;
    }
    if (tal_is_inf_f(rel)) { 
      return true; 
    } 
    if (tal_is_inf_f(value_a) || tal_is_inf_f(value_b)) {
      return value_a == value_b;
    }
    const float diff = absf__(value_a - value_b);
    const float max = max_abs_f__(value_a, value_b);
    return diff <= (max * rel);
  }

  bool tal_cmpe_d(const double value_a, const double value_b, 
      const double rel, bool* const err) {

  }

  bool tal_cmpl_f(const float value_a, const float value_b, 
      const float rel, bool* const err) {

  }

  bool tal_cmpl_d(const double value_a, const double value_b, 
      const double rel, bool* const err) {

  }

  bool tal_cmpg_f(const float value_a, const float value_b, 
      const float rel, bool* const err) {
        
  }

  bool tal_cmpg_d(const double value_a, const double value_b, 
      const double rel, bool* const err) {

  }

  bool tal_cmple_f(const float value_a, const float value_b, 
      const float rel, bool* const err) {

  }

  bool tal_cmple_d(const double value_a, const double value_b, 
      const double rel, bool* const err) {

  }

  bool tal_cmpge_f(const float value_a, const float value_b, 
      const float rel, bool* const err) {

  }

  bool tal_cmpge_d(const double value_a, const double value_b, 
      const double rel, bool* const err) {

  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif