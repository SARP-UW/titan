/**
 * This file is part of the Titan Flight Computer Project.
 * Copyright (c) 2024 SARP.
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
 * @file common/util/overflow.h 
 * @authors Aaron McBride 
 * @brief Contains overflow detection utilities.
 * @note - Nothing in this header is from the C++ standard library.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"
#include "common/util/utility.h"
#include "common/util/limits.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Overflow Detection Utilities
   **************************************************************************************************/ 

  /**
   * @brief Determines if addition between two values is well defined.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if the sum of @p 'l_value' and @p 'r_value' is 
   *          within the range of their promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_add(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if addition between two values is well defined and
   *        if the result can be losslessly assigned/cast to a specific type.
   * @tparam T The type to assign/cast the result to.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if the sum of @p 'l_value' and @p 'r_value' is 
   *          within the range of their promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_add(const Tl l_value,  const Tr r_value);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr auto sat_add(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr T sat_add(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<common_type_t<Tl, Tr>, ErrorCode> try_add(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<T, ErrorCode> try_add(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if subtraction between two values is well defined.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if the difference of @p 'l_value' and @p 'r_value is 
   *          within the range of their promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_sub(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if subtraction between two values is well defined and
   *        if the result can be losslessly assigned/cast to a specific type.
   * @tparam T The type to assign/cast the result to.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if the difference of @p 'l_value' and @p 'r_value is 
   *          within the range of their promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_sub(const Tl l_value, const Tr r_value);
  
  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @param sat_flag 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr auto sat_sub(const Tl l_value, const Tr r_value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @param sat_flag 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr T sat_sub(const Tl l_value, const Tr r_value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<common_type_t<Tl, Tr>, ErrorCode> try_sub(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<T, ErrorCode> try_sub(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if multiplication between two values is well defined.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if the product of @p 'l_value' and @p 'r_value' is
   *          within the range of their promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_mul(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if multiplication between two values is well defined
   *        and if the result can be losslessly assigned/cast to a specific type.
   * @tparam T The type to assign/cast the result to.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if the product of @p 'l_value' and @p 'r_value' is
   *          within the range of their promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_mul(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @param sat_flag 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr auto sat_mul(const Tl l_value, const Tr r_value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @param sat_flag 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr T sat_mul(const Tl l_value, const Tr r_value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @param sat_flag 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<common_type_t<Tl, Tr>, ErrorCode> try_mul(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @param sat_flag 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<T, ErrorCode> try_mul(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if division between two values is well defined.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if @p 'r_value' does not equal 0 and the quotient of
   *          @p 'l_value' and @p 'r_value' is within the range of their 
   *          promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_div(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if division between two values is well defined
   *        and if the result can be losslessly assigned/cast to a specific type.
   * @tparam T The type to assign/cast the result to.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if @p 'r_value' does not equal 0 and the quotient of
   *          @p 'l_value' and @p 'r_value' is within the range of their 
   *          promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_div(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<common_type_t<Tl, Tr>, ErrorCode> try_div(const Tl l_value, const Tr r_value);
  
  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<T, ErrorCode> try_div(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if modulo between two values is well defined.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if @p 'r_value' does not equal 0 and the modulus of
   *          @p 'l_value' and @p 'r_value' is within the range of their 
   *          promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_mod(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if modulo between two values is well defined
   *        and if the result can be losslessly assigned/cast to a specific type.
   * @tparam T The type to assign/cast the result to.
   * @tparam Tl The integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if @p 'r_value' does not equal 0 and the modulus of
   *          @p 'l_value' and @p 'r_value' is within the range of their 
   *          promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_mod(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<common_type_t<Tl, Tr>, ErrorCode> try_mod(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<T, ErrorCode> try_mod(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if a left bit-shift operation between 
   *        two values is well defined.
   * @tparam Tl The unsigned integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if shifting @p 'l_value' left by @p 'r_value' bits results
   *          in a value that is within the range of their promoted type, or
   *          false otherwise (also false if @p 'r_value' is negative).
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_lshift(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if a left bit-shift operation between 
   *        two values is well defined and if the result can be losslessly
   *        assigned/cast to a specific type.
   * @tparam T The type to assign/cast the result to.
   * @tparam Tl The unsigned integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if shifting @p 'l_value' left by @p 'r_value' bits results
   *          in a value that is within the range of their promoted type, or
   *          false otherwise (also false if @p 'r_value' is negative).
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_lshift(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr auto sat_lshift(const Tl l_value, const Tr r_value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr T sat_lshift(const Tl l_value, const Tr r_value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<common_type_t<Tl>, ErrorCode> try_lshift(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<T, ErrorCode> try_lshift(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if a right bit-shift operation between 
   *        two values is well defined.
   * @tparam Tl The unsigned integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if shifting @p 'l_value' right by @p 'r_value' bits results
   *          in a value that is within the range of their promoted type, or
   *          false otherwise (also false if @p 'r_value' is negative).
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_rshift(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if a right bit-shift operation between 
   *        two values is well defined and if the result can be losslessly
   *        assigned/cast to a specific type.
   * @tparam T The type to assign/cast the result to.
   * @tparam Tl The unsigned integral type of the "left" value.
   * @tparam Tr The integral type of the "right" value.
   * @param l_value The value on the left side of the operation.
   * @param r_value The value on the right side of the operation.
   * @returns True if shifting @p 'l_value' right by @p 'r_value' bits results
   *          in a value that is within the range of their promoted type, or
   *          false otherwise (also false if @p 'r_value' is negative).
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr bool can_rshift(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @param sat_flag 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr auto sat_rshift(const Tl l_value, const Tr r_value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @param sat_flag 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr T sat_rshift(const Tl l_value, const Tr r_value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<common_type_t<Tl>, ErrorCode> try_rshift(const Tl l_value, const Tr r_value);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam Tl 
   * @tparam Tr 
   * @param l_value 
   * @param r_value 
   * @return 
   */
  template<typename T, typename Tl, typename Tr>
  [[nodiscard]] constexpr Result<T, ErrorCode> try_rshift(const Tl l_value, const Tr r_value);

  /**
   * @brief Determines if the negation of a value is well defined.
   * @tparam T The integral type of the negated value.
   * @param value The negated value.
   * @returns True if negating @p 'value' results in a value that is within
   *          the range of it's promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T>
  [[nodiscard]] constexpr bool can_negate(const T value);

  /**
   * @brief Determines if the negation of a value is well defined and the
   *        if result can be losslessly assigned/cast to a specific type.
   * @tparam T The integral type of the negated value.
   * @param value The negated value.
   * @returns True if negating @p 'value' results in a value that is within
   *          the range of it's promoted type, or false otherwise.
   * @note - This function's behavior is defined regardless of the signedness 
   *       of @p 'l_value' and @p 'r_value'.
   */
  template<typename T, typename U>
  [[nodiscard]] constexpr bool can_negate(const U value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @param sat_flag 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr auto sat_negate(const T value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam U 
   * @param value 
   * @param sat_flag 
   * @return 
   */
  template<typename T, typename U>
  [[nodiscard]] constexpr T sat_negate(const U value, bool* sat_flag = nullptr);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr Result<common_type_t<T>, ErrorCode> try_negate(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @tparam U 
   * @param value 
   * @return 
   */
  template<typename T, typename U>
  [[nodiscard]] constexpr Result<T, ErrorCode> can_negate(const U value);

  /**************************************************************************************************
   * @internal Standard Math Utilities
   **************************************************************************************************/

  namespace {

    // Minimum number of digits in the promoted type of any expression.
    constexpr int min_prom_digits{numeric_limits<int32_t>::digits};
    
    // Gets the absolute value of a signed int and prevents overflows by 
    // casting the result to the equivalent unsigned type.
    template<typename T>
    constexpr auto safe_abs(const T value) {
      using UnsignedType = make_unsigned_t<T>;
      using ValueLim = numeric_limits<T>;
      #if TI_TWO_COMPLEMENT
        if (value == ValueLim::lowest()) {
          return static_cast<UnsignedType>(ValueLim::max()) + 1;
        }
      #endif
      return static_cast<UnsignedType>(value < 0 ? -value : value);
    }

    constexpr bool set_sat_flag(bool*& sat_flag) {
      if (sat_flag != nullptr) { *sat_flag = true; }
    }

  } // namespace annonymous

  template<typename Tl, typename Tr>
  constexpr bool can_add(const Tl l_value, const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

    if constexpr (TI_HAS_BUILTIN_ADD_OVF && 
        is_integer_v<Tl> && is_integer_v<Tr>) {
      return TI_BUILTIN_ADD_OVF(Tl, Tr, l_value, r_value);
    } else {
      using Rlim = numeric_limits<Tr>;
      using Llim = numeric_limits<Tl>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;

      if constexpr (Llim::digits >= min_prom_digits || 
          Rlim::digits >= min_prom_digits) {
        if constexpr (is_signed_v<Tl> && is_signed_v<Tr>) {
          if (l_value < 0 && r_value < 0) {
            return l_value >= (PromLim::lowest() - r_value);
          } else if (l_value > 0 && r_value > 0) {
            return l_value <= (PromLim::max() - r_value);
          } else {
            return true;
          }
        } else if constexpr (is_signed_v<Tl>) {
          if constexpr (is_signed_v<PromType>) {
            return l_value <= (Llim::max() - r_value);
          } else if (l_value < 0) {
            return r_value >= safe_abs(l_value);
          } else {
            return static_cast<Tr>(l_value) <= (Rlim::max() - r_value);
          }
        } else if constexpr (is_signed_v<Tr>) {
          return can_add<Tr, Tl>(r_value, l_value);
        } else {
          return l_value <= PromLim::max() - r_value;
        }
      } else {
        return true;
      }
    }
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool can_add(const Tl l_value,  const Tr r_value) {
    return can_add<Tl, Tr>(l_value, r_value) && in_range<T>(l_value + r_value);
  }

  template<typename Tl, typename Tr>
  constexpr auto sat_add(const Tl l_value, const Tr r_value, bool* sat_flag) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

      using Rlim = numeric_limits<Tr>;
      using Llim = numeric_limits<Tl>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;

    if constexpr (Llim::digits >= min_prom_digits || 
        Rlim::digits >= min_prom_digits) {
      if constexpr (is_signed_v<Tl> && is_signed_v<Tr>) {
        if (l_value < 0 && r_value < 0) {
          if (l_value < (PromLim::lowest() - r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::lowest();
          }
        } else if (l_value > 0 && r_value > 0 && 
            l_value > (PromLim::max() - r_value)) {
          set_sat_flag(sat_flag);
          return PromLim::max();
        }
      } else if constexpr (is_signed_v<Tl>) {
        if constexpr (is_signed_v<PromType>) {
          if (l_value > (Llim::max() - r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::max();
          }
        } else if (l_value < 0) {
          if (r_value < safe_abs(l_value))  {
            set_sat_flag(sat_flag);
            return PromLim::lowest();
          }
        } else if (static_cast<Tr>(l_value) > (PromLim::max() - r_value)) {
          set_sat_flag(sat_flag);
          return PromLim::max();
        }
      } else if constexpr (is_signed_v<Tr>) {
        return sat_add<Tr, Tl>(r_value, l_value, sat_flag);
      } else if (l_value > (PromLim::max() - r_value)) {
        set_sat_flag(sat_flag);
        return PromLim::max();
      }
    }
    return l_value + r_value;
  }

  template<typename T, typename Tl, typename Tr>
  constexpr T sat_add(const Tl l_value,  const Tr r_value, bool* sat_flag) {
    return to_range<T>(sat_add<Tl, Tr>(l_value, r_value, sat_flag), sat_flag);
  }

  template<typename Tl, typename Tr>
  constexpr Result<common_type_t<Tl, Tr>, ErrorCode> 
      try_add(const Tl l_value,  const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

      using Rlim = numeric_limits<Tr>;
      using Llim = numeric_limits<Tl>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;

    if constexpr (Llim::digits >= min_prom_digits || 
        Rlim::digits >= min_prom_digits) {
      if constexpr (is_signed_v<Tl> && is_signed_v<Tr>) {
        if (l_value < 0 && r_value < 0) {
          if (l_value < (PromLim::lowest() - r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (l_value > 0 && r_value > 0 &&
            l_value > (PromLim::max() - r_value)) {
          return Error{ErrorCode::out_of_range};
        }
      } else if constexpr (is_signed_v<Tl>) {
        if constexpr (is_signed_v<PromType>) {
          if (l_value > (Llim::max() - r_value)) {
            Error{ErrorCode::out_of_range};
          }
        } else if (l_value < 0) {
          if (r_value < safe_abs(l_value))  {
            return Error{ErrorCode::out_of_range};
          }
        } else if (static_cast<Tr>(l_value) > (PromLim::max() - r_value)) {
          return Error{ErrorCode::out_of_range};
        }
      } else if constexpr (is_signed_v<Tr>) {
        return try_add<Tr, Tl>(r_value, l_value, sat_flag);
      } else if (l_value > (PromLim::max() - r_value)) {
        return Error{ErrorCode::out_of_range};
      }
    }
    return Valid{l_value + r_value};
  }

  template<typename T, typename Tl, typename Tr>
  constexpr Result<T, ErrorCode> try_add(const Tl l_value,  const Tr r_value) {
    return try_add<Tl, Tr>(l_value, r_value).map_valid([](auto&& value) {
      return numeric_cast<T>(value);
    });
  }

  template<typename Tl, typename Tr>
  constexpr bool can_sub(const Tl l_value, const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

    if constexpr (TI_HAS_BUILTIN_SUB_OVF && 
        is_integer_v<Tl> && is_integer_v<Tr>) {
      return TI_BUILTIN_SUB_OVF(Tl, Tr, l_value, r_value);
    } else {
      using Llim = numeric_limits<Tl>;
      using Rlim = numeric_limits<Tr>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;

      if constexpr (Llim::digits >= min_prom_digits ||
          Rlim::digits >= min_prom_digits) {
        if constexpr (is_signed_v<Tl> && is_signed_v<Tr>) {
          if (l_value >= 0 && r_value < 0) {
            return l_value <= (PromLim::max() + r_value);
          } else if (l_value < 0 && r_value > 0) {
            return l_value >= (PromLim::lowest() + r_value);
          } else {
            return true;
          }
        } else if constexpr (is_signed_v<Tl>) {
          if constexpr (is_signed_v<PromType>) {
            return l_value >= (Llim::lowest() + r_value);
          } else if (l_value >= 0) {
            return static_cast<Tr>(l_value) >= r_value;
          } else {
            return false;
          }
        } else if constexpr (is_signed_v<Tr>) {
          if constexpr (is_signed_v<PromType>) {
            return r_value >= 0 || l_value <= (Rlim::max() + r_value);
          } else if (r_value > 0) {
            return l_value >= safe_abs(r_value);
          } else {
            return l_value <= (Llim::max() + static_cast<Tl>(r_value));
          }
        } else { 
          return l_value >= r_value;
        }
      } else {
        return true;
      }
    }
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool can_sub(const Tl l_value, const Tr r_value) {
    return can_sub<Tl, Tr>(l_value, r_value) && in_range<T>(l_value - r_value);
  }

  template<typename Tl, typename Tr>
  constexpr bool sat_sub(const Tl l_value, const Tr r_value, bool* sat_flag) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

      using Llim = numeric_limits<Tl>;
      using Rlim = numeric_limits<Tr>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;

    if constexpr (Llim::digits >= min_prom_digits ||
        Rlim::digits >= min_prom_digits) {
      if constexpr (is_signed_v<Tl> && is_signed_v<Tr>) {
        if (l_value >= 0 && r_value < 0) {
          if (l_value > (PromLim::max() + r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::max();
          }
        } else if (l_value < 0 && r_value > 0 && 
            l_value < (PromLim::lowest() + r_value)) {
          set_sat_flag(sat_flag);
          return PromLim::lowest();
        }
      } else if constexpr (is_signed_v<Tl>) {
        if constexpr (is_signed_v<PromType>) {
          if (l_value < (PromLim::lowest() + r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::lowest();
          }
        } else if (l_value >= 0) {
          if (static_cast<Tr>(l_value) < r_value) {
            set_sat_flag(sat_flag);
            return PromLim::lowest();
          }
        } else {
          set_sat_flag(sat_flag);
          return PromType{0};
        }
      } else if constexpr (is_signed_v<Tr>) {
        if constexpr (is_signed_v<PromType>) {
          if (r_value < 0 && l_value > (PromLim::max() + r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::max();
          }
        } else if (r_value > 0) {
          if (l_value < safe_abs(r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::lowest();
          }
        } else if (l_value > (PromLim::max() + static_cast<Tl>(r_value))) {
          set_sat_flag(sat_flag);
          return PromLim::max();
        }
      } else if (l_value < r_value) {
        set_sat_flag(sat_flag);
        return PromType{0};
      }
    }
    return l_value - r_value;
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool sat_sub(const Tl l_value, const Tr r_value, bool* sat_flag) {
    return to_range<T>(sat_sub<Tl, Tr>(l_value, r_value, sat_flag), sat_flag);
  }

  template<typename Tl, typename Tr>
  constexpr Result<common_type_t<Tl, Tr>, ErrorCode> 
      try_sub(const Tl l_value, const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

      using Llim = numeric_limits<Tl>;
      using Rlim = numeric_limits<Tr>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;

    if constexpr (Llim::digits >= min_prom_digits ||
        Rlim::digits >= min_prom_digits) {
      if constexpr (is_signed_v<Tl> && is_signed_v<Tr>) {
        if (l_value >= 0 && r_value < 0) {
          if (l_value > (PromLim::max() + r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (l_value < 0 && r_value > 0 && 
            l_value < (PromLim::lowest() + r_value)) {
          return Error{ErrorCode::out_of_range};
        }
      } else if constexpr (is_signed_v<Tl>) {
        if constexpr (is_signed_v<PromType>) {
          if (l_value < (PromLim::lowest() + r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (l_value >= 0) {
          if (static_cast<Tr>(l_value) < r_value) {
            return Error{ErrorCode::out_of_range};
          }
        } else {
          return Error{ErrorCode::out_of_range};
        }
      } else if constexpr (is_signed_v<Tr>) {
        if constexpr (is_signed_v<PromType>) {
          if (r_value < 0 && l_value > (PromLim::max() + r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (r_value > 0) {
          if (l_value < safe_abs(r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (l_value > (PromLim::max() + static_cast<Tl>(r_value))) {
          return Error{ErrorCode::out_of_range};
        }
      } else if (l_value < r_value) {
        return Error{ErrorCode::out_of_range};
      }
    }
    return Valid{l_value - r_value};
  }

  template<typename T, typename Tl, typename Tr>
  constexpr Result<T, ErrorCode> try_sub(const Tl l_value, const Tr r_value) {
    return try_sub<Tl, Tr>(l_value, r_value).map_valid([](auto&& valid) {
      return numeric_cast<T>(valid);
    });
  }

  template<typename Tl, typename Tr>
  constexpr bool can_mul(const Tl l_value, const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

    if constexpr (TI_HAS_BUILTIN_MUL_OVF && 
        is_integer_v<Tl> && is_integer_v<Tr>) {
      return TI_BUILTIN_MUL_OVF(Tl, Tr, l_value, r_value);
    } else {
      using Llim = numeric_limits<Tl>;
      using Rlim = numeric_limits<Tr>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;
      constexpr int mul_min_prom_digits{(min_prom_digits / 2) + 1};

      if constexpr (Llim::digits > mul_min_prom_digits ||
          Rlim::digits > mul_min_prom_digits) {
        if constexpr (is_signed_v<Tl> && is_signed_v<Tl>) {
          if (l_value < 0 && r_value < 0) {
            return l_value >= PromLim::max() / r_value;
          } else if (l_value < 0 && r_value > 0) {
            return l_value >= PromLim::lowest() / r_value;
          } else if (l_value > 0 && r_value < 0) {
            return r_value >= PromLim::lowest() / l_value;
          } else if (l_value > 0 && r_value > 0) {
            return l_value <= PromLim::max() / r_value;
          } else {
            return true;
          }
        } else if constexpr (is_signed_v<Tl>) {
          if (l_value > 0 && r_value != 0) {
            return l_value <= PromLim::max() / r_value;
          } else if (l_value < 0 && r_value != 0) {
            if constexpr (is_signed_v<PromType>) {
              return l_value >= PromLim::lowest() / r_value;
            } else {
              return false;
            }
          } else {
            return true;
          }
        } else if constexpr (is_signed_v<Tr>) {
          return can_mul<Tr, Tl>(r_value, l_value);
        } else {
          return l_value <= PromLim::max() / r_value;
        }
      } else {
        return true;
      }
    }
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool can_mul(const Tl l_value, const Tr r_value) {
    return can_mul<Tl, Tr>(l_value, r_value) && in_range<T>(l_value * r_value);
  }

  template<typename Tl, typename Tr>
  constexpr bool sat_mul(const Tl l_value, const Tr r_value, bool* sat_flag) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

      using Llim = numeric_limits<Tl>;
      using Rlim = numeric_limits<Tr>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;
      constexpr int mul_min_prom_digits{(min_prom_digits / 2) + 1};

    if constexpr (Llim::digits > mul_min_prom_digits ||
        Rlim::digits > mul_min_prom_digits) {
      if constexpr (is_signed_v<Tl> && is_signed_v<Tl>) {
        if (l_value < 0 && r_value < 0) {
          if (l_value < (PromLim::max() / r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::max();
          }
        } else if (l_value < 0 && r_value > 0) {
          if (l_value < (PromLim::lowest() / r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::lowest();
          }
        } else if (l_value > 0 && r_value < 0) {
          if (r_value < (PromLim::lowest() / l_value)) {
            set_sat_flag(sat_flag);
            return PromLim::lowest();
          }
        } else if (l_value > 0 && r_value > 0) {
          if (l_value > (PromLim::max() / r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::max();
          }
        }
      } else if constexpr (is_signed_v<Tl>) {
        if (l_value > 0 && r_value != 0) {
          if (l_value < (PromLim::max() / r_value)) {
            set_sat_flag(sat_flag);
            return PromLim::max();
          }
        } else if (l_value < 0 && r_value != 0) {
          if constexpr (is_signed_v<PromType>) {
            if (l_value < (PromLim::lowest() / r_value)) {
              set_sat_flag(sat_flag);
              return PromLim::lowest();
            }
          } else {
            set_sat_flag(sat_flag);
            return PromType{0};
          }
        }
      } else if constexpr (is_signed_v<Tr>) {
        return can_mul<Tr, Tl>(r_value, l_value);
      } else if (l_value > PromLim::max() / r_value) {
        set_sat_flag(sat_flag);
        return PromLim::max();
      }
    }
    return l_value * r_value;
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool sat_mul(const Tl l_value, const Tr r_value, bool* sat_flag) {
    return to_range<T>(sat_mul<Tl, Tr>(l_value, r_value, sat_flag), sat_flag);
  }

  template<typename Tl, typename Tr>
  constexpr Result<common_type_t<Tl, Tr>, ErrorCode> 
      try_mul(const Tl l_value, const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

      using Llim = numeric_limits<Tl>;
      using Rlim = numeric_limits<Tr>;
      using PromType = common_type_t<Tl, Tr>;
      using PromLim = numeric_limits<PromType>;
      constexpr int mul_min_prom_digits{(min_prom_digits / 2) + 1};

    if constexpr (Llim::digits > mul_min_prom_digits ||
        Rlim::digits > mul_min_prom_digits) {
      if constexpr (is_signed_v<Tl> && is_signed_v<Tl>) {
        if (l_value < 0 && r_value < 0) {
          if (l_value < (PromLim::max() / r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (l_value < 0 && r_value > 0) {
          if (l_value < (PromLim::lowest() / r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (l_value > 0 && r_value < 0) {
          if (r_value < (PromLim::lowest() / l_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (l_value > 0 && r_value > 0) {
          if (l_value > (PromLim::max() / r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        }
      } else if constexpr (is_signed_v<Tl>) {
        if (l_value > 0 && r_value != 0) {
          if (l_value < (PromLim::max() / r_value)) {
            return Error{ErrorCode::out_of_range};
          }
        } else if (l_value < 0 && r_value != 0) {
          if constexpr (is_signed_v<PromType>) {
            if (l_value < (PromLim::lowest() / r_value)) {
              return Error{ErrorCode::out_of_range};
            }
          } else {
            return Error{ErrorCode::out_of_range}
          }
        }
      } else if constexpr (is_signed_v<Tr>) {
        return can_mul<Tr, Tl>(r_value, l_value);
      } else if (l_value > PromLim::max() / r_value) {
        return Error{ErrorCode::out_of_range};
      }
    }
    return Valid{l_value * r_value};
  }

  template<typename T, typename Tl, typename Tr>
  constexpr Result<T, ErrorCode> try_mul(const Tl l_value, const Tr r_value) {
    return try_mul<Tl, Tr>(l_value, r_value).map_valid([](auto&& valid) {
      return numeric_cast<T>(valid);
    });
  }

  template<typename Tl, typename Tr>
  constexpr bool can_div(const Tl l_value, const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");
    using CommonType = common_type_t<Tl, Tr>;

    if constexpr (is_unsigned_v<CommonType>) {
      if constexpr (is_signed_v<Tl>) {
        if (l_value < 0) { return false; }
      } 
      if constexpr (is_signed_v<Tr>) {
        if (r_value < 0) { return false };
      }
    }
    return r_value != 0;
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool can_div(const Tl l_value, const Tr r_value) {
    return can_div<Tl, Tr>(l_value, r_value) && in_range<T>(l_value / r_value);
  }

  template<typename Tl, typename Tr>
  constexpr Result<common_type_t<Tl, Tr>, ErrorCode> 
      try_div(const Tl l_value, const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");
    using CommonType = common_type_t<Tl, Tr>;

    if constexpr (is_unsigned_v<CommonType>) {
      if constexpr (is_signed_v<Tl>) {
        if (l_value < 0) { 
          return Error{ErrorCode::out_of_range}; 
        }
      } 
      if constexpr (is_signed_v<Tr>) {
        if (r_value < 0) { 
          return Error{ErrorCode::out_of_range}; 
        }
      }
    }
    if (r_value == 0) {
      return Error{ErrorCode::out_of_range}; // POSSIBLY CHANGE?
    }
    return Valid{l_value / r_value};
  }

  template<typename T, typename Tl, typename Tr>
  constexpr Result<T, ErrorCode> try_div(const Tl l_value, const Tr r_value) {
    return try_div<Tl, Tr>(l_value, r_value).map_valid([](auto&& valid) {
      return numeric_cast<T>(valid);
    });
  }

  template<typename Tl, typename Tr>
  constexpr bool can_mod(const Tl l_value, const Tr r_value) {
    return can_div(l_value, r_value);
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool can_mod(const Tl l_value, const Tr r_value) {
    return can_div(l_value, r_value) && in_range<T>(l_value % r_value);
  }

  template<typename Tl, typename Tr>
  constexpr Result<common_type_t<Tl, Tr>, ErrorCode> 
      try_mod(const Tl l_value, const Tr r_value) {
    static_assert(is_integral_v<Tl>, "Tl must be an integral type.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");
    using CommonType = common_type_t<Tl, Tr>;

    if constexpr (is_unsigned_v<CommonType>) {
      if constexpr (is_signed_v<Tl>) {
        if (l_value < 0) { 
          return Error{ErrorCode::out_of_range}; 
        }
      } 
      if constexpr (is_signed_v<Tr>) {
        if (r_value < 0) { 
          return Error{ErrorCode::out_of_range}; 
        }
      }
    }
    if (r_value == 0) {
      return Error{ErrorCode::out_of_range}; // POSSIBLY CHANGE?
    }
    return Valid{l_value % r_value};
  }

  template<typename T, typename Tl, typename Tr>
  constexpr Result<T, ErrorCode> try_mod(const Tl l_value, const Tr r_value) {
    return try_mod<Tl, Tr>(l_value, r_value).map_valid([](auto&& valid) {
      return numeric_cast<T>(valid);
    });
  }

  template<typename Tl, typename Tr>
  constexpr bool can_lshift(const Tl l_value, const Tr r_value) {
    static_assert(is_unsigned_integer_v<Tl>, "Tl must be an unsigned integer.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");
    using Llim = numeric_limits<Tl>;
    
    if (r_value == 0) { return true; }
    if (r_value >= Llim::digits) { return false; }
    if constexpr (is_signed_v<Tr>) {
      if (r_value < 0) { return false; }
    }
    const int32_t min_clz_len{Llim::digits - r_value};
    const Tl min_clz_mask{~((Tl{1} << min_clz_len) - 1)};
    return (l_value & min_clz_mask) == 0;
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool can_lshift(const Tl l_value, const Tr r_value) {
    return can_lshift<Tl, Tr>(l_value, r_value) && in_range<T>(l_value << r_value);
  }

  template<typename Tl, typename Tr>
  constexpr auto sat_lshift(const Tl l_value, const Tr r_value, bool* sat_flag) {
    static_assert(is_unsigned_integer_v<Tl>, "Tl must be an unsigned integer.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");
    using Ct = common_type_t<Tl>;

    if constexpr (is_signed_v<Tr>) {
      if (r_value < 0) {
        set_sat_flag(sat_flag);
        return static_cast<Ct>(l_value);
      }
    }
    const int32_t max_shift{TI_BUILTIN_CLZ(Tl, ul_value) - 1};
    if (r_value > max_shift) {
      set_sat_flag(sat_flag);
      return l_value << max_shift;
    }
    return l_value << r_value;
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool sat_lshift(const Tl l_value, const Tr r_value, bool* sat_flag) {
    return to_range<T>(sat_lshift<Tl, Tr>(l_value, r_value, sat_flag), sat_flag);
  }

  template<typename Tl, typename Tr>
  constexpr Result<common_type_t<Tl>, ErrorCode> try_lshift(const Tl l_value, const Tr r_value) {
    static_assert(is_unsigned_integer_v<Tl>, "Tl must be an unsigned integer.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");

    if constexpr (is_signed_v<Tr>) {
      if (r_value < 0) {
        return Error{ErrorCode::out_of_range};
      }
    }
    const int32_t max_shift{TI_BUILTIN_CLZ(Tl, ul_value) - 1};
    if (r_value > max_shift) {
      return Error{ErrorCode::out_of_range};
    }
    return Valid{l_value << r_value};
  }

  template<typename T, typename Tl, typename Tr>
  constexpr Result<T, ErrorCode> try_lshift(const Tl l_value, const Tr r_value) {
    return try_lshift<Tl, Tr>(l_value, r_value).map_valid([](auto&& valid) {
      return numeric_cast<T>(valid);
    });
  }

  template<typename Tl, typename Tr>
  constexpr bool can_rshift(const Tl l_value, const Tr r_value) {
    static_assert(is_unsigned_integer_v<Tl>, "Tl must be an unsigned integer.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");
    using Llim = numeric_limits<Tl>;

    if (r_value >= Llim::digits) { return false; }
    if constexpr (is_signed_v<Tr>) {
      if (r_value < 0) { return false; }
    }
    const Tl min_ctz_mask{(Tl{1} << r_value) - 1};
    return (l_value & min_ctz_mask) == 0;
  }

  template<typename T, typename Tl, typename Tr>
  constexpr bool can_rshift(const Tl l_value, const Tr r_value) {
    return can_rshift<Tl, Tr>(l_value, r_value) && in_range<T>(l_value >> r_value);
  }

  template<typename Tl, typename Tr>
  constexpr auto sat_rshift(const Tl l_value, const Tr r_value, bool* sat_flag) {
    static_assert(is_unsigned_integer_v<Tl>, "Tl must be an unsigned integer.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");
    using Ct = common_type_t<Tl>;

    if constexpr (is_signed_v<Tr>) {
      if (r_value < 0) {
        set_sat_flag(sat_flag);
        return static_cast<Ct>(l_value);
      }
    }
    const int32_t max_shift{TI_BUILTIN_CTZ(Tl, ul_value) - 1};
    if (r_value > max_shift) {
      set_sat_flag(sat_flag);
      return l_value >> max_shift;
    }
    return l_value >> r_value;
  }

  template<typename T, typename Tl, typename Tr>
  constexpr T sat_rshift(const Tl l_value, const Tr r_value, bool* sat_flag) {
    return to_range<T>(sat_rshift<Tl, Tr>(l_value, r_value, sat_flag), sat_flag);
  }

  template<typename Tl, typename Tr>
  constexpr Result<common_type_t<Tl>, ErrorCode> try_rshift(const Tl l_value, const Tr r_value) {
    static_assert(is_unsigned_integer_v<Tl>, "Tl must be an unsigned integer.");
    static_assert(is_integral_v<Tr>, "Tr must be an integral type.");
    using Ct = common_type_t<Tl>;

    if constexpr (is_signed_v<Tr>) {
      if (r_value < 0) {
        return Error{ErrorCode::out_of_range};
      }
    }
    const int32_t max_shift{TI_BUILTIN_CTZ(Tl, ul_value) - 1};
    if (r_value > max_shift) {
      return Error{ErrorCode::out_of_range};
    }
    return Valid{l_value >> r_value};
  }

  template<typename T, typename Tl, typename Tr>
  constexpr Result<T, ErrorCode> try_rshift(const Tl l_value, const Tr r_value) {
    return try_rshift<Tl, Tr>(l_value, r_value).map_valid([](auto&& valid) {
      return numeric_cast<T>(valid);
    });
  }

  template<typename T>
  constexpr bool can_negate(const T value) {
    static_assert(is_integral_v<T>, "T must be an integral type.");
    if constexpr (is_signed_v<T>) {
      using ValueLim = numeric_limits<T>;
      if constexpr (ValueLim::digits >= min_prom_digits) {
        #if TI_TWO_COMPLEMENT
          return value > ValueLim::lowest();
        #elif TI_ONE_COMPLEMENT
          return value < ValueLim::max();
        #elif TI_SIGN_MAGNITUDE
          return true;
        #endif
      } else {
        return true;
      }
    } else {
      return value == 0;
    }
  }

  template<typename T, typename U>
  constexpr bool can_negate(const U value) {
    return can_negate<U>(value) && in_range<T>(-value);
  }

  template<typename T>
  constexpr auto sat_negate(const T value, bool* sat_flag) {
    static_assert(is_integral_v<T>, "T must be an integral type.");
    if constexpr (is_signed_v<T>) {
      using ValueLim = numeric_limits<T>;
      if constexpr (ValueLim::digits >= min_prom_digits) {
        #if TI_TWO_COMPLEMENT
          if (value <= ValueLim::lowest()) {
            set_sat_flag(sat_flag);
            return ValueLim::max();
          }
        #elif TI_ONE_COMPLEMENT
          if (value >= ValueLim::max()) {
            set_sat_flag(sat_flag);
            return ValueLim::lowest();
          }  
        #endif
      }
    } else if (value != 0) {
      set_sat_flag(sat_flag);
      return T{0};
    }
    return -value;
  }

  template<typename T, typename U>
  constexpr T sat_negate(const U value, bool* sat_flag) {
    return to_range<T>(sat_negate<U>(value, sat_flag), sat_flag);
  }

  template<typename T>
  constexpr Result<common_type_t<T>, ErrorCode> try_negate(const T value) {
    static_assert(is_integral_v<T>, "T must be an integral type.");
    if constexpr (is_signed_v<T>) {
      using ValueLim = numeric_limits<T>;
      if constexpr (ValueLim::digits >= min_prom_digits) {
        #if TI_TWO_COMPLEMENT
          if (value <= ValueLim::lowest()) {
            return Error{ErrorCode::out_of_range};
          }
        #elif TI_ONE_COMPLEMENT
          if (value >= ValueLim::max()) {
            return Error{ErrorCode::out_of_range};
          }  
        #endif
      }
    } else if (value != 0) {
      return Error{ErrorCode::out_of_range};
    }
    return Valid{-value};
  }

  template<typename T, typename U>
  constexpr Result<T, ErrorCode> try_negate(const U value) {
    return try_negate<T>(value).map_valid([](auto&& valid) {
      return numeric_cast<T>(valid);
    });
  }

  /// @endinternal

} // ti::util