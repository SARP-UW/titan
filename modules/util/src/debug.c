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
 * @file modules/util/src/debug.c
 * @authors Aaron McBride
 * @brief Implementation of debugging utilities.
 */

#include "util/debug.h"

// Halts the program if 'cond' is false
void ti_assert(bool cond) {
  #if TI_DEBUG
    if (!cond) {
      asm volatile (
        "isb \n\t"
        "dsb \n\t"
        "bkpt #0"
        :::"memory"
      );
    }
  #endif
}

// Triggers a breakpoint in the debugger
void ti_breakpoint(void) {
  #if TI_DEBUG
    asm volatile (
      "isb \n\t"
      "dsb \n\t"
      "bkpt #0"
      :::"memory"
    );
  #endif
}