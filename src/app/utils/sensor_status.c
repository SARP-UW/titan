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
 * @file app/utils/sensor_status.c
 * @authors Mahir Emran
 * @brief Utility data to detect if sensor is done
 */
#include "sensor_status.h"

void sensor_status_init(sensor_status_t *status) {
    if (!status) return;

    status->gnss_done = false;
    status->imu1_done = false;
    status->imu2_done = false;
    status->baro1_done = false;
    status->baro2_done = false;
    status->temp1_done = false;
    status->temp2_done = false;
    status->mag1_done = false;
    status->mag2_done = false;
    status->adc_done = false;

    status->gnss_error = false;
    status->imu1_error = false;
    status->imu2_error = false;
    status->baro1_error = false;
    status->baro2_error = false;
    status->temp1_error = false;
    status->temp2_error = false;
    status->mag1_error = false;
    status->mag2_error = false;
    status->adc_error = false;
}

bool sensor_status_all_done(const sensor_status_t *status) {
    if (!status) return true;

    return status->gnss_done &&
           status->imu1_done &&
           status->imu2_done &&
           status->baro1_done &&
           status->baro2_done &&
           status->temp1_done &&
           status->temp2_done &&
           status->mag1_done &&
           status->mag2_done &&
           status->adc_done;
}

bool sensor_status_has_error(const sensor_status_t *status) {
    if (!status) return false;

    return status->gnss_error ||
           status->imu1_error ||
           status->imu2_error ||
           status->baro1_error ||
           status->baro2_error ||
           status->temp1_error ||
           status->temp2_error ||
           status->mag1_error ||
           status->mag2_error ||
           status->adc_error;
}