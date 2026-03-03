#include "app/state.h"


//     --- ( ) FILLING: Remote delivery of fuel
//     ~~~ ( ) Actuate GSE Valves to load propellant
//     ~~~ ( ) Monitor mass flow and pressure
//     ~~~ ( ) If overpressurization is detected, auto abort to SAFE/ABORT
bool fill_state_init(){

    return 1;
}

int fill_state_run(){
    return 3;
}

bool fill_state_destroy(){
    return 1;
}

state build_fill_state() {
    const state fill_state = {
        .init = &fill_state_init,
        .run = &fill_state_run,
        .destroy = &fill_state_destroy
    };
    return fill_state;
}