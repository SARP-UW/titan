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

  typedef struct {
    uint16_t first_cluster;    // Starting cluster of the file
    uint16_t current_cluster;  // Current cluster being read/written
    uint32_t file_size;        // Size of the file in bytes
    uint32_t file_pointer;     // Offset into the file
    uint32_t dir_entry_sector; // Sector of the directory entry
    uint16_t dir_entry_offset; // Offset within that sector
  } FileHandle;

  // Bios Parameter Block (BPB), holds filesystem metadata.
  // Definition on p.9 of FAT specification
  typedef struct {
    uint32_t BS_jmpBoot;
    uint64_t BS_OEMName;
    uint16_t BPB_BytsPerSec;
    uint8_t BPB_SecPerClus;
    uint16_t BPB_RsvdSecCnt;
    uint8_t BPB_NumFATs;
    uint16_t BPB_RootEntCnt;
    uint16_t BPB_TotSec16;
    int8_t BPB_Media;
    uint16_t BPB_FATSz16;
    uint16_t BPB_SecPerTrk;
    uint16_t BPB_NumHeads;
    uint32_t BPB_HiddSec;
    uint32_t BPB_TotSec32;
  } BPB;

  // Returns heap allocated BPB
  BPB* hal_init_SDMMC();

  // Returns a file handle for the (new) file given a filename.
  // file_pointer will be at the end of the file
  FileHandle *hal_open_file_SDMMC(
      char* filename,
      BPB* bpb,
      bool create_file
    );
  
  // Writes the given data into the file described by given FileHandle,
  // starting at the FileHandle's file_pointer.
  // returns whether write succeeded.
  bool hal_write_file_SDMMC(FileHandle *file,
      uint8_t* data,
      uint32_t n_bytes,
      BPB* bpb
    );

  //////////// SDMMC DRIVER HEADER /////////////

  // Initialize SDMMC
  bool driver_init_SDMMC();

  // Reads num_blocks sectors of data at specified LBA into given buff.
  uint8_t *read_sector_SDMMC(
      uint32_t logical_block_address
    );
  
  // Writes the data buffer to the logical block address (sector num),
  // works even if buff spans multiple sectors.
  bool write_sector_SDMMC(
      uint32_t logical_block_address,
      uint8_t *buff
    );

  //////////// HAL IMPLEMENTATION | HELPERS /////////////

  void copy_arr(char *src, char *dest, int32_t bytes) {
    for (int i = 0; i < bytes; i++) {
      dest[i] = src[i];
    }
  }

  // Represents a directory as described by FAT specification p.23
  // for FAT16 DIR_FstClusLO represents entire cluster number of data cluster.
  typedef struct DirEntry {
    char *DIR_Name;
    int8_t DIR_Attr;
    int8_t DIR_CrtTimeTenth;
    int16_t DIR_CrtTime;
    int16_t DIR_CrtDate;
    int16_t DIR_LstAccDate;
    int16_t DIR_WrtTime;
    int16_t DIR_WrtDate;
    int16_t DIR_FstClusLO;
    int32_t DIR_FileSize;
  } DirEntry;

  // create_file helper
  // Returns cluster number of first cluster in the FAT that is free to
  // be allocated. Returns -1 if not found.
  uint16_t find_free_cluster(BPB* bpb) {
    // TODO: Assumes FAT is 1 sector long
    uint8_t *sector = read_sector_SDMMC(bpb->BPB_RsvdSecCnt);
    for (int offset = 4; offset < bpb->BPB_BytsPerSec; offset += 2) {
      if (*((int16_t *) sector + offset) == 0) {
        return (offset / 2);
      }
    }
    return -1;
  }

  // create_file helper
  // Initialies a directory entry, takes a pointer to a sector, an offset to the entry
  // within the sector, and the template DirEntry
  void initialize_direntry(uint8_t *dir, int32_t entry_offset, DirEntry entry) {
      strcpy((char *) dir + entry_offset, entry.DIR_Name);
      *(dir + entry_offset + 11) = entry.DIR_Attr;
      *(dir + entry_offset + 12) = 0;
      *(dir + entry_offset + 13) = entry.DIR_CrtTimeTenth;
      *(dir + entry_offset + 14) = entry.DIR_CrtTime;
      *(dir + entry_offset + 16) = entry.DIR_CrtDate;
      *(dir + entry_offset + 18) = entry.DIR_LstAccDate;
      *(dir + entry_offset + 20) = 0;
      *(dir + entry_offset + 22) = entry.DIR_WrtTime;
      *(dir + entry_offset + 24) = entry.DIR_WrtDate;
      *(dir + entry_offset + 26) = entry.DIR_FstClusLO;
      *(dir + entry_offset + 28) = entry.DIR_FileSize;

  }

  // Describes location of FAT entry
  typedef struct {
    uint16_t fat_sec_num;       // Section number FAT is in
    uint16_t fat_ent_offset;    // Offet from the start of the section
  } FatEntry;

  // utility function
  // Returns a FatEntry corresponding to the FAT of the given cluster.
  FatEntry get_fat_entry(uint16_t cluster, BPB *bpb) {
    uint32_t fat_offset = cluster * 2; // Two bytes per FAT entry.
    uint16_t fat_sec_num = bpb->BPB_RsvdSecCnt + (fat_offset / bpb->BPB_BytsPerSec);
    uint16_t fat_ent_offset = fat_offset % bpb->BPB_BytsPerSec;

    return (FatEntry){.fat_sec_num = fat_sec_num, .fat_ent_offset = fat_ent_offset};
  }

  // create_file helper
  // Sets the FAT entry of the given cluster number to the given value.
  void set_fat_value(uint16_t cluster_num, uint16_t val, BPB *bpb) {
    FatEntry fat_ent = get_fat_entry(cluster_num, bpb);
    uint8_t *fat_sec = read_sector_SDMMC(fat_ent.fat_sec_num);
    *((uint16_t *)fat_sec + fat_ent.fat_ent_offset) = val;
    write_sector_SDMMC(fat_ent.fat_sec_num, fat_sec);
  }

  // hal_open_file_SDMMC helper
  // Creates a file w/ given filename, returns address of first data cluster
  // of the file
  FileHandle *create_file(char *filename, BPB* bpb) {
    // STEP 1: Find first free slot in the root directory
    // Formula taken from p28 of FAT specification:
    uint32_t root_dir_secnum = (bpb->BPB_RsvdSecCnt + (bpb->BPB_NumFATs * bpb->BPB_FATSz16));
    uint8_t *root_dir_sector = read_sector_SDMMC(root_dir_secnum);
    // Root directory is comprised of BPB_RootEntCnt 32-bit directory entries,
    // if DIR_NAME[0] = 0xE5 or 0x00, dir entry is free, if 0x00 all
    // subsequent entries are free.
    int offset = 0;
    while (root_dir_sector[offset] != 0x00 && root_dir_sector[offset] != 0xE5) {
      offset += 32;
    }
    // STEP 2: Create the file in the slot that's been found.
    RTC_DateTime cur_time = tal_read_RTC();
    // See sec 6.3 of FAT specs for date/time format.
    uint16_t cur_time_fmt = cur_time.secs / 2 |
      (cur_time.mins << 5) |
      (cur_time.hours << 11);
    uint16_t cur_date_fmt = cur_time.date |
        (cur_time.month << 5) |
        ((cur_time.years - 1980) << 9);
    int32_t first_free_cluster = find_free_cluster(bpb);
    if (first_free_cluster == -1) return NULL;
    struct DirEntry new_entry = {
      .DIR_Name = filename,                      // TODO: Check strcpy
      .DIR_Attr = 0x20,                          // ATTR_ARCHIVE 
      .DIR_CrtTimeTenth = (10 * cur_time.subsec),// Subsec Tenths are 10 * subsec.
      .DIR_CrtTime = cur_time_fmt,
      .DIR_CrtDate = cur_date_fmt,
      .DIR_LstAccDate = cur_date_fmt,
      .DIR_WrtTime = cur_time_fmt,
      .DIR_WrtDate = cur_date_fmt,
      .DIR_FstClusLO = first_free_cluster,
      .DIR_FileSize = 0,
    };
    initialize_direntry(root_dir_sector, offset, new_entry);
    set_fat_value(first_free_cluster, 0xffff, bpb);
    write_sector_SDMMC(root_dir_secnum, root_dir_sector);

    FileHandle *file_info = malloc(sizeof(FileHandle));
    file_info->first_cluster = first_free_cluster;
    file_info->current_cluster = first_free_cluster;
    file_info->file_size = 0;
    file_info->file_pointer = 0;
    file_info->dir_entry_sector = root_dir_secnum;
    file_info->dir_entry_offset = offset;
    return file_info;
  }
  
  // hal_open_file_SDMMC helper
  // Returns FileHandle of file specified by filename.
  // otherwise returns null.
  FileHandle *find_file(char *filename, BPB* bpb) {
    uint16_t root_directory = bpb->BPB_RsvdSecCnt + (bpb->BPB_NumFATs * bpb->BPB_FATSz16);
    // TODO: ASSUMES ROOT DIRECTORY IS 1 SECTOR LONG
    uint8_t *sector = read_sector_SDMMC(root_directory);
    for (int offset = 0; sector[offset] != 0x00 && offset < bpb->BPB_BytsPerSec; offset += 32) {
      uint8_t *name = sector + offset;
      if (!strcmp(filename, (char *) name)) {
        FileHandle *file_info = malloc(sizeof(FileHandle));
        file_info->first_cluster = *((uint16_t *)sector + offset + 26);
        file_info->current_cluster = file_info->first_cluster;
        file_info->file_size = *((uint32_t *)sector + offset + 28);
        file_info->file_pointer = 0;
        file_info->dir_entry_sector = root_directory;
        file_info->dir_entry_offset = offset;
        return file_info;
      }
    }
    return NULL;
  }
  
  // hal_init_SDMMC helper
  // takes offset and a num bytes and returns the little-endian interpretation
  // of the bytes at that offset
  // num bytes should never be greater than 8.
  uint64_t get_bpb_field(uint8_t *bpb_sector, uint8_t offset, uint8_t num_bytes) {
    uint64_t result = 0;
    for (size_t i = 0; i < num_bytes; i++) {
      result |= (uint64_t)(unsigned char) bpb_sector[offset + i] << (8 * i);
    }
    return result;
  }

  // hal_write_file_SDMMC helper
  // takes the dir entry sector and offset, and adds the given value to the filesize.
  void update_filesize(uint32_t dir_entry_sec_num, uint16_t dir_entry_offset, size_t size) {
    uint8_t *dir_entry_sec = read_sector_SDMMC(dir_entry_sec_num);
    *((uint32_t *) dir_entry_sec + dir_entry_offset + 28) += size;
    write_sector_SDMMC(dir_entry_sec_num, dir_entry_sec);
  }


  // hal_write_file_SDMMC helper
  // Takes cluster number of last allocated cluster in file chain, allocates
  // a new cluster at the end of the chain, returning cluster number of new cluster.
  uint16_t allocate_new_cluster(uint16_t current_cluster, BPB *bpb) {
    // Make current_cluster point to the next free cluster.
    FatEntry fat_ent = get_fat_entry(current_cluster, bpb);
    uint8_t *fat_sec = read_sector_SDMMC(fat_ent.fat_sec_num);
    uint16_t next_free_cluster = find_free_cluster(bpb);
    *((uint16_t *)fat_sec + fat_ent.fat_ent_offset) = next_free_cluster;

    // Make the next free cluster 0xffff instead of 0x0.
    FatEntry free_fat_ent = get_fat_entry(next_free_cluster, bpb);
    uint8_t *free_fat_sec = read_sector_SDMMC(free_fat_ent.fat_sec_num);
    *((int16_t *)free_fat_sec + free_fat_ent.fat_ent_offset) = 0xffff;

    return next_free_cluster;
  }

  // hal_write_file_SDMMC helper
  // Gets the FAT entry for a given cluster number.
  // Assumes FAT16.
  uint16_t check_fat_entry(uint16_t current_cluster, BPB *bpb) {
    FatEntry fat_ent = get_fat_entry(current_cluster, bpb);

    uint8_t *fat_sec = read_sector_SDMMC(fat_ent.fat_sec_num);
    return *((uint16_t *) fat_sec + fat_ent.fat_ent_offset);
  }

  // hal_write_file_SDMMC helper
  // Returns correct sector numbe for given cluster number and file pointer.
  int32_t get_sec_num(int16_t current_cluster, int32_t file_pointer, BPB *bpb) {
    uint32_t bytes_per_clus = bpb->BPB_BytsPerSec * bpb->BPB_SecPerClus;

    uint32_t bpb_and_fat = bpb->BPB_RsvdSecCnt + (bpb->BPB_NumFATs * bpb->BPB_FATSz16);
    uint32_t root_dir = ((bpb->BPB_RootEntCnt * 32) + (bpb->BPB_BytsPerSec - 1)) \
                        / bpb->BPB_BytsPerSec;
    uint32_t cur_clus = (current_cluster - 2) * bpb->BPB_SecPerClus;
    uint32_t within_clus = (file_pointer % bytes_per_clus)/bpb->BPB_BytsPerSec;

    return bpb_and_fat + root_dir + cur_clus + within_clus;
  }

  //////////// HAL IMPLEMENTATION | API FUNCTIONS /////////////
  FileHandle *hal_open_file_SDMMC(char* filename, BPB *bpb, bool cf) {
    FileHandle *file = find_file(filename, bpb);
    if (file == NULL && cf) {
      file = create_file(filename, bpb);
    }
    return file;
  }

  BPB* hal_init_SDMMC() {
    BPB* retval = malloc(sizeof(BPB));
    uint8_t *bpb_sector = read_sector_SDMMC(0);
    retval->BS_jmpBoot = get_bpb_field(bpb_sector, 0, 3);
    retval->BS_OEMName = get_bpb_field(bpb_sector, 3, 8);
    retval->BPB_BytsPerSec = get_bpb_field(bpb_sector, 11, 2);
    retval->BPB_SecPerClus = get_bpb_field(bpb_sector, 13, 1);
    retval->BPB_RsvdSecCnt = get_bpb_field(bpb_sector, 14, 2);
    retval->BPB_NumFATs = get_bpb_field(bpb_sector, 16, 1);
    retval->BPB_RootEntCnt = get_bpb_field(bpb_sector, 17, 2);
    retval->BPB_TotSec16 = get_bpb_field(bpb_sector, 19, 2);
    retval->BPB_Media = get_bpb_field(bpb_sector, 21, 1);
    retval->BPB_FATSz16 = get_bpb_field(bpb_sector, 22, 2);
    retval->BPB_SecPerTrk = get_bpb_field(bpb_sector, 24, 2);
    retval->BPB_NumHeads = get_bpb_field(bpb_sector, 26, 2);
    retval->BPB_HiddSec = get_bpb_field(bpb_sector, 28, 4);
    retval->BPB_TotSec32 = get_bpb_field(bpb_sector, 32, 4);
    return retval;
  }

  bool hal_write_file_SDMMC(FileHandle *file, uint8_t* data, uint32_t n_bytes, BPB* bpb) {
    uint32_t written_so_far = 0;
    while (n_bytes > 0) {
      // Read the sector that we're going to write to
      uint32_t cur_sec_num = get_sec_num(file->current_cluster, file->file_pointer, bpb);
      uint8_t *cur_sector = read_sector_SDMMC(cur_sec_num);
      // Write to the sector at the correct offset
      uint32_t offset = file->file_pointer % bpb->BPB_BytsPerSec;
      uint32_t i = 0;
      while (n_bytes > 0 && i + offset < bpb->BPB_BytsPerSec) {
        cur_sector[offset + i] = data[written_so_far + i];
        i++;
        n_bytes--;
      }
      written_so_far += i;
      file->file_pointer += i;
      write_sector_SDMMC(cur_sec_num, cur_sector);
      // If we ran off the cluster, go to the next or allocate a new one.
      if (n_bytes > 0 && file->file_pointer % (bpb->BPB_BytsPerSec * bpb->BPB_SecPerClus) == 0) {
        uint16_t fat_ent = check_fat_entry(file->current_cluster, bpb);
        uint16_t next_cluster = fat_ent;
        if (fat_ent == 0xffff) {
          next_cluster = allocate_new_cluster(file->current_cluster, bpb);
        } 
        file->current_cluster = next_cluster;
      }
    }
    // update the file size in the dir_entry and the FileHandle
    file->file_size += written_so_far;
    update_filesize(file->dir_entry_sector, file->dir_entry_offset, written_so_far);
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
