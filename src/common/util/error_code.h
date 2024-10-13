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
 * @file common/util/error_code.h 
 * @authors Aaron McBride 
 * @brief Contains the 'ErrorCode' enum.
 * @note - Nothing in this header is from the C++ standard library.
 */

#pragma once

namespace ti::util {

  /**************************************************************************************************
   * @section Error Code Enum
   **************************************************************************************************/

  /**
   * @brief Enum class which denotes the cause of an error.
   * @note - This enum's underlying value is an int32_t, which ranges from 0 to 14.
   */
  enum class ErrorCode : int {
    none                = 0,  /** @brief No error occurred. */
    other               = 1,  /** @brief An error not representable by an ErrorCode value occurred. */
    unkown              = 2,  /** @brief An error with an unknown cause occurred. */
    invalid_arg         = 3,  /** @brief A request was made with parameters that cannot be interpreted. */
    timeout             = 4,  /** @brief An operation ran out of time. */
    not_found           = 5,  /** @brief An entity was requested which does not exist. */
    already_exists      = 6,  /** @brief An entity was requested that already exists. */
    invalid_perms       = 7,  /** @brief An operation/resource was requested with invalid permissions. */
    resource_exhausted  = 8,  /** @brief A required resource was exhausted. */
    failed_precondition = 9,  /** @brief A request was made with parameters that can be interpreted, but are not valid. */
    aborted             = 10, /** @brief An operation was aborted (usually due to conflict with annother operation). */
    out_of_range        = 11, /** @brief A numeric value was/became too large or small. */
    unimplemented       = 12, /** @brief An operation was requested that is not yet implemented. */
    internal            = 13, /** @brief An internal error has occurred. */
    unavailable         = 14, /** @brief A transient error occurred. */
  };

  /**
   * @brief Gets the string representation of the given ErrorCode value.
   * @param errc The target ErrorCode enum value.
   * @returns A c string that contains the name of @p 'errc'.
   */
  [[nodiscard]] constexpr const char* to_string(const ErrorCode errc);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  constexpr const char* to_string(const ErrorCode errc) {
    switch(errc) {
      case ErrorCode::none: { return "none"; }
      case ErrorCode::other: { return "other"; }
      case ErrorCode::unkown: { return "unkown"; }
      case ErrorCode::invalid_arg: { return "invalid argument"; }
      case ErrorCode::timeout: { return "timeout"; }
      case ErrorCode::not_found: { return "not found"; }
      case ErrorCode::already_exists: { return "resource already exists"; }
      case ErrorCode::invalid_perms: { return "invalid permissions"; }
      case ErrorCode::resource_exhausted: { return "resource exhausted"; }
      case ErrorCode::failed_precondition: { return "failed precondition"; }
      case ErrorCode::aborted: { return "operation aborted"; }
      case ErrorCode::out_of_range: { return "value out of range"; }
      case ErrorCode::unimplemented: { return "operation unimplemented"; }
      case ErrorCode::internal: { return "internal error"; }
      case ErrorCode::unavailable: { return "resource unavailable"; }
      default: { return "unknown error"; }
    }
  }

  /// @endinternal

} // namespace ti::util