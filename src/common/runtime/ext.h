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
 * @file common/runtime/ext.h
 * @authors Aaron McBride
 * @brief External function definitions used for runtime support.
 */

#pragma once
#include <stdint.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  __attribute__((weak)) void ti_ext_exit(void);

  __attribute__((weak)) void ti_ext_abort(void);

  __attribute__((weak)) void ti_ext_bkpt(void);

  __attribute__((weak)) void ti_ext_log(const char* msg);

#if defined(__cplusplus)
  }
#endif
