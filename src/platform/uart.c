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
 * @file common/platform/usart.h /// @todo UPDATE THIS
 * @authors Charles Faisandier, Joanna Zhou
 * @brief USART Driver Implementation
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "platform/mmio.h"
#include "platform/gpio.h"
#include "platform/uart.h"
#include "platform/clk.h"

#define CR_REG_COUNT 3
#define NUM_REQUESTS_PER_UART 2

#define IS_USART_CHANNEL(channel) \
    ((channel) == UART1 || (channel) == UART2 || (channel) == UART3 || (channel) == UART6)

/**************************************************************************************************
 * @section  Data Structures
 **************************************************************************************************/
// TODO: Integrate this within mmio.h
 static const rw_reg32_t UARTx_CRx[UART_CHANNEL_COUNT][CR_REG_COUNT + 1] = {
    [UART1] = {
        [1] = USARTx_CR1[1],
        [2] = USARTx_CR2[1],
        [3] = USARTx_CR3[1], 
    },
    [UART2] = {
        [1] = USARTx_CR1[2],
        [2] = USARTx_CR2[2],
        [3] = USARTx_CR3[2], 
    },
    [UART3] = {
        [1] = USARTx_CR1[3],
        [2] = USARTx_CR2[3],
        [3] = USARTx_CR3[3], 
    },
    [UART4] = {
        [1] = UARTx_CR1[4],
        [2] = UARTx_CR2[4],
        [3] = UARTx_CR3[4],
    },
    [UART5] = {
        [1] = UARTx_CR1[5],
        [2] = UARTx_CR2[5],
        [3] = UARTx_CR3[5],
    },
    [UART6] = {
        [1] = USARTx_CR1[6],
        [2] = USARTx_CR2[6],
        [3] = USARTx_CR3[6], 
    },
    [UART7] = {
        [1] = UARTx_CR1[7],
        [2] = UARTx_CR2[7],
        [3] = UARTx_CR3[7],
    },
    [UART8] = {
        [1] = UARTx_CR1[8],
        [2] = UARTx_CR2[8],
        [3] = UARTx_CR3[8],
    },
};

// Stores dmamux request numbers. Index 0 is for RX stream, 1 for TX stream.
const static uint8_t uart_dmamux_req[UART_CHANNEL_COUNT][NUM_REQUESTS_PER_UART] = {
    [UART1] = {
        [0] = 41,
        [1] = 42,
    },
    [UART2] = {
        [0] = 43,
        [1] = 44,
    },
    [UART3] = {
        [0] = 45,
        [1] = 46,
    },
    [UART4] = {
        [0] = 63,
        [1] = 64,
    },
    [UART5] = {
        [0] = 65,
        [1] = 66,
    },
    [UART6] = {
        [0] = 71,
        [1] = 72,
    },
    [UART7] = {
        [0] = 79,
        [1] = 80,
    },
    [UART8] = {
        [0] = 81,
        [1] = 82,
    },
};

volatile dma_periph_streaminfo_t uart_to_dma[UART_CHANNEL_COUNT] = {0};

bool uart_busy[UART_CHANNEL_COUNT] = {0};

uart_context_t uart_contexts[UART_CHANNEL_COUNT] = {0};

uint32_t timeout;

/**************************************************************************************************
 * @section Private Function Implementations
 **************************************************************************************************/
