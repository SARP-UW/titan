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
 * @file include/tal/error_handler.h
 * @authors Joshua Beard & Aaron McBride & Charles Faisandier
 * @brief Error logging and reporting subsystem.
 */

#pragma once

#include "tal/error.h" // The error logger subsystem still needs to know about this

/**
 * @brief Initializes the error logger subsystem.
 * * @note This function should be called during system startup to set up 
 * the persistent flash memory and radio communication for error reporting.
 */
void error_handler_init(void);

/**
 * @brief Logs a critical, unrecoverable error.
 * * @param error_details A pointer to the tal_err_t struct containing the 
 * details of the critical error.
 * * @note This function logs the error to a persistent flash memory location 
 * with a timestamp. The log entry is explicitly marked as a critical event. 
 * The error is also immediately transmitted over the radio.
 */
void error_handler_log_critical(const tal_err_t* error_details);

/**
 * @brief Logs one or more non-critical, recoverable errors.
 * * @param error_details A pointer to the tal_flag_t struct containing a 
 * list of non-critical errors that have occurred.
 * * @note This function iterates through the error list in the provided 
 * tal_flag_t. Each error is logged to persistent flash memory with a 
 * timestamp and transmitted over the radio.
 */
void error_handler_log_non_critical(const tal_flag_t* error_details);

/**
 * @brief Logs a successful operation or event.
 * * @param desc A description of the successful operation or event.
 * * @note This function logs a success message to the persistent flash memory  
 * and to radio with a timestamp. It's especially useful for reporting that
 * the basic system init was successful, so we know the system is alive.
 */
void error_handler_log_successful(char *desc);