/**
 * This file is part of the Titan Avionics Library
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
 * @file src/lib/float/fp_value.c
 * @authors Aaron McBride
 * @brief Implementation of special fp value functions.
 */

#include "src/lib/float/fp_impl.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  float tal_nan_f(void) {
    static const uint32_t flt_nan_value = flt_exp_mask | flt_mant_mask;
    return to_flt__(flt_nan_value);
  }

  double tal_nan_d(void) {
    static const uint64_t dbl_nan_value = dbl_exp_mask | dbl_mant_mask;
    return to_dbl__(dbl_nan_value);
  }

  float tal_inf_f(void) {
    static const uint32_t flt_inf_value = flt_exp_mask;
    return to_flt__(flt_inf_value);
  }

  double tal_inf_d(void) {
    static const uint64_t dbl_inf_value = dbl_exp_mask;
    return to_dbl__(dbl_inf_value);
  }

#if defined(__cplusplus)
  } // extern "C"
#endif