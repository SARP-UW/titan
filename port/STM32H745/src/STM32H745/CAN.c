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
 * @file common/platform/CAN.c /// @todo UPDATE THIS
 * @authors Joanna Zhou
 * @brief CAN Driver
 */

 #include <stdint.h>
 #include <stdbool.h>
 #include <stddef.h>
 #include <string.h>
 #include "resource/mmio.h"
 #include "titan/gpio.h"
 
 #if defined(__cplusplus)
   extern "C" {
 #endif
 
 
bool CAN_init(int CAN_num, int tx_pin, int rx_pin, uint32_t baud_rate, uint32_t addr) {
    tal_set_mode(tx_pin, 2);
    tal_set_mode(rx_pin, 2);
    
    tal_alternate_mode(tx_pin, 9);
    tal_alternate_mode(rx_pin, 9);
 
     
    // Enter software initialization by setting INIT bit in FDCAN_CCCR
    // For testing: FDCAN-TX is high in this state
    WRITE_FIELD(FDCANx_FDCAN_CCCR[CAN_num], FDCANx_FDCAN_CCCR_INIT, 1);
    while (!READ_FIELD(FDCANx_FDCAN_CCCR[CAN_num], FDCANx_FDCAN_CCCR_INIT));
    
    // Access to the FDCAN configuration registers is only enabled when both INIT bit in 
    // FDCAN_CCCR register and CCE bit in FDCAN_CCCR register are set.
    // CCE bit in FDCAN_CCCR register can be set only while INIT bit in FDCAN_CCCR is set.
    WRITE_FIELD(FDCANx_FDCAN_CCCR[CAN_num], FDCANx_FDCAN_CCCR_CCE, 1);
    while (!READ_FIELD(FDCANx_FDCAN_CCCR[CAN_num], FDCANx_FDCAN_CCCR_CCE));

    // Classic CAN
    WRITE_FIELD(FDCANx_FDCAN_CCCR[CAN_num], FDCANx_FDCAN_CCCR_FDOE, 0);

    // Bit timing (baud rate)
    // nominal bit timing for traditional CAN
    // The value used by the hardware is the one programmed, incremented by 1.
    const uint8_t bit_time = 16;
    const uint8_t sync_seg = 1;
    const uint8_t tseg1 = 13;
    const uint8_t tseg2 = 2;
    // Sync Jump Width
    const uint8_t sjw = 2;          

    // TODO: clock frequency needs to be figured out
    uint32_t NBRP = (CLK_FREQ / (baud_rate * bit_time));

    if (NBRP > 31) {
        return false;
    }

    WRITE_FIELD(FDCANx_FDCAN_NBTP[CAN_num], FDCANx_FDCAN_NBTP_NSJW, sjw - 1);
    WRITE_FIELD(FDCANx_FDCAN_NBTP[CAN_num], FDCANx_FDCAN_NBTP_NBRP, NBRP - 1);
    WRITE_FIELD(FDCANx_FDCAN_NBTP[CAN_num], FDCANx_FDCAN_NBTP_NTSEG1, tseg1 - 1);
    WRITE_FIELD(FDCANx_FDCAN_NBTP[CAN_num], FDCANx_FDCAN_NBTP_TSEG2, tseg2 - 1);

    // Filters
    // The FDCAN offers the possibility to configure two sets of acceptance filters, one for 
    // standard identifiers and one for extended identifiers. These filters can be assigned to Rx 
    // buffer, Rx FIFO 0 or Rx FIFO 1. For acceptance filtering each list of filters is executed from 
    // element #0 until the first matching element. Acceptance filtering stops at the first matching 
    // element.

    // Standard FIFO 0
    // 00: Accept in Rx FIFO 0
    // 01: Accept in Rx FIFO 1
    // 10: Reject
    // 11: Reject
    WRITE_FIELD(FDCANx_FDCAN_GFC[CAN_num], FDCANx_FDCAN_GFC_ANFS, 0);
    WRITE_FIELD(FDCANx_FDCAN_GFC[CAN_num], FDCANx_FDCAN_GFC_ANFE, 0);

 
    // TX FIFO operation
    WRITE_FIELD(FDCANx_FDCAN_TXBC[CAN_num], FDCANx_FDCAN_TXBC_TFQM, 0);
    // No TX buffer, all allocated to FIFO (little bit confused on this tbh)
    WRITE_FIELD(FDCANx_FDCAN_TXBC[CAN_num], FDCANx_FDCAN_TXBC_TFQS, 32);
    WRITE_FIELD(FDCANx_FDCAN_TXBC[CAN_num], FDCANx_FDCAN_TXBC_NDTB, 0);

    // RX FIFO 0 max, 64 bits, no FIFO 1
    // missing F0OM in register?
    WRITE_FIELD(FDCANx_FDCAN_RXF0C[CAN_num], FDCANx_FDCAN_RXF0C_F0S, 64);
    WRITE_FIELD(FDCANx_FDCAN_RXF1C[CAN_num], FDCANx_FDCAN_RXF1C_F1S, 0);

    // The message RAM has a width of 32 bits. The FDCAN module can be configured to allocate 
    // up to 2560 words in the message RAM. It is not necessary to configure each of the sections 
    // listed in Figure 780, nor is there any restriction with respect to the sequence of the sections.
    WRITE_FIELD(FDCANx_FDCAN_TXBC[CAN_num], FDCANx_FDCAN_TXBC_TBSA, addr);
    WRITE_FIELD(FDCANx_FDCAN_RXF1C[CAN_num], FDCANx_FDCAN_RXF0C_F0SA, addr + 32 * 4);

    // Clear INIT to finish software initialization
    // CCE bit in FDCAN_CCCR register is automatically cleared when INIT bit in FDCAN_CCCR is cleared.
    WRITE_FIELD(FDCANx_FDCAN_CCCR[CAN_num], FDCANx_FDCAN_CCCR_INIT, 0);

}
 
 // For test only (For real use, replace with a timer-based delay.)
 uint32_t TIMEOUT = 10000;
 
 // TODO: update with checking with free space and load at once
 void CAN_send(int CAN_num, uint32_t id, uint8_t* data, uint8_t len) {
    uint32 addr = READ_FIELD(FDCANx_FDCAN_TXBC[CAN_num], FDCANx_FDCAN_TXBC_TBSA);

    while (len > 0) {
        // Find the next available TX FIFO index
        while (READ_FIELD(FDCANx_FDCAN_TXFQS[CAN_num], FDCANx_FDCAN_TXFQS_TFQF));
        uint32_t index = READ_FIELD(FDCANx_FDCAN_TXFQS[CAN_num], FDCAN_TXFQS_TFQPI);

        // Calculate address of TX buffer in RAM
        // the start address of the next available (free) Tx FIFO buffer is calculated by adding four times the put 
        // index FDCAN_TXFQS.TFQPI (0 … 31) to the Tx buffer start address FDCAN_TXBC.TBSA.
        uint32_t tx_addr = addr + (index * 4);

        // TODO: Write standard ID

        // TODO: Write DLC (Data Length Code) & flags

        // TODO: Write data, update data & len

        //Request transmission
        WRITE_FIELD(FDCANx_FDCAN_TXBAR[CAN_num], FDCANx_FDCAN_TXBAR[CAN_num], (1 << index));

    }
    
}

void CAN_receive(int CAN_num, uint32_t* id, uint8_t* data, uint8_t* len) {
    // Check fill level
    if (READ_FIELD(FDCANx_FDCAN_RXF0S[CAN_num], FDCANx_FDCAN_RXF0S_F0FL) == 0) {
        return;
    }

    // Get index of next message
    uint32_t index = READ_FIELD(FDCANx_FDCAN_RXF0S[CAN_num], FDCANx_FDCAN_RXF0S_F0G);

    // TODO: Calculate addr
    // TODO: extract ID & DLC & data

    // Acknowledge reception
    WRITE_FIELD(FDCANx_FDCAN_RXF0A[CAN_num], FDCANx_FDCAN_RXF0A_FA01, (1 << index));
}
 
 
 
 #if defined(__cplusplus)
   }
 #endif