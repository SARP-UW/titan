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
 * @file modules/kernel/src/sys.c
 * @authors Aaron McBride
 * @brief Implementation of general system utilities.
 */

#include "kernel/sys.h"
#include "internal/mmio.h"
#include "util/atomic.h"
#include "kernel/time.h"
#include "ti_config.h"

#ifndef TI_CFG_EXCLUSIVE_SECTION_TIMEOUT
  #define TI_CFG_EXCLUSIVE_SECTION_TIMEOUT 1000000
#endif

#ifndef TI_CFG_EXCLUSIVE_SECTION_ACK_TIMEOUT
  #define TI_CFG_EXCLUSIVE_SECTION_ACK_TIMEOUT 10000
#endif

#ifndef TI_CFG_EXCLUSIVE_SECTION_LOCK_TIMEOUT
  #define TI_CFG_EXCLUSIVE_SECTION_LOCK_TIMEOUT 1000
#endif

// "Key" value for VECTKEY field to allow writes to AIRCR
const static uint32_t _RESET_VECTKEY_VALUE = 0x5FA;

// Part number for CM7 core (stored in CPUID)
const static uint32_t _CM7_PARTNO = 0xC27;

// Critical section nesting counters for CM7/CM4 core
static int32_t _cm7_critical_count = 0;
static int32_t _cm4_critical_count = 0;

// Exclusive section nesting counters for CM7/CM4 core
static int32_t _cm7_exclusive_count = 0;
static int32_t _cm4_exclusive_count = 0;

// Lock variable for modification of above exclusive section counters
static int32_t _exclusive_lock = 0;

// Shutdown acknowledgment variables for CM7/CM4 core
static int32_t _cm7_shutdown_flag = 0;
static int32_t _cm4_shutdown_flag = 0;

// Gets the critical count for the core this function is running on.
static int32_t* _get_critical_count(void) {
  return ti_get_core() == TI_CORE_ID_CM7 ? &_cm7_critical_count : &_cm4_critical_count;
}

// Gets the exclusive count for the core this function is running on.
static int32_t* _get_this_exclusive_count(void) {
  return ti_get_core() == TI_CORE_ID_CM7 ? &_cm7_exclusive_count : &_cm4_exclusive_count;
}

// Gets the exclusive count for the core this function is NOT running on.
static int32_t* _get_alt_exclusive_count(void) {
  return ti_get_core() == TI_CORE_ID_CM7 ? &_cm4_exclusive_count : &_cm7_exclusive_count;
}

// Gets the shutdown flag for the core this function is running on.
static int32_t* _get_this_shutdown_flag(void) {
  return ti_get_core() == TI_CORE_ID_CM7 ? &_cm7_shutdown_flag : &_cm4_shutdown_flag;
}

// Gets the shutdown flag for the core this function is NOT running on.
static int32_t* _get_alt_shutdown_flag(void) {
  return ti_get_core() == TI_CORE_ID_CM7 ? &_cm4_shutdown_flag : &_cm7_shutdown_flag;
}

// Attempts to acquire the exclusive section lock, returns true if successful (false if timeout).
static bool _acq_exclusive_lock(void) {
  const int64_t start_time = ti_get_time();
  while (!ti_atomic_cmp_exchange((uint32_t*)&_exclusive_lock, &(uint32_t){0}, 1U)) {
    if ((ti_get_time() - start_time) > TI_CFG_EXCLUSIVE_SECTION_LOCK_TIMEOUT) {
      return false;
    }
  }
  return true;
}

// Executes shutdown sequence for the CM7 core
__attribute__((noreturn))
static void _exec_cm7_shutdown(void) {
  typedef void (*kernel_exit_fn_t)(void);
  extern kernel_exit_fn_t* __ti_kernel_cm7_exit_array_start;
  extern kernel_exit_fn_t* __ti_kernel_cm7_exit_array_end;
  kernel_exit_fn_t* cur_kernel_fn = __ti_kernel_cm7_exit_array_start;
  while (cur_kernel_fn < __ti_kernel_cm7_exit_array_end) {
    (*cur_kernel_fn)();
    cur_kernel_fn++;
  }
  typedef void (*mcu_exit_fn_t)(void);
  extern mcu_exit_fn_t* __mcu_exit_array_start;
  extern mcu_exit_fn_t* __mcu_exit_array_end;
  mcu_exit_fn_t* cur_mcu_fn = __mcu_exit_array_start;
  while (cur_mcu_fn < __mcu_exit_array_end) {
    (*cur_mcu_fn)();
    cur_mcu_fn++;
  }
  SET_FIELD(SCB_SCR, SCB_SCR_SLEEPDEEP);
  asm volatile (
    "dsb \n\t"
    "isb \n\t"
  );
  while (true) {
    asm volatile ("wfe");
  }
}

