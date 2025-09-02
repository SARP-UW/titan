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
 * @file modules/kernel/src/host.c
 * @authors Aaron McBride
 * @brief Implementation of semi-hosting facilities.
 */

#include <string.h>
#include <stdlib.h>
#include "kernel/host.h" // header
#include "ti_config.h"
#include "internal/mmio.h"
#include "util/core.h"
#include "util/atomic.h"
#include "kernel/mutex.h"

/**************************************************************************************************
 * @section Configuration Defaults
 **************************************************************************************************/

#ifndef TI_CFG_SEMIHOSTING_ENABLED
  #define TI_CFG_SEMIHOSTING_ENABLED 0
#endif

#ifndef TI_CFG_HOST_FILE_MUTEX_TIMEOUT
  #define TI_CFG_HOST_FILE_MUTEX_TIMEOUT 1000
#endif

#ifndef TI_CFG_HOST_IO_MUTEX_TIMEOUT
  #define TI_CFG_HOST_IO_MUTEX_TIMEOUT 1000
#endif

/**************************************************************************************************
 * @section Internal Utilities
 **************************************************************************************************/

#if TI_CFG_SEMIHOSTING_ENABLED

  static const int32_t _HOST_OP_OPEN   = 0x01; // Open file on host (Args: path, mode, path length) (Ret: file handle)
  static const int32_t _HOST_OP_CLOSE  = 0x02; // Close file on host (Args: file handle) (Ret: error)
  static const int32_t _HOST_OP_WRITE  = 0x05; // Write to file on host (Args: file handle, buf, len) (Ret: bytes not written)
  static const int32_t _HOST_OP_READ   = 0x06; // Read from file on host (Args: file handle, buf, len) (Ret: bytes read)
  static const int32_t _HOST_OP_SEEK   = 0x0A; // Move file cursor on host (Args: file handle, offset) (Ret: error)
  static const int32_t _HOST_OP_FLEN   = 0x0C; // Get length of file (Args: file handle) (Ret: file length)
  static const int32_t _HOST_OP_WRITE0 = 0x04; // Write string to host IO (Args: string) (Ret: None)
  static const int32_t _HOST_OP_READC  = 0x07; // Read char from host IO (Args: None) (Ret: input char)
  static const int32_t _HOST_OP_TIME   = 0x11; // Get time from host (Args: None) (Ret: timestamp)
  static const int32_t _HOST_OP_ISTTY  = 0x09; // Check if host file is an interactive device (Args: file handle) (Ret: result)

  // Executes a semihosting operation on the host machine
  // Given arguments are passed to machine, and result is returned
  // See: https://developer.arm.com/documentation/dui0471/m/what-is-semihosting-
  static int32_t _exec_host_op(int32_t op, int32_t arg1, int32_t arg2, int32_t arg3) {
    int32_t result;
    asm volatile (
      "mov r0, %[_op]     \n\t"
      "mov r1, %[_arg1]   \n\t"
      "mov r2, %[_arg2]   \n\t"
      "mov r3, %[_arg3]   \n\t"
      "bkpt 0xAB          \n\t"
      "mov %[_result], r0 \n\t"
      : [_result] "=r" (result)
      : [_op] "r" (op), 
        [_arg1] "r" (arg1), 
        [_arg2] "r" (arg2), 
        [_arg3] "r" (arg3)
      : "r0", "r1", "r2", "r3"
    );
    return result;
  }

  // Returns true if the host is currently available (debugger connected).
  static bool _is_host_available(void) {
    return IS_FIELD_SET(DBG_DHCSR, DBG_DHCSR_C_DEBUGEN);
  }

#endif

/**************************************************************************************************
 * @section File Utilities
 **************************************************************************************************/

// Internal host file info struct
struct _int_file_t {
  int32_t id;                    // Unique identifier for file (matches id field in returned handle)
  enum ti_host_file_mode_t mode; // Mode the file is opened with
  int32_t pos;                   // Position of cursor in the file
  int32_t file_handle;           // Handle for file given by host on open
  bool is_tty;                   // True if file is an interactive device (TTY)
  struct ti_mutex_t file_mutex;  // Mutex for file access
};

#if TI_CFG_SEMIHOSTING_ENABLED

  // Ensure that memory size definition is correct
  _Static_assert(TI_HOST_FILE_MEM_SIZE == (sizeof(struct _int_file_t) + TI_MUTEX_MEM_SIZE));

  // Last used file identifier (start at non-zero num to reduce chance of collision)
  static int32_t _cur_file_id = 123;

#endif

