/**
 * This file is part of the Titan Avionics Library
 * Copyright (c) 2024 Aaron McBride.
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
 * @file common/env/bits/compiler_interface/attribute.h 
 * @authors Aaron McBride 
 * @brief Compiler-agnostic attribute interface.
 */

#pragma once

/**************************************************************************************************
 * @section Function Attribute Interface
 **************************************************************************************************/

#if defined (__GNUC__)

  // Function attribute aliases
  #define TI_ATTR_ALWAYS_INLINE_FN [[gnu::always_inline]]
  #define TI_ATTR_NAKED_FN [[gnu::naked]]
  #define TI_ATTR_REG_FN [[gnu::optimize("O0")]]
  #define TI_ATTR_INTERRUPT_FN [[gnu::interrupt]]
  #define TI_ATTR_WEAK_FN [[gnu::weak]]

  // Function attribute flags
  #define TI_HAS_ATTR_ALWAYS_INLINE_FN 1
  #define TI_HAS_ATTR_NAKED_FN 1
  #define TI_HAS_ATTR_REG_FN 1
  #define TI_HAS_ATTR_INTERRUPT_FN 1
  #define TI_HAS_ATTR_WEAK_FN 1

#endif

/**************************************************************************************************
 * @section Variable Attribute Interface
 **************************************************************************************************/

#if defined (__GNUC__)

  // Variable attribute aliases
  #define TI_ATTR_SECTION_VAR(name) [[gnu::section(#name)]]
  #define TI_ATTR_PACKED_VAR [[gnu::packed]]
  #define TI_ATTR_WEAK_VAR [[gnu::weak]]

  // Variable attribute flags
  #define TI_HAS_ATTR_SECTION_VAR 1
  #define TI_HAS_ATTR_PACKED_VAR 1
  #define TI_HAS_ATTR_WEAK_VAR 1

#endif