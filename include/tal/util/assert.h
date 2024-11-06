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
 * @file include/tal/util/assert.h
 * @authors Aaron McBride
 * @brief Runtime assert utilities.
 */

#pragma once
#include <assert.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include "include/tal/util/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Standard Assert Macro
   **************************************************************************************************/

  #if defined(TAL_DEBUG)

    /**
     * @brief Asserts that a given condition is true.
     * @param cond (bool) The condition to assert.
     * @param msg (const char*) The message to emit if the assertion fails.
     * @returns (bool) The result of the given condition.
     * @note - If the condition is false, and TAL_DEBUG is defined, this function
     *         will emit the given error message and location of the assertion
     *         and then abort execution.
     */
    #define tal_assert(cond, msg) \
        ((bool)(cond) ? true : tal_assert__(msg, __FILE__, __LINE__))

  #else

    /** @overload tal_assert(cond, msg) */
    #define tal_assert(cond, msg) \
        ((void)msg, (bool)(cond))

  #endif

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  tal_fn_attr_noreturn bool tal_assert__(const char* msg, const char* file, int line);

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif