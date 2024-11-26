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
 * @file include/tal/bit.h
 * @authors Aaron McBride
 * @brief Bit manipulation utilities.
 * @note API stable.
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Type Size Utilities
   **************************************************************************************************/

  /**
   * @def @b tal_bit_size(type)
   * @brief Evaluates to the size of @p [type] in bits.
   * @param type (typename) The type to query.
   */

  /**
   * @def @b tal_byte_size(type)
   * @brief Evaluates to the size of @p [type] in bytes.
   * @param type (typename) The type to query.
   * @note - Prefer to sizeof when size in bytes specifically is needed.
   */

  /**************************************************************************************************
   * @section Bit Querying Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_single_bit
   * @brief Determines if an integer is a power of two.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (bool) True if the given value is a power of two, or false otherwise.
   * @note - If an integer is a power of two, it has only one set bit.
   * @{
   */
  inline bool tal_single_bit_u8(const uint8_t value);
  inline bool tal_single_bit_u16(const uint16_t value);
  inline bool tal_single_bit_u32(const uint32_t value);
  inline bool tal_single_bit_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_bit_width
   * @brief Determines the number of bits needed to represent a numeric value.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The minimum number of bits needed to represent the given
   *          value (1 + log2(value)).
   * @note - If the given value is equal to 0, this function returns 0.
   * @{
   */
  inline int32_t tal_bit_width_u8(const uint8_t value);
  inline int32_t tal_bit_width_u16(const uint16_t value);
  inline int32_t tal_bit_width_u32(const uint32_t value);
  inline int32_t tal_bit_width_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_clz
   * @brief Counts the number of leading zero bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of leading zero bits in the given value.
   * @note - "Leading" bits are the most significant bits.
   * @{
   */
  inline int32_t tal_clz_u8(const uint8_t value);
  inline int32_t tal_clz_u16(const uint16_t value);
  inline int32_t tal_clz_u32(const uint32_t value);
  inline int32_t tal_clz_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_clo
   * @brief Counts the number of leading one bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of leading one bits in the given value.
   * @note - "Leading" bits are the most significant bits.
   * @{
   */
  inline int32_t tal_clo_u8(const uint8_t value);
  inline int32_t tal_clo_u16(const uint16_t value);
  inline int32_t tal_clo_u32(const uint32_t value);
  inline int32_t tal_clo_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_ctz
   * @brief Counts the number of trailing zero bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of trailing zero bits in the given value.
   * @note - "Trailing" bits are the least significant bits.
   * @{
   */
  inline int32_t tal_ctz_u8(const uint8_t value);
  inline int32_t tal_ctz_u16(const uint16_t value);
  inline int32_t tal_ctz_u32(const uint32_t value);
  inline int32_t tal_ctz_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_cto
   * @brief Counts the number of trailing one bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of trailing one bits in the given value.
   * @note - "Trailing" bits are the least significant bits.
   * @{
   */
  inline int32_t tal_cto_u8(const uint8_t value);
  inline int32_t tal_cto_u16(const uint16_t value);
  inline int32_t tal_cto_u32(const uint32_t value);
  inline int32_t tal_cto_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_popcount
   * @brief Counts the number of set bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of set bits in the given value.
   * @{
   */
  inline int32_t tal_popcount_u8(const uint8_t value);
  inline int32_t tal_popcount_u16(const uint16_t value);
  inline int32_t tal_popcount_u32(const uint32_t value);
  inline int32_t tal_popcount_u64(const uint64_t value);
  /** @} */

  /**************************************************************************************************
   * @section Bit Manipulation Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_rbit
   * @brief Reverses the bits of an integer.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The given value with the 
   *          order of it's bits reversed.
   * @{
   */
  inline uint8_t tal_rbit_u8(const uint8_t value);
  inline uint16_t tal_rbit_u16(const uint16_t value);
  inline uint32_t tal_rbit_u32(const uint32_t value);
  inline uint64_t tal_rbit_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_rbyte
   * @brief Reverses the bits of an integer.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The given value with the 
   *          order of it's bytes reversed.
   * @{
   */
  inline uint16_t tal_rbyte_u16(const uint16_t value);
  inline uint32_t tal_rbyte_u32(const uint32_t value);
  inline uint64_t tal_rbyte_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_bit_ceil
   * @brief Rounds an integer up to the nearest power of two.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The smallest power 
   *          of two which is greater than or equal to the given value.
   * @note - If an integer is power of two, it has only one set bit.
   * @{
   */
  inline uint8_t tal_bit_ceil_u8(const uint8_t value);
  inline uint16_t tal_bit_ceil_u16(const uint16_t value);
  inline uint32_t tal_bit_ceil_u32(const uint32_t value);
  inline uint64_t tal_bit_ceil_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_bit_floor
   * @brief Rounds an integer down to the nearest power of two.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The greatest power 
   *          of two which is less than or equal to the given value.
   * @note - If an integer is power of two, it has only one set bit.
   * @{
   */
  inline uint8_t tal_bit_floor_u8(const uint8_t value);
  inline uint16_t tal_bit_floor_u16(const uint16_t value);
  inline uint32_t tal_bit_floor_u32(const uint32_t value);
  inline uint64_t tal_bit_floor_u64(const uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_rotl
   * @brief Performs a circular left shift on an integer value.
   * @param value (unsigned integer denoted by suffix) The value to rotate.
   * @param shift (int32_t) The number of bits to rotate by.
   * @returns (unsigned integer denoted by suffix) The result of circularly 
   *          rotating the given value to the left by @p [shift] bits, or right
   *          by @p [shift] bits if @p [shift] is negative.
   * @note - This function performs a "circular shift", meaining that bits
   *         shifted beyond the end of the integer's range wrap around to
   *         the beginning.
   * @{
   */
  inline uint8_t tal_rotl_u8(const uint8_t value, const int32_t shift);
  inline uint16_t tal_rotl_u16(const uint16_t value, const int32_t shift);
  inline uint32_t tal_rotl_u32(const uint32_t value, const int32_t shift);
  inline uint64_t tal_rotl_u64(const uint64_t value, const int32_t shift);
  /** @} */

  /**
   * @defgroup @b tal_rotr
   * @brief Performs a circular right shift on an integer value.
   * @param value (unsigned integer denoted by suffix) The value to rotate.
   * @param shift (int32_t) The number of bits to rotate by.
   * @returns (unsigned integer denoted by suffix) The result of circularly 
   *          rotating the given value to the right by 'shift' bits, or left
   *          by @p [shift] bits is @p [shift] is negative.
   * @note - This function performs a "circular shift", meaining that bits
   *         shifted beyond the end of the integer's range wrap around to
   *         the beginning.
   * @{
   */
  inline uint8_t tal_rotr_u8(const uint8_t value, const int32_t shift);
  inline uint16_t tal_rotr_u16(const uint16_t value, const int32_t shift);
  inline uint32_t tal_rotr_u32(const uint32_t value, const int32_t shift);
  inline uint64_t tal_rotr_u64(const uint64_t value, const int32_t shift);
  /** @} */

  /**************************************************************************************************
   * @section Bitmask Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_mask
   * @brief Creates a mask of contiguous set bits at specific location.
   * @param pos (int32_t) The number of bits between the LSB and the first set bit.
   * @param len (int32_t) The number of contiguous set bits.
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or 
   *            @p [len] is negative, @p [pos] + @p [len] exceeds the bit-width 
   *            of the suffix type, or an internal error occurs.
   * @returns (unsigned integer denoted by suffix) A mask with @p [len] 
   *          contiguous set bits starting @p [pos] bits from the LSB, or 0 if 
   *          an error occurs.
   */
  inline uint8_t tal_mask_u8(const int32_t pos, const int32_t len, 
      bool* const err);
  inline uint16_t tal_mask_u16(const int32_t pos, const int32_t len, 
      bool* const err);
  inline uint32_t tal_mask_u32(const int32_t pos, const int32_t len, 
      bool* const err);
  inline uint64_t tal_mask_u64(const int32_t pos, const int32_t len, 
      bool* const err);

  /**
   * @defgroup @b tal_write_bits
   * @brief Writes a value to a specific range of bits in another value.
   * @param value (unsigned integer denoted by suffix) The value to write to.
   * @param dest (unsigned integer denoted by suffix) The value to write to.
   * @param pos (int32_t) The position of the range to write to (bits from lsb).
   * @param len (int32_t) The length of the range to write to (bits).
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or 
   *            @p [len] is negative, @p [pos] + @p [len] exceeds the bit-width 
   *            of the suffix type, the bit-width of @p [value] exceeds @p [len], 
   *            or an internal error occurs.
   * @returns (unsigned integer denoted by suffix) The result of writing 
   *          @p [value] to the range of bits in @p [dest] specified by @p [pos] 
   *          and @p [len] or @p [dest] unaltered if an error occurs.
   */
  inline uint8_t tal_write_bits_u8(const uint8_t value, const uint8_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline uint16_t tal_write_bits_u16(const uint16_t value, const uint16_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline uint32_t tal_write_bits_u32(const uint32_t value, const uint32_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline uint64_t tal_write_bits_u64(const uint64_t value, const uint64_t dest, 
      const int32_t pos, const int32_t len, bool* const err);

  /**
   * @defgroup @b tal_read_bits
   * @brief Reads a value from a specific range of bits in another value.
   * @param dest (unsigned integer denoted by suffix) The value to read from.
   * @param pos (int32_t) The position of the range to read from (bits from lsb).
   * @param len (int32_t) The length of the range to read from (bits).
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or 
   *            @p [len] is negative, @p [pos] + @p [len] exceeds the bit-width 
   *            of the suffix type, or an internal error occurs.
   * @returns (unsigned integer denoted by suffix) The value of the range of 
   *          bits in @p [dest] specified by @p [pos] and @p [len], or 0 if an 
   *          error occurs.
   */
  inline uint8_t tal_read_bits_u8(const uint8_t dest, const int32_t pos, 
      const int32_t len, bool* const err);
  inline uint16_t tal_read_bits_u16(const uint16_t dest, const int32_t pos, 
      const int32_t len, bool* const err);
  inline uint32_t tal_read_bits_u32(const uint32_t dest, const int32_t pos, 
      const int32_t len, bool* const err);
  inline uint64_t tal_read_bits_u64(const uint64_t dest, const int32_t pos, 
      const int32_t len, bool* const err);

  /**
   * @defgroup @b tal_set_bits
   * @brief Sets all bits in a specific range to either 0 or 1.
   * @param value (bool) If true, all bits in the given range are set to 1.
   *              If false, all bits in the given range are set to 0.
   * @param dest (unsigned integer denoted by suffix) The value to modify.
   * @param pos (int32_t) The position of the range to modify (bits from lsb).
   * @param len (int32_t) The length of the range to modify (bits).
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or 
   *            @p [len] is negative, @p [pos] + @p [len] exceeds the bit-width 
   *            of the suffix type, or an internal error occurs.
   * @returns (unsigned integer denoted by suffix) The result of setting all
   *          bits in the range of @p [dest] specified by @p [pos] and @p [len] 
   *          to @p [value], or @p [dest] unaltered if an error occurs.
   */
  inline uint8_t tal_set_bits_u8(const bool value, const uint8_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline uint16_t tal_set_bits_u16(const bool value, const uint16_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline uint32_t tal_set_bits_u32(const bool value, const uint32_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline uint64_t tal_set_bits_u64(const bool value, const uint64_t dest, 
      const int32_t pos, const int32_t len, bool* const err);

  /**
   * @defgroup @b tal_get_bits
   * @brief Determines if all bits in a specific range are set to either 0 or 1.
   * @param value (bool) If true, all bits in the given range are compared to 1.
   *              If false, all bits in the given range are compared to 0.
   * @param dest (unsigned integer denoted by suffix) The value to query.
   * @param pos (int32_t) The position of the range to query (bits from lsb).
   * @param len (int32_t) The length of the range to query (bits).
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or 
   *            @p [len] is negative, @p [pos] + @p [len] exceeds the bit-width 
   *            of the suffix type, or an internal error occurs.
   * @returns (bool) True if no error occurs and all bits in the range of
   *          @p [dest] specified by @p [pos] and @p [len] are equal to 
   *          @p [value], or false otherwise.
   */
  inline bool tal_get_bits_u8(const bool value, const uint8_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline bool tal_get_bits_u16(const bool value, const uint16_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline bool tal_get_bits_u32(const bool value, const uint32_t dest, 
      const int32_t pos, const int32_t len, bool* const err);
  inline bool tal_get_bits_u64(const bool value, const uint64_t dest, 
      const int32_t pos, const int32_t len, bool* const err);


  /** @internal */

  /**************************************************************************************************
   * @section Implementation of Type Size Utilities
   **************************************************************************************************/

  #define tal_bit_size(type) \
      ((int32_t)sizeof(type) * CHAR_BIT)

  #define tal_byte_size(type) \
      ((int32_t)sizeof(type) * (CHAR_BIT / 8))

  /**************************************************************************************************
   * @section Implementation for Bit Querying Utilities
   **************************************************************************************************/

  bool tal_single_bit_u8(const uint8_t value) {
    return value && !(value & (value - 1u));
  }

  bool tal_single_bit_u16(const uint16_t value) {
    return value && !(value & (value - 1u));
  }

  bool tal_single_bit_u32(const uint32_t value) {
    return value && !(value & (value - 1u));
  }

  bool tal_single_bit_u64(const uint64_t value) {
    return value && !(value & (value - 1u));
  }

  int32_t tal_bit_width_u8(const uint8_t value) {
    return tal_bit_size(value) - tal_clz_u8(value);
  }

  int32_t tal_bit_width_u16(const uint16_t value) {
    return tal_bit_size(value) - tal_clz_u16(value);
  }

  int32_t tal_bit_width_u32(const uint32_t value) {
    return tal_bit_size(value) - tal_clz_u32(value);
  }

  int32_t tal_bit_width_u64(const uint64_t value) {
    return tal_bit_size(value) - tal_clz_u64(value);
  }

  #if defined(TAL_ARCH_ARMV7M)

    int32_t tal_clz_u8(const uint8_t value) {
      uint32_t result = 0u;
      asm (
        "clz %[result_], %[value_]" 
        : [result_] "=r" (result) 
        : [value_] "r" (value)
      );
      static const int32_t bit_diff = tal_bit_size(result) -
          tal_bit_size(value);
      return (int32_t)result - bit_diff;
    }

  #else

    int32_t tal_clz_u8(const uint8_t value) {
      static const int32_t value_bits = tal_bit_size(value);
      int32_t count = 0;
      for (int32_t i = 0; i < value_bits; ++i) {
        const uint8_t mask = (uint8_t)1 << ((value_bits - 1) - i);
        if ((value & mask) != 0u) { break; }
        ++count;
      }
      return count;
    }

  #endif

  #if defined(TAL_ARCH_ARMV7M)

    int32_t tal_clz_u16(const uint16_t value) {
      uint32_t result = 0u;
      asm (
        "clz %[result_], %[value_]" 
        : [result_] "=r" (result) 
        : [value_] "r" (value)
      );
      static const int32_t bit_diff = tal_bit_size(result) - 
          tal_bit_size(value);
      return (int32_t)result - bit_diff;
    }

  #else

    int32_t tal_clz_u16(const uint16_t value) {
      static const int32_t value_bits = tal_bit_size(value);
      int32_t count = 0;
      for (int32_t i = 0; i < value_bits; ++i) {
        const uint16_t mask = (uint16_t)1 << ((value_bits - 1) - i);
        if ((value & mask) != 0u) { break; }
        ++count;
      }
      return count;
    }

  #endif

  #if defined(TAL_ARCH_ARMV7M)

    int32_t tal_clz_u32(const uint32_t value) {
      uint32_t result = 0u;
      asm (
        "clz %[result_], %[value_]" 
        : [result_] "=r" (result) 
        : [value_] "r" (value)
      );
      return (int32_t)result;
    }

  #else

    int32_t tal_clz_u32(const uint32_t value) {
      static const int32_t value_bits = tal_bit_size(value);
      int32_t count = 0;
      for (int32_t i = 0; i < value_bits; ++i) {
        const uint32_t mask = (uint32_t)1 << ((value_bits - 1) - i);
        if ((value & mask) != 0u) { break; }
        ++count;
      }
      return count;
    }

  #endif

  #if defined(TAL_ARCH_ARMV7M)

    int32_t tal_clz_u64(const uint64_t value) {
      static const int32_t value_bits = tal_bit_size(value);
      const uint32_t h_value = (uint32_t)(value >> (value_bits / 2));
      uint32_t h_result = 0u;
      asm (
        "clz %[h_result_], %[h_value_]"
        : [h_result_] "=r" (h_result) 
        : [h_value_] "r" (h_value)
      );
      if (h_result == tal_bit_size(h_value)) {
        const uint32_t l_value = (uint32_t)value;
        uint32_t l_result = 0u;
        asm (
          "clz %[l_result_], %[l_value_]" 
          : [l_result_] "=r" (l_result) 
          : [l_value_] "r" (l_value)
        );
        return (int32_t)(h_result + l_result);
      } else {
        return (int32_t)h_result;
      }
    }

  #else

    int32_t tal_clz_u64(const uint64_t value) {
      static const int32_t value_bits = tal_bit_size(value);
      int32_t count = 0;
      for (int32_t i = 0; i < 64; ++i) {
        const uint64_t mask = (uint64_t)1 << ((value_bits - 1) - i);
        if ((value & mask) != 0u) { break; }
        ++count;
      }
      return count;
    }

  #endif

  int32_t tal_clo_u8(const uint8_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint8_t mask = (uint8_t)1 << ((value_bits - 1) - i);
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_clo_u16(const uint16_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint16_t mask = (uint16_t)1 << ((value_bits - 1) - i);
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_clo_u32(const uint32_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint32_t mask = (uint32_t)1 << ((value_bits - 1) - i);
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_clo_u64(const uint64_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint64_t mask = (uint64_t)1 << ((value_bits - 1) - i);
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_ctz_u8(const uint8_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i= 0; i < value_bits; ++i) {
      const uint8_t mask = (uint8_t)1 << i;
      if ((value & mask) != 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_ctz_u16(const uint16_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i= 0; i < value_bits; ++i) {
      const uint16_t mask = (uint16_t)1 << i;
      if ((value & mask) != 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_ctz_u32(const uint32_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i= 0; i < value_bits; ++i) {
      const uint32_t mask = (uint32_t)1 << i;
      if ((value & mask) != 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_ctz_u64(const uint64_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i= 0; i < value_bits; ++i) {
      const uint64_t mask = (uint64_t)1 << i;
      if ((value & mask) != 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_cto_u8(const uint8_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint8_t mask = (uint8_t)1 << i;
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_cto_u16(const uint16_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint16_t mask = (uint16_t)1 << i;
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_cto_u32(const uint32_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint32_t mask = (uint32_t)1 << i;
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_cto_u64(const uint64_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint64_t mask = (uint64_t)1 << i;
      if ((value & mask) == 0u) { break; }
      ++count;
    }
    return count;
  }

  int32_t tal_popcount_u8(const uint8_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint8_t mask = (uint8_t)1 << i;
      if ((value & mask) != 0u) { ++count; }
    }
    return count;
  }

  int32_t tal_popcount_u16(const uint16_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint16_t mask = (uint16_t)1 << i;
      if ((value & mask) != 0u) { ++count; }
    }
    return count;
  }

  int32_t tal_popcount_u32(const uint32_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint32_t mask = (uint32_t)1 << i;
      if ((value & mask) != 0u) { ++count; }
    }
    return count;
  }

  int32_t tal_popcount_u64(const uint64_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint64_t mask = (uint64_t)1 << i;
      if ((value & mask) != 0u) { ++count; }
    }
    return count;
  }

  /**************************************************************************************************
   * @section Implementation for Bit Manipulation Utilities
   **************************************************************************************************/

  // A bit-mask which denotes a single byte (0 offset).
  static const uint64_t byte_mask__ = (((uint64_t)1 << 8) - 1u);

  uint8_t tal_rbit_u8(const uint8_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    uint8_t result = 0u;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint8_t mask = (value >> i) & 1u;
      result |= mask << ((value_bits - 1) - i);
    }
    return result;
  }

  uint16_t tal_rbit_u16(const uint16_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    uint16_t result = 0u;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint16_t mask = (value >> i) & 1u;
      result |= mask << ((value_bits - 1) - i);
    }
    return result;
  }

  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_rbit_u32(const uint32_t value) {
      uint32_t result = 0u;
      asm (
        "rbit %[result_], %[value_]"
        : [result_] "=r" (result)
        : [value_] "r" (value)
      );
      return result;      
    }

  #else

    uint32_t tal_rbit_u32(const uint32_t value) {
      static const int32_t value_bits = tal_bit_size(value);
      uint32_t result = 0;
      for (int32_t i = 0; i < value_bits; ++i) {
        const uint32_t mask = (value >> i) & 1u;
        result |= mask << ((value_bits - 1) - i);
      }
      return result;
    }

  #endif

  uint64_t tal_rbit_u64(const uint64_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    uint64_t result = 0u;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint64_t mask = (value >> i) & 1u;
      result |= mask << ((value_bits - 1) - i);
    }
    return result;
  }

  #if defined(TAL_ARCH_ARMV7M)

    uint16_t tal_rbyte_u16(const uint16_t value) {
      uint32_t result = 0u;
      asm (
        "rev16 %[result_], %[value_]"
        : [result_] "=r" (result)
        : [value_] "r" (value)
      );
      return (uint16_t)result;
    }

  #else

    uint16_t tal_rbyte_u16(const uint16_t value) {
      static const int32_t value_bytes = tal_byte_size(value);
      uint16_t result = 0u;
      for (int32_t i = 0; i < value_bytes; ++i) {
        const uint16_t mask = (value >> (i * 8)) & byte_mask__;
        result |= mask << (((value_bytes - 1) - i) * 8);
      }
      return result;
    }

  #endif

  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_rbyte_u32(const uint32_t value) {
      uint32_t result = 0u;
      asm (
        "rev %[result_], %[value_]"
        : [result_] "=r" (result)
        : [value_] "r" (value)
      );
      return result;
    }

  #else

    uint32_t tal_rbyte_u32(const uint32_t value) {
      static const int32_t value_bytes = tal_byte_size(value);
      uint32_t result = 0u;
      for (int32_t i = 0; i < value_bytes; ++i) {
        const uint32_t mask = (value >> (i * 8)) & byte_mask__;
        result |= mask << (((value_bytes - 1) - i) * 8);
      }
      return result;      
    }

  #endif

  uint64_t tal_rbyte_u64(const uint64_t value) {
    static const int32_t value_bytes = tal_byte_size(value);
    uint64_t result = 0u;
    for (int32_t i = 0; i < value_bytes; ++i) {
      const uint64_t mask = (value >> (i * 8)) & byte_mask__;
      result |= mask << (((value_bytes - 1) - i) * 8);
    }
    return result;
  }

  uint8_t tal_bit_ceil_u8(const uint8_t value) {
    if (value <= 1u) { return 1; }
    return (uint8_t)1 << tal_bit_width_u8(value - 1u);
  }

  uint16_t tal_bit_ceil_u16(const uint16_t value) {
    if (value <= 1u) { return 1; }
    return (uint16_t)1 << tal_bit_width_u16(value - 1u);
  }

  uint32_t tal_bit_ceil_u32(const uint32_t value) {
    if (value <= 1u) { return 1; }
    return (uint32_t)1 << tal_bit_width_u32(value - 1u);
  }

  uint64_t tal_bit_ceil_u64(const uint64_t value) {
    if (value <= 1u) { return 1; }
    return (uint64_t)1 << tal_bit_width_u64(value - 1u);
  }

  uint8_t tal_bit_floor_u8(const uint8_t value) {
    if (value <= 0u) { return 0; }
    return (uint8_t)1 << (tal_bit_width_u8(value - 1u) - 1);
  }

  uint16_t tal_bit_floor_u16(const uint16_t value) {
    if (value <= 0u) { return 0; }
    return (uint16_t)1 << (tal_bit_width_u16(value - 1u) - 1);
  }

  uint32_t tal_bit_floor_u32(const uint32_t value) {
    if (value <= 0u) { return 0; }
    return (uint32_t)1 << (tal_bit_width_u32(value - 1u) - 1);
  }

  uint64_t tal_bit_floor_u64(const uint64_t value) {
    if (value <= 0u) { return 0; }
    return (uint64_t)1 << (tal_bit_width_u64(value - 1u) - 1);
  }

  uint8_t tal_rotl_u8(const uint8_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t rshift = value_bits - diff;
      return (value << diff) | (value >> rshift);
    } else if (diff < 0) {
      return tal_rotr_u8(value, -shift);
    } else {
      return value;
    }
  }

  uint16_t tal_rotl_u16(const uint16_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t rshift = value_bits - diff;
      return (value << diff) | (value >> rshift);
    } else if (diff < 0) {
      return tal_rotr_u16(value, -shift);
    } else {
      return value;
    }
  }

  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_rotl_u32(const uint32_t value, const int32_t shift) {
      static const int32_t value_bits = tal_bit_size(value);
      const int32_t diff = shift % value_bits;
      if (diff > 0) {
        const int32_t ror_shift = value_bits - diff;
        uint32_t result = 0u;
        asm (
          "ror %[result_], %[value_], %[ror_shift_]"
          : [result_] "=r" (result)
          : [value_] "r" (value), [ror_shift_] "rm" (ror_shift)
        );
        return result;
      } else if (diff < 0) {
        return tal_rotr_u32(value, -shift);
      } else {
        return value;
      }
    }

  #else

    uint32_t tal_rotl_u32(const uint32_t value, const int32_t shift) {
      static const int32_t value_bits = tal_bit_size(value);
      const int32_t diff = shift % value_bits;
      if (diff > 0) {
        const int32_t rshift = value_bits - diff;
        return (value << diff) | (value >> rshift);
      } else if (diff < 0) {
        return tal_rotr_u32(value, -shift);
      } else {
        return value;
      }
    }

  #endif

  uint64_t tal_rotl_u64(const uint64_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t rshift = value_bits - diff;
      return (value << diff) | (value >> rshift);
    } else if (diff < 0) {
      return tal_rotr_u64(value, -shift);
    } else {
      return value;
    }
  }

  uint8_t tal_rotr_u8(const uint8_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t lshift = value_bits - diff;
      return (value >> diff) | (value << lshift);
    } else if (diff < 0) {
      return tal_rotl_u8(value, -shift);
    } else {
      return value;
    }
  }

  uint16_t tal_rotr_u16(const uint16_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t lshift = value_bits - diff;
      return (value >> diff) | (value << lshift);
    } else if (diff < 0) {
      return tal_rotl_u16(value, -shift);
    } else {
      return value;
    }
  }

  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_rotr_u32(const uint32_t value, const int32_t shift) {
      static const int32_t value_bits = tal_bit_size(value);
      const int32_t diff = shift % value_bits;
      if (diff > 0) {
        uint32_t result = 0u;
        asm (
          "ror %[result_], %[value_], %[diff_]"
          : [result_] "=r" (result)
          : [value_] "r" (value), [diff_] "r" (diff)
        );
        return result;
      } else if (diff < 0) {
        return tal_rotl_u32(value, -shift);
      } else {
        return value;
      }
    }

  #else

    uint32_t tal_rotr_u32(const uint32_t value, const int32_t shift) {
      static const int32_t value_bits = tal_bit_size(value);
      const int32_t diff = shift % value_bits;
      if (diff > 0) {
        const int32_t lshift = value_bits - diff;
        return (value >> diff) | (value << lshift);
      } else if (diff < 0) {
        return tal_rotl_u32(value, -shift);
      } else {
        return value;
      }      
    }

  #endif

  uint64_t tal_rotr_u64(const uint64_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t lshift = value_bits - diff;
      return (value >> diff) | (value << lshift);
    } else if (diff < 0) {
      return tal_rotl_u64(value, -shift);
    } else {
      return value;
    }
  }

  /**************************************************************************************************
   * @section Implementation for Bitmask Utilities
   **************************************************************************************************/

  // Returns true if the given pos/len defines a mask within the bounds of a type
  // with the given bit-size.
  static bool valid_mask__(const int32_t bit_size, const int32_t pos,
      const int32_t len) {
    return (pos >= 0) && (len >= 0) && ((pos + len) < bit_size);
  } 

  uint8_t tal_mask_u8(const int32_t pos, const int32_t len, bool* const err) {
    if (!valid_mask__(tal_bit_size(uint8_t), pos, len)) {
      *err = true;
      return 0u;
    }
    if (len == 0) { return 0u; }
    return (((uint8_t)1 << len) - 1u) << pos;
  }

  uint16_t tal_mask_u16(const int32_t pos, const int32_t len, bool* const err) {
    if (!valid_mask__(tal_bit_size(uint16_t), pos, len)) {
      *err = true;
      return 0u;
    }
    if (len == 0) { return 0u; }
    return (((uint16_t)1 << len) - 1u) << pos;
  }

  uint32_t tal_mask_u32(const int32_t pos, const int32_t len, bool* const err) {
    if (!valid_mask__(tal_bit_size(uint32_t), pos, len)) {
      *err = true;
      return 0u;
    }
    if (len == 0) { return 0u; }
    return (((uint32_t)1 << len) - 1u) << pos;
  }

  uint64_t tal_mask_u64(const int32_t pos, const int32_t len, bool* const err) {
    if (!valid_mask__(tal_bit_size(uint64_t), pos, len)) {
      *err = true;
      return 0u;
    }
    if (len == 0) { return 0u; }
    return (((uint64_t)1 << len) - 1u) << pos;
  }

  #if defined(TAL_ARCH_ARMV7M)

    uint8_t tal_write_bits_u8(const uint8_t value, const uint8_t dest, 
        const int32_t pos, const int32_t len, bool* const err) {
      if (!valid_mask__(tal_bit_size(uint8_t), pos, len) ||
          tal_bit_width_u8(value) > len) {
        *err = true;
        return false;
      }
      uint32_t result = 0u;
      asm (
        "bfi %[result_], %[value_], %[pos_], %[len_]"
        : [result_] "=r" (result)
        : [value_] "r" (value), [pos_] "rm" (pos), [len_] "rm" (len)
      );
      return (uint8_t)result;
    }

  #else

    uint8_t tal_write_bits_u8(const uint8_t value, const uint8_t dest, 
        const int32_t pos, const int32_t len, bool* const err) {
      bool *mask_err = false;
      const uint8_t mask = tal_mask_u8(pos, len, &mask_err);
      if (mask_err || tal_bit_width_u8(value) > len) {
        *err = true;
        return value;
      }
      return (dest & ~mask) | (value << pos);
    }

  #endif

  #if defined(TAL_ARCH_ARMV7M)

    uint16_t tal_write_bits_u16(const uint16_t value, const uint16_t dest, 
        const int32_t pos, const int32_t len, bool* const err) {
      if (!valid_mask__(tal_bit_size(uint16_t), pos, len) ||
          tal_bit_width_u16(value) > len) {
        *err = true;
        return value;
      }
      uint32_t result = 0u;
      asm (
        "bfi %[result_], %[value_], %[pos_], %[len_]"
        : [result_] "=r" (result)
        : [value_] "r" (value), [pos_] "rm" (pos), [len_] "rm" (len)
      );
      return (uint16_t)result;
    }    

  #else

    uint16_t tal_write_bits_u16(const uint16_t value, const uint16_t dest, 
        const int32_t pos, const int32_t len, bool* const err) {
      bool mask_err = false;
      const uint16_t mask = tal_mask_u16(pos, len, &mask_err);
      if (mask_err || tal_bit_width_u16(value) > len) {
        *err = true;
        return value;
      }
      return (dest & ~mask) | (value << pos);
    }

  #endif

  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_write_bits_u32(const uint32_t value, const uint32_t dest, 
        const int32_t pos, const int32_t len, bool* const err) {
      if (!valid_mask__(tal_bit_size(uint32_t), pos, len) ||
          tal_bit_width_u32(value) > len) {
        *err = true;
        return value;
      }
      uint32_t result = 0u;
      asm (
        "bfi %[result_], %[value_], %[pos_], %[len_]"
        : [result_] "=r" (result)
        : [value_] "r" (value), [pos_] "rm" (pos), [len_] "rm" (len)
      );
      return result;
    }

  #else

    uint32_t tal_write_bits_u32(const uint32_t value, const uint32_t dest, 
        const int32_t pos, const int32_t len, bool* const err) {
      bool mask_err = false;
      const uint32_t mask = tal_mask_u32(pos, len, &mask_err);
      if (mask_err || tal_bit_width_u32(value) > len) {
        *err = true;
        return value;
      }
      return (dest & ~mask) | (value << pos);
    }

  #endif

  uint64_t tal_write_bits_u64(const uint64_t value, const uint64_t dest, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint64_t mask = tal_mask_u64(pos, len, &mask_err);
    if (mask_err || tal_bit_width_u64(value) > len) {
      *err = true;
      return value;
    }
    return (dest & ~mask) | (value << pos);
  }

  #if defined(TAL_ARCH_ARMV7M)

    uint8_t tal_read_bits_u8(const uint8_t src, const int32_t pos, 
        const int32_t len, bool* const err) {
      if (!valid_mask__(tal_bit_size(uint8_t), pos, len)) {
        *err = true;
        return 0u;
      }
      uint32_t result = 0u;
      asm (
        "ubfx %[result_], %[src_], %[pos_], %[len_]"
        : [result_] "=r" (result)
        : [src_] "r" (src), [pos_] "rm" (pos), [len_] "rm" (len)
      );
      return (uint8_t)result;
    }

  #else

    uint8_t tal_read_bits_u8(const uint8_t src, const int32_t pos, 
        const int32_t len, bool* const err) {
      bool mask_err = false;
      const uint8_t mask = tal_mask_u8(pos, len, &mask_err);
      if (mask_err) {
        *err = true;
        return 0u;
      }
      return (src & mask) >> pos;
    }

  #endif


  #if defined(TAL_ARCH_ARMV7M)

    uint16_t tal_read_bits_u16(const uint16_t src, const int32_t pos, 
        const int32_t len, bool* const err) {
      if (!valid_mask__(tal_bit_size(uint16_t), pos, len)) {
        *err = true;
        return 0u;
      }
      uint32_t result = 0u;
      asm (
        "ubfx %[result_], %[src_], %[pos_], %[len_]"
        : [result_] "=r" (result)
        : [src_] "r" (src), [pos_] "rm" (pos), [len_] "rm" (len)
      );
      return (uint16_t)result;
    }

  #else

    uint16_t tal_read_bits_u16(const uint16_t src, const int32_t pos, 
        const int32_t len, bool* const err) {
      bool mask_err = false;
      const uint16_t mask = tal_mask_u16(pos, len, &mask_err);
      if (mask_err) {
        *err = true;
        return 0u;
      }
      return (src & mask) >> pos;
    }

  #endif


  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_read_bits_u32(const uint32_t src, const int32_t pos, 
        const int32_t len, bool* const err) {
      if (!valid_mask__(tal_bit_size(uint32_t), pos, len)) {
        *err = true;
        return false;
      }
      uint32_t result = 0u;
      asm (
        "ubfx %[result_], %[src_], %[pos_], %[len_]"
        : [result_] "=r" (result)
        : [src_] "r" (src), [pos_] "rm" (pos), [len_] "rm" (len)
      );
      return result;
    }

  #else

    uint32_t tal_read_bits_u32(const uint32_t src, const int32_t pos, 
        const int32_t len, bool* const err) {
      bool mask_err = false;
      const uint32_t mask = tal_mask_u32(pos, len, &mask_err);
      if (mask_err) {
        *err = true;
        return 0u;
      }
      return (src & mask) >> pos;
    }

  #endif

  uint64_t tal_read_bits_u64(const uint64_t src, const int32_t pos, 
      const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint64_t mask = tal_mask_u64(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return 0u;
    }
    return (src & mask) >> pos;
  }

  uint8_t tal_set_bits_u8(const bool value, const uint8_t dest, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint8_t mask = tal_mask_u8(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return dest;
    }
    if (value) {
      return dest | mask;
    } else {
      return dest & ~mask;
    }
  }

  uint16_t tal_set_bits_u16(const bool value, const uint16_t dest, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint16_t mask = tal_mask_u16(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return dest;
    }
    if (value) {
      return dest | mask;
    } else {
      return dest & ~mask;
    }
  }

  uint32_t tal_set_bits_u32(const bool value, const uint32_t dest, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint32_t mask = tal_mask_u32(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return dest;
    }
    if (value) {
      return dest | mask;
    } else {
      return dest & ~mask;
    }
  }

  uint64_t tal_set_bits_u64(const bool value, const uint64_t dest, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint64_t mask = tal_mask_u64(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return dest;
    }
    if (value) {
      return dest | mask;
    } else {
      return dest & ~mask;
    }
  }

  bool tal_get_bits_u8(const bool value, const uint8_t src, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint8_t mask = tal_mask_u8(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return false;
    }
    if (value) {
      return (src & mask) == mask;
    } else {
      return (src & mask) == 0u;
    }
  }

  bool tal_get_bits_u16(const bool value, const uint16_t src, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint16_t mask = tal_mask_u16(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return false;
    }
    if (value) {
      return (src & mask) == mask;
    } else {
      return (src & mask) == 0u;
    }
  }

  bool tal_get_bits_u32(const bool value, const uint32_t src, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint32_t mask = tal_mask_u32(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return false;
    }
    if (value) {
      return (src & mask) == mask;
    } else {
      return (src & mask) == 0u;
    }
  }

  bool tal_get_bits_u64(const bool value, const uint64_t src, 
      const int32_t pos, const int32_t len, bool* const err) {
    bool mask_err = false;
    const uint64_t mask = tal_mask_u64(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return false;
    }
    if (value) {
      return (src & mask) == mask;
    } else {
      return (src & mask) == 0u;
    }
  }


  /** @endinternal */

#if defined(__cplusplus)
  }
#endif