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
 * @file modules/inputs/src/gnss.c
 * @authors Charles Faisandier
 * @brief Implementation of NEO-M9N-00B
 */
#include "mcu/gpio.h"
#include "inputs/gnss.h"
#include "internal/mmio.h"
#include "mcu/exti.h"
#include "app/mem_loc.h"
#include "kernel/semaphore.h"
#include "kernel/thread.h"
#include "util/errc.h"

#define PVT_MESSAGE_SIZE 8 + 92   // 8 is size of headers and metadata, 92 is payload size
#define TX_SIZE 250     // Fixed size array length for tx

/**************************************************************************************************
 * @section Private Data Structures
 **************************************************************************************************/
gnss_config_t config = {0};
struct ti_semaphore_t semaphore = {0};
struct ti_thread_t thread = {0};
uint8_t pvt_message[PVT_MESSAGE_SIZE];    

/**************************************************************************************************
 * @section Private Type Definitions
 **************************************************************************************************/
enum {
    NO_FIX,
    DEAD_REC,
    FIX_2D,
    FIX_3D,
    GNSS_DED_REC,
    TIME_ONLY,
} gnss_fix_t;

/**************************************************************************************************
 * @section Private Function Implementations
 **************************************************************************************************/
uint16_t calculate_checksum(uint8_t *data, uint32_t size) {
    // TODO: implement checksum algorithm
    return 0x0000;
}

// MAX LENGTH TX_SIZE - 8
int send_ubx_message_blocking(uint8_t class, uint8_t id, uint16_t length, uint8_t *data) {
    // TODO: Parameter checking

    // Create the ubx message and send it.
    uint32_t tx_size = 8 + length; // 2 bytes for sync chars, 2 bytes for class and id, 2 bytes for length, 2 bytes for checksum.
    uint8_t ubx_tx[TX_SIZE];
    ubx_tx[0] = 0xb5;
    ubx_tx[1] = 0x62;
    ubx_tx[2] = class;
    ubx_tx[3] = id;
    *((uint16_t*)&ubx_tx[4]) = length; 
    for (int i = 0; i < length; i++) {
        ubx_tx[6 + i] = data[i];
    }
    *((uint16_t*)&ubx_tx[6 + length]) = calculate_checksum(ubx_tx, tx_size);
    int errt = spi_write_blocking(config.device, ubx_tx, tx_size);
    if (!errt)
        return errt;

    // Get the agnowledgement message and check it
    const uint8_t rx_size = 10;
    uint8_t ubx_rx[rx_size];
    int errt = spi_read_blocking(config.device, ubx_rx, rx_size);
    if (!errt) {
        return errt;
    }
    uint16_t calc_checksum = calculate_checksum(ubx_rx, rx_size);
    if (calc_checksum != *((uint16_t*)&ubx_rx[8]))
        return TI_ERRC_UBX_CHECKSUM;
    if (ubx_rx[0] != 0xb5 || ubx_rx[1] != 0x62)
        return TI_ERRC_UBX_HEADER;
    if (ubx_rx[3] != 0x01 || ubx_rx[2] != 0x05)
        return TI_ERRC_UBX_CLASS_ID;
    if (*((uint16_t*)&ubx_rx[4]) != 0x02)
        return TI_ERRC_UBX_SIZE;
    if (ubx_rx[6] != class || ubx_rx[7] != id)
        return TI_ERRC_UBX_PAYLOAD;
    return true;
}

bool check_gnss_config_params(gnss_config_t *gnss_config) {
    if (gnss_config == NULL) {
        return false;
    }
    if (!IS_VALID_DEVICE(gnss_config->device)) {
        return false;
    }
    if (!gnss_config->dsel_pin) {
        return false;
    }
    if (port_index_from_pin[gnss_config->txready_pin_mcu] == -1) {
        return false;
    }
    if (gnss_config->txready_pin_gnss < 15 || gnss_config->txready_pin_gnss > 17) {
        return false;
    }
    return true;
}

void gnss_irq_callback(){
    ti_semaphore_give(semaphore);
}

