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
 * @internal
 * @file src/common/util/num.h
 * @authors Aaron McBride
 * @brief Core numeric utilities.
 * @note - API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Relational Utilities
   ************************************************************************************************/

  /**
   * @defgroup @b min_x
   * @brief Gets the minimum of two values.
   * @param a (integral type denoted by suffix) The first value.
   * @param b (integral type denoted by suffix) The second value.
   * @returns (integral type denoted by suffix) The minimum of @p [a] and @p [b].
   * @{
   */
  inline int8_t min_i8(int8_t a, int8_t b);
  inline int16_t min_i16(int16_t a, int16_t b);
  inline int32_t min_i32(int32_t a, int32_t b);
  inline int64_t min_i64(int64_t a, int64_t b);
  inline uint8_t min_u8(uint8_t a, uint8_t b);
  inline uint16_t min_u16(uint16_t a, uint16_t b);
  inline uint32_t min_u32(uint32_t a, uint32_t b);
  inline uint64_t min_u64(uint64_t a, uint64_t b);
  inline float min_f(float a, float b);
  inline double min_d(double a, double b);
  inline long double min_ld(long double a, long double b);
  /** @} */

  /**
   * @defgroup @b max_x
   * @brief Gets the maximum of two values.
   * @param a (integral type denoted by suffix) The first value.
   * @param b (integral type denoted by suffix) The second value.
   * @returns (integral type denoted by suffix) The maximum of @p [a] and @p [b].
   * @{
   */
  inline int8_t max_i8(int8_t a, int8_t b);
  inline int16_t max_i16(int16_t a, int16_t b);
  inline int32_t max_i32(int32_t a, int32_t b);
  inline int64_t max_i64(int64_t a, int64_t b);
  inline uint8_t max_u8(uint8_t a, uint8_t b);
  inline uint16_t max_u16(uint16_t a, uint16_t b);
  inline uint32_t max_u32(uint32_t a, uint32_t b);
  inline uint64_t max_u64(uint64_t a, uint64_t b);
  inline float max_f(float a, float b);
  inline double max_d(double a, double b);
  inline long double max_ld(long double a, long double b);
  /** @} */

  /**
   * @defgroup @b clamp_x
   * @brief Clamps a value to a range.
   * @param value (integral type denoted by suffix) The value to clamp.
   * @param min (integral type denoted by suffix) The minimum value of the range (inclusive).
   * @param max (integral type denoted by suffix) The maximum value of the range (inclusive).
   * @returns (integral type denoted by suffix) @p [value] clamped to the given range.
   * @note - If @p [min] is greater than @p [max], this function returns @p [value].
   * @{
   */
  inline int8_t clamp_i8(int8_t value, int8_t min, int8_t max);
  inline int16_t clamp_i16(int16_t value, int16_t min, int16_t max);
  inline int32_t clamp_i32(int32_t value, int32_t min, int32_t max);
  inline int64_t clamp_i64(int64_t value, int64_t min, int64_t max);
  inline uint8_t clamp_u8(uint8_t value, uint8_t min, uint8_t max);
  inline uint16_t clamp_u16(uint16_t value, uint16_t min, uint16_t max);
  inline uint32_t clamp_u32(uint32_t value, uint32_t min, uint32_t max);
  inline uint64_t clamp_u64(uint64_t value, uint64_t min, uint64_t max);
  inline float clamp_f(float value, float min, float max);
  inline double clamp_d(double value, double min, double max);
  inline long double clamp_ld(long double value, long double min, long double max);
  /** @} */

  /**
   * @defgroup @b fcmp_x
   * @brief Compares two floating-point values.
   * @param lhs (fp type denoted by suffix) The left-hand value to compare.
   * @param rhs (fp type denoted by suffix) The right-hand value to compare.
   * @param abs (fp type denoted by suffix) The absolute tolerance.
   * @param rel (fp type denoted by suffix) The relative tolerance.
   * @return (int32_t) -1 if @p [lhs] < @p [rhs], 1 if @p [lhs] > @p [rhs],
   *         or 0 if the difference between @p [lhs] and @p [rhs] is within
   *         the given relative OR absolute tolerance.
   * @{
   */
  inline int32_t fcmp_f(float lhs, float rhs, float abs, float rel);
  inline int32_t fcmp_d(double lhs, double rhs, double abs, double rel);
  inline int32_t fcmp_ld(long double lhs, long double rhs, long double abs, long double rel);
  /** @} */

  /**
   * @brief Compares two integer values.
   * @param lhs (integer value) The left-hand value to compare.
   * @param rhs (integer value) The right-hand value to compare.
   * @returns (int32_t value) -1 if @p [lhs] < @p [rhs], 1 if @p [lhs] > @p [rhs], 
   *          or 0 if @p [lhs] == @p [rhs].
   * @note - This macro can safely compare signed and unsigned integers.
   * @note - Arguments to this macro are expanded multiple times.
   */
  #define ICMP(lhs, rhs)

  /**
   * @brief Determines if an integral value is in the range of an integral type.
   * @param type (token) The name of the target integral type.
   * @param value (integral value) The value to query.
   * @returns (boolean value) True if @p [value] is in the range of @p [type], 
   *          or false otherwise.
   * @note - @p [type] must be the name of a type recognized by the C standard.
   * @note - The arguments to this macro are expanded more than once.
   */
  #define IN_RANGE(type, value)

  /************************************************************************************************
   * Rounding Utilities
   ************************************************************************************************/

  /**
   * @defgroup @b ceil_x
   * @brief Rounds an integer value up to a multiple.
   * @param value (integer type denoted by suffix) The value to value.
   * @param step (integer type denoted by suffix) The multiple to round to.
   * @returns (integer type denoted by suffix) The smallest multiple 
   *          of @p [step] >= @p [value].
   * @note - If @p [step] is zero, this function returns @p [value].
   * @{
   */
  inline int8_t ceil_i8(int8_t value, int8_t step);
  inline int16_t ceil_i16(int16_t value, int16_t step);
  inline int32_t ceil_i32(int32_t value, int32_t step);
  inline int64_t ceil_i64(int64_t value, int64_t step);
  inline uint8_t ceil_u8(uint8_t value, uint8_t step);
  inline uint16_t ceil_u16(uint16_t value, uint16_t step);
  inline uint32_t ceil_u32(uint32_t value, uint32_t step);
  inline uint64_t ceil_u64(uint64_t value, uint64_t step);
  /** @} */

  /**
   * @defgroup @b floor_x
   * @brief Rounds an integer value down to a multiple.
   * @param value (integer type denoted by suffix) The value to value.
   * @param step (integer type denoted by suffix) The multiple to round to.
   * @returns (integer type denoted by suffix) The greatest multiple 
   *          of @p [step] <= @p [value].
   * @note - If @p [step] is zero, this function returns @p [value].
   * @{
   */
  inline int8_t floor_i8(int8_t value, int8_t step);
  inline int16_t floor_i16(int16_t value, int16_t step);
  inline int32_t floor_i32(int32_t value, int32_t step);
  inline int64_t floor_i64(int64_t value, int64_t step);
  inline uint8_t floor_u8(uint8_t value, uint8_t step);
  inline uint16_t floor_u16(uint16_t value, uint16_t step);
  inline uint32_t floor_u32(uint32_t value, uint32_t step);
  inline uint64_t floor_u64(uint64_t value, uint64_t step);
  
  /**
   * @defgroup @b round_x
   * @brief Rounds am integer value to the nearest multiple.
   * @param value (integer type denoted by suffix) The value to value.
   * @param step (integer type denoted by suffix) The multiple to round to.
   * @returns (integer type denoted by suffix) The neareset multiple 
   *          of @p [step] to @p [value].
   * @note - This function rounds towards zero when multiples are equidistant.
   * @note - If @p [step] is zero, this function returns @p [value].
   * @{
   */
  inline int8_t round_i8(int8_t value, int8_t step);
  inline int16_t round_i16(int16_t value, int16_t step);
  inline int32_t round_i32(int32_t value, int32_t step);
  inline int64_t round_i64(int64_t value, int64_t step);
  inline uint8_t round_u8(uint8_t value, uint8_t step);
  inline uint16_t round_u16(uint16_t value, uint16_t step);
  inline uint32_t round_u32(uint32_t value, uint32_t step);
  inline uint64_t round_u64(uint64_t value, uint64_t step);
  /** @} */

  /**
   * @defgroup @b div_ceil_x
   * @brief Performs a ceiling integer division operation.
   * @param lhs (integer type denoted by suffix) The dividend.
   * @param rhs (integer type denoted by suffix) The divisor.
   * @returns (integer type denoted by suffix) The closest integer 
   *          to zero >= @p [lhs] / @p [rhs].
   * @note - if @p [rhs] is zero, this function returns zero.
   * @{
   */
  inline int8_t div_ceil_i8(int8_t lhs, int8_t rhs);
  inline int16_t div_ceil_i16(int16_t lhs, int16_t rhs);
  inline int32_t div_ceil_i32(int32_t lhs, int32_t rhs);
  inline int64_t div_ceil_i64(int64_t lhs, int64_t rhs);
  inline uint8_t div_ceil_u8(uint8_t lhs, uint8_t rhs);
  inline uint16_t div_ceil_u16(uint16_t lhs, uint16_t rhs);
  inline uint32_t div_ceil_u32(uint32_t lhs, uint32_t rhs);
  inline uint64_t div_ceil_u64(uint64_t lhs, uint64_t rhs);
  /** @} */

  /************************************************************************************************
   * Overflow Detection Utilities
   ************************************************************************************************/
  
  /**
   * @defgroup @b can_add_x
   * @brief Determines if an integer addition operation will overflow.
   * @param lhs (integer type denoted by suffix) The first value to add.
   * @param rhs (integer type denoted by suffix) The second value to add.
   * @returns (bool) False if @p [lhs] + @p [rhs] will overflow, or true otherwise.
   * @{
   */
  inline bool can_add_i8(int8_t lhs, int8_t rhs);
  inline bool can_add_i16(int16_t lhs, int16_t rhs);
  inline bool can_add_i32(int32_t lhs, int32_t rhs);
  inline bool can_add_i64(int64_t lhs, int64_t rhs);
  inline bool can_add_u8(uint8_t lhs, uint8_t rhs);
  inline bool can_add_u16(uint16_t lhs, uint16_t rhs);
  inline bool can_add_u32(uint32_t lhs, uint32_t rhs);
  inline bool can_add_u64(uint64_t lhs, uint64_t rhs);
  /** @} */

  /**
   * @defgroup @b can_sub_x
   * @brief Determines if an integer subtraction operation will overflow.
   * @param lhs (integer type denoted by suffix) The value to subtract from.
   * @param rhs (integer type denoted by suffix) The value to subtract.
   * @returns (bool) False if @p [lhs] - @p [rhs] will overflow, or true otherwise.
   * @{
   */
  inline bool can_sub_i8(int8_t lhs, int8_t rhs);
  inline bool can_sub_i16(int16_t lhs, int16_t rhs);
  inline bool can_sub_i32(int32_t lhs, int32_t rhs);
  inline bool can_sub_i64(int64_t lhs, int64_t rhs);
  inline bool can_sub_u8(uint8_t lhs, uint8_t rhs);
  inline bool can_sub_u16(uint16_t lhs, uint16_t rhs);
  inline bool can_sub_u32(uint32_t lhs, uint32_t rhs);
  inline bool can_sub_u64(uint64_t lhs, uint64_t rhs);
  /** @} */

  /**
   * @defgroup @b can_mul_x
   * @brief Determines if an integer multiplication operation will overflow.
   * @param lhs (integer type denoted by suffix) The first value to multiply.
   * @param rhs (integer type denoted by suffix) The second value to multiply.
   * @returns (bool) False if @p [lhs] * @p [rhs] will overflow, or true otherwise.
   * @{
   */
  inline bool can_mul_i8(int8_t lhs, int8_t rhs);
  inline bool can_mul_i16(int16_t lhs, int16_t rhs);
  inline bool can_mul_i32(int32_t lhs, int32_t rhs);
  inline bool can_mul_i64(int64_t lhs, int64_t rhs);
  inline bool can_mul_u8(uint8_t lhs, uint8_t rhs);
  inline bool can_mul_u16(uint16_t lhs, uint16_t rhs);
  inline bool can_mul_u32(uint32_t lhs, uint32_t rhs);
  inline bool can_mul_u64(uint64_t lhs, uint64_t rhs);
  /** @} */

  /************************************************************************************************
   * Implementation Resources
   ************************************************************************************************/

  #define _TI_char_MAX CHAR_MAX
  #define _TI_char_MIN CHAR_MIN

  #define _TI_short_MAX SHRT_MAX
  #define _TI_short_MIN SHRT_MIN

  #define _TI_int_MAX INT_MAX
  #define _TI_int_MIN INT_MIN

  #define _TI_long_MAX LONG_MAX
  #define _TI_long_MIN LONG_MIN

  #define _TI_long_long_MAX LLONG_MAX
  #define _TI_long_long_MIN LLONG_MIN

  #define _TI_uint8_t_MAX UINT8_MAX
  #define _TI_uint8_t_MIN UINT8_C(0)

  #define _TI_uint16_t_MAX UINT16_MAX
  #define _TI_uint16_t_MIN UINT16_C(0)

  #define _TI_uint32_t_MAX UINT32_MAX
  #define _TI_uint32_t_MIN UINT32_C(0)

  #define _TI_uint64_t_MAX UINT64_MAX
  #define _TI_uint64_t_MIN UINT64_C(0)

  #define _TI_int8_t_MAX INT8_MAX
  #define _TI_int8_t_MIN INT8_MIN

  #define _TI_int16_t_MAX INT16_MAX
  #define _TI_int16_t_MIN INT16_MIN

  #define _TI_int32_t_MAX INT32_MAX
  #define _TI_int32_t_MIN INT32_MIN

  #define _TI_int64_t_MAX INT64_MAX
  #define _TI_int64_t_MIN INT64_MIN

  #define _TI_intptr_t_MAX INTPTR_MAX
  #define _TI_intptr_t_MIN INTPTR_MIN

  #define _TI_uintptr_t_MAX UINTPTR_MAX
  #define _TI_uintptr_t_MIN UINTPTR_C(0)

  #define _TI_intmax_t_MAX INTMAX_MAX
  #define _TI_intmax_t_MIN INTMAX_MIN

  #define _TI_uintmax_t_MAX UINTMAX_MAX
  #define _TI_uintmax_t_MIN UINTMAX_C(0)

  #define _TI_size_t_MAX SIZE_MAX
  #define _TI_size_t_MIN SIZE_C(0)

  #define _TI_ptrdiff_t_MAX PTRDIFF_MAX
  #define _TI_ptrdiff_t_MIN PTRDIFF_MIN

  #define _TI_float_MAX FLT_MAX
  #define _TI_float_MIN FLT_TRUE_MIN

  #define _TI_double_MAX DBL_MAX
  #define _TI_double_MIN DBL_TRUE_MIN

  #define _TI_long_double_MAX LDBL_MAX
  #define _TI_long_double_MIN LDBL_TRUE_MIN

  #define _TI_bool_MAX true
  #define _TI_bool_MIN false

  /************************************************************************************************
   * Implementation of Relational Utilities
   ************************************************************************************************/

  /**** min_x ****/

  int8_t min_i8(int8_t a, int8_t b) {
    return (a < b) ? a : b;
  }

  int16_t min_i16(int16_t a, int16_t b) {
    return (a < b) ? a : b;
  }

  int32_t min_i32(int32_t a, int32_t b) {
    return (a < b) ? a : b;
  }

  int64_t min_i64(int64_t a, int64_t b) {
    return (a < b) ? a : b;
  }

  uint8_t min_u8(uint8_t a, uint8_t b) {
    return (a < b) ? a : b;
  }

  uint16_t min_u16(uint16_t a, uint16_t b) {
    return (a < b) ? a : b;
  }

  uint32_t min_u32(uint32_t a, uint32_t b) {
    return (a < b) ? a : b;
  }

  uint64_t min_u64(uint64_t a, uint64_t b) {
    return (a < b) ? a : b;
  }

  float min_f(float a, float b) {
    return (a < b) ? a : b;
  }

  double min_d(double a, double b) {
    return (a < b) ? a : b;
  }

  long double min_ld(long double a, long double b) {
    return (a < b) ? a : b;
  }

  /**** max_x ****/

  int8_t max_i8(int8_t a, int8_t b) {
    return (a > b) ? a : b;
  }

  int16_t max_i16(int16_t a, int16_t b) {
    return (a > b) ? a : b;
  }

  int32_t max_i32(int32_t a, int32_t b) {
    return (a > b) ? a : b;
  }

  int64_t max_i64(int64_t a, int64_t b) {
    return (a > b) ? a : b;
  }

  uint8_t max_u8(uint8_t a, uint8_t b) {
    return (a > b) ? a : b;
  }

  uint16_t max_u16(uint16_t a, uint16_t b) {
    return (a > b) ? a : b;
  }

  uint32_t max_u32(uint32_t a, uint32_t b) {
    return (a > b) ? a : b;
  }

  uint64_t max_u64(uint64_t a, uint64_t b) {
    return (a > b) ? a : b;
  }

  float max_f(float a, float b) {
    return (a < b) ? a : b;
  }

  double max_d(double a, double b) {
    return (a < b) ? a : b;
  }

  long double max_ld(long double a, long double b) {
    return (a < b) ? a : b;
  }

  /**** clamp_x ****/

  int8_t clamp_i8(int8_t value, int8_t min, int8_t max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  int16_t clamp_i16(int16_t value, int16_t min, int16_t max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  int32_t clamp_i32(int32_t value, int32_t min, int32_t max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  int64_t clamp_i64(int64_t value, int64_t min, int64_t max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  uint8_t clamp_u8(uint8_t value, uint8_t min, uint8_t max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  uint16_t clamp_u16(uint16_t value, uint16_t min, uint16_t max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  uint32_t clamp_u32(uint32_t value, uint32_t min, uint32_t max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  uint64_t clamp_u64(uint64_t value, uint64_t min, uint64_t max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  float clamp_f(float value, float min, float max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  double clamp_d(double value, double min, double max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  long double clamp_ld(long double value, long double min, long double max) {
    if (min <= max) {
      if (value < min) { return min; }
      if (value > max) { return max; }
    }
    return value;
  }

  /**** fcmp_x ****/

  int32_t fcmp_f(float lhs, float rhs, float abs, float rel) {
    if (fabsf(lhs - rhs) <= max_f(abs, rel * 
        max_f(fabsf(lhs), fabsf(rhs)))) {
      return 0;
    } else if (lhs > rhs) {
      return 1;
    } else {
      return -1;
    }
  }

  int32_t fcmp_d(double lhs, double rhs, double abs, double rel) {
    if (fabs(lhs - rhs) <= max_d(abs, rel * 
        max_d(fabs(lhs), fabs(rhs)))) {
      return 0;
    } else if (lhs > rhs) {
      return 1;
    } else {
      return -1;
    }
  }

  int32_t fcmp_ld(long double lhs, long double rhs, 
      long double abs, long double rel) {
    if (fabsl(lhs - rhs) <= max_ld(abs, rel * 
        max_ld(fabsl(lhs), fabsl(rhs)))) {
      return 0;
    } else if (lhs > rhs) {
      return 1;
    } else {
      return -1;
    }
  }

  /**** Other ****/

  #undef ICMP
  #define ICMP(lhs, rhs) ( \
    (((lhs) < 0) && ((rhs) > 0)) ? -1 : \
    (((lhs) > 0) && ((rhs) < 0)) ?  1 : \
    ((lhs) < (rhs)) ? -1 : \
    ((lhs) > (rhs)) ?  1 : 0 \
  )

  #undef IN_RANGE
  #define IN_RANGE(type, value) ( \
    (ICMP((value), _TI_ ## type ## _MIN) >= 0) && \
    (ICMP((value), _TI_ ## type ## _MAX) <= 0) \
  )

  /************************************************************************************************
   * Implementation of Rounding Utilities
   ************************************************************************************************/

  /**** ceil_x ****/

  int8_t ceil_i8(int8_t value, int8_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) {
      return ((value + (step - 1)) / step) * step;
    } else {
      return (value / step) * step;
    }
  }

  int16_t ceil_i16(int16_t value, int16_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) {
      return ((value + (step - 1)) / step) * step;
    } else {
      return (value / step) * step;
    }
  }

  int32_t ceil_i32(int32_t value, int32_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) {
      return ((value + (step - 1)) / step) * step;
    } else {
      return (value / step) * step;
    }
  }

  int64_t ceil_i64(int64_t value, int64_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) {
      return ((value + (step - 1)) / step) * step;
    } else {
      return (value / step) * step;
    }
  }

  uint8_t ceil_u8(uint8_t value, uint8_t step) {
    if (step == 0U) { return value; }
    return ((value + (step - 1U)) / step) * step;
  }

  uint16_t ceil_u16(uint16_t value, uint16_t step) {
    if (step == 0U) { return value; }
    return ((value + (step - 1U)) / step) * step;
  }

  uint32_t ceil_u32(uint32_t value, uint32_t step) {
    if (step == 0U) { return value; }
    return ((value + (step - 1U)) / step) * step;
  }

  uint64_t ceil_u64(uint64_t value, uint64_t step) {
    if (step == 0U) { return value; }
    return ((value + (step - 1U)) / step) * step;
  }

  /**** floor_x ****/

  int8_t floor_i8(int8_t value, int8_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) { 
      return (value / step) * step; 
    } else { 
      return ((value - (step - 1)) / step) * step; 
    }
  }

  int16_t floor_i16(int16_t value, int16_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) { 
      return (value / step) * step; 
    } else { 
      return ((value - (step - 1)) / step) * step; 
    }
  }

  int32_t floor_i32(int32_t value, int32_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) { 
      return (value / step) * step; 
    } else { 
      return ((value - (step - 1)) / step) * step; 
    }
  }

  int64_t floor_i64(int64_t value, int64_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) { 
      return (value / step) * step; 
    } else { 
      return ((value - (step - 1)) / step) * step; 
    }
  }

  uint8_t floor_u8(uint8_t value, uint8_t step) {
    if (step == 0U) { return value; }
    return (value / step) * step; 
  }

  uint16_t floor_u16(uint16_t value, uint16_t step) {
    if (step == 0U) { return value; }
    return (value / step) * step; 
  }

  uint32_t floor_u32(uint32_t value, uint32_t step) {
    if (step == 0U) { return value; }
    return (value / step) * step; 
  }

  uint64_t floor_u64(uint64_t value, uint64_t step) {
    if (step == 0U) { return value; }
    return (value / step) * step; 
  }

  /**** round_x ****/

  int8_t round_i8(int8_t value, int8_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) {
      return ((value + (step / 2)) / step) * step;
    } else {
      return ((value - (step / 2)) / step) * step;
    }
  }

  int16_t round_i16(int16_t value, int16_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) {
      return ((value + (step / 2)) / step) * step;
    } else {
      return ((value - (step / 2)) / step) * step;
    }
  }

  int32_t round_i32(int32_t value, int32_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) {
      return ((value + (step / 2)) / step) * step;
    } else {
      return ((value - (step / 2)) / step) * step;
    }
  }

  int64_t round_i64(int64_t value, int64_t step) {
    if (step == 0) { return value; }
    if (step < 0) { step = -step; }
    if (value >= 0) {
      return ((value + (step / 2)) / step) * step;
    } else {
      return ((value - (step / 2)) / step) * step;
    }
  }

  uint8_t round_u8(uint8_t value, uint8_t step) {
    if (step == 0U) { return value; }
    return ((value + (step / 2U)) / step) * step;
  }

  uint16_t round_u16(uint16_t value, uint16_t step) {
    if (step == 0U) { return value; }
    return ((value + (step / 2U)) / step) * step;
  }

  uint32_t round_u32(uint32_t value, uint32_t step) {
    if (step == 0U) { return value; }
    return ((value + (step / 2U)) / step) * step;
  }

  uint64_t round_u64(uint64_t value, uint64_t step) {
    if (step == 0U) { return value; }
    return ((value + (step / 2U)) / step) * step;
  }

  /**** div_ceil_x ****/

  int8_t div_ceil_i8(int8_t lhs, int8_t rhs) {
    if (rhs == 0) { return lhs; }
    const int8_t abs_r = rhs < 0 ? -rhs : rhs;
    if (lhs >= 0) {
      return (lhs + (abs_r - 1)) / rhs;
    } else {
      return (lhs - (abs_r - 1)) / rhs;
    }
  }

  int16_t div_ceil_i16(int16_t lhs, int16_t rhs) {
    if (rhs == 0) { return lhs; }
    const int16_t abs_r = rhs < 0 ? -rhs : rhs;
    if (lhs >= 0) {
      return (lhs + (abs_r - 1)) / rhs;
    } else {
      return (lhs - (abs_r - 1)) / rhs;
    }
  }

  int32_t div_ceil_i32(int32_t lhs, int32_t rhs) {
    if (rhs == 0) { return lhs; }
    const int32_t abs_r = rhs < 0 ? -rhs : rhs;
    if (lhs >= 0) {
      return (lhs + (abs_r - 1)) / rhs;
    } else {
      return (lhs - (abs_r - 1)) / rhs;
    }
  }

  int64_t div_ceil_i64(int64_t lhs, int64_t rhs) {
    if (rhs == 0) { return lhs; }
    const int64_t abs_r = rhs < 0 ? -rhs : rhs;
    if (lhs >= 0) {
      return (lhs + (abs_r - 1)) / rhs;
    } else {
      return (lhs - (abs_r - 1)) / rhs;
    }
  }

  uint8_t div_ceil_u8(uint8_t lhs, uint8_t rhs) {
    if (rhs == 0U) { return lhs; }
    return (lhs + (rhs - 1U)) / rhs;
  }

  uint16_t div_ceil_u16(uint16_t lhs, uint16_t rhs) {
    if (rhs == 0U) { return lhs; }
    return (lhs + (rhs - 1U)) / rhs;
  }

  uint32_t div_ceil_u32(uint32_t lhs, uint32_t rhs) {
    if (rhs == 0U) { return lhs; }
    return (lhs + (rhs - 1U)) / rhs;
  }

  uint64_t div_ceil_u64(uint64_t lhs, uint64_t rhs) {
    if (rhs == 0U) { return lhs; }
    return (lhs + (rhs - 1U)) / rhs;
  }

  /************************************************************************************************
   * Implementation of Overflow Detection Utilities
   ************************************************************************************************/

  /**** can_add_x ****/

  bool can_add_i8(int8_t lhs, int8_t rhs) {
    if (rhs > 0) {
      return lhs <= (INT8_MAX - rhs);
    } else {
      return lhs >= (INT8_MIN - rhs);
    }
  }

  bool can_add_i16(int16_t lhs, int16_t rhs) {
    if (rhs > 0) {
      return lhs <= (INT16_MAX - rhs);
    } else {
      return lhs >= (INT16_MIN - rhs);
    }
  }

  bool can_add_i32(int32_t lhs, int32_t rhs) {
    if (rhs > 0) {
      return lhs <= (INT32_MAX - rhs);
    } else {
      return lhs >= (INT32_MIN - rhs);
    }
  }

  bool can_add_i64(int64_t lhs, int64_t rhs) {
    if (rhs > 0) {
      return lhs <= (INT64_MAX - rhs);
    } else {
      return lhs >= (INT64_MIN - rhs);
    }
  }

  bool can_add_u8(uint8_t lhs, uint8_t rhs) {
    return lhs <= (UINT8_MAX - rhs);
  }

  bool can_add_u16(uint16_t lhs, uint16_t rhs) {
    return lhs <= (UINT16_MAX - rhs);
  }

  bool can_add_u32(uint32_t lhs, uint32_t rhs) {
    return lhs <= (UINT32_MAX - rhs);
  }

  bool can_add_u64(uint64_t lhs, uint64_t rhs) {
    return lhs <= (UINT64_MAX - rhs);
  }


  /**** can_sub_x ****/

  bool can_sub_i8(int8_t lhs, int8_t rhs) {
    if (rhs > 0) {
      return lhs >= (INT8_MIN + rhs);
    } else {
      return lhs <= (INT8_MAX + rhs);
    }
  }

  bool can_sub_i16(int16_t lhs, int16_t rhs) {
    if (rhs > 0) {
      return lhs >= (INT16_MIN + rhs);
    } else {
      return lhs <= (INT16_MAX + rhs);
    }
  }

  bool can_sub_i32(int32_t lhs, int32_t rhs) {
    if (rhs > 0) {
      return lhs >= (INT32_MIN + rhs);
    } else {
      return lhs <= (INT32_MAX + rhs);
    }
  }

  bool can_sub_i64(int64_t lhs, int64_t rhs) {
    if (rhs > 0) {
      return lhs >= (INT64_MIN + rhs);
    } else {
      return lhs <= (INT64_MAX + rhs);
    }
  }

  bool can_sub_u8(uint8_t lhs, uint8_t rhs) {
    return lhs >= rhs;
  }

  bool can_sub_u16(uint16_t lhs, uint16_t rhs) {
    return lhs >= rhs;
  }

  bool can_sub_u32(uint32_t lhs, uint32_t rhs) {
    return lhs >= rhs;
  }

  bool can_sub_u64(uint64_t lhs, uint64_t rhs) {
    return lhs >= rhs;
  }


  /**** can_mul_x ****/

  bool can_mul_i8(int8_t lhs, int8_t rhs) {
    if (lhs > 0) {
      if (rhs > 0) { return lhs <= (INT8_MAX / rhs); }
      if (rhs < 0) { return rhs >= (INT8_MIN / lhs); }
    }
    if (lhs < 0) {
      if (rhs > 0) { return lhs >= (INT8_MIN / rhs); }
      if (rhs < 0) { return lhs >= (INT8_MAX / rhs); }
    }
    return true;
  }

  bool can_mul_i16(int16_t lhs, int16_t rhs) {
    if (lhs > 0) {
      if (rhs > 0) { return lhs <= (INT8_MAX / rhs); }
      if (rhs < 0) { return rhs >= (INT8_MIN / lhs); }
    }
    if (lhs < 0) {
      if (rhs > 0) { return lhs >= (INT8_MIN / rhs); }
      if (rhs < 0) { return lhs >= (INT8_MAX / rhs); }
    }
    return true;
  }

  bool can_mul_i32(int32_t lhs, int32_t rhs) {
    if (lhs > 0) {
      if (rhs > 0) { return lhs <= (INT8_MAX / rhs); }
      if (rhs < 0) { return rhs >= (INT8_MIN / lhs); }
    }
    if (lhs < 0) {
      if (rhs > 0) { return lhs >= (INT8_MIN / rhs); }
      if (rhs < 0) { return lhs >= (INT8_MAX / rhs); }
    }
    return true;
  }

  bool can_mul_i64(int64_t lhs, int64_t rhs) {
    if (lhs > 0) {
      if (rhs > 0) { return lhs <= (INT8_MAX / rhs); }
      if (rhs < 0) { return rhs >= (INT8_MIN / lhs); }
    }
    if (lhs < 0) {
      if (rhs > 0) { return lhs >= (INT8_MIN / rhs); }
      if (rhs < 0) { return lhs >= (INT8_MAX / rhs); }
    }
    return true;
  }

  bool can_mul_u8(uint8_t lhs, uint8_t rhs) {
    return lhs <= (UINT8_MAX / rhs);
  }

  bool can_mul_u16(uint16_t lhs, uint16_t rhs) {
    return lhs <= (UINT16_MAX / rhs);
  }

  bool can_mul_u32(uint32_t lhs, uint32_t rhs) {
    return lhs <= (UINT32_MAX / rhs);
  }

  bool can_mul_u64(uint64_t lhs, uint64_t rhs) {
    return lhs <= (UINT64_MAX / rhs);
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */