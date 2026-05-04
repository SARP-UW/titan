//
// Created by Joshua Beard on 3/1/26.
//

//     -- ( ) STANDBY: Rocket on pad awaiting instruction
//     ~~~ ( ) Await the start fill command
#include <string.h>

#include "app/state.h"
#include "app/utils/devices.h"
#include "app/utils/packets.h"
#include "app/utils/pinout.h"
#include "app/utils/state_comm.h"
#include "app/utils/extern_flash.h"
#include "peripheral/errc.h"
#include "peripheral/gpio.h"
#include "peripheral/systick.h"

#define STANDBY_STATE_IDX 1
#define FILL_STATE_IDX 2
#define LOOP_PERIOD_MS 100U

bool standby_state_init(){
    enum ti_errc_t errc;

    memset(valve_states, 0, sizeof(valve_states));
    memset(servo_states, 0, sizeof(servo_states));

    tal_set_mode((int)RS485_DE, 1);
    tal_set_mode((int)RS485_RE, 1);
    tal_set_pin((int)RS485_DE, 1);
    tal_set_pin((int)RS485_RE, 0);

    state_comm_shared.last_command_status = COMMAND_STATUS_WAITING;

    radio_init(&radio_dev, &radio_spi_config, &radio_config, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize radio");
    }

    log_state(STANDBY_STATE, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to log standby state");
    }

    return 1;
}

int standby_state_run(){
    static const uint8_t comm_tags[] = {0};
    enum ti_errc_t errc;
    size_t state_packet_len;
    size_t comm_packet_len;
    uint8_t requested_state = STANDBY_STATE_IDX;

    tal_set_pin((int)RS485_DE, 1);
    tal_set_pin((int)RS485_RE, 0);

    build_state_packet(valve_states,
                       VALVE_COUNT,
                       servo_states,
                       SERVO_COUNT,
                       state_comm_shared.state_packet,
                       sizeof(state_comm_shared.state_packet),
                       &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to build standby state packet");
    }

    state_packet_len = (size_t)(9U + ((VALVE_COUNT + 7U) / 8U) + (2U * SERVO_COUNT));
    send_packet_radio_flash(&radio_dev, state_comm_shared.state_packet, state_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send standby state packet");
    }

    build_comm_packet(state_comm_shared.ping_id,
                      STANDBY_STATE_IDX,
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
        TI_SET_ERRC(&errc, errc, "Failed to build standby comm packet");
    }

    send_packet_radio_flash(&radio_dev, state_comm_shared.comm_packet, comm_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send standby comm packet");
    }

    receive_uplink_comm_packet(&radio_dev,
                               state_comm_shared.rx_packet,
                               sizeof(state_comm_shared.rx_packet),
                               &state_comm_shared.uplink_comm,
                               &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to receive standby uplink packet");
    }

    if (decode_set_mode_command(&state_comm_shared.uplink_comm,
                                &requested_state,
                                &state_comm_shared.last_command_id,
                                &state_comm_shared.last_command_status)) {
        if (requested_state == FILL_STATE_IDX) {
            state_comm_shared.ping_id++;
            state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
            systick_delay(LOOP_PERIOD_MS);
            return FILL_STATE_IDX;
        }

        state_comm_shared.last_command_status = COMMAND_STATUS_INVALID_STATE;
    }

    state_comm_shared.ping_id++;
    state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
    systick_delay(LOOP_PERIOD_MS);

    return STANDBY_STATE_IDX;
}

bool standby_state_destroy(){
    return 1;
}

state build_standby_state() {
    const state standby_state = {
        .init = &standby_state_init,
        .run = &standby_state_run,
        .destroy = &standby_state_destroy
    };
    return standby_state;
}