#include "app/state.h"


//     -- ( ) FIRING: Deliver propelants to manifold
//     ~~~ ( ) Open main propelant valves
//     ~~~ ( ) Execute control loop for engine burn
//     ~~~ ( ) REcord telemetry to Sd card

bool fire_state_init(){

    return 1;
}

int fire_state_run(){
    return 6;
}

bool fire_state_destroy(){
    return 1;
}

state build_fire_state() {
    const state fire_state = {
        .init = &fire_state_init,
        .run = &fire_state_run,
        .destroy = &fire_state_destroy
    };
    return fire_state;
}