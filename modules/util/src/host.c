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
 * @file modules/util/src/host.c
 * @authors Aaron McBride
 * @brief Implementation of semi-hosting facilities.
 */

#include "util/host.h"

#ifndef TI_CFG_MAX_FILE_COUNT
  #define TI_CFG_MAX_FILE_COUNT 8
#endif

/**************************************************************************************************
 * @section Internal Utilities
 **************************************************************************************************/

static const int32_t _HOST_OP_OPEN = 0x01; // Open file on host (Args: path, mode, path length) (Ret: file handle)

// Executes an operation on the host computer with the given arguments, returns the result.
static uint32_t _exec_host_op(uint32_t op, uint32_t arg1, uint32_t arg2, uint32_t arg3) {
  uint32_t result;
  asm volatile (
    "mov r0, %[_op] \n\t"
    "mov r1, %[_arg1] \n\t"
    "mov r2, %[_arg2] \n\t"
    "mov r3, %[_arg3] \n\t"
    "bkpt 0xAB \n\t"
    "mov %[_result], r0"
    : [_result] "=r" (result)
    : [_op] "r" (op), 
      [_arg1] "r" (arg1), 
      [_arg2] "r" (arg2), 
      [_arg3] "r" (arg3)
    : "r0", "r1", "r2", "r3"
  );
  return result;
}

/**************************************************************************************************
 * @section File Utilities
 **************************************************************************************************/

// Invalid file handle struct
struct ti_file_t TI_INVALID_FILE = {
  .handle = NULL,
  .id = -1,
};

// Internal file info struct
struct _int_file_t {
  enum ti_file_mode_t mode;
  int32_t file_handle;
  int32_t id;
  int32_t pos;
};

// Pointers to file info structs (open files)
static struct _int_file_t* _file_list[TI_CFG_MAX_FILE_COUNT] = {NULL};

// Unique open file identifier
static int32_t _cur_file_id = 0;

// Opens a file on the host machine
struct ti_file_t ti_open_host_file(void* mem, const char* path, enum ti_file_mode_t mode, enum ti_errc_t* errc_out) {
  if (!mem || !path) {
    *errc_out = TI_ERRC_INVALID_ARG;
    return TI_INVALID_FILE;
  }
  const int32_t file_handle = _exec_host_op(_HOST_OP_OPEN, (uint32_t)path, )

}

void ti_close_host_file(struct ti_file_t file);

__attribute__((format(printf, 2, 3))) void ti_write_host_file(struct ti_file_t file, const char* fmt, ...);

void ti_read_host_file(struct ti_file_t file, char* buf, int32_t size);

int32_t ti_get_host_file_pos(struct ti_file_t file);

void ti_set_host_file_pos(struct ti_file_t file, int32_t pos);

void ti_move_host_file_pos(struct ti_file_t file, int32_t offset);

bool ti_check_host_file(const char* path);

bool ti_is_host_file_open(struct ti_file_t file);

enum ti_file_mode_t ti_get_host_file_mode(struct ti_file_t file);

/**************************************************************************************************
 * @section Standard Input/Output Utilities
 **************************************************************************************************/

__attribute__((format(printf, 1, 2))) void ti_write_host_io(const char* fmt, ...);

void ti_read_host_io(char* buf, int32_t size);

/**************************************************************************************************
 * @section Time Utilities
 **************************************************************************************************/

int64_t ti_get_host_time(void);