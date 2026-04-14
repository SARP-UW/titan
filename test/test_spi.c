#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include "devices/adc.h"
#include <stdio.h>

void test_spi() {
	uint8_t inst = 1;
	uint8_t ss_pins[1] = {43};
	enum ti_errc_t errc;

	spi_init(inst, 1, ss_pins, 1, &errc);

	uint8_t src[1] = {0xAA};
	uint8_t dst[1] = {0x00};

	while (1) {
			asm("BKPT #0");
			spi_transfer_sync(inst, ss_pins[0], src, dst, 1, &errc);
			asm("BKPT #0");
	}
}

void test_spi_read_write() {
	enum ti_errc_t errc;
	spi_init(1, 1, (uint8_t[]){43}, 1, &errc);

	uint8_t src[1] = {};
	uint8_t dst[1] = {};
	int result = 0;

	asm("BKPT #0");

	result = spi_rreg(0x01, 1, &errc);

	asm("BKPT #0");
}

void _start() {
	//test_spi();
	test_spi_read_write();
}
