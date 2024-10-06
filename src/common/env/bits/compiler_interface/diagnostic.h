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
 * @file common/env/bits/diagnostic.h 
 * @authors Aaron McBride 
 * @brief Compiler-agnostic diagnostic control interface.
 */

#pragma once

/**************************************************************************************************
 * @section Diagnostic Control Interface
 **************************************************************************************************/

#if defined(__GNUC__)

  #define TI_DIAG_SUPPRESS_ALL \
      _Pragma("GCC diagnostic push") \
      _Pragma("GCC diagnostic ignored \"-Wall\"") \
      _Pragma("GCC diagnostic ignored \"-Wextra\"") \
      _Pragma("GCC diagnostic ignored \"-Wpedantic\"")

  #define TI_DIAG_END_SUPPRESS \
      _Pragma("GCC diagnostic pop")

#endif