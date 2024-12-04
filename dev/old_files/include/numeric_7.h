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
 * @file include/tal/numeric.h
 * @authors Aaron McBride
 * @brief Numeric utilities.
 */

#pragma once
#include <limits.h>
#include "include/tal/numeric.h" // header
#include "include/tal/float.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  int8_t tal_accum_i8(const int8_t* const mem, const int32_t size,
      int8_t (*fn)(int8_t, int8_t), bool* const err);
  int16_t tal_accum_i16(const int16_t* const mem, const int32_t size,
      int16_t (*fn)(int16_t, int16_t), bool* const err);
  int32_t tal_accum_i32(const int32_t* const mem, const int32_t size,
      int32_t (*fn)(int32_t, int32_t), bool* const err);
  int64_t tal_accum_i64(const int64_t* const mem, const int32_t size,
      int64_t (*fn)(int64_t, int64_t), bool* const err);
  uint8_t tal_accum_u8(const uint8_t* const mem, const int32_t size,
      uint8_t (*fn)(uint8_t, uint8_t), bool* const err);
  uint16_t tal_accum_u16(const uint16_t* const mem, const int32_t size,
      uint16_t (*fn)(uint16_t, uint16_t), bool* const err);
  uint32_t tal_accum_u32(const uint32_t* const mem, const int32_t size,
      uint32_t (*fn)(uint32_t, uint32_t), bool* const err);
  uint64_t tal_accum_u64(const uint64_t* const mem, const int32_t size,
      uint64_t (*fn)(uint64_t, uint64_t), bool* const err);
  float tal_accum_f(const float* const mem, const int32_t size,
      float (*fn)(float, float), bool* const err);
  double tal_accum_d(const double* const mem, const int32_t size,
      double (*fn)(double, double), bool* const err);

  /**************************************************************************************************
   * @section Checked Arithmetic
   **************************************************************************************************/

  int8_t tal_try_neg_i8(const int8_t lhs, bool* const err);
  int16_t tal_try_neg_i16(const int16_t lhs, bool* const err);
  int32_t tal_try_neg_i32(const int32_t lhs, bool* const err);
  int64_t tal_try_neg_i64(const int64_t lhs, bool* const err);

  float tal_try_neg_f(const float lhs, bool* const err);
  double tal_try_neg_d(const double lhs, bool* const err);


  int8_t tal_try_add_i8(const int8_t lhs, const int8_t rhs, 
      bool* const err);
  int16_t tal_try_add_i16(const int16_t lhs, const int16_t rhs, 
      bool* const err);
  int32_t tal_try_add_i32(const int32_t lhs, const int32_t rhs, 
      bool* const err);
  int64_t tal_try_add_i64(const int64_t lhs, const int64_t rhs, 
      bool* const err);

  uint8_t tal_try_add_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const err);
  uint16_t tal_try_add_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const err);
  uint32_t tal_try_add_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const err);
  uint64_t tal_try_add_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const err);

  float tal_try_add_f(const float lhs, const float rhs, bool* const err);
  double tal_try_add_d(const double lhs, const double rhs, bool* const err);


  int8_t tal_try_sub_i8(const int8_t lhs, const int8_t rhs, 
      bool* const err);
  int16_t tal_try_sub_i16(const int16_t lhs, const int16_t rhs, 
      bool* const err);
  int32_t tal_try_sub_i32(const int32_t lhs, const int32_t rhs, 
      bool* const err);
  int64_t tal_try_sub_i64(const int64_t lhs, const int64_t rhs, 
      bool* const err);

  uint8_t tal_try_sub_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const err);
  uint16_t tal_try_sub_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const err);
  uint32_t tal_try_sub_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const err);
  uint64_t tal_try_sub_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const err);

  float tal_try_sub_f(const float lhs, const float rhs, bool* const err);
  double tal_try_sub_d(const double lhs, const double rhs, bool* const err);


  int8_t tal_try_mul_i8(const int8_t lhs, const int8_t rhs, 
      bool* const err);
  int16_t tal_try_mul_i16(const int16_t lhs, const int16_t rhs, 
      bool* const err);
  int32_t tal_try_mul_i32(const int32_t lhs, const int32_t rhs, 
      bool* const err);
  int64_t tal_try_mul_i64(const int64_t lhs, const int64_t rhs, 
      bool* const err);

  uint8_t tal_try_mul_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const err);
  uint16_t tal_try_mul_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const err);
  uint32_t tal_try_mul_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const err);
  uint64_t tal_try_mul_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const err);

  float tal_try_mul_f(const float lhs, const float rhs, bool* const err);
  double tal_try_mul_d(const double lhs, const double rhs, bool* const err);


  int8_t tal_try_div_i8(const int8_t lhs, const int8_t rhs, 
      bool* const err);
  int16_t tal_try_div_i16(const int16_t lhs, const int16_t rhs, 
      bool* const err);
  int32_t tal_try_div_i32(const int32_t lhs, const int32_t rhs, 
      bool* const err);
  int64_t tal_try_div_i64(const int64_t lhs, const int64_t rhs, 
      bool* const err);

  uint8_t tal_try_div_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const err);
  uint16_t tal_try_div_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const err);
  uint32_t tal_try_div_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const err);
  uint64_t tal_try_div_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const err);

  float tal_try_div_f(const float lhs, const float rhs, bool* const err);
  double tal_try_div_d(const double lhs, const double rhs, bool* const err);

  int8_t tal_try_mod_i8(const int8_t lhs, const int8_t rhs, 
      bool* const err);
  int16_t tal_try_mod_i16(const int16_t lhs, const int16_t rhs, 
      bool* const err);
  int32_t tal_try_mod_i32(const int32_t lhs, const int32_t rhs, 
      bool* const err);
  int64_t tal_try_mod_i64(const int64_t lhs, const int64_t rhs, 
      bool* const err);

  uint8_t tal_try_mod_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const err);
  uint16_t tal_try_mod_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const err);
  uint32_t tal_try_mod_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const err);
  uint64_t tal_try_mod_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const err);


  int8_t tal_try_lshift_i8(const int8_t lhs, const int32_t rhs, 
      bool* const err);
  int16_t tal_try_lshift_i16(const int16_t lhs, const int32_t rhs, 
      bool* const err);
  int32_t tal_try_lshift_i32(const int32_t lhs, const int32_t rhs, 
      bool* const err);
  int64_t tal_try_lshift_i64(const int64_t lhs, const int32_t rhs, 
      bool* const err);

  uint8_t tal_try_lshift_u8(const uint8_t lhs, const int32_t rhs, 
      bool* const err);
  uint16_t tal_try_lshift_u16(const uint16_t lhs, const int32_t rhs, 
      bool* const err);
  uint32_t tal_try_lshift_u32(const uint32_t lhs, const int32_t rhs, 
      bool* const err);
  uint64_t tal_try_lshift_u64(const uint64_t lhs, const int32_t rhs, 
      bool* const err);


  int8_t tal_try_rshift_i8(const int8_t lhs, const int32_t rhs, 
      bool* const err);
  int16_t tal_try_rshift_i16(const int16_t lhs, const int32_t rhs, 
      bool* const err);
  int32_t tal_try_rshift_i32(const int32_t lhs, const int32_t rhs, 
      bool* const err);
  int64_t tal_try_rshift_i64(const int64_t lhs, const int32_t rhs, 
      bool* const err);

  uint8_t tal_try_rshift_u8(const uint8_t lhs, const int32_t rhs, 
      bool* const err);
  uint16_t tal_try_rshift_u16(const uint16_t lhs, const int32_t rhs, 
      bool* const err);
  uint32_t tal_try_rshift_u32(const uint32_t lhs, const int32_t rhs, 
      bool* const err);
  uint64_t tal_try_rshift_u64(const uint64_t lhs, const int32_t rhs, 
      bool* const err);

  /**************************************************************************************************
   * @section Saturating Arithmetic
   **************************************************************************************************/

  int8_t tal_sat_neg_i8(const int8_t value, bool* const sat);
  int16_t tal_sat_neg_i16(const int16_t value, bool* const sat);
  int32_t tal_sat_neg_i32(const int32_t value, bool* const sat);
  int64_t tal_sat_neg_i64(const int64_t value, bool* const sat);

  float tal_sat_neg_f(const float value, bool* const sat);
  double tal_sat_neg_d(const double value, bool* const sat);


  int8_t tal_sat_add_i8(const int8_t lhs, const int8_t rhs, 
      bool* const sat);
  int16_t tal_sat_add_i16(const int16_t lhs, const int16_t rhs, 
      bool* const sat);
  int32_t tal_sat_add_i32(const int32_t lhs, const int32_t rhs, 
      bool* const sat);
  int64_t tal_sat_add_i64(const int64_t lhs, const int64_t rhs, 
      bool* const sat);

  uint8_t tal_sat_add_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const sat);
  uint16_t tal_sat_add_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const sat);
  uint32_t tal_sat_add_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const sat);
  uint64_t tal_sat_add_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const sat);

  float tal_sat_add_f(const float lhs, const float rhs, bool* const sat);
  double tal_sat_add_d(const double lhs, const double rhs, bool* const sat);


  int8_t tal_sat_sub_i8(const int8_t lhs, const int8_t rhs, 
      bool* const sat);
  int16_t tal_sat_sub_i16(const int16_t lhs, const int16_t rhs, 
      bool* const sat);
  int32_t tal_sat_sub_i32(const int32_t lhs, const int32_t rhs, 
      bool* const sat);
  int64_t tal_sat_sub_i64(const int64_t lhs, const int64_t rhs, 
      bool* const sat);

  uint8_t tal_sat_sub_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const sat);
  uint16_t tal_sat_sub_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const sat);
  uint32_t tal_sat_sub_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const sat);
  uint64_t tal_sat_sub_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const sat);

  float tal_sat_sub_f(const float lhs, const float rhs, bool* const sat);
  double tal_sat_sub_d(const double lhs, const double rhs, bool* const sat);


  int8_t tal_sat_mul_i8(const int8_t lhs, const int8_t rhs, 
      bool* const sat);
  int16_t tal_sat_mul_i16(const int16_t lhs, const int16_t rhs, 
      bool* const sat);
  int32_t tal_sat_mul_i32(const int32_t lhs, const int32_t rhs, 
      bool* const sat);
  int64_t tal_sat_mul_i64(const int64_t lhs, const int64_t rhs, 
      bool* const sat);

  uint8_t tal_sat_mul_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const sat);
  uint16_t tal_sat_mul_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const sat);
  uint32_t tal_sat_mul_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const sat);
  uint64_t tal_sat_mul_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const sat);

  float tal_sat_mul_f(const float lhs, const float rhs, bool* const sat);
  double tal_sat_mul_d(const double lhs, const double rhs, bool* const sat);


  int8_t tal_sat_div_i8(const int8_t lhs, const int8_t rhs, 
      bool* const sat);
  int16_t tal_sat_div_i16(const int16_t lhs, const int16_t rhs, 
      bool* const sat);
  int32_t tal_sat_div_i32(const int32_t lhs, const int32_t rhs, 
      bool* const sat);
  int64_t tal_sat_div_i64(const int64_t lhs, const int64_t rhs, 
      bool* const sat);

  uint8_t tal_sat_div_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const sat);
  uint16_t tal_sat_div_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const sat);
  uint32_t tal_sat_div_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const sat);
  uint64_t tal_sat_div_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const sat);

  float tal_sat_div_f(const float lhs, const float rhs, bool* const sat);
  double tal_sat_div_d(const double lhs, const double rhs, bool* const sat);


  int8_t tal_sat_mod_i8(const int8_t lhs, const int8_t rhs, 
      bool* const sat);
  int16_t tal_sat_mod_i16(const int16_t lhs, const int16_t rhs, 
      bool* const sat);
  int32_t tal_sat_mod_i32(const int32_t lhs, const int32_t rhs, 
      bool* const sat);
  int64_t tal_sat_mod_i64(const int64_t lhs, const int64_t rhs, 
      bool* const sat);

  uint8_t tal_sat_mod_u8(const uint8_t lhs, const uint8_t rhs, 
      bool* const sat);
  uint16_t tal_sat_mod_u16(const uint16_t lhs, const uint16_t rhs, 
      bool* const sat);
  uint32_t tal_sat_mod_u32(const uint32_t lhs, const uint32_t rhs, 
      bool* const sat);
  uint64_t tal_sat_mod_u64(const uint64_t lhs, const uint64_t rhs, 
      bool* const sat);


  int8_t tal_sat_lshift_i8(const int8_t lhs, const int32_t rhs, 
      bool* const sat);
  int16_t tal_sat_lshift_i16(const int16_t lhs, const int32_t rhs, 
      bool* const sat);
  int32_t tal_sat_lshift_i32(const int32_t lhs, const int32_t rhs, 
      bool* const sat);
  int64_t tal_sat_lshift_i64(const int64_t lhs, const int32_t rhs, 
      bool* const sat);

  uint8_t tal_sat_lshift_u8(const uint8_t lhs, const int32_t rhs, 
      bool* const sat);
  uint16_t tal_sat_lshift_u16(const uint16_t lhs, const int32_t rhs, 
      bool* const sat);
  uint32_t tal_sat_lshift_u32(const uint32_t lhs, const int32_t rhs, 
      bool* const sat);
  uint64_t tal_sat_lshift_u64(const uint64_t lhs, const int32_t rhs, 
      bool* const sat);


  int8_t tal_sat_rshift_i8(const int8_t lhs, const int32_t rhs, 
      bool* const sat);
  int16_t tal_sat_rshift_i16(const int16_t lhs, const int32_t rhs, 
      bool* const sat);
  int32_t tal_sat_rshift_i32(const int32_t lhs, const int32_t rhs, 
      bool* const sat);
  int64_t tal_sat_rshift_i64(const int64_t lhs, const int32_t rhs, 
      bool* const sat);

  uint8_t tal_sat_rshift_u8(const uint8_t lhs, const int32_t rhs, 
      bool* const sat);
  uint16_t tal_sat_rshift_u16(const uint16_t lhs, const int32_t rhs, 
      bool* const sat);
  uint32_t tal_sat_rshift_u32(const uint32_t lhs, const int32_t rhs, 
      bool* const sat);
  uint64_t tal_sat_rshift_u64(const uint64_t lhs, const int32_t rhs, 
      bool* const sat);

   /**************************************************************************************************
   * @section Checked Type Conversion
   **************************************************************************************************/

  /**
   * @defgroup @b tal_try_cast (int)
   * @brief TODO
   * @param value (any numeric type)
   * @param err (bool*)
   * @returns (integer type denoted by suffix)
   * @{
   */
  #define tal_try_cast_i8(value, err)
  #define tal_try_cast_i16(value, err)
  #define tal_try_cast_i32(value, err)
  #define tal_try_cast_i64(value, err)
  #define tal_try_cast_u8(value, err)
  #define tal_try_cast_u16(value, err)
  #define tal_try_cast_u32(value, err)
  #define tal_try_cast_u64(value, err)
  /** @} */

  /**
   * @defgroup @b tal_try_cast (fp)
   * @brief TODO
   * @param value (any numeric type)
   * @param err (bool*)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  #define tal_try_cast_f(value, err)
  #define tal_try_cast_d(value, err)
  /** @} */

   /**************************************************************************************************
   * @section Saturating Type Conversion
   **************************************************************************************************/

  #define tal_sat_cast_i8(value, sat)
  #define tal_sat_cast_i16(value, sat)
  #define tal_sat_cast_i32(value, sat)
  #define tal_sat_cast_i64(value, sat)

  #define tal_sat_cast_u8(value, sat)
  #define tal_sat_cast_u16(value, sat)
  #define tal_sat_cast_u32(value, sat)
  #define tal_sat_cast_u64(value, sat)

  #define tal_sat_cast_f(value, sat)
  #define tal_sat_cast_d(value, sat)

   /**************************************************************************************************
   * @section Comparison Utilities
   **************************************************************************************************/

  /**
   * @brief TODO
   * @param lhs (any numeric type)
   * @param rhs (any numeric type)
   * @param err (bool*)
   * @returns (int32_t)
   */
  #define tal_cmp(lhs, rhs, err)

  /**
   * @brief TODO
   * @param lhs (any numeric type)
   * @param rhs (any numeric type)
   * @param abs (any numeric type)
   * @param err (bool*)
   * @returns (int32_t)
   */
  #define tal_abs_cmp(lhs, rhs, abs, err)

  /**
   * @brief TODO
   * @param lhs (any numeric type)
   * @param rhs (any numeric type)
   * @param abs (any numeric type)
   * @param err (bool*)
   * @returns (int32_t)
   */
  #define tal_rel_cmp(lhs, rhs, abs, err)

  /**
   * @brief TODO
   * @param lhs (any numeric type)
   * @param rhs (any numeric type)
   * @param rel (any numeric type)
   * @param err (bool*)
   * @returns (int32_t)
   */
  #define tal_ulp_cmp(lhs, rhs, rel, err)

#if defined(__cplusplus)
  } // extern "C"
#endif