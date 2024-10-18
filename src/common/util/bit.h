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

/**
 * @brief Evaluates to the number of bits in @p 'type'.
 * @param type The type to get the bit size of.
 */
#define ti_bit_size(type) (sizeof(type) * CHAR_BIT)

/**
 * @brief Evaluates to true if the system is little endian, 
 *        or false otherwise.
 */
#define ti_little_endian __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__

/**
 * @brief Evaluates to true if the system is big endian, 
 *        or false otherwise.
 */
#define ti_big_endian __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__

/**
 * @brief Reverses the bits of an integer.
 * @param value The uint8_t value to modify.
 * @returns A uint8_t equal to the bit-reversed version of the given value.
 */
uint8_t ti_rbit8(const uint8_t value);

/**
 * @brief Reverses the bits of an integer.
 * @param value The uint16_t value to modify.
 * @returns A uint16_t equal to the bit-reversed version of the given value.
 */
uint16_t ti_rbit16(const uint16_t value);

/**
 * @brief Reverses the bits of an integer.
 * @param value The uint32_t value to modify.
 * @returns A uint32_t equal to the bit-reversed version of the given value.
 */
uint32_t ti_rbit32(const uint32_t value);

/**
 * @brief Reverses the bits of an integer.
 * @param value The uint64_t value to modify.
 * @returns A uint64_t equal to the bit-reversed version of the given value.
 */
uint64_t ti_rbit64(const uint64_t value);

/**
 * @brief Reverses the bytes of an integer.
 * @param value The uint16_t value to modify.
 * @returns A uint16_t equal to the byte-reversed version of the given value.
 * @note - This function does not change the order of the bits within each
 *         byte.
 */
uint16_t ti_rbyte16(const uint16_t value);

/**
 * @brief Reverses the bytes of an integer.
 * @param value The uint32_t value to modify.
 * @returns A uint32_t equal to the byte-reversed version of the given value.
 * @note - This function does not change the order of the bits within each
 *         byte.
 */
uint32_t ti_rbyte32(const uint32_t value);

/**
 * @brief Reverses the bytes of an integer.
 * @param value The uint64_t value to modify.
 * @returns A uint64_t equal to the byte-reversed version of the given value.
 * @note - This function does not change the order of the bits within each
 *         byte.
 */
uint64_t ti_rbyte64(const uint64_t value);

/**
 * @brief Determines if an integer is a power of two.
 * @param value The uint8_t value to query.
 * @returns True if the given value is a power of two, or false otherwise.
 * @note - If an integer is a power of two, it has only one set bit.
 */
bool ti_single_bit8(const uint8_t value);

/**
 * @brief Determines if an integer is a power of two.
 * @param value The uint16_t value to query.
 * @returns True if the given value is a power of two, or false otherwise.
 * @note - If an integer is a power of two, it has only one set bit.
 */
bool ti_single_bit16(const uint16_t value);

/**
 * @brief Determines if an integer is a power of two.
 * @param value The uint32_t value to query.
 * @returns True if the given value is a power of two, or false otherwise.
 * @note - If an integer is a power of two, it has only one set bit.
 */
bool ti_single_bit32(const uint32_t value);

/**
 * @brief Determines if an integer is a power of two.
 * @param value The uint64_t value to query.
 * @returns True if the given value is a power of two, or false otherwise.
 * @note - If an integer is a power of two, it has only one set bit.
 */
bool ti_single_bit64(const uint64_t value);

/**
 * @brief Rounds an integer up to the nearest power of two.
 * @param value The uint8_t value to ceil.
 * @returns A uint8_t which equals the smallest power of two >= 'value'.
 * @note - If an integer is power of two, it has only one set bit.
 */
uint8_t ti_bit_ceil8(const uint8_t value);

/**
 * @brief Rounds an integer up to the nearest power of two.
 * @param value The uint16_t value to ceil.
 * @returns A uint16_t which equals the smallest power of two >= 'value'.
 * @note - If an integer is power of two, it has only one set bit.
 */
uint16_t ti_bit_ceil16(const uint16_t value);

/**
 * @brief Rounds an integer up to the nearest power of two.
 * @param value The uint32_t value to ceil.
 * @returns A uint32_t which equals the smallest power of two >= 'value'.
 * @note - If an integer is power of two, it has only one set bit.
 */
uint32_t ti_bit_ceil32(const uint32_t value);

/**
 * @brief Rounds an integer up to the nearest power of two.
 * @param value The uint64_t value to ceil.
 * @returns A uint64_t which equals the smallest power of two >= 'value'.
 * @note - If an integer is power of two, it has only one set bit.
 */
uint64_t ti_bit_ceil64(const uint64_t value);

/**
 * @brief Rounds an integer down to the nearest power of two.
 * @param value The uint8_t value to floor.
 * @returns A uint8_t which equals the greatest power of two <= 'value'.
 * @note - If an integer is power of two, it has only one set bit.
 */
uint8_t ti_bit_floor8(const uint8_t value);

/**
 * @brief Rounds an integer down to the nearest power of two.
 * @param value The uint16_t value to floor.
 * @returns A uint16_t which equals the greatest power of two <= 'value'.
 * @note - If an integer is power of two, it has only one set bit.
 */
uint16_t ti_bit_floor16(const uint16_t value);

/**
 * @brief Rounds an integer down to the nearest power of two.
 * @param value The uint32_t value to floor.
 * @returns A uint32_t which equals the greatest power of two <= 'value'.
 * @note - If an integer is power of two, it has only one set bit.
 */
uint32_t ti_bit_floor32(const uint32_t value);

/**
 * @brief Rounds an integer down to the nearest power of two.
 * @param value The uint64_t value to floor.
 * @returns A uint64_t which equals the greatest power of two <= 'value'.
 * @note - If an integer is power of two, it has only one set bit.
 */
uint64_t ti_bit_floor64(const uint64_t value);

/**
 * @brief Determines the number of bits needed to represent a value.
 * @param value The uint8_t value to query.
 * @returns A int32_t which equals the minimum number of bits needed to
 *          represent the given value. That is, 1 + log2('value').
 * @note - If the given value is 0, the result is 0.
 */
int32_t ti_bit_width8(const uint8_t value);

/**
 * @brief Determines the number of bits needed to represent a value.
 * @param value The uint16_t value to query.
 * @returns A int32_t which equals the minimum number of bits needed to
 *          represent the given value. That is, 1 + log2(value).
 * @note - If the given value is 0, the result is 0.
 */
int32_t ti_bit_width16(const uint16_t value);

/**
 * @brief Determines the number of bits needed to represent a value.
 * @param value The uint32_t value to query.
 * @returns A int32_t which equals the minimum number of bits needed to
 *          represent the given value. That is, 1 + log2(value).
 * @note - If the given value is 0, the result is 0.
 */
int32_t ti_bit_width32(const uint32_t value);

/**
 * @brief Determines the number of bits needed to represent a value.
 * @param value The uint64_t value to query.
 * @returns A int32_t which equals the minimum number of bits needed to
 *          represent the given value. That is, 1 + log2(value).
 * @note - If the given value is 0, the result is 0.
 */
int32_t ti_bit_width64(const uint64_t value);

/**
 * @brief Performs a circular left shift on an integer value.
 * @param value The uint8_t value to rotate.
 * @param shift A int32_t which denotes the number of bits to rotate by.
 * @returns A uint8_t which equals the result of rotating the given value
 *          to the left by 'shift' bits.
 * @note - This function performs a "circular shift", meaining that bits
 *         shifted beyond the end of the integer's range wrap around to
 *         the beginning.
 */
uint8_t ti_rotl8(const uint8_t value, const int32_t shift);

/**
 * @brief Performs a circular left shift on an integer value.
 * @param value The uint16_t value to rotate.
 * @param shift A int32_t which denotes number of bits to rotate by.
 * @returns A uint16_t which equals the result of rotating the given value
 *          to the left by 'shift' bits.
 * @note - This function performs a "circular shift", meaining that bits
 *         shifted beyond the end of the integer's range wrap around to
 *         the beginning.
 */
uint16_t ti_rotl16(const uint16_t value, const int32_t shift);

