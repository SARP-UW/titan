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
 * @file common/util/core/util_types.h 
 * @authors Aaron McBride 
 * @brief Contains various utility types.
 */

#pragma once

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Utility Type Declarations
   **************************************************************************************************/

  /**
   * @brief Denotes the type of a raw (un-typed) null pointer.
   */
  using nullptr_t = decltype(nullptr);

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

  /**
   * @brief Unit type which can only represent a single value.
   * @see www.wikipedia.org/wiki/Unit_type
   */
  struct monostate_t;

  /**
   * @brief Value of all monostate_t instances.
   * @see monostate_t
   */
  inline constexpr monostate_t monostate{};

  /**
   * @brief Equality comparison operator for monostate_t values. 
   * @return Always true (since all monostate_t instances represent the same value).
   */
  [[nodiscard]] constexpr bool operator == (monostate_t, monostate_t);

  /**
   * @brief Inequality comparison operator for monostate_t values.
   * @return Always false (since all monostate_t instances represent the same value).
   */
  [[nodiscard]] constexpr bool operator != (monostate_t, monostate_t);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename T> 
  struct in_place_type_t {
    constexpr explicit in_place_type_t() = default;
  };

  struct monostate_t {
    constexpr explicit monostate_t() = default;
  };

  constexpr bool operator == (monostate_t, monostate_t) { return true; }
  constexpr bool operator != (monostate_t, monostate_t) { return false; }

  /// @endinternal

} // namespace ti::util