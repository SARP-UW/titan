/**
 * This file is part of the Titan Library.
 * Copyright (c) 2025 UW SARP
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
 * @internal
 * @file modules/mcu/src/dma.c
 * @authors Charles Faisandier
 * @brief DMA driver implementation.
 */
#include "util/errc.h"
#include "mcu/dma.h"
#include "mcu/mmio.h"
#include "mcu/spi.h"
// #include "mcu/uart.h"
#include "kernel/mutex.h"

/**************************************************************************************************
 * @section Internal Type Definitions
 **************************************************************************************************/
typedef struct {
    uint8_t instance;
    uint8_t stream;
} dma_info_t;

// Configuration structure for a DMA stream
typedef struct {
    uint8_t   instance;      // 1, 2, MDMA
    uint8_t     stream;        // Specific stream/channel (0-7 for 1/2)
    uint32_t         request_id;    // DMAMUX request ID for peripheral (if applicable, e.g., DMA_REQUEST_USART1_TX)
    dma_direction_t  direction;
    uint8_t  src_data_size; // Source data width
    uint8_t  dest_data_size; // Destination data width
    uint8_t   priority;
    bool             fifo_enabled;   // Generally disabled for sending instructions to peripherals,
                                        // but enabled for high-throughput transfers
    dma_fifo_threshold_t fifo_threshold; // FIFO threshold for 1/2 (e.g., DMA_FIFO_THRESHOLD_FULL)
    // Callback for this stream
    dma_callback_t   callback;
} dma_stream_config_t;

// Mutexes
struct ti_mutex_t mutex[DMA_INSTANCE_COUNT + 1][DMA_STREAM_COUNT];

/**************************************************************************************************
 * @section Internal Data Structures
 **************************************************************************************************/
// Data structure to store DMA callbacks
dma_callback_t dma_callbacks[DMA_INSTANCE_COUNT][DMA_STREAM_COUNT] = {0};

// Data structure to store DMA callback context
void *dma_callback_context[DMA_INSTANCE_COUNT][DMA_STREAM_COUNT] = {0};

// Keeps track of interrupt numbers for DMA events
int32_t volatile dma_irq_numbers[DMA_INSTANCE_COUNT + 1][DMA_STREAM_COUNT] = {
    [1] = {
        [0] = 11,
        [1] = 12,
        [2] = 13,
        [3] = 14,
        [4] = 15,
        [5] = 16,
        [6] = 17,
        [7] = 47,
    },
    [2] = {
        [0] = 56,
        [1] = 57,
        [2] = 58,
        [3] = 59,
        [4] = 60,
        [5] = 68,
        [6] = 69,
        [7] = 70,
    }
};

// Simplifies finding the correct DMA stream control register
static rw_reg32_t dma_cr_map[DMA_INSTANCE_COUNT + 1][DMA_STREAM_COUNT] = {
    [1] = {
        [0] = DMAx_S0CR[1],
        [1] = DMAx_S1CR[1],
        [2] = DMAx_S2CR[1],
        [3] = DMAx_S3CR[1],
        [4] = DMAx_S4CR[1],
        [5] = DMAx_S5CR[1],
        [6] = DMAx_S6CR[1],
        [7] = DMAx_S7CR[1],
    },
    [2] = {
        [0] = DMAx_S0CR[2],
        [1] = DMAx_S1CR[2],
        [2] = DMAx_S2CR[2],
        [3] = DMAx_S3CR[2],
        [4] = DMAx_S4CR[2],
        [5] = DMAx_S5CR[2],
        [6] = DMAx_S6CR[2],
        [7] = DMAx_S7CR[2],
    }
};

/**************************************************************************************************
 * @section Private Functions
 **************************************************************************************************/
