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
 * @file modules/util/include/util/math.h
 * @authors Aaron McBride
 * @brief Math utilities.
 */

#pragma once
#include <stdint.h>
#include "util/errc.h"

/**
 * @brief Determines if two integral values can be added without causing an overflow.
 * @param lhs (integral value) The left-hand side operand.
 * @param rhs (integral value) The right-hand side operand.
 * @returns (boolean) True if the addition of @p [lhs] and @p [rhs] will not cause an overflow, or false otherwise.
 * @note - @p [lhs] and @p [rhs] are only expanded once.
 */
#define TI_CAN_ADD(lhs, rhs) ({ \
  __builtin_add_overflow_p((lhs), (rhs), (typeof((lhs) + (rhs)))0); \
})

/**
 * @brief Determines if two integral values can be subtracted without causing an overflow.
 * @param lhs (integral value) The left-hand side operand.
 * @param rhs (integral value) The right-hand side operand.
 * @returns (boolean) True if the subtraction of @p [lhs] and @p [rhs] will not cause an overflow, or false otherwise.
 * @note - @p [lhs] and @p [rhs] are only expanded once.
 */
#define TI_CAN_SUB(lhs, rhs) ({ \
  __builtin_sub_overflow_p((lhs), (rhs), (typeof((lhs) - (rhs)))0); \
})

/**
 * @brief Determines if two integral values can be multiplied without causing an overflow.
 * @param lhs (integral value) The left-hand side operand.
 * @param rhs (integral value) The right-hand side operand.
 * @returns (boolean) True if the multiplication of @p [lhs] and @p [rhs] will not cause an overflow, or false otherwise.
 * @note - @p [lhs] and @p [rhs] are only expanded once.
 */
#define TI_CAN_MUL(lhs, rhs) ({ \
  __builtin_mul_overflow_p((lhs), (rhs), (typeof((lhs) * (rhs)))0); \
})

/**
 * @brief Determines if a integral value can be cast to a different integral type without causing an overflow.
 * @param value (integral value) The value to be cast.
 * @param type (integral type) The target type for the cast.
 * @returns (boolean) True if the cast does not result in an overflow, or false otherwise.
 * @note - @p [value] is only expanded once.
 */
#define TI_CAN_NCAST(value, type) ({ \
  __builtin_add_overflow_p((value), (typeof(value))0, (type)0); \
})

/**
 * @brief Adds two integral values, and checks for an overflow.
 * @param lhs (integral value) The left-hand side operand.
 * @param rhs (integral value) The right-hand side operand.
 * @param ovf (boolean pointer) Overflow flag out argument.
 * @returns (integral value) The result of adding @p [lhs] to @p [rhs].
 * @note - If the operation causes an overflow @p [ovf] will be set to true.
 * @note - If the operation does not cause an overflow, @p [ovf] will not be modified.
 * @note - @p [lhs], @p [rhs], and @p [ovf] are only expanded once.
 */
#define TI_ADD(lhs, rhs, ovf) ({ \
  __auto_type _lhs = (lhs); \
  __auto_type _rhs = (rhs); \
  __auto_type _ovf = (ovf); \
  if (!TI_CAN_ADD(_lhs, _rhs)) { \
    *_ovf = true; \
  } \
  _lhs + _rhs; \
})

/**
 * @brief Subtracts two integral values, and checks for an overflow.
 * @param lhs (integral value) The left-hand side operand.
 * @param rhs (integral value) The right-hand side operand.
 * @param ovf (boolean pointer) Overflow flag out argument.
 * @returns (integral value) The result of subtracting @p [rhs] from @p [lhs].
 * @note - If the operation causes an overflow @p [ovf] will be set to true.
 * @note - If the operation does not cause an overflow, @p [ovf] will not be modified.
 * @note - @p [lhs], @p [rhs], and @p [ovf] are only expanded once.
 */
#define TI_SUB(lhs, rhs, ovf) ({ \
  __auto_type _lhs = (lhs); \
  __auto_type _rhs = (rhs); \
  __auto_type _ovf = (ovf); \
  if (!TI_CAN_SUB(_lhs, _rhs)) { \
    *_ovf = true; \
  } \
  _lhs - _rhs; \
})

