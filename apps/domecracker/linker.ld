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
 * @file apps/domecracker/linker.ld
 * @authors Aaron McBride
 * @brief Linker script for the Domecracker application target.
 */

/* Reference constants */
__SYS_ALIGN   = 4;    /* Memory address alignment */
__STACK_ALIGN = 8;    /* Stack alignment */
__KSTACK_SIZE = 1024; /* Size of kernel stack regions for both cores */

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

  /************************************************************************************************
   * Special Sections
   ************************************************************************************************/

  /* Kernel stack for CM7 core */
  .cm7_kstack :
  {
    . = ALIGN(__STACK_ALIGN);
    __cm7_kstack_start = .;
    . += __KSTACK_SIZE;
    . = ALIGN(__STACK_ALIGN);
    __cm7_kstack_end = .;
  } > CM7_DTCM

  /* Kernel stack for CM4 core */
  .cm4_kstack :
  {
    . = ALIGN(__STACK_ALIGN);
    __cm4_kstack_start = .;
    . += __KSTACK_SIZE;
    . = ALIGN(__STACK_ALIGN);
    __cm4_kstack_end = .;
  } > SRAM4

  /* Vector table for CM7 core */
  .cm7_vtable :
  {
    . = ALIGN(__SYS_ALIGN);
    __cm7_vtable_start = .;
    LONG(__cm7_kstack_end);
    KEEP(*(.cm7_vtable .cm7_vtable.*))
    . = ALIGN(__SYS_ALIGN);
    __cm7_vtable_end = .;
  } > FLASH_BK1

  /* Vector table for CM4 core */
  .cm4_vtable :
  {
    . = ALIGN(__SYS_ALIGN);
    __cm4_vtable_start = .;
    LONG(__cm4_kstack_end);
    KEEP(*(.cm4_vtable .cm4_vtable.*))
    . = ALIGN(__SYS_ALIGN);
    __cm4_vtable_end = .;
  } > FLASH_BK2

  /************************************************************************************************
   * Constant Program Data Sections
   ************************************************************************************************/

  /* Read-only (const) program data in flash bank 1 */
  .rodata_bk1 :
  {
    . = ALIGN(__SYS_ALIGN);
    __rodata_bk1_start = .;
    *(.rodata .rodata*)
    . = ALIGN(__SYS_ALIGN);
    __rodata_bk1_end = .;
  } > FLASH_BK1

  /* Read-only (const) program data in flash bank 2 */
  .rodata_bk2 :
  {
    . = ALIGN(__SYS_ALIGN);
    __rodata_bk2_start = .;
    *(.rodata .rodata*)
    . = ALIGN(__SYS_ALIGN);
    __rodata_bk2_end = .;
  } > FLASH_BK2

  /* Program text (code) in flash bank 1 */
  .text_bk1 :
  {
    . = ALIGN(__SYS_ALIGN);
    __text_bk1_start = .;
    *(.text .text.*)
    . = ALIGN(__SYS_ALIGN);
    __text_bk1_end = .;
  } > FLASH_BK1

  /* Program text (code) in flash bank 2 */
  .text_bk2 :
  {
    . = ALIGN(__SYS_ALIGN);
    __text_bk2_start = .;
    *(.text .text.*)
    . = ALIGN(__SYS_ALIGN);
    __text_bk2_end = .;
  } > FLASH_BK2

  /************************************************************************************************
   * Program Data Sections
   ************************************************************************************************/

  /* Program data section in AXI-SRAM at flash bank 1 */
  .data_bk1_axi_sram :
  {
    . = ALIGN(__SYS_ALIGN);
    __data_bk1_axi_sram_dst = .;
    *(.data .data.*)
    . = ALIGN(__SYS_ALIGN);
  } > AXI_SRAM AT > FLASH_BK1
  __data_bk1_axi_sram_start = LOADADDR(.data_bk1_axi_sram);
  __data_bk1_axi_sram_end = __data_bk1_axi_sram_start + SIZEOF(.data_bk1_axi_sram);

  /* Program data section in AXI-SRAM at flash bank 2 */
  .data_bk2_axi_sram :
  {
    . = ALIGN(__SYS_ALIGN);
    __data_bk2_axi_sram_dst = .;
    *(.data .data.*)
    . = ALIGN(__SYS_ALIGN);
  } > AXI_SRAM AT > FLASH_BK2
  __data_bk2_axi_sram_start = LOADADDR(.data_bk2_axi_sram);
  __data_bk2_axi_sram_end = __data_bk2_axi_sram_start + SIZEOF(.data_bk2_axi_sram);

  /* Program data section in SRAM123 at flash bank 1 */
  .data_bk1_sram123 :
  {
    . = ALIGN(__SYS_ALIGN);
    __data_bk1_sram123_dst = .;
    *(.data .data.*)
    . = ALIGN(__SYS_ALIGN);
  } > SRAM123 AT > FLASH_BK1
  __data_bk1_sram123_start = LOADADDR(.data_bk1_sram123);
  __data_bk1_sram123_end = __data_bk1_sram123_start + SIZEOF(.data_bk1_sram123);

  /* Program data section in SRAM123 at flash bank 2 */
  .data_bk2_sram123 :
  {
    . = ALIGN(__SYS_ALIGN);
    __data_bk2_sram123_dst = .;
    *(.data .data.*)
    . = ALIGN(__SYS_ALIGN);
  } > SRAM123 AT > FLASH_BK2
  __data_bk2_sram123_start = LOADADDR(.data_bk2_sram123);
  __data_bk2_sram123_end = __data_bk2_sram123_start + SIZEOF(.data_bk2_sram123);

  /* Program data section in SRAM4 at flash bank 1 */
  .data_bk1_sram4 :
  {
    . = ALIGN(__SYS_ALIGN);
    __data_bk1_sram4_dst = .;
    *(.data .data.*)
    . = ALIGN(__SYS_ALIGN);
  } > SRAM4 AT > FLASH_BK1
  __data_bk1_sram4_start = LOADADDR(.data_bk1_sram4);
  __data_bk1_sram4_end = __data_bk1_sram4_start + SIZEOF(.data_bk1_sram4);

  /* Program data section in SRAM4 at flash bank 2 */
  .data_bk2_sram4 :
  {
    . = ALIGN(__SYS_ALIGN);
    __data_bk2_sram4_dst = .;
    *(.data .data.*)
    . = ALIGN(__SYS_ALIGN);
  } > SRAM4 AT > FLASH_BK2
  __data_bk2_sram4_start = LOADADDR(.data_bk2_sram4);
  __data_bk2_sram4_end = __data_bk2_sram4_start + SIZEOF(.data_bk2_sram4);

  /* Program bss (uninitialized data) in AXI SRAM */
  .bss_axi_sram :
  {
    . = ALIGN(__SYS_ALIGN);
    __bss_axi_sram_start = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(__SYS_ALIGN);
    __bss_axi_sram_end = .;
  } > AXI_SRAM

  /* Program bss (uninitialized data) in SRAM123 */
  .bss_sram123 :
  {
    . = ALIGN(__SYS_ALIGN);
    __bss_sram123_start = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(__SYS_ALIGN);
    __bss_sram123_end = .;
  } > SRAM123

  /* Program bss (uninitialized data) in SRAM4 */
  .bss_sram4 :
  {
    . = ALIGN(__SYS_ALIGN);
    __bss_sram4_start = .;
    *(.bss .bss.*)
    *(COMMON)
    . = ALIGN(__SYS_ALIGN);
    __bss_sram4_end = .;
  } > SRAM4

  /************************************************************************************************
   * Program Initialization Tables
   ************************************************************************************************/

  /* Table of regions to load into memory */
  .load_table :
  {
    . = ALIGN(__SYS_ALIGN);
    __load_table_start = .;
    LONG(__data_bk1_axi_sram_start);
    LONG(__data_bk1_axi_sram_end);
    LONG(__data_bk1_axi_sram_dst);
    LONG(__data_bk2_axi_sram_start);
    LONG(__data_bk2_axi_sram_end);
    LONG(__data_bk2_axi_sram_dst);
    LONG(__data_bk1_sram123_start);
    LONG(__data_bk1_sram123_end);
    LONG(__data_bk1_sram123_dst);
    LONG(__data_bk2_sram123_start);
    LONG(__data_bk2_sram123_end);
    LONG(__data_bk2_sram123_dst);
    LONG(__data_bk1_sram4_start);
    LONG(__data_bk1_sram4_end);
    LONG(__data_bk1_sram4_dst);
    LONG(__data_bk2_sram4_start);
    LONG(__data_bk2_sram4_end);
    LONG(__data_bk2_sram4_dst);
    . = ALIGN(__SYS_ALIGN);
    __load_table_end = .;
  } > FLASH_BK2

  /* Table of regions to be cleared */
  .clear_table :
  {
    . = ALIGN(__SYS_ALIGN);
    __clear_table_start = .;
    LONG(__bss_axi_sram_start);
    LONG(__bss_axi_sram_end);
    LONG(__bss_sram123_start);
    LONG(__bss_sram123_end);
    LONG(__bss_sram4_start);
    LONG(__bss_sram4_end);
    . = ALIGN(__SYS_ALIGN);
    __clear_table_end = .;
  } > FLASH_BK2

  /************************************************************************************************
   * Free Flash Memory Regions
   ************************************************************************************************/

  /* Section for free flash memory in bank 1 */
  .free_flash_bk1 :
  {
    . = ALIGN(__SYS_ALIGN);
    __free_flash_bk1_start = .;
  } > FLASH_BK1
  __free_flash_bk1_end = ORIGIN(FLASH_BK1) + LENGTH(FLASH_BK1);

  /* Section for free flash memory in bank 2 */
  .free_flash_bk2 :
  {
    . = ALIGN(__SYS_ALIGN);
    __free_flash_bk2_start = .;
  } > FLASH_BK2
  __free_flash_bk2_end = ORIGIN(FLASH_BK2) + LENGTH(FLASH_BK2);

}