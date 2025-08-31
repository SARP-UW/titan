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
#include "util/errc.h"

int64_t ti_get_time(void);

void ti_sleep(int64_t duration, enum ti_errc_t* errc_out);

void ti_sleep_until(int64_t time, enum ti_errc_t* errc_out);

void ti_wait(int64_t duration, enum ti_errc_t* errc_out);

void ti_wait_until(int64_t time, enum ti_errc_t* errc_out);


int64_t ti_micros_to_time(int64_t micros, enum ti_errc_t* errc_out);

int64_t ti_time_to_micros(int64_t time, enum ti_errc_t* errc_out);

int64_t ti_millis_to_time(int64_t millis, enum ti_errc_t* errc_out);

int64_t ti_time_to_millis(int64_t time, enum ti_errc_t* errc_out);

int64_t ti_seconds_to_time(int64_t seconds, enum ti_errc_t* errc_out);

int64_t ti_time_to_seconds(int64_t time, enum ti_errc_t* errc_out);

int64_t ti_minutes_to_time(int64_t minutes, enum ti_errc_t* errc_out);

int64_t ti_time_to_minutes(int64_t time, enum ti_errc_t* errc_out);

int64_t ti_hours_to_time(int64_t hours, enum ti_errc_t* errc_out);

int64_t ti_time_to_hours(int64_t time, enum ti_errc_t* errc_out);

int64_t ti_days_to_time(int64_t days, enum ti_errc_t* errc_out);

int64_t ti_time_to_days(int64_t time, enum ti_errc_t* errc_out);