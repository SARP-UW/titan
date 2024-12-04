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
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
  extern "C" {
#endif

   /**************************************************************************************************
   * @section Core Numeric Utilities
   **************************************************************************************************/

  int8_t tal_abs_i8(const int8_t value, bool* const err);
  int16_t tal_abs_i16(const int16_t value, bool* const err);
  int32_t tal_abs_i32(const int32_t value, bool* const err);
  int64_t tal_abs_i64(const int64_t value, bool* const err);

  float tal_abs_f(const float value, bool* const err);
  double tal_abs_d(const double value, bool* const err);


  int8_t tal_min2_i8(const int8_t lhs, const int8_t rhs, bool* const err);
  int16_t tal_min2_i16(const int16_t lhs, const int16_t rhs, bool* const err);
  int32_t tal_min2_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_min2_i64(const int64_t lhs, const int64_t rhs, bool* const err);

  uint8_t tal_min2_u8(const uint8_t lhs, const uint8_t rhs, bool* const err);
  uint16_t tal_min2_u16(const uint16_t lhs, const uint16_t rhs, bool* const err);
  uint32_t tal_min2_u32(const uint32_t lhs, const uint32_t rhs, bool* const err);
  uint64_t tal_min2_u64(const uint64_t lhs, const uint64_t rhs, bool* const err);

  float tal_min2_f(const float lhs, const float rhs, bool* const err);
  double tal_min2_d(const double lhs, const double rhs, bool* const err);


  int8_t tal_max2_i8(const int8_t lhs, const int8_t rhs, bool* const err);
  int16_t tal_max2_i16(const int16_t lhs, const int16_t rhs, bool* const err);
  int32_t tal_max2_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_max2_i64(const int64_t lhs, const int64_t rhs, bool* const err);

  uint8_t tal_max2_u8(const uint8_t lhs, const uint8_t rhs, bool* const err);
  uint16_t tal_max2_u16(const uint16_t lhs, const uint16_t rhs, bool* const err);
  uint32_t tal_max2_u32(const uint32_t lhs, const uint32_t rhs, bool* const err);
  uint64_t tal_max2_u64(const uint64_t lhs, const uint64_t rhs, bool* const err);

  float tal_max2_f(const float lhs, const float rhs, bool* const err);
  double tal_max2_d(const double lhs, const double rhs, bool* const err);


  #define tal_icmp(lhs, rhs)
  #define tal_fcmp(lhs, rhs, rel, tol, err)


  int8_t tal_clamp_i8(const int8_t value, const int8_t bound_a, 
      const int8_t bound_b, bool* const err);
  int16_t tal_clamp_i16(const int16_t value, const int16_t bound_a,
      const int16_t bound_b, bool* const err);
  int32_t tal_clamp_i32(const int32_t value, const int32_t bound_a,
      const int32_t bound_b, bool* const err);
  int64_t tal_clamp_i64(const int64_t value, const int64_t bound_a,
      const int64_t bound_b, bool* const err);
  
  uint8_t tal_clamp_u8(const uint8_t value, const uint8_t bound_a,
      const uint8_t bound_b, bool* const err);
  uint16_t tal_clamp_u16(const uint16_t value, const uint16_t bound_a,
      const uint16_t bound_b, bool* const err);
  uint32_t tal_clamp_u32(const uint32_t value, const uint32_t bound_a,
      const uint32_t bound_b, bool* const err);
  uint64_t tal_clamp_u64(const uint64_t value, const uint64_t bound_a,
      const uint64_t bound_b, bool* const err);
  
  float tal_clamp_f(const float value, const float bound_a, const float bound_b, 
      bool* const err);
  double tal_clamp_d(const double value, const double bound_a, const double bound_b, 
      bool* const err);

  
  int8_t tal_in_range_i8(const int8_t value, const int8_t bound_a, 
      const int8_t bound_b, bool* const err);
  int16_t tal_in_range_i16(const int16_t value, const int16_t bound_a,
      const int16_t bound_b, bool* const err);
  int32_t tal_in_range_i32(const int32_t value, const int32_t bound_a,
      const int32_t bound_b, bool* const err);
  int64_t tal_in_range_i64(const int64_t value, const int64_t bound_a,
      const int64_t bound_b, bool* const err);
  
  uint8_t tal_in_range_u8(const uint8_t value, const uint8_t bound_a,
      const uint8_t bound_b, bool* const err);
  uint16_t tal_in_range_u16(const uint16_t value, const uint16_t bound_a,
      const uint16_t bound_b, bool* const err);
  uint32_t tal_in_range_u32(const uint32_t value, const uint32_t bound_a,
      const uint32_t bound_b, bool* const err);
  uint64_t tal_in_range_u64(const uint64_t value, const uint64_t bound_a,
      const uint64_t bound_b, bool* const err);
  
  float tal_in_range_f(const float value, const float bound_a, 
      const float bound_b, bool* const err);
  double tal_in_range_d(const double value, const double bound_a, 
      const double bound_b, bool* const err);


  int8_t tal_copy_sign_i8(const int8_t value, const int8_t sign, 
      bool* const err);
  int16_t tal_copy_sign_i16(const int16_t value, const int16_t sign, 
      bool* const err);
  int32_t tal_copy_sign_i32(const int32_t value, const int32_t sign, 
      bool* const err);
  int64_t tal_copy_sign_i64(const int64_t value, const int64_t sign, 
      bool* const err);

  float tal_copy_sign_f(const float value, const float sign,
      bool* const err);
  double tal_copy_sign_d(const double value, const double sign, 
      bool* const err);

   /**************************************************************************************************
   * @section Aggregate Numeric Utilities
   **************************************************************************************************/

  int8_t tal_min_i8(const int8_t* const values, const int32_t n, 
      bool* const err);
  int16_t tal_min_i16(const int16_t* const values, const int32_t n, 
      bool* const err);
  int32_t tal_min_i32(const int32_t* const values, const int32_t n, 
      bool* const err);
  int64_t tal_min_i64(const int64_t* const values, const int32_t n, 
      bool* const err);
  
  uint8_t tal_min_u8(const uint8_t* const values, const int32_t n, 
      bool* const err);
  uint16_t tal_min_u16(const uint16_t* const values, const int32_t n, 
      bool* const err);
  uint32_t tal_min_u32(const uint32_t* const values, const int32_t n, 
      bool* const err);
  uint64_t tal_min_u64(const uint64_t* const values, const int32_t n, 
      bool* const err);
  
  float tal_min_f(const float* const values, const int32_t n, 
      bool* const err);
  double tal_min_d(const double* const values, const int32_t n, 
      bool* const err);


  int8_t tal_max_i8(const int8_t* const values, const int32_t n, 
      bool* const err);
  int16_t tal_max_i16(const int16_t* const values, const int32_t n,
      bool* const err);
  int32_t tal_max_i32(const int32_t* const values, const int32_t n,
      bool* const err);
  int64_t tal_max_i64(const int64_t* const values, const int32_t n,
      bool* const err);
  
  uint8_t tal_max_u8(const uint8_t* const values, const int32_t n,
      bool* const err);
  uint16_t tal_max_u16(const uint16_t* const values, const int32_t n,
      bool* const err);
  uint32_t tal_max_u32(const uint32_t* const values, const int32_t n,
      bool* const err);
  uint64_t tal_max_u64(const uint64_t* const values, const int32_t n,
      bool* const err);
  
  float tal_max_f(const float* const values, const int32_t n,
      bool* const err);
  double tal_max_d(const double* const values, const int32_t n,
      bool* const err);


  int8_t tal_summation_i8(const int8_t* const values, const int32_t n, 
      bool* const err);
  int16_t tal_summation_i16(const int16_t* const values, const int32_t n, 
      bool* const err);
  int32_t tal_summation_i32(const int32_t* const values, const int32_t n, 
      bool* const err);
  int64_t tal_summation_i64(const int64_t* const values, const int32_t n, 
      bool* const err);

  uint8_t tal_summation_u8(const uint8_t* const values, const int32_t n, 
      bool* const err);
  uint16_t tal_summation_u16(const uint16_t* const values, const int32_t n, 
      bool* const err);
  uint32_t tal_summation_u32(const uint32_t* const values, const int32_t n, 
      bool* const err);
  uint64_t tal_summation_u64(const uint64_t* const values, const int32_t n, 
      bool* const err);

  float tal_summation_f(const float* const values, const int32_t n, 
      bool* const err);
  double tal_summation_d(const double* const values, const int32_t n, 
      bool* const err);
  
  
  int8_t tal_product_i8(const int8_t* const values, const int32_t n,
      bool* const err);
  int16_t tal_product_i16(const int16_t* const values, const int32_t n,
      bool* const err);
  int32_t tal_product_i32(const int32_t* const values, const int32_t n,
      bool* const err);
  int64_t tal_product_i64(const int64_t* const values, const int32_t n,
      bool* const err);

  uint8_t tal_product_u8(const uint8_t* const values, const int32_t n,
      bool* const err);
  uint16_t tal_product_u16(const uint16_t* const values, const int32_t n,
      bool* const err);
  uint32_t tal_product_u32(const uint32_t* const values, const int32_t n,
      bool* const err);
  uint64_t tal_product_u64(const uint64_t* const values, const int32_t n,
      bool* const err);

  float tal_product_f(const float* const values, const int32_t n, 
      bool* const err);
  double tal_product_d(const double* const values, const int32_t n, 
      bool* const err);


  int8_t tal_accum_i8(const int8_t* const values, const int32_t n,
      int8_t (*op)(const int8_t*, int8_t), bool* const err);
  int16_t tal_accum_i16(const int16_t* const values, const int32_t n,
      int16_t (*op)(const int16_t*, int16_t), bool* const err);
  int32_t tal_accum_i32(const int32_t* const values, const int32_t n,
      int32_t (*op)(const int32_t*, int32_t), bool* const err);
  int64_t tal_accum_i64(const int64_t* const values, const int32_t n,
      int64_t (*op)(const int64_t*, int64_t), bool* const err);
  
  uint8_t tal_accum_u8(const uint8_t* const values, const int32_t n,
      uint8_t (*op)(const uint8_t*, uint8_t), bool* const err);
  uint16_t tal_accum_u16(const uint16_t* const values, const int32_t n,
      uint16_t (*op)(const uint16_t*, uint16_t), bool* const err);
  uint32_t tal_accum_u32(const uint32_t* const values, const int32_t n,
      uint32_t (*op)(const uint32_t*, uint32_t), bool* const err);
  uint64_t tal_accum_u64(const uint64_t* const values, const int32_t n,
      uint64_t (*op)(const uint64_t*, uint64_t), bool* const err);

  float tal_accum_f(const float* const values, const int32_t n,
      float (*op)(const float*, float), bool* const err);
  double tal_accum_d(const double* const values, const int32_t n,
      double (*op)(const double*, double), bool* const err);
  
  /**************************************************************************************************
   * @section Checked Arithmetic Utilities
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
   * @section Saturating Arithmetic Utilities
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
   * @section Checked Type Conversion Utilities
   **************************************************************************************************/

  #define tal_try_cast_i8(value, err)
  #define tal_try_cast_i16(value, err)
  #define tal_try_cast_i32(value, err)
  #define tal_try_cast_i64(value, err)

  #define tal_try_cast_u8(value, err)
  #define tal_try_cast_u16(value, err)
  #define tal_try_cast_u32(value, err)
  #define tal_try_cast_u64(value, err)

  #define tal_try_cast_f(value, err)
  #define tal_try_cast_d(value, err)

   /**************************************************************************************************
   * @section Saturating Type Conversion Utilities
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


#if defined(__cplusplus)
  } // extern "C"
#endif