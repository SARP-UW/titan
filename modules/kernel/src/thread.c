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
#include <string.h>
#include "kernel/thread.h" // header
#include "kernel/sys.h"
#include "internal/mmio.h"
#include "util/core.h"
#include "util/atomic.h"
#include "util/math.h"
#include "util/macro.h"
#include "kernel/critlock.h"

#ifndef TI_CFG_MAX_THREADS
  #define TI_CFG_MAX_THREADS 16
#endif

#ifndef TI_CFG_MAX_THREAD_PRIORITY
  #define TI_CFG_MAX_THREAD_PRIORITY 32
#endif

// Internal thread information struct
struct _int_thread_t {
  void* sp;
  int32_t id;
  void* stack_base;
  int32_t stack_size;
  int32_t priority;
  enum ti_thread_state_t state;
  int32_t sched_count;
};

// Struct representing layout of hardware stack frame
__attribute__((packed))
struct _hw_frame_t {
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r12;
  uint32_t lr;
  uint32_t pc;
  uint32_t xpsr;
};

// Struct representing layout of software stack frame
__attribute__((packed))
struct _sw_frame_t {
    uint32_t r4;
    uint32_t r5;
    uint32_t r6;
    uint32_t r7;
    uint32_t r8;
    uint32_t r9;
    uint32_t r10;
    uint32_t r11;
    uint32_t exc_return;
};

// Required alignment for stack pointer
static const int32_t _SYS_STACK_ALIGN = 8;

// Initial value of XPSR register for new threads
static const int32_t _INIT_XPSR_VALUE = 0x01000000;

// Initial value of exc_return for new threads
static const int32_t _INIT_EXC_RETURN_VALUE = 0xFFFFFFFD;

// Size of "full" stack frame (hw + sw)
static const int32_t _FULL_FRAME_SIZE = sizeof(struct _hw_frame_t) + sizeof(struct _sw_frame_t);

// List of existing threads
static struct _int_thread_t* _thread_list[TI_CFG_MAX_THREADS] = {NULL};

// Current thread running on CM7/CM4 core
static struct _int_thread_t* _cm7_thread = NULL;
static struct _int_thread_t* _cm4_thread = NULL;

// Memory for thread edit critlock
static uint8_t _thread_critlock_mem[TI_CRITLOCK_MEM_SIZE] = {0};

// Critlock for editing internal thread structures and thread list
static struct ti_critlock_t _thread_critlock = TI_INVALID_CRITLOCK;

// Unique thread ID counter (start at non-zero value to reduce chance of collision)
static int32_t _next_thread_id = 123;

#define _SCHEDULE_THREADS_IMPL(core_token, other_core_token) \
  static void _schedule_threads_##core_token(void) { \
    while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U)); \
    if ((_##core_token##_thread != NULL) && (_##core_token##_thread->state == TI_THREAD_STATE_RUNNING)) { \
      _##core_token##_thread->state = TI_THREAD_STATE_READY; \
    } \
    _##core_token##_thread = NULL; \
    struct _int_thread_t* next_thread = NULL; \
    TI_FOREACH(cur_thread, _thread_list) { \
      if (*cur_thread != NULL) { \
        (*cur_thread)->sched_count += (*cur_thread)->priority; \
      } \
    } \
    TI_FOREACH(cur_thread, _thread_list) { \
      if ((*cur_thread != NULL) && ((*cur_thread)->state == TI_THREAD_STATE_READY)) { \
        if (next_thread == NULL) { \
          next_thread = *cur_thread; \
        } else if ((*cur_thread)->sched_count > next_thread->sched_count) { \
          next_thread = *cur_thread; \
        } \
      } \
    } \
    if (next_thread != NULL) { \
      next_thread->state = TI_THREAD_STATE_RUNNING; \
      next_thread->sched_count = 0; \
      _##core_token##_thread = next_thread; \
    } \
    ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U); \
  }

// Declare scheduler function for CM7 and CM4 cores
_SCHEDULE_THREADS_IMPL(cm7, cm4)
_SCHEDULE_THREADS_IMPL(cm4, cm7)

// Idle function (used when no threads are running)
__attribute__((naked, optimize("O0")))
static void _idle_fn(void) {
  asm volatile (
    "loop: \n\t"
    "wfi \n\t"
    "b loop \n\t"
    :::
  );
}

