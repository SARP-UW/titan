#include "app/state.h"


//     -- ( ) SAFE/ABORT: Venting to abort mission
//     ~~~ ( ) Vent everything
bool safe_state_init(){

    return 1;
}

int safe_state_run(){
    return -1; // TODO, decide where this state goes
}

bool safe_state_destroy(){
    return 1;
}

state build_safe_state() {
    const state safe_state = {
        .init = &safe_state_init,
        .run = &safe_state_run,
        .destroy = &safe_state_destroy
    };
    return safe_state;
}