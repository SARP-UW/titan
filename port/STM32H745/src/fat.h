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
 * @brief header for FAT16 Filesystem
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

# if defined(__cplusplus)
extern "C" {
# endif
  // File Handle; represents a file in the filessystem.
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
  BPB* init_filesystem();

  // Returns a file handle for the (new) file given a filename.
  // file_pointer will be at the end of the file
  FileHandle *open_file(
      char* filename,   // The filename of the file to open
      BPB* bpb,         // Bios parameter block
      bool create_file  // Whether to create the file or not
    );
  
  // Writes the given data into the file described by given FileHandle,
  // starting at the FileHandle's file_pointer.
  // returns whether write succeeded.
  bool write_file(
      FileHandle *file, // FileHandle of file to write to
      uint8_t* data,    // Data to send
      uint32_t n_bytes, // num bytes to send
      BPB* bpb          // Bios parameter block
    );

# if defined(__cplusplus)
}
# endif
