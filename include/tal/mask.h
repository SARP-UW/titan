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
 * @file include/tal/mask.h 
 * @authors Aaron McBride
 * @brief Bitmask utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "tal/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Bitmask Utilities
   **************************************************************************************************/

  /**
   * @defgroup tal_get_mask
   * @brief Generates a bitmask of a specific length with bits at a specific location.
   * @param pos (unsigned integer denoted by suffix) The location of the first 
   *            set bit in the mask (from lsb).
   * @param len (int32_t) The number of contiguous set bits in the mask.
   * @returns (unsigned integer denoted by suffix) A bitmask with 'len' set 
   *          bits, 'pos' bits from the lsb.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_get_mask_u8(
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint16_t tal_get_mask_u16(
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint32_t tal_get_mask_u32(
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint64_t tal_get_mask_u64(
      const int32_t pos, const int32_t len);
  /** @} */

  /**
   * @defgroup tal_valid_mask
   * @brief Determines if a mask is valid for a specific memory location type.
   * @param pos (unsigned integer denoted by suffix) The offset of the mask from 
   *            the lsb of the memory location (in bits).
   * @param len (int32_t) The length of the mask (in bits).
   * @returns (bool) True if a mask of 'len' bits, 'pos' bits from the lsb of
   *          a pointer to 'type' is valid, or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_valid_mask_u8(
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_valid_mask_u16(
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_valid_mask_u32(
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_valid_mask_u64(
      const int32_t pos, const int32_t len);
  /** @} */

  /**
   * @defgroup tal_write_mask
   * @brief Writes a value to a bit-specific location in memory.
   * @param value (unsigned integer denoted by suffix) The value to write.
   * @param loc (pointer to unsigned integer denoted by suffix) The location in 
   *            memory to write to.
   * @param pos (int32_t) The offset (bits from lsb) of the location to write to.
   * @param len (int32_t) The length (in bits) of the location to write to.
   * @{
   */
  tal_fn_attr_inline inline void tal_write_mask_u8(const uint8_t value, 
      uint8_t* loc, const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_write_mask_u16(const uint16_t value, 
      uint16_t* loc, const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_write_mask_u32(const uint32_t value, 
      uint32_t* loc, const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_write_mask_u64(const uint64_t value, 
      uint64_t* loc, const int32_t pos, const int32_t len);
      
  tal_fn_attr_inline inline void tal_write_mask_u8v(const uint8_t value, 
      volatile uint8_t* loc, const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_write_mask_u16v(const uint16_t value, 
      volatile uint16_t* loc, const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_write_mask_u32v(const uint32_t value, 
      volatile uint32_t* loc, const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_write_mask_u64v(const uint64_t value, 
      volatile uint64_t* loc, const int32_t pos, const int32_t len);
  /** @} */

  /**
   * @defgroup tal_read_mask
   * @brief Reads the value at a bit-specific location in memory.
   * @param loc (const pointer to unsigned integer denoted by suffix) The 
   *            location in memory to read from.
   * @param pos (int32_t) The offset (bits from lsb) of the location to read from.
   * @param len (int32_t) The length (in bits) of the location to read from.
   * @returns (same type as 'loc' without pointer) The value stored in 'len' 
   *          bits, 'pos' bits from the lsb at the given location.
   * @{
   */
  tal_fn_attr_inline inline uint8_t tal_read_mask_u8(const uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint16_t tal_read_mask_u16(const uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint32_t tal_read_mask_u32(const uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint64_t tal_read_mask_u64(const uint64_t* loc, 
      const int32_t pos, const int32_t len);

  tal_fn_attr_inline inline uint8_t tal_read_mask_u8v(const volatile uint8_t* loc,
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint16_t tal_read_mask_u16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint32_t tal_read_mask_u32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline uint64_t tal_read_mask_u64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);
  /** @} */

  /**
   * @defgroup tal_set_mask
   * @brief Sets a series of bits to 1 at a specific location in memory.
   * @param loc (pointer to unsigned integer denoted by suffix) The location in 
   *            memory to set bits at.
   * @param pos (int32_t) The offset of the location to set bits at (number of
   *            bits from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to set (after 'pos').
   * @{
   */
  tal_fn_attr_inline inline void tal_set_mask_u8(uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_set_mask_u16(uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_set_mask_u32(uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_set_mask_u64(uint64_t* loc, 
      const int32_t pos, const int32_t len);

  tal_fn_attr_inline inline void tal_set_mask_u8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_set_mask_u16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_set_mask_u32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_set_mask_u64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);
  /** @} */

  /**
   * @defgroup tal_clear_mask
   * @brief Sets a series of bits to 0 at a specific location in memory.
   * @param loc (pointer to unsigned integer denoted by suffix) The location in 
   *            memory to clear bits at.
   * @param pos (int32_t) The offset of the location to clear bits at (number of
   *            bits from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to clear (after 'pos').
   * @{
   */
  tal_fn_attr_inline inline void tal_clear_mask_u8(uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_clear_mask_u16(uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_clear_mask_u32(uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_clear_mask_u64(uint64_t* loc, 
      const int32_t pos, const int32_t len);

  tal_fn_attr_inline inline void tal_clear_mask_u8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_clear_mask_u16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_clear_mask_u32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_clear_mask_u64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);
  /** @} */

  /**
   * @defgroup tal_toggle_mask
   * @brief Toggles a series of bits at a specific location in memory.
   * @param loc (pointer to unsigned integer denoted by suffix) The location in 
   *            memory to toggle bits at.
   * @param pos (int32_t) The offset of the location to toggle bits at (number of
   *            bits from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to toggle (after 'pos').
   * @{
   */
  tal_fn_attr_inline inline void tal_toggle_mask_u8(uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_toggle_mask_u16(uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_toggle_mask_u32(uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_toggle_mask_u64(uint64_t* loc, 
      const int32_t pos, const int32_t len);

  tal_fn_attr_inline inline void tal_toggle_mask_u8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_toggle_mask_u16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_toggle_mask_u32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline void tal_toggle_mask_u64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);
  /** @} */

  /**
   * @defgroup tal_is_set
   * @brief Determines if a series of bits are set a specific location in memory.
   * @param loc (const pointer to unsigned integer denoted by suffix) The 
   *            location in memory to check.
   * @param pos (int32_t) The offset of the location to check (number of bits 
   *            from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to check (after 'pos').
   * @returns (bool) True if 'len' bits are set, 'pos' bits from the lsb at
   *          'loc', or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_is_set_u8(const uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_set_u16(const uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_set_u32(const uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_set_u64(const uint64_t* loc, 
      const int32_t pos, const int32_t len);

  tal_fn_attr_inline inline bool tal_is_set_u8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_set_u16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_set_u32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_set_u64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);
  /** @} */

  /**
   * @defgroup tal_is_clear
   * @brief Determines if a series of bits are clear a specific location in memory.
   * @param loc (const pointer to unsigned integer denoted by suffix) The 
   *            location in memory to check.
   * @param pos (int32_t) The offset of the location to check (number of bits
   *            from lsb of 'loc').
   * @param len (int32_t) The number of consecutive bits to check (after 'pos').
   * @returns (bool) True if 'len' bits are clear, 'pos' bits from the lsb at
   *          'loc', or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_is_clear_u8(const uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_clear_u16(const uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_clear_u32(const uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_clear_u64(const uint64_t* loc, 
      const int32_t pos, const int32_t len);

  tal_fn_attr_inline inline bool tal_is_clear_u8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_clear_u16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_clear_u32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len);
  tal_fn_attr_inline inline bool tal_is_clear_u64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len);
  /** @} */

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  uint8_t tal_get_mask_u8(const int32_t pos, const int32_t len) {
    return (((uint8_t)1 << pos) - 1u) << len;
  }

  uint16_t tal_get_mask_u16(const int32_t pos, const int32_t len) {
    return (((uint16_t)1 << pos) - 1u) << len;
  }

  uint32_t tal_get_mask_u32(const int32_t pos, const int32_t len) {
    return (((uint32_t)1 << pos) - 1u) << len;
  }

  uint64_t tal_get_mask_u64(const int32_t pos, const int32_t len) {
    return (((uint64_t)1 << pos) - 1u) << len;
  }

  bool tal_valid_mask_u8(const int32_t pos, const int32_t len) {
    return (pos >= 0) && (len >= 1) && ((pos + len) <= 8);
  }
  
  bool tal_valid_mask_u16(const int32_t pos, const int32_t len) {
    return (pos >= 0) && (len >= 1) && ((pos + len) <= 16);
  }

  bool tal_valid_mask_u32(const int32_t pos, const int32_t len) {
    return (pos >= 0) && (len >= 1) && ((pos + len) <= 32);
  }

  bool tal_valid_mask_u64(const int32_t pos, const int32_t len) {
    return (pos >= 0) && (len >= 1) && ((pos + len) <= 64);
  }

  void tal_write_mask8(const uint8_t value, uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void tal_write_mask_u16(const uint16_t value, uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void tal_write_mask_u32(const uint32_t value, uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void tal_write_mask_u64(const uint64_t value, uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void tal_write_mask_u8v(const uint8_t value, volatile uint8_t* loc,
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void tal_write_mask_u16v(const uint16_t value, volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void tal_write_mask_u32v(const uint32_t value, volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  void tal_write_mask_u64v(const uint64_t value, volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    *loc = (*loc & ~mask) | ((value << pos) & mask);
  }

  uint8_t tal_read_mask_u8(const uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    return (*loc & mask) >> pos;
  }

  uint16_t tal_read_mask_u16(const uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    return (*loc & mask) >> pos;
  }

  uint32_t tal_read_mask_u32(const uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    return (*loc & mask) >> pos;
  }

  uint64_t tal_read_mask_u64(const uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    return (*loc & mask) >> pos;
  }

  uint8_t tal_read_mask_u8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    return (*loc & mask) >> pos;
  }

  uint16_t tal_read_mask_u16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    return (*loc & mask) >> pos;
  }

  uint32_t tal_read_mask_u32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    return (*loc & mask) >> pos;
  }

  uint64_t tal_read_mask_u64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    return (*loc & mask) >> pos;
  }

  void tal_set_mask_u8(uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    *loc = *loc | mask;
  }

  void tal_set_mask_u16(uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    *loc = *loc | mask;
  }

  void tal_set_mask_u32(uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    *loc = *loc | mask;
  }
  
  void tal_set_mask_u64(uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    *loc = *loc | mask;
  }

  void tal_set_mask_u8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    *loc = *loc | mask;
  }

  void tal_set_mask_u16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    *loc = *loc | mask;
  }

  void tal_set_mask_u32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    *loc = *loc | mask;
  }

  void tal_set_mask_u64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    *loc = *loc | mask;
  }

  void tal_clear_mask_u8(uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    *loc = *loc & ~mask;
  }

  void tal_clear_mask_u16(uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    *loc = *loc & ~mask;
  }

  void tal_clear_mask_u32(uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    *loc = *loc & ~mask;
  }

  void tal_clear_mask_u64(uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    *loc = *loc & ~mask;
  }

  void tal_clear_mask_u8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    *loc = *loc & ~mask;
  }

  void tal_clear_mask_u16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    *loc = *loc & ~mask;
  }

  void tal_clear_mask_u32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    *loc = *loc & ~mask;
  }

  void tal_clear_mask_u64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    *loc = *loc & ~mask;
  }

  void tal_toggle_mask_u8(uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    *loc = *loc ^ mask;
  }

  void tal_toggle_mask_u16(uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    *loc = *loc ^ mask;
  }

  void tal_toggle_mask_u32(uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    *loc = *loc ^ mask;
  }
  
  void tal_toggle_mask_u64(uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    *loc = *loc ^ mask;
  }

  void tal_toggle_mask_u8v(volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    *loc = *loc ^ mask;
  }

  void tal_toggle_mask_u16v(volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    *loc = *loc ^ mask;
  }

  void tal_toggle_mask_u32v(volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    *loc = *loc ^ mask;
  }

  void tal_toggle_mask_u64v(volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    *loc = *loc ^ mask;
  }

  bool tal_is_set_u8(const uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    return (*loc & mask) == mask;
  }

  bool tal_is_set_u16(const uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    return (*loc & mask) == mask;
  }

  bool tal_is_set_u32(const uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    return (*loc & mask) == mask;
  }

  bool tal_is_set_u64(const uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    return (*loc & mask) == mask;
  }

  bool tal_is_set_u8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    return (*loc & mask) == mask;
  }

  bool tal_is_set_u16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    return (*loc & mask) == mask;
  }

  bool tal_is_set_u32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    return (*loc & mask) == mask;
  }

  bool tal_is_set_u64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    return (*loc & mask) == mask;
  }

  bool tal_is_clear_u8(const uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    return (*loc & mask) == 0u;
  }

  bool tal_is_clear_u16(const uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    return (*loc & mask) == 0u;
  }

  bool tal_is_clear_u32(const uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    return (*loc & mask) == 0u;
  }

  bool tal_is_clear_u64(const uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    return (*loc & mask) == 0u;
  }

  bool tal_is_clear_u8v(const volatile uint8_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint8_t mask = tal_get_mask_u8(pos, len);
    return (*loc & mask) == 0u;
  }

  bool tal_is_clear_u16v(const volatile uint16_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint16_t mask = tal_get_mask_u16(pos, len);
    return (*loc & mask) == 0u;
  }

  bool tal_is_clear_u32v(const volatile uint32_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint32_t mask = tal_get_mask_u32(pos, len);
    return (*loc & mask) == 0u;
  }

  bool tal_is_clear_u64v(const volatile uint64_t* loc, 
      const int32_t pos, const int32_t len) {
    const uint64_t mask = tal_get_mask_u64(pos, len);
    return (*loc & mask) == 0u;
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif
