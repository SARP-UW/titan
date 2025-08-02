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
 * @file include/tal/error.h
 * @authors Joshua Beard & Aaron McBride & Charles Faisandier
 * @brief Error handling utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Constants
   **************************************************************************************************/

  #define tal_max_err_cnt 10

  /**************************************************************************************************
   * @section Error Types
   **************************************************************************************************/

  typedef struct {
    const char* msg;
    const char* func;
    const char* file;
    int32_t line;
    bool is_error;
  }tal_err_t;

  typedef struct {
    tal_err_t* err_list[tal_max_err_cnt];
    int32_t err_count;
  }tal_flag_t;

  /**************************************************************************************************
   * @section Error Handling Utilities
   **************************************************************************************************/

  #define tal_raise(flag, msg) \
      static const tal_err_t err_##__LINE__ = {msg, __PRETTY_FUNCTION__, __FILE__, __LINE__}; tal_raise_impl__(flag, &err_##__LINE__);

  #define tal_raise_ret(flag, msg, ret) \
      static const tal_err_t err##__LINE__ = {msg, __PRETTY_FUNCTION__, __FILE__, __LINE__}; tal_raise_impl__(flag, &err##__LINE__); return ret;

  bool tal_is_err(const tal_flag_t* flag);

  const tal_err_t* tal_get_err(const tal_flag_t* flag, const int32_t index);


  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  void tal_raise_impl__(tal_flag_t* flag, const tal_err_t* error) {
    for (int32_t i = 0; i < tal_max_err_cnt; ++i) {
      tal_err_t* c_err = &flag->err_list[i];
      if (!c_err->is_error) {
        c_err->msg = msg;
        c_err->file = file;
        c_err->func = func;
        c_err->line = line;
        c_err->is_error = true;
        break;
      }
    }
    return; // @todo -> do something on err list ovf?
  }

  void tal_raise_impl__(tal_flag_t* flag, const tal_err_t* error) {
    if (flag->err_count < tal_max_err_cnt) {
        flag->err_list[flag->err_count] = error;
    }
    
    flag->err_count++;
}

#if defined(__cplusplus)
  }
#endif