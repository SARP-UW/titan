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
 * @file src/STM32H745_CM7/thread.c
 * @authors Aaron McBride
 * @brief ?
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "include/ti/thread.h" // header
#include "include/ti/lib_config.h"
#include "src/STM32H745_CM7/interrupt.h"
#include "src/STM32H745_CM7/mmio.h"
#include "src/STM32H745_CM7/device_config.h"

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Implementation Resources
   ************************************************************************************************/

  // Layout of basic stack frame.
  // Used when initializing a new thread.
  typedef struct {
    uint32_t xPSR;
    uint32_t PC;
    uint32_t LR;
    uint32_t other[4];
    uint32_t arg;
    uint32_t other[8];
  } init_frame_t;

  // Thread control block 
  // Defines the state of a thread.
  typedef struct {
    void* sp;
    void* stack_base;
    int32_t stack_size;
    void (*fn)(void*);
    int32_t id;
    int32_t priority;
    ti_thread_state_e state;
    uint64_t current_tick;
    int32_t crit_depth;
  } tcb_t;

  // Initial xPSR value (used when initializing first stack frame)
  static const uint32_t _INIT_xPSR_VALUE = 0x01000000U;

  // Mask for extracting the IPSR value from xPSR.
  static const uint32_t _IPSR_MASK = 0x1FFU;

  // Array of thread control blocks.
  static tcb_t _tcb_array[TI_THREAD_MAX_THREADS];

  // Pointer to active thread control block.
  static tcb_t* _active_tcb;

  // Scheduler tick counter.
  static uint32_t _sched_tick = 0U;

  // Memory for idle thread stack.
  static uint8_t _idle_mem[TI_THREAD_MIN_STACK_SIZE];

  // Pointer to idle thread tcb.
  static tcb_t* _idle_tcb;

  /************************************************************************************************
   * Internal Functions
   ************************************************************************************************/

  // Idle thread - runs when no other threads are active.
  static void _idle_thread(void*) {
    while (1) {
      __asm__ ("wfi");
    }
  }

  // Enters a critical section in kernal code
  __attribute__((warn_unused_result))
  static bool _kernal_enter_critical(void) {
    uint32_t primask_value;
    __asm__ volatile ("mrs %0, primask" : "=r" (primask_value));
    __asm__ volatile ("cpsid i" ::: "memory");
    return true;
  }

  // Exits a critical section in kernal code
  static void _kernal_exit_critical(bool entry_flag) {
    if (entry_flag) {
      __asm__ volatile ("cpsie i" ::: "memory");
    }
  }

  // Gets the thread control block corresponding to the specified thread.
  static tcb_t* _get_tcb(ti_thread_t* thread) {
    return thread ? (tcb_t*)thread->handle : _active_tcb;
  }

  // Scheduler - updates the active thread.
  static bool _schedule_threads(void) {
    tcb_t* next_tcb = NULL;
    int32_t max_priority = -1;
    for (int32_t i = 0; i < TI_THREAD_MAX_THREADS; i += 1) {
      tcb_t* const tcb = &_tcb_array[i];
      if ((tcb->state == TI_THREAD_RUNNING) || (tcb->state == TI_THREAD_READY)) {
        const int32_t cur_priority = tcb->priority + (int32_t)tcb->current_tick;
        #if TI_THREAD_STRICT_PRIORITY
          if (!next_tcb || (cur_priority > max_priority) ||
              (tcb->priority > next_tcb->priority)) {
        #else
          if (!next_tcb || (cur_priority > max_priority)) {
        #endif
          max_priority = cur_priority;
          next_tcb = tcb;
        }
      }
    }
    if (_active_tcb == next_tcb) {
      return false;
    }
    if (_active_tcb->state == TI_THREAD_RUNNING) {
      _active_tcb->state = TI_THREAD_READY;
    }
    next_tcb->state = TI_THREAD_RUNNING;
    _active_tcb->current_tick = 0U;
    _active_tcb = next_tcb;
    return true;
  }

  /************************************************************************************************
   * Exception Handlers
   ************************************************************************************************/

  // PendSV handler - switches context.
  __attribute__((naked))
  void pendsv_exc_handler(void) {
    __asm__ volatile (

      // Save previous tcb
      "CPSID i                 \n\t"
      "ldr r1, %0              \n\t"
      "stmdb sp!, {r1}         \n\t"

      // Schedule next thread
      "bl _schedule_threads    \n\t"
      "ldmia sp!, {r1}         \n\t"
      "cbz r0, end             \n\t"

      // Save context
      "mrs r0, psp             \n\t"
      "tst lr, #0x10           \n\t"
      "it eq                   \n\t"
      "vstmdbeq r0!, {s16-s31} \n\t"
      "stmdb r0!, {r4-r11, lr} \n\t"

      // Save stack pointer
      "ldr r1, [r1]            \n\t"
      "str r0, [r1]            \n\t"

      // Load stack pointer
      "ldr r0, %0              \n\t"
      "ldr r0, [r0]            \n\t"
      "ldr r0, [r0]            \n\t"

      // Load context
      "msr psp, r0             \n\t"
      "ldmia r0!, {r4-r11, lr} \n\t"
      "tst lr, #0x10           \n\t"
      "it eq                   \n\t"
      "vldmiaeq r0!, {s16-s31} \n\t"

      // Return from handler
      "end:                    \n\t"
      "CPSIE i                 \n\t"
      "bx lr                   \n\t"
      : 
      : "i" (&_active_tcb)
      : "memory"
    );
  }

  // Systick handler - updates thread tick values.
  void systick_exc_handler(void) {
    _sched_tick += 1U;
    if (_sched_tick >= (TI_THREAD_SCHED_FREQ / TI_THREAD_TICK_FREQ)) {
      _sched_tick = 0U;
    }
    bool sched_update_flag = false;
    for (int32_t i = 0; i < TI_THREAD_MAX_THREADS; i += 1) {
      tcb_t* const tcb = &_tcb_array[i];
      if (tcb->state == TI_THREAD_SLEEPING) {
        tcb->current_tick -= 1U;
        if (tcb->current_tick == 0U) {
          tcb->state = TI_THREAD_READY;
          sched_update_flag = true;
        }
      } else if ((_sched_tick == 0U) && (tcb != _idle_tcb) &&
          (tcb->state == TI_THREAD_READY)) {
        tcb->current_tick += 1U;
        sched_update_flag = true;
      }
    }
    if (sched_update_flag) {
      WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    }
  }

  /************************************************************************************************
   * Initialization and De-initialization Functions
   ************************************************************************************************/

  // Initializes threading system
  void init_thread_sys(void) {
    for (int32_t i = 0; i < TI_THREAD_MAX_THREADS; i += 1) {
      _tcb_array[i] = (tcb_t) {
        .sp = NULL,
        .stack_base = NULL,
        .stack_size = 0,
        .fn = NULL,
        .id = 0,
        .priority = TI_THREAD_MIN_PRIORITY,
        .state = TI_THREAD_NULL,
        .current_tick = 0U,
        .crit_depth = 0
      };
    }
    ti_thread_t idle_thread = ti_thread_create(
        &_idle_thread, 
        TI_THREAD_MIN_PRIORITY, 
        &_idle_mem, 
        TI_THREAD_MIN_STACK_SIZE
    );
    _idle_tcb = (tcb_t*)idle_thread.handle;
    _idle_tcb->priority -= 1;
    const uint32_t reload_value = (TI_CLK_CPU_FREQ / TI_THREAD_TICK_FREQ) - 1;

    // Set up systick timer
    WRITE_FIELD(SYST_RVR, SYST_RVR_RELOAD, reload_value);
    WRITE_FIELD(SYST_CSR, SYST_CSR_TICKINT, 1U);
    WRITE_FIELD(SYST_CSR, SYST_CSR_ENABLE, 1U);

    // Set priority of systick and pendsv interrupts (lowest possible).
    WRITE_FIELD(SCB_SHPRx[3], SCB_SHPRx_PRI_x[SYSTICK_EXC_NUM], UINTMAX_MAX);
    WRITE_FIELD(SCB_SHPRx[3], SCB_SHPRx_PRI_x[PENDSV_EXC_NUM], UINTMAX_MAX);
  }

  // De-initializes threading system 
  void deinit_thread_sys(void) {
    WRITE_FIELD(SYST_CSR, SYST_CSR_ENABLE, 0U);
  }

  /************************************************************************************************
   * Implementation of Thread Functions
   ************************************************************************************************/

  ti_thread_t ti_thread_create(void (*fn)(void*), int32_t priority, 
      void* stack, int32_t stack_size) { 
    static int32_t current_id = 0;
    const bool crit_flag = _kernal_enter_critical();
    if (fn && stack && (priority > TI_THREAD_MIN_PRIORITY) &&
        (priority < TI_THREAD_MAX_PRIORITY) && 
        (stack_size < TI_THREAD_MIN_STACK_SIZE)) {
      for (int32_t i = 0; i < TI_THREAD_MAX_THREADS; i++) {
        tcb_t* const tcb = &_tcb_array[i];
        if (tcb->state == TI_THREAD_NULL) {
          tcb->sp = NULL,
          tcb->stack_base = stack;
          tcb->stack_size = stack_size;
          tcb->fn = fn;
          tcb->id = current_id++;
          tcb->priority = priority;
          tcb->state = TI_THREAD_STOPPED;
          tcb->current_tick = 0U;
          _kernal_exit_critical(crit_flag);
          return (ti_thread_t) {
            .handle = tcb,
            .id = tcb->id
          };
        }
      }
    }
    _kernal_exit_critical(crit_flag);
    return (ti_thread_t) {
      .handle = NULL,
      .id = -1
    };
  }

  bool ti_thread_destroy(ti_thread_t* thread) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(thread);
    if ((state == TI_THREAD_NULL) || 
        (state == TI_THREAD_CRITICAL)) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    tcb_t* const tcb = _get_tcb(thread);
    tcb->state = TI_THREAD_NULL;
    if (tcb == _active_tcb) {
      WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    }
    _kernal_exit_critical(crit_flag);
    return true;
  }

  bool ti_thread_start(ti_thread_t* thread, void* arg) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(thread);
    if ((state == TI_THREAD_NULL) || 
        (state == TI_THREAD_CRITICAL)) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    tcb_t* const tcb = _get_tcb(thread);
    tcb->sp = (void*)((uint8_t*)tcb->stack_base + 
    (tcb->stack_size - (int32_t)sizeof(init_frame_t)));
    tcb->state = TI_THREAD_READY;
    tcb->current_tick = 0U;
    for (int32_t i = 0; i < tcb->stack_size; i++) {
      ((uint8_t*)tcb->stack_base)[i] = 0U;
    }
    init_frame_t* const init_frame = (init_frame_t*)tcb->sp;
    init_frame->xPSR = _INIT_xPSR_VALUE;
    init_frame->PC = (uint32_t)tcb->fn;
    init_frame->LR = (uint32_t)ti_thread_exit;
    init_frame->arg = (uint32_t)arg;
    WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    _kernal_exit_critical(crit_flag);
    return true;
  }

  bool ti_thread_stop(ti_thread_t* thread) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(thread);
    if ((state == TI_THREAD_NULL) || 
        (state == TI_THREAD_CRITICAL)) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    tcb_t* const tcb = _get_tcb(thread);
    tcb->state = TI_THREAD_STOPPED;
    if (tcb == _active_tcb) {
      WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    }
    _kernal_exit_critical(crit_flag);
    return true;
  }

  bool ti_thread_suspend(ti_thread_t* thread) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(thread);
    if ((state == TI_THREAD_NULL) || 
        (state == TI_THREAD_STOPPED) ||
        (state == TI_THREAD_CRITICAL)) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    tcb_t* const tcb = _get_tcb(thread);
    tcb->state = TI_THREAD_SUSPENDED;
    if (tcb == _active_tcb) {
      WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    }
    _kernal_exit_critical(crit_flag);
    return true;
  }

  bool ti_thread_resume(ti_thread_t* thread) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(thread);
    if (state != TI_THREAD_SUSPENDED) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    tcb_t* const tcb = _get_tcb(thread);
    tcb->state = TI_THREAD_READY;
    tcb->current_tick = 0U;
    WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    _kernal_exit_critical(crit_flag);
    return true;
  }

  bool ti_thread_set_priority(ti_thread_t* thread, int32_t priority) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(thread);
    if ((priority < TI_THREAD_MIN_PRIORITY) || 
        (priority > TI_THREAD_MAX_PRIORITY) ||
        (state == TI_THREAD_NULL)) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    _get_tcb(thread)->priority = priority;
    WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    _kernal_exit_critical(crit_flag);
    return true;
  }

  int32_t ti_thread_get_priority(ti_thread_t* thread) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(thread);
    if (state == TI_THREAD_NULL) {
      _kernal_exit_critical(crit_flag);
      return -1;
    }
    const int32_t priority = _get_tcb(thread)->priority;
    _kernal_exit_critical(crit_flag);
    return priority;
  }

  ti_thread_state_e ti_thread_state(ti_thread_t* thread) {
    const bool crit_flag = _kernal_enter_critical();
    const uint32_t ispr_value;
    __asm__ volatile ("mrs %0, IPSR" : "=r" (ispr_value));
    tcb_t* const tcb = _get_tcb(thread);
    if (!tcb || (thread->id != tcb->id) || (ispr_value != 0U)) {
      _kernal_exit_critical(crit_flag);
      return TI_THREAD_NULL;
    }
    const ti_thread_state_e state = tcb->state;
    _kernal_exit_critical(crit_flag);
    return state;
  }

  ti_thread_t ti_thread_current(void) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(NULL);
    if (state == TI_THREAD_NULL) {
      _kernal_exit_critical(crit_flag);
      return (ti_thread_t) {
        .handle = NULL,
        .id = -1
      };
    }
    _kernal_exit_critical(crit_flag);
    return (ti_thread_t) {
      .handle = _active_tcb,
      .id = _active_tcb->id
    };
  }

  bool ti_thread_equal(ti_thread_t* thread1, ti_thread_t* thread2) {
    return (thread1->handle == thread2->handle) && 
        (thread1->id == thread2->id);
  }

  bool ti_thread_exit(void) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(NULL);
    if ((state == TI_THREAD_CRITICAL) ||
        (state == TI_THREAD_NULL)) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    _get_tcb(NULL)->state = TI_THREAD_STOPPED;
    WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    _kernal_exit_critical(crit_flag);
    return true;
  }

  bool ti_thread_sleep(uint64_t ticks) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(NULL);
    if ((state == TI_THREAD_CRITICAL) ||
        (state == TI_THREAD_NULL)) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    tcb_t* const tcb = _get_tcb(NULL);
    tcb->state = TI_THREAD_SLEEPING;
    tcb->current_tick = ticks;
    WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    _kernal_exit_critical(crit_flag);
    return true;
  }
 
  bool ti_thread_enter_critical(void) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(NULL);
    if (state == TI_THREAD_NULL) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    tcb_t* const tcb = _get_tcb(NULL);
    tcb->state = TI_THREAD_CRITICAL;
    tcb->crit_depth += 1;
    return true;
  }

  bool ti_thread_exit_critical(void) {
    const bool crit_flag = _kernal_enter_critical();
    const ti_thread_state_e state = ti_thread_state(NULL);
    if ((state == TI_THREAD_NULL) || 
        (state == TI_THREAD_CRITICAL)) {
      _kernal_exit_critical(crit_flag);
      return false;
    }
    tcb_t* const tcb = _get_tcb(NULL);
    tcb->crit_depth -= 1;
    if (tcb->crit_depth == 0) {
      tcb->state = TI_THREAD_READY;
      __asm__ volatile ("cpsie i" ::: "memory");
    }
    WRITE_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET, 1U);
    return true;
  }

#ifdef __cplusplus
  } // extern "C"
#endif