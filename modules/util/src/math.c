/**
 * This file is part of the Titan Project.
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
 * @file modules/util/include/util/math.h
 * @authors Aaron McBride
 * @brief Implementation of math utilities.
 */

#include "util/math.h" // header

#define MAX_FUNC_IMPL(type, suffix) \
  type ti_max_##suffix(const type value_1, const type value_2) { \
    return value_1 > value_2 ? value_1 : value_2; \
  }

MAX_FUNC_IMPL(int8_t, i8)
MAX_FUNC_IMPL(int16_t, i16)
MAX_FUNC_IMPL(int32_t, i32)
MAX_FUNC_IMPL(int64_t, i64)
MAX_FUNC_IMPL(uint8_t, u8)
MAX_FUNC_IMPL(uint16_t, u16)
MAX_FUNC_IMPL(uint32_t, u32)
MAX_FUNC_IMPL(uint64_t, u64)

#define MIN_FUNC_IMPL(type, suffix) \
  type ti_min_##suffix(const type value_1, const type value_2) { \
    return value_1 < value_2 ? value_1 : value_2; \
  }

MIN_FUNC_IMPL(int8_t, i8)
MIN_FUNC_IMPL(int16_t, i16)
MIN_FUNC_IMPL(int32_t, i32)
MIN_FUNC_IMPL(int64_t, i64)
MIN_FUNC_IMPL(uint8_t, u8)
MIN_FUNC_IMPL(uint16_t, u16)
MIN_FUNC_IMPL(uint32_t, u32)
MIN_FUNC_IMPL(uint64_t, u64)

#define CLAMP_FUNC_IMPL(type, suffix) \
  type ti_clamp_##suffix(const type value, const type min, const type max) { \
    if (value < min) { \
      return min; \
    } \
    if (value > max) { \
      return max; \
    } \
    return value; \
  }

CLAMP_FUNC_IMPL(int8_t, i8)
CLAMP_FUNC_IMPL(int16_t, i16)
CLAMP_FUNC_IMPL(int32_t, i32)
CLAMP_FUNC_IMPL(int64_t, i64)
CLAMP_FUNC_IMPL(uint8_t, u8)
CLAMP_FUNC_IMPL(uint16_t, u16)
CLAMP_FUNC_IMPL(uint32_t, u32)
CLAMP_FUNC_IMPL(uint64_t, u64)

#define FLOOR_FUNC_SIGNED_IMPL(type, suffix, limit_prefix) \
  type ti_floor_##suffix(const type value, const type align, enum ti_errc_t* errc_out) { \
    *errc_out = TI_ERRC_NONE; \
    if (align <= 0) { \
      *errc_out = TI_ERRC_INVALID_ARG; \
      return value; \
    } \
    type rem = value % align; \
    if ((rem != 0) && ((value < 0) != (align < 0))) { \
      type floored = value - rem - align; \
      if (floored > value) { \
        *errc_out = TI_ERRC_OVERFLOW; \
        return limit_prefix##_MIN; \
      } \
      return floored; \
    } \
    return value - rem; \
  }

FLOOR_FUNC_SIGNED_IMPL(int8_t, i8, INT8)
FLOOR_FUNC_SIGNED_IMPL(int16_t, i16, INT16)
FLOOR_FUNC_SIGNED_IMPL(int32_t, i32, INT32)
FLOOR_FUNC_SIGNED_IMPL(int64_t, i64, INT64)

#define FLOOR_FUNC_UNSIGNED_IMPL(type, suffix) \
  type ti_floor_##suffix(const type value, const type align, enum ti_errc_t* errc_out) { \
    *errc_out = TI_ERRC_NONE; \
    if (align == 0) { \
      *errc_out = TI_ERRC_INVALID_ARG; \
      return value; \
    } \
    return value - (value % align); \
  }

FLOOR_FUNC_UNSIGNED_IMPL(uint8_t, u8)
FLOOR_FUNC_UNSIGNED_IMPL(uint16_t, u16)
FLOOR_FUNC_UNSIGNED_IMPL(uint32_t, u32)
FLOOR_FUNC_UNSIGNED_IMPL(uint64_t, u64)

