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
 * @file include/ti/exec.h
 * @authors Aaron McBride
 * @brief Execution control facilities.
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
    THREAD_RUNNING,
    THREAD_READY,
    THREAD_SUSPENDED,
    THREAD_SLEEPING,
    THREAD_DEAD
  } ti_thread_state_t;

  typedef struct {
    int32_t id;
    void* handle;
  } ti_thread_t;


  ti_thread_t ti_thread_enter(void (*fn)(void*), void* arg, int32_t priority);

  void ti_thread_exit(ti_thread_t* thread);



  void ti_thread_suspend(ti_thread_t* thread);

  void ti_thread_resume(ti_thread_t* thread);



  void ti_thread_sleep(ti_thread_t* thread, uint64_t ticks);

  void ti_thread_wake(ti_thread_t* thread);



  void ti_thread_yeild(ti_thread_t* thread);



  void ti_thread_set_priority(ti_thread_t* thread, int32_t priority);

  int32_t ti_thread_get_priority(ti_thread_t* thread);



  void ti_thread_enter_critical(void);

  void ti_thread_exit_critical(void);

  bool ti_thread_is_critical(void);



  ti_thread_state_t ti_thread_state(ti_thread_t* thread);



  ti_thread_t ti_thread_self(void);



  ti_thread_t ti_thread_valid(void);





  




 
#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */