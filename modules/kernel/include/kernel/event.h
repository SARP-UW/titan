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
 * @file modules/kernel/include/kernel/event.h
 * @authors Aaron McBride
 * @brief Event synchronization primitives.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

struct ti_event_t {
  const int32_t id;
  const void* const handle;
};

#define TI_EVENT_MEM_SIZE 0

struct ti_event_t ti_create_event(void* mem);

void ti_destroy_event(struct ti_event_t event);

void ti_trigger_event(struct ti_event_t event);

bool ti_await_event(struct ti_event_t event, int64_t timeout);

bool ti_is_event_valid(struct ti_event_t event);

bool ti_is_event_equal(struct ti_event_t event_1, struct ti_event_t event_2);