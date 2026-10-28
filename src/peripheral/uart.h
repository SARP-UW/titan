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
 * @file peripheral/uart.h
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
  uart_datalength_t data_length; // Payload bits, excluding parity
  uint32_t clk_freq; // UART kernel clock in Hz, before prescaler
  uint32_t baud_rate;
} uart_config_t;

/**
 * @brief Configure a UART for full-duplex polling, one stop bit, and an RX pull-up. Uses oversampling by 16 and PRESC /1.
 * @param errc Optional error output; set to TI_ERRC_NONE on success.
 */
void uart_init(const uart_config_t *config, enum ti_errc_t *errc);

/**
 * @brief Send bytes, blocking until the final stop bit has been transmitted.
 * @param errc Optional error output. A failure may imply a partial transfer.
 */
void uart_write_blocking(uart_channel_t channel, const uint8_t *tx_buff,
                         uint32_t size, enum ti_errc_t *errc);

/**
 * @brief Receive exactly size bytes, w/ blocking.
 * @param errc Optional error output. A failure may result in a partial buffer.
 * @note Reports framing/noise/parity errors as TI_ERRC_BUS and overrun as
 * TI_ERRC_OVERFLOW
 */
void uart_read_blocking(uart_channel_t channel, uint8_t *rx_buff,
                        uint32_t size, enum ti_errc_t *errc);
