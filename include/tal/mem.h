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
#include "include/tal/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Memory Utilities
   **************************************************************************************************/

  /**
   * @brief Copies a block of memory from one location to annother.
   * @param dst (void*) The destination location
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to copy.
   * @returns (void*) The destination location.
   * @warning - The source and destination locations must NOT overlap.
   */
  tal_fn_attr_inline inline void* tal_memcpy(void* restrict dst, 
      const void* restrict src, const int32_t size);

  /**
   * @brief Copies a block of memory from one location to annother, n times.
   * @param dst (void*) The destination location
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to copy.
   * @param n (int32_t) The number of times to copy the source to the destination.
   * @returns (void*) The destination location.
   * @note - Each block of memory from 'source' is copied to a contiguous location
   *         in 'destination'.
   * @warning - The source and destination locations must NOT overlap.
   */
  tal_fn_attr_inline inline void* tal_memncpy(void* restrict dst, 
      const void* restrict src, const int32_t size, const int32_t n);

  /**
   * @brief Moves a block of memory from one location to annother.
   * @param dst (void*) The destination location
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to move.
   * @returns (void*) The destination location.
   * @note - The source and destination locations MAY overlap.
   */
  tal_fn_attr_inline inline void* tal_memmove(void* dst, const void* src, 
      const int32_t size);

  /**
   * @defgroup tal_memset_ux
   * @brief Sets every block of memory at a location to a specific value.
   * @param mem (void*) The location in memory to set.
   * @param value (unsigned integer denoted by suffix) The value to set.
   * @param cnt (int32_t) The number of values to set (note size varies by type).
   * @returns (void*) The set location in memory.
   * @{
   */
  tal_fn_attr_inline inline void* tal_memset_u8(void* mem, 
      const uint8_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memset_u16(void* mem, 
      const uint16_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memset_u32(void* mem, 
      const uint32_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memset_u64(void* mem, 
      const uint64_t value, const int32_t cnt);
  /** @} */

  /**
   * @brief Swaps the contents of two blocks of memory.
   * @param mem_a (void*) The first block of memory.
   * @param mem_b (void*) The second block of memory.
   * @param size (int32_t) The number of bytes to swap.
   * @warning - The source and destination locations must NOT overlap.
   */
  tal_fn_attr_inline inline void tal_memswap(void* restrict mem_a, 
      void* restrict mem_b, const int32_t size);

  /**
   * @brief Exchanges the contents of a block of memory with annother.
   * @param dst (void*) The destination location.
   * @param xchg (void*) The location to exchange the memory of.
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to exchange.
   * @returns (void*) The exchanged location.
   * @note - This function copies the contents of 'src' to 'xchg', and
   *         copies the old contents of 'xchg' to 'dst'.
   * @warning - The source, destination and exchange locations must not overlap.
   */
  tal_fn_attr_inline inline void* tal_memxchg(void* restrict dst, 
      void* restrict xchg, const void* restrict src, const int32_t size);

  /**
   * @defgroup tal_memxchg_ux
   * @brief Exchanges the contents of a block of memory with a specific value.
   * @param dst (void*) The destination location.
   * @param xchg (void*) The location to exchange the memory of.
   * @param value (unsigned integer denoted by suffix) The value to exchange.
   * @param cnt (int32_t) The number of values to exchange (note size varies by type).
   * @returns (void*) The exchanged location.
   * @note - This function copies the contents of 'value' to 'xchg', and
   *         copies the old contents of 'xchg' to 'dst'.
   * @{
   */
  tal_fn_attr_inline inline void* tal_memxchg_u8(void* dst, void* xchg, 
      const uint8_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memxchg_u16(void* dst, void* xchg, 
      const uint16_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memxchg_u32(void* dst, void* xchg, 
      const uint32_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memxchg_u64(void* dst, void* xchg, 
      const uint64_t value, const int32_t cnt);
  /** @} */

  /**
   * @brief Compares two blocks of memory for equality.
   * @param mem_a (const void*) The first block of memory.
   * @param mem_b (const void*) The second block of memory.
   * @param size (int32_t) The number of bytes to compare.
   * @returns (bool) True if every bit in 'mem_a' is equal to the
   *          corresponding bit in 'mem_b', or false otherwise.
   * @note - 'mem_a' and 'mem_b' may overlap.
   */
  tal_fn_attr_inline inline bool tal_memcmp(const void* mem_a, 
      const void* mem_b, const int32_t size);

  /**
   * @brief Compares two blocks of memory for equality, n times.
   * @param mem_a (const void*) The first block of memory.
   * @param mem_b (const void*) The second block of memory.
   * @param size (int32_t) The number of bytes to compare.
   * @param n (int32_t) The number of times to compare 'mem_b' to 'mem_a'.
   * @returns (bool) True if every 'size' bytes in 'mem_a' is equal to
   *          'mem_b', or false otherwise.
   * @note - 'mem_a' and 'mem_b' may overlap.
   */
  tal_fn_attr_inline inline bool tal_memncmp(const void* restrict mem_a, 
      const void* restrict mem_b, const int32_t size, const int32_t n);

  /**
   * @defgroup tal_memcmp_ux
   * @brief Compares every (suffix) bytes in a block of memory to a specific value.
   * @param mem (const void*) The block of memory to compare.
   * @param value (unsigned integer denoted by suffix) The value to compare.
   * @param cnt (int32_t) The number of values to compare (note size varies by type).
   * @returns (bool) True if every (suffix) bytes in 'mem' is equal to 'value',
   *          or false otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_memcmp_u8(const void* mem, 
      const uint8_t value, const int32_t cnt);
  tal_fn_attr_inline inline bool tal_memcmp_u16(const void* mem, 
      const uint16_t value, const int32_t cnt);
  tal_fn_attr_inline inline bool tal_memcmp_u32(const void* mem, 
      const uint32_t value, const int32_t cnt);
  tal_fn_attr_inline inline bool tal_memcmp_u64(const void* mem, 
      const uint64_t value, const int32_t cnt);
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
  tal_fn_attr_inline inline void* tal_memmem(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize);

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
  tal_fn_attr_inline inline void* tal_memrmem(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize);

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
  tal_fn_attr_inline inline void* tal_memnmem(const void* mem, const void* fmem, 
      const int32_t size, const int32_t fsize, const int32_t n);

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
  tal_fn_attr_inline inline void* tal_memval8(const void* mem, 
      const uint8_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memval16(const void* mem, 
      const uint16_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memval32(const void* mem, 
      const uint32_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memval64(const void* mem, 
      const uint64_t value, const int32_t cnt);
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
  tal_fn_attr_inline inline void* tal_memrval8(const void* mem, 
      const uint8_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memrval16(const void* mem, 
      const uint16_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memrval32(const void* mem, 
      const uint32_t value, const int32_t cnt);
  tal_fn_attr_inline inline void* tal_memrval64(const void* mem, 
      const uint64_t value, const int32_t cnt);
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
  tal_fn_attr_inline inline void* tal_memnval8(const void* mem, 
      const uint8_t value, const int32_t cnt, const int32_t n);
  tal_fn_attr_inline inline void* tal_memnval16(const void* mem, 
      const uint16_t value, const int32_t cnt, const int32_t n);
  tal_fn_attr_inline inline void* tal_memnval32(const void* mem, 
      const uint32_t value, const int32_t cnt, const int32_t n);
  tal_fn_attr_inline inline void* tal_memnval64(const void* mem, 
      const uint64_t value, const int32_t cnt, const int32_t n);
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
  tal_fn_attr_inline inline int32_t tal_memmem_i(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize);

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
  tal_fn_attr_inline inline int32_t tal_memrmem_i(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize);

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
  tal_fn_attr_inline inline int32_t tal_memnmem_i(const void* mem, 
      const void* fmem, const int32_t size, const int32_t fsize, const int32_t n);

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
  tal_fn_attr_inline inline int32_t tal_memval8_i(void* mem, 
      const uint8_t value, const int32_t cnt);
  tal_fn_attr_inline inline int32_t tal_memval16_i(void* mem, 
      const uint16_t value, const int32_t cnt);
  tal_fn_attr_inline inline int32_t tal_memval32_i(void* mem, 
      const uint32_t value, const int32_t cnt);
  tal_fn_attr_inline inline int32_t tal_memval64_i(void* mem, 
      const uint64_t value, const int32_t cnt);
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
  tal_fn_attr_inline inline int32_t tal_memrval8_i(void* mem, 
      const uint8_t value, const int32_t cnt);
  tal_fn_attr_inline inline int32_t tal_memrval16_i(void* mem, 
      const uint16_t value, const int32_t cnt);
  tal_fn_attr_inline inline int32_t tal_memrval32_i(void* mem, 
      const uint32_t value, const int32_t cnt);
  tal_fn_attr_inline inline int32_t tal_memrval64_i(void* mem, 
      const uint64_t value, const int32_t cnt);
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
  tal_fn_attr_inline inline int32_t tal_memnval8_i(void* mem, 
      const uint8_t value, const int32_t cnt, const int32_t n);
  tal_fn_attr_inline inline int32_t tal_memnval16_i(void* mem, 
      const uint16_t value, const int32_t cnt, const int32_t n);
  tal_fn_attr_inline inline int32_t tal_memnval32_i(void* mem, 
      const uint32_t value, const int32_t cnt, const int32_t n);
  tal_fn_attr_inline inline int32_t tal_memnval64_i(void* mem, 
      const uint64_t value, const int32_t cnt, const int32_t n);
  /** @} */

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  void* tal_memcpy(void* restrict dst, const void* restrict src, 
      const int32_t size) {
    if (dst && src && size > 0) {
      uint8_t *d = dst;
      const uint8_t *s = src;
      for (int32_t i = 0; i < size; ++i) { d[i] = s[i]; }
    }
    return dst;
  }

  void* tal_memncpy(void* restrict dst, const void* restrict src,
      const int32_t size, const int32_t n) {
    if (dst && src && size > 0 && n > 0) {
      uint8_t *d = dst;
      const uint8_t *s = src;
      for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = 0; j < size; ++j) { d[j * i] = s[j]; }
      }
    }
    return dst;
  }

  void* tal_memmove(void* dst, const void* src, const int32_t size) {
    if (dst && src && size > 0) {
      uint8_t *d = dst;
      const uint8_t *s = src;
      if (d <= s) {
        for (int32_t i = 0; i < size; ++i) { d[i] = s[i]; }
      } else {
        for (int32_t i = size - 1; i >= 0; --i) { d[i] = s[i]; }
      }
    }
    return dst;
  }

  void* tal_memset_u8(void* mem, const uint8_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      uint8_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_memset_u16(void* mem, const uint16_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      uint16_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_memset_u32(void* mem, const uint32_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      uint32_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_memset_u64(void* mem, const uint64_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      uint64_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void tal_memswap(void* restrict mem_a, void* restrict mem_b, 
      const int32_t size) {
    if (mem_a && mem_b && size > 0) {
      uint8_t *a = mem_a;
      uint8_t *b = mem_b;
      for(int32_t i = 0; i < size; ++i){
        uint8_t tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
      }
    }
  }

  void* tal_memxchg(void* restrict dst, void* restrict xchg, 
      const void* restrict src, const int32_t size) {
    if (dst && xchg && src && size > 0) {
      uint8_t *d = dst;
      uint8_t *x = xchg;
      const uint8_t *s = src;
      for (int32_t i = 0; i < size; ++i) {
        uint8_t tmp = x[i];
        x[i] = s[i];
        d[i] = tmp;
      }
    }
    return xchg;
  }

  void* tal_memxchg_u8(void* dst, void* xchg, const uint8_t value, 
      const int32_t cnt) {
    if (dst && xchg && cnt > 0) {
      uint8_t *d = dst;
      uint8_t *x = xchg;
      for (int32_t i = 0; i < cnt; ++i) {
        uint8_t tmp = x[i];
        x[i] = value;
        d[i] = tmp;
      }
    }
    return xchg;
  }

  void* tal_memxchg_u16(void* dst, void* xchg, const uint16_t value, 
      const int32_t cnt) {
    if (dst && xchg && cnt > 0) {
      uint16_t *d = dst;
      uint16_t *x = xchg;
      for (int32_t i = 0; i < cnt; ++i) {
        uint16_t tmp = x[i];
        x[i] = value;
        d[i] = tmp;
      }
    }
    return xchg;
  }

  void* tal_memxchg_u32(void* dst, void* xchg, const uint32_t value, 
      const int32_t cnt) {
    if (dst && xchg && cnt > 0) {
      uint32_t *d = dst;
      uint32_t *x = xchg;
      for (int32_t i = 0; i < cnt; ++i) {
        uint32_t tmp = x[i];
        x[i] = value;
        d[i] = tmp;
      }
    }
    return xchg;
  }

  void* tal_memxchg_u64(void* dst, void* xchg, const uint64_t value, 
      const int32_t cnt) {
    if (dst && xchg && cnt > 0) {
      uint64_t *d = dst;
      uint64_t *x = xchg;
      for (int32_t i = 0; i < cnt; ++i) {
        uint64_t tmp = x[i];
        x[i] = value;
        d[i] = tmp;
      }
    }
    return xchg;
  }

  bool tal_memcmp(const void* mem_a, const void* mem_b, const int32_t size) {
    if (!mem_a || !mem_b || size <= 0) { return false; }
    const uint8_t *a = mem_a;
    const uint8_t *b = mem_b;
    for (int32_t i = 0; i < size; ++i) {
      if (a[i] != b[i]) { return false; }
    }
    return true;
  }

  bool tal_memncmp(const void* mem_a, const void* mem_b, const int32_t size, 
      const int32_t n) {
    if (!mem_a || !mem_b || size <= 0 && n <= 0) { return false; }
    const uint8_t *a = mem_a;
    const uint8_t *b = mem_b;
    for (int32_t i = 0; i < n; ++i) {
      for (int32_t j = 0; j < size; ++j) {
        if (a[j * i] != b[j]) { return false; }
      }
    }
    return true;
  }

  bool tal_memcmp_u8(const void* mem, const uint8_t value, const int32_t cnt) {
    if (!mem || cnt <= 0) { return false; }
    const uint8_t *m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_memcmp_u16(const void* mem, const uint16_t value, const int32_t cnt) {
    if (!mem || cnt <= 0) { return false; }
    const uint16_t *m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_memcmp_u32(const void* mem, const uint32_t value, const int32_t cnt) {
    if (!mem || cnt <= 0) { return false; }
    const uint32_t *m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_memcmp_u64(const void* mem, const uint64_t value, const int32_t cnt) {
    if (!mem || cnt <= 0) { return false; }
    const uint64_t *m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  void* tal_memmem(const void* mem, const void* fmem, const int32_t size, 
      const int32_t fsize) {
    if (mem && fmem && size > 0 && fsize > 0) {
      int32_t fi = 0;
      const uint8_t *m = mem;
      const uint8_t *f = fmem;
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

  void* tal_memrmem(const void* mem, const void* fmem, const int32_t size, 
      const int32_t fsize) {
    if (mem && fmem && size > 0 && fsize > 0) {
      int32_t fi = fsize - 1;
      const uint8_t *m = mem;
      const uint8_t *f = fmem;
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

  void* tal_memnmem(const void* mem, const void* fmem, const int32_t size, 
      const int32_t fsize, const int32_t n) {
    if (mem && fmem && size > 0 && fsize > 0) {
      int32_t fi = 0;
      int32_t fcnt = 0;
      const uint8_t *m = mem;
      const uint8_t *f = fmem;
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

  void* tal_memval8(const void* mem, const uint8_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint8_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_memval16(const void* mem, const uint16_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint16_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_memval32(const void* mem, const uint32_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint32_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_memval64(const void* mem, const uint64_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint64_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_memrval8(const void* mem, const uint8_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint8_t *m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_memrval16(const void* mem, const uint16_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint16_t *m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_memrval32(const void* mem, const uint32_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint32_t *m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_memrval64(const void* mem, const uint64_t value, const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint64_t *m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }


  void* tal_memnval8(const void* mem, const uint8_t value, 
      const int32_t cnt, const int32_t n) {
    if (mem && cnt > 0) {
      int32_t cur_cnt = 0;
      const uint8_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_memnval16(const void* mem, const uint16_t value, 
      const int32_t cnt, const int32_t n) {
    if (mem && cnt > 0) {
      int32_t cur_cnt = 0;
      const uint16_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_memnval32(const void* mem, const uint32_t value, 
      const int32_t cnt, const int32_t n) {
    if (mem && cnt > 0) {
      int32_t cur_cnt = 0;
      const uint32_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_memnval64(const void* mem, const uint64_t value, 
      const int32_t cnt, const int32_t n) {
    if (mem && cnt > 0) {
      int32_t cur_cnt = 0;
      const uint64_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  int32_t tal_memmem_i(const void* mem, const void* fmem, 
      const int32_t size, const int32_t fsize) {
    if (mem && fmem && size > 0 && fsize > 0) {
      int32_t fi = 0;
      const uint8_t *m = mem;
      const uint8_t *f = fmem;
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

  int32_t tal_memrmem_i(const void* mem, const void* fmem, 
      const int32_t size, const int32_t fsize) {
    if (mem && fmem && size > 0 && fsize > 0) {
      int32_t fi = fsize - 1;
      const uint8_t *m = mem;
      const uint8_t *f = fmem;
      for (int32_t i = size - 1; i >= 0; --i) {
        if (m[i] == f[fi]) {
          --fi;
          if (!fi) { return i + fsize; }
        } else { 
          fi = 0;
        }
      }
    }
    return -1;
  }

  int32_t tal_memnmem_i(const void* mem, const void* fmem, 
      const int32_t size, const int32_t fsize, const int32_t n) {
    if (mem && fmem && size > 0 && fsize > 0) {
      int32_t fi = 0;
      int32_t fcnt = 0;
      const uint8_t *m = mem;
      const uint8_t *f = fmem;
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

  int32_t tal_memval8_i(void* mem, const uint8_t value, 
      const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint8_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_memval16_i(void* mem, const uint16_t value, 
      const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint16_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_memval32_i(void* mem, const uint32_t value, 
      const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint32_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_memval64_i(void* mem, const uint64_t value, 
      const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint64_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }
  
  int32_t tal_memrval8_i(void* mem, const uint8_t value, 
      const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint8_t *m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_memrval16_i(void* mem, const uint16_t value, 
      const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint16_t *m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_memrval32_i(void* mem, const uint32_t value, 
      const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint32_t *m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_memrval64_i(void* mem, const uint64_t value, 
      const int32_t cnt) {
    if (mem && cnt > 0) {
      const uint64_t *m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }
  
  int32_t tal_memnval8_i(void* mem, const uint8_t value, 
      const int32_t cnt, const int32_t n) {
    if (mem && cnt > 0) {
      int32_t cur_cnt = 0;
      const uint8_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_memnval16_i(void* mem, const uint16_t value, 
      const int32_t cnt, const int32_t n) {
    if (mem && cnt > 0) {
      int32_t cur_cnt = 0;
      const uint16_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_memnval32_i(void* mem, const uint32_t value, 
      const int32_t cnt, const int32_t n) {
    if (mem && cnt > 0) {
      int32_t cur_cnt = 0;
      const uint32_t *m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_memnval64_i(void* mem, const uint64_t value, 
      const int32_t cnt, const int32_t n) {
    if (mem && cnt > 0) {
      int32_t cur_cnt = 0;
      const uint64_t *m = mem;
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