// PendSV exception handler (context switcher for threads)
#define _PENDSV_EXC_HANDLER_IMPL(core_token) \
  __attribute__((naked, optimize("O0"))) \
  static void cm7_pendsv_exc_handler(void) { \
    asm volatile( \
      \
      /* Load in stack pointer from internal thread struct */ \
      TI_STR(ldr r3, =_##core_token##_thread \n\t) \
      "ldr r2, [r3] \n\t" \
      \
      /* If current thread is idle - skip saving context */ \
      "movs r12, #0     \n\t" \
      "cbz r2, schedule \n\t" \
      "movs r12, #1     \n\t" \
      \
      /* Save context of current thread (push registers to stack) */ \
      "mrs r0, psp             \n\t" \ 
      "isb                     \n\t" \
      "tst lr, #0x10           \n\t" \
      "it eq                   \n\t" \
      "vstmdbeq r0!, {s16-s31} \n\t" \
      "stmdb r0!, {r4-r11, lr} \n\t" \
      "str r0, [r2]            \n\t" \
      \
      /* Invoke thread scheduler function */ \
      "schedule:       \n\t" \
      "mrs r1, primask \n\t" \
      "cpsid i         \n\t" \
      "dsb             \n\t" \
      "isb             \n\t" \
      TI_STR(bl _schedule_threads_##core_token \n\t) \
      "dsb             \n\t" \
      "isb             \n\t" \
      "msr primask, r1 \n\t" \
      \
      /* Load in stack pointer of next thread */ \
      TI_STR(ldr r3, =_##core_thread##_thread \n\t) \
      "ldr r1, [r3] \n\t" \
      \
      /* If next thread is NULL - dont restore context from stack */ \
      "cbz r1, restore_idle \n\t" \
      \
      /* Restore context of next thread (pull registers from stack) */ \
      "ldr r0, [r1]            \n\t" \
      "ldmia r0!, {r4-r11, lr} \n\t" \
      "tst lr, #0x10           \n\t" \
      "it eq                   \n\t" \
      "vldmiaeq r0!, {s16-s31} \n\t" \
      "msr psp, r0             \n\t" \
      "isb                     \n\t" \
      "bx lr                   \n\t" \
      \
      /* Create context for idle thread (not from stack) */ \
      "restore_idle:       \n\t" \
      "ldr r0, =_idle_fn   \n\t" \
      "mrs r1, msp         \n\t" \
      "sub r1, r1, #32     \n\t" \
      "str r0, [r1, #24]   \n\t" \
      "ldr r0, =0x01000000 \n\t" \
      "str r0, [r1, #28]   \n\t" \
      "msr msp, r1         \n\t" \
      "ldr r0, =0xFFFFFFF9 \n\t" \
      "mov lr, r0          \n\t" \
      "bx lr               \n\t" \
      \
      ::: "r0","r1","r2","r3","r12","memory" \
    ); \
  }

// Declare pendsv handler for CM7 and CM4 cores
_PENDSV_EXC_HANDLER_IMPL(cm7)
_PENDSV_EXC_HANDLER_IMPL(cm4)

// Exit point for threads
static void _thread_exit(void) {
  // TODO
}

// Initialization function for threading system (invoked from startup.c)
bool _ti_init_thread(void) {
  enum ti_errc_t int_errc;
  _thread_critlock = ti_create_critlock(_thread_critlock_mem, &int_errc);
  return int_errc == TI_ERRC_NONE;
}

struct ti_thread_t ti_create_thread(void* const mem, void (*const entry_fn)(void*), void* const arg, int32_t stack_size, const int32_t priority, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!mem || !entry_fn || (stack_size < TI_THREAD_MIN_STACK_SIZE) || (priority < 1) || (priority > TI_CFG_MAX_THREAD_PRIORITY)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return TI_INVALID_THREAD;
  }
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)(mem + stack_size);
  int_thread->sp = (void*)ti_floor_u32((uint32_t)mem + stack_size, _SYS_STACK_ALIGN, &(enum ti_errc_t){0}) - _FULL_FRAME_SIZE;
  int_thread->id = (int32_t)ti_atomic_add((uint32_t*)&_next_thread_id, 1U);
  int_thread->stack_base = mem;
  int_thread->stack_size = stack_size;
  int_thread->priority = priority;
  int_thread->state = TI_THREAD_STATE_READY;
  int_thread->sched_count = 0;
  memset(int_thread->sp, 0, _FULL_FRAME_SIZE);
  // Initialize stack frame so that when context switcher loads it into registers it enters the new thread
  struct _hw_frame_t* const hw_frame = (struct _hw_frame_t*)(int_thread->sp + sizeof(struct _sw_frame_t));
  hw_frame->r0 = (uint32_t)arg;
  hw_frame->pc = (uint32_t)entry_fn;
  hw_frame->lr = (uint32_t)&_thread_exit;
  hw_frame->xpsr = _INIT_XPSR_VALUE;
  struct _sw_frame_t* const sw_frame = (struct _sw_frame_t*)int_thread->sp;
  sw_frame->exc_return = _INIT_EXC_RETURN_VALUE;
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  bool entry_found = false;
  TI_FOREACH(cur_thread, _thread_list) {
    if (*cur_thread == NULL) {
      *cur_thread = int_thread;
      entry_found = true;
      break;
    }
  }
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
  if (!entry_found) {
    *errc_out = TI_ERRC_NO_MEM;
    return TI_INVALID_THREAD;
  }
  return (struct ti_thread_t) {
    .id = int_thread->id,
    .handle = int_thread,
  };
}

void ti_destroy_thread(const struct ti_thread_t thread, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  if (int_thread->state != TI_THREAD_STATE_STOPPED) {
    ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
    ti_exit_critical();
    *errc_out = TI_ERRC_INVALID_STATE;
    return;
  }
  TI_FOREACH(cur_thread, _thread_list) {
    if (*cur_thread == int_thread) {
      *cur_thread = NULL;
      break;
    }
  }
  int_thread->id = -1;
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
}

void ti_suspend_thread(const struct ti_thread_t thread, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  if ((int_thread->state != TI_THREAD_STATE_READY) && (int_thread->state != TI_THREAD_STATE_RUNNING)) {
    *errc_out = TI_ERRC_INVALID_STATE;
    ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
    ti_exit_critical();
    return;
  }
  int_thread->state = TI_THREAD_STATE_SUSPENDED;
  if (ti_get_this_thread().id == thread.id) {
    SET_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET);
  }
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
}

