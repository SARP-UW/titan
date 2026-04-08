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
 * @file devices/imu.h
 * @authors Jude Merritt
 * @brief ICM-42688-P IMU driver implementation
 */


#include "internal/mmio.h"
#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include <stdint.h>

#pragma once

struct result { 
    int16_t accel_x; 
    int16_t accel_y;
    int16_t accel_z;
    int16_t gyro_x;
    int16_t gyro_y;
    int16_t gyro_z;
    int16_t temp; // Internal temperature
};
/**
 * @brief IMU SPI device struct
 */
struct imu_spi_dev {
    uint8_t inst;      /**< SPI hardware instance */
    uint8_t ss_pin;    /**< Slave select pin */
};

/**
 * @brief IMU sensor result struct
 */
struct imu_result {
    int16_t accel_x;   /**< X-axis acceleration */
    int16_t accel_y;   /**< Y-axis acceleration */
    int16_t accel_z;   /**< Z-axis acceleration */
    int16_t gyro_x;    /**< X-axis gyroscope */
    int16_t gyro_y;    /**< Y-axis gyroscope */
    int16_t gyro_z;    /**< Z-axis gyroscope */
    int16_t temp;      /**< Internal temperature */
};

/**
 * @brief Initializes the ICM-42688-P IMU. 
 * 
 * @param dev  pointer to the imu_spi_dev structure. 
 */
enum ti_errc_t imu_init(struct imu_spi_dev* dev);

/**
 * @brief Performs a burst read of the sensor registers and returns them 
 *        by updating the result structure. Ensure that the desired SPI
 *        instance has been initialized before calling this function. 
 * 
 * @param dev  pointer to the imu_spi_dev structure. 
 * @param result  pointer to the imu_result structure. 
 * @return ti_errc_t error code.
 */
enum ti_errc_t imu_transfer(struct imu_spi_dev* dev, struct imu_result* result);