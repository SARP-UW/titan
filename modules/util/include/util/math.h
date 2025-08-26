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

int8_t ti_max_i8(int8_t value_1, int8_t value_2);
int16_t ti_max_i16(int16_t value_1, int16_t value_2);
int32_t ti_max_i32(int32_t value_1, int32_t value_2);
int64_t ti_max_i64(int64_t value_1, int64_t value_2);
uint8_t ti_max_u8(uint8_t value_1, uint8_t value_2);
uint16_t ti_max_u16(uint16_t value_1, uint16_t value_2);
uint32_t ti_max_u32(uint32_t value_1, uint32_t value_2);
uint64_t ti_max_u64(uint64_t value_1, uint64_t value_2);

int8_t ti_min_i8(int8_t value_1, int8_t value_2);
int16_t ti_min_i16(int16_t value_1, int16_t value_2);
int32_t ti_min_i32(int32_t value_1, int32_t value_2);
int64_t ti_min_i64(int64_t value_1, int64_t value_2);
uint8_t ti_min_u8(uint8_t value_1, uint8_t value_2);
uint16_t ti_min_u16(uint16_t value_1, uint16_t value_2);
uint32_t ti_min_u32(uint32_t value_1, uint32_t value_2);
uint64_t ti_min_u64(uint64_t value_1, uint64_t value_2);

int8_t ti_clamp_i8(int8_t value, int8_t min, int8_t max);
int16_t ti_clamp_i16(int16_t value, int16_t min, int16_t max);
int32_t ti_clamp_i32(int32_t value, int32_t min, int32_t max);
int64_t ti_clamp_i64(int64_t value, int64_t min, int64_t max);
uint8_t ti_clamp_u8(uint8_t value, uint8_t min, uint8_t max);
uint16_t ti_clamp_u16(uint16_t value, uint16_t min, uint16_t max);
uint32_t ti_clamp_u32(uint32_t value, uint32_t min, uint32_t max);
uint64_t ti_clamp_u64(uint64_t value, uint64_t min, uint64_t max);

int8_t ti_floor_i8(int8_t value, int8_t align);
int16_t ti_floor_i16(int16_t value, int16_t align);
int32_t ti_floor_i32(int32_t value, int32_t align);
int64_t ti_floor_i64(int64_t value, int64_t align);
uint8_t ti_floor_u8(uint8_t value, uint8_t align);
uint16_t ti_floor_u16(uint16_t value, uint16_t align);
uint32_t ti_floor_u32(uint32_t value, uint32_t align);
uint64_t ti_floor_u64(uint64_t value, uint64_t align);

int8_t ti_ceil_i8(int8_t value, int8_t align);
int16_t ti_ceil_i16(int16_t value, int16_t align);
int32_t ti_ceil_i32(int32_t value, int32_t align);
int64_t ti_ceil_i64(int64_t value, int64_t align);
uint8_t ti_ceil_u8(uint8_t value, uint8_t align);
uint16_t ti_ceil_u16(uint16_t value, uint16_t align);
uint32_t ti_ceil_u32(uint32_t value, uint32_t align);
uint64_t ti_ceil_u64(uint64_t value, uint64_t align);

int8_t ti_round_i8(int8_t value, int8_t align);
int16_t ti_round_i16(int16_t value, int16_t align);
int32_t ti_round_i32(int32_t value, int32_t align);
int64_t ti_round_i64(int64_t value, int64_t align);
uint8_t ti_round_u8(uint8_t value, uint8_t align);
uint16_t ti_round_u16(uint16_t value, uint16_t align);
uint32_t ti_round_u32(uint32_t value, uint32_t align);
uint64_t ti_round_u64(uint64_t value, uint64_t align);
