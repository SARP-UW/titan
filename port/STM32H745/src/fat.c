#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "clock.h"
#include "block_device.h"
#include "fat.h"

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
  uint8_t *sector = read_sector(bpb->BPB_RsvdSecCnt);
  for (int offset = 4; offset < bpb->BPB_BytsPerSec; offset += 2) {
    if (*(int16_t *)(sector + offset) == 0) {
      free(sector);
      return (offset / 2);
    }
  }
  free(sector);
  return -1;
}

// create_file helper
// Initialies a directory entry, takes a pointer to a sector, an offset to the entry
// within the sector, and the template DirEntry
void initialize_direntry(uint8_t *dir, int32_t entry_offset, DirEntry entry) {
  char name[8], ext[3];
  const char *dot = strchr(entry.DIR_Name, '.');

  size_t i;
  for (i = 0; i < 8 && i < strlen(entry.DIR_Name) && entry.DIR_Name[i] != '.'; i++) {
    name[i] = entry.DIR_Name[i];
  }
  for (; i < 8; i++) {
    name[i] = ' ';
  }

  if (dot) {
    for (size_t i = 0; i < 3 && i < strlen(dot + 1); i++){
      ext[i] = (dot + 1)[i];
    }
  } else {
    for (int i = 0; i < 3; i++)
      ext[i] = ' ';
  }

  // Copy name and extension into the first 11 bytes
  memcpy(dir + entry_offset, name, 8);
  memcpy(dir + entry_offset + 8, ext, 3);
  *(uint8_t *)(dir + entry_offset + 11) = entry.DIR_Attr;
  *(uint8_t *)(dir + entry_offset + 12) = 0;
  *(uint8_t *)(dir + entry_offset + 13) = entry.DIR_CrtTimeTenth;
  *(uint16_t *)(dir + entry_offset + 14) = entry.DIR_CrtTime;
  *(uint16_t *)(dir + entry_offset + 16) = entry.DIR_CrtDate;
  *(uint16_t *)(dir + entry_offset + 18) = entry.DIR_LstAccDate;
  *(uint16_t *)(dir + entry_offset + 20) = 0; // Only valid for FAT32
  *(uint16_t *)(dir + entry_offset + 22) = entry.DIR_WrtTime;
  *(uint16_t *)(dir + entry_offset + 24) = entry.DIR_WrtDate;
  *(uint16_t *)(dir + entry_offset + 26) = entry.DIR_FstClusLO;
  *(uint32_t *)(dir + entry_offset + 28) = entry.DIR_FileSize;
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
  uint8_t *fat_sec = read_sector(fat_ent.fat_sec_num);
  *((uint16_t *)(fat_sec + fat_ent.fat_ent_offset)) = val;
  write_sector(fat_ent.fat_sec_num, fat_sec);
  free(fat_sec);
}

// hal_open_file_SDMMC helper
// Creates a file w/ given filename, returns address of first data cluster
// of the file
FileHandle *create_file(char *filename, BPB* bpb) {
  // STEP 1: Find first free slot in the root directory
  // Formula taken from p28 of FAT specification:
  uint32_t root_dir_secnum = (bpb->BPB_RsvdSecCnt + (bpb->BPB_NumFATs * bpb->BPB_FATSz16));
  uint8_t *root_dir_sector = read_sector(root_dir_secnum);
  // Root directory is comprised of BPB_RootEntCnt 32-bit directory entries,
  // if DIR_NAME[0] = 0xE5 or 0x00, dir entry is free, if 0x00 all
  // subsequent entries are free.
  int offset = 0;
  while (root_dir_sector[offset] != 0x00 && root_dir_sector[offset] != 0xE5) {
    offset += 32;
  }
  // STEP 2: Create the file in the slot that's been found.
  DateTime cur_time = read_clock();
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
  write_sector(root_dir_secnum, root_dir_sector);
  free(root_dir_sector);

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
  uint8_t *sector = read_sector(root_directory);
  for (int offset = 0; sector[offset] != 0x00 && offset < bpb->BPB_BytsPerSec; offset += 32) {
    uint8_t *name = sector + offset;
    if (!strcmp(filename, (char *) name)) {
      FileHandle *file_info = malloc(sizeof(FileHandle));
      file_info->first_cluster = *(uint16_t *)(sector + offset + 26);
      file_info->current_cluster = file_info->first_cluster;
      file_info->file_size = *(uint32_t *)(sector + offset + 28);
      file_info->file_pointer = file_info->file_size;
      file_info->dir_entry_sector = root_directory;
      file_info->dir_entry_offset = offset;
      free(sector);
      return file_info;
    }
  }
  free(sector);
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
  uint8_t *dir_entry_sec = read_sector(dir_entry_sec_num);
  *(uint32_t *)(dir_entry_sec + dir_entry_offset + 28) = size;
  write_sector(dir_entry_sec_num, dir_entry_sec);
  free(dir_entry_sec);
}


