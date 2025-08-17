/**
 * This file is part of the Titan Project.
 * Copyright (c) 2025 UW SARP
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
 * @file modules/kernel/include/kernel/time.h
 * @authors Aaron McBride
 * @brief Time related utilities.
 */

#pragma once
#include <stdint.h>

/**
 * @brief TODO
 * @return 
 */
int64_t ti_get_time(void);

/**
 * @brief TODO
 * @param duration 
 */
void ti_sleep(int64_t duration);

/**
 * @brief TODO
 * @param time 
 */
void ti_sleep_until(int64_t time);

/**
 * @brief TODO
 * @param duration 
 */
void ti_wait(int64_t duration);

/**
 * @brief TODO
 * @param time 
 */
void ti_wait_until(int64_t time);