/**
 * @brief Multiplies two integral values, and checks for an overflow.
 * @param lhs (integral value) The left-hand side operand.
 * @param rhs (integral value) The right-hand side operand.
 * @param ovf (boolean pointer) Overflow flag out argument.
 * @returns (integral value) The result of multiplying @p [lhs] and @p [rhs].
 * @note - If the operation causes an overflow @p [ovf] will be set to true.
 * @note - If the operation does not cause an overflow, @p [ovf] will not be modified.
 * @note - @p [lhs], @p [rhs], and @p [ovf] are only expanded once.
 */
#define TI_MUL(lhs, rhs, ovf) ({ \
  __auto_type _lhs = (lhs); \
  __auto_type _rhs = (rhs); \
  __auto_type _ovf = (ovf); \
  if (!TI_CAN_MUL(_lhs, _rhs)) { \
    *_ovf = true; \
  } \
  _lhs * _rhs; \
})

/**
 * @brief Casts an integral value to a different integral type, and checks for an overflow.
 * @param value (integral value) The value to be cast.
 * @param type (integral type) The target type for the cast.
 * @param ovf (boolean pointer) Overflow flag out argument.
 * @returns (integral value) The result of the cast.
 * @note - If the operation causes an overflow @p [ovf] will be set to true.
 * @note - If the operation does not cause an overflow, @p [ovf] will not be modified.
 * @note - @p [value], @p [type], and @p [ovf] are only expanded once.
 */
#define TI_NCAST(value, type, ovf) ({ \
  __auto_type _value = (value); \
  __auto_type _ovf = (ovf); \
  if (!TI_CAN_NCAST(_value, type)) { \
    *_ovf = true; \
  } \
  (type)_value; \
})

/**
 * @{
 * @brief Gets the maximum of two integers.
 * @param value_1 (integer type denoted by suffix) The first value.
 * @param value_2 (integer type denoted by suffix) The second value.
 * @returns (integer type denoted by suffix) The maximum of @p [value_1] and @p [value_2].
 */
int8_t ti_max_i8(int8_t value_1, int8_t value_2);
int16_t ti_max_i16(int16_t value_1, int16_t value_2);
int32_t ti_max_i32(int32_t value_1, int32_t value_2);
int64_t ti_max_i64(int64_t value_1, int64_t value_2);
uint8_t ti_max_u8(uint8_t value_1, uint8_t value_2);
uint16_t ti_max_u16(uint16_t value_1, uint16_t value_2);
uint32_t ti_max_u32(uint32_t value_1, uint32_t value_2);
uint64_t ti_max_u64(uint64_t value_1, uint64_t value_2);
/** @} */

/**
 * @{
 * @brief Gets the minimum of two integers.
 * @param value_1 (integer type denoted by suffix) The first value.
 * @param value_2 (integer type denoted by suffix) The second value.
 * @returns (integer type denoted by suffix) The minimum of @p [value_1] and @p [value_2].
 */
int8_t ti_min_i8(int8_t value_1, int8_t value_2);
int16_t ti_min_i16(int16_t value_1, int16_t value_2);
int32_t ti_min_i32(int32_t value_1, int32_t value_2);
int64_t ti_min_i64(int64_t value_1, int64_t value_2);
uint8_t ti_min_u8(uint8_t value_1, uint8_t value_2);
uint16_t ti_min_u16(uint16_t value_1, uint16_t value_2);
uint32_t ti_min_u32(uint32_t value_1, uint32_t value_2);
uint64_t ti_min_u64(uint64_t value_1, uint64_t value_2);
/** @} */

/**
 * @{
 * @brief Clamps an integer value between a minimum and maximum.
 * @param value (integer type denoted by suffix) The value to clamp.
 * @param min (integer type denoted by suffix) The minimum value.
 * @param max (integer type denoted by suffix) The maximum value.
 * @return (integer type denoted by suffix) @p [min] if @p [value] < @p [min], @p [max] if @p [value] > @p [max], or @p [value] otherwise.
 */
int8_t ti_clamp_i8(int8_t value, int8_t min, int8_t max);
int16_t ti_clamp_i16(int16_t value, int16_t min, int16_t max);
int32_t ti_clamp_i32(int32_t value, int32_t min, int32_t max);
int64_t ti_clamp_i64(int64_t value, int64_t min, int64_t max);
uint8_t ti_clamp_u8(uint8_t value, uint8_t min, uint8_t max);
uint16_t ti_clamp_u16(uint16_t value, uint16_t min, uint16_t max);
uint32_t ti_clamp_u32(uint32_t value, uint32_t min, uint32_t max);
uint64_t ti_clamp_u64(uint64_t value, uint64_t min, uint64_t max);
/** @} */

