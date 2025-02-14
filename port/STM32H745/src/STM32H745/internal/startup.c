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
 * @file src/STM32H745_CM7/startup.c
 * @authors Aaron McBride
 * @brief Reset handler and program startup code.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "STM32H745/internal/mmio.h"
#include "STM32H745/internal/interrupt.h"

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Memory Initialization/Finalization Routines
   ************************************************************************************************/

  // Initializes CM7 ITCM section
  static void init_cm7_itcm(void) {
    extern uint32_t __cm7_itcm_start__;
    extern uint32_t __cm7_itcm_dst__;
    extern uint32_t __cm7_itcm_end__;
    uint32_t* itcm_src = &__cm7_itcm_start__;
    uint32_t* itcm_dst = &__cm7_itcm_dst__;
    uint32_t* const itcm_end = &__cm7_itcm_end__;
    while (itcm_dst < itcm_end) {
      *itcm_dst++ = *itcm_src++;
    }
  }

  // Initializes CM7 DTCM section
  static void init_cm7_dtcm(void) {
    extern uint32_t __cm7_dtcm_start__;
    extern uint32_t __cm7_dtcm_dst__;
    extern uint32_t __cm7_dtcm_end__;
    uint32_t* dtcm_src = &__cm7_dtcm_start__;
    uint32_t* dtcm_dst = &__cm7_dtcm_end__;
    uint32_t* const dtcm_end = &__cm7_dtcm_dst__;
    while (dtcm_dst < dtcm_end) {
      *dtcm_dst++ = *dtcm_src++;
    }
  }

  // Initializes kernal memory section
  static void init_kmem(void) {
    extern uint32_t __kmem_start__;
    extern uint32_t __kmem_dst__;
    extern uint32_t __kmem_end__;
    uint32_t* kmem_src = &__kmem_start__;
    uint32_t* kmem_dst = &__kmem_dst__;
    uint32_t* const kmem_end = &__kmem_end__;
    while (kmem_dst < kmem_end) {
      *kmem_dst++ = *kmem_src++;
    }
  }

  // Initializes .bss section (zeros it)
  static void init_bss(void) {
    extern uint32_t __cm4_bss_start__;
    extern uint32_t __cm4_bss_end__;
    uint32_t* bss_current = &__cm4_bss_start__;
    uint32_t* const bss_end = &__cm4_bss_end__;
    while (bss_current < bss_end) {
      *bss_current++ = 0U;
    }
  }

  // Initializes .data section
  static void init_data(void) {
    extern uint32_t __data_start__;
    extern uint32_t __data_dst__;
    extern uint32_t __data_end__;
    uint32_t* data_src = &__data_start__;
    uint32_t* data_dst = &__data_dst__;
    uint32_t* const data_end = &__data_end__;
    while (data_dst < data_end) {
      *data_dst++ = *data_src++;
    }
  }

  // Initializes heap section (zeros it)
  static void init_heap(void) {
    extern uint32_t __heap_start__;
    extern uint32_t __heap_end__;
    uint32_t* heap_current = &__heap_start__;
    uint32_t* const heap_end = &__heap_end__;
    while(heap_current < heap_end) {
      *heap_current++ = 0U;
    }
  }

  /************************************************************************************************
   * Program Initialization/Finialization Routines
   ************************************************************************************************/

  // Invokes pre-constructor functions
  static void invoke_preinit(void) {
    typedef void (*func_t)(void);
    extern func_t __preinit_array_start__;
    extern func_t __preinit_array_end__;
    func_t* current_fn = &__preinit_array_start__;
    func_t* const end_fn = &__preinit_array_end__;
    while (current_fn < end_fn) {
      (*current_fn++)();
    }
  }

  // Invokes constructor functions
  static void invoke_init(void) {
    typedef void (*func_t)(void);
    extern func_t __init_array_start__;
    extern func_t __init_array_end__;
    func_t* current_fn = &__init_array_start__;
    func_t* const end_fn = &__init_array_end__;
    while (current_fn < end_fn) {
      (*current_fn++)();
    }
  }

  // Invokes destructor functions
  static void invoke_fini(void) {
    typedef void (*func_t)(void);
    extern func_t __fini_array_start__;
    extern func_t __fini_array_end__;
    func_t* current_fn = &__fini_array_start__;
    func_t* const end_fn = &__fini_array_end__;
    while (current_fn < end_fn) {
      (*current_fn++)();
    }
  }

  /************************************************************************************************
   * Peripheral Initialization Routines
   ************************************************************************************************/

  // Initializes the clock system
  // static void init_clock_system(void) {
  //   WRITE_FIELD(RCC_CR, RCC_CR_HSION, 1U);
  //   while (READ_FIELD(RCC_CR, RCC_CR_HSIRDY) == 0U);
  // }

  /************************************************************************************************
   * Reset Handler Implementation
   ************************************************************************************************/

  // Main function prototype
  extern void main(void);

  // Reset handler logic for the CM7 core
  void alt_cm7_reset_exc_handler(void) {
    init_cm7_itcm();
    init_cm7_dtcm();
    init_kmem();
    init_data();
    init_bss();
    init_heap();
    invoke_preinit();
    invoke_init();
    main();
    invoke_fini();
  }

  // Reset handler logic for the CM4 core
  void alt_cm4_reset_exc_handler(void) {
    while (true) {
      __asm__ ("nop");
    }
  }

  // Entry point for reset handler (CM7 core)
  // Zeros kernal stack - used by init functions
  __attribute__((naked)) 
  void cm7_reset_exc_handler() {
    __asm__ volatile (
      "cpsid i          \n\t"
      "ldr r0, cm7_kstack_start \n\t"
      "ldr r1, cm7_kstack_end \n\t"
      "mov r2, #4       \n\t"
      "cm7_rst_loop1:   \n\t"
      "cmp r1, r0       \n\t"
      "bcc end          \n\t"
      "str r2, [r0]     \n\t"
      "add r0, r0, #4   \n\t"
      "bl cm7_rst_loop1 \n\t"
      "cm7_rst_end:     \n\t"
      "bl alt_cm7_reset_exc_handler \n\t"
      "cpsie i          \n\t"
      "cm7_rst_loop2:   \n\t"
      "wfi              \n\t"
      "bl cm7_rst_loop2 \n\t"
      "cm7_kstack_start: \n\t"
      ".word __cm7_kstack_start__ \n\t"
      "cm7_kstack_end: \n\t"
      ".weak .word __cm7_kstack_end__ \n\t"
      ::: "r0", "r1", "r2", "memory"
    );
  }

  // Entry point for reset handler (CM4 core)
  // Zeros kernal stack - used by init functions
  __attribute__((naked))
  void cm4_reset_exc_handler() {
    __asm__ volatile (
      "cpsid i          \n\t"
      "ldr r0, cm4_kstack_start \n\t"
      "ldr r1, cm4_kstack_end \n\t"
      "mov r2, #4       \n\t"
      "cm4_rst_loop:    \n\t"
      "cmp r1, r0       \n\t"
      "bcc end          \n\t"
      "str r2, [r0]     \n\t"
      "add r0, r0, #4   \n\t"
      "bl cm4_rst_loop  \n\t"
      "cm4_rst_end:     \n\t"
      "bl alt_cm4_reset_exc_handler \n\t"
      "cpsie i          \n\t"
      "cm4_rst_loop2:   \n\t"
      "wfi              \n\t"
      "bl cm4_rst_loop2 \n\t"
      "cm4_kstack_start: \n\t"
      ".word __cm4_kstack_start__ \n\t"
      "cm4_kstack_end: \n\t"
      ".word __cm4_kstack_end__ \n\t"
      ::: "r0", "r1", "r2", "memory"
    );
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */