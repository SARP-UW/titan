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
  FLASH1 (rx)  : ORIGIN = 0x08000000, LENGTH = 1024k
  FLASH2 (rx)  : ORIGIN = 0x08100000, LENGTH = 512k
  RAM (rwx) : ORIGIN = 0x24000000, LENGTH = 512k
}

SECTIONS {

  /* CM7 Vector table */
  .cm7_vtable: {
    cm7_vtable_start__ = .;
    . = ALIGN(4);
    KEEP(*(.cm7_vtable))
    . = ALIGN(4);
    cm7_vtable_end__ = .;
  } > FLASH1

  /* CM4 Vector table */
  .cm4_vtable: {
    cm4_vtable_start__ = 
    . = ALIGN(4);
    KEEP(*(.cm4_vtable))
    . = ALIGN(4);
    cm4_vtable_end__ = .;
  } > FLASH2

  /* Code section */
  .text: {
    text_start__ = .;
    . = ALIGN(4);
    *(.text)
    *(.text*)
    *(.glue_7)
    *(.glue_7t)
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    . = ALIGN(4);
    text_end__ = .;
  } > FLASH1

  /* Read-only data section */
  .rodata: {
    rodata_start__ = .;
    . = ALIGN(4);
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
    rodata_end__ = .;
  } > FLASH2

  /* Data section */
  .data: {
    data_start__ = .;
    . = ALIGN(4);
    *(.data)
    *(.data*)
    . = ALIGN(4);
    data_end__ = .;
  } > RAM AT > FLASH1

  /* bss section */
  .bss: {
    bss_start__ = .;
    . = ALIGN(4);
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    bss_end__ = .;
  } > RAM

}