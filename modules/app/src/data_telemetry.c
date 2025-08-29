/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2024 UW SARP
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
 * @file modules/app/src/data_telemetry.c
 * @authors Charles Faisandier
 * @brief Data telemetry module implementation.
 */
#include "app/data_telemetry.h"
#include "kernel/thread.h"
#include "kernel/semaphore.h"

/**************************************************************************************************
 * @section Private Data Structures
 **************************************************************************************************/
struct data_telemetry_config_t *dt_config = {0};
struct ti_thread_t thread = {0};

/**************************************************************************************************
 * @section Private Functions
 **************************************************************************************************/
void send_sensor_data() {
    
}

void data_telemetry_thread(void) {
    while (1) {
        ti_aquire_semaphore(*dt_config->semaphore, dt_config->semaphore_timeout);
        send_sensor_data();
    }
}

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
// Assumes the radio is already initialized.
int data_telemetry_start(struct data_telemetry_config_t *config) {
    // TODO: Parameter checking
    
    // Initialization
    int errc = ti_radio_init(config->radio_config);
    if (errc != TI_ERRC_NONE) {
        return errc;
    }
}

void data_telemetry_stop() {
    ti_destroy_semaphore(*dt_config->semaphore);
    ti_destroy_thread(thread);
}