/**
 * @brief Performs a circular left shift on an integer value.
 * @param value The uint32_t value to rotate.
 * @param shift A int32_t which denotes number of bits to rotate by.
 * @returns A uint32_t which equals the result of rotating the given value
 *          to the left by 'shift' bits.
 * @note - This function performs a "circular shift", meaining that bits
 *         shifted beyond the end of the integer's range wrap around to
 *         the beginning.
 */
uint32_t ti_rotl32(const uint32_t value, const int32_t shift);

/**
 * @brief Performs a circular left shift on an integer value.
 * @param value The uint64_t value to rotate.
 * @param shift A int32_t which denotes number of bits to rotate by.
 * @returns A uint64_t which equals the result of rotating the given value
 *          to the left by 'shift' bits.
 * @note - This function performs a "circular shift", meaining that bits
 *         shifted beyond the end of the integer's range wrap around to
 *         the beginning.
 */
uint64_t ti_rotl64(const uint64_t value, const int32_t shift);

/**
 * @brief Performs a circular right shift on an integer value.
 * @param value The uint8_t value to rotate.
 * @param shift A int32_t which denotes the number of bits to rotate by.
 * @returns A uint8_t which equals the result of rotating the given value
 *          to the right by 'shift' bits.
 * @note - This function performs a "circular shift", meaining that bits
 *         shifted beyond the end of the integer's range wrap around to
 *         the beginning.
 */
uint8_t ti_rotr8(const uint8_t value, const int32_t shift);

/**
 * @brief Performs a circular right shift on an integer value.
 * @param value The uint16_t value to rotate.
 * @param shift A int32_t which denotes the number of bits to rotate by.
 * @returns A uint16_t which equals the result of rotating the given value
 *          to the right by 'shift' bits.
 * @note - This function performs a "circular shift", meaining that bits
 *         shifted beyond the end of the integer's range wrap around to
 *         the beginning.
 */
uint16_t ti_rotr16(const uint16_t value, const int32_t shift);

/**
 * @brief Performs a circular right shift on an integer value.
 * @param value The uint32_t value to rotate.
 * @param shift A int32_t which denotes the number of bits to rotate by.
 * @returns A uint32_t which equals the result of rotating the given value
 *          to the right by 'shift' bits.
 * @note - This function performs a "circular shift", meaining that bits
 *         shifted beyond the end of the integer's range wrap around to
 *         the beginning.
 */
uint32_t ti_rotr32(const uint32_t value, const int32_t shift);

/**
 * @brief Performs a circular right shift on an integer value.
 * @param value The uint64_t value to rotate.
 * @param shift A int32_t which denotes the number of bits to rotate by.
 * @returns A uint64_t which equals the result of rotating the given value
 *          to the right by 'shift' bits.
 * @note - This function performs a "circular shift", meaining that bits
 *         shifted beyond the end of the integer's range wrap around to
 *         the beginning.
 */
uint64_t ti_rotr64(const uint64_t value, const int32_t shift);

/**
 * @brief Counts the number of leading zero bits in an integer.
 * @param value The uint8_t value to query.
 * @returns A int32_t which denotes the number of leading zero bits in 
 *          the given value (leading = most significant).
 */
int32_t ti_clz8(const uint8_t value);

/**
 * @brief Counts the number of leading zero bits in an integer.
 * @param value The uint16_t value to query.
 * @returns A int32_t which denotes the number of leading zero bits in 
 *          the given value (leading = most significant).
 */
int32_t ti_clz16(const uint16_t value);

/**
 * @brief Counts the number of leading zero bits in an integer.
 * @param value The uint32_t value to query.
 * @returns A int32_t which denotes the number of leading zero bits in 
 *          the given value (leading = most significant).
 */
int32_t ti_clz32(const uint32_t value);

/**
 * @brief Counts the number of leading zero bits in an integer.
 * @param value The uint64_t value to query.
 * @returns A int32_t which denotes the number of leading zero bits in 
 *          the given value (leading = most significant).
 */
int32_t ti_clz64(const uint64_t value);

