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
 * @file src/lib/float/fp_impl.h
 * @authors Aaron McBride
 * @brief Implementation resources for floating point utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <float.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  // Length of mantissa field
  static const int32_t flt_mant_len = (FLT_MANT_DIG - 1);
  static const int32_t dbl_mant_len = (DBL_MANT_DIG - 1);

  // Mask for mantissa field
  static const uint32_t flt_mant_mask = (UINT32_C(1) << flt_mant_len) - 1u;
  static const uint64_t dbl_mant_mask = (UINT64_C(1) << dbl_mant_len) - 1u;
  
  // Length of exponent field
  static const int32_t flt_exp_len = 8;
  static const int32_t dbl_exp_len = 11;

  // Mask for exponent field
  static const uint32_t flt_exp_mask = 
      ((UINT32_C(1) << flt_exp_len) - 1u) << flt_mant_len;
  static const uint64_t dbl_exp_mask = 
      ((UINT64_C(1) << dbl_exp_len) - 1u) << dbl_mant_len;

  // Mask for sign bit
  static const uint32_t flt_sign_mask = 
      UINT32_C(1) << ((sizeof(float) * CHAR_BIT) - 1u);
  static const uint64_t dbl_sign_mask = 
      UINT64_C(1) << ((sizeof(double) * CHAR_BIT) - 1u);

  // Bias (offset) of exponent
  static const int32_t flt_exp_bias = FLT_MAX_EXP - 1;
  static const int32_t dbl_exp_bias = DBL_MAX_EXP - 1;

  // Bitwise conversion of given value (uint32) to flt type
  static float to_flt__(const uint32_t value) {
    union { uint32_t uint32_t; float f; } uni = {.uint32_t = value};
    return uni.f;
  }

  // Bitwise conversion of given value (uint64) to dbl type
  static double to_dbl__(const uint64_t value) {
    union { uint64_t uint64_t; double d; } uni = {.uint64_t = value};
    return uni.d;
  }

  // Bitwise conversion of given value (flt) to uint32 type
  static uint32_t to_uint32__(const float value) {
    union { float f; uint32_t uint32_t; } uni = {.f = value};
    return uni.uint32_t;
  }

  // Bitwise conversion of given value (dbl) to uint64 type.
  static uint64_t to_uint64__(const double value) {
    union { double d; uint64_t uint64_t; } uni = {.d = value};
    return uni.uint64_t;
  }

#if defined(__cplusplus)
  } // extern "C"
#endif