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
 * @internal
 * @file src/util/mem.h
 * @authors Aaron McBride
 * @brief Memory utilities.
 * @note - API stable.
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Memory Utilities
   ************************************************************************************************/

  /**
   * @defgroup @b mem_swap_x
   * @brief Swaps two blocks of memory.
   * @param mem1 (void*) A pointer to the first block of memory.
   * @param mem2 (void*) A pointer to the second block of memory.
   * @param size (int32_t) The number of bytes to swap.
   * @note - If @p [mem1] or @p [mem2] is NULL, or @p [size] is less than 1,
   *        this function has no side effects.
   * @note - The function suffixed with 'v' takes volatile pointers.
   * @note - @p [mem1] and @p [mem2] may overlap.
   */
  inline void mem_swap(void* mem1, void* mem2, int32_t size);
  inline void mem_swap_v(volatile void* mem1, volatile void* mem2, int32_t size);

  /**
   * @defgroup @b mem_find_x
   * @brief Finds a block of memory within another block of memory.
   * @param qmem (const void*) The memory to search.
   * @param qsize (int32_t) The size of the memory to search.
   * @param tmem (const void*) The target memory to find.
   * @param tsize (int32_t) The size of the target memory.
   * @param n (int32_t) The occurance of @p [tmem] to find. 
   *          If positive, @p [qmem] is searched forwards, 
   *          if @p [n] is negative, @p [qmem] is searched backwards.
   * @returns (void*) A pointer to the @p [n] occurance of @p [tmem] within
   *          @p [qmem], or NULL if it is not found.
   * @note - If @p [qmem] or @p [tmem] is NULL, or @p [qsize] or @p [tsize]
   *         is less than 1, or @p [n] is 0, this function has no side effects.
   * @note - The function suffixed with 'v' takes volatile src/dst pointers.
   * @note - qmem and tmem may overlap.
   */
  inline void* mem_find(const void* qmem, int32_t qsize, 
      const void* tmem, int32_t tsize, int32_t n);
  inline void* mem_find_v(volatile const void* qmem, int32_t qsize, 
      const volatile void* tmem, int32_t tsize, int32_t n);
  /** @} */

  /**
   * @defgroup @b mem_index_x
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
   * @note - The function suffixed with 'v' takes volatile src/dst pointers.
   */
  inline int32_t mem_index(const void* qmem, int32_t qsize,
      const void* tmem, int32_t tsize, int32_t n);
  inline int32_t mem_index_v(const volatile void* qmem, int32_t qsize,
      const volatile void* tmem, int32_t tsize, int32_t n);

  /************************************************************************************************
   * Implementation of Memory Utilities
   ************************************************************************************************/

  /**** mem_swap ****/

  void mem_swap(void* mem1, void* mem2, int32_t size) {
    if (mem1 && mem2 && size > 0) {
      uint8_t* mem1_ = (uint8_t*)mem1;
      uint8_t* mem2_ = (uint8_t*)mem2;
      for (int32_t i = 0; i < size; i++) {
        uint8_t tmp = mem1_[i];
        mem1_[i] = mem2_[i];
        mem2_[i] = tmp;
      }
    }
  }

  void mem_swap_v(volatile void* mem1, volatile void* mem2, int32_t size) {
    if (mem1 && mem2 && size > 0) {
      uint8_t* mem1_ = (uint8_t*)mem1;
      uint8_t* mem2_ = (uint8_t*)mem2;
      for (int32_t i = 0; i < size; i++) {
        uint8_t tmp = mem1_[i];
        mem1_[i] = mem2_[i];
        mem2_[i] = tmp;
      }
    }
  }

  /**** mem_find ****/

  void* mem_find(const void* qmem, int32_t qsize, 
      const void* tmem, int32_t tsize, int32_t n) {
    if (qmem && tmem && qsize > 0 && tsize > 0 && n) {
      const uint8_t* qmem_ = (const uint8_t*)qmem;
      int32_t occurance = 0;
      if (n > 0) {
        for (int32_t i = 0; i < qsize; i++) {
          if (!memcmp(&qmem_[i], tmem, tsize)) {
            if (++occurance >= n) { return (void*)&qmem_[i]; }
          }
        }
      } else {
        for (int32_t i = qsize - 1; i >= 0; i--) {
          if (!memcmp(&qmem_[i], tmem, tsize)) {
            if (++occurance >= -n) { return (void*)&qmem_[i]; }
          }
        }
      }
    }
    return NULL;
  }

  void* mem_find_v(const volatile void* qmem, int32_t qsize, 
      const volatile void* tmem, int32_t tsize, int32_t n) {
    if (qmem && tmem && qsize > 0 && tsize > 0 && n) {
      const uint8_t* qmem_ = (const uint8_t*)qmem;
      int32_t occurance = 0;
      if (n > 0) {
        for (int32_t i = 0; i < qsize; i++) {
          if (!memcmp(&qmem_[i], tmem, tsize)) {
            if (++occurance >= n) { return (void*)&qmem_[i]; }
          }
        }
      } else {
        for (int32_t i = qsize - 1; i >= 0; i--) {
          if (!memcmp(&qmem_[i], tmem, tsize)) {
            if (++occurance >= -n) { return (void*)&qmem_[i]; }
          }
        }
      }
    }
    return NULL;
  }

  /**** mem_index_v ****/

  int32_t mem_index(const void* qmem, int32_t qsize,
      const void* tmem, int32_t tsize, int32_t n) {
    void* result = mem_find(qmem, qsize, tmem, tsize, n);
    return result ? (((uint8_t*)result - (uint8_t*)qmem) / qsize) : -1;
  }

  int32_t mem_index_v(const volatile void* qmem, int32_t qsize,
      const volatile void* tmem, int32_t tsize, int32_t n) {
    void* result = mem_find_v(qmem, qsize, tmem, tsize, n);
    return result ? (((uint8_t*)result - (uint8_t*)qmem) / qsize) : -1;
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */