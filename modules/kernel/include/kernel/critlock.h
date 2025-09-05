/**
 * This file is part of the Titan Project.
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
 * @file modules/kernel/include/kernel/critlock.h
 * @authors Aaron McBride
 * @brief Critlock synchronization primitives.
 *
 * TODO: Paragraph with general usage information here.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "util/errc.h"

/** @brief Handle for critlock instances. */
struct ti_critlock_t {
  int32_t id;
  const void* handle;
};

/** @brief Size of memory block required for a critlock instance. */
#define TI_CRITLOCK_MEM_SIZE 8

/** @brief Reference invalid critlock instance (will always be invalid). */
static const struct ti_critlock_t TI_INVALID_CRITLOCK = { 
  .id = -1, 
  .handle = NULL, 
};

/**
 * @brief Creates a new critlock instance.
 * @param mem (void*) Memory used internally for the critlock instance (must be at least TI_CRITLOCK_MEM_SIZE bytes).
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (struct ti_critlock_t) Handle for the created critlock (equal to TI_INVALID_CRITLOCK if an error occurs).
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [mem] is null.
 */
struct ti_critlock_t ti_create_critlock(void* mem, enum ti_errc_t* errc_out);

/**
 * @brief Destroys a critlock instance.
 * @param critlock (struct ti_critlock_t) Handle for the critlock to destroy.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - The behavior of any function which utilizes the critlock is undefined if it is called concurrently with this function.
 * @note - The state/existance of the critlock is guaranteed to be unchanged if an error occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [critlock] does not exist.
 * @warning - TI_ERRC_INVALID_STATE is raised if the critlock is locked.
 */
void ti_destroy_critlock(struct ti_critlock_t critlock, enum ti_errc_t* errc_out);

/**
 * @brief Acquires ownership over a critlock.
 * @param critlock (struct ti_critlock_t) Handle for the critlock to acquire.
 * @param timeout (int64_t) Timeout for acquiring the critlock (in standard time units).
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (bool) True if the critlock was acquired successfully, or false otherwise (timeout/error).
 * @note - A critlock can never be recursively acquired.
 * @note - Acquiring a critlock causes this thread to enter a critical section (interrupts disabled).
 * @note - This function will attempt to acquire the critlock at least once regardless of the value of @p [timeout].
 * @note - The state of the critlock is guaranteed to be unchanged if an error occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [critlock] does not exist.
 */
bool ti_acquire_critlock(struct ti_critlock_t critlock, int64_t timeout, enum ti_errc_t* errc_out);

/**
 * @brief Releases ownership of a critlock.
 * @param critlock (struct ti_critlock_t) Handle for the critlock to release.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - A critlock should never be released by a thread which does not have ownership over it.
 * @note - Releasing a critlock causes this thread to exit a critical section (matching entry upon acquisition).
 * @note - The state of the critlock is guaranteed to be unchanged if an error occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [critlock] does not exist.
 * @warning - TI_ERRC_INVALID_STATE is raised if the critlock is not currently locked.
 */
void ti_release_critlock(struct ti_critlock_t critlock, enum ti_errc_t* errc_out);

/**
 * @brief Determines if a critlock is currently locked.
 * @param critlock (struct ti_critlock_t) Handle for the critlock to check.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (bool) True if no error occurs and the critlock is currently locked, or false otherwise.
 * @note - The state of the critlock is guaranteed to be unchanged if an error occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [critlock] does not exist.
 */
bool ti_is_critlock_locked(struct ti_critlock_t critlock, enum ti_errc_t* errc_out);

/**
 * @brief Determines if a critlock instance exists.
 * @param critlock (struct ti_critlock_t) Handle for the critlock to inspect.
 * @returns (bool) True if the critlock exists (created and not destroyed), or false otherwise.
 */
bool ti_is_valid_critlock(struct ti_critlock_t critlock);

/**
 * @brief Determines if two critlock instances are equal.
 * @param critlock_1 (struct ti_critlock_t) Handle for the first critlock to compare.
 * @param critlock_2 (struct ti_critlock_t) Handle for the second critlock to compare.
 * @returns (bool) True if @p [critlock_1] and @p [critlock_2] refer to the same internal critlock instance (regardless of existence), or false otherwise.
 */
bool ti_is_critlock_equal(struct ti_critlock_t critlock_1, struct ti_critlock_t critlock_2);