inline static void clear_stream_interrupts(uint8_t instance, uint8_t stream) {
    if (stream < 4) {
        CLR_FIELD(DMAx_LIFCR[instance], DMAx_LIFCR_CTCIFx[stream]);
        CLR_FIELD(DMAx_LIFCR[instance], DMAx_LIFCR_CHTIFx[stream]);
        CLR_FIELD(DMAx_LIFCR[instance], DMAx_LIFCR_CTEIFx[stream]);
        CLR_FIELD(DMAx_LIFCR[instance], DMAx_LIFCR_CDMEIFx[stream]);
        CLR_FIELD(DMAx_LIFCR[instance], DMAx_LIFCR_CFEIFx[stream]);
    } else {
        // TODO: Fields for HIFCR do not exist in mmio.h (using LIFCR which is the exact same)
        CLR_FIELD(DMAx_HIFCR[instance], DMAx_LIFCR_CTCIFx[stream]);
        CLR_FIELD(DMAx_HIFCR[instance], DMAx_LIFCR_CHTIFx[stream]);
        CLR_FIELD(DMAx_HIFCR[instance], DMAx_LIFCR_CTEIFx[stream]);
        CLR_FIELD(DMAx_HIFCR[instance], DMAx_LIFCR_CDMEIFx[stream]);
        CLR_FIELD(DMAx_HIFCR[instance], DMAx_LIFCR_CFEIFx[stream]);
    }
}

// A helper function to map the enum to the register value
inline static uint32_t get_data_size_bits(uint8_t size) {
    switch (size) {
        case 1:
            return 0b00;
        case 2:
            return 0b01;
        case 4:
            return 0b10;
    }
}

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
/**
 * @brief Initializes the DMA subsystem (enables clocks for all DMA controllers).
 * Should be called once during system boot.
 */
void dma_init() {
    // Enable clocks for 1, 2, and DMAMUX
    SET_FIELD(RCC_AHB1ENR, RCC_AHB1ENR_1EN); // TODO: I can't find this field in our mmio.h
    SET_FIELD(RCC_AHB1ENR, RCC_AHB1ENR_2EN); // TODO: I can't find this field in our mmio.h
    // TODO: I'm not sure how to enable the DMAMUX clock
    SET_FIELD(RCC_D3AMR, RCC_D3AMR_BDMAAMEN);  // D3 System Autonomous Mode Register for DMAMUX

    // Software reset the DMA controllers (nice for debugging)
    SET_FIELD(RCC_AHB1RSTR, RCC_AHB1RSTR_DMAxRST[1]);
    CLR_FIELD(RCC_AHB1RSTR, RCC_AHB1RSTR_DMAxRST[1]); // Clear 1 reset
    SET_FIELD(RCC_AHB1RSTR, RCC_AHB1RSTR_DMAxRST[2]);
    CLR_FIELD(RCC_AHB1RSTR, RCC_AHB1RSTR_DMAxRST[2]); // Clear 2 reset

    // Clear all DMA Interrupts
    CLEAR_REGISTER(DMAx_LIFCR[1]); // Clear 1 low interrupt flags
    CLEAR_REGISTER(DMAx_HIFCR[1]); // Clear 1 high interrupt flags
    CLEAR_REGISTER(DMAx_LIFCR[2]); // Clear 2 low interrupt flags
    CLEAR_REGISTER(DMAx_HIFCR[2]); // Clear 2 high interrupt flags   

    // Create mutexes
    for (int i = 1; i <= DMA_INSTANCE_COUNT; i++) {
        for (int j = 0; j < DMA_STREAM_COUNT; j++) {
            ti_create_mutex(&mutex[i][j]);
        }
    }
}

/**
 * @brief Configures a specific DMA stream to a specific request ID, and enables it.
 * This allocates and sets up the chosen stream based on the provided configuration.
 * @param config Pointer to the configuration structure.
 * @param flag Pointer to the flag structure for error handling.
 */
