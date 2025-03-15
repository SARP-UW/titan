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
 * @file dev/src/sdmmc.h
 * @authors Charles Faisandier
 * @brief Driver for the SDMMC
 */

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "internal/mmio.h"
#include <string.h>
#include "gpio.h"
#include "rtc.h"

int SECTOR_SIZE = 512;

# if defined(__cplusplus)
extern "C" {
# endif
  //////////// HAL HEADER /////////////

  typedef char* FILE;

  FILE hal_open_file_SDMMC(char* filename);
  
  bool hal_write_file_SDMMC(FILE file, uint32_t* data);

  //////////// SDMMC DRIVER HEADER /////////////

  bool driver_init_SDMMC();


  // Returns heap allocated sector of data.
  FILE read_sector_SDMMC(void *address);

  //////////// HAL IMPLEMENTATION /////////////

  // Returns the adddress to the directory entry of the file if found
  // in the root directory, otherwise returns null.
  FILE find_file(char *filename) {
    // Go to root directory
    void *root_directory = (BPB_ResvdSecCnt + (BPB_NumFATs * PBPFATSz16)) * SECTOR_SIZE;
    // Iterate through the files
    FILE sector = read_sector_SDMMC(root_directory);
    for (int offset = 0; sector[offset] != 0x00 && offset < SECTOR_SIZE; offset += 32) {
      // Check name of file at entry.
      char *name = sector + offset;
      if (!strcmp(filename, name)) {
        // If same as desired filename return its address.
        int cluster_num = *((uint8_t *) sector + offset + 26); // Cluster num is 26 offset 2 byte number.
        FILE file_address = cluster_num * BPB_SecPerClus * BPB_BytsPerSec ;
        return file_address;
      }
    }
    // If found return address
    return NULL;
  }

  void copy_arr(char *src, char *dest, int32_t bytes) {
    for (int i = 0; i < bytes; i++) {
      dest[i] = src[i];
    }
  }

  struct DirEntry {
    char *DIR_Name;

  }

  FILE create_file(char *filename) {
    // Find first free slot in the root directory
    void *root_directory = (BPB_ResvdSecCnt + (BPB_NumFATs * PBPFATSz16)) * SECTOR_SIZE;
    FILE sector = read_sector_SDMMC(root_directory);
    int offset = 0;
    while (sector[offset] != 0x00) {
      offset += 32;
    }
    // Copy the whole root directory sector
    FILE new_sector = malloc(BPB_BytesPerSec);
    copy_arr(sector, new_sector, BPB_BytesPerSec);
    // Add the entry
    RTC_DateTime tal_read_RTC();
    struct DirEntry new_entry = {
      .DIR_Name = filename,
      .DIR_Attr = 0x20, // ATTR_ARCHIVE -- has been modified since last backup
      .DIR_CrtTimeTenth = 
    }
    initialize_direntry(new_sector, offset, new_entry);
    // Re-write whole directory sector


  }

  FILE hal_open_file_SDMMC(char* filename) {
    FILE file = find_file(filename);
    if (file == NULL) {
      file = create_file(filename);
    }
    return file;
  }
  
  bool hal_write_file_SDMMC(FILE file, uint32_t* data) {
    return true;
  }

  //////////// SDMMC DRIVER IMPLEMENTATION /////////////

  bool driver_init_SDMMC() {
    // SDMMC1 and SDMMC1 Delay Block enable
    WRITE_FIELD(RCC_AHBxENR[3], RCC_AHBxENR_SDMMC1EN, 1);
   
    // Configuring "PD2"
    int sdmmc_cmd_pin = 114;
    tal_set_mode(sdmmc_cmd_pin, 2);
    tal_set_drain(sdmmc_cmd_pin, 1);
    tal_set_speed(sdmmc_cmd_pin, 3);
    tal_alternate_mode(sdmmc_cmd_pin, 0xC);
    tal_pull_pin(sdmmc_cmd_pin, 1);

    WRITE_FIELD(SDMMCx_POWER[1], SDMMCx_POWER_PWRCTRL, 0x03);
    WRITE_FIELD(SDMMCx_POWER[1], SDMMCx_POWER_DIRPOL, 1);  
    WRITE_FIELD(SDMMCx_CLKCR[1], SDMMCx_CLKCR_WIDBUS, 1);
    WRITE_FIELD(SDMMCx_CLKCR[1], SDMMCx_CLKCR_PWRSAV, 0);
  }


  void send_SDMMC_command(uint8_t cmd_index, uint32_t arguement, uint8_t response_type) {
    while (READ_FIELD(SDMMCx_STAR[1], SDMMCx_STAR_CPSMACT));

    WRITE_FIELD(SDMMCx_ARGR[1], SDMMCx_ARGR[1], arguement);
    WRITE_FIELD(SDMMCx_CMDR[1], SDMMCx_CMDR_CMDINDEX, cmd_index);
    WRITE_FIELD(SDMMCx_CMDR[1], SDMMCx_CMDR_WAITRESP, response_type);

    while (READ_FIELD(SDMMCx_STAR[1], SDMMCx_STAR_CPSMACT));
  }


  void set_block_length(uint32_t block_size) {
    send_SDMMC_command(16, block_size, 1);
  }


  void write_multiple_blocks(uint32_t start_block, uint32_t num_blocks, uint32_t *data) {
    send_SDMMC_command(25, start_block, 1);

    for (uint32_t block = 0; block < num_blocks; block++) {
      while (READ_FIELD(SDMMCx_STAR[1], SDMMCx_STAR_TXFIFOE)); // Wait for FIFO queue to be empty.

      for (int i = 0; i < 128; i++) {
        WRITE_FIELD(SDMMCxFIFOR[1], SDMMCxFIFOR[1], data[block * 128 + i]);
      }

      while (READ_FIELD(SDMMCx_STAR[1], SDMMCx_STAR_DBCKEND)); // Wait for data to be transmitted
    }

    send_SDMMC_command(25, 0, 1); // Stop transmission.
  }

# if defined(__cplusplus)
}
# endif
