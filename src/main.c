/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * @file main.c
 * @brief ADC bring-up test: reads AIN0 on the ADS124S0x at SENSOR_CS_1.
 *
 * Attach a debugger, run, and inspect the volatile globals below at each BKPT.
 * adc_ain0_uv holds the last good AIN0 reading in microvolts.
 */

#include "peripheral/spi.h"
#include "peripheral/systick.h"
#include "peripheral/errc.h"
#include "devices/adc.h"
#include "app/utils/devices.h"
#include "app/utils/pinout.h"
#include <stdint.h>
#include <stdio.h>

volatile enum ti_errc_t spi_errc = TI_ERRC_NONE;
volatile enum ti_errc_t adc_init_errc = TI_ERRC_NONE;
volatile enum ti_errc_t adc_read_errc = TI_ERRC_NONE;
volatile uint8_t adc_dev_id = 0xFF; /* 0 = ADS124S08, 1 = ADS124S06 */
volatile int32_t adc_ain0_uv = 0;   /* last good AIN4 reading, microvolts */
volatile uint32_t adc_ok_count = 0;
volatile uint32_t adc_fail_count = 0;

void _start() {
    enum ti_errc_t errc = TI_ERRC_NONE;

    /* Every chip select on the instance has to be listed here, or spi_init()
     * never drives that pin as an output held high. */
    uint8_t ss_pins[1] = { (uint8_t)SENSOR_CS_1 };

    systick_init();

    /* The ADS124S0x only talks SPI mode 1; the driver sets that per transfer
     * anyway, so initializing the bus in mode 1 just avoids the switching. */
    spi_init((uint8_t)SENSOR_SPI_INST, MODE_1, ss_pins, 1, &spi_errc);

    /* ADC on SENSOR_CS_1. adc_init() checks the device ID, writes a known
     * config (INPMUX = AIN0/AINCOM, gain 1, internal 2.5 V ref, 400 SPS) and
     * starts continuous conversions. */
    adc_init(&adc_dev, &adc_init_errc);
    adc_dev_id = adc_read_manufacturer_id(&adc_read_errc);

    while (1) {
        /* adc_channels[0] is AIN0 vs AINCOM, gain 1, internal 2.5 V reference. */
        errc = TI_ERRC_NONE;
        int32_t uv = adc_read_voltage(&adc_channels[0], &errc);
        adc_read_errc = errc;

        if (errc == TI_ERRC_NONE) {
            adc_ain0_uv = uv;
            adc_ok_count++;
        } else {
            adc_fail_count++;
        }
    }
}