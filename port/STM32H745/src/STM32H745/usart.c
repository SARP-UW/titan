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
 * @authors Joanna Zhou
 * @brief USART Driver
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "resource/mmio.h"
#include "titan/gpio.h"
#include "titan/usart.h"

#if defined(__cplusplus)
  extern "C" {
#endif


// TODO read: overrun error, noise, framing error, clock deviation tolerance

bool usart_init(int usart_num, int tx_pin, int rx_pin, uint32_t baud_rate, int data_len, int parity) {
    tal_set_mode(tx_pin, 2);
    tal_set_mode(rx_pin, 2);
    if (usart_num == 1 || usart_num == 2 || usart_num == 3 || usart_num == 6) {
        switch (usart_num) {
            case 1:
                if (tx_pin == 74) {  
                    tal_alternate_mode(tx_pin, 4);
                } else {
                    tal_alternate_mode(tx_pin, 7);
                }

                if (rx_pin == 75) {
                    tal_alternate_mode(rx_pin, 4);
                } else {
                    tal_alternate_mode(rx_pin, 7);
                }
                break;
            case 2:
            case 3:
            case 6:
                tal_alternate_mode(tx_pin, 7);
                tal_alternate_mode(rx_pin, 7);
                break;
        }

        // hard-coded clock freq, needs to be changed
        WRITE_FIELD(USARTx_BRR[usart_num], USARTx_BRR_BRR_4_15, 64000000/baud_rate);


        WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_FIFOEN, 1);

        // // Set data length (7 - M10, 8 - M00 or 9 - M01) M0: bit 12 and M1: bit 28 in USART_CR1
        if (parity != 0) {
            switch (data_len) {
                case 7:
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[0], 0);
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[1], 0);
                    break;
                case 8:
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[0], 0);
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[1], 1);
                    break;
                default:
                    return false;
                    break;
            }
            WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_PCE, 1);

            if (parity == 1) {
                WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_PS, 1);
            } else if (parity == 2) {
                WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_PS, 0);
            }
            
        } else {
            switch (data_len) {
                case 7:
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[0], 1);
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[1], 0);
                    break;
                case 8:
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[0], 0);
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[1], 0);
                    break;
                case 9:
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[0], 0);
                    WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_Mx[1], 1);
                    break;
                default:
                    return false;
                    break;
            }
        }
        
        WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_UE, 1);
        WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_TE, 1);
        WRITE_FIELD(USARTx_CRx[usart_num][1], USARTx_CRx_RE, 1);
        return true;

    } else if (usart_num == 4 || usart_num == 5 || usart_num == 7 || usart_num == 8) {
        switch (usart_num) {
            case 4:
                if (tx_pin == 100) {  
                    tal_alternate_mode(tx_pin, 6);
                } else {
                    tal_alternate_mode(tx_pin, 8);
                }

                if (rx_pin == 101) {
                    tal_alternate_mode(rx_pin, 6);
                } else {
                    tal_alternate_mode(rx_pin, 8);
                }
                break;
            case 5:
                if (tx_pin == 111) {  
                    tal_alternate_mode(tx_pin, 8);
                } else {
                    tal_alternate_mode(tx_pin, 14);
                }

                if (rx_pin == 114) {
                    tal_alternate_mode(rx_pin, 8);
                } else {
                    tal_alternate_mode(rx_pin, 14);
                }
                break;
            case 7:
                if (tx_pin == 108 || tx_pin == 131) {  
                    tal_alternate_mode(tx_pin, 11);
                } else {
                    tal_alternate_mode(tx_pin, 7);
                }

                if (rx_pin == 97 || rx_pin == 130) {
                    tal_alternate_mode(rx_pin, 11);
                } else {
                    tal_alternate_mode(rx_pin, 7);
                }
                break;
            case 8:
                
                tal_alternate_mode(tx_pin, 8);
                tal_alternate_mode(rx_pin, 8);
        }


        WRITE_FIELD(UARTx_BRR[usart_num], UARTx_BRR_BRR_4_15, 64000000/baud_rate);

        WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_FIFOEN, 1);
       
        if (parity != 0) {
            switch (data_len) {
                case 7:
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[0], 0);
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[1], 0);
                    break;
                case 8:
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[0], 0);
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[1], 1);
                    break;
                default:
                    return false;
                    break;
            }
            WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_PCE, 1);

            if (parity == 1) {
                WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_PS, 1);
            } else if (parity == 2) {
                WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_PS, 0);
            }
            
        } else {
            switch (data_len) {
                case 7:
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[0], 1);
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[1], 0);
                    break;
                case 8:
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[0], 0);
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[1], 0);
                    break;
                case 9:
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[0], 0);
                    WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_Mx[1], 1);
                    break;
                default:
                    return false;
                    break;
            }
        }


        WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_UE, 1);
        WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_TE, 1);
        WRITE_FIELD(UARTx_CRx[usart_num][1], UARTx_CRx_RE, 1);
        return true;
    } else {
        return false;
    }



    // // Select clock source (through the UE bit)
    // // The clock source frequency is usart_ker_ck, which will determine baud rate

    // // Select oversampling method (16 - 0 or 8 - 1) through OVER8 bit in USART_CR1
    // // 8 achieves higher speed but lower tolerance for clock deviation, opposite for 16
    // // USART_1_CR1 &= ~(1 << 15); // currently set to 16


    // // Configure TX, RX pins, 98(TX 7), 99(RX 7)
    // tal_set_mode(98, 2);
    // tal_set_mode(99, 2);
    // tal_alternate_mode(98, 7);
    // tal_alternate_mode(99, 7);

    // // Set baud rate, set in USART_BRR
    // // If oversampling by 16, write value = usart_ker_ck/required baud rate
    // // If oversampling by 8, write value = 2 * usart_ker_ck/required baud rate
    // // USART_1_BRR = 2 * usart_ker_ck/baud_rate;

    // // FIFO enabled (buffer to prevent overrun)
    // // USART_1_CR1 |= (1 << 29);
    // WRITE_FIELD(USARTx_CRx[1][1], USARTx_CRx_FIFOEN, 1);

    // // Set data length (7 - M10, 8 - M00 or 9 - M01) M0: bit 12 and M1: bit 28 in USART_CR1
    // // USART_1_CR1 &= ~((1 << 12) | (1 << 28));
    // WRITE_FIELD(USARTx_CRx[1][1], USARTx_CRx_Mx[1], 1);
    // // Enable parity control, set 1 to PCE bit (bit 10) in the USART_CR1 register
    // // Bit 9 PS, 0: Even parity, 1: Odd parity
    // //  | SB | 8-bit data PB | STB | if want to achieve this, needs to set data length to 9
    // // parity bit takes the last bit in the data length
    // WRITE_FIELD(USARTx_CRx[1][1], USARTx_CRx_PCE, 1);
    // WRITE_FIELD(USARTx_CRx[1][1], USARTx_CRx_PS, 1);


    // // Set stop bit length (0.5, 1(default), 1.5, 2), USART_CR2, bits 13,12 
    // // USART_1_CR2 &= ~((1 << 12) | (1 << 13));
    // // Enable USART
    // // USART_1_CR1 |= 1;
    // WRITE_FIELD(USARTx_CRx[1][1], USARTx_CRx_UE, 1);

    // // Write to TE (when writing to TE, an idle frame is sent, prepared to send data)
    // // USART_1_CR1 |= (1 << 3);
    // WRITE_FIELD(USARTx_CRx[1][1], USARTx_CRx_TE, 1);
    // // Write to RE (search for starting bit, prepared to receive data)
    // // USART_1_CR1 |= (1 << 2);
    // WRITE_FIELD(USARTx_CRx[1][1], USARTx_CRx_RE, 1);

    // // auto baud rate detection?
    // // USART synchronous mode (Master/slave mode)?
    // // Flow control
    // return true;
}

