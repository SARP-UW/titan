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
 * @file common/platform/usart.h
 * @authors Joanna Zhou
 * @brief USART Driver
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#if defined(__cplusplus)
  extern "C" {
#endif


#define USART_1_BASE 0x40011000
#define USART_CR1_OFFSET 0x00
#define USART_CR2_OFFSET 0x04
#define USART_BRR_OFFSET 0x0C
#define USART_RDR_OFFSET 0x24
#define USART_TDR_OFFSET 0x28
#define USART_ISR_OFFSET 0x1C


#define USART_1_CR1 *((volatile uint32_t *)(USART_1_BASE + USART_CR1_OFFSET))
#define USART_1_CR2 *((volatile uint32_t *)(USART_1_BASE + USART_CR2_OFFSET))
#define USART_1_BRR *((volatile uint32_t *)(USART_1_BASE + USART_BRR_OFFSET))
#define USART_1_RDR *((volatile uint32_t *)(USART_1_BASE + USART_RDR_OFFSET))
#define USART_1_TDR *((volatile uint32_t *)(USART_1_BASE + USART_TDR_OFFSET))
#define USART_1_ISR *((volatile uint32_t *)(USART_1_BASE + USART_ISR_OFFSET))


// TODO read: overrun error, noise, framing error, clock deviation tolerance, FIFO (if needed)


void usart_init(void) {
    // Select clock source (through the UE bit)
    // The clock source frequency is usart_ker_ck, which will determine baud rate

    // Select oversampling method (16 - 0 or 8 - 1) through OVER8 bit in USART_CR1
    // 8 achieves higher speed but lower tolerance for clock deviation, opposite for 16

    // Configure TX, RX pins, 98(TX 7), 99(RX 7)
    tal_set_mode(98, 2);
    tal_set_mode(99, 2);
    tal_alternate_mode(98, 7);
    tal_alternate_mode(99, 7);

    // Set baud rate, set in USART_BRR
    // If oversampling by 16, write value = usart_ker_ck/required baud rate
    // If oversampling by 8, write value = 2 * usart_ker_ck/required baud rate

    // FIFO enabled? (buffer to prevent overrun)
    USART_1_CR1 |= (1 << 29);

    // Set data length (7 - M10, 8 - M00 or 9 - M01) M0: bit 12 and M1: bit 28 in USART_CR1
    USART_1_CR1 &= ~((1 << 12) | (1 << 28));
    // Set stop bit length (0.5, 1(default), 1.5, 2), USART_CR2, bits 13,12 
    USART_1_CR2 &= ~((1 << 12) | (1 << 13));
    // Enable USART
    USART_1_CR1 |= 1;

    // Write to TE (when writing to TE, an idle frame is sent, prepared to send data)
    USART_1_CR1 |= (1 << 3);
    // Write to RE (search for starting bit, prepared to receive data)
    USART_1_CR1 |= (1 << 2);

    
    // parity control?
    // auto baud rate detection?
    // USART synchronous mode (Master/slave mode)?
    // Flow control
}

// For test only
uint32_t TIMEOUT = 100000;
bool read_timeout = false;

bool usart_write(int8_t* data, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) {
        bool write_timeout = usart_write_byte(data[i]);
        if (!write_timeout) {
            return false;
        }
    }
    return true;
}

bool usart_write_byte(int8_t data) {
    // for test only
    uint32_t count = 0;

    // Write the data to send in USART_TDR. 
    // TXFNF is set when TXFIFO is not full meaning that data can be written in the USART_TDR
    while ((USART_1_ISR & (1 << 7)) >> 7 != 1) {
        if (count == TIMEOUT) {
            return false;
        }
        count++;
    }

    USART_1_TDR = data;
    return true;
    // FIFO disabled: If multiple frames are sent, wait for TXE flag = 1 to write the next one to USART_TDR
    // When the last data is written to the USART_TDR register, wait until TC = 1.

    // break character?
}

void usart_read(uint8_t* data_array, uint32_t size) { 
    for (uint32_t i = 0; i < size; i++) {
        int8_t result = usart_read_byte();
        if (read_timeout = true) {
            return;
        }
        data_array[i] = result;
    }
}

int8_t usart_read_byte(void) {
    // for test only
    uint32_t count = 0;

    // Read data from USART_RDR. 
    // When FIFO is enabled, RXFNE bit is set when RXFIFO not empty, data can be read from USART_RDR
    
    while ((USART_1_ISR & (1 << 5)) >> 5 != 1) {
        if (count == TIMEOUT) {
            read_timeout = true;
            // Check
            return 0;
        }
        count++;
    }
    
    int8_t *data = (int8_t *)USART_1_RDR;
    return *data;
}

#if defined(__cplusplus)
  }
#endif