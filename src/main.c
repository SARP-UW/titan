
#include "string.h"
#include <stdint.h>
#include "app/utils/extern_flash.h"
#include "app/utils/packets.h"
#include "app/utils/state_comm.h"
#include "devices/umbilical.h"
#include "peripheral/errc.h"
#include "peripheral/gpio.h"
#include "peripheral/qspi.h"
#include "peripheral/systick.h"
#include "peripheral/uart.h"
#include "peripheral/pwm.h"

#define CLOCK_FREQ 64000000
#define PWM_FREQ 200
#define OPEN 700
#define CLOSED 300

#define OMV_INPUT_PIN 43
#define FMV_INPUT_PIN 40

struct ti_pwm_config_t OMV_open_config = {
    2, 1, PWM_FREQ, OPEN, CLOCK_FREQ
};

struct ti_pwm_config_t OMV_closed_config = {
    2, 1, PWM_FREQ, CLOSED, CLOCK_FREQ
};

struct ti_pwm_config_t FMV_open_config = {
    5, 3, PWM_FREQ, OPEN, CLOCK_FREQ
};

struct ti_pwm_config_t FMV_closed_config = {
    5, 3, PWM_FREQ, CLOSED, CLOCK_FREQ
};

// MAIN PROGRAM

void set_servos() {

    tal_enable_clock(OMV_INPUT_PIN);
    tal_enable_clock(FMV_INPUT_PIN);
    tal_set_mode(OMV_INPUT_PIN, 0);
    tal_set_mode(FMV_INPUT_PIN, 0);
    tal_pull_pin(OMV_INPUT_PIN, -1);
    tal_pull_pin(FMV_INPUT_PIN, -1);

    tal_enable_clock(45);
    tal_set_mode(45, 1);
    tal_set_pin(45, 0);



    while (1) {
        // Set OMV servo

        if (tal_read_pin(OMV_INPUT_PIN)) {
            ti_set_pwm(OMV_open_config, (void*)0);
        } else {
            ti_set_pwm(OMV_closed_config, (void*)0);
        }

        // Set FMV servo
        if (tal_read_pin(FMV_INPUT_PIN)) {
            ti_set_pwm(FMV_open_config, (void*)0);
        } else {
            ti_set_pwm(FMV_closed_config, (void*)0);
        }
    }
}

void _start() {
    set_servos();
}

