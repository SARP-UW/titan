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
 * @internal
 * @file include/ti/task.h
 * @authors Aaron McBride
 * @brief RTOS task control interface.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
  extern "C" {
#endif 

  /**********************************************************************************************
   * ?
   **********************************************************************************************/
  
  typedef enum {
    AWAIT_SUCCESS,
    AWAIT_TIMEOUT,
    AWAIT_ABORT,
    AWAIT_ERROR
  } ti_await_result_t;

  typedef enum {
    TASK_RUNNING,
    TASK_READY,
    TASK_SUSPENDED,
    TASK_SLEEPING,
    TASK_WAITING,
    TASK_DESTROYED,
  } ti_task_state_t;

  typedef struct {
    int32_t instance_id;
    void* handle;
  } ti_task_t;

  typedef void* ti_task_crit_t;

  /**********************************************************************************************
   * ?
   **********************************************************************************************/


  ti_task_t ti_task_create(void (*fn)(void*), void* arg, 
      int32_t priority, void* stack, int32_t stack_size);

  void ti_task_destroy(ti_task_t task);


  void ti_task_suspend(ti_task_t task);

  void ti_task_resume(ti_task_t task);


  void ti_task_sleep(ti_task_t task, uint64_t ticks);

  void ti_task_wake(ti_task_t task);


  ti_await_result_t ti_task_await(ti_task_t task, 
      ti_task_t other, uint64_t to_ticks, int32_t tag);

  void ti_task_continue(ti_task_t task);

  void ti_task_raise(ti_task_t task, int32_t tag);


  void ti_task_set_priority(ti_task_t task, int32_t priority);

  int32_t ti_task_get_priority(ti_task_t task);


  ti_task_crit_t ti_task_enter_critical(void);

  void ti_task_exit_critical(ti_task_crit_t entry_handle);
  

  ti_task_state_t ti_task_get_state(ti_task_t task);

  ti_task_t ti_task_get_self(void);

  bool ti_task_equal(ti_task_t task1, ti_task_t task2);

  void ti_task_yeild(void);

 
#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */