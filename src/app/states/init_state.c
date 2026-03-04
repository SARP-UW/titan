//
// Created by Joshua Beard on 1/17/26.
//

#pragma once
#include <stdint.h>
#include "app/state.h"
#include "init_state.h"

#include "peripheral/gpio.h"
#include "peripheral/qspi.h"
#include "peripheral/errc.h"


//     ~~~ ( ) Look in flash mem to see if we are recovering from a crash
//     ~~~ ( ) initializes everything
//     ~~~ ( ) Establish radio and umbillical communication
//     ~~~ ( ) Verify all actuators and valves in safe position
bool init_state_init() {

    qspi_init(); // probably should return a ti_errc_t

    return 1;
}

int init_state_run() {
    // index of next state, NOT true
    // also this state has no run block
    return 1;
}

bool init_state_destroy() {
    // nothing to do
    return 1;
}

state build_init_state() {
    const state init_state = {
        .init = &init_state_init,
        .run = &init_state_run,
        .destroy = &init_state_destroy
    };
    return init_state;
}
