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
 * @file common/util/str.h
 * @authors Aaron McBride
 * @brief String manipulation and querying utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "common/util/attribute.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section C-String Utilities
   **************************************************************************************************/

  // todo -> implement, doc
  // Appends src to dest and returns dest.
  ti_fn_attr_inline inline char* ti_strcat (char* dest, const char* src);

  // todo -> implement, doc
  // Returns pointer to first occurrence of qchar in str.
  ti_fn_attr_inline inline char* ti_strchr(const char* s, char c);

  // todo -> implement, doc
  // Return strue if str_a and str_b are equal.
  ti_fn_attr_inline inline bool ti_strcmp(const char* str_a, const char* str_b);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strmove(char* dest, const char* src);

  // todo -> implement, doc
  // Copies src to dest and returns dest.
  ti_fn_attr_inline inline char* ti_strcpy(char* restrict dest, const char* restrict src);

  // todo -> implement, doc
  ti_fn_attr_inline inline int32_t ti_strcspn(const char* str, const char* qstr);

  // todo -> implement, doc
  ti_fn_attr_inline inline int32_t ti_strlen(const char* str);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strncat(char* dest, const char* src, int32_t n);

  // todo -> implement, doc
  ti_fn_attr_inline inline bool ti_strncmp(const char* str_a, const char* str_b, int32_t n);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strncpy(char* dest, const char* src, int32_t n);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strpbrk(const char* qstr, const char* str);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strrchr(const char* str, char qchar);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strnchr(const char* str, char qchar, int32_t n);

  // todo -> implement, doc
  ti_fn_attr_inline inline int32_t ti_strspn(const char* str, const char* qstr);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strstr(const char* str, const char* qstr);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strnstr(const char* str, const char* qstr, int32_t n);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strrstr(const char* str, const char* qstr);

  // todo -> implement, doc
  ti_fn_attr_inline inline char* ti_strtok(char* str, const char* delim);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  #define ti_invalid_index -1

  char* ti_strcat (char* dest, const char* src) {
    char *ret = dest;
    while (*dest) { dest++; }
    while (*dest++ = *src++);
    return ret;
  }

  char* ti_strchr(const char* s, char c) {
    while (*s != (char)c) {
      if (!*s++) { return 0; }
    }
    return (char*)s;
  }

  int32_t ti_stridx(const char* str, const char qchar) {
    for (*s != (char)c) {
      if (!*s++) { return ti_invalid_index; }
    }
  }

  bool ti_strcmp(const char* str_a, const char* str_b) {
    if (str_a == NULL || str_b == NULL) { return false; }
    for (int32_t i = 0; true; ++i) {
      if (str_a[i] != str_b[i]) { return false; }
      if (str_a[i] == 0) { break; }
    }
    return true;
  }

  char* ti_strmove(char* dest, const char* src) {
    if (dest != NULL && src != NULL) {
      for (int32_t i = 0; true; ++i) {
        dest[i] = src[i];
        if (src[i] == 0) { break; }
      }
    }
    return dest;
  }

  char* ti_strcpy(char* restrict dest, const char* restrict src) {
    char *ret = dest;
    while (*dest++ = *src++);
    return ret;
  }

  int32_t ti_strcspn(const char* str, const char* qstr) {

  }

  int32_t ti_strlen(const char* str) {
    int32_t i = 0;
    while (str[i++] != 0);
    return i;
  }

  char* ti_strncat(char* dest, const char* src, int32_t n) {

  }

  bool ti_strncmp(const char* str_a, const char* str_b, int32_t n);

  char* ti_strncpy(char* dest, const char* src, int32_t n);

  char* ti_strpbrk(const char* qstr, const char* str);

  char* ti_strrchr(const char* str, char qchar);

  char* ti_strnchr(const char* str, char qchar, int32_t n);

  int32_t ti_strspn(const char* str, const char* qstr);

  char* ti_strstr(const char* str, const char* qstr);

  char* ti_strnstr(const char* str, const char* qstr, int32_t n);

  char* ti_strrstr(const char* str, const char* qstr);

  char* ti_strtok(char* str, const char* delim);

#if defined(__cplusplus)
  }
#endif