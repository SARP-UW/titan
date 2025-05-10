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
 * @file dev/src/clock.h
 * @authors Charles Faisandier
 * @brief header for general clock
 */
#pragma once
#include <stdint.h>
#include <stdbool.h>

# if defined(__cplusplus)
extern "C" {
# endif

  typedef struct {
    int16_t hours;
    int16_t mins;
    int16_t secs;
    int16_t years;
    int16_t weekday;
    int16_t month;
    int16_t date;
    double subsec;
  } DateTime;

  DateTime read_clock();

  bool write_clock(DateTime datetime);

  bool init_clock();

# if defined(__cplusplus)
}
# endif