struct ti_host_file_t ti_open_host_file(void* const mem, const char* const path, const enum ti_host_file_mode_t mode, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return TI_INVALID_HOST_FILE;
    }
    if (!mem || !path || mode == TI_HOST_FILE_MODE_INVALID) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return TI_INVALID_HOST_FILE;
    }
    struct _int_file_t* const int_file = (struct _int_file_t*)mem;
    int_file->id = (int32_t)ti_atomic_add((uint32_t*)&_cur_file_id, 1U);
    int_file->mode = mode;
    int_file->pos = 0;
    const int32_t file_handle = _exec_host_op(_HOST_OP_OPEN, (int32_t)path, (int32_t)mode, strlen(path));
    if (file_handle < 0) {
      *errc_out = TI_ERRC_HOST;
      return TI_INVALID_HOST_FILE;
    }
    int_file->file_handle = file_handle;
    const int32_t is_tty_result = _exec_host_op(_HOST_OP_ISTTY, file_handle, 0, 0);
    if (is_tty_result != 0 && is_tty_result != 1) {
      *errc_out = TI_ERRC_HOST;
      return TI_INVALID_HOST_FILE;
    }
    int_file->is_tty = is_tty_result;
    void* const mutex_mem = (void*)((char*)mem + sizeof(struct _int_file_t));
    enum ti_errc_t int_errc;
    int_file->file_mutex = ti_create_mutex(mutex_mem, TI_MUTEX_TYPE_NORMAL, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return TI_INVALID_HOST_FILE;
    }
    return (struct ti_host_file_t){
      .id = int_file->id,
      .handle = (void*)int_file,
    };
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return TI_INVALID_HOST_FILE;
  #endif
}

void ti_close_host_file(const struct ti_host_file_t file, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available() || ti_is_interrupt()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return;
    }
    if (!ti_is_valid_host_file(file)) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return;
    }
    enum ti_errc_t int_errc;
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    const bool acq_result = ti_acquire_mutex(int_file->file_mutex, TI_CFG_HOST_FILE_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return;
    }
    int32_t host_result = _exec_host_op(_HOST_OP_CLOSE, int_file->file_handle, 0, 0);
    if (host_result < 0) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
      *errc_out = TI_ERRC_HOST;
      return;
    }
    int_file->id = -1;
    ti_release_mutex(int_file->file_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return;
    }
    ti_destroy_mutex(int_file->file_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
    }
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
  #endif
}

void ti_write_host_file(const struct ti_host_file_t file, const char* const str, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available() || ti_is_interrupt()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return;
    }
    if (!ti_is_valid_host_file(file) || !str) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return;
    }
    enum ti_errc_t int_errc;
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    const bool acq_result = ti_acquire_mutex(int_file->file_mutex, TI_CFG_HOST_FILE_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return;
    }
    const int32_t str_len = strlen(str);
    // host_result = number of characters NOT written
    const int32_t host_result = _exec_host_op(_HOST_OP_WRITE, int_file->file_handle, (int32_t)str, str_len);
    if (!int_file->is_tty) {
      if (int_file->mode == TI_HOST_FILE_MODE_APPEND || int_file->mode == TI_HOST_FILE_MODE_APPEND_READ) {
        const int32_t file_len = _exec_host_op(_HOST_OP_FLEN, int_file->file_handle, 0, 0);
        if (file_len < 0) {
          int_file->pos += str_len - host_result;
          ti_release_mutex(int_file->file_mutex, &int_errc);
          if (int_errc != TI_ERRC_NONE) {
            *errc_out = TI_ERRC_INTERNAL;
            return;
          }
          *errc_out = TI_ERRC_HOST;
          return;
        }
        int_file->pos = file_len;
      } else {
        int_file->pos += str_len - host_result;
      }
    }
    if (host_result != 0) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
      *errc_out = TI_ERRC_HOST;
      return;
    }
    ti_release_mutex(int_file->file_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
    }
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
  #endif
}

int32_t ti_read_host_file(const struct ti_host_file_t file, char* const buf, const int32_t size, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available() || ti_is_interrupt()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return -1;
    }
    if (!ti_is_valid_host_file(file) || !buf || size < 0) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return -1;
    }
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    if (int_file->mode == TI_HOST_FILE_MODE_WRITE || int_file->mode == TI_HOST_FILE_MODE_APPEND) {
      *errc_out = TI_ERRC_INVALID_OP;
      return -1;
    }
    enum ti_errc_t int_errc;
    bool acq_result = ti_acquire_mutex(int_file->file_mutex, TI_CFG_HOST_FILE_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return -1;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return -1;
    }
    // host_result = number of characters NOT read from given size
    const int32_t host_result = _exec_host_op(_HOST_OP_READ, int_file->file_handle, (int32_t)buf, size);
    const int32_t read_char_count = size - host_result;
    if (!int_file->is_tty) {
      int_file->pos += read_char_count;
    }
    ti_release_mutex(int_file->file_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return -1;
    }
    return read_char_count;
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return -1;
  #endif
}

