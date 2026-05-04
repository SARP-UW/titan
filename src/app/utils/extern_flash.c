#include <stdint.h>
#include "peripheral/qspi.h"
#include "peripheral/errc.h"
#include "extern_flash.h"

volatile uint32_t* const state_addr_ptr = (volatile uint32_t*)0x38800000; // Address of current state
volatile uint32_t* const data_addr_ptr = (volatile uint32_t*)0x38800004; // Address of current data log
volatile uint32_t* const curr_page_space_ptr = (volatile uint32_t*)0x38800008; // Remaining space in current page

// ONLY INITIALIZE ONCE AT THE START OF THE PROGRAM. 
// DO NOT CALL MORE THAN ONCE OR YOU WILL LOSE ALL DATA IN EXTERNAL FLASH MEMORY
void init_extern_flash() {
    *state_addr_ptr = STATE_POOL_BASE_ADDR;
    *curr_page_space_ptr = 0; 
}

void log_state(enum states_t state, enum ti_errc_t* errc) {
    qspi_cmd_t cmd = {
        .instruction = 0x02, // Page Program command
        .instruction_mode = QSPI_MODE_SINGLE,
        .address = *state_addr_ptr,
        .address_mode = QSPI_MODE_SINGLE,
        .address_size = 3, // 24-bit address
        .dummy_cycles = 0,
        .data_mode = QSPI_MODE_SINGLE,
        .data_size = 1
    };

    uint8_t data = (uint8_t) state; 
    qspi_send_cmd(&cmd, &data, false, errc); 

    *state_addr_ptr += 1;
}

bool check_saved_state() {
    return *state_addr_ptr != STATE_POOL_BASE_ADDR;
}

enum states_t get_prev_state(enum ti_errc_t* errc) {
    qspi_cmd_t cmd = {
        .instruction = 0x03, // Read Data command
        .instruction_mode = QSPI_MODE_SINGLE,
        .address = *state_addr_ptr - 1,
        .address_mode = QSPI_MODE_SINGLE,
        .address_size = 3, // 24-bit address
        .dummy_cycles = 0,
        .data_mode = QSPI_MODE_SINGLE,
        .data_size = 1
    };

    uint8_t data;
    qspi_send_cmd(&cmd, &data, true, errc); 

    if (errc != TI_ERRC_NONE) {
        return -1;
    }

    return (enum states_t) data; 
}

// Data logged can be no larger than 256 bytes at a time. 
void log_data(uint8_t* data, uint16_t length, enum ti_errc_t* errc) {
    qspi_cmd_t cmd = {
            .instruction = 0x02, // Page Program command
            .instruction_mode = QSPI_MODE_SINGLE,
            .address = *data_addr_ptr,
            .address_mode = QSPI_MODE_SINGLE,
            .address_size = 3, // 24-bit address
            .dummy_cycles = 0,
            .data_mode = QSPI_MODE_SINGLE,
            .data_size = length
        };

    // If the current page space exceeds 256 bytes, we need to move to the next page
    if ((*curr_page_space_ptr  + length) > 256) {
        uint8_t diff = 256 - (*curr_page_space_ptr); 
        *curr_page_space_ptr = length - diff;

        cmd.data_size = diff;
        qspi_send_cmd(&cmd, data, false, errc);

        cmd.data_size = length - diff;
        cmd.address += diff; 
        data += diff; 
        qspi_send_cmd(&cmd, data, false, errc);
    } 
    else {
        *curr_page_space_ptr += length;
        qspi_send_cmd(&cmd, data, false, errc);
    }

    *data_addr_ptr += length;
}
