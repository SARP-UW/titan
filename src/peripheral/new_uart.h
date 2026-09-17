#pragma once

#include "dma.h"
#include "errc.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    UART1 = 1,
    UART2,
    UART3,
    UART4,
    UART5,
    UART6,
    UART7,
    UART8,
    UART_CHANNEL_COUNT,
} uart_channel_t;

typedef enum {
    UART_PARITY_DISABLED,
    UART_PARITY_EVEN,
    UART_PARITY_ODD,
} uart_parity_t;

typedef enum {
    UART_DATALENGTH_7,
    UART_DATALENGTH_8,
    UART_DATALENGTH_9,
} uart_datalength_t;

typedef struct {
    uart_channel_t channel;
    uart_parity_t parity;
    uart_datalength_t data_length;
    uint32_t clk_freq;
    uint32_t baud_rate;
} uart_config_t;

/**
 * @brief Initializes a UART channel.
 *
 * @param config UART configuration.
 * @param errc Pointer to error status output.
 */
void uart_init(uart_config_t *config, enum ti_errc_t *errc);

/**
 * @brief Writes data to a UART channel using blocking transmission.
 *
 * @param channel UART channel.
 * @param tx_buff Buffer containing data to transmit.
 * @param size Number of bytes to transmit.
 * @param errc Pointer to error status output.
 */
void uart_write_blocking(
    uart_channel_t channel,
    uint8_t *tx_buff,
    uint32_t size,
    enum ti_errc_t *errc
);

/**
 * @brief Reads data from a UART channel using blocking reception.
 *
 * @param channel UART channel.
 * @param rx_buff Buffer where received data will be stored.
 * @param size Number of bytes to receive.
 * @param errc Pointer to error status output.
 */
void uart_read_blocking(
    uart_channel_t channel,
    uint8_t *rx_buff,
    uint32_t size,
    enum ti_errc_t *errc
);