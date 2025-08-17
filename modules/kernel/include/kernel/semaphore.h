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

struct {
  const int32_t id;
  const void* const handle;
} ti_semaphore_t;

struct ti_semaphore_t ti_create_semaphore(int32_t max_count, int32_t init_count);

void ti_destroy_semaphore(struct ti_semaphore_t semaphore);