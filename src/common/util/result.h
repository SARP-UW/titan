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

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation Forward Declarations
   **************************************************************************************************/

  namespace {

    struct Vtag {};
    struct Etag {};

    template<typename V, typename E>
    struct ResultBase;

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section Result Class Declaration
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

  template<typename V, typename E>
  class Result : public ResultBase<V, E> {

    public:

      using ValidType = V;
      using ErrorType = E;
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
      [[nodiscard]] constexpr bool is_valid(T&& value) const;

      template<typename T>
      [[nodiscard]] constexpr bool is_error(T&& value) const;

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
      constexpr auto map_valid(T&& mapping);

      template<typename T>
      constexpr auto map_valid(T&& mapping) const;

      template<typename T>
      constexpr auto map_error(T&& mapping);

      template<typename T>
      constexpr auto map_error(T&& mapping) const;

      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping);

      template<typename V1, typename E1>
      constexpr auto map(V1&& valid_mapping, E1&& error_mapping) const;

      template<typename F>
      constexpr auto apply_valid(F&& fn);

      template<typename F>
      constexpr auto apply_valid(F&& fn) const;

      template<typename F>
      constexpr auto apply_error(F&& fn);

      template<typename F>
      constexpr auto apply_error(F&& fn) const;

      template<typename Fv, typename Fe>
      constexpr auto apply(Fv&& valid_fn, Fe&& error_fn);

      template<typename Fv, typename Fe>
      constexpr auto apply(Fv&& valid_fn, Fe&& error_fn) const;

      using ResultBase<V, E>::~ResultBase;

    private:

      union StorageT;

      template<typename T>
      constexpr void ctor_valid();

      StorageT storage_;
      bool valid_flag_;

  }; // class Result

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename V, typename E>
  union Result<V, E>::StorageT {

    template<typename T>
    constexpr StorageT(Vtag, T&& value) :
        valid{forward<T>(value)} {}

    template<typename T>
    constexpr Storage(Etag, T&& value) :
        error{forward<T>(value)} {}

    template<typename... Args>
    constexpr Storage(Vtag, Args&&... args) :
        valid{forward<Args>(args)...} {}

    template<typename... Args>
    constexpr Storage(Etag, Args&&... args) :
        error{forward<Args>(args)...} {}

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

  }

  template<typename V, typename E>
  template<typename T>
  Result<V, E>& Result<V, E>::operator=(Valid<T>&& valid) {

  }

  template<typename V, typename E>
  template<typename T>
  Result<V, E>& Result<V, E>::operator=(const Error<T>& error) {

  }

  template<typename V, typename E>
  template<typename T>
  Result<V, E>& Result<V, E>::operator=(Error<T>&& error) {

  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  Result<V, E>& Result<V, E>::operator=(const Result<V1, E1>& other) {

  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  Result<V, E>& Result<V, E>::operator=(Result<V1, E1>&& other) {

  }

  template<typename V, typename E>
  template<typename T>
  void Result<V, E>::emplace(const Valid<T>& valid) {

  }

  template<typename V, typename E>
  template<typename T>
  void Result<V, E>::emplace(Valid<T>&& valid) {

  }

  template<typename V, typename E>
  template<typename T>
  void Result<V, E>::emplace(const Error<T>& error) {

  }

  template<typename V, typename E>
  template<typename T>
  void Result<V, E>::emplace(Error<T>&& error) {

  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  void Result<V, E>::emplace(const Result<V1, E1>& other) {

  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  void Result<V, E>::emplace(Result<V1, E1>&& other) {

  }

  template<typename V, typename E>
  template<typename T, typename... Args>
  void Result<V, E>::emplace(in_place_type_t<Valid<T>>, Args&&... args) {

  }

  template<typename V, typename E>
  template<typename T, typename... Args>
  void Result<V, E>::emplace(in_place_type_t<Error<T>>, Args&&... args) {

  }

  template<typename V, typename E>
  constexpr bool Result<V, E>::is_valid() const {

  }

  template<typename V, typename E>
  constexpr bool Result<V, E>::is_error() const {

  }

  template<typename V, typename E>
  constexpr Result<V, E>::operator bool() const {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr bool Result<V, E>::is_valid(T&& value) const {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr bool Result<V, E>::is_error(T&& value) const {

  }

  template<typename V, typename E>
  constexpr V& Result<V, E>::valid() & {

  }

  template<typename V, typename E>
  constexpr const V& Result<V, E>::valid() const & {

  }

  template<typename V, typename E>
  constexpr V&& Result<V, E>::valid() && {

  }

  template<typename V, typename E>
  constexpr const V&& Result<V, E>::valid() const && {

  }

  template<typename V, typename E>
  constexpr V& Result<V, E>::operator*() & {

  }

  template<typename V, typename E>
  constexpr const V& Result<V, E>::operator*() const & {

  }

  template<typename V, typename E>
  constexpr V&& Result<V, E>::operator*() && {

  }

  template<typename V, typename E>
  constexpr const V&& Result<V, E>::operator*() const && {

  }

  template<typename V, typename E>
  constexpr V* Result<V, E>::valid_ptr() {

  }

  template<typename V, typename E>
  constexpr const V* Result<V, E>::valid_ptr() const {

  }

  template<typename V, typename E>
  constexpr V* Result<V, E>::operator->() {

  }

  template<typename V, typename E>
  constexpr const V* Result<V, E>::operator->() const {

  }

  template<typename V, typename E>
  constexpr E& Result<V, E>::error() & {

  }

  template<typename V, typename E>
  constexpr const E& Result<V, E>::error() const & {

  }

  template<typename V, typename E>
  constexpr E&& Result<V, E>::error() && {

  }

  template<typename V, typename E>
  constexpr const E&& Result<V, E>::error() const && {

  }

  template<typename V, typename E>
  constexpr E* Result<V, E>::error_ptr() {

  }

  template<typename V, typename E>
  constexpr const E* Result<V, E>::error_ptr() const {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr V Result<V, E>::valid_or(T&& def_value) const & {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr V&& Result<V, E>::valid_or(T&& def_value) && {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr E Result<V, E>::error_or(T&& def_value) const & {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr E&& Result<V, E>::error_or(T&& def_value) && {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_valid(T&& mapping) {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_valid(T&& mapping) const {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_error(T&& mapping) {

  }

  template<typename V, typename E>
  template<typename T>
  constexpr auto Result<V, E>::map_error(T&& mapping) const {

  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  constexpr auto Result<V, E>::map(V1&& valid_mapping, E1&& error_mapping) {

  }

  template<typename V, typename E>
  template<typename V1, typename E1>
  constexpr auto Result<V, E>::map(V1&& valid_mapping, E1&& error_mapping) const {

  }

  template<typename V, typename E>
  template<typename F>
  constexpr auto Result<V, E>::apply_valid(F&& fn) {

  }

  template<typename V, typename E>
  template<typename F>
  constexpr auto Result<V, E>::apply_valid(F&& fn) const {

  }

  template<typename V, typename E>
  template<typename F>
  constexpr auto Result<V, E>::apply_error(F&& fn) {

  }

  template<typename V, typename E>
  template<typename F>
  constexpr auto Result<V, E>::apply_error(F&& fn) const {

  }

  template<typename V, typename E>
  template<typename Fv, typename Fe>
  constexpr auto Result<V, E>::apply(Fv&& valid_fn, Fe&& error_fn) {

  }

  template<typename V, typename E>
  template<typename Fv, typename Fe>
  constexpr auto Result<V, E>::apply(Fv&& valid_fn, Fe&& error_fn) const {

  }

  /// @endinternal

} // namespace ti::util
