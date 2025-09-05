/**
 * @internal
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
 * @file modules/kernel/src/kernel_util.h
 * @authors Aaron McBride
 * @brief Internal utilities for the kernel module.
 */

#pragma once
#include <stdbool.h>
#include "util/macro.h"

/**
 * @brief Declares a function which will be executed durring the kernel initialization sequence.
 * @param fn_name (token) Name of the function to be declared.
 * @param prio (integral value) Priority of the function (lower values execute first, can only be 0-9).
 * @note - The declared function is static (not externally accessible).
 * @note - The function takes no arguments and returns a bool indicating if the initialization was successful.
 * @note - This function declares a function, thus it must be followed by a block declaration (brackets with function body inside).
 * @note - Symbols prefixed with "__kernel_init_fn_" are reserved in all scopes this macro is used in.
 */
#define _KERNEL_INIT_FN(fn_name, prio) \
  __attribute__((section(TI_XSTR(.ti_kernel_init.prio)), used)) \
  static bool (*const __kernel_init_fn_##fn_name)(void) = &fn_name; \
  static bool fn_name(void)

/** @endinternal */