void ti_resume_thread(const struct ti_thread_t thread, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  if (int_thread->state != TI_THREAD_STATE_SUSPENDED) {
    ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
    ti_exit_critical();
    *errc_out = TI_ERRC_INVALID_STATE;
    return;
  }
  int_thread->state = TI_THREAD_STATE_READY;
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
}

void ti_exit(void) {
  if (ti_is_interrupt()) {
    asm volatile (
      "mov lr, #0xFFFFFFF9 \n\t"
      "bx lr               \n\t"
      ::: "lr"
    );
  } else {
    ti_enter_critical();
    while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
    struct _int_thread_t* cur_thread = (ti_get_this_core() == TI_CORE_ID_CM7) ? _cm7_thread : _cm4_thread;
    cur_thread->state = TI_THREAD_STATE_STOPPED;
    SET_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET);
    ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
    ti_exit_critical();
  }
}

void ti_yield(void) {
  if (!ti_is_interrupt()) {
    SET_FIELD(SCB_ICSR, SCB_ICSR_PENDSVSET);
  }
}

void ti_set_thread_priority(const struct ti_thread_t thread, const int32_t priority, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread) || (priority < 1) || (priority > TI_CFG_MAX_THREAD_PRIORITY)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  int_thread->priority = priority;
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
}

int32_t ti_get_thread_priority(const struct ti_thread_t thread, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return -1;
  }
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  const int32_t priority = int_thread->priority;
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
  return priority;
}

enum ti_thread_state_t ti_get_thread_state(const struct ti_thread_t thread, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return -1;
  }
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  const enum ti_thread_state_t state = int_thread->state;
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
  return state;
}

int32_t ti_get_thread_stack_size(const struct ti_thread_t thread, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return -1;
  }
  // No need to acquire lock - stack size is immutable
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  return int_thread->stack_size;
}

int32_t ti_get_thread_stack_usage(const struct ti_thread_t thread, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return -1;
  }
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  const int32_t sp_offset = (int32_t)((uint32_t)int_thread->sp - (uint32_t)int_thread->stack_base);
  const int32_t stack_usage = int_thread->stack_size - sp_offset;
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
  return stack_usage;
}

bool ti_is_thread_overflow(const struct ti_thread_t thread, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_thread(thread)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return false;
  }
  ti_enter_critical();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_thread_edit_lock, &(uint32_t){0U}, 1U));
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  const bool is_overflow = (uint32_t)int_thread->sp < (uint32_t)int_thread->stack_base;
  ti_atomic_store((uint32_t*)&_thread_edit_lock, 0U);
  ti_exit_critical();
  return is_overflow;
}

struct ti_thread_t ti_get_this_thread(void) {
  if (ti_is_interrupt()) {
    return TI_INVALID_THREAD;
  }
  // No need to acquire lock, function will only execute if _cm7/cm4_thread is set 
  struct _int_thread_t* const this_thread = (ti_get_this_core() == TI_CORE_ID_CM7) ? _cm7_thread : _cm4_thread;
  if (this_thread == NULL) {
    return TI_INVALID_THREAD;
  }
  return (struct ti_thread_t) {
    .id = this_thread->id,
    .handle = this_thread,
  };
}

bool ti_is_valid_thread(struct ti_thread_t thread) {
  if (thread.id < 0 || thread.handle == NULL) {
    return false;
  }
  struct _int_thread_t* const int_thread = (struct _int_thread_t*)thread.handle;
  return thread.id == int_thread->id;
}

bool ti_is_thread_equal(struct ti_thread_t thread_1, struct ti_thread_t thread_2) {
  return (thread_1.id == thread_2.id) && (thread_1.handle == thread_2.handle);
}