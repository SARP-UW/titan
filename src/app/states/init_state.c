//
// Created by Joshua Beard on 1/17/26.
//

#include <stdint.h>
#include "app/state.h"
#include "init_state.h"
#include "app/utils/extern_flash.h"

#include "peripheral/gpio.h"
#include "peripheral/qspi.h"
#include "peripheral/errc.h"


//     ~~~ ( ) Look in flash mem to see if we are recovering from a crash
//     ~~~ ( ) initializes everything
//     ~~~ ( ) Establish radio and umbillical communication
//     ~~~ ( ) Verify all actuators and valves in safe position

// Static variable to store the recovered state
static enum states_t recovered_state = INIT_STATE;
static bool has_recovered_state = false;

bool init_state_init() {
    enum ti_errc_t errc;

    qspi_init(); // probably should return a ti_errc_t
    ti_log_init(); /* Scan flash log region; safe to ignore return — logger degrades gracefully */

    // Check if we're recovering from a crash
    if (check_saved_state()) {
        enum states_t prev_state = get_prev_state(&errc);
        if (errc != TI_ERRC_NONE) {
            TI_SET_ERRC(&errc, errc, "Failed to get previous state from flash");
        } else {
            recovered_state = prev_state;
            has_recovered_state = true;
            // TODO: Handle recovery from previous state
            // This could involve:
            // - Restoring valve/servo positions
            // - Re-initializing sensors that were active
            // - Notifying comms controller
        }
    }

    log_state(INIT_STATE, &errc);
    if (errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to log init state");
    }

    return 1;
}

int init_state_run() {
    // index of next state, NOT true
    // also this state has no run block

    // If we recovered from a crash, we might want to go to a different state
    // For now, we always go to standby (state 1)
    // TODO: Implement logic to transition to recovered state if appropriate
    return 1;
}

bool init_state_destroy() {
    // nothing to do
    return 1;
}

// Function to check if we recovered from a crash
bool init_state_has_recovered_state() {
    return has_recovered_state;
}

// Function to get the recovered state
enum states_t init_state_get_recovered_state() {
    return recovered_state;
}

state build_init_state() {
    const state init_state = {
        .init = &init_state_init,
        .run = &init_state_run,
        .destroy = &init_state_destroy
    };
    return init_state;
}
