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
 * @file devices/imu.c
 * @authors Ayla Crowell
 * @brief ICM-45686 IMU driver
 */


#include <stdint.h>
#include "devices/imu.h"
#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include "peripheral/systick.h"

// Registers
#define ACCEL_DATA_X1_UI 0x00
#define PWR_MGMT0 0x10
#define INT1_STATUS0 0x19
#define ACCEL_CONFIG0 0x1B
#define GYRO_CONFIG0 0x1C
#define REG_MISC2 0x7F

// Bits
#define READ_BIT 0x80
#define WRITE_BIT 0x7F

#define SOFT_RST_BIT 0x02
#define RST_DONE_BIT 0x80

#define ACCEL_CONFIG_MASK 0x7F
#define ACCEL_CONFIG_VAL 0x03
#define GYRO_CONFIG_VAL 0x13
#define LN_VAL 0x0F

static inline void validate_dev_values(struct imu_spi_dev* dev, enum ti_errc_t* errc) {
    if (errc) *errc = TI_ERRC_NONE;
    // Check that SPI instance is valid
    if (dev == NULL || dev->inst < 1 || dev->inst > 6) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "SPI inst error");
        return;
    }
}

// Read a register
static uint8_t imu_rreg(struct imu_spi_dev* dev, uint8_t reg, enum ti_errc_t* errc) {
    uint8_t tx[2] = {reg | READ_BIT, 0}; // 10.5. | 0x80 sets MSB to 1 for read
    uint8_t rx[2] = {0, 0};

    spi_transfer_sync(dev->inst, dev->ss_pin, tx, rx, 2, errc);

    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to read imu registers");
        return 0;
    }

    return rx[1];
}

// Write to a register
static void imu_wreg(struct imu_spi_dev* dev, uint8_t reg, uint8_t val, enum ti_errc_t* errc) {
    uint8_t tx[2] = {reg & WRITE_BIT, val}; // 10.5. & 0x7F sets MSB to 0 for write

    spi_transfer_sync(dev->inst, dev->ss_pin, tx, NULL, 2, errc);

    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to write imu register");
        return;
    }
}

// Read accelerometer, gyroscope, and temperature data
static void imu_rregs(struct imu_spi_dev* dev, struct imu_result* result, enum ti_errc_t* errc) {
    uint8_t tx[15] = {ACCEL_DATA_X1_UI | READ_BIT, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 16.1 Read 14 bytes starting from ACCEL_DATA_X1_UI
    uint8_t rx[15] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    spi_transfer_sync(dev->inst, dev->ss_pin, tx, rx, 15, errc);

    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to read imu registers");
        return;
    }

    result->accel_x = (int16_t)((rx[1] << 8) | rx[2]);
    result->accel_y = (int16_t)((rx[3] << 8) | rx[4]);
    result->accel_z = (int16_t)((rx[5] << 8) | rx[6]);
    result->gyro_x  = (int16_t)((rx[7] << 8) | rx[8]);
    result->gyro_y  = (int16_t)((rx[9] << 8) | rx[10]);
    result->gyro_z  = (int16_t)((rx[11] << 8) | rx[12]);
    result->temp    = (int16_t)((rx[13] << 8) | rx[14]);
    return;
}

// static void convert_raw_to_physical(struct imu_result* result, struct imu_spi_dev* dev) {
//     // raw * full scale / 2^15 (num of bits in 16-bit signed int)
//     switch (dev->accel_fs) {
//         case ACCEL_FS_32G:
//             result->accel_x = result->accel_x / 1024;
//             result->accel_y = result->accel_y / 1024;
//             result->accel_z = result->accel_z / 1024;
//             break;
//         // case ACCEL_FS_16G:
//         //     result->accel_x / 2048; result->accel_y / 2048; result->accel_z / 2048; break;
//         // case ACCEL_FS_8G:
//         //     result->accel_x / 4096; result->accel_y / 4096; result->accel_z / 4096; break;
//         // case ACCEL_FS_4G:
//         //     result->accel_x / 8192; result->accel_y / 8192; result->accel_z / 8192; break;
//         // case ACCEL_FS_2G:
//         //     result->accel_x / 16384; result->accel_y / 16384; result->accel_z / 16384; break;
//         default:
//             return; // Invalid FS
//     }

