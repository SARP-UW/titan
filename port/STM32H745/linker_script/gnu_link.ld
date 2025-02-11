/**
 * This file is part of the titan project.
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
 * @file port/STM32H745/resource/gcc_link.ld
 * @authors Aaron McBride
 * @brief GCC linker script for the STM32H745 port.
 */

/* Required vtable alignment. */
#define VTABLE_ALIGNMENT 1024

/* Required stack alignment. */
#define STACK_ALIGNMENT 8

/* Required vtable alignment. */
#define HEAP_ALIGNMENT 8

/* Kernel stack size. */
#define KSTACK_SIZE 1024

/* Define the memory layout */
MEMORY 
{
  FLASH_MEM (rx) : ORIGIN = 0x08000000, LENGTH = 2048k /* Internal flash memory */
  AXI_SRAM (xrw) : ORIGIN = 0x24000000, LENGTH = 512k  /* AXI SRAM */
  SRAM123 (xrw)  : ORIGIN = 0x10000000, LENGTH = 288k  /* SRAM 1, 2 and 3 */
  SRAM4 (xrw)    : ORIGIN = 0x38000000, LENGTH = 64k   /* SRAM 4 */
  BKUP_RAM (xrw) : ORIGIN = 0x38800000, LENGTH = 4k    /* Backup RAM */
  CM7_ITCM (xrw) : ORIGIN = 0x00000000, LENGTH = 64k   /* CM7 Instruction Tightly Coupled Memory */
  CM7_DTCM (xrw) : ORIGIN = 0x20000000, LENGTH = 128k  /* CM7 Data Tightly Coupled Memory */
}

