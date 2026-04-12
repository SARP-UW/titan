#include "app/state.h"
#include "app/utils/devices.h"
#include "app/utils/packets.h"
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

#define ADC_PACKET_INDEX 0x00
#define LOOP_PERIOD_MS 100U
#define COMM_PERIOD_MS 1000U
#define SENSOR_CYCLES_PER_COMM (COMM_PERIOD_MS / LOOP_PERIOD_MS)

/** Buffers for packets */
static uint8_t gnss_packet[PACKET_GNSS_SIZE];
static uint8_t sensor_packet[PACKET_SENSOR_SIZE];
static uint8_t adc_packet[PACKET_ADC_MAX_SIZE];
static uint8_t state_packet[PACKET_STATE_MAX_SIZE];
static uint8_t comm_packet[PACKET_COMM_MAX_SIZE];
static uint8_t rx_packet[PACKET_RX_MAX_SIZE];
static comm_packet_t uplink_comm;

static uint32_t elapsed_ms;
static uint32_t processor_time_ms;
static uint16_t ping_id;

bool fire_state_init(){
    enum ti_errc_t errc;

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

    return 1;
}

int fire_state_run(){
    static const uint8_t comm_tags[] = {0};

    for (uint8_t cycle = 0; cycle < SENSOR_CYCLES_PER_COMM; cycle++) {
        enum ti_errc_t errc;
        size_t adc_packet_len;
        size_t state_packet_len;

        gnss_pvt_t gnss_pvt;
        gnss_get_pvt(&gnss_dev, &gnss_pvt, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to get GNSS PVT data");
        }

        build_gnss_packet(&gnss_pvt, gnss_packet, sizeof(gnss_packet), &errc);
        send_packet_radio_flash(&radio_dev, gnss_packet, sizeof(gnss_packet), &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit GNSS packet");
        }

        struct imu_result imu_result1;
        struct imu_result imu_result2;
        errc = imu_transfer(&imu_dev1, &imu_result1);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transfer IMU 1 data");
        }
        errc = imu_transfer(&imu_dev2, &imu_result2);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transfer IMU 2 data");
        }

        temperature_result_t temperature_result1;
        temperature_result_t temperature_result2;
        temperature_read_temp(&temperature_dev1, &temperature_result1, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to read temperature 1 data");
        }
        temperature_read_temp(&temperature_dev2, &temperature_result2, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to read temperature 2 data");
        }
        barometer_result_t barometer_result1;
        barometer_result_t barometer_result2;
        barometer_result1 = get_barometer_data(&barometer_dev1, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to read barometer 1 data");
        }
        barometer_result2 = get_barometer_data(&barometer_dev2, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to read barometer 2 data");
        }
        struct magnetometer_result_t magnetometer_result1;
        struct magnetometer_result_t magnetometer_result2;
        errc = magnetometer_read(&magnetometer_dev1, &magnetometer_result1);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transfer magnetometer 1 data");
        }
        errc = magnetometer_read(&magnetometer_dev2, &magnetometer_result2);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transfer magnetometer 2 data");
        }

        build_sensor_packet(&imu_result1,
                            &imu_result2,
                            &barometer_result1,
                            &barometer_result2,
                            &magnetometer_result1,
                            &magnetometer_result2,
                            &temperature_result1,
                            &temperature_result2,
                            sensor_packet,
                            sizeof(sensor_packet),
                            &errc);
        send_packet_radio_flash(&radio_dev, sensor_packet, sizeof(sensor_packet), &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit sensor data packet");
        }

        build_adc_packet(adc_channels, adc_channel_count, ADC_PACKET_INDEX, adc_packet, sizeof(adc_packet), &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to build ADC packet");
        }

        adc_packet_len = (size_t)(10U + (3U * adc_channel_count));
        send_packet_radio_flash(&radio_dev, adc_packet, adc_packet_len, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit ADC packet");
        }

        build_state_packet(valve_states,
                           VALVE_COUNT,
                           servo_states,
                           SERVO_COUNT,
                           state_packet,
                           sizeof(state_packet),
                           &errc);
        state_packet_len = (size_t)(9U + ((VALVE_COUNT + 7U) / 8U) + (2U * SERVO_COUNT));
        send_packet_radio_flash(&radio_dev, state_packet, state_packet_len, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit state packet");
        }

        elapsed_ms += LOOP_PERIOD_MS;
        processor_time_ms += LOOP_PERIOD_MS;
        systick_delay(LOOP_PERIOD_MS);
    }

    {
        enum ti_errc_t errc;
        size_t comm_packet_len;

        build_comm_packet(ping_id,
                          0,
                          processor_time_ms,
                          uplink_comm.command_id,
                          0,
                          comm_tags,
                          1,
                          comm_packet,
                          sizeof(comm_packet),
                          &comm_packet_len,
                          &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to build comm packet");
        }

        send_packet_radio_flash(&radio_dev, comm_packet, comm_packet_len, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to transmit comm packet");
        }

        receive_uplink_comm_packet(&radio_dev, rx_packet, sizeof(rx_packet), &uplink_comm, &errc);
        if (errc && errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to receive or parse uplink comm packet");
        }
    }

    ping_id++;
    elapsed_ms = 0;

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