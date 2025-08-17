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
 * @file modules/kernel/src/startup.c
 * @authors Aaron McBride
 * @brief Reset handlers and system initialization logic.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "common/mmio.h"
#include "common/interrupt.h"

/************************************************************************************************
 * @section Program Initialization Routines
 ************************************************************************************************/

/**
 * @brief Loads required sections of memory from flash into RAM.
 */
static void load_prog_mem(void) {

  typedef struct {
    const uint32_t *start; // Start of section to load
    const uint32_t *end;   // End of section to load
    uint32_t *dst;         // Start of location to load section to.
  } load_entry_t;

  extern load_entry_t* __load_table_start;
  extern load_entry_t* __load_table_end;

  load_entry_t* cur_entry = __load_table_start;
  while (cur_entry < __load_table_end) {
    const uint32_t* src = cur_entry->start;
    uint32_t* dst = cur_entry->dst;
    while (src < cur_entry->end) {
      *dst++ = *src++;
    }
    cur_entry++;
  }
}

/**
 * @brief Clears required sections of memory. 
 */
static void clear_prog_mem(void) {

  typedef struct {
    uint32_t *start; // Start of section to clear
    uint32_t *end;   // End of section to clear
  } clear_entry_t;

  extern clear_entry_t* __clear_table_start;
  extern clear_entry_t* __clear_table_end;

  clear_entry_t* cur_entry = __clear_table_start;
  while (cur_entry < __clear_table_end) {
    uint32_t* dst = cur_entry->start;
    while (dst < cur_entry->end) {
      *dst++ = 0U;
    }
    cur_entry++;
  }
}

/************************************************************************************************
 * @section Reset Handlers
 ************************************************************************************************/

/**
 * @brief Reset handler for the CM7 core.
 */
void cm7_reset_exc_handler(void) {
  load_prog_mem();
  clear_prog_mem();
  while (true) {
    asm ("wfi");
  }
}

/**
 * @brief Reset handler for the CM4 core.
 */
void cm4_reset_exc_handler(void) {
  while (true) {
    asm ("wfi");
  }
}