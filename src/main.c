/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * @file main.c
 * @brief ADC bring-up test: reads AIN4 on the ADS124S0x at SENSOR_CS_2 (MCU pin 77).
 *
 * Attach a debugger, run, and inspect the volatile globals below at each BKPT.
 * adc_ain4_uv holds the last good AIN4 reading in microvolts.
 */

#include "peripheral/spi.h"
#include "peripheral/systick.h"
#include "peripheral/errc.h"
#include "devices/adc.h"
#include "app/utils/devices.h"
#include "app/utils/pinout.h"
#include <stdint.h>
#include <stdio.h>

/* Debug globals: volatile so the optimizer keeps them for inspection. */
volatile enum ti_errc_t spi_errc      = TI_ERRC_NONE;
volatile enum ti_errc_t adc_init_errc = TI_ERRC_NONE;
volatile enum ti_errc_t adc_read_errc = TI_ERRC_NONE;
volatile uint8_t  adc_dev_id     = 0xFF;  /* 0 = ADS124S08, 1 = ADS124S06 */
volatile int32_t adc_ain4_uv    = 0;     /* last good AIN4 reading, microvolts */
volatile uint32_t adc_ok_count   = 0;
volatile uint32_t adc_fail_count = 0;

/* ADC on SENSOR_CS_2 (MCU pin 77, ADC_CS_2 on the schematic). */
static struct adc_spi_dev test_adc_dev = {
    .inst = (uint8_t)SENSOR_SPI_INST,
    .ss_pin = (uint8_t)SENSOR_CS_2
};

/* AIN4 vs AINCOM, gain 1, internal 2.5 V reference. */
static const struct adc_channel ain4_channel = {
    .pos_pin = AIN4,
    .neg_pin = AINCOM,
    .gain = GAIN_1,
    .source = REF_INTERNAL,
    .ref_mv = 2500,
    .name = "ain4"
};

void _start() {
    enum ti_errc_t errc = TI_ERRC_NONE;

    /* Every chip select on the instance has to be listed here, or spi_init()
     * never drives that pin as an output held high. */
    uint8_t ss_pins[1] = { (uint8_t)SENSOR_CS_2 };

    systick_init();

    /* The ADS124S0x only talks SPI mode 1; the driver sets that per transfer
     * anyway, so initializing the bus in mode 1 just avoids the switching. */
    spi_init((uint8_t)SENSOR_SPI_INST, MODE_1, ss_pins, 1, &errc);
    spi_errc = errc;

    /* adc_init() checks the device ID, writes a known config (gain 1,
     * internal 2.5 V ref, 400 SPS) and starts continuous conversions. Each
     * read sets INPMUX from the channel, so AIN4 is selected per read. */
    adc_init(&test_adc_dev, &errc);
    adc_init_errc = errc;
    adc_dev_id = adc_read_device_id(&errc);

    while (1) {
        errc = TI_ERRC_NONE;
        int32_t uv = adc_read_microvolts(&ain4_channel, &errc);
        adc_read_errc = errc;

        if (errc == TI_ERRC_NONE) {
            adc_ain4_uv = uv;
            adc_ok_count++;
        } else {
            adc_fail_count++;
        }

        systick_delay(200);
    }
}
