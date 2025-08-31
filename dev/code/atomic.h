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
 * @file modules/kernel/include/kernel/atomic.h
 * @authors Aaron McBride
 * @brief Atomic operations.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

void ti_atomic_store(volatile uint32_t* dst, uint32_t value);

uint32_t ti_atomic_load(volatile const uint32_t* src);

uint32_t ti_atomic_exchange(volatile uint32_t* dst, uint32_t value);

uint32_t ti_atomic_cmp_exchange(volatile uint32_t* dst, uint32_t exp, uint32_t value);

void ti_atomic_add(volatile uint32_t* dst, uint32_t value);

void ti_atomic_sub(volatile uint32_t* dst, uint32_t value);

void ti_atomic_and(volatile uint32_t* dst, uint32_t value);

void ti_atomic_or(volatile uint32_t* dst, uint32_t value);

void ti_atomic_xor(volatile uint32_t* dst, uint32_t value);