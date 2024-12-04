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
 * @brief Bit querying/manipulation utilities.
 * @note API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Bit-Size Utilities
   **************************************************************************************************/

  /**
   * @def @b tal_bit_size(type)
   * @brief Evaluates to the size of @p [type] in bits.
   * @param type (typename or variable) The type to query.
   */

  /**
   * @def @b tal_byte_size(type)
   * @brief Evaluates to the size of @p [type] in bytes.
   * @param type (typename or variable) The type to query.
   * @note - Prefer to sizeof when size in bytes specifically is needed.
   */

  /**************************************************************************************************
   * @section Bit Inspection Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_single_bit
   * @brief Determines if a value has only one set bit (is a power of two).
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (bool) True if @p [value] has only one set bit (is a power of two),
   *          or false otherwise.
   * @{
   */
  bool tal_single_bit_u8(uint8_t value);
  bool tal_single_bit_u16(uint16_t value);
  bool tal_single_bit_u32(uint32_t value);
  bool tal_single_bit_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_bit_width
   * @brief Determines the number of bits needed to represent a value.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The minimum number of bits needed to represent @p [value].
   * @note - If the given value is equal to 0, this function returns 0.
   * @{
   */
  int32_t tal_bit_width_u8(uint8_t value);
  int32_t tal_bit_width_u16(uint16_t value);
  int32_t tal_bit_width_u32(uint32_t value);
  int32_t tal_bit_width_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_clz
   * @brief Determines the number of leading zero bits in a value.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of consecutive cleared (0) bits in @p [value]
   *          starting from the most significant ("leading") bit.
   * @{
   */
  int32_t tal_clz_u8(uint8_t value);
  int32_t tal_clz_u16(uint16_t value);
  int32_t tal_clz_u32(uint32_t value);
  int32_t tal_clz_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_clo
   * @brief Counts the number of leading one bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of consecutive set (1) bits in @p [value]
   *          starting from the most significant ("leading") bit.
   * @{
   */
  int32_t tal_clo_u8(uint8_t value);
  int32_t tal_clo_u16(uint16_t value);
  int32_t tal_clo_u32(uint32_t value);
  int32_t tal_clo_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_ctz
   * @brief Counts the number of trailing zero bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of consecutive cleared (0) bits in @p [value]
   *          starting from the least significant ("trailing") bit.
   * @{
   */
  int32_t tal_ctz_u8(uint8_t value);
  int32_t tal_ctz_u16(uint16_t value);
  int32_t tal_ctz_u32(uint32_t value);
  int32_t tal_ctz_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_cto
   * @brief Counts the number of trailing one bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of consecutive set (1) bits in @p [value]
   *          starting from the least significant ("trailing") bit.
   * @{
   */
  int32_t tal_cto_u8(uint8_t value);
  int32_t tal_cto_u16(uint16_t value);
  int32_t tal_cto_u32(uint32_t value);
  int32_t tal_cto_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_popcount
   * @brief Counts the number of set bits in an integer.
   * @param value (unsigned integer denoted by suffix) The value to query.
   * @returns (int32_t) The number of set (1) bits in @p [value].
   * @{
   */
  int32_t tal_popcount_u8(uint8_t value);
  int32_t tal_popcount_u16(uint16_t value);
  int32_t tal_popcount_u32(uint32_t value);
  int32_t tal_popcount_u64(uint64_t value);
  /** @} */

  /**************************************************************************************************
   * @section Bit Manipulation Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_rbit
   * @brief Reverses the order of a value's bits.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) @p [value] with the order of
   *          it's bits reversed.
   * @{
   */
  uint8_t tal_rbit_u8(uint8_t value);
  uint16_t tal_rbit_u16(uint16_t value);
  uint32_t tal_rbit_u32(uint32_t value);
  uint64_t tal_rbit_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_rbyte
   * @brief Reverses the order of a value's bytes.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) @p [value] with the order of
   *          it's bytes reversed.
   * @{
   */
  uint16_t tal_rbyte_u16(uint16_t value);
  uint32_t tal_rbyte_u32(uint32_t value);
  uint64_t tal_rbyte_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_bit_ceil
   * @brief Rounds a value up to the nearest power of two.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The smallest power 
   *          of two which is greater than or equal to @p [value].
   * @note - If an integer is power of two, it has only one set bit.
   * @{
   */
  uint8_t tal_bit_ceil_u8(uint8_t value);
  uint16_t tal_bit_ceil_u16(uint16_t value);
  uint32_t tal_bit_ceil_u32(uint32_t value);
  uint64_t tal_bit_ceil_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_bit_floor
   * @brief Rounds a value down to the nearest power of two.
   * @param value (unsigned integer denoted by suffix) The value to modify.
   * @returns (unsigned integer denoted by suffix) The greatest power 
   *          of two which is less than or equal to the given @p [value].
   * @note - If an integer is power of two, it has only one set bit.
   * @{
   */
  uint8_t tal_bit_floor_u8(uint8_t value);
  uint16_t tal_bit_floor_u16(uint16_t value);
  uint32_t tal_bit_floor_u32(uint32_t value);
  uint64_t tal_bit_floor_u64(uint64_t value);
  /** @} */

  /**
   * @defgroup @b tal_rotl
   * @brief Performs a circular bit-shift on an integer value.
   * @param value (unsigned integer denoted by suffix) The value to rotate.
   * @param shift (int32_t) The number of bits to rotate by (positive denotes
   *        a right rotation, negative denotes a left rotation).
   * @returns (unsigned integer denoted by suffix) The result of circularly 
   *          rotating the given value to the right by @p [shift] bits if it
   *          is positive or left by @p [shift] bits if it is negative.
   * @note - This function performs a "circular shift", meaining that bits
   *       shifted beyond the end of the integer's range wrap around to
   *       the beginning.
   * @{
   */
  uint8_t tal_bit_rot_u8(uint8_t value, int32_t shift);
  uint16_t tal_bit_rot_u16(uint16_t value, int32_t shift);
  uint32_t tal_bit_rot_u32(uint32_t value, int32_t shift);
  uint64_t tal_bit_rot_u64(uint64_t value, int32_t shift);
  /** @} */

  /**************************************************************************************************
   * @section Bitmask Utilities
   **************************************************************************************************/

  /**
   * @defgroup @b tal_mask
   * @brief Creates a mask of contiguous set bits at specific location.
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or
   *        @p [len] is negative, or @p [pos] + @p [len] exceeds the bit-width 
   *        of the suffix type.
   * @param pos (int32_t) The number of bits between the LSB and the first set bit.
   * @param len (int32_t) The number of contiguous set bits.
   * @returns (unsigned integer denoted by suffix) A mask with @p [len] 
   *          contiguous set bits starting @p [pos] bits from the LSB, or 0 if 
   *          an error occured.
   * @{
   */
  uint8_t tal_mask_u8(bool* err, int32_t pos, int32_t len);
  uint16_t tal_mask_u16(bool* err, int32_t pos, int32_t len);
  uint32_t tal_mask_u32(bool* err, int32_t pos, int32_t len);
  uint64_t tal_mask_u64(bool* err, int32_t pos, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_write_bits
   * @brief Writes a value to a specific range of bits in another value.
   * @param value (unsigned integer denoted by suffix) The value to write to.
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or 
   *        @p [len] is negative, @p [pos] + @p [len] exceeds the bit-width 
   *        of the suffix type, or the bit-width of @p [value] exceeds @p [len].
   * @param dest (unsigned integer denoted by suffix) The value to write to.
   * @param pos (int32_t) The position of the range to write to (bits from lsb).
   * @param len (int32_t) The length of the range to write to (bits).
   * @returns (unsigned integer denoted by suffix) The result of writing 
   *          @p [value] to the range of bits in @p [dest] specified by @p [pos] 
   *          and @p [len] or @p [dest] unaltered if an error occured.
   * @{
   */
  uint8_t tal_write_bits_u8(bool* err, uint8_t value, uint8_t dest, int32_t pos, int32_t len);
  uint16_t tal_write_bits_u16(bool* err, uint16_t value, uint16_t dest, int32_t pos, int32_t len);
  uint32_t tal_write_bits_u32(bool* err, uint32_t value, uint32_t dest, int32_t pos, int32_t len);
  uint64_t tal_write_bits_u64(bool* err, uint64_t value, uint64_t dest, int32_t pos, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_read_bits
   * @brief Reads a value from a specific range of bits in another value.
   * @param src (unsigned integer denoted by suffix) The value to read from.
   * @param pos (int32_t) The position of the range to read from (bits from lsb).
   * @param len (int32_t) The length of the range to read from (bits).
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or 
   *        @p [len] is negative, or @p [pos] + @p [len] exceeds the bit-width 
   *        of the suffix type.
   * @returns (unsigned integer denoted by suffix) The value of the range of 
   *          bits in @p [src] specified by @p [pos] and @p [len], or 0 if an 
   *          error occured.
   * @{
   */
  uint8_t tal_read_bits_u8(bool* err, uint8_t src, int32_t pos, int32_t len);
  uint16_t tal_read_bits_u16(bool* err, uint16_t src, int32_t pos, int32_t len);
  uint32_t tal_read_bits_u32(bool* err, uint32_t src, int32_t pos, int32_t len);
  uint64_t tal_read_bits_u64(bool* err, uint64_t src, int32_t pos, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_set_bits
   * @brief Sets all bits in a specific range to either 0 or 1.
   * @param value (bool) If true, all bits in the given range are set to 1.
   *        If false, all bits in the given range are set to 0.
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or 
   *        @p [len] is negative, or @p [pos] + @p [len] exceeds the bit-width 
   *        of the suffix type.
   * @param dest (unsigned integer denoted by suffix) The value to modify.
   * @param pos (int32_t) The position of the range to modify (bits from lsb).
   * @param len (int32_t) The length of the range to modify (bits).
   * @returns (unsigned integer denoted by suffix) The result of setting all
   *          bits in the range of @p [dest] specified by @p [pos] and @p [len] 
   *          to @p [value], or @p [dest] unaltered if an error occured.
   * @{
   */
  uint8_t tal_set_bits_u8(bool* err, bool value, uint8_t dest, int32_t pos, int32_t len);
  uint16_t tal_set_bits_u16(bool* err, bool value, uint16_t dest, int32_t pos, int32_t len);
  uint32_t tal_set_bits_u32(bool* err, bool value, uint32_t dest, int32_t pos, int32_t len);
  uint64_t tal_set_bits_u64(bool* err, bool value, uint64_t dest, int32_t pos, int32_t len);
  /** @} */

  /**
   * @defgroup @b tal_get_bits
   * @brief Determines if all bits in a specific range are set or cleared.
   * @param err (bool*) Error flag. Accessed and set true if @p [pos] or
   *        @p [len] is negative, or @p [pos] + @p [len] exceeds the bit-width 
   *        of the suffix type.
   * @param src (unsigned integer denoted by suffix) The value to query.
   * @param pos (int32_t) The position of the range to query (bits from lsb).
   * @param len (int32_t) The length of the range to query (bits).
   * @returns (int32_t) If no error occured and all bits in the range of @p [src]
   *          specified by @p [pos] and @p [len] are set the function returns 1.
   *          If no error occured and all bits in the range are cleared the 
   *          function returns -1. Otherwise the function returns 0.
   * @{
   */
  int32_t tal_get_bits_u8(bool* err, uint8_t src, int32_t pos, int32_t len);
  int32_t tal_get_bits_u16(bool* err, uint16_t src, int32_t pos, int32_t len);
  int32_t tal_get_bits_u32(bool* err, uint32_t src, int32_t pos, int32_t len);
  int32_t tal_get_bits_u64(bool* err, uint64_t src, int32_t pos, int32_t len);
  /** @} */

#if defined(__cplusplus)
  } // extern "C"
#endif

// Macro implementations
#include "src/lib/bit/bit_size.h"