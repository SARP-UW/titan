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
 * @file app/utils/sensor_status.h
 * @authors Mahir Emran
 * @brief Utility data to detect if sensor is done
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "peripheral/errc.h"
#include "devices/imu.h"
#include "devices/gnss.h"
#include "devices/barometer.h"
#include "devices/adc.h"
#include "devices/magnetometer.h"
#include "devices/temperature.h"

/**************************************************************************************************
 * @section Non-blocking sensor operation structures
 **************************************************************************************************/

// Structure to track non-blocking sensor operations
typedef struct {
    bool gnss_done;
    bool imu1_done;
    bool imu2_done;
    bool baro1_done;
    bool baro2_done;
    bool temp1_done;
    bool temp2_done;
    bool mag1_done;
    bool mag2_done;
    bool adc_done;

    // Error tracking for each sensor
    bool gnss_error;
    bool imu1_error;
    bool imu2_error;
    bool baro1_error;
    bool baro2_error;
    bool temp1_error;
    bool temp2_error;
    bool mag1_error;
    bool mag2_error;
    bool adc_error;
} sensor_status_t;

/**************************************************************************************************
 * @section Non-blocking sensor function declarations
 **************************************************************************************************/

// Initialize all sensor status flags to false
void sensor_status_init(sensor_status_t *status);

// Check if all sensors are done
bool sensor_status_all_done(const sensor_status_t *status);

// Check if any sensor operation failed
bool sensor_status_has_error(const sensor_status_t *status);

// Non-blocking GNSS read
void gnss_start_read(gnss_t *dev, gnss_pvt_t *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc);

// Non-blocking IMU reads
void imu_start_read(struct imu_spi_dev *dev, struct imu_result *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc);

// Non-blocking barometer reads
void barometer_start_read(barometer_t *dev, barometer_result_t *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc);

// Non-blocking temperature reads
void temperature_start_read(temperature_t *dev, temperature_result_t *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc);

// Non-blocking magnetometer reads
void magnetometer_start_read(struct magnetometer_spi_dev *dev, struct magnetometer_result_t *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc);

// Non-blocking ADC read for multiple channels
void adc_start_read(struct adc_spi_dev *dev, const struct adc_channel *channels, uint8_t channel_count, bool *done_flag, bool *error_flag, enum ti_errc_t *errc);