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
 * @file include/tal/attr.h
 * @authors Aaron McBride
 * @brief Compiler-agnostic function/variable/type attributes.
 */

#pragma once
#include "src/common/tmp.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Attribute
   **************************************************************************************************/

  /**
   * @def @b attr_weak
   * @brief Declares a symbol as weak, allowing it to be overridden by a symbol
   *        with the same name in a different (linked) translation unit.
   * @note - This attribute can be applied to functions, variables and types.
   */

  /**
   * @def @b attr_section(name)
   * @brief Forces the compiler to place a symbol's associated data/code in
   *        specific section of the binary. 
   * @param name (token - not string literal) The name of the target section.
   * @note - This attribute can be applied to functions, variables and types.
   */

  /**
   * @def @b attr_packed
   * @brief Prevents the compiler from inserting padding between the members 
   *        of a struct/union.
   * @note - This attribute can only be applied to struct/union types/variables.
   * @warning - The alignment of struct/union members is not guaranteed when this
   *            attribute is used.
   */

  /**
   * @def @b attr_naked
   * @brief Indicates to the compiler that a function is implemented in assembly.
   * @note - This attribute prevents the compiler from generating prologue/epilogue
   *         code automatically for the function, and may help with optimization.
   * @note - This attribute can be applied to functions only.
   */

  /**
   * @def @b attr_nopt
   * @brief Prevents the compiler from applying optimizations to a function,
   *        regardless of the current optimization level
   * @note - This attribute can be applied to functions only.
   */


  /** @internal */

  /**************************************************************************************************
   * @section Implementation for Attributes
   **************************************************************************************************/

  #if defined(__GNUC__)

    #define attr_weak __attribute__((weak))
    #define attr_section(name) __attribute__((section(name)))
    #define attr_packed __attribute__((packed))
    #define attr_nopt __attribute__((optimize("O0")))
    #define attr_naked __attribute__((naked))
    
  #elif defined(__clang__)

    #define attr_weak __attribute__((weak))
    #define attr_section(name) __attribute__((section(name)))
    #define attr_packed __attribute__((packed))
    #define attr_naked __attribute__((naked))
    #define attr_nopt __attribute__((optnone))

  #elif defined(__IAR__)

    #define attr_weak __weak
    #define attr_section(name) _Pragma(XSTRING(CONCAT(location=, name)))
    #define attr_packed __packed
    #define attr_naked __naked
    #define attr_nopt _Pragma("optimize=none")

  #endif


  /** @endinternal */

#if defined(__cplusplus)
  }
#endif