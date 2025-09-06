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
 * @file modules/kernel/include/kernel/thread.h
 * @authors Aaron McBride
 * @brief Thread management and control facilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "util/errc.h"

/** @brief Handle for a thread instance. */
struct ti_thread_t {
  int32_t id;
  const void* handle;
};

/** @brief Denotes the state of a thread. */
enum ti_thread_state_t {
  TI_THREAD_STATE_RUNNING,
  TI_THREAD_STATE_READY,
  TI_THREAD_STATE_SUSPENDED,
  TI_THREAD_STATE_STOPPED,
};

/** @brief Minimum required stack size for threads.  */
#define TI_THREAD_MIN_STACK_SIZE 128

/**
 * @brief Gets the size of the memory block required for a thread instance.
 * @param stack_size (integral value) The desired stack size for the thread.
 * @returns (integral value) The size of the memory block required for the thread instance.
 * @note - @p [stack_size] is only expanded once.
 */
#define TI_THREAD_MEM_SIZE(stack_size) \
  ((stack_size) + 32)

/** @brief Reference invalid thread instance (will always be invalid). */
static const struct ti_thread_t TI_INVALID_THREAD = {
  .id = -1,
  .handle = NULL
};

/**
 * @brief Creates a new thread instance.
 * @param mem (void*) Memory used internally for thread instance (must be at least TI_THREAD_MEM_SIZE(@p [stack_size]) bytes).
 * @param entry_fn (void (*)(void*)) The entry function for the thread.
 * @param arg (void*) Argument passed to the thread entry function.
 * @param stack_size (int32_t) The size of the stack used for the thread.
 * @param priority (int32_t) The priority of the thread (1 to TI_CFG_MAX_THREAD_PRIORITY, higher values result in less latency).
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (struct ti_thread_t) Handle for the created thread instance (equal to TI_INVALID_THREAD on error).
 * @note - The created thread will begin execution automatically after the scheduler runs.
 * @note - The state of the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [mem] or @p [entry_fn] are NULL, if @p [stack_size] is less than TI_THREAD_MIN_STACK_SIZE, or if @p [priority] is out of range.
 * @warning - TI_ERRC_NO_MEM is raised if TI_CFG_MAX_THREADS threads already exist.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
struct ti_thread_t ti_create_thread(void* mem, void (*entry_fn)(void*), void* arg, int32_t stack_size, int32_t priority, enum ti_errc_t* errc_out);

/**
 * @brief Destroys a thread instance.
 * @param thread (struct ti_thread_t) Handle for the thread instance to destroy.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - The behavior of any function which uses @p [thread] is undefined if invoked during the execution of this function.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the given thread and the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist.
 * @warning - TI_ERRC_INVALID_STATE is raised if the thread is not in the TI_THREAD_STATE_STOPPED state.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
void ti_destroy_thread(struct ti_thread_t thread, enum ti_errc_t* errc_out);

/**
 * @brief Suspends a running thread, preventing it from executing until resumed.
 * @param thread (struct ti_thread_t) Handle for the thread instance to suspend.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - If the calling thread is being suspended, the scheduler will run immediately.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the given thread and the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist.
 * @warning - TI_ERRC_INVALID_STATE is raised if the thread is not in the TI_THREAD_STATE_READY or TI_THREAD_STATE_RUNNING state, or if attempting to suspend the calling thread while in a critical/exclusive section.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
void ti_suspend_thread(struct ti_thread_t thread, enum ti_errc_t* errc_out);

/**
 * @brief Resumes a suspended thread, allowing it to continue execution.
 * @param thread (struct ti_thread_t) Handle for the thread instance to resume.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the given thread and the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist.
 * @warning - TI_ERRC_INVALID_STATE is raised if the thread is not in the TI_THREAD_STATE_SUSPENDED state.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
void ti_resume_thread(struct ti_thread_t thread, enum ti_errc_t* errc_out);

/**
 * @brief Immediately stops execution of the calling thread/interrupt.
 * @note - If invoked from a thread, the thread will be immediately stopped without saving context.
 * @note - If invoked from an interrupt, the interrupt will be immediately exited without saving context.
 * @note - If invoked from within a critical/exclusive section the section will be reset.
 * @note - If an error occurs, this function will continue trying to stop the thread/interrupt indefinitely.
 */
