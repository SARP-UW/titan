
#include <string.h>

#include "app/utils/extern_flash.h"
#include "app/utils/packets.h"
#include "app/utils/state_comm.h"
#include "devices/umbilical.h"
#include "peripheral/errc.h"
#include "peripheral/gpio.h"
#include "peripheral/qspi.h"
#include "peripheral/systick.h"

#define LOOP_PERIOD_MS 100U
#define SYSTEM_MODE_STANDBY 1U



static umbilical_t umbilical_dev;
static umbilical_uart_dev umbilical_uart_config = {
    .uart_channel = 2,
    .baud_rate = 115200
};

typedef struct __attribute__((packed)) {
    uint16_t buffer_len;
    uint16_t ping_id;
    uint32_t system_time;
    uint16_t command_id;
    uint8_t command_type;
    uint8_t command_tag;
    uint8_t command_valid;
    uint8_t reserved;
    uint16_t args_len;
} rx_log_header_t;

static void log_rx_packet(const uint8_t *buffer,
                          size_t buffer_len,
                          const comm_packet_t *packet,
                          enum ti_errc_t *errc) {
    if (!buffer || !packet || !errc) {
        return;
    }

    rx_log_header_t header = {
        .buffer_len = (uint16_t)buffer_len,
        .ping_id = packet->ping_id,
        .system_time = packet->system_time,
        .command_id = packet->command_id,
        .command_type = packet->command_type,
        .command_tag = packet->command_tag,
        .command_valid = (uint8_t)(packet->command_valid ? 1U : 0U),
        .reserved = 0U,
        .args_len = (uint16_t)packet->command_args_len
    };

    uint8_t header_bytes[sizeof(header)] = {0};
    memcpy(header_bytes, &header, sizeof(header_bytes));
    log_data(header_bytes, (uint16_t)sizeof(header_bytes), errc);
    if (*errc != TI_ERRC_NONE) {
        return;
    }

    if (buffer_len > 0U) {
        log_data((uint8_t *)buffer, (uint16_t)buffer_len, errc);
    }
}

// NOLINTNEXTLINE(readability-identifier-naming)
void _start() { // NOLINT(misc-use-internal-linkage)
    enum ti_errc_t errc;
    static const uint8_t comm_tags[] = {0};
    size_t comm_packet_len = 0U;

    systick_init();
    // qspi_init();
    // ti_log_init();
    // init_extern_flash();

    // tal_set_mode(txpin, 1);
    // tal_set_mode(rxpin, 1);
    // tal_set_pin(txpin, 1);
    // tal_set_pin(rxpin, 0);

    state_comm_shared.last_command_status = COMMAND_STATUS_WAITING;

    umbilical_init(&umbilical_dev, &umbilical_uart_config, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize umbilical");
    }
    asm("BKPT #0");

    // uint8_t buf[10];
    // for (int i = 0; i < 10; i++) {
    //     buf[i] = i+1;
    // }

    //  send_packet_umbilical(&umbilical_dev,
    //                           buf,
    //                           10,
    //                           &errc);
    // asm("BKPT #0");

    size_t actual_read;
    uint8_t buf2[10];


    // umbilical_receive(&umbilical_dev,
    //                       buf2,
    //                       10,
    //                       &actual_read,
    //                       &errc);

    // asm("BKPT #0");

    // state_comm_shared.last_command_id = 255;
    // state_comm_shared.last_command_status = 255;

    while (1) {
        size_t rx_len = 0U;

        build_comm_packet(state_comm_shared.ping_id,
                          SYSTEM_MODE_STANDBY,
                          state_comm_shared.processor_time_ms,
                          state_comm_shared.last_command_id,
                          state_comm_shared.last_command_status,
                          comm_tags,
                          1,
                          state_comm_shared.comm_packet,
                          sizeof(state_comm_shared.comm_packet),
                          &comm_packet_len,
                          &errc);

        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to build reply comm packet");
            asm("BKPT #0");
            continue;
        }
        asm("BKPT #0");
        send_packet_umbilical(&umbilical_dev,
                              state_comm_shared.comm_packet,
                              comm_packet_len,
                              &errc);

        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to send reply comm packet");
            asm("BKPT #0");
            continue;
        }

        asm("BKPT #0");

        state_comm_shared.ping_id++;
        state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
        umbilical_receive(&umbilical_dev,
                          state_comm_shared.rx_packet,
                          16, 
                          //sizeof(state_comm_shared.rx_packet),
                          &rx_len,
                          &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to receive umbilical packet");
            asm("BKPT #0");
            continue;
        }
        asm("BKPT #0");
        parse_uplink_comm_packet(state_comm_shared.rx_packet,
                                 rx_len,
                                 &state_comm_shared.uplink_comm,
                                 &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to parse umbilical packet");
            asm("BKPT #0");
            continue;
        }

        asm("BKPT #0");
        if (state_comm_shared.uplink_comm.command_valid) {
            state_comm_shared.last_command_id = state_comm_shared.uplink_comm.command_id;
            state_comm_shared.last_command_status = COMMAND_STATUS_SUCCESS;
        } else {
            state_comm_shared.last_command_status = COMMAND_STATUS_WAITING;
        }
        systick_delay(LOOP_PERIOD_MS);
        asm("BKPT #0");
    }
}