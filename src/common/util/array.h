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
 * @file common/util/array.h 
 * @authors Aaron McBride 
 * @brief Contains array utilities.
 */

#pragma once
#include "common/util/cstdint.h"

namespace ti::util {
    
  /**************************************************************************************************
   * @section Array Query Utilities
   **************************************************************************************************/

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr int index_of(T&& query, const U(&array)[N]);

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr int index_of(T&& query, const size_t n, const U(&array)[N]);

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr int last_index_of(T&& query, const U(&array)[N]);

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr int last_index_of(T&& query, const size_t n, const U(&array)[N]);

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr bool is_contained(T&& query, const U(&array)[N]);

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr bool is_contained(T&& query, const size_t count, const U(&array)[N]);

  template<typename T, size_t N1, typename U, size_t N2>
  [[nodiscard]] constexpr bool is_equal(const T(&array_a)[N1], const U(&array_b)[N2]);

  /**************************************************************************************************
   * @section Array Transformation Utilities
   **************************************************************************************************/

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr auto fill(T&& value, const U(&array)[N]);

  template<typename T, size_t N>
  [[nodiscard]] constexpr auto extract(const size_t start, const size_t end, const T(&array)[N]);

  template<typename T, size_t N1, typename U, size_t N2>
  [[nodiscard]] constexpr auto join(const T(&array_a)[N1], const U(&array_b)[N2]);

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr auto join(T&& value, const U(&array)[N]);

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr auto join(const U(&array)[N], T&& value);

  template<typename T, size_t N1, typename U, size_t N2>
  [[nodiscard]] constexpr auto insert(const T(&array_a)[N1], const size_t index, const U(&array_b)[N2]);

  template<typename T, typename U, size_t N>
  [[nodiscard]] constexpr auto insert(T&& value, const size_t index, const U(&array)[N]);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  /// @endinternal

} // namespace ti::util
