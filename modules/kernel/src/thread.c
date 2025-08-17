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
 * @file modules/kernel/src/thread.c
 * @authors Aaron McBride
 * @brief Implementation of thread management and control utilities.
 */

#pragma once
#include "kernel/thread.h"

/**************************************************************************************************
 * @section Internal Utilities
 **************************************************************************************************/

typedef struct {
  void* sp;
  int32_t stack_size;
  int32_t id;
  thread_entry_fn_t entry_fn;
  int32_t priority;
  thread_state_e state;
  int32_t crit_depth;
  int32_t sched_count;
} tcb_t;

tcb_t* tcb_table[MAX_THREAD_COUNT];



/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/

