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
 * @file peripheral/uart.c
 * @brief async UART4/5/7/8. Codex used for reorganizing code
 */
#include "uart.h"
#include "gpio.h"
#include "internal/mmio.h"
#include <stdbool.h>
#include <stddef.h>

#define UART_POLL_LIMIT 1000000U
// ISR PE, FE, NF, ORE
#define UART_RX_ERRORS 0x0FU
#define UART_REGISTER_FIELD MAKE_FIELD(field32_t, 0, 32)
#define UART_RX_ERROR_FIELD MAKE_FIELD(field32_t, 0, 4)

static bool valid_channel(uart_channel_t channel) {
  switch (channel) {
    case UART4:
    case UART5:
    case UART7:
    case UART8:
      return true;
    default:
      return false;
  }
}

static bool wait_for_flags(uart_channel_t channel, uint32_t mask,
                           bool receiving, enum ti_errc_t *errc) {
  for (uint32_t count = 0; count < UART_POLL_LIMIT; ++count) {
    uint32_t status = READ_FIELD(UARTx_ISR[channel], UART_REGISTER_FIELD);
    if (receiving && (status & UART_RX_ERRORS)) {
      WRITE_WO_FIELD(UARTx_ICR[channel], UART_RX_ERROR_FIELD, status & UART_RX_ERRORS);
      SET_WO_FIELD(UARTx_RQR[channel], UARTx_RQR_RXFRQ);
      if (status & UARTx_ISR_ORE.msk) {
        TI_SET_ERRC(errc, TI_ERRC_OVERFLOW, "UART receive overrun");
      } else {
        TI_SET_ERRC(errc, TI_ERRC_BUS, "UART receive framing/noise/parity error");
      }
      return false;
    }
    if ((status & mask) == mask) {
      return true;
    }
  }
  TI_SET_ERRC(errc, TI_ERRC_TIMEOUT, "UART polling timeout");
  return false;
}

static bool valid_transfer(uart_channel_t channel, const uint8_t *buffer,
                           uint32_t size, bool receiving, enum ti_errc_t *errc) {
  if (!valid_channel(channel) || buffer == NULL || size == 0) {
    TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART transfer parameters");
    return false;
  }
  uint32_t required = UARTx_CR1_UE.msk;
  if (receiving) {
    required |= UARTx_CR1_RE.msk;
  } else {
    required |= UARTx_CR1_TE.msk;
  }
  uint32_t control = READ_FIELD(UARTx_CR1[channel], UART_REGISTER_FIELD);
  if ((control & required) != required) {
    TI_SET_ERRC(errc, TI_ERRC_BUS, "UART is not enabled for this transfer");
    return false;
  }
  return true;
}

