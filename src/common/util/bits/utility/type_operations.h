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
 * @file common/util/bits/utility/type_operations.h 
 * @authors Aaron McBride 
 * @brief Contains utilities that perform operations on types.
 */

#pragma once
#include "common/tmp.h"
#include "common/util/type_traits.h"
#include "common/util/bits/utility/range.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Type Operation Utilities
   **************************************************************************************************/

  /**
   * @brief Initiates a move operation on the given value by 
   *        casting it to an rvalue reference.
   * @tparam T The type of the value to move.
   * @param value The value to move.
   * @returns An rvalue reference to the given value.
   * @see https://en.cppreference.com/w/cpp/utility/move
   */
  template<typename T>
  [[nodiscard]] constexpr T&& move(T&& value);

  /**
   * @brief Forwards the given value as it's original type 
   *        (lvalue or rvalue reference).
   * @tparam T The type of the value to forward (must be a 
   *         deduced template parameter).
   * @param value The value to forward.
   * @returns An rvalue reference to the given value.
   * @see https://en.cppreference.com/w/cpp/utility/forward
   */
  template<typename T>
  [[nodiscard]] constexpr T&& forward(T&& value);

  template<typename T>
  [[nodiscard]] constexpr T&& forward(T& value);

  /**
   * @brief Adds a const qualifier to the given value.
   * @tparam T The type of the value to modify.
   * @param value The value to modify.
   * @returns @p 'value' with a const qualifier added to it's type.
   * @note - The value @p 'T' cannot be a temporary.
   */
  template<typename T> 
  [[nodiscard]] constexpr const T as_const(T& value);

  template<typename T> 
  [[nodiscard]] constexpr const T as_const(T&&) = delete;

  /**
   * @brief Creates an unevaluated value of a specific type.
   * @tparam T The type of the value to create.
   * @returns An unevaluated value of the given type.
   * @note - This method can only be called in unevaluated contexts.
   * @see https://en.cppreference.com/w/cpp/utility/declval
   */
  template<typename T> 
  T declval();

  /**
   * @brief Converts an enumeration value to it's underlying type.
   * @tparam T The enum type of the value.
   * @param enum_value The enumeration value to convert.
   * @returns The underlying value of @p 'enum_value'.
   * @warning - This function requires compiler support.
   */
  template<typename T>
  [[nodiscard]] constexpr auto to_underlying(T&& enum_value);

  /**************************************************************************************************
   * @section Non-Standard Type Operation Utilities
   **************************************************************************************************/

  /**
   * @brief Casts an integral value to a new integral type.
   * @tparam To The integral type to cast to.
   * @tparam From The integral type of the value.
   * @param value The value to cast.
   * @returns @p 'value' cast (losslessly) to @p 'To'.
   * @warning - This function raises a fatal error if @p 'value' is out of
   *          range of @p 'To'.
   */
  template<typename To, typename From>
  [[nodiscard]] constexpr To numeric_cast(const From value);

  /**
   * @brief Casts an integral value to it's signed equivalent.
   * @tparam T The initial integral type of the value.
   * @param value The value to cast.
   * @returns @p 'value' cast (losslessly) to @p 'T's signed equivalent.
   * @warning - This function raises a fatal error if @p 'value' is out of
   *          range of @p 'T's signed equivalent.
   * @note - If @p 'T' is already signed then this function returns
   *       @p 'value' unchanged.
   * @note - The "signed equivalent" of @p 'T' is the signed integral 
   *       type with the same size.
   */
  template<typename T>
  [[nodiscard]] constexpr auto to_signed(const T value);

  /**
   * @brief Casts an integral value to it's unsigned equivalent.
   * @tparam T The initial integral type of the value.
   * @param value The value to cast.
   * @returns @p 'value' cast (losslessly) to @p 'T's unsigned equivalent.
   * @warning - This function raises a fatal error if @p 'value' is out of
   *          range of @p 'T's unsigned equivalent.
   * @note - If @p 'T' is already unsigned then this function returns
   *       @p 'value' unchanged.
   * @note - The "unsigned equivalent" of @p 'T' is the unsigned integral 
   *       type with the same size.
   */
  template<typename T>
  [[nodiscard]] constexpr auto to_unsigned(const T value);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename T>
  [[nodiscard]] constexpr T&& move(T&& value) {
    return static_cast<T&&>(value);
  }

  template<typename T>
  [[nodiscard]] constexpr T&& move<T&>(T&& value) {
    return static_cast<T&&>(value);
  }

  template<typename T>
  [[nodiscard]] constexpr T&& forward(T&& value) {
    return static_cast<T&&>(value);
  }

  template<typename T>
  [[nodiscard]] constexpr T&& forward<T&>(T&& value) {
    return static_cast<T&&>(value);
  }

  template<typename T>
  [[nodiscard]] constexpr T&& forward(T& value) {
    static_assert(!is_lvalue_reference_v<T>, 
        "'T' must be an lvalue reference.");
    return static_cast<T&&>(value);
  }

  template<typename T>
  [[nodiscard]] constexpr T&& forward<T&>(T& value) {
    static_assert(!is_lvalue_reference_v<T>, 
        "'T' must be an lvalue reference.");
    return static_cast<T&&>(value);
  }

  template<typename T> 
  constexpr const T as_const(T& value) {
    return value;
  }

  template<typename T> 
  T declval() {
    static_assert(!sizeof(T), "'declval' cannot be used in an evaluated context.");
  }

  template<typename T>
  constexpr auto to_underlying(T&& enum_value) {
    static_assert(is_enum_v<T>, "'T' must be an enumeration type.");
    using UnderlyingT = underlying_type_t<T>;
    return static_cast<UnderlyingT>(enum_value);
  }

  template<typename To, typename From>
  constexpr To numeric_cast(const From value) {
    static_assert(is_integral_v<To>, "'To' must be an integral type.");
    static_assert(is_integral_v<From>, "'From' must be an integral type.");
    if (!in_range<To>(value)) { sys_error("Value out of range of 'To'"); }
    return static_cast<To>(value);
  }

  template<typename T>
  constexpr auto to_signed(const T value) {
    static_assert(is_integral_v<T>, "'T' must be an integral type.");
    if constexpr (is_integer_v<T> && is_unsigned_v<T>) {
      using SignedType = make_signed_t<T>;
      return numeric_cast<SignedType>(value);
    } else if constexpr (is_bool<T>) {
      return static_cast<int8_t>(value);
    } else {
      return value;
    }
  }

  template<typename T>
  constexpr auto to_unsigned(const T value) {
    static_assert(is_integral_v<T>, "'T' must be an integral type.");
    if constexpr (is_integer_v<T> && is_signed_v<T>) {
      using UnsignedType = make_unsigned_t<T>;
      return numeric_cast<UnsignedType>(value);
    } else if constexpr (is_bool_v<T>) {
      return static_cast<uint8_t>(value);
    } else {
      return value;
    }
  }

  /// @endinternal

} // namespace ti::util