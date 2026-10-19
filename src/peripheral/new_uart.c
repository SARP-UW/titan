#include "new_uart.h"
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

static bool valid_usart_channel(uart_channel_t channel)
{
    return channel == UART1 ||
           channel == UART2 ||
           channel == UART3 ||
           channel == UART6;
}

static bool uart_write_byte(uart_channel_t channel, uint8_t data) {
    int count = 0;

    if (valid_usart_channel(channel)) {
        // Wait until status register is set to TXE, ready to accept.
        while (!READ_FIELD(USARTx_ISR[channel], USARTx_ISR_TXE)) {
            if (count++ >= 1000000) {
                return false;
            }
        }

        WRITE_FIELD(USARTx_TDR[channel], USARTx_TDR_TDR, data);

        count = 0;

        while (!READ_FIELD(USARTx_ISR[channel], USARTx_ISR_TC)) {
            if (count++ >= 1000000) {
                return false;
            }
        }
    } else {
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
    }
    return true;
}

void uart_write_blocking(uart_channel_t channel, uint8_t *tx_buff, uint32_t size, enum ti_errc_t *errc) {
    if (!valid_uart_channel(channel) && !valid_usart_channel(channel)) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART/USART channel");
        return;
    }
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

    if (valid_usart_channel(channel)) {
        // Wait until a byte has been received.
        while (!READ_FIELD(USARTx_ISR[channel], USARTx_ISR_RXNE)) {

            if (count++ >= 1000000) {
                return false;
            }
        }

        // Read received byte from Receive Data Register.
        *data = (uint8_t)READ_FIELD(USARTx_RDR[channel], USARTx_RDR_RDR);

    } else {
        // Wait until a byte has been received.
        while (!READ_FIELD(UARTx_ISR[channel], UARTx_ISR_RXNE)) {

            if (count++ >= 1000000) {
                return false;
            }
        }

        // Read received byte from Receive Data Register.
        *data = (uint8_t)READ_FIELD(UARTx_RDR[channel], UARTx_RDR_RDR);

    }

    return true;
}

