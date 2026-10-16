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
 * @file app/communication/command.c
 * @authors Mahir Emran
 * @brief Command processing for uplink packets
 */
#include "app/communication/command.h"

static comm_result_t empty_result(void) {
    return (comm_result_t){
        .action = COMM_ACTION_NONE,
        .param1 = 0U,
        .param2 = 0U,
        .param3 = 0U,
        .valid = false
    };
}

static void set_status(uint8_t *status, command_status_t value) {
    if (status) {
        *status = (uint8_t)value;
    }
}

static bool has_args(const comm_packet_t *packet, size_t count) {
    return packet->command_args != NULL && packet->command_args_len >= count;
}

static uint16_t read_arg_u16(const uint8_t *args) {
    return (uint16_t)(((uint16_t)args[0] << 8) | args[1]);
}

void command_processor_init(command_processor_t *processor) {
    if (processor) {
        *processor = (command_processor_t){0};
    }
}

comm_result_t process_command_with_context(command_processor_t *processor,
                                           const comm_packet_t *packet,
                                           uint8_t current_state,
                                           uint16_t *last_command_id,
                                           uint8_t *last_command_status) {
    comm_result_t result = empty_result();
    (void)current_state;

    if (!packet || !packet->packet_present || !packet->command_valid) {
        return result;
    }
    if (last_command_id) {
        *last_command_id = packet->command_id;
    }
    if (packet->command_type != COMMAND_TYPE_STATIC) {
        set_status(last_command_status, COMMAND_STATUS_INVALID_TAG);
        return result;
    }

    switch (packet->command_tag) {
        case COMMAND_TAG_CHANGE_VALVE_STATE:
            if (!has_args(packet, 2U)) {
                set_status(last_command_status, COMMAND_STATUS_INVALID_ARGS);
                return result;
            }
            result.action = COMM_ACTION_CHANGE_VALVE_STATE;
            result.param1 = packet->command_args[0];
            result.param2 = packet->command_args[1];
            break;

        case COMMAND_TAG_PULSE_VALVE:
            if (!has_args(packet, 3U)) {
                set_status(last_command_status, COMMAND_STATUS_INVALID_ARGS);
                return result;
            }
            result.action = COMM_ACTION_PULSE_VALVE;
            result.param1 = packet->command_args[0];
            result.param2 = read_arg_u16(&packet->command_args[1]);
            break;

        case COMMAND_TAG_CHANGE_SERVO_STATE:
            if (!has_args(packet, 3U)) {
                set_status(last_command_status, COMMAND_STATUS_INVALID_ARGS);
                return result;
            }
            result.action = COMM_ACTION_CHANGE_SERVO_STATE;
            result.param1 = packet->command_args[0];
            result.param2 = read_arg_u16(&packet->command_args[1]);
            break;

        case COMMAND_TAG_PULSE_SERVO:
            if (!has_args(packet, 5U)) {
                set_status(last_command_status, COMMAND_STATUS_INVALID_ARGS);
                return result;
            }
            result.action = COMM_ACTION_PULSE_SERVO;
            result.param1 = packet->command_args[0];
            result.param2 = read_arg_u16(&packet->command_args[1]);
            result.param3 = read_arg_u16(&packet->command_args[3]);
            break;

        case COMMAND_TAG_SET_SYS_MODE:
            if (!has_args(packet, 1U)) {
                set_status(last_command_status, COMMAND_STATUS_INVALID_ARGS);
                return result;
            }
            result.action = COMM_ACTION_SET_MODE;
            result.param1 = packet->command_args[0];
            break;

        case COMMAND_TAG_SET_COMM_LINK:
            if (!has_args(packet, 1U)) {
                set_status(last_command_status, COMMAND_STATUS_INVALID_ARGS);
                return result;
            }
            result.action = COMM_ACTION_SET_COMM_LINK;
            result.param1 = packet->command_args[0];
            break;

        case COMMAND_TAG_SLEEP:
            result.action = COMM_ACTION_SLEEP;
            break;

        case COMMAND_TAG_WAKE:
            result.action = COMM_ACTION_WAKE;
            break;

        case COMMAND_TAG_RESTART:
            if (!processor) {
                set_status(last_command_status, COMMAND_STATUS_INVALID_ARGS);
                return result;
            }
            if (processor->restart_awaiting_confirmation) {
                if (packet->command_id != processor->restart_pending_command_id) {
                    set_status(last_command_status, COMMAND_STATUS_INVALID_ARGS);
                    return result;
                }
                result.action = COMM_ACTION_RESTART_CONFIRM;
                processor->restart_awaiting_confirmation = false;
                processor->restart_pending_command_id = 0U;
            } else {
                result.action = COMM_ACTION_RESTART_REQUEST;
                processor->restart_awaiting_confirmation = true;
                processor->restart_pending_command_id = packet->command_id;
                set_status(last_command_status, COMMAND_STATUS_AWAITING_CONFIRMATION);
                result.valid = true;
                return result;
            }
            break;

        default:
            set_status(last_command_status, COMMAND_STATUS_INVALID_TAG);
            return result;
    }

    result.valid = true;
    set_status(last_command_status, COMMAND_STATUS_SUCCESS);
    return result;
}

comm_result_t process_command(const comm_packet_t *packet,
                              uint8_t current_state,
                              uint16_t *last_command_id,
                              uint8_t *last_command_status) {
    static command_processor_t legacy_processor;
    return process_command_with_context(&legacy_processor,
                                        packet,
                                        current_state,
                                        last_command_id,
                                        last_command_status);
}