bool set_alternate_function(tal_flag_t *flag, uart_channel_t channel, uint8_t tx_pin, uint8_t rx_pin) {
    switch (channel) {
        case UART1:
            if (tx_pin == 98 || tx_pin == 133) {
                tal_alternate_mode(tx_pin, 7);
            } else if (tx_pin == 74) {
                tal_alternate_mode(tx_pin, 4);
            } else {
                tal_raise(flag, "Invalid TX Pin for channel");
                return false;
            }
            if (rx_pin == 99 || rx_pin == 134) {
                tal_alternate_mode(rx_pin, 7);
            } else if (tx_pin == 75) {
                tal_alternate_mode(rx_pin, 4);
            } else {
                tal_raise(flag, "Invalid RX Pin for channel");
                return false;
            }
            break;
        case UART2:
            if (tx_pin == 39 || tx_pin == 117) {
                tal_alternate_mode(tx_pin, 7);
            } else {
                tal_raise(flag, "Invalid TX Pin for channel");
                return false;
            }
            if (rx_pin == 40 || rx_pin == 120) {
                tal_alternate_mode(tx_pin, 7);
            } else {
                tal_raise(flag, "Invalid RX Pin for channel");
                return false;
            }
            break;
        case UART3:
            if (tx_pin == 66 || tx_pin == 109 || tx_pin == 76 ) {
                set_alternate_mode(tx_pin, 7);
            } else {
                tal_raise(flag, "Invalid TX Pin for channel");
                return false;
            }
            if (rx_pin == 67 || tx_pin == 110 || tx_pin == 77) {
                set_alternate_mode(rx_pin, 7);
            } else {
                tal_raise(flag, "Invalid RX Pin for channel");
                return false;
            }
            break;
        case UART4:
            if (tx_pin == 37 || tx_pin == 137 || tx_pin == 109 || tx_pin == 113) {
                set_alternate_mode(tx_pin, 8);
            } else if (tx_pin == 100) {
                set_alternate_mode(tx_pin, 6);
            } else {
                tal_raise(flag, "Invalid TX Pin for channel");
                return false;
            }
            if (rx_pin == 38 || rx_pin == 136 || rx_pin == 110 || rx_pin == 112) {
                set_alternate_mode(rx_pin, 8);
            } else if (rx_pin == 101) {
                set_alternate_mode(rx_pin, 6);
            } else {
                tal_raise(flag, "Invalid RX Pin for channel");
                return false;
            }
            break;
        case UART5:
            if (tx_pin == 133 || rx_pin == 73) {
                set_alternate_mode(tx_pin, 14);
            } else if (tx_pin == 111) {
                set_alternate_mode(tx_pin, 8);
            } else {
                tal_raise(flag, "Invalid TX Pin for channel");
                return false;
            }
            if (rx_pin == 132 || rx_pin == 72) {
                set_alternate_mode(rx_pin, 14);
            } else if (rx_pin == 114) {
                set_alternate_mode(rx_pin, 8);
            } else {
                tal_raise(flag, "Invalid RX Pin for channel");
                return false;
            }
            break;
        case UART6:
            if (tx_pin == 93 || tx_pin == 122) {
                set_alternate_mod(tx_pin, 7);
            } else {
                tal_raise(flag, "Invalid TX Pin for channel");
                return false;
            }
            if (rx_pin == 94) {
                set_alternate_mode(rx_pin, 7);
            } else {
                tal_raise(flag, "Invalid RX Pin for channel");
                return false;
            }
            break;
        case UART7:
            if (tx_pin == 108 || tx_pin == 131) {
                set_alternate_mode(tx_pin, 11);
            } else if (tx_pin == 58 || tx_pin == 21) {
                set_alternate_mode(tx_pin, 7);
            } else {
                tal_raise(flag, "Invalid TX Pin for channel");
                return false;
            }
            if (rx_pin == 97 || rx_pin == 130) {
                set_alternate_mode(rx_pin, 11);
            } else if (rx_pin == 57 || rx_pin == 20) {
                set_alternate_mode(rx_pin, 7);
            } else {
                tal_raise(flag, "Invalid RX Pin for channel");
                return false;
            }
            break;
        case UART8:
            if (tx_pin == 139) {
                set_alternate_mode(tx_pin, 8);
            } else {
                tal_raise(flag, "Invalid TX Pin for channel");
                return false;
            }
            if (rx_pin == 138) {
                set_alternate_mode(rx_pin, 8);
            } else {
                tal_raise(flag, "Invalid RX Pin for channel");
                return false;
            }            
            break;
   }
   return true;
}

