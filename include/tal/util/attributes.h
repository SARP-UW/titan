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
 * @file include/tal/util/attributes.h
 * @authors Aaron McBride
 * @brief Compiler-agnostic function, variable and type attributes.
 */

#pragma once

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Non-Standard Function Attributes
   **************************************************************************************************/

  /** 
   * @def tal_fn_attr_weak
   * @brief Enables a function to be defined in a different TU.
   */

  /** 
   * @def tal_fn_attr_alias(name)
   * @brief Makes a function an alias (different name for) annother function. 
   * @note - The aliased function may be defined in a different, non-visible TU.
   */

  /** 
   * @def tal_fn_attr_inline
   * @brief Forces all calls to a function to be inlined.
   * @note - Requires that the function be defined in the same TU.
   */

  /** 
   * @def tal_fn_attr_noinline
   * @brief Prevents any call to a function from being inlined. 
   */

  /**
   * @def tal_fn_attr_warn(msg)
   * @brief Emits a warning (durring compilation) if a function is called.
   * @param msg The warning message to emit.
   */

  /**
   * @def tal_fn_attr_section(name)
   * @brief Places a function in a specific section of memory.
   * @param name The name of the section, as defined in the linker script.
   */

  /**
   * @def tal_fn_attr_noreturn
   * @brief Indicates to the compiler that a function will not return,
   *        which allows for aggressive optimizations.
   */

  /**
   * @def tal_fn_attr_raw
   * @brief Indicates to the compiler that a function should not be
   *        optimized in any way.
   * @note - This attribute is primarilly useful for asm functions.
   */

  #if defined(__GNUC__)

    #define tal_fn_attr_weak __attribute__((weak))
    #define tal_fn_attr_alias(name) __attribute__((alias(name))) 
    #define tal_fn_attr_inline __attribute__((always_inline)) 
    #define tal_fn_attr_noinline __attribute__((noinline)) 
    #define tal_fn_attr_warn(msg) __attribute__((deprecated(msg)))
    #define tal_fn_attr_section(name) __attribute__((section(name)))
    #define tal_fn_attr_noreturn __attribute__((noreturn))
    #define tal_fn_attr_raw __attribute__((optimize("O0")))
 
  #endif

  /**************************************************************************************************
   * @section Non-Standard Variable Attributes
   **************************************************************************************************/

  /**
   * @def tal_var_attr_weak
   * @brief Enables a variable to be defined in a different TU.
   */

  /**
   * @def tal_var_attr_alias(name)
   * @brief Makes a variable an alias (different name for) annother variable.
   * @note - The aliased variable may be defined in a different, non-visible TU.
   */

  /**
   * @def tal_var_attr_warn(msg)
   * @brief Emits a warning (durring compilation) if a variable is accessed.
   * @param msg The warning message to emit.
   */

  /**
   * @def tal_var_attr_packed
   * @brief Prevents the members of a specific struct from being padded.
   * @warning - Some targets may not support unaligned memory access, which
   *            may be required to access certain non-padded struct members.
   */

  /**
   * @def tal_var_attr_section(name)
   * @brief Places a variable in a specific section of memory.
   * @param name The name of the section, as defined in the linker script.
   */

  /**
   * @def tal_var_attr_unused
   * @brief Indicates to the compiler that a variable may not be used.
   * @note - This attribute prevents the compiler from removing a variable
   *         from the compiled program even if it is unused.
   */

  #if defined(__GNUC__)

    #define tal_var_attr_weak __attribute__((weak))
    #define tal_var_attr_alias(name) __attribute__((alias(name)))
    #define tal_var_attr_warn(msg) __attribute__((deprecated(msg)))
    #define tal_var_attr_packed __attribute__((packed))
    #define tal_var_attr_section(name) __attribute__((section(name)))
    #define tal_var_attr_unused __attribute__((unused))

  #endif

  /**************************************************************************************************
   * @section Non-Standard Type Attributes
   **************************************************************************************************/

  /**
   * @def tal_type_attr_warn(msg)
   * @brief Emits a warning (durring compilation) if a type is used.
   * @param msg The warning message to emit.
   */

  /**
   * @def tal_type_attr_packed
   * @brief Prevents the members of all instances of a struct from being padded.
   * @warning - Some targets may not support unaligned memory access, which
   *            may be required to access certain non-padded struct members.
   */

  /**
   * @def tal_type_attr_aligned(n)
   * @brief Aligns all instances of a type to a specific byte boundary.
   * @param n The byte boundary to align the type to.
   */

  /**
   * @def tal_type_attr_unused
   * @brief Indicates to the compiler that a type may not be used.
   * @note - This attribute prevents the compiler from removing a type from
   *         the compiled program even if it is unused.
   */

  #if defined(__GNUC__)

    #define tal_type_attr_warn(msg) __attribute__((deprecated(msg)))
    #define tal_type_attr_packed __attribute__((packed))
    #define tal_type_attr_aligned(n) __attribute__((aligned(n)))
    #define tal_type_attr_unused __attribute__((unused))

  #endif

#if defined(__cplusplus)
  }
#endif