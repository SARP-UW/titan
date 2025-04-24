/**
 * This file is part of the Titan HAL
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
 * @file include/ti/thread.h
 * @authors Aaron McBride
 * @brief ?
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
  extern "C" {
#endif

  static const int32_t TI_THREAD_MIN_STACK_SIZE = 128;
  static const int32_t TI_THREAD_MIN_PRIORITY = 0;
  static const int32_t TI_THREAD_MAX_PRIORITY = 256;

  typedef enum {
    TI_THREAD_RUNNING,
    TI_THREAD_READY,
    TI_THREAD_SUSPENDED,
    TI_THREAD_SLEEPING,
    TI_THREAD_CRITICAL,
    TI_THREAD_STOPPED,
    TI_THREAD_NULL,
  } ti_thread_state_e;

  typedef struct {
    int32_t id;
    void* handle;
  } ti_thread_t;

  ti_thread_t ti_thread_create(void (*fn)(void*), 
      int32_t priority, void* stack, int32_t stack_size);

  bool ti_thread_destroy(ti_thread_t* thread);

  bool ti_thread_start(ti_thread_t* thread, void* arg);

  bool ti_thread_stop(ti_thread_t* thread);

  bool ti_thread_suspend(ti_thread_t* thread);
  
  bool ti_thread_resume(ti_thread_t* thread);
  
  bool ti_thread_set_priority(ti_thread_t* thread, int32_t priority);
  
  int32_t ti_thread_get_priority(ti_thread_t* thread);
  
  ti_thread_state_e ti_thread_state(ti_thread_t* thread);

  ti_thread_t ti_thread_current(void);

  bool ti_thread_equal(ti_thread_t* thread1, ti_thread_t* thread2);

  bool ti_thread_exit(void);

  bool ti_thread_sleep(uint64_t ticks);

  bool ti_thread_enter_critical(void);

  bool ti_thread_exit_critical(void);

#ifdef __cplusplus
  } // extern "C"
#endif