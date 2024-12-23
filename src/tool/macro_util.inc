/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2024 UW SARP
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
 * @file src/tool/macro_util.inc
 * @authors Aaron McBride
 * @brief Implementation of core utilities for the C preprocessor.
 */

#if !defined(SRC_TOOL_MACRO_UTIL_INC)
#define SRC_TOOL_MACRO_UTIL_INC

#if defined(__cplusplus)
  extern "C" {
#endif

  #undef _TAL_STR
  #define _TAL_STR(x) #x

  #undef _TAL_STR_X
  #define _TAL_STR_X(x) _TAL_STR(x)

  #undef _TAL_CAT
  #define _TAL_CAT(a, b) a##b

  #undef _TAL_CAT_X
  #define _TAL_CAT_X(a, b) _TAL_CAT(a, b)

  #undef _TAL_JOIN
  #define _TAL_JOIN(a, b, c) a##b##c

  #undef _TAL_JOIN_X
  #define _TAL_JOIN_X(a, b, c) _TAL_JOIN(a, b, c)

  #undef _TAL_CAT_SNAKE
  #define _TAL_CAT_SNAKE(a, b) a##_##b

  #undef _TAL_CAT_SNAKE_X
  #define _TAL_CAT_SNAKE_X(a, b) _TAL_CAT_SNAKE(a, b)

  #undef _TAL_CAT_PATH
  #define _TAL_CAT_PATH(a, b) a##/##b

  #undef _TAL_CAT_PATH_X
  #define _TAL_CAT_PATH_X(a, b) _TAL_CAT_PATH(a, b)

#if defined(__cplusplus)
  } // extern "C"
#endif

#endif // SRC_TOOL_MACRO_UTIL_INC