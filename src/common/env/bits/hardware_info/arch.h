/**
 * This file is part of the Titan Avionics Library
 * Copyright (c) 2024 Aaron McBride.
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
 * @file common/env/bits/hardware_info/arch.h 
 * @authors Aaron McBride 
 * @brief Contains information about the target architecture.
 */

#pragma once

/**************************************************************************************************
 * @section Target Architecture Information
 **************************************************************************************************/

#if defined(TI_ARCH_ARMV7)
  #define TI_ARCH_SIZE 32
  // TODO
#else
  #error TITAN ERROR: Unkown architecture.
#endif