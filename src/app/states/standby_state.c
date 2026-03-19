//
// Created by Joshua Beard on 3/1/26.
//

//     -- ( ) STANDBY: Rocket on pad awaiting instruction
//     ~~~ ( ) Await the start fill command
#include "app/state.h"

bool standby_state_init(){

    return 1;
}

int standby_state_run(){
    return 2;
}

bool standby_state_destroy(){
    return 1;
}

state build_standby_state() {
    const state standby_state = {
        .init = &standby_state_init,
        .run = &standby_state_run,
        .destroy = &standby_state_destroy
    };
    return standby_state;
}