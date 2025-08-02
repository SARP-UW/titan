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
 * @file include/tal/error.h
 * @authors Joshua Beard & Aaron McBride & Charles Faisandier
 * @brief Error handling utilities implementation.
 */
#include "tal/error.h"
#include <stddef.h>

/**************************************************************************************************
 * @section Public API Implementation
 **************************************************************************************************/

/**
 * @brief Checks if the given error flag indicates an error.
 *
 * @param err The error to check.
 * @return true if the error indicates an error, false otherwise.
 */
bool tal_is_err(const tal_err_t* err) {
        // If the total error count is greater than zero, an error has occurred.
        if (err == NULL) {
            return false; // If the flag is NULL, we cannot determine if an error occurred.
    }
    // Check the is_error field to determine if this flag represents an error.
    return err->is_error;
}

/**************************************************************************************************
 * @internal Implementation
 **************************************************************************************************/

/**
 * @internal
 * @brief Internal implementation to log an error to the flag.
 *
 * @param flag The error flag to log the error to.
 * @param error A pointer to the static error struct.
 */
void tal_raise_impl__(tal_flag_t* flag, const tal_err_t* error) {
    // Check if the error list has space for another error.
    if (flag->err_count < tal_max_err_cnt) {
        // If there is space, store the pointer to the new error.
        flag->err_list[flag->err_count] = error;
    }
    
    // Increment the total error count, regardless of whether it was logged.
    flag->err_count++;
}