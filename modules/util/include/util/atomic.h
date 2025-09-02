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
 * @file modules/util/include/util/atomic.h
 * @authors Aaron McBride
 * @brief Atomic operations.
 */

#pragma once

#include <stdint.h>
#include <stdbool.h> 

/**
 * @brief Atomically loads a value from memory (unsigned).
 * @param src (const volatile uint32_t*) The location to load from.
 * @returns (uint32_t) The value stored at @p [src].
 */
uint32_t ti_atomic_load(const volatile uint32_t* src);

/**
 * @brief Atomically stores a value to memory.
 * @param dst (volatile uint32_t*) The location to store to.
 * @param value (uint32_t) The value to store.
 */
void ti_atomic_store(volatile uint32_t* dst, uint32_t value);

/**
 * @brief Atomically exchanges a value in memory.
 * @param dst (volatile uint32_t*) The location to exchange the value.
 * @param value (uint32_t) The new value to store.
 * @returns (uint32_t) The value previously stored at @p [dst].
 */
uint32_t ti_atomic_exchange(volatile uint32_t* dst, uint32_t value);

/**
 * @brief Atomically compares and exchanges a value in memory.
 * @param dst (volatile uint32_t*) The location to compare and exchange the value.
 * @param expected (uint32_t*) A pointer to the expected value to compare against and 
 *                 the location where the initial value at @p [dst] will be stored.
 * @param desired (uint32_t) The new value to store if the comparison is successful.
 * @return (bool) True if the exchange was successful, false otherwise.
 * @note - If the value at @p [dst] equals the value at @p [expected] then @p [dst]
 *         will be set to @p [desired].
 * @note - If the value at @p [dst] does not equal the value at @p [expected] then
 *         the value at @p [expected] will be updated with the value at @p [dst] and
 *         @p [dst] WILL NOT be set to @p [desired].
 */
bool ti_atomic_cmp_exchange(volatile uint32_t* dst, uint32_t* expected, uint32_t desired);

/**
 * @brief Performs an atomic addition/assignment operation on a value in memory.
 * @param dst (volatile uint32_t*) The location to perform the operation on.
 * @param value (uint32_t) The value to add to that at @p [dst].
 * @returns (uint32_t) The initial value stored at @p [dst].
 * @note - This function atomically fetches the value at @p [dst], adds it to
 *         @p [value], and stores the result back to @p [dst].
 */
uint32_t ti_atomic_add(volatile uint32_t* dst, uint32_t value);

/**
 * @brief Performs an atomic subtraction/assignment operation on a value in memory.
 * @param dst (volatile uint32_t*) The location to perform the operation on.
 * @param value (uint32_t) The value to subtract from that at @p [dst].
 * @returns (uint32_t) The initial value stored at @p [dst].
 * @note - This function atomically fetches the value at @p [dst], subtracts
 *         @p [value] from it, and stores the result back to @p [dst].
 */
uint32_t ti_atomic_sub(volatile uint32_t* dst, uint32_t value);