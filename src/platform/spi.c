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
 * @file common/platform/spi.c
 * @authors Charles Faisandier
 * @brief Implementation of SPI driver interface
 */
#include "platform/spi.h"
#include "tal/error.h"
#include "mmio.h"
#include "gpio.h"
#include <stdint.h>

#define DATA_REG_SIZE 32
#define NUM_REQUESTS_PER_SPI 2
// Maximum number of devices per SPI instance
#define MAX_DEVICES_PER_INSTANCE 5

/**************************************************************************************************
 * @section Internal Data Structures
 **************************************************************************************************/
volatile dma_periph_streaminfo_t spi_to_dma[SPI_INSTANCE_COUNT] = {0};

// Used to look up SPI DMAMUX request numbers
// Note: SPI6 Does not seem to have requests
// Index 0 is RX index 1 is TX
const static uint8_t spi_dmamux_req[SPI_INSTANCE_COUNT][NUM_REQUESTS_PER_SPI] = {
    [1] = {
        [0] = 37,
        [1] = 38,  
    },
    [2] = {
        [0] = 39,
        [1] = 40,
    },
    [3] = {
        [0] = 61,
        [1] = 62,
    },
    [4] = {
        [0] = 83,
        [1] = 84,
    },
    [5] = {
        [0] = 85,
        [1] = 86,
    }
};

// Used to make sure we wait that transfers are complete before starting a new one
bool spi_busy[SPI_INSTANCE_COUNT] = {0};

// Stores SPI contexts
static spi_context_t spi_context_arr[SPI_INSTANCE_COUNT][MAX_DEVICES_PER_INSTANCE] = {0};

/**************************************************************************************************
 * @section Private Function Implementations
 **************************************************************************************************/
inline static bool check_spi_config_validity(tal_flag_t *flag, spi_config_t *config) {
    if (config == NULL) {
        tal_set_err(flag, "SPI_CONFIG_ERROR: Config pointer is NULL");
        return false;
    }
    if (config->instance < SPI_INSTANCE_MIN || config->instance >= SPI_INSTANCE_COUNT ) {
        tal_set_err(flag, "SPI_CONFIG_ERROR: Invalid SPI instance");
        return false;
    }
    if (config->mode < SPI_MODE_MIN || config->mode >= SPI_MODE_COUNT) {
        tal_set_err(flag, "SPI_CONFIG_ERROR: Invalid SPI mode");
        return false;
    }
    if (config->data_size < SPI_DATA_SIZE_MIN || config->data_size >= SPI_DATA_SIZE_COUNT) {
        tal_set_err(flag, "SPI_CONFIG_ERROR: Invalid data size");
        return false;
    }
    if (config->baudrate_prescaler < SPI_BAUDRATE_PRESCALER_MIN ||
         config->baudrate_prescaler >= SPI_BAUDRATE_PRESCALER_COUNT) {
        tal_set_err(flag, "SPI_CONFIG_ERROR: Invalid baudrate prescaler");
        return false;
    }
    if (config->first_bit < SPI_FIRST_BIT_MIN || config->first_bit >= SPI_FIRST_BIT_COUNT) {
        tal_set_err(flag, "SPI_CONFIG_ERROR: Invalid first bit configuration");
        return false;
    }
    return true;
}

/**************************************************************************************************
 * @section Public Function Implementations
 **************************************************************************************************/
/**
 * @brief Initializes an SPI controller. Configures a TX and RX DMA stream for the SPI peripheral. 
 * It's important to choose SPI parameters that are compatible with all devices that will share the
 * controller.
 * 
 * @param flag Flag pointer for error heandling
 * @param config Point to config structure
 * @param tx_stream DMA configuration for TX stream
 * @param rx_stream DMA configuration for RX stream
 */
