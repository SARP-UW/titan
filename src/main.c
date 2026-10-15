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
#include "peripheral/gpio.h"
#include <stdint.h>
#include <stdio.h>

/* Pause the debugger and inspect these. */
volatile extern int32_t  adc_ain0_uv = 0;         // Last good AIN0-vs-AINCOM reading, microvolts
volatile extern uint8_t  adc_dev_id = 0xFF;       // 0 = ADS124S08, 1 = ADS124S06
volatile uint32_t adc_ok_count = 0;        // Successful conversions
volatile uint32_t adc_fail_count = 0;      // Failed conversions

volatile enum ti_errc_t spi_errc      = TI_ERRC_NONE;  // spi_init() result
volatile enum ti_errc_t adc_init_errc = TI_ERRC_NONE;  // adc_init() result
volatile enum ti_errc_t adc_read_errc = TI_ERRC_NONE;  // Last adc_read_microvolts() result

void _start() {
    enum ti_errc_t errc = TI_ERRC_NONE;

    /* Every chip select on the instance has to be listed here, or spi_init()
     * never drives that pin as an output held high. */
    uint8_t ss_pins[1] = { (uint8_t)IMU_1_CS };

    systick_init();

    /* The ADS124S0x only talks SPI mode 1; the driver sets that per transfer
     * anyway, so initializing the bus in mode 1 just avoids the switching. */
    spi_init((uint8_t)SENSOR_SPI_INST, MODE_1, ss_pins, 1, &errc);
    spi_errc = errc;

    uint8_t pin = 101; // USB_DATA+
    tal_enable_clock(pin);
    tal_set_mode(pin, 1); // gpio


    struct imu_spi_dev imu_dev = {
        .inst = SENSOR_SPI_INST,
        .ss_pin = ss_pins[0],
    };
    imu_init(&imu_dev, &errc);
    struct imu_result imu_result;
    imu_transfer(&imu_dev, &imu_result, &errc);

    while (1) {
        tal_set_pin(pin, 1);
        systick_delay(50);
        tal_set_pin(pin, 0);
        systick_delay(50);
    }
}
