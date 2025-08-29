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
 * @file src/platform/i2c.c
 * @authors Charles Faisandier
 * @brief I2C driver implementation
 */

#pragma once
#include "mcu/i2c.h"
#include "internal/mmio.h"
#include "mcu/dma.h"
#include "util/errc.h"
#include "kernel/mutex.h"
#include <stdint.h>


#define I2C_INSTANCE_COUNT 4

/**************************************************************************************************
 * @section Internal Data Structures and Data Types
 **************************************************************************************************/
// Used to find the right request number for the I2C instance
// Index 0 is for RX request, 1 is for TX
// I2C4 is handled by DMAMUX2 so It's excluded for now.
static const i2c_dmamux_req[I2C_INSTANCE_COUNT][2] = {
    [1] = {
        [0] = 33,
        [1] = 34,
    },
    [2] = {
        [0] = 35,
        [1] = 36,
    },
    [3] = {
        [0] = 73,
        [1] = 74,
    },
};

i2c_config_t *i2c_configs[I2C_INSTANCE_COUNT] = {0};

struct ti_mutex_t i2c_mutex[I2C_INSTANCE_COUNT] = {0};

uint8_t i2c_contexts[] = {1, 2, 3, 4};

void *guest_contexts[I2C_INSTANCE_COUNT] = {0};

dma_callback_t i2c_callbacks[I2C_INSTANCE_COUNT] = {0};

/**************************************************************************************************
 * @section Private Helper Functions
 **************************************************************************************************/
void i2c_callback(bool success, void *context) {
    // TODO: Implement callback handling
    uint8_t instance = *((uint8_t*)context);
    if (i2c_callbacks[instance]) {
        i2c_callbacks[instance](success, guest_contexts[instance]);
    }
    if (!ti_release_mutex(i2c_mutex[instance], i2c_configs[instance]->mutex_timeout)) {
        // TODO: Log error.
    }
    return false;
}

/**************************************************************************************************
 * @section Public Function Implementation 
 **************************************************************************************************/
int i2c_init(i2c_config_t *config){
    // TODO: Check parameters

    // Register config
    i2c_configs[config->instance] = config;

    // 1. Enable the I2C clock
    SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_I2CxEN[config->instance]);

    // 2. Enable the GPIO clock and configure pins
    tal_enable_clock(config->scl_pin);
    tal_enable_clock(config->sda_pin);

    // Alternate function mode
    tal_set_mode(config->sda_pin, 2); 
    tal_set_mode(config->scl_pin, 2);
    tal_alternate_mode(config->sda_pin, 4); 
    tal_alternate_mode(config->scl_pin, 4);

    // Open drain
    tal_set_drain(config->sda_pin, 1); 
    tal_set_drain(config->scl_pin, 1);

    // High speed
    tal_set_speed(config->sda_pin, 3);
    tal_set_speed(config->scl_pin, 3);

    // Pull up
    tal_pull_pin(config->sda_pin, 1); 
    tal_pull_pin(config->scl_pin, 1);

    // 3. Disable peripheral before configuring
    WRITE_FIELD(I2Cx_CR1[config->instance], I2Cx_CR1_PE, 0);
    
    // 4. Configure addressing mode (7-bit or 10-bit)
    if (config->addr_mode == I2C_ADDR_10BIT) {
        SET_FIELD(I2Cx_CR2[config->instance], I2Cx_CR2_ADD10);
    } else {
        CLR_FIELD(I2Cx_CR2[config->instance], I2Cx_CR2_ADD10);
    }

    // 5. Configure analog and digital filters
    if (config->analog_filter) CLR_FIELD(I2Cx_CR1[config->instance], I2Cx_CR1_ANFOFF);
    WRITE_FIELD(I2Cx_CR1[config->instance], I2Cx_CR1_DNF, config->digital_filter);

    // 6. Set timing
    *I2Cx_TIMINGR[config->instance] = config->timing;

    // 10. Re-enable the I2C peripheral
    SET_FIELD(I2Cx_CR1[config->instance], I2Cx_CR1_PE);

    return true;
}

