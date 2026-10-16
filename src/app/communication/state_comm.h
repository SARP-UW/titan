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
 * @file app/communication/state_comm.h
 * @authors Mahir Emran
 * @brief State-machine communication context
 */
/** Communication state owned by the state machine. */
#pragma once

#include <stdint.h>

#include "app/communication/command.h"
#include "app/communication/packet_protocol.h"

typedef struct {
    uint8_t gnss_packet[PACKET_GNSS_SIZE];
    uint8_t sensor_packet[PACKET_SENSOR_SIZE];
    uint8_t adc_packet[PACKET_ADC_MAX_SIZE];
    uint8_t state_packet[PACKET_STATE_MAX_SIZE];
    uint8_t comm_packet[PACKET_COMM_MAX_SIZE];
    uint8_t rx_packet[PACKET_RX_MAX_SIZE];
    comm_packet_t uplink_comm;
    command_processor_t command_processor;

    uint16_t ping_id;
    uint16_t last_command_id;
    uint8_t last_command_status;
    uint32_t processor_time_ms;
} state_comm_t;

/* Old name retained so I dont get random bugs */
typedef state_comm_t state_comm_shared_t;

extern state_comm_t state_comm_shared;

void state_comm_init(state_comm_t *communication);

/** Process this state's decoded uplink command and update its command status. */
comm_result_t state_comm_process_command(state_comm_t *communication,
                                         uint8_t current_state);
