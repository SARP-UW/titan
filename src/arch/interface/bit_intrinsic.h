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
 * @file arch/interface/bit_intrinsic.h
 * @authors Aaron McBride
 * @brief Interface for intrinsic bit manipulation/inspection operations.
 */

#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  int32_t arch_clz_u8(uint8_t value);
  int32_t arch_clz_u16(uint16_t value);
  int32_t arch_clz_u32(uint32_t value);
  int32_t arch_clz_u64(uint64_t value);

  int32_t arch_ctz_u8(uint8_t value);
  int32_t arch_ctz_u16(uint16_t value);
  int32_t arch_ctz_u32(uint32_t value);
  int32_t arch_ctz_u64(uint64_t value);

  int32_t arch_popcnt_u8(uint8_t value);
  int32_t arch_popcnt_u16(uint16_t value);
  int32_t arch_popcnt_u32(uint32_t value);
  int32_t arch_popcnt_u64(uint64_t value);

  int32_t arch_bit_rev_u8(uint8_t value);
  int32_t arch_bit_rev_u16(uint16_t value);
  int32_t arch_bit_rev_u32(uint32_t value);
  int32_t arch_bit_rev_u64(uint64_t value);

  uint8_t arch_byte_rev_u16(uint16_t value);
  uint32_t arch_byte_rev_u32(uint32_t value);
  uint64_t arch_byte_rev_u64(uint64_t value);

  uint8_t arch_bit_insert_u8(uint8_t value, uint8_t dst, int32_t pos, int32_t len);
  uint16_t arch_bit_insert_u16(uint16_t value, uint16_t dst, int32_t pos, int32_t len);
  uint32_t arch_bit_insert_u32(uint32_t value, uint32_t dst, int32_t pos, int32_t len);
  uint64_t arch_bit_insert_u64(uint64_t value, uint64_t dst, int32_t pos, int32_t len);

  uint8_t arch_bit_extract_u8(uint8_t value, int32_t pos, int32_t len);
  uint16_t arch_bit_extract_u16(uint16_t value, int32_t pos, int32_t len);
  uint32_t arch_bit_extract_u32(uint32_t value, int32_t pos, int32_t len);
  uint64_t arch_bit_extract_u64(uint64_t value, int32_t pos, int32_t len);
  
#if defined(__cplusplus)
  } // extern "C"
#endif