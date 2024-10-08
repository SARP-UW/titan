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
 * @file common/util/type_traits.h 
 * @authors Aaron McBride 
 * @brief Contains type traits and meta-programming utilities for
 *        querying and modifying types.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    // Helper utility for generating values in unevaluated contexts.
    template<typename T> T&& value;

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

    // Implementation for 'extent_v'
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

    // Implementation of 'type_index_v'.
    template<size_t index, typename T, typename... U>
    struct IndexTypeImpl {
      using Type = typename IndexTypeImpl<index - 1, U...>::Type;
    };

    template<typename T, typename... U>
    struct IndexTypeImpl<0, T, U...> {
      using Type = T;
    };

    // Implementation for 'is_detected_v' and 'detected_t'.
    template<typename DefT, template<typename...> typename Trait,
        typename Enable, typename... Args>
    struct DetectorImpl {
      static constexpr bool value{false};
      using Type = DefT;
    };

    template<typename T> 
    using detect_or_void_ = void;

    template<typename DefT, template<typename...> typename Trait, typename... Args>
    struct DetectorImpl<DefT, Trait, detect_or_void_<Trait<Args...>>, Args...> {
      static constexpr bool value{true};
      using Type = Trait<Args...>;
    };

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section Standard Primary Type Category Traits
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

  /**************************************************************************************************
   * @section Standard Logical Operation Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if every condition in the
   *        given parameter pack of boolean values is true, or false otherwise.
   * @tparam ... A parameter pack of boolean values to query.
   */
  template<bool cond, bool... other> 
  inline constexpr bool conjunction_v{cond && conjunction_v<other...>};

  template<bool cond>
  inline constexpr bool conjunction_v<cond>{cond};

  /**
   * @brief Template bool value that evaluates to true if at least one condition
   *        in the given parameter pack of boolean values is true, or false otherwise.
   * @tparam ... A parameter pack of boolean values to query.
   */
  template<bool cond, bool... other>
  inline constexpr bool disjunction_v{cond || disjunction_v<other...>};
  
  template<bool cond>
  inline constexpr bool disjunction_v<cond>{cond};

  /************************************************************************************************
   * @section Non-Standard Type Pack Indexing Traits/Utilities
   ***********************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the type at a specific index
   *        in the given parameter pack.
   * @tparam index The index of the target type in the parameter pack (size_t NTTP). 
   * @tparam ...T The parameter pack to index into.
   */
  template<size_t index, typename... T>
  using index_type_t = typename IndexTypeImpl<index, T...>::Type;

  /**
   * @brief Template size_t value that evaluates to the index of the first
   *        occurance of a specific type in the given parameter pack.
   * @tparam T The type to get the index of.
   * @tparam ...U The parameter pack to search in.
   */
  template<typename T, typename... U>
  inline constexpr size_t type_index_v{0};

  template<typename T, typename... U>
  inline constexpr size_t type_index_v<T, T, U...>{0};

  template<typename T, typename U, typename... V>
  inline constexpr size_t type_index_v<T, U, V...>{
      1 + type_index_v<T, V...>};

  /**
   * @brief Template bool value that evaluates to true if a specific type is
   *        contained in the given parameter pack, or false otherwise.
   * @tparam T The type to search for.
   * @tparam ...U The parameter pack to search through.
   */
  template<typename T, typename... U>
  inline constexpr bool contains_type_v{
      type_index_v<T, U...> < sizeof...(U)};

  /************************************************************************************************
   * @section Non-Standard Value Pack Indexing Traits/Utilities
   ***********************************************************************************************/

  /**
   * @brief Template value that evaluates to the value at a specific index in
   *        the given variadic NTTP value pack.
   * @tparam index The index of the target value in the value pack (size_t NTTP).
   * @tparam ...value_pack The variadic NTTP value pack to index into.
   */
  template<size_t index, auto value, auto... value_pack>
  inline constexpr auto index_value_v{index_value_v<index - 1, value_pack...>};

  template<auto value, auto... value_pack>
  inline constexpr auto index_value_v<0, value, value_pack...>{value};

  /**
   * @brief Template size_t value that evaluates to the index of the first
   *        occurance of a specific value in the given variadic pack of NTTP values.
   * @tparam value The value to get the index of.
   * @tparam ...value_pack The variadic pack of NTTP values to search through.
   */
  template<auto value, auto... value_pack>
  inline constexpr size_t value_index_v{0};

  template<auto value, auto... value_pack>
  inline constexpr size_t value_index_v<value, value, value_pack...>{0};

  template<auto value, auto o_value, auto... value_pack>
  inline constexpr size_t value_index_v<value, o_value, value_pack...>{
      1 + value_index_v<value, value_pack...>};

  /**
   * @brief Template bool value that evaluates to true if a specific value is
   *        contained in the given variadic pack of NTTP values, or false otherwise.
   * @tparam value The value to search for.
   * @tparam ...value_pack The variadic pack of NTTP values to search through.
   */
  template<auto value, auto... value_pack>
  inline constexpr bool contains_value_v{
      value_index_v<value, value_pack...> < sizeof...(value_pack)};

  /**************************************************************************************************
   * @section Non-Standard SFINAE Detection Traits/Utilities
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if no substitution failure
   *        occurs when instantiating the given type trait with the given set arguments,
   *        or false otherwise.
   * @tparam Trait A template template parameter that denotes the type trait to test.
   * @tparam ...Args The arguments to attempt instantiation of @p 'Trait' with.
   */
  template<template <typename...> typename Trait, typename... Args>
  static constexpr bool is_detected_v{DetectorImpl<void, Trait, void, Args...>::value};

  /**
   * @brief Template type alias that evaluates to the type of the given type trait when 
   *        instantiated with the given set of arguments if no substitution failure
   *        (SFINAE) occurs, or a default type otherwise.
   * @tparam DefT The default type to evaluate to if a substitution failure (SFINAE) occurs.
   * @tparam Trait A template template parameter that denotes the type trait to test.
   * @tparam ...Args The arguments to attempt instantiation of @p 'Trait' with.
   */
  template<typename DefT, template<typename...> typename Trait, typename... Args>
  using detected_t = typename DetectorImpl<DefT, Trait, void, Args...>::Type;

} // namespace ti::util