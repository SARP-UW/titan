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
 * @file common/util/memory.h 
 * @authors Aaron McBride 
 * @brief Contains memory management utilities.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Miscellaneous Memory Utilities
   **************************************************************************************************/ 

  /**
   * @brief Gets the address of an object.
   * @tparam T The type of the object.
   * @param target A lvalue reference to object to get the address of.
   * @returns A pointer to @p 'target'.
   */
  template<typename T>
  [[nodiscard]] constexpr T* addressof(T& target);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/ 

  template<typename T>
  constexpr T* addressof(T& target) {
    return TI_BUILTIN_ADDRESSOF(target);
  }

  /// @endinternal

} // namespace ti::util