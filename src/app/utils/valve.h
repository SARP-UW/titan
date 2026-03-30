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
 * @file app/utils/valve.h
 * @authors Joshua Beard
 * @brief Utility functions to actuate valves by name
 */


#include "src/util/error.h"

enum Valve {
    
};

/**
 * @param valve Valve name to actuate as defined in the Valve enum
 * @param actuated True if providing power to valve, False if unpowering valve
 * 
 * @note The actuated parameter is done this way (instead of open/closed) because some
 * valves may have a different default state and it would become confusing in software
 * to need to track which ones need power or a lack of power to reach a commanded state
 */
tal_err_t set_valve(enum Valve valve, bool actuated){

}