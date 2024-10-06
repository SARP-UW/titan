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
 * @file common/util/bits/utility/lang_support.h 
 * @authors Aaron McBride 
 * @brief Contains language support utilities.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/type_traits.h"

namespace ti::util {

  /************************************************************************************************
   * @section Standard Language Support Utilities
   ***********************************************************************************************/

  /**
   * @brief Informs the compiler that a location in code is unreachable.
   * @note - Use to denote actually unreachable locations in code,
   *       not to denote locations where an error should be triggered.
   */
  TI_ATTR_ALWAYS_INLINE_FN [[noreturn]] inline constexpr void unreachable();

  /**
   * @brief Gets the address of an object.
   * @tparam T The type of the object.
   * @param target A lvalue reference to object to get the address of.
   * @returns A pointer to @p 'target'.
   */
  template<typename T>
  [[nodiscard]] constexpr T* addressof(T& target);

  /************************************************************************************************
   * @section Non-Standard Language Support Utilities
   ***********************************************************************************************/

  /**
   * @brief Informs the compiler that a condition is likely to be true.
   * @param cond The boolean condition that is likely to be true.
   * @param perc An int32_t which denotes the percent (0 - 100) likelihood that 
   *        @p 'cond' is true (defaults to 100).
   * @returns A boolean value equal to @p 'cond'.
   */
  TI_ATTR_ALWAYS_INLINE_FN inline constexpr bool likely(
      const bool cond, const int32_t perc = 100);

  /**
   * @brief Informs the compiler that a condition is likely to be false.
   * @param cond The boolean condition that is likely to be false.
   * @param perc An int32_t which denotes the percent (0 - 100) likelihood that
   *        @p 'cond' is false (defaults to 100).
   * @returns A boolean value equal to @p 'cond'.
   */
  TI_ATTR_ALWAYS_INLINE_FN inline constexpr bool unlikely(
      const bool cond, const int32_t perc = 100);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  inline constexpr void unreachable() {
    #if defined(TI_DEBUG)
      TI_BUILTIN_TRAP();
    #else
      TI_BUILTIN_UNREACHABLE();
    #endif
  }

  template<typename T>
  [[nodiscard]] constexpr T* addressof(T& target) {
    return TI_BUILTIN_ADDRESSOF(target);
  }


  inline constexpr bool likely(const bool cond, const int32_t perc) {
    return TI_BUILTIN_EXPECT_PROB(cond, true, perc / 100);
  }

  inline constexpr bool unlikely(const bool cond, const int32_t perc) {
    return TI_BUILTIN_EXPECT_PROB(cond, false, perc / 100);
  } 

  /// @endinternal

} // namespace ti::util