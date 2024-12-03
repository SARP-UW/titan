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
 * @file common/platform/nvm.h
 * @authors Ashton Doane 
 * @brief 
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "src/platform/gpio.h"

#if defined(__cplusplus)
  extern "C" {
#endif

    /**************************************************************************************************
    * @section NVM CONSTANTS
    * 
    * FROM DOCUMENTATION
        * At startup, the boot memory space is selected by the BOOT pin and BOOT_ADDx option
            bytes, allowing to program any boot memory address from 0x0000 0000 to 0x3FFF FFFF
            which includes:
            • All flash address space
            • flash memory and SRAMs (except for ITCM /DTCM RAMs which cannot be accessed
            by the Cortex®-M4 core)

        The flash memory is divided into two independent banks. Each bank is organized as follows:
            • A user flash memory block of 512 Kbytes (STM32H7xxxG) or 1-Mbyte (STM32H7xxxI)
            containing eight user sectors of 128 Kbytes (4 K flash memory words)
            • 128 Kbytes of System flash memory from which the device can boot
            • 2 Kbytes (64 flash words) of user option bytes for user configuration
    **************************************************************************************************/
    #define FLASH_BASE 0x08000000 //example location, unsure of real.

   /**************************************************************************************************
    * @section NVM INTERFACE
    **************************************************************************************************/
    void nvm_write_data(void* data_ptr, int32_t data_len, const bool* err);

    void nvm_read_data(void* read_addr, int32_t data_len, const bool* err);
    
    /**************************************************************************************************
    * @section NVM IMPLEMENTATION
    **************************************************************************************************/
   
#if defined(__cplusplus)
  }
#endif