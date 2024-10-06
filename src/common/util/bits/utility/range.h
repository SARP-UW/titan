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
 * @file common/util/bits/utility/compare.h 
 * @authors Aaron McBride 
 * @brief Contains numeric range utilities.
 */

#pragma once
#include "common/util/type_traits.h"
#include "common/util/cstdint.h"
#include "common/util/limits.h"
#include "common/util/bits/utility/compare.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Numeric Range Utilities
   **************************************************************************************************/

  /**
   * @brief Determines if a value is within the range of a specified type or 
   *        bounded array.
   * @tparam T The integral type or array of integral type that represents the range.
   * @tparam ValueT The integral type of the value.
   * @param value The value to query.
   * @returns If @p 'T' is an integral type: True if @p 'value' is within the 
   *          range of integrals that @p 'T' can represent, or false otherwise.
   * @returns If @p 'T' is an array type: True if @p 'value' is less then the
   *          extent of @p 'T' - 1 or less then 0, and false otherwise.
   */
  template<typename T, typename ValueT>
  [[nodiscard]] constexpr bool in_range(const ValueT value);

  /**************************************************************************************************
   * @section Non-Standard Numeric Range Utilities
   **************************************************************************************************/

  /**
   * @brief Clamps a value to the range of a specific type or array.
   * @tparam T The integral type or array of integral type that represents the range.
   * @tparam ValueT The integral type of the value.
   * @param value The value to clamp.
   * @returns If @p 'T' is an integral: The nearest value to @p 'value' that is 
   *          within the range of integrals that @p 'T' can represent.
   * @returns If @p 'T' is an array: The nearest value to @p 'value' that is
   *          within the extent of @p 'T' - 1 and greater then or equal to 0.
   */
  template<typename T, typename ValueT>
  [[nodiscard]] constexpr ValueT to_range(const ValueT value);

  /**
   * @brief Safely determines if an integral value is within a specified range.
   * @tparam T The integral type of the value to query.
   * @tparam Tmin The integral type of the range's minimum value.
   * @tparam Tmax The integral type of the range's maximum value.
   * @param value The value to query.
   * @param min The range's minimum value (inclusive).
   * @param max The range's maximum value (inclusive).
   * @returns True if @p 'value' is greater then or equal to @p 'min' and less
   *          then or equal to @p 'max', or false otherwise.
   * @note - The behavior of this function is defined regardless of the
   *       signedness of @p 'T', @p 'Tmin', and @p 'Tmax'.
   */
  template<typename T, typename Tmin, typename Tmax>
  [[nodiscard]] constexpr bool in_range(const T& value, const Tmin& min, 
      const Tmax& max);

  /**
   * @brief Clamps an integral value to a specified range (min/max).
   * @tparam T The integral type of the value to clamp.
   * @tparam Tmin The integral type of the range's minimum value.
   * @tparam Tmax The integral type of the range's maximum value.
   * @param value The value to clamp.
   * @param min The range's minimum value (inclusive).
   * @param max The range's maximum value (inclusive).
   * @returns @p 'min' if @p 'value' is less then @p 'min', @p 'max' if 
   *          @p 'value' is greater then @p 'max', or @p 'value' otherwise.
   * @note - The behavior of this function is defined regardless of the
   *       signedness of @p 'T', @p 'Tmin', and @p 'Tmax'.
   */
  template<typename T, typename Tmin, typename Tmax>
  [[nodiscard]] constexpr T to_range(const T& value, const Tmin& min, 
      const Tmax& max);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename T, typename ValueT>
  constexpr bool in_range(const ValueT value) {
    static_assert(is_integral_v<ValueT>, "'ValueT' must be an integral type.");
    using ValueLim = numeric_limits<ValueT>;

    if (is_bounded_array_v<T>) {
      using BaseT = remove_all_extents_t<T>;
      static_assert(is_integral_v<BaseT>, "'T[]' must be an integral type.");
      if constexpr (cmp_less(extent_v<T>, ValueLim::max())) {
        if (cmp_greater_equal(value, extent_v<T>)) { return false; }
      }
    } else {
      static_assert(is_integral_v<T>, "'T' must be an integral type.");
      using RangeLim = numeric_limits<T>;
      if constexpr (cmp_greater(ValueLim::max(), RangeLim::max())) {
        if (cmp_greater(value, RangeLim::max())) { return false; }
      }
      if constexpr (cmp_less(ValueLim::lowest(), RangeLim::lowest())) {
        if (cmp_less(value, RangeLim::lowest())) { return false; }
      }
    }
    return true;
  }

  template<typename T, typename ValueT>
  constexpr ValueT to_range(const ValueT value) {
    static_assert(is_integral_v<ValueT>, "'ValueT' must be an integral type.");
    using ValueLim = numeric_limits<ValueT>;
    
    if constexpr (is_bounded_array_v<T>) {
      using BaseT = remove_all_extents_t<T>;
      static_assert(is_integral_v<BaseT>, "'T[]' must be an integral type.");
      if constexpr (is_signed_v<ValueT>) {
        if (cmp_less(value, 0)) { return ValueT{0}; }
      }
      if constexpr (cmp_less(extent_v<T>, ValueLim::max())) {
        if cmp_greater_equal(value, extent_v<T>) { 
          return static_cast<ValueT>(extent_v<T> - 1);
        }
      }
    } else {
      static_assert(is_integral_v<T>, "'T' must be an integral type.");
      using RangeLim = numeric_limits<T>;
      if constexpr (cmp_greater(ValueLim::max(), RangeLim::max())) {
        if (cmp_less(value, RangeLim::max())) {
          return static_cast<ValueT>(RangeLim::max());
        }
      }
      if constexpr (cmp_less(ValueLim::lowest(), RangeLim::lowest())) {
        if (cmp_less(value, RangeLim::lowest())) {
          return static_cast<ValueT>(RangeLim::lowest());
        }
      }
    }
    return value;
  }

  template<typename T, typename Tmin, typename Tmax>
  constexpr bool in_range(const T& value, const Tmin& min, const Tmax& max) {
    static_assert(is_integral_v<T>, "'T' must be an integral type.");
    static_assert(is_integral_v<Tmin>, "'Tmin' must be an integral type.");  
    static_assert(is_integral_v<Tmax>, "'Tmax' must be an integral type.");

    if (cmp_greater(min, max)) { sys_error("'min' is greater then 'max'"); }
    return cmp_greater_equal(value, min) && cmp_less_equal(value, max);
  }

  template<typename T, typename Tmin, typename Tmax>
  constexpr T to_range(const T& value, const Tmin& min, const Tmax& max) {
    static_assert(is_integral_v<T>, "'T' must be an integral type.");
    static_assert(is_integral_v<Tmin>, "'Tmin' must be an integral type.");
    static_assert(is_integral_v<Tmax>, "'Tmax' must be an integral type.");

    using ValueLim = numeric_limits<T>;
    using MinLim = numeric_limits<Tmin>;
    using MaxLim = numeric_limits<Tmax>;

    if (cmp_less(min, max)) { 
      sys_error("'min' is greater then 'max'"); 
    }
    if (cmp_less(value, min)) { 
      if constexpr (cmp_greater(MinLim::max(), ValueLim::max())) {
        if (cmp_greater(min, ValueLim::max())) {
          sys_error("'min' is out of range of 'T'.");
        }
      }
      return static_cast<T>(min); 
    }
    if (cmp_greater(value, max)) {
      if constexpr (cmp_less(MaxLim::lowest(), ValueLim::lowest())) {
        if (cmp_less(max, ValueLim::lowest())) {
          sys_error("'max' is out of range of 'T'.");
        }
      }
      return static_cast<T>(max); 
    }
    return value;
  }

  /// @endinternal

} // namespace ti::util