int32_t ti_get_host_file_pos(const struct ti_host_file_t file, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (ti_is_interrupt()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return -1;
    }
    if (!ti_is_valid_host_file(file)) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return -1;
    }
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    if (int_file->is_tty) {
      *errc_out = TI_ERRC_INVALID_OP;
      return -1;
    }
    enum ti_errc_t int_errc;
    bool acq_result = ti_acquire_mutex(int_file->file_mutex, TI_CFG_HOST_FILE_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return -1;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return -1;
    }
    const int32_t file_pos = int_file->pos;
    ti_release_mutex(int_file->file_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return -1;
    }
    return file_pos;
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return -1;
  #endif
}

void ti_set_host_file_pos(const struct ti_host_file_t file, const int32_t pos, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available() || ti_is_interrupt()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return;
    }
    if (!ti_is_valid_host_file(file)) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return;
    }
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    if (int_file->is_tty) {
      *errc_out = TI_ERRC_INVALID_OP;
      return;
    }
    enum ti_errc_t int_errc;
    bool acq_result = ti_acquire_mutex(int_file->file_mutex, TI_CFG_HOST_FILE_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return;
    }
    const int32_t file_len = _exec_host_op(_HOST_OP_FLEN, int_file->file_handle, 0, 0);
    if (file_len < 0) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
      *errc_out = TI_ERRC_HOST;
      return;
    }
    if (abs(pos) > file_len) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
      *errc_out = TI_ERRC_INVALID_ARG;
      return;
    }
    const int32_t abs_pos = (pos >= 0) ? pos : (file_len + pos);
    const int32_t host_result = _exec_host_op(_HOST_OP_SEEK, int_file->file_handle, abs_pos, 0);
    if (host_result != 0) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
      *errc_out = TI_ERRC_HOST;
      return;
    }
    int_file->pos = abs_pos;
    ti_release_mutex(int_file->file_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
    }
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
  #endif
}

void ti_move_host_file_pos(const struct ti_host_file_t file, const int32_t offset, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available() || ti_is_interrupt()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return;
    }
    if (!ti_is_valid_host_file(file)) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return;
    }
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    if (int_file->is_tty) {
      *errc_out = TI_ERRC_INVALID_OP;
      return;
    }
    enum ti_errc_t int_errc;
    const bool acq_result = ti_acquire_mutex(int_file->file_mutex, TI_CFG_HOST_FILE_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return;
    }
    const int32_t file_len = _exec_host_op(_HOST_OP_FLEN, int_file->file_handle, 0, 0);
    if (file_len < 0) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
      *errc_out = TI_ERRC_HOST;
      return;
    }
    const int32_t new_pos = int_file->pos + offset;
    if (new_pos < 0 || new_pos > file_len) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
      *errc_out = TI_ERRC_INVALID_ARG;
      return;
    }
    const int32_t host_result = _exec_host_op(_HOST_OP_SEEK, int_file->file_handle, new_pos, 0);
    if (host_result != 0) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
      *errc_out = TI_ERRC_HOST;
      return;
    }
    int_file->pos = new_pos;
    ti_release_mutex(int_file->file_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
    }
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
  #endif
}

int32_t ti_get_host_file_len(const struct ti_host_file_t file, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return -1;
    }
    if (!ti_is_valid_host_file(file)) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return -1;
    }
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    if (int_file->is_tty) {
      *errc_out = TI_ERRC_INVALID_OP;
      return -1;
    }
    enum ti_errc_t int_errc;
    const bool acq_result = ti_acquire_mutex(int_file->file_mutex, TI_CFG_HOST_FILE_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return -1;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return -1;
    }
    const int32_t file_len = _exec_host_op(_HOST_OP_FLEN, int_file->file_handle, 0, 0);
    if (file_len < 0) {
      ti_release_mutex(int_file->file_mutex, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return -1;
      }
      *errc_out = TI_ERRC_HOST;
      return -1;
    }
    ti_release_mutex(int_file->file_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return -1;
    }
    return file_len;
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return -1;
  #endif
}

bool ti_is_host_file_tty(const struct ti_host_file_t file, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!ti_is_valid_host_file(file)) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return false;
    }
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    return int_file->is_tty;
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return false;
  #endif
}

