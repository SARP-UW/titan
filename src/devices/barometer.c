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
 * @file devices/barometer.c
 * @authors Jude Merritt
 * @brief MS561101BA03 Barometer driver
 */

#include "barometer.h"
#include <stdbool.h>
#include <stdint.h>
#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include "peripheral/systick.h"

#define D1_BASE_CMD 0x40
#define D2_BASE_CMD 0x50
#define ADC_READ    0x00
#define RESET       0x1E

// Calibration coefficients
typedef enum {
    PROM_ADDR_MANUFACTURER = 0xA0,
    PROM_ADDR_C1           = 0xA2,
    PROM_ADDR_C2           = 0xA4,
    PROM_ADDR_C3           = 0xA6,
    PROM_ADDR_C4           = 0xA8,
    PROM_ADDR_C5           = 0xAA,
    PROM_ADDR_C6           = 0xAC,
    PROM_ADDR_CRC          = 0xAE
}prom_addr_t;

static inline void validate_dev_values(barometer_t *dev, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    //Check that SPI instance is valid
    if ((dev->spi_dev.inst < 1) || (dev->spi_dev.inst > 6)) { //
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "SPI inst error"); return; //
    }

    //Check that OSR value is valid
    if ((dev->osr < 0x00) || (dev->osr > 0x08)) { //
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "OSR error"); return; //
    }
}

// Provides the necessary conversion time delay based on the specified oversampling ratio (OSR) using the SysTick timer.
static void barometer_delay(uint8_t osr) {
    uint8_t conversion_time;

   /*
    * The conversion times are based on the following table:
    * OSR   Min.   Max.
    * 4096  7.40   9.04
    * 2048  3.72   4.54
    * 1024  1.88   2.28
    * 512   0.95   1.17
    * 256   0.48   0.60
    */
    switch (osr) {
        case OSR_256:  conversion_time = 1;  break;
        case OSR_512:  conversion_time = 2;  break;
        case OSR_1024: conversion_time = 3;  break;
        case OSR_2048: conversion_time = 5;  break;
        case OSR_4096: conversion_time = 10; break;
        default: return;
    }

    systick_delay(conversion_time);
}

// Sends a command to the sensor and reads the multi-byte response.
static uint32_t barometer_transfer(barometer_t *dev, uint8_t cmd, uint8_t bytes_to_read, enum ti_errc_t *errc) {
    uint8_t tx[4] = {cmd, 0, 0, 0};
    uint8_t rx[4] = {0, 0, 0, 0};
    uint32_t result = 0;

    spi_transfer_sync(dev->spi_dev.inst, dev->spi_dev.ss_pin, tx, rx, bytes_to_read + 1, errc); //
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return 0; } //

    if (bytes_to_read == 2) {
        result = (uint32_t)((rx[1] << 8) | rx[2]);
    } else if (bytes_to_read == 3) {
        result = (uint32_t)((rx[1] << 16) | (rx[2] << 8) | rx[3]);
    }

    return result;
}

/**************************************************************************************************
 * @section Public Function Implementations
 **************************************************************************************************/

void barometer_init(barometer_t *dev, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    // Check OSR and device fields
    validate_dev_values(dev, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; } //

    // Reset the sensor
    barometer_transfer(dev, RESET, 0, errc); //
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; } //

    // Wait for internal reload
    barometer_delay(dev->osr);

    // Read PROM values
    dev->calibration_data.sens     = (uint16_t)barometer_transfer(dev, PROM_ADDR_C1, 2, errc); //
    dev->calibration_data.off      = (uint16_t)barometer_transfer(dev, PROM_ADDR_C2, 2, errc); //
    dev->calibration_data.tcs      = (uint16_t)barometer_transfer(dev, PROM_ADDR_C3, 2, errc); //
    dev->calibration_data.tco      = (uint16_t)barometer_transfer(dev, PROM_ADDR_C4, 2, errc); //
    dev->calibration_data.t_ref    = (uint16_t)barometer_transfer(dev, PROM_ADDR_C5, 2, errc); //
    dev->calibration_data.tempsens = (uint16_t)barometer_transfer(dev, PROM_ADDR_C6, 2, errc); //
}

barometer_result_t get_barometer_data(barometer_t *dev, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    // Get raw D1 pressure data
    barometer_transfer(dev, D1_BASE_CMD + dev->osr, 0, errc);
    barometer_delay(dev->osr); //
    uint32_t d1 = barometer_transfer(dev, ADC_READ, 3, errc); //
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return dev->result; } //

    // Get raw D2 temperature data
    barometer_transfer(dev, D2_BASE_CMD + dev->osr, 0, errc);
    barometer_delay(dev->osr); //
    uint32_t d2 = barometer_transfer(dev, ADC_READ, 3, errc); //
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return dev->result; } //

    if ((d1 || d2) <= 0) {
        TI_SET_ERRC(errc, TI_ERRC_DEVICE, "Zero ADC data"); return dev->result; //
    }

    // Calculate temperature difference
    int32_t delta_t = d2 - ((int32_t)dev->calibration_data.t_ref << 8);

    // Calculate actual temperature
    int32_t temp = 2000 + (((int64_t)delta_t * dev->calibration_data.tempsens) >> 23);

    // Calculate initial offset and sensitivity
    int64_t off  = ((int64_t)dev->calibration_data.off << 16) + (((int64_t)dev->calibration_data.tco * delta_t) >> 7);
    int64_t sens = ((int64_t)dev->calibration_data.sens << 15) + (((int64_t)dev->calibration_data.tcs * delta_t) >> 8);

    // Second order temperature compensation
    int64_t temp_2 = 0;
    int64_t off_2  = 0;
    int64_t sens_2 = 0;

    // If temperature is below 20°C
    if (temp < 2000) {
        temp_2 = ((int64_t)delta_t * delta_t) >> 31;
        off_2  = 5 * ((int64_t)(temp - 2000) * (temp - 2000)) >> 1;
        sens_2 = 5 * ((int64_t)(temp - 2000) * (temp - 2000)) >> 2;

        // If temperature if below -15°C
        if (temp < -1500) {
            off_2  = off_2 + (7 * ((int64_t)(temp + 1500) * (temp + 1500)));
            sens_2 = sens_2 + (11 * ((int64_t)(temp + 1500) * (temp + 1500)) >> 1);
        }
    }

    temp -= temp_2;
    off  -= off_2;
    sens -= sens_2;

    // Calculate temperature compensated pressure
    int32_t pressure = (((d1 * sens) >> 21) - off) >> 15;

    // Results
    dev->result.pressure    = (float)pressure / 100.0F;    // Units of mbar/hPa
    dev->result.temperature = (float)temp / 100.0F; // Units of Celcius

    if ((dev->result.pressure <= 0 || dev->result.temperature) <= 0) {
        TI_SET_ERRC(errc, TI_ERRC_DEVICE, "Invalid computation"); return dev->result; 
    }

    return dev->result;
}