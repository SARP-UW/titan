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
 * @file common/util/bits/utility/value_operations.h 
 * @authors Aaron McBride 
 * @brief Contains utilities that perform operations on values.
 */

#pragma once
#include "common/util/type_traits.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Value Operation Utilities
   **************************************************************************************************/

  /**
   * @brief Swaps the values of two objects.
   * @tparam T The type of the first value.
   * @tparam U The type of the second value.
   * @param value_a The first value to swap.
   * @param value_b The second value to swap.
   * @note - @p 'value_a' and @p 'value_b' must be cross-assignable.
   */
  template<typename T, typename U>
  [[nodiscard]] constexpr void swap(T&& value_a, U&& value_b);

  /**
   * @brief Exchanges the value of an object with another and returns
   *        the original value.
   * @tparam T The type of the value to exchange.
   * @tparam U The type of the value to assign to @p 'value'.
   * @param value The value to exchange.
   * @param other The value to assign to @p 'value'.
   */
  template<typename T, typename U>
  [[nodiscard]] constexpr T exchange(T& value, U&& other);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename T, typename U>
  [[nodiscard]] constexpr void swap(T&& value_a, U&& value_b) {
    static_assert(is_assignable_v<T, U&&>,
        "'T' must be assignable from 'U&&'.");
    static_assert(is_assignable_v<U, T&&>,
        "'U' must be assignable from 'T&&'.");
    if constexpr (is_constructible_v<T, T&&>) {
      T temp{static_cast<T&&>(value_a)};
      value_a = static_cast<U&&>(value_b);
      value_b = static_cast<T&&>(temp);
    } else if constexpr (is_constructible_v<U, U&&>) {
      U temp{static_cast<U&&>(value_b)};
      value_b = static_cast<T&&>(value_a);
      value_a = stati_cast<U&&>(temp);
    } else {
      static_assert(false, "'T' or 'U' must be move constructible.");
    }
  }
  template<typename T, typename U, auto N>
  [[nodiscard]] constexpr void swap(T (&value_a)[N], U (&value_b)[N]) {
    for (decltype(N) i{0}; i < N; ++i) { 
      swap(value_a[i], value_b[i]); 
    }
  }

  template<typename T, typename U>
  [[nodiscard]] constexpr T exchange(T& value, U&& other) {
    static_assert(is_assignable_v<T&, U>,
        "'T' must be assignable from 'U'.");
    static_assert(is_constructible_v<T, T&>,
        "'T' must be move constructible.");
    T old_value{static_cast<T&&>(value)};
    if constexpr (std::is_lvalue_reference_v<U>) {
      value = other;
    } else {
      value = static_cast<U&&>(other);
    }
    return old_value;
  }

  /// @endinternal

} // namespace ti::util