#define CEIL_FUNC_SIGNED_IMPL(type, suffix, limit_prefix) \
  type ti_ceil_##suffix(const type value, const type align, enum ti_errc_t* errc_out) { \
    *errc_out = TI_ERRC_NONE; \
    if (align <= 0) { \
      *errc_out = TI_ERRC_INVALID_ARG; \
      return value; \
    } \
    type rem = value % align; \
    if ((rem != 0) && ((value > 0) == (align > 0))) { \
      type ceiled = value - rem + align; \
      if (ceiled < value) { \
        *errc_out = TI_ERRC_OVERFLOW; \
        return limit_prefix##_MAX; \
      } \
      return ceiled; \
    } \
    return value - rem; \
  }

CEIL_FUNC_SIGNED_IMPL(int8_t, i8, INT8)
CEIL_FUNC_SIGNED_IMPL(int16_t, i16, INT16)
CEIL_FUNC_SIGNED_IMPL(int32_t, i32, INT32)
CEIL_FUNC_SIGNED_IMPL(int64_t, i64, INT64)

#define CEIL_FUNC_UNSIGNED_IMPL(type, suffix, limit_prefix) \
  type ti_ceil_##suffix(const type value, const type align, enum ti_errc_t* errc_out) { \
    *errc_out = TI_ERRC_NONE; \
    if (align == 0) { \
      *errc_out = TI_ERRC_INVALID_ARG; \
      return value; \
    } \
    type rem = value % align; \
    if (rem != 0) { \
      type up = value + (align - rem); \
      if (up < value) { \
        *errc_out = TI_ERRC_OVERFLOW; \
        return limit_prefix##_MAX; \
      } \
      return up; \
    } \
    return value; \
  }

CEIL_FUNC_UNSIGNED_IMPL(uint8_t, u8, UINT8)
CEIL_FUNC_UNSIGNED_IMPL(uint16_t, u16, UINT16)
CEIL_FUNC_UNSIGNED_IMPL(uint32_t, u32, UINT32)
CEIL_FUNC_UNSIGNED_IMPL(uint64_t, u64, UINT64)

#define ROUND_FUNC_SIGNED_IMPL(type, suffix, limit_prefix) \
  type ti_round_##suffix(const type value, const type align, enum ti_errc_t* errc_out) { \
    *errc_out = TI_ERRC_NONE; \
    if (align <= 0) { \
      *errc_out = TI_ERRC_INVALID_ARG; \
      return value; \
    } \
    type rem = value % align; \
    type down = value - rem; \
    if ((rem != 0) && ((value < 0) != (align < 0))) { \
      type adj = down - align; \
      if (adj > value) { \
        *errc_out = TI_ERRC_OVERFLOW; \
        return limit_prefix##_MIN; \
      } \
      down = adj; \
    } \
    type up = down; \
    if ((rem != 0) && ((value > 0) == (align > 0))) { \
      type adj = down + align; \
      if (adj < value) { \
        *errc_out = TI_ERRC_OVERFLOW; \
        return limit_prefix##_MAX; \
      } \
      up = adj; \
    } \
    type diff_down = value - down; \
    type diff_up = up - value; \
    if (diff_up < diff_down) { \
      return up; \
    } \
    return down; \
  }

ROUND_FUNC_SIGNED_IMPL(int8_t, i8, INT8)
ROUND_FUNC_SIGNED_IMPL(int16_t, i16, INT16)
ROUND_FUNC_SIGNED_IMPL(int32_t, i32, INT32)
ROUND_FUNC_SIGNED_IMPL(int64_t, i64, INT64)

#define ROUND_FUNC_UNSIGNED_IMPL(type, suffix, limit_prefix) \
  type ti_round_##suffix(const type value, const type align, enum ti_errc_t* errc_out) { \
    *errc_out = TI_ERRC_NONE; \
    if (align == 0) { \
      *errc_out = TI_ERRC_INVALID_ARG; \
      return value; \
    } \
    type rem = value % align; \
    type down = value - rem; \
    type up = down; \
    if (rem != 0) { \
      up = down + align; \
      if (up < value) { \
        *errc_out = TI_ERRC_OVERFLOW; \
        return limit_prefix##_MAX; \
      } \
    } \
    if ((rem * 2) < align) { \
      return down; \
    } \
    return up; \
  }

ROUND_FUNC_UNSIGNED_IMPL(uint8_t, u8, UINT8)
ROUND_FUNC_UNSIGNED_IMPL(uint16_t, u16, UINT16)
ROUND_FUNC_UNSIGNED_IMPL(uint32_t, u32, UINT32)
ROUND_FUNC_UNSIGNED_IMPL(uint64_t, u64, UINT64)