// For test only (For real use, replace with a timer-based delay.)
uint32_t TIMEOUT = 10000;

static bool usart_write_byte(int usart_num, uint8_t data) {
    // for test only
    uint32_t count = 0;

    if (usart_num == 1 || usart_num == 2 || usart_num == 3 || usart_num == 6) {
        // Write the data to send in USART_TDR. 
        // TXFNF is set when TXFIFO is not full meaning that data can be written in the USART_TDR
        while (READ_FIELD(USARTx_ISR[usart_num], USARTx_ISR_TXE) != 1) {
            if (count == TIMEOUT) {
                return false;
            }
            count++;
        }

        WRITE_FIELD(USARTx_TDR[usart_num], USARTx_TDR_TDR, data);
        return true;
    } else {
        // Write the data to send in USART_TDR. 
        // TXFNF is set when TXFIFO is not full meaning that data can be written in the USART_TDR
        while (READ_FIELD(UARTx_ISR[usart_num], UARTx_ISR_TXE) != 1) {
            if (count == TIMEOUT) {
                return false;
            }
            count++;
        }

        WRITE_FIELD(UARTx_TDR[usart_num], UARTx_TDR_TDR, data);
        return true;
    }

        
    // FIFO disabled: If multiple frames are sent, wait for TXE flag = 1 to write the next one to USART_TDR
    // When the last data is written to the USART_TDR register, wait until TC = 1.

    // break character?
}

void usart_read(int usart_num, uint8_t* data_array, uint32_t size) { 
    for (uint32_t i = 0; i < size; i++) {
        uint8_t result = usart_read_byte(usart_num);
        if (result == -1) {
            return;
        }
        data_array[i] = result;
    }
}

static uint8_t usart_read_byte(int usart_num) {
    // for test only
    uint32_t count = 0;

    // Read data from USART_RDR. 
    // When FIFO is enabled, RXFNE bit is set when RXFIFO not empty, data can be read from USART_RDR
    
    if (usart_num == 1 || usart_num == 2 || usart_num == 3 || usart_num == 6) {
        while (READ_FIELD(USARTx_ISR[usart_num], USARTx_ISR_RXNE) != 1) {
            if (count == TIMEOUT) {
                return -1;
            }
            count++;
        }
        
        uint8_t data = READ_FIELD(USARTx_RDR[usart_num], USARTx_RDR_RDR);
        return data;
    } else {
        while (READ_FIELD(UARTx_ISR[usart_num], UARTx_ISR_RXNE) != 1) {
            if (count == TIMEOUT) {
                return -1;
            }
            count++;
        }
        
        uint8_t data = READ_FIELD(UARTx_RDR[usart_num], UARTx_RDR_RDR);
        return data;
    }
}

bool usart_write(int usart_num, uint8_t* data, uint32_t length) {
    for (uint32_t i = 0; i < length; i++) {
        bool write_timeout = usart_write_byte(usart_num, data[i]);
        if (!write_timeout) {
            return false;
        }
    }
    return true;
}

void usart_read(int usart_num, uint8_t* data_array, uint32_t size) { 
    for (uint32_t i = 0; i < size; i++) {
        uint8_t result = usart_read_byte(usart_num);
        if (read_timeout == true) {
            return;
        }
        data_array[i] = result;
    }
}

#if defined(__cplusplus)
  }
#endif