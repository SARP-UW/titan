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

struct ti_thread_t {
  int32_t id;
  const void* handle;
};

enum ti_thread_state_t {
  TI_THREAD_STATE_EXCLUSIVE,
  TI_THREAD_STATE_CRITICAL,
  TI_THREAD_STATE_RUNNING,
  TI_THREAD_STATE_READY,
  TI_THREAD_STATE_SUSPENDED,
  TI_THREAD_STATE_STOPPED,
  TI_THREAD_STATE_OVERFLOW,
};

enum ti_core_id_t {
  TI_CORE_ID_CM7,
  TI_CORE_ID_CM4,
};

#define TI_THREAD_MIN_STACK_SIZE 128

#define TI_THREAD_MEM_SIZE(stack_size) 0

static const struct ti_thread_t TI_INVALID_THREAD = {
  .id = -1,
  .handle = NULL
};

struct ti_thread_t ti_create_thread(void* mem, void (*entry_fn)(void*), void* arg, int32_t stack_size, int32_t priority, enum ti_errc_t* errc_out);

void ti_destroy_thread(struct ti_thread_t thread, enum ti_errc_t* errc_out);

void ti_suspend_thread(struct ti_thread_t thread, enum ti_errc_t* errc_out);

void ti_resume_thread(struct ti_thread_t thread, enum ti_errc_t* errc_out);

void ti_enter_critical(void);

void ti_exit_critical(void);

void ti_enter_exclusive(void);

void ti_exit_exclusive(void);

void ti_exit(void);

void ti_yield(void);

void ti_set_thread_priority(struct ti_thread_t thread, int32_t priority, enum ti_errc_t* errc_out);

int32_t ti_get_thread_priority(struct ti_thread_t thread, enum ti_errc_t* errc_out);

enum thread_state_t ti_get_thread_state(struct ti_thread_t thread, enum ti_errc_t* errc_out);

int32_t ti_get_thread_stack_size(struct ti_thread_t thread, enum ti_errc_t* errc_out);

int32_t ti_get_thread_stack_usage(struct ti_thread_t thread, enum ti_errc_t* errc_out);

struct ti_thread_t ti_get_this_thread(void);

enum ti_core_id_t ti_get_this_core(void);

bool ti_is_interrupt(void);

bool ti_is_valid_thread(struct ti_thread_t thread);

bool ti_is_thread_equal(struct ti_thread_t thread_1, struct ti_thread_t thread_2);