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
 * @file devices/magnetometer.c
 * @authors Advaith Vijayakumar
 * @brief IMMC5983MA magnetometer implementation
 */

#include "magnetometer.h"

#include <stdint.h>

#include "internal/mmio.h"
#include "peripheral/spi.h"
#include "peripheral/errc.h"

// Register addresses (pg. 13)
#define X_OUT_0 0x00
#define X_OUT_1 0x01
#define Y_OUT_0 0x02
#define Y_OUT_1 0x03
#define Z_OUT_0 0x04
#define Z_OUT_1 0x05
#define XYZ_OUT_2 0x06
#define TEMP_OUT 0x07
#define DEVICE_STATUS 0x08
#define CONTROL_REG_0 0x09
#define CONTROL_REG_1 0xA
#define CONTROL_REG_2 0xB
#define CONTROL_REG_3 0xB
#define PRODUCT_ID_1 0xC

// Control bit flags (pg. 14)
#define CTRL0_TM_M 0x1          // Take magnetic field measurement
#define CTRL0_TM_T 0x2          // Take temperature measurement

// Indicates a measurement event of magnetic field is completed
#define STATUS_M_DONE 0x01

#define MAX_SPI_BUF_LEN 10

static inline void validate_dev_values(struct magnetometer_spi_dev *dev, 
        enum ti_errc_t *errc) {
    if (!errc) return;
    *errc = TI_ERRC_NONE;
    if (!dev) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Null device pointer");
        return;
    }

    // Check that the SPI instance is valid
    if (dev->inst < 1 || dev->inst > 6) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "SPI inst error");
        return;
    }
}

// Writes a single byte (val) to an indexed register (reg) via SPI
static void magnetometer_write_reg(struct magnetometer_spi_dev *dev,
        uint8_t reg, uint8_t val, enum ti_errc_t *errc) {
    /* SPI write protocol (pg. 5)
    * Bit 0: RW bit (0 for writing)
    * Bit 1: don't care
    * Bit 2-7: register address
    * Bit 8-15: data to write
    */
    uint8_t tx[2] = {(reg << 2) & 0xFC, val};
    uint8_t rx[2] = {0, 0};
    spi_transfer_sync(dev->inst, dev->ss_pin, tx, rx, 2, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Propagated SPI write error");
    }
}

// Reads bytes_to_read bytes starting from an indexed register via SPI
static void magnetometer_read_regs(struct magnetometer_spi_dev *dev,
        uint8_t reg, uint8_t *rx_buf, uint8_t bytes_to_read,
        enum ti_errc_t *errc) {
    /* SPI write protocol (pg. 5)
     * Bit 0: RW bit (1 for reading)
     * Bit 1: don't care
     * Bit 2-7: register address
     * Bit 8-15: data to write
     */
    uint8_t tx[MAX_SPI_BUF_LEN] = {0};
    tx[0] = ((reg << 2) & 0xFC) | 0x01;
    spi_transfer_sync(dev->inst, dev->ss_pin, tx, rx_buf, bytes_to_read + 1, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Propagated SPI read error");
    }
}

/**************************************************************************************************
 * @section Public Function Implementations
 **************************************************************************************************/

enum ti_errc_t magnetometer_init(struct magnetometer_spi_dev *dev) {
    enum ti_errc_t errc = TI_ERRC_NONE;
    validate_dev_values(dev, &errc);
    return errc;
}

enum ti_errc_t magnetometer_read(struct magnetometer_spi_dev *dev, 
        magnetometer_result_t *result) {
    // Validate dev 
    enum ti_errc_t errc = TI_ERRC_NONE;
    if (!result) return TI_ERRC_INVALID_ARG;
    validate_dev_values(dev, &errc);
    if (errc != TI_ERRC_NONE) return errc;

    // Initiate magnetic field measurement by writing 1 to TM_M bit
    // of Control Register 0 (pg. 14)
    magnetometer_write_reg(dev, CONTROL_REG_0, CTRL0_TM_M, &errc);
    if (errc != TI_ERRC_NONE) return errc;

    // Poll status register until Meas_M_Done bit is set to 1
    uint8_t status_buf[2] = {0};

    for (int i = 0; i < 1000; i++) {  // guard against infinite loop
        magnetometer_read_regs(dev, DEVICE_STATUS, status_buf, 1, &errc);
        if (errc != TI_ERRC_NONE) return errc;

        if (status_buf[1] & STATUS_M_DONE) {
            break;
        }
        systic_delay(10);
    }

    if (!(status_buf[1] & STATUS_M_DONE)) {
        return TI_ERRC_TIMEOUT;
    }

    // Burst read X, Y, Z data registers and temperature
    // Registers are contiguous 8 bytes beginning at XOut
    uint8_t data[MAX_SPI_BUF_LEN] = {0};
    magnetometer_read_regs(dev, X_OUT_0, data, 8, &errc);
    if (errc != TI_ERRC_NONE) return errc;

    /* Parse the read data into based on the register map (pg. 13)
     * data[0] is dummy
     * data[1..2] = X_OUT_0, X_OUT_1
     * data[3..4] = Y_OUT_0, Y_OUT_1
     * data[5..6] = Z_OUT_0, Z_OUT_1
     * data[7] = XYZ_OUT_2
     * data[8] = TEMP_OUT
     */
    uint8_t x0 = data[X_OUT_0 + 1];         // Xout[17:10]
    uint8_t x1 = data[X_OUT_1 + 1];         // Xout[9:2]
    uint8_t y0 = data[Y_OUT_0 + 1];         // Yout[17:10]
    uint8_t y1 = data[Y_OUT_1 + 1];         // Yout[9:2]
    uint8_t z0 = data[Z_OUT_0 + 1];         // Zout[17:10]
    uint8_t z1 = data[Z_OUT_1 + 1];         // Zout[9:2]
    uint8_t xyz2 = data[XYZ_OUT_2 + 1];     // Xout[1:0], Yout[1:0], Zout[1:0]
    uint8_t temp = data[TEMP_OUT + 1];      // Temperature output

    // Construct 18-bit output format as specified (pg. 13)
    result->mag_x = (int32_t)(((uint32_t)x0 << 10) | ((uint32_t)x1 << 2)
        | ((xyz2 >> 6) & 0x03));
    result->mag_y = (int32_t)(((uint32_t)y0 << 10) | ((uint32_t)y1 << 2)
        | ((xyz2 >> 4) & 0x03));
    result->mag_z = (int32_t)(((uint32_t)z0 << 10) | ((uint32_t)z1 << 2)
        | ((xyz2 >> 2) & 0x03));

    // Temperature conversion: 0.8°C per count, 0x00 corresponds to -75°C (pg. 14)
    result->temperature = -75.0f + ((float)temp * 0.8f);

    return TI_ERRC_NONE;
}
