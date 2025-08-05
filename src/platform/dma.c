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
 * @file src/platform/dma.c
 * @authors Charles Faisandier
 * @brief DMA driver implementation.
 */
#include "tal/error.h"
#include "platform/dma.h"
#include "platform/mmio.h"
#include "platform/spi.h"

/**************************************************************************************************
 * @section Internal Data Structures
 **************************************************************************************************/
// Data structure to store DMA callbacks
dma_callback_t dma_callbacks[DMA_INSTANCE_COUNT][DMA_STREAM_COUNT] = {0};

// Data structure to store DMA callback context
void *dma_callback_context[DMA_INSTANCE_COUNT][DMA_STREAM_COUNT] = {0};

// Data structure to store which streams are configured
bool dma_streams_configured[DMA_INSTANCE_COUNT][DMA_STREAM_COUNT] = {0};

// Keeps track of interrupt numbers for DMA events
int32_t dma_irq_numbers[DMA_INSTANCE_COUNT][DMA_STREAM_COUNT] = {
    [DMA1] = {
        [DMA_STREAM_0] = 11,
        [DMA_STREAM_1] = 12,
        [DMA_STREAM_2] = 13,
        [DMA_STREAM_3] = 14,
        [DMA_STREAM_4] = 15,
        [DMA_STREAM_5] = 16,
        [DMA_STREAM_6] = 17,
        [DMA_STREAM_7] = 47,
    },
    [DMA2] = {
        [DMA_STREAM_0] = 56,
        [DMA_STREAM_1] = 57,
        [DMA_STREAM_2] = 58,
        [DMA_STREAM_3] = 59,
        [DMA_STREAM_4] = 60,
        [DMA_STREAM_5] = 68,
        [DMA_STREAM_6] = 69,
        [DMA_STREAM_7] = 70,
    }
};

// Simplifies finding the correct DMA stream control register
static volatile rw_reg32_t dma_cr_map[3][8] = {
    [DMA1] = {
        [DMA_STREAM_0] = DMAx_S0CR[1],
        [DMA_STREAM_1] = DMAx_S1CR[1],
        [DMA_STREAM_2] = DMAx_S2CR[1],
        [DMA_STREAM_3] = DMAx_S3CR[1],
        [DMA_STREAM_4] = DMAx_S4CR[1],
        [DMA_STREAM_5] = DMAx_S5CR[1],
        [DMA_STREAM_6] = DMAx_S6CR[1],
        [DMA_STREAM_7] = DMAx_S7CR[1],
    },
    [DMA2] = {
        [DMA_STREAM_0] = DMAx_S0CR[2],
        [DMA_STREAM_1] = DMAx_S1CR[2],
        [DMA_STREAM_2] = DMAx_S2CR[2],
        [DMA_STREAM_3] = DMAx_S3CR[2],
        [DMA_STREAM_4] = DMAx_S4CR[2],
        [DMA_STREAM_5] = DMAx_S5CR[2],
        [DMA_STREAM_6] = DMAx_S6CR[2],
        [DMA_STREAM_7] = DMAx_S7CR[2],
    }
};

// Field that writes to the whole register.
static field32_t FULL_REGISTER;


/**************************************************************************************************
 * @section Private Functions
 **************************************************************************************************/
// Sanity check for DMA configuration
inline static bool check_config_valid(tal_flag_t *flag, const dma_config_t* config) {
    if (config == NULL) {
        tal_raise(flag, "DMA configuration is NULL");
        return false;
    }
    if (config->instance < DMA_INSTANCE_MIN || config->instance >= DMA_INSTANCE_COUNT) {
        tal_raise(flag, "Invalid DMA instance");
        return false;
    }
    if (config->stream < DMA_STREAM_MIN || config->stream >= DMA_STREAM_COUNT) {
        tal_raise(flag, "Invalid DMA stream");
        return false;
    }
    if (config->direction < DMA_DIRECTION_MIN || config->direction >= DMA_DIR_COUNT) {
        tal_raise(flag, "Invalid DMA direction");
        return false;
    }
    if (config->src_data_size < DMA_DATA_SIZE_MIN || config->src_data_size >= DMA_DATA_SIZE_COUNT) {
        tal_raise(flag, "Invalid DMA source data size");
        return false;
    }
    if (config->dest_data_size < DMA_DATA_SIZE_MIN || config->dest_data_size >= DMA_DATA_SIZE_COUNT) {
        tal_raise(flag, "Invalid DMA destination data size");
        return false;
    }
    if (config->priority < DMA_PRIORITY_MIN || config->priority >= DMA_PRIORITY_COUNT) {
        tal_raise(flag, "Invalid DMA priority");
        return false;
    }
    if (config->fifo_threshold < DMA_FIFO_THRESHOLD_MIN || config->fifo_threshold >= DMA_FIFO_THRESHOLD_COUNT) {
        tal_raise(flag, "Invalid DMA FIFO threshold");
        return false;
    }
    if (dma_streams_configured[config->instance][config->stream]) {
        tal_raise(flag, "DMA stream is already configured");
        return false;
    }
        return true;
}

