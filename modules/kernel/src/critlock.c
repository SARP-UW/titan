/**
 * This file is part of the Titan Project.
 * Copyright (c) 2024 UW SARP
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
 * @file modules/kernel/src/critlock.c
 * @authors Aaron McBride
 * @brief Implementation of critlock synchronization primitives.
 */

#include "kernel/critlock.h" // header
#include "kernel/sys.h"
#include "kernel/time.h"
#include "util/atomic.h"

// Internal critlock information struct
struct _int_critlock_t {
  int32_t id;   // Unique identifier for critlock (matches id in ti_critlock_t)
  int32_t lock; // Lock state (0 = unlocked, 1 = locked)
};

// Ensure that memory size definition is correct
_Static_assert(TI_CRITLOCK_MEM_SIZE == sizeof(struct _int_critlock_t));

// Last used critlock identifier (start at non-zero num to reduce chance of collision)
static int32_t _cur_critlock_id = 123;

struct ti_critlock_t ti_create_critlock(void* mem, enum ti_errc_t* errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!mem) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return TI_INVALID_CRITLOCK;
  }
  struct _int_critlock_t* const int_critlock = (struct _int_critlock_t*)mem;
  int_critlock->id = (int32_t)ti_atomic_add((uint32_t*)&_cur_critlock_id, 1U);
  int_critlock->lock = 0;
  return (struct ti_critlock_t){
    .id = int_critlock->id,
    .handle = int_critlock,
  };
}

void ti_destroy_critlock(const struct ti_critlock_t critlock, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_critlock(critlock)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  struct _int_critlock_t* const int_critlock = (struct _int_critlock_t*)critlock.handle;
  if ((int32_t)ti_atomic_load((uint32_t*)&int_critlock->lock) != 0) {
    *errc_out = TI_ERRC_INVALID_STATE;
    return;
  }
  int_critlock->id = -1;
}

bool ti_acquire_critlock(const struct ti_critlock_t critlock, const int64_t timeout, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_critlock(critlock)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return false;
  }
  const int64_t start_time = ti_get_time();
  struct _int_critlock_t* const int_critlock = (struct _int_critlock_t*)critlock.handle;
  do {
    ti_enter_critical();
    if (ti_atomic_cmp_exchange((uint32_t*)&int_critlock->lock, &(uint32_t){0U}, 1U)) {
      return true;
    }
    ti_exit_critical();
    ti_yield();
  } while ((ti_get_time() - start_time) < timeout);
  return false;
}

void ti_release_critlock(const struct ti_critlock_t critlock, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_critlock(critlock)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  struct _int_critlock_t* const int_critlock = (struct _int_critlock_t*)critlock.handle;
  if ((int32_t)ti_atomic_load((uint32_t*)&int_critlock->lock) == 0) {
    *errc_out = TI_ERRC_INVALID_STATE;
    return;
  }
  ti_atomic_store((uint32_t*)&int_critlock->lock, 0U);
  ti_exit_critical();
}

bool ti_is_critlock_locked(const struct ti_critlock_t critlock, enum ti_errc_t* const errc_out) {
  *errc_out = TI_ERRC_NONE;
  if (!ti_is_valid_critlock(critlock)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return false;
  }
  struct _int_critlock_t* const int_critlock = (struct _int_critlock_t*)critlock.handle;
  return (int32_t)ti_atomic_load((uint32_t*)&int_critlock->lock) != 0;
}

bool ti_is_valid_critlock(const struct ti_critlock_t critlock) {
  if (critlock.id < 0 || !critlock.handle) {
    return false;
  }
  // Can't acquire lock because critlock may be invalid -> atomic load is best option
  struct _int_critlock_t* const int_critlock = (struct _int_critlock_t*)critlock.handle;
  return (int32_t)ti_atomic_load((uint32_t*)&int_critlock->id) == critlock.id;
}

bool ti_is_critlock_equal(const struct ti_critlock_t critlock_1, const struct ti_critlock_t critlock_2) {
  return (critlock_1.id == critlock_2.id) && (critlock_1.handle == critlock_2.handle);
}