void ti_exit(void);

/**
 * @brief Yields execution of the calling thread to allow other threads to run.
 * @note - If invoked from an interrupt or within a critical/exclusive section, this function does nothing.
 */
void ti_yield(void);

/**
 * @brief Sets the priority of a thread.
 * @param thread (struct ti_thread_t) Handle for the thread instance to modify.
 * @param priority (int32_t) The new priority of the thread (1 to TI_CFG_MAX_THREAD_PRIORITY, higher values result in less latency).
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the given thread and the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist or if @p [priority] is out of range.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
void ti_set_thread_priority(struct ti_thread_t thread, int32_t priority, enum ti_errc_t* errc_out);

/**
 * @brief Gets the priority of a thread.
 * @param thread (struct ti_thread_t) Handle for the thread instance to query.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (int32_t) The priority of the thread, or -1 if an error occurred.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the given thread and the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
int32_t ti_get_thread_priority(struct ti_thread_t thread, enum ti_errc_t* errc_out);

/**
 * @brief Gets the current state of a thread.
 * @param thread (struct ti_thread_t) Handle for the thread instance to query.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (enum ti_thread_state_t) The state of the thread, or -1 if an error occurred.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the given thread and the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
enum ti_thread_state_t ti_get_thread_state(struct ti_thread_t thread, enum ti_errc_t* errc_out);

/**
 * @brief Gets the stack size of a thread.
 * @param thread (struct ti_thread_t) Handle for the thread instance to query.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (int32_t) The stack size of the thread, or -1 if an error occurred.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist.
 */
int32_t ti_get_thread_stack_size(struct ti_thread_t thread, enum ti_errc_t* errc_out);

/**
 * @brief Gets the current stack usage of a thread.
 * @param thread (struct ti_thread_t) Handle for the thread instance to query.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (int32_t) The number of bytes in use on the thread's stack (updated the last time the scheduler ran), or -1 if an error occured.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the given thread and the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
int32_t ti_get_thread_stack_usage(struct ti_thread_t thread, enum ti_errc_t* errc_out);

/**
 * @brief Determines if a thread's stack has overflowed.
 * @param thread (struct ti_thread_t) Handle for the thread instance to query.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (bool) True if no error occured and the thread's stack has overflowed, or false otherwise.
 * @note - The state of the given thread and the multithreading system is guaranteed to be unchanged if any error other than TI_ERRC_INTERNAL occurs.
 * @note - The state of the given thread and the multithreading system is undefined if TI_ERRC_INTERNAL occurs.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [thread] does not exist.
 * @warning - TI_ERRC_TIMEOUT is raised if it cannot gain exclusive access to internal data structures within TI_CFG_THREAD_TIMEOUT time units.
 * @warning - TI_ERRC_INTERNAL can be raised if an internal error occurs.
 */
bool ti_is_thread_overflow(struct ti_thread_t thread, enum ti_errc_t* errc_out);

/**
 * @brief Gets the handle of the thread which invoked this function.
 * @returns (struct ti_thread_t) Handle to the calling thread (equal to TI_INVALID_THREAD if called from non-thread context).
 * @note - This function returns TI_INVALID_THREAD if called from an interrupt.
 */
struct ti_thread_t ti_get_this_thread(void);

/**
 * @brief Determines if a thread exists.
 * @param thread (struct ti_thread_t) Handle for the thread instance to query.
 * @return (bool) True if the thread exists (created and not destroyed), or false otherwise.
 */
bool ti_is_valid_thread(struct ti_thread_t thread);

/**
 * @brief Determines if two thread handles refer to the same thread instance.
 * @param thread_1 (struct ti_thread_t) Handle for the first thread instance to compare.
 * @param thread_2 (struct ti_thread_t) Handle for the second thread instance to compare.
 * @return (bool) True if both handles refer to the same internal thread instance (regardless of existance), or false otherwise.
 */
bool ti_is_thread_equal(struct ti_thread_t thread_1, struct ti_thread_t thread_2);