bool spi_init(tal_flag_t *flag, spi_config_t *config, dma_callback_t callback, periph_dma_config_t *tx_stream, periph_dma_config_t *rx_stream) {
    // Parameter checking
    if (flag == NULL) {
        return false;
    }
    if (callback == NULL) {
        tal_raise(flag, "DMA Callback cannot be NULL");
        return false;
    }
    if (!check_spi_dma_config_validity(flag, tx_stream)) return false;
    if (!check_spi_dma_config_validity(flag, rx_stream)) return false;

    // Enable SPI Peripheral Clock
    switch (config->instance) {
        case (SPI1):
            SET_FIELD(RCC_AHB2ENR, RCC_ABP2ENR_SPI1EN); // TODO: Can't find this field
            break;
        case (SPI2):
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_SPIxEN[2]);
            break;
        case (SPI3):
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_SPIxEN[3]);
            break;
        case (SPI4):
            SET_FIELD(RCC_APB2ENR, RCC_APB2ENR_SPI4EN); // TODO: Can't find this field
            break;
        case (SPI5):
            SET_FIELD(RCC_APB2ENR, RCC_ABP2ENR_SPI5EN); // TODO: Can't find this field
            break;
        case (SPI6):
            SET_FIELD(RCC_ABP4ENR, RCC_ABP4ENR_SPI6EN); // TODO: Can't find this field
            break;
    }

    // Configure SPI Mode
    switch (config->mode) {
        case (SPI_MODE_0):
            CLR_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_CPOL);
            CLR_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_CPHA);
            break;
        case (SPI_MODE_1):
            CLR_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_CPOL);
            SET_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_CPHA);
            break;
        case (SPI_MODE_2):
            SET_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_CPOL);
            CLR_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_CPHA);
            break;
        case (SPI_MODE_3):
            SET_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_CPOL);
            SET_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_CPHA);
            break;
    }

    // Configure Baude Rate Prescaler
    switch (config->baudrate_prescaler) {
        case (SPI_BAUDRATE_PRESCALER_256):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_MBR, 0b111);
            break;
        case (SPI_BAUDRATE_PRESCALER_128):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_MBR, 0b110);
            break;
        case (SPI_BAUDRATE_PRESCALER_64):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_MBR, 0b101);
            break;
        case (SPI_BAUDRATE_PRESCALER_32):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_MBR, 0b100);
            break;
        case (SPI_BAUDRATE_PRESCALER_16):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_MBR, 0b011);
            break;
        case (SPI_BAUDRATE_PRESCALER_8):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_MBR, 0b010);
            break;
        case (SPI_BAUDRATE_PRESCALER_4):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_MBR, 0b001);
            break;
        case (SPI_BAUDRATE_PRESCALER_2):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_MBR, 0b000);
            break;
    }

    // Set the Data Frame Format
    switch (config->data_size) {
        case (SPI_DATA_SIZE_16BIT):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_DSIZE, 0b1111);
            break;
        case (SPI_DATA_SIZE_8BIT):
            WRITE_FIELD(SPIx_CFG1[config->instance], SPIx_CFG1_DSIZE, 0b111);
            break;
    }

    // Configure First Bit Transmitted
    switch (config->first_bit) {
        case (SPI_FIRST_BIT_LSB):
            SET_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_LSBFRST);
            break;
        case (SPI_FIRST_BIT_MSB):
            CLR_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_LSBFRST);
            break;
    }

    // Configure as master
    SET_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_MASTER);

    // Configure SPI software-NSS
    CLR_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_SSOE);
    CLR_FIELD(SPIx_CFG2[config->instance], SPIx_CFG2_SSM);

    // Enable the SPI
    SET_FIELD(SPIx_CR1[config->instance], SPIx_CR1_SPE);

    // Set up internal DMA tracking
    dma_periph_streaminfo_t info = {
        .rx_instance = rx_stream->instance,
        .tx_instance = tx_stream->instance,
        .rx_stream = rx_stream->stream,
        .tx_stream = tx_stream->stream
    };
    spi_to_dma[config->instance] = info;

    // TX stream configuration
    dma_config_t dma_tx_stream = {
        .instance = tx_stream->instance,
        .stream = tx_stream->stream,
        .request_id = spi_dmamux_req[config->instance][1],
        .direction = tx_stream->direction,
        .src_data_size = tx_stream->src_data_size,
        .dest_data_size = tx_stream->dest_data_size,
        .priority = tx_stream->priority,
        .fifo_enabled = false, // FIFO disabled for tx
        .fifo_threshold = tx_stream->fifo_threshold,
        .callback = callback, // We need to know if it failed.
    };
    dma_configure_stream(flag, &dma_tx_stream);

    // RX stream configuration
    dma_config_t dma_rx_stream = {
        .instance = rx_stream->instance,
        .stream = rx_stream->stream,
        .request_id = spi_dmamux_req[config->instance][0],
        .direction = rx_stream->direction,
        .src_data_size = tx_stream->src_data_size,
        .dest_data_size = tx_stream->dest_data_size,
        .priority = tx_stream->priority,
        .fifo_enabled = false, // FIFO disabled for tx
        .fifo_threshold = tx_stream->fifo_threshold,
        .callback = callback,
    };
    dma_configure_stream(flag, &dma_rx_stream);

}

