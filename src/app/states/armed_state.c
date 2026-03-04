#include "app/state.h"

//     -- ( ) ARMED: Final Countdown Sequence and umbilical disconnect
//     ~~~ ( ) switch power from umbilical to battery
//     ~~~ ( ) arm igniter 

bool armed_state_init(){

    return 1;
}

int armed_state_run(){
    return 5;
}

bool armed_state_destroy(){
    return 1;
}

state build_armed_state() {
    const state armed_state = {
        .init = &armed_state_init,
        .run = &armed_state_run,
        .destroy = &armed_state_destroy
    };
    return armed_state;
}