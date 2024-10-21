/**
 * This file is part of the Titan Flight Computer Project
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
 * @file common/util/attribute.h
 * @authors Aaron McBride
 * @brief Compiler-agnostic function and variable attributes.
 */

#pragma once

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Function Attributes
   **************************************************************************************************/

  #if defined(__GNUC__)

    /** 
     * @brief Enables a function to be defined in a different TU.
     */
    #define ti_fn_attr_weak __attribute__((weak))

    /** 
     * @brief Makes a function an alias (different name for) annother function. 
     * @note - The aliased function may be defined in a different, non-visible TU.
     */
    #define ti_fn_attr_alias(name) __attribute__((alias(name))) 

    /** 
     * @brief Forces all calls to a function to be inlined.
     * @note - Requires that the function be defined in the same TU.
     */
    #define ti_fn_attr_inline __attribute__((always_inline)) 

    /** 
     * @brief Prevents any call to a function from being inlined. 
     */
    #define ti_fn_attr_noinline __attribute__((noinline)) 

    /** 
     * @brief Runs a function automatically before main() is entered. If 
     *        there are multiple entry functions, they are invoked in order 
     *        from lowest to highest priority. 
     */
    #define ti_fn_attr_entry(prio) __attribute__((constructor(prio))) 

    /** 
     * @brief Runs a function automatically after main() returns. If there 
     *        are multiple exit functions, they are invoked in order from 
     *        lowest, to highest priority.  
     */
    #define ti_fn_attr_exit(prio) __attribute__((destructor(prio))) 

    /**
     * @brief Emits a warning (durring compilation) if a function is called.
     * @param msg The warning message to emit.
     */
    #define ti_fn_attr_deprecated(msg) __attribute__((deprecated(msg)))

    /**
     * @brief Emits an error (durring compilation) if a function is called.
     * @param msg The error message to emit.
     */
    #define ti_fn_attr_unavailable(msg) __attribute__((unavailable(msg)))

    /**
     * @brief Places a function in a specific section of memory.
     * @param name The name of the section, as defined in the linker script.
     */
    #define ti_fn_attr_section(name) __attribute__((section(name)))
    
    /**
     * @brief Indicates to the compiler that a function will not return,
     *        which allows for aggressive optimizations.
     */
    #define ti_fn_attr_noreturn __attribute__((noreturn))

    /**
     * @brief Indicates to the compiler that a function should not be
     *        optimized in any way.
     * @note - This attribute is primarilly useful for asm functions.
     */
    #define ti_fn_attr_raw __attribute__((optimize("O0")))
 
  #endif

  /**************************************************************************************************
   * @section Variable Attributes
   **************************************************************************************************/

  #if defined(__GNUC__)

    /**
     * @brief Enables a variable to be defined in a different TU.
     */
    #define ti_var_attr_weak __attribute__((weak))

    /**
     * @brief Makes a variable an alias (different name for) annother variable.
     * @note - The aliased variable may be defined in a different, non-visible TU.
     */
    #define ti_var_attr_alias(name) __attribute__((alias(name)))

    /**
     * @brief Emits a warning (durring compilation) if a variable is accessed.
     * @param msg The warning message to emit.
     */
    #define ti_var_attr_deprecated(msg) __attribute__((deprecated(msg)))

    /**
     * @brief Emits an error (durring compilation) if a variable is accessed.
     * @param msg The error message to emit.
     */
    #define ti_var_attr_unavailable(msg) __attribute__((unavailable(msg)))

    /**
     * @brief Prevents the members of a specific struct from being padded.
     * @warning - Some targets may not support unaligned memory access, which
     *            may be required to access certain non-padded struct members.
     */
    #define ti_var_attr_packed __attribute__((packed))

    /**
     * @brief Aligns a variable to a specific byte boundary.
     * @param n The byte boundary to align the variable to.
     */
    #define ti_var_attr_aligned(n) __attribute__((aligned(n)))

    /**
     * @brief Places a variable in a specific section of memory.
     * @param name The name of the section, as defined in the linker script.
     */
    #define ti_var_attr_section(name) __attribute__((section(name)))

    /**
     * @brief Indicates to the compiler that a variable may not be used.
     * @note - This attribute prevents the compiler from removing a variable
     *         from the compiled program even if it is unused.
     */
    #define ti_var_attr_unused __attribute__((unused))

  #endif

  /**************************************************************************************************
   * @section Type Attributes
   **************************************************************************************************/

  #if defined(__GNUC__)

    /**
     * @brief Emits a warning (durring compilation) if a type is used.
     * @param msg The warning message to emit.
     */
    #define ti_type_attr_deprecated(msg) __attribute__((deprecated(msg)))

    /**
     * @brief Emits an error (durring compilation) if a type is used.
     * @param msg The error message to emit.
     */
    #define ti_type_attr_unavailable(msg) __attribute__((unavailable(msg)))

    /**
     * @brief Prevents the members of all instances of a struct from being padded.
     * @warning - Some targets may not support unaligned memory access, which
     *            may be required to access certain non-padded struct members.
     */
    #define ti_type_attr_packed __attribute__((packed))

    /**
     * @brief Aligns all instances of a type to a specific byte boundary.
     * @param n The byte boundary to align the type to.
     */
    #define ti_type_attr_aligned(n) __attribute__((aligned(n)))

    /**
     * @brief Indicates to the compiler that a type may not be used.
     * @note - This attribute prevents the compiler from removing a type from
     *         the compiled program even if it is unused.
     */
    #define ti_type_attr_unused __attribute__((unused))

  #endif

#if defined(__cplusplus)
  }
#endif