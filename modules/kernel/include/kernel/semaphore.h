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
 * @file modules/kernel/include/kernel/semaphore.h
 * @authors Aaron McBride
 * @brief Semaphore synchronization primitives.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "kernel/thread.h"

struct ti_semaphore_t {
  const int32_t id;
  const void* const handle;
};

#define TI_SEMAPHORE_MEM_SIZE(capacity) 0

struct ti_semaphore_t ti_create_semaphore(void* mem, int32_t capacity);

void ti_destroy_semaphore(struct ti_semaphore_t semaphore);

bool ti_aquire_semaphore(struct ti_semaphore_t semaphore, uint64_t timeout);

bool ti_release_semaphore(struct ti_semaphore_t semaphore, uint64_t timeout);

int32_t ti_get_semaphore_capacity(struct ti_semaphore_t semaphore);

int32_t ti_get_semaphore_count(struct ti_semaphore_t semaphore);

bool ti_is_semaphore_full(struct ti_semaphore_t semaphore);

struct ti_thread_t ti_get_semaphore_owner(struct ti_semaphore_t semaphore, int32_t index);

bool ti_is_valid_semaphore(struct ti_semaphore_t semaphore);

bool ti_is_semaphore_equal(struct ti_semaphore_t semaphore1, struct ti_semaphore_t semaphore2);