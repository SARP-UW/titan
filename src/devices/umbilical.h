/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
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
 * @file devices/umbilical.h
 * @authors Mahir Emran
 * @brief Umbilical communication driver interface using UART
 */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "peripheral/errc.h"

/**************************************************************************************************
 * @section Type Definitions
 **************************************************************************************************/

/**
 * @brief UART config for umbilical communication.
 */
typedef struct {
  uint8_t uart_channel;   /**< UART channel (1=UART1, 2=UART2, etc.) */
  uint32_t baud_rate;      /**< Baud rate for communication */
} umbilical_uart_dev;

/** @brief Umbilical device handle. Allocate one and pass to all umbilical_* functions. */
typedef struct {
  umbilical_uart_dev uart_config;  /**< UART configuration for this device. */
  bool initialized;                /**< Whether the device has been initialized. */
} umbilical_t;

/**************************************************************************************************
 * @section Function Definitions
 **************************************************************************************************/

/**
 * @brief Initializes the umbilical UART communication.
 *
 * @param dev        Pointer to the umbilical device handle.
 * @param uart_config Pointer to the UART configuration (channel + baud rate).
 * @return TI_ERRC_NONE on success, or an appropriate error code on failure.
 */
void umbilical_init(umbilical_t *dev, const umbilical_uart_dev *uart_config, enum ti_errc_t *errc);

/**
 * @brief Transmits a packet over the umbilical UART.
 *
 * @param dev   Pointer to the umbilical device handle.
 * @param data  Pointer to the transmit data buffer.
 * @param len   Number of bytes to transmit.
 * @return TI_ERRC_NONE on success, or an appropriate error code on failure.
 */
void umbilical_transmit(umbilical_t *dev, const uint8_t *data, size_t len, enum ti_errc_t *errc);

/**
 * @brief Receives a packet from the umbilical UART.
 *
 * @param dev         Pointer to the umbilical device handle.
 * @param data        Pointer to the receive data buffer.
 * @param max_len     Maximum number of bytes to receive.
 * @param actual_len  Pointer to store the actual number of bytes received.
 * @return TI_ERRC_NONE on success, or an appropriate error code on failure.
 */
void umbilical_receive(umbilical_t *dev, uint8_t *data, size_t max_len, size_t *actual_len, enum ti_errc_t *errc);