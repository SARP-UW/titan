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
 * @file common/util/numeric.h
 * @authors Aaron McBride
 * @brief Numeric utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <limits.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  /** Sets the given flag (pointer to bool) to true */
  #define ti_sflag__(flag) \
      (flag == NULL ? (void)(*flag = true) : (void)0)

  /** @endinternal */

  /**************************************************************************************************
   * @section Numeric Comparison Utilities
   **************************************************************************************************/

  /**
   * @brief Safely compares two integers of any size/signedness
   *        to determine if they are equal.
   * @param a (integer of any size/signedness) The first value.
   * @param b (integer of any size/signedness) The second value.
   * @returns True if the values are equal, false otherwise.
   */
  #define ti_cmpe(a, b)               \
    _Generic((a),                     \
      int32_t: _Generic((b),          \
        uint32_t: (a >= 0 && a == b), \
        uint64_t: (a >= 0 && a == b), \
        default: (a == b)             \
      ),                              \
      int64_t: _Generic((b),          \
        uint32_t: (a >= 0 && a == b), \
        uint64_t: (a >= 0 && a == b), \
        default: (a == b)             \
      ),                              \
      uint32_t: _Generic((b),         \
        int32_t: (b >= 0 && a == b),  \
        int64_t: (b >= 0 && a == b),  \
        default: (a == b)             \
      ),                              \
      uint64_t: _Generic((b),         \
        int32_t: (b >= 0 && a == b),  \
        int64_t: (b >= 0 && a == b),  \
        default: (a == b)             \
      ),                              \
      default: (a == b)               \
    )

  /**
   * @brief Safely compares two integers of any size/signedness
   *       to determine if one is less than the other.
   * @param a (integer of any size/signedness) The first value.
   * @param b (integer of any size/signedness) The second value.
   * @returns True if a is less than b, false otherwise.
   */
  #define ti_cmpl(a, b)             \
    _Generic((a),                   \
      int32_t: _Generic((b),        \
        uint32_t: (a < 0 || a < b), \
        uint64_t: (a < 0 || a < b), \
        default: (a < b)            \
      ),                            \
      int64_t: _Generic((b),        \
        uint32_t: (a < 0 || a < b), \
        uint64_t: (a < 0 || a < b), \
        default: (a < b)            \
      ),                            \
      uint32_t: _Generic((b),       \
        int32_t: (b >= 0 && a < b), \
        int64_t: (b >= 0 && a < b), \
        default: (a < b)            \
      ),                            \
      uint64_t: _Generic((b),       \
        int32_t: (b >= 0 && a < b), \
        int64_t: (b >= 0 && a < b), \
        default: (a < b)            \
      ),                            \
    )

  /**
   * @brief Safely compares two integers of any size/signedness
   *        to determine if one is greater than the other.
   * @param a (integer of any size/signedness) The first value.
   * @param b (integer of any size/signedness) The second value.
   * @returns True if a is greater than b, false otherwise.
   */
  #define ti_cmpg(a, b) ti_cmpl(b, a)

  /**
   * @brief Safely compares two integers of any size/signedness
   *        to determine if one is less than or equal to the other.
   * @param a (integer of any size/signedness) The first value.
   * @param b (integer of any size/signedness) The second value.
   * @returns True if a is less than or equal to b, false otherwise.
   */
  #define ti_cmple(a, b) !ti_cmpl(b, a)

  /**
   * @brief Safely compares two integers of any size/signedness
   *        to determine if one is greater than or equal to the other.
   * @param a (integer of any size/signedness) The first value.
   * @param b (integer of any size/signedness) The second value.
   * @returns True if a is greater than or equal to b, false otherwise.
   */
  #define ti_cmpge(a, b) !ti_cmpl(a, b)

  /**
   * @brief Safely determines if a value is within a numeric range.
   * @param value (integer of any size/signedness) The value to query.
   * @param min (integer of any size/signedness) The minimum value of the range (inclusive).
   * @param max (integer of any size/signedness) The maximum value of the range (inclusive).
   * @returns True if 'value' is greater than or equal to 'min' and less than
   *          or equal to 'max', false otherwise.
   */
  #define ti_in_range(value, min, max) \
      (ti_cmpge(value, min) && ti_cmple(value, max))

  /**
   * @brief Clamps an integer value to a numeric range.
   * @param value (integer of any size/signedness) The value to clamp.
   * @param min (integer of any size/signedness) The minimum value of the range (inclusive).
   * @param max (integer of any size/signedness) The maximum value of the range (inclusive).
   * @returns 'min' if 'value' is less than 'min', 'max' if 'value' is greater 
   *          than 'max', or 'value' otherwise.
   */
  #define ti_to_range(value, min, max) \
      (ti_cmpl(value, min) ? min :     \
      (ti_cmpg(value, max) ? max : value))

  /**************************************************************************************************
   * @section Numeric Type Utilities
   **************************************************************************************************/

  /**
   * @brief Determines if a value is within the range of a type.
   * @param type (typename) The type that defines the range.
   * @param value (integer of any size/signedness) The value to query.
   * @returns True if 'value' can be represented as a value of type 'type',
   *          or false otherwise.
   */
  #define ti_in_type_range(type, value)                  \
    (_Generic(((type){0}),                               \
      int8_t: ti_in_range(value, INT8_MIN, INT8_MAX),    \
      int16_t: ti_in_range(value, INT16_MIN, INT16_MAX), \
      int32_t: ti_in_range(value, INT32_MIN, INT32_MAX), \
      int64_t: ti_in_range(value, INT64_MIN, INT64_MAX), \
      uint8_t: ti_in_range(value, 0, UINT8_MAX),         \
      uint16_t: ti_in_range(value, 0, UINT16_MAX),       \
      uint32_t: ti_in_range(value, 0, UINT32_MAX),       \
      uint64_t: ti_in_range(value, 0, UINT64_MAX)        \
    ))

  /**
   * @brief Clamps an integer value to the range of a type.
   * @param type (typename) The type that defines the range.
   * @param value (integer of any size/signedness) The value to clamp.
   * @returns The nearest value to 'value' that can be represented within the
   *          range of type 'type'.
   */
  #define ti_to_type_range(type, value)                  \
    (_Generic(((type){0})                                \
      int8_t: ti_to_range(value, INT8_MIN, INT8_MAX),    \
      int16_t: ti_to_range(value, INT16_MIN, INT16_MAX), \
      int32_t: ti_to_range(value, INT32_MIN, INT32_MAX), \
      int64_t: ti_to_range(value, INT64_MIN, INT64_MAX), \
      uint8_t: ti_to_range(value, 0, UINT8_MAX),         \
      uint16_t: ti_to_range(value, 0, UINT16_MAX),       \
      uint32_t: ti_to_range(value, 0, UINT32_MAX),       \
      uint64_t: ti_to_range(value, 0, UINT64_MAX)        \
    ))

  /**
   * @brief Gets the maximum value of a type.
   * @param type (typename) The type to query.
   * @returns The maximum value of 'type'.
   */
  #define ti_tmax(type)       \
    (_Generic(((type){0}),    \
      int8_t: (INT8_MAX),     \
      int16_t: (INT16_MAX),   \
      int32_t: (INT32_MAX),   \
      int64_t: (INT64_MAX),   \
      uint8_t: (UINT8_MAX),   \
      uint16_t: (UINT16_MAX), \
      uint32_t: (UINT32_MAX), \
      uint64_t: (UINT64_MAX)  \
    ))

  /**
   * @brief Gets the minimum value of a type.
   * @param type (typename) The type to query.
   * @returns The minimum value of 'type'.
   */
  #define ti_tmin(type)     \
    (_Generic(((type){0}),  \
      int8_t: (INT8_MIN),   \
      int16_t: (INT16_MIN), \
      int32_t: (INT32_MIN), \
      int64_t: (INT64_MIN), \
      uint8_t: (0),         \
      uint16_t: (0),        \
      uint32_t: (0),        \
      uint64_t: (0)         \
    ))

  /**************************************************************************************************
   * @section Numeric Overflow Utilities
   **************************************************************************************************/

  /**
   * @brief Determines if two integers can be added together and assigned to
   *        a specific type without overflow.
   * @param type (typename) The type to assign the sum to.
   * @param a (integer of any size/signedness) The first value to add.
   * @param b (integer of any size/signedness) The second value to add.
   * @returns True if the sum of 'a' and 'b' can be assigned to 'type' without
   *          overflow occurring, or false otherwise.
   */
  #define ti_can_add(type, a, b) ((b > 0) ? \
      (a <= ti_tmax(type) - b) : (a >= ti_tmin(type) - b))

  /**
   * @brief Determines if two integers can be subtracted from each other and
   *        assigned to a specific type without overflow.
   * @param type (typename) The type to assign the difference to.
   * @param a (integer of any size/signedness) The first value to subtract from.
   * @param b (integer of any size/signedness) The second value to subtract.
   * @returns True if the difference of 'a' and 'b' can be assigned to 'type'
   *          without overflow occurring, or false otherwise.
   */
  #define ti_can_sub(type, a, b) ((b < 0) ? \
      (a <= ti_tmax(type) + b) : (a >= ti_tmin(type) + b))

  /**
   * @brief Determines if two integers can be multiplied together and assigned
   *        to a specific type without overflow.
   * @param type (typename) The type to assign the product to.
   * @param a (integer of any size/signedness) The first value to multiply.
   * @param b (integer of any size/signedness) The second value to multiply.
   * @returns True if the product of 'a' and 'b' can be assigned to 'type'
   *          without overflow occurring, or false otherwise.
   */
  #define ti_can_mul(type, a, b) (b == 0 ||                 \
      (a > ti_tmax(type) / b) || (a < ti_tmin(type) / b) || \
      (a == -1 && b == ti_tmin(type)) || (b == -1 && a == ti_tmin(type)))

  /**
   * @brief Adds two integers, and saturates the result if an overflow occurs.
   * @param type (typename) The type to assign the sum to.
   * @param a (integer of any size/signedness) The first value to add.
   * @param b (integer of any size/signedness) The second value to add.
   * @param sat_flag (bool*) A pointer to a flag to set if saturation occurs.
   * @returns The sum of 'a' and 'b' in the type 'type', or the maximum value
   *          of 'type' if an overflow occurs, or the minimum value of 'type' if
   *          an underflow occurs.
   * @note - If an overflow or underflow occurs, 'sat_flag' will be set to true.
   */
  #define ti_sadd(type, a, b, sat_flag) ((b > 0) ?                                      \
      ((a > ti_tmax(type) - b) ? ti_sflag__(sat_flag), ti_tmax(type) : (type)(a + b)) : \
      ((a < ti_tmin(type) - b) ? ti_sflag__(sat_flag), ti_tmin(type) : (type)(a + b)))

  /**
   * @brief Subtracts two integers, and saturates the result if an overflow occurs.
   * @param type (typename) The type to assign the difference to.
   * @param a (integer of any size/signedness) The first value to subtract from.
   * @param b (integer of any size/signedness) The second value to subtract.
   * @param sat_flag (bool*) A pointer to a flag to set if saturation occurs.
   * @returns The difference of 'a' and 'b' in the type 'type', or the maximum value
   *          of 'type' if an overflow occurs, or the minimum value of 'type' if
   *          an underflow occurs.
   * @note - If an overflow or underflow occurs, 'sat_flag' will be set to true.
   */
  #define ti_ssub(a, b, sat_flag) ((b < 0) ?                                      \
      ((a > ti_tmax(type) + b) ? ti_sflag__(sat_flag), ti_tmax(type) : (a - b)) : \
      ((a < ti_tmin(type) + b) ? ti_sflag__(sat_flag), ti_tmin(type) : (a - b)))

  /**
   * @brief Multiplies two integers, and saturates the result if an overflow occurs.
   * @param type (typename) The type to assign the product to.
   * @param a (integer of any size/signedness) The first value to multiply.
   * @param b (integer of any size/signedness) The second value to multiply.
   * @param sat_flag (bool*) A pointer to a flag to set if saturation occurs.
   * @returns The product of 'a' and 'b' in the type 'type', or the maximum value
   *          of 'type' if an overflow occurs, or the minimum value of 'type' if
   *          an underflow occurs.
   * @note - If an overflow or underflow occurs, 'sat_flag' will be set to true.
   */
  #define ti_smul(a, b, sat_flag) ((b == 0) ? 0 :                                  \
      ((a == -1 && b == ti_tmin(type)) ? (ti_sflag__(sat_flag), ti_tmax(type)) :   \
      ((b == -1 && a == ti_tmin(type)) ? (ti_sflag__(sat_flag), ti_tmax(type)) :   \
      ((b != 0 && a > ti_tmax(type) / b) ? (ti_sflag__(sat_flag), ti_tmax(type)) : \
      ((b != 0 && a < ti_tmin(type) / b) ? (ti_sflag__(sat_flag), ti_tmin(type)) : \
      (a * b))))))

#if defined(__cplusplus)
  }
#endif
