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
// Does not take care of blocking or unblocking the spi device
int radio_get_CTS() {
    uint8_t read_cmd_buff = 0x44;
    uint8_t read_resp_buff = 0;
    struct spi_sync_transfer_t transfer = {
        .device = config.spi_dev,
        .source = &read_cmd_buff,
        .dest = &read_resp_buff,
        .size = 1,
        .timeout = 1000,
        .read_inc = true,
    };
    int errc = spi_transfer_sync(&transfer);
    if (errc != TI_ERRC_NONE) {
        return errc;
    }
    if (read_resp_buff != 0xFF) {
        
        while (read_resp_buff != 0xFF) {
            errc = spi_transfer_sync(&transfer);
            if (errc != TI_ERRC_NONE) {
                return errc;
            }
            if (--config.timeout == 0) {
                return TI_ERRC_RADIO_CTS_TIMEOUT;
            }
        }
    }
    return TI_ERRC_NONE;
}

int radio_send_command(void *command, size_t size) {
   spi_block(config.spi_dev);
   
   // Send command
   uint8_t rx_buff;
   struct spi_sync_transfer_t transfer = {
       .device = config.spi_dev,
       .source = command,
       .dest = &rx_buff,
       .size = size,
       .timeout = 1000,
       .read_inc = false,
   };
   int errc = spi_transfer_sync(&transfer);
   if (errc != TI_ERRC_NONE) {
       spi_unblock(config.spi_dev);
       return errc;
   }

   // Wait for CTS
   uint8_t read_cmd_buff = 0x44;
   errc = radio_get_CTS();
   spi_unblock(config.spi_dev);
   if (errc != TI_ERRC_NONE) {
       return errc;
   }

   return TI_ERRC_NONE;
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

   // Power on the device
   uint8_t power_on_cmd[] = {
    0x02,
    0x01, // Normal operation
    0x00, // Internal crystal
    0x01, 0xC9, 0xC3, 0x80}; // 30MHz crystal, 4.5V
   size_t power_on_size = sizeof(power_on_cmd) / sizeof(power_on_cmd[0]);
   radio_send_command(&power_on_cmd, power_on_size);

   // Global configuration
   uint8_t global_config_command[] = {
       0x11, // Set property
       0x00, // Group: Global
       0x01, // Num props: 1
       0x00, // Start prop: GLOBAL_XO_TUNE
       config->global_xo_tune,
   };
   size_t global_config_size = sizeof(global_config_command);
   int errc = radio_send_command(&global_config_command, global_config_size);
   if (errc != TI_ERRC_NONE) {
       return errc;
   }
   
   // Control configuration
   uint8_t control_config_command[] = {
       0x11, // Set property
       0x01, // Group: Control
       0x04, // Num props: 4
       0x00, // Start prop: FRR_CTL_A_MODE
       0x09, // Current state
       0x04, // PACKET_SENT Flag
       0x08, // Error flag
       0x10, // Check if lots of interference
   };
   size_t control_config_size = sizeof(control_config_command);
   errc = radio_send_command(&control_config_command, control_config_size);
   if (errc != TI_ERRC_NONE) {
       return errc;
   }

   // Modem configuration
   uint8_t modem_config_command[] = {
       0x11, // Set property
       0x20, // Group: Modem
       0x07, // Num props: 7
       0x00, // Start prop: MODEM_MOD_TYPE
       config->mod_type,
       0x00, // Default
       0x04, // Default
       ((uint8_t *) config->data_rate)[2], // Bps?
       ((uint8_t *) config->data_rate)[1], // Bps?
       ((uint8_t *) config->data_rate)[0], // Bps?
       config->gauss_oversample, // 0-3
   };
   size_t modem_config_size = sizeof(modem_config_command);
   errc = radio_send_command(&modem_config_command, modem_config_size);
   if (errc != TI_ERRC_NONE) {
       return errc;
   }

   // TODO: Maybe add match functionality?

   return TI_ERRC_NONE;
}