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
 * @file app/utils/state_comm.c
 * @authors Mahir Emran
 * @brief Command processing for uplink packets
 */
#include "app/utils/state_comm.h"

static bool restart_awaiting_confirmation = false;
static uint16_t restart_pending_command_id = 0;

state_comm_shared_t state_comm_shared = {
    .last_command_status = COMMAND_STATUS_NULL
};

comm_result_t process_command(const comm_packet_t *packet,
                              uint8_t current_state,
                              uint16_t *last_command_id,
                              uint8_t *last_command_status) {
    comm_result_t result = {
        .action = COMM_ACTION_NONE,
        .param1 = 0,
        .param2 = 0,
        .param3 = 0,
        .valid = false
    };

    if (!packet || !packet->packet_present || !packet->command_valid) {
        return result;
    }

    if (last_command_id) {
        *last_command_id = packet->command_id;
    }

    if (packet->command_type != COMMAND_TYPE_STATIC) {
        if (last_command_status) {
            *last_command_status = COMMAND_STATUS_INVALID_TAG;
        }
        return result;
    }

    switch (packet->command_tag) {
        case COMMAND_TAG_CHANGE_VALVE_STATE: {
            if (!packet->command_args || packet->command_args_len < 2U) {
                if (last_command_status) {
                    *last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                return result;
            }
            result.action = COMM_ACTION_CHANGE_VALVE_STATE;
            result.param1 = packet->command_args[0];  // valve id
            result.param2 = packet->command_args[1];  // new state (0 = closed, 1 = open)
            result.valid = true;
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_SUCCESS;
            }
            break;
        }

        case COMMAND_TAG_PULSE_VALVE: {
            if (!packet->command_args || packet->command_args_len < 3U) {
                if (last_command_status) {
                    *last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                return result;
            }
            result.action = COMM_ACTION_PULSE_VALVE;
            result.param1 = packet->command_args[0];  // valve id
            result.param2 = ((uint16_t)packet->command_args[1] << 8) | packet->command_args[2];  // pulse duration (ms)
            result.valid = true;
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_SUCCESS;
            }
            break;
        }

        case COMMAND_TAG_CHANGE_SERVO_STATE: {
            if (!packet->command_args || packet->command_args_len < 3U) {
                if (last_command_status) {
                    *last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                return result;
            }
            result.action = COMM_ACTION_CHANGE_SERVO_STATE;
            result.param1 = packet->command_args[0];  // servo id
            result.param2 = ((uint16_t)packet->command_args[1] << 8) | packet->command_args[2];  // new position
            result.valid = true;
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_SUCCESS;
            }
            break;
        }

        case COMMAND_TAG_PULSE_SERVO: {
            if (!packet->command_args || packet->command_args_len < 5U) {
                if (last_command_status) {
                    *last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                return result;
            }
            result.action = COMM_ACTION_PULSE_SERVO;
            result.param1 = packet->command_args[0];  // servo id
            result.param2 = ((uint16_t)packet->command_args[1] << 8) | packet->command_args[2];  // new position
            result.param3 = ((uint16_t)packet->command_args[3] << 8) | packet->command_args[4];  // pulse duration (ms)
            result.valid = true;
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_SUCCESS;
            }
            break;
        }

        case COMMAND_TAG_SET_SYS_MODE: {
            if (!packet->command_args || packet->command_args_len < 1U) {
                if (last_command_status) {
                    *last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                return result;
            }
            result.action = COMM_ACTION_SET_MODE;
            result.param1 = packet->command_args[0];
            result.valid = true;
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_SUCCESS;
            }
            break;
        }

        case COMMAND_TAG_SET_COMM_LINK: {
            if (!packet->command_args || packet->command_args_len < 1U) {
                if (last_command_status) {
                    *last_command_status = COMMAND_STATUS_INVALID_ARGS;
                }
                return result;
            }
            result.action = COMM_ACTION_SET_COMM_LINK;
            result.param1 = packet->command_args[0];
            result.valid = true;
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_SUCCESS;
            }
            break;
        }

        case COMMAND_TAG_SLEEP: {
            result.action = COMM_ACTION_SLEEP;
            result.valid = true;
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_SUCCESS;
            }
            break;
        }

        case COMMAND_TAG_WAKE: {
            result.action = COMM_ACTION_WAKE;
            result.valid = true;
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_SUCCESS;
            }
            break;
        }

        case COMMAND_TAG_RESTART: {
            if (restart_awaiting_confirmation) {
                if (packet->command_id == restart_pending_command_id) {
                    result.action = COMM_ACTION_RESTART_CONFIRM;
                    result.valid = true;
                    restart_awaiting_confirmation = false;
                    restart_pending_command_id = 0;
                    if (last_command_status) {
                        *last_command_status = COMMAND_STATUS_SUCCESS;
                    }
                } else {
                    if (last_command_status) {
                        *last_command_status = COMMAND_STATUS_INVALID_ARGS;
                    }
                }
            } else {
                result.action = COMM_ACTION_RESTART_REQUEST;
                result.valid = true;
                restart_awaiting_confirmation = true;
                restart_pending_command_id = packet->command_id;
                if (last_command_status) {
                    *last_command_status = COMMAND_STATUS_AWAITING_CONFIRMATION;
                }
            }
            break;
        }

        default: {
            if (last_command_status) {
                *last_command_status = COMMAND_STATUS_INVALID_TAG;
            }
            break;
        }
    }

    return result;
}
