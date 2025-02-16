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
 * @file port/STM32H745/linker_scripts/gnu_link.ld
 * @authors Aaron McBride
 * @brief GNU linker script for the STM32H745 port.
 * @todo Integrate with FMC/QSPI memory (?)
 */

/* Reference constants */
__SYS_ALIGN = 4;
__STACK_ALIGN = 8;
__CM7_KSTACK_SIZE = 512;
__CM4_KSTACK_SIZE = 512;

/* Program entry point */
ENTRY(cm7_reset_exc_handler)

/* Define the memory layout */
MEMORY 
{
  FLASH_BK1 (rx) : ORIGIN = 0x08000000, LENGTH = 1024k /* Internal flash memory */
  FLASH_BK2 (rx) : ORIGIN = 0x08100000, LENGTH = 1024k /* Internal flash memory */
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

  /* Vector table for CM7 core. */
  .cm7_vtable :
  {
    . = ALIGN(__SYS_ALIGN);
    __cm7_vtable_start = .;
    LONG(__cm7_kstack_end);
    KEEP(*(.cm7_vtable .cm7_vtable.*))
    . = ALIGN(__SYS_ALIGN);
    __cm7_vtable_end = .;
  } > FLASH_BK1

  /* Vector table for CM4 core. */
  .cm4_vtable :
  {
    . = ALIGN(__SYS_ALIGN);
    __cm4_vtable_start = .;
    LONG(__cm4_kstack_end);
    KEEP(*(.cm4_vtable .cm4_vtable.*))
    . = ALIGN(__SYS_ALIGN);
    __cm4_vtable_end = .;
  } > FLASH_BK2

  /* Pre-initialization function array. */
  .preinit_array :
  {
    . = ALIGN(__SYS_ALIGN);
    __preinit_array_start = .;
    KEEP(*(.preinit_array))
    . = ALIGN(__SYS_ALIGN);
    __preinit_array_end = .;
  } > FLASH_BK1

  /* Initialization function array. */
  .init_array :
  {
    . = ALIGN(__SYS_ALIGN);
    __init_array_start = .;
    KEEP(*(SORT(.init_array*)))
    KEEP(*(.init_array))
    . = ALIGN(__SYS_ALIGN);
    __init_array_end = .;
  } > FLASH_BK1

  /* Kernel initialization function array. */
  .fini_array :
  {
    . = ALIGN(__SYS_ALIGN);
    __fini_array_start = .;
    KEEP(*(.fini_array))
    KEEP(*(SORT(.fini_array*)))
    . = ALIGN(__SYS_ALIGN);
    __fini_array_end = .;
  } > FLASH_BK1

  /* Read-only (const) program data. */
  .rodata :
  {
    . = ALIGN(__SYS_ALIGN);
    __rodata_start = .;
    *(.rodata .rodata* .gnu.linkonce.r.*)
    . = ALIGN(__SYS_ALIGN);
    __rodata_end = .;
  } > FLASH_BK1

  /* Program text (code) */
  .text :
  {
    . = ALIGN(__SYS_ALIGN);
    __text_start = .;
    *(.text .text.* .gnu.linkonce.t.*)
    . = ALIGN(__SYS_ALIGN);
    __text_end = .;
  } > FLASH_BK2

  .data :
  {
    . = ALIGN(__SYS_ALIGN);
    __data_start = .;
    *(.data .data.*)
    . = ALIGN(__SYS_ALIGN);
    __data_end = .;
  } > AXI_SRAM AT > FLASH_BK1
  __data_dst = LOADADDR(.data);

  /* Program bss (uninitialized data) */
  .bss :
  {
    . = ALIGN(__SYS_ALIGN);
    __bss_start = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(__SYS_ALIGN);
    __bss_end = .;
  } > AXI_SRAM

  /* CM7 kernal stack (clear). */
  .cm7_kstack :
  {
    . = ALIGN(__STACK_ALIGN);
    __cm7_kstack_start = .;
    . += __CM7_KSTACK_SIZE;
    . = ALIGN(__STACK_ALIGN);
    __cm7_kstack_end = .;
  } > CM7_DTCM

  /* CM4 kernal stack (clear). */
  .cm4_kstack :
  {
    . = ALIGN(__STACK_ALIGN);
    __cm4_kstack_start = .;
    . += __CM4_KSTACK_SIZE;
    . = ALIGN(__STACK_ALIGN);
    __cm4_kstack_end = .;
  } > SRAM123

  /* CM7 instruction tightly coupled memory (load). */
  .cm7_itcm_load :
  {
    . = ALIGN(__SYS_ALIGN);
    __cm7_itcm_load_start = .;
    *(.cm7_itcm_load .cm7_itcm_load.*)
    . = ALIGN(__SYS_ALIGN);
    __cm7_itcm_load_end = .;
  } > CM7_ITCM AT > FLASH_BK1
  __cm7_itcm_load_dst = LOADADDR(.cm7_itcm_load);

  /* CM7 instruction tightly coupled memory (clear). */
  .cm7_itcm_clear :
  {
    . = ALIGN(__SYS_ALIGN);
    __cm7_itcm_clear_start = .;
    *(.cm7_itcm_clear .cm7_itcm_clear.*)
    . = ALIGN(__SYS_ALIGN);
    __cm7_itcm_clear_end = .;
  } > CM7_ITCM

  /* CM7 data tightly coupled memory (load). */
  .cm7_dtcm_load :
  {
    . = ALIGN(__SYS_ALIGN);
    __cm7_dtcm_load_start = .;
    *(.cm7_dtcm_load .cm7_dtcm_load.*)
    . = ALIGN(__SYS_ALIGN);
    __cm7_dtcm_load_end = .;
  } > CM7_DTCM AT > FLASH_BK1
  __cm7_dtcm_load_dst = LOADADDR(.cm7_dtcm_load);

  /* CM7 data tightly coupled memory (clear). */
  .cm7_dtcm_clear :
  {
    . = ALIGN(__SYS_ALIGN);
    __cm7_dtcm_clear_start = .;
    *(.cm7_dtcm_clear .cm7_dtcm_clear.*)
    . = ALIGN(__SYS_ALIGN);
    __cm7_dtcm_clear_end = .;
  } > CM7_DTCM

  /* SRAM 4 (load). */
  .sram4_load :
  {
    . = ALIGN(__SYS_ALIGN);
    __sram4_load_start = .;
    *(.sram4_load .sram4_load.*)
    . = ALIGN(__SYS_ALIGN);
    __sram4_load_end = .;
  } > SRAM4 AT > FLASH_BK1
  __sram4_load_dst = LOADADDR(.sram4_load);

  /* SRAM 4 (clear). */
  .sram4_clear :
  {
    . = ALIGN(__SYS_ALIGN);
    __sram4_clear_start = .;
    *(.sram4_clear .sram4_clear.*)
    . = ALIGN(__SYS_ALIGN);
    __sram4_clear_end = .;
  } > SRAM4

  /* Backup ram (load). */
  .bkup_ram_load :
  {
    . = ALIGN(__SYS_ALIGN);
    __bkup_ram_load_start = .;
    *(.bkup_ram_load .bkup_ram_load.*)
    . = ALIGN(__SYS_ALIGN);
    __bkup_ram_load_end = .;
  } > BKUP_RAM AT > FLASH_BK1
  __bkup_ram_load_dst = LOADADDR(.bkup_ram_load);

  /* Backup ram (clear). */
  .bkup_ram_clear :
  {
    . = ALIGN(__SYS_ALIGN);
    __bkup_ram_clear_start = .;
    *(.bkup_ram_clear .bkup_ram_clear.*)
    . = ALIGN(__SYS_ALIGN);
    __bkup_ram_clear_end = .;
  } > BKUP_RAM

  /* Table of regions to load into ram */
  .load_table :
  {
    . = ALIGN(__SYS_ALIGN);
    __load_table_start = .;
    LONG(__data_start);
    LONG(__data_end);
    LONG(__data_dst);
    LONG(__cm7_itcm_load_start);
    LONG(__cm7_itcm_load_end);
    LONG(__cm7_itcm_load_dst);
    LONG(__cm7_dtcm_load_start);
    LONG(__cm7_dtcm_load_end);
    LONG(__cm7_dtcm_load_dst);
    LONG(__sram4_load_start);
    LONG(__sram4_load_end);
    LONG(__sram4_load_dst);
    LONG(__bkup_ram_load_start);
    LONG(__bkup_ram_load_end);
    LONG(__bkup_ram_load_dst);
    . = ALIGN(__SYS_ALIGN);
    __load_table_end = .;
  } > FLASH_BK1

  .clear_table :
  {
    . = ALIGN(__SYS_ALIGN);
    __clear_table_start = .;
    LONG(__bss_start);
    LONG(__bss_end);
    LONG(__cm7_itcm_clear_start);
    LONG(__cm7_itcm_clear_end);
    LONG(__cm7_dtcm_clear_start);
    LONG(__cm7_dtcm_clear_end);
    LONG(__sram4_clear_start);
    LONG(__sram4_clear_end);
    LONG(__bkup_ram_clear_start);
    LONG(__bkup_ram_clear_end);
    . = ALIGN(__SYS_ALIGN);
    __clear_table_end = .;
  } > FLASH_BK2

  /* User flash bank 1. */
  .flash_bk1_end :
  {
    . = ALIGN(__SYS_ALIGN);
    __user_flash_bk1_start = .;
    . = ORIGIN(FLASH_BK1) + LENGTH(FLASH_BK1);
    . = ALIGN(__SYS_ALIGN);
    __user_flash_bk1_end = .;
  } > FLASH_BK1

  /* User flash bank 2. */
  .flash_bk2_end :
  {
    . = ALIGN(__SYS_ALIGN);
    __user_flash_bk2_start = .;
    . = ORIGIN(FLASH_BK2) + LENGTH(FLASH_BK2);
    . = ALIGN(__SYS_ALIGN);
    __user_flash_bk2_end = .;
  } > FLASH_BK2

  /* Internal heap. */
  .heap :
  {
    . = ALIGN(__SYS_ALIGN);
    __heap_start = .;
    . = ORIGIN(SRAM123) + LENGTH(SRAM123);
    . = ALIGN(__SYS_ALIGN);
    __heap_end = .;
  } > SRAM123

}