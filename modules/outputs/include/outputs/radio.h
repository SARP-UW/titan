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

enum ti_radio_mod_type {
    MOD_TYPE_CW = 0,
    MOD_TYPE_OOK = 1,
    MOD_TYPE_2FSK = 2,
    MOD_TYPE_2GFSK = 3,
    MOD_TYPE_4FSK = 4,
    MOD_TYPE_4GFSK = 5,
};

// TODO: Potentially add CRC
struct ti_radio_config_t {
   spi_device_t spi_dev;
   uint32_t timeout; // Number of times to poll CTS before timeout
   uint8_t global_xo_tune; // Internal capacitor tuning
   uint8_t gauss_oversample; // 0-3
   uint32_t data_rate; // Bps?
   uint8_t mod_type; // Modulation type
   uint16_t f1_length; // Field 1 length: 0-1fff
   uint16_t f2_length; // Field 2 length: 0-1fff
   uint16_t f3_length; // Field 3 length: 0-1fff
   uint16_t f4_length; // Field 4 length: 0-1fff
   uint16_t f5_length; // Field 5 length: 0-1fff
   uint8_t tx_threshold; // Num bytes in TX_FIFO to trigger re-fill
   uint8_t sdn_pin;
   uint8_t nirq_pin;
   bool combined_fifo;
   uint32_t interupt_priority;
   uint32_t tx_write_timeout;
};

/**
 * @brief Initializes the radio with the given configuration.
 * @param config Configuration struct
 * @returns Initialization error code
 */
int ti_radio_init(struct ti_radio_config_t *config);

/**
 * @brief Transmits data over the radio on the specified channel.
 * @param data Pointer to data to transmit
 * @param size Size of data in bytes (0x0-0x1FFF)
 * @param channel Channel to transmit on
 * @returns Transmission error code
 */
int ti_radio_transmit(void *data, size_t size, uint8_t channel);