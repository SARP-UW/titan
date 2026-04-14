#include <stdint.h>
#include "peripheral/qspi.h"
#include "peripheral/errc.h"
#include "extern_flash.h"

void init_extern_flash() {
    curr_state_addr = STATE_POOL_BASE_ADDR;
    curr_data_addr = DATA_POOL_BASE_ADDR;
}

/**
 * @brief  placeholder
 */
void write_extern_flash(enum data_type type, uint8_t* data, uint8_t length, enum ti_errc_t *errc) {
    qspi_cmd_t cmd;
    cmd.instruction = 0x02; 
    cmd.instruction_mode = QSPI_MODE_SINGLE;
    cmd.address_mode = QSPI_MODE_SINGLE;
    cmd.address_size = 24; // 24-bit address
    cmd.dummy_cycles = 0;
    cmd.data_mode = QSPI_MODE_SINGLE; 
    cmd.data_size = length; // This CANNOT be greater than 256 for a single page program operation

    switch(type) {
        case STATE:
            cmd.address = curr_state_addr;
            curr_state_addr += 256;
            break;
        case DATA:
            cmd.address = curr_data_addr;
            curr_data_addr += 256;
            break;
        default:
            *errc = TI_ERRC_INVALID_ARG;
            return;
    }  

    qspi_poll_status_blk();

    qspi_send_cmd(&cmd, data, false, errc);
}
