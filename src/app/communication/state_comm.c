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
 * @file app/communication/state_comm.c
 * @authors Mahir Emran
 * @brief Communication state storage and command wrapper
 */
#include "app/communication/state_comm.h"

state_comm_t state_comm_shared = {
    .last_command_status = COMMAND_STATUS_NULL
};

void state_comm_init(state_comm_t *communication) {
    if (!communication) {
        return;
    }

    communication->ping_id = 0U;
    communication->last_command_id = 0U;
    communication->last_command_status = COMMAND_STATUS_NULL;
    communication->processor_time_ms = 0U;
    communication->uplink_comm = (comm_packet_t){0};
    command_processor_init(&communication->command_processor);
}

comm_result_t state_comm_process_command(state_comm_t *communication,
                                         uint8_t current_state) {
    if (!communication) {
        return (comm_result_t){0};
    }

    return process_command_with_context(&communication->command_processor,
                                       &communication->uplink_comm,
                                       current_state,
                                       &communication->last_command_id,
                                       &communication->last_command_status);
}
