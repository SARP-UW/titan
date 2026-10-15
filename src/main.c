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
#include "peripheral/pwm.h"

#include <stdint.h>


void _start() {
    
    int pin = 136;
    
    tal_enable_clock(pin);
    tal_set_mode(pin, 1);

    systick_init();

    // struct ti_pwm_config_t pwm = {
    //     4, 3, 500, 500, 16*4000000
    // };
    // enum ti_errc_t error = TI_ERRC_NONE;

    // ti_set_pwm(pwm, &error);

    
    while(true){
        for(int j = 0; j < 100; j++){
            tal_set_pin(pin, 1);
            for(uint64_t i = 0; i < 3209; i++){
                asm volatile ("NOP");
            }
            tal_set_pin(pin, 0);
            for(uint64_t i = 0; i < 39583; i++){
                asm volatile ("NOP");
            }
        }

        for(int j = 0; j < 100; j++){
            tal_set_pin(pin, 1);
            for(uint64_t i = 0; i < (3209 + 500); i++){
                asm volatile ("NOP");
            }
            tal_set_pin(pin, 0);
            for(uint64_t i = 0; i < (39583 - 500); i++){
                asm volatile ("NOP");
            }
        }
    }
}
