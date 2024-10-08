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
 * @file common/util/error.h 
 * @authors Aaron McBride 
 * @brief Contains error code/source enums and related utilities.
 * @note - Nothing in this header is apart of the standard C++ library.
 */

#pragma once
#include "common/util/utility.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  #define TI_TO_STR_FUNC_(x) #x
  #define TI_TO_STR_(x) TI_TO_STR_FUNC_(x)

  /// @endinternal

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
   * @section String Conversion Utilities
   **************************************************************************************************/

  /**
   * @brief Creates an error message string that contains the file name, line 
   *        number and given message.
   * @param msg A string which contains the error message.
   * @note - The location embedded in the message is the location (in code)
   *       where this macro is invoked.
   * @note - The format of the generated error message is: "TITAN ERROR: File {<file>}, 
   *         Line {<line>}, Message {<msg>}"
   */
  #define TI_ERROR_MSG(msg) ("TITAN ERROR: File {"__FILE__ \
      "}, Line {" TI_TO_STR_(__LINE__) "}, Message {" msg "}")

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
   * @section Error Info Class Declaration
   **************************************************************************************************/

  /**
   * @brief Contains information about an error.
   */
  class ErrorInfo {

    public:

      /** @brief The default error code value. */
      static constexpr ErrorCode default_error_code{ErrorCode::unkown};

      /** @brief The default error source value. */
      static constexpr ErrorSource default_source{ErrorSource::unknown};

      /** @brief The default error message. */
      static constexpr const char* default_msg{nullptr};

      /**
       * @brief Initializes a new 'ErrorInfo' instance and with information about 
       *        it's associated error.
       * @param code An ErrorCode enum value which denotes the cause of the error.
       * @param source An ErrorSource enum value which denotes the source of the error.
       * @param msg A c-string which contains a message about the error.
       */
      constexpr explicit ErrorInfo(
          const ErrorCode code = default_error_code, 
          const ErrorSource source = default_source, 
          const char* msg = default_msg);

      /**
       * @brief Creates a copy of annother 'ErrorInfo' instance.
       * @param other The 'ErrorInfo' instance to copy.
       */
      constexpr ErrorInfo(const ErrorInfo& other);

      /**
       * @brief Sets this 'ErrorInfo' equal to annother.
       * @param other The 'ErrorInfo' instance to copy.
       * @returns A reference to this 'ErrorInfo' instance.
       */
      constexpr ErrorInfo& operator=(const ErrorInfo& other);

      /**
       * @brief Assigns a new error to this 'ErrorInfo' instance.
       * @param code An ErrorCode enum value which denotes the cause of the error.
       * @param source An ErrorSource enum value which denotes the source of the error.
       * @param msg A c-string which contains a message about the error.
       * @note - This method will overwrite all existing error information.
       */
      constexpr void assign(
          const ErrorCode code = default_error_code,
          const ErrorSource source = default_source,
          const char* msg = nullptr);

      /**
       * @brief Sets the error code enum value associated with this 
       *        'ErrorInfo' instance.
       * @param code The ErrorCode enum value to set.
       */
      constexpr void set_error_code(const ErrorCode code);

      /**
       * @brief Gets the error code associated with this 'ErrorInfo' instance.
       * @returns The assigned ErrorCode enum value.
       */
      [[nodiscard]] constexpr ErrorCode error_code() const;

      /**
       * @brief Gets the string representation of the error code 
       *        associated with this 'ErrorInfo' instance.
       * @returns A c-string which contains the error code string.
       */
      [[nodiscard]] constexpr const char* error_code_str() const;

      /**
       * @brief Sets the error source enum value associated with this 
       *        'ErrorInfo' instance.
       * @param source The ErrorSource enum value to set.
       */
      constexpr void set_error_source(const ErrorSource source);

      /**
       * @brief Gets the error source associated with this 'ErrorInfo' instance.
       * @returns The assigned ErrorSource enum value.
       */
      [[nodiscard]] constexpr ErrorSource error_source() const;

      /**
       * @brief Gets the string representation of the error source 
       *        associated with this 'ErrorInfo' instance.
       * @returns A c-string which contains the error source string.
       */
      [[nodiscard]] constexpr const char* error_source_str() const;

      /**
       * @brief Sets the message associated with this 'ErrorInfo' instance.
       * @param msg A c-string which constains the error message.
       */
      constexpr void set_message(const char* msg);

      /**
       * @brief Gets the message associated with this 'ErrorInfo' instance.
       * @returns A c-string which contains the error message.
       */
      [[nodiscard]] constexpr const char* message() const;

    private:

      ErrorCode code_{default_errc};
      ErrorSource source_{default_source};
      const char* msg_{default_msg};

  };

  /**
   * @brief Compares two 'ErrorInfo' instances for equality.
   * @param lhs The left-hand 'ErrorInfo' instance.
   * @param rhs The right-hand 'ErrorInfo' instance.
   * @returns True if the error associated with both instances is the same,
   *          or false otherwise (ErrorTypes must have the same error code, 
   *          source and message).
   */
  [[nodiscard]] constexpr bool operator == (const ErrorInfo& lhs, const ErrorInfo& rhs);

  /**
   * @brief Compares two 'ErrorInfo' instances for inequality.
   * @param lhs The left-hand 'ErrorInfo' instance.
   * @param rhs The right-hand 'ErrorInfo' instance.
   * @returns True if the error associated with @p 'lhs' is different from 
   *          the error associated with @p 'rhs', or false otherwise (ErrorTypes 
   *          are not equal if they have differing error codes, sources and/or 
   *          messages).
   */
  [[nodiscard]] constexpr bool operator != (const ErrorInfo& lhs, const ErrorInfo& rhs);

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

  constexpr ErrorInfo::ErrorInfo(const ErrorCode code, 
      const ErrorSource source, const char* msg) :
          code_{code}, source_{source}, msg_{msg} {}

  constexpr ErrorInfo::ErrorInfo(const ErrorInfo& other) :
      code_{other.code_}, source_{other.source_}, msg_{other.msg_} {}

  constexpr ErrorInfo& ErrorInfo::operator=(const ErrorInfo& other) {
    if (unlikely(this != &other)) {
      this->code_ = other.code_;
      this->source_ = other.source_;
      this->msg_ = other.msg_;
    }
    return *this;
  }

  constexpr void ErrorInfo::assign(const ErrorCode code, 
      const ErrorSource source, const char* msg) {
    code_ = code;
    source_ = source;
    msg_ = msg;
  }

  constexpr void ErrorInfo::set_error_code(const ErrorCode code) {
    code_ = code;
  }

  constexpr ErrorCode ErrorInfo::error_code() const {
    return code_;
  }

  constexpr const char* ErrorInfo::error_code_str() const {
    return to_string(code_);
  }

  constexpr void ErrorInfo::set_error_source(const ErrorSource source) {
    source_ = source;
  }

  constexpr ErrorSource ErrorInfo::error_source() const {
    return source_;
  }

  constexpr const char* ErrorInfo::error_source_str() const {
    return to_string(source_);
  }

  constexpr void ErrorInfo::set_message(const char* msg) {
    msg_ = msg;
  }

  constexpr const char* ErrorInfo::message() const {
    return msg_;
  }

  constexpr bool operator == (const ErrorInfo& lhs, const ErrorInfo& rhs) {
    return lhs.error_code() == rhs.error_code() &&
        lhs.error_source() == rhs.error_source() &&
        lhs.message() == rhs.message();
  }

  constexpr bool operator != (const ErrorInfo& lhs, const ErrorInfo& rhs) {
    return !(lhs == rhs);
  }

  /// @endinternal

} // namespace ti::util