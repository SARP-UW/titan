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
 * @file modules/kernel/include/kernel/alloc.h
 * @authors Aaron McBride
 * @brief Memory allocation facilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

void* ti_alloc(int32_t size);

bool ti_can_alloc(int32_t size);

void ti_free(void* mem);

bool ti_is_alloc(void* mem);

int32_t ti_get_alloc_size(void* mem);