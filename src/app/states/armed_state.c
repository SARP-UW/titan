#include "app/state.h"
#include "app/utils/devices.h"
#include "app/utils/packets.h"
#include "app/utils/pinout.h"
#include "app/utils/state_comm.h"
#include "app/utils/extern_flash.h"
#include "peripheral/gpio.h"
#include "peripheral/errc.h"
#include "peripheral/systick.h"

//     -- ( ) ARMED: Final Countdown Sequence and umbilical disconnect
//     ~~~ ( ) switch power from umbilical to battery
//     ~~~ ( ) arm igniter

#define ARMED_STATE_IDX 4U
#define FIRE_STATE_IDX 5U
#define SAFE_STATE_IDX 6U
#define LOOP_PERIOD_MS 100U

#define ARMED_MSG_TAG_NONE 0x00U
#define ARMED_MSG_TAG_IGNITER_ARMED 0x01U
#define ARMED_MSG_TAG_POWER_SWITCHED 0x02U

bool armed_state_init(){
    enum ti_errc_t errc;

    tal_set_mode((int)RS485_DE, 1);
    tal_set_mode((int)RS485_RE, 1);
    tal_set_pin((int)RS485_DE, 1);
    tal_set_pin((int)RS485_RE, 0);

    state_comm_shared.last_command_status = COMMAND_STATUS_WAITING;

    radio_init(&radio_dev, &radio_spi_config, &radio_config, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize radio");
    }

    log_state(ARMED_STATE, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to log armed state");
    }

    return 1;
}

int armed_state_run(){
    enum ti_errc_t errc;
    size_t state_packet_len;
    size_t comm_packet_len;
    uint8_t comm_tags[1] = {ARMED_MSG_TAG_NONE};
    uint8_t requested_state = ARMED_STATE_IDX;

    tal_set_pin((int)RS485_DE, 1);
    tal_set_pin((int)RS485_RE, 0);

    // TODO: Switch power from umbilical to battery
    comm_tags[0] = ARMED_MSG_TAG_POWER_SWITCHED;

    // TODO: Arm igniter
    comm_tags[0] = ARMED_MSG_TAG_IGNITER_ARMED;

    build_state_packet(valve_states,
                       VALVE_COUNT,
                       servo_states,
                       SERVO_COUNT,
                       state_comm_shared.state_packet,
                       sizeof(state_comm_shared.state_packet),
                       &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to build armed state packet");
    }

    state_packet_len = (size_t)(9U + ((VALVE_COUNT + 7U) / 8U) + (2U * SERVO_COUNT));
    send_packet_radio_flash(&radio_dev, state_comm_shared.state_packet, state_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send armed state packet");
    }

    build_comm_packet(state_comm_shared.ping_id,
                      ARMED_STATE_IDX,
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
        TI_SET_ERRC(&errc, errc, "Failed to build armed comm packet");
    }

    send_packet_radio_flash(&radio_dev, state_comm_shared.comm_packet, comm_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send armed comm packet");
    }

    receive_uplink_comm_packet(&radio_dev,
                               state_comm_shared.rx_packet,
                               sizeof(state_comm_shared.rx_packet),
                               &state_comm_shared.uplink_comm,
                               &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to receive armed uplink packet");
    }

    if (decode_set_mode_command(&state_comm_shared.uplink_comm,
                                &requested_state,
                                &state_comm_shared.last_command_id,
                                &state_comm_shared.last_command_status)) {
        if (requested_state == FIRE_STATE_IDX || requested_state == SAFE_STATE_IDX) {
            state_comm_shared.ping_id++;
            state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
            systick_delay(LOOP_PERIOD_MS);
            return (int)requested_state;
        }

        state_comm_shared.last_command_status = COMMAND_STATUS_INVALID_STATE;
    }

    state_comm_shared.ping_id++;
    state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
    systick_delay(LOOP_PERIOD_MS);

    return ARMED_STATE_IDX;
}

bool armed_state_destroy(){
    return 1;
}

state build_armed_state() {
    const state armed_state = {
        .init = &armed_state_init,
        .run = &armed_state_run,
        .destroy = &armed_state_destroy
    };
    return armed_state;
}