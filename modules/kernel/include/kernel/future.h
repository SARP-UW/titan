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
 * @file modules/kernel/include/kernel/future.h
 * @authors Aaron McBride
 * @brief Future synchronization primitives.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

struct ti_future_t {
  const int32_t id;
  const void* const handle;
};

#define TI_FUTURE_MEM_SIZE(size) 0

struct ti_future_t ti_create_future(void* mem, int32_t size);

void ti_destroy_future(struct ti_future_t future);

bool ti_await_future(struct ti_future_t future, void* dst, int64_t timeout);

bool ti_check_future(struct ti_future_t future);

void ti_set_future(struct ti_future_t future, const void* src);

int32_t ti_get_future_size(struct ti_future_t future);

bool ti_is_valid_future(struct ti_future_t future);

bool ti_is_future_equal(struct ti_future_t future_1, struct ti_future_t future_2);