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
 * @file devices/magnetometer.h
 * @authors Jude Merritt
 * @brief IMMC5983MA magnetometer implementation
 */


#include "internal/mmio.h"
#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include <stdint.h>

#pragma once

/**
 * @brief Global SPI configuration for magnetometer (shared instance)
 */
extern struct magnetometer_spi_dev {
    uint8_t inst;      /**< SPI hardware instance (0-based) */
    uint8_t ss_pin;    /**< Slave select pin */
} magnetometer_spi_global;

/**
 * @brief Magnetometer reading result
 */
struct magnetometer_result_t {
    int32_t mag_x;        /**< X-axis magnetic field */
    int32_t mag_y;        /**< Y-axis magnetic field */
    int32_t mag_z;        /**< Z-axis magnetic field */
    float temperature;    /**< Internal temperature */
};

/**
 * @brief Initializes the IMMC5983MA Magnetometer. 
 * 
 * @param dev  pointer to the magnetometer_spi_dev structure. 
 */
enum ti_errc_t magnetometer_init(struct magnetometer_spi_dev* dev);

/**
 * @brief Performs a burst read of the sensor registers and returns them 
 *        by updating the result structure. Ensure that the desired SPI
 *        instance has been initialized before calling this function. 
 * 
 * @param dev  pointer to the magnetometer_spi_dev structure. 
 * @param result  pointer to the result structure. 
 * @return ti_errc_t error code.
 */
enum ti_errc_t magnetometer_read(struct magnetometer_spi_dev* dev, struct magnetometer_result_t* result);