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
 * @file common/util/bits/type_traits/type_transformation.h 
 * @authors Aaron McBride 
 * @brief Contains type traits that transform types.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    template<typename T> T value;

    // Implementation for 'remove_const_t'.
    template<typename T> struct R_ConstImpl { using Type = T; };
    template<typename T> struct R_ConstImpl<const T> { using Type = T; };

    // Implementation for 'remove_volatile_t'.
    template<typename T> struct R_VolatileImpl { using Type = T; };
    template<typename T> struct R_VolatileImpl<volatile T> { using Type = T; };

    // Implementation for 'remove_lvalue_reference_t'.
    template<typename T> struct R_LrefImpl { using Type = T; };
    template<typename T> struct R_LrefImpl<T&> { using Type = T; };

    // Implementation for 'remove_rvalue_reference_t'.
    template<typename T> struct R_RrefImpl { using Type = T; };
    template<typename T> struct R_RrefImpl<T&&> { using Type = T; };

    // Implementation for 'remove_pointer_t'.
    template<typename T> struct R_PtrImpl { using Type = T; };
    template<typename T> struct R_PtrImpl<T*> { using Type = T; };

    // Implementation for 'make_signed_v'
    template<typename T> struct SignedSelector { using Type = T; };
    template<> struct SignedSelector<unsigned char> { using Type = signed char; };
    template<> struct SignedSelector<unsigned short int> { using Type = signed short int; };
    template<> struct SignedSelector<unsigned int> { using Type = signed int; };
    template<> struct SignedSelector<unsigned long int> { using Type = signed long int; };
    template<> struct SignedSelector<unsigned long long int> { using Type = signed long long int; };

    template<> struct SignedSelector<const unsigned char> { using Type = const signed char; };
    template<> struct SignedSelector<const unsigned short int> { using Type = const signed short int; };
    template<> struct SignedSelector<const unsigned int> { using Type = const signed int; };
    template<> struct SignedSelector<const unsigned long int> { using Type = const signed long int; };
    template<> struct SignedSelector<const unsigned long long int> { using Type = const signed long long int; };

    template<> struct SignedSelector<volatile unsigned char> { using Type = volatile signed char; };
    template<> struct SignedSelector<volatile unsigned short int> { using Type = volatile signed short int; };
    template<> struct SignedSelector<volatile unsigned int> { using Type = volatile signed int; };
    template<> struct SignedSelector<volatile unsigned long int> { using Type = volatile signed long int; };
    template<> struct SignedSelector<volatile unsigned long long int> { using Type = volatile signed long long int; };

    template<> struct SignedSelector<const volatile unsigned char> { using Type = const volatile signed char; };
    template<> struct SignedSelector<const volatile unsigned short int> { using Type = const volatile signed short int; };
    template<> struct SignedSelector<const volatile unsigned int> { using Type = const volatile signed int; };
    template<> struct SignedSelector<const volatile unsigned long int> { using Type = const volatile signed long int; };
    template<> struct SignedSelector<const volatile unsigned long long int> { using Type = const volatile signed long long int; };
    
    // Implementation for 'make_unsigned_v'
    template<typename T> struct UnsignedSelector { using Type = T; };
    template<> struct UnsignedSelector<signed char> { using Type = unsigned char; };
    template<> struct UnsignedSelector<signed short int> { using Type = unsigned short int; };
    template<> struct UnsignedSelector<signed int> { using Type = unsigned int; };
    template<> struct UnsignedSelector<signed long int> { using Type = unsigned long int; };
    template<> struct UnsignedSelector<signed long long int> { using Type = unsigned long long int; };

    template<> struct UnsignedSelector<const signed char> { using Type = const unsigned char; };
    template<> struct UnsignedSelector<const signed short int> { using Type = const unsigned short int; };
    template<> struct UnsignedSelector<const signed int> { using Type = const unsigned int; };
    template<> struct UnsignedSelector<const signed long int> { using Type = const unsigned long int; };
    template<> struct UnsignedSelector<const signed long long int> { using Type = const unsigned long long int; };

    template<> struct UnsignedSelector<volatile signed char> { using Type = volatile unsigned char; };
    template<> struct UnsignedSelector<volatile signed short int> { using Type = volatile unsigned short int; };
    template<> struct UnsignedSelector<volatile signed int> { using Type = volatile unsigned int; };
    template<> struct UnsignedSelector<volatile signed long int> { using Type = volatile unsigned long int; };
    template<> struct UnsignedSelector<volatile signed long long int> { using Type = volatile unsigned long long int; };

    template<> struct UnsignedSelector<const volatile signed char> { using Type = const volatile unsigned char; };
    template<> struct UnsignedSelector<const volatile signed short int> { using Type = const volatile unsigned short int; };
    template<> struct UnsignedSelector<const volatile signed int> { using Type = const volatile unsigned int; };
    template<> struct UnsignedSelector<const volatile signed long int> { using Type = const volatile unsigned long int; };
    template<> struct UnsignedSelector<const volatile signed long long int> { using Type = const volatile unsigned long long int; };

    // Implementation for 'remove_extent_t'.
    template<typename T> struct R_ExtentImpl { using Type = T; };
    template<typename T> struct R_ExtentImpl<T[]> { using Type = T; };
    template<typename T, size_t N> struct R_ExtentImpl<T[N]> { using Type = T; };

    // Implementation for 'remove_all_extents_t'.
    template<typename T> struct R_AllExtentImpl { using Type = T; };
    template<typename T> struct R_AllExtentImpl<T[]> { using Type = typename R_AllExtentImpl<T>::Type; };
    template<typename T, size_t N> struct R_AllExtentImpl<T[N]> { using Type = typename R_AllExtentImpl<T>::Type};    

    // Implementation for 'decay_t'.
    template<typename T> struct DecayImpl { using Type = T; };
    template<typename T> struct DecayImpl<T&> { using Type = T; };
    template<typename T> struct DecayImpl<T&&> { using Type = T; };

    template<typename T> struct DecayImpl<const T> { using Type = T; };
    template<typename T> struct DecayImpl<const T&> { using Type = T; };
    template<typename T> struct DecayImpl<const T&&> { using Type = T; };

    template<typename T> struct DecayImpl<volatile T> { using Type = T; };
    template<typename T> struct DecayImpl<volatile T&> { using Type = T; };
    template<typename T> struct DecayImpl<volatile T&&> { using Type = T; };

    template<typename T> struct DecayImpl<const volatile T> { using Type = T; };
    template<typename T> struct DecayImpl<const volatile T&> { using Type = T; };
    template<typename T> struct DecayImpl<const volatile T&&> { using Type = T; };

    template<typename T> struct DecayImpl<T[]> { using Type = T*; };
    template<typename T> struct DecayImpl<T(&)[]> { using Type = T*; };
    template<typename T> struct DecayImpl<T(&&)[]> { using Type = T*; };

    template<typename T, size_t N> struct DecayImpl<T[N]> { using Type = T*; };
    template<typename T, size_t N> struct DecayImpl<T(&)[N]> { using Type = T*; };
    template<typename T, size_t N> struct DecayImpl<T(&&)[N]> { using Type = T*; };

    template<typename R, typename... Args> struct DecayImpl<R(Args...)> { using Type = R(*)(Args...); };

    // Implementation for 'enable_if_t'.
    template<bool cond, typename T> struct EnableType {};
    template<typename T> struct EnableType<true, T> { using Type = T; };

    // Implementation for 'conditional_t'.
    template<bool cond, typename FalseT, typename TrueT> 
    struct CondType { using Type = TrueT; };

    template<typename FalseT, typename TrueT> 
    struct CondType<false, FalseT, TrueT> { using Type = FalseT; };

  } // namespace anonymous

  /// @endinternal

  /**************************************************************************************************
   * @section Standard CV Transformation Traits
   **************************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the given type with
   *        (top-level) const qualifiers removed.
   * @tparam T The type to modify.
   */
  template<typename T> 
  using remove_const_t = typename R_ConstImpl<T>::Type;

  /**
   * @brief Template type alias that evaluates to the given type with
   *        (top-level) volatile qualifiers removed.
   * @tparam T The type to modify.
   */
  template<typename T> 
  using remove_volatile_t = typename R_VolatileImpl<T>::Type;

  /**
   * @brief Template type alias that evaluates to the given type with
   *        const and volatile qualifiers removed.
   * @tparam T The type to modify.
   * @see remove_const_t
   * @see remove_volatile_t
   */
  template<typename T> 
  using remove_cv_t = remove_const_t<remove_volatile_t<T>>; 

  /**
   * @brief Template type alias that evaluates to the given type with a
   *        (top-level) const qualifier added.
   * @tparam T The type to modify.
   */
  template<typename T> 
  using add_const_t = const T;

  /**
   * @brief Template type alias that evaluates to the given type with a
   *        (top-level) volatile qualifier added.
   * @tparam T The type to modify.
   */
  template<typename T> 
  using add_volatile_t = volatile T;

  /**
   * @brief Template type alias that evaluates to the given type with
   *        (top-level) const and volatile qualifiers added.
   * @tparam T The type to modify.
   * @see add_const_t
   * @see add_volatile_t
   */
  template<typename T> 
  using add_cv_t = add_const_t<add_volatile_t<T>>;

  /**************************************************************************************************
   * @section Standard Reference Transformation Traits
   **************************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the given type with
   *        reference modifiers removed (l_value or r_value).
   * @tparam T The type to modify.
   */
  template<typename T> 
  using remove_reference_t = typename R_RrefImpl<typename R_LrefImpl<T>::Type>::Type;

  /**
   * @brief Template type alias that evaluates to the given type with an
   *        l_value reference modifier added.
   * @tparam T The type to modify.
   */
  template<typename T> 
  using add_lvalue_reference_t = T&;

  /**
   * @brief Template type alias that evaluates to the given type with an
   *        r_value reference modifier added.
   * @tparam T The type to modify.
   */
  template<typename T> 
  using add_rvalue_reference_t = T&&;

  /**************************************************************************************************
   * @section Standard Pointer Transformation Traits
   **************************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the given type with
   *        pointer modifiers removed.
   * @tparam T The type to modify.
   */
  template<typename T> 
  using remove_pointer_t = typename R_PtrImpl<T>::Type;

  /**
   * @brief Template type alias that evaluates to the given type with a
   *        pointer modifier added.
   * @tparam T The type to modify.
   */
  template<typename T> 
  using add_pointer_t = T*;

  /**************************************************************************************************
   * @section Standard Signedness Transformation Traits
   **************************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the signed equivalent of a 
   *        given integer type.
   * @tparam T The integer type to make signed.
   * @note - The "signed equivalent" of an unsigned integer type is the signed 
   *         integer type with the same size.
   * @note - If the given type is already signed, this alias does nothing.
   */
  template<typename T> 
  using make_signed_t = typename SignedSelector<T>::Type;

  /**
   * @brief Template type alias that evaluates to the unsigned equivalent of a
   *        given integer type.
   * @tparam T The integer type to make unsigned.
   * @note - The "unsigned equivalent" of a signed integer type is the unsigned
   *         integer type with the same size.
   * @note - If the given type is already signed, this alias does nothing.
   */
  template<typename T> 
  using make_unsigned_t = typename UnsignedSelector<T>::Type;

  /**************************************************************************************************
   * @section Standard Array Transformation Traits
   **************************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the given type with the 
   *        top-most array (bounded/unbounded) modifier removed.
   * @tparam T The type to modify.
   */
  template<typename T>
  using remove_extent_t = typename R_ExtentImpl<T>::Type;

  /**
   * @brief Template type alias that evaluates to the given type with ALL array
   *        (bounded/unbounded) modifiers removed (regardless of rank).
   * @tparam T The type to modify.
   */
  template<typename T>
  using remove_all_extents_t = typename R_AllExtentImpl<T>::Type;

  /**************************************************************************************************
   * @section Standard Miscellaneous Type Transformation Traits
   **************************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the decayed version of the
   *        given type (no cv, ref, or array qualifiers... etc).
   * @tparam T The type to decay.
   * @see https://en.cppreference.com/w/cpp/types/decay
   */
  template<typename T> 
  using decay_t = typename DecayImpl<T>::Type;

  /**
   * @brief Template type alias that evaluates to the given type with all (top-level)
   *        const, volatile and reference qualifiers/modifiers removed.
   * @tparam T The type to modify.
   */
  template<typename T>
  using remove_cvref_t = remove_cv_t<remove_reference_t<T>>;

  /**
   * @brief Template type alias that evaluates to the underlying version of the
   *        given enumeration type.
   * @tparam T The enumeration type to query.
   */
  template<typename T>
  using underlying_type_t = TI_BUILTIN_UNDERLYING_TYPE(T);

  /**
   * @brief Template type alias that evaluates to a specific type if the given
   *        condition is true, or no type if the condition is false (SFINAE).
   * @tparam cond The boolean condition (NTTP).
   * @tparam T The type to conditionally evaluate to (defaults to void).
   */
  template<bool cond, typename T = void>
  using enable_if_t = typename EnableType<cond, T>::Type;

  /**
   * @brief Template type alias that evaluates to one type if the given condition
   *        is true, or annother if it is false.
   * @tparam cond The boolean condition (NTTP).
   * @tparam TrueT The type to evaluate to if @p 'cond' is true.
   * @tparam FalseT The type to evaluate to if @p 'cond' is false.
   */
  template<bool cond, typename TrueT, typename FalseT>
  using conditional_t = typename CondType<cond, FalseT, TrueT>::Type;

  /**
   * @brief Template type alias that evaluates to the result of invoking the
   *        given callable with the given set of arguments.
   * @tparam F The callable type to invoke.
   * @tparam ...Args The argument types to invoke the callable with.
   */
  template<typename F, typename... Args>
  using invoke_result_t = decltype(value<F>(value<Args>...));

  /**
   * @brief Template type alias that always evaluates to void and takes an
   *        arbitrary variadic pack of types.
   * @tparam ... A variadic pack of types.
   * @note - Useful for SFINAE-based idioms, since it allows for the transformation
   *       of an expression's type while preserving SFINAE behavior.
   */
  template<typename...>
  using void_t = void;

  /**************************************************************************************************
   * @section Non-Standard Type Transformation Traits
   **************************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the promoted version of the
   *        given types (this is the type they are implicitly converted to durring
   *        arithmetic operations).
   * @tparam T The left-hand integral type.
   * @tparam U The right-hand integral type.
   */
  template<typename T, typename U>
  using promoted_type_t = decltype(value<T> + value<U>);

  /**
   * @brief Template type alias that evaluates to a given type and takes an
   *        arbitrary variadic pack of types.
   * @tparam T The type to evaluate to.
   * @tparam ... An arbitrary variadic pack of types.
   * @note - Useful for SFINAE, since it allows for the transformation of an
   *       expression's type while preserving SFINAE behavior.
   * @see void_t
   */
  template<typename T, typename...>
  using type_t = T;

} // namespace ti::util