int i2c_read_async(struct i2c_transfer_async_t *transfer) {
    // TODO: Check parameters

    // De-reference for readability
    struct i2c_device_t device = transfer->device; 
    uint8_t *rx_data = transfer->data;
    size_t size = transfer->size;

    // Check if busy
    if (!ti_acquire_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
        return TI_ERRC_MUTEX_AQU_TIMEOUT;
    }

    // Register callback and context
    i2c_callbacks[device.instance] = transfer->callback;
    guest_contexts[device.instance] = (void*)transfer->context;

    dma_transfer_t rx_transfer = {
        .request_id = i2c_dmamux_req[device.instance][0],
        .direction = PERIPH_TO_MEM,
        .src_data_size = 1,
        .dest_data_size = 1,
        .priority = transfer->dma_priority,
        .fifo_enabled = false,
        .fifo_threshold = 0,
        .callback = i2c_callback,
        .src = I2Cx_RXDR[device.instance],
        .dest = rx_data,
        .size = size,
        .context = (void*)&i2c_contexts[device.instance],
        .mem_inc = false,
    };

    int errc = dma_start_transfer(&rx_transfer);
    if (errc != TI_ERRC_NONE) {
        return errc;
    }

    // Configure and enable I2C for a read
    if (READ_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_ADD10)) {
        WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_SADD_10BIT, device.address);
    } else {
        WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_SADD_7BIT, device.address);
    }
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_AUTOEND);
    WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_NBYTES, size);
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_RD_WRN); // Set to 1 for a read operation
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_PECBYTE);
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_RELOAD);

    // Enable the DMA requests and start the transfer
    SET_FIELD(I2Cx_CR1[device.instance], I2Cx_CR1_RXDMAEN); // Enable DMA for reception
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_START);  // Send the START condition

    return true;
}

int i2c_write_async(struct i2c_transfer_async_t *transfer) {
    // 1. Check parameters

    // De-reference for readability
    struct i2c_device_t device = transfer->device;
    uint8_t *tx_data = transfer->data;
    size_t size = transfer->size;

    // 2. Check if the I2C bus is busy using an atomic operation.
    if (!ti_acquire_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
        return TI_ERRC_MUTEX_AQU_TIMEOUT;
    }   

    // 3. Configure the DMA transfer
    dma_transfer_t tx_transfer = {
        .request_id = i2c_dmamux_req[device.instance][1],
        .direction = MEM_TO_PERIPH,
        .src_data_size = 1,
        .dest_data_size = 1,
        .priority = transfer->dma_priority,
        .fifo_enabled = false,
        .fifo_threshold = 0,
        .callback = i2c_callback,
        .src = tx_data,
        .dest = I2Cx_TXDR[device.instance],
        .size = size,
        .context = (void*)&i2c_contexts[device.instance],
        .mem_inc = false,
    };

    // 4. Start the DMA transfer
    int errc = dma_start_transfer(&tx_transfer);
    if (errc != TI_ERRC_NONE) {
        if (!ti_release_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
            return TI_ERRC_MUTEX_REL_TIMEOUT;
        }
        return errc;
    }

    // 5. Configure and enable the I2C peripheral for a write
    if (READ_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_ADD10)) {
        WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_SADD_10BIT, device.address);
    } else {
        WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_SADD_7BIT, device.address);
    }
    WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_NBYTES, size);    // Set number of bytes
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_RD_WRN);            // Set to 0 for a write operation
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_AUTOEND);           // Auto-generate STOP condition
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_PECBYTE);           // Disable PEC
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_RELOAD);            // Disable reload

    // 6. Enable the DMA requests and start the transfer
    SET_FIELD(I2Cx_CR1[device.instance], I2Cx_CR1_TXDMAEN); // Enable DMA for transmission
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_START);   // Send the START condition

    return true;
}