bool spi_device_init(tal_flag_t *flag, spi_device_t *device) {
    // Enable GPIO port clock
    tal_enable_clock(device->gpio_pin);
    
    // Configure pin mode as output
    tal_set_mode(device->gpio_pin, 1);

    // Set up device context
    for (int i = 0; i < MAX_DEVICES_PER_INSTANCE; i++) {
        if (spi_context_arr[device->instance][i].device == NULL) {
            spi_context_arr[device->instance][i].device = device;
            spi_context_arr[device->instance][i].busy = &(spi_busy[device->instance]);
            break;
        }
    }

    // Set initial state
    tal_pull_pin(device->gpio_pin, 1);
    tal_set_pin(device->gpio_pin, 1);
}

 /**
  * @brief Writes data over SPI asyncronously
  * @param flag Error flag
  * @param device Spi device to use
  * @param source Pointer to source data
  * @param size Size of source data in bytes
  */
 bool spi_write_async(tal_flag_t *flag, spi_device_t *device, void *source, size_t size) {
    spi_instance_t instance = device->instance;
    // Check if SPI instance is available
    // TODO: make this an atomic operation with a mutex
    if (spi_busy[instance]) {
        tal_raise(flag, "SPI is busy");
        return false;
    }
    spi_busy[instance] = true;

    // Pull SS line low
    tal_set_pin(device->gpio_pin, 0);

    // Get context
    spi_context_t *context;
    for (int i = 0; i < MAX_DEVICES_PER_INSTANCE; i++) {
        if (spi_context_arr[instance][i].device->instance == device->instance &&
            spi_context_arr[instance][i].device->gpio_pin == device->gpio_pin) {
            context = &(spi_context_arr[instance][i]);
        }
    }
    // TODO: Check if context was initialized, return error if not.
    
    // TX Transfer
    dma_transfer_t tx_transfer = {
        .instance = spi_to_dma[instance].tx_instance,
        .stream = spi_to_dma[instance].tx_stream,
        .src = source,
        .dest = SPIx_TXDR[instance],
        .size = size,
        .context = context,
        .disable_mem_inc = false,
    };
    dma_start_transfer(flag, &tx_transfer);

    // TX Transfer
    uint8_t dummy_buffer;
    dma_transfer_t rx_transfer = {
        .instance = spi_to_dma[instance].rx_instance,
        .stream = spi_to_dma[instance].rx_stream,
        .src = SPIx_RXDR[instance],
        .dest = &dummy_buffer,
        .size = size,
        .context = context,
        .disable_mem_inc = true,
    };
    dma_start_transfer(flag, &rx_transfer);

    // Enable DMA requests
    SET_FIELD(SPIx_CFG1[instance], SPIx_CFG1_RXDMAEN);
    SET_FIELD(SPIx_CFG1[instance], SPIx_CFG1_TXDMAEN);

    return true;
 }

 /**
  * @brief Writes data over SPI asyncronously
  * @param flag Error flag
  * @param device Spi device to use
  * @param dest Pointer to rx data buffer
  * @param size Size of rx data in bytes
  */
 bool spi_read_async(tal_flag_t *flag, spi_device_t *device, void *dest, size_t size) {
    spi_instance_t instance = device->instance;
    // Check if SPI instance is available
    // TODO: make this an atomic operation with a mutex
    if (spi_busy[instance]) {
        tal_raise(flag, "SPI is busy");
        return false;
    }
    spi_busy[instance] = true;

    // Pull SS line low
    tal_set_pin(device->gpio_pin, 0);

    // Get context
    spi_context_t *context;
    for (int i = 0; i < MAX_DEVICES_PER_INSTANCE; i++) {
        if (spi_context_arr[instance][i].device->instance == device->instance &&
            spi_context_arr[instance][i].device->gpio_pin == device->gpio_pin) {
            context = &(spi_context_arr[instance][i]);
        }
    }
    // TODO: Check if context was initialized, return error if not.
    
    // TX Transfer
    uint8_t dummy_buffer;
    dma_transfer_t tx_transfer = {
        .instance = spi_to_dma[instance].tx_instance,
        .stream = spi_to_dma[instance].tx_stream,
        .src = &dummy_buffer,
        .dest = SPIx_TXDR[instance],
        .size = size,
        .context = context,
        .disable_mem_inc = true,
    };
    dma_start_transfer(flag, &tx_transfer);

    // TX Transfer
    dma_transfer_t rx_transfer = {
        .instance = spi_to_dma[instance].rx_instance,
        .stream = spi_to_dma[instance].rx_stream,
        .src = SPIx_RXDR[instance],
        .dest = dest,
        .size = size,
        .context = context,
        .disable_mem_inc = false,
    };
    dma_start_transfer(flag, &rx_transfer);

    // Enable DMA requests
    SET_FIELD(SPIx_CFG1[instance], SPIx_CFG1_RXDMAEN);
    SET_FIELD(SPIx_CFG1[instance], SPIx_CFG1_TXDMAEN);

    return true;
 }