// Executes shutdown sequence for the CM4 core
__attribute__((noreturn))
static void _exec_cm4_shutdown(void) {
  typedef void (*kernel_exit_fn_t)(void);
  extern kernel_exit_fn_t* __ti_kernel_cm4_exit_array_start;
  extern kernel_exit_fn_t* __ti_kernel_cm4_exit_array_end;
  kernel_exit_fn_t* cur_fn = __ti_kernel_cm4_exit_array_start;
  ti_enter_critical();
  while (cur_fn < __ti_kernel_cm4_exit_array_end) {
    (*cur_fn)();
    cur_fn++;
  }
  SET_FIELD(SCB_SCR, SCB_SCR_SLEEPDEEP);
  asm volatile (
    "dsb \n\t"
    "isb \n\t"
  );
  while (true) {
    asm volatile ("wfe");
  }
}

// Gets the shutdown function for the core this function is running on.
typedef void (*_shutdown_fn_t)(void);
static _shutdown_fn_t _get_this_shutdown_fn(void) {
  return ti_get_core() == TI_CORE_ID_CM7 ? &_exec_cm7_shutdown : &_exec_cm4_shutdown;
}

// Implementation of exclusive section update handler for CM7/CM4 core
#define _EXCLUSIVE_UPDATE_IMPL(this_core_name, alt_core_name) \
  ti_enter_critical(); \
  if (_acq_exclusive_lock()) { \
    if (_##alt_core_name##_exclusive_count > 0) { \
      _##this_core_name##_exclusive_count = -1; \
      const int64_t start_time = ti_get_time(); \
      while (_##alt_core_name##_exclusive_count > 0) { \
        if ((ti_get_time() - start_time) > TI_CFG_EXCLUSIVE_SECTION_TIMEOUT) { \
          _##this_core_name##_exclusive_count = 0; \
          _##alt_core_name##_exclusive_count = 0; \
          ti_atomic_store((uint32_t*)&_exclusive_lock, 0U); \
          ti_exit_critical(); \
          goto exclusive_handler_exit; \
        } \
        ti_atomic_store((uint32_t*)&_exclusive_lock, 0U); \
        if (!_acq_exclusive_lock()) { \
          _##this_core_name##_exclusive_count = 0; \
          ti_exit_critical(); \
          goto exclusive_handler_exit; \
        } \
      } \
      _##this_core_name##_exclusive_count = 0; \
    } \
    ti_atomic_store((uint32_t*)&_exclusive_lock, 0U); \
  } \
  ti_exit_critical(); \
  exclusive_handler_exit:

// System update handler for CM7 core (triggered by SEV instruction from CM4 core)
void cpu1_sev_irq_handler(void) {
  ti_enter_critical();
  if ((int32_t)ti_atomic_load((uint32_t*)&_cm4_shutdown_flag) != 0) {
    ti_atomic_store((uint32_t*)&_cm7_shutdown_flag, 1U);
    _exec_cm7_shutdown();
  }
  ti_exit_critical();
  _EXCLUSIVE_UPDATE_IMPL(cm7, cm4)
}

// System update handler for CM4 core (triggered by SEV instruction on CM7 core)
void cpu2_sev_irq_handler(void) {
  ti_enter_critical();
  if ((int32_t)ti_atomic_load((uint32_t*)&_cm7_shutdown_flag) != 0) {
    ti_atomic_store((uint32_t*)&_cm4_shutdown_flag, 1U);
    _exec_cm4_shutdown();
  }
  ti_exit_critical();
  _EXCLUSIVE_UPDATE_IMPL(cm4, cm7)
}

__attribute__((noreturn))
void ti_sys_restart(void) {
  ti_enter_critical();
  uint32_t reg_value = *SCB_AIRCR;
  WRITE_FIELD(&reg_value, SCB_AIRCR_VECTKEYSTAT, _RESET_VECTKEY_VALUE);
  SET_FIELD(&reg_value, SCB_AIRCR_SYSRESETREQ);
  *SCB_AIRCR = reg_value;
  asm volatile (
    "dsb \n\t"
    "isb \n\t"
  );
  while (true) {
    asm volatile ("wfe");
  }
}

__attribute__((noreturn))
void ti_sys_shutdown(void) {
  ti_enter_critical();
  _shutdown_fn_t const this_shutdown_fn = _get_this_shutdown_fn();
  int32_t* const this_shutdown_flag = _get_this_shutdown_flag();
  int32_t* const alt_shutdown_flag = _get_alt_shutdown_flag();
  ti_atomic_store((uint32_t*)this_shutdown_flag, 1U);
  asm volatile (
    "dsb \n\t"
    "sev \n\t"
  );
  while ((int32_t)ti_atomic_load((uint32_t*)alt_shutdown_flag) != 1);
  this_shutdown_fn();
}

void ti_sys_sleep(void) {
  if (!ti_is_critical()) {
    asm volatile (
      "dsb \n\t"
      "isb \n\t"
      "wfi \n\t"
    );
  }
}

void ti_enter_critical(void) {
  int32_t* const critical_count = _get_critical_count();
  if (*critical_count == 0) {
    asm volatile (
      "cpsid i \n\t"
      "isb     \n\t"
    );
  }
  (*critical_count)++;
}

void ti_exit_critical(void) {
  int32_t* const critical_count = _get_critical_count();
  if (*critical_count > 0) {
    (*critical_count)--;
    if (*critical_count == 0) {
      asm volatile (
        "cpsie i \n\t"
        "isb     \n\t"
      );
    }
  }
}