int i2c_read_sync(struct i2c_transfer_sync_t *transfer) {
    // TODO: Check parameters
    // De-reference for readability
    struct i2c_device_t device = transfer->device; 
    uint8_t *rx_data = transfer->data;
    size_t size = transfer->size;

    if (!ti_acquire_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
        return TI_ERRC_MUTEX_AQU_TIMEOUT;
    }

    // Configure and enable I2C for a read
    if (READ_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_ADD10)) {
        WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_SADD_10BIT, device.address);
    } else {
        WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_SADD_7BIT, device.address);
    }
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_AUTOEND);
    WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_NBYTES, size);
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_RD_WRN); // Set to 1 for a read operation
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_PECBYTE);
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_RELOAD);

    // Start the transfer
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_START);  // Send the START condition

    // Read the data byte by byte in a blocking loop.
    for (size_t i = 0; i < size; ++i) {
        // Wait until the receive data register is not empty (RXNE flag).
        uint32_t timeout = 0;
        while (!READ_FIELD(I2Cx_ISR[device.instance], I2Cx_ISR_RXNE)) {
            if (timeout++ > i2c_configs[device.instance]->i2c_timeout) {
                if (!ti_release_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
                    return TI_ERRC_MUTEX_REL_TIMEOUT;
                }
                return TI_ERRC_I2C_TIMEOUT;
            }
        }
        // Read the received byte from the data register.
        rx_data[i] = (uint8_t)READ_FIELD(I2Cx_RXDR[device.instance], I2Cx_RXDR_RXDATA);
    }
    
    // Wait for the STOP condition to be sent (STOPF flag).
    uint32_t timeout_stop = 0;
    while (!READ_FIELD(I2Cx_ISR[device.instance], I2Cx_ISR_STOPF)) {
         if (timeout_stop++ > i2c_configs[device.instance]->i2c_timeout) {
            if (!ti_release_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
                return TI_ERRC_MUTEX_REL_TIMEOUT;
            }
            return TI_ERRC_I2C_TIMEOUT;
        }
    }
    // Clear the STOPF flag by writing 1 to it.
    WRITE_FIELD(I2Cx_ICR[device.instance], I2Cx_ICR_STOPCF, 1);
    if (!ti_release_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
        return TI_ERRC_MUTEX_REL_TIMEOUT;
    }
    return true;
}

int i2c_write_blocking(struct i2c_transfer_sync_t *transfer) {
    // TODO: Check parameters

    // De-reference for readability
    struct i2c_device_t device = transfer->device; 
    uint8_t *tx_data = transfer->data;
    size_t size = transfer->size;

    // 2. Check if busy
    if (!ti_acquire_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
        return TI_ERRC_MUTEX_AQU_TIMEOUT;
    }

    // 3. Configure the I2C peripheral for a write
    // The peripheral's NBYTES register will handle the number of bytes to transfer.
    WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_NBYTES, size);
    
    // Set the slave address and the read/write direction bit.
    if (READ_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_ADD10)) {
        // For 10-bit addressing, the address is written directly to the SADD_10BIT field.
        WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_SADD_10BIT, device.address);
    } else {
        // For 7-bit addressing, the address is shifted left by one.
        WRITE_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_SADD_7BIT, device.address);
    }
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_RD_WRN);     // Set to 0 for a write operation
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_AUTOEND);    // Auto-generate STOP condition
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_PECBYTE);    // Disable PEC
    CLR_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_RELOAD);     // Disable reload

    // 4. Send the START condition to begin the transaction.
    SET_FIELD(I2Cx_CR2[device.instance], I2Cx_CR2_START);

    // 5. Write the data byte by byte in a blocking loop.
    for (size_t i = 0; i < size; ++i) {
        // Wait until the transmit data register is empty (TXIS flag).
        uint32_t timeout = 0;
        while (!READ_FIELD(I2Cx_ISR[device.instance], I2Cx_ISR_TXIS)) {
            if (timeout++ > i2c_configs[device.instance]->i2c_timeout) {
                if (!ti_release_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
                    return TI_ERRC_MUTEX_REL_TIMEOUT;
                }
                return TI_ERRC_I2C_TIMEOUT;
            }
        }
        // Write the next byte to the transmit data register.
        WRITE_FIELD(I2Cx_TXDR[device.instance], I2Cx_TXDR_TXDATA, tx_data[i]);
    }
    
    // 6. Wait for the STOP condition to be sent (STOPF flag).
    uint32_t timeout_stop = 0;
    while (!READ_FIELD(I2Cx_ISR[device.instance], I2Cx_ISR_STOPF)) {
         if (timeout_stop++ > i2c_configs[device.instance]->i2c_timeout) {
            if (!ti_release_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
                return TI_ERRC_MUTEX_REL_TIMEOUT;
            }
            return TI_ERRC_I2C_TIMEOUT;
        }
    }
    // Clear the STOPF flag by writing 1 to it.
    WRITE_FIELD(I2Cx_ICR[device.instance], I2Cx_ICR_STOPCF, 1);

    if (!ti_release_mutex(i2c_mutex[device.instance], i2c_configs[device.instance]->mutex_timeout)) {
        return TI_ERRC_MUTEX_REL_TIMEOUT;
    }

    return TI_ERRC_NONE;
}