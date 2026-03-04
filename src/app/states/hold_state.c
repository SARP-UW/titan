#include "app/state.h"

//     - ( ) HOLD: Maintain launch ready state
//     ~~~ ( ) Monitor leaks or pressure drops
//     ~~~ ( ) Keep GSE Connected for power/data
//     ~~~ ( ) Vent ethonol tank to equalize with nitrous tank

bool hold_state_init(){

    return 1;
}

int hold_state_run(){
    return 4;
}

bool hold_state_destroy(){
    return 1;
}

state build_hold_state() {
    const state hold_state = {
        .init = &hold_state_init,
        .run = &hold_state_run,
        .destroy = &hold_state_destroy
    };
    return hold_state;
}