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
 * @file include/tal/mem.h
 * @authors Joshua Beard, Aaron McBride
 * @brief Memory manipulation and querying utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/common/attributes.h"
#include "include/tal/numeric.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**
   * @brief Copies a block of memory from one location to annother.
   * @param dst (void*) The destination location
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to copy.
   * @param err (bool*) The error flag. Accessed and set if 'size' is less 
   *            than 0, or if 'dst' or 'src' are NULL. If set, this function 
   *            is guaranteed to have no other side effects.
   * @returns (void*) The destination location ('dst').
   * @note - The source and destination locations may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_copy(void* dst, const void* src, 
      const int32_t size, bool* err);

  /**
   * @brief Copies a block of memory from one location to annother, n times.
   * @param dst (void*) The destination location.
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to copy.
   * @param n (int32_t) The number of times to copy 'size' bytes from the source
   *          location to a contiguous location in the destination.
   * @param err (bool*) The error flag. Accessed and set if 'size' or 'n' is
   *            less than 0, or if 'dst' or 'src' are NULL. If set, this function
   *            is guaranteed to have no other side effects.
   * @returns (void*) The destination location ('dst').
   * @note - The source and destination locations may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_copyn(void* dst, const void* src, 
      const int32_t size, const int32_t n, bool* err);

  /**
   * @defgroup tal_mem_copyn_xx
   * @brief Sets every value in memory at a location to a specific value.
   * @param mem (void*) The location in memory to set.
   * @param value (integer type denoted by suffix) The value to set.
   * @param cnt (int32_t) The number of values to set (note: size varies by type).
   * @param err (bool*) The error flag. Accessed and set if 'cnt' is less than 0,
   *            or if 'mem' is NULL. If set, this function is guaranteed to have
   *            no other side effects.
   * @returns (void*) The set location in memory ('mem').
   * @{
   */
  tal_fn_attr_inline inline void* tal_mem_copyn_u8(void* mem, const uint8_t value, 
      const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_copyn_u16(void* mem, const uint16_t value, 
      const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_copyn_u32(void* mem, const uint32_t value, 
      const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_copyn_u64(void* mem, const uint64_t value, 
      const int32_t cnt, bool* err);
  /** @} */

  /**
   * @brief Swaps the contents of two blocks of memory.
   * @param mem_a (void*) The first block of memory.
   * @param mem_b (void*) The second block of memory.
   * @param size (int32_t) The number of bytes to swap.
   * @param err (bool*) The error flag. Accessed and set if 'size' is less than 0,
   *            or if 'mem_a' or 'mem_b' are NULL. If set, this function is 
   *            guaranteed to have no other side effects.
   * @note - 'mem_a' and 'mem_b' must NOT overlap.
   */
  tal_fn_attr_inline inline void tal_mem_swap(void* restrict mem_a, 
      void* restrict mem_b, const int32_t size, bool* err);

  /**
   * @brief Compares two blocks of memory for equality.
   * @param mem_a (const void*) The first block of memory.
   * @param mem_b (const void*) The second block of memory.
   * @param size (int32_t) The number of bytes to compare.
   * @param err (bool*) The error flag. Accessed and set if 'size' is less than 0,
   *            or if 'mem_a' or 'mem_b' are NULL. If set, this function returns
   *            false and is guaranteed to have no other side effects.
   * @returns (bool) True if every bit in 'mem_a' is equal to the corresponding 
   *          bit in 'mem_b', or false otherwise.
   * @note - 'mem_a' and 'mem_b' may overlap.
   */
  tal_fn_attr_inline inline bool tal_mem_cmp(const void* mem_a, 
      const void* mem_b, const int32_t size, bool* err);

  /**
   * @brief Compares a block of memory to annother for equality, n times.
   * @param mem_a (const void*) The first block of memory.
   * @param mem_b (const void*) The second, block of memory (repeated).
   * @param size (int32_t) The number of bytes to compare.
   * @param n (int32_t) The number of times to compare 'mem_b' to contiguous
   *          blocks of memory in 'mem_a'.
   * @param err (bool*) The error flag. Accessed and set if 'size' or 'n' is less
   *            than 0, or if 'mem_a' or 'mem_b' are NULL. If set, this function
   *            returns false and is guaranteed to have no other side effects.
   * @returns (bool) True if every 'size' bytes in 'mem_a' is equal to 'mem_b'
   *          'n' times, or false otherwise.
   * @note - 'mem_a' and 'mem_b' may overlap.
   */
  tal_fn_attr_inline inline bool tal_mem_cmpn(const void* mem_a, 
      const void* mem_b, const int32_t size, const int32_t n, bool* err);

  /**
   * @defgroup tal_mem_cmpn_x
   * @brief Compares every <size of value> bytes in a block of memory to a 
   *        specific value.
   * @param mem (const void*) The block of memory to compare.
   * @param value (integer type denoted by suffix) The value to compare (repeated).
   * @param cnt (int32_t) The number of values to compare (note size varies by type).
   * @param err (bool*) The error flag. Accessed and set if 'cnt' is less than 0,
   *            or if 'mem' is NULL. If set, this function returns false and is
   *            guaranteed to have no other side effects.
   * @returns (bool) True if every <size of value> bytes in 'mem' is equal to 'value',
   *          or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_mem_cmpn_u8(const void* mem, 
      const uint8_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline bool tal_mem_cmpn_u16(const void* mem, 
      const uint16_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline bool tal_mem_cmpn_u32(const void* mem, 
      const uint32_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline bool tal_mem_cmpn_u64(const void* mem, 
      const uint64_t value, const int32_t cnt, bool* err);
  /** @} */

  /**
   * @brief Gets a pointer to the first location in a block of memory that
   *        is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @returns (void*) A pointer to the start of the first location in 'mem'
   *          that contains 'fsize' bytes which are equal to 'fmem', or
   *          NULL if no such location exists, or invalid arguments are given.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_get(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize, bool* err);

  /**
   * @brief Gets a pointer to the last location in a block of memory that 
   *        is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @returns (void*) A pointer to the start of the last location in 'mem'
   *          that contains 'fsize' bytes which are equal to 'fmem', or
   *          NULL if no such location exists, or invalid arguments are given.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_getr(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize, bool* err);

  /**
   * @brief Gets a pointer to the nth location in a block of memory that
   *        is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @param n (int32_t) The index of the matching location to get.
   * @returns (void*) A pointer to the start of the nth location in 'mem'
   *          that contains 'fsize' bytes which are equal to 'fmem', or
   *          NULL if no such location exists, or invalid arguments are given.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_getn(const void* mem, const void* fmem, 
      const int32_t size, const int32_t fsize, const int32_t n, bool* err);

  /**
   * @defgroup tal_memval
   * @brief Gets a pointer to the first location in a block of memory that
   *        contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @returns (void*) A pointer to the start of the first location in 'mem'
   *          that contains 'value', or NULL if no such location exists, or
   *          invalid arguments are given.
   * @{
   */
  tal_fn_attr_inline inline void* tal_mem_get_u8(const void* mem, 
      const uint8_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_get_u16(const void* mem, 
      const uint16_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_get_u32(const void* mem, 
      const uint32_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_get_u64(const void* mem, 
      const uint64_t value, const int32_t cnt, bool* err);
  /** @} */

  /**
   * @defgroup tal_memrval
   * @brief Gets a pointer to the last location in a block of memory that
   *        contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @returns (void*) A pointer to the start of the last location in 'mem'
   *          that contains 'value', or NULL if no such location exists, or
   *          invalid arguments are given.
   * @{
   */
  tal_fn_attr_inline inline void* tal_mem_ptrr_u8(const void* mem, 
      const uint8_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_getr_u16(const void* mem, 
      const uint16_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_getr_u32(const void* mem, 
      const uint32_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline void* tal_mem_getr_u64(const void* mem, 
      const uint64_t value, const int32_t cnt, bool* err);
  /** @} */

  /**
   * @defgroup tal_memnval
   * @brief Gets a pointer to the nth location in a block of memory that
   *        contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @param n (int32_t) The index of the matching location to get.
   * @returns (void*) A pointer to the start of the nth location in 'mem'
   *          that contains 'value', or NULL if no such location exists, or
   *          invalid arguments are given.
   * @{
   */
  tal_fn_attr_inline inline void* tal_mem_getn_u8(const void* mem, 
      const uint8_t value, const int32_t cnt, const int32_t n, bool* err);
  tal_fn_attr_inline inline void* tal_mem_getn_u16(const void* mem, 
      const uint16_t value, const int32_t cnt, const int32_t n, bool* err);
  tal_fn_attr_inline inline void* tal_mem_getn_u32(const void* mem, 
      const uint32_t value, const int32_t cnt, const int32_t n, bool* err);
  tal_fn_attr_inline inline void* tal_mem_getn_u64(const void* mem, 
      const uint64_t value, const int32_t cnt, const int32_t n, bool* err);
  /** @} */

  /**
   * @brief Gets the byte offset of the first location in a block of memory
   *        that is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @returns (int32_t) The byte offset of the first location in 'mem'
   *          that contains 'fsize' bytes which are equal to 'fmem', or
   *         -1 if no such location exists, or invalid arguments are given.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_mem_index(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize, bool* err);

  /**
   * @brief Gets the byte offset of the last location in a block of memory
   *        that is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @returns (int32_t) The byte offset of the last location in 'mem'
   *          that contains 'fsize' bytes which are equal to 'fmem', or
   *          -1 if no such location exists, or invalid arguments are given.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_mem_indexr(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize, bool* err);

  /**
   * @brief Gets the byte offset of the nth location in a block of memory
   *        that is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @param n (int32_t) The index of the matching location to get.
   * @returns (int32_t) The byte offset of the nth location in 'mem'
   *          that contains 'fsize' bytes which are equal to 'fmem', or
   *          -1 if no such location exists, or invalid arguments are given.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_mem_indexn(const void* mem, const void* fmem,
      const int32_t size, const int32_t fsize, const int32_t n, bool* err);

  /**
   * @defgroup tal_memval_i
   * @brief Gets the (suffix) offset of the first location in a block of memory
   *        that contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @returns (int32_t) The byte offset of the first location in 'mem'
   *          that contains 'value', or -1 if no such location exists, or
   *          invalid arguments are given.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_mem_index_u8(const void* mem, 
      const uint8_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_index_u16(const void* mem, 
      const uint16_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_index_u32(const void* mem, 
      const uint32_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_index_u64(const void* mem, 
      const uint64_t value, const int32_t cnt, bool* err);
  /** @} */

  /**
   * @defgroup tal_memrval_i
   * @brief Gets the (suffix) offset of the last location in a block of memory
   *        that contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @returns (int32_t) The byte offset of the last location in 'mem'
   *          that contains 'value', or -1 if no such location exists, or
   *          invalid arguments are given.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_mem_indexr_u8(const void* mem, 
      const uint8_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_indexr_u16(const void* mem, 
      const uint16_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_indexr_u32(const void* mem, 
      const uint32_t value, const int32_t cnt, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_indexr_u64(const void* mem, 
      const uint64_t value, const int32_t cnt, bool* err);
  /** @} */

  /**
   * @defgroup tal_memnval_i
   * @brief Gets the (suffix) offset of the nth location in a block of memory
   *        that contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @param n (int32_t) The index of the matching location to get.
   * @returns (int32_t) The byte offset of the nth location in 'mem'
   *          that contains 'value', or -1 if no such location exists, or
   *          invalid arguments are given.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_mem_indexn_u8(const void* mem, 
      const uint8_t value, const int32_t cnt, const int32_t n, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_indexn_u16(const void* mem, 
      const uint16_t value, const int32_t cnt, const int32_t n, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_indexn_u32(const void* mem, 
      const uint32_t value, const int32_t cnt, const int32_t n, bool* err);
  tal_fn_attr_inline inline int32_t tal_mem_indexn_u64(const void* mem, 
      const uint64_t value, const int32_t cnt, const int32_t n, bool* err);
  /** @} */

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  static bool mem_overlap(const void* mem_a, const void* mem_b,
      const int32_t size) {
    const uint64_t a_addr = (uint64_t)mem_a;
    const uint64_t b_addr = (uint64_t)mem_b;
    bool flag = false;
    if (a_addr < b_addr) {
      return tal_sadd_u64(a_addr, (uint64_t)size, &flag) > b_addr;
    } else {
      return tal_sadd_u64(b_addr, (uint64_t)size, &flag) > a_addr;
    }
  }

  void* tal_mem_copy(void* dst, const void* src, const int32_t size, bool* err) {
    if (!dst || !src || size < 0) {
      *err = true;
    } else {
      uint8_t* d = dst;
      const uint8_t* s = src;
      if ((uintptr_t)d <= (uintptr_t)s) {
        for (int32_t i = 0; i < size; ++i) { d[i] = s[i]; }
      } else {
        for (int32_t i = size - 1; i >= 0; --i) { d[i] = s[i]; }
      }
    }
    return dst;
  }

  void* tal_mem_copyn(void* dst, const void* src, const int32_t size, 
      const int32_t n, bool* err) {
    if (!dst || !src || n < 0 || size < 0) {
      *err = true;
    } else {
      uint8_t* d = dst;
      const uint8_t* s = src;
      if ((uintptr_t)d <= (uintptr_t)s) {
        for (int32_t i = 0; i < n; ++i) {
          for (int32_t j = 0; j < size; ++j) { d[(i * size) + j] = s[j]; }
        }
      } else {
        for (int32_t i = n - 1; i >= 0; --i) {
          for (int32_t j = size - 1; j >= 0; --j) { d[(i * size) + j] = s[i]; }
        }
      }
    }
    return dst;
  }

  void* tal_mem_copyn_u8(void* mem, const uint8_t value, const int32_t cnt, 
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_mem_copyn_u16(void* mem, const uint16_t value, const int32_t cnt, 
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_mem_copyn_u32(void* mem, const uint32_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_mem_copyn_u64(void* mem, const uint64_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void tal_mem_swap(void* restrict mem_a, void* restrict mem_b, 
      const int32_t size, bool* err) {
    if (!mem_a || !mem_b || size < 0 || mem_overlap(mem_a, mem_b, size)) {
      *err = true;
    } else {
      uint8_t* a = mem_a;
      uint8_t* b = mem_b;
      for(int32_t i = 0; i < size; ++i){
        uint8_t tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
      }
    }
  }

  bool tal_mem_cmp(const void* mem_a, const void* mem_b, const int32_t size,
      bool* err) {
    if (!mem_a || !mem_b || size <= 0) {
      *err = true;
      return false;
    } 
    const uint8_t* a = mem_a;
    const uint8_t* b = mem_b;
    for (int32_t i = 0; i < size; ++i) {
      if (a[i] != b[i]) { return false; }
    }
    return true;
  }

  bool tal_mem_cmpn(const void* mem_a, const void* mem_b, const int32_t size,
      const int32_t n, bool* err) {
    if (!mem_a || !mem_b || size < 0 || n < 0) {
      *err = true;
      return false;
    }
    const uint8_t* a = mem_a;
    const uint8_t* b = mem_b;
    for (int32_t i = 0; i < n; ++i) {
      for (int32_t j = 0; j < size; ++j) {
        if (a[j * i] != b[j]) { return false; }
      }
    }
    return true;
  }

  bool tal_mem_cmpn_u8(const void* mem, const uint8_t value, const int32_t cnt, 
      bool* err) {
    if (!mem || cnt < 0) { 
      *err = true;
      return false;
    }
    const uint8_t* m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_mem_cmpn_u16(const void* mem, const uint16_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) { 
      *err = true;
      return false;
    }
    const uint16_t* m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_mem_cmpn_u32(const void* mem, const uint32_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) { 
      *err = true;
      return false;
    }
    const uint32_t* m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_mem_cmpn_u64(const void* mem, const uint64_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) { 
      *err = true;
      return false;
    }
    const uint64_t* m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  void* tal_mem_get(const void* mem, const void* fmem, const int32_t size, 
      const int32_t fsize, bool* err) {
    if (!mem || !fmem || size < 0 || fsize < 0) {
      *err = true;
    } else {
      int32_t fi = 0;
      const uint8_t* m = mem;
      const uint8_t* f = fmem;
      for (int32_t i = 0; i < size; ++i) {
        if (m[i] == f[fi]) {
          ++fi;
          if (fi == fsize) { return (void*)(mem + i - fsize); }
        } else { 
          fi = 0;
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getr(const void* mem, const void* fmem, const int32_t size, 
      const int32_t fsize, bool* err) {
    if (!mem || !fmem || size < 0 || fsize < 0) {
      *err = true;
    } else {
      int32_t fi = fsize - 1;
      const uint8_t* m = mem;
      const uint8_t* f = fmem;
      for (int32_t i = size - 1; i >= 0; --i) {
        if (m[i] == f[fi]) {
          --fi;
          if (!fi) { return (void*)(mem + i + fsize); }
        } else { 
          fi = 0;
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getn(const void* mem, const void* fmem, const int32_t size, 
      const int32_t fsize, const int32_t n, bool* err) {
    if (!mem || !fmem || size < 0 || fsize < 0 || n < 0) {
      *err = true;
    } else {
      int32_t fi = 0;
      int32_t fcnt = 0;
      const uint8_t* m = mem;
      const uint8_t* f = fmem;
      for (int32_t i = 0; i < size; ++i) {
        if (m[i] == f[fi]) {
          ++fi;
          if (fi == fsize) {
            ++fcnt;
            if (fcnt == n) { return (void*)(mem + i - fsize); }
          }
        } else {
          fi = 0;
        }
      }
    }
    return NULL;
  }

  void* tal_mem_get_u8(const void* mem, const uint8_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_get_u16(const void* mem, const uint16_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_get_u32(const void* mem, const uint32_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_get_u64(const void* mem, const uint64_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_getr_u8(const void* mem, const uint8_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint8_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_getr_u16(const void* mem, const uint16_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint16_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_getr_u32(const void* mem, const uint32_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint32_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_getr_u64(const void* mem, const uint64_t value, const int32_t cnt,
      bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint64_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }


  void* tal_mem_getn_u8(const void* mem, const uint8_t value, const int32_t cnt, 
      const int32_t n, bool* err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getn_u16(const void* mem, const uint16_t value, const int32_t cnt, 
      const int32_t n, bool* err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getn_u32(const void* mem, const uint32_t value, const int32_t cnt, 
      const int32_t n, bool* err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getn_u64(const void* mem, const uint64_t value, const int32_t cnt, 
      const int32_t n, bool* err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  int32_t tal_mem_index(const void* mem, const void* fmem, const int32_t size, 
      const int32_t fsize, bool* err) {
    if (!mem || !fmem || size < 0 || fsize < 0) {
      *err = true;
    } else {
      int32_t fi = 0;
      const uint8_t* m = mem;
      const uint8_t* f = fmem;
      for (int32_t i = 0; i < size; ++i) {
        if (m[i] == f[fi]) {
          ++fi;
          if (fi == fsize) { return i - fsize; }
        } else { 
          fi = 0;
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexr(const void* mem, const void* fmem, const int32_t size, 
      const int32_t fsize, bool* err) {
    if (!mem || !fmem || size < 0 || fsize < 0) {
      *err = true;
    } else {
      int32_t fi = fsize - 1;
      const uint8_t* m = mem;
      const uint8_t* f = fmem;
      for (int32_t i = size - 1; i >= 0; --i) {
        if (m[i] == f[fi]) {
          --fi;
          if (!fi) { return i; }
        } else { 
          fi = fsize - 1;
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn(const void* mem, const void* fmem, const int32_t size,
      const int32_t fsize, const int32_t n, bool* err) {
    if (!mem || !fmem || size < 0 || fsize < 0 || n < 0) {
      *err = true;
    } else {
      int32_t fi = 0;
      int32_t fcnt = 0;
      const uint8_t* m = mem;
      const uint8_t* f = fmem;
      for (int32_t i = 0; i < size; ++i) {
        if (m[i] == f[fi]) {
          ++fi;
          if (fi == fsize) {
            ++fcnt;
            if (fcnt == n) { return i - fsize; }
          }
        } else {
          fi = 0;
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_index_u8(const void* mem, const uint8_t value, 
      const int32_t cnt, bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
  }

  int32_t tal_mem_index_u16(const void* mem, const uint16_t value, 
      const int32_t cnt,  bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_index_u32(const void* mem, const uint32_t value, 
      const int32_t cnt, bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_index_u64(const void* mem, const uint64_t value, 
      const int32_t cnt, bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }
  
  int32_t tal_mem_indexr_u8(const void* mem, const uint8_t value, 
      const int32_t cnt, bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint8_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexr_u16(const void* mem, const uint16_t value, 
      const int32_t cnt, bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint16_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexr_u32(const void* mem, const uint32_t value, 
      const int32_t cnt, bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint32_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexr_u64(const void* mem, const uint64_t value, 
      const int32_t cnt, bool* err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint64_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn_u8(const void* mem, const uint8_t value, 
      const int32_t cnt, const int32_t n, bool* err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn_u16(const void* mem, const uint16_t value, 
      const int32_t cnt, const int32_t n, bool* err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn_u32(const void* mem, const uint32_t value, 
      const int32_t cnt, const int32_t n, bool* err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn_u64(const void* mem, const uint64_t value, 
      const int32_t cnt, const int32_t n, bool* err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

#if defined(__cplusplus)
  }
#endif