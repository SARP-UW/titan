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
 * @todo Needs more work generally...
 */

/* Reference constants */
__VTABLE_ALIGNMENT__ = 1024;
__STACK_ALIGNMENT__ = 8;
__HEAP_ALIGNMENT__ = 8;
__KSTACK_SIZE__ = 1024;

/* Set program entry point */
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

  /* Vector table for CM7 core */
  .cm7_vtable : 
  {
    . = ALIGN(__VTABLE_ALIGNMENT__);
    __cm7_vtable_start__ = .;
    LONG(__cm7_kstack_end__);
    KEEP(*(.cm7_vtable .cm7_vtable.*))
    . = ALIGN(__VTABLE_ALIGNMENT__);
    __cm7_vtable_end__ = .;
  } > FLASH_BK1

  /* Vector table for CM4 core */
  .cm4_vtable : 
  {
    . = ALIGN(__VTABLE_ALIGNMENT__);
    __cm4_vtable_start__ = .;
    LONG(__cm4_kstack_end__);
    KEEP(*(.cm4_vtable .cm4_vtable.*))
    . = ALIGN(__VTABLE_ALIGNMENT__);
    __cm4_vtable_end__ = .;
  } > FLASH_BK2

  /* ARM exception table */
  .arm_extab :
  {
    __extab_start = .;
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    __extab_end = .;
  } > FLASH_BK1

  /* ARM exception index table */
  .arm_exidx :
  {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } > FLASH_BK1

  /* ARM attributes section */
  .ARM.attributes : 
  { 
    __arm_attributes_start__ = .;
    *(.ARM.attributes) 
    __arm_attributes_end__ = .;
  } > FLASH_BK1

  /* Pre-initialization function array */
  .preinit_array :
  {
    . = ALIGN(4);
    __preinit_array_start__ = .;
    KEEP (*(.preinit_array))
    . = ALIGN(4);
    __preinit_array_end__ = .;
  } > FLASH_BK1

  /* Initialization function array */
  .init_array :
  {
    . = ALIGN(4);
    __init_array_start__ = .;
    KEEP (*(SORT(.init_array*)))
    KEEP (*(.init_array))
    . = ALIGN(4);
    __init_array_end__ = .;
  } > FLASH_BK1

  /* Finalization function array */
  .fini_array :
  {
    . = ALIGN(4);
    __fini_array_start__ = .;
    KEEP (*(SORT(.fini_array*)))
    KEEP (*(.fini_array))
    . = ALIGN(4);
    __fini_array_end__ = .;
  } > FLASH_BK1

  /* CM7 ITCM Section */
  .cm7_itcm  :
  {
    . = ALIGN(4);
    __cm7_itcm_start__ = .;
    *(.cm7_itcm)
    *(.cm7_itcm.*)
    . = ALIGN(4);
    __cm7_itcm_end__ = .;
  } > CM7_ITCM AT > FLASH_BK1
  __cm7_itcm_dst__ = LOADADDR(.cm7_itcm);

  /* Kernel stack for CM7 core */
  .cm7_kstack : 
  {
    . = ALIGN(__STACK_ALIGNMENT__);
    __cm7_kstack_start__ = .;
    . += __KSTACK_SIZE__;
    . = ALIGN(__STACK_ALIGNMENT__);
    __cm7_kstack_end__ = .;
  } > CM7_DTCM

  /* CM7 DTCM Section */
  .cm7_dtcm :
  {
    . = ALIGN(4);
    __cm7_dtcm_start__ = .;
    *(.cm7_dtcm)
    *(.cm7_dtcm.*)
    . = ALIGN(4);
    __cm7_dtcm_end__ = .;
  } > CM7_DTCM AT > FLASH_BK1
  __cm7_dtcm_dst__ = LOADADDR(.cm7_dtcm);

  /* Kernel memory */
  .kmem :
  {
    . = ALIGN(4);
    __kmem_start__ = .;
    *(.kmem)
    *(.kmem.*)
    . = ALIGN(4);
    __kmem_end__ = .;
  } > SRAM4 AT > FLASH_BK1
  __kmem_dst__ = LOADADDR(.kmem);

  /* Program constant data section */
  .rodata :
  {
    . = ALIGN(4);
    __rodata_start__ = .;
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
    __rodata_end__ = .;
  } > FLASH_BK1

  /* Initialized data section */
  .data :
  {
    . = ALIGN(4);
    __data_start__ = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    __data_end__ = .;
  } > AXI_SRAM AT > FLASH_BK1
  __data_dst__ = LOADADDR(.data);

  /* User flash section (bank 1) */
  __user_flash_bk1_start__ = __data_end__;
  __user_flash_bk1_end__ = ORIGIN(FLASH_BK1) + LENGTH(FLASH_BK1);

  /* Uninitialized data section */
  .bss :
  {
    . = ALIGN(4);
    __bss_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
  } > AXI_SRAM

  /* Program text (code) section */
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
  } > FLASH_BK2

  /* User flash section (bank 2) */
  __user_flash_bk2_start__ = __text_end__;
  __user_flash_bk2_end__ = ORIGIN(FLASH_BK2) + LENGTH(FLASH_BK2);

  /* Kernel stack for CM4 core */
  .cm4_kstack : 
  {
    . = ALIGN(__STACK_ALIGNMENT__);
    __cm4_kstack_start__ = .;
    . += __KSTACK_SIZE__;
    . = ALIGN(__STACK_ALIGNMENT__);
    __cm4_kstack_end__ = .;
  } > SRAM123

  /* Heap section (TODO) */
  .heap :
  {
    . = ALIGN(__HEAP_ALIGNMENT__);
    __heap_start__ = .;
    end = __heap_start__;
    _end = __heap_start__;
    __end = __heap_start__;
    KEEP(*(.heap))
    . = ALIGN(__HEAP_ALIGNMENT__);
    __heap_end__ = .;
    __HeapLimit__ = __heap_end__;
  } > SRAM123

}