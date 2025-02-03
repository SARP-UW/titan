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
 * @file src/common/util/bit.h
 * @authors Aaron McBride
 * @brief Bit manipulation utilities.
 * @note - API stable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdnoreturn.h>

#ifdef __ICCARM__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * @section Core Pre-Processor Utilities
   **********************************************************************************************/

  /**
   * @brief Stringifies a token.
   * @param x (token) The token to stringify.
   * @returns (string literal) The result of stringifying @p [x].
   */
  #define str(x)

  /**
   * @brief Expands and stringifies a token.
   * @param x (token) The token to stringify.
   * @returns (string literal) The result of expanding and 
   *          stringifying @p [x].
   */
  #define strx(x)

  /**
   * @brief Concatenates two tokens.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @returns (token) The result of concatenating 
   *          @p [a] and @p [b].
   */
  #define cat(a, b)

  /**
   * @brief Expands and concatenates two tokens.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @returns (token) The result of expanding and concatenating 
   *          @p [a] and @p [b].
   */
  #define catx(a, b)

  /**
   * @brief Concatenates three tokens.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @param c (token) The third token.
   * @returns (token) The result of concatenating 
   *          @p [a], @p [b], and @p [c].
   */
  #define cat3(a, b, c)

  /**
   * @brief Expands and concatenates three tokens.
   * @param a (token) The first token.
   * @param b (token) The second token.
   * @param c (token) The third token.
   * @returns (token) The result of expanding and concatenating 
   *          @p [a], @p [b], and @p [c].
   */
  #define cat3x(a, b, c)

  /**********************************************************************************************
   * @section Uncategorised Core Utilities
   **********************************************************************************************/

  /**
   * @brief Determines the number of elements in an array.
   * @param array (token) The name of the target array.
   * @returns (int32_t) The number of elements in @p [array].
   * @note - @p [array] is expanded more than once.
   */
  #define array_size(array)



  /** @internal */

  /**********************************************************************************************
   * @section Implementation of Core Pre-Processor Utilities
   **********************************************************************************************/

  #undef str
  #define str(x) #x

  #undef strx
  #define strx(x) str(x)

  #undef cat
  #define cat(a, b) a ## b

  #undef catx
  #define catx(a, b) cat(a, b)

  #undef cat3
  #define cat3(a, b, c) a ## b ## c

  #undef cat3x
  #define cat3x(a, b, c) join(a, b, c)

  /**********************************************************************************************
   * @section Implementation of Uncategorised Core Utilities
   **********************************************************************************************/

  #undef array_size
  #define array_size(array) ({ \
    (void)((void*)&array == (void*)array); \
    (int32_t)(sizeof(array) / sizeof(array[0])); \
  })

  /** @endinternal */

#ifdef __cplusplus
  } // extern "C"
#endif