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
 * @file include/tal/alloc.h
 * @authors Aaron McBride
 * @brief Dynamic allocation facilities.
 */

#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**
   * @brief TODO
   * @param size (int32_t)
   * @returns void*
   */
  void* malloc(int32_t size);

  /**
   * @brief TODO
   * @param ptr (void*)
   * @param new_size (int32_t)
   * @returns (void*)
   */
  void* realloc(void* ptr, int32_t new_size);

  /**
   * @brief TODO
   * @param ptr (void*)
   * @returns (void*)
   */
  void* alloca(int32_t size);

  /**
   * @brief TODO
   * @param ptr (void*)
   * @returns (void*)
   */
  bool free(void* ptr);

  /**
   * @brief TODO
   * @param ptr (void*)
   * @returns (int32_t)
   */
  int32_t alloc_size(void* ptr);

  /**
   * @brief TODO
   * @param ptr (void*)
   * @returns (bool)
   */
  bool is_alloc(void* ptr);
  
#if defined(__cplusplus)
  } // extern "C"
#endif