int dma_configure_stream(const dma_stream_config_t* config) {
    // Validate the parameters
    if (!check_config_valid( config)) return TI_ERRC_INVALID_ARG;
    
    // register and context callback
    dma_callbacks[config->instance][config->stream] = config->callback;

    // Disable the stream before configuration
    CLR_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_EN);

    // Wait for the stream to be fully disabled
    while (READ_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_EN));

    // Clear whole DMA stream configuration register
    CLEAR_REGISTER(dma_cr_map[config->instance][config->stream]);

    // Enable memory increment (ensures dma moves through source buffer)
    SET_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_MINC);

    // Disable peripheral increment (we don't want to increment peripheral registers)
    CLR_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_PINC);

    // Enable transfer complete/error interrupts
    SET_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_TCIE);
    SET_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_TEIE);

    // set source and destination data sizes
    field32_t src_datasize_field;
    field32_t dest_datasize_field;
    if (config->direction == MEM_TO_PERIPH) {
        src_datasize_field = DMAx_SxCR_MSIZE;
        dest_datasize_field = DMAx_SxCR_PSIZE;
    } else {
        src_datasize_field = DMAx_SxCR_PSIZE;
        dest_datasize_field = DMAx_SxCR_MSIZE;
    }
    WRITE_FIELD(dma_cr_map[config->instance][config->stream], src_datasize_field, get_data_size_bits(config->src_data_size)); 
    WRITE_FIELD(dma_cr_map[config->instance][config->stream], dest_datasize_field, get_data_size_bits(config->dest_data_size)); 

    // Set priority level
    WRITE_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_PL, config->priority);

    // Set FIFO mode and threshold if applicable
    if (config->fifo_enabled) {
        SET_FIELD(DMAx_SxFCR[config->instance][config->stream], DMAx_SxFCR_DMDIS);
        if (config->fifo_threshold == DMA_FIFO_THRESHOLD_FULL) {
            WRITE_FIELD(DMAx_SxFCR[config->instance][config->stream], DMAx_SxFCR_FTH, 0b11); // Full
        } else if (config->fifo_threshold == DMA_FIFO_THRESHOLD_THREEQUARTERS) {
            WRITE_FIELD(DMAx_SxFCR[config->instance][config->stream], DMAx_SxFCR_FTH, 0b10); // Three-quarters
        } else if (config->fifo_threshold == DMA_FIFO_THRESHOLD_HALF) {
            WRITE_FIELD(DMAx_SxFCR[config->instance][config->stream], DMAx_SxFCR_FTH, 0b01); // Half
        } else if (config->fifo_threshold == DMA_FIFO_THRESHOLD_QUARTER) {
            WRITE_FIELD(DMAx_SxFCR[config->instance][config->stream], DMAx_SxFCR_FTH, 0b00); // Quarter
        }
    } else {
        CLR_FIELD(DMAx_SxFCR[config->instance][config->stream], DMAx_SxFCR_DMDIS);
    }

    // Set stream direction
    if (config->direction == PERIPH_TO_MEM) {
        WRITE_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_DIR, 0b00); // Peripheral to memory
    } else if (config->direction == MEM_TO_PERIPH) {
        WRITE_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_DIR, 0b01); // Memory to peripheral
    }

    // Configure the request ID of the channel in the DMAMUX
    int dmamux_channel = ((config->instance - 1) * 7) + config->stream;
    WRITE_FIELD(DMAMUX1_CxCR[dmamux_channel], DMAMUXx_CxCR_DMAREQ_ID, config->request_id);

    // Enable the IRQ for the DMA stream (in the NVIC)
    set_irq_enabled(dma_irq_numbers[config->instance][config->stream], true);

    return TI_ERRC_NONE;
}

/** 
 * @brief Starts a DMA transfer for the specified stream.
 * This function initiates the transfer based on the previously configured settings.
 * @param instance The DMA instance (1, 2, MDMA, BDMA).
 * @param stream The specific stream to start.
 * @param src Pointer to the source data buffer.
 * @param dest Pointer to the destination data buffer.
 * @param size Number of bytes to transfer.
 */
