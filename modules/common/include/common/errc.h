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
 * @file modules/common/include/common/errc.h
 * @authors Aaron McBride
 * @brief Error code definitions and utility functions.
 */

#pragma once
#include <stdint.h>

/** @brief TODO */
enum {
  TI_ERRC_NONE = 0,
} ti_errc_t;

void some_function(int arg, ti_errc_t* error);

/**
 * @brief TODO
 * @param errc 
 * @param out 
 */
char* ti_get_errc_name(enum ti_errc_t errc);

/**
 * @brief TODO
 * @param errc
 * @param out 
 */
char* ti_get_errc_desc(enum ti_errc_t errc);