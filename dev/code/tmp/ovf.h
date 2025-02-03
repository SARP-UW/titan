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
 * @file src/common/util/ovf.h
 * @authors Aaron McBride
 * @brief Overflow detection utilities.
 * @note - API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/common/util/num.h"

#ifdef __ICCARM__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * @section Overflow Detection Utilities
   **********************************************************************************************/

  /**
   * @brief Determines if an addition operation will overflow.
   * @param lhs (integral type) The left operand.
   * @param rhs (integral type) The right operand.
   * @returns (bool) True if the addition will not overflow, 
   *          or false otherwise.
   */
  #define can_add(lhs, rhs)

  /**
   * @brief Determines if a subtraction operation will overflow.
   * @param lhs (integral type) The left operand.
   * @param rhs (integral type) The right operand.
   * @returns (bool) True if the subtraction will not overflow, 
   *          or false otherwise.
   */
  #define can_sub(lhs, rhs)

  /**
   * @brief Determines if a multiplication operation will overflow.
   * @param lhs (integral type) The left operand.
   * @param rhs (integral type) The right operand.
   * @returns (bool) True if the multiplication will not overflow, 
   *          or false otherwise.
   */
  #define can_mul(lhs, rhs)

  /**
   * @brief Determines if a integral cast operation will overflow.
   * @param value (integral type) The value to cast.
   * @param type (token) The name of the integral type to cast to.
   * @returns (bool) True if the cast operation will not overflow, 
   *          or false otherwise.
   */
  #define can_cast(value, type)

  /** @internal */

  /**********************************************************************************************
   * @section Implementation Resources
   **********************************************************************************************/

  // Gets the maximum value of an integral type.
  #define tmax_(x) \
    _Generic((x), \
      int8_t: INT8_MAX, \
      int16_t: INT16_MAX, \
      int32_t: INT32_MAX, \
      int64_t: INT64_MAX, \
      uint8_t: UINT8_MAX, \
      uint16_t: UINT16_MAX, \
      uint32_t: UINT32_MAX, \
      uint64_t: UINT64_MAX \
      float: FLT_MAX, \
      double: DBL_MAX, \
      bool: true, \
      default: 0 \
    )

  // Gets the minimum value of an integral type
  #define tmin_(x) \
    _Generic((x), \
      int8_t: INT8_MIN, \
      int16_t: INT16_MIN, \
      int32_t: INT32_MIN, \
      int64_t: INT64_MIN, \
      uint8_t: UINT8_C(0), \
      uint16_t: UINT16_C(0), \
      uint32_t: UINT32_C(0), \
      uint64_t: UINT64_C(0) \
      float: FLT_DENORM_MIN, \
      double: DBL_DENORM_MIN, \
      bool: false, \
      default: 0 \
    )

  /**********************************************************************************************
   * @section Overflow Detection Utilities
   **********************************************************************************************/

  #undef can_add
  #define can_add(lhs, rhs) ({ \
    const __auto_type lhs_ = (lhs); \
    const __auto_type rhs_ = (rhs); \
    bool result = true; \
    if (lhs_ > 0 && rhs_ > 0) { \
      result = cmp(lhs_, tmax_(lhs_ + rhs_) - rhs_) <= 0; \
    } else if (lhs_ < 0 && rhs_ < 0) { \
      result = cmp(lhs_, tmin_(lhs_ + rhs_) - rhs_) >= 0; \
    } \
    result; \
  })

  #undef can_sub
  #define can_sub(lhs, rhs) ({ \
    const __auto_type lhs_ = (lhs); \
    const __auto_type rhs_ = (rhs); \
    bool result = true; \
    if (lhs_ > 0 && rhs_ < 0) { \
      result = cmp(lhs_, tmax_(lhs_ + rhs_) + rhs_) <= 0; \
    } else if (lhs_ < 0 && rhs_ > 0) { \
      result = cmp(lhs_, tmin_(lhs_ + rhs_) + rhs_) >= 0; \
    } \
    result; \
  })

  #undef can_mul
  #define can_mul(lhs, rhs) ({ \
    const __auto_type lhs_ = (lhs); \
    const __auto_type rhs_ = (rhs); \
    bool result = true; \
    if (lhs_ > 0 && rhs_ > 0) { \
      result = cmp(lhs_, tmax_(lhs_ + rhs_) / rhs_) <= 0; \
    } else if (lhs_ < 0 && rhs_ < 0) { \
      result = cmp(lhs_, tmin_(lhs_ + rhs_) / rhs_) >= 0; \
    } else if (lhs_ > 0 && rhs_ < 0) { \
      result = cmp(lhs_, tmin_(lhs_ + rhs_) / rhs_) >= 0; \
    } else if (lhs_ < 0 && rhs_ > 0) { \
      result = cmp(lhs_, tmax_(lhs_ + rhs_) / rhs_) <= 0; \
    } \
    result; \
  })

  #undef can_cast
  #define can_cast(value, type) ({ \
    const __auto_type value_ = (value); \
    (cmp(value_, tmin_((type)0)) >= 0) && \
    (cmp(value_, tmax_((type)0)) <= 0); \
  })

  /** @endinternal */

#ifdef __cplusplus
  } // extern "C"
#endif