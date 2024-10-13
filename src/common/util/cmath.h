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
 * @file common/util/math.h 
 * @authors Aaron McBride 
 * @brief Contains common math functions.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"
#include "common/util/type_traits.h"
#include "common/util/error_code.h"
#include "common/util/result.h"
#include "common/util/utility.h"
#include "misc.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Math Utilities
   **************************************************************************************************/

  template<typename T>
  [[nodiscard]] constexpr Result<T, ErrorCode> abs(const T value);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto min(const T l_value, const U r_value);

  template<typename T, size_t N>
  [[nodiscard]] constexpr T min(const T (&values)[N]);

  template<typename... T>
  [[nodiscard]] constexpr auto max(const T... values);

  template<typename... T>
  [[nodiscard]] constexpr auto mean(const T... values);

  template<typename... T>
  [[nodiscard]] constexpr auto median(const T... values);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto div_ceil(const T num, const U den);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto gcd(const T value_a, const U value_b);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto lcm(const T value_a, const U value_b);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto round_to(const T value, const U mul);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto ceil_to(const T value, const U mul);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto floor_to(const T value, const U mul);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto log_floor(const T base, const U value);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto log_ceil(const T base, const U value);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto pow(const T base, const U exp);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto wrap(const T value, const U mod);

  /**************************************************************************************************
   * @internal Non-Standard Math Utilities
   **************************************************************************************************/

  namespace {

  }

  template<typename T>
  [[nodiscard]] constexpr Result<T, ErrorCode> abs(const T value) {
    constexpr int32_t t_digits{numeric_limits<T>::digits};
    if constexpr (is_signed_v<T>) {
      constexpr int32_t p_digits{numeric_limits<common_type_t<T>>::digits};
      if constexpr (TI_TWO_COMPLEMENT && t_digits >= p_digits) {
        if (value <= numeric_limits<T>::lowest()) {
          return Error{ErrorCode::out_of_range};
        }
      } else if constexpr (TI_ONE_COMPLEMENT && t_digits >= p_digits) {
        if (value >= numeric_limits<T>::max()) {
          return Error{ErrorCode::out_of_range};
        }
      }
    } else if (value == 0) {
      return Error{ErrorCode::out_of_range};
    }
    return Valid{value < 0 ? -value : value};
  }

  template<typename T, size_t N>
  [[nodiscard]] constexpr auto min(const T (&values)[N]) {
    size_t min_idx{0};
    for (size_t i = 0; i < N; ++i) {
      if (values[i] < values[min_idx]) {
        min_idx = i;
      }
    }
    return min_idx;
  }

  template<typename... T>
  [[nodiscard]] constexpr auto max(const T... values);

  template<typename... T>
  [[nodiscard]] constexpr auto mean(const T... values);

  template<typename... T>
  [[nodiscard]] constexpr auto median(const T... values);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto div_ceil(const T num, const U den);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto gcd(const T value_a, const U value_b);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto lcm(const T value_a, const U value_b);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto round_to(const T value, const U mul);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto ceil_to(const T value, const U mul);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto floor_to(const T value, const U mul);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto log_floor(const T base, const U value);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto log_ceil(const T base, const U value);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto pow(const T base, const U exp);

  template<typename T, typename U>
  [[nodiscard]] constexpr auto wrap(const T value, const U mod);

  /// @endinternal

} // ti::util