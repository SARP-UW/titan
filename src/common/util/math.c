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
 * @file common/util/math.c
 * @authors Aaron McBride, Joshua Beard
 * @brief Math utilities
 */


#include <stdint.h>
#include "math.h"

int abs(const int x)
{
    if(x < 0) {
        return -x;
    }
    return x;
}


int pow(int x, const uint32_t n)
{
    if(n == 0) {
        return 1;
    }
    for (int i = 0; i < n - 1; i++) {
        x *= x;
    }
    return x;
}

int floor(const int x, const int multiple)
{
    return x - x % multiple;
}

int ceil(int x, int multiple)
{
    return floor(x, multiple) + multiple;
}
