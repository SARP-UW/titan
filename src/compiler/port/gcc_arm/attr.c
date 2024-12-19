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
 * @file src/compiler/port/gcc_arm/attr.h
 * @authors Aaron McBride
 * @brief Implementation of the type, function and variable attribute
 *        interface for the ARM GCC compiler.
 */

#if defined(__cplusplus)
  extern "C" {
#endif

  /************************************************************************************************
   * @section Function Attributes
   ************************************************************************************************/

  #define _fn_attr_weak __attribute__((weak))

  #define _fn_attr_asm __attribute__((naked))

  #define _fn_attr_interrupt __attribute__((interrupt))

  #define _fn_attr_nopt __attribute__((optimize("O0")))

  #define _fn_attr_unused __attribute__((unused))

  /************************************************************************************************
   * @section Variable Attributes
   ************************************************************************************************/

  #define _var_attr_packed __attribute__((packed))

  #define _var_attr_unused __attribute__((unused))

  #define _var_attr_section(name) __attribute__((section(name)))

  /************************************************************************************************
   * @section Type Attributes
   ************************************************************************************************/

  #define _type_attr_packed __attribute__((packed))

  #define _type_attr_aligned(n) __attribute__((aligned(n)))

#if defined(__cplusplus)
  } // extern "C"
#endif