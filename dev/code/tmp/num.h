/**
 * This file is part of the Titan HAL
 * Copyright (c) 2025 UW SARP
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
 * @file src/common/util/num.h
 * @authors Aaron McBride
 * @brief Numeric utilities.
 * @note - API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __ICCARM__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * @section Relation Utilities
   **********************************************************************************************/

  /**
   * @brief Safely compares two integral values.
   * @param lhs (integral type) The left value to compare.
   * @param rhs (integral type) The right value to compare.
   * @returns (int32_t) -1 if @p [lhs] is less than @p [rhs], 0 if @p [lhs] 
   *          is equal to @p [rhs], or 1 if @p [lhs] is greater than @p [rhs].
   * @note - The behavior of this macro is defined even if the signedness of
   *         @p [lhs] and @p [rhs] differ.
   */
  #define cmp(lhs, rhs)

  /**
   * @brief Determines the absolute value of an integral value.
   * @param value (integral type) The target value.
   * @returns (type of @p [value]) The absolute value of @p [value].
   * @note - If the absolute value of @p [value] is out of bounds of the
   *         type of @p [value], the result will saturate.
   */
  #define abs(value)

  /**
   * @brief Determines the minimum of two integral values.
   * @param a (integral type) The first value.
   * @param b (integral type) The second value.
   * @returns (type of @p [a]) The minimum of @p [a] and @p [b].
   */
  #define min(a, b)

  /**
   * @brief Determines the maximum of two integral values.
   * @param a (integral type) The first value.
   * @param b (integral type) The second value.
   * @returns (type of @p [a]) The maximum of @p [a] and @p [b].
   */
  #define max(a, b)

  /**
   * @brief Clamps an integral value to a given range.
   * @param value (integral type) The value to clamp.
   * @param min (integral type) The minimum value of the range.
   * @param max (integral type) The maximum value of the range.
   * @returns (type of @p [value]) @p [min] if @p [value] is less than 
   *          @p [min], @p [max] if @p [value] is greater than @p [max], 
   *          or @p [value] otherwise.
   */
  #define clamp(value, min, max)

  /**
   * @brief Determines if a value is in a given range.
   * @param value (integral type) The value to query.
   * @param min (integral type) The minimum value of the range.
   * @param max (integral type) The maximum value of the range.
   * @returns (bool) True if @p [value] is greater than or equal to
   *          @p [min] and less than or equal to @p [max].
   */
  #define in_range(value, min, max)

  /**********************************************************************************************
   * @section Rounding Utilities
   **********************************************************************************************/

  /**
   * @brief Rounds a value up to the nearest given multiple.
   * @param value (integral type) The value to round.
   * @param mul (integral type) The multiple to round to.
   * @returns (type of @p [value]) The value rounded up to the nearest
   *          multiple of @p [mul].
   */
  #define ceil(value, mul)

  /**
   * @brief Rounds a value down to the nearest given multiple.
   * @param value (integral type) The value to round.
   * @param mul (integral type) The multiple to round to.
   * @returns (type of @p [value]) The value rounded down to the nearest
   *          multiple of @p [mul].
   */
  #define floor(value, mul)

  /**
   * @brief Rounds a value to the nearest given multiple.
   * @param value (integral type) The value to round.
   * @param mul (integral type) The multiple to round to.
   * @returns (type of @p [value]) The value rounded to the nearest
   *          multiple of @p [mul].
   */
  #define round(value, mul)

  /**
   * @brief Divides two values and rounds the result up to the nearest integer.
   * @param lhs (integer) The dividend.
   * @param rhs (integer) The divisor.
   * @returns (type of @p [lhs]) The result of @p [lhs] divided by @p [rhs], 
   *          rounded up to the nearest integer.
   */
  #define div_ceil(lhs, rhs)

  /**********************************************************************************************
   * @section Uncategorised Numeric Utilities
   **********************************************************************************************/

  /**
   * @brief Determines the result of raising a base to an exponent.
   * @param value (integer) The base value.
   * @param exp (integer) The exponent value.
   * @returns (type of @p [value]) The result of raising @p [value] to
   *          the power of @p [exp].
   */
  #define pow(value, exp)

  #define log(base, value, remf)

  /** @internal */

  /**********************************************************************************************
   * @section Implementation of Relational Utilities
   **********************************************************************************************/

  #undef cmp
  #define cmp(lhs, rhs) ({ \
    const __auto_type lhs_ = (lhs); \
    const __auto_type rhs_  = (rhs); \
    int32_t result = 0; \
    if (lhs_ < 0 && rhs_ > 0) { \
      result = -1; \
    } else if (lhs_ > 0 && rhs_ < 0) { \
      result = 1; \
    } else if (lhs_ < rhs_) { \
      result = -1; \
    } else if (lhs_ > rhs_) { \
      result = 1; \
    } \
    result; \
  })

  #undef abs
  #define abs(value) ({ \
    const __auto_type value_ = (value); \
    typeof(value_) result = value_; \
    if (value_ < 0) { \
      if (value_ == tmin_(value_)) { \
        result = tmax_(value_); \
      } else { \
        result = -value_; \
      } \
    } \
    result; \
  })

  #undef min
  #define min(a, b) ({ \
    const __auto_type a_ = (a); \
    const __auto_type b_ = (b); \
    cmp(a_, b_) < 0 ? a_ : b_; \
  })

  #undef max
  #define max(a, b) ({ \
    const __auto_type a_ = (a); \
    const __auto_type b_ = (b); \
    cmp(a_, b_) > 0 ? a_ : b_; \
  })

  #undef clamp
  #define clamp(value, min, max) ({ \
    const __auto_type value_ = (value); \
    const __auto_type tmin_ = (min); \
    const __auto_type tmax_ = (max); \
    cmp(value_, tmin_) < 0 ? tmin_ : \
    cmp(value_, tmin_) > 0 ? tmax_ : value_; \
  })

  #undef in_range
  #define in_range(value, min, max) ({ \
    const __auto_type value_ = (value); \
    cmp(value, min) >= 0 && cmp(value, max) <= 0; \
  })

  /**********************************************************************************************
   * @section Implementation of Rounding Utilities
   **********************************************************************************************/

  #undef ceil
  #define ceil(value, mul) ({ \
    const __auto_type value_ = (value); \
    const __auto_type mul_ = (mul); \
    value_ + (mul_ - (value_ % mul_)); \
  })

  #undef floor
  #define floor(value, mul) ({ \
    const __auto_type value_ = (value); \
    const __auto_type mul_ = (mul); \
    value_ - (value_ % mul_); \
  })

  #undef round
  #define round(value, mul) ({ \
    const __auto_type value_ = (value); \
    const __auto_type mul_ = (mul); \
    value_ + (mul_ / 2) - ((value_ + (mul_ / 2)) % mul_); \
  })

  #undef div_ceil
  #define div_ceil(lhs, rhs) ({ \
    const __auto_type l_ = (lhs); \
    const __auto_type r_ = (rhs); \
    l_ / r_ + (l_ % r_ != 0 && (l_ ^ r_) > 0); \
  })

  /**********************************************************************************************
   * @section Implementation of Uncategorised Numeric Utilities
   **********************************************************************************************/

  #undef pow
  #define pow(value, exp) ({ \
    const __auto_type value_ = (value); \
    const __auto_type exp_ = (exp); \
    typeof(value_ + exp_) result = 1; \
    for (int32_t i = 0; i < exp_; i++) { \
      result *= value_; \
    } \
    result; \
  })

  /** @endinternal */

#ifdef __cplusplus
  } // extern "C"
#endif