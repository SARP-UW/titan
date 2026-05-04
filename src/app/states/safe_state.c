#include "app/state.h"
#include "app/utils/devices.h"
#include "app/utils/packets.h"
#include "app/utils/pinout.h"
#include "app/utils/state_comm.h"
#include "app/utils/extern_flash.h"
#include "app/utils/sensor_status.h"
#include "peripheral/gpio.h"
#include "peripheral/errc.h"
#include "peripheral/systick.h"

//     -- ( ) SAFE/ABORT: Venting to abort mission
//     ~~~ ( ) Vent everything

#define SAFE_STATE_IDX 6U
#define LOOP_PERIOD_MS 100U
#define SAFE_PRESSURE_THRESHOLD 100U // Pressure below this is considered safe

#define SAFE_MSG_TAG_NONE 0x00U
#define SAFE_MSG_TAG_VENTING 0x01U
#define SAFE_MSG_TAG_SAFE 0x02U

bool safe_state_init(){
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

    barometer_init(&barometer_dev1, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize ethanol pressure sensor");
    }

    barometer_init(&barometer_dev2, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize nitrous pressure sensor");
    }

    log_state(SAFE_STATE, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to log safe state");
    }

    return 1;
}

int safe_state_run(){
    enum ti_errc_t errc;
    size_t state_packet_len;
    size_t comm_packet_len;
    uint8_t comm_tags[1] = {SAFE_MSG_TAG_NONE};
    uint8_t requested_state = SAFE_STATE_IDX;
    sensor_status_t sensor_status;

    tal_set_pin((int)RS485_DE, 1);
    tal_set_pin((int)RS485_RE, 0);

    // Open all vent valves
    for (uint8_t i = 0; i < VALVE_COUNT; i++) {
        valve_states[i] = 1U; // Open all valves
    }
    comm_tags[0] = SAFE_MSG_TAG_VENTING;

    // Initialize status flags
    sensor_status_init(&sensor_status);

    // Read pressures in parallel
    barometer_result_t ethanol;
    barometer_result_t nitrous;
    barometer_start_read(&barometer_dev1, &ethanol, &sensor_status.baro1_done, &sensor_status.baro1_error, &errc);
    barometer_start_read(&barometer_dev2, &nitrous, &sensor_status.baro2_done, &sensor_status.baro2_error, &errc);

    // Wait for all barometers to complete
    while (!sensor_status_all_done(&sensor_status)) {
        // Wait for completion
    }

    // Check for errors
    if (sensor_status_has_error(&sensor_status)) {
        if (sensor_status.baro1_error) {
            TI_SET_ERRC(&errc, errc, "Failed to read ethanol pressure");
        }
        if (sensor_status.baro2_error) {
            TI_SET_ERRC(&errc, errc, "Failed to read nitrous pressure");
        }
    }

    // Check if pressures are safe
    if (ethanol.pressure < SAFE_PRESSURE_THRESHOLD && nitrous.pressure < SAFE_PRESSURE_THRESHOLD) {
        comm_tags[0] = SAFE_MSG_TAG_SAFE;
    }

    build_state_packet(valve_states,
                       VALVE_COUNT,
                       servo_states,
                       SERVO_COUNT,
                       state_comm_shared.state_packet,
                       sizeof(state_comm_shared.state_packet),
                       &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to build safe state packet");
    }

    state_packet_len = (size_t)(9U + ((VALVE_COUNT + 7U) / 8U) + (2U * SERVO_COUNT));
    send_packet_radio_flash(&radio_dev, state_comm_shared.state_packet, state_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send safe state packet");
    }

    build_comm_packet(state_comm_shared.ping_id,
                      SAFE_STATE_IDX,
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
        TI_SET_ERRC(&errc, errc, "Failed to build safe comm packet");
    }

    send_packet_radio_flash(&radio_dev, state_comm_shared.comm_packet, comm_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send safe comm packet");
    }

    receive_uplink_comm_packet(&radio_dev,
                               state_comm_shared.rx_packet,
                               sizeof(state_comm_shared.rx_packet),
                               &state_comm_shared.uplink_comm,
                               &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to receive safe uplink packet");
    }

    if (decode_set_mode_command(&state_comm_shared.uplink_comm,
                                &requested_state,
                                &state_comm_shared.last_command_id,
                                &state_comm_shared.last_command_status)) {
        // Only allow transition to standby state from safe state
        if (requested_state == 1) { // STANDBY_STATE_IDX
            state_comm_shared.ping_id++;
            state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
            systick_delay(LOOP_PERIOD_MS);
            return 1;
        }

        state_comm_shared.last_command_status = COMMAND_STATUS_INVALID_STATE;
    }

    state_comm_shared.ping_id++;
    state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
    systick_delay(LOOP_PERIOD_MS);

    return SAFE_STATE_IDX;
}

bool safe_state_destroy(){
    return 1;
}

state build_safe_state() {
    const state safe_state = {
        .init = &safe_state_init,
        .run = &safe_state_run,
        .destroy = &safe_state_destroy
    };
    return safe_state;
}