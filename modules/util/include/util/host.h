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
 * @file modules/util/include/util/host.h
 * @authors Aaron McBride
 * @brief Semi-hosting facilities.
 */

#pragma once
#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "util/errc.h"

/**************************************************************************************************
 * @section File Utilities
 **************************************************************************************************/

struct ti_file_t {
  const int32_t id;
  const void* const handle;
};

enum ti_file_mode_t {
  TI_FILE_MODE_READ,
  TI_FILE_MODE_WRITE,
  TI_FILE_MODE_APPEND,
  TI_FILE_MODE_READ_WRITE,
  TI_FILE_MODE_WRITE_READ,
  TI_FILE_MODE_APPEND_READ,
};

extern struct ti_file_t TI_INVALID_FILE;

#define TI_FILE_MEM_SIZE 0 

struct ti_file_t ti_open_host_file(void* mem, const char* path, 
    enum ti_file_mode_t mode, enum ti_errc_t* errc_out);

void ti_close_host_file(struct ti_file_t file);

__attribute__((format(printf, 2, 3))) void ti_write_host_file(
    struct ti_file_t file, const char* fmt, ...);

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