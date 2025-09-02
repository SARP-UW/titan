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
 * @file modules/util/src/errc.c
 * @authors Aaron McBride
 * @brief Implementation of error code utility functions.
 */

#include "util/errc.h"

const char* ti_get_errc_name(enum ti_errc_t errc_in, enum ti_errc_t* errc_out) {
  switch (errc_in) {
    case TI_ERRC_NONE:          return "No Error";
    case TI_ERRC_UNKNOWN:       return "Unknown Error";
    case TI_ERRC_INTERNAL:      return "Internal Error";
    case TI_ERRC_INVALID_ARG:   return "Invalid Argument";
    case TI_ERRC_HOST:          return "Host Error";
    case TI_ERRC_NO_MEM:        return "No Memory";
    case TI_ERRC_INVALID_OP:    return "Invalid Operation";
    case TI_ERRC_INVALID_STATE: return "Invalid State";
    case TI_ERRC_UNSUPPORTED:   return "Unsupported Operation";
    case TI_ERRC_TIMEOUT:       return "Timeout Error";
    default: {
      *errc_out = TI_ERRC_INVALID_ARG;
      return NULL;
    }
  }
}

const char* ti_get_errc_desc(enum ti_errc_t errc_in, enum ti_errc_t* errc_out) {
  switch (errc_in) {
    case TI_ERRC_NONE:          return "No error occurred.";
    case TI_ERRC_UNKNOWN:       return "Unknown error occurred.";
    case TI_ERRC_INTERNAL:      return "Internal error occurred.";
    case TI_ERRC_INVALID_ARG:   return "Invalid argument passed to function.";
    case TI_ERRC_HOST:          return "Error occurred on the host machine.";
    case TI_ERRC_NO_MEM:        return "Memory allocation failed.";
    case TI_ERRC_INVALID_OP:    return "The requested operation is invalid.";
    case TI_ERRC_INVALID_STATE: return "The requested operation cannot be completed due to the state of the program.";
    case TI_ERRC_UNSUPPORTED:   return "The requested operation is not implemented/supported.";
    case TI_ERRC_TIMEOUT:       return "A timeout occurred.";
    default: {
      *errc_out = TI_ERRC_INVALID_ARG;
      return NULL;
    }
  }
}