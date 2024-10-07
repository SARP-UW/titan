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
#include "common/util/cstdint.h"
#include "common/util/type_traits.h"
#include "common/util/utility.h"
#include "common/util/misc.h"
#include "common/tmp.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation Forward Declarations
   **************************************************************************************************/

  namespace {

    struct Vtag {};
    struct Etag {};

    template<typename V, typename E, typename = void>
    struct ResultBase;

    template<typename T>
    inline constexpr bool valid_result_type_v{
        !is_void_v<T> && !is_reference_v<T>};

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section Result Class Utilities
   **************************************************************************************************/

  template<typename T>
  struct Error {
    using ValueType = T;
    T value;
  };

  template<typename T>
  struct Valid {
    using ValueType = T;
    T value;
  };

  template<typename T> Error(T) -> Error<T>;
  template<typename T> Valid(T) -> Valid<T>;

  template<typename T> 
  inline constexpr bool is_result_v{false};

  template<typename T> 
  inline constexpr bool is_error_v{false};

  template<typename T> 
  inline constexpr bool is_valid_v{false};

  /**************************************************************************************************
   * @section Result Class Declaration
   **************************************************************************************************/

  template<typename V = monostate_t, typename E = monostate_t>
  class Result : public ResultBase<V, E> {

    public:

      static_assert(valid_result_type_v<V>, "'V' is not a valid result type.");
      static_assert(valid_result_type_v<E>, "'E' is not a valid result type.");

      using ValidType = V;
      using ErrorType = E;
      using in_place_valid_t = in_place_type_t<Valid<ValidType>>;
      using in_place_error_t = in_place_type_t<Error<ErrorType>>;
      using ThisType = Result<V, E>;

      template<typename T>
      constexpr Result(const Valid<T>& valid);

      template<typename T>
      constexpr Result(Valid<T>&& valid);

      template<typename T>
      constexpr Result(const Error<T>& error);

      template<typename T>
      constexpr Result(Error<T>&& error);

      template<typename V1, typename E1>
      constexpr Result(const Result<V1, E1>& other);

      template<typename V1, typename E1>
      constexpr Result(Result<V1, E1>&& other);

      template<typename T, typename... Args>
      constexpr explicit Result(in_place_type_t<Valid<T>>, Args&&... args);

      template<typename T, typename... Args>
      constexpr explicit Result(in_place_type_t<Error<T>>, Args&&... args);

      template<typename T>
      ThisType& operator=(const Valid<T>& valid);

      template<typename T>
      ThisType& operator=(Valid<T>&& valid);

      template<typename T>
      ThisType& operator=(const Error<T>& error);

      template<typename T>
      ThisType& operator=(Error<T>&& error);

      template<typename V1, typename E1>
      ThisType& operator=(const Result<V1, E1>& other);

      template<typename V1, typename E1>
      ThisType& operator=(Result<V1, E1>&& other);

      template<typename T>
      void emplace(const Valid<T>& valid);

      template<typename T>
      void emplace(Valid<T>&& valid);

      template<typename T>
      void emplace(const Error<T>& error);

      template<typename T>
      void emplace(Error<T>&& error);

      template<typename V1, typename E1>
      void emplace(const Result<V1, E1>& other);

      template<typename V1, typename E1>
      void emplace(Result<V1, E1>&& other);

      template<typename T, typename... Args>
      void emplace(in_place_type_t<Valid<T>>, Args&&... args);

      template<typename T, typename... Args>
      void emplace(in_place_type_t<Error<T>>, Args&&... args);

      [[nodiscard]] constexpr bool is_valid() const;

      [[nodiscard]] constexpr bool is_error() const;

      constexpr operator bool() const;

      template<typename T>
      [[nodiscard]] constexpr bool is_valid(const T& value) const;

      template<typename T>
      [[nodiscard]] constexpr bool is_error(const T& value) const;

      [[nodiscard]] constexpr V& valid() &;

      [[nodiscard]] constexpr const V& valid() const &;

      [[nodiscard]] constexpr V&& valid() &&;

      [[nodiscard]] constexpr const V&& valid() const &&;

      [[nodiscard]] constexpr V& operator*() &;

      [[nodiscard]] constexpr const V& operator*() const &;

      [[nodiscard]] constexpr V&& operator*() &&;

      [[nodiscard]] constexpr const V&& operator*() const &&;

      [[nodiscard]] constexpr V* valid_ptr();

      [[nodiscard]] constexpr const V* valid_ptr() const;

      [[nodiscard]] constexpr V* operator->();

      [[nodiscard]] constexpr const V* operator->() const;

      [[nodiscard]] constexpr E& error() &;

      [[nodiscard]] constexpr const E& error() const &;

      [[nodiscard]] constexpr E&& error() &&;

      [[nodiscard]] constexpr const E&& error() const &&;

      [[nodiscard]] constexpr E* error_ptr();

      [[nodiscard]] constexpr const E* error_ptr() const;

      template<typename T>
      [[nodiscard]] constexpr V valid_or(T&& def_value) const &;

      template<typename T>
      [[nodiscard]] constexpr V&& valid_or(T&& def_value) &&;

      template<typename T>
      [[nodiscard]] constexpr E error_or(T&& def_value) const &;

      template<typename T>
      [[nodiscard]] constexpr E&& error_or(T&& def_value) &&;

      template<typename T>
      constexpr auto map_valid(T&& mapping) &;

      template<typename T>
      constexpr auto map_valid(T&& mapping) const &;

      template<typename T>
      constexpr auto map_valid(T&& mapping) &&;

      template<typename T>
      constexpr auto map_valid(T&& mapping) const &&;

      template<typename T>
      constexpr auto map_error(T&& mapping) &;

      template<typename T>
      constexpr auto map_error(T&& mapping) const &;

      template<typename T>
      constexpr auto map_error(T&& mapping) &&;

      template<typename T>
      constexpr auto map_error(T&& mapping) const &&;

      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) &;

      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) const &;

      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) &&;

      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) const &&;

      template<typename F>
      constexpr void apply_valid(F&& fn) &;

      template<typename F>
      constexpr void apply_valid(F&& fn) const &;

      template<typename F>
      constexpr void apply_valid(F&& fn) &&;

      template<typename F>
      constexpr void apply_valid(F&& fn) const &&;

      template<typename F>
      constexpr void apply_error(F&& fn) &;

      template<typename F>
      constexpr void apply_error(F&& fn) const &;

      template<typename F>
      constexpr void apply_error(F&& fn) &&;

      template<typename F>
      constexpr void apply_error(F&& fn) const &&;

      using ResultBase<V, E>::~ResultBase;

    private:

      union StorageT;

      template<typename... Args>
      constexpr void ctor_valid(Args&&... args);

      template<typename... Args>
      constexpr void ctor_error(Args&&... args);

      constexpr void reset_storage();

      StorageT storage_;
      bool valid_flag_;

  }; // class Result

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

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
        valid{forward<T>(value)} {};

    template<typename T>
    constexpr Storage(Etag, T&& value) :
        error{forward<T>(value)} {};

    template<typename... Args>
    constexpr Storage(Vtag, Args&&... args) :
        valid{forward<Args>(args)...} {};

    template<typename... Args>
    constexpr Storage(Etag, Args&&... args) :
        error{forward<Args>(args)...} {};

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
      storage_{Vtag{}, move(valid.value)},
      valid_flag_{true} {}

  template<typename V, typename E>
  template<typename T>
  constexpr Result<V, E>::Result(const Error<T>& error) :
      storage_{Etag{}, error.value},
      valid_flag_{false} {}

  template<typename V, typename E>
  template<typename T>
  constexpr Result<V, E>::Result(Error<T>&& error) :
      storage_{Etag{}, move(error.value)},
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
          other.valid_flag_ ? move(other.valid()) : 
              move(other.error())},
      valid_flag_{other.valid_flag_} {}

  template<typename V, typename E>
  template<typename T, typename... Args>
  constexpr Result<V, E>::Result(
      in_place_type_t<Valid<T>>, Args&&... args) :
          storage_{Vtag{}, forward<Args>(args)...},
          valid_flag_{true} {}


  template<typename V, typename E>
  template<typename T, typename... Args>
  constexpr Result<V, E>::Result(
      in_place_type_t<Error<T>>, Args&&... args) :
          storage_{Etag{}, forward<Args>(args)...},
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
      storage_.valid = move(valid.value);
    } else {
      storage_.error.~E();
      ctor_valid(move(valid.value));
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
      storage_.error = move(error.value);
    } else {
      storage_.valid.~V();
      ctor_error(move(error.value));
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
        this->operator=(Valid<V1>{move(other.valid())});
      } else {
        this->operator=(Error<E1>{move(other.error())});
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
    ctor_valid(move(valid.value));
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
    ctor_error(move(error.value));
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
      this->ctor_valid(move(other.valid()));
    } else {
      this->ctor_error(move(other.error()));
    }
  }

  template<typename V, typename E>
  template<typename T, typename... Args>
  void Result<V, E>::emplace(in_place_type_t<Valid<T>>, Args&&... args) {
    reset_storage();
    ctor_valid(forward<Args>(args)...);
  }

  template<typename V, typename E>
  template<typename T, typename... Args>
  void Result<V, E>::emplace(in_place_type_t<Error<T>>, Args&&... args) {
    reset_storage();
    ctor_error(forward<Args>(args)...);
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
    if (unlikely(!is_valid())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return storage_.valid;
  }

  template<typename V, typename E>
  constexpr const V& Result<V, E>::valid() const & {
    if (unlikely(!is_valid())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return storage_.valid;
  }

  template<typename V, typename E>
  constexpr V&& Result<V, E>::valid() && {
    if (unlikely(!is_valid())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return move(storage_.valid);
  }

  template<typename V, typename E>
  constexpr const V&& Result<V, E>::valid() const && {
    if (unlikely(!is_valid())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return move(storage_.valid);
  }

  template<typename V, typename E>
  constexpr V& Result<V, E>::operator*() & {
    if (unlikely(!is_valid())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return valid();
  }

  template<typename V, typename E>
  constexpr const V& Result<V, E>::operator*() const & {
    return valid();
  }

  template<typename V, typename E>
  constexpr V&& Result<V, E>::operator*() && {
    return move(valid());
  }

  template<typename V, typename E>
  constexpr const V&& Result<V, E>::operator*() const && {
    return move(valid());
  }

  template<typename V, typename E>
  constexpr V* Result<V, E>::valid_ptr() {
    return is_valid() ? addressof(storage_.valid) : nullptr;
  }

  template<typename V, typename E>
  constexpr const V* Result<V, E>::valid_ptr() const {
    return is_valid() ? addressof(storage_.valid) : nullptr;
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
    if (unlikely(!is_error())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return storage_.error;
  }

  template<typename V, typename E>
  constexpr const E& Result<V, E>::error() const & {
    if (unlikely(!is_error())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return storage_.error;
  }

  template<typename V, typename E>
  constexpr E&& Result<V, E>::error() && {
    if (unlikely(!is_error())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return move(storage_.error);
  }

  template<typename V, typename E>
  constexpr const E&& Result<V, E>::error() const && {
    if (unlikely(!is_error())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return move(storage_.error);
  }

  template<typename V, typename E>
  constexpr E* Result<V, E>::error_ptr() {
    if (unlikely(!is_error())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return addressof(storage_.error);
  }

  template<typename V, typename E>
  constexpr const E* Result<V, E>::error_ptr() const {
    if (unlikely(!is_error())) {
      sys_error("Invalid result access.");
      unreachable();
    }
    return addressof(storage_.error);
  }

  template<typename V, typename E>
  template<typename T>
  constexpr V Result<V, E>::valid_or(T&& def_value) const & {
    if (is_valid()) {
      return valid();
    } else {
      return forward<T>(def_value);
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr V&& Result<V, E>::valid_or(T&& def_value) && {
    if (is_valid()) {
      return move(valid());
    } else {
      return forward<T>(def_value);
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr E Result<V, E>::error_or(T&& def_value) const & {
    if (is_error()) {
      return error();
    } else {
      return forward<T>(def_value);
    }
  }

  template<typename V, typename E>
  template<typename T>
  constexpr E&& Result<V, E>::error_or(T&& def_value) && {
    if (is_error()) {
      return move(error());
    } else {
      return forward<T>(def_value);
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
          return ResultT{forward<T>(mapping)(storage_.valid)};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{forward<T>(mapping)()};
        } else {
          return ResultT{forward<T>(mapping)};
        }
      } else {
        return ResultT{Error<E>{storage_.error}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<MappingT, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, V&>) {
          return ResultT{Valid<T>{forward<T>(mapping)(storage_.valid)}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Valid<T>{forward<T>(mapping)()}};
        } else {
          return ResultT{Valid<T>{Forward<T>(mapping)}};
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
          return ResultT{forward<T>(mapping)(storage_.valid)};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{forward<T>(mapping)()};
        } else {
          return ResultT{forward<T>(mapping)};
        }
      } else {
        return ResultT{Error<E>{storage_.error}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<MappingT, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, const V&>) {
          return ResultT{Valid<T>{forward<T>(mapping)(storage_.valid)}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Valid<T>{forward<T>(mapping)()}};
        } else {
          return ResultT{Valid<T>{Forward<T>(mapping)}};
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
          return ResultT{forward<T>(mapping)(move(storage_.valid))};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{forward<T>(mapping)()};
        } else {
          return ResultT{forward<T>(mapping)};
        }
      } else {
        return ResultT{Error<E>{move(storage_.error)}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<MappingT, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, V&&>) {
          return ResultT{Valid<T>{forward<T>(mapping)(move(storage_.valid))}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Valid<T>{forward<T>(mapping)()}};
        } else {
          return ResultT{Valid<T>{Forward<T>(mapping)}};
        }
      } else {
        return ResultT{Error<E>{move(storage_.error)}};
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
          return ResultT{forward<T>(mapping)(move(storage_.valid))};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{forward<T>(mapping)()};
        } else {
          return ResultT{forward<T>(mapping)};
        }
      } else {
        return ResultT{Error<E>{move(storage_.error)}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<MappingT, E>;
      if (is_valid()) {
        if constexpr (is_invocable_v<T, const V&&>) {
          return ResultT{Valid<T>{forward<T>(mapping)(move(storage_.valid))}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Valid<T>{forward<T>(mapping)()}};
        } else {
          return ResultT{Valid<T>{Forward<T>(mapping)}};
        }
      } else {
        return ResultT{Error<E>{move(storage_.error)}};
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
          return ResultT{forward<T>(mapping)(storage_.error)};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{forward<T>(mapping)()};
        } else {
          return ResultT{forward<T>(mapping)};
        }
      } else {
        return ResultT{Valid<V>{storage_.valid}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<V, MappingT>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, E&>) {
          return ResultT{Error<T>{forward<T>(mapping)(storage_.error)}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Error<T>{forward<T>(mapping)()}};
        } else {
          return ResultT{Error<T>{forward<T>(mapping)}};
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
          return ResultT{forward<T>(mapping)(storage_.error)};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{forward<T>(mapping)()};
        } else {
          return ResultT{forward<T>(mapping)};
        }
      } else {
        return ResultT{Valid<V>{storage_.valid}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<V, MappingT>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, const E&>) {
          return ResultT{Error<T>{forward<T>(mapping)(storage_.error)}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Error<T>{forward<T>(mapping)()}};
        } else {
          return ResultT{Error<T>{forward<T>(mapping)}};
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
          return ResultT{forward<T>(mapping)(move(storage_.error))};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{forward<T>(mapping)()};
        } else {
          return ResultT{forward<T>(mapping)};
        }
      } else {
        return ResultT{Valid<V>{move(storage_.valid)}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<V, MappingT>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, E&&>) {
          return ResultT{Error<T>{forward<T>(mapping)(move(storage_.error))}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Error<T>{forward<T>(mapping)()}};
        } else {
          return ResultT{Error<T>{forward<T>(mapping)}};
        }
      } else {
        return ResultT{Valid<V>{move(storage_.valid)}};
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
          return ResultT{forward<T>(mapping)(move(storage_.error))};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{forward<T>(mapping)()};
        } else {
          return ResultT{forward<T>(mapping)};
        }
      } else {
        return ResultT{Valid<V>{move(storage_.valid)}};
      }
    } else if constexpr (valid_result_type_v<MapingT>) {
      using ResultT = Result<V, MappingT>;
      if (is_error()) {
        if constexpr (is_invocable_v<T, const E&&>) {
          return ResultT{Error<T>{forward<T>(mapping)(move(storage_.error))}};
        } else if constexpr (is_invocable_v<T>) {
          return ResultT{Error<T>{forward<T>(mapping)()}};
        } else {
          return ResultT{Error<T>{forward<T>(mapping)}};
        }
      } else {
        return ResultT{Valid<V>{move(storage_.valid)}};
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
          return forward<V1>(valid_mapping)(storage_.valid);
        } else if constexpr (is_invocable_v<V1>) {
          return forward<V1>(valid_mapping)();
        } else {
          return forward<V1>(valid_mapping);
        }
      } else if constexpr (is_invocable_v<E1, E&>) {
        return forward<E1>(error_mapping)(storage_.error);
      } else if constexpr (is_invocable_v<E1>) {
        return forward<E1>(error_mapping)();
      } else {
        return forward<E1>(error_mapping);
      }
    } else {
      static_assert(valid_result_type_v<ValidT> && 
          valid_result_type_v<ErrorT>, "Invalid mapping types.");
      using ResultT = Result<ValidT, ErrorT>;
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, V&>) {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)(storage_.valid)}};
        } else if constexpr (is_invocable_v<V1>) {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)()}};
        } else {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)}};
        }
      } else if constexpr (is_invocable_v<E1, E&>) {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)(storage_.error)}};
      } else if constexpr (is_invocable_v<E1>) {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)()}};
      } else {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)}};
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
          return forward<V1>(valid_mapping)(storage_.valid);
        } else if constexpr (is_invocable_v<V1>) {
          return forward<V1>(valid_mapping)();
        } else {
          return forward<V1>(valid_mapping);
        }
      } else if constexpr (is_invocable_v<E1, const E&>) {
        return forward<E1>(error_mapping)(storage_.error);
      } else if constexpr (is_invocable_v<E1>) {
        return forward<E1>(error_mapping)();
      } else {
        return forward<E1>(error_mapping);
      }
    } else {
      static_assert(valid_result_type_v<ValidT> && 
          valid_result_type_v<ErrorT>, "Invalid mapping types.");
      using ResultT = Result<ValidT, ErrorT>;
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, const V&>) {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)(storage_.valid)}};
        } else if constexpr (is_invocable_v<V1>) {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)()}};
        } else {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)}};
        }
      } else if constexpr (is_invocable_v<E1, const E&>) {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)(storage_.error)}};
      } else if constexpr (is_invocable_v<E1>) {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)()}};
      } else {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)}};
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
          return forward<V1>(valid_mapping)(move(storage_.valid));
        } else if constexpr (is_invocable_v<V1>) {
          return forward<V1>(valid_mapping)();
        } else {
          return forward<V1>(valid_mapping);
        }
      } else if constexpr (is_invocable_v<E1, E&&>) {
        return forward<E1>(error_mapping)(move(storage_.error));
      } else if constexpr (is_invocable_v<E1>) {
        return forward<E1>(error_mapping)();
      } else {
        return forward<E1>(error_mapping);
      }
    } else {
      static_assert(valid_result_type_v<ValidT> && 
          valid_result_type_v<ErrorT>, "Invalid mapping types.");
      using ResultT = Result<ValidT, ErrorT>;
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, V&>) {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)(move(storage_.valid))}};
        } else if constexpr (is_invocable_v<V1>) {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)()}};
        } else {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)}};
        }
      } else if constexpr (is_invocable_v<E1, E&>) {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)(move(storage_.error))}};
      } else if constexpr (is_invocable_v<E1>) {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)()}};
      } else {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)}};
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
          return forward<V1>(valid_mapping)(move(storage_.valid));
        } else if constexpr (is_invocable_v<V1>) {
          return forward<V1>(valid_mapping)();
        } else {
          return forward<V1>(valid_mapping);
        }
      } else if constexpr (is_invocable_v<E1, const E&&>) {
        return forward<E1>(error_mapping)(move(storage_.error));
      } else if constexpr (is_invocable_v<E1>) {
        return forward<E1>(error_mapping)();
      } else {
        return forward<E1>(error_mapping);
      }
    } else {
      static_assert(valid_result_type_v<ValidT> && 
          valid_result_type_v<ErrorT>, "Invalid mapping types.");
      using ResultT = Result<ValidT, ErrorT>;
      if (is_valid()) {
        if constexpr (is_invocable_v<V1, const V&&>) {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)(move(storage_.valid))}};
        } else if constexpr (is_invocable_v<V1>) {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)()}};
        } else {
          return ResultT{Valid<ValidT>{forward<V1>(valid_mapping)}};
        }
      } else if constexpr (is_invocable_v<E1, const E&&>) {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)(move(storage_.error))}};
      } else if constexpr (is_invocable_v<E1>) {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)()}};
      } else {
        return ResultT{Error<ErrorT>{forward<E1>(error_mapping)}};
      }
    }
  }

  template<typename V, typename E>
  template<typename F>
  constexpr void Result<V, E>::apply_valid(F&& fn) & {
    if (is_valid()) {
      if constexpr (is_invocable_v<F, V&>) {
        forward<F>(fn)(storage_.valid);
      } else if constexpr (is_invocable_v<F>) {
        forward<F>(fn)();
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
        forward<F>(fn)(storage_.valid);
      } else if constexpr (is_invocable_v<F>) {
        forward<F>(fn)();
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
        forward<F>(fn)(move(storage_.valid));
      } else if constexpr (is_invocable_v<F>) {
        forward<F>(fn)();
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
        forward<F>(fn)(move(storage_.valid));
      } else if constexpr (is_invocable_v<F>) {
        forward<F>(fn)();
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
        forward<F>(fn)(storage_.error);
      } else if constexpr (is_invocable_v<F>) {
        forward<F>(fn)();
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
        forward<F>(fn)(storage_.error);
      } else if constexpr (is_invocable_v<F>) {
        forward<F>(fn)();
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
        forward<F>(fn)(move(storage_.error));
      } else if constexpr (is_invocable_v<F>) {
        forward<F>(fn)();
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
        forward<F>(fn)(move(storage_.error));
      } else if constexpr (is_invocable_v<F>) {
        forward<F>(fn)();
      } else {
        static_assert(false, "Invalid application type.");
      }
    }
  }

  template<typename V, typename E>
  template<typename... Args>
  constexpr void Result<V, E>::ctor_valid(Args&&... args) {
    V* const new_ptr{addressof(storage_.valid)};
    ::new (new_ptr) V{forward<Args>(args)...};
    valid_flag_ = true;
  }

  template<typename V, typename E>
  template<typename... Args>
  constexpr void Result<V, E>::ctor_error(Args&&... args) {
    E* const new_ptr{addressof(storage_.error)};
    ::new (new_ptr) E{forward<Args>(args)...};
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

  /// @endinternal

} // namespace ti::util
