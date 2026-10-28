#include "peripheral/gpio.h"
#include "peripheral/uart.h"
#include "peripheral/errc.h"
#include <stdio.h>

void test_uart(){
	uart_config_t config;
	uart_channel_t channel = UART8;
	uart_parity_t parity = UART_PARITY_DISABLED;
	uart_datalength_t data_length = UART_DATALENGTH_8;
	config.channel = channel;
	config.parity = parity;
	config.data_length = data_length;
	config.baud_rate = 9600;
	config.clk_freq = 64000000; // Reset clock configuration: UART4 kernel clock.
	enum ti_errc_t errc;
	errc = TI_ERRC_NONE;
	uint8_t tx = 0xAA;
	uint8_t rx = 0x0;

	uart_init(&config, &errc);
	if (errc != TI_ERRC_NONE) {
		while (1) { asm("BKPT #0"); }
	}
	asm("BKPT #0");

	while (1) {
		uart_write_blocking(channel, &tx, 1, &errc);
		if (errc != TI_ERRC_NONE) {
			while (1) { asm("BKPT #0"); }
		}
		uart_read_blocking(channel, &rx, 1, &errc);
		if (errc != TI_ERRC_NONE) {
			while (1) { asm("BKPT #0"); }
		}
		asm("BKPT #0");
	}
}

void _start() {
	test_uart();
}
