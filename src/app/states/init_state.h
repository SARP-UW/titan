//
// Created by Joshua Beard on 3/1/26.
//

#pragma once

#include "app/utils/extern_flash.h"

bool init_state_init();

int init_state_run();

bool init_state_destroy();

state build_init_state();

// Function to check if we recovered from a crash
bool init_state_has_recovered_state();

// Function to get the recovered state
enum states_t init_state_get_recovered_state();