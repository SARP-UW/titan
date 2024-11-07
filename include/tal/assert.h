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
 * @file include/tal/assert.h
 * @authors Aaron McBride
 * @brief Runtime assertion utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "include/tal/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Assertion Utilities
   **************************************************************************************************/

  /**
   * @def tal_assert(cond, msg)
   * @brief Asserts that a given condition is true.
   * @param cond (bool) The condition to assert.
   * @param msg (const char*) The message to emit if the condition is false.
   * @returns (bool) The result of the given condition.
   * @note - If the condition is false, and TAL_DEBUG is defined, this function
   *         will emit the given error message and location of the assertion
   *         and then abort execution.
   */

  #if defined(TAL_DEBUG)
    #define tal_assert(cond, msg) ((bool)(cond) ? \
         true : tal_assert_fail__(msg, __FILE__, __LINE__))
  #else
    #define tal_assert(cond, msg) ((void)msg, (bool)(cond))
  #endif

  /**
   * @brief Requires that a given condition is true.
   * @param cond (bool) The condition to require.
   * @param msg (const char*) The message to emit if the condition is false.
   * @returns (bool) The result of the given condition.
   * @note - If the condition is false this function will abort execution even
   *         if TAL_DEBUG is not defined.
   */
  #define tal_require(cond, msg) ((bool)(cond) ? \
      true : tal_require_fail__(msg, __FILE__, __LINE__))

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  // todo -> update implementation
  tal_fn_attr_noreturn bool tal_assert_fail__(const char* msg, 
      const char* file, const int32_t line) {
    #if defined(TAL_ARCH_ARMV7M)
      asm volatile ("SVC #1");
    #else
      *(int32_t*)0 = 0;
    #endif
  }

  // todo -> update implementation
  tal_fn_attr_noreturn bool tal_require_fail__(const char* msg, 
      const char* file, const int32_t line) {
    #if defined(TAL_ARCH_ARMV7M)
      asm volatile ("SVC #1");
    #else
      *(int32_t*)0 = 0;
    #endif
  }

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif