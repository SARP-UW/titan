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
 * @file app/utils/sensor_nb.h
 * @authors Mahir Emran
 * @brief Utility functions to do sensor blocking
 */

#include "sensor_status.h"
#include "devices/imu.h"
#include "devices/gnss.h"
#include "devices/barometer.h"
#include "devices/adc.h"
#include "devices/magnetometer.h"
#include "devices/temperature.h"
#include "peripheral/errc.h"

/**************************************************************************************************
 * @section GNSS Non-blocking Implementation
 **************************************************************************************************/

void gnss_start_read(gnss_t *dev, gnss_pvt_t *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc) {
    if (!dev || !result || !done_flag || !error_flag) {
        if (errc) *errc = TI_ERRC_INVALID_ARG;
        *done_flag = true;
        *error_flag = true;
        return;
    }

    *done_flag = false;
    *error_flag = false;
    if (errc) *errc = TI_ERRC_NONE;

    // For now, use blocking call but set flags appropriately
    gnss_get_pvt(dev, result, errc);
    *done_flag = true;
    *error_flag = (errc && *errc != TI_ERRC_NONE);
}

/**************************************************************************************************
 * @section IMU Non-blocking Implementation
 **************************************************************************************************/

void imu_start_read(struct imu_spi_dev *dev, struct imu_result *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc) {
    if (!dev || !result || !done_flag || !error_flag) {
        if (errc) *errc = TI_ERRC_INVALID_ARG;
        *done_flag = true;
        *error_flag = true;
        return;
    }

    *done_flag = false;
    *error_flag = false;
    if (errc) *errc = TI_ERRC_NONE;

    // For now, use blocking call but set flags appropriately
    enum ti_errc_t result_errc = imu_transfer(dev, result);
    if (errc) *errc = result_errc;
    *done_flag = true;
    *error_flag = (result_errc != TI_ERRC_NONE);
}

/**************************************************************************************************
 * @section Barometer Non-blocking Implementation
 **************************************************************************************************/

void barometer_start_read(barometer_t *dev, barometer_result_t *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc) {
    if (!dev || !result || !done_flag || !error_flag) {
        if (errc) *errc = TI_ERRC_INVALID_ARG;
        *done_flag = true;
        *error_flag = true;
        return;
    }

    *done_flag = false;
    *error_flag = false;
    if (errc) *errc = TI_ERRC_NONE;

    // For now, use blocking call but set flags appropriately
    *result = get_barometer_data(dev, errc);
    *done_flag = true;
    *error_flag = (errc && *errc != TI_ERRC_NONE);
}

/**************************************************************************************************
 * @section Temperature Non-blocking Implementation
 **************************************************************************************************/

void temperature_start_read(temperature_t *dev, temperature_result_t *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc) {
    if (!dev || !result || !done_flag || !error_flag) {
        if (errc) *errc = TI_ERRC_INVALID_ARG;
        *done_flag = true;
        *error_flag = true;
        return;
    }

    *done_flag = false;
    *error_flag = false;
    if (errc) *errc = TI_ERRC_NONE;

    // For now, use blocking call but set flags appropriately
    temperature_read_temp(dev, result, errc);
    *done_flag = true;
    *error_flag = (errc && *errc != TI_ERRC_NONE);
}

/**************************************************************************************************
 * @section Magnetometer Non-blocking Implementation
 **************************************************************************************************/

void magnetometer_start_read(struct magnetometer_spi_dev *dev, struct magnetometer_result_t *result, bool *done_flag, bool *error_flag, enum ti_errc_t *errc) {
    if (!dev || !result || !done_flag || !error_flag) {
        if (errc) *errc = TI_ERRC_INVALID_ARG;
        *done_flag = true;
        *error_flag = true;
        return;
    }

    *done_flag = false;
    *error_flag = false;
    if (errc) *errc = TI_ERRC_NONE;

    // For now, use blocking call but set flags appropriately
    enum ti_errc_t result_errc = magnetometer_read(dev, result);
    if (errc) *errc = result_errc;
    *done_flag = true;
    *error_flag = (result_errc != TI_ERRC_NONE);
}

/**************************************************************************************************
 * @section ADC Non-blocking Implementation
 **************************************************************************************************/

void adc_start_read(struct adc_spi_dev *dev, const struct adc_channel *channels, uint8_t channel_count, bool *done_flag, bool *error_flag, enum ti_errc_t *errc) {
    if (!dev || !channels || !done_flag || !error_flag) {
        if (errc) *errc = TI_ERRC_INVALID_ARG;
        *done_flag = true;
        *error_flag = true;
        return;
    }

    *done_flag = false;
    *error_flag = false;
    if (errc) *errc = TI_ERRC_NONE;

    // For now, use blocking calls but set flags appropriately
    for (uint8_t i = 0; i < channel_count; i++) {
        int voltage = adc_read_voltage(&channels[i], errc);
        if (errc && *errc != TI_ERRC_NONE) {
            *done_flag = true;
            *error_flag = true;
            return;
        }
        // Note: Results would need to be stored somewhere for packet building
        // This is handled by the packet building functions that read directly
    }
    *done_flag = true;
    *error_flag = false;
}