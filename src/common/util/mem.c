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

    for (int i=0; i<size; i++) {
        *(d + i) = *(s + i);
    }
    return dst;
}

void* ti_memset(void* mem, char value, size_t size)
{

    char *d = mem;
    for(int i = 0; i < size; i++){
        *(d + i) = value;
    }

    return mem;
}

void* ti_memexch(void* dst, void* src, char value, size_t size)
{
    ti_memcpy(dst, src, size);
    ti_memset(src, value, size);
    return dst;
}

void ti_memswap(void* mem_a, void* mem_b, size_t size)
{
    char *pA = mem_a;
    char *pB = mem_b;

    for(int i = 0; i < size; i++){
        char a = *(pA + i);
        *(pA + i) = *(pB + i);
        *(pB + i) = a;
    }
}


int ti_memcmp(void* mem_a, void* mem_b, size_t size)
{
    char *pA = mem_a;
    char *pB = mem_b;


    for(int i = 0; i < size; i++){
        char a = *(pA + i);
        char b = *(pB + i);

        if(a == b){
            continue;
        }
        return a < b ? -1 : 1;
    }
    return 0;
}