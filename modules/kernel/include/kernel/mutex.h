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
#include "kernel/thread.h"

/** @brief TODO */
enum {
  TI_MUTEX_STATE_UNLOCKED,
  TI_MUTEX_STATE_LOCKED,
  TI_MUTEX_STATE_NULL,
} ti_mutex_state_t;

/** @brief TODO */
struct {
  const int32_t id;
  const void* const handle;
} ti_mutex_t;

/**
 * @brief TODO
 * @returns
 */
struct ti_mutex_t ti_create_mutex(void);

/**
 * @brief TODO
 * @param mutex 
 */
void ti_destroy_mutex(struct ti_mutex_t mutex);

/**
 * @brief TODO
 * @param mutex 
 * @param timeout 
 * @returns 
 */
bool ti_acquire_mutex(struct ti_mutex_t mutex, int64_t timeout);

/**
 * @brief TODO
 * @param mutex 
 * @param timeout 
 * @returns
 */
bool ti_release_mutex(struct ti_mutex_t mutex, int64_t timeout);

/**
 * @brief TODO
 * @param mutex
 * @returns
 */
enum ti_mutex_state_t ti_get_mutex_state(struct ti_mutex_t mutex);

/**
 * @brief TODO
 * @param mutex
 * @returns
 */
struct ti_thread_t ti_get_mutex_owner(struct ti_mutex_t mutex);