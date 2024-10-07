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
 * @brief Contains sign-safe integer comparison utilities.
 */

#pragma once
#include "common/util/type_traits.h"
#include "common/tmp.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Comparison Utilities
   **************************************************************************************************/

  /**
   * @brief Safely determines if two integers of any type are equal.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is equal to @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_equal(const Tl l_value, const Tr r_value);

  /**
   * @brief Safely determines if one integer of any type is less than
   *        annother integer of any type.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is less then @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_less(const Tl l_value, const Tr r_value);
  
  /**
   * @brief Safely determines if one integer of any type is greater than
   *        annother integer of any type.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is greater then @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_greater(const Tl l_value, const Tr r_value);

  /**
   * @brief Safely determines if one integer of any type is less than
   *        or equal to annother integer of any type.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is less then or equal to @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_less_equal(const Tl l_value, const Tr r_value);

  /**
   * @brief Safely determines if one integer of any type is greater than
   *        or equal to annother integer of any type.
   * @tparam Tl The "left-hand" integral type.
   * @tparam Tr The "right-hand" integral type.
   * @param l_value The "left-hand" integral value.
   * @param r_value The "right-hand" integral value.
   * @returns True if @p 'l_value' is greater then or equal to @p 'r_value', 
   *          or false otherwise.
   * @note - The behavior of this function is defined regardless of the 
   *       signedness of @p 'Tl' and @p 'Tr'. 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool cmp_greater_equal(const Tl l_value, const Tr r_value);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename Tl, typename Tr>
  constexpr bool cmp_equal(const Tl l_value, const Tr r_value) {
    using PromType = promoted_type_t<Tl, Tr>;

    if constexpr (is_integer_v<Tl> && is_integer_v<Tr> && is_unsigned_v<PromType>) {
      if constexpr (is_signed_v<Tl> && is_unsigned_v<Tr>) {
        using UnsignedType = make_unsigned_t<Tl>;
        return l_value >= Tl{0} && static_cast<UnsignedType>(l_value) == r_value;
      } 
      if constexpr (is_unsigned_v<Tl> && is_signed_v<Tr>) {
        using UnsignedType = make_unsigned_t<Tr>;
        return r_value >= Tr{0} && l_value == static_cast<UnsignedType>(r_value);
      }
    }
    return l_value == r_value;
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_less(const Tl l_value, const Tr r_value) {
    using PromType = promoted_type_t<Tl, Tr>;
    
    if constexpr (is_integer_v<Tl> && is_integer_v<Tr> && is_unsigned_v<PromType>) {
      if constexpr (is_signed_v<Tl> && is_unsigned_v<Tr>) {
        using UnsignedType = make_unsigned_t<Tl>;
        return l_value < Tl{0} || static_cast<UnsignedType>(l_value) < r_value;
      } 
      if constexpr (is_unsigned_v<Tl> && is_signed_v<Tr>) {
        using UnsignedType = make_unsigned_t<Tr>;
        return r_value >= Tr{0} && l_value < static_cast<UnsignedType>(r_value);
      }
    }
    return l_value < r_value;
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_greater(const Tl l_value, const Tr r_value) {
    return cmp_less(r_value, l_value);
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_less_equal(const Tl l_value, const Tr r_value) {
    return !cmp_less(r_value, l_value);
  }

  template<typename Tl, typename Tr>
  constexpr bool cmp_greater_equal(const Tl l_value, const Tr r_value) {
    return !cmp_less(l_value, r_value);
  }

  /// @endinternal

} // namespace ti::util