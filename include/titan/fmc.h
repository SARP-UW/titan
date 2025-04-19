/**
 * This file is part of the Titan Flight Computer Project
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
 * @file common/platform/fmc.h
 * @authors Garv Maheshwari
 * @brief Driver for the FMC to interface with 128mb SDRAM
 */

 #pragma once
 #include <stdint.h>
 #include <stddef.h>
 #include <stdbool.h>
 
 #if defined(__cplusplus)
   extern "C" {
 #endif
 

 
void init_fmc_sdram();

 

//Expansion to internal memory automatically
//Init and DeInit function -DeInit is not necessary for MVP
 
 #if defined(__cplusplus)
   }
 #endif