#pragma once
#include <stdint.h>
#include <stdbool.h>

# if defined(__cplusplus)
extern "C" {
# endif

  // Initialize SDMMC
  bool init_block_device();

  // Reads a single sector at the given LBA, returns heap-allocated sector.
  // returns NULL if not able to allocate.
  uint8_t *read_sector(
      uint32_t logical_block_address
      );

  // Writes the data buffer to the logical block address (sector num),
  // works even if buff spans multiple sectors.
  bool write_sector(
      uint32_t logical_block_address,
      const uint8_t *buff
      );

# if defined(__cplusplus)
}
# endif
