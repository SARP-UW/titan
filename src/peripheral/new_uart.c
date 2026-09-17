#include "uart.h"
#include "gpio.h"
#include "../internal/mmio.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

static bool valid_uart_channel(uart_channel_t channel)
{
    return channel == UART4 ||
           channel == UART5 ||
           channel == UART7 ||
           channel == UART8;
}

static bool uart_write_byte(uart_channel_t channel, uint8_t data) {
    int count = 0;
    // Wait until status register is set to TXE, ready to accept.
    while (!READ_FIELD(UARTx_ISR[channel], UARTx_ISR_TXE)) {
        if (count++ >= 1000000) {
            return false;
        }
    }
    // Put byte into Transmit Data Register (TDR).
    WRITE_FIELD(UARTx_TDR[channel], UARTx_TDR_TDR, data);
    count = 0;
    // Wait until transmission complete flag is 1.
    while (READ_FIELD(UARTx_ISR[channel], UARTx_ISR_TC) == 0) {
        if (count++ >= 1000000) {
            return false;
        }
    }
    return true;
}

void uart_write_blocking(uart_channel_t channel, uint8_t *tx_buff, uint32_t size, enum ti_errc_t *errc) {
    if (tx_buff == NULL || size == 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART write parameters");
        return;
    }
    // Write one byte at a time.
    for (uint32_t i = 0; i < size; i++) {
        if (!uart_write_byte(channel, tx_buff[i])) {
            TI_SET_ERRC(errc, TI_ERRC_TIMEOUT, "UART write timed out");
            return;
        }
    }
}

static bool uart_read_byte(uart_channel_t channel, uint8_t *data) {

    int count = 0;

    if (data == NULL) {
        return false;
    }

    // Wait until a byte has been received.
    while (!READ_FIELD(UARTx_ISR[channel], UARTx_ISR_RXNE)) {

        if (count++ >= 1000000) {
            return false;
        }
    }

    // Read received byte from Receive Data Register.
    *data = (uint8_t)READ_FIELD(UARTx_RDR[channel], UARTx_RDR_RDR);

    return true;
}

void uart_read_blocking(uart_channel_t channel, uint8_t *rx_buff, uint32_t size, enum ti_errc_t *errc) {
    if (rx_buff == NULL || size == 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART read parameters");
        return;
    }

    for (uint32_t i = 0; i < size; i++) {
        if (!uart_read_byte(channel, &rx_buff[i])) {
            TI_SET_ERRC(errc, TI_ERRC_TIMEOUT, "UART read timed out");
            return;
        }
    }
}

static void init_uart_pins(uart_channel_t channel)
{
    int tx_pin;
    int rx_pin;
    int alt_mode;

    switch (channel) {
        case UART4:
            tx_pin = 37;   // PA0
            rx_pin = 38;   // PA1
            alt_mode = 8;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UART4EN);
            break;

        case UART5:
            tx_pin = 133;  // PB6
            rx_pin = 132;  // PB5
            alt_mode = 14;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UART5EN);
            break;

        case UART7:
            tx_pin = 58;   // PE8
            rx_pin = 57;   // PE7
            alt_mode = 7;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UART7EN);
            break;

        case UART8:
            tx_pin = 139;  // PE1
            rx_pin = 138;  // PE0
            alt_mode = 8;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UART8EN);
            break;

        default:
            return;
    }

    // Enable GPIO port clocks.
    tal_enable_clock(tx_pin);
    tal_enable_clock(rx_pin);

    // Put TX and RX pins into alternate function mode.
    tal_set_mode(tx_pin, 2);
    tal_set_mode(rx_pin, 2);

    // Select the UART alternate function for each pin.
    tal_alternate_mode(tx_pin, alt_mode);
    tal_alternate_mode(rx_pin, alt_mode);
}

void uart_init(uart_config_t *config, enum ti_errc_t *errc)
{
    if (config == NULL) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "UART config cannot be NULL");
        return;
    }

    if (!valid_uart_channel(config->channel) || config->baud_rate == 0 || config->clk_freq == 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART clock or baud rate or UART channel");
        return;
    }

    uart_channel_t channel = config->channel;
    uart_parity_t parity = config->parity;
    uart_datalength_t data_length = config->data_length;
    uint32_t baud_rate = config->baud_rate;
    uint32_t clk_freq = config->clk_freq;


    init_uart_pins(channel);

    // Turn off UART peripheral while configuring its registers.
    // UE = UART enable pin.
    CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_UE);
    // Set the baud rate of register for UART.
    uint32_t brr_value = clk_freq / baud_rate;
    WRITE_FIELD(
        UARTx_BRR[channel],
        UARTx_BRR_BRR_4_15,
        brr_value
    );

    switch (parity) {
        case UART_PARITY_DISABLED:
            CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_PCE);
            break;

        case UART_PARITY_EVEN:
            SET_FIELD(UARTx_CR1[channel], UARTx_CR1_PCE);
            CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_PS);
            break;

        case UART_PARITY_ODD:
            SET_FIELD(UARTx_CR1[channel], UARTx_CR1_PCE);
            SET_FIELD(UARTx_CR1[channel], UARTx_CR1_PS);
            break;

        default:
            TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART parity");
            return;
    }

    switch (data_length) {
        case UART_DATALENGTH_7:
            SET_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
            CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
            break;

        case UART_DATALENGTH_8:
            CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
            CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
            break;

        case UART_DATALENGTH_9:
            CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
            SET_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
            break;

        default:
            TI_SET_ERRC(
                errc,
                TI_ERRC_INVALID_ARG,
                "Invalid UART data length"
            );
            return;
    }

    // Use value 0 to set the amount of stop bits to the default 1.
    WRITE_FIELD(UARTx_CR2[channel], UARTx_CR2_STOP, 0);

    // Finished Configuring UART, now enabling transmitter and reciever.

    // Transmitter Enable
    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_TE);
    // Receiver Enable
    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_RE);

    // UART ENABLE.
    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_UE);
}