/**
 * @{
 * @brief Rounds an integer value down to the nearest multiple of a given alignment.
 * @param value (integer type denoted by suffix) The value to floor.
 * @param align (integer type denoted by suffix) The alignment to floor to.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @return (integer type denoted by suffix) The nearest multiple of @p [alignment] less than or equal to @p [value].
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [alignment] is less than or equal to zero.
 * @warning - TI_ERRC_OVERFLOW is raised if the operation results in an overflow.
 */
int8_t ti_floor_i8(int8_t value, int8_t align, enum ti_errc_t* errc_out);
int16_t ti_floor_i16(int16_t value, int16_t align, enum ti_errc_t* errc_out);
int32_t ti_floor_i32(int32_t value, int32_t align, enum ti_errc_t* errc_out);
int64_t ti_floor_i64(int64_t value, int64_t align, enum ti_errc_t* errc_out);
uint8_t ti_floor_u8(uint8_t value, uint8_t align, enum ti_errc_t* errc_out);
uint16_t ti_floor_u16(uint16_t value, uint16_t align, enum ti_errc_t* errc_out);
uint32_t ti_floor_u32(uint32_t value, uint32_t align, enum ti_errc_t* errc_out);
uint64_t ti_floor_u64(uint64_t value, uint64_t align, enum ti_errc_t* errc_out);
/** @} */

/**
 * @{
 * @brief Rounds an integer value up to the nearest multiple of a given alignment.
 * @param value (integer type denoted by suffix) The value to ceil.
 * @param align (integer type denoted by suffix) The alignment to ceil to.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @return (integer type denoted by suffix) The nearest multiple of @p [alignment] greater than or equal to @p [value].
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [alignment] is less than or equal to zero.
 * @warning - TI_ERRC_OVERFLOW is raised if the operation results in an overflow.
 */
int8_t ti_ceil_i8(int8_t value, int8_t align, enum ti_errc_t* errc_out);
int16_t ti_ceil_i16(int16_t value, int16_t align, enum ti_errc_t* errc_out);
int32_t ti_ceil_i32(int32_t value, int32_t align, enum ti_errc_t* errc_out);
int64_t ti_ceil_i64(int64_t value, int64_t align, enum ti_errc_t* errc_out);
uint8_t ti_ceil_u8(uint8_t value, uint8_t align, enum ti_errc_t* errc_out);
uint16_t ti_ceil_u16(uint16_t value, uint16_t align, enum ti_errc_t* errc_out);
uint32_t ti_ceil_u32(uint32_t value, uint32_t align, enum ti_errc_t* errc_out);
uint64_t ti_ceil_u64(uint64_t value, uint64_t align, enum ti_errc_t* errc_out);
/** @} */

/**
 * @{
 * @brief Rounds an integer value up to the nearest multiple of a given alignment.
 * @param value (integer type denoted by suffix) The value to round.
 * @param align (integer type denoted by suffix) The alignment to round to.
 * @param errc_out (enum ti_errc_t*) Out argument for error code.
 * @return (integer type denoted by suffix) The nearest multiple of @p [alignment] greater than or equal to @p [value].
 * @warning - TI_ERRC_INVALID_ARG is raised if @p [alignment] is less than or equal to zero.
 * @warning - TI_ERRC_OVERFLOW is raised if the operation results in an overflow.
 */
int8_t ti_round_i8(int8_t value, int8_t align, enum ti_errc_t* errc_out);
int16_t ti_round_i16(int16_t value, int16_t align, enum ti_errc_t* errc_out);
int32_t ti_round_i32(int32_t value, int32_t align, enum ti_errc_t* errc_out);
int64_t ti_round_i64(int64_t value, int64_t align, enum ti_errc_t* errc_out);
uint8_t ti_round_u8(uint8_t value, uint8_t align, enum ti_errc_t* errc_out);
uint16_t ti_round_u16(uint16_t value, uint16_t align, enum ti_errc_t* errc_out);
uint32_t ti_round_u32(uint32_t value, uint32_t align, enum ti_errc_t* errc_out);
uint64_t ti_round_u64(uint64_t value, uint64_t align, enum ti_errc_t* errc_out);
/** @} */