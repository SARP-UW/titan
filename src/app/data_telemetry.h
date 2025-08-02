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
 * @file src/app/data_telemetry.h
 * @authors Charles Faisandier
 * @brief Public interface for the data telemetry subsystem.
 */

#pragma once
#include "tal/error.h"

// Callback function type
typedef void (*data_telemetry_callback_t)(tal_err_t *err);

/**
 * @brief Initializes the data telemetry subsystem.
 *
 * This function sets up the data telemetry to send agglomerated data from data_collector
 * to the ground station.
 *
 * @return tal_err_t* Returns a pointer to an error flag if initialization fails, NULL otherwise.
 */
tal_err_t *data_telemetry_init(data_telemetry_callback_t telemetry_callback);

/**
 * @brief Logs the data from the data collector.
 *
 * This function sends the agglomerated data from data_collector
 * to the ground station.
 * @param buffsize The size of the data_collector buffer.
 * @return tal_err_t* Returns a pointer to an error flag if logging fails, NULL otherwise.
 */
tal_err_t *data_telemetry_start(size_t buffsize);