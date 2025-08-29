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
#include "kernel/mutex.h"
#include "util/errc.h"
#include "mcu/spi.h"
#include "mcu/gpio.h"

#define RADIO_MUTEX_TIMEOUT 1000

/**************************************************************************************************
 * @section Private Type Definitions
 **************************************************************************************************/
struct radio_context_t {
    void *data;
    size_t size;
};

/**************************************************************************************************
 * @section Private Data Structures
 **************************************************************************************************/
struct ti_radio_config_t config = {0};
struct ti_mutex_t radio_mutex = {0};
struct radio_context_t radio_context = {0};

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
       return errc;
   }

   // Wait for CTS
   uint8_t read_cmd_buff = 0x44;
   errc = radio_get_CTS();
   if (errc != TI_ERRC_NONE) {
       return errc;
   }

   return TI_ERRC_NONE;
}

int cancel_transaction() {
    uint8_t cancel_command[] = {
        0x34, // Change state
        0x01, // Go to ready state
    };
    size_t cancel_size = sizeof(cancel_command);
    spi_block(config.spi_dev);
    int errc =  radio_send_command(&cancel_command, cancel_size);
    spi_unblock(config.spi_dev);
    ti_mutex_release(radio_mutex, RADIO_MUTEX_TIMEOUT);
    exti_disable(config.nirq_pin);
    return errc;
}

void spi_callback(bool success) {
  spi_unblock(config.spi_dev);
  if (!success) {
    // TODO: Log, potentially handle error
    return;
  }
    uint8_t frr_command = 0x50;
    uint8_t rx_data;
    spi_block(config.spi_dev);
    int errc = spi_transfer_sync(&(struct spi_sync_transfer_t){
        .device = config.spi_dev,
        .source = &frr_command,
        .dest = &rx_data,
        .size = 1,
        .timeout = config.tx_write_timeout,
        .read_inc = true,
    });
    if (errc != TI_ERRC_NONE) {
        cancel_transaction();
    }
    uint8_t frr_size = 4;
    uint8_t frr_results[4];
    errc = spi_transfer_sync(&(struct spi_sync_transfer_t){
        .device = config.spi_dev,
        .source = &rx_data,
        .dest = frr_results,
        .size = frr_size,
        .timeout = config.tx_write_timeout,
        .read_inc = false,
    });
    spi_unblock(config.spi_dev);
    if (errc != TI_ERRC_NONE) {
        cancel_transaction();
    }
    uint8_t cur_state = frr_results[0];
    uint8_t ph_pend = frr_results[1];
    uint8_t int_chip_pending = frr_results[2];
    uint8_t latched_rssi = frr_results[3];
    // FIFO error or CRC error or CMD error
    if (cur_state == 0x04 || ph_pend == 0x01 || int_chip_pending == 0x01) {
        // TODO: Log frr results
        cancel_transaction();
    // READY state and PACKET_SENT
    } else if (cur_state == 0x01 && ph_pend == 0x04) {
        exti_disable(config.nirq_pin);
        ti_mutex_release(radio_mutex, RADIO_MUTEX_TIMEOUT);
    }
    return;
}