bool uart_write_byte(uart_channel_t channel, uint8_t data) {
    uint32_t count = 0;

    // Get the correct registers/fields
    rw_reg32_t isr_reg;
    field32_t isr_field;
    rw_reg32_t tdr_reg;
    field32_t tdr_field;
    if (IS_USART_CHANNEL(channel)) {
        isr_reg = USARTx_ISR[channel];
        isr_field = USARTxISR_TXFNF;  // TODO: Figure out why this field doesn't exist
        tdr_reg = USARTx_TDR[channel];
        tdr_field = USARTx_TDR_TDR;
    } else {
        isr_reg = UARTx_ISR[channel];
        isr_field = UARTxISR_TXFNF; // TODO: Figure out why this field doesn't exist
        tdr_reg = UARTx_TDR[channel];
        tdr_field = UARTx_TDR_TDR;
    }

    // Wait until the transmit FIFO is not full.
    while (READ_FIELD(isr_reg, isr_field) == 0) { 
        if (count++ >= timeout) {
            return false; // Return false on timeout
        }
    }

    // Write the data to the transmit data register.
    // This automatically pushes the data into the FIFO.
    WRITE_FIELD(tdr_reg, tdr_field, data);

    // This is a blocking function, so we return immediately after the data is placed
    // in the FIFO. If you needed to ensure the data was completely sent, you would
    // wait for the TC (Transmission Complete) flag.
    return true;
}

bool uart_read_byte(uint8_t channel, uint8_t *data) {
    uint32_t count = 0;

    // Get the correct registers/fields.
    rw_reg32_t isr_reg;
    field32_t isr_field;
    rw_reg32_t rdr_reg;
    field32_t rdr_field;

    // Use the macro to select the correct register set for USART vs UART
    if (IS_USART_CHANNEL(channel)) {
        isr_reg = USARTx_ISR[channel];
        isr_field = USARTx_ISR_RXFNE; // TODO: Figure out why this field doesn't exist
        rdr_reg = USARTx_RDR[channel];
        rdr_field = USARTx_RDR_RDR;
    } else {
        isr_reg = UARTx_ISR[channel];
        isr_field = UARTx_ISR_RXFNE; // TODO: Figure out why this field doesn't exist
        rdr_reg = UARTx_RDR[channel];
        rdr_field = UARTx_RDR_RDR;
    }
    
    // Input validation: ensure the destination pointer is not NULL
    if (data == NULL) {
        return false;
    }

    // Wait until the receive FIFO is not empty.
    while (READ_FIELD(isr_reg, isr_field) == 0) { 
        if (count++ >= timeout) {
            return false; // Return false on timeout
        }
    }

    // Read the data from the receive data register.
    // The hardware automatically retrieves the next available byte from the FIFO.
    *data = (uint8_t)READ_FIELD(rdr_reg, rdr_field);

    return true;
}

inline bool verify_transfer_parameters(tal_flag_t *flag, uart_channel_t channel, uint8_t *buff, size_t size) {
    if (flag == NULL) {
        return false;
    }
    if (buff == NULL) {
        tal_raise(flag, "Buffer cannot be NULL");
        return false;
    }
    if (size == 0) {
        tal_raise(flag, "Size cannot be zero");
        return false;
    }
    return true;
}

/**************************************************************************************************
 * @section Public Function Implementations
 **************************************************************************************************/
bool uart_init(tal_flag_t *flag, uart_config_t *usart_config, dma_callback_t *callback, periph_dma_config_t *tx_stream, periph_dma_config_t *rx_stream) {
    // De-reference struct members for readability
    uart_channel_t channel = usart_config->channel;
    uint8_t tx_pin = usart_config->tx_pin;
    uint8_t rx_pin = usart_config->rx_pin;
    uint8_t ck_pin = usart_config->ck_pin;
    uint32_t baud_rate = usart_config->baud_rate;
    uart_parity_t parity = usart_config->parity;
    uart_datalength_t data_length = usart_config->data_length;

    // TODO: Potentially choose which kernel clock to use (might be done in main init function)

    // Enable usart clock
    switch (channel) {
        // TODO: Figure out USARTxEN for USART 1 and 6
        // TODO: Fields appear to be wrong for this in mmio.h
        case UART1:
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[8]);
            break;
        case UART2:
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_USARTxEN[2]);
            break;
        case UART3:
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_USARTxEN[3]);
            break;
        case UART4:
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[4]);
            break;
        case UART5:
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[5]);
            break;
        case UART6:
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[8]);
            break;
        case UART7:
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[7]);
            break;
        case UART8:
            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[8]);
            break;
        default:
            // Handle error or invalid USART number
            break;
    }

    // Set alternate-function mode
    tal_set_mode(tx_pin, 2);
    tal_set_mode(rx_pin, 2);

    // Set the right alternate function
    if (!set_alternate_function(flag, channel, tx_pin, rx_pin)) return false;

    // Enable the clocks for the gpio pins
    tal_enable_clock(rx_pin);
    tal_enable_clock(tx_pin);


    // Ensure the clock pin is disabled for asynchronous mode
    CLR_FIELD(UARTx_CRx[channel][2], USARTx_CR2_CLKEN);

    // Set baud rate
    uint32_t clk_freq;
    if (IS_USART_CHANNEL(channel)) {
        clk_freq = clock_get_freq_ahb2();
    } else {
        clk_freq = clock_get_freq_ahb1();
    }
    uint32_t brr_value = (uint32_t)roundf((float)clk_freq / baud_rate);
    WRITE_FIELD(USARTx_BRR[channel], USARTx_BRR_BRR_4_15, brr_value);

    // TODO: Write now all the field manipulations use UARTx_CR1, not differentiating
    //       between UART and USART. Find a way to do this, perhapse with an internal array.
    // Set parity
    switch (parity) {
        case (UART_PARITY_DISABLED):
            CLR_FIELD(UARTx_CRx[channel][1], UARTx_CR1_PCE);
            break;
        case (UART_PARITY_EVEN):
            SET_FIELD(UARTx_CRx[channel][1], UARTx_CR1_PCE);
            CLR_FIELD(UARTx_CRx[channel][1], UARTx_CR1_PS);
            break;
        case (UART_PARITY_ODD):
            SET_FIELD(UARTx_CRx[channel][1], UARTx_CR1_PCE);
            SET_FIELD(UARTx_CRx[channel][1], UARTx_CR1_PS);
            break;
    }

    // Set data length
    switch (data_length) {
        case (UART_DATALENGTH_7):
            if (!parity) {
                tal_raise(flag, "Invalid parity datasize combo");
                return false;
            }
            SET_FIELD(UARTx_CRx[channel][1], UARTx_CR1_Mx[0]);
            CLR_FIELD(UARTx_CRx[channel][1], UARTx_CR1_Mx[1]);
            break;
        case (UART_DATALENGTH_8):
            CLR_FIELD(UARTx_CRx[channel][1], UARTx_CR1_Mx[0]);
            CLR_FIELD(UARTx_CRx[channel][1], UARTx_CR1_Mx[1]);
            break;
        case (UART_DATALENGTH_9):
            if (parity) {
                tal_raise(flag, "Invalid parity datasize combo");
                return false;
            }
            SET_FIELD(UARTx_CRx[channel][1], UARTx_CR1_Mx[0]);
            SET_FIELD(UARTx_CRx[channel][1], UARTx_CR1_Mx[1]);
            break;
    }

    // Enable the FIFOs
    WRITE_FIELD(UARTx_CRx[channel][1], UARTx_CR1_FIFOEN, 1);

    dma_config_t dma_tx_stream = {
        .instance = tx_stream->instance,
        .stream = tx_stream->stream,
        .request_id = uart_dmamux_req[channel][1],
        .direction = tx_stream->direction,
        .src_data_size = tx_stream->src_data_size,
        .dest_data_size = tx_stream->dest_data_size,
        .priority = tx_stream->priority,
        .fifo_enabled = false, // FIFO disabled for tx
        .fifo_threshold = tx_stream->fifo_threshold,
        .callback = callback, // We need to know if it failed.
    };
    dma_configure_stream(flag, &dma_tx_stream);

    dma_config_t dma_rx_stream = {
        .instance = rx_stream->instance,
        .stream = rx_stream->stream,
        .request_id = uart_dmamux_req[channel][0],
        .direction = rx_stream->direction,
        .src_data_size = rx_stream->src_data_size,
        .dest_data_size = rx_stream->dest_data_size,
        .priority = rx_stream->priority,
        .fifo_enabled = false, // FIFO disabled for tx
        .fifo_threshold = rx_stream->fifo_threshold,
        .callback = callback, // We need to know if it failed.
    };
    dma_configure_stream(flag, &dma_rx_stream);

    // Save stream info
    dma_periph_streaminfo_t info = {
        .rx_instance = rx_stream->instance,
        .tx_instance = tx_stream->instance,
        .rx_stream = rx_stream->stream,
        .tx_stream = tx_stream->stream
    };
    uart_to_dma[channel] = info;

    // Set the timeout parameter
    timeout = usart_config->timeout;

    // Enable the peripheral
    WRITE_FIELD(UARTx_CRx[channel][1], USARTx_CR1_UE, 1);
    WRITE_FIELD(UARTx_CRx[channel][1], USARTx_CR1_TE, 1);
    WRITE_FIELD(UARTx_CRx[channel][1], USARTx_CR1_RE, 1);
}

