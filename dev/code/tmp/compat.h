/**
 * This file is part of the Titan HAL
 * Copyright (c) 2025 UW SARP
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
 * @file src/common/util/compat.h
 * @authors Aaron McBride
 * @brief Compiler compatibility interface
 */

#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * @section ?
   **********************************************************************************************/

  #define ti_used

  #define ti_unused

  #define ti_weak

  #define ti_alias(name)

  #define ti_packed

  #define ti_naked

  #define ti_no_optimize

  #define ti_section(name)

  #define ti_no_discard

  #define ti_const

  #define ti_pure

  #define ti_volatile

  #define ti_no_inline

  #define ti_always_inline

  #define ti_constructor(priority)

  /**********************************************************************************************
   * @section ?
   **********************************************************************************************/

  #define ti_warning(msg)

  #define ti_typeof(x)

  #define ti_stmt(x)

  #define ti_asm(x)

  #define ti_auto_type

#ifdef __cplusplus
  } // extern "C"
#endif