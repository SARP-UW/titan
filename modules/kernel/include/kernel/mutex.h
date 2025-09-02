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

/** @brief Handle for a mutex instance. */
struct ti_mutex_t {
  int32_t id;
  const void* handle;
};

/** @brief Denotes the type of a mutex. */
enum ti_mutex_type_t {
  TI_MUTEX_TYPE_INVALID,   /** @brief Invalid mutex type (do not use). */
  TI_MUTEX_TYPE_NORMAL,    /** @brief Non-recursive mutex type (can't be acquired multiple times by the same thread). */
  TI_MUTEX_TYPE_RECURSIVE, /** @brief Recursive mutex type (can be acquired multiple times by the same thread). */
};

/** @brief Size of memory required for a mutex instance. */
#define TI_MUTEX_MEM_SIZE 24

/** @brief Reference invalid mutex instance (guaranteed to always be invalid). */
static const struct ti_mutex_t TI_INVALID_MUTEX = {
  .id = -1,
  .handle = NULL,
};

/**
 * @brief Creates a new mutex instance.
 * @param mem (void*) Memory used internally for the mutex instance (must be at least TI_MUTEX_MEM_SIZE bytes).
 * @param type (enum ti_mutex_type_t) Type of mutex to create.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (struct ti_mutex_t) Handle for the created mutex (equal to TI_INVALID_MUTEX if an error occurs).
 * @note - If @p [mem] is modified before the mutex is destroyed, the behavior of the mutex is undefined.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [mem] is null or @p [type] is equal to TI_MUTEX_TYPE_INVALID.
 */
struct ti_mutex_t ti_create_mutex(void* mem, enum ti_mutex_type_t type, enum ti_errc_t* errc_out);

/**
 * @brief Destroys a mutex instance.
 * @param mutex (struct ti_mutex_t) Handle to the mutex to destroy.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - Interacting with a mutex in any way while it is being destroyed results in undefined behavior.
 * @note - If any error occurs, the state/existence of the mutex is guaranteed to be unchanged by this function.
 * @warning - TI_ERRC_INVALID_ARG is raised if the mutex identified by @p [mutex] does not exist.
 * @warning - TI_ERRC_INVALID_STATE is raised if the mutex is currently locked by any thread.
 */
void ti_destroy_mutex(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

/**
 * @brief Acquires ownership over a mutex for the calling thread (with timeout).
 * @param mutex (struct ti_mutex_t) Handle to the mutex to acquire.
 * @param timeout (int64_t) Timeout duration in microseconds.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @return (bool) True if the mutex was acquired successfully, or false otherwise (timeout or error).
 * @note - If any error occurs, the state of the mutex is guaranteed to be unchanged by this function.
 * @note - This function will always attempt to acquire the mutex at least once regardless of the value of @p [timeout].
 * @warning - TI_ERRC_INVALID_OP is raised if this function is called from an interrupt.
 * @warning - TI_ERRC_INVALID_ARG is raised if the mutex identified by @p [mutex] does not exist.
 * @warning - TI_ERRC_INVALID_STATE is raised if the mutex is already owned by the calling thread and it's type is not TI_MUTEX_TYPE_RECURSIVE.
 * @warning - TI_ERRC_INTERNAL can be raised by this function.
 */
bool ti_acquire_mutex(struct ti_mutex_t mutex, int64_t timeout, enum ti_errc_t* errc_out);

/**
 * @brief Releases ownership over a mutex from the calling thread.
 * @param mutex (struct ti_mutex_t) Handle to the mutex to release.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - If any error occurs, the state of the mutex is guaranteed to be unchanged by this function.
 * @warning - TI_ERRC_INVALID_OP is raised if this function is called from an interrupt.
 * @warning - TI_ERRC_INVALID_ARG is raised if the mutex identified by @p [mutex] does not exist.
 * @warning - TI_ERRC_INTERNAL can be raised by this function.
 * @warning - TI_ERRC_INVALID_STATE is raised if the mutex is not owned by the calling thread.
 */
void ti_release_mutex(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

/**
 * @brief Determines if a mutex is currently owned by a thread.
 * @param mutex (struct ti_mutex_t) Handle to the mutex to inspect.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @return (bool) True if the mutex is currently owned by a thread, false otherwise.
 * @warning - TI_ERRC_INVALID_ARG is raised if the mutex identified by @p [mutex] does not exist.
 */
bool ti_is_mutex_locked(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

/**
 * @brief Gets the current owner of a mutex.
 * @param mutex (struct ti_mutex_t) Handle to the mutex to inspect.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @return (struct ti_thread_t) Handle to the thread that currently owns the mutex, or TI_INVALID_THREAD if the mutex is not owned or an error occurred.
 * @warning - TI_ERRC_INVALID_ARG is raised if the mutex identified by @p [mutex] does not exist.
 */
struct ti_thread_t ti_get_mutex_owner(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

/**
 * @brief Gets the type of a mutex.
 * @param mutex (struct ti_mutex_t) Handle to the mutex to inspect.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @return (enum ti_mutex_type_t) The type of the mutex, or TI_MUTEX_TYPE_INVALID if an error occurred.
 * @warning - TI_ERRC_INVALID_ARG is raised if the mutex identified by @p [mutex] does not exist.
 */
enum ti_mutex_type_t ti_get_mutex_type(struct ti_mutex_t mutex, enum ti_errc_t* errc_out);

/**
 * @brief Determines if a mutex exists.
 * @param mutex (struct ti_mutex_t) Handle to the mutex to inspect.
 * @return (bool) True if the mutex identified by @p [mutex] exists, or false otherwise.
 */
bool ti_is_valid_mutex(struct ti_mutex_t mutex);

/**
 * @brief Determines if two mutexes are equal.
 * @param mutex_1 (struct ti_mutex_t) Handle to the first mutex to compare.
 * @param mutex_2 (struct ti_mutex_t) Handle to the second mutex to compare.
 * @return (bool) True if @p [mutex_1] and @p [mutex_2] identify the same internal mutex (even if it does not exist) or false otherwise.
 */
bool ti_is_mutex_equal(struct ti_mutex_t mutex_1, struct ti_mutex_t mutex_2);