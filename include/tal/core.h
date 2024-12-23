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
 * @file include/tal/core.h
 * @authors Aaron McBride
 * @brief Core language facilities.
 */

#ifndef INCLUDE_TAL_CORE_H
#define INCLUDE_TAL_CORE_H

#include "src/tool/macro_util.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /************************************************************************************************
   * @section Conveinence Macros for Language Keywords
   ************************************************************************************************/

  /**
   * @brief TODO
   */
  #define bool

  /**
   * @brief TODO
   */
  #define atomic

  /**
   * @brief TODO
   */
  #define complex

  /**
   * @brief TODO
   */
  #define imaginary

  /**
   * @brief TODO
   */
  #define noreturn

  /**
   * @brief TODO
   */
  #define thread_local

  /**
   * @brief TODO
   * @param cond
   * @param msg
   */
  #define static_assert(cond, msg)

  /**
   * @brief TODO
   * @param n
   */
  #define alignas(n)

  /**
   * @brief TODO
   * @param x
   */
  #define alignof(x)

  /************************************************************************************************
   * @section Core Value Definitions
   ************************************************************************************************/

  /**
   * @brief TODO
   */
  #define true

  /**
   * @brief TODO
   */
  #define false

  /**
   * @brief TODO
   */
  #define NULL

  /************************************************************************************************
   * @section Type Utilities
   ************************************************************************************************/

  /**
   * @brief TODO
   * @param type
   * @param member
   */
  #define offsetof(type, member)

  /**
   * @brief TODO
   * @param array
   */
  #define array_length(array)

  /**
   * @brief TODO
   * @param x
   */
  #define ssizeof(x)

  /************************************************************************************************
   * @section Compilation Utilities
   ************************************************************************************************/

  #define likely(cond)

  #define unlikely(cond)

  #define unreachable(cond)

  #define trap()

  /************************************************************************************************
   * @section Variadic Function Utilities
   ************************************************************************************************/

  /**
   * @brief TODO
   */
  #define va_list

  /**
   * @brief TODO
   * @param ap
   * @param type
   */
  #define va_arg(ap, type)

  /**
   * @brief TODO
   * @param dest
   * @param src
   */
  #define va_copy(dest, src)

  /**
   * @brief TODO
   * @param ap
   */
  #define va_end(ap)

  /**
   * @brief TODO
   * @param ap
   * @param param
   */
  #define va_start(ap, param)

  /************************************************************************************************
   * @section Control Flow Utilities
   ************************************************************************************************/

  /**
   * @brief TODO
   * @param cond
   */
  #define setjmp(env)

  /**
   * @brief TODO
   * @param env
   * @param val
   */
  #define longjmp(env, val)

  /************************************************************************************************
   * @section Control Flow Utilities
   ************************************************************************************************/


#if defined(__cplusplus)
  } /* extern "C" */
#endif

/* Port implementation */
#include _TAL_STR_X(_TAL_JOIN(src/port/, TAL_PORT_DIR, /core.inc))

#endif /* INCLUDE_TAL_CORE_H */