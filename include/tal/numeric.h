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
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "include/tal/attributes.h"
#include "include/tal/env_info.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**
   * @defgroup tal_abs
   * @brief Gets the absolute value of an integer.
   * @param value (signed integer denoted by suffix) The value to modify.
   * @returns The absolute value of 'value'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_abs_i8(const int8_t value);
  tal_fn_attr_inline inline int16_t tal_abs_i16(const int16_t value);
  tal_fn_attr_inline inline int32_t tal_abs_i32(const int32_t value);
  tal_fn_attr_inline inline int64_t tal_abs_i64(const int64_t value);
  /** @} */

  /**
   * @defgroup tal_clamp
   * @brief Clamps an integer value to a given range.
   * @param value (integer type denoted by suffix) The value to clamp.
   * @param min (integer type denoted by suffix) The minimum value of the range.
   * @param max (integer type denoted by suffix) The maximum value of the range.
   * @returns (integer type denoted by suffix) If 'value' is less than 'min', this
   *          function returns 'min'. If 'value' is greater than 'max', this function
   *          returns 'max'. Otherwise, this function returns 'value'.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_clamp_i8(const int8_t value, const int8_t min, const int8_t max);
  tal_fn_attr_inline inline int16_t tal_clamp_i16(const int16_t value, const int16_t min, const int16_t max);
  tal_fn_attr_inline inline int32_t tal_clamp_i32(const int32_t value, const int32_t min, const int32_t max);
  tal_fn_attr_inline inline int64_t tal_clamp_i64(const int64_t value, const int64_t min, const int64_t max);

  tal_fn_attr_inline inline uint8_t tal_clamp_u8(const uint8_t value, const uint8_t min, const uint8_t max);
  tal_fn_attr_inline inline uint16_t tal_clamp_u16(const uint16_t value, const uint16_t min, const uint16_t max);
  tal_fn_attr_inline inline uint32_t tal_clamp_u32(const uint32_t value, const uint32_t min, const uint32_t max);
  tal_fn_attr_inline inline uint64_t tal_clamp_u64(const uint64_t value, const uint64_t min, const uint64_t max);
  /** @} */

  /**
   * @defgroup tal_in_range
   * @brief Determines if an integer is within a given range.
   * @param value (integer type denoted by suffix) The value to query.
   * @param min (integer type denoted by suffix) The minimum value of the range.
   * @param max (integer type denoted by suffix) The maximum value of the range.
   * @returns (bool) True if 'value' is greater than or equal to 'min' and less than
   *          or equal to 'max', or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_in_range_i8(const int8_t value, const int8_t min, const int8_t max);
  tal_fn_attr_inline inline bool tal_in_range_i16(const int16_t value, const int16_t min, const int16_t max);
  tal_fn_attr_inline inline bool tal_in_range_i32(const int32_t value, const int32_t min, const int32_t max);
  tal_fn_attr_inline inline bool tal_in_range_i64(const int64_t value, const int64_t min, const int64_t max);

  tal_fn_attr_inline inline bool tal_in_range_u8(const uint8_t value, const uint8_t min, const uint8_t max);
  tal_fn_attr_inline inline bool tal_in_range_u16(const uint16_t value, const uint16_t min, const uint16_t max);
  tal_fn_attr_inline inline bool tal_in_range_u32(const uint32_t value, const uint32_t min, const uint32_t max);
  tal_fn_attr_inline inline bool tal_in_range_u64(const uint64_t value, const uint64_t min, const uint64_t max);
  /** @} */

  /**
   * @defgroup tal_satcast
   * @brief Casts an integer to a given type, and clamps it's value to the new 
   *        type's range.
   * @param value (intmax_t/uintmax_t denoted by end of suffix) The value to cast.
   * @param sat_flag (bool*) A flag that will be set true if the value was clamped.
   * @returns (integer type denoted by suffix) INTX_MIN if 'value' is less than INTX_MIN,
   *          INTX_MAX if 'value' is greater then INTX_MAX or 'value' otherwise.
   * @note - 'sat_flag' is an optional - it may be NULL.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_satcast_i8(const int64_t value, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_satcast_i16(const int64_t value, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_satcast_i32(const int64_t value, bool* sat_flag);

  tal_fn_attr_inline inline int8_t tal_satcast_i8u(const uint64_t value, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_satcast_i16u(const uint64_t value, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_satcast_i32u(const uint64_t value, bool* sat_flag);

  tal_fn_attr_inline inline uint8_t tal_satcast_u8(const int64_t value, bool* sat_flag);
  tal_fn_attr_inline inline uint16_t tal_satcast_u16(const int64_t value, bool* sat_flag);
  tal_fn_attr_inline inline uint32_t tal_satcast_u32(const int64_t value, bool* sat_flag);

  tal_fn_attr_inline inline uint8_t tal_satcast_u8u(const uint64_t value, bool* sat_flag);
  tal_fn_attr_inline inline uint16_t tal_satcast_u16u(const uint64_t value, bool* sat_flag);
  tal_fn_attr_inline inline uint32_t tal_satcast_u32u(const uint64_t value, bool* sat_flag);
  /** @} */

  /**
   * @brief Saturating negation operation.
   * @param value (signed integer denoted by suffix) The value to negate.
   * @param sat_flag (bool*) A flag to set if the operation saturates.
   * @returns (signed integer denoted by suffix) The negated value, clamped
   *          to the min/max range of its integer type.
   * @note - 'sat_flag' is an optional - it may be NULL.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_sneg_i8(const int8_t value, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_sneg_i16(const int16_t value, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_sneg_i32(const int32_t value, bool* sat_flag);
  tal_fn_attr_inline inline int64_t tal_sneg_i64(const int64_t value, bool* sat_flag);
  /** @} */

  /**
   * @defgroup tal_sadd
   * @brief Saturating add operation.
   * @param value_a (integer type denoted by suffix) The first value to add.
   * @param value_b (integer type denoted by suffix) The second value to add.
   * @param sat_flag (bool*) A flag to set if the operation saturates.
   * @returns (integer type denoted by suffix) The sum of 'value_a' and 'value_b',
   *          clamped to the min/max range of their integer type.
   * @note - 'sat_flag' is an optional - it may be NULL.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_sadd_i8(const int8_t value_a, const int8_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_sadd_i16(const int16_t value_a, const int16_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_sadd_i32(const int32_t value_a, const int32_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int64_t tal_sadd_i64(const int64_t value_a, const int64_t value_b, bool* sat_flag);
  
  tal_fn_attr_inline inline uint8_t tal_sadd_u8(const uint8_t value_a, const uint8_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint16_t tal_sadd_u16(const uint16_t value_a, const uint16_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint32_t tal_sadd_u32(const uint32_t value_a, const uint32_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint64_t tal_sadd_u64(const uint64_t value_a, const uint64_t value_b, bool* sat_flag);
  /** @} */

  /**
   * @defgroup tal_ssub
   * @brief Saturating subtraction operation.
   * @param value_a (integer type denoted by suffix) The value to subtract from.
   * @param value_b (integer type denoted by suffix) The value to subtract.
   * @param sat_flag (bool*) A flag to set if the operation saturates.
   * @returns (integer type denoted by suffix) The difference of 'value_a' and 'value_b',
   *          clamped to the min/max range of their integer type.
   * @note - 'sat_flag' is an optional - it may be NULL.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_ssub_i8(const int8_t value_a, const int8_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_ssub_i16(const int16_t value_a, const int16_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_ssub_i32(const int32_t value_a, const int32_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int64_t tal_ssub_i64(const int64_t value_a, const int64_t value_b, bool* sat_flag);

  tal_fn_attr_inline inline uint8_t tal_ssub_u8(const uint8_t value_a, const uint8_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint16_t tal_ssub_u16(const uint16_t value_a, const uint16_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint32_t tal_ssub_u32(const uint32_t value_a, const uint32_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint64_t tal_ssub_u64(const uint64_t value_a, const uint64_t value_b, bool* sat_flag);
  /** @} */

  /**
   * @defgroup tal_smul
   * @b
   * rief Saturating multiplication operation.
   * @param value_a (integer type denoted by suffix) The first value to multiply.
   * @param value_b (integer type denoted by suffix) The second value to multiply.
   * @param sat_flag (bool*) A flag to set if the operation saturates.
   * @returns (integer type denoted by suffix) The product of 'value_a' and 'value_b',
   *          clamped to the min/max range of their integer type.
   * @note - 'sat_flag' is an optional - it may be NULL.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_smul_i8(const int8_t value_a, const int8_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_smul_i16(const int16_t value_a, const int16_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_smul_i32(const int32_t value_a, const int32_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline int64_t tal_smul_i64(const int64_t value_a, const int64_t value_b, bool* sat_flag);

  tal_fn_attr_inline inline uint8_t tal_smul_u8(const uint8_t value_a, const uint8_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint16_t tal_smul_u16(const uint16_t value_a, const uint16_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint32_t tal_smul_u32(const uint32_t value_a, const uint32_t value_b, bool* sat_flag);
  tal_fn_attr_inline inline uint64_t tal_smul_u64(const uint64_t value_a, const uint64_t value_b, bool* sat_flag);
  /** @} */

  /**
   * @defgroup tal_sdiv
   * @brief Saturating division operation.
   * @param num (integer type denoted by suffix) The numerator.
   * @param div (integer type denoted by suffix) The denominator.
   * @param sat_flag (bool*) A flag to set if the operation saturates.
   * @returns (integer type denoted by suffix) The result of dividing 'num' by 'div',
   *          or 0 if 'div' is equal to zero.
   * @note - 'sat_flag' is an optional - it may be NULL.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_sdiv_i8(const int8_t num, const int8_t div, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_sdiv_i16(const int16_t num, const int16_t div, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_sdiv_i32(const int32_t num, const int32_t div, bool* sat_flag);
  tal_fn_attr_inline inline int64_t tal_sdiv_i64(const int64_t num, const int64_t div, bool* sat_flag);

  tal_fn_attr_inline inline uint8_t tal_sdiv_u8(const uint8_t num, const uint8_t div, bool* sat_flag);
  tal_fn_attr_inline inline uint16_t tal_sdiv_u16(const uint16_t num, const uint16_t div, bool* sat_flag);
  tal_fn_attr_inline inline uint32_t tal_sdiv_u32(const uint32_t num, const uint32_t div, bool* sat_flag);
  tal_fn_attr_inline inline uint64_t tal_sdiv_u64(const uint64_t num, const uint64_t div, bool* sat_flag);
  /** @} */

  /**
   * @defgroup tal_slshift
   * @brief Saturating left bit-shift operation.
   * @param value (integer type denoted by suffix) The value to shift.
   * @param shift (int32_t) The number of bits to shift by.
   * @param sat_flag (bool*) A flag to set if the operation saturates.
   * @returns (integer type denoted by suffix) The result of shifting 'value' 
   *          left by the max number of bits less then or equal to 'shift' such 
   *          that no bit is shifted beyond the integer's range.
   * @note - If 'shift' is negative, this function returns 'value' and sets 
   *         'sat_flag' to true (if not NULL).
   * @note - 'sat_flag' is an optional - it may be NULL.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_slshift_i8(const int8_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_slshift_i16(const int16_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_slshift_i32(const int32_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline int64_t tal_slshift_i64(const int64_t value, const int32_t shift, bool* sat_flag);

  tal_fn_attr_inline inline uint8_t tal_slshift_u8(const uint8_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline uint16_t tal_slshift_u16(const uint16_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline uint32_t tal_slshift_u32(const uint32_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline uint64_t tal_slshift_u64(const uint64_t value, const int32_t shift, bool* sat_flag);
  /** @} */

  /**
   * @brief Saturating right bit-shift operation.
   * @param value (integer type denoted by suffix) The value to shift.
   * @param shift (int32_t) The number of bits to shift by.
   * @param sat_flag (bool*) A flag to set if the operation saturates.
   * @returns (integer type denoted by suffix) The result of shifting 'value'
   *          right by the max number of bits less then or equal to 'shift' such 
   *          that no bit is shifted beyond the integer's range.
   * @note - If 'shift' is negative, this function returns 'value' and sets
   *         'sat_flag' to true (if not NULL).
   * @note - 'sat_flag' is an optional - it may be NULL.
   * @{
   */
  tal_fn_attr_inline inline int8_t tal_sarshift_i8(const int8_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline int16_t tal_sarshift_i16(const int16_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline int32_t tal_sarshift_i32(const int32_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline int64_t tal_sarshift_i64(const int64_t value, const int32_t shift, bool* sat_flag);

  tal_fn_attr_inline inline uint8_t tal_sarshift_u8(const uint8_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline uint16_t tal_sarshift_u16(const uint16_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline uint32_t tal_sarshift_u32(const uint32_t value, const int32_t shift, bool* sat_flag);
  tal_fn_attr_inline inline uint64_t tal_sarshift_u64(const uint64_t value, const int32_t shift, bool* sat_flag);
  /** @} */

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  int8_t tal_abs_i8(const int8_t value) {    
    return value < 0 ? -value : value; 
  }

  int16_t tal_abs_i16(const int16_t value) { 
    return value < 0 ? -value : value; 
  }

  int32_t tal_abs_i32(const int32_t value) { 
    return value < 0 ? -value : value; 
  }

  int64_t tal_abs_i64(const int64_t value) { 
    return value < 0 ? -value : value; 
  }

  int8_t tal_min_i8(const int8_t value_a, const int8_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  int16_t tal_min_i16(const int16_t value_a, const int16_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  int32_t tal_min_i32(const int32_t value_a, const int32_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  int64_t tal_min_i64(const int64_t value_a, const int64_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  uint8_t tal_min_u8(const uint8_t value_a, const uint8_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  uint16_t tal_min_u16(const uint16_t value_a, const uint16_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  uint32_t tal_min_u32(const uint32_t value_a, const uint32_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  uint64_t tal_min_u64(const uint64_t value_a, const uint64_t value_b) {
    return value_a < value_b ? value_a : value_b;
  }

  int8_t tal_max_i8(const int8_t value_a, const int8_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  int16_t tal_max_i16(const int16_t value_a, const int16_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  int32_t tal_max_i32(const int32_t value_a, const int32_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  int64_t tal_max_i64(const int64_t value_a, const int64_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  uint8_t tal_max_u8(const uint8_t value_a, const uint8_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  uint16_t tal_max_u16(const uint16_t value_a, const uint16_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }
  
  uint32_t tal_max_u32(const uint32_t value_a, const uint32_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  uint64_t tal_max_u64(const uint64_t value_a, const uint64_t value_b) {
    return value_a > value_b ? value_a : value_b;
  }

  int8_t tal_clamp_i8(const int8_t value, 
      const int8_t min, const int8_t max) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    }
    return value;
  }

  int16_t tal_clamp_i16(const int16_t value, 
      const int16_t min, const int16_t max) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    }
    return value;
  }

  int32_t tal_clamp_i32(const int32_t value, 
      const int32_t min, const int32_t max) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    }
    return value;
  }

  int64_t tal_clamp_i64(const int64_t value, 
      const int64_t min, const int64_t max) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    }
    return value;
  }

  uint8_t tal_clamp_u8(const uint8_t value, 
      const uint8_t min, const uint8_t max) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    }
    return value;
  }

  uint16_t tal_clamp_u16(const uint16_t value, 
      const uint16_t min, const uint16_t max) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    }
    return value;
  }

  uint32_t tal_clamp_u32(const uint32_t value, 
      const uint32_t min, const uint32_t max) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    }
    return value;
  }

  uint64_t tal_clamp_u64(const uint64_t value, 
      const uint64_t min, const uint64_t max) {
    if (value < min) {
      return min;
    } else if (value > max) {
      return max;
    }
    return value;
  }

  bool tal_in_range_i8(const int8_t value, 
      const int8_t min, const int8_t max) {
    return value >= min && value <= max;
  }

  bool tal_in_range_i16(const int16_t value, 
      const int16_t min, const int16_t max) {
    return value >= min && value <= max;
  }

  bool tal_in_range_i32(const int32_t value, 
      const int32_t min, const int32_t max) {
    return value >= min && value <= max;
  }

  bool tal_in_range_i64(const int64_t value, 
      const int64_t min, const int64_t max) {
    return value >= min && value <= max;
  }

  bool tal_in_range_u8(const uint8_t value, 
      const uint8_t min, const uint8_t max) {
    return value >= min && value <= max;
  }

  bool tal_in_range_u16(const uint16_t value, 
      const uint16_t min, const uint16_t max) {
    return value >= min && value <= max;
  }

  bool tal_in_range_u32(const uint32_t value, 
      const uint32_t min, const uint32_t max) {
    return value >= min && value <= max;
  }

  bool tal_in_range_u64(const uint64_t value, 
      const uint64_t min, const uint64_t max) {
    return value >= min && value <= max;
  }

  int8_t tal_satcast_i8(const int64_t value, bool* sat_flag) {
    if (value < INT8_MIN) {
      if (sat_flag) { *sat_flag = true; }
      return INT8_MIN;
    }
    if (value > INT8_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return INT8_MAX;
    }
    return (int8_t)value;
  }

  int16_t tal_satcast_i16(const int64_t value, bool* sat_flag) {
    if (value < INT16_MIN) {
      if (sat_flag) { *sat_flag = true; }
      return INT16_MIN;
    }
    if (value > INT16_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return INT16_MAX;
    }
    return (int16_t)value;
  }

  int32_t tal_satcast_i32(const int64_t value, bool* sat_flag) {
    if (value < INT32_MIN) {
      if (sat_flag) { *sat_flag = true; }
      return INT32_MIN;
    }
    if (value > INT32_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return INT32_MAX;
    }
    return (int32_t)value;
  }

  int8_t tal_satcast_i8u(const uint64_t value, bool* sat_flag) {
    if (value > INT8_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return INT8_MAX;
    }
    return (int8_t)value;
  }

  int16_t tal_satcast_i16u(const uint64_t value, bool* sat_flag) {
    if (value > INT16_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return INT16_MAX;
    }
    return (int16_t)value;
  }

  int32_t tal_satcast_i32u(const uint64_t value, bool* sat_flag) {
    if (value > INT32_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return INT32_MAX;
    }
    return (int32_t)value;
  }

  uint8_t tal_satcast_u8(const int64_t value, bool* sat_flag) {
    if (value < 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    if (value > UINT8_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return UINT8_MAX;
    }
    return (uint8_t)value;
  }

  uint16_t tal_satcast_u16(const int64_t value, bool* sat_flag) {
    if (value < 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    if (value > UINT16_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return UINT16_MAX;
    }
    return (uint16_t)value;
  }

  uint32_t tal_satcast_u32(const int64_t value, bool* sat_flag) {
    if (value < 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    if (value > UINT32_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return UINT32_MAX;
    }
    return (uint32_t)value;
  }

  uint8_t tal_satcast_u8u(const uint64_t value, bool* sat_flag) {
    if (value > UINT8_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return UINT8_MAX;
    }
    return (uint8_t)value;
  }

  uint16_t tal_satcast_u16u(const uint64_t value, bool* sat_flag) {
    if (value > UINT16_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return UINT16_MAX;
    }
    return (uint16_t)value;
  }

  uint32_t tal_satcast_u32u(const uint64_t value, bool* sat_flag) {
    if (value > UINT32_MAX) {
      if (sat_flag) { *sat_flag = true; }
      return UINT32_MAX;
    }
    return (uint32_t)value;
  }

  int8_t tal_sneg_i8(const int8_t value, bool* sat_flag) {
    #if (tal_sys_signrep == tal_signrep_two_compl_v)
      if (value == INT8_MIN) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MIN;
      }
    #elif (tal_sys_signrep == tal_signrep_one_compl_v)
      if (value == INT8_MAX) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MAX;
      }
    #endif
    return -value;
  }

  int16_t tal_sneg_i16(const int16_t value, bool* sat_flag) {
    #if (tal_sys_signrep == tal_signrep_two_compl_v)
      if (value == INT16_MIN) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MIN;
      }
    #elif (tal_sys_signrep == tal_signrep_one_compl_v)
      if (value == INT16_MAX) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MAX;
      }
    #endif
    return -value;
  }

  int32_t tal_sneg_i32(const int32_t value, bool* sat_flag) {
    #if (tal_sys_signrep == tal_signrep_two_compl_v)
      if (value == INT32_MIN) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MIN;
      }
    #elif (tal_sys_signrep == tal_signrep_one_compl_v)
      if (value == INT32_MAX) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MAX;
      }
    #endif
    return -value;
  }

  int64_t tal_sneg_i64(const int64_t value, bool* sat_flag) {
    #if (tal_sys_signrep == tal_signrep_two_compl_v)
      if (value == INT64_MIN) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MIN;
      }
    #elif (tal_sys_signrep == tal_signrep_one_compl_v)
      if (value == INT64_MAX) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MAX;
      }
    #endif
    return -value;
  }

  int8_t tal_sadd_i8(const int8_t value_a, 
      const int8_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT8_MAX - value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MAX;
      }
    } else if (value_a < 0 && value_b < 0) {
      if (value_a < (INT8_MIN + value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MIN;
      }
    }
    return value_a + value_b;
  }

  int16_t tal_sadd_i16(const int16_t value_a, 
      const int16_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT16_MAX - value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MAX;
      }
    } else if (value_a < 0 && value_b < 0) {
      if (value_a < (INT16_MIN + value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MIN;
      }
    }
    return value_a + value_b;
  }

  int32_t tal_sadd_i32(const int32_t value_a, 
      const int32_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT32_MAX - value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MAX;
      }
    } else if (value_a < 0 && value_b < 0) {
      if (value_a < (INT32_MIN + value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MIN;
      }
    }
    return value_a + value_b;
  }

  int64_t tal_sadd_i64(const int64_t value_a, 
      const int64_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT64_MAX - value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MAX;
      }
    } else if (value_a < 0 && value_b < 0) {
      if (value_a < (INT64_MIN + value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MIN;
      }
    }
    return value_a + value_b;
  }
  
  uint8_t tal_sadd_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* sat_flag) {
    if (value_a > (UINT8_MAX - value_b)) {
      if (sat_flag) { *sat_flag = true; }
      return UINT8_MAX;
    }
    return value_a + value_b;
  }

  uint16_t tal_sadd_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* sat_flag) {
    if (value_a > (UINT16_MAX - value_b)) {
      if (sat_flag) { *sat_flag = true; }
      return UINT16_MAX;
    }
    return value_a + value_b;
  }

  uint32_t tal_sadd_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* sat_flag) {
    if (value_a > (UINT32_MAX - value_b)) {
      if (sat_flag) { *sat_flag = true; }
      return UINT32_MAX;
    }
    return value_a + value_b;
  }

  uint64_t tal_sadd_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* sat_flag) {
    if (value_a > (UINT64_MAX - value_b)) {
      if (sat_flag) { *sat_flag = true; }
      return UINT64_MAX;
    }
    return value_a + value_b;
  }

  int8_t tal_ssub_i8(const int8_t value_a, 
      const int8_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b < 0) {
      if (value_a > (INT8_MAX + value_b)) { 
        if (sat_flag) { *sat_flag = true; }
        return INT8_MAX;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT8_MIN + value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MIN;
      }
    }
    return value_a - value_b;
  }

  int16_t tal_ssub_i16(const int16_t value_a, 
      const int16_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b < 0) {
      if (value_a > (INT16_MAX + value_b)) { 
        if (sat_flag) { *sat_flag = true; }
        return INT16_MAX;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT16_MIN + value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MIN;
      }
    }
    return value_a - value_b;
  }

  int32_t tal_ssub_i32(const int32_t value_a, 
      const int32_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b < 0) {
      if (value_a > (INT32_MAX + value_b)) { 
        if (sat_flag) { *sat_flag = true; }
        return INT32_MAX;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT32_MIN + value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MIN;
      }
    }
    return value_a - value_b;
  }

  int64_t tal_ssub_i64(const int64_t value_a, 
      const int64_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b < 0) {
      if (value_a > (INT64_MAX + value_b)) { 
        if (sat_flag) { *sat_flag = true; }
        return INT64_MAX;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT64_MIN + value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MIN;
      }
    }
    return value_a - value_b;
  }

  uint8_t tal_ssub_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* sat_flag) {
    if (value_a < value_b) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return value_a - value_b;
  }

  uint16_t tal_ssub_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* sat_flag) {
    if (value_a < value_b) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return value_a - value_b;
  }

  uint32_t tal_ssub_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* sat_flag) {
    if (value_a < value_b) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return value_a - value_b;
  }

  uint64_t tal_ssub_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* sat_flag) {
    if (value_a < value_b) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return value_a - value_b;
  }

  int8_t tal_smul_i8(const int8_t value_a, 
      const int8_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT8_MAX / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MAX;
      }
    } else if (value_a > 0 && value_b < 0) {
      if (value_b < (INT8_MIN / value_a)) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MIN;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT8_MIN / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MIN;
      }
    } else if (value_a < 0 && value_b < 0) {
      #if (tal_sys_signrep == tal_signrep_one_compl_v)
        if (value_b == -1 && value_a == INT8_MIN) {
          if (sat_flag) { *sat_flag = true; }
          return INT8_MAX;
        }
      #endif
      if (value_a < (INT8_MAX / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT8_MAX;
      }
    }
    return value_a * value_b;
  }

  int16_t tal_smul_i16(const int16_t value_a, 
      const int16_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT16_MAX / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MAX;
      }
    } else if (value_a > 0 && value_b < 0) {
      if (value_b < (INT16_MIN / value_a)) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MIN;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT16_MIN / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MIN;
      }
    } else if (value_a < 0 && value_b < 0) {
      #if (tal_sys_signrep == tal_signrep_one_compl_v)
        if (value_b == -1 && value_a == INT16_MIN) {
          if (sat_flag) { *sat_flag = true; }
          return INT16_MAX;
        }
      #endif
      if (value_a < (INT16_MAX / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT16_MAX;
      }
    }
    return value_a * value_b;
  }

  int32_t tal_smul_i32(const int32_t value_a, 
      const int32_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT32_MAX / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MAX;
      }
    } else if (value_a > 0 && value_b < 0) {
      if (value_b < (INT32_MIN / value_a)) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MIN;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT32_MIN / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MIN;
      }
    } else if (value_a < 0 && value_b < 0) {
      #if (tal_sys_signrep == tal_signrep_one_compl_v)
        if (value_b == -1 && value_a == INT32_MIN) {
          if (sat_flag) { *sat_flag = true; }
          return INT32_MAX;
        }
      #endif
      if (value_a < (INT32_MAX / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT32_MAX;
      }
    }
    return value_a * value_b;
  }

  int64_t tal_smul_i64(const int64_t value_a, 
      const int64_t value_b, bool* sat_flag) {
    if (value_a > 0 && value_b > 0) {
      if (value_a > (INT64_MAX / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MAX;
      }
    } else if (value_a > 0 && value_b < 0) {
      if (value_b < (INT64_MIN / value_a)) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MIN;
      }
    } else if (value_a < 0 && value_b > 0) {
      if (value_a < (INT64_MIN / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MIN;
      }
    } else if (value_a < 0 && value_b < 0) {
      #if (tal_sys_signrep == tal_signrep_one_compl_v)
        if (value_b == -1 && value_a == INT64_MIN) {
          if (sat_flag) { *sat_flag = true; }
          return INT64_MAX;
        }
      #endif
      if (value_a < (INT64_MAX / value_b)) {
        if (sat_flag) { *sat_flag = true; }
        return INT64_MAX;
      }
    }
    return value_a * value_b;
  }

  uint8_t tal_smul_u8(const uint8_t value_a, 
      const uint8_t value_b, bool* sat_flag) {
    if (value_a > (UINT8_MAX / value_b)) {
      if (sat_flag) { *sat_flag = true; }
      return UINT8_MAX;
    }
    return value_a * value_b;
  }
  
  uint16_t tal_smul_u16(const uint16_t value_a, 
      const uint16_t value_b, bool* sat_flag) {
    if (value_a > (UINT16_MAX / value_b)) {
      if (sat_flag) { *sat_flag = true; }
      return UINT16_MAX;
    }
    return value_a * value_b;
  }

  uint32_t tal_smul_u32(const uint32_t value_a, 
      const uint32_t value_b, bool* sat_flag) {
    if (value_a > (UINT32_MAX / value_b)) {
      if (sat_flag) { *sat_flag = true; }
      return UINT32_MAX;
    }
    return value_a * value_b;
  }

  uint64_t tal_smul_u64(const uint64_t value_a, 
      const uint64_t value_b, bool* sat_flag) {
    if (value_a > (UINT64_MAX / value_b)) {
      if (sat_flag) { *sat_flag = true; }
      return UINT64_MAX;
    }
    return value_a * value_b;
  }

  int8_t tal_sdiv_i8(const int8_t num, 
      const int8_t div, bool* sat_flag) {
    if (div == 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return num / div;
  }
  
  int16_t tal_sdiv_i16(const int16_t num, 
      const int16_t div, bool* sat_flag) {
    if (div == 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return num / div;
  }
  
  int32_t tal_sdiv_i32(const int32_t num, 
      const int32_t div, bool* sat_flag) {
    if (div == 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return num / div;
  }
  
  int64_t tal_sdiv_i64(const int64_t num, 
      const int64_t div, bool* sat_flag) {
    if (div == 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return num / div;
  }
  
  uint8_t tal_sdiv_u8(const uint8_t num, const uint8_t div, bool* sat_flag) {
    if (div == 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return num / div;
  }

  uint16_t tal_sdiv_u16(
    const uint16_t num, const uint16_t div, bool* sat_flag) {
    if (div == 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return num / div;
  }

  uint32_t tal_sdiv_u32(const uint32_t num, const uint32_t div, bool* sat_flag) {
    if (div == 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return num / div;
  }

  uint64_t tal_sdiv_u64(const uint64_t num, const uint64_t div, bool* sat_flag) {
    if (div == 0) {
      if (sat_flag) { *sat_flag = true; }
      return 0;
    }
    return num / div;
  }

  int8_t tal_slshift_i8(const int8_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int32_t i = 0; i < shift; ++i) {
      const int8_t mask = (int8_t)1 << (8 - 1 - i);
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  int16_t tal_slshift_i16(const int16_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int32_t i = 0; i < shift; ++i) {
      const int16_t mask = (int16_t)1 << (16 - 1 - i);
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  int32_t tal_slshift_i32(const int32_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int32_t i = 0; i < shift; ++i) {
      const int32_t mask = (int32_t)1 << (32 - 1 - i);
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  int64_t tal_slshift_i64(const int64_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int32_t i = 0; i < shift; ++i) {
      const int64_t mask = (int64_t)1 << (64 - 1 - i);
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  uint8_t tal_slshift_u8(const uint8_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int32_t i = 0; i < shift; ++i) {
      const uint8_t mask = (uint8_t)1 << (8 - 1 - i);
      if ((value & mask) != 0u) {
        if (sat_flag) { *sat_flag = true; }
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  uint16_t tal_slshift_u16(const uint16_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int32_t i = 0; i < shift; ++i) {
      const uint16_t mask = (uint16_t)1 << (16 - 1 - i);
      if ((value & mask) != 0u) {
        if (sat_flag) { *sat_flag = true; }
        return value << (i - 1);
      }
    }
    return value << shift;
  }
  
  uint32_t tal_slshift_u32(const uint32_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int32_t i = 0; i < shift; ++i) {
      const uint32_t mask = (uint32_t)1 << (32 - 1 - i);
      if ((value & mask) != 0u) {
        if (sat_flag) { *sat_flag = true; }
        return value << (i - 1);
      }
    }
    return value << shift;
  }

  uint64_t tal_slshift_u64(const uint64_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int32_t i = 0; i < shift; ++i) {
      const uint64_t mask = (uint64_t)1 << (64 - 1 - i);
      if ((value & mask) != 0u) {
        if (sat_flag) { *sat_flag = true; }
        return value << (i - 1);
      }
    }
    return value << shift;
  }


  int8_t tal_sarshift_i8(const int8_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int i = 0; i < shift; ++i) {
      const int8_t mask = (int8_t)1 << i;
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  int16_t tal_sarshift_i16(const int16_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int i = 0; i < shift; ++i) {
      const int16_t mask = (int16_t)1 << i;
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  int32_t tal_sarshift_i32(const int32_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int i = 0; i < shift; ++i) {
      const int32_t mask = (int32_t)1 << i;
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  int64_t tal_sarshift_i64(const int64_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int i = 0; i < shift; ++i) {
      const int64_t mask = (int64_t)1 << i;
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  uint8_t tal_sarshift_u8(const uint8_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int i = 0; i < shift; ++i) {
      const uint8_t mask = (uint8_t)1 << i;
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  uint16_t tal_sarshift_u16(const uint16_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int i = 0; i < shift; ++i) {
      const uint16_t mask = (uint16_t)1 << i;
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  uint32_t tal_sarshift_u32(const uint32_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int i = 0; i < shift; ++i) {
      const uint32_t mask = (uint32_t)1 << i;
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  uint64_t tal_sarshift_u64(const uint64_t value, 
      const int32_t shift, bool* sat_flag) {
    for (int i = 0; i < shift; ++i) {
      const uint64_t mask = (uint64_t)1 << i;
      if ((value & mask) != 0) {
        if (sat_flag) { *sat_flag = true; }
        return value >> (i - 1);
      }
    }
    return value >> shift;
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif
