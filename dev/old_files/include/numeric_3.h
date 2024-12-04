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
   * @section Comparison Utilities
   **************************************************************************************************/

  typedef enum {
    tal_equal = 0,
    tal_less = -1,
    tal_greater = 1,
  }tal_cmp_t;

  tal_cmp_t tal_cmp_ii(const int64_t lhs, const int64_t rhs);
  tal_cmp_t tal_cmp_iu(const int64_t lhs, const uint64_t rhs);
  tal_cmp_t tal_cmp_if(const int64_t lhs, const float rhs, 
      const float rel, const float tol, bool* const err);
  tal_cmp_t tal_cmp_uf(const uint64_t lhs, const float rhs,
      const float rel, const float tol, bool* const err);

  tal_cmp_t tal_cmp_uu(const uint64_t lhs, const uint64_t rhs);
  tal_cmp_t tal_cmp_ui(const uint64_t lhs, const int64_t rhs);
  tal_cmp_t tal_cmp_id(const int64_t lhs, const double rhs, 
      const double rel, const double tol, bool* const err);
  tal_cmp_t tal_cmp_ud(const uint64_t lhs, const double rhs,
      const double rel, const double tol, bool* const err);

  tal_cmp_t tal_cmp_ff(const float lhs, const float rhs, 
      const float rel, const float tol, bool* const err);
  tal_cmp_t tal_cmp_fd(const float lhs, const double rhs, 
      const float rel, const float tol, bool* const err);
  tal_cmp_t tal_cmp_fi(const float lhs, const int64_t rhs, 
      const float rel, const float tol, bool* const err);
  tal_cmp_t tal_cmp_fu(const float lhs, const uint64_t rhs,
      const float rel, const float tol, bool* const err);

  tal_cmp_t tal_cmp_dd(const double lhs, const double rhs, 
      const double rel, const double tol, bool* const err);
  tal_cmp_t tal_cmp_df(const double lhs, const float rhs, 
      const double rel, const double tol, bool* const err);
  tal_cmp_t tal_cmp_di(const double lhs, const int64_t rhs, 
      const double rel, const double tol, bool* const err);
  tal_cmp_t tal_cmp_du(const double lhs, const uint64_t rhs,
      const double rel, const double tol, bool* const err);
      
  /**************************************************************************************************
   * @section Arithmetic Utilities
   **************************************************************************************************/

  int8_t tal_neg_i8(const int8_t value, bool* const err);
  int16_t tal_neg_i16(const int16_t value, bool* const err);
  int32_t tal_neg_i32(const int32_t value, bool* const err);
  int64_t tal_neg_i64(const int64_t value, bool* const err);

  float tal_neg_f(const float value, bool* const err);
  double tal_neg_d(const double value, bool* const err);


  int8_t tal_add_i8(const int8_t lhs, const int8_t rhs, bool* const err);
  int16_t tal_add_i16(const int16_t lhs, const int16_t rhs, bool* const err);
  int32_t tal_add_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_add_i64(const int64_t lhs, const int64_t rhs, bool* const err);

  uint8_t tal_add_u8(const uint8_t lhs, const uint8_t rhs, bool* const err);
  uint16_t tal_add_u16(const uint16_t lhs, const uint16_t rhs, bool* const err);
  uint32_t tal_add_u32(const uint32_t lhs, const uint32_t rhs, bool* const err);
  uint64_t tal_add_u64(const uint64_t lhs, const uint64_t rhs, bool* const err);

  float tal_add_f(const float lhs, const float rhs, bool* const err);
  double tal_add_d(const double lhs, const double rhs, bool* const err);


  int8_t tal_sub_i8(const int8_t lhs, const int8_t rhs, bool* const err);
  int16_t tal_sub_i16(const int16_t lhs, const int16_t rhs, bool* const err);
  int32_t tal_sub_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_sub_i64(const int64_t lhs, const int64_t rhs, bool* const err);

  uint8_t tal_sub_u8(const uint8_t lhs, const uint8_t rhs, bool* const err);
  uint16_t tal_sub_u16(const uint16_t lhs, const uint16_t rhs, bool* const err);
  uint32_t tal_sub_u32(const uint32_t lhs, const uint32_t rhs, bool* const err);
  uint64_t tal_sub_u64(const uint64_t lhs, const uint64_t rhs, bool* const err);

  float tal_sub_f(const float lhs, const float rhs, bool* const err);
  double tal_sub_d(const double lhs, const double rhs, bool* const err);


  int8_t tal_mul_i8(const int8_t lhs, const int8_t rhs, bool* const err);
  int16_t tal_mul_i16(const int16_t lhs, const int16_t rhs, bool* const err);
  int32_t tal_mul_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_mul_i64(const int64_t lhs, const int64_t rhs, bool* const err);

  uint8_t tal_mul_u8(const uint8_t lhs, const uint8_t rhs, bool* const err);
  uint16_t tal_mul_u16(const uint16_t lhs, const uint16_t rhs, bool* const err);
  uint32_t tal_mul_u32(const uint32_t lhs, const uint32_t rhs, bool* const err);
  uint64_t tal_mul_u64(const uint64_t lhs, const uint64_t rhs, bool* const err);

  float tal_mul_f(const float lhs, const float rhs, bool* const err);
  double tal_mul_d(const double lhs, const double rhs, bool* const err);


  int8_t tal_div_i8(const int8_t lhs, const int8_t rhs, bool* const err);
  int16_t tal_div_i16(const int16_t lhs, const int16_t rhs, bool* const err);
  int32_t tal_div_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_div_i64(const int64_t lhs, const int64_t rhs, bool* const err);

  uint8_t tal_div_u8(const uint8_t lhs, const uint8_t rhs, bool* const err);
  uint16_t tal_div_u16(const uint16_t lhs, const uint16_t rhs, bool* const err);
  uint32_t tal_div_u32(const uint32_t lhs, const uint32_t rhs, bool* const err);
  uint64_t tal_div_u64(const uint64_t lhs, const uint64_t rhs, bool* const err);

  float tal_div_f(const float lhs, const float rhs, bool* const err);
  double tal_div_d(const double lhs, const double rhs, bool* const err);


  int8_t tal_mod_i8(const int8_t lhs, const int8_t rhs, bool* const err);
  int16_t tal_mod_i16(const int16_t lhs, const int16_t rhs, bool* const err);
  int32_t tal_mod_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_mod_i64(const int64_t lhs, const int64_t rhs, bool* const err);

  uint8_t tal_mod_u8(const uint8_t lhs, const uint8_t rhs, bool* const err);
  uint16_t tal_mod_u16(const uint16_t lhs, const uint16_t rhs, bool* const err);
  uint32_t tal_mod_u32(const uint32_t lhs, const uint32_t rhs, bool* const err);
  uint64_t tal_mod_u64(const uint64_t lhs, const uint64_t rhs, bool* const err);


  int8_t tal_lshift_i8(const int8_t lhs, const int32_t rhs, bool* const err);
  int16_t tal_lshift_i16(const int16_t lhs, const int32_t rhs, bool* const err);
  int32_t tal_lshift_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_lshift_i64(const int64_t lhs, const int32_t rhs, bool* const err);

  uint8_t tal_lshift_u8(const uint8_t lhs, const int32_t rhs, bool* const err);
  uint16_t tal_lshift_u16(const uint16_t lhs, const int32_t rhs, bool* const err);
  uint32_t tal_lshift_u32(const uint32_t lhs, const int32_t rhs, bool* const err);
  uint64_t tal_lshift_u64(const uint64_t lhs, const int32_t rhs, bool* const err);


  int8_t tal_rshift_i8(const int8_t lhs, const int32_t rhs, bool* const err);
  int16_t tal_rshift_i16(const int16_t lhs, const int32_t rhs, bool* const err);
  int32_t tal_rshift_i32(const int32_t lhs, const int32_t rhs, bool* const err);
  int64_t tal_rshift_i64(const int64_t lhs, const int32_t rhs, bool* const err);

  uint8_t tal_rshift_u8(const uint8_t lhs, const int32_t rhs, bool* const err);
  uint16_t tal_rshift_u16(const uint16_t lhs, const int32_t rhs, bool* const err);
  uint32_t tal_rshift_u32(const uint32_t lhs, const int32_t rhs, bool* const err);
  uint64_t tal_rshift_u64(const uint64_t lhs, const int32_t rhs, bool* const err);

  /**************************************************************************************************
   * @section Aggregate Arithmetic Utilities
   **************************************************************************************************/

  int8_t tal_summation_i8(const int8_t* const values, 
      const int32_t n, bool* const err);
  int16_t tal_summation_i16(const int16_t* const values, 
      const int32_t n, bool* const err);
  int32_t tal_summation_i32(const int32_t* const values, 
      const int32_t n, bool* const err);
  int64_t tal_summation_i64(const int64_t* const values, 
      const int32_t n, bool* const err);

  uint8_t tal_summation_u8(const uint8_t* const values, 
      const int32_t n, bool* const err);
  uint16_t tal_summation_u16(const uint16_t* const values, 
      const int32_t n, bool* const err);
  uint32_t tal_summation_u32(const uint32_t* const values, 
      const int32_t n, bool* const err);
  uint64_t tal_summation_u64(const uint64_t* const values, 
      const int32_t n, bool* const err);

  float tal_summation_f(const float* const values, 
      const int32_t n, bool* const err);
  double tal_summation_d(const double* const values,
      const int32_t n, bool* const err);


  int8_t tal_product_i8(const int8_t* const values, 
      const int32_t n, bool* const err);
  int16_t tal_product_i16(const int16_t* const values,
      const int32_t n, bool* const err);
  int32_t tal_product_i32(const int32_t* const values,
      const int32_t n, bool* const err);
  int64_t tal_product_i64(const int64_t* const values,
      const int32_t n, bool* const err);
  
  uint8_t tal_product_u8(const uint8_t* const values,
      const int32_t n, bool* const err);
  uint16_t tal_product_u16(const uint16_t* const values,
      const int32_t n, bool* const err);
  uint32_t tal_product_u32(const uint32_t* const values,
      const int32_t n, bool* const err);
  uint64_t tal_product_u64(const uint64_t* const values,
      const int32_t n, bool* const err);

  float tal_product_f(const float* const values,
      const int32_t n, bool* const err);
  double tal_product_d(const double* const values,
      const int32_t n, bool* const err);

  /**************************************************************************************************
   * @section Casting Utilities
   **************************************************************************************************/

  int8_t tal_cast_i8i(const int64_t value, bool* const err);
  int16_t tal_cast_i16i(const int64_t value, bool* const err);
  int32_t tal_cast_i32i(const int64_t value, bool* const err);

  int8_t tal_cast_i8u(const uint64_t value, bool* const err);
  int16_t tal_cast_i16u(const uint64_t value, bool* const err);
  int32_t tal_cast_i32u(const uint64_t value, bool* const err);
  int64_t tal_cast_i64u(const uint64_t value, bool* const err);

  int8_t tal_cast_i8f(const float value, bool* const err);
  int16_t tal_cast_i16f(const float value, bool* const err);
  int32_t tal_cast_i32f(const float value, bool* const err);
  int64_t tal_cast_i64f(const float value, bool* const err);

  int8_t tal_cast_i8d(const double value, bool* const err);
  int16_t tal_cast_i16d(const double value, bool* const err);
  int32_t tal_cast_i32d(const double value, bool* const err);
  int64_t tal_cast_i64d(const double value, bool* const err);

  uint8_t tal_cast_u8i(const int64_t value, bool* const err);
  uint16_t tal_cast_u16i(const int64_t value, bool* const err);
  uint32_t tal_cast_u32i(const int64_t value, bool* const err);
  uint64_t tal_cast_u64i(const int64_t value, bool* const err);

  uint8_t tal_cast_u8u(const uint64_t value, bool* const err);
  uint16_t tal_cast_u16u(const uint64_t value, bool* const err);
  uint32_t tal_cast_u32u(const uint64_t value, bool* const err);

  uint8_t tal_cast_u8f(const float value, bool* const err);
  uint16_t tal_cast_u16f(const float value, bool* const err);
  uint32_t tal_cast_u32f(const float value, bool* const err);
  uint64_t tal_cast_u64f(const float value, bool* const err);

  uint8_t tal_cast_u8d(const double value, bool* const err);
  uint16_t tal_cast_u16d(const double value, bool* const err);
  uint32_t tal_cast_u32d(const double value, bool* const err);
  uint64_t tal_cast_u64d(const double value, bool* const err);

  float tal_cast_fi(const int64_t value, const float rel,
      const float tol, bool* const err);
  float tal_cast_fu(const uint64_t value, const float rel,
      const float tol, bool* const err);
  float tal_cast_fd(const double value, const float rel,
      const float tol, bool* const err);

  double tal_cast_di(const int64_t value, const double rel,
      const double tol, bool* const err);
  double tal_cast_du(const uint64_t value, const double rel,
      const double tol, bool* const err);
  double tal_cast_df(const float value, const double rel, 
      const double tol, bool* const err);

  /**************************************************************************************************
   * @section Core Numeric Utilities
   **************************************************************************************************/

  int8_t tal_abs_i8(const int8_t value, bool* const err);
  int16_t tal_abs_i16(const int16_t value, bool* const err);
  int32_t tal_abs_i32(const int32_t value, bool* const err);
  int64_t tal_abs_i64(const int64_t value, bool* const err);

  float tal_abs_f(const float value, bool* const err);
  double tal_abs_d(const double value, bool* const err);


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

  /**************************************************************************************************
   * @section Miscellaneous Numeric Utilities
   **************************************************************************************************/

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


  void tal_swap_i8(int8_t* const lhs, int8_t* const rhs, 
      bool* const err);
  void tal_swap_i16(int16_t* const lhs, int16_t* const rhs, 
      bool* const err);
  void tal_swap_i32(int32_t* const lhs, int32_t* const rhs,
      bool* const err);
  void tal_swap_i64(int64_t* const lhs, int64_t* const rhs,
      bool* const err);
  
  void tal_swap_u8(uint8_t* const lhs, uint8_t* const rhs,
      bool* const err);
  void tal_swap_u16(uint16_t* const lhs, uint16_t* const rhs,
      bool* const err);
  void tal_swap_u32(uint32_t* const lhs, uint32_t* const rhs,
      bool* const err);
  void tal_swap_u64(uint64_t* const lhs, uint64_t* const rhs,
      bool* const err);
  
  void tal_swap_f(float* const lhs, float* const rhs,
      bool* const err);
  void tal_swap_d(double* const lhs, double* const rhs,
      bool* const err);

#if defined(__cplusplus)
  }
#endif