bool ti_check_host_file(const char* const path, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return false;
    }
    if (!path) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return false;
    }
    // In read mode, if file does not exist opening fails -> thus negative handle
    const int32_t tmp_handle = _exec_host_op(_HOST_OP_OPEN, (int32_t)path, (int32_t)TI_HOST_FILE_MODE_READ, strlen(path));
    if (tmp_handle >= 0) {
      const int32_t close_result = _exec_host_op(_HOST_OP_CLOSE, tmp_handle, 0, 0);
      if (close_result == -1) {
        *errc_out = TI_ERRC_HOST;
        return false;
      }
      return true;
    } else {
      return false;
    }
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return false;
  #endif
}

enum ti_host_file_mode_t ti_get_host_file_mode(const struct ti_host_file_t file, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!ti_is_valid_host_file(file)) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return TI_HOST_FILE_MODE_INVALID;
    }
    struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
    return int_file->mode;
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return TI_HOST_FILE_MODE_INVALID;
  #endif
}

bool ti_is_valid_host_file(const struct ti_host_file_t file) {
  if (!file.handle || file.id < 0) {
    return false;
  }
  struct _int_file_t* int_file = (struct _int_file_t*)file.handle;
  return file.id == int_file->id;
}

bool ti_is_host_file_equal(const struct ti_host_file_t file_1, const struct ti_host_file_t file_2) {
  return file_1.id == file_2.id;
}

/**************************************************************************************************
 * @section Standard Input/Output Utilities
 **************************************************************************************************/

#if TI_CFG_SEMIHOSTING_ENABLED

  // Memory for host IO mutex
  static uint8_t _io_mutex_mem[TI_MUTEX_MEM_SIZE];

  // Mutex used for ensuring exclusive access to host IO
  static struct ti_mutex_t _io_mutex = TI_INVALID_MUTEX;

#endif

void ti_write_host_io(const char* const str, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available() || ti_is_interrupt()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return;
    }
    if (!str) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return;
    }
    enum ti_errc_t int_errc;
    if (!ti_is_valid_mutex(_io_mutex)) {
      _io_mutex = ti_create_mutex((void*)_io_mutex_mem, TI_MUTEX_TYPE_NORMAL, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return;
      }
    }
    const bool acq_result = ti_acquire_mutex(_io_mutex, TI_CFG_HOST_IO_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return;
    }
    _exec_host_op(_HOST_OP_WRITE0, (int32_t)str, 0, 0);
    ti_release_mutex(_io_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
    }
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
  #endif
}

int32_t ti_read_host_io(char* const buf, const int32_t size, enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available() || ti_is_interrupt()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return -1;
    }
    if (!buf || size < 0) {
      *errc_out = TI_ERRC_INVALID_ARG;
      return -1;
    }
    enum ti_errc_t int_errc;
    if (!ti_is_valid_mutex(_io_mutex)) {
      _io_mutex = ti_create_mutex((void*)_io_mutex_mem, TI_MUTEX_TYPE_NORMAL, &int_errc);
      if (int_errc != TI_ERRC_NONE) {
        *errc_out = TI_ERRC_INTERNAL;
        return -1;
      }
    }
    const bool acq_result = ti_acquire_mutex(_io_mutex, TI_CFG_HOST_IO_MUTEX_TIMEOUT, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
      return -1;
    }
    if (!acq_result) {
      *errc_out = TI_ERRC_TIMEOUT;
      return -1;
    }
    int32_t char_count = 0;
    while (char_count < size) {
      const char cur_char = (char)_exec_host_op(_HOST_OP_READC, 0, 0, 0);
      if (cur_char == '\0' || cur_char == '\n' || cur_char == '\r') {
        break;
      }
      buf[char_count++] = cur_char;
    }
    ti_release_mutex(_io_mutex, &int_errc);
    if (int_errc != TI_ERRC_NONE) {
      *errc_out = TI_ERRC_INTERNAL;
    }
    return char_count;
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return -1;
  #endif
}

/**************************************************************************************************
 * @section Time Utilities
 **************************************************************************************************/

int64_t ti_get_host_time(enum ti_errc_t* const errc_out) {
  #if TI_CFG_SEMIHOSTING_ENABLED
    *errc_out = TI_ERRC_NONE;
    if (!_is_host_available()) {
      *errc_out = TI_ERRC_INVALID_OP;
      return -1;
    }
    const int32_t host_time = _exec_host_op(_HOST_OP_TIME, 0, 0, 0);
    if (host_time < 0) {
      *errc_out = TI_ERRC_HOST;
    }
    return host_time;
  #else
    *errc_out = TI_ERRC_UNSUPPORTED;
    return -1;
  #endif
}