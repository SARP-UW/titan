/**
 * This file is part of the Titan Project.
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
 * @file modules/util/include/util/debug.h
 * @authors Aaron McBride
 * @brief Debugging utilities.
 */

#pragma once
#include <stdbool.h>

/**
 * @brief Halts the program if the given condition is false.
 * @param cond (bool) The target condition.
 * @note This function does nothing if TI_DEBUG is false.
 */
void ti_assert(bool cond);

/**
 * @brief Triggers a breakpoint in the program.
 * @note This function does nothing if TI_DEBUG is false.
 */
void ti_breakpoint(void);