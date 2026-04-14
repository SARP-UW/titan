#include <stdint.h>
#include "peripheral/qspi.h"
#include "peripheral/errc.h"

#pragma once

#define STATE_POOL_BASE_ADDR 0x00000000 // 496 writes of space at 256 bytes per write
uint32_t curr_state_addr;

#define DATA_POOL_BASE_ADDR 0x1F0000000 // 30,750 writes of space at 256 bytes per write
uint32_t curr_data_addr;

enum data_type {
    STATE, 
    DATA
};

void init_extern_flash();


void write_extern_flash(enum data_type type, uint8_t* data, uint8_t length, enum ti_errc_t *errc);
