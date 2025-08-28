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
 * @file modules/outputs/include/output/radio.h
 * @authors Charles Faisandier
 * @brief Radio Public Interface.
 */
#pragma once
#include <stdint.h>
#include "mcu/spi.h"

struct ti_radio_config {
   spi_device_t spi_dev;
   uint32_t timeout; // Number of times to poll CTS before timeout
   uint8_t global_xo_tune; // Internal capacitor tuning
   uint8_t gauss_oversample; // 0-3
   uint32_t data_rate; // Bps?
   uint8_t mod_type; // Modulation type
   int sdn_pin;
};

/**
 * @brief Initializes the radio with the given configuration.
 * @param config Configuration struct
 * @returns Initialization error code
 */
int ti_radio_init(struct ti_radio_config *config);