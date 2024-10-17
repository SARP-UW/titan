/**
 * This file is part of the Titan Flight Computer Project
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
 * @file common/util/bit.h
 * @authors Aaron McBride
 * @brief Bit manipulation utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  #define ti_bit_size(type) (sizeof(type) * CHAR_BIT)

  // impl complete
  // todo -> doc
  uint8_t ti_rbit8(const uint8_t value);
  uint16_t ti_rbit16(const uint16_t value);
  uint32_t ti_rbit32(const uint32_t value);
  uint64_t ti_rbit64(const uint64_t value);

  // impl complete
  // todo -> doc
  uint16_t ti_rbyte16(const uint16_t value);
  uint32_t ti_rbyte32(const uint32_t value);
  uint64_t ti_rbyte64(const uint64_t value);

  // impl complete
  // todo -> doc
  bool ti_single_bit8(const uint8_t value);
  bool ti_single_bit16(const uint16_t value);
  bool ti_single_bit32(const uint32_t value);
  bool ti_single_bit64(const uint64_t value);

  // impl complete
  // todo -> doc
  uint8_t ti_bit_ceil8(const uint8_t value);
  uint16_t ti_bit_ceil16(const uint16_t value);
  uint32_t ti_bit_ceil32(const uint32_t value);
  uint64_t ti_bit_ceil64(const uint64_t value);

  // impl complete
  // todo -> doc
  uint8_t ti_bit_floor8(const uint8_t value);
  uint16_t ti_bit_floor16(const uint16_t value);
  uint32_t ti_bit_floor32(const uint32_t value);
  uint64_t ti_bit_floor64(const uint64_t value);

  // impl complete
  // todo -> doc
  int32_t ti_bit_width8(const uint8_t value);
  int32_t ti_bit_width16(const uint16_t value);
  int32_t ti_bit_width32(const uint32_t value);
  int32_t ti_bit_width64(const uint64_t value);

  // impl complete
  // todo -> doc
  uint8_t ti_rotl8(const uint8_t value, const int32_t shift);
  uint16_t ti_rotl16(const uint16_t value, const int32_t shift);
  uint32_t ti_rotl32(const uint32_t value, const int32_t shift);
  uint64_t ti_rotl64(const uint64_t value, const int32_t shift);

  // impl complete
  // todo -> doc
  uint8_t ti_rotr8(const uint8_t value, const int32_t shift);
  uint16_t ti_rotr16(const uint16_t value, const int32_t shift);
  uint32_t ti_rotr32(const uint32_t value, const int32_t shift);
  uint64_t ti_rotr64(const uint64_t value, const int32_t shift);

  // impl complete
  // todo -> doc
  int32_t ti_clz8(const uint8_t value);
  int32_t ti_clz16(const uint16_t value);
  int32_t ti_clz32(const uint32_t value);
  int32_t ti_clz64(const uint64_t value);

  // impl complete
  // todo -> doc
  int32_t ti_clo8(const uint8_t value);
  int32_t ti_clo16(const uint16_t value);
  int32_t ti_clo32(const uint32_t value);
  int32_t ti_clo64(const uint64_t value);

  // impl complete
  // todo -> doc
  int32_t ti_ctz8(const uint8_t value);
  int32_t ti_ctz16(const uint16_t value);
  int32_t ti_ctz32(const uint32_t value);
  int32_t ti_ctz64(const uint64_t value);

  // impl complete
  // todo -> doc
  int32_t ti_cto8(const uint8_t value);
  int32_t ti_cto16(const uint16_t value);
  int32_t ti_cto32(const uint32_t value);
  int32_t ti_cto64(const uint64_t value);

  // impl complete
  // todo -> doc
  int32_t ti_popcount8(const uint8_t value);
  int32_t ti_popcount16(const uint16_t value);
  int32_t ti_popcount32(const uint32_t value);
  int32_t ti_popcount64(const uint64_t value);

  // impl complete
  // todo -> doc
  uint8_t ti_mask8(const int32_t length, const int32_t pos);
  uint16_t ti_mask16(const int32_t length, const int32_t pos);
  uint32_t ti_mask32(const int32_t length, const int32_t pos);
  uint64_t ti_mask64(const int32_t length, const int32_t pos);

#if defined(__cplusplus)
  }
#endif