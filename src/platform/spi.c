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

/**************************************************************************************************
 * @section Internal Data Structures
 **************************************************************************************************/

// Used to know what DMA RX/TX Instance/Streams belong to what SPI instances
typedef struct {
    dma_instance_t rx_instance; // TODO: Perhaps simplify this so only one instance
    dma_instance_t tx_instance;
    dma_stream_t rx_stream;
    dma_stream_t tx_stream;
} spi_streaminfo_t;
volatile spi_streaminfo_t spi_to_dma[SPI_INSTANCE_COUNT] = {0};

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

volatile bool transfer_complete = false;

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

inline static bool check_spi_dma_config_validity(tal_flag_t *flag, spi_dma_config_t *dma_config) {
    if (dma_config == NULL) {
        tal_set_err(flag, "SPI_DMA_CONFIG_ERROR: DMA config pointer is NULL");
        return false;
    }
    if (dma_config->instance < 0 || dma_config->instance >= DMA_INSTANCE_COUNT) {
        tal_set_err(flag, "SPI_DMA_CONFIG_ERROR: Invalid DMA instance");
        return false;
    }
    if (dma_config->stream < 0 || dma_config->stream >= DMA_STREAM_COUNT) {
        tal_set_err(flag, "SPI_DMA_CONFIG_ERROR: Invalid DMA stream");
        return false;
    }
    if (dma_config->direction < 0 || dma_config->direction >= DMA_DIR_COUNT ) {
        tal_set_err(flag, "SPI_DMA_CONFIG_ERROR: Invalid DMA direction");
        return false;
    }
    if (dma_config->src_data_size < 0 || dma_config->src_data_size >= DMA_DATA_SIZE_COUNT) {
        tal_set_err(flag, "SPI_DMA_CONFIG_ERROR: Invalid source data size");
        return false;
    }
    if (dma_config->dest_data_size < 0 || dma_config->dest_data_size >= DMA_DATA_SIZE_COUNT) {
        tal_set_err(flag, "SPI_DMA_CONFIG_ERROR: Invalid destination data size");
        return false;
    }
    if (dma_config->priority < 0 || dma_config->priority >= DMA_PRIORITY_COUNT) {
        tal_set_err(flag, "SPI_DMA_CONFIG_ERROR: Invalid DMA priority");
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
bool spi_init(tal_flag_t *flag, spi_config_t *config, dma_callback_t callback, spi_dma_config_t *tx_stream, spi_dma_config_t *rx_stream) {
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
    spi_streaminfo_t info = {
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
    gpio_port_t port = port_index_from_pin[device->gpio_pin] / 100;
    switch (port) {
        case (GPIO_PORT_A): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOAEN);
            break;
        case (GPIO_PORT_B): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOBEN);
            break;
        case (GPIO_PORT_C): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOCEN);
            break;
        case (GPIO_PORT_D): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIODEN);
            break;
        case (GPIO_PORT_E): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOEEN);
            break;
        case (GPIO_PORT_F): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOFEN);
            break;
        case (GPIO_PORT_G): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOGEN);
            break;
        case (GPIO_PORT_H): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOHEN);
            break;
        case (GPIO_PORT_I): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOIEN);
            break;
        case (GPIO_PORT_J): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOJEN);
            break;
        case (GPIO_PORT_K): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOKEN);
            break;
    }
    // Configure pin mode as output
    tal_set_mode(device->gpio_pin, 1);

    // Set initial state
    tal_pull_pin(device->gpio_pin, 1);
    tal_set_pin(device->gpio_pin, 1);
}

/**
 * @brief Transmit data over SPI, receives a command through tx_data, and stores the response in rx_data.
 * @param flag Pointer to the flag structure
 * @param instance The SPI instance to use
 * @param tx_data Pointer to the data to transmit
 * @param rx_data Pointer to the buffer for received data
 * @param length The length of the data to transmit
 */
 void spi_transmit(tal_flag_t *flag, spi_transfer_t *transfer) {
    // Reset flag to prepare for new transfer
    transfer_complete = false;
    // Assert the CS pin for the specified device
    tal_set_pin(transfer->device->gpio_pin, 0);

    spi_instance_t cur_instance = transfer->device->instance;
    // Start TX transfer
    // TODO: Figure out command register
    rw_reg32_t command_reg = SPIx_TXDR[transfer->device->instance];
    dma_start_transfer(flag, spi_to_dma[cur_instance].tx_instance,
                       spi_to_dma[cur_instance].tx_stream, transfer->tx_data,
                       command_reg, transfer->size, (void *) transfer->device);
    
    // Start RX Transfer
    // TODO: Figure out data register
    rw_reg32_t data_reg = SPIx_RXDR[transfer->device->instance];
    dma_start_transfer(flag, spi_to_dma[cur_instance].rx_instance,
                       spi_to_dma[cur_instance].rx_stream, data_reg,
                       transfer->rx_data, transfer->size, (void *) transfer->device);
                       // ^ TODO: Verify transfer->size

    // Enable DMA requests (SPI CR Register)
    SET_FIELD(SPIx_CFG1[transfer->device->instance], SPIx_CFG1_RXDMAEN);
    SET_FIELD(SPIx_CFG1[transfer->device->instance], SPIx_CFG1_TXDMAEN);

    // Wait for transfer to be complete
    while (!transfer_complete);

    // De-assert CS pin
    tal_set_pin(transfer->device->gpio_pin, 1);
 }