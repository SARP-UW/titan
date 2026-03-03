//
// Created by Joshua Beard on 1/17/26.
//

#include "state.h"
#include "states/init_state.h"
#include "states/standby_state.h"
#include "states/fill_state.h"
#include "states/hold_state.h"
#include "states/armed_state.h"
#include "states/fire_state.h"
#include "states/safe_state.h"

#define NUM_STATES 7
static state states[NUM_STATES];

void setup_states() {
    states[0] = build_init_state();
    states[1] = build_standby_state();
    states[2] = build_fill_state();
    states[3] = build_hold_state();
    states[4] = build_armed_state();
    states[5] = build_fire_state();
    states[6] = build_safe_state();
}

void run_state_machine() {
    // NOTE: in our final impl, state[0] should be a boot state that also
    // looks in our flash memory to see if we are recovering from a crash,
    // and if so it returns the state to go to (this would be sick)

    state curr = states[0];

    while (1) {
        curr.init();
        const int next_state = curr.run();
        curr.destroy();

        if (next_state == -1) {
            break;
        }
        curr = states[next_state];
    }
}
