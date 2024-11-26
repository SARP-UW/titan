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

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Attribute Definitions
   **************************************************************************************************/

  /**
   * @def @b tal_attr_weak__
   * @brief Declares a symbol as weak, allowing it to be overridden by a symbol
   *        with the same name in a different (linked) translation unit.
   * @note - This attribute can be applied to functions, variables and types.
   */

  /**
   * @def @b tal_attr_forceinline__
   * @brief Forces the compiler to inline a function.
   * @note - If the compiler can't inline the function, it will likely emit 
   *         an error/warning.
   * @note - Function with this attribute must be defined (implemented) in the 
   *         same translation unit they are declared in.
   * @note - This attribute can be applied to functions only.
   */

  /**
   * @def @b tal_attr_noinline__
   * @brief Prevents the compiler from inlining a function.
   * @note - This attribute can be applied to functions only.
   */

  /**
   * @def @b tal_attr_seciton__(name)
   * @brief Forces the compiler to place a symbol's associated data/code in
   *        specific section of the binary. 
   * @param name (string literal) The name of the target section.
   * @note - This attribute can be applied to functions, variables and types.
   */

  /**
   * @def @b tal_attr_packed__
   * @brief Prevents the compiler from inserting padding between the members 
   *        of a struct/union.
   * @note - This attribute can only be applied to struct/union types/variables.
   * @warning - The alignment of struct/union members is not guaranteed when this
   *            attribute is used.
   */

  /**
   * @def @b tal_attr_unused__
   * @brief Forces the compiler to include a symbol in the binary even if it is
   *        not referenced/used. Also suppresses related warnings.
   * @note - This attribute can be applied to functions, variables and types.
   */

  /**
   * @def @b tal_attr_asm__
   * @brief Indicates to the compiler that a function is implemented in assembly.
   * @note - This attribute prevents the compiler from generating prologue/epilogue
   *         code automatically for the function, and may help with optimization.
   * @note - This attribute can be applied to functions only.
   */

  /**
   * @def @b tal_attr_nopt__
   * @brief Prevents the compiler from applying optimizations to a function,
   *        regardless of the current optimization level
   * @note - This attribute can be applied to functions only.
   */

  /** @internal */

  /**************************************************************************************************
   * @section Implementation of Attributes
   **************************************************************************************************/

  #if defined(__GNUC__)

    #define tal_attr_weak__ __attribute__((weak))
    #define tal_attr_inline__ __attribute__((always_inline))
    #define tal_attr_noinline__ __attribute__((noinline))
    #define tal_attr_section__(name) __attribute__((section(name)))
    #define tal_attr_packed__ __attribute__((packed))
    #define tal_attr_unused__ __attribute__((unused))
    #define tal_attr_nopt__ __attribute__((optimize("O0")))

    #if defined(__arm__)
      #define tal_attr_interrupt__ __attribute__((interrupt))
      #define tal_attr_asm__ __attribute__((naked))
    #else
      #define tal_attr_interrupt__
      #define tal_attr_asm__
    #endif
    
  #elif defined(__clang__)

    #define tal_attr_weak__ __attribute__((weak))
    #define tal_attr_inline__ __attribute__((always_inline))
    #define tal_attr_noinline__ __attribute__((noinline))
    #define tal_attr_section__(name) __attribute__((section(name)))
    #define tal_attr_packed__ __attribute__((packed))
    #define tal_attr_unused__ __attribute__((unused))
    #define tal_attr_asm__ __attribute__((naked))
    #define tal_attr_nopt__ __attribute__((optnone))

    #if defined(__arm__)
      #define tal_attr_interrupt__ __attribute__((interrupt("IRQ")))
    #else
      #define tal_attr_interrupt__ __attribute__((interrupt))
    #endif

  #elif defined(__IAR__)

    #if defined(__arm__)
      #define tal_attr_weak__ __weak
      #define tal_attr_inline__ _Pragma("inline=forced")
      #define tal_attr_noinline__ _Pragma("inline=never")
      #define tal_attr_section__(name) _Pragma("location="name)
      #define tal_attr_packed__ __packed
      #define tal_attr_unused__ __root
      #define tal_attr_asm__ __naked
      #define tal_attr_nopt__ _Pragma("optimize=none") 
    #endif

  #endif

  /** @endinternal */

#if defined(__cplusplus)
  }
#endif