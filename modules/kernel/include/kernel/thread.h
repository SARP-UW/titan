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
#include "common/errc.h"

/** @brief TODO */
static const int32_t TI_MAX_THREAD_PRIORITY = 255;

/** @brief TODO */
static const int32_t TI_MIN_THREAD_PRIORITY = 0;

/** @brief TODO */
enum {
  TI_THREAD_STATE_CRITICAL,
  TI_THREAD_STATE_RUNNING,
  TI_THREAD_STATE_READY,
  TI_THREAD_STATE_SUSPENDED,
  TI_THREAD_STATE_STOPPED,
  TI_THREAD_STATE_OVERFLOW,
  TI_THREAD_STATE_NULL,
} ti_thread_state_t;

/** @brief TODO */
struct {
  const int32_t id;
  const void* const handle;
} ti_thread_t;

/**
 * @brief TODO
 * @param entry_fn 
 * @param arg 
 * @param stack 
 * @param stack_size 
 * @param priority 
 * @return 
 */
struct ti_thread_t ti_create_thread(void (*entry_fn)(void*), void* arg, void* stack, int32_t stack_size, int32_t priority);

/**
 * @brief TODO
 * @param thread 
 */
void ti_destroy_thread(struct ti_thread_t thread);

/**
 * @brief TODO
 * @param thread 
 */
void ti_suspend_thread(struct ti_thread_t thread);

/**
 * @brief TODO
 * @param thread 
 */
void ti_resume_thread(struct ti_thread_t thread);

/**
 * @brief TODO
 */
void ti_enter_critical(void);

/**
 * @brief TODO
 */
void ti_exit_critical(void);

/**
 * @brief TODO
 */
void ti_exit(void);

/**
 * @brief TODO
 */
void ti_yield(void);

/**
 * @brief TODO
 * @param thread 
 * @param priority 
 */
void ti_set_thread_priority(struct ti_thread_t thread, int32_t priority);

/**
 * @brief TODO
 * @param thread 
 * @return 
 */
int32_t ti_get_thread_priority(struct ti_thread_t thread);

/**
 * @brief TODO
 * @param thread 
 * @return 
 */
enum thread_state_t ti_get_thread_state(struct ti_thread_t thread);

/**
 * @brief TODO
 * @return
 */
struct ti_thread_t ti_get_this_thread(void);

/**
 * @brief TODO
 * @param thread_1 
 * @param thread_2 
 * @return 
 */
bool ti_is_thread_equal(struct ti_thread_t thread_1, struct ti_thread_t thread_2);