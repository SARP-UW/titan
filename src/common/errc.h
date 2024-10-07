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
 * @file common/util/errc.h 
 * @authors Aaron McBride 
 * @brief Contains error code enums.
 */

#pragma once
#include "common/util/utility.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Error Code and Source Enum Definitions
   **************************************************************************************************/

  /**
   * @brief Denotes the cause of an error.
   */
  enum class ErrorCode {
    other, /** @brief Denotes that the cause of an error is not representable by any 'ErrorCode' values. */
    unkown, /** @brief Denotes that the cause of an errors is unknown. */
    invalid_arg, /** @brief Denotes that a given argument is invalid. */
    out_of_bounds, /** @brief Denotes that a value or type is out of bounds. */
    invalid_access, /** @brief Denotes that an attempt to access a value is invalid. */
  };

  /**
   * @brief Denotes the source of an error.
   */
  enum class ErrorSource {
    other, /** @brief Denotes that the source of an error is not representable by any 'ErrorSource' value. */
    unknown, /** @brief Denotes that the source of an error is unknown. */
    util_lib, /** @brief Denotes the 'common/util' library */
    runtime_lib, /** @brief Denotes the 'common/runtime' library */
  };

  /**************************************************************************************************
   * @section Enum to String Conversion Utilities
   **************************************************************************************************/

  /**
   * @brief Gets the string representation of an 'ErrorCode' enum value.
   * @param errc The 'ErrorCode' enum value to convert.
   * @returns A c-string which contains the error code string.
   */
  [[nodiscard]] constexpr const char* to_string(const ErrorCode errc);

  /**
   * @brief Gets the string representation of an 'ErrorSource' enum value.
   * @param source The 'ErrorSource' enum value to convert.
   * @returns A c-string which contains the error source string.
   */
  [[nodiscard]] constexpr const char* to_string(const ErrorSource source);

  /**************************************************************************************************
   * @section Error Type Class Declaration
   **************************************************************************************************/

  /**
   * @brief Contains information about an error.
   */
  class ErrorType {

    public:

      /** @brief The default error code value. */
      static constexpr ErrorCode default_errc{ErrorCode::unkown};

      /** @brief The default error source value. */
      static constexpr ErrorSource default_source{ErrorSource::unknown};

      /** @brief The default error message. */
      static constexpr const char* default_msg{nullptr};

      /**
       * @brief Initializes a new 'ErrorType' instance and with information about 
       *        it's associated error.
       * @param errc An ErrorCode enum value which denotes the cause of the error.
       * @param source An ErrorSource enum value which denotes the source of the error.
       * @param msg A c-string which contains a message about the error.
       */
      constexpr explicit ErrorType(
          const ErrorCode errc = default_errc, 
          const ErrorSource source = default_source, 
          const char* msg = default_msg);

      /**
       * @brief Creates a copy of annother 'ErrorType' instance.
       * @param other The 'ErrorType' instance to copy.
       */
      constexpr ErrorType(const ErrorType& other);

      /**
       * @brief Sets this 'ErrorType' equal to annother.
       * @param other The 'ErrorType' instance to copy.
       * @returns A reference to this 'ErrorType' instance.
       */
      constexpr ErrorType& operator=(const ErrorType& other);

      /**
       * @brief Assigns a new error to this 'ErrorType' instance.
       * @param errc An ErrorCode enum value which denotes the cause of the error.
       * @param source An ErrorSource enum value which denotes the source of the error.
       * @param msg A c-string which contains a message about the error.
       */
      constexpr void assign(
          const ErrorCode errc = default_errc, 
          const ErrorSource source = default_source, 
          const char* msg = default_msg);

      /**
       * @brief Sets the error code associated with this 'ErrorType' instance.
       * @param errc An ErrorCode enum value which denotes the cause of the error.
       */
      constexpr void set_error_code(const ErrorCode errc);

      /**
       * @brief Gets the error code associated with this 'ErrorType' instance.
       * @returns The assigned ErrorCode enum value.
       */
      [[nodiscard]] constexpr ErrorCode error_code() const;

      /**
       * @brief Gets the string representation of the error code 
       *        associated with this 'ErrorType' instance.
       * @returns A c-string which contains the error code string.
       */
      [[nodiscard]] constexpr const char* error_code_str() const;

      /**
       * @brief Sets the error source associated with this 'ErrorType' instance.
       * @param source An ErrorSource enum value which denotes the source of the error.
       */
      constexpr void set_error_source(const ErrorSource source);

      /**
       * @brief Gets the error source associated with this 'ErrorType' instance.
       * @returns The assigned ErrorSource enum value.
       */
      [[nodiscard]] constexpr ErrorSource error_source() const;

      /**
       * @brief Gets the string representation of the error source 
       *        associated with this 'ErrorType' instance.
       * @returns A c-string which contains the error source string.
       */
      [[nodiscard]] constexpr const char* error_source_str() const;

      /**
       * @brief Sets the message associated with this 'ErrorType' instance.
       * @param msg A c-string which contains the error message.
       */
      constexpr void set_message(const char* msg);

      /**
       * @brief Gets the message associated with this 'ErrorType' instance.
       * @returns A c-string which contains the error message.
       */
      [[nodiscard]] constexpr const char* message() const;

    private:

      ErrorCode errc_;
      ErrorSource source_;
      const char* msg_;

  };

  /**
   * @brief Compares two 'ErrorType' instances for equality.
   * @param lhs The left-hand 'ErrorType' instance.
   * @param rhs The right-hand 'ErrorType' instance.
   * @returns True if the error associated with both instances is the same,
   *          or false otherwise (ErrorTypes must have the same error code, 
   *          source and message).
   */
  [[nodiscard]] constexpr bool operator == (const ErrorType& lhs, const ErrorType& rhs);

  /**
   * @brief Compares two 'ErrorType' instances for inequality.
   * @param lhs The left-hand 'ErrorType' instance.
   * @param rhs The right-hand 'ErrorType' instance.
   * @returns True if the error associated with @p 'lhs' is different from 
   *          the error associated with @p 'rhs', or false otherwise (ErrorTypes 
   *          are not equal if they have differing error codes, sources and/or 
   *          messages).
   */
  [[nodiscard]] constexpr bool operator != (const ErrorType& lhs, const ErrorType& rhs);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  constexpr const char* to_string(const ErrorCode errc) {
    switch(errc) {
      case ErrorCode::other: { return "other"; }
      case ErrorCode::unkown: { return "unkown"; }
      case ErrorCode::invalid_arg: { return "invalid argument"; }
      case ErrorCode::out_of_bounds: { return "out of bounds"; }
      case ErrorCode::invalid_access: { return "invalid access"; }
    }
  }

  constexpr const char* to_string(const ErrorSource source) {
    switch(source) {
      case ErrorSource::other: { return "other"; }
      case ErrorSource::unknown: { return "unknown"; }
      case ErrorSource::util_lib: { return "util library"; }
      case ErrorSource::runtime_lib: { return "runtime library"; }
    }
  }

  constexpr ErrorType::ErrorType(
      const ErrorCode errc = default_errc, 
      const ErrorSource source = default_source, 
      const char* msg = default_msg) :
          errc_{errc}, source_{source}, msg_{msg} {}

  constexpr ErrorType::ErrorType(const ErrorType& other) :
      errc_{other.errc_}, source_{other.source_}, msg_{other.msg_} {}

  constexpr ErrorType& ErrorType::operator=(const ErrorType& other) {
    if (unlikely(this != &other)) {
      this->errc_ = other.errc_;
      this->source_ = other.source_;
      this->msg_ = other.msg_;
    }
    return *this;
  }

  constexpr void ErrorType::assign(
      const ErrorCode errc = ErrorCode::unkown, 
      const ErrorSource source = ErrorSource::unknown, 
      const char* msg = nullptr) {
    errc_ = errc;
    source_ = source;
    msg_ = msg;
  }

  constexpr void ErrorType::set_error_code(const ErrorCode errc) {
    errc_ = errc;
  }

  constexpr ErrorCode ErrorType::error_code() const {
    return errc_;
  }

  constexpr const char* ErrorType::error_code_str() const {
    return to_string(errc_);
  }

  constexpr void ErrorType::set_error_source(const ErrorSource source) {
    source_ = source;
  }

  constexpr ErrorSource ErrorType::error_source() const {
    return source_;
  }

  constexpr const char* ErrorType::error_source_str() const {
    return to_string(source_);
  }

  constexpr void ErrorType::set_message(const char* msg) {
    msg_ = msg;
  }

  constexpr const char* ErrorType::message() const {
    return msg_;
  }

  constexpr bool operator == (const ErrorType& lhs, const ErrorType& rhs) {
    return lhs.error_code() == rhs.error_code() &&
        lhs.error_source() == rhs.error_source() &&
        lhs.message() == rhs.message();
  }

  constexpr bool operator != (const ErrorType& lhs, const ErrorType& rhs) {
    return !(lhs == rhs);
  }

  /// @endinternal

} // namespace ti::util