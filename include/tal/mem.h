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
 * @file include/tal/mem.h
 * @authors Aaron McBride
 * @brief Memory/array utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Search Operations
   **************************************************************************************************/

  int32_t tal_find(const void* const mem, const int32_t size, 
      const void* const value, const int32_t vsize, const int32_t n, 
      bool* const err);

  int32_t tal_rfind(const void* const mem, const int32_t size, 
      const void* const value, const int32_t vsize, const int32_t n, 
      bool* const err);

  int32_t tal_find_if(const void* const mem, const int32_t size,
      bool (*pred)(const void*), const int32_t vsize, const int32_t n, 
      bool* const err);

  int32_t tal_rfind_if(const void* const mem, const int32_t size, 
      bool (*fn)(const void*), const int32_t vsize, const int32_t n, 
      bool* const err);

  int32_t tal_find_match(const void* const mem1, const void* const mem2, 
      const int32_t size, const int32_t msize, const int32_t n, bool* const err);

  int32_t tal_rfind_match(const void* const mem1, const void* const mem2, 
      const int32_t size, const int32_t msize, const int32_t n, bool* const err);

  int32_t tal_find_seq(const void* const mem, const int32_t size,
      const void* const value, const int32_t vsize, const int32_t cnt,
      const int32_t n, bool* const err);

  int32_t tal_rfind_seq(const void* const mem, const int32_t size,
      const void* const value, const int32_t vsize, const int32_t cnt,
      const int32_t n, bool* const err);

  int32_t tal_find_any(const void* const mem, const int32_t size, 
      const void* const fmem, const int32_t fsize, const int32_t vsize, 
      bool* const err);

  int32_t tal_rfind_any(const void* const mem, const int32_t size, 
      const void* const fmem, const int32_t fsize, const int32_t vsize, 
      bool* const err);

  int32_t tal_find_unique(const void* const mem, const int32_t size,
      const int32_t vsize, const int32_t n, bool* const err);

  int32_t tal_rfind_unique(const void* const mem, const int32_t size,
      const int32_t vsize, const int32_t n, bool* const err);

  /**************************************************************************************************
   * @section Memory Inspection Utilities
   **************************************************************************************************/

  bool tal_contains(const void* const mem, const int32_t size,
      const void* const value, const int32_t vsize, bool* const err);

  bool tal_is_unique(const void* const mem, const int32_t size, 
      const int32_t vsize, bool* const err);

  int32_t tal_count(const void* const mem, const int32_t size,
      const void* const value, const int32_t vsize, bool* const err);
  
  int32_t tal_count_if(const void* const mem, const int32_t size,
      bool (*fn)(const void*), const int32_t vsize, bool* const err);

  bool tal_all_of(const void* const mem, const int32_t size,
      const int32_t vsize, bool (*pred)(const void*), bool* const err);
  
  bool tal_any_of(const void* const mem, const int32_t size, 
      const int32_t vsize, bool (*pred)(const void*), bool* const err);
  
  bool tal_none_of(const void* const mem, const int32_t size, 
      const int32_t vsize, bool (*pred)(const void*), bool* const err);

  int32_t tal_mem_cmp(const void* const mem1, const void* const mem2,
      const int32_t size, bool* const err);

  /**************************************************************************************************
   * @section Memory Manipulation Utilities
   **************************************************************************************************/

  void tal_copy(void* const dst, const void* const src, 
      const int32_t size, const int32_t n, bool* const err);

  void tal_move(void* const dst, void* const src, 
      const int32_t size, bool* const err);

  void tal_clr(void* const mem, const int32_t size, bool* const err);

  void tal_fill(void* const mem, const int32_t size, 
      const void* const value, const int32_t vsize, bool* const err);

  void tal_insert(void* const mem, const int32_t size, const void* const value, 
      const int32_t vsize, const int32_t off, const int32_t n, bool* const err);

  void tal_extract(void* const dst, void* const mem, const int32_t size, 
      const int32_t off, const int32_t xsize, bool* const err);

  void tal_mem_shift(void* const mem, const int32_t size, 
      const int32_t shift, bool* const err);

  void tal_mem_rot(void* const src, const int32_t size, 
      const int32_t rot, bool* const err);
  
  void tal_mem_rev(void* const mem, const int32_t size, 
      const int32_t vsize, bool* const err);

  void tal_swap(void* restrict const mem1, void* restrict const mem2, 
      const int32_t size, bool* const err);
  
  void tal_generate(void* const mem, const int32_t size,
      const int32_t vsize, uint8_t (*gen_fn)(int32_t), bool* const err);

  void tal_qsort(void* const mem, const int32_t size, const int32_t vsize,
      int32_t (*cmp_fn)(const void*, const void*), bool* const err);

  void tal_sample(void* const dst, const void* const src, const int32_t size, 
      const int32_t vsize, const int32_t n, const int32_t seed, bool* const err);

  void tal_shuffle(void* const mem, const int32_t size, const int32_t vsize,
      const int32_t seed, bool* const err);

#if defined(__cplusplus)
  } // extern "C"
#endif