//     switch (dev->gyro_fs) {
//         case GYRO_FS_4000DPS:
//             result->gyro_x = result->gyro_x * 4000 / 32768;
//             result->gyro_y = result->gyro_y * 4000 / 32768;
//             result->gyro_z = result->gyro_z * 4000 / 32768;
//             break;
//         // case GYRO_FS_2000DPS:
//         //     result->gyro_x * 2000 / 32768; result->gyro_y * 2000 / 32768; result->gyro_z * 2000 / 32768;
//         //     break;
//         // case GYRO_FS_1000DPS:
//         //     result->gyro_x * 1000 / 32768; result->gyro_y * 1000 / 32768; result->gyro_z * 1000 / 32768;
//         //     break;
//         // case GYRO_FS_500DPS:
//         //     result->gyro_x * 500 / 32768; result->gyro_y * 500 / 32768; result->gyro_z * 500 / 32768;
//         //     break;
//         // case GYRO_FS_250DPS:
//         //     result->gyro_x * 250 / 32768; result->gyro_y * 250 / 32768; result->gyro_z * 250 / 32768;
//         //     break;
//         // case GYRO_FS_125DPS:
//         //     result->gyro_x * 125 / 32768;    result->gyro_y * 125 / 32768; result->gyro_z * 125 / 32768;
//         //     break;
//         // case GYRO_FS_62_5DPS:
//         //     result->gyro_x * 62.5 / 32768; result->gyro_y * 62.5 / 32768; result->gyro_z * 62.5 / 32768;
//         //     break;
//         // case GYRO_FS_31_25DPS:
//         //     result->gyro_x * 31.25 / 32768; result->gyro_y * 31.25 / 32768; result->gyro_z * 31.25 / 32768;
//         //     break;
//         // case GYRO_FS_15_625DPS:
//         //     result->gyro_x * 15.625 / 32768; result->gyro_y * 15.625 / 32768; result->gyro_z * 15.625 / 32768;
//         //     break;
//         default:
//             return; // Invalid FS
//     }

//     // TODO: temperature conversion

//     return;
// }

// static uint8_t imu_self_test(struct imu_spi_dev* dev, enum ti_errc_t* errc) {
//     // To be implemented

//     // 17.84. Soft reset
//     uint8_t reg_misc2 = imu_rreg(dev, REG_MISC2, errc);
//     imu_wreg(dev, REG_MISC2, reg_misc2 | SOFT_RST_BIT, errc); // Set bit 0 to 1 for soft reset

//     // 17.24. Check reset complete
//     while(imu_rreg(dev, INT1_STATUS0, errc) << 7 == 0) {
//         systick_delay(1); // Wait for reset to complete
//     }


//     // 18.6. Check the self-test results
//     return 0;
// }

/**************************************************************************************************
 * @section Public Function Implementations
 **************************************************************************************************/

enum ti_errc_t imu_init(struct imu_spi_dev* dev, enum ti_errc_t* errc) {
    validate_dev_values(dev, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Write error"); return *errc; }

    systick_delay(1); // 3.3.2. Wait for the IMU to power up 1ms

    // 17.84. Soft reset
    uint8_t reg_misc2 = imu_rreg(dev, REG_MISC2, errc);
    imu_wreg(dev, REG_MISC2, reg_misc2 | SOFT_RST_BIT, errc); // Set rst bit to 1 for soft reset
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Write error"); return *errc; }


    // 17.24. Check reset complete
    uint16_t counter = 0;
    while((imu_rreg(dev, INT1_STATUS0, errc) & RST_DONE_BIT) == 0 && counter < 10000) {
        systick_delay(1); // Wait for reset to complete
        counter++;
    }
    if (counter >= 10000) {
        TI_SET_ERRC(errc, TI_ERRC_TIMEOUT, "Reset timeout");
        return *errc;
    }

    // 17.17. Set gyro and accel to Low Noise mode
    uint8_t pwr_mgmt0_val = imu_rreg(dev, PWR_MGMT0, errc);
    imu_wreg(dev, PWR_MGMT0, pwr_mgmt0_val | LN_VAL, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Failed to configure LN"); return *errc; }

    // 17.26. Accel config to +=32g scale and 6.4kHz ODR
    uint8_t accel_config0_val = imu_rreg(dev, ACCEL_CONFIG0, errc);
    imu_wreg(dev, ACCEL_CONFIG0, ((accel_config0_val & ~ACCEL_CONFIG_MASK) | ACCEL_CONFIG_VAL), errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Failed to config accel"); return *errc; }

    // 17.27. Gyro config to 2000dps scale and 6.4kHz ODR
    imu_wreg(dev, GYRO_CONFIG0, GYRO_CONFIG_VAL, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Failed to config gyro"); return *errc; }
    return *errc;
}

enum ti_errc_t imu_transfer(struct imu_spi_dev* dev, struct imu_result* result, enum ti_errc_t* errc) {
    imu_rregs(dev, result, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Failed to read imu"); return *errc; }
    // convert_raw_to_physical(result, dev);
    return *errc;
}



/**
 * TODO
 * 1. fix fs mask
 * 2. check imu transfer
 * 3. implement self test
 */