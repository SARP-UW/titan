#include "uart.h"
#include "gpio.h"
#include "../internal/mmio.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

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
    uart_channel_t channel = config->channel;
    uart_parity_t parity = config->parity;
    uart_datalength_t data_length = config->data_length;
    uint32_t baud_rate = config->baud_rate;
    uint32_t clk_freq = config->clk_freq;

    init_uart_pins(channel);

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

    // Use value 0 to set the amount of stop bits to the default 1.
    WRITE_FIELD(UARTx_CR2[channel], UARTx_CR2_STOP, 0);

    // Transmitter Enable
    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_TE);
    // Receiver Enable
    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_RE);
    // UART Enable
    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_UE);
}