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
 * @file include/ti/task.c
 * @authors Aaron McBride
 * @brief Implementation of the RTOS task control interface.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "include/ti/task.h" // header
#include "src/port/STM32H745_CM7/internal/sys_util.h"
#include "src/port/STM32H745_CM7/internal/interrupt.h"
#include "src/port/STM32H745_CM7/internal/mmio.h"
#include "src/port/STM32H745_CM7/internal/compat.h"


COMPAT_FILE

#ifdef __cplusplus
  extern "C" {
#endif 

  #define TI_MAX_TASKS 32

  #define TI_TICK_FREQ 1000000

  #define TI_CPU_FREQ 400000000


  /**********************************************************************************************
   * Internal Resources
   **********************************************************************************************/

  typedef struct {
    void* stack_ptr;
    int32_t stack_size;
    int32_t instance_id;
    int32_t priority;
    ti_task_state_t state;
    uint64_t current_tick;
    int32_t await_tag;
    tcb_t* await_tcb;
    int32_t crit_depth;
  } tcb_t;


  static tcb_t tcb_mem[TI_MAX_TASKS];
  static tcb_t* current_tcb;
  static tcb_t* next_tcb;
  static int32_t rr_index;

  /**********************************************************************************************
   * ?
   **********************************************************************************************/


  /**********************************************************************************************
   * ?
   **********************************************************************************************/

  __attribute__((naked))
  void pendsv_exc_handler() {
    TI_VOLATILE_ASM (

      // Save context.
      "mrs r0, psp                \n\t"
      "tst lr, #0x10              \n\t"
      "it eq                      \n\t"
      "vstmdbeq r0!, {s16-s31}    \n\t"
      "stmdb r0!, {r4-r11, lr}    \n\t"

      // Save stack pointer.
      "ldr r1, %0                 \n\t"
      "ldr r1, [r1]               \n\t"
      "str r0, [r1]               \n\t"

      // Load stack pointer.
      "ldr r0, %1                 \n\t"
      "ldr r0, [r0]               \n\t"
      "str r0, [r1]               \n\t"
      "ldr r0, [r0]               \n\t"

      // Load context.
      "ldmia r0!, {r4-r11, lr}    \n\t"
      "tst lr, #0x10              \n\t"
      "it eq                      \n\t"
      "vldmiaeq r0!, {s16-s31}    \n\t"
      "msr psp, r0                \n\t"
      "bx lr                      \n\t"
      : 
      : "m" (&current_tcb),
        "m" (&next_tcb)
    );
  }


  void systick_exc_handler() {
    const bool crit_flag = enter_critical();
    for (int32_t i = 0; i < TI_MAX_TASKS; i++) {
      tcb_t* const tcb = &tcb_mem[i];
      if ((tcb->state == TASK_SLEEPING) ||
          (tcb->state == TASK_WAITING)) {
        tcb->current_tick--;
        if (tcb->current_tick == 0) {
          tcb->state == TASK_READY;
          if (tcb->priority > next_tcb->priority) {
            next_tcb = tcb;
          }
        }
      }
    }
    if (current_tcb == next_tcb) {
      for (int32_t i = 0; i < TI_MAX_TASKS; i++) {
        const int32_t next_rr_index = (rr_index + i) % TI_MAX_TASKS;
        tcb_t* const tcb = &tcb_mem[next_rr_index];
        if (tcb->priority == next_tcb->priority) {
          rr_index = next_rr_index;
          next_tcb = tcb;
        }
      }
    }
    if (current_tcb != next_tcb) {
      write_field(SCB_ICSR, SCB_ICSR_PENDSVSET, 1);
    }
    exit_critical(crit_flag);
  }

  /**********************************************************************************************
   * ?
   **********************************************************************************************/

  ti_task_t ti_task_create(void (*fn)(void*), void* arg, 
      int32_t priority, void* stack, int32_t stack_size) {
    static int32_t current_id = 0;
    for (int32_t i = 0; i < TI_MAX_TASKS; i++) {
      tcb_t* const tcb = &tcb_mem[i];
      if (tcb->state == TASK_DESTROYED) {
        tcb->stack_ptr = stack;
        tcb->stack_size = stack_size;
        tcb->instance_id = current_id++;
        tcb->priority = priority;
        tcb->state = TASK_READY;
        tcb->current_tick = 0;
        tcb->await_tag = 0;
        tcb->await_tcb = NULL;
        tcb->crit_depth = 0;
        return (ti_task_t) { 
          .instance_id = tcb->instance_id, 
          .handle = tcb
        };
      }
    }
    return (ti_task_t) {
      .instance_id = -1,
      .handle = NULL
    };
  }

  void ti_task_destroy(ti_task_t task) {
    
  }


  void ti_task_suspend(ti_task_t task) {
    if (valid_task(task)) {
      tcb_t* const tcb = (tcb_t*)task.handle;
      tcb->await_tag = 0;
      tcb->await_tcb = NULL;
      tcb->current_tick = 0;
      tcb->state = TASK_SUSPENDED;
      if(tcb == current_tcb) {
        write_field(SCB_ICSR, SCB_ICSR_PENDSVSET, 1);
      }
    }
  }

  void ti_task_resume(ti_task_t task) {
    tcb_t* const tcb = (tcb_t*)task.handle;
  }


  void ti_task_sleep(ti_task_t task, uint64_t ticks) {

  }

  void ti_task_wake(ti_task_t task) {

  }


  ti_await_result_t ti_task_await(ti_task_t task, ti_task_t other, uint64_t to_ticks, int32_t tag);

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