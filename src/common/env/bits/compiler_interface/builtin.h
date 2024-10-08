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
 * @file common/env/bits/compiler_interface/builtin.h 
 * @authors Aaron McBride 
 * @brief Compiler-agnosti builtin function/type trait interface.
 */

#pragma once

/**************************************************************************************************
 * @section Compiler Builtin Function Interface
 **************************************************************************************************/

#if defined (__GNUC__)

  // Builtin function aliases
  #define TI_BUILTIN_EXPECT(value, result) __builtin_expect(value, result)
  #define TI_BUILTIN_UNREACHABLE() __builtin_unreachable()
  #define TI_BUILTIN_TRAP() __builtin_trap()
  #define TI_BUILTIN_ADDRESSOF(target) __builtin_addressof(target)
  #define TI_BUILTIN_BIT_CAST(to_type, value_type, value) __builtin_bit_cast(to_type, value)
  #define TI_BUILTIN_CLZ(value_type, value) __builtin_clzg(value, 0)
  #define TI_BUILTIN_CTZ(value_type, value) __builtin_ctzg(value, 0)
  #define TI_BUILTIN_POPCOUNT(value_type, value) __builtin_popcount(value)
  #define TI_BUILTIN_PARITY(value_type, value) __builtin_parity(value)
  #define TI_BUILTIN_IS_CONSTEVAL() __builtin_is_constant_evaluated()

  // Builtin function flags
  #define TI_HAS_BUILTIN_EXPECT 1
  #define TI_HAS_BUILTIN_UNREACHABLE 1
  #define TI_HAS_BUILTIN_TRAP 1
  #define TI_HAS_BUILTIN_ADDRESSOF 1
  #define TI_HAS_BUILTIN_BIT_CAST 1
  #define TI_HAS_BUILTIN_CLZ 1
  #define TI_HAS_BUILTIN_CTZ 1
  #define TI_HAS_BUILTIN_POPCOUNT 1
  #define TI_HAS_BUILTIN_PARITY 1
  #define TI_HAS_BUILTIN_IS_CONSTEVAL 1

#endif

/**************************************************************************************************
 * @section Compiler Builtin Type Trait Interface
 **************************************************************************************************/

#if defined (__GNUC__)

  // Builtin type trait aliases
  #define TI_BUILTIN_UNDERLYING_TYPE(type) __underlying_type(type)
  #define TI_BUILTIN_IS_TRIVIAL(type) __is_trivial(type)
  #define TI_BUILTIN_IS_TRIVIALLY_COPYABLE(type) __is_trivially_copyable(type)
  #define TI_BUILTIN_IS_STANDARD_LAYOUT(type) __is_standard_layout(type)
  #define TI_BUILTIN_IS_ENUM(type) __is_enum(type)
  #define TI_BUILTIN_IS_CLASS(type) __is_class(type)

  // Builtin type trait flags
  #define TI_HAS_BUILTIN_UNDERLYING_TYPE 1
  #define TI_HAS_BUILTIN_IS_TRIVIAL 1
  #define TI_HAS_BUILTIN_IS_TRIVIALLY_COPYABLE 1
  #define TI_HAS_BUILTIN_IS_STANDARD_LAYOUT 1
  #define TI_HAS_BUILTIN_IS_ENUM 1
  #define TI_HAS_BUILTIN_IS_CLASS 1

#endif

