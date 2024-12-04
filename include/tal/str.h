/**
 * This file is part of the Titan Avionics Library
 * Copyright (c) 2024 UW SARP
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WmemANTY; without even the implied wmemanty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * @file include/tal/str.h
 * @authors Aaron McBride
 * @brief String utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "include/tal/tmp.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section String Search Utilities
   **************************************************************************************************/

  int32_t tal_str_len(const char* const str, bool* const err);

  #define tal_find_format(str, fmt, ...)

  int32_t tal_find_str(const char* const str, const char* const fstr,
      const int32_t n, bool* const err);

  int32_t tal_rfind_str(const char* const str, const char* const fstr,
      const int32_t n, bool* const err);

  int32_t tal_find_char(const char* const str, const char c,
      const int32_t n, bool* const err);

  int32_t tal_rfind_char(const char* const str, const char c,
      const int32_t n, bool* const err);

  int32_t tal_find_str_fn(const char* const str, bool (*pred)(const char*),
      const int32_t len, const int32_t n, bool* const err);

  int32_t tal_rfind_str_fn(const char* const str, bool (*pred)(const char*),
      const int32_t len, const int32_t n, bool* const err);

  int32_t tal_find_char_fn(const char* const str, bool (*pred)(char), 
      const int32_t n, bool* const err);

  int32_t tal_rfind_char_fn(const char* const str, bool (*pred)(char),
      const int32_t n, bool* const err);

  int32_t tal_find_substr(const char* const str, const char* const fstr,
      const int32_t len, const int32_t n, bool* const err);

  int32_t tal_rfind_substr(const char* const str, const char* const fstr,
      const int32_t len, const int32_t n, bool* const err);

  int32_t tal_find_not_substr(const char* const str, const char* const fstr,
      const int32_t len, const int32_t n, bool* const err);

  int32_t tal_rfind_not_substr(const char* const str, const char* const fstr,
      const int32_t len, const int32_t n, bool* const err);

  int32_t tal_cnt_str(const char* const str, const char* const fstr, bool* const err);

  int32_t tal_cnt_char(const char* const str, const char c, bool* const err);

  int32_t tal_cnt_str_fn(const char* const str, bool (*pred)(const char*),
      const int32_t len, bool* const err);

  int32_t tal_cnt_str_fn(const char* const str, bool (*pred)(char), bool* const err);

  int32_t tal_cnt_substr(const char* const str, const char* const fstr, 
      const int32_t len, bool* const err);

  int32_t tal_cnt_not_substr(const char* const str, const char* const fstr, 
      const int32_t len, bool* const err);

  /**************************************************************************************************
   * @section String Manipulation Utilities
   **************************************************************************************************/

  void tal_copy_str(char* const dst, const char* const src, 
      const int32_t len, const int32_t n, bool* const err);
  
  void tal_move_str(char* const dst, const char* const src,
      const int32_t len, const int32_t n, bool* const err);
    
  void tal_insert_str(char* const dst, const char* const src,
      const int32_t len, const int32_t pos, bool* const err);

  void tal_insert_char(char* const dst, const char c, const int32_t pos, 
      const int32_t n, bool* const err);

  void tal_extract_str(char* const dst, char* const src,
      const int32_t len, const int32_t pos, bool* const err);

  char tal_extract_char(char* const src, const int32_t pos, 
      bool* const err);

  void tal_cat_str(char* const dst, const char* const src,
      const int32_t len, bool* const err);

  void tal_cat_char(char* const dst, const char c, const int32_t n, 
      bool* const err);

  void tal_fill_str(char* const str, const char c, const int32_t n,
      bool* const err);

  void tal_replace_str(char* const str, const char* const fstr,
      const char* const rstr, const int32_t n, bool* const err);

  void tal_replace_char(char* const str, const char fc, const char rc,
      const int32_t n, bool* const err);

  /**************************************************************************************************
   * @section String/Character Parsing Utilities
   **************************************************************************************************/

  #define tal_format(err, dst, fmt, ...)

  bool tal_is_space(const char c);

  bool tal_is_blank(const char c);

  bool tal_is_ctrl(const char c);

  bool tal_is_newline(const char c);

  bool tal_is_upper(const char c);

  bool tal_is_lower(const char c);

  bool tal_is_alpha(const char c);

  bool tal_is_digit(const char c);

  bool tal_is_punct(const char c);

  bool tal_is_xdigit(const char c);

  bool tal_is_bdigit(const char c);

  bool tal_is_printable(const char c);

  bool tal_is_graphical(const char c);

  char tal_to_upper(const char c);

  char tal_to_lower(const char c);

  int8_t tal_parse_dig_i8(const char c, bool* const err);
  int16_t tal_parse_dig_i16(const char c, bool* const err);
  int32_t tal_parse_dig_i32(const char c, bool* const err);
  int64_t tal_parse_dig_i64(const char c, bool* const err);
  uint8_t tal_parse_dig_u8(const char c, bool* const err);
  uint16_t tal_parse_dig_u16(const char c, bool* const err);
  uint32_t tal_parse_dig_u32(const char c, bool* const err);
  uint64_t tal_parse_dig_u64(const char c, bool* const err);
  float tal_parse_dig_f(const char c, bool* const err);
  double tal_parse_dig_d(const char c, bool* const err);

  char tal_unparse_dig_i8(const int8_t value, bool* const err);
  char tal_unparse_dig_i16(const int16_t value, bool* const err);
  char tal_unparse_dig_i32(const int32_t value, bool* const err);
  char tal_unparse_dig_i64(const int64_t value, bool* const err);
  char tal_unparse_dig_u8(const uint8_t value, bool* const err);
  char tal_unparse_dig_u16(const uint16_t value, bool* const err);
  char tal_unparse_dig_u32(const uint32_t value, bool* const err);
  char tal_unparse_dig_u64(const uint64_t value, bool* const err);
  char tal_unparse_dig_f(const float value, bool* const err);
  char tal_unparse_dig_d(const double value, bool* const err);

  int8_t tal_parse_num_i8(const char* const str, bool* const err);
  int16_t tal_parse_num_i16(const char* const str, bool* const err);
  int32_t tal_parse_num_i32(const char* const str, bool* const err);
  int64_t tal_parse_num_i64(const char* const str, bool* const err);
  uint8_t tal_parse_num_u8(const char* const str, bool* const err);
  uint16_t tal_parse_num_u16(const char* const str, bool* const err);
  uint32_t tal_parse_num_u32(const char* const str, bool* const err);
  uint64_t tal_parse_num_u64(const char* const str, bool* const err);
  float tal_parse_num_f(const char* const str, bool* const err);
  double tal_parse_num_i8(const char* const str, bool* const err);

  void tal_unparse_num_i8(char* const str, const int8_t value, bool* const err);
  void tal_unparse_num_i16(char* const str, const int16_t value, bool* const err);
  void tal_unparse_num_i32(char* const str, const int32_t value, bool* const err);
  void tal_unparse_num_i64(char* const str, const int64_t value, bool* const err);
  void tal_unparse_num_u8(char* const str, const uint8_t value, bool* const err);
  void tal_unparse_num_u16(char* const str, const uint16_t value, bool* const err);
  void tal_unparse_num_u32(char* const str, const uint32_t value, bool* const err);
  void tal_unparse_num_u64(char* const str, const uint64_t value, bool* const err);
  void tal_unparse_num_f(char* const str, const float value, bool* const err);
  void tal_unparse_num_d(char* const str, const double value, bool* const err);

#if defined(__cplusplus)
  } // extern "C"
#endif