/* Define the output sections */
SECTIONS
{

  /************************************************************************************************
   * Vector Table Sections
   ************************************************************************************************/

  /* Vector table for cm7 core */
  .cm7_vtable : 
  {
    . = ALIGN(VTABLE_ALIGNMENT);
    __cm7_vtable_start__ = .;
    LONG(__cm7_kstack_end__);
    KEEP(*(.cm7_vtable))
    . = ALIGN(VTABLE_ALIGNMENT);
    __cm7_vtable_end__ = .;
  } > CM7_ITCM

  /* Vector table for cm4 core */
  .cm4_vtable : 
  {
    . = ALIGN(VTABLE_ALIGNMENT);
    __cm4_vtable_start__ = .;
    LONG(__cm4_kstack_end__);
    KEEP(*(.cm4_vtable))
    . = ALIGN(VTABLE_ALIGNMENT);
    __cm4_vtable_end__ = .;
  } > SRAM123

  /************************************************************************************************
   * Kernal Stack Sections
   ************************************************************************************************/

  /* Kernel stack for cm7 core */
  .cm7_kstack : 
  {
    . = ALIGN(STACK_ALIGNMENT);
    __cm7_kstack_start__ = .;
    . += KSTACK_SIZE;
    . = ALIGN(STACK_ALIGNMENT);
    __cm7_kstack_size__ = .;
  } > CM7_DTCM

  /* Kernel stack for cm4 core */
  .cm4_kstack : 
  {
    . = ALIGN(STACK_ALIGNMENT);
    __cm4_kstack_start__ = .;
    . += KSTACK_SIZE;
    . = ALIGN(STACK_ALIGNMENT);
    __cm4_kstack_end__ = .;
  } > SRAM123

  /************************************************************************************************
   * Tight Coupled Memory Sections
   ************************************************************************************************/

  /* ITCM Section (instruction tightly coupled memory) */
  .cm7_itcm :
  {
    . = ALIGN(4);
    __cm7_isr_start__ = .;
    *(.cm7_itcm)
    . = ALIGN(4);
    __cm7_isr_end__ = .;
  } > CM7_ITCM

  /* DTCM Section (data tightly coupled memory) */
  .cm7_dtcm :
  {
    . = ALIGN(4);
    __cm7_dcm_start__ = .;
    *(.cm7_dtcm)
    . = ALIGN(4);
    __cm7_dcm_end__ = .;
  } > CM7_DTCM

  /************************************************************************************************
   * ARM ABI Sections
   ************************************************************************************************/ 

  /* Exception table in flash bank 1 */
  .arm_extab :
  {
    __extab_start = .;
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    __arm_extab = .;
  } > FLASH_MEM

  /* Exception index table in flash bank 1 */
  .arm_exidx :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } > FLASH_MEM

  /* ARM attributes section */
  .ARM.attributes : 
  { 
    __arm_attributes_start__ = .;
    *(.ARM.attributes) 
    __arm_attributes_end__ = .;
  } > FLASH_MEM

  /************************************************************************************************
   * Initialization/Finalization Function Array Sections
   ************************************************************************************************/

  /* Pre-initialization function array in flash bank 1 */
  .preinit_array :
  {
    . = ALIGN(4);
    __preinit_array_start__ = .;
    KEEP (*(.preinit_array))
    . = ALIGN(4);
    __preinit_array_end__ = .;
  } > FLASH_MEM


  /* Initialization function array in flash bank 1 */
  .init_array :
  {
    . = ALIGN(4);
    __init_array_start__ = .;
    KEEP (*(SORT(.init_array*)))
    KEEP (*(.init_array))
    . = ALIGN(4);
    __init_array_end__ = .;
  } > FLASH_MEM

  /* Finalization function array in flash bank 1 */
  .fini_array :
  {
    . = ALIGN(4);
    __fini_array_start__ = .;
    KEEP (*(SORT(.fini_array*)))
    KEEP (*(.fini_array))
    . = ALIGN(4);
    __fini_array_end__ = .;
  } > FLASH_MEM

  /************************************************************************************************
   * Text Section
   ************************************************************************************************/

  .text :
  {
    . = ALIGN(4);
    __text_start__ = .;
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
    __text_end__ = .;
  } > FLASH_MEM

  /************************************************************************************************
   * Read-Only Data Section
   ************************************************************************************************/

  .rodata :
  {
    . = ALIGN(4);
    __rodata_start__ = .;
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
    __rodata_end__ = .;
  } > FLASH_MEM

  /************************************************************************************************
   * Data Sections
   ************************************************************************************************/

  /* Program data section 1 (axi sram) */
  .data1 :
  {
    . = ALIGN(4);
    __data1_start__ = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    __data1_end__ = .;
  } > AXI_SRAM AT > FLASH_MEM

  /* Program data section 2 (sram 1, 2 and 3) */
  .data2 :
  {
    . = ALIGN(4);
    __data2_start__ = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    __data2_end__ = .;
  } > SRAM123 AT > FLASH_MEM

  /* Program data section 3 (sram 4) */
  .data3 :
  {
    . = ALIGN(4);
    __data3_start__ = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    __data3_end__ = .;
  } > SRAM4 AT > FLASH_MEM

  /* Data section table */
  .data_table :
  {
    . = ALIGN(4);
    __data_table_start__ = .;
    LONG(__data1_start__)
    LONG(LOADADDR(.data1))
    LONG(__data1_end__)
    LONG(__data2_start__)
    LONG(LOADADDR(.data2))
    LONG(__data2_end__)
    LONG(__data3_start__)
    LONG(LOADADDR(.data3))
    LONG(__data3_end__)
    . = ALIGN(4);
    __data_table_end__ = .;
  }

  /************************************************************************************************
   * User Flash Section
   ************************************************************************************************/

  .user_flash :
  {
    . = ALIGN(4);
    __user_flash_start__ = .;
    . += LENGTH(FLASH_MEM);
    . = ALIGN(4);
    __user_flash_end__ = .;
  } > FLASH_MEM

  /************************************************************************************************
   * BSS Sections
   ************************************************************************************************/

  /* Program bss section 1 (axi sram) */
  .bss1 :
  {
    . = ALIGN(4);
    __bss1_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss1_end__ = .;
  } > AXI_SRAM

  /* Program bss section 2 (sram 1, 2 and 3) */
  .bss2 :
  {
    . = ALIGN(4);
    __bss2_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss2_end__ = .;
  } > SRAM123

  /* Program bss section 3 (sram 4) */
  .bss3 :
  {
    . = ALIGN(4);
    __bss3_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss3_end__ = .;
  } > SRAM4

  /* BSS section table */
  .bss_table :
  {
    . = ALIGN(4);
    __bss_table_start__ = .;
    LONG(__bss1_start__)
    LONG(__bss1_end__)
    LONG(__bss2_start__)
    LONG(__bss2_end__)
    LONG(__bss3_start__)
    LONG(__bss3_end__)
    . = ALIGN(4);
    __bss_table_end__ = .;
  }

  /************************************************************************************************
   * Heap Sections
   ************************************************************************************************/

  /* Heap section 1 (axi sram) */
  .heap1 :
  {
    . = ALIGN(HEAP_ALIGNMENT);
    __heap1_start__ = .;
    . += LENGTH(AXI_SRAM);
    . = ALIGN(HEAP_ALIGNMENT);
    __heap1_end__ = .;
  } > AXI_SRAM

  /* Heap section 2 (sram 1, 2 and 3) */
  .heap2 :
  {
    . = ALIGN(HEAP_ALIGNMENT);
    __heap2_start__ = .;
    . += LENGTH(SRAM123);
    . = ALIGN(HEAP_ALIGNMENT);
    __heap2_end__ = .;
  } > SRAM123

  /* Heap section 3 (sram 4) */
  .heap3 :
  {
    . = ALIGN(HEAP_ALIGNMENT);
    __heap3_start__ = .;
    . += LENGTH(SRAM4);
    . = ALIGN(HEAP_ALIGNMENT);
    __heap3_end__ = .;
  } > SRAM4

  /* Heap section table */
  .heap_table :
  {
    . = ALIGN(4);
    __heap_table_start__ = .;
    LONG(__heap1_start__)
    LONG(__heap1_end__)
    LONG(__heap2_start__)
    LONG(__heap2_end__)
    LONG(__heap3_start__)
    LONG(__heap3_end__)
    . = ALIGN(4);
    __heap_table_end__ = .;
  }

}