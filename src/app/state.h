//
// Created by Joshua Beard on 1/17/26.
//

#pragma once
#include <stdbool.h>

typedef struct {
    bool (*init)(void); 
    int (*run)(void);
    bool (*destroy)(void); 
} state;


