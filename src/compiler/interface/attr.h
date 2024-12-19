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
 * @file src/compiler/interface/attr.h
 * @authors Aaron McBride
 * @brief Interface for type, function and variable attributes.
 */

#if defined(__cplusplus)
  extern "C" {
#endif

  /************************************************************************************************
   * @section Function Attributes
   ************************************************************************************************/

  /** @brief Makes a function weakly linked. */
  #define _fn_attr_weak

  /** @brief Prevents the compiler from generating entry/exit sequences. */
  #define _fn_attr_asm

  /** @brief Indicates to the compiler that a function is an interrupt handler. */
  #define _fn_attr_interrupt

  /** @brief Prevents the compiler from optimizing a function. */
  #define _fn_attr_nopt

  /** @brief Ensures unused function is included in binary. */
  #define _fn_attr_unused

  /************************************************************************************************
   * @section Variable Attributes
   ************************************************************************************************/

  /** @brief Prevents the compiler from adding padding to members. */
  #define _var_attr_packed

  /** @brief Ensures unused variable is included in binary. */
  #define _var_attr_unused

  /** @brief Allocates variable in the given memory section. */
  #define _var_attr_section(name)

  /************************************************************************************************
   * @section Type Attributes
   ************************************************************************************************/

  /** @brief Prevents the compiler from adding padding to members. */
  #define _type_attr_packed

  /** @brief Ensures all instances of a type are aligned to the given byte boundry. */
  #define _type_attr_aligned(n)

#if defined(__cplusplus)
  } // extern "C"
#endif