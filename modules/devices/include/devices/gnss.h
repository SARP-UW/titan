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
 * @file modules/inputs/include/inputs/gnss.h
 * @authors Charles Faisandier
 * @brief NEO-M9N-00B GNSS Driver Public Interface
 * 
 * This is currently a minimal driver: it does not support using multiple
 * GNSS constelations, the odometer, anti-jamming/spoofing or any other
 * advanced functions. It only uses GPS.
 */
#include "util/errc.h"
#include "periphs/spi.h"
#include "periphs/hrtim.h"

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/
// GNSS Config Struct
typedef struct {
   spi_device_t device;
   uint8_t dsel_pin;
   uint8_t txready_pin_mcu;     // NOTE: If either of these txready pins are set to zero, a software
   uint8_t txready_pin_gnss;    //       interrupt is used instead.
   uint32_t inter_prio;
   uint32_t thread_prio;
   uint8_t pvt_rate; // Rate of signal output in Hz
} gnss_config_t;

// GNSS data struct
typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint32_t tacc; // Time accuracy estimate
    int32_t nano;
    int32_t lon;
    int32_t lat;
    int32_t height; // Ellipsoid
    uint32_t hacc;
    uint32_t vacc;
    int32_t veln;
    int32_t vele;
    int32_t veld;
    int32_t gspeed;
    int32_t headmot;
    uint32_t sacc;
    uint32_t headacc;
} gnss_data_t;

/**************************************************************************************************
 * @section Functions
 **************************************************************************************************/
/**
 * @brief Initializes the gnss
 * @param flag: Error flag
 * @param device: Spi device struct
 * @returns Whether the initialization was successful
 */
int gnss_init(gnss_config_t *gnss_config, struct hrtim_config_t *hrtim_config);

/**
 * @brief Stops the gnss system.
 * @returns Deinit error code
 */
int gnss_deinit();