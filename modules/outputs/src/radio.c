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
 * @file modules/outputs/include/output/radio.c
 * @authors Charles Faisandier
 * @brief Radio Implementation.
 */
#include "outputs/radio.h"
#include "util/errc.h"
#include "mcu/spi.h"
#include "mcu/gpio.h"

/**************************************************************************************************
 * @section Private Functions
 **************************************************************************************************/
struct ti_radio_config config = {0};

/**************************************************************************************************
 * @section Private Functions
 **************************************************************************************************/
int radio_send_command(void *command, size_t size) {
   // STEP 1: Check clear-to-send byte.
   uint8_t read_cmd_buff = 0x44;
   spi_write_blocking(device);
}

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
int ti_radio_init(struct ti_radio_config *config) {
   // configure sdn pin
   ti_gpio_clock_enable(config->sdn_pin);
   ti_gpio_set_drain(config->sdn_pin, 0);

   // Reset radio peripheral
   ti_set_pin(config->sdn_pin, 1);
   ti_set_pin(config->sdn_pin, 0);

   // Initialize spi device
   ti_spi_device_init(config->spi_dev);

   // 

   return 0;
}