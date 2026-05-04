#include "app/state.h"
#include "app/utils/devices.h"
#include "app/utils/packets.h"
#include "app/utils/state_comm.h"
#include "app/utils/extern_flash.h"
#include "app/utils/sensor_status.h"
#include "devices/imu.h"
#include "devices/gnss.h"
#include "devices/barometer.h"
#include "devices/actuator.h"
#include "devices/adc.h"
#include "devices/magnetometer.h"
#include "devices/temperature.h"
#include "devices/radio.h"
#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include "peripheral/systick.h"

//     -- ( ) FIRING: Deliver propelants to manifold
//     ~~~ ( ) Open main propelant valves
//     ~~~ ( ) Execute control loop for engine burn
//     ~~~ ( ) Send and record telemetry

#define FIRE_STATE_IDX 5U
#define ADC_PACKET_INDEX 0x00
#define LOOP_PERIOD_MS 100U
#define COMM_PERIOD_MS 1000U
#define SENSOR_CYCLES_PER_COMM (COMM_PERIOD_MS / LOOP_PERIOD_MS)

bool fire_state_init(){
    enum ti_errc_t errc;

    state_comm_shared.last_command_status = COMMAND_STATUS_WAITING;

    radio_init(&radio_dev, &radio_spi_config, &radio_config, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize radio");
    }
    errc = imu_init(&imu_dev1);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize IMU 1");
    }
    errc = imu_init(&imu_dev2);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize IMU 2");
    }
    gnss_init(&gnss_dev, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize GNSS");
    }
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
    magnetometer_init(&magnetometer_dev1);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize magnetometer 1");
    }
    magnetometer_init(&magnetometer_dev2);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize magnetometer 2");
    }

    adc_init(&adc_dev, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize ADC");
    }

    log_state(FIRE_STATE, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to log fire state");
    }

    return 1;
}