void uart_read_blocking(uart_channel_t channel, uint8_t *rx_buff, uint32_t size, enum ti_errc_t *errc) {
    if (!valid_uart_channel(channel) && !valid_usart_channel(channel)) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART/USART channel");
        return;
    }
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
    // transmit pin
    int tx_pin;
    // recieve pin
    int rx_pin;
    // make the mode for UART
    int alt_mode;

    switch (channel) {
        case UART1:
            tx_pin = 98;   // PA9
            rx_pin = 99;   // PA10
            alt_mode = 7;

            // enable clock for UART or USART
            SET_FIELD(RCC_APB2ENR, RCC_APB2ENR_USARTxEN[1]);
            break;

        case UART4:
            tx_pin = 37;   // PA0
            rx_pin = 38;   // PA1
            alt_mode = 8;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[4]);
            break;

        case UART2:
            tx_pin = 39;   // PA2
            rx_pin = 40;   // PA3
            alt_mode = 7;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_USARTxEN[2]);
            break;

        case UART3:
            tx_pin = 66;   // PB10
            rx_pin = 67;   // PB11
            alt_mode = 7;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_USARTxEN[3]);
            break;

        case UART5:
            tx_pin = 133;  // PB6
            rx_pin = 132;  // PB5
            alt_mode = 14;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[5]);
            break;

        case UART6:
            tx_pin = 93;   // PC6
            rx_pin = 94;   // PC7
            alt_mode = 7;

            SET_FIELD(RCC_APB2ENR, RCC_APB2ENR_USARTxEN[6]);
            break;
        case UART7:
            tx_pin = 58;   // PE8
            rx_pin = 57;   // PE7
            alt_mode = 7;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[7]);
            break;

        case UART8:
            tx_pin = 139;  // PE1
            rx_pin = 138;  // PE0
            alt_mode = 8;

            SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_UARTxEN[8]);
            break;

        default:
            return;
    }

    // Enable GPIOA port clocks.
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
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "UART/USART config cannot be NULL");
        return;
    }

    if ((!valid_uart_channel(config->channel) &&
         !valid_usart_channel(config->channel)) ||
         config->baud_rate == 0 ||
         config->clk_freq == 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART/USART configuration");
        return;
    }

    uart_channel_t channel = config->channel;
    uart_parity_t parity = config->parity;
    uart_datalength_t data_length = config->data_length;
    uint32_t baud_rate = config->baud_rate;
    uint32_t clk_freq = config->clk_freq;

    // Check UART/USART parity and data length before configuring registers.
    if (parity != UART_PARITY_DISABLED &&
        parity != UART_PARITY_EVEN &&
        parity != UART_PARITY_ODD) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART/USART parity");
        return;
    }

    if (data_length != UART_DATALENGTH_7 &&
        data_length != UART_DATALENGTH_8 &&
        data_length != UART_DATALENGTH_9) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART/USART data length");
        return;
    }

    if (data_length == UART_DATALENGTH_9) {
        TI_SET_ERRC(
            errc,
            TI_ERRC_INVALID_ARG,
            "9 data bits is not supported"
        );
        return;
    }

    uint32_t brr_value = clk_freq / baud_rate;

    if (brr_value < 16 || brr_value > 0xFFFF) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid UART/USART baud rate divider");
        return;
    }

    init_uart_pins(channel);

    if (valid_usart_channel(channel)) {

        // Turn off USART peripheral while configuring its registers.
        // UE = USART enable bit.
        CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_UE);

        // Configure USART for asynchronous mode.
        CLR_FIELD(USARTx_CR2[channel], USARTx_CR2_CLKEN);

        // Configure USART for oversampling by 16.
        CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_OVER8);

        // Set the baud rate register for USART.
        WRITE_FIELD(
            USARTx_BRR[channel],
            USARTx_BRR_BRR_4_15,
            brr_value >> 4
        );

        WRITE_FIELD(
            USARTx_BRR[channel],
            USARTx_BRR_BRR_0_3,
            brr_value & 0xF
        );

        switch (parity) {
            case UART_PARITY_DISABLED:
                CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_PCE);
                break;

            case UART_PARITY_EVEN:
                SET_FIELD(USARTx_CR1[channel], USARTx_CR1_PCE);
                CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_PS);
                break;

            case UART_PARITY_ODD:
                SET_FIELD(USARTx_CR1[channel], USARTx_CR1_PCE);
                SET_FIELD(USARTx_CR1[channel], USARTx_CR1_PS);
                break;

            default:
                TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid USART parity");
                return;
        }

        switch (data_length) {
            // Setting USART hardware word-length bits to be payload (data_length) + parity.
            /* M1:M0 = 10  -> 7-bit hardware word
            M1:M0 = 00  -> 8-bit hardware word
            M1:M0 = 01  -> 9-bit hardware word */
            case UART_DATALENGTH_7:
                if (parity == UART_PARITY_DISABLED) {
                    // 7 data bits, no parity -> 7-bit hardware word
                    SET_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[0]);
                    CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[1]);
                } else {
                    // 7 data bits + parity -> 8-bit hardware word
                    CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[0]);
                    CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[1]);
                }
                break;

            case UART_DATALENGTH_8:
                if (parity == UART_PARITY_DISABLED) {
                    // 8 data bits, no parity -> 8-bit hardware word
                    CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[0]);
                    CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[1]);
                } else {
                    // 8 data bits + parity -> 9-bit hardware word
                    CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[0]);
                    SET_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[1]);
                }
                break;

            case UART_DATALENGTH_9:
                TI_SET_ERRC(
                    errc,
                    TI_ERRC_INVALID_ARG,
                    "9 data bits with parity is not supported"
                );

                /*
                This 9 data bits NO parity is possible for this USART peripheral, but
                will need to change read and write parameters to uint16_t.
                CLR_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[0]);
                SET_FIELD(USARTx_CR1[channel], USARTx_CR1_Mx[1]);
                break;
                */
                return;

            default:
                TI_SET_ERRC(
                    errc,
                    TI_ERRC_INVALID_ARG,
                    "Invalid USART data length"
                );
                return;
        }

        // Use value 0 to set the amount of USART stop bits to the default 1.
        WRITE_FIELD(USARTx_CR2[channel], USARTx_CR2_STOP, 0);

        // Finished Configuring USART, now enabling transmitter and receiver.

        // USART Transmitter Enable
        SET_FIELD(USARTx_CR1[channel], USARTx_CR1_TE);
        // USART Receiver Enable
        SET_FIELD(USARTx_CR1[channel], USARTx_CR1_RE);

        // USART ENABLE.
        SET_FIELD(USARTx_CR1[channel], USARTx_CR1_UE);

    } else {

        // Turn off UART peripheral while configuring its registers.
        // UE = UART enable bit.
        CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_UE);

        // Configure UART for asynchronous mode.
        CLR_FIELD(UARTx_CR2[channel], UARTx_CR2_CLKEN);

        // Configure UART for oversampling by 16.
        CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_OVER8);

        // Set the baud rate register for UART.
        WRITE_FIELD(
            UARTx_BRR[channel],
            UARTx_BRR_BRR_4_15,
            brr_value >> 4
        );

        WRITE_FIELD(
            UARTx_BRR[channel],
            UARTx_BRR_BRR_0_3,
            brr_value & 0xF
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
            // Setting UART hardware word-length bits to be payload (data_length) + parity.
            /* M1:M0 = 10  -> 7-bit hardware word
            M1:M0 = 00  -> 8-bit hardware word
            M1:M0 = 01  -> 9-bit hardware word */
            case UART_DATALENGTH_7:
                if (parity == UART_PARITY_DISABLED) {
                    // 7 data bits, no parity -> 7-bit hardware word
                    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
                    CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
                } else {
                    // 7 data bits + parity -> 8-bit hardware word
                    CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
                    CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
                }
                break;

            case UART_DATALENGTH_8:
                if (parity == UART_PARITY_DISABLED) {
                    // 8 data bits, no parity -> 8-bit hardware word
                    CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
                    CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
                } else {
                    // 8 data bits + parity -> 9-bit hardware word
                    CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
                    SET_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
                }
                break;

            case UART_DATALENGTH_9:
                TI_SET_ERRC(
                    errc,
                    TI_ERRC_INVALID_ARG,
                    "9 data bits with parity is not supported"
                );

                /*
                This 9 data bits NO parity is possible for this UART peripheral, but
                will need to change read and write parameters to uint16_t.
                CLR_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[0]);
                SET_FIELD(UARTx_CR1[channel], UARTx_CR1_Mx[1]);
                break;
                */
                return;

            default:
                TI_SET_ERRC(
                    errc,
                    TI_ERRC_INVALID_ARG,
                    "Invalid UART data length"
                );
                return;
        }

        // Use value 0 to set the amount of UART stop bits to the default 1.
        WRITE_FIELD(UARTx_CR2[channel], UARTx_CR2_STOP, 0);

        // Finished Configuring UART, now enabling transmitter and receiver.

        // UART Transmitter Enable
        SET_FIELD(UARTx_CR1[channel], UARTx_CR1_TE);
        // UART Receiver Enable
        SET_FIELD(UARTx_CR1[channel], UARTx_CR1_RE);

        // UART ENABLE.
        SET_FIELD(UARTx_CR1[channel], UARTx_CR1_UE);
    }
}