int dma_start_transfer(dma_transfer_t *dma_transfer) {
    // TODO: Parameter checking
    // Find an available instance/stream and aquire mutex
    dma_info_t dma_info = {0};
    for (int i = 1; i <= DMA_INSTANCE_COUNT; i++) {
        for (int j = 0; j <= DMA_STREAM_COUNT; j++) {
            if (!ti_is_mutex_locked(mutex[i][j])) {
                ti_acquire_mutex(mutex[i][j], 0);
                dma_info.stream = j;
                dma_info.instance = i;
            }
        }
    }
    if (dma_info.instance == 0)
        return TI_ERRC_DMA_NO_AVAIL_STREAM;

    dma_stream_config_t stream_config = {
        .instance = dma_info.instance,
        .stream = dma_info.stream,
        .request_id = dma_transfer->request_id,
        .direction = dma_transfer->direction,
        .src_data_size = dma_transfer->src_data_size,
        .dest_data_size = dma_transfer->dest_data_size,
        .priority = dma_transfer->priority,
        .fifo_enabled = dma_transfer->fifo_enabled,
        .fifo_threshold = dma_transfer->fifo_threshold,
        .callback = dma_transfer->callback,
    };
    int errc = dma_configure_stream(&stream_config);
    if (errc)
        return errc;

    uint8_t instance = dma_info.instance;
    uint8_t stream = dma_info.stream;
    void *src = dma_transfer->src;
    void *dest = dma_transfer->dest;

    // Configure callback context
    dma_callback_context[instance][stream] = dma_transfer->context;

    // Clear interrupt flags from pervious transfers
    clear_stream_interrupts(instance, stream);
    
    // Disable stream, wait until fully disabled
    CLR_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_EN);
    while (READ_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_EN));

    // Configure dynamic transfer parameters (source, destination, size)
    WRITE_FIELD(DMAx_SxNDTR[instance][stream], DMAx_SxNDTR_NDT, dma_transfer->size / dma_transfer->src_data_size);

    *DMAx_SxPAR[instance][stream] = dest;
    *DMAx_SxM0AR[instance][stream] = src;

    // Disable memory incrementation if specified
    if (dma_transfer->disable_mem_inc) {
        CLR_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_MINC);
    }

    // Enable the stream
    SET_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_EN);
    return TI_ERRC_NONE;
}


// SPI Interrupt handler example
void irq_9_handler(void) { // Handler for 1 Stream 1 (for example)
    // Disable the stream and clear the dynamic parameters.
    CLR_FIELD(dma_cr_map[1][1], DMAx_SxCR_EN);
    *DMAx_SxM0AR[1][1] = 0;
    *DMAx_SxPAR[1][1] = 0;
    CLR_FIELD(DMAx_SxNDTR[1][1], DMAx_SxNDTR_NDT);
    ti_release_mutex(mutex[1][1]);
    set_irq_disabled(dma_irq_numbers[1][1], true);

    // Trigger the callback
    dma_callbacks[1][1](true, (void *) dma_callback_context[1][1]); // False for error
}

// WRONG: Keeping for reference until UART is fixed
// UART Interrupt handler example
void irq_10_handler(void) {
    // Disable the stream and clear the dynamic parameters.
    CLR_FIELD(dma_cr_map[1][2], DMAx_SxCR_EN);
    *DMAx_SxM0AR[1][2] = 0;
    *DMAx_SxPAR[1][2] = 0;
    CLR_FIELD(DMAx_SxNDTR[1][2], DMAx_SxNDTR_NDT);

    // De-init uart dma transactio
    // uart_context_t *context = dma_callback_context[1][2];
    // CLR_FIELD(UARTx_CRx[context->channel][3], UARTx_CR3_DMAT);
    // context->busy = false;
}

// WRONG: Keeping for reference until I2C is fixed
// I2C Interrupt handler example
void irq_11_handler(void) {
    // Disable the stream and clear the dynamic parameters.
    CLR_FIELD(dma_cr_map[1][3], DMAx_SxCR_EN);
    *DMAx_SxM0AR[1][3] = 0;
    *DMAx_SxPAR[1][3] = 0;
    CLR_FIELD(DMAx_SxNDTR[1][3], DMAx_SxNDTR_NDT);

    // De-init uart dma transactio
    bool *i2c_busy = dma_callback_context[1][3];
    *(i2c_busy) = false;
}