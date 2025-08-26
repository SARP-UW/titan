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
 * @file modules/kernel/include/kernel/flag.h
 * @authors Aaron McBride
 * @brief Flag synchronization primitives.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

struct  ti_flag_t {
  const int32_t id;
  const void* const handle;
};

#define TI_FLAG_MEM_SIZE 0

struct ti_flag_t ti_create_flag(void* mem);

void ti_destroy_flag(struct ti_flag_t flag);

void ti_set_flag(struct ti_flag_t flag);

void ti_clear_flag(struct ti_flag_t flag);

bool ti_get_flag(struct ti_flag_t flag);

bool ti_await_flag(struct ti_flag_t flag, bool state, int64_t timeout);

bool ti_is_flag_valid(struct ti_flag_t flag);

bool ti_is_flag_equal(struct ti_flag_t flag_1, struct ti_flag_t flag_2);