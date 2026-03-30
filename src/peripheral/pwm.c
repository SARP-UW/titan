/**
* This file is part of the Titan Flight Computer Project
* Copyright (c) 2026 UW SARP
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
* @file peripheral/pwm.c
* @authors Joshua Beard, Aaron Mcbride, Jude Merritt
* @brief Implementation of the PWM driver interface
* */

#include "peripheral/pwm.h"
#include "peripheral/errc.h"
#include "peripheral/gpio.h"
#include "internal/mmio.h"


/**************************************************************************************************
* @section Macros
**************************************************************************************************/

//#define PWM_CLOCK_FREQ 2000000
#define MAX_DUTY_CYCLE 1000
#define INSTANCE_COUNT 5


/**************************************************************************************************
* @section Private Function Implementations
**************************************************************************************************/

static void check_pwm_config_validity(struct ti_pwm_config_t pwm_config, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (pwm_config.freq <= 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "PWM frequency must be positive"); return; //
    }

    if (pwm_config.clock_freq <= 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "PWM clock frequency must be positive"); return; //
    }

    uint32_t freq_prescaler = pwm_config.clock_freq / pwm_config.freq;
    if (freq_prescaler == 0 || freq_prescaler > UINT16_MAX) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "PWM prescaler calculation invalid"); return; //
    }

    if (pwm_config.duty > MAX_DUTY_CYCLE) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "PWM duty cycle out of range"); return; //
    }

    if (pwm_config.channel < 1 || pwm_config.channel > 4) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "PWM channel out of range"); return; //
    }

    if (pwm_config.instance < 2 || pwm_config.instance > 5) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "PWM instance out of range"); return; //
    }
}


