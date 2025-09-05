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

/**
 * @brief Indicates to the compiler that a condition is likely to be true.
 * @param cond (expression) The likely condition.
 * @returns (bool) The result of @p [cond].
 * @remark - This macro should be used sparingly, for conditions that are only EXTREMELY likely.
 * @remark - This macro can aid in compiler optimization.
 */
#define TI_LIKELY(cond) ({ \
  __builtin_expect(!!(cond), 1) \
})

/** 
 * @brief Indicates to the compiler that a condition is unlikely to be true.
 * @param cond (expression) The unlikely condition.
 * @returns (bool) The result of @p [cond].
 * @remark - This macro should be used sparingly, for conditions that are only EXTREMELY unlikely.
 * @remark - This macro can aid in compiler optimization.
 */
#define TI_UNLIKELY(cond) ({ \
  __builtin_expect(!!(cond), 0) \
})

/**
 * @brief Gets the size of a struct/union member.
 * @param type (type) The type of the parent struct/union.
 * @param member (token) The name of the member to get the size of.
 * @returns (int32_t) The size of @p [member].
 * @note - @p [type] and @p [member] are expanded more than once.
 */
#define TI_MEMBER_SIZE(type, member) ({ \
  (int32_t)sizeof(((type*)0)->member) \
})

/**
 * @brief Gets a pointer to the parent struct/union containing the given member.
 * @param ptr (pointer) A pointer to a member of the parent struct/union.
 * @param type (type) The type of the parent struct/union.
 * @param member (token) The name of the member pointed to by @p [ptr].
 * @returns (pointer to @p [type]) A pointer to the parent struct/union.
 * @note - @p [type] and @p [member] are expanded more than once.
 * @note - @p [ptr] is only expanded once.
 */
#define TI_CONTAINER_OF(ptr, type, member) ({ \
  __auto_type _ptr = (ptr); \
  _ptr ? (type*)((uint8_t*)_ptr - offsetof(type, member)) : NULL; \
})

/**
 * @brief Determines the number of elements in a static array.
 * @param array (array) The target array (size must be statically declared in TU).
 * @returns (int32_t) The number of elements in @p [array].
 * @note - @p [array] cannot be an array argument of a function.
 * @note - @p [array] is expanded more than once.
 */
#define TI_ARRAY_LEN(array) ({ \
  _Static_assert(!__builtin_types_compatible_p(typeof(array), typeof(&(array)[0]))); \
  ((int32_t)sizeof(array) / (int32_t)sizeof((array)[0])); \
})

/**
 * @brief Iterates over each element in an array forwards.
 * @param elem (token) The name of the variable which stores a pointer to the current element.
 * @param array (array) The target array to iterate over (must be statically sized in TU).
 * @note - This macro expands to a for loop and thus must be followed by a block declaration (brackets).
 * @note - @p [elem] and @p [array] are expanded more than once.
 * @note - "break" and "continue" will work as expected in this for loop.
 */
#define TI_FOREACH(elem, array) \
  for (__auto_type elem = &((array)[0]); elem < &((array)[TI_ARRAY_LEN(array)]); elem++)

/**
 * @brief Iterates over each element in an array backwards.
 * @param elem (token) The name of the variable which stores a pointer to the current element.
 * @param array (array) The target array to iterate over (must be statically sized in TU).
 * @note - This macro expands to a for loop and thus must be followed by a block declaration (brackets).
 * @note - @p [elem] and @p [array] are expanded more than once.
 * @note - "break" and "continue" will work as expected in this for loop.
 */
#define TI_FOREACH_REV(elem, array) \
  for (__auto_type elem = &((array)[TI_ARRAY_LEN(array) - 1]); elem >= &((array)[0]); elem--)

/**
 * @brief Defers execution of a block of code until the current scope is exited.
 * @param va_args (code block) The code block to execute when the current scope is exited.
 * @note - Any identifiers prefixed with __ti_defer are reserved in the scope this macro is used.
 * @note - This macro must not be expanded (used) twice on the same line.
 * @note - If multiple blocks of code are deferred, they will be executed in reverse order.
 */
#define TI_DEFER(...) \
  void TI_XCAT(__ti_defer_fn_, __LINE__) (...) { __VA_ARGS__ } \
  __attribute__((cleanup(TI_XCAT(__ti_defer_fn_, __LINE__)))) bool TI_XCAT(__ti_defer_val_, __LINE__);