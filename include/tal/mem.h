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
 * @note API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/common/attributes.h" // for inline attribute
#include "include/tal/tmp.h" // for dummy error flag

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Memory Manipulation Utilities
   **************************************************************************************************/

  /**
   * @brief Copies a block of memory from one location to annother.
   * @param dst (void*) The destination location
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to copy.
   * @param err (bool*) The error flag. Accessed and set true if 'size' is 
   *            negative, 'dst' or 'src' is NULL/out of bounds, or an internal
   *            error occurs.
   * @returns (void*) 'dst'.
   * @note - This function copies every byte from 'src' to contiguous bytes
   *         starting at 'dst'.
   * @note - This function has no side effects if an error occurs.
   * @note - The source and destination locations may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_copy(void* const dst, 
      const void* const src, const int32_t size, bool* const err);

  /**
   * @brief Copies a block of memory from one location to annother, n times.
   * @param dst (void*) The destination location.
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of byte to copy.
   * @param n (int32_t) The number of times to copy 'src'.
   * @param err (bool*) The error flag. Accessed and set true if 'size' or 'n'
   *            is negative, 'dst' or 'src' is NULL/out of bounds, or an internal
   *            error occurs.
   * @returns (void*) 'dst'.
   * @note - This function copies every byte in 'src' to contiguous bytes in
   *         'dst', 'n' times.
   * @note - This function has no side effects if an error occurs.
   * @note - The source and destination locations may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_copyn(void* const dst, 
      const void* const src, const int32_t size, const int32_t n, 
      bool* const err);

  /**
   * @brief Inserts a block of memory into annother block of memory.
   * @param dst (void*) The destination location.
   * @param src (const void*) The source location.
   * @param dst_size (int32_t) The size of the destination block.
   * @param off (int32_t) The offset in bytes from the start of 'dst' where
   *            'src' should be inserted.
   * @param src_size (int32_t) The size of the source block.
   * @param err (bool*) The error flag. Accessed and set true if 'dst_size', 
   *            'src_size', or 'off' is negative, 'dst' and 'src' overlap, or are 
   *             NULL/out of bounds, or an internal error occurs.
   * @note - This function copies every byte in 'src' to contiguous bytes in
   *         'dst' and shifts all overwritten byte in 'dst' to higher addresses.
   * @note - This function has no side effects if an error occurs.
   * @note - 'dst' and 'src' must NOT overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_insert(void* const restrict dst,
      const void* const restrict src, const int32_t dst_size, const int32_t off,
      const int32_t src_size, bool* const err);

  /**
   * @brief Inserts a block of memory into annother block of memory, n times.
   * @param dst (void*) The destination location.
   * @param src (const void*) The source location.
   * @param dst_size (int32_t) The size of the destination block.
   * @param off (int32_t) The offset in bytes from the start of 'dst' where
   *            'src' should be inserted.
   * @param src_size (int32_t) The size of the source block.
   * @param n (int32_t) The number of times to insert 'src' into 'dst'.
   * @param err (bool*) The error flag. Accessed and set true if 'dst' or 'src'
   *            is NULL/out of bounds, 'dst_size', 'src_size', 'off', or 'n' is 
   *            negative, or an internal error occurs.
   * @returns (void*) 'dst'.
   * @note - This function copies every byte in 'src' to contiguous bytes in
   *         'dst' 'n' times, and shifts all overwritten byte in 'dst' to 
   *         higher addresses.
   * @note - This function has no side effects if an error occurs.
   * @note - 'dst' and 'src' must NOT overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_insertn(void* const restrict dst,
      const void* const restrict src, const int32_t dst_size, const int32_t off,
      const int32_t src_size, const int32_t n, bool* const err);

  /**
   * @brief Clears all data from a block of memory.
   * @param mem (void*) The memory location to clear.
   * @param size (int32_t) The number of bytes to clear.
   * @param err (bool*) The error flag. Accessed and set true if 'size' is
   *            negative, 'mem' is NULL/out of bounds, or an internal error 
   *            occurs.
   * @returns (void*) 'mem'.
   * @note - This function sets every byte in 'mem' to zero.
   * @note - This function has no side effects if an error occurs.
   */
  tal_fn_attr_inline inline void* tal_mem_clear(void* const mem,
      const int32_t size, bool* const err);

  /**
   * @brief Swaps the contents of two blocks of memory.
   * @param mem_a (void*) The first block of memory.
   * @param mem_b (void*) The second block of memory.
   * @param size (int32_t) The number of bytes to swap.
   * @param err (bool*) The error flag. Accessed and set true if 'size' is
   *            negative, 'mem_a' and 'mem_b' overlap or are NULL/out of bounds,
   *            or an internal error occurs.
   * @note - This function swaps every byte in 'mem_a' with the corresponding
   *         byte in 'mem_b'.
   * @note - This function has no side effects if an error occurs.
   */
  tal_fn_attr_inline inline void tal_mem_swap(void* const restrict mem_a, 
      void* const restrict mem_b, const int32_t size, bool* const err);

  /**************************************************************************************************
   * @section Memory Comparison Utilities
   **************************************************************************************************/

  /**
   * @brief Compares two blocks of memory for equality.
   * @param mem_a (const void*) The first block of memory.
   * @param mem_b (const void*) The second block of memory.
   * @param size (int32_t) The number of bytes to compare.
   * @param err (bool*) The error flag. Accessed and set true if 'size' is 
   *            negative, 'mem_a' or 'mem_b' is NULL/out of bounds, or an
   *            internal error occurs.
   * @returns (bool) True if no error occurs, and every bit in 'mem_a' is equal 
   *          to it's corresponding bit in 'mem_b', or false otherwise.
   * @note - If no bits are compared, this function returns true ('size' == 0).
   * @note - 'mem_a' and 'mem_b' may overlap.
   */
  tal_fn_attr_inline inline bool tal_mem_cmp(const void* const mem_a, 
      const void* const mem_b, const int32_t size, bool* const err);

  /**
   * @brief Compares a block of memory to annother for equality, n times.
   * @param mem_a (const void*) The first block of memory.
   * @param mem_b (const void*) The second, block of memory (repeated).
   * @param size (int32_t) The number of bytes to compare.
   * @param n (int32_t) The number of times to compare 'mem_b' to 'mem_a'.
   * @param err (bool*) The error flag. Accessed and set true if 'size' or 'n'
   *            is negative, 'mem_a' or 'mem_b' is NULL/out of bounds, or an
   *            internal error occurs.
   * @returns (bool) True if no error occurs and 'size' bytes of 'mem_b' are 
   *          equal to 'n' contiguous blocks in 'mem_a', or false otherwise.
   * @note - 'mem_a' and 'mem_b' may overlap.
   */
  tal_fn_attr_inline inline bool tal_mem_cmpn(const void* const mem_a, 
      const void* const mem_b, const int32_t size, const int32_t n, 
      bool* const err);

  /**************************************************************************************************
   * @section Memory Search Utilities
   **************************************************************************************************/

  /**
   * @brief Gets a pointer to the first location in a block of memory that
   *        is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @param err (bool*) The error flag. Accessed and set true if 'size' or
   *            'fsize' is negative, 'mem' or 'fmem' is NULL/out of bounds,
   *            or an internal error occurs.
   * @returns (void*) A pointer to the start of the first location in 'mem'
   *          that contains 'fsize' bytes which are equal to 'fmem', or
   *          NULL if no such location exists, or an error occurs.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_get(const void* const mem, 
      const void* const fmem, const int32_t size, const int32_t fsize, 
      bool* const err);

  /**
   * @brief Gets a pointer to the last location in a block of memory that 
   *        is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @param err (bool*) The error flag. Accessed and set true if 'size' or
   *            'fsize' is negative, 'mem' or 'fmem' is NULL/out of bounds,
   *            or an internal error occurs.
   * @returns (void*) A pointer to the start of the last location in 'mem' that 
   *          contains 'fsize' bytes which are equal to 'fmem', or NULL if no 
   *          such location exists or an error occurs.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_getr(const void* const mem, 
      const void* const fmem, const int32_t size, const int32_t fsize, 
      bool* const err);

  /**
   * @brief Gets a pointer to the nth location in a block of memory that
   *        is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @param n (int32_t) The index of the matching location to get.
   * @param err (bool*) The error flag. Accessed and set true if 'size', 'fsize',
   *           or 'n' is negative, 'mem' or 'fmem' is NULL/out of bounds,
   *           or an internal error occurs.
   * @returns (void*) A pointer to the start of the nth location in 'mem' that 
   *          contains 'fsize' bytes which are equal to 'fmem', or NULL if no 
   *          such location exists or an error occurs.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline void* tal_mem_getn(const void* const mem, 
      const void* const fmem, const int32_t size, const int32_t fsize, 
      const int32_t n, bool* const err);

  /**
   * @brief Gets the byte offset of the first location in a block of memory
   *        that is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @param err (bool*) The error flag. Accessed and set true if 'size' or
   *            'fsize' is negative, 'mem' or 'fmem' is NULL/out of bounds,
   *            or an internal error occurs.
   * @returns (int32_t) The byte offset of the first location in 'mem' that 
   *          contains 'fsize' bytes which are equal to 'fmem', or -1 if no 
   *          such location exists or an error occurs.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_mem_index(const void* const mem, 
      const void* const fmem, const int32_t size, const int32_t fsize, 
      bool* const err);

  /**
   * @brief Gets the byte offset of the last location in a block of memory
   *        that is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @param err (bool*) The error flag. Accessed and set true if 'size' or
   *            'fsize' is negative, 'mem' or 'fmem' is NULL/out of bounds,
   *            or an internal error occurs.
   * @returns (int32_t) The byte offset of the last location in 'mem' that 
   *          contains 'fsize' bytes which are equal to 'fmem', or -1 if no 
   *          such location exists, or an error occurs.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_mem_indexr(const void* const mem, 
      const void* const fmem, const int32_t size, const int32_t fsize, 
      bool* const err);

  /**
   * @brief Gets the byte offset of the nth location in a block of memory
   *        that is the same as annother block of memory.
   * @param mem (const void*) The memory location to search within.
   * @param fmem (const void*) The memory block to find in 'mem'.
   * @param size (int32_t) The total number of bytes to search in 'mem'.
   * @param fsize (int32_t) The number of bytes in 'fmem'.
   * @param n (int32_t) The index of the matching location to get.
   * @param err (bool*) The error flag. Accessed and set true if 'size', 'fsize',
   *            or 'n' is negative, 'mem' or 'fmem' are NULL/out of bounds,
   *            or an internal error occurs.
   * @returns (int32_t) The byte offset of the nth location in 'mem' that 
   *          contains 'fsize' bytes which are equal to 'fmem', or -1 if no 
   *          such location exists, or an error occurs.
   * @note - 'mem' and 'fmem' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_mem_indexn(const void* const mem, 
      const void* const fmem, const int32_t size, const int32_t fsize, 
      const int32_t n, bool* const err);

  /**************************************************************************************************
   * @internal Helper Functions
   **************************************************************************************************/

  // Determines if two memory regions overlap
  static bool mem_overlap(const void* const mem_a, const void* const mem_b,
      const int32_t a_size, const int32_t b_size) {
    const uint64_t a_addr = (uint64_t)mem_a;
    const uint64_t b_addr = (uint64_t)mem_b;
    return (a_addr < b_addr ? (a_addr + (uint64_t)a_size) >= b_addr : 
        (b_addr + (uint64_t)b_size) > a_addr);
  }

  // Determines if a memory region is out of bounds
  static bool mem_oob(const void* const mem, const int32_t size) {
    const uintptr_t addr = (uintptr_t)mem;
    return addr > (UINTPTR_MAX - (uint32_t)size);
  }

  /**************************************************************************************************
   * @internal Implementation of Memory Manipulation Utilities
   **************************************************************************************************/

  void* tal_mem_copy(void* dst, const void* src, const int32_t size, 
      bool* const err) {
    if (!dst || !src || size < 0 ||
        mem_oob(dst, size) || mem_obb(src, size)) {
      *err = true;
    } else {
      uint8_t* const d_byte = dst;
      const uint8_t* const s_byte = src;
      const uint64_t dst_addr = (uint64_t)dst;
      const uint64_t src_addr = (uint64_t)src;
      if (dst_addr <= src_addr) {
        for (int32_t i = 0; i < size; ++i) { 
          d_byte[i] = s_byte[i];
        }
      } else {
        for (int32_t i = size - 1; i >= 0; --i) { 
          d_byte[i] = s_byte[i]; 
        }
      }
    }
    return dst;
  }

  void* tal_mem_copyn(void* dst, const void* src, const int32_t size, 
      const int32_t n, bool* const err) {
    if (!dst || !src || n < 0 || size < 0 || 
        (n != 0 && size > (INT32_MAX / n)) ||
        mem_oob(dst, size * n) || mem_oob(src, size)) {
      *err = true;
    } else {
      uint8_t* const d_byte = dst;
      const uint8_t* const s_byte = src;
      const uint64_t dst_addr = (uint64_t)dst;
      const uint64_t src_addr = (uint64_t)src;
      if (dst_addr <= src_addr) {
        for (int32_t i = 0; i < n; ++i) {
          for (int32_t j = 0; j < size; ++j) { 
            d_byte[(i * size) + j] = s_byte[j]; 
          }
        }
      } else {
        for (int32_t i = n - 1; i >= 0; --i) {
          for (int32_t j = size - 1; j >= 0; --j) { 
            d_byte[(i * size) + j] = s_byte[j]; 
          }
        }
      }
    }
    return dst;
  }

  void* tal_mem_insert(void* const restrict dst, const void* const restrict src, 
      const int32_t dst_size, const int32_t off, const int32_t src_size, 
      bool* const err) {
    if (!dst || !src || dst_size < 0 || off < 0 || 
        src_size < 0 || off > dst_size || 
        (dst_size - off) > (INT32_MAX - src_size) ) {
      *err = true;
    } else {
      const int32_t dst_span = (dst_size - off) + src_size;
      if (mem_oob(dst, dst_span) || mem_oob(src, src_size) ||
          mem_overlap(dst + off, src, dst_span, src_size)) {
        *err = true;
      } else {
        uint8_t* const d_byte = dst;
        const uint8_t* const s_byte = src;
        for (int32_t i = dst_size - 1; i >= off; --i) {
          d_byte[src_size + i] = d_byte[i];
        }
        for (int32_t i = 0; i < src_size; ++i) {
          d_byte[off + i] = s_byte[i];
        }
      }
    }
    return dst;
  }

  void* tal_mem_insertn(void* const restrict dst, const void* const restrict src, 
      const int32_t dst_size, const int32_t off, const int32_t src_size, 
      const int32_t n, bool* const err) {
    if (!dst || !src || dst_size < 0 || off < 0 ||
        src_size < 0 || n < 0 || off > dst_size ||
        (n != 0 && src_size > (INT32_MAX / n)) ||
        (dst_size - off) > (INT32_MAX - (src_size * n))) {
      *err = true;
    } else {
      const int32_t dst_span = (dst_size - off) + (n * src_size);
      if (mem_oob(dst, dst_span) || mem_oob(src, src_size) ||
          mem_overlap(dst + off, src, dst_span, src_size)) {
        *err = true;
      } else {
        uint8_t* const d_byte = dst;
        const uint8_t* const s_byte = src;
        for (int32_t i = dst_size - 1; i >= off; --i) {
          d_byte[(src_size * n) + i] = d_byte[i];
        }
        for (int32_t i = 0; i < n; ++i) {
          for (int32_t j = 0; j < src_size; ++j) {
            d_byte[off + (i * src_size) + j] = s_byte[j];
          }
        }
      }
    }
    return dst;
  }
  
  void* tal_mem_clear(void* const mem, const int32_t size, bool* const err) {
    if (!mem || size < 0 || mem_oob(mem, size)) {
      *err = true;
    } else {
      uint8_t* const m_byte = mem;
      for (int32_t i = 0; i < size; ++i) {
        m_byte[i] = 0;
      }
    }
    return mem;
  }

  void tal_mem_swap(void* const restrict mem_a, void* const restrict mem_b,
      const int32_t size, bool* const err) {
    if (!mem_a || !mem_b || size < 0 ||
        mem_oob(mem_a, size) || mem_oob(mem_b, size) ||
        mem_overlap(mem_a, mem_b, size, size)) {
      *err = true;
    } else {
      uint8_t* const a_byte = mem_a;
      uint8_t* const b_byte = mem_b;
      for(int32_t i = 0; i < size; ++i){
        uint8_t tmp = a_byte[i];
        a_byte[i] = b_byte[i];
        b_byte[i] = tmp;
      }
    }
  }

  /**************************************************************************************************
   * @internal Implementation of Memory Comparison Utilities
   **************************************************************************************************/

  bool tal_mem_cmp(const void* const mem_a, const void* const mem_b, 
      const int32_t size, bool* const err) {
    if (!mem_a || !mem_b || size < 0 ||
        mem_oob(mem_a, size) || mem_oob(mem_b, size)) {
      *err = true;
      return false;
    } 
    const uint8_t* const a_byte = mem_a;
    const uint8_t* const b_byte = mem_b;
    for (int32_t i = 0; i < size; ++i) {
      if (a_byte[i] != b_byte[i]) { return false; }
    }
    return true;
  }

  bool tal_mem_cmpn(const void* const mem_a, const void* const mem_b, 
      const int32_t size, const int32_t n, bool* const err) {
    if (!mem_a || !mem_b || size < 0 || n < 0 ||
        (n != 0 && size > (INT32_MAX / n)) ||
        mem_oob(mem_a, (size * n)) || mem_oob(mem_b, size)) {
      *err = true;
      return false;
    }
    const uint8_t* a_byte = mem_a;
    const uint8_t* b_byte = mem_b;
    for (int32_t i = 0; i < n; ++i) {
      const int32_t i_off = i * size;
      for (int32_t j = 0; j < size; ++j) {
        if (a_byte[i_off + j] != b_byte[j]) { return false; }
      }
    }
    return true;
  }

  /**************************************************************************************************
   * @internal Implementation of Memory Search Utilities
   **************************************************************************************************/

  void* tal_mem_get(const void* const mem, const void* const fmem, 
      const int32_t size, const int32_t fsize, bool* const err) {
    if (!mem || !fmem || size < 0 || fsize < 0 || fsize > size ||
        mem_oob(mem, size) || mem_oob(fmem, fsize)) {
      *err = true;
    } else {
      int32_t f_index = 0;
      const uint8_t* const m_byte = mem;
      const uint8_t* const f_byte = fmem;
      for (int32_t i = 0; i < size; ++i) {
        if (m_byte[i] == f_byte[f_index]) {
          ++f_index;
          if (f_index >= fsize) { 
            return (void*)mem + (i - fsize); 
          }
        } else { 
          f_index = 0;
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getr(const void* const mem, const void* const fmem, 
      const int32_t size, const int32_t fsize, bool* const err) {
    if (!mem || !fmem || size < 0 || fsize < 0 || fsize > size ||
        mem_oob(mem, size) || mem_oob(fmem, fsize)) {
      *err = true;
    } else {
      int32_t f_index = fsize - 1;
      const uint8_t* const m_byte = mem;
      const uint8_t* const f_byte = fmem;
      for (int32_t i = size - 1; i >= 0; --i) {
        if (m_byte[i] == f_byte[f_index]) {
          --f_index;
          if (f_index <= 0) { 
            return (void*)mem + i; 
          }
        } else { 
          f_index = fsize - 1;
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getn(const void* const mem, const void* const fmem, 
      const int32_t size, const int32_t fsize, const int32_t n, 
      bool* const err) {
    if (!mem || !fmem || size < 0 || fsize < 0 || n < 0 || 
        fsize > size || mem_oob(mem, size) || mem_oob(fmem, fsize)) {
      *err = true;
    } else {
      int32_t fcnt = 0;
      int32_t f_index = 0;
      const uint8_t* const m_byte = mem;
      const uint8_t* const f_byte = fmem;
      for (int32_t i = 0; i < size; ++i) {
        if (m_byte[i] == f_byte[f_index]) {
          ++f_index;
          if (f_index >= fsize) {
            ++fcnt;
            if (fcnt >= n) { 
              return (void*)mem + (i - fsize); 
            }
          }
        } else {
          f_index = 0;
        }
      }
    }
    return NULL;
  }

  int32_t tal_mem_index(const void* const mem, const void* const fmem, 
      const int32_t size, const int32_t fsize, bool* const err) {
    if (!mem || !fmem || size < 0 || fsize < 0 || fsize > size ||
        mem_oob(mem, size) || mem_oob(fmem, fsize)) {
      *err = true;
    } else {
      int32_t f_index = 0;
      const uint8_t* const m_byte = mem;
      const uint8_t* const f_byte = fmem;
      for (int32_t i = 0; i < size; ++i) {
        if (m_byte[i] == f_byte[f_index]) {
          ++f_index;
          if (f_index >= fsize) { return i - fsize; }
        } else { 
          f_index = 0;
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexr(const void* const mem, const void* const fmem, 
      const int32_t size, const int32_t fsize, bool* const err) {
    if (!mem || !fmem || size < 0 || fsize < 0 || fsize > size ||
        mem_oob(mem, size) || mem_oob(fmem, fsize)) {
      *err = true;
    } else {
      int32_t f_index = fsize - 1;
      const uint8_t* const m_byte = mem;
      const uint8_t* const f_byte = fmem;
      for (int32_t i = size - 1; i >= 0; --i) {
        if (m_byte[i] == f_byte[f_index]) {
          --f_index;
          if (!f_index) { return i; }
        } else { 
          f_index = fsize - 1;
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn(const void* const mem, const void* const fmem, 
      const int32_t size, const int32_t fsize, const int32_t n, bool* const err) {
    if (!mem || !fmem || size < 0 || fsize < 0 || n < 0 ||
        fsize > size || mem_oob(mem, size) || mem_oob(fmem, fsize)) {
      *err = true;
    } else {
      int32_t fcnt = 0;
      int32_t f_index = 0;
      const uint8_t* const m_byte = mem;
      const uint8_t* const f_byte = fmem;
      for (int32_t i = 0; i < size; ++i) {
        if (m_byte[i] == f_byte[f_index]) {
          ++f_index;
          if (f_index >= fsize) {
            ++fcnt;
            if (fcnt >= n) { return i - fsize; }
          }
        } else {
          f_index = 0;
        }
      }
    }
    return -1;
  }

#if defined(__cplusplus)
  }
#endif