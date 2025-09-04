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
 * @file modules/kernel/src/mutex.c
 * @authors Aaron McBride
 * @brief Implementation of mutex synchronization primitives.
 */

#include "kernel/mutex.h" // header
#include "util/atomic.h"
#include "kernel/thread.h"
#include "kernel/time.h"
#include "util/math.h"

// Internal mutex information struct
struct _int_mutex_t {
  int32_t id;                // Unique identifier for mutex (matches id in ti_mutex_t)
  enum ti_mutex_type_t type; // Type of mutex (normal, recursive)
  int32_t edit_lock;         // Edit lock for mutex (acquired when owner/lock_count are edited)
  struct ti_thread_t owner;  // Current owner of mutex (thread)
  int32_t lock_count;        // Number of times mutex is locked (for recursive mutexes)
};

// Ensure that memory size definition is correct
_Static_assert(TI_MUTEX_MEM_SIZE == sizeof(struct _int_mutex_t));

// Last used mutex identifier (start at non-zero num to reduce chance of collision)
static int32_t _cur_mutex_id = 123;

struct ti_mutex_t ti_create_mutex(void* const mem, const enum ti_mutex_type_t type, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!mem || type == TI_MUTEX_TYPE_INVALID) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return TI_INVALID_MUTEX;
  }
  struct _int_mutex_t* const int_mutex = (struct _int_mutex_t*)mem;
  int_mutex->id = (int32_t)ti_atomic_add((uint32_t*)&_cur_mutex_id, 1U);
  int_mutex->type = type;
  int_mutex->edit_lock = 0;
  int_mutex->owner = TI_INVALID_THREAD;
  int_mutex->lock_count = 0;
  return (struct ti_mutex_t){
    .id = int_mutex->id,
    .handle = int_mutex,
  };
}

void ti_destroy_mutex(const struct ti_mutex_t mutex, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_mutex(mutex)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  struct _int_mutex_t* const int_mutex = (struct _int_mutex_t*)mutex.handle;
  while (!ti_atomic_cmp_exchange((uint32_t*)&int_mutex->edit_lock, &(uint32_t){0U}, 1U)) {
    ti_yield();
  }
  if (int_mutex->lock_count != 0) {
    *errc_out = TI_ERRC_INVALID_STATE;
    ti_store_atomic(&int_mutex->edit_lock, 0U);
    return;
  }
  int_mutex->id = -1;
  ti_store_atomic(&int_mutex->edit_lock, 0U);
}

bool ti_acquire_mutex(const struct ti_mutex_t mutex, const int64_t timeout, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (ti_is_interrupt()) {
    *errc_out = TI_ERRC_INVALID_OP;
    return false;
  }
  if (!ti_is_valid_mutex(mutex)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return false;
  }
  enum ti_errc_t int_errc = TI_ERRC_NONE;
  const struct ti_thread_t this_thread = ti_get_this_thread(&int_errc);
  if (int_errc != TI_ERRC_NONE) {
    *errc_out = TI_ERRC_INTERNAL;
    return false;
  }
  struct _int_mutex_t* const int_mutex = (struct _int_mutex_t*)mutex.handle;
  while (!ti_atomic_cmp_exchange((uint32_t*)&int_mutex->edit_lock, &(uint32_t){0U}, 1U)) {
    ti_yield();
  }
  if (ti_is_thread_equal(int_mutex->owner, this_thread)) {
    if (int_mutex->type == TI_MUTEX_TYPE_RECURSIVE) {
      int_mutex->lock_count++;
      ti_store_atomic(&int_mutex->edit_lock, 0U);
      return true;
    } else {
      *errc_out = TI_ERRC_INVALID_STATE;
      ti_store_atomic(&int_mutex->edit_lock, 0U);
      return false;
    }
  }
  ti_atomic_store(&int_mutex->edit_lock, 0U);
  const int64_t start_time = ti_get_time();
  do {
    while (!ti_atomic_cmp_exchange((uint32_t*)&int_mutex->edit_lock, &(uint32_t){0U}, 1U)) {
      ti_yield();
    }
    if (int_mutex->lock_count == 0) {
      int_mutex->owner = this_thread;
      int_mutex->lock_count = 1;
      ti_atomic_store(&int_mutex->edit_lock, 0U);
      return true;
    }
    ti_atomic_store(&int_mutex->edit_lock, 0U);
    ti_yield();
  } while ((ti_get_time() - start_time) < timeout);
  return false;
}

