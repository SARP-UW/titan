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
 * @file devices/umbilical.c
 * @authors Mahir Emran
 * @brief Umbilical communication driver implementation using UART
 */
#include "devices/umbilical.h"
#include "peripheral/uart.h"
#include "peripheral/gpio.h"
#include "app/utils/pinout.h"

void umbilical_init(umbilical_t *dev, const umbilical_uart_dev *uart_config, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!dev || !uart_config) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid umbilical init args");
        return;
    }

    dev->uart_config = *uart_config;
    dev->initialized = false;

    uart_config_t uart_cfg = {
        .channel = (uart_channel_t)uart_config->uart_channel,
        .parity = UART_PARITY_DISABLED,
        .data_length = UART_DATALENGTH_8,
        .clk_freq = 4000000,
        .baud_rate = uart_config->baud_rate
    };

    periph_dma_config_t tx_dma = {0};
    periph_dma_config_t rx_dma = {0};

    uart_init(&uart_cfg, NULL, &tx_dma, &rx_dma, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to initialize UART for umbilical");
        return;
    }

    dev->initialized = true;
}

void umbilical_transmit(umbilical_t *dev, const uint8_t *data, size_t len, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!dev || !dev->initialized) {
        TI_SET_ERRC(errc, TI_ERRC_UNKNOWN, "Umbilical device not initialized");
        return;
    }
    if (!data || len == 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid umbilical transmit args");
        return;
    }

    uart_write_blocking((uart_channel_t)dev->uart_config.uart_channel, (uint8_t *)data, (uint32_t)len, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to transmit umbilical packet");
    }
}

void umbilical_receive(umbilical_t *dev, uint8_t *data, size_t max_len, size_t *actual_len, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!dev || !dev->initialized) {
        TI_SET_ERRC(errc, TI_ERRC_UNKNOWN, "Umbilical device not initialized");
        return;
    }
    if (!data || max_len == 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid umbilical receive args");
        return;
    }

    // uart_flush_rx((uart_channel_t)dev->uart_config.uart_channel, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        if (actual_len) *actual_len = 0;
        return;
    }

    uart_read_blocking((uart_channel_t)dev->uart_config.uart_channel, data, (uint32_t)max_len, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to receive umbilical packet");
        if (actual_len) *actual_len = 0;
        return;
    }

    if (actual_len) *actual_len = max_len;
}