bool parse_pvt(void) {
    // Check the received message is what we expect
    uint16_t calc_checksum = calculate_checksum(pvt_message, PVT_MESSAGE_SIZE);
    if (calc_checksum != *((uint16_t*)&pvt_message[8]))
        return false;
    if (pvt_message[0] != 0xb5 || pvt_message[1] != 0x62)
        return false;
    if (pvt_message[2] != 0x01 || pvt_message[3] != 0x07)
        return false;
    if (*((uint16_t*)&pvt_message[4]) != 92)
        return false;
    
    // Parse the message
    uint8_t fixtype = pvt_message[20]; // We should never get any deadrec flags
    if (fixtype == NO_FIX)
        return false;
    uint8_t valid = pvt_message[6 + 11];
    if (valid & 0x01) {// validDate
        gnss_data_buff.year = *((uint16_t *) &pvt_message[4]);
        gnss_data_buff.month = pvt_message[6];
        gnss_data_buff.day = pvt_message[7];
    } // Else 0?
    if (valid & 0x02) {
        gnss_data_buff.hour = pvt_message[8];
        gnss_data_buff.min = pvt_message[9];
        gnss_data_buff.sec = pvt_message[10]; // I'm not checking fully resolved so there might be uncertainty
    } // Else 0?
    gnss_data_buff.tacc = *((uint32_t *) &pvt_message[12]);
    gnss_data_buff.nano = *((int32_t *) &pvt_message[16]);
    if (fixtype == FIX_2D || fixtype == FIX_3D) {
        gnss_data_buff.lon = *((int32_t *) &pvt_message[24]);
        gnss_data_buff.lat = *((int32_t *) &pvt_message[28]);
        gnss_data_buff.hacc = *((uint32_t *) &pvt_message[40]);
        gnss_data_buff.veln = *((int32_t *) &pvt_message[48]);
        gnss_data_buff.vele = *((int32_t *) &pvt_message[52]);
        gnss_data_buff.gspeed = *((int32_t *) &pvt_message[60]);
        gnss_data_buff.sacc = *((uint32_t *) &pvt_message[68]);
        if (fixtype == FIX_3D) {
            gnss_data_buff.height = *((int32_t *) &pvt_message[32]);
            gnss_data_buff.vacc = *((uint32_t *) &pvt_message[44]);
            gnss_data_buff.veld = *((int32_t *) &pvt_message[56]);
        } // Else 0?
    } // Else 0?
    gnss_data_buff.headmot = *((int32_t *) &pvt_message[64]);
    gnss_data_buff.headacc = *((uint32_t *) &pvt_message[72]);
    
}

void gnss_thread() {
    while (1) {
        ti_take_semaphore(semaphore);
        spi_read_async(config.device, pvt_message, PVT_MESSAGE_SIZE, &parse_pvt, 4);
    }
}

/**************************************************************************************************
 * @section Public Function Implementations
 **************************************************************************************************/
int gnss_init(gnss_config_t *gnss_config) {
    // Check parameters
    if (!check_gnss_config_params(gnss_config))
        return TI_ERRC_INVALID_ARG;

    // De-reference config for readability
    spi_device_t device = gnss_config->device;
    uint8_t dsel_pin = gnss_config->dsel_pin;
    uint8_t txready_pin_mcu = gnss_config->txready_pin_mcu;
    uint8_t txready_pin_gnss = gnss_config->txready_pin_gnss;
    uint32_t inter_prio = gnss_config->inter_prio;
    uint32_t thread_prio = gnss_config->thread_prio;
    uint8_t pvt_rate = gnss_config->pvt_rate;

    // Select SPI as desired protocol
    tal_enable_clock(dsel_pin);
    tal_set_drain(dsel_pin, 0);
    tal_pull_pin(dsel_pin, -1);

    // Configure txready_pin_mcu
    tal_enable_clock(txready_pin_mcu);
    tal_set_mode(txready_pin_mcu, 0);
    tal_set_drain(txready_pin_mcu, 0);
    tal_pull_pin(txready_pin_mcu, 1);
    tal_set_speed(txready_pin_mcu, 1);

    // Create the stream and enable the isr
    semaphore = ti_create_semaphore(1, 0);
    thread = ti_create_thread(&gnss_thread, NULL, 0, 0, thread_prio); // TODO: Find stack pointer and size
    exti_enable_isr(txready_pin_mcu, &gnss_irq_callback, inter_prio, true);

    // Configure SPI device
    enum ti_errc_t errc = spi_device_init(device);
    if (errc != 0)
        return errc;
    config.device= device;

    // Set gnss configuration
    uint8_t config_msg[] = {
        0x10, 0x64, 0x00, 0x06, // CFG-SPI-ENABLED
        0x01,
        0x10, 0xa2, 0x00, 0x01, // CFG-TXREADY-ENABLED
        0x01,
        0x10, 0xa2, 0x00, 0x02, // CFG-TXREADY-POLARITY
        0x01,                   // Low-active
        0x20, 0xa2, 0x00, 0x03, // CFG_TXREADY-PIN
        txready_pin_gnss,
        0x20, 0x91, 0x00, 0x0a, // CFG-MSTGOUT-UBX-NAV-PVT-SPI | How often to output the PVT info on SPI
        pvt_rate,
        0x10, 0x31, 0x00, 0x1f, // CFG-SIGNAL-GPS-ENA
        0x01,
    };
    size_t payload_size = 30;
    if (!send_ubx_message_blocking(0x06, 0x8A, payload_size, config_msg))
        return TI_ERRC_GNSS_CONFIG_FAIL;    

    return TI_ERRC_NONE;
}

int gnss_deinit() {
    // Disable gpio clocks
    tal_disable_clock(config.dsel_pin);
    tal_disable_clock(config.txready_pin_mcu);

    // Delete thread and disable isr
    ti_destroy_thread(thread);
    ti_semaphore_destroy(semaphore);
    exti_disable_isr(config.txready_pin_mcu);

    // Set GNSS to sleep
    uint8_t *config_msg = {
        0x20, 0xd0, 0x00, 0x01,
        0x01,
    };
    size_t payload_size = 5;
    if (!send_ubx_message_blocking(0x06, 0x8A, payload_size, config_msg))
        return TI_ERRC_GNSS_CONFIG_FAIL;

    return TI_ERRC_NONE;
}