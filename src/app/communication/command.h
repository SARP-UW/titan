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
 * @file app/communication/command.h
 * @authors Mahir Emran
 * @brief Command translation API
 */
/** Translation from a validated uplink command into a state-machine action. */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "app/communication/packet_protocol.h"

typedef enum {
    COMMAND_TYPE_STATIC = 0x00U,
    COMMAND_TYPE_CUSTOM = 0x01U
} command_type_t;

/* Keep these wire values stable for compatibility with existing clients. */
typedef enum {
    COMMAND_TAG_CHANGE_VALVE_STATE = 0x00U,
    COMMAND_TAG_PULSE_VALVE = 0x01U,
    COMMAND_TAG_CHANGE_SERVO_STATE = 0x02U,
    COMMAND_TAG_PULSE_SERVO = 0x03U,
    COMMAND_TAG_SET_SYS_MODE = 0x04U,
    COMMAND_TAG_SET_COMM_LINK = 0x05U,
    COMMAND_TAG_SLEEP = 0x06U,
    COMMAND_TAG_WAKE = 0x07U,
    COMMAND_TAG_RESTART = 0x08U
} command_tag_t;

typedef enum {
    COMMAND_STATUS_WAITING = 0x00U,
    COMMAND_STATUS_IN_PROGRESS = 0x01U,
    COMMAND_STATUS_SUCCESS = 0x02U,
    COMMAND_STATUS_INVALID_TAG = 0x03U,
    COMMAND_STATUS_INVALID_ARGS = 0x04U,
    COMMAND_STATUS_OUT_OF_RANGE = 0x05U,
    COMMAND_STATUS_HARDWARE_ERROR = 0x06U,
    COMMAND_STATUS_TIMEOUT = 0x07U,
    COMMAND_STATUS_INVALID_STATE = 0x08U,
    COMMAND_STATUS_ABORTED = 0x09U,
    COMMAND_STATUS_AWAITING_CONFIRMATION = 0x0AU,
    COMMAND_STATUS_NULL = 0xFFU
} command_status_t;

typedef enum {
    COMM_ACTION_NONE,
    COMM_ACTION_CHANGE_VALVE_STATE,
    COMM_ACTION_PULSE_VALVE,
    COMM_ACTION_CHANGE_SERVO_STATE,
    COMM_ACTION_PULSE_SERVO,
    COMM_ACTION_SET_MODE,
    COMM_ACTION_SET_COMM_LINK,
    COMM_ACTION_SLEEP,
    COMM_ACTION_WAKE,
    COMM_ACTION_RESTART_REQUEST,
    COMM_ACTION_RESTART_CONFIRM
} comm_action_t;

typedef struct {
    comm_action_t action;
    uint8_t param1;      /* valve/servo ID or primary parameter */
    uint16_t param2;     /* position, pulse duration, or secondary parameter */
    uint16_t param3;     /* additional parameter for servo pulse */
    bool valid;
} comm_result_t;

/** State that must survive between the two restart commands. */
typedef struct {
    bool restart_awaiting_confirmation;
    uint16_t restart_pending_command_id;
} command_processor_t;

void command_processor_init(command_processor_t *processor);

comm_result_t process_command_with_context(command_processor_t *processor,
                                           const comm_packet_t *packet,
                                           uint8_t current_state,
                                           uint16_t *last_command_id,
                                           uint8_t *last_command_status);

/* Compatibility entry point for callers that do not own a processor context. */
comm_result_t process_command(const comm_packet_t *packet,
                              uint8_t current_state,
                              uint16_t *last_command_id,
                              uint8_t *last_command_status);
