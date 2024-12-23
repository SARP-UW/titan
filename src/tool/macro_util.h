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
 * @file src/tool/macro_util.h
 * @authors Aaron McBride
 * @brief Core utilities for the C preprocessor.
 */

#if !defined(SRC_TOOL_MACRO_UTIL_H)
#define SRC_TOOL_MACRO_UTIL_H

#if defined(__cplusplus)
  extern "C" {
#endif

  /**
   * @brief Stringifies a token.
   * @param x (token) The token to modify.
   * @returns (string literal) The stringified version of @p [x].
   */
  #define _TAL_STR(x)

  /**
   * @brief Stringifies and expands a token.
   * @param x (token) The token to modify.
   * @returns (string literal) The stringified version of @p [x], after it has
   *          undergone a single round of macro expansion.
   */
  #define _TAL_STR_X(x)

  /**
   * @brief Concatenates two tokens.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @returns (token) The concatenation of @p [a] and @p [b].
   */
  #define _TAL_CAT(a, b)

  /**
   * @brief Concatenates and expands two tokens.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @returns (token) The concatenation of @p [a] and @p [b], after both have
   *          undergone one round of macro expansion.
   */
  #define _TAL_CAT_X(a, b)

  /**
   * @brief Concatenates three tokens.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @param c (token) The third token.
   * @returns (token) The concatenation of @p [a], @p [b], and @p [c].
   * @note - The tokens are concatenated in the same order they are given.
   */
  #define _TAL_JOIN(a, b, c)

  /**
   * @brief Concatenates and expands three tokens.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @param c (token) The third token.
   * @returns (token) The concatenation of @p [a], @p [b], and @p [c], after all
   *          three tokens have undergone one round of macro expansion.
   * @note - The tokens are concatenated in the same order they are given.
   */
  #define _TAL_JOIN_X(a, b, c)

  /**
   * @brief Concatenates two tokens with a snake case separator.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @returns (token) The concatenation of @p [a] and @p [b], separated by an
   *          underscore.
   * @note - The tokens are concatenated in the same order they are given.
   */
  #define _TAL_CAT_SNAKE(a, b)

  /**
   * @brief Concatenates and expands two tokens with a snake case separator.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @returns (token) The concatenation of @p [a] and @p [b], separated by an
   *          underscore, after both have undergone one round of macro expansion.
   * @note - The tokens are concatenated in the same order they are given.
   */
  #define _TAL_CAT_SNAKE_X(a, b)

  /**
   * @brief Concatenates two tokens with a path separator.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @returns (token) The concatenation of @p [a] and @p [b], separated by a
   *          forward slash (path seperator).
   * @note - The tokens are concatenated in the same order they are given.
   */
  #define _TAL_CAT_PATH(a, b)

  /**
   * @brief Concatenates and expands two tokens with a path separator.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @returns (token) The concatenation of @p [a] and @p [b], separated by a
   *          forward slash (path seperator), after both have undergone one round
   *          of macro expansion.
   * @note - The tokens are concatenated in the same order they are given.
   */
  #define _TAL_CAT_PATH_X(a, b)

#if defined(__cplusplus)
  } // extern "C"
#endif

// Macro implementation
#include "src/tool/macro_util.inc"

#endif // SRC_TOOL_MACRO_UTIL_H