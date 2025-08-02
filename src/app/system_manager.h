// src/app/system_manager.h
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
 * @file src/app/system_manager.h
 * @authors Charles Faisandier
 * @brief Public interface for the system manager module.
 */

#include "tal/error.h" // For error_t

/**
 * @brief Initializes the system manager and all its controlled application modules.
 * This includes sensor drivers, communication managers, data logging, etc.
 * Should be called once during application startup from main.c.
 *
 * @return NULL if initialization is successful, or a tal_err_t error if initialization fails.
 */
tal_err_t *system_manager_init(void);

/**
 * @brief Runs the main application loop.
 * This function typically never returns and handles the continuous processing
 * and management of all system tasks.
 */
void system_manager_run(void);