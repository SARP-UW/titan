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
 * @file src/lib/float/fp_inspect.c
 * @authors Aaron McBride
 * @brief Implementation of fp value inspection utilities.
 */

#include "src/lib/float/fp_impl.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  int32_t tal_fexp_f(bool* const err, const float value) {
    if (!tal_is_finite_f(value)) {
      *err = true;
      return 0;
    }
    const uint32_t bit_value = to_uint32__(value);
    const uint32_t exp_value = (bit_value & flt_exp_mask) >> flt_mant_len;
    return (int32_t)exp_value - flt_exp_bias;
  }

  int32_t tal_fexp_d(bool* const err, const double value) {
    if (!tal_is_finite_f(value)) {
      *err = true;
      return 0;
    }
    const uint64_t bit_value = to_uint64__(value);
    const uint64_t exp_value = (bit_value & dbl_exp_mask) >> dbl_mant_len;
    return (int32_t)exp_value - dbl_exp_bias;
  }

  float tal_mant_f(bool* const err, const float value) {
    if (!tal_is_finite_f(value)) {
      *err = true;
      return tal_nan_f();
    }
    uint32_t bit_value = to_uint32__(value);
    bit_value &= flt_mant_mask;
    bit_value |= (uint32_t)flt_exp_bias << flt_mant_len;
    return to_flt__(bit_value);
  }

  double tal_mant_d(bool* const err, const double value) {
    if (!tal_is_finite_d(value)) {
      *err = true;
      return tal_nan_d();
    }
    uint64_t bit_value = to_uint64__(value);
    bit_value &= dbl_mant_mask;
    bit_value |= (uint64_t)dbl_exp_bias << dbl_mant_len;
    return to_dbl__(bit_value);
  }

  float tal_max_ulp_f(bool* const err, const float value) {
    if (tal_is_nan_f(value)) {
      *err = true;
      return tal_nan_f();
    }
    if (tal_is_inf_f(value)) {
      return tal_inf_f();
    }
    uint32_t bit_value = to_uint32__(value);
    if (tal_sign_bit_f(value)) {
      ++bit_value;
      return value - to_flt__(bit_value);
    } else {
      ++bit_value;
      return to_flt__(bit_value) - value;
    }
  }

  double tal_max_ulp_d(bool* const err, const double value) {
    if (tal_is_nan_d(value)) {
      *err = true;
      return tal_nan_d();
    }
    if (tal_is_inf_d(value)) {
      return tal_inf_d();
    }
    uint64_t bit_value = to_uint64__(value);
    if (tal_sign_bit_d(value)) {
      ++bit_value;
      return value - to_dbl__(bit_value);
    } else {
      ++bit_value;
      return to_dbl__(bit_value) - value;
    }
  }

  float tal_min_ulp_f(bool* const err, const float value) {
    if (tal_is_nan_f(value)) {
      *err = true;
      return tal_nan_f();
    }
    if (tal_is_inf_f(value)) {
      return tal_inf_f();
    }
    uint32_t bit_value = to_uint32__(value);
    if (tal_sign_bit_f(value)) {
      --bit_value;
      return to_flt__(bit_value) - value;
    } else {
      --bit_value;
      return value - to_flt__(bit_value);
    }
  }

  double tal_min_ulp_d(bool* const err, const double value) {
    if (tal_is_nan_d(value)) {
      *err = true;
      return tal_nan_d();
    }
    if (tal_is_inf_d(value)) {
      return tal_inf_d();
    }
    uint64_t bit_value = to_uint64__(value);
    if (tal_sign_bit_d(value)) {
      --bit_value;
      return to_dbl__(bit_value) - value;
    } else {
      --bit_value;
      return value - to_dbl__(bit_value);
    }
  }

  int32_t tal_to_ulp_f(bool* const err, const float value) {
    if (!tal_is_finite_f(value)) {
      *err = true;
      return 0;
    }
    const uint32_t bit_value = to_uint32__(value);
    return (int32_t)(bit_value & ~flt_sign_mask);
  }

  int64_t tal_to_ulp_d(bool* const err, const double value) {
    if (!tal_is_finite_d(value)) {
      *err = true;
      return 0;
    }
    const uint64_t bit_value = to_uint64__(value);
    return (int64_t)(bit_value & ~dbl_sign_mask);
  }

#if defined(__cplusplus)
  } // extern "C"
#endif