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
#include <stddef.h>
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
  TI_HOST_FILE_MODE_READ        = 1,  /** @brief (POSIX mode: "r") Opens a file for reading. File must exist. */
  TI_HOST_FILE_MODE_WRITE       = 5,  /** @brief (POSIX mode: "w") Opens a file for writing. New file is created (will overwrite). */
  TI_HOST_FILE_MODE_APPEND      = 9,  /** @brief (POSIX mode: "a") Opens a file for appending. Cursor placed at end of file on write. File may exist (won't overwrite). */
  TI_HOST_FILE_MODE_READ_WRITE  = 3,  /** @brief (POSIX mode: "r+") Opens a file for reading and writing. File must exist. */
  TI_HOST_FILE_MODE_WRITE_READ  = 7,  /** @brief (POSIX mode: "w+") Opens a file for writing and reading. New file is created (can overwrite). */
  TI_HOST_FILE_MODE_APPEND_READ = 11, /** @brief (POSIX mode: "a+") Opens a file for appending and reading. Cursor placed at end of file on write. File must exist. */
};

/** @brief Size of memory block required for a host file. */
#define TI_HOST_FILE_MEM_SIZE 52

/** @brief Reference invalid host file handle (guaranteed to always be invalid).  */
static const struct ti_host_file_t TI_INVALID_HOST_FILE = {
  .id = -1,
  .handle = NULL,
};

