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
 * @file common/util/math.h
 * @authors Joshua Beard
 * @brief Math utilities
*/
#include <stdint.h>
// 8, 32, 64
#ifndef MATH_H
#define MATH_H

int abs(int x);
int pow(int x, uint32_t n);

/**
 * @param x
 * @param multiple
 * @return x floored to the nearest multiple of "multiple"
 * eg: floor(10, 5) = 10.  floor(10, 4) = 8
 */
int floor(int x, int multiple);
int ceil(int x, int multiple);




#endif //MATH_H
