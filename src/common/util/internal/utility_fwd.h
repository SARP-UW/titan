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
 * @file common/util/internal/util_fwd.h 
 * @authors Aaron McBride 
 * @brief Contains foward declarations for various types.
 * @note - This file is internal to the 'Util' module.
 */

#pragma once
#include "common/util/type_traits.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation Forward Declarations
   **************************************************************************************************/

  template<typename T> 
  struct in_place_type_t {
    constexpr explicit in_place_type_t() = default;
  };

  /// @endinternal

} // namespace ti::util