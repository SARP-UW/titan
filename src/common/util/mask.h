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
 * @file common/util/mask.h 
 * @authors Aaron McBride
 * @brief Bitmask utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "common/util/attribute.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Bitmask Utilities
   **************************************************************************************************/

  /**
   * @brief Generates a bitmask of a specific length at a specific location.
   * @param pos (int32_t) The location of the first bit in the mask (from lsb).
   * @param len (int32_t) The number of contiguous set bits in the mask.
   * @returns (uint64_t) A bitmask with 'len' set bits, 'pos' bits from the lsb.
   */
  ti_fn_attr_inline inline uint64_t ti_get_mask(const int32_t pos, const int32_t len);

  /**
   * @brief Determines if a mask is valid for a specific memory location type.
   * @param type (typename) Unsigned integer typename that denotes alignment 
   *             of memory location.
   * @param pos (int32_t) The offset of the mask from the lsb of the memory 
   *            location (in bits).
   * @param len (int32_t) The length of the mask (in bits).
   * @returns (bool) True if a mask of 'len' bits, 'pos' bits from the lsb of
   *          a pointer to 'type' is valid, or false otherwise.
   */
  #define ti_valid_mask(type, pos, len) \
    _Generic(((type){0}) \
      uint8_t: ti_valid_mask8, \
      uint16_t: ti_valid_mask16, \
      uint32_t: ti_valid_mask32, \
      uint64_t: ti_valid_mask64 \
      default: false \
    )

  ti_fn_attr_inline inline bool ti_valid_mask8(
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_valid_mask16(
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_valid_mask32(
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_valid_mask64(
      const int32_t pos, const int32_t len);

  /**
   * @brief Writes a value to a bit-specific location in memory.
   * @param value (unsigned integer with same type as 'loc') The value to write.
   * @param loc (pointer to unsigned integer of any size/volatility) The 
   *            location in memory to write to.
   * @param pos (int32_t) The offset (bits from lsb) of the location to write to.
   * @param len (int32_t) The length (in bits) of the location to write to.
   * @note - The size of 'loc' determines the alignment of this operation.
   * @note - The volatility of 'loc' determines if this operation is volatile.
   */
  #define ti_write_mask(value, loc, pos, len) \
    _Generic((loc), \
      uint8_t*: ti_write_mask8, \
      uint16_t*: ti_write_mask16, \
      uint32_t*: ti_write_mask32, \
      uint64_t*: ti_write_mask64, \
      volatile uint8_t*: ti_write_mask8v, \
      volatile uint16_t*: ti_write_mask16v, \
      volatile uint32_t*: ti_write_mask32v, \
      volatile uint64_t*: ti_write_mask64v \
    )(value, loc, pos, len)

  ti_fn_attr_inline inline void ti_write_mask8(const uint8_t value, 
      uint8_t* loc, const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_write_mask16(const uint16_t value, 
      uint16_t* loc, const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_write_mask32(const uint32_t value, 
      uint32_t* loc, const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_write_mask64(const uint64_t value, 
      uint64_t* loc, const int32_t pos, const int32_t len);

  ti_fn_attr_inline inline void ti_write_mask8v(const uint8_t value, 
      volatile uint8_t* loc, const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_write_mask16v(const uint16_t value, 
      volatile uint16_t* loc, const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_write_mask32v(const uint32_t value, 
      volatile uint32_t* loc, const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_write_mask64v(const uint64_t value, 
      volatile uint64_t* loc, const int32_t pos, const int32_t len);

  /**
   * @brief Reads the value at a bit-specific location in memory.
   * @param loc (pointer to unsigned integer of any size/constness/volatility) 
   *            The location in memory to read from.
   * @param pos (int32_t) The offset (bits from lsb) of the location to read from.
   * @param len (int32_t) The length (in bits) of the location to read from.
   * @returns (same type as 'loc' without pointer) The value stored in 'len' 
   *          bits, 'pos' bits from the lsb at the given location.
   * @note - The size of 'loc' determines the alignment of this read operation.
   * @note - The volatility of 'loc' determines if this operation is volatile.
   */
  #define ti_read_mask(loc, pos, len) \
    _Generic((loc), \
      uint8_t*: ti_read_mask8, \
      uint16_t*: ti_read_mask16, \
      uint32_t*: ti_read_mask32, \
      uint64_t*: ti_read_mask64, \
      const uint8_t*: ti_read_mask8, \
      const uint16_t*: ti_read_mask16, \
      const uint32_t*: ti_read_mask32, \
      const uint64_t*: ti_read_mask64, \
      volatile uint8_t*: ti_read_mask8v, \
      volatile uint16_t*: ti_read_mask16v, \
      volatile uint32_t*: ti_read_mask32v, \
      volatile uint64_t*: ti_read_mask64v, \
      const volatile uint8_t*: ti_read_mask8v, \
      const volatile uint16_t*: ti_read_mask16v, \
      const volatile uint32_t*: ti_read_mask32v, \
      const volatile uint64_t*: ti_read_mask64v \
    )(loc, pos, len)

  ti_fn_attr_inline inline uint8_t ti_read_mask8(const uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline uint16_t ti_read_mask16(const uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline uint32_t ti_read_mask32(const uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline uint64_t ti_read_mask64(const uint64_t* loc, 
      const int32_t pos, const int32_t len);

  ti_fn_attr_inline inline uint8_t ti_read_mask8v(const volatile uint8_t* loc,
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline uint16_t ti_read_mask16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline uint32_t ti_read_mask32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline uint64_t ti_read_mask64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);

  /**
   * @brief Sets a series of bits to 1 at a specific location in memory.
   * @param loc (pointer to unsigned integer of any size/volatility) The 
   *            location in memory to set bits at.
   * @param pos (int32_t) The offset of the location to set bits at (number of
   *            bits from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to set (after 'pos').
   * @note - The size of 'loc' determines the alignment of this operation.
   * @note - The volatility of 'loc' determines if this operation is volatile.
   */
  #define ti_set_mask(loc, pos, len) \
    _Generic((loc), \
      uint8_t*: ti_set_mask8, \
      uint16_t*: ti_set_mask16, \
      uint32_t*: ti_set_mask32, \
      uint64_t*: ti_set_mask64, \
      volatile uint8_t*: ti_set_mask8v, \
      volatile uint16_t*: ti_set_mask16v, \
      volatile uint32_t*: ti_set_mask32v, \
      volatile uint64_t*: ti_set_mask64v \
    )(loc, pos, len)

  ti_fn_attr_inline inline void ti_set_mask8(uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_set_mask16(uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_set_mask32(uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_set_mask64(uint64_t* loc, 
      const int32_t pos, const int32_t len);

  ti_fn_attr_inline inline void ti_set_mask8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_set_mask16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_set_mask32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_set_mask64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);

  /**
   * @brief Sets a series of bits to 0 at a specific location in memory.
   * @param loc (pointer to unsigned integer of any size/volatility) The
   *            location in memory to clear bits at.
   * @param pos (int32_t) The offset of the location to clear bits at (number of
   *            bits from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to clear (after 'pos').
   * @note - The size of 'loc' determines the alignment of this operation.
   * @note - The volatility of 'loc' determines if this operation is volatile.
   */
  #define ti_clear_mask(loc, pos, len) \
    _Generic((loc), \
      uint8_t*: ti_clear_mask8, \
      uint16_t*: ti_clear_mask16, \
      uint32_t*: ti_clear_mask32, \
      uint64_t*: ti_clear_mask64, \
      volatile uint8_t*: ti_clear_mask8v, \
      volatile uint16_t*: ti_clear_mask16v, \
      volatile uint32_t*: ti_clear_mask32v, \
      volatile uint64_t*: ti_clear_mask64v \
    )(loc, pos, len)

  ti_fn_attr_inline inline void ti_clear_mask8(uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_clear_mask16(uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_clear_mask32(uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_clear_mask64(uint64_t* loc, 
      const int32_t pos, const int32_t len);

  ti_fn_attr_inline inline void ti_clear_mask8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_clear_mask16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_clear_mask32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_clear_mask64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);

  /**
   * @brief Toggles a series of bits at a specific location in memory.
   * @param loc (pointer to unsigned integer of any size/volatility) The
   *            location in memory to toggle bits at.
   * @param pos (int32_t) The offset of the location to toggle bits at (number of
   *            bits from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to toggle (after 'pos').
   * @note - The size of 'loc' determines the alignment of this operation.
   * @note - The volatility of 'loc' determines if this operation is volatile.
   */
  #define ti_toggle_mask(loc, pos, len) \
    _Generic((loc), \
      uint8_t*: ti_toggle_mask8, \
      uint16_t*: ti_toggle_mask16, \
      uint32_t*: ti_toggle_mask32, \
      uint64_t*: ti_toggle_mask64, \
      volatile uint8_t*: ti_toggle_mask8v, \
      volatile uint16_t*: ti_toggle_mask16v, \
      volatile uint32_t*: ti_toggle_mask32v, \
      volatile uint64_t*: ti_toggle_mask64v \
    )(loc, pos, len)

  ti_fn_attr_inline inline void ti_toggle_mask8(uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_toggle_mask16(uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_toggle_mask32(uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_toggle_mask64(uint64_t* loc, 
      const int32_t pos, const int32_t len);

  ti_fn_attr_inline inline void ti_toggle_mask8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_toggle_mask16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_toggle_mask32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline void ti_toggle_mask64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);

  /**
   * @brief Determines if a series of bits are set a specific location in memory.
   * @param loc (pointer to unsigned integer of any size/constness/volatility) 
   *            The location in memory to check.
   * @param pos (int32_t) The offset of the location to check (number of bits 
   *            from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to check (after 'pos').
   * @returns (bool) True if 'len' bits are set, 'pos' bits from the lsb at
   *          'loc', or false otherwise.
   * @note - The size of 'loc' determines the alignment of this operation.
   * @note - The volatility of 'loc' determines if this operation is volatile.
   */
  #define ti_is_set(loc, pos, len) \
    _Generic((loc), \
      uint8_t*: ti_is_set8, \
      uint16_t*: ti_is_set16, \
      uint32_t*: ti_is_set32, \
      uint64_t*: ti_is_set64, \
      const uint8_t*: ti_is_set8, \
      const uint16_t*: ti_is_set16, \
      const uint32_t*: ti_is_set32, \
      const uint64_t*: ti_is_set64, \
      volatile uint8_t*: ti_is_set8v, \
      volatile uint16_t*: ti_is_set16v, \
      volatile uint32_t*: ti_is_set32v, \
      volatile uint64_t*: ti_is_set64v, \
      const volatile uint8_t*: ti_is_set8v, \
      const volatile uint16_t*: ti_is_set16v, \
      const volatile uint32_t*: ti_is_set32v, \
      const volatile uint64_t*: ti_is_set64v \
    )(loc, pos, len)

  ti_fn_attr_inline inline bool ti_is_set8(const uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_set16(const uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_set32(const uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_set64(const uint64_t* loc, 
      const int32_t pos, const int32_t len);

  ti_fn_attr_inline inline bool ti_is_set8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_set16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_set32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_set64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);

  /**
   * @brief Determines if a series of bits are clear a specific location in memory.
   * @param loc (pointer to unsigned integer of any size/constness/volatility)
   *            The location in memory to check.
   * @param pos (int32_t) The offset of the location to check (number of bits
   *            from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to check (after 'pos').
   * @returns (bool) True if 'len' bits are clear, 'pos' bits from the lsb at
   *          'loc', or false otherwise.
   * @note - The size of 'loc' determines the alignment of this operation.
   * @note - The volatility of 'loc' determines if this operation is volatile.
   */
  #define ti_is_clear(loc, pos, len) \
    _Generic((loc), \
      uint8_t*: ti_is_clear8, \
      uint16_t*: ti_is_clear16, \
      uint32_t*: ti_is_clear32, \
      uint64_t*: ti_is_clear64, \
      const uint8_t*: ti_is_clear8, \
      const uint16_t*: ti_is_clear16, \
      const uint32_t*: ti_is_clear32, \
      const uint64_t*: ti_is_clear64, \
      volatile uint8_t*: ti_is_clear8v, \
      volatile uint16_t*: ti_is_clear16v, \
      volatile uint32_t*: ti_is_clear32v, \
      volatile uint64_t*: ti_is_clear64v, \
      const volatile uint8_t*: ti_is_clear8v, \
      const volatile uint16_t*: ti_is_clear16v, \
      const volatile uint32_t*: ti_is_clear32v, \
      const volatile uint64_t*: ti_is_clear64v \
    )(loc, pos, len)

  ti_fn_attr_inline inline bool ti_is_clear8(const uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_clear16(const uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_clear32(const uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_clear64(const uint64_t* loc, 
      const int32_t pos, const int32_t len);

  ti_fn_attr_inline inline bool ti_is_clear8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_clear16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_clear32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  ti_fn_attr_inline inline bool ti_is_clear64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  uint64_t ti_get_mask(const int32_t pos, const int32_t len) {
    return ((((uint64_t)1 << len) - 1u) << pos);
  }

  bool ti_valid_mask8(const int32_t pos, const int32_t len) {
    const int32_t max_bit = CHAR_BIT * sizeof(uint8_t);
    return (pos >= 0) && (len >= 1) && ((pos + len) <= max_bit);
  }
  
  bool ti_valid_mask16(const int32_t pos, const int32_t len) {
    const int32_t max_bit = CHAR_BIT * sizeof(uint16_t);
    return (pos >= 0) && (len >= 1) && ((pos + len) <= max_bit);
  }

  bool ti_valid_mask32(const int32_t pos, const int32_t len) {
    const int32_t max_bit = CHAR_BIT * sizeof(uint32_t);
    return (pos >= 0) && (len >= 1) && ((pos + len) <= max_bit);
  }

  bool ti_valid_mask64(const int32_t pos, const int32_t len) {
    const int32_t max_bit = CHAR_BIT * sizeof(uint64_t);
    return (pos >= 0) && (len >= 1) && ((pos + len) <= max_bit);
  }

  void ti_write_mask8(const uint8_t value, uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void ti_write_mask16(const uint16_t value, uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void ti_write_mask32(const uint32_t value, uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void ti_write_mask64(const uint64_t value, uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = ti_get_mask(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void ti_write_mask8v(const uint8_t value, volatile uint8_t* loc,
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void ti_write_mask16v(const uint16_t value, volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void ti_write_mask32v(const uint32_t value, volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void ti_write_mask64v(const uint64_t value, volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = ti_get_mask(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  uint8_t ti_read_mask8(const uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    return (*loc & mask) >> pos;
  }

  uint16_t ti_read_mask16(const uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    return (*loc & mask) >> pos;
  }

  uint32_t ti_read_mask32(const uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    return (*loc & mask) >> pos;
  }

  uint64_t ti_read_mask64(const uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    return (*loc & mask) >> pos;
  }

  uint8_t ti_read_mask8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    return (*loc & mask) >> pos;
  }

  uint16_t ti_read_mask16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    return (*loc & mask) >> pos;
  }

  uint32_t ti_read_mask32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    return (*loc & mask) >> pos;
  }

  uint64_t ti_read_mask64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    return (*loc & mask) >> pos;
  }

  void ti_set_mask8(uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    *loc = *loc | mask;
  }

  void ti_set_mask16(uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    *loc = *loc | mask;
  }

  void ti_set_mask32(uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    *loc = *loc | mask;
  }
  
  void ti_set_mask64(uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    *loc = *loc | mask;
  }

  void ti_set_mask8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    *loc = *loc | mask;
  }

  void ti_set_mask16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    *loc = *loc | mask;
  }

  void ti_set_mask32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    *loc = *loc | mask;
  }

  void ti_set_mask64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    *loc = *loc | mask;
  }

  void ti_clear_mask8(uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    *loc = *loc & ~mask;
  }

  void ti_clear_mask16(uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    *loc = *loc & ~mask;
  }

  void ti_clear_mask32(uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    *loc = *loc & ~mask;
  }

  void ti_clear_mask64(uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    *loc = *loc & ~mask;
  }

  void ti_clear_mask8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    *loc = *loc & ~mask;
  }

  void ti_clear_mask16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    *loc = *loc & ~mask;
  }

  void ti_clear_mask32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    *loc = *loc & ~mask;
  }

  void ti_clear_mask64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    *loc = *loc & ~mask;
  }

  void ti_toggle_mask8(uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    *loc = *loc ^ mask;
  }

  void ti_toggle_mask16(uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    *loc = *loc ^ mask;
  }

  void ti_toggle_mask32(uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    *loc = *loc ^ mask;
  }
  
  void ti_toggle_mask64(uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    *loc = *loc ^ mask;
  }

  void ti_toggle_mask8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    *loc = *loc ^ mask;
  }

  void ti_toggle_mask16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    *loc = *loc ^ mask;
  }

  void ti_toggle_mask32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    *loc = *loc ^ mask;
  }

  void ti_toggle_mask64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    *loc = *loc ^ mask;
  }

  bool ti_is_set8(const uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    return (*loc & mask) == mask;
  }

  bool ti_is_set16(const uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    return (*loc & mask) == mask;
  }

  bool ti_is_set32(const uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    return (*loc & mask) == mask;
  }

  bool ti_is_set64(const uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    return (*loc & mask) == mask;
  }

  bool ti_is_set8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    return (*loc & mask) == mask;
  }

  bool ti_is_set16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    return (*loc & mask) == mask;
  }

  bool ti_is_set32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    return (*loc & mask) == mask;
  }

  bool ti_is_set64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    return (*loc & mask) == mask;
  }

  bool ti_is_clear8(const uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    return (*loc & mask) == 0;
  }

  bool ti_is_clear16(const uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    return (*loc & mask) == 0;
  }

  bool ti_is_clear32(const uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    return (*loc & mask) == 0;
  }

  bool ti_is_clear64(const uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    return (*loc & mask) == 0;
  }

  bool ti_is_clear8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = (uint8_t)ti_get_mask(pos, len);
    return (*loc & mask) == 0;
  }

  bool ti_is_clear16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = (uint16_t)ti_get_mask(pos, len);
    return (*loc & mask) == 0;
  }

  bool ti_is_clear32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = (uint32_t)ti_get_mask(pos, len);
    return (*loc & mask) == 0;
  }

  bool ti_is_clear64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = (uint64_t)ti_get_mask(pos, len);
    return (*loc & mask) == 0;
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif
