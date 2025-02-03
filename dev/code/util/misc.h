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
 * @file src/common/util/misc.h
 * @authors Aaron McBride 
 * @brief Miscellaneous utilities.
 * @note - API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdnoreturn.h>

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Compiler Hints
   ************************************************************************************************/

  /**
   * @brief Hints to the compiler that a condition is likely to be true.
   * @param x (bool) The condition that is likely true.
   * @returns (bool) The result of the given condition - @p [x].
   * @note - Arguments to this macro are only expanded once.
   */
  #define LIKELY(x)

  /**
   * @brief Hints to the compiler that a condition is likely to be false.
   * @param x (bool) The condition that is likely false.
   * @returns (bool) The result of the given condition - @p [x].
   * @note - Arguments to this macro are only expanded once.
   */
  #define UNLIKELY(x)

  /**
   * @brief Hints to the compiler that a location in code is unreachable.
   * @note - The behavior of this macro when executed is undefined. 
   */
  #define UNREACHABLE()

  /**
   * @brief Compiler optimization barrier.
   * @note - This macro specifically prevents the compiler from reordering 
   *         memory accesses that occur before or after it.
   */
  #define CBAR()

  /************************************************************************************************
   * Array Utilities
   ************************************************************************************************/

  /**
   * @brief Determines the size of an array.
   * @param array (token) The name of the array to query.
   * @returns (int32_t) The number of elements in @p [array].
   * @note - Arguments to this macro are expanded more than once.
   * @note - @p [array] cannot be a pointer to an array.
   */
  #define ARRAY_SIZE(array)

  /**
   * @brief Determines if an index is within the bounds of an array.
   * @param array (token) The name of the target array.
   * @param index (int32_t) The index to query.
   * @returns (bool) True if @p [index] is within the bounds of @p [array], or false otherwise.
   * @note - Arguments to this macro are expanded more than once.
   * @note - @p [array] cannot be a pointer to an array.
   */
  #define IN_BOUNDS(array, index)

  /************************************************************************************************
   * Implementation of Compiler Hints
   ************************************************************************************************/

  /**** LIKELY ****/

  #undef LIKELY
  #define LIKELY(x) (!!(x))  

  #if (defined(__GNUC__) || defined(__clang__)) && \
      __has_builtin(__builtin_expect)

    #undef LIKELY
    #define LIKELY(x) __builtin_expect(!!(x), 1)

  #endif 

  /**** UNLIKELY ****/

  #undef UNLIKELY
  #define UNLIKELY(x) (!!(x))

  #if (defined(__GNUC__) || defined(__clang__)) && \
      __has_builtin(__builtin_expect)

    #undef UNLIKELY
    #define UNLIKELY(x) __builtin_expect(!!(x), 0)

  #endif 

  /**** UNREACHABLE ****/

  noreturn void _unreachable_fn(void) { 
    for (;;) {} 
  }

  #undef UNREACHABLE
  #define UNREACHABLE() _unreachable_fn()

  #if (defined(__GNUC__) || defined(__clang__)) && \
      __has_builtin(__builtin_unreachable)

    #undef UNREACHABLE
    #define UNREACHABLE() __builtin_unreachable()

  #endif 

  /**** Other ****/

  #undef CBAR
  #define CBAR() ( \
    __asm__ volatile ("" ::: "memory") \
  )

  /************************************************************************************************
   * Implementation of Array Utilities
   ************************************************************************************************/

  #undef ARRAY_SIZE
  #define ARRAY_SIZE(array) ( \
    (int32_t)(sizeof(array) / sizeof((array)[0])) \
  )

  #undef IN_BOUNDS
  #define IN_BOUNDS(array, index) ( \
    (index) >= 0 && (index) < ARRAY_SIZE(array) \
  )

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */