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
 * @file src/app/system_manager.c
 * @authors Charles Faisandier
 * @brief System manager for the Titan Flight Computer application.
 */

/**************************************************************************************************
 * @section Preprocessor Directives
 **************************************************************************************************/

#include "system_manager.h"
#include "tal/error.h" // For error_t and error handling
#include "sensors/temp_sensor.h" // For sensor initialization and management
#include "app/data_collector.h"
#include "app/data_telemetry.h" // For telemetry data handling
#include "app/data_logger.h" // For logging data
#include "platform/dma.h"

#define NUM_SENSORS 1

// Fetch peripheral configurations.
extern spi_config_t spi1_config;
extern spi_dma_config_t spi1_dma_tx_config;
extern spi_dma_config_t spi1_dma_rx_config;
extern temp_sensor_config_t temp_sensor_config;

/**************************************************************************************************
 * @section Static Variables
 **************************************************************************************************/

static tal_flag_t g_system_errors = {0};
static g_sensors_ready_count = 0;
static sensor_data_ready_t sensor_data_ready = {0};

static struct {
    bool temp_sensor;
    // Add more sensors here as needed
} sensor_available;


/*******************************************************************
 * @section Application Callbacks
 ******************************************************************/
static void data_collector_callback(tal_err_t *err, size_t buffsize) {
    if (tal_is_err(err)) {
        error_handler_log_critical(err);
    } else {
        data_logger_start(buffsize);
        data_telemetry_start(buffsize);
    }
}

static void data_telemetry_callback(tal_err_t *err) {
    if (tal_is_err(err)) {
        error_handler_log_critical(err);
    }
}

static void data_logger_callback(tal_err_t *err) {
    if (tal_is_err(err)) {
        error_handler_log_critical(err);
    }
}

/*******************************************************************
 * @section Communication Protocol Callbacks
 ******************************************************************/

static void spi1_callback(bool success, void *context) {
    spi_device_t *spi_device = context;
    // Check which device it was
    if (spi_device->gpio_pin == temp_sensor_config.ss_gpio) // Repeat for all sensors
        sensor_data_ready.temp_sensor = success;
    
    // Update device ready
    // Check if we are ready to collect the data
    g_sensors_ready_count++;
    if (g_sensors_ready_count == NUM_SENSORS) {
        // All sensors have attempted data retrieval, we can start the data collection loop
        data_collector_start(&sensor_data_ready);
    }

    transfer_complete = true;
}

/**************************************************************************************************
 * @section Public Function Implementations
 **************************************************************************************************/

tal_err_t *system_manager_init(void) {
    // SPI initialization
    spi_init(&g_system_errors, &spi1_config, spi1_callback, &spi1_dma_tx_config, &spi1_dma_rx_config);

    // Data collector initialization
    tal_err_t *collector_err = data_collector_init(data_collector_callback);
    if (tal_is_err(collector_err)) {
        error_handler_log_critical(collector_err);
        return -1; // What's the point anymore...
    }

    // Data telemetry initialization
    tal_err_t *telemetry_err = data_telemetry_init(data_telemetry_callback);
    if (tal_is_err(telemetry_err)) {
        error_handler_log_critical(telemetry_err);
    }

    // Data logger initialization
    tal_err_t *logger_err = data_logger_init(data_logger_callback);
    if (tal_is_err(logger_err)) {
        error_handler_log_critical(logger_err);
    }

    // Sensor initialization
    sensor_available.temp_sensor = temp_sensor_init(&g_system_errors);

    error_handler_log_non_critical(&g_system_errors);
    g_system_errors = (tal_flag_t){0}; // Reset the error flag after logging
    return NULL;
}

void system_manager_run(void) {
    while (true) {
        if (sensor_available.temp_sensor) {
           temp_sensor_read_temperature(&g_system_errors); 
        }
    }
}