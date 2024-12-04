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
 * @file src/lib/float/fp_classify.c
 * @authors Aaron McBride
 * @brief Implementation of fp classification utilities.
 */

#include "src/lib/float/fp_impl.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  bool tal_is_finite_f(const float value) {
    return !tal_is_nan_f(value) && !tal_is_inf_f(value);
  }

  bool tal_is_finite_d(const double value) {
    return !tal_is_nan_d(value) && !tal_is_inf_d(value);
  }

  bool tal_is_nan_f(const float value) {
    const uint32_t bit_value = to_uint32__(value);
    return (bit_value & flt_exp_mask) == flt_exp_mask &&
        (bit_value & flt_mant_mask) != 0u;
  }

  bool tal_is_nan_d(const double value) {
    const uint64_t bit_value = to_uint64__(value);
    return (bit_value & dbl_exp_mask) == dbl_exp_mask &&
        (bit_value & dbl_mant_mask) != 0u;
  }

  bool tal_is_inf_f(const float value) {
    const uint32_t bit_value = to_uint32__(value);
    return (bit_value & flt_exp_mask) == flt_exp_mask &&
        (bit_value & flt_mant_mask) == 0u;
  }

  bool tal_is_inf_d(const double value) {
    const uint64_t bit_value = to_uint64__(value);
    return (bit_value & dbl_exp_mask) == dbl_exp_mask &&
        (bit_value & dbl_mant_mask) == 0u;
  }

  bool tal_is_normal_f(const float value) {
    return tal_is_finite_f(value) && !tal_is_denorm_f(value);
  }

  bool tal_is_normal_d(const double value) {
    return tal_is_finite_d(value) && !tal_is_denorm_d(value);
  }

  bool tal_is_denorm_f(const float value) {
    const uint32_t bit_value = to_uint32__(value);
    return (bit_value & flt_exp_mask) == 0u &&
        (bit_value & flt_mant_mask) != 0u;
  }

  bool tal_is_denorm_d(const double value) {
    const uint64_t bit_value = to_uint64__(value);
    return (bit_value & dbl_exp_mask) == 0u &&
        (bit_value & dbl_mant_mask) != 0u;
  }

  bool tal_sign_bit_f(const float value) {
    const uint32_t bit_value = to_uint32__(value);
    return (bit_value & flt_sign_mask) != 0u;
  }

  bool tal_sign_bit_d(const double value) {
    const uint64_t bit_value = to_uint64__(value);
    return (bit_value & dbl_sign_mask) != 0u;
  }

#if defined(__cplusplus)
  } // extern "C"
#endif