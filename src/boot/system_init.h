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
 * @file src/boot/system_init.h
 * @authors Charles Faisandier
 * @brief Core system initialization for the STM32H745XIH3 MCU
 */

#pragma once
#include "tal/error.h" 

/**
 * @brief Performs the essential low-level system initialization.
 * This function configures the microcontroller's core components such as:
 * - System clocks (HCLK, PCLKs, CPU clocks)
 * - Flash memory latency
 * - Basic power domains
 * - Enables clocks for essential peripheral buses (e.g., AHB, APB for DMA, GPIO)
 * - Configures initial interrupt controller settings (e.g., NVIC grouping)
 *
 * @return tal_err_t* Returns a pointer to an error flag if initialization fails, NULL otherwise.
 */
tal_err_t *system_init(void);