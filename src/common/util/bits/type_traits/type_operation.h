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
 * @brief Contains type traits for querying operations on/between types.
 */

#pragma once

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    template<typename T> T value;

    // Implementation for 'is_constructible_v'.
    template<typename, typename T, typename... Args>
    inline constexpr bool ctor_test_v{false};

    template<typename T, typename... Args>
    inline constexpr bool ctor_test_v<decltype(
        void(T{value<Args>...})), T, Args...>{true};

    // Implementation for 'is_default_constructible_v'.
    template<typename T, typename = void>
    inline constexpr bool test_default_ctor_v{false};

    template<typename T>
    inline constexpr bool test_default_ctor_v<T, decltype(
        void(T{}))>{true};

    // Implementation for 'is_assignable_v'.
    template<typename T, typename U, typename = void>
    inline constexpr bool assign_test_v{false};

    template<typename T, typename U>
    inline constexpr bool assign_test_v<T, U, decltype(
        void(value<T> = value<U>))>{true};

    // Implementation for 'is_equality_comparable_v'.
    template<typename T, typename U, typename = void>
    inline constexpr bool eq_cmp_test_v{false};

    template<typename T, typename U>
    inline constexpr bool eq_cmp_test_v<T, U, decltype(
        void(value<T> == value<U>), void(value<T> != value<U>))>{true};

    // Implementation for 'is_comparable_v'.
    template<typename T, typename U, typename = void>
    inline constexpr bool cmp_test_v{false};

    template<typename T, typename U>
    inline constexpr bool cmp_test_v<T, U, decltype(
        void(value<T> < value<U>), void(value<T> > value<U>),
        void(value<T> >= value<U>), void(value<T> <= value<U>))>{true};

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section Standard Type Operation Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is constructible with the argument types, or false otherwise.
   * @tparam T The type to construct.
   * @tparam ...Args The argument types to attempt construction with.
   */
  template<typename T, typename... Args>
  inline constexpr bool is_constructible_v{ctor_test_v<void, T, Args...>};

  /**
   * @brief Template bool value that evaluates to true if the given type is
   *        default constructible, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T>
  inline constexpr bool is_default_constructible_v{test_default_ctor_v<T>};

  /**
   * @brief Template bool value that evaluates to true if the given type is
   *        copy constructible, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T>
  inline constexpr bool is_copy_constructible_v{is_constructible_v<T, const T&>};

  /**
   * @brief Template bool value that evaluates to true if the given type is
   *        move constructible, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T>
  inline constexpr bool is_move_constructible_v{is_constructible_v<T, T&&>};

  /**
   * @brief Template bool value that evaluates to true if one type is
   *        assignable to annother, or false otherwise.
   * @tparam T The type to assign to.
   * @tparam U The type to assign from.
   */
  template<typename T, typename U>
  inline constexpr bool is_assignable_v{assign_test_v<T, U>};

  /**
   * @brief Template bool value that evaluates to true if the given type is
   *        copy assignable, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T>
  inline constexpr bool is_copy_assignable_v{is_assignable_v<T&, const T&>};

  /**
   * @brief Template bool value that evaluates to true if the given type is
   *        move assignable, or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T>
  inline constexpr bool is_move_assignable_v{is_assignable_v<T&, T&&>};

  /**
   * @brief Template bool value that evaluates to true if the given type is
   *        destructible (default or custom), or false otherwise.
   * @tparam T The type to query.
   */
  template<typename T>
  inline constexpr bool is_destructible_v{test_dtor_v<T>}; 

  /**************************************************************************************************
   * @section Non-Standard Type Operation Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if the given types
   *        are equality comparable (==, !=), or false otherwise.
   * @tparam T The left-hand type to compare.
   * @tparam U The right-hand type to compare.
   */
  template<typename T, typename U>
  inline constexpr bool is_equality_comparable_v{eq_cmp_test_v<T, U>};

  /**
   * @brief Template bool value that evaluates to true if the given types
   *        are fully comparable (<, >, <=, >=, ==, !=), or false otherwise.
   * @tparam T The left-hand type to compare.
   * @tparam U The right-hand type to compare.
   */
  template<typename T, typename U>
  inline constexpr bool is_comparable_v{cmp_test_v<T, U> && eq_cmp_test_v<T, U>};

} // namespace ti::util