bool spi_write_blocking(tal_flag_t *flag, spi_device_t *device, void *source, size_t size) {
    // Parameter validation
    if (flag == NULL || source == NULL || size == 0) {
        tal_raise(flag, "Invalid parameters for spi_write_blocking");
        return false;
    }

    spi_instance_t instance = device->instance;
    if (spi_busy[instance]) {
        tal_raise(flag, "SPI is busy");
        return false;
    }
    spi_busy[instance] = true;

    uint8_t *tx_data = (uint8_t *)source;

    // Pull SS line low to select the device
    tal_set_pin(device->gpio_pin, 0);

    // Dummy variable to hold received data
    uint8_t dummy_rx_data;

    // Loop through each byte of the data to transmit
    for (size_t i = 0; i < size; ++i) {
        // Wait for the TX buffer to be empty before writing the next byte.
        // This is the correct flag to check inside a byte-by-byte loop.
        while (!(READ_FIELD(SPIx_SR[instance], SPIx_SR_TXP)));

        // Write the data to the SPI data register.
        // This automatically starts the transfer.
        *SPIx_TXDR[instance] = tx_data[i];

        // Wait for the RX buffer to receive data.
        // This is a blocking read to prevent a receive buffer overrun.
        while (!(READ_FIELD(SPIx_SR[instance], SPIx_SR_RXP)));

        // Read the dummy data from the RX register to clear the RXNE flag
        // and prepare for the next incoming byte.
        dummy_rx_data = *((uint8_t *)SPIx_RXDR[instance]);
    }

    // Wait for the entire transmission to be completed.
    // The TXC flag is the correct one to check for this.
    while (!(READ_FIELD(SPIx_SR[instance], SPIx_SR_TXC)));

    // Pull SS line high to deselect the device
    tal_set_pin(device->gpio_pin, 1);

    spi_busy[instance] = false;
    return true;
 }

 bool spi_read_blocking(tal_flag_t *flag, spi_device_t *device, void *dest, size_t size) {
  // Parameter validation
    if (flag == NULL || dest == NULL || size == 0) {
        tal_raise(flag, "Invalid parameters for spi_read_blocking");
        return false;
    }

    // Check if SPI instance is busy
    spi_instance_t instance = device->instance;
    if (spi_busy[instance]) {
        tal_raise(flag, "SPI is busy");
        return false;
    }
    spi_busy[instance] = true;

    uint8_t *rx_data = (uint8_t *)dest;

    // Pull SS line low to select the device
    tal_set_pin(device->gpio_pin, 0);

    // Loop through each byte to receive.
    for (size_t i = 0; i < size; ++i) {
        // Wait for the TxFIFO to have at least one empty slot before writing the next byte.
        // This is crucial for a read, as we must send a dummy byte to clock the slave.
        while (!(READ_FIELD(SPIx_SR[instance], SPIx_SR_TXP)));

        // Write a dummy byte to the SPI data register to start the transfer.
        // The value (e.g., 0xFF) does not matter for the slave's response.
        *SPIx_TXDR[instance] = 0xFF;

        // Wait for the RxFIFO to have data.
        // The RXP (Rx-Packet) flag is the correct one to check for this.
        while (!(READ_FIELD(SPIx_SR[instance], SPIx_SR_RXP)));
        
        // Read the valid data from the RX register and store it in the destination buffer.
        rx_data[i] = *SPIx_RXDR[instance];
    }

    // Wait for the entire transmission of the last dummy byte to be completed.
    // The TXC flag is the correct one to check for this.
    while (!(READ_FIELD(SPIx_SR[instance], SPIx_SR_TXC)));

    // Pull SS line high to deselect the device
    tal_set_pin(device->gpio_pin, 1);
    spi_busy[instance] = false;
    return true;
 }