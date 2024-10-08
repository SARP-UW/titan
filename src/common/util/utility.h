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
 * @file common/util/utility.h 
 * @authors Aaron McBride 
 * @brief Contains general-purpose language utilities.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/type_traits.h"
#include "common/util/cstdint.h"
#include "common/tmp.h"
#include <utility>

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
   * @section Standard Type Operation Utilities
   **************************************************************************************************/

  /**
   * @brief Forwards the given value as it's original type (lref or rref).
   * @tparam T The type of the value to forward (must be a deduced type).
   * @param value The value to forward.
   * @returns An rvalue reference to the given value.
   * @see https://en.cppreference.com/w/cpp/utility/forward
   */
  template<typename T>
  [[nodiscard]] constexpr T&& forward(remove_reference_t<T>&& value);

  template<typename T>
  [[nodiscard]] constexpr T&& forward(remove_reference_t<T>& value);

  /**
   * @brief Forwards the given value as a different type while preserving
   *        the value category of the value's original type (lref or rref).
   * @tparam As The type to forward the value as.
   * @tparam T The type of the value to forward (must be a deduced type).
   * @param value The value to forward.
   * @returns A reference to the given value cast to @p 'As'.
   * @see https://en.cppreference.com/w/cpp/utility/forward_like
   */
  template<typename As, typename T>
  [[nodiscard]] constexpr auto&& forward_like(T&& value);

  /**
   * @brief Initiates a move operation on the given value by casting it to an 
   *        rvalue reference.
   * @tparam T The type of the value to move.
   * @param value The value to move.
   * @returns An rvalue reference to the given value.
   * @see https://en.cppreference.com/w/cpp/utility/move
   */
  template<typename T>
  [[nodiscard]] constexpr auto&& move(T&& value);

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
  add_rvalue_reference_t<T> declval();

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
   * @section Standard Numeric Range Utilities
   **************************************************************************************************/

  /**
   * @brief Determines if a value is within the range of a specified type or 
   *        bounded array.
   * @tparam T The integral type or array of integral type that represents the range.
   * @tparam ValueT The integral type of the value.
   * @param value The value to query.
   * @returns If @p 'T' is an integral type: True if @p 'value' is within the 
   *          range of integrals that @p 'T' can represent, or false otherwise.
   * @returns If @p 'T' is an array type: True if @p 'value' is less then the
   *          extent of @p 'T' - 1 or less then 0, and false otherwise.
   */
  template<typename T, typename ValueT>
  [[nodiscard]] constexpr bool in_range(const ValueT value);

  /**************************************************************************************************
   * @section Non-Standard Numeric Range Utilities
   **************************************************************************************************/

  /**
   * @brief Clamps a value to the range of a specific type or array.
   * @tparam T The integral type or array of integral type that represents the range.
   * @tparam ValueT The integral type of the value.
   * @param value The value to clamp.
   * @returns If @p 'T' is an integral: The nearest value to @p 'value' that is 
   *          within the range of integrals that @p 'T' can represent.
   * @returns If @p 'T' is an array: The nearest value to @p 'value' that is
   *          within the extent of @p 'T' - 1 and greater then or equal to 0.
   */
  template<typename T, typename ValueT>
  [[nodiscard]] constexpr ValueT to_range(const ValueT value);

  /**
   * @brief Safely determines if an integral value is within a specified range.
   * @tparam T The integral type of the value to query.
   * @tparam Tmin The integral type of the range's minimum value.
   * @tparam Tmax The integral type of the range's maximum value.
   * @param value The value to query.
   * @param min The range's minimum value (inclusive).
   * @param max The range's maximum value (inclusive).
   * @returns True if @p 'value' is greater then or equal to @p 'min' and less
   *          then or equal to @p 'max', or false otherwise.
   * @note - The behavior of this function is defined regardless of the
   *       signedness of @p 'T', @p 'Tmin', and @p 'Tmax'.
   */
  template<typename T, typename Tmin, typename Tmax>
  [[nodiscard]] constexpr bool in_range(const T& value, const Tmin& min, 
      const Tmax& max);

  /**
   * @brief Clamps an integral value to a specified range (min/max).
   * @tparam T The integral type of the value to clamp.
   * @tparam Tmin The integral type of the range's minimum value.
   * @tparam Tmax The integral type of the range's maximum value.
   * @param value The value to clamp.
   * @param min The range's minimum value (inclusive).
   * @param max The range's maximum value (inclusive).
   * @returns @p 'min' if @p 'value' is less then @p 'min', @p 'max' if 
   *          @p 'value' is greater then @p 'max', or @p 'value' otherwise.
   * @note - The behavior of this function is defined regardless of the
   *       signedness of @p 'T', @p 'Tmin', and @p 'Tmax'.
   */
  template<typename T, typename Tmin, typename Tmax>
  [[nodiscard]] constexpr T to_range(const T& value, const Tmin& min, 
      const Tmax& max);

  /**************************************************************************************************
   * @section Standard Comparison Utilities
   **************************************************************************************************/

  /**
   * @brief Safely determines if two integers of any type are equal.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is equal to @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_equal(const Tl l_value, const Tr r_value);

  /**
   * @brief Safely determines if one integer of any type is less than
   *        annother integer of any type.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is less then @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_less(const Tl l_value, const Tr r_value);
  
  /**
   * @brief Safely determines if one integer of any type is greater than
   *        annother integer of any type.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is greater then @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_greater(const Tl l_value, const Tr r_value);

  /**
   * @brief Safely determines if one integer of any type is less than
   *        or equal to annother integer of any type.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is less then or equal to @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_less_equal(const Tl l_value, const Tr r_value);

  /**
   * @brief Safely determines if one integer of any type is greater than
   *        or equal to annother integer of any type.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is greater then or equal to @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_greater_equal(const Tl l_value, const Tr r_value);

  /************************************************************************************************
   * @section Standard Language Support Utilities
   ***********************************************************************************************/

  /**
   * @brief Informs the compiler that a location in code is unreachable.
   * @note - Use to denote actually unreachable locations in code,
   *       not to denote locations where an error should be triggered.
   */
  TI_ATTR_ALWAYS_INLINE_FN [[noreturn]] inline constexpr void unreachable();

  /************************************************************************************************
   * @section Non-Standard Language Support Utilities
   ***********************************************************************************************/

  /**
   * @brief Informs the compiler that a condition is likely to be true.
   * @param cond The boolean condition that is likely to be true.
   * @param perc An int32_t which denotes the percent (0 - 100) likelihood that 
   *        @p 'cond' is true (defaults to 100).
   * @returns A boolean value equal to @p 'cond'.
   */
  TI_ATTR_ALWAYS_INLINE_FN inline constexpr bool likely(
      const bool cond, const int32_t perc = 100);

  /**
   * @brief Informs the compiler that a condition is likely to be false.
   * @param cond The boolean condition that is likely to be false.
   * @param perc An int32_t which denotes the percent (0 - 100) likelihood that
   *        @p 'cond' is false (defaults to 100).
   * @returns A boolean value equal to @p 'cond'.
   */
  TI_ATTR_ALWAYS_INLINE_FN inline constexpr bool unlikely(
      const bool cond, const int32_t perc = 100);

  /**************************************************************************************************
   * @section Standard Tag Type Declarations
   **************************************************************************************************/

  /**
   * @brief Tag type used to indicate in-place construction of a specific type.
   * @tparam T The type to construct in-place.
   */
  template<typename T> 
  struct in_place_type_t;

  /**
   * @brief Tag type value used to indicate in-place construction of a specific type.
   * @tparam T The type to construct in-place.
   */
  template<typename T> 
  inline constexpr in_place_type_t<T> in_place_type{};

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

  template<typename T>
  constexpr auto&& move(T&& value) {
    using BaseT = remove_reference_t<T>;
    return static_cast<BaseT&&>(value);
  }

  template<typename T>
  constexpr T&& forward(remove_reference_t<T>&& value) {
    static_assert(!is_rvalue_reference_v<T>, 
        "'T' must be an rvalue reference.");
    return static_cast<T&&>(value);
  }

  template<typename T>
  constexpr T&& forward(remove_reference_t<T>& value) {
    return static_cast<T&&>(value);
  }

  template<typename As, typename T>
  constexpr auto&& forward_like(T&& value) {
    if constexpr (is_lvalue_reference_v<As&&>) {
      if constexpr (is_const_v<remove_reference_t<As>>) {
        return as_const(value);
      } else {
        return static_cast<T&>(value);
      }
    } else if constexpr (is_const_v<remove_reference_t<As>>) {
      return move(as_const(value));
    } else {
      return move(value);
    }
  }

  template<typename T> 
  constexpr const T as_const(T& value) {
    return value;
  }

  template<typename T> 
  add_rvalue_reference_t<T> declval() {
    static_assert(false, "'declval' cannot be used in an evaluated context.");
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

  template<typename T, typename ValueT>
  constexpr bool in_range(const ValueT value) {
    static_assert(is_integral_v<ValueT>, "'ValueT' must be an integral type.");
    using ValueLim = numeric_limits<ValueT>;

    if (is_bounded_array_v<T>) {
      using BaseT = remove_all_extents_t<T>;
      static_assert(is_integral_v<BaseT>, "'T[]' must be an integral type.");
      if constexpr (cmp_less(extent_v<T>, ValueLim::max())) {
        if (cmp_greater_equal(value, extent_v<T>)) { return false; }
      }
    } else {
      static_assert(is_integral_v<T>, "'T' must be an integral type.");
      using RangeLim = numeric_limits<T>;
      if constexpr (cmp_greater(ValueLim::max(), RangeLim::max())) {
        if (cmp_greater(value, RangeLim::max())) { return false; }
      }
      if constexpr (cmp_less(ValueLim::lowest(), RangeLim::lowest())) {
        if (cmp_less(value, RangeLim::lowest())) { return false; }
      }
    }
    return true;
  }

  template<typename T, typename ValueT>
  constexpr ValueT to_range(const ValueT value) {
    static_assert(is_integral_v<ValueT>, "'ValueT' must be an integral type.");
    using ValueLim = numeric_limits<ValueT>;
    
    if constexpr (is_bounded_array_v<T>) {
      using BaseT = remove_all_extents_t<T>;
      static_assert(is_integral_v<BaseT>, "'T[]' must be an integral type.");
      if constexpr (is_signed_v<ValueT>) {
        if (cmp_less(value, 0)) { return ValueT{0}; }
      }
      if constexpr (cmp_less(extent_v<T>, ValueLim::max())) {
        if cmp_greater_equal(value, extent_v<T>) { 
          return static_cast<ValueT>(extent_v<T> - 1);
        }
      }
    } else {
      static_assert(is_integral_v<T>, "'T' must be an integral type.");
      using RangeLim = numeric_limits<T>;
      if constexpr (cmp_greater(ValueLim::max(), RangeLim::max())) {
        if (cmp_less(value, RangeLim::max())) {
          return static_cast<ValueT>(RangeLim::max());
        }
      }
      if constexpr (cmp_less(ValueLim::lowest(), RangeLim::lowest())) {
        if (cmp_less(value, RangeLim::lowest())) {
          return static_cast<ValueT>(RangeLim::lowest());
        }
      }
    }
    return value;
  }

  template<typename T, typename Tmin, typename Tmax>
  constexpr bool in_range(const T& value, const Tmin& min, const Tmax& max) {
    static_assert(is_integral_v<T>, "'T' must be an integral type.");
    static_assert(is_integral_v<Tmin>, "'Tmin' must be an integral type.");  
    static_assert(is_integral_v<Tmax>, "'Tmax' must be an integral type.");

    if (cmp_greater(min, max)) { sys_error("'min' is greater then 'max'"); }
    return cmp_greater_equal(value, min) && cmp_less_equal(value, max);
  }

  template<typename T, typename Tmin, typename Tmax>
  constexpr T to_range(const T& value, const Tmin& min, const Tmax& max) {
    static_assert(is_integral_v<T>, "'T' must be an integral type.");
    static_assert(is_integral_v<Tmin>, "'Tmin' must be an integral type.");
    static_assert(is_integral_v<Tmax>, "'Tmax' must be an integral type.");

    using ValueLim = numeric_limits<T>;
    using MinLim = numeric_limits<Tmin>;
    using MaxLim = numeric_limits<Tmax>;

    if (cmp_less(min, max)) { 
      sys_error("'min' is greater then 'max'"); 
    }
    if (cmp_less(value, min)) { 
      if constexpr (cmp_greater(MinLim::max(), ValueLim::max())) {
        if (cmp_greater(min, ValueLim::max())) {
          sys_error("'min' is out of range of 'T'.");
        }
      }
      return static_cast<T>(min); 
    }
    if (cmp_greater(value, max)) {
      if constexpr (cmp_less(MaxLim::lowest(), ValueLim::lowest())) {
        if (cmp_less(max, ValueLim::lowest())) {
          sys_error("'max' is out of range of 'T'.");
        }
      }
      return static_cast<T>(max); 
    }
    return value;
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_equal(const Tl l_value, const Tr r_value) {
    using PromType = promoted_type_t<Tl, Tr>;

    if constexpr (is_integer_v<Tl> && is_integer_v<Tr> && is_unsigned_v<PromType>) {
      if constexpr (is_signed_v<Tl> && is_unsigned_v<Tr>) {
        using UnsignedType = make_unsigned_t<Tl>;
        return l_value >= Tl{0} && static_cast<UnsignedType>(l_value) == r_value;
      } 
      if constexpr (is_unsigned_v<Tl> && is_signed_v<Tr>) {
        using UnsignedType = make_unsigned_t<Tr>;
        return r_value >= Tr{0} && l_value == static_cast<UnsignedType>(r_value);
      }
    }
    return l_value == r_value;
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_less(const Tl l_value, const Tr r_value) {
    using PromType = promoted_type_t<Tl, Tr>;
    
    if constexpr (is_integer_v<Tl> && is_integer_v<Tr> && is_unsigned_v<PromType>) {
      if constexpr (is_signed_v<Tl> && is_unsigned_v<Tr>) {
        using UnsignedType = make_unsigned_t<Tl>;
        return l_value < Tl{0} || static_cast<UnsignedType>(l_value) < r_value;
      } 
      if constexpr (is_unsigned_v<Tl> && is_signed_v<Tr>) {
        using UnsignedType = make_unsigned_t<Tr>;
        return r_value >= Tr{0} && l_value < static_cast<UnsignedType>(r_value);
      }
    }
    return l_value < r_value;
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_greater(const Tl l_value, const Tr r_value) {
    return cmp_less(r_value, l_value);
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_less_equal(const Tl l_value, const Tr r_value) {
    return !cmp_less(r_value, l_value);
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_greater_equal(const Tl l_value, const Tr r_value) {
    return !cmp_less(l_value, r_value);
  }

  inline constexpr void unreachable() {
    #if defined(TI_DEBUG)
      TI_BUILTIN_TRAP();
    #else
      TI_BUILTIN_UNREACHABLE();
    #endif
  }

  inline constexpr bool likely(const bool cond, const int32_t perc) {
    if (in_range(perc, 0, 100)) { sys_error("'perc' is out of range."); }
    return TI_BUILTIN_EXPECT_PROB(cond, true, perc / 100);
  }

  inline constexpr bool unlikely(const bool cond, const int32_t perc) {
    if (in_range(perc, 0, 100)) { sys_error("'perc' is out of range."); }
    return TI_BUILTIN_EXPECT_PROB(cond, false, perc / 100);
  } 

  template<typename T> 
  struct in_place_type_t {
    constexpr explicit in_place_type_t() = default;
  };

  /// @endinternal

} // namespace ti::util