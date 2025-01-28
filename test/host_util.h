/**
 * This file is part of the Titan HAL
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
 * @file test/test_util.h
 * @authors Aaron McBride
 * @brief Testing utilities.
 */

// NOTE:
// The functions/resource in this file are intended to be TEMPORARY,
// A proper semi-hosting driver will be implemented in the future.
// As a result, please only use the code found in this file for
// testing purposes, and not in drivers or other production code.

#pragma once
#include <stdint.h>
#include <stdbool.h>

#ifdef __ICCARM__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * @section Host Commands
   **********************************************************************************************/

    /* File operations */
    #define HOST_OPEN   0x01U //Open a file or stream on the host system.
    #define HOST_ISTTY  0x09U //Check whether a file handle is associated with a file or a stream/terminal such as stdout.
    #define HOST_WRITE  0x05U //Write to a file or stream.
    #define HOST_READ   0x06U //Read from a file at the current cursor position.
    #define HOST_CLOSE  0x02U //Closes a file on the host which has been opened by HOST_OPEN.
    #define HOST_FLEN   0x0CU //Get the length of a file.
    #define HOST_SEEK   0x0AU //Set the file cursor to a given position in a file.
    #define HOST_TMPNAM 0x0DU //Get a temporary absolute file path to create a temporary file.
    #define HOST_REMOVE 0x0EU //Remove a file on the host system. Possibly insecure!
    #define HOST_RENAME 0x0FU //Rename a file on the host system. Possibly insecure!

    /* Terminal I/O operations */
    #define HOST_WRITEC 0x03U //Write one character to the debug terminal.
    #define HOST_WRITE0 0x04U //Write a 0-terminated string to the debug terminal.
    #define HOST_READC  0x07U //Read one character from the debug terminal.

    /* Time operations */
    #define HOST_CLOCK    0x10U //Get the current time in clock ticks.
    #define HOST_ELAPSED  0x30U //Get the elapsed time in clock ticks.
    #define HOST_TICKFREQ 0x31U //Get the frequency of the clock ticks.
    #define HOST_TIME     0x11U //Get the current time in seconds since the Unix epoch.

    /* System/Misc. operations */
    #define HOST_ERRNO       0x13U //Returns the value of the C library errno variable that is associated with the semihosting implementation.
    #define HOST_GET_CMDLINE 0x15U //Get commandline parameters for the application to run with (argc and argv for main())
    #define HOST_HEAPINFO    0x16U //Get heap information
    #define HOST_ISERROR     0x08U //Check if a return value is an error code.
    #define HOST_SYSTEM      0x12U //Execute a command on the host system.

  /**********************************************************************************************
   * @section Utilities
   **********************************************************************************************/

  // Haults execution if the given condition is false
  #define assert(cond) ({ \
    if (!(cond)) { \
      asm volatile ("bkpt #0x0"); \
    } \
  })

  // Executes a command on the host system and returns the result.
  inline uint32_t host_cmd(uint32_t id, uint32_t arg) {
    uint32_t res;
    asm volatile (
      "mov r0, %[id_] \n"
      "mov r1, %[arg_] \n"
      "bkpt #0xAB \n"
      "mov %[res_], r0 \n"
      : [res_] "=r" (res)
      : [id_] "r" (id), [arg_] "r" (arg)
      : "r0", "r1"
    );
    return res;
  }

  // Prints a string to the host terminal
  inline void host_print(const char* msg) {
    host_cmd(HOST_WRITE0, (uint32_t)msg);
  }

  // Prints an unsigned integer to the host terminal
  inline void host_print_uint(uint32_t value) {
    char buff[10];
    int32_t i = 0;
    while (value) {
      buff[i++] = (value % 10) + '0';
      value /= 10;
    }
    buff[i] = '\0';
    host_print(buff);
  }

  // Prints an integer to the host terminal
  inline void host_print_int(int32_t value) {
    if (value < 0) { 
      host_cmd(HOST_WRITEC, '-'); 
    }
    host_print_uint((uint32_t)(-value));
  }

#ifdef __cplusplus
  } // extern "C"
#endif