// hal_write_file_SDMMC helper
// Takes cluster number of last allocated cluster in file chain, allocates a new
// cluster at the end of the chain.
uint16_t allocate_new_cluster(uint16_t current_cluster, BPB *bpb) {
  // Make current_cluster point to the next free cluster.
  FatEntry fat_ent = get_fat_entry(current_cluster, bpb);
  uint8_t *fat_sec = read_sector(fat_ent.fat_sec_num);
  uint16_t next_free_cluster = find_free_cluster(bpb);
  *(uint16_t *)(fat_sec + fat_ent.fat_ent_offset) = next_free_cluster;
  write_sector(fat_ent.fat_sec_num, fat_sec);
  free(fat_sec);

  // Make the next free cluster 0xffff instead of 0x0.
  FatEntry free_fat_ent = get_fat_entry(next_free_cluster, bpb);
  uint8_t *free_fat_sec = read_sector(free_fat_ent.fat_sec_num);
  *(int16_t *)(free_fat_sec + free_fat_ent.fat_ent_offset) = 0xffff;
  write_sector(free_fat_ent.fat_sec_num, free_fat_sec);
  free(free_fat_sec);

  return next_free_cluster;
}

// hal_write_file_SDMMC helper
// Gets the FAT entry for a given cluster number.
// Assumes FAT16.
uint16_t check_fat_entry(uint16_t current_cluster, BPB *bpb) {
  FatEntry fat_ent = get_fat_entry(current_cluster, bpb);

  uint8_t *fat_sec = read_sector(fat_ent.fat_sec_num);
  uint16_t fat_ent_val = *((uint16_t *)(fat_sec + fat_ent.fat_ent_offset));
  free(fat_sec);
  return fat_ent_val;
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
FileHandle *open_file(char* filename, BPB *bpb, bool cf) {
  FileHandle *file = find_file(filename, bpb);
  if (file == NULL && cf) {
    file = create_file(filename, bpb);
  }
  return file;
}

BPB* init_filesystem() {
  BPB* retval = malloc(sizeof(BPB));
  uint8_t *bpb_sector = read_sector(0);
  if (bpb_sector == NULL) {
    free(retval);
    return NULL;
  }
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

bool write_file(FileHandle *file, uint8_t* data, uint32_t n_bytes, BPB* bpb) {
  uint32_t written_so_far = 0;
  while (n_bytes > 0) {
    // Read the sector that we're going to write to
    uint32_t cur_sec_num = get_sec_num(file->current_cluster, file->file_pointer, bpb);
    uint8_t *cur_sector = read_sector(cur_sec_num);
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
    write_sector(cur_sec_num, cur_sector);
    free(cur_sector);
    // If we ran off the cluster, go to the next or allocate a new one.
    if (file->file_pointer % (bpb->BPB_BytsPerSec * bpb->BPB_SecPerClus) == 0) {
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
  update_filesize(file->dir_entry_sector, file->dir_entry_offset, file->file_size);
  return true;
}