/**
 * @brief Counts the number of leading one bits in an integer.
 * @param value The uint8_t value to query.
 * @returns A int32_t which denotes the number of leading one bits in 
 *          the given value (leading = most significant).
 */
int32_t ti_clo8(const uint8_t value);

/**
 * @brief Counts the number of leading one bits in an integer.
 * @param value The uint16_t value to query.
 * @returns A int32_t which denotes the number of leading one bits in 
 *          the given value (leading = most significant).
 */
int32_t ti_clo16(const uint16_t value);

/**
 * @brief Counts the number of leading one bits in an integer.
 * @param value The uint32_t value to query.
 * @returns A int32_t which denotes the number of leading one bits in 
 *          the given value (leading = most significant).
 */
int32_t ti_clo32(const uint32_t value);

/**
 * @brief Counts the number of leading one bits in an integer.
 * @param value The uint64_t value to query.
 * @returns A int32_t which denotes the number of leading one bits in 
 *          the given value (leading = most significant).
 */
int32_t ti_clo64(const uint64_t value);

/**
 * @brief Counts the number of trailing zero bits in an integer.
 * @param value The uint8_t value to query.
 * @returns A int32_t which denotes the number of trailing zero bits in 
 *          the given value (trailing = least significant).
 */
int32_t ti_ctz8(const uint8_t value);

/**
 * @brief Counts the number of trailing zero bits in an integer.
 * @param value The uint16_t value to query.
 * @returns A int32_t which denotes the number of trailing zero bits in 
 *          the given value (trailing = least significant).
 */
int32_t ti_ctz16(const uint16_t value);

/**
 * @brief Counts the number of trailing zero bits in an integer.
 * @param value The uint32_t value to query.
 * @returns A int32_t which denotes the number of trailing zero bits in 
 *          the given value (trailing = least significant).
 */
int32_t ti_ctz32(const uint32_t value);

/**
 * @brief Counts the number of trailing zero bits in an integer.
 * @param value The uint64_t value to query.
 * @returns A int32_t which denotes the number of trailing zero bits in 
 *          the given value (trailing = least significant).
 */
int32_t ti_ctz64(const uint64_t value);

/**
 * @brief Counts the number of trailing one bits in an integer.
 * @param value The uint8_t value to query.
 * @returns A int32_t which denotes the number of trailing one bits in 
 *          the given value (trailing = least significant).
 */
int32_t ti_cto8(const uint8_t value);

/**
 * @brief Counts the number of trailing one bits in an integer.
 * @param value The uint16_t value to query.
 * @returns A int32_t which denotes the number of trailing one bits in 
 *          the given value (trailing = least significant).
 */
int32_t ti_cto16(const uint16_t value);

/**
 * @brief Counts the number of trailing one bits in an integer.
 * @param value The uint32_t value to query.
 * @returns A int32_t which denotes the number of trailing one bits in 
 *          the given value (trailing = least significant).
 */
int32_t ti_cto32(const uint32_t value);

/**
 * @brief Counts the number of trailing one bits in an integer.
 * @param value The uint64_t value to query.
 * @returns A int32_t which denotes the number of trailing one bits in 
 *          the given value (trailing = least significant).
 */
int32_t ti_cto64(const uint64_t value);

/**
 * @brief Counts the number of set bits in an integer.
 * @param value The uint8_t value to query.
 * @returns A int32_t which denotes the number of set bits in the given value.
 */
int32_t ti_popcount8(const uint8_t value);

/**
 * @brief Counts the number of set bits in an integer.
 * @param value The uint16_t value to query.
 * @returns A int32_t which denotes the number of set bits in the given value.
 */
int32_t ti_popcount16(const uint16_t value);

/**
 * @brief Counts the number of set bits in an integer.
 * @param value The uint32_t value to query.
 * @returns A int32_t which denotes the number of set bits in the given value.
 */
int32_t ti_popcount32(const uint32_t value);

/**
 * @brief Counts the number of set bits in an integer.
 * @param value The uint64_t value to query.
 * @returns A int32_t which denotes the number of set bits in the given value.
 */
int32_t ti_popcount64(const uint64_t value);

#if defined(__cplusplus)
  }
#endif