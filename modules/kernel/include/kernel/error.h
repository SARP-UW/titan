/**
 * This file is part of the Titan Project.
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
 * @file modules/kernel/include/kernel/error.h
 * @authors Aaron McBride
 * @brief Thread error handling and reporting utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "util/errc.h"
#include "kernel/thread.h"

struct ti_error_t {
  const enum ti_errc_t errc;
  const char* msg;
  const char* file;
  const char* func;
  const int32_t line; 
};

#define TI_ERROR(errc, msg) ()

#define TI_ERROR_IF(cond, errc, msg) ()

bool ti_is_error(struct ti_thread_t thread);

bool ti_await_error(struct ti_thread_t thread, int64_t timeout, struct ti_error_t* error_out);