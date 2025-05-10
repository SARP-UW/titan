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
 * @brief Driver Implementation for the SDMMC
 */

#include "block_device.h"
#include <stdbool.h>
#include <stdint.h>
#include "internal/mmio.h"
#include "gpio.h"

bool init_block_device() {
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

  return true;
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
