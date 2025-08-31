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
 * @file modules/kernel/include/kernel/host.h
 * @authors Aaron McBride
 * @brief Semi-hosting facilities.
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "util/errc.h"

/**************************************************************************************************
 * @section File Utilities
 **************************************************************************************************/

/** @brief Identifies an open file on the host. */
struct ti_host_file_t {
  int32_t id;
  const void* handle;
};

/** @brief Denotes the mode in which to open a file on the host. */
enum ti_host_file_mode_t {
  TI_HOST_FILE_MODE_INVALID     = -1, /** @brief Invalid file mode (DO NOT USE). */
  TI_HOST_FILE_MODE_READ        = 1,  /** @brief (POSIX mode: "r") Opens a file for reading. Cursor at start of file. File must exist. */
  TI_HOST_FILE_MODE_WRITE       = 5,  /** @brief (POSIX mode: "w") Opens a file for writing. Cursor at start of file. New file is created (will overwrite). */
  TI_HOST_FILE_MODE_APPEND      = 9,  /** @brief (POSIX mode: "a") Opens a file for appending. Cursor always at end of file. File may exist (won't overwrite). */
  TI_HOST_FILE_MODE_READ_WRITE  = 3,  /** @brief (POSIX mode: "r+") Opens a file for reading and writing. Cursor at start of file. File must exist. */
  TI_HOST_FILE_MODE_WRITE_READ  = 7,  /** @brief (POSIX mode: "w+") Opens a file for writing and reading. Cursor at start of file. New file is created (can overwrite). */
  TI_HOST_FILE_MODE_APPEND_READ = 11, /** @brief (POSIX mode: "a+") Opens a file for appending and reading. Cursor at end of file after each write. File must exist. */
};

/** @brief Size of memory block required for a host file. */
#define TI_FILE_MEM_SIZE 20 

/** @brief Invalid host file constant.  */
extern const struct ti_host_file_t TI_INVALID_HOST_FILE;

/**
 * @brief Opens a file on the host machine.
 * @param mem (void*) Pointer to memory block for file info.
 * @param path (const char*) Absolute path to the desired file.
 * @param mode (enum ti_host_file_mode_t) Mode to open the file in.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (struct ti_host_file_t) Handle to the opened file or an invalid file (TI_INVALID_HOST_FILE) if an error occurred.
 * @warning - TI_ERRC_INVALID_OP is raised if a debugger is not connected and or semihosting is disabled.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [mem] or @p [path] are NULL, or @p [mode] is TI_HOST_FILE_MODE_INVALID.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 */
struct ti_host_file_t ti_open_host_file(void* mem, const char* path, enum ti_host_file_mode_t mode, enum ti_errc_t* errc_out);

/**
 * @brief 
 * @param file 
 * @param errc_out 
 */
void ti_close_host_file(struct ti_host_file_t file, enum ti_errc_t* errc_out);

void ti_write_host_file(struct ti_host_file_t file, const char* str, enum ti_errc_t* errc_out);

int32_t ti_read_host_file(struct ti_host_file_t file, char* buf, int32_t size, enum ti_errc_t* errc_out);

int32_t ti_get_host_file_pos(struct ti_host_file_t file, enum ti_errc_t* errc_out);

void ti_set_host_file_pos(struct ti_host_file_t file, int32_t pos, enum ti_errc_t* errc_out);

void ti_move_host_file_pos(struct ti_host_file_t file, int32_t offset, enum ti_errc_t* errc_out);

int32_t ti_get_host_file_len(struct ti_host_file_t file, enum ti_errc_t* errc_out);

bool ti_is_host_file_tty(struct ti_host_file_t file, enum ti_errc_t* errc_out);

bool ti_check_host_file(const char* path, enum ti_errc_t* errc_out);

enum ti_host_file_mode_t ti_get_host_file_mode(struct ti_host_file_t file, enum ti_errc_t* errc_out);

bool ti_is_valid_host_file(struct ti_host_file_t file);

bool ti_is_host_file_equal(struct ti_host_file_t file_1, struct ti_host_file_t file_2, enum ti_errc_t* errc_out);

/**************************************************************************************************
 * @section Standard Input/Output Utilities
 **************************************************************************************************/

void ti_write_host_io(const char* str, enum ti_errc_t* errc_out);

int32_t ti_read_host_io(char* buf, int32_t size, enum ti_errc_t* errc_out);

/**************************************************************************************************
 * @section Time Utilities
 **************************************************************************************************/

int64_t ti_get_host_time(enum ti_errc_t* errc_out);