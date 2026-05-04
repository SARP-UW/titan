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
 * @brief Utility functions to send packets
 */
#include "app/utils/state_comm.h"

state_comm_shared_t state_comm_shared = {
    .last_command_status = COMMAND_STATUS_NULL
};

bool decode_set_mode_command(const comm_packet_t *packet,
                             uint8_t *requested_mode,
                             uint16_t *last_command_id,
                             uint8_t *last_command_status) {
    if (!packet || !packet->packet_present || !packet->command_valid) {
        return false;
    }

    if (last_command_id) {
        *last_command_id = packet->command_id;
    }

    if (packet->command_type != COMMAND_TYPE_STATIC || packet->command_tag != COMMAND_TAG_SET_SYS_MODE) {
        if (last_command_status) {
            *last_command_status = COMMAND_STATUS_INVALID_TAG;
        }
        return false;
    }

    if (!packet->command_args || packet->command_args_len < 1U || !requested_mode) {
        if (last_command_status) {
            *last_command_status = COMMAND_STATUS_INVALID_ARGS;
        }
        return false;
    }

    *requested_mode = packet->command_args[0];
    if (last_command_status) {
        *last_command_status = COMMAND_STATUS_SUCCESS;
    }
    return true;
}
