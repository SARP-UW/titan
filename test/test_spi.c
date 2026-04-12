#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include <stdio.h>

void test_spi() {
	uint8_t inst = 1;
	uint8_t ss_pins[1] = {43};
	enum ti_errc_t errc;

	spi_init(inst, MODE_0, ss_pins, 1, &errc);

	uint8_t src[1] = {0xAA};
	uint8_t dst[1] = {0x00};

	while (1) {
			asm("BKPT #0");
			spi_transfer_sync(inst, ss_pins[0], src, dst, 1, &errc);
			asm("BKPT #0");
	}
}

void _start() {
	test_spi();
}
