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
 * @file modules/kernel/include/kernel/queue.h
 * @authors Aaron McBride
 * @brief Queue synchronization primitives.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

struct ti_queue_t {
  const int32_t id;
  const void* const handle;
};

#define TI_QUEUE_MEM_SIZE(size, length) 0

struct ti_queue_t create_queue(void* mem, int32_t size, int32_t length);

void destroy_queue(struct ti_queue_t queue);

void ti_queue_push(struct ti_queue_t queue, const void* src);

void ti_queue_pop(struct ti_queue_t queue, void* dst);

void ti_reset_queue(struct ti_queue_t queue);

int32_t ti_get_queue_size(struct ti_queue_t queue);

int32_t ti_get_queue_length(struct ti_queue_t queue);

int32_t ti_get_queue_count(struct ti_queue_t queue);

bool ti_is_queue_full(struct ti_queue_t queue);

bool ti_is_valid_queue(struct ti_queue_t queue);

bool ti_is_queue_equal(struct ti_queue_t queue_1, struct ti_queue_t queue_2);