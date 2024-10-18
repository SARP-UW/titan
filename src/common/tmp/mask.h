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
 * @file common/util/reg.h 
 * @authors Aaron McBride
 * @brief Register access utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#if defined(__cplusplus)
  extern "C" {
#endif

void ti_write_mask8(uint8_t value, uint8_t *dest, const int32_t pos, const int32_t len);
void ti_write_mask16(uint16_t value, uint16_t *dest, const int32_t pos, const int32_t len);
void ti_write_mask32(uint32_t value, uint32_t *dest, const int32_t pos, const int32_t len);
void ti_write_mask64(uint64_t value, uint64_t *dest, const int32_t pos, const int32_t len);

void ti_write_mask8v(uint8_t value, uint8_t *dest, const int32_t pos, const int32_t len);
void ti_write_mask16v(uint16_t value, uint16_t *dest, const int32_t pos, const int32_t len);
void ti_write_mask32v(uint32_t value, uint32_t *dest, const int32_t pos, const int32_t len);
void ti_write_mask64v(uint64_t value, uint64_t *dest, const int32_t pos, const int32_t len);

uint8_t ti_read_mask8(const uint8_t *src, const int32_t pos, const int32_t len);
uint16_t ti_read_mask16(const uint16_t *src, const int32_t pos, const int32_t len);
uint32_t ti_read_mask32(const uint32_t *src, const int32_t pos, const int32_t len);
uint64_t ti_read_mask64(const uint64_t *src, const int32_t pos, const int32_t len);

uint8_t ti_read_mask8v(const uint8_t *src, const int32_t pos, const int32_t len);
uint16_t ti_read_mask16v(const uint16_t *src, const int32_t pos, const int32_t len);
uint32_t ti_read_mask32v(const uint32_t *src, const int32_t pos, const int32_t len);
uint64_t ti_read_mask64v(const uint64_t *src, const int32_t pos, const int32_t len);

void ti_set_mask8(uint8_t *dest, const int32_t pos, const int32_t len);
void ti_set_mask16(uint16_t *dest, const int32_t pos, const int32_t len);
void ti_set_mask32(uint32_t *dest, const int32_t pos, const int32_t len);
void ti_set_mask64(uint64_t *dest, const int32_t pos, const int32_t len);

void ti_set_mask8v(uint8_t *dest, const int32_t pos, const int32_t len);
void ti_set_mask16v(uint16_t *dest, const int32_t pos, const int32_t len);
void ti_set_mask32v(uint32_t *dest, const int32_t pos, const int32_t len);
void ti_set_mask64v(uint64_t *dest, const int32_t pos, const int32_t len);

void ti_clear_mask8(uint8_t *dest, const int32_t pos, const int32_t len);
void ti_clear_mask16(uint16_t *dest, const int32_t pos, const int32_t len);
void ti_clear_mask32(uint32_t *dest, const int32_t pos, const int32_t len);
void ti_clear_mask64(uint64_t *dest, const int32_t pos, const int32_t len);

void ti_clear_mask8v(uint8_t *dest, const int32_t pos, const int32_t len);
void ti_clear_mask16v(uint16_t *dest, const int32_t pos, const int32_t len);
void ti_clear_mask32v(uint32_t *dest, const int32_t pos, const int32_t len);
void ti_clear_mask64v(uint64_t *dest, const int32_t pos, const int32_t len);

bool ti_is_mask_set8(const uint8_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_set16(const uint16_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_set32(const uint32_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_set64(const uint64_t *src, const int32_t pos, const int32_t len);

bool ti_is_mask_set8v(const uint8_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_set16v(const uint16_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_set32v(const uint32_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_set64v(const uint64_t *src, const int32_t pos, const int32_t len);

bool ti_is_mask_clear8(const uint8_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_clear16(const uint16_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_clear32(const uint32_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_clear64(const uint64_t *src, const int32_t pos, const int32_t len);

bool ti_is_mask_clear8v(const uint8_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_clear16v(const uint16_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_clear32v(const uint32_t *src, const int32_t pos, const int32_t len);
bool ti_is_mask_clear64v(const uint64_t *src, const int32_t pos, const int32_t len);

/**
 * @brief Creates a bit-mask.
 * @param pos A int32_t that denotes the position of the mask.
 * @param length A int32_t that denotes the number of set bits in the mask.
 * @returns A uintptr_t which contains 'length' set bits (consecutive), 'pos' 
 *          bits from the lsb.
 */
uintptr_t ti_mask(const int32_t pos, const int32_t length);

/**
 * @brief Creates a bit-mask.
 * @param pos A int32_t that denotes the position of the mask.
 * @param length A int32_t that denotes the number of set bits in the mask.
 * @returns A uint8_t which contains 'length' set bits (consecutive), 'pos' 
 *          bits from the lsb.
 */
uint8_t ti_mask8(const int32_t pos, const int32_t length);

/**
 * @brief Creates a bit-mask.
 * @param pos A int32_t that denotes the position of the mask.
 * @param length A int32_t that denotes the number of set bits in the mask.
 * @returns A uint16_t which contains 'length' set bits (consecutive), 'pos' 
 *          bits from the lsb.
 */
uint16_t ti_mask16(const int32_t pos, const int32_t length);

/**
 * @brief Creates a bit-mask.
 * @param pos A int32_t that denotes the position of the mask.
 * @param length A int32_t that denotes the number of set bits in the mask.
 * @returns A uint32_t which contains 'length' set bits (consecutive), 'pos' 
 *          bits from the lsb.
 */
uint32_t ti_mask32(const int32_t pos, const int32_t length);

/**
 * @brief Creates a bit-mask.
 * @param pos A int32_t that denotes the position of the mask.
 * @param length A int32_t that denotes the number of set bits in the mask.
 * @returns A uint64_t which contains 'length' set bits (consecutive), 'pos' 
 *          bits from the lsb.
 */
uint64_t ti_mask64(const int32_t pos, const int32_t length);

uintptr_t ti_mask(const int32_t length, const int32_t pos) {
  return (((1u << length) - 1u) << pos);
}

uint8_t ti_mask8(const int32_t length, const int32_t pos) {
  return (((1u << length) - 1u) << pos);
}

uint16_t ti_mask16(const int32_t length, const int32_t pos) {
  return (((1u << length) - 1u) << pos);
}

uint32_t ti_mask32(const int32_t length, const int32_t pos) {
  return (((1u << length) - 1u) << pos);
}

uint64_t ti_mask64(const int32_t length, const int32_t pos) {
  return (((1u << length) - 1u) << pos);
}

#if defined(__cplusplus)
  }
#endif
