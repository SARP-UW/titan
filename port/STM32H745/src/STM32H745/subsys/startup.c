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
 * @internal
 * @file src/STM32H745_CM7/subsys/startup.c
 * @authors Aaron McBride
 * @brief Reset handler and program startup code.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "STM32H745/resource/mmio.h"
#include "STM32H745/resource/interrupt.h"

#ifdef __IAR_SYSTEMS_ICC__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Program Initialization/Finialization Routines
   ************************************************************************************************/

  // Loads data from flash to RAM
  static void _load_mem(void) {

    // Type of entries in the load table.
    typedef struct {
      const uint32_t *start; // Start of section to load
      const uint32_t *end;   // End of section to load
      uint32_t *dst;         // Start of location to load section to.
    } load_tbl_t;

    // "Load table" location (defined by linker script)
    extern load_tbl_t __load_table_start[];
    extern load_tbl_t __load_table_end[];

    // Iterate through sections in the load table
    const int32_t length = __load_table_end - __load_table_start;
    for (int32_t i = 0; i < length; i++) {

      // Copy each word in the section from flash (start) to RAM (dst)
      const int32_t size = __load_table_start[i].end - __load_table_start[i].start;
      for (int32_t j = 0; j < size; j++) {
        __load_table_start[i].dst[j] = __load_table_start[i].start[j];
      }
    }
  }

  // Clears required regions in RAM
  static void _clear_mem(void) {

    // Type of entries in the clear table.
    typedef struct {
      uint32_t *start; // Start of section to clear
      uint32_t *end;   // End of section to clear
    } clear_tbl_t;

    // "Clear table" location (defined by linker script)
    extern clear_tbl_t __clear_table_start[];
    extern clear_tbl_t __clear_table_end[];

    // Iterate through entries in the clear table
    const int32_t length = __clear_table_end - __clear_table_start;
    for (int32_t i = 0; i < length; i++) {

      // Assign 0 to each word in the section (clear it)
      const int32_t size = __clear_table_start[i].end - __clear_table_start[i].start;
      for (int32_t j = 0; j < size; j++) {
        __clear_table_start[i].start[j] = 0U;
      }
    }
  }

  // newlib/picolib provide init_array and fini_array functions
  #if !defined(__NEWLIB__) && !defined(__PICOLIB__)

    // Invokes pre-initialization functions
    static void _invoke_preinit(void) {

      // Pre-initialization function prototype
      typedef void (*preinit_func_t)(void);

      // Pre-initialization function table location (defined by linker script)
      extern preinit_func_t __preinit_array_start[];
      extern preinit_func_t __preinit_array_end[];

      // Iterate through the preinit function table and invoke functions
      const int32_t length = __preinit_array_end - __preinit_array_start;
      for (int32_t i = 0; i < length; i++) {
        if (__preinit_array_start[i] != NULL) {
          __preinit_array_start[i]();
        }
      }
    }

    // Invokes initialization functions
    static void _invoke_init(void) {

      // Initialization function prototype
      typedef void (*init_func_t)(void);

      // Initialization function table location (defined by linker script)
      extern init_func_t __init_array_start[];
      extern init_func_t __init_array_end[];

      // Iterate through the init function table and invoke functions
      const int32_t length = __init_array_end - __init_array_start;
      for (int32_t i = 0; i < length; i++) {
        if (__init_array_start[i] != NULL) {
          __init_array_start[i]();
        }
      }
    }

    // Invokes finalization functions
    static void _invoke_fini(void) {

      // Finalization function prototype
      typedef void (*fini_func_t)(void);

      // Finalization function table location (defined by linker script)
      extern fini_func_t __fini_array_start[];
      extern fini_func_t __fini_array_end[];

      // Iterate through the fini function table and invoke functions
      const int32_t length = __fini_array_end - __fini_array_start;
      for (int32_t i = 0; i < length; i++) {
        if (__fini_array_start[i] != NULL) {
          __fini_array_start[i]();
        }
      }
    }

  #endif

  /************************************************************************************************
   * Core Initialization/Finalization Routines
   ************************************************************************************************/

  #define _CORE_CM7_CACHE_SIZE
  #define _CORE_CM7_CACHE_LINE_SIZE

  void init_core_cm7(void) {

    // Set thread mode to privileged
    __asm__ volatile (
      "mrs r0, CONTROL \n\t"
      "orr r0, r0, 0x1 \n\t"
      "msr CONTROL, r0 \n\t"
    );

    // Enable the FPU
    SET_FIELD(FPU_CPACR, FPU_CPACR_CP);

    // Enable the instruction cache
    SET_FIELD(SCB_CCR, SCB_CCR_IC);

    // Enable the data cache


  }

  void init_core_cm4(void) {

    // Set thread mode to privileged
    __asm__ volatile (
      "mrs r0, CONTROL \n\t"
      "orr r0, r0, 0x1 \n\t"
      "msr CONTROL, r0 \n\t"
    );

    // Enable the FPU
    SET_FIELD(FPU_CPACR, FPU_CPACR_CP);

  }

  /************************************************************************************************
   * Reset Handler Entry Functions
   ************************************************************************************************/

  // Entry point for CM7 reset handler
  __attribute__((naked)) 
  void cm7_reset_exc_handler() {
    __asm__ volatile (
      "cpsid i                       \n\t" // Disable interrupts
      "ldr r0, =__cm7_kstack_start   \n\t" // Address of start of stack section
      "ldr r1, =__cm7_kstack_end     \n\t" // Address of end of stack section
      "ldr r2, =0x0                  \n\t" // Clear r2 (used for zeroing memory)
      "cm7_rst_loop1:                \n\t" 
      "cmp r1, r0                    \n\t"
      "bcc cm7_rst_end               \n\t" // If at end of stack section, end loop
      "str r2, [r0]                  \n\t" // Assign 0 (word) to the current memory location
      "add r0, r0, 0x4               \n\t" // Increment the memory location by 4 (size of word)
      "b cm7_rst_loop1               \n\t"
      "cm7_rst_end:                  \n\t"
      "bl alt_cm7_reset_exc_handler  \n\t" // "Call" the main reset handler (below)
      "cm7_rst_loop2:                \n\t" // Infinite loop
      "wfi                           \n\t" // Wait for interrupt (likely reset interrupt)
      "b cm7_rst_loop2               \n\t"
      ::: "r0", "r1", "r2", "memory"
    );
  }

  // Entry point for CM4 reset handler
  __attribute__((naked))
  void cm4_reset_exc_handler() {
    __asm__ volatile (
      "cpsid i                       \n\t" // Disable interrupts
      "ldr r0, =__cm4_kstack_start   \n\t" // Address of start of stack section
      "ldr r1, =__cm4_kstack_end     \n\t" // Address of end of stack section
      "ldr r2, =0x0                  \n\t" // Clear r2 (used for zeroing memory)
      "cm4_rst_loop1:                \n\t" 
      "cmp r1, r0                    \n\t"
      "bcc cm4_rst_end               \n\t" // If at end of stack section, end loop
      "str r2, [r0]                  \n\t" // Assign 0 (word) to the current memory location
      "add r0, r0, 0x4               \n\t" // Increment the memory location by 4 (size of word)
      "b cm4_rst_loop1               \n\t"
      "cm4_rst_end:                  \n\t"
      "bl alt_cm4_reset_exc_handler  \n\t" // "Call" the main reset handler (below)
      "cm4_rst_loop2:                \n\t" // Infinite loop
      "wfi                           \n\t" // Wait for interrupt (likely reset interrupt)
      "b cm4_rst_loop2               \n\t"
      ::: "r0", "r1", "r2", "memory"
    );
  }

  /************************************************************************************************
   * Primary Reset Handlers
   ************************************************************************************************/

  // Main function prototype
  extern void main(void);

  // Primary reset handler for the CM7 core
  __attribute__((used))
  void alt_cm7_reset_exc_handler(void) {
    _load_mem();
    _clear_mem();
    #if (__NEWLIB__) || (__PICOLIB__)
      __libc_init_array();
    #else
      _invoke_preinit();
      _invoke_init();
    #endif
    main();
    #if (__NEWLIB__) || (__PICOLIB__)
      __libc_fini_array();
    #else
      _invoke_fini();
    #endif
  }

  // Primary reset handler for the CM4 core
  __attribute__((used))
  void alt_cm4_reset_exc_handler(void) {
    while (true) { 
      __asm__ ("nop"); 
    }
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */