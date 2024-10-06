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
 * @file common/util/bits/type_traits/logical_operator.h 
 * @authors Aaron McBride
 * @brief Contains type traits that performing logical operations.
 */

#pragma once
#include "common/util/cstdint.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Logical Operation Traits
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if every condition in the
   *        given parameter pack of boolean values is true, or false otherwise.
   * @tparam ... A parameter pack of boolean values to query.
   */
  template<bool cond, bool... other> 
  inline constexpr bool conjunction_v{cond && conjunction_v<other...>};

  template<bool cond>
  inline constexpr bool conjunction_v<cond>{cond};

  /**
   * @brief Template bool value that evaluates to true if at least one condition
   *        in the given parameter pack of boolean values is true, or false otherwise.
   * @tparam ... A parameter pack of boolean values to query.
   */
  template<bool cond, bool... other>
  inline constexpr bool disjunction_v{cond || disjunction_v<other...>};
  
  template<bool cond>
  inline constexpr bool disjunction_v<cond>{cond};

} // namespace ti::util