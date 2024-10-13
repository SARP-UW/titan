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
 */

/**
 * @file common/util/result.h
 * @authors Aaron McBride
 * @brief Contains the "Result" type, used for error handling.
 */

#pragma once
#include "common/tmp.h"
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"
#include "common/util/type_traits.h"
#include "common/util/internal/utility_fwd.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation Forward Declarations
   **************************************************************************************************/

  namespace {

    // Class which contains optional Result destructor.
    template<typename, typename, typename = void>
    struct ResultBase;

    // True if given type is a valid V/E type for Result.
    template<typename T>
    inline constexpr bool valid_result_type_v{
        !is_void_v<T> && !is_reference_v<T>};

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section Result Class Utilities
   **************************************************************************************************/

  /**
   * @brief Wrapper aggregate used to indicate that the given value is 
   *        associated with an error.
   * @tparam T The type of the error value (defaults to monostate_t).
   */
  template<typename T = monostate_t>
  struct Error {

    /** @brief The type of the error value. */
    using ValueType = T;

    /** @brief The error value. */
    ValueType value{};
  };

  /**
   * @brief Wrapper aggregate used to indicate that the given value is
   *        not associated with an error.
   * @tparam T The type of the valid value (defaults to monostate_t).
   */
  template<typename T = monostate_t>
  struct Valid {

    /** @brief The type of the valid value. */
    using ValueType = T; 

    /** @brief The valid value. */
    ValueType value{}; 
  };

  // Deduction guides for 'Valid' and 'Error' value wrappers.
  template<typename T> Valid(T) -> Valid<T>;
  template<typename T> Error(T) -> Error<T>;

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a 'Result' class type, or false otherwise.
   * @tparam T The type to query.
   * @note - CV qualifiers on @p 'T' are ignored.
   */
  template<typename T> 
  inline constexpr bool is_result_v{false};

  /**
   * @brief @brief Template bool value the evaluates to true if the given type
   *        is a 'Error' struct type, or false otherwise.
   * @tparam T The type to query.
   * @note - CV qualifiers on @p 'T' are ignored.
   */
  template<typename T> 
  inline constexpr bool is_error_v{false};

  /**
   * @brief Template bool value that evaluates to true if the given type
   *        is a 'Valid' struct type, or false otherwise.
   * @tparam T The type to query.
   * @note - CV qualifiers on @p 'T' are ignored.
   */
  template<typename T> 
  inline constexpr bool is_valid_v{false};

  /**
   * @brief Macro used to propegate errors. If the given 'Result' class instance
   *        contains an error, it is returned from the current function, otherwise 
   *        this macro evaluates to the contained valid value.
   * @param fn An expression that evaluates to a 'Result' class instance.
   */
  #define TRY(fn) \
    ({ \
      auto res{fn};\
      if (res.is_error()) { \
        return res.error(); \
      } \
      res.value() \
    })

  /**
   * @brief Macro used to propegate errors. If the given 'Result' class instance
   *        contains an error, the given error is returned from the current 
   *        function, otherwise this macro evaluates to the contained valid value.
   * @param fn An expression that evaluates to a 'Result' class instance.
   * @param err The value to return as an error if @p 'fn' represents an error.
   */
  #define TRY_OR(fn, err) \
    ({ \
      auto res{fn};\
      if (res.is_error()) { \
        return err; \
      } \
      res.value() \
    })

  /**
   * @brief Macro used to require that a given 'Result' class instance is valid.
   *        If @p 'fn' evaluates to a valid result, this macro evaluates to the
   *        contained value, otherwise, a fatal error is raised with @p 'msg'.
   * @param fn An expression that evaluates to a 'Result' class instance.
   * @param msg The c string message to pass to sys_error if the result is an error.
   */
  #define REQUIRE(fn, msg) \
    ({ \
      auto res{fn}; \
      if (res.is_error()) { \
        sys_error(msg); \
      } \
      res.value() \
    })

  /**************************************************************************************************
   * @section Result Class Declaration
   **************************************************************************************************/

  /**
   * @brief A class which represents either a valid or error value.
   * @tparam V The type of the valid value (defaults to monostate_t).
   * @tparam E The type of the error value (defaults to monostate_t).
   */
  template<typename V = monostate_t, typename E = monostate_t>
  class Result : public ResultBase<V, E> {

    public:

      static_assert(valid_result_type_v<V>, "'V' is not a valid result type.");
      static_assert(valid_result_type_v<E>, "'E' is not a valid result type.");

      /** @brief The type of the valid value. */
      using ValidType = V;

      /** @brief The type of the error value. */
      using ErrorType = E;

      /** @brief Tag type used to signal in-place construction of a valid value. */
      using in_place_valid_t = in_place_type_t<Valid<ValidType>>;

      /** @brief Tag type used to signal in-place construction of an error value. */
      using in_place_error_t = in_place_type_t<Error<ErrorType>>;

      /** @brief The type of this 'Result' class. */
      using ThisType = Result<V, E>;

      /**
       * @brief Creates a result class instance with a valid value.
       * @tparam T The type of the valid value.
       * @param valid The valid value, wrapped in a 'Valid' struct.
       */
      template<typename T>
      constexpr Result(const Valid<T>& valid);

      /// @overload template<typename T> Result(const Valid<T>& valid);
      template<typename T>
      constexpr Result(Valid<T>&& valid);

      /**
       * @brief Creates a result class instance with an error value.
       * @tparam T The type of the error value.
       * @param error The error value, wrapped in an 'Error' struct.
       */
      template<typename T>
      constexpr Result(const Error<T>& error);

      /// @overload template<typename T> Result(const Error<T>& error);
      template<typename T>
      constexpr Result(Error<T>&& error);

      /**
       * @brief Creates a copy of annother result class instance.
       * @tparam V1 The type of the other result's valid value.
       * @tparam E1 The type of the other result's error value.
       * @param other The other result class instance to copy.
       */
      template<typename V1, typename E1>
      constexpr Result(const Result<V1, E1>& other);

      /**
       * @brief Moves the given result class instance into this one.
       * @tparam V1 The type of the other result's valid value.
       * @tparam E1 The type of the other result's error value.
       * @param other The other result class instance to move from.
       */
      template<typename V1, typename E1>
      constexpr Result(Result<V1, E1>&& other);

      /**
       * @brief Creates a result class instance with an in-place constructed valid value.
       * @tparam T The type of the value to construct in-place (must be convertible 
       *         to this result's valid type).
       * @tparam ...Args The types of the arguments to pass to the constructor of @p 'T'.
       * @param in_place_type_t An instance of 'in_place_type_t' with the type Valid<T>.
       * @param ...args The arguments to pass to the constructor of @p 'T'.
       */
      template<typename T, typename... Args>
      constexpr explicit Result(in_place_type_t<Valid<T>>, Args&&... args);

      /**
       * @brief Creates a result class instance with an in-place constructed error value.
       * @tparam T The type of the value to construct in-place (must be convertible
       *         to this result's error type).
       * @tparam ...Args The argument types to pass to the constructor of @p 'T'.
       * @param in_place_type_t An instance of 'in_place_type_t' with the type Error<T>.
       * @param ...args The arguments to pass to the constructor of @p 'T'.
       */
      template<typename T, typename... Args>
      constexpr explicit Result(in_place_type_t<Error<T>>, Args&&... args);

      /**
       * @brief Assigns a valid value to this result.
       * @tparam T The type of the value to assign.
       * @param valid The value to assign, wrapped in a 'Valid<T>' struct.
       * @returns A reference to this result.
       * @note - If this result already contains a valid value, @p 'valid' is 
       *       assigned to it, otherwise @p 'valid' is used to construct a 
       *       valid value.
       */
      template<typename T>
      ThisType& operator=(const Valid<T>& valid);

      /// @overload template<typename T> ThisType& operator=(const Valid<T>& valid);
      template<typename T>
      ThisType& operator=(Valid<T>&& valid);

      /**
       * @brief Assigns an error value to this result.
       * @tparam T The type of the value to assign.
       * @param error The value to assign, wrapped in an 'Error<T>' struct.
       * @returns A reference to this result.
       * @note - If this result already contains an error value, @p 'error' is 
       *       assigned to it, otherwise @p 'error' is used to construct an 
       *       error value.
       */
      template<typename T>
      ThisType& operator=(const Error<T>& error);

      /// @overload template<typename T> ThisType& operator=(const Error<T>& error);
      template<typename T>
      ThisType& operator=(Error<T>&& error);

      /**
       * @brief Assigns the value contained in annother result class instance 
       *        to this one.
       * @tparam V1 The type of the other result's valid value.
       * @tparam E1 The type of the other result's error value.
       * @param other The other result class instance to assign from.
       * @returns A reference to this result.
       * @note - If @p 'other' contains the same kind (valid/error) of value as 
       *       this instance, it is assigned to the associated value, otherwise 
       *       the value is used to construct a new instance of the associated 
       *       type in this class (valid/error).
       */
      template<typename V1, typename E1>
      ThisType& operator=(const Result<V1, E1>& other);

      /// @overload template<typename V1, typename E1> ThisType& operator=(const Result<V1, E1>& other);
      template<typename V1, typename E1>
      ThisType& operator=(Result<V1, E1>&& other);

      /**
       * @brief Constructs a new valid value inside this result.
       * @tparam T The type of the given value.
       * @param valid The value (wrapped in a 'Valid<T>' struct) used to 
       *        construct a new instance of this result's valid type with.
       * @note - This function will destroy the value contained in this
       *       result, regardless of it's kind (valid/error).
       */
      template<typename T>
      void emplace(const Valid<T>& valid);

      /// @overload template<typename T> void emplace(const Valid<T>& valid);
      template<typename T>
      void emplace(Valid<T>&& valid);

      /**
       * @brief Constructs a new error value inside this result.
       * @tparam T The type of the given value.
       * @param error The value (wrapped in an 'Error<T>' struct) used to
       *        construct a new instance of this result's error type with.
       * @note - This function will destroy the value contained in this
       *       result, regardless of it's kind (valid/error).
       */
      template<typename T>
      void emplace(const Error<T>& error);

      /// @overload template<typename T> void emplace(Error<T>&& error);
      template<typename T>
      void emplace(Error<T>&& error);

      /**
       * @brief Constructs a new valid or error value inside this result, 
       *        using the value contained in annother result instance.
       * @tparam V1 The type of the other result's valid value.
       * @tparam E1 The type of the other result's error value.
       * @param other The other result class instance. 
       * @note - This function will destroy the value contained in this
       *       result, regardless of it's kind (valid/error).
       */
      template<typename V1, typename E1>
      void emplace(const Result<V1, E1>& other);

      /// @overload template<typename V1, typename E1> void emplace(const Result<V1, E1>& other);
      template<typename V1, typename E1>
      void emplace(Result<V1, E1>&& other);

      /**
       * @brief Constructs a new valid value in-place inside this result.
       * @tparam T The type of the value to construct in-place (must be 
       *         convertible to this result's valid type).
       * @tparam ...Args The type of the arguments to pass to the constructor of @p 'T'.
       * @param in_place_type_t An instance of 'in_place_type_t' with the type Valid<T>.
       * @param ...args The arguments to pass to the constructor of @p 'T'.
       */
      template<typename T, typename... Args>
      void emplace(in_place_type_t<Valid<T>>, Args&&... args);

      /**
       * @brief Constructs a new error value in-place inside this result.
       * @tparam T The type of the value to construct in-place (must be 
       *         convertible to this result's error type).
       * @tparam ...Args The type of the arguments to pass to the constructor of @p 'T'.
       * @param  in_place_type_t An instance of 'in_place_type_t' with the type Error<T>.
       * @param ...args The arguments to pass to the constructor of @p 'T'.
       */
      template<typename T, typename... Args>
      void emplace(in_place_type_t<Error<T>>, Args&&... args);

      /**
       * @brief Determines if this result contains it's 'valid' value.
       * @returns True if this result contains it's 'valid' value or false otherwise.
       */
      [[nodiscard]] constexpr bool is_valid() const;

      /**
       * @brief Determines if this result contains it's 'error' value.
       * @return True if this result contains it's 'error' value or false otherwise.
       */
      [[nodiscard]] constexpr bool is_error() const;

      /**
       * @brief Implicit cast to bool which evaluates to true if this result 
       *        contains it's 'valid' value or false otherwise.
       */
      constexpr operator bool() const;

      /**
       * @brief Determines if this result contains the given 'valid' value.
       * @tparam T The type of the given value.
       * @param value The value to compare to this result's 'valid' value.
       * @returns True if this result contains a 'valid' value and it is
       *          equal to @p 'value', or false otherwise.
       * @note - @p 'T' must be equality comparable to this result's 'valid' type.
       */
      template<typename T>
      [[nodiscard]] constexpr bool is_valid(const T& value) const;

      /**
       * @brief Determines if this result contains the given 'error' value.
       * @tparam T The type of the given value.
       * @param value The value to compare to this result's 'error' value.
       * @returns True if this result contains an 'error' value and it is
       *          equal to @p 'value', or false otherwise.
       * @note - @p 'T' must be equality comparable to this result's 'error' type.
       */
      template<typename T>
      [[nodiscard]] constexpr bool is_error(const T& value) const;

      /**
       * @brief Gets the valid value contained in this result.
       * @returns A reference to the 'valid' value.
       * @note - If this result contains an 'error' value, a fatal error is raised.
       */
      [[nodiscard]] constexpr V& valid() &;

      /// @overload [[nodiscard]] constexpr const V& valid() const &;
      [[nodiscard]] constexpr const V& valid() const &;

      /**
       * @brief Moves out the valid value contained in this result.
       * @returns This result's 'valid' value.
       * @note - If this result contains an 'error' value, a fatal error is raised.
       */
      [[nodiscard]] constexpr V&& valid() &&;

      /// @overload [[nodiscard]] constexpr const V&& valid() const &&;
      [[nodiscard]] constexpr const V&& valid() const &&;

      /**
       * @brief Gets the 'valid' value contained in this result.
       * @returns A reference to this result's 'valid' value.
       * @note - If this result contains an 'error' value, a fatal error is raised.
       */
      [[nodiscard]] constexpr V& operator*() &;

      /// @overload [[nodiscard]] constexpr const V& operator*() const &;
      [[nodiscard]] constexpr const V& operator*() const &;

      /**
       * @brief Moves out the 'valid' value contained in this result.
       * @returns This result's 'valid' value.
       * @note - If this result contains an 'error' value, a fatal error is raised.
       */
      [[nodiscard]] constexpr V&& operator*() &&;

      /// @overload [[nodiscard]] constexpr const V&& operator*() const &&;
      [[nodiscard]] constexpr const V&& operator*() const &&;

      /**
       * @brief Gets a pointer to the 'valid' value contained in this result.
       * @return A pointer to this result's 'valid' value.
       * @note - If this result contains an 'error' value, a nullptr is returned.
       */
      [[nodiscard]] constexpr V* valid_ptr();

      /// @overload [[nodiscard]] constexpr const V* valid_ptr() const;
      [[nodiscard]] constexpr const V* valid_ptr() const;

      /**
       * @brief Gets a pointer to the 'valid' value contained in this result.
       * @returns A pointer to this result's 'valid' value.
       * @note - If this result contains an 'error' value, a nullptr is returned.
       */
      [[nodiscard]] constexpr V* operator->();

      /// @overload [[nodiscard]] constexpr const V* operator->() const;
      [[nodiscard]] constexpr const V* operator->() const;

      /**
       * @brief Gets the error value contained in this result.
       * @returns A reference to the 'error' value.
       * @note - If this result contains a 'valid' value, a fatal error is raised.
       */
      [[nodiscard]] constexpr E& error() &;

      /// @overload [[nodiscard]] constexpr const E& error() const &;
      [[nodiscard]] constexpr const E& error() const &;

      /**
       * @brief Moves out the error value contained in this result.
       * @returns This result's 'error' value.
       * @note - If this result contains a 'valid' value, a fatal error is raised.
       */
      [[nodiscard]] constexpr E&& error() &&;

      /// @overload [[nodiscard]] constexpr const E&& error() const &&;
      [[nodiscard]] constexpr const E&& error() const &&;

      /**
       * @brief Gets a pointer to the 'error' value contained in this result.
       * @returns A pointer to this result's 'error' value.
       */
      [[nodiscard]] constexpr E* error_ptr();

      /// @overload [[nodiscard]] constexpr const E* error_ptr() const;
      [[nodiscard]] constexpr const E* error_ptr() const;

      /**
       * @brief Gets this result's 'valid' value or a deafult value if it contains
       *        an 'error' value.
       * @tparam T The type of the default value.
       * @param def_value The default value.
       * @returns A copy of this result's 'valid' value if it exists (this result
       *          does not contain an error), or @p 'def_value' otherwise.
       * @note - @p 'def_value' must be convertible to this result's 'valid' type.
       */
      template<typename T>
      [[nodiscard]] constexpr V valid_or(T&& def_value) const &;

      /**
       * @brief Moves out this result's 'valid' value or a default value if it 
       *        contains an 'error' value.
       * @tparam T The type of the default value.
       * @param def_value The default value.
       * @returns A copy of this result's 'valid' value if it exists (this result
       *          does not contain an error), or @p 'def_value' otherwise.
       * @note - @p 'def_value' must be convertible to this result's 'valid' type.
       */
      template<typename T>
      [[nodiscard]] constexpr V&& valid_or(T&& def_value) &&;

      /**
       * @brief Gets this result's 'error' value or a default value if it contains
       *        a valid value.
       * @tparam T The type of the default value.
       * @param def_value The default value.
       * @returns A copy of this result's 'error' value if it exists (this result
       *          does not contains a valid value), or @p 'def_value' otherwise.
       * @note - @p 'def_value' must be convertible to this result's 'error' type.
       */
      template<typename T>
      [[nodiscard]] constexpr E error_or(T&& def_value) const &;

      /**
       * @brief Moves out this result's 'error' value or a default value if it
       *        contains a valid value.
       * @tparam T The type of the default value.
       * @param def_value The default value.
       * @returns A copy of this result's 'error' value if it exists (this result
       *          does not contain a valid value), or @p 'def_value' otherwise.
       * @note - @p 'def_value' must be convertible to this result's 'error' type.
       */
      template<typename T>
      [[nodiscard]] constexpr E&& error_or(T&& def_value) &&;

      /**
       * @brief Maps this result's 'valid' type to a new type using the given
       *        mapping function or value.
       * @tparam T The type of the mapping function/value.
       * @param mapping The mapping function/value.
       * @returns A result instance that contains the outcome of mapping 
       *          (or flat-maping) this result's 'valid' value to @p 'mapping'.
       * @see https://en.wikipedia.org/wiki/monad_(functional_programming)         
       */
      template<typename T>
      constexpr auto map_valid(T&& mapping) &;

      /// @overload template<typename T> constexpr auto map_valid(T&& mapping) &;
      template<typename T>
      constexpr auto map_valid(T&& mapping) const &;

      /// @overload template<typename T> constexpr auto map_valid(T&& mapping) &;
      template<typename T>
      constexpr auto map_valid(T&& mapping) &&;

      /// @overload template<typename T> constexpr auto map_valid(T&& mapping) &;
      template<typename T>
      constexpr auto map_valid(T&& mapping) const &&;

      /**
       * @brief Maps this result's 'error' type to a new type using the given
       *        mapping function/value.
       * @tparam T The type of the mapping function/value.
       * @param mapping The mapping function/value.
       * @returns A result instance that contains the outcome of mapping
       *          (or flat-maping) this result's 'error' value to @p 'mapping'.
       * @see https://en.wikipedia.org/wiki/monad_(functional_programming)
       */
      template<typename T>
      constexpr auto map_error(T&& mapping) &;

      /// @overload template<typename T> constexpr auto map_error(T&& mapping) &;
      template<typename T>
      constexpr auto map_error(T&& mapping) const &;

      /// @overload template<typename T> constexpr auto map_error(T&& mapping) &;
      template<typename T>
      constexpr auto map_error(T&& mapping) &&;

      /// @overload template<typename T> constexpr auto map_error(T&& mapping) &;
      template<typename T>
      constexpr auto map_error(T&& mapping) const &&;

      /**
       * @brief Maps this result's 'valid' or 'error' value to a new type
       *        using the given mapping functions/values.
       * @tparam V1 The type of the valid mapping function/value.
       * @tparam E1 The type of the error mapping function/value.
       * @param valid_mapping The valid mapping function/value.
       * @param error_mapping The error mapping function/value.
       * @returns The result of mapping this result's 'valid' or 'error' value
       *          to @p 'valid_mapping' or @p 'error_mapping' (depnding on which
       *          value currently exists).
       */
      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) &;

      /// @overload template<typename V1, typename E1> constexpr auto map(V1&& valid_mapping, E1&& error_mapping) &;
      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) const &;

      /// @overload template<typename V1, typename E1> constexpr auto map(V1&& valid_mapping, E1&& error_mapping) &;
      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) &&;

      /// @overload template<typename V1, typename E1> constexpr auto map(V1&& valid_mapping, E1&& error_mapping) &;
      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) const &&;

      /**
       * @brief Invokes the given function with this result's 'valid' value,
       *        if it exists (i.e. this result does not contain an 'error' value).
       * @tparam F The type of the callable object to invoke.
       * @param fn The callable object to invoke.
       */
      template<typename F>
      constexpr void apply_valid(F&& fn) &;

      /// @overload template<typename F> constexpr void apply_valid(F&& fn) &;
      template<typename F>
      constexpr void apply_valid(F&& fn) const &;

      /// @overload template<typename F> constexpr void apply_valid(F&& fn) &;
      template<typename F>
      constexpr void apply_valid(F&& fn) &&;

      /// @overload template<typename F> constexpr void apply_valid(F&& fn) &;
      template<typename F>
      constexpr void apply_valid(F&& fn) const &&;

      /**
       * @brief Invokes the given function with this result's 'error' value,
       *       if it exists (i.e. this result does not contain a 'valid' value).
       * @tparam F The type of the callable object to invoke.
       * @param fn The callable object to invoke.
       */
      template<typename F>
      constexpr void apply_error(F&& fn) &;

      /// @overload template<typename F> constexpr void apply_error(F&& fn) &;
      template<typename F>
      constexpr void apply_error(F&& fn) const &;

      /// @overload template<typename F> constexpr void apply_error(F&& fn) &;
      template<typename F>
      constexpr void apply_error(F&& fn) &&;

      /// @overload template<typename F> constexpr void apply_error(F&& fn) &;
      template<typename F>
      constexpr void apply_error(F&& fn) const &&;

      /**
       * @brief TODO
       */
      using ResultBase<V, E>::~ResultBase;

    private:

      union StorageT;

      // Constructs a new valid value in storage using the given arguments.
      template<typename... Args>
      constexpr void ctor_valid(Args&&... args);

      // Constructs a new error value in storage using the given arguments.
      template<typename... Args>
      constexpr void ctor_error(Args&&... args);

      // Calls the destructor of the value currently in storage.
      constexpr void reset_storage();

      StorageT storage_; // Union which holds either an error or valid value.
      bool valid_flag_; // If true, storage_ contains valid value, otherwise error value.

  }; // class Result

  /**
   * @brief TODO
   * @tparam Vl 
   * @tparam El 
   * @tparam Vr 
   * @tparam Er 
   * @param lhs 
   * @param rhs 
   * @return 
   */
  template<typename Vl, typename El, typename Vr, typename Er>
  [[nodiscard]] constexpr bool operator==(const Result<Vl, El>& lhs, 
      const Result<Vr, Er>& rhs);

  /**
   * @brief TODO
   * @tparam Vl 
   * @tparam El 
   * @tparam Vr 
   * @tparam Er 
   * @param lhs 
   * @param rhs 
   * @return 
   */
  template<typename Vl, typename El, typename Vr, typename Er>
  [[nodiscard]] constexpr bool operator!=(const Result<Vl, El>& lhs, 
      const Result<Vr, Er>& rhs);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    // Tags used for construction of error/valid values.
    struct Vtag {};
    struct Etag {};

    // Gets result of unknown type used in map/apply method
    template<typename T, typename Vmod>
    using fn_result_t = conditional_t<is_invocable_v<T, Vmod>, 
        invoke_result_t<T, Vmod>, conditional_t<is_invocable_v<T>, 
        invoke_result_t<T>, T>>;

    // Implementation of conditional result destructor
    template<typename V, typename E, typename>
    struct ResultBase {
      ~ResultBase() = default;
    };

    template<typename V, typename E>
    struct ResultBase<V, E, enable_if_t<
        !is_trivial_v<V> || !is_trivial_v<E>>> {
      ~ResultBase() {
        using ChildT = Result<V, E>;
        static_cast<ChildT*>(this)->reset_storage();
      }
    };

    // Implementation of utility/move, needed to avoid circular dependency
    template<typename T>
    [[nodiscard]] constexpr auto&& res_move(T&& value) {
      using BaseT = remove_reference_t<T>;
      return static_cast<BaseT&&>(value);
    }

    // Internal implementation of utility/forward, needed to avoid circular dependency
    template<typename T>
    [[nodiscard]] constexpr T&& res_forward(remove_reference_t<T>&& value) {
      static_assert(!is_rvalue_reference_v<T>, 
          "'T' must be an rvalue reference.");
      return static_cast<T&&>(value);
    }

    template<typename T>
    [[nodiscard]] constexpr T&& res_forward(remove_reference_t<T>& value) {
      return static_cast<T&&>(value);
    }

  } // namespace annoymous

  template<typename V, typename E> inline constexpr bool is_result_v<Result<V, E>>{true};
  template<typename V, typename E> inline constexpr bool is_result_v<const Result<V, E>>{true};
  template<typename V, typename E> inline constexpr bool is_result_v<volatile Result<V, E>>{true};
  template<typename V, typename E> inline constexpr bool is_result_v<const volatile Result<V, E>>{true};

  template<typename T> inline constexpr bool is_error_v<Error<T>>{true};
  template<typename T> inline constexpr bool is_error_v<const Error<T>>{true};
  template<typename T> inline constexpr bool is_error_v<volatile Error<T>>{true};
  template<typename T> inline constexpr bool is_error_v<const volatile Error<T>>{true};

  template<typename T> inline constexpr bool is_valid_v<Valid<T>>{true};
  template<typename T> inline constexpr bool is_valid_v<const Valid<T>>{true};
  template<typename T> inline constexpr bool is_valid_v<volatile Valid<T>>{true};
  template<typename T> inline constexpr bool is_valid_v<const volatile Valid<T>>{true};

  template<typename V, typename E>
  union Result<V, E>::StorageT {

    template<typename T>
    constexpr StorageT(Vtag, T&& value) :
        valid{res_forward<T>(value)} {};

    template<typename T>
    constexpr Storage(Etag, T&& value) :
        error{res_forward<T>(value)} {};

    template<typename... Args>
    constexpr Storage(Vtag, Args&&... args) :
        valid{res_forward<Args>(args)...} {};

    template<typename... Args>
    constexpr Storage(Etag, Args&&... args) :
        error{res_forward<Args>(args)...} {};

    V valid;
    E error;

  };

  template<typename V, typename E>
  template<typename T>
  constexpr Result<V, E>::Result(const Valid<T>& valid) :
      storage_{Vtag{}, valid.value},
      valid_flag_{true} {}

  template<typename V, typename E>
  template<typename T>
  constexpr Result<V, E>::Result(Valid<T>&& valid) :
      storage_{Vtag{}, res_move(valid.value)},
      valid_flag_{true} {}

  template<typename V, typename E>
  template<typename T>
  constexpr Result<V, E>::Result(const Error<T>& error) :
      storage_{Etag{}, error.value},
      valid_flag_{false} {}

  template<typename V, typename E>
  template<typename T>
  constexpr Result<V, E>::Result(Error<T>&& error) :
      storage_{Etag{}, res_move(error.value)},
      valid_flag_{false} {}

  template<typename V, typename E>
  template<typename V1, typename E1>
  constexpr Result<V, E>::Result(const Result<V1, E1>& other) :
      storage_{other.valid_flag_ ? Vtag{} : Etag{}, 
          other.valid_flag_ ? other.valid() : other.error()},
      valid_flag_{other.valid_flag_} {}

  template<typename V, typename E>
  template<typename V1, typename E1>
  constexpr Result<V, E>::Result(Result<V1, E1>&& other) :
      storage_{other.valid_flag_ ? Vtag{} : Etag{}, 
          other.valid_flag_ ? res_move(other.valid()) : 
              res_move(other.error())},
      valid_flag_{other.valid_flag_} {}

  template<typename V, typename E>
  template<typename T, typename... Args>
  constexpr Result<V, E>::Result(
      in_place_type_t<Valid<T>>, Args&&... args) :
          storage_{Vtag{}, res_forward<Args>(args)...},
          valid_flag_{true} {}


  template<typename V, typename E>
  template<typename T, typename... Args>
  constexpr Result<V, E>::Result(
      in_place_type_t<Error<T>>, Args&&... args) :
          storage_{Etag{}, res_forward<Args>(args)...},
          valid_flag_{false} {}

  template<typename V, typename E>
  template<typename T>
  Result<V, E>& Result<V, E>::operator=(const Valid<T>& valid) {
    static_assert(is_assignable_v<V, const T&>,
        "'V' must be assignable from 'const T&'.");
    if (is_valid()) {
      storage_.valid = valid.value;
    } else {
      storage_.error.~E();
      ctor_valid(valid.value);
    }
    return *this;
  }

  template<typename V, typename E>
  template<typename T>
  Result<V, E>& Result<V, E>::operator=(Valid<T>&& valid) {
    static_assert(is_assignable_v<V, T&&>,
        "'V' must be assignable from 'T&&'.");
    if (is_valid()) {
      storage_.valid = res_move(valid.value);
    } else {
      storage_.error.~E();
      ctor_valid(res_move(valid.value));
    }
    return *this;
  }

  template<typename V, typename E>
  template<typename T>
  Result<V, E>& Result<V, E>::operator=(const Error<T>& error) {
    static_assert(is_assignable_v<E, const T&>,
        "'E' must be assignable from 'const T&'.");
    if (is_error()) {
      storage_.error = error.value;
    } else {
      storage_.valid.~V();
      ctor_error(error.value);
    }
    return *this;
  }

  template<typename V, typename E>
  template<typename T>
  Result<V, E>& Result<V, E>::operator=(Error<T>&& error) {
    static_assert(is_assignable_v<E, T&&>,
        "'E' must be assignable from 'T&&'.");
    if (is_error()) {
      storage_.error = res_move(error.value);
    } else {
      storage_.valid.~V();
      ctor_error(res_move(error.value));
    }
    return *this;
  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  Result<V, E>& Result<V, E>::operator=(const Result<V1, E1>& other) {
    if (likely(this != other)) {
      if (other.is_valid()) {
        this->operator=(Valid<V1>{other.valid()});
      } else {
        this->operator=(Error<E1>{other.error()});
      }
    }
    return *this;
  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  Result<V, E>& Result<V, E>::operator=(Result<V1, E1>&& other) {
    if (likely(this != other)) {
      if (other.is_valid()) {
        this->operator=(Valid<V1>{res_move(other.valid())});
      } else {
        this->operator=(Error<E1>{res_move(other.error())});
      }
    }
    return *this;
  }

  template<typename V, typename E>
  template<typename T>
  void Result<V, E>::emplace(const Valid<T>& valid) {
    reset_storage();
    ctor_valid(valid.value);
  }

  template<typename V, typename E>
  template<typename T>
  void Result<V, E>::emplace(Valid<T>&& valid) {
    reset_storage();
    ctor_valid(res_move(valid.value));
  }

  template<typename V, typename E>
  template<typename T>
  void Result<V, E>::emplace(const Error<T>& error) {
    reset_storage();
    ctor_error(error.value);
  }

  template<typename V, typename E>
  template<typename T>
  void Result<V, E>::emplace(Error<T>&& error) {
    reset_storage();
    ctor_error(res_move(error.value));
  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  void Result<V, E>::emplace(const Result<V1, E1>& other) {
    this->reset_storage();
    if (other.is_valid()) {
      this->ctor_valid(other.valid());
    } else {
      this->ctor_error(other.error());
    }
  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  void Result<V, E>::emplace(Result<V1, E1>&& other) {
    this->reset_storage();
    if (other.is_valid()) {
      this->ctor_valid(res_move(other.valid()));
    } else {
      this->ctor_error(res_move(other.error()));
    }
  }

  template<typename V, typename E>
  template<typename T, typename... Args>
  void Result<V, E>::emplace(in_place_type_t<Valid<T>>, Args&&... args) {
    reset_storage();
    ctor_valid(res_forward<Args>(args)...);
  }

  template<typename V, typename E>
  template<typename T, typename... Args>
  void Result<V, E>::emplace(in_place_type_t<Error<T>>, Args&&... args) {
    reset_storage();
    ctor_error(res_forward<Args>(args)...);
  }

  template<typename V, typename E>
  constexpr bool Result<V, E>::is_valid() const {
    return valid_flag_;
  }

  template<typename V, typename E>
  constexpr bool Result<V, E>::is_error() const {
    return !valid_flag_;
  }

  template<typename V, typename E>
  constexpr Result<V, E>::operator bool() const {
    return is_valid();
  }

  template<typename V, typename E>
  template<typename T>
  constexpr bool Result<V, E>::is_valid(const T& value) const {
    static_assert(is_equality_comparable_v<const V&, const T&>,
        "'const V&' must be equality comparable with 'const T&'.");
    return is_valid() && storage_.valid == value;
  }

  template<typename V, typename E>
  template<typename T>
  constexpr bool Result<V, E>::is_error(const T& value) const {
    static_assert(is_equality_comparable_v<const E&, const T&>,
        "'const E&' must be equality comparable with 'const T&'.");
    return is_error() && storage_.error == value;
  }

  template<typename V, typename E>
  constexpr V& Result<V, E>::valid() & {
    if (TI_BUILTIN_EXPECT(!is_valid(), false, 1)) {
      sys_error("Invalid result access.");
    }
    return storage_.valid;
  }

  template<typename V, typename E>
  constexpr const V& Result<V, E>::valid() const & {
    if (TI_BUILTIN_EXPECT(!is_valid(), false, 1)) {
      sys_error("Invalid result access.");
    }
    return storage_.valid;
  }

  template<typename V, typename E>
  constexpr V&& Result<V, E>::valid() && {
    if (TI_BUILTIN_EXPECT(!is_valid(), false, 1)) {
      sys_error("Invalid result access.");
    }
    return res_move(storage_.valid);
  }

  template<typename V, typename E>
  constexpr const V&& Result<V, E>::valid() const && {
    if (TI_BUILTIN_EXPECT(!is_valid(), false, 1)) {
      sys_error("Invalid result access.");
    }
    return res_move(storage_.valid);
  }

  template<typename V, typename E>
  constexpr V& Result<V, E>::operator*() & {
    if (TI_BUILTIN_EXPECT(is_valid(), true, 1)) {
      sys_error("Invalid result access.");
    }
    return valid();
  }

  template<typename V, typename E>
  constexpr const V& Result<V, E>::operator*() const & {
    return valid();
  }

  template<typename V, typename E>
  constexpr V&& Result<V, E>::operator*() && {
    return res_move(valid());
  }

  template<typename V, typename E>
  constexpr const V&& Result<V, E>::operator*() const && {
    return res_move(valid());
  }

  template<typename V, typename E>
  constexpr V* Result<V, E>::valid_ptr() {
    return is_valid() ? TI_BUILTIN_ADDRESSOF(storage_.valid) : nullptr;
  }

  template<typename V, typename E>
  constexpr const V* Result<V, E>::valid_ptr() const {
    return is_valid() ? TI_BUILTIN_ADDRESSOF(storage_.valid) : nullptr;
  }

  template<typename V, typename E>
  constexpr V* Result<V, E>::operator->() {
    return valid_ptr();
  }

  template<typename V, typename E>
  constexpr const V* Result<V, E>::operator->() const {
    return valid_ptr();
  }

  template<typename V, typename E>
  constexpr E& Result<V, E>::error() & {
    if (TI_BUILTIN_EXPECT(!is_error(), false, 1)) {
      sys_error("Invalid result access.");
    }
    return storage_.error;
  }

  template<typename V, typename E>
  constexpr const E& Result<V, E>::error() const & {
    if (TI_BUILTIN_EXPECT(!is_error(), false, 1)) {
      sys_error("Invalid result access.");
    }
    return storage_.error;
  }

  template<typename V, typename E>
  constexpr E&& Result<V, E>::error() && {
    if (TI_BUILTIN_EXPECT(!is_error(), false, 1)) {
      sys_error("Invalid result access.");
    }
    return res_move(storage_.error);
  }

  template<typename V, typename E>
  constexpr const E&& Result<V, E>::error() const && {
    if (TI_BUILTIN_EXPECT(!is_error(), false, 1)) {
      sys_error("Invalid result access.");
    }
    return res_move(storage_.error);
  }

  template<typename V, typename E>
  constexpr E* Result<V, E>::error_ptr() {
    return is_error() ? TI_BUILTIN_ADDRESSOF(storage_.error) : nullptr;
  }

  template<typename V, typename E>
  constexpr const E* Result<V, E>::error_ptr() const {
    return is_error() ? TI_BUILTIN_ADDRESSOF(storage_.error) : nullptr;
  }

  template<typename V, typename E>
  template<typename T>
  constexpr V Result<V, E>::valid_or(T&& def_value) const & {
    if (is_valid()) {
      return valid();
    } else {
      return res_forward<T>(def_value);
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr V&& Result<V, E>::valid_or(T&& def_value) && {
    if (is_valid()) {
      return res_move(valid());
    } else {
      return res_forward<T>(def_value);
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr E Result<V, E>::error_or(T&& def_value) const & {
    if (is_error()) {
      return error();
    } else {
      return res_forward<T>(def_value);
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr E&& Result<V, E>::error_or(T&& def_value) && {
    if (is_error()) {
      return res_move(error());
    } else {
      return res_forward<T>(def_value);
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_valid(T&& mapping) & {
    using MappingT = fn_result_t<T, V&>;
    if constexpr (is_result_v<MappingT>) {
      using ResultT = Result<typename MappingT::ValidType, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, V&>) {
          return ResultT{res_forward<T>(mapping)(storage_.valid)};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{res_forward<T>(mapping)()};
        } else {
          return ResultT{res_forward<T>(mapping)};
        }
      } else {
        return ResultT{Error<E>{storage_.error}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<MappingT, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, V&>) {
          return ResultT{Valid<T>{res_forward<T>(mapping)(storage_.valid)}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Valid<T>{res_forward<T>(mapping)()}};
        } else {
          return ResultT{Valid<T>{res_forward<T>(mapping)}};
        }
      } else {
        return ResultT{Error<E>{storage_.error}};
      }
    } else {
      static_assert(false, "Invalid mapping type.");
      unreachable();
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_valid(T&& mapping) const & {
    using MappingT = fn_result_t<T, const V&>;
    if constexpr (is_result_v<MappingT>) {
      using ResultT = Result<typename MappingT::ValidType, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, const V&>) {
          return ResultT{res_forward<T>(mapping)(storage_.valid)};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{res_forward<T>(mapping)()};
        } else {
          return ResultT{res_forward<T>(mapping)};
        }
      } else {
        return ResultT{Error<E>{storage_.error}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<MappingT, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, const V&>) {
          return ResultT{Valid<T>{res_forward<T>(mapping)(storage_.valid)}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Valid<T>{res_forward<T>(mapping)()}};
        } else {
          return ResultT{Valid<T>{res_forward<T>(mapping)}};
        }
      } else {
        return ResultT{Error<E>{storage_.error}};
      }
    } else {
      static_assert(false, "Invalid mapping type.");
      unreachable();
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_valid(T&& mapping) && {
    using MappingT = fn_result_t<T, V&&>;
    if constexpr (is_result_v<MappingT>) {
      using ResultT = Result<typename MappingT::ValidType, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, V&&>) {
          return ResultT{res_forward<T>(mapping)(res_move(storage_.valid))};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{res_forward<T>(mapping)()};
        } else {
          return ResultT{res_forward<T>(mapping)};
        }
      } else {
        return ResultT{Error<E>{res_move(storage_.error)}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<MappingT, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, V&&>) {
          return ResultT{Valid<T>{res_forward<T>(mapping)(res_move(storage_.valid))}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Valid<T>{res_forward<T>(mapping)()}};
        } else {
          return ResultT{Valid<T>{res_forward<T>(mapping)}};
        }
      } else {
        return ResultT{Error<E>{res_move(storage_.error)}};
      }
    } else {
      static_assert(false, "Invalid mapping type.");
      unreachable();
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_valid(T&& mapping) const && {
    using MappingT = fn_result_t<T, const V&&>;
    if constexpr (is_result_v<MappingT>) {
      using ResultT = Result<typename MappingT::ValidType, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, const V&&>) {
          return ResultT{res_forward<T>(mapping)(res_move(storage_.valid))};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{res_forward<T>(mapping)()};
        } else {
          return ResultT{res_forward<T>(mapping)};
        }
      } else {
        return ResultT{Error<E>{res_move(storage_.error)}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<MappingT, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, const V&&>) {
          return ResultT{Valid<T>{res_forward<T>(mapping)(res_move(storage_.valid))}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Valid<T>{res_forward<T>(mapping)()}};
        } else {
          return ResultT{Valid<T>{res_forward<T>(mapping)}};
        }
      } else {
        return ResultT{Error<E>{res_move(storage_.error)}};
      }
    } else {
      static_assert(false, "Invalid mapping type.");
      unreachable();
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_error(T&& mapping) & {
    using MappingT = fn_result_t<T, E&>;
    if constexpr (is_result_v<MappingT>) {
      using ResultT = Result<V, typename MappingT::ErrorType>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, E&>) {
          return ResultT{res_forward<T>(mapping)(storage_.error)};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{res_forward<T>(mapping)()};
        } else {
          return ResultT{res_forward<T>(mapping)};
        }
      } else {
        return ResultT{Valid<V>{storage_.valid}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<V, MappingT>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, E&>) {
          return ResultT{Error<T>{res_forward<T>(mapping)(storage_.error)}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Error<T>{res_forward<T>(mapping)()}};
        } else {
          return ResultT{Error<T>{res_forward<T>(mapping)}};
        }
      } else {
        return ResultT{Valid<V>{storage_.valid}};
      }
    } else {
      static_assert(false, "Invalid mapping type.");
      unreachable();
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_error(T&& mapping) const & {
    using MappingT = fn_result_t<T, const E&>;
    if constexpr (is_result_v<MappingT>) {
      using ResultT = Result<V, typename MappingT::ErrorType>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, const E&>) {
          return ResultT{res_forward<T>(mapping)(storage_.error)};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{res_forward<T>(mapping)()};
        } else {
          return ResultT{res_forward<T>(mapping)};
        }
      } else {
        return ResultT{Valid<V>{storage_.valid}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<V, MappingT>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, const E&>) {
          return ResultT{Error<T>{res_forward<T>(mapping)(storage_.error)}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Error<T>{res_forward<T>(mapping)()}};
        } else {
          return ResultT{Error<T>{res_forward<T>(mapping)}};
        }
      } else {
        return ResultT{Valid<V>{storage_.valid}};
      }
    } else {
      static_assert(false, "Invalid mapping type.");
      unreachable();
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_error(T&& mapping) && {
    using MappingT = fn_result_t<T, E&&>;
    if constexpr (is_result_v<MappingT>) {
      using ResultT = Result<V, typename MappingT::ErrorType>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, E&&>) {
          return ResultT{res_forward<T>(mapping)(res_move(storage_.error))};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{res_forward<T>(mapping)()};
        } else {
          return ResultT{res_forward<T>(mapping)};
        }
      } else {
        return ResultT{Valid<V>{res_move(storage_.valid)}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<V, MappingT>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, E&&>) {
          return ResultT{Error<T>{res_forward<T>(mapping)(res_move(storage_.error))}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Error<T>{res_forward<T>(mapping)()}};
        } else {
          return ResultT{Error<T>{res_forward<T>(mapping)}};
        }
      } else {
        return ResultT{Valid<V>{res_move(storage_.valid)}};
      }
    } else {
      static_assert(false, "Invalid mapping type.");
      unreachable();
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_error(T&& mapping) const && {
    using MappingT = fn_result_t<T, const E&&>;
    if constexpr (is_result_v<MappingT>) {
      using ResultT = Result<V, typename MappingT::ErrorType>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, const E&&>) {
          return ResultT{res_forward<T>(mapping)(res_move(storage_.error))};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{res_forward<T>(mapping)()};
        } else {
          return ResultT{res_forward<T>(mapping)};
        }
      } else {
        return ResultT{Valid<V>{res_move(storage_.valid)}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<V, MappingT>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, const E&&>) {
          return ResultT{Error<T>{res_forward<T>(mapping)(res_move(storage_.error))}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Error<T>{res_forward<T>(mapping)()}};
        } else {
          return ResultT{Error<T>{res_forward<T>(mapping)}};
        }
      } else {
        return ResultT{Valid<V>{res_move(storage_.valid)}};
      }
    } else {
      static_assert(false, "Invalid mapping type.");
      unreachable();
    }
  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  constexpr auto Result<V, E>::map(V1&& valid_mapping, E1&& error_mapping) & {
    using ValidT = fn_result_t<V1, V&>;
    using ErrorT = fn_result_t<E1, E&>;
    if constexpr (is_result_v<ValidT> && is_result_v<ErrorT>) {
      static_assert(is_same_v<ValidT, ErrorT>, "Invalid mapping types.");
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, V&>) {
          return res_forward<V1>(valid_mapping)(storage_.valid);
        } else if constexpr (is_invocable_v<V1>) {
          return res_forward<V1>(valid_mapping)();
        } else {
          return res_forward<V1>(valid_mapping);
        }
      } else if constexpr (is_invocable_v<E1, E&>) {
        return res_forward<E1>(error_mapping)(storage_.error);
      } else if constexpr (is_invocable_v<E1>) {
        return res_forward<E1>(error_mapping)();
      } else {
        return res_forward<E1>(error_mapping);
      }
    } else {
      static_assert(valid_result_type_v<ValidT> && 
          valid_result_type_v<ErrorT>, "Invalid mapping types.");
      using ResultT = Result<ValidT, ErrorT>;
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, V&>) {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)(storage_.valid)}};
        } else if constexpr (is_invocable_v<V1>) {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)()}};
        } else {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)}};
        }
      } else if constexpr (is_invocable_v<E1, E&>) {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)(storage_.error)}};
      } else if constexpr (is_invocable_v<E1>) {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)()}};
      } else {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)}};
      }
    }
  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  constexpr auto Result<V, E>::map(V1&& valid_mapping, E1&& error_mapping) const & {
    using ValidT = fn_result_t<V1, const V&>;
    using ErrorT = fn_result_t<E1, const E&>;
    if constexpr (is_result_v<ValidT> && is_result_v<ErrorT>) {
      static_assert(is_same_v<ValidT, ErrorT>, "Invalid mapping types.");
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, const V&>) {
          return res_forward<V1>(valid_mapping)(storage_.valid);
        } else if constexpr (is_invocable_v<V1>) {
          return res_forward<V1>(valid_mapping)();
        } else {
          return res_forward<V1>(valid_mapping);
        }
      } else if constexpr (is_invocable_v<E1, const E&>) {
        return res_forward<E1>(error_mapping)(storage_.error);
      } else if constexpr (is_invocable_v<E1>) {
        return res_forward<E1>(error_mapping)();
      } else {
        return res_forward<E1>(error_mapping);
      }
    } else {
      static_assert(valid_result_type_v<ValidT> && 
          valid_result_type_v<ErrorT>, "Invalid mapping types.");
      using ResultT = Result<ValidT, ErrorT>;
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, const V&>) {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)(storage_.valid)}};
        } else if constexpr (is_invocable_v<V1>) {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)()}};
        } else {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)}};
        }
      } else if constexpr (is_invocable_v<E1, const E&>) {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)(storage_.error)}};
      } else if constexpr (is_invocable_v<E1>) {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)()}};
      } else {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)}};
      }
    }
  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  constexpr auto Result<V, E>::map(V1&& valid_mapping, E1&& error_mapping) && {
    using ValidT = fn_result_t<V1, V&&>;
    using ErrorT = fn_result_t<E1, E&&>;
    if constexpr (is_result_v<ValidT> && is_result_v<ErrorT>) {
      static_assert(is_same_v<ValidT, ErrorT>, "Invalid mapping types.");
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, V&&>) {
          return res_forward<V1>(valid_mapping)(res_move(storage_.valid));
        } else if constexpr (is_invocable_v<V1>) {
          return res_forward<V1>(valid_mapping)();
        } else {
          return res_forward<V1>(valid_mapping);
        }
      } else if constexpr (is_invocable_v<E1, E&&>) {
        return res_forward<E1>(error_mapping)(res_move(storage_.error));
      } else if constexpr (is_invocable_v<E1>) {
        return res_forward<E1>(error_mapping)();
      } else {
        return res_forward<E1>(error_mapping);
      }
    } else {
      static_assert(valid_result_type_v<ValidT> && 
          valid_result_type_v<ErrorT>, "Invalid mapping types.");
      using ResultT = Result<ValidT, ErrorT>;
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, V&>) {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)(res_move(storage_.valid))}};
        } else if constexpr (is_invocable_v<V1>) {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)()}};
        } else {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)}};
        }
      } else if constexpr (is_invocable_v<E1, E&>) {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)(res_move(storage_.error))}};
      } else if constexpr (is_invocable_v<E1>) {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)()}};
      } else {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)}};
      }
    }
  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  constexpr auto Result<V, E>::map(V1&& valid_mapping, E1&& error_mapping) const && {
    using ValidT = fn_result_t<V1, const V&&>;
    using ErrorT = fn_result_t<E1, const E&&>;
    if constexpr (is_result_v<ValidT> && is_result_v<ErrorT>) {
      static_assert(is_same_v<ValidT, ErrorT>, "Invalid mapping types.");
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, const V&&>) {
          return res_forward<V1>(valid_mapping)(res_move(storage_.valid));
        } else if constexpr (is_invocable_v<V1>) {
          return res_forward<V1>(valid_mapping)();
        } else {
          return res_forward<V1>(valid_mapping);
        }
      } else if constexpr (is_invocable_v<E1, const E&&>) {
        return res_forward<E1>(error_mapping)(res_move(storage_.error));
      } else if constexpr (is_invocable_v<E1>) {
        return res_forward<E1>(error_mapping)();
      } else {
        return res_forward<E1>(error_mapping);
      }
    } else {
      static_assert(valid_result_type_v<ValidT> && 
          valid_result_type_v<ErrorT>, "Invalid mapping types.");
      using ResultT = Result<ValidT, ErrorT>;
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, const V&&>) {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)(res_move(storage_.valid))}};
        } else if constexpr (is_invocable_v<V1>) {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)()}};
        } else {
          return ResultT{Valid<ValidT>{res_forward<V1>(valid_mapping)}};
        }
      } else if constexpr (is_invocable_v<E1, const E&&>) {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)(res_move(storage_.error))}};
      } else if constexpr (is_invocable_v<E1>) {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)()}};
      } else {
        return ResultT{Error<ErrorT>{res_forward<E1>(error_mapping)}};
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_valid(F&& fn) & {
    if (is_valid()) {
      if constexpr (is_invocable_v<F, V&>) {
        res_forward<F>(fn)(storage_.valid);
      } else if constexpr (is_invocable_v<F>) {
        res_forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_valid(F&& fn) const & {
    if (is_valid()) {
      if constexpr (is_invocable_v<F, const V&>) {
        res_forward<F>(fn)(storage_.valid);
      } else if constexpr (is_invocable_v<F>) {
        res_forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_valid(F&& fn) && {
    if (is_valid()) {
      if constexpr (is_invocable_v<F, V&&>) {
        res_forward<F>(fn)(res_move(storage_.valid));
      } else if constexpr (is_invocable_v<F>) {
        res_forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_valid(F&& fn) const && {
    if (is_valid()) {
      if constexpr (is_invocable_v<F, const V&&>) {
        res_forward<F>(fn)(res_move(storage_.valid));
      } else if constexpr (is_invocable_v<F>) {
        res_forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_error(F&& fn) & {
    if (is_error()) {
      if constexpr (is_invocable_v<F, E&>) {
        res_forward<F>(fn)(storage_.error);
      } else if constexpr (is_invocable_v<F>) {
        res_forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_error(F&& fn) const & {
    if (is_error()) {
      if constexpr (is_invocable_v<F, const E&>) {
        res_forward<F>(fn)(storage_.error);
      } else if constexpr (is_invocable_v<F>) {
        res_forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_error(F&& fn) && {
    if (is_error()) {
      if constexpr (is_invocable_v<F, E&&>) {
        res_forward<F>(fn)(res_move(storage_.error));
      } else if constexpr (is_invocable_v<F>) {
        res_forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_error(F&& fn) const && {
    if (is_error()) {
      if constexpr (is_invocable_v<F, const E&&>) {
        res_forward<F>(fn)(res_move(storage_.error));
      } else if constexpr (is_invocable_v<F>) {
        res_forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename... Args>
  constexpr void Result<V, E>::ctor_valid(Args&&... args) {
    V* const new_ptr{TI_BUILTIN_ADDRESSOF(storage_.valid)};
    ::new (new_ptr) V{res_forward<Args>(args)...};
    valid_flag_ = true;
  }

  template<typename V, typename E>
  template<typename... Args>
  constexpr void Result<V, E>::ctor_error(Args&&... args) {
    E* const new_ptr{TI_BUILTIN_ADDRESSOF(storage_.error)};
    ::new (new_ptr) E{res_forward<Args>(args)...};
    valid_flag_ = false;
  }

  template<typename V, typename E>
  constexpr void Result<V, E>::reset_storage() {
    if (is_valid()) {
      storage_.valid.~V();
    } else {
      storage_.error.~E();
    }
  }

  template<typename Vl, typename El, typename Vr, typename Er>
  constexpr bool operator==(const Result<Vl, El>& lhs, 
      const Result<Vr, Er>& rhs) {
    static_assert(is_equality_comparable_v<Vl, Vr>,
        "'Vl' must be equality comparable with 'Vr'.");
    static_assert(is_equality_comparable_v<El, Er>,
        "'El' must be equality comparable with 'Er'.");
    if (lhs.is_valid() && rhs.is_valid()) {
      return lhs.valid() == rhs.valid();
    } else if (lhs.is_error() && rhs.is_error()) {
      return lhs.error() == rhs.error();
    } else {
      return false;
    }
  }

  template<typename Vl, typename El, typename Vr, typename Er>
  constexpr bool operator!=(const Result<Vl, El>& lhs, 
      const Result<Vr, Er>& rhs) {
    return !operator==(lhs, rhs);
  }

  /// @endinternal

} // namespace ti::util