void tx_empty_callback(void) {
    uint8_t fifo_size = config.combined_fifo ? 129 : 64;
    size_t bytes_avail = fifo_size - config.tx_threshold;
    uint8_t rx_data;
    int errc = spi_block(config.spi_dev);
    if (errc != TI_ERRC_NONE)
        return errc;
    int errc = spi_transfer_async(&(struct spi_async_transfer_t){
        .device = config.spi_dev,
        .source = radio_context.data,
        .dest = &rx_data,
        .size = bytes_avail < radio_context.size ? bytes_avail : radio_context.size,
        .callback = spi_callback,
        .write_fifo = true,
        .read_fifo = false,
        .write_mem_inc = true,
        .read_mem_inc = false,
    });
    if (errc != TI_ERRC_NONE) {
        // TODO: Log this, handle error.
        cancel_transaction();
        return;
    }
}

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
int ti_radio_init(struct ti_radio_config_t *config) {
    if (ti_acquire_mutex(radio_mutex, RADIO_MUTEX_TIMEOUT) != TI_ERRC_NONE) {
        return TI_ERRC_MUTEX_LOCKED;
    }

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
   size_t power_on_size = sizeof(power_on_cmd);
   radio_send_command(&power_on_cmd, power_on_size);

   // Register the interrupt
   ti_exti_register_pin(config->nirq_pin, &tx_empty_callback, config->interupt_priority, true);

   // Global configuration
   uint8_t global_config_command[] = {
       0x11, // Set property
       0x00, // Group: Global
       0x04, // Num props: 4
       0x00, // Start prop: GLOBAL_XO_TUNE
       config->global_xo_tune,
       0x00, // Default clock
       0x00, // Default low battery threshold
       0x01 | (config->combined_fifo << 3),  // Combined FIFO and high power mode
   };
   size_t global_config_size = sizeof(global_config_command);
   int errc = radio_send_command(&global_config_command, global_config_size);
   if (errc != TI_ERRC_NONE) {
       ti_release_mutex(radio_mutex, RADIO_MUTEX_TIMEOUT);
       return errc;
   }

   // Interrupt configuration
    uint8_t interrupt_config_command[] = {
        0x11, // Set property
        0x01, // Group: Control
        0x02, // Num props: 2
        0x00, // Start prop: INT_CTL_ENABLE
        0x01, // Enable PH nIRQ
        0x02, // TX_FIFO_ALMOST_EMPTY interrupt
    };

   // Fast Response Register Control configuration
   uint8_t control_config_command[] = {
       0x11, // Set property
       0x02, // Group: FRR Control
       0x04, // Num props: 4
       0x00, // Start prop: FRR_CTL_A_MODE
       0x09, // Reg A: Current state
       0x03, // Reg B: PACKET_SENT Flag
       0x08, // Reg C: Error flag
       0x10, // Reg D: Check if lots of interference
   };
   size_t control_config_size = sizeof(control_config_command);
   errc = radio_send_command(&control_config_command, control_config_size);
   if (errc != TI_ERRC_NONE) {
        ti_release_mutex(radio_mutex, RADIO_MUTEX_TIMEOUT);
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
        ti_release_mutex(radio_mutex, RADIO_MUTEX_TIMEOUT);
       return errc;
   }

   // Packet configuration
   // TODO: Potentially add CRC
    uint8_t packet_config_command[] = {
        0x11, // Set property
        0x12, // Group: Packet
        0x0b,
        15, // Num props: 13
        config->tx_threshold, // TX Threshold
        0x30, // TX Threshold: default
        ((uint8_t *) config->f1_length)[1],
        ((uint8_t *) config->f1_length)[0],
        0x00, // Field 1 Config: Default
        0x00, // Field 1 CRC Config: Default.
        ((uint8_t *) config->f2_length)[1],
        ((uint8_t *) config->f2_length)[0],
        0x00, // Field 2 Config: Default
        0x00, // Field 2 CRC Config: Default.
        ((uint8_t *) config->f3_length)[1],
        ((uint8_t *) config->f3_length)[0],
        0x00, // Field 3 Config: Default
        0x00, // Field 3 CRC Config: Default.
        ((uint8_t *) config->f4_length)[1],
        ((uint8_t *) config->f4_length)[0],
        0x00, // Field 4 Config: Default
        0x00, // Field 4 CRC Config: Default.
        ((uint8_t *) config->f5_length)[1],
        ((uint8_t *) config->f5_length)[0],
    };
    size_t packet_config_size = sizeof(packet_config_command);
    errc = radio_send_command(&packet_config_command, packet_config_size);
    if (errc != TI_ERRC_NONE) {
        ti_release_mutex(radio_mutex, RADIO_MUTEX_TIMEOUT);
        return errc;
    }

   // TODO: Maybe add match functionality?

   // TODO: Maybe configure variable length fields?
   

   return TI_ERRC_NONE;
}

int ti_radio_transmit(void *data, size_t size, uint8_t channel) {
    if (!ti_acquire_mutex(radio_mutex, RADIO_MUTEX_TIMEOUT)) {
        return TI_ERRC_MUTEX_LOCKED;
    }
    // TODO: Parameter checking

    // Register context
    radio_context.data = data;
    radio_context.size = size; 

    // Write data to TX FIFO
    uint8_t write_fifo_command[] = {
        0x66, // Write TX FIFO
    };
    uint8_t rx_data;
    spi_block(config.spi_dev);
    int errc = spi_transfer_sync(&(struct spi_sync_transfer_t){
        .device = config.spi_dev,
        .source = write_fifo_command,
        .dest = &rx_data,
        .size = 1,
        .timeout = 1000,
        .read_inc = false,
    });
    if (errc != TI_ERRC_NONE) {
        spi_unblock(config.spi_dev);
        return errc;
    }

    // Send START_TX command
    uint8_t start_tx_command[] = {
        0x31, // Start TX
        channel,
        0x30, // Enter TX mode, exit READY state, don't re-transmit.
        ((uint8_t *) &size)[1],
        ((uint8_t *) &size)[0],
        0x00, // No delay
        0x00, // No repeat
    };
    size_t start_tx_size = sizeof(start_tx_command);
    int errc = radio_send_command(&start_tx_command, start_tx_size);
    spi_unblock(config.spi_dev);
    if (errc != TI_ERRC_NONE) {
        return errc;
    }
    // Enable the interrupt
    exti_enable(config.nirq_pin);


    return TI_ERRC_NONE;
}