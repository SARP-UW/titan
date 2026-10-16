/**
 * Packet serialization and parsing.
 *
 * This layer builds and parses packet fields. ADC packet construction reads
 * its channels; transport and command handling live in separate modules.
 */
#pragma once

#include <stddef.h>
#include <stdint.h>

#include "app/communication/packet_protocol.h"
#include "devices/adc.h"
#include "devices/barometer.h"
#include "devices/gnss.h"
#include "devices/temperature.h"
#include "peripheral/errc.h"

void build_gnss_packet(const gnss_pvt_t *pvt,
                       uint8_t *buffer,
                       size_t buffer_len,
                       enum ti_errc_t *errc);

void build_sensor_packet(const barometer_result_t *baro1,
                         const barometer_result_t *baro2,
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

void parse_uplink_comm_packet(const uint8_t *buffer,
                              size_t buffer_len,
                              comm_packet_t *out,
                              enum ti_errc_t *errc);
