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
 * @file common/util/bits/type_traits/type_category.h 
 * @authors Aaron McBride 
 * @brief Contains type traits for querying type categories.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    // Implementation for 'is_integral_v'
    template<typename T> inline constexpr bool raw_integral_v{false};
    template<> inline constexpr bool raw_integral_v<unsigned char>{true};
    template<> inline constexpr bool raw_integral_v<signed char>{true};
    template<> inline constexpr bool raw_integral_v<unsigned short int>{true};
    template<> inline constexpr bool raw_integral_v<signed short int>{true};
    template<> inline constexpr bool raw_integral_v<unsigned int>{true};
    template<> inline constexpr bool raw_integral_v<signed int>{true};
    template<> inline constexpr bool raw_integral_v<unsigned long int>{true};
    template<> inline constexpr bool raw_integral_v<signed long int>{true};
    template<> inline constexpr bool raw_integral_v<unsigned long long int>{true};
    template<> inline constexpr bool raw_integral_v<signed long long int>{true};
    template<> inline constexpr bool raw_integral_v<bool>{true};

    // Implementation for 'is_function_v'
    template<typename T> inline constexpr bool const_fn_test_v{true};
    template<typename T> inline constexpr bool const_fn_test_v<const T>{false};
    template<typename T> inline constexpr bool const_fn_test_v<const volatile T>{false};

    template<typename T> inline constexpr bool ref_fn_test_v{true};
    template<typename T> inline constexpr bool ref_fn_test_v<T&>{false};
    template<typename T> inline constexpr bool ref_fn_test_v<T&&>{false};

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section Standard Type Category Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if the given type is 
   *        void, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_void_v{false};
  template<> inline constexpr bool is_void_v<void>{true};
  template<> inline constexpr bool is_void_v<const void>{true};
  template<> inline constexpr bool is_void_v<volatile void>{true};
  template<> inline constexpr bool is_void_v<const volatile void>{true};

  /**
   * @brief Template bool value that evaluates to true if the given type 
   *        is nullptr_t, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_null_pointer_v{false};
  template<> inline constexpr bool is_null_pointer_v<decltype(nullptr)>{true};
  template<> inline constexpr bool is_null_pointer_v<const decltype(nullptr)>{true};
  template<> inline constexpr bool is_null_pointer_v<volatile decltype(nullptr)>{true};
  template<> inline constexpr bool is_null_pointer_v<const volatile decltype(nullptr)>{true};

  /**
   * @brief Template bool value that evaluates to true if the given type 
   *        is an integral type (integer or bool), or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_integral_v{raw_integral_v<T>};
  template<typename T> inline constexpr bool is_integral_v<const T>{raw_integral_v<T>};
  template<typename T> inline constexpr bool is_integral_v<volatile T>{raw_integral_v<T>};
  template<typename T> inline constexpr bool is_integral_v<const volatile T>{raw_integral_v<T>};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a bounded or unbounded array, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_array_v{false};
  template<typename T> inline constexpr bool is_array_v<T[]>{true};
  template<typename T, size_t N> inline constexpr bool is_array_v<T[N]>{true};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is an enum type, or false otherwise.
   * @tparam T The type to query.
   * @warning - This trait requires compiler support!
   */
  template<typename T>
  inline constexpr bool is_enum_v{TI_BUILTIN_IS_ENUM(T)};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a class/struct type, or false otherwise.
   * @tparam T The type to query.
   * @warning - This trait requires compiler support!
   */
  template<typename T>
  inline constexpr bool is_class_v{TI_BUILTIN_IS_CLASS(T)};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a function type, or false otherwise. 
   * @tparam T The type to query.
   */
  template<typename T> 
  inline constexpr bool is_function_v{
      const_fn_test_v<const T> && ref_fn_test_v<T>};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a pointer (single, double or tripple), or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_pointer_v{false};
  template<typename T> inline constexpr bool is_pointer_v<T*>{true};

  /**
   * @brief Template bool value that evaluates to true if the given type 
   *        is an l_value reference, false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_lvalue_reference_v{false};
  template<typename T> inline constexpr bool is_lvalue_reference_v<T&>{true};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is an r_value reference, false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_rvalue_reference_v{false};
  template<typename T> inline constexpr bool is_rvalue_reference_v<T&&>{true};

  /**************************************************************************************************
   * @section Standard Compound Type Category Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if the given type 
   *        is a reference (l_value or r_value), or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> 
  inline constexpr bool is_reference_v{is_lref_v<T> || is_rref_v<T>};

  /**************************************************************************************************
   * @section Non-Standard Type Category Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is an integer type (non-bool integral type), or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_integer_v{is_integral_v<T>};
  template<> inline constexpr bool is_integer_v<bool>{false};
  template<> inline constexpr bool is_integer_v<const bool>{false};
  template<> inline constexpr bool is_integer_v<volatile bool>{false};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a bool, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_bool_v{false};
  template<> inline constexpr bool is_bool_v<bool>{true};
  template<> inline constexpr bool is_bool_v<const bool>{true};
  template<> inline constexpr bool is_bool_v<volatile bool>{true};
  template<> inline constexpr bool is_bool_v<const volatile bool>{true};

} // namespace ti::util