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
 * @file include/tal/util/stdlib.h
 * @authors Aaron McBride
 * @brief General language utilities.
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "include/tal/util/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section String Conversion Utilities
   **************************************************************************************************/

  tal_fn_attr_inline inline int8_t tal_ato_i8(const char* str);
  tal_fn_attr_inline inline int16_t tal_ato_i16(const char* str);
  tal_fn_attr_inline inline int32_t tal_ato_i32(const char* str);
  tal_fn_attr_inline inline int64_t tal_ato_i64(const char* str);
  tal_fn_attr_inline inline uint8_t tal_ato_u8(const char* str);
  tal_fn_attr_inline inline uint16_t tal_ato_u16(const char* str);
  tal_fn_attr_inline inline uint32_t tal_ato_u32(const char* str);
  tal_fn_attr_inline inline uint64_t tal_ato_u64(const char* str);

  tal_fn_attr_inline inline int8_t tal_strto_i8(const char* str, const char** str_end, const int32_t base);
  tal_fn_attr_inline inline int16_t tal_strto_i16(const char* str, const char** str_end, const int32_t base);
  tal_fn_attr_inline inline int32_t tal_strto_i32(const char* str, const char** str_end, const int32_t base);
  tal_fn_attr_inline inline int64_t tal_strto_i64(const char* str, const char** str_end, const int32_t base);
  tal_fn_attr_inline inline uint8_t tal_strto_u8(const char* str, const char** str_end, const int32_t base);
  tal_fn_attr_inline inline uint16_t tal_strto_u16(const char* str, const char** str_end, const int32_t base);
  tal_fn_attr_inline inline uint32_t tal_strto_u32(const char* str, const char** str_end, const int32_t base);
  tal_fn_attr_inline inline uint64_t tal_strto_u64(const char* str, const char** str_end, const int32_t base);

  /**************************************************************************************************
   * @section Miscellaneous Utilities
   **************************************************************************************************/

  tal_fn_attr_inline inline int8_t tal_rand_i8(int32_t seed);
  tal_fn_attr_inline inline int16_t tal_rand_i16(int32_t seed);
  tal_fn_attr_inline inline int32_t tal_rand_i32(int32_t seed);
  tal_fn_attr_inline inline int64_t tal_rand_i64(int32_t seed);
  tal_fn_attr_inline inline uint8_t tal_rand_u8(int32_t seed);
  tal_fn_attr_inline inline uint16_t tal_rand_u16(int32_t seed);
  tal_fn_attr_inline inline uint32_t tal_rand_u32(int32_t seed);
  tal_fn_attr_inline inline uint64_t tal_rand_u64(int32_t seed);

  // add qsort here...

  /**************************************************************************************************
   * @section Dynamic Allocation Utilities
   **************************************************************************************************/

  tal_fn_attr_inline inline void* tal_malloc(int32_t size);

  tal_fn_attr_inline inline bool tal_free(void* mem);

  tal_fn_attr_inline inline void* tal_alligned_alloc(int32_t align, int32_t size);
  
  tal_fn_attr_inline inline void* tal_calloc(int32_t num, int32_t size);

  tal_fn_attr_inline inline void* tal_realloc(void* mem, int32_t size);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  #define tal_exit_fn_count__ 32
  static void (*tal_exit_fn_array__[tal_exit_fn_count__])(void) = {NULL};

  void tal_abort(void) {
    #if defined(TAL_ARCH_ARMV7M)
      asm volatile ("SVC #1");
    #else
      *(int*)0 = 0;
    #endif
  }

  void tal_exit(void) {
    for (int32_t i = tal_exit_fn_count__ - 1; i >= 0; --i) {
      if (tal_exit_fn_array__[i]) { tal_exit_fn_array__[i](); }
    }
    #if defined(TAL_ARCH_ARMV7M)

    #else
      
    #endif
  }

  bool tal_at_exit(void (*fn)(void)) {
    for (int32_t i = 0; i < tal_exit_fn_count__; ++i) {
      if (!tal_exit_fn_array__[i]) { 
        tal_exit_fn_array__[i] = fn;
        return true;
      }
    }
    return false;
  }





  /** @endinternal */

#if defined(__cplusplus)
  }
#endif