void ti_release_mutex(const struct ti_mutex_t mutex, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (ti_is_interrupt()) {
    *errc_out = TI_ERRC_INVALID_OP;
    return;
  }
  if (!ti_is_valid_mutex(mutex)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  enum ti_errc_t int_errc = TI_ERRC_NONE;
  const struct ti_thread_t this_thread = ti_get_this_thread(&int_errc);
  if (int_errc != TI_ERRC_NONE) {
    *errc_out = TI_ERRC_INTERNAL;
    return;
  }
  struct _int_mutex_t* const int_mutex = (struct _int_mutex_t*)mutex.handle;
  while (!ti_atomic_cmp_exchange((uint32_t*)&int_mutex->edit_lock, &(uint32_t){0U}, 1U)) {
    ti_yield();
  }
  if (!ti_is_thread_equal(int_mutex->owner, this_thread)) {
    *errc_out = TI_ERRC_INVALID_STATE;
    ti_atomic_store(&int_mutex->edit_lock, 0U);
    return;
  }
  if (int_mutex->type == TI_MUTEX_TYPE_RECURSIVE) {
    int_mutex->lock_count--;
    if (int_mutex->lock_count == 0) {
      int_mutex->owner = TI_INVALID_THREAD;
    }
  } else {
    int_mutex->owner = TI_INVALID_THREAD;
    int_mutex->lock_count = 0;
  }
  ti_atomic_store(&int_mutex->edit_lock, 0U);
}

bool ti_is_mutex_locked(const struct ti_mutex_t mutex, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (ti_is_interrupt()) {
    *errc_out = TI_ERRC_INVALID_OP;
    return false;
  }
  if (!ti_is_valid_mutex(mutex)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return false;
  }
  struct _int_mutex_t* const int_mutex = (struct _int_mutex_t*)mutex.handle;
  while (!ti_atomic_cmp_exchange((uint32_t*)&int_mutex->edit_lock, &(uint32_t){0U}, 1U)) {
    ti_yield();
  }
  const int32_t mutex_lock_count = int_mutex->lock_count != 0;
  ti_atomic_store(&int_mutex->edit_lock, 0U);
  return mutex_lock_count != 0;
}

struct ti_thread_t ti_get_mutex_owner(const struct ti_mutex_t mutex, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (ti_is_interrupt()) {
    *errc_out = TI_ERRC_INVALID_OP;
    return TI_INVALID_THREAD;
  }
  if (!ti_is_valid_mutex(mutex)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return TI_INVALID_THREAD;
  }
  struct _int_mutex_t* const int_mutex = (struct _int_mutex_t*)mutex.handle;
  while (!ti_atomic_cmp_exchange((uint32_t*)&int_mutex->edit_lock, &(uint32_t){0U}, 1U)) {
    ti_yield();
  }
  const struct ti_thread_t mutex_owner = int_mutex->owner;
  ti_atomic_store(&int_mutex->edit_lock, 0U);
  return mutex_owner;
}

enum ti_mutex_type_t ti_get_mutex_type(const struct ti_mutex_t mutex, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_mutex(mutex)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return TI_MUTEX_TYPE_INVALID;
  }
  // No need to acquire edit lock because 'type' is immutable
  struct _int_mutex_t* const int_mutex = (struct _int_mutex_t*)mutex.handle;
  return int_mutex->type;
}

bool ti_is_valid_mutex(const struct ti_mutex_t mutex) {
  if (mutex.handle == NULL || mutex.id < 0) {
    return false;
  }
  // Can't acquire edit lock because we dont know if mutex is valid
  // thus best next option is to atomically load the ID field.
  struct _int_mutex_t* const int_mutex = (struct _int_mutex_t*)mutex.handle;
  return (int32_t)ti_atomic_load((uint32_t*)&int_mutex->id) == mutex.id;
}

bool ti_is_mutex_equal(const struct ti_mutex_t mutex_1, const struct ti_mutex_t mutex_2) {
  return mutex_1.id == mutex_2.id;
}