/**
 * This file is part of the Titan Flight Computer Project
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
 * @file src/STM32H7x5/link.ld
 * @authors Aaron McBride
 * @brief Linker script.
 */

/* Program entry point */
ENTRY(reset_handler)

MEMORY {
  FLASH1    (rx)  : ORIGIN = 0x08000000, LENGTH = 1024k
  FLASH2    (rx)  : ORIGIN = 0x08100000, LENGTH = 512k
  USR_FLASH (rx)  : ORIGIN = 0x08200000, LENGTH = 512k
  AXI_SRAM  (rwx) : ORIGIN = 0x24000000, LENGTH = 512k
  DTCM_RAM  (rwx) : ORIGIN = 0x20000000, LENGTH = 128k
  ITCM_RAM  (rwx) : ORIGIN = 0x00000000, LENGTH = 64k
  SRAM1     (rwx) : ORIGIN = 0x30000000, LENGTH = 128k
  SRAM2     (rwx) : ORIGIN = 0x30020000, LENGTH = 128k
  SRAM3     (rwx) : ORIGIN = 0x30040000, LENGTH = 32k
  BKUP_RAM  (rwx) : ORIGIN = 0x38800000, LENGTH = 4k
}

/* CM7 stack */
__cm7_stack_start = ORIGIN(DTCM_RAM)
__cm7_stack_end = ORIGIN(DTCM_RAM) + LENGTH(DTCM_RAM)

/* CM4 stack */
__cm4_stack_start = ORIGIN(SRAM1)
__cm4_stack_end = ORIGIN(SRAM1) + LENGTH(SRAM1)

SECTIONS {

  /* CM7 Vector table */
  .cm7_vtable: {
    __cm7_vtable_start = .;
    . = ALIGN(4);
    KEEP(*(.cm7_vtable))
    . = ALIGN(4);
    __cm7_vtable_end = .;
  } > FLASH1

  /* CM4 Vector table */
  .cm4_vtable: {
    __cm4_vtable_start = 
    . = ALIGN(4);
    KEEP(*(.cm4_vtable))
    . = ALIGN(4);
    __cm4_vtable_end = .;
  } > FLASH2

  /* Code section */
  .text: {
    __text_start = .;
    . = ALIGN(4);

    /* General code */
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
    *(.gnu.linkonce.t.*)

    /* Pre-initialization code */
    . = ALIGN(4);
    KEEP(*(.init))
    . = ALIGN(4);
    __preinit_array_start = .;
    KEEP (*(.preinit_array))
    __preinit_array_end = .;

    /* Initialization code */      
    . = ALIGN(4);
    __init_array_start = .;
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    __init_array_end = .;

    /* Finalization code */
    . = ALIGN(4);
    KEEP(*(.fini))
    . = ALIGN(4);
    __fini_array_start = .;
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    __fini_array_end = .;

    . = ALIGN(4);
    __text_end = .;
  } > FLASH1

  /* Read-only data section */
  .rodata: {
    __rodata_start = .;
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(4);
    __rodata_end = .;
  } > FLASH2

  /* Data section */
  .data: {
    __data_start = .;
    . = ALIGN(4);
    *(.data)
    *(.data*)
    . = ALIGN(4);
    __data_end = .;
  } > RAM AT > FLASH1

  /* bss section */
  .bss: {
    __bss_start = .;
    . = ALIGN(4);
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end = .;
  } > RAM

}