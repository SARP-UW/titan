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
 * @authors Charles Faisandier
 * @brief Error logging and reporting subsystem.
 */

#pragma once
#include "tal/error.h" 
#include "app/error_handler.h" 

/**
 * @brief Initializes the launch sequence subsystem.
 * * @note This function should be called during system startup to set up 
 * the launch sequence parameters and state.
 */
void launch_sequence_init(void);

/**
 * @brief Starts the launch sequence.
 * * @note This function initiates the launch sequence, which may involve 
 * checking system readiness, starting sensors, and preparing for flight.
 */
void launch_sequence_start(void);