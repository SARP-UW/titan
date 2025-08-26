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
 * @file modules/util/include/util/errc.h
 * @authors Aaron McBride
 * @brief Error code definitions and utility functions.
 */

#pragma once
#include <stddef.h>
#include <stdint.h>
#include "util/errc.h"

/** @brief Error code enum. */
enum ti_errc_t {
  TI_ERRC_NONE = 0, /** @brief No error occurred. */
  TI_ERRC_UNKNOWN,  /** @brief Unknown error occurred. */
  TI_ERRC_INVALID_ARG, /** @brief Invalid argument passed to function. */
};

/**
 * @brief Gets the name of an error code.
 * @param errc_in (enum ti_errc_t) The target error code.
 * @param errc_out (enum ti_errc_t*) Output error code for this function.
 * @returns (const char*) String containing the name of @p [errc].
 */
const char* ti_get_errc_name(enum ti_errc_t errc_in, enum ti_errc_t* errc_out);

/**
 * @brief Gets the description of an error code.
 * @param errc_in (enum ti_errc_t) The target error code.
 * @param errc_out (enum ti_errc_t*) Output error code for this function.
 * @returns (const char*) String containing the description of @p [errc].
 */
const char* ti_get_errc_desc(enum ti_errc_t errc_in, enum ti_errc_t* errc_out);