static void pwm_set_pin_vals /* NOLINT(bugprone-easily-swappable-parameters) */(int* pin, int* alt_mode, int32_t instance, int32_t channel) {
    *alt_mode = (instance == 2) ? 1 : 2;
    switch (instance) {
        case 2:
            switch (channel) {
                case 1:
                    *pin = 37; // A0
                    //*pin = 44; // A5
                    //*pin = 108; // A15
                    break;
                case 2:
                    *pin = 38; // A1
                    // *pin = 130; // B3
                    break;
                case 3:
                    *pin = 39; // A2
                    // *pin = 66; // B10
                    break;
                case 4:
                    *pin = 40; // A3
                    // *pin = 67; // B11
                    break;
                default:
                    break;
            }
            break;
        case 3:
            switch (channel) {
                case 1:
                    *pin = 45; // A6
                    // *pin = 93; // C6
                    break;
                case 2:
                    *pin = 46; // A7
                    // *pin = 94; // C7
                    break;
                case 3:
                    *pin = 49; // B0
                    // *pin = 95; // C8
                    break;
                case 4:
                    *pin = 50; // B1
                    // *pin = 96; // C9
                    break;
                default:
                    break;
            }
            break;
        case 4:
            switch (channel) {
                case 1:
                    *pin = 133; // B6
                    break;
                case 2:
                    *pin = 134; // B7
                    break;
                case 3:
                    *pin = 136; // B8
                    break;
                case 4:
                    *pin = 137; // B9
                    break;
                default:
                    break;
            }
            break;
        case 5:
          switch (channel) {
                case 1:
                    *pin = 37; // A0
                    break;
                case 2:
                    *pin = 38; // A1
                    break;
                case 3:
                    *pin = 39; // A2
                    break;
                case 4:
                    *pin = 40; // A3
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}


/**************************************************************************************************
* @section Public Function Implementations
**************************************************************************************************/

void ti_set_pwm(struct ti_pwm_config_t pwm_config, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (pwm_config.instance > INSTANCE_COUNT) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "PWM instance out of range"); return; //
    }

    check_pwm_config_validity(pwm_config, errc); //
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Propagated"); return; //
    }

    // Enable PWM clock
    SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_TIMxEN[pwm_config.instance]);

    // Set up GPIO pin
    int pin = 0;
    int alt_mode = 0;
    pwm_set_pin_vals(&pin, &alt_mode, pwm_config.instance, pwm_config.channel);
    tal_enable_clock(pin);
    tal_set_mode(pin, 2);
    tal_alternate_mode(pin, alt_mode);

    // Determine the appropriate ARR field based on 32-bit (TIM2, TIM5) vs 16-bit (TIM3, TIM4)
    const bool is_32bit_timer = ((pwm_config.instance == 2) || (pwm_config.instance == 5)) != 0;
    field32_t arr_field = G_TIMx_ARR_ARR_L;
    if (is_32bit_timer) {
        arr_field = G_TIMx_ARR_ARR_32B;
    }

    // Set frequency of timer (using the correct 16-bit or 32-bit field)
    uint32_t freq_prescaler = (pwm_config.clock_freq / pwm_config.freq) - 1;

    WRITE_FIELD(G_TIMx_ARR[pwm_config.instance], arr_field, freq_prescaler);

    // Determine the appropriate CCR field based on 32-bit vs 16-bit
    field32_t ccr_field_1 = G_TIMx_CCR1_CCR1_L;
    field32_t ccr_field_2 = G_TIMx_CCR2_CCR2_L;
    field32_t ccr_field_3 = G_TIMx_CCR3_CCR3_L;
    field32_t ccr_field_4 = G_TIMx_CCR4_CCR4_L;
    if (is_32bit_timer) {
        ccr_field_1 = G_TIMx_CCR1_CCR1_32B;
        ccr_field_2 = G_TIMx_CCR2_CCR2_32B;
        ccr_field_3 = G_TIMx_CCR3_CCR3_32B;
        ccr_field_4 = G_TIMx_CCR4_CCR4_32B;
    }

    // Set duty cycle
    uint32_t ccr_value = (freq_prescaler * pwm_config.duty) / MAX_DUTY_CYCLE;

    switch(pwm_config.channel) {
        case 1:
            WRITE_FIELD(G_TIMx_CCR1[pwm_config.instance], ccr_field_1, ccr_value);
            break;
        case 2:
            WRITE_FIELD(G_TIMx_CCR2[pwm_config.instance], ccr_field_2, ccr_value);
            break;
        case 3:
            WRITE_FIELD(G_TIMx_CCR3[pwm_config.instance], ccr_field_3, ccr_value);
            break;
        case 4:
            WRITE_FIELD(G_TIMx_CCR4[pwm_config.instance], ccr_field_4, ccr_value);
            break;
        default:
            TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid PWM channel for CCR"); return; //
    }

    // Set to output compare
    if (pwm_config.channel == 1 || pwm_config.channel == 2) {
        WRITE_FIELD(G_TIMx_CCMR1_OUTPUT[pwm_config.instance], G_TIMx_CCMR1_OUTPUT_OCxM[pwm_config.channel], 0b0110);
        SET_FIELD(G_TIMx_CCMR1_OUTPUT[pwm_config.instance], G_TIMx_CCMR1_OUTPUT_OCxPE[pwm_config.channel]);
    } else if (pwm_config.channel == 3 || pwm_config.channel == 4) {
        WRITE_FIELD(G_TIMx_CCMR2_OUTPUT[pwm_config.instance], G_TIMx_CCMR2_OUTPUT_OCxM[pwm_config.channel], 0b0110);
        SET_FIELD(G_TIMx_CCMR2_OUTPUT[pwm_config.instance], G_TIMx_CCMR2_OUTPUT_OCxPE[pwm_config.channel]);
    }

    // Enable PWM channel output on the timer
    SET_FIELD(G_TIMx_CCER[pwm_config.instance], G_TIMx_CCER_CCxE[pwm_config.channel]);
    // Enable the timer
    SET_FIELD(G_TIMx_CR1[pwm_config.instance], G_TIMx_CR1_CEN);
    // Enable PWM output
    SET_FIELD(G_TIMx_CR1[pwm_config.instance], G_TIMx_CR1_ARPE);
}