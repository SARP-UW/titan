/**
 * This file is part of the Titan Flight Computer Project
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
 * @file src/port/GCC_STM32H745ZI_CM7/internal/ref.h
 * @authors Aaron McBride
 * @brief Reference constants for implementation.
 */

#ifndef SRC_PORT_GCC_STM32H745ZI_CM7_INTERNAL_REF_H
#define SRC_PORT_GCC_STM32H745ZI_CM7_INTERNAL_REF_H

  #include <stdint.h>

  #if defined(__cplusplus)
    extern "C" {
  #endif

    /**********************************************************************************************
     * @section Linker Symbols
     **********************************************************************************************/
      
    extern uint32_t __stack_start; /* address of start of stack */
    extern uint32_t __stack_end;   /* address of end of stack */

    extern uint32_t __text_start; /* address of start of .text section */
    extern uint32_t __text_end;   /* address of end of .text section */

    extern uint32_t __data_start; /* address of start of .data section */
    extern uint32_t __data_end;   /* address of end of .data section */

    extern uint32_t __rodata_start; /* address of start of .rodata section */
    extern uint32_t __rodata_end;   /* address of end of .rodata section */

    extern uint32_t __bss_start; /* address of start of .bss section */
    extern uint32_t __bss_end;   /* address of end of .bss section */

    extern uint32_t __heap_start; /* address of start of heap */
    extern uint32_t __heap_end;   /* address of end of heap */

    extern uint32_t __user_flash_start; /* address of start of user flash memory */
    extern uint32_t __user_flash_end;   /* address of end of user flash memory */

    extern uint32_t __common_start; /* address of start of common memory section */
    extern uint32_t __common_end;   /* address of end of common memory section */

  #if defined(__cplusplus)
    } /* extern "C" */
  #endif

#endif /* SRC_PORT_GCC_STM32H745ZI_CM7_INTERNAL_VTABLE_H */