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
 * @file src/app/main.c
 * @authors Charles Faisandier
 * @brief Main entry point for the Titan Flight Computer application.
 */

#include "tal/error.h"         
#include "boot/system_init.h"  
#include "app/system_manager.h"
#include "app/error_handler.h"  
#include "app/data_collector.h"
#include "app/data_telemetry.h"
#include "app/launch_sequence.h"
#include "platform/dma.h"

/**
 * @brief Main entry point of the Titan Flight Computer application.
 * This function is called after the C runtime environment is set up by startup.c.
 */
int main(void) {
    // System initialization
    tal_err_t *init_err = system_init(); 
    if (tal_is_err(init_err)) {
        return -1; // Initialization failed, we cannot proceed
    }
    tal_err_t *err = dma_init();
    if (tal_is_err(err)) {
        return -1; // DMA initialization failed, we cannot proceed
    }
    error_handler_init(); // If this fails, we're in the dark.
    error_handler_log_successful("System initialization successful");

    // Launch sequence
    launch_sequence_init();
    launch_sequence_start();

    // Data collection
    tal_err_t *manager_err = system_manager_init(); 
    if (tal_is_err(manager_err)) {
        error_handler_log_critical(manager_err);
    }

    system_manager_run(); 

    return 0;
}