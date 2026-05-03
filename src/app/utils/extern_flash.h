#include <stdint.h>
#include "peripheral/qspi.h"
#include "peripheral/errc.h"

#pragma once

#define STATE_POOL_BASE_ADDR 0x00000000 
volatile uint32_t* const state_addr_ptr = (volatile uint32_t*)0x38800000; // Address of current state

#define DATA_POOL_BASE_ADDR 0x00000200
volatile uint32_t* const data_addr_ptr = (volatile uint32_t*)0x38800004; // Address of current data log
volatile uint32_t* const curr_page_space_ptr = (volatile uint32_t*)0x38800008; // Remaining space in current page

enum states_t {
    ARMED_STATE = 0x01,
    FILL_STATE = 0x02,
    FIRE_STATE = 0x03,
    HOLD_STATE = 0x04,
    INIT_STATE = 0x05,
    SAFE_STATE = 0x06,
    STANDBY_STATE = 0x07
};

void init_extern_flash();

void log_state(enum states_t state, enum ti_errc_t* errc);

enum states_t get_prev_state(enum ti_errc_t* errc);

bool check_saved_state();

void log_data(uint8_t* data, uint16_t length, enum ti_errc_t* errc);
