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
 * @file common/util/bits/type_traits/type_property.h 
 * @authors Aaron McBride 
 * @brief Contains type traits for querying type properties.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    // Implementation for 'is_signed_v'
    template<typename T> inline constexpr bool raw_signed_v{false};
    template<> inline constexpr bool raw_signed_v<signed char>{true};
    template<> inline constexpr bool raw_signed_v<signed short int>{true};
    template<> inline constexpr bool raw_signed_v<signed int>{true};
    template<> inline constexpr bool raw_signed_v<signed long int>{true};
    template<> inline constexpr bool raw_signed_v<signed long long int>{true};

    // Implementation for 'is_unsigned_v'
    template<typename T> inline constexpr bool raw_unsigned_v{false};
    template<> inline constexpr bool raw_unsigned_v<unsigned char>{true};
    template<> inline constexpr bool raw_unsigned_v<unsigned short int>{true};
    template<> inline constexpr bool raw_unsigned_v<unsigned int>{true};
    template<> inline constexpr bool raw_unsigned_v<unsigned long int>{true};
    template<> inline constexpr bool raw_unsigned_v<unsigned long long int>{true};

    template<typename T, size_t N = 0>
    struct ExtentImpl { 
      static constexpr size_t value{0}; 
    };

    template<typename T>
    struct ExtentImpl<T[], 0> { 
      static constexpr size_t value{0}; 
    };

    template<typename T, size_t N>
    struct ExtentImpl<T[], N> { 
      static constexpr size_t value{ExtentImpl<T, N - 1>::value}; 
    };

    template<typename T, size_t I>
    struct ExtentImpl<T[I], 0> { 
      static constexpr size_t value{I}; 
    };

    template<typename T, size_t I, size_t N>
    struct ExtentImpl<T[I], N> { 
      static constexpr size_t value{ExtentImpl<T, N - 1>::value}; 
    };

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section Standard Type Property Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is (top-level) const qualified, false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_const_v{false};
  template<typename T> inline constexpr bool is_const_v<const T>{true};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is (top-level) volatile qualified, false otherwise.
   * @tparam T The type to query.
   */  
  template<typename T> inline constexpr bool is_volatile_v{false};
  template<typename T> inline constexpr bool is_volatile_v<volatile T>{true};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is trivial, or false otherwise.
   * @tparam T The type to query.
   * @warning - This trait requires compiler support!
   * @see https://en.cppreference.com/w/cpp/named_req/TrivialType
   */
  template<typename T>
  inline constexpr bool is_trivial_v{TI_BUILTIN_IS_TRIVIAL(T)};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is trivially copyable, or false otherwise.
   * @tparam T The type to query.
   * @warning - This trait requires compiler support!
   * @see https://en.cppreference.com/w/cpp/named_req/TriviallyCopyable
   */
  template<typename T>
  inline constexpr bool is_trivially_copyable_v{
      TI_BUILTIN_IS_TRIVIALLY_COPYABLE(T)};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a standard layout type, or false otherwise.
   * @tparam T The type to query.
   * @warning - This trait requires compiler support!.
   * @see https://en.cppreference.com/w/cpp/named_req/StandardLayoutType
   */
  template<typename T>
  inline constexpr bool is_standard_layout_v{
      TI_BUILTIN_IS_STANDARD_LAYOUT(T)};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a signed type, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_signed_v{raw_signed_v<T>};
  template<typename T> inline constexpr bool is_signed_v<const T>{raw_signed_v<T>};
  template<typename T> inline constexpr bool is_signed_v<volatile T>{raw_signed_v<T>};
  template<typename T> inline constexpr bool is_signed_v<const volatile T>{raw_signed_v<T>};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is an unsigned type, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T> inline constexpr bool is_unsigned_v{raw_unsigned_v<T>};
  template<typename T> inline constexpr bool is_unsigned_v<const T>{raw_unsigned_v<T>};
  template<typename T> inline constexpr bool is_unsigned_v<volatile T>{raw_unsigned_v<T>};
  template<typename T> inline constexpr bool is_unsigned_v<const volatile T>{raw_unsigned_v<T>};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is an unbounded array type, or false otherwise.
   * @tparam T The type to query.
   * @note - An "unbounded" array type is an array type with no specified size.
   */
  template<typename T> inline constexpr bool is_unbounded_array_v{false};
  template<typename T> inline constexpr bool is_unbounded_array_v<T[]>{true};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a bounded array type, or false otherwise.
   * @tparam T The type to query.
   * @note - A "bounded" array type is an array type with a specified size.
   */
  template<typename T> inline constexpr bool is_bounded_array_v{false};
  template<typename T, size_t N> inline constexpr bool is_bounded_array_v<T[N]>{true}; 

  /**
   * @brief Gets the extent (length) of an array type in a specific dimension.
   * @tparam T The array type to query.
   * @tparam N A size_t NTTP that denotes the array dimension to query.
   */
  template<typename T, size_t N = 0>
  inline constexpr size_t extent_v{ExtentImpl<T, N>::value};

} // namespace ti::util