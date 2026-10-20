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
 * @file peripheral/new_uart.h
 * @brief Polling-only asynchronous UART4/5/7/8 driver.
 */
#pragma once

#include "errc.h"
#include <stdint.h>

typedef enum {
  UART4 = 4,
  UART5 = 5,
  UART7 = 7,
  UART8 = 8,
} uart_channel_t;

typedef enum {
  UART_PARITY_DISABLED,
  UART_PARITY_EVEN,
  UART_PARITY_ODD,
} uart_parity_t;

typedef enum {
  UART_DATALENGTH_7,
  UART_DATALENGTH_8,
} uart_datalength_t;

typedef struct {
  uart_channel_t channel;
  uart_parity_t parity;
  uart_datalength_t data_length; /**< Payload bits, excluding parity. */
  uint32_t clk_freq; /**< Actual UART kernel clock in Hz, before PRESC. */
  uint32_t baud_rate;
} uart_config_t;

/**
 * @brief Configure a UART for full-duplex polling, one stop bit, and an RX pull-up.
 *
 * Pins are MCU package numbers used by gpio.h:
 * UART4: PA0 TX (37), PC11 RX (110), AF8. PA1 is avoided on the Nucleo board.
 * UART5: PB6 TX (133), PB5 RX (132), AF14.
 * UART7: PE8 TX (58), PE7 RX (57), AF7.
 * UART8: PE1 TX (139), PE0 RX (138), AF8.
 *
 * Uses oversampling by 16 and PRESC /1. The caller supplies the actual kernel
 * clock frequency; this function does not change the RCC kernel clock source.
 * Reinitialization discards queued receive data.
 * @param errc Optional error output; set to TI_ERRC_NONE on success.
 */
void uart_init(const uart_config_t *config, enum ti_errc_t *errc);

/**
 * @brief Send bytes, waiting until the final stop bit has been transmitted.
 * @param errc Optional error output. A failure may follow a partial transfer.
 * @note Polling waits have a finite iteration limit, not a millisecond deadline.
 */
void uart_write_blocking(uart_channel_t channel, const uint8_t *tx_buff,
                         uint32_t size, enum ti_errc_t *errc);

/**
 * @brief Receive exactly size bytes, waiting on RXNE/RXFNE.
 * @param errc Optional error output. A failure may leave a partial buffer.
 * @note Reports framing/noise/parity errors as TI_ERRC_BUS and overrun as
 * TI_ERRC_OVERFLOW. On these errors the receive queue is flushed for recovery.
 * Polling waits have a finite iteration limit, not a millisecond deadline.
 */
void uart_read_blocking(uart_channel_t channel, uint8_t *rx_buff,
                        uint32_t size, enum ti_errc_t *errc);
