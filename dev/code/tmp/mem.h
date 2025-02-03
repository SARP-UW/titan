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
 * @file src/common/util/mem.h
 * @authors Aaron McBride
 * @brief Memory utilities.
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
   * @section Memory Manipulation Utilities
   **********************************************************************************************/

  /**
   * @brief Copies a block of memory.
   * @param dst (void*) The destination location.
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to copy.
   * @returns (void*) The given destination pointer - @p [dst].
   * @note - If @p [src] or @p [dst] is NULL, or @p [size] is less than 1,
   *         this function has no side effects.
   * @note - dst and src may overlap.
   */
  inline void* mem_copy(void* dst, const void* src, int32_t size);

  /**
   * @brief Sets a block of memory to a given value.
   * @param dst (void*) The destination location.
   * @param size (int32_t) The number of bytes to set.
   * @param value (uint8_t) The value to set each byte to.
   * @returns (void*) The given destination pointer - @p [dst].
   * @note - If @p [dst] is NULL or @p [size] is less than 1, this function
   *         has no side effects.
   */
  inline void* mem_fill(void* dst, int32_t size, uint8_t value);

  /// @todo
  inline void mem_swap(void* mem1, void* mem2, int32_t size);

  /**********************************************************************************************
   * @section Memory Inspection Utilities
   **********************************************************************************************/

  /**s
   * @brief Compares two blocks of memory.
   * @param mem1 (const void*) The first block of memory.
   * @param mem2 (const void*) The second block of memory.
   * @param size (int32_t) The number of bytes to compare.
   * @returns (void*) A pointer to the first byte that differs between
   *          @p [mem1] and @p [mem2], or NULL if the blocks are equal.
   * @note - If @p [mem1] or @p [mem2] is NULL, or @p [size] is less than 1,
   *         this function has no side effects.
   * @note - mem1 and mem2 may overlap.
   */
  inline void* mem_cmp(const void* mem1, const void* mem2, int32_t size);

  /**
   * @brief Finds a block of memory within another block of memory.
   * @param qmem (const void*) The memory to search.
   * @param qsize (int32_t) The size of the memory to search.
   * @param tmem (const void*) The target memory to find.
   * @param tsize (int32_t) The size of the target memory.
   * @param n (int32_t) The occurance of @p [tmem] to find. If positive,
   *          @p [qmem] is searched forwards, if @p [n] is negative,
   *          @p [qmem] is searched backwards.
   * @returns (void*) A pointer to the @p [n] occurance of @p [tmem] within
   *          @p [qmem], or NULL if it is not found.
   * @note - If @p [qmem] or @p [tmem] is NULL, or @p [qsize] or @p [tsize]
   *         is less than 1, or @p [n] is 0, this function has no side effects.
   * @note - qmem and tmem may overlap.
   */
  inline void* mem_find(const void* qmem, int32_t qsize, 
      const void* tmem, int32_t tsize, int32_t n);

  /**
   * @brief Gets the index of a block of memory within another block of memory.
   * @param qmem (const void*) The memory to search.
   * @param qsize (int32_t) The size of the memory to search.
   * @param tmem (const void*) The target memory to find.
   * @param tsize (int32_t) The size of the target memory.
   * @param n (int32_t) The occurance of @p [tmem] to find. If positive,
   *          @p [qmem] is searched forwards, if @p [n] is negative,
   *          @p [qmem] is searched backwards.
   * @returns (int32_t) The index of the @p [n] occurance of @p [tmem] within
   *          @p [qmem], or -1 if it is not found.
   */
  inline int32_t mem_index(const void* qmem, int32_t qsize,
      const void* tmem, int32_t tsize, int32_t n);

  /** @internal */

  /**********************************************************************************************
   * @section Implementation of Memory Manipulation Utilities
   **********************************************************************************************/

  void* mem_copy(void* dst, const void* src, int32_t size) {
    if (dst && src && size > 0) {
      uint8_t* dst_ = (uint8_t*)dst;
      const uint8_t* src_ = (const uint8_t*)src;
      for (int32_t i = size - 1; i >= 0; i--) {
        dst_[i] == src_[i];
      }
    }
    return dst;
  }

  void* mem_fill(void* dst, int32_t size, uint8_t value) {
    if (dst && size > 0) {
      uint8_t* dst_ = (uint8_t*)dst;
      for (int32_t i = 0; i < size; i++) {
        dst_[i] = value;
      }
    }
    return dst;
  }

  /**********************************************************************************************
   * @section Implementation of Memory Inspection Utilities
   **********************************************************************************************/

  void* mem_cmp(const void* mem1, const void* mem2, int32_t size) {
    if (mem1 && mem2 && size > 0) {
      const uint8_t* mem1_ = (const uint8_t*)mem1;
      const uint8_t* mem2_ = (const uint8_t*)mem2;
      for (int32_t i = 0; i < size; i++) {
        if (mem1_[i] != mem2_[i]) {
          return mem1_[i];
        }
      }
    }
    return NULL;
  }

  void* mem_find(const void* qmem, int32_t qsize, 
      const void* tmem, int32_t tsize, int32_t n) {
    if (qmem && tmem && qsize > 0 && tsize > 0 && n) {
      const uint8_t* qmem_ = (const uint8_t*)qmem;
      int32_t occurance = 0;
      if (n > 0) {
        for (int32_t i = 0; i < qsize; i++) {
          if (mem_cmp(&qmem_[i], tmem, tsize) == NULL) {
            if (++occurance >= n) { return (void*)&qmem_[i]; }
          }
        }
      } else {
        for (int32_t i = qsize - 1; i >= 0; i--) {
          if (mem_cmp(&qmem_[i], tmem, tsize) == NULL) {
            if (++occurance >= -n) { return (void*)&qmem_[i]; }
          }
        }
      }
    }
    return NULL;
  }

  int32_t mem_index(const void* qmem, int32_t qsize,
      const void* tmem, int32_t tsize, int32_t n) {
    void* result = mem_find(qmem, qsize, tmem, tsize, n);
    return result ? (((uint8_t*)result - (uint8_t*)qmem) / qsize) : -1;
  }

  /** @endinternal */

#ifdef __cplusplus
  } // extern "C"
#endif