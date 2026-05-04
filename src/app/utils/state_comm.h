/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @file app/utils/state_comm.h
 * @authors Mahir Emran
 * @brief Utility functions to send packets
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>

#include "app/utils/packets.h"

#define COMMAND_TYPE_STATIC 0x00U
#define COMMAND_TAG_SET_SYS_MODE 0x04U

#define COMMAND_STATUS_WAITING 0x00U
#define COMMAND_STATUS_SUCCESS 0x02U
#define COMMAND_STATUS_INVALID_TAG 0x03U
#define COMMAND_STATUS_INVALID_ARGS 0x04U
#define COMMAND_STATUS_INVALID_STATE 0x08U
#define COMMAND_STATUS_NULL 0xFFU

typedef struct {
    uint8_t gnss_packet[PACKET_GNSS_SIZE];
    uint8_t sensor_packet[PACKET_SENSOR_SIZE];
    uint8_t adc_packet[PACKET_ADC_MAX_SIZE];
    uint8_t state_packet[PACKET_STATE_MAX_SIZE];
    uint8_t comm_packet[PACKET_COMM_MAX_SIZE];
    uint8_t rx_packet[PACKET_RX_MAX_SIZE];
    comm_packet_t uplink_comm;

    uint16_t ping_id;
    uint16_t last_command_id;
    uint8_t last_command_status;
    uint32_t processor_time_ms;
} state_comm_shared_t;

extern state_comm_shared_t state_comm_shared;

bool decode_set_mode_command(const comm_packet_t *packet,
                             uint8_t *requested_mode,
                             uint16_t *last_command_id,
                             uint8_t *last_command_status);
