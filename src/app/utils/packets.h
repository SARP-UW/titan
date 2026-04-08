#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "devices/adc.h"
#include "devices/barometer.h"
#include "devices/gnss.h"
#include "devices/imu.h"
#include "devices/magnetometer.h"
#include "devices/radio.h"
#include "devices/temperature.h"
#include "peripheral/errc.h"

#define PACKET_MAGIC_HEADER 5350924267264234322ULL
#define PACKET_SENSOR_TYPE 0x01U
#define PACKET_GNSS_TYPE 0x02U
#define PACKET_ADC_TYPE 0x03U
#define PACKET_STATE_TYPE 0x04U
#define PACKET_COMM_TYPE 0x05U

#define PACKET_GNSS_SIZE 31U
#define PACKET_SENSOR_SIZE 61U
#define PACKET_ADC_MAX_SIZE 64U
#define PACKET_STATE_MAX_SIZE 64U
#define PACKET_COMM_MAX_SIZE 64U
#define PACKET_RX_MAX_SIZE 64U

typedef struct {
    bool packet_present;
    uint16_t ping_id;
    uint32_t system_time;
    bool command_valid;
    uint16_t command_id;
    uint8_t command_type;
    uint8_t command_tag;
    const uint8_t *command_args;
    size_t command_args_len;
} comm_packet_t;

void build_gnss_packet(const gnss_pvt_t *pvt, uint8_t *buffer, size_t buffer_len, enum ti_errc_t *errc);

void build_sensor_packet(const struct imu_result *imu1,
                         const struct imu_result *imu2,
                         const barometer_result_t *baro1,
                         const barometer_result_t *baro2,
                         const struct magnetometer_result_t *mag1,
                         const struct magnetometer_result_t *mag2,
                         const temperature_result_t *temp1,
                         const temperature_result_t *temp2,
                         uint8_t *buffer,
                         size_t buffer_len,
                         enum ti_errc_t *errc);

void build_adc_packet(const struct adc_channel *channels,
                      uint8_t channel_count,
                      uint8_t packet_index,
                      uint8_t *buffer,
                      size_t buffer_len,
                      enum ti_errc_t *errc);

void build_state_packet(const uint8_t *valves,
                        uint16_t valve_count,
                        const uint16_t *servos,
                        uint16_t servo_count,
                        uint8_t *buffer,
                        size_t buffer_len,
                        enum ti_errc_t *errc);

void build_comm_packet(uint16_t ping_id,
                       uint8_t system_mode,
                       uint32_t processor_time_ms,
                       uint16_t last_command_id,
                       uint8_t last_command_status,
                       const uint8_t *message_tags,
                       uint8_t message_count,
                       uint8_t *buffer,
                       size_t buffer_len,
                       size_t *packet_len,
                       enum ti_errc_t *errc);

void send_packet_radio_flash(radio_t *radio,
                             const uint8_t *packet,
                             size_t packet_len,
                             enum ti_errc_t *errc);

void parse_uplink_comm_packet(const uint8_t *buffer,
                              size_t buffer_len,
                              comm_packet_t *out,
                              enum ti_errc_t *errc);

void receive_uplink_comm_packet(radio_t *radio,
                                uint8_t *rx_buffer,
                                size_t rx_buffer_len,
                                comm_packet_t *out,
                                enum ti_errc_t *errc);
