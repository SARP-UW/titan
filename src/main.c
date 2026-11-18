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
#include "peripheral/gpio.h"
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
    tal_enable_clock((int)RS485_DE);
    tal_enable_clock((int)RS485_RE);
    tal_set_mode((int)RS485_DE, 1);
    tal_set_mode((int)RS485_RE, 1);
    tal_set_pin((int)RS485_DE, 1);
    tal_set_pin((int)RS485_RE, 1);

    tal_enable_clock(39);
    tal_set_mode(39, 1);


    while(1){
        tal_set_pin(39, 1);
        for (int i = 0; i < 100000; i++){
            asm("NOP");
        }
        tal_set_pin(39, 0);
        for (int i = 0; i < 100000; i++){
            asm("NOP");
        }
    }
}