bool uart_write_async(tal_flag_t *flag, uart_channel_t channel, uint8_t* tx_buff, uint32_t size) {
    // Verify parameters
    verify_transfer_parameters(flag, channel, tx_buff, size);

    // Check if usart channel is busy
    if (uart_busy[channel]) {
        tal_raise(flag, "USART channel is busy");
        return false;
    }
    uart_busy[channel] = true;

    // Configure DMA stream
    uart_context_t context = {
        .busy = &uart_busy[channel],
        .channel = channel,
    };
    uart_contexts[channel] = context;
    dma_transfer_t tx_transfer = {
        .instance = uart_to_dma[channel].tx_instance,
        .stream = uart_to_dma[channel].tx_stream,
        .src = tx_buff,
        .dest = USARTx_TDR[channel], // TODO: Figure out differentiation between USARTx_TDR and UARTx_TDR.
        .size = size,
        .context = &uart_contexts[channel],
        .disable_mem_inc = false,
    };
    dma_start_transfer(flag, &tx_transfer);

    // Enable the dma requests
    SET_FIELD(UARTx_CRx[channel][3], UARTx_CR3_DMAT);

    return true;
}

bool uart_read_async(tal_flag_t *flag, uart_channel_t channel, uint8_t* rx_buff, uint32_t size) {
    // Verify parameters
    verify_transfer_parameters(flag, channel, rx_buff, size);

    // Check if usart channel is busy
    if (uart_busy[channel]) {
        tal_raise(flag, "USART channel is busy");
        return false;
    }
    uart_busy[channel] = true;

    // Configure DMA stream
    uart_context_t context = {
        .busy = &uart_busy[channel],
        .channel = channel,
    };
    uart_contexts[channel] = context;
    dma_transfer_t tx_transfer = {
        .instance = uart_to_dma[channel].tx_instance,
        .stream = uart_to_dma[channel].tx_stream,
        .src = USARTx_RDR[channel], // TODO: Figure out differentiation between USARTx_RDR and UARTx_RDR.
        .dest = rx_buff, 
        .size = size,
        .context = &uart_contexts[channel],
        .disable_mem_inc = false,
    };
    dma_start_transfer(flag, &tx_transfer);

    // Enable the dma requests
    SET_FIELD(UARTx_CRx[channel][3], UARTx_CR3_DMAT);

    return true;
}

bool usart_write_bocking(tal_flag_t *flag, uart_channel_t channel, uint8_t* tx_buff, uint32_t size) {
    // Verify parameters
    verify_transfer_parameters(flag, channel, tx_buff, size);

    // Check if usart channel is busy
    if (uart_busy[channel]) {
        tal_raise(flag, "USART channel is busy");
        return false;
    }
    uart_busy[channel] = true;

    // Transmit the data byte by byte
    for (uint32_t i = 0; i < size; i++) {
        if (!uart_write_byte(channel, tx_buff[i])) {
            tal_raise(flag, "USART write timeout");
            uart_busy[channel] = false;
            return false;
        }
    }

    uart_busy[channel] = false;
    return true;
}

bool uart_read_blocking(tal_flag_t *flag, uart_channel_t channel, uint8_t* rx_buff, uint32_t size) {
    // Verify parameters
    verify_transfer_parameters(flag, channel, rx_buff, size);

    // Check if usart channel is busy
    if (uart_busy[channel]) {
        tal_raise(flag, "USART channel is busy");
        return false;
    }
    uart_busy[channel] = true;
  
    // Receive the data byte by byte
    for (uint32_t i = 0; i < size; i++) {
        if (!uart_read_byte(channel, &rx_buff[i])) {
            tal_raise(flag, "USART read timeout");
            uart_busy[channel] = false;
            return false;
        }
    }

    uart_busy[channel] = false;
    return true;
}
