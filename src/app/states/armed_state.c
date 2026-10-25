#include "app/state.h"
#include "app/utils/devices.h"
#include "app/utils/packets.h"
#include "app/utils/pinout.h"
#include "app/utils/state_comm.h"
#include "app/utils/sensor_status.h"
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

    // Initialize radio
    radio_init(&radio_dev, &radio_spi_config, &radio_config, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize radio");
    }

    // Initialize sensors
    // imu_init(&imu_dev1, &errc);
    // if (errc && errc != TI_ERRC_NONE) {
    //     TI_SET_ERRC(&errc, errc, "Failed to initialize IMU 1");
    // }

    // imu_init(&imu_dev2, &errc);
    // if (errc && errc != TI_ERRC_NONE) {
    //     TI_SET_ERRC(&errc, errc, "Failed to initialize IMU 2");
    // }

    barometer_init(&barometer_dev1, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize barometer 1");
    }

    barometer_init(&barometer_dev2, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize barometer 2");
    }

    temperature_init(&temperature_dev1, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize temperature 1");
    }

    temperature_init(&temperature_dev2, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize temperature 2");
    }

    log_state(ARMED_STATE, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to log armed state");
    }

    return 1;
}

int armed_state_run(){
    enum ti_errc_t errc;
    size_t sensor_packet_len;
    size_t state_packet_len;
    size_t comm_packet_len;
    uint8_t comm_tags[1] = {ARMED_MSG_TAG_NONE};
    sensor_status_t sensor_status;
    // struct imu_result imu1_result = {0};
    // struct imu_result imu2_result = {0};
    barometer_result_t baro1_result = {0};
    barometer_result_t baro2_result = {0};
    // struct magnetometer_result_t mag1_result = {0};
    // struct magnetometer_result_t mag2_result = {0};
    temperature_result_t temp1_result = {0};
    temperature_result_t temp2_result = {0};

    tal_set_pin((int)RS485_DE, 1);
    tal_set_pin((int)RS485_RE, 0);

    // Switch power from umbilical to battery by pulling BATT_EN low
    tal_set_mode((int)BATT_EN, 1);
    tal_set_pin((int)BATT_EN, 0);
    comm_tags[0] = ARMED_MSG_TAG_POWER_SWITCHED;

    // TODO: Arm igniter
    comm_tags[0] = ARMED_MSG_TAG_IGNITER_ARMED;

    // Initialize status flags for parallel sensor reads
    sensor_status_init(&sensor_status);

    // Read all sensors in parallel
    // imu_start_read(&imu_dev1, &imu1_result, &sensor_status.imu1_done, &sensor_status.imu1_error, &errc);
    // imu_start_read(&imu_dev2, &imu2_result, &sensor_status.imu2_done, &sensor_status.imu2_error, &errc);
    barometer_start_read(&barometer_dev1, &baro1_result, &sensor_status.baro1_done, &sensor_status.baro1_error, &errc);
    barometer_start_read(&barometer_dev2, &baro2_result, &sensor_status.baro2_done, &sensor_status.baro2_error, &errc);
    temperature_start_read(&temperature_dev1, &temp1_result, &sensor_status.temp1_done, &sensor_status.temp1_error, &errc);
    temperature_start_read(&temperature_dev2, &temp2_result, &sensor_status.temp2_done, &sensor_status.temp2_error, &errc);

    // Wait for all sensors to complete
    while (!sensor_status_all_done(&sensor_status)) {
        // Wait for completion
    }

    // Check for sensor errors
    if (sensor_status_has_error(&sensor_status)) {
        // if (sensor_status.imu1_error) {
        //     TI_SET_ERRC(&errc, errc, "Failed to read IMU 1");
        // }
        // if (sensor_status.imu2_error) {
        //     TI_SET_ERRC(&errc, errc, "Failed to read IMU 2");
        // }
        if (sensor_status.baro1_error) {
            TI_SET_ERRC(&errc, errc, "Failed to read barometer 1");
        }
        if (sensor_status.baro2_error) {
            TI_SET_ERRC(&errc, errc, "Failed to read barometer 2");
        }
        if (sensor_status.temp1_error) {
            TI_SET_ERRC(&errc, errc, "Failed to read temperature 1");
        }
        if (sensor_status.temp2_error) {
            TI_SET_ERRC(&errc, errc, "Failed to read temperature 2");
        }
    }

    // Send sensor data packet (0x01)
    build_sensor_packet(&baro1_result, &baro2_result,
                       &temp1_result, &temp2_result,
                       state_comm_shared.sensor_packet, sizeof(state_comm_shared.sensor_packet), &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to build armed sensor packet");
    }

    sensor_packet_len = PACKET_SENSOR_SIZE;
    send_packet_radio_flash(&radio_dev, state_comm_shared.sensor_packet, sensor_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send armed sensor packet");
    }

    // Send state packet (0x04)
    build_state_packet(valve_states, VALVE_COUNT, servo_states, SERVO_COUNT,
                       state_comm_shared.state_packet, sizeof(state_comm_shared.state_packet), &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to build armed state packet");
    }

    state_packet_len = (size_t)(9U + ((VALVE_COUNT + 7U) / 8U) + (2U * SERVO_COUNT));
    send_packet_radio_flash(&radio_dev, state_comm_shared.state_packet, state_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send armed state packet");
    }

    // Send comm packet (0x05)
    build_comm_packet(state_comm_shared.ping_id, ARMED_STATE_IDX,
                      state_comm_shared.processor_time_ms, state_comm_shared.last_command_id,
                      state_comm_shared.last_command_status, comm_tags, 1,
                      state_comm_shared.comm_packet, sizeof(state_comm_shared.comm_packet),
                      &comm_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to build armed comm packet");
    }

    send_packet_radio_flash(&radio_dev, state_comm_shared.comm_packet, comm_packet_len, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to send armed comm packet");
    }

    // Receive uplink comm packet and wait for command
    receive_uplink_comm_packet(&radio_dev, state_comm_shared.rx_packet,
                               sizeof(state_comm_shared.rx_packet),
                               &state_comm_shared.uplink_comm, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to receive armed uplink packet");
    }

    // Process command and handle state transitions
    comm_result_t cmd_result = process_command(&state_comm_shared.uplink_comm, ARMED_STATE_IDX,
                                               &state_comm_shared.last_command_id,
                                               &state_comm_shared.last_command_status);

    if (cmd_result.valid) {
        switch (cmd_result.action) {
            case COMM_ACTION_CHANGE_VALVE_STATE:
                // Change valve state
                if (cmd_result.param1 < VALVE_COUNT) {
                    valve_states[cmd_result.param1] = (uint8_t)cmd_result.param2;
                } else {
                    state_comm_shared.last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                break;

            case COMM_ACTION_PULSE_VALVE:
                // Pulse valve for specified duration
                if (cmd_result.param1 < VALVE_COUNT && cmd_result.param2 > 0) {
                    // TODO: Implement valve pulse functionality
                } else {
                    state_comm_shared.last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                break;

            case COMM_ACTION_CHANGE_SERVO_STATE:
                // Change servo position
                if (cmd_result.param1 < SERVO_COUNT) {
                    servo_states[cmd_result.param1] = cmd_result.param2;
                } else {
                    state_comm_shared.last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                break;

            case COMM_ACTION_PULSE_SERVO:
                // Pulse servo to position for specified duration
                if (cmd_result.param1 < SERVO_COUNT && cmd_result.param3 > 0) {
                    // TODO: Implement servo pulse functionality
                } else {
                    state_comm_shared.last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                break;

            case COMM_ACTION_SET_MODE:
                if (cmd_result.param1 == FIRE_STATE_IDX || cmd_result.param1 == SAFE_STATE_IDX) {
                    state_comm_shared.ping_id++;
                    state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
                    systick_delay(LOOP_PERIOD_MS);
                    return (int)cmd_result.param1;
                }
                state_comm_shared.last_command_status = COMMAND_STATUS_INVALID_STATE;
                break;

            case COMM_ACTION_SET_COMM_LINK:
                // TODO: Implement comm link switching (0 = RS485, 1 = radio)
                break;

            case COMM_ACTION_SLEEP:
                // TODO: Implement sleep functionality
                break;

            case COMM_ACTION_WAKE:
                // TODO: Implement wake functionality
                break;

            case COMM_ACTION_RESTART_REQUEST:
                // First restart command received, awaiting confirmation
                break;

            case COMM_ACTION_RESTART_CONFIRM:
                // Restart confirmed, perform system restart
                // TODO: Implement actual restart
                break;

            default:
                break;
        }
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