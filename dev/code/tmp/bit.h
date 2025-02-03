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
 * @file src/common/util/bit.h
 * @authors Aaron McBride
 * @brief Bit manipulation utilities.
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
   * @section Bit Manipulation Utilities
   **********************************************************************************************/

  /**
   * @brief Rounds a value down to the nearest integral power of 2.
   * @param value (integral type) The target value.
   * @returns (integral type) The largest power of 2 less than or 
   *          equal to @p [value].
   * @note - The arguments of this macro are only expanded once.
   * @note - The result will have only one set bit.
   */
  #define bit_floor(value)

  /**
   * @brief Rounds a value up to the nearest integral power of 2.
   * @param value (integral type) The target value.
   * @returns (integral type) The smallest power of 2 greater than or 
   *          equal to @p [value].
   * @note - The arguments of this macro are only expanded once.
   * @note - The result will have only one set bit.
   */
  #define bit_ceil(value)

  /**
   * @brief Reverses the bits of a value.
   * @param value (integral type) The target value.
   * @returns (type of @p [value]) The bit-wise reversal of @p [value].
   * @note - The arguments of this macro are only expanded once.
   */
  #define bit_rev(value)

  /**
   * @brief Reverses the bytes of a value.
   * @param value (integral type) The target value.
   * @returns (type of @p [value]) The byte-wise reversal of @p [value].
   * @note - The arguments of this macro are only expanded once.
   */
  #define byte_rev(value)

  /**
   * @brief Rotates the bits of a value.
   * @param value (integral type) The target value.
   * @param n (integer) The number of bits to rotate by. 
   *          Positive = msb, Negative = lsb.
   * @returns (type of @p [value]) The bit-wise rotation of 
   *          @p [value] by @p [n].
   * @note - Bits rotated beyond the bounds of the value, 
   *         wrap around to the other side.
   * @note - The arguments of this macro are only expanded once.
   */
  #define bit_rot(value, n)

  /**********************************************************************************************
   * @section Bit Inspection Utilities
   **********************************************************************************************/

  /**
   * @brief Determines the number of leading zeros in a value.
   * @param value (integral type) The target value.
   * @returns (int32_t) The number of leading zeros in @p [value].
   * @note - The arguments of this macro is only expanded once.
   */
  #define clz(value)

  /**
   * @brief Determines the number of trailing zeros in an integer value.
   * @param value (integral type) The target value.
   * @returns (int32_t) The number of trailing zeros in @p [value].
   * @note - The arguments of this macro is only expanded once.
   */
  #define ctz(value)

  /**
   * @brief Determines the number of set bits in an integer value.
   * @param value (integral type) The target value.
   * @returns (int32_t) The number of set bits in @p [value].
   * @note - The arguments of this macro is only expanded once.
   */
  #define popcnt(value)

  /**
   * @brief Determines the number of bits required to represent a value.
   * @param x (integral type) The target value.
   * @returns (int32_t) The number of bits needed to fully represent @p [x].
   */
  #define bit_width(value)

  /**********************************************************************************************
   * @section Uncategorised Bit Utilities
   **********************************************************************************************/

  /**
   * @brief Gets the size of a type in bits.
   * @param x (expression) The target type or value.
   * @returns (int32_t) The size of @p [x] in bits.
   * @note - The arguments of this macro is only expanded once.
   */
  #define bit_size(x)

  /**
   * @brief Creates a bit mask.
   * @param pos (integer) The position of the first set bit (from lsb).
   * @param len (integer) The number of consecutive bits to set.
   * @returns (max unsigned integer) A bit mask with @p [len] set bits, 
   *          starting @p [pos] bits from the lsb.
   * @note - The arguments of this macro are only expanded once.
   */
  #define get_msk(pos, len)  

  /**
   * @brief Casts a value to another type without changing its bit 
   *        representation.
   * @param type (token) The name of the target type.
   * @param value (value) The target value.
   * @returns (type) The bitwise representation of @p [value] cast
   *          to the target type - @p [type].
   */
  #define bit_cast(type, value)

  /** @internal */

  /**********************************************************************************************
   * @section Implementation Resources
   **********************************************************************************************/

  // Gets an unsigned value with the same size
  // as the given integral type.
  #define to_uint_(x) \
    typeof(_Generic((x), \
      int8_t: uint8_t, \
      int16_t: uint16_t, \
      int32_t: uint32_t, \
      int64_t: uint64_t, \
      uint8_t: uint8_t, \
      uint16_t: uint16_t, \
      uint32_t: uint32_t, \
      uint64_t: uint64_t, \
      float: uint32_t, \
      double: uint64_t, \
      bool: uint8_t, \
      char: uint8_t, \
      default: void \
    ))

  /**********************************************************************************************
   * @section Implementation of Bit Manipulation Utilities
   **********************************************************************************************/

  #undef bit_floor
  #define bit_floor(value) ({ \
    const to_unsigned_(value) value_ = (value); \
    (typeof(value))(UINTMAX_C(1) << (bit_width(value_) - 1)); \
  })

  #define bit_ceil
  #define bit_ceil(value) ({ \
    const to_unsigned_(value) value_ = (value); \
    (typeof(value))(UINTMAX_C(1) << bit_width(value_ - 1)); \
  })

  #undef bit_rev
  #define bit_rev(value) ({ \
    const to_unsigned_(value) value_ = (value); \
    typeof(uvalue) result = 0; \
    for (int32_t i = 0; i < bit_size(value_); i++) { \
      const typeof(uvalue) msk = UINTMAX_C(1) << i; \
      if (uvalue & msk) { \
        result |= (UINTMAX_C(1) << (bsize - 1 - i)); \
      } \
    } \
    (typeof(value_))result; \
  })

  #undef byte_rev
  #define byte_rev(value) ({ \
    const __auto_type value_ = (value); \
    const to_unsigned_(value_) uvalue = (value_); \
    static const int32_t bsize = bit_size(value_); \
    typeof(uvalue) result = 0; \
    for (int32_t i = 0; i < bsize; i += CHAR_BIT) { \
      const typeof(uvalue) msk = UINTMAX_C(0xFF) << i; \
      result |= (uvalue & msk) << ((bsize - CHAR_BIT) - i); \
    } \
    (typeof(value_))result; \
  })

  #undef bit_rot
  #define bit_rot(value, n) ({ \
    const __auto_type value_ = (value); \
    const to_unsigned_(value_) uvalue = (value_); \
    const int32_t n_ = (n); \
    const int32_t r = n_ % bit_size(value_); \
    typeof(uvalue) result = 0; \
    if (n_ < 0) { \
      result = (uvalue << (bsize + r)) | (uvalue >> -r); \
    } else { \
      result = (uvalue << r) | (uvalue >> (bsize - r)); \
    } \
    (typeof(value_))result; \
  })

  /**********************************************************************************************
   * @section Implementation of Bit Inspection Utilities
   **********************************************************************************************/

  #undef clz
  #define clz(value) ({ \
    const to_unsigned_(value) uvalue_ = (value); \
    const int32_t bsize = bit_size(value_); \
    int32_t result = 0; \
    for (int32_t i = bsize - 1; i >= 0; i--) { \
      const typeof(uvalue_) msk = get_msk(i, 1); \
      if (uvalue_ & msk) { break; } \
      result++; \
    } \
    result; \
  })

  #undef ctz
  #define ctz(value) ({ \
    int32_t result = 0; \
    const to_unsigned_(value) uvalue_ = (value); \
    const int32_t bsize = bit_size(value); \
    for (int32_t i = 0; i < bsize; i++) { \
      const typeof(uvalue_) msk = get_msk(i, 1); \
      if (uvalue_ & msk) { break; } \
      result++; \
    } \
    result; \
  })

  #undef popcnt
  #define popcnt(value) ({ \
    int32_t result = 0; \
    const to_unsigned_(value) uvalue_ = (value); \
    const int32_t bsize = bit_size(value); \
    for (int32_t i = 0; i < bsize; i++) { \
      const typeof(uvalue_) msk = get_msk(i, 1); \
      if (uvalue_ & msk) { result++; } \
    } \
    result; \
  })

  #undef bit_width
  #define bit_width(value) ({ \
    const __auto_type value_ = (value); \
    bit_size(value_) - clz(value_); \
  })

  /**********************************************************************************************
   * @section Implementation of Uncategorised Bit Utilities
   **********************************************************************************************/

  #undef bit_size
  #define bit_size(x) ({ \
    (int32_t)sizeof(x) * CHAR_BIT; \
  })

  #undef get_msk
  #define get_msk(pos, len) ({ \
    ((UINTMAX_C(1) << (len)) - UINTMAX_C(1)) << (pos); \
  })

  #undef bit_cast
  #define bit_cast(type, value) ({ \
    const __auto_type value_ = (value); \
    const union { typeof(value_) v; type r; } u = {.v = value_}; \
    u.r; \
  })

  /** @endinternal */

#ifdef __cplusplus
  extern "C" }
#endif