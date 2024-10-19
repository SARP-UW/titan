/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2024 UW SARP
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * @file common/util/mem.h
 * @authors Aaron McBride
 * @brief Memory manipulation and querying utilities.
 */

#pragma once
#include "common/util/mem.h"

void* ti_memcpy(void* dst, void* src, size_t size)
{
    char *d = dst;
    const char *s = src;

    for (i=0; i<size; i++) {
        *(d + i) = *(s + i);
    }
    return dst;
}

void* ti_memset(void* mem, char value, size_t size){

    char *d = mem;
    for(int i = 0; i < size; i++){
        *(d + i) = value;
    }

    return mem;
}