/**
 * @brief Opens a file on the host machine.
 * @param mem (void*) Memory used internally for the host file instance (must be at least TI_HOST_FILE_MEM_SIZE bytes).
 * @param path (const char*) Absolute path to the file to open.
 * @param mode (enum ti_host_file_mode_t) Mode to open the file in.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (struct ti_host_file_t) Handle to the opened file (equal to TI_INVALID_HOST_FILE if an error occurred).
 * @note - If the host allows it, multiple instances of the same file may be opened.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [mem] or @p [path] are NULL, or @p [mode] is TI_HOST_FILE_MODE_INVALID.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
struct ti_host_file_t ti_open_host_file(void* mem, const char* path, enum ti_host_file_mode_t mode, enum ti_errc_t* errc_out);

/**
 * @brief Closes a file open on the host machine.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - The state of the file is guaranteed to be unchanged if an error other than TI_ERRC_HOST or TI_ERRC_INTERNAL occurs.
 * @note - If TI_ERRC_HOST or TI_ERRC_INTERNAL are raised, the state of the file is undefined.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device or if this function is called from an interrupt.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open).
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
void ti_close_host_file(struct ti_host_file_t file, enum ti_errc_t* errc_out);

/**
 * @brief Writes a string to a file on the host machine.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param str (const char*) The string to write to the file.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - This function writes @p [str] into the given file starting at the location of the file's cursor (overwriting any existing data).
 * @note - If the file is open in an "append" mode the cursor is automatically set to the end of the file prior to writing.
 * @note - If the file is an interactive device (TTY) the position of the cursor has no effect, @p [str] is written to the output stream directly.
 * @note - The state of the file is guaranteed to be unchanged if an error other than TI_ERRC_HOST or TI_ERRC_INTERNAL occurs.
 * @note - If TI_ERRC_HOST or TI_ERRC_INTERNAL are raised, the state of the file is undefined.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device, if this function is called from an interrupt or if the file was opened in a read-only mode.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open) or @p [str] is NULL.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_TIMEOUT is raised if this thread can't gain exclusive access to the file before the configured timeout duration.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
void ti_write_host_file(struct ti_host_file_t file, const char* str, enum ti_errc_t* errc_out);

/**
 * @brief Reads data from a file on the host machine.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param buf (char*) Buffer to place read characters into.
 * @param size (int32_t) Maximum number of bytes to read.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (int32_t) Number of bytes read (or -1 if an error occurred).
 * @note - This function reads up to @p [size] bytes from the file starting at the location of the file's cursor.
 * @note - If the file is an interactive device (TTY) the position of the cursor has no effect, data is read from the input stream directly.
 * @note - Reaching the end of the file before @p [size] bytes are read will not raise an error.
 * @note - The state of the file is guaranteed to be unchanged if an error other than TI_ERRC_HOST or TI_ERRC_INTERNAL occurs.
 * @note - If TI_ERRC_HOST or TI_ERRC_INTERNAL are raised, the state of the file is undefined.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device, if this function is called from an interrupt, or if the file was opened in a write-only mode.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open), if @p [buf] is NULL, or if @p [size] is negative.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_TIMEOUT is raised if this thread can't gain exclusive access to the file before the configured timeout duration.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
int32_t ti_read_host_file(struct ti_host_file_t file, char* buf, int32_t size, enum ti_errc_t* errc_out);

/**
 * @brief Gets the current position of a file's cursor on the host machine.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (int32_t) Current position of the file's cursor (in bytes from start of file), or -1 if an error occurred.
 * @note - The state of the file is guaranteed to be unchanged if an error other than TI_ERRC_INTERNAL occurs.
 * @note - If TI_ERRC_INTERNAL is raised, the state of the file is undefined.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if this function is called from an interrupt, or if the file is an interactive device (TTY).
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open).
 * @warning - TI_ERRC_TIMEOUT is raised if this thread can't gain exclusive access to the file before the configured timeout duration.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
int32_t ti_get_host_file_pos(struct ti_host_file_t file, enum ti_errc_t* errc_out);

/**
 * @brief Sets the current position of a file's cursor on the host machine.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param pos (int32_t) New position of the file's cursor (in bytes, from start of file if positive, or end of file if negative).
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - The state of the file is guaranteed to be unchanged if an error other than TI_ERRC_HOST or TI_ERRC_INTERNAL occurs.
 * @note - If TI_ERRC_HOST or TI_ERRC_INTERNAL are raised, the state of the file is undefined.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device, if this function is called from an interrupt, or if the file is an interactive device (TTY).
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open), or if @p [pos] is out of bounds of the file.
 * @warning - TI_ERRC_TIMEOUT is raised if this thread can't gain exclusive access to the file before the configured timeout duration.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
void ti_set_host_file_pos(struct ti_host_file_t file, int32_t pos, enum ti_errc_t* errc_out);

/**
 * @brief Moves the current position of a file's cursor on the host machine.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param offset (int32_t) Offset to move the cursor position by (in bytes).
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - The state of the file is guaranteed to be unchanged if an error other than TI_ERRC_HOST or TI_ERRC_INTERNAL occurs.
 * @note - If TI_ERRC_HOST or TI_ERRC_INTERNAL are raised, the state of the file is undefined.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device, if this function is called from an interrupt, or if the file is an interactive device (TTY).
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open), or if @p [offset] results in the cursor's position being out of bounds of the file.
 * @warning - TI_ERRC_TIMEOUT is raised if this thread can't gain exclusive access to the file before the configured timeout duration.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
void ti_move_host_file_pos(struct ti_host_file_t file, int32_t offset, enum ti_errc_t* errc_out);

/**
 * @brief Gets the length of a file on the host machine.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (int32_t) Length of the file in bytes, or -1 if an error occurs.
 * @note - The state of the file is guaranteed to be unchanged if an error other than TI_ERRC_INTERNAL occurs.
 * @note - If TI_ERRC_INTERNAL is raised, the state of the file is undefined.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device, if this function is called from an interrupt, or if the file is an interactive device (TTY).
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open).
 * @warning - TI_ERRC_TIMEOUT is raised if this thread can't gain exclusive access to the file before the configured timeout duration.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
int32_t ti_get_host_file_len(struct ti_host_file_t file, enum ti_errc_t* errc_out);

/**
 * @brief Determines if a file on the host machine is an interactive device.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @return (bool) True if no error occurs and the file is an interactive device (TTY), or false otherwise.
 * @note - The state of the file is guaranteed to be unchanged if an error occurs.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open).
 */
