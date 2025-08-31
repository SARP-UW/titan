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
 * @file modules/kernel/include/kernel/mutex.h
 * @authors Aaron McBride
 * @brief Mutex synchronization primitives.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "util/errc.h"
#include "kernel/thread.h"

struct ti_mutex_t {
  int32_t id;
  const void* handle;
};

enum ti_mutex_type_t {
  TI_MUTEX_TYPE_INVALID,
  TI_MUTEX_TYPE_NORMAL,
  TI_MUTEX_TYPE_RECURSIVE,
};

#define TI_MUTEX_MEM_SIZE 20

extern const struct ti_mutex_t TI_INVALID_MUTEX;

struct ti_mutex_t ti_create_mutex(void* mem, enum ti_mutex_type_t type, enum ti_errc_t* errc_out);

void ti_destroy_mutex(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

bool ti_acquire_mutex(struct ti_mutex_t mutex, int64_t timeout, enum ti_errc_t* errc_out);

bool ti_release_mutex(struct ti_mutex_t mutex, int64_t timeout, enum ti_errc_t* errc_out);

bool ti_is_mutex_locked(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

struct ti_thread_t ti_get_mutex_owner(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

enum ti_mutex_type_t ti_get_mutex_type(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

bool ti_is_valid_mutex(struct ti_mutex_t mutex);

bool ti_is_mutex_equal(struct ti_mutex_t mutex_1, struct ti_mutex_t mutex_2);