void uart_init(const uart_config_t *config, enum ti_errc_t *errc) {
  if (errc) *errc = TI_ERRC_NONE;
  if (config == NULL || !valid_channel(config->channel) ||
      config->baud_rate == 0 || config->clk_freq == 0 ||
      (config->parity != UART_PARITY_DISABLED &&
       config->parity != UART_PARITY_EVEN && config->parity != UART_PARITY_ODD) ||
      (config->data_length != UART_DATALENGTH_7 &&
       config->data_length != UART_DATALENGTH_8)) {
    TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART configuration");
    return;
  }

  uint32_t divisor = config->clk_freq / config->baud_rate;
  if (config->clk_freq % config->baud_rate >=
      (config->baud_rate / 2U) + (config->baud_rate % 2U)) {
    ++divisor;
  }
  if (divisor < 16U || divisor > 0xFFFFU) {
    TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "UART baud divisor out of range");
    return;
  }

  uart_channel_t channel = config->channel;
  uint8_t tx_pin;
  uint8_t rx_pin;
  uint8_t alternate;
  field32_t clock_enable;
  switch (channel) {
    case UART4:
      tx_pin = 37; rx_pin = 110; alternate = 8; // A0, C11
      clock_enable = RCC_APB1LENR_UARTxEN[channel];
      break;
    case UART5:
      tx_pin = 133; rx_pin = 132; alternate = 14; // B6, B5
      clock_enable = RCC_APB1LENR_UARTxEN[channel];
      break;
    case UART7:
      tx_pin = 58; rx_pin = 57; alternate = 7; // E8, E7
      clock_enable = RCC_APB1LENR_USARTxEN[channel];
      break;
    case UART8:
      tx_pin = 139; rx_pin = 138; alternate = 8; // E1, E0
      clock_enable = RCC_APB1LENR_USARTxEN[channel];
      break;
    default:
      return;
  }

  SET_FIELD(RCC_APB1LENR, clock_enable);
  (void)READ_FIELD(RCC_APB1LENR, clock_enable);
  CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_UE);

  tal_enable_clock(tx_pin);
  tal_enable_clock(rx_pin);
  tal_set_drain(tx_pin, 0);
  tal_pull_pin(rx_pin, 1);
  tal_alternate_mode(tx_pin, alternate);
  tal_alternate_mode(rx_pin, alternate);
  tal_set_mode(tx_pin, 2);
  tal_set_mode(rx_pin, 2);

  CLR_FIELD(UARTx_CR1[channel], UART_REGISTER_FIELD);
  // one stop bit, LSB first
  CLR_FIELD(UARTx_CR2[channel], UART_REGISTER_FIELD);
  CLR_FIELD(UARTx_CR3[channel], UART_REGISTER_FIELD); 
  CLR_FIELD(UARTx_PRESC[channel], UARTx_PRESC_PRESCALER);
  SET_FIELD(UARTx_CR1[channel], UARTx_CR1_TE);
  SET_FIELD(UARTx_CR1[channel], UARTx_CR1_RE);
  SET_FIELD(UARTx_CR1[channel], UARTx_CR1_FIFOEN);
  if (config->parity != UART_PARITY_DISABLED) {
    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_PCE);
    if (config->parity == UART_PARITY_ODD) {
      SET_FIELD(UARTx_CR1[channel], UARTx_CR1_PS);
    }
    if (config->data_length == UART_DATALENGTH_8) {
      SET_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
    }
  } else if (config->data_length == UART_DATALENGTH_7) {
    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
  }

  WRITE_FIELD(UARTx_BRR[channel], UARTx_BRR_BRR_4_15, divisor >> 4);
  WRITE_FIELD(UARTx_BRR[channel], UARTx_BRR_BRR_0_3, divisor & 0x0FU);
  SET_FIELD(UARTx_CR1[channel], UARTx_CR1_UE);

  if (!wait_for_flags(channel, UARTx_ISR_TEACK.msk | UARTx_ISR_REACK.msk,
                      false, errc)) {
    CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_UE);
    return;
  }
  SET_WO_FIELD(UARTx_RQR[channel], UARTx_RQR_RXFRQ);
  SET_WO_FIELD(UARTx_ICR[channel], UART_RX_ERROR_FIELD);
}

void uart_write_blocking(uart_channel_t channel, const uint8_t *tx_buff,
                         uint32_t size, enum ti_errc_t *errc) {
  if (errc) *errc = TI_ERRC_NONE;
  if (!valid_transfer(channel, tx_buff, size, false, errc)) return;

  for (uint32_t i = 0; i < size; ++i) {
    if (!wait_for_flags(channel, UARTx_ISR_TXE.msk, false, errc)) return;
    WRITE_WO_FIELD(UARTx_TDR[channel], UARTx_TDR_TDR, tx_buff[i]);
  }
  (void)wait_for_flags(channel, UARTx_ISR_TC.msk, false, errc);
}

void uart_read_blocking(uart_channel_t channel, uint8_t *rx_buff,
                        uint32_t size, enum ti_errc_t *errc) {
  if (errc) *errc = TI_ERRC_NONE;
  if (!valid_transfer(channel, rx_buff, size, true, errc)) return;

  uint32_t control = READ_FIELD(UARTx_CR1[channel], UART_REGISTER_FIELD);
  uint8_t data_mask = 0xFFU;
  if ((control & UARTx_CR1_Mx[1].msk) ||
      ((control & UARTx_CR1_PCE.msk) && !(control & UARTx_CR1_Mx[0].msk))) {
    data_mask = 0x7FU;
  }
  for (uint32_t i = 0; i < size; ++i) {
    if (!wait_for_flags(channel, UARTx_ISR_RXNE.msk, true, errc)) return;
    rx_buff[i] = (uint8_t)(READ_FIELD(UARTx_RDR[channel], UARTx_RDR_RDR) & data_mask);
  }
}
