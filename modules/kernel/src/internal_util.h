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
 * @file modules/kernel/src/internal_util.h
 * @authors Aaron McBride
 * @brief Internal utilities for the kernel module.
 */

#pragma once
#include <stdbool.h>
#include "util/macro.h"

#define _KERNEL_INIT_FN(fn_name, prio) \
  __attribute__((section(TI_XSTR(.ti_kernel_init.prio)), used)) \
  static bool (*const _init_fn_##fn_name)(void) = &fn_name; \
  bool fn_name(void)

_KERNEL_INIT_FN(_init_host, 010) {
  return true;
}

/** @endinternal */