inline static void clear_stream_interrupts(dma_instance_t instance, dma_stream_t stream) {
    if (stream < DMA_STREAM_4) {
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
inline static uint32_t get_data_size_bits(dma_data_size_t size) {
    switch (size) {
        case DMA_DATA_SIZE_BYTE:
            return 0b00;
        case DMA_DATA_SIZE_HALFWORD:
            return 0b01;
        case DMA_DATA_SIZE_WORD:
            return 0b10;
    }
}

// Helper function to convert the bit value to a byte count
inline static uint32_t get_size_in_bytes(uint32_t bits) {
    if (bits == 0b00) return 1;
    if (bits == 0b01) return 2;
    if (bits == 0b10) return 4;
    return 0; // Invalid size
}

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/
/**
 * @brief Initializes the DMA subsystem (enables clocks for all DMA controllers).
 * Should be called once during system boot.
 */
tal_err_t *dma_init(void) {
    // Enable clocks for DMA1, DMA2, and DMAMUX
    SET_FIELD(RCC_AHB1ENR, RCC_AHB1ENR_DMA1EN); // TODO: I can't find this field in our mmio.h
    SET_FIELD(RCC_AHB1ENR, RCC_AHB1ENR_DMA2EN); // TODO: I can't find this field in our mmio.h
    // TODO: I'm not sure how to enable the DMAMUX clock
    SET_FIELD(RCC_D3AMR, RCC_D3AMR_BDMAAMEN);  // D3 System Autonomous Mode Register for DMAMUX

    // Software reset the DMA controllers (nice for debugging)
    SET_FIELD(RCC_AHB1RSTR, RCC_AHB1RSTR_DMAxRST[1]);
    CLR_FIELD(RCC_AHB1RSTR, RCC_AHB1RSTR_DMAxRST[1]); // Clear DMA1 reset
    SET_FIELD(RCC_AHB1RSTR, RCC_AHB1RSTR_DMAxRST[2]);
    CLR_FIELD(RCC_AHB1RSTR, RCC_AHB1RSTR_DMAxRST[2]); // Clear DMA2 reset

    // Clear all DMA Interrupts
    CLEAR_REGISTER(DMAx_LIFCR[1]); // Clear DMA1 low interrupt flags
    CLEAR_REGISTER(DMAx_HIFCR[1]); // Clear DMA1 high interrupt flags
    CLEAR_REGISTER(DMAx_LIFCR[2]); // Clear DMA2 low interrupt flags
    CLEAR_REGISTER(DMAx_HIFCR[2]); // Clear DMA2 high interrupt flags   

    // Initialize fields.
    FULL_REGISTER = MAKE_FIELD(field32_t, 0, 32); // Assuming 'm0a' is a 32-bit field starting at position 0
}

/**
 * @brief Configures a specific DMA stream to a specific request ID, and enables it.
 * This allocates and sets up the chosen stream based on the provided configuration.
 * @param config Pointer to the configuration structure.
 * @param flag Pointer to the flag structure for error handling.
 */
bool dma_configure_stream(tal_flag_t *flag, const dma_config_t* config) {
    // Validate the parameters
    if (flag == NULL)
        return false;
    if (!check_config_valid(flag, config)) return false;
    
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
    if (config->priority == DMA_PRIORITY_LOW) {
        WRITE_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_PL, 0b00);
    } else if (config->priority == DMA_PRIORITY_MEDIUM) {
        WRITE_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_PL, 0b01);
    } else if (config->priority == DMA_PRIORITY_HIGH) {
        WRITE_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_PL, 0b10);
    } else if (config->priority == DMA_PRIORITY_VERY_HIGH) {
        WRITE_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_PL, 0b11);
    }

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
    } else if (config->direction == MEM_TO_MEM) {
        WRITE_FIELD(dma_cr_map[config->instance][config->stream], DMAx_SxCR_DIR, 0b10); // Memory to memory
    }

    // Configure the request ID of the channel in the DMAMUX
    WRITE_FIELD(DMAMUXx_CxCR[config->instance][config->stream], DMAMUXx_CxCR_DMAREQ_ID, config->request_id);

    // Enable the IRQ for the DMA stream (in the NVIC)
    set_irq_enabled(dma_irq_numbers[config->instance][config->stream], true);

    dma_streams_configured[config->instance][config->stream] = true;
}

