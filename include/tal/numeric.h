/**
 * This file is part of the Titan Avionics Library
 * Copyright (c) 2024 UW SARP
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WmemANTY; without even the implied wmemanty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * @file include/tal/numeric.h
 * @authors Aaron McBride
 * @brief Core numeric utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Range Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_clamp (int)
   * @brief TODO
   * @param value (integer type denoted by suffix)
   * @param b1 (integer type denoted by suffix)
   * @param b2 (integer type denoted by suffix)
   * @returns (integer type denoted by suffix)
   * @{
   */
  int8_t tal_clamp_i8(const int8_t value, const int8_t b1, const int8_t b2);
  int16_t tal_clamp_i16(const int16_t value, const int16_t b1, const int16_t b2);
  int32_t tal_clamp_i32(const int32_t value, const int32_t b1, const int32_t b2);
  int64_t tal_clamp_i64(const int64_t value, const int64_t b1, const int64_t b2);
  uint8_t tal_clamp_u8(const uint8_t value, const uint8_t b1, const uint8_t b2);
  uint16_t tal_clamp_u16(const uint16_t value, const uint16_t b1, const uint16_t b2);
  uint32_t tal_clamp_u32(const uint32_t value, const uint32_t b1, const uint32_t b2);
  uint64_t tal_clamp_u64(const uint64_t value, const uint64_t b1, const uint64_t b2);
  /** @} */

  /**
   * @defgroup @b tal_clamp (fp)
   * @brief TODO
   * @param value (floating point type denoted by suffix)
   * @param b1 (floating point type denoted by suffix)
   * @param b2 (floating point type denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  float tal_clamp_f(const float value, const float b1, const float b2);
  double tal_clamp_d(const double value, const double b1, const double b2);
  /** @} */

  /**
   * @defgroup @b tal_in_range (int)
   * @brief TODO
   * @param value (integer type denoted by suffix)
   * @param b1 (integer type denoted by suffix)
   * @param b2 (integer type denoted by suffix)
   * @returns (bool)
   * @{
   */
  int8_t tal_in_range_i8(const int8_t value, const int8_t b1, const int8_t b2);
  int16_t tal_in_range_i16(const int16_t value, const int16_t b1, const int16_t b2);
  int32_t tal_in_range_i32(const int32_t value, const int32_t b1, const int32_t b2);
  int64_t tal_in_range_i64(const int64_t value, const int64_t b1, const int64_t b2);
  uint8_t tal_in_range_u8(const uint8_t value, const uint8_t b1, const uint8_t b2);
  uint16_t tal_in_range_u16(const uint16_t value, const uint16_t b1, const uint16_t b2);
  uint32_t tal_in_range_u32(const uint32_t value, const uint32_t b1, const uint32_t b2);
  uint64_t tal_in_range_u64(const uint64_t value, const uint64_t b1, const uint64_t b2);
  /** @} */

  /**
   * @defgroup @b tal_in_range (fp)
   * @brief TODO
   * @param value (floating point type denoted by suffix)
   * @param b1 (floating point type denoted by suffix)
   * @param b2 (floating point type denoted by suffix)
   * @returns (bool)
   * @{
   */
  float tal_in_range_f(const float value, const float b1, const float b2);
  double tal_in_range_d(const double value, const double b1, const double b2);
  /** @} */

  /**************************************************************************************************
   * @section Min/Max Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_min (int)
   * @brief TODO
   * @param ... (integer types denoted by suffix)
   * @returns (integer type denoted by suffix)
   * @{
   */
  #define tal_min_i8(...)
  #define tal_min_i16(...)
  #define tal_min_i32(...)
  #define tal_min_i64(...)
  #define tal_min_u8(...)
  #define tal_min_u16(...)
  #define tal_min_u32(...)
  #define tal_min_u64(...)
  /** @} */

  /**
   * @defgroup @b tal_min (fp)
   * @brief TODO
   * @param ... (floating point types denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  #define tal_min_f(...)
  #define tal_min_d(...)
  /** @} */

  /**
   * @defgroup @b tal_max (int)
   * @brief TODO
   * @param ... (integer types denoted by suffix)
   * @returns (integer type denoted by suffix)
   * @{
   */
  #define tal_max_i8(...)
  #define tal_max_i16(...)
  #define tal_max_i32(...)
  #define tal_max_i64(...)
  #define tal_max_u8(...)
  #define tal_max_u16(...)
  #define tal_max_u32(...)
  #define tal_max_u64(...)
  /** @} */

  /**
   * @defgroup @b tal_max (fp)
   * @brief TODO
   * @param ... (floating point types denoted by suffix)
   * @returns (floating point type denoted by suffix)
   * @{
   */
  #define tal_max_f(...)
  #define tal_max_d(...)
  /** @} */

  /**************************************************************************************************
   * @section Sign Utilities
   **************************************************************************************************/

  int8_t tal_abs_i8(const int8_t value, bool* const err);
  int16_t tal_abs_i16(const int16_t value, bool* const err);
  int32_t tal_abs_i32(const int32_t value, bool* const err);
  int64_t tal_abs_i64(const int64_t value, bool* const err);
  float tal_abs_f(const float value, bool* const err);
  double tal_abs_d(const double value, bool* const err);

  int8_t tal_apply_sign_i8(const int8_t mag, const int8_t sign, bool* const err);
  int16_t tal_apply_sign_i16(const int16_t mag, const int16_t sign, bool* const err);
  int32_t tal_apply_sign_i32(const int32_t mag, const int32_t sign, bool* const err);
  int64_t tal_apply_sign_i64(const int64_t mag, const int64_t sign, bool* const err);
  float tal_apply_sign_f(const float mag, const float sign, bool* const err);
  double tal_apply_sign_d(const double mag, const double sign, bool* const err);

  /**************************************************************************************************
   * @section Rounding Utilities
   **************************************************************************************************/

  float tal_floor_f(const float value, bool* const err);
  double tal_floor_d(const double value, bool* const err);

  float tal_trunc_f(const float value, bool* const err);
  double tal_trunc_d(const double value, bool* const err);

  float tal_ceil_f(const float value, bool* const err);
  double tal_ceil_d(const double value, bool* const err);

  float tal_round_f(const float value, bool* const err);
  double tal_round_d(const double value, bool* const err);

  /**************************************************************************************************
   * @section Comparison Utilities
   **************************************************************************************************/

  #define tal_cmp(lhs, rhs, err)

  #define tal_cmp_abs(lhs, rhs, abs, err)

  #define tal_cmp_rel(lhs, rhs, abs, err)

  #define tal_cmp_ulp(lhs, rhs, rel, err)

  /**************************************************************************************************
   * @section Overflow Detection
   **************************************************************************************************/

  #define tal_can_cast_i8(value, err)
  #define tal_can_cast_i16(value, err)
  #define tal_can_cast_i32(value, err)
  #define tal_can_cast_i64(value, err)
  #define tal_can_cast_u8(value, err)
  #define tal_can_cast_u16(value, err)
  #define tal_can_cast_u32(value, err)
  #define tal_can_cast_u64(value, err)
  #define tal_can_cast_f(value, err)
  #define tal_can_cast_d(value, err)

  bool tal_can_neg_i8(const int8_t value);
  bool tal_can_neg_i16(const int16_t value);
  bool tal_can_neg_i32(const int32_t value);
  bool tal_can_neg_i64(const int64_t value);
  bool tal_can_neg_f(const float value);
  bool tal_can_neg_d(const double value);

  bool tal_can_add_i8(const int8_t lhs, const int8_t rhs);
  bool tal_can_add_i16(const int16_t lhs, const int16_t rhs);
  bool tal_can_add_i32(const int32_t lhs, const int32_t rhs);
  bool tal_can_add_i64(const int64_t lhs, const int64_t rhs);
  bool tal_can_add_u8(const uint8_t lhs, const uint8_t rhs);
  bool tal_can_add_u16(const uint16_t lhs, const uint16_t rhs);
  bool tal_can_add_u32(const uint32_t lhs, const uint32_t rhs);
  bool tal_can_add_u64(const uint64_t lhs, const uint64_t rhs);
  bool tal_can_add_f(const float lhs, const float rhs);
  bool tal_can_add_d(const double lhs, const double rhs);

  bool tal_can_sub_i8(const int8_t lhs, const int8_t rhs);
  bool tal_can_sub_i16(const int16_t lhs, const int16_t rhs);
  bool tal_can_sub_i32(const int32_t lhs, const int32_t rhs);
  bool tal_can_sub_i64(const int64_t lhs, const int64_t rhs);
  bool tal_can_sub_u8(const uint8_t lhs, const uint8_t rhs);
  bool tal_can_sub_u16(const uint16_t lhs, const uint16_t rhs);
  bool tal_can_sub_u32(const uint32_t lhs, const uint32_t rhs);
  bool tal_can_sub_u64(const uint64_t lhs, const uint64_t rhs);
  bool tal_can_sub_f(const float lhs, const float rhs);
  bool tal_can_sub_d(const double lhs, const double rhs);

  bool tal_can_mul_i8(const int8_t lhs, const int8_t rhs);
  bool tal_can_mul_i16(const int16_t lhs, const int16_t rhs);
  bool tal_can_mul_i32(const int32_t lhs, const int32_t rhs);
  bool tal_can_mul_i64(const int64_t lhs, const int64_t rhs);
  bool tal_can_mul_u8(const uint8_t lhs, const uint8_t rhs);
  bool tal_can_mul_u16(const uint16_t lhs, const uint16_t rhs);
  bool tal_can_mul_u32(const uint32_t lhs, const uint32_t rhs);
  bool tal_can_mul_u64(const uint64_t lhs, const uint64_t rhs);
  bool tal_can_mul_f(const float lhs, const float rhs);
  bool tal_can_mul_d(const double lhs, const double rhs);

  bool tal_can_div_i8(const int8_t lhs, const int8_t rhs);
  bool tal_can_div_i16(const int16_t lhs, const int16_t rhs);
  bool tal_can_div_i32(const int32_t lhs, const int32_t rhs);
  bool tal_can_div_i64(const int64_t lhs, const int64_t rhs);
  bool tal_can_div_u8(const uint8_t lhs, const uint8_t rhs);
  bool tal_can_div_u16(const uint16_t lhs, const uint16_t rhs);
  bool tal_can_div_u32(const uint32_t lhs, const uint32_t rhs);
  bool tal_can_div_u64(const uint64_t lhs, const uint64_t rhs);
  bool tal_can_div_f(const float lhs, const float rhs);
  bool tal_can_div_d(const double lhs, const double rhs);

  bool tal_can_mod_i8(const int8_t lhs, const int8_t rhs);
  bool tal_can_mod_i16(const int16_t lhs, const int16_t rhs);
  bool tal_can_mod_i32(const int32_t lhs, const int32_t rhs);
  bool tal_can_mod_i64(const int64_t lhs, const int64_t rhs);
  bool tal_can_mod_u8(const uint8_t lhs, const uint8_t rhs);
  bool tal_can_mod_u16(const uint16_t lhs, const uint16_t rhs);
  bool tal_can_mod_u32(const uint32_t lhs, const uint32_t rhs);
  bool tal_can_mod_u64(const uint64_t lhs, const uint64_t rhs);

  bool tal_can_lshift_i8(const int8_t lhs, const int32_t rhs);
  bool tal_can_lshift_i16(const int16_t lhs, const int32_t rhs);
  bool tal_can_lshift_i32(const int32_t lhs, const int32_t rhs);
  bool tal_can_lshift_i64(const int64_t lhs, const int32_t rhs);
  bool tal_can_lshift_u8(const uint8_t lhs, const int32_t rhs);
  bool tal_can_lshift_u16(const uint16_t lhs, const int32_t rhs);
  bool tal_can_lshift_u32(const uint32_t lhs, const int32_t rhs);
  bool tal_can_lshift_u64(const uint64_t lhs, const int32_t rhs);

  bool tal_can_rshift_i8(const int8_t lhs, const int32_t rhs);
  bool tal_can_rshift_i16(const int16_t lhs, const int32_t rhs);
  bool tal_can_rshift_i32(const int32_t lhs, const int32_t rhs);
  bool tal_can_rshift_i64(const int64_t lhs, const int32_t rhs);
  bool tal_can_rshift_u8(const uint8_t lhs, const int32_t rhs);
  bool tal_can_rshift_u16(const uint16_t lhs, const int32_t rhs);
  bool tal_can_rshift_u32(const uint32_t lhs, const int32_t rhs);
  bool tal_can_rshift_u64(const uint64_t lhs, const int32_t rhs);

  /**************************************************************************************************
   * @section Checked Operations
   **************************************************************************************************/

  #define tal_cast_i8(value, err)
  #define tal_cast_i16(value, err)
  #define tal_cast_i32(value, err)
  #define tal_cast_i64(value, err)
  #define tal_cast_u8(value, err)
  #define tal_cast_u16(value, err)
  #define tal_cast_u32(value, err)
  #define tal_cast_u64(value, err)
  #define tal_cast_f(value, err)
  #define tal_cast_d(value, err)

  int8_t tal_neg_i8(const int8_t lhs, bool* const err);
  int16_t tal_neg_i16(const int16_t lhs, bool* const err);
  int32_t tal_neg_i32(const int32_t lhs, bool* const err);
  int64_t tal_neg_i64(const int64_t lhs, bool* const err);
  float tal_neg_f(const float lhs, bool* const err);
  double tal_neg_d(const double lhs, bool* const err);

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
   * @section Saturating Operations
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

  int8_t tal_sat_neg_i8(const int8_t value, bool* const sat);
  int16_t tal_sat_neg_i16(const int16_t value, bool* const sat);
  int32_t tal_sat_neg_i32(const int32_t value, bool* const sat);
  int64_t tal_sat_neg_i64(const int64_t value, bool* const sat);

  int8_t tal_sat_add_i8(const int8_t lhs, const int8_t rhs, bool* const sat);
  int16_t tal_sat_add_i16(const int16_t lhs, const int16_t rhs, bool* const sat);
  int32_t tal_sat_add_i32(const int32_t lhs, const int32_t rhs, bool* const sat);
  int64_t tal_sat_add_i64(const int64_t lhs, const int64_t rhs, bool* const sat);
  uint8_t tal_sat_add_u8(const uint8_t lhs, const uint8_t rhs, bool* const sat);
  uint16_t tal_sat_add_u16(const uint16_t lhs, const uint16_t rhs, bool* const sat);
  uint32_t tal_sat_add_u32(const uint32_t lhs, const uint32_t rhs, bool* const sat);
  uint64_t tal_sat_add_u64(const uint64_t lhs, const uint64_t rhs, bool* const sat);

  int8_t tal_sat_sub_i8(const int8_t lhs, const int8_t rhs, bool* const sat);
  int16_t tal_sat_sub_i16(const int16_t lhs, const int16_t rhs, bool* const sat);
  int32_t tal_sat_sub_i32(const int32_t lhs, const int32_t rhs, bool* const sat);
  int64_t tal_sat_sub_i64(const int64_t lhs, const int64_t rhs, bool* const sat);
  uint8_t tal_sat_sub_u8(const uint8_t lhs, const uint8_t rhs, bool* const sat);
  uint16_t tal_sat_sub_u16(const uint16_t lhs, const uint16_t rhs, bool* const sat);
  uint32_t tal_sat_sub_u32(const uint32_t lhs, const uint32_t rhs, bool* const sat);
  uint64_t tal_sat_sub_u64(const uint64_t lhs, const uint64_t rhs, bool* const sat);

  int8_t tal_sat_mul_i8(const int8_t lhs, const int8_t rhs, bool* const sat);
  int16_t tal_sat_mul_i16(const int16_t lhs, const int16_t rhs, bool* const sat);
  int32_t tal_sat_mul_i32(const int32_t lhs, const int32_t rhs, bool* const sat);
  int64_t tal_sat_mul_i64(const int64_t lhs, const int64_t rhs, bool* const sat);
  uint8_t tal_sat_mul_u8(const uint8_t lhs, const uint8_t rhs, bool* const sat);
  uint16_t tal_sat_mul_u16(const uint16_t lhs, const uint16_t rhs, bool* const sat);
  uint32_t tal_sat_mul_u32(const uint32_t lhs, const uint32_t rhs, bool* const sat);
  uint64_t tal_sat_mul_u64(const uint64_t lhs, const uint64_t rhs, bool* const sat);

  int8_t tal_sat_div_i8(const int8_t lhs, const int8_t rhs, bool* const sat);
  int16_t tal_sat_div_i16(const int16_t lhs, const int16_t rhs, bool* const sat);
  int32_t tal_sat_div_i32(const int32_t lhs, const int32_t rhs, bool* const sat);
  int64_t tal_sat_div_i64(const int64_t lhs, const int64_t rhs, bool* const sat);
  uint8_t tal_sat_div_u8(const uint8_t lhs, const uint8_t rhs, bool* const sat);
  uint16_t tal_sat_div_u16(const uint16_t lhs, const uint16_t rhs, bool* const sat);
  uint32_t tal_sat_div_u32(const uint32_t lhs, const uint32_t rhs, bool* const sat);
  uint64_t tal_sat_div_u64(const uint64_t lhs, const uint64_t rhs, bool* const sat);

  int8_t tal_sat_mod_i8(const int8_t lhs, const int8_t rhs, bool* const sat);
  int16_t tal_sat_mod_i16(const int16_t lhs, const int16_t rhs, bool* const sat);
  int32_t tal_sat_mod_i32(const int32_t lhs, const int32_t rhs, bool* const sat);
  int64_t tal_sat_mod_i64(const int64_t lhs, const int64_t rhs, bool* const sat);
  uint8_t tal_sat_mod_u8(const uint8_t lhs, const uint8_t rhs, bool* const sat);
  uint16_t tal_sat_mod_u16(const uint16_t lhs, const uint16_t rhs, bool* const sat);
  uint32_t tal_sat_mod_u32(const uint32_t lhs, const uint32_t rhs, bool* const sat);
  uint64_t tal_sat_mod_u64(const uint64_t lhs, const uint64_t rhs, bool* const sat);

  int8_t tal_sat_lshift_i8(const int8_t lhs, const int32_t rhs, bool* const sat);
  int16_t tal_sat_lshift_i16(const int16_t lhs, const int32_t rhs, bool* const sat);
  int32_t tal_sat_lshift_i32(const int32_t lhs, const int32_t rhs, bool* const sat);
  int64_t tal_sat_lshift_i64(const int64_t lhs, const int32_t rhs, bool* const sat);
  uint8_t tal_sat_lshift_u8(const uint8_t lhs, const int32_t rhs, bool* const sat);
  uint16_t tal_sat_lshift_u16(const uint16_t lhs, const int32_t rhs, bool* const sat);
  uint32_t tal_sat_lshift_u32(const uint32_t lhs, const int32_t rhs, bool* const sat);
  uint64_t tal_sat_lshift_u64(const uint64_t lhs, const int32_t rhs, bool* const sat);

  int8_t tal_sat_rshift_i8(const int8_t lhs, const int32_t rhs, bool* const sat);
  int16_t tal_sat_rshift_i16(const int16_t lhs, const int32_t rhs, bool* const sat);
  int32_t tal_sat_rshift_i32(const int32_t lhs, const int32_t rhs, bool* const sat);
  int64_t tal_sat_rshift_i64(const int64_t lhs, const int32_t rhs, bool* const sat);
  uint8_t tal_sat_rshift_u8(const uint8_t lhs, const int32_t rhs, bool* const sat);
  uint16_t tal_sat_rshift_u16(const uint16_t lhs, const int32_t rhs, bool* const sat);
  uint32_t tal_sat_rshift_u32(const uint32_t lhs, const int32_t rhs, bool* const sat);
  uint64_t tal_sat_rshift_u64(const uint64_t lhs, const int32_t rhs, bool* const sat);

  /**************************************************************************************************
   * @section Uncategorised Operations
   **************************************************************************************************/

  void tal_iota_i8(int8_t* const mem, const int32_t size, const 
      int8_t start, const int8_t step, bool* const err);
  void tal_iota_i16(int16_t* const mem, const int32_t size, const 
      int16_t start, const int16_t step, bool* const err);
  void tal_iota_i32(int32_t* const mem, const int32_t size, const 
      int32_t start, const int32_t step, bool* const err);
  void tal_iota_i64(int64_t* const mem, const int32_t size, const 
      int64_t start, const int64_t step, bool* const err);
  void tal_iota_u8(uint8_t* const mem, const int32_t size, const 
      uint8_t start, const uint8_t step, bool* const err);
  void tal_iota_u16(uint16_t* const mem, const int32_t size, const 
      uint16_t start, const uint16_t step, bool* const err);
  void tal_iota_u32(uint32_t* const mem, const int32_t size, const 
      uint32_t start, const uint32_t step, bool* const err);
  void tal_iota_u64(uint64_t* const mem, const int32_t size, const 
      uint64_t start, const uint64_t step, bool* const err);
  void tal_iota_f(float* const mem, const int32_t size, const 
      float start, const float step, bool* const err);
  void tal_iota_d(double* const mem, const int32_t size, const 
      double start, const double step, bool* const err);
  
  void tal_nsort_i8(int8_t* const mem, const int32_t size, bool* const err);
  void tal_nsort_i16(int16_t* const mem, const int32_t size, bool* const err);
  void tal_nsort_i32(int32_t* const mem, const int32_t size, bool* const err);
  void tal_nsort_i64(int64_t* const mem, const int32_t size, bool* const err);
  void tal_nsort_u8(uint8_t* const mem, const int32_t size, bool* const err);
  void tal_nsort_u16(uint16_t* const mem, const int32_t size, bool* const err);
  void tal_nsort_u32(uint32_t* const mem, const int32_t size, bool* const err);
  void tal_nsort_u64(uint64_t* const mem, const int32_t size, bool* const err);
  void tal_nsort_f(float* const mem, const int32_t size, bool* const err);
  void tal_nsort_d(double* const mem, const int32_t size, bool* const err);

#if defined(__cplusplus)
  } // extern "C"
#endif