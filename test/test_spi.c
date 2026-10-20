#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include "devices/adc.h"
#include <stdio.h>

#define TEST_SINGLE_BYTE 0

void test_spi() {
	uint8_t inst = 3;
	uint8_t ss_pins[1] = {43}; // A4
	enum ti_errc_t errc;

	spi_init(inst, 0, ss_pins, 1, &errc);
	asm("BKPT #0");
	uint8_t src[] = {
		0x00, 0xFF, 0xAA, 0x55,
		0x01, 0x02, 0x03, 0x04, 0x05,
		0x06, 0x07, 0x08, 0x09, 0x0A
	};
	uint8_t dst[sizeof(src)] = {0x00};

	while (1) {
		for (size_t i = 0; i < sizeof(dst); ++i) {
			dst[i] = 0xEE;
		}
		#if TEST_SINGLE_BYTE
		for (size_t i = 0; i < sizeof(src) / sizeof(src[0]); ++i) {
			spi_transfer_sync(inst, ss_pins[0], &src[i], &dst[i], 1, &errc);
			asm("BKPT #0");
		}
		#else
		spi_transfer_sync(inst, ss_pins[0], src, dst, sizeof(src), &errc);
		asm("BKPT #0");
		#endif
	}
}

void test_spi_read_write() {
	enum ti_errc_t errc;
	asm("BKPT #0");
	spi_init(1, 1, (uint8_t[]){43}, 1, &errc);
	adc_init(&(struct adc_spi_dev){.inst = 1, .ss_pin = 43}, &errc);

	uint8_t src[1] = {};
	uint8_t dst[1] = {};
	int status_reg = 0;

	asm("BKPT #0");

	status_reg = adc_read_manufacturer_id(&errc);

	asm("BKPT #0");
}

void _start() {
	test_spi();
	// test_spi_read_write();
}