/** 
 * @brief Starts a DMA transfer for the specified stream.
 * This function initiates the transfer based on the previously configured settings.
 * @param instance The DMA instance (DMA1, DMA2, MDMA, BDMA).
 * @param stream The specific stream to start.
 * @param src Pointer to the source data buffer.
 * @param dest Pointer to the destination data buffer.
 * @param size Number of bytes to transfer.
 */
bool dma_start_transfer(tal_flag_t *flag, dma_instance_t instance, dma_stream_t stream, const void* src, void* dest, size_t size, void *context) {
    // Check parameters
    if (flag == NULL)
        return false;
    if (instance < DMA_INSTANCE_MIN || instance >= DMA_INSTANCE_COUNT) {
        tal_raise(flag, "Invalid DMA instance");
        return false;
    }
    if (stream < DMA_STREAM_MIN || stream >= DMA_STREAM_COUNT) {
        tal_raise(flag, "Invalid DMA stream");
        return false;
    }
    if (src == NULL) {
        tal_raise(flag, "Invalid source pointer");
        return false;
    }
    if (dest == NULL) {
        tal_raise(flag, "Invalid destination pointer");
        return false;
    }
    
    // Configure callback context
    dma_callback_context[instance][stream] = context;

    // Clear interrupt flags from pervious transfers
    clear_stream_interrupts(instance, stream);
    
    // Disable stream, wait until fully disabled
    CLR_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_EN);
    while (READ_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_EN));

    // Configure dynamic transfer parameters (source, destination, size)
    dma_data_size_t src_datasize;
    dma_direction_t stream_dir = READ_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_DIR);
    if (stream_dir == 0b00) // Peripheral to memory
        src_datasize = READ_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_PSIZE );
    else 
        src_datasize = READ_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_MSIZE );
    
    WRITE_FIELD(DMAx_SxNDTR[instance][stream], DMAx_SxNDTR_NDT, size / get_size_in_bytes(src_datasize));

    if (stream_dir == 0b00) {
        WRITE_FIELD(DMAx_SxPAR[instance][stream], FULL_REGISTER, src);
        WRITE_FIELD(DMAx_SxM0AR[instance][stream], FULL_REGISTER, dest);
    } else {
        WRITE_FIELD(DMAx_SxM0AR[instance][stream], FULL_REGISTER, src);
        WRITE_FIELD(DMAx_SxPAR[instance][stream], FULL_REGISTER, dest);
    }

    // Enable the stream
    SET_FIELD(dma_cr_map[instance][stream], DMAx_SxCR_EN);
}

// Interrupt handler example (success or error)
void irq_9_handler(void) { // Handler for DMA1 Stream 1 (for example)
    // Trigger the callback
    dma_callbacks[DMA1][DMA_STREAM_1](true, (void *) dma_callback_context[DMA1][DMA_STREAM_1]); // False for error

    // Disable the stream and clear the dynamic parameters.
    CLR_FIELD(dma_cr_map[DMA1][DMA_STREAM_1], DMAx_SxCR_EN);
    CLR_FIELD(DMAx_SxPAR[DMA1][DMA_STREAM_1], FULL_REGISTER);
    CLR_FIELD(DMAx_SxM0AR[DMA1][DMA_STREAM_1], FULL_REGISTER);
    CLR_FIELD(DMAx_SxNDTR[DMA1][DMA_STREAM_1], DMAx_SxNDTR_NDT);
}
