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
 * @file common/util/cstdint.h 
 * @authors Aaron McBride 
 * @brief Contains all implemented facilities of the cstdint library.
 */

#pragma once
#include "common/env/compiler_interface.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Width-Based Integer Types
   **************************************************************************************************/

  using int8_t = TI_INT8_TYPE;
  using uint8_t = TI_UINT8_TYPE;

  using int16_t = TI_INT16_TYPE;
  using uint16_t = TI_UINT16_TYPE;

  using int32_t = TI_INT32_TYPE;
  using uint32_t = TI_UINT32_TYPE;

  using int64_t = TI_INT64_TYPE;
  using uint64_t = TI_UINT64_TYPE;

  using intmax_t = TI_INTMAX_TYPE;
  using uintmax_t = TI_UINTMAX_TYPE;

  using intptr_t = TI_INTPTR_TYPE;
  using uintptr_t = TI_UINTPTR_TYPE;

  using size_t = TI_SIZE_TYPE;

} // namespace ti::util