int fire_state_run(){
    static const uint8_t comm_tags[] = {0};
    sensor_status_t sensor_status;

    for (uint8_t cycle = 0; cycle < SENSOR_CYCLES_PER_COMM; cycle++) {
        enum ti_errc_t errc;
        size_t adc_packet_len;
        size_t state_packet_len;

        gnss_pvt_t gnss_pvt;
        struct imu_result imu_result1;
        struct imu_result imu_result2;
        barometer_result_t barometer_result1;
        barometer_result_t barometer_result2;
        temperature_result_t temperature_result1;
        temperature_result_t temperature_result2;
        struct magnetometer_result_t magnetometer_result1;
        struct magnetometer_result_t magnetometer_result2;

        // Initialize status flags
        sensor_status_init(&sensor_status);

        // START ALL SENSOR READS IN PARALLEL
        gnss_start_read(&gnss_dev, &gnss_pvt, &sensor_status.gnss_done, &sensor_status.gnss_error, &errc);
        imu_start_read(&imu_dev1, &imu_result1, &sensor_status.imu1_done, &sensor_status.imu1_error, &errc);
        imu_start_read(&imu_dev2, &imu_result2, &sensor_status.imu2_done, &sensor_status.imu2_error, &errc);
        barometer_start_read(&barometer_dev1, &barometer_result1, &sensor_status.baro1_done, &sensor_status.baro1_error, &errc);
        barometer_start_read(&barometer_dev2, &barometer_result2, &sensor_status.baro2_done, &sensor_status.baro2_error, &errc);
        temperature_start_read(&temperature_dev1, &temperature_result1, &sensor_status.temp1_done, &sensor_status.temp1_error, &errc);
        temperature_start_read(&temperature_dev2, &temperature_result2, &sensor_status.temp2_done, &sensor_status.temp2_error, &errc);
        magnetometer_start_read(&magnetometer_dev1, &magnetometer_result1, &sensor_status.mag1_done, &sensor_status.mag1_error, &errc);
        magnetometer_start_read(&magnetometer_dev2, &magnetometer_result2, &sensor_status.mag2_done, &sensor_status.mag2_error, &errc);
        adc_start_read(&adc_dev, adc_channels, adc_channel_count, &sensor_status.adc_done, &sensor_status.adc_error, &errc);

        while (!sensor_status_all_done(&sensor_status)) {
            // Wait for all sensors to complete
            // TODO: other work to do here?
        }

        // Check for any sensor errors
        if (sensor_status_has_error(&sensor_status)) {
            // Log error but continue with available data
            if (sensor_status.gnss_error) {
                TI_SET_ERRC(&errc, TI_ERRC_DEVICE, "GNSS sensor error");
            }
            if (sensor_status.imu1_error || sensor_status.imu2_error) {
                TI_SET_ERRC(&errc, TI_ERRC_DEVICE, "IMU sensor error");
            }
            if (sensor_status.baro1_error || sensor_status.baro2_error) {
                TI_SET_ERRC(&errc, TI_ERRC_DEVICE, "Barometer sensor error");
            }
            if (sensor_status.temp1_error || sensor_status.temp2_error) {
                TI_SET_ERRC(&errc, TI_ERRC_DEVICE, "Temperature sensor error");
            }
            if (sensor_status.mag1_error || sensor_status.mag2_error) {
                TI_SET_ERRC(&errc, TI_ERRC_DEVICE, "Magnetometer sensor error");
            }
            if (sensor_status.adc_error) {
                TI_SET_ERRC(&errc, TI_ERRC_DEVICE, "ADC sensor error");
            }
        }

        // ALL SENSORS DONE - NOW SEND ALL PACKETS AT ONCE
        // Build and send GNSS packet
        build_gnss_packet(&gnss_pvt,
                          state_comm_shared.gnss_packet,
                          sizeof(state_comm_shared.gnss_packet),
                          &errc);
        send_packet_radio_flash(&radio_dev,
                                state_comm_shared.gnss_packet,
                                sizeof(state_comm_shared.gnss_packet),
                                &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit GNSS packet");
        }

        // Build and send sensor packet
        build_sensor_packet(&imu_result1,
                            &imu_result2,
                            &barometer_result1,
                            &barometer_result2,
                            &magnetometer_result1,
                            &magnetometer_result2,
                            &temperature_result1,
                            &temperature_result2,
                            state_comm_shared.sensor_packet,
                            sizeof(state_comm_shared.sensor_packet),
                            &errc);
        send_packet_radio_flash(&radio_dev,
                                state_comm_shared.sensor_packet,
                                sizeof(state_comm_shared.sensor_packet),
                                &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit sensor data packet");
        }

        // Build and send ADC packet
        build_adc_packet(adc_channels,
                         adc_channel_count,
                         ADC_PACKET_INDEX,
                         state_comm_shared.adc_packet,
                         sizeof(state_comm_shared.adc_packet),
                         &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to build ADC packet");
        }

        adc_packet_len = (size_t)(10U + (3U * adc_channel_count));
        send_packet_radio_flash(&radio_dev, state_comm_shared.adc_packet, adc_packet_len, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit ADC packet");
        }

        // Build and send state packet
        build_state_packet(valve_states,
                           VALVE_COUNT,
                           servo_states,
                           SERVO_COUNT,
                           state_comm_shared.state_packet,
                           sizeof(state_comm_shared.state_packet),
                           &errc);
        state_packet_len = (size_t)(9U + ((VALVE_COUNT + 7U) / 8U) + (2U * SERVO_COUNT));
        send_packet_radio_flash(&radio_dev, state_comm_shared.state_packet, state_packet_len, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit state packet");
        }

        state_comm_shared.processor_time_ms += LOOP_PERIOD_MS;
        systick_delay(LOOP_PERIOD_MS);
    }

    // Comm packet handling (same as before)
    {
        enum ti_errc_t errc;
        size_t comm_packet_len;

        build_comm_packet(state_comm_shared.ping_id,
                          FIRE_STATE_IDX,
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
            TI_SET_ERRC(&errc, errc, "Failed to build comm packet");
        }

        send_packet_radio_flash(&radio_dev, state_comm_shared.comm_packet, comm_packet_len, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit comm packet");
        }

        receive_uplink_comm_packet(&radio_dev,
                                   state_comm_shared.rx_packet,
                                   sizeof(state_comm_shared.rx_packet),
                                   &state_comm_shared.uplink_comm,
                                   &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to receive or parse uplink comm packet");
        }

        state_comm_shared.last_command_id = state_comm_shared.uplink_comm.command_id;
        state_comm_shared.last_command_status = state_comm_shared.uplink_comm.command_valid
                                              ? COMMAND_STATUS_SUCCESS
                                              : COMMAND_STATUS_WAITING;
    }

    state_comm_shared.ping_id++;

    return 6;
}

bool fire_state_destroy(){
    return 1;
}

state build_fire_state() {
    const state fire_state = {
        .init = &fire_state_init,
        .run = &fire_state_run,
        .destroy = &fire_state_destroy
    };
    return fire_state;
}