void ti_reset_critical(void) {
  int32_t* const critical_count = _get_critical_count();
  *critical_count = 0;
  asm volatile (
    "cpsie i \n\t"
    "isb     \n\t"
  );
}

bool ti_is_critical(void) {
  int32_t* const critical_count = _get_critical_count();
  return *critical_count > 0;
}

void ti_enter_exclusive(enum ti_errc_t* errc_out) {
  *errc_out = TI_ERRC_NONE;
  int32_t* const this_exclusive_count = _get_this_exclusive_count();
  int32_t* const alt_exclusive_count = _get_alt_exclusive_count();
  ti_enter_critical();
  if (!_acq_exclusive_lock()) {
    ti_exit_critical();
    *errc_out = TI_ERRC_INTERNAL;
    return;
  }
  // We need to be able to ack from this function in case both cores try to enter exclusive 
  // sections at the same time. Otherwise because we are in critical section -> deadlock
  if (*alt_exclusive_count > 0) {
    *this_exclusive_count = -1;
    const int64_t start_time = ti_get_time();
    while (*alt_exclusive_count > 0) {
      if ((ti_get_time() - start_time) > TI_CFG_EXCLUSIVE_SECTION_TIMEOUT) {
        *this_exclusive_count = 0;
        *alt_exclusive_count = 0;
        ti_atomic_store((uint32_t*)&_exclusive_lock, 0U);
        ti_exit_critical();
        *errc_out = TI_ERRC_TIMEOUT;
        return;
      }
      // Give up lock to allow for other core to exit exclusive section
      // Re-acquire lock before loop so other core can't enter exclusive section before we lock it below.
      ti_atomic_store((uint32_t*)&_exclusive_lock, 0U);
      if (!_acq_exclusive_lock()) {
        ti_exit_critical();
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
    }
  }
  if (*this_exclusive_count == -1) {
    *this_exclusive_count = 0;
  }
  (*this_exclusive_count)++;
  asm volatile (
    "dsb \n\t"
    "sev \n\t"
  );
  const int64_t start_time = ti_get_time();
  while (*alt_exclusive_count != -1) {
    if ((ti_get_time() - start_time) > TI_CFG_EXCLUSIVE_SECTION_ACK_TIMEOUT) {
      *this_exclusive_count = 0;
      *alt_exclusive_count = 0;
      ti_atomic_store((uint32_t*)&_exclusive_lock, 0U);
      ti_exit_critical();
      *errc_out = TI_ERRC_TIMEOUT;
      return;
    }
    // Give up lock to allow for other core chance to acknowledge our exclusive section
    ti_atomic_store((uint32_t*)&_exclusive_lock, 0U);
    if (!_acq_exclusive_lock()) {
      *this_exclusive_count = 0;
      ti_exit_critical();
      *errc_out = TI_ERRC_INTERNAL;
      return;
    }
  }
  ti_atomic_store((uint32_t*)&_exclusive_lock, 0U);
  ti_exit_critical();
}

void ti_exit_exclusive(enum ti_errc_t* errc_out) {
  *errc_out = TI_ERRC_NONE;
  int32_t* const this_exclusive_count = _get_this_exclusive_count();
  ti_enter_critical();
  if (!_acq_exclusive_lock()) {
    ti_exit_critical();
    *errc_out = TI_ERRC_INTERNAL;
    return;
  }
  if (*this_exclusive_count <= 0) {
    ti_atomic_store((uint32_t*)&_exclusive_lock, 0U);
    ti_exit_critical();
    *errc_out = TI_ERRC_INTERNAL;
    return;
  }
  (*this_exclusive_count)--;
  ti_atomic_store((uint32_t*)&_exclusive_lock, 0U);
  ti_exit_critical();
}

void ti_reset_exclusive(enum ti_errc_t* errc_out) {
  *errc_out = TI_ERRC_NONE;
  int32_t* const this_exclusive_count = _get_this_exclusive_count();
  int32_t* const alt_exclusive_count = _get_alt_exclusive_count();
  ti_enter_critical();
  if (!_acq_exclusive_lock()) {
    ti_exit_critical();
    *errc_out = TI_ERRC_INTERNAL;
    return;
  }
  *this_exclusive_count = 0;
  ti_atomic_store((uint32_t*)&_exclusive_lock, 0U);
  ti_exit_critical();
}

bool ti_is_exclusive(void) {
  // No need to acquire lock, only reading value
  int32_t* const exclusive_count = _get_this_exclusive_count();
  return ti_atomic_load((uint32_t*)exclusive_count) > 0;
}

enum ti_core_id_t ti_get_core(void) {
  const uint32_t partno = READ_FIELD(SCB_CPUID, SCB_CPUID_PARTNO);
  return (partno == _CM7_PARTNO) ? TI_CORE_ID_CM7 : TI_CORE_ID_CM4;
}

bool ti_is_interrupt(void) {
  uint32_t ipsr_value;
  asm volatile ("mrs %[ipsr_value], ipsr" : [ipsr_value] "=r" (ipsr_value));
  return ipsr_value != 0;
}