bool ti_is_host_file_tty(struct ti_host_file_t file, enum ti_errc_t* errc_out);

/**
 * @brief Checks for the existance of a file on the host machine.
 * @param path (const char*) Absolute path to the file to probe.
 * @returns (bool) True if no error occurs and the file exists on the host machine, or false otherwise.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [path] is NULL.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 */
bool ti_check_host_file(const char* path, enum ti_errc_t* errc_out);

/**
 * @brief Gets the mode of a file on the host machine.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (enum ti_host_file_mode_t) Mode the file was opened with, or TI_HOST_FILE_MODE_INVALID if an error occurs.
 * @note - The state of the file is guaranteed to be unchanged if an error occurs.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [file] does not exist (not open).
 */
enum ti_host_file_mode_t ti_get_host_file_mode(struct ti_host_file_t file, enum ti_errc_t* errc_out);

/**
 * @brief Determines if a host file instance is currently open.
 * @param file (struct ti_host_file_t) Handle to the target host file.
 * @returns (bool) True if the file instance is currently open, or false otherwise.
 */
bool ti_is_valid_host_file(struct ti_host_file_t file);

/**
 * @brief Determines if two host file instances are equal.
 * @param file_1 (struct ti_host_file_t) Handle to the first host file.
 * @param file_2 (struct ti_host_file_t) Handle to the second host file.
 * @return (bool) True if the two host file handles identify the same internal host file instance (even if closed), or false otherwise.
 */
bool ti_is_host_file_equal(struct ti_host_file_t file_1, struct ti_host_file_t file_2);

/**************************************************************************************************
 * @section Standard Input/Output Utilities
 **************************************************************************************************/

/**
 * @brief Writes a string to the host machine's standard output (I/O).
 * @param str (const char*) The string to write.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @note - The state of the host I/O is guaranteed to be unchanged if an error other than TI_ERRC_HOST or TI_ERRC_INTERNAL occurs.
 * @note - The state of the host I/O is undefined if TI_ERRC_HOST or TI_ERRC_INTERNAL is raised.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device, or if this function is called from an interrupt.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [str] is NULL.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_TIMEOUT is raised if this thread can't gain exclusive access to the host I/O before the configured timeout duration.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
void ti_write_host_io(const char* str, enum ti_errc_t* errc_out);

/**
 * @brief Reads a string from the host machine's standard input (I/O).
 * @param buf (char*) Buffer to place read characters into.
 * @param size (int32_t) Maximum number of bytes to read.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (int32_t) The number of bytes read, or -1 if an error occurred.
 * @note - This function will read from the host I/O until either @p [size] bytes have been read or until '\0', '\n', or '\r' is encountered.
 * @note - This function will not raise an error if less than @p [size] bytes are read.
 * @note - The state of the host I/O is guaranteed to be unchanged if an error other than TI_ERRC_HOST or TI_ERRC_INTERNAL occurs.
 * @note - The state of the host I/O is undefined if TI_ERRC_HOST or TI_ERRC_INTERNAL is raised.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device, or if this function is called from an interrupt.
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [buf] is NULL or @p [size] is negative.
 * @warning - TI_ERRC_HOST is raised if an error occurs on the host machine.
 * @warning - TI_ERRC_TIMEOUT is raised if this thread can't gain exclusive access to the host I/O before the configured timeout duration.
 * @warning - TI_ERRC_INTERNAL may be raised by this function.
 */
int32_t ti_read_host_io(char* buf, int32_t size, enum ti_errc_t* errc_out);

/**************************************************************************************************
 * @section Time Utilities
 **************************************************************************************************/

/**
 * @brief Gets the current time from the host machine.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @returns (int64_t) The current time in seconds since the unix epoch, or -1 if an error occurred.
 * @warning - TI_ERRC_UNSUPPORTED is raised if TI_SEMIHOSTING_ENABLED is false.
 * @warning - TI_ERRC_INVALID_OP is raised if no debugger is connected to the device.
 */
int64_t ti_get_host_time(enum ti_errc_t* errc_out);