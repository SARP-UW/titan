/**
 * This file is part of the Titan Project.
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
 * @file modules/util/include/util/core.h
 * @authors Aaron McBride
 * @brief Core language utilities.
 */

#pragma once
#include <stdbool.h>
#include "util/macro.h"

#define TI_LIKELY(cond) ({ \
  __builtin_expect(!!(cond), 1) \
})

#define TI_UNLIKELY(cond) ({ \
  __builtin_expect(!!(cond), 0) \
})

#define TI_DEFER(body) \
  void TI_XCAT(__def_fn_, __LINE__) (...) { body } \
  __attribute__((cleanup(TI_XCAT(__def_fn_, __LINE__)))) bool TI_XCAT(__def_val_, __LINE__);

#define TI_CONTAINER_OF(ptr, type, member) ({ \
  typeof(ptr) _ptr = (ptr); \
  _ptr ? (typeof(type)*)((char*)_ptr - offsetof(type, member)) : NULL; \
})

  /**
 * @brief Determines the number of elements in a static array.
 * @param array (array) The target array (size must be statically declared in TU).
 * @returns (int32_t) The number of elements in @p [array].
 * @note - @p [array] is expanded more than once.
 */
#define TI_ARRAY_LEN(array) ({ \
  (sizeof(array) / sizeof((array)[0])); \
})

/**
 * @brief Iterates forwards over each element in a static array.
 * @param index (token) The name of the variable which stores the current index (int32_t).
 * @param elem (token) The name of the variable which stores a pointer to the current element.
 * @param array (array) The target array (size must be statically declared in TU).
 * @note - This macro must be followed by a block declaration (open/close brackets).
 * @note - The symbol '__break' must not be used within the scope of the foreach loop.
 * @note - @p [index], @p [elem], @p [array], are expanded more than once.
 */
#define TI_FOREACH(index, elem, array) \
  for (int32_t index = 0; index < TI_ARRAY_LEN(array); index++) \
      for (__auto_type elem = &(array)[index]; elem < &(array)[index + 1]; elem++)

/**
 * @brief Iterates backwards over each element in a static array.
 * @param index (token) The name of the variable which stores the current index (int32_t).
 * @param elem (token) The name of the variable which stores a pointer to the current element.
 * @param array (array) The target array (size must be statically declared in TU).
 * @note - This macro must be followed by a block declaration (open/close brackets).
 * @note - The symbol '__break' must not be used within the scope of the foreach loop.
 * @note - @p [index], @p [elem], @p [array], are expanded more than once.
 */
#define TI_FOREACH_REV(index, elem, array) \
  for (int32_t index = TI_ARRAY_LEN(array) - 1; index >= 0; index--) \
      for (__auto_type elem = &(array)[index]; elem < &(array)[index + 1]; elem++)