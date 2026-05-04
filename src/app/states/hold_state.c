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

//     - ( ) HOLD: Maintain launch ready state
//     ~~~ ( ) Monitor leaks or pressure drops
//     ~~~ ( ) Keep GSE Connected for power/data
//     ~~~ ( ) Vent ethonol tank to equalize with nitrous tank

#define HOLD_STATE_IDX 3
#define MAX_STATE_INDEX 6
#define ADC_PACKET_INDEX 0x00U
#define LOOP_PERIOD_MS 100U
#define ETHANOL_VENT_VALVE_IDX 0U
#define ARMED_STATE_IDX 4U
#define PRESSURE_DROP_THRESHOLD 1000U
#define PRESSURE_EQUALIZE_BAND 200U

#define HOLD_MSG_TAG_NONE 0x00U
#define HOLD_MSG_TAG_PRESSURE_ALERT 0x01U
#define HOLD_MSG_TAG_VENT_OPEN 0x02U

static uint32_t prev_ethanol_pressure;
static uint32_t prev_nitrous_pressure;
static bool have_prev_pressure;

static uint8_t update_hold_pressure_and_vent(enum ti_errc_t *errc) {
    sensor_status_t sensor_status;
    barometer_result_t ethanol;
    barometer_result_t nitrous;

    // Initialize status flags
    sensor_status_init(&sensor_status);

    // START BAROMETER READS IN PARALLEL
    barometer_start_read(&barometer_dev1, &ethanol, &sensor_status.baro1_done, &sensor_status.baro1_error, errc);
    barometer_start_read(&barometer_dev2, &nitrous, &sensor_status.baro2_done, &sensor_status.baro2_error, errc);

    while (!sensor_status_all_done(&sensor_status)) {
        // Wait for completion
        // TODO: other work to do here?
    }

    // Check for errors
    if (sensor_status_has_error(&sensor_status)) {
        if (sensor_status.baro1_error) {
            TI_SET_ERRC(errc, TI_ERRC_DEVICE, "Failed to read ethanol pressure");
        }
        if (sensor_status.baro2_error) {
            TI_SET_ERRC(errc, TI_ERRC_DEVICE, "Failed to read nitrous pressure");
        }
        return HOLD_MSG_TAG_PRESSURE_ALERT;
    }

    const uint32_t ethanol_pressure = ethanol.pressure;
    const uint32_t nitrous_pressure = nitrous.pressure;
    bool pressure_alert = false;

    if (have_prev_pressure) {
        if ((prev_ethanol_pressure > ethanol_pressure && (prev_ethanol_pressure - ethanol_pressure) > PRESSURE_DROP_THRESHOLD)
            || (prev_nitrous_pressure > nitrous_pressure && (prev_nitrous_pressure - nitrous_pressure) > PRESSURE_DROP_THRESHOLD)) {
            pressure_alert = true;
        }
    }

    prev_ethanol_pressure = ethanol_pressure;
    prev_nitrous_pressure = nitrous_pressure;
    have_prev_pressure = true;

    if (ethanol_pressure > (nitrous_pressure + PRESSURE_EQUALIZE_BAND)) {
        valve_states[ETHANOL_VENT_VALVE_IDX] = 1U;
    } else {
        valve_states[ETHANOL_VENT_VALVE_IDX] = 0U;
    }

    if (pressure_alert) {
        return HOLD_MSG_TAG_PRESSURE_ALERT;
    }
    if (valve_states[ETHANOL_VENT_VALVE_IDX] != 0U) {
        return HOLD_MSG_TAG_VENT_OPEN;
    }
    return HOLD_MSG_TAG_NONE;
}

bool hold_state_init(){
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

    adc_init(&adc_dev, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize ADC");
    }

    barometer_init(&barometer_dev1, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize ethanol pressure sensor");
    }

    barometer_init(&barometer_dev2, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize nitrous pressure sensor");
    }

    prev_ethanol_pressure = 0;
    prev_nitrous_pressure = 0;
    have_prev_pressure = false;

    log_state(HOLD_STATE, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to log hold state");
    }

    return 1;
}

int hold_state_run(){
    enum ti_errc_t errc;
    size_t adc_packet_len;
    size_t state_packet_len;
    size_t comm_packet_len;
    uint8_t comm_tags[1] = {HOLD_MSG_TAG_NONE};
    uint8_t requested_state = HOLD_STATE_IDX;

    tal_set_pin((int)RS485_DE, 1);
    tal_set_pin((int)RS485_RE, 0);

    comm_tags[0] = update_hold_pressure_and_vent(&errc);

    build_adc_packet(adc_channels,
                     adc_channel_count,
                     ADC_PACKET_INDEX,
                     state_comm_shared.adc_packet,
                     sizeof(state_comm_shared.adc_packet),
                     &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to build hold ADC packet");
    }

    adc_packet_len = (size_t)(10U + (3U * adc_channel_count));
    send_packet_radio_flash(&radio_dev, state_comm_shared.adc_packet, adc_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send hold ADC packet");
    }

    build_state_packet(valve_states,
                       VALVE_COUNT,
                       servo_states,
                       SERVO_COUNT,
                       state_comm_shared.state_packet,
                       sizeof(state_comm_shared.state_packet),
                       &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to build hold state packet");
    }

    state_packet_len = (size_t)(9U + ((VALVE_COUNT + 7U) / 8U) + (2U * SERVO_COUNT));
    send_packet_radio_flash(&radio_dev, state_comm_shared.state_packet, state_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send hold state packet");
    }

    build_comm_packet(state_comm_shared.ping_id,
                      HOLD_STATE_IDX,
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
        TI_SET_ERRC(&errc, errc, "Failed to build hold comm packet");
    }

    send_packet_radio_flash(&radio_dev, state_comm_shared.comm_packet, comm_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send hold comm packet");
    }

    receive_uplink_comm_packet(&radio_dev,
                               state_comm_shared.rx_packet,
                               sizeof(state_comm_shared.rx_packet),
                               &state_comm_shared.uplink_comm,
                               &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to receive hold uplink packet");
    }

    if (decode_set_mode_command(&state_comm_shared.uplink_comm,
                                &requested_state,
                                &state_comm_shared.last_command_id,
                                &state_comm_shared.last_command_status)) {
        if (requested_state == HOLD_STATE_IDX || requested_state == ARMED_STATE_IDX || requested_state == MAX_STATE_INDEX) {
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

    return HOLD_STATE_IDX;
}

bool hold_state_destroy(){
    return 1;
}

state build_hold_state() {
    const state hold_state = {
        .init = &hold_state_init,
        .run = &hold_state_run,
        .destroy = &hold_state_destroy
    };
    return hold_state;
}
