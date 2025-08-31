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

// Definition of invalid mutex constant
const struct ti_mutex_t TI_INVALID_MUTEX = {
  .id = -1,
  .handle = NULL,
};

// Internal mutex information struct
struct _int_mutex_t {
  int32_t id;
  enum ti_mutex_type_t type; 
  struct ti_thread_t owner;
  int32_t lock_count;
};

// Ensure that mutex memory size definition matches size of internal mutex structure
_Static_assert(TI_MUTEX_MEM_SIZE == sizeof(struct _int_mutex_t));

// Last used mutex identifier
static int32_t _cur_mutex_id = 0;

struct ti_mutex_t ti_create_mutex(void* mem, enum ti_mutex_type_t type, enum ti_errc_t* errc_out) {
  if (!mem || type == TI_MUTEX_TYPE_INVALID) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return TI_INVALID_MUTEX;
  }
  struct _int_mutex_t* int_mutex = (struct _int_mutex_t*)mem;
  int_mutex->id = _cur_mutex_id++;
  int_mutex->type = type;
  int_mutex->owner = TI_INVALID_THREAD;
  int_mutex->lock_count = 0;
  return (struct ti_mutex_t){
    .id = int_mutex->id,
    .handle = int_mutex,
  };
}

void ti_destroy_mutex(struct ti_mutex_t mutex, enum ti_errc_t* errc_out) {
  if (!ti_is_valid_mutex(mutex)) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return;
  }
  struct _int_mutex_t* int_mutex = (struct _int_mutex_t*)mutex.handle;
  if (int_mutex->lock_count > 0) {
    *errc_out = TI_ERRC_INVALID_STATE;
    return;
  }


}

bool ti_acquire_mutex(struct ti_mutex_t mutex, int64_t timeout, enum ti_errc_t* errc_out) {

}

bool ti_release_mutex(struct ti_mutex_t mutex, int64_t timeout, enum ti_errc_t* errc_out) {

}

bool ti_is_mutex_locked(struct ti_mutex_t mutex, enum ti_errc_t* errc_out) {

}

struct ti_thread_t ti_get_mutex_owner(struct ti_mutex_t mutex, enum ti_errc_t* errc_out) {

}

enum ti_mutex_type_t ti_get_mutex_type(struct ti_mutex_t mutex, enum ti_errc_t* errc_out) {

}

bool ti_is_valid_mutex(struct ti_mutex_t mutex) {

}

bool ti_is_mutex_equal(struct ti_mutex_t mutex_1, struct ti_mutex_t mutex_2) {

}