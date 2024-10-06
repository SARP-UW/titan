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
 * @file common/util/bits/type_traits/type_relationship.h 
 * @authors Aaron McBride 
 * @brief Contains type traits for querying type relationships.
 */

#pragma once

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    template<typename T> T value;

    // Implementation for 'is_convertible_v'.
    template<typename From, typename To, typename = void>
    inline constexpr bool convert_test_v{false};

    template<typename From, typename To>
    inline constexpr bool convert_test_v<From, To, decltype(
        void(value<void (&)(To)>(value<From>)),
        void(static_cast<To(*)()>(nullptr)))>{true};

    // Implementation for 'is_invocable_v'.
    template<typename Enable, typename F, typename... Args>
    inline constexpr bool invoke_test_v{false};

    template<typename F, typename... Args>
    inline constexpr bool invoke_test_v<decltype(
        void(value<F>(value<Args>...))), F, Args...>{true};

  } // namespace anonymous

  /// @endinternal

  /**************************************************************************************************
   * @section Standard Type Relationship Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if the given types
   *        are the same type (including qualifiers), or false otherwise.
   * @tparam T The first type to compare.
   * @tparam U The second type to compare.
   */
  template<typename T, typename U> inline constexpr bool is_same_v{false};
  template<typename T, typename U> inline constexpr bool is_same_v<T, T>{true};

  /**
   * @brief Template bool value that evaluates to true if the given types
   *        are implicitly convertible, or false otherwise.
   * @tparam From The type to convert from.
   * @tparam To The type to convert to.
   * @note - This trait only tests for convertions in one direction (From -> To).
   */
  template<typename From, typename To> 
  inline constexpr bool is_convertible_v{convert_test_v<From, To>};

  /**
   * @brief Template bool value that evaluates to true if the given types
   *        is invocable with the argument types, or false otherwise.
   * @tparam F The type of the callable to invoke.
   * @tparam ...Args The argument types to attempt the invocation with.
   */
  template<typename F, typename... Args>
  inline constexpr bool is_invocable_v{invocable_test_v<void, F, Args...>};

} // namespace ti::util