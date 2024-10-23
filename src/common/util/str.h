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

#define ti_err_idx -1

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section String Transformation Utilities
   **************************************************************************************************/

  ti_fn_attr_inline inline char* ti_strcat(char* dest, const char* src); // FINAL

  ti_fn_attr_inline inline char* ti_strncat(char* dest, const char* src, int32_t n); // FINAL

  ti_fn_attr_inline inline char* ti_strcpy(char* restrict dest, const char* restrict src); // FINAL

  /**************************************************************************************************
   * @section String Comparison Utilities
   **************************************************************************************************/

  ti_fn_attr_inline inline int32_t ti_strcmp(const char* str_l, const char* str_r); // FINAL

  ti_fn_attr_inline inline int32_t ti_strncmp(const char* str_l, const char* str_r, int32_t n); // FINAL


  /**************************************************************************************************
   * @section Character Query Utilities
   **************************************************************************************************/

  ti_fn_attr_inline inline char* ti_strchr(const char* str, char qchar); // FINAL

  ti_fn_attr_inline inline char* ti_strrchr(const char* str, char qchar); // FINAL

  ti_fn_attr_inline inline char* ti_strnchr(const char* str, char qchar, int32_t n); // FINAL


  ti_fn_attr_inline inline int32_t ti_stridx(const char* str, char qchar); // FINAL

  ti_fn_attr_inline inline int32_t ti_strridx(const char* str, char qchar); // FINAL

  ti_fn_attr_inline inline int32_t ti_strnidx(const char* str, char qchar, int32_t n); // FINAL


  ti_fn_attr_inline inline int32_t ti_strspn(const char* dest, const char* src);

  ti_fn_attr_inline inline int32_t ti_strcspn(const char* str, const char* qstr);

  ti_fn_attr_inline inline int32_t ti_strspn(const char* str, const char* qstr);


  /**************************************************************************************************
   * @section String Query Utilities
   **************************************************************************************************/




  // // todo -> implement, doc

  // // todo -> implement, doc
  // ti_fn_attr_inline inline int32_t ti_strlen(const char* str);


  // // todo -> implement, doc

  // // todo -> implement, doc
  // ti_fn_attr_inline inline char* ti_strncpy(char* dest, const char* src, int32_t n);

  // // todo -> implement, doc
  // ti_fn_attr_inline inline char* ti_strpbrk(const char* qstr, const char* str);


  // // todo -> implement, doc

  // // todo -> implement, doc
  // ti_fn_attr_inline inline char* ti_strstr(const char* str, const char* qstr);

  // // todo -> implement, doc
  // ti_fn_attr_inline inline char* ti_strnstr(const char* str, const char* qstr, int32_t n);

  // // todo -> implement, doc
  // ti_fn_attr_inline inline char* ti_strrstr(const char* str, const char* qstr);

  // // todo -> implement, doc
  // ti_fn_attr_inline inline char* ti_strtok(char* str, const char* delim);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  // Transform

  char* ti_strcat (char* dest, const char* src) {
    if (dest && src) {
      char* tdest = dest;
      while (*tdest) { ++tdest; }
      while (*src) { 
        *tdest = *src; 
        ++tdest;
        ++src;
      }
    }
    return dest;
  }

  char* ti_strncat(char* dest, const char* src, int32_t n) {
    if (dest && src && n > 0) {
      char* tdest = dest;
      while (*tdest) { ++tdest; }
      for (int32_t i = 0; i < n && *src; ++i) {
        *tdest = *src;
        ++tdest;
        ++src;
      }
    }
    return dest;
  }

  char* ti_strcpy(char* restrict dest, const char* restrict src) {
    if (dest && src) {
      char* tdest = dest;
      while (*src) {
        *tdest = *src;
        ++tdest;
        ++src;
      }
    }
    return dest;
  }


  // Compare

  int32_t ti_strcmp(const char* str_l, const char* str_r) {
    if (!str_l || !str_r) { return 0; }
    while (*str_l == *str_r && *str_l && *str_r) {
      str_l++;
      str_r++;
    }
    return (int32_t)*str_l - (int32_t)*str_r;
  }

  int32_t ti_strncmp(const char* str_l, const char* str_r, int32_t n) {
    if (str_l && str_r && n > 0) {
      for (int32_t i = 0; i < n; ++i) {
        if (*str_l != *str_r || !*str_l || !*str_r) { 
          return (int32_t)*str_l - (int32_t)*str_r; 
        }
        ++str_l;
        ++str_r;
      }
    }
    return 0;
  }


  // Query

  char* ti_strchr(const char* str, char qchar) {
    if (str) {
      while (*str != qchar) {
        if (!*str) { return NULL; }
        ++str;
      }
    }
    return (char*)str;
  }

  char* ti_strrchr(const char* str, char qchar) {
    if (str) {
      const char* tstr = str;
      while (*tstr) {
        if (*tstr == qchar) { str = tstr; }
        ++tstr;
      }
      if (!qchar) { return (char*)tstr; }
    }
    return (char*)str;
  }

  char* ti_strnchr(const char* str, char qchar, int32_t n) {
    if (str && n > 0)  {
      int32_t count = 0;
      while (*str) {
        if (*str == qchar) {
          ++count;
          if (count >= n) { return (char*)str; }
        }
        ++str;
      }
      if (!qchar && n == 1) { return (char*)str; }
    }
    return NULL;
  }



  int32_t ti_stridx(const char* str, char qchar) {
    if (!str) { return ti_err_idx; }
    int32_t i = 0;
    while (*str != qchar) {
      if (!*str) { return ti_err_idx; }
      ++str;
      ++i;
    }
    return i;
  }

  int32_t ti_strridx(const char* str, char qchar) {
    int32_t ret = ti_err_idx;
    if (str) {
      int32_t i = 0;
      while (*str) {
        if (*str == qchar) { ret == i; }
        ++str;
        ++i;
      }
      if (!qchar) { return i; }
    }
    return ret;
  }

  int32_t ti_strnidx(const char* str, char qchar, int32_t n) {
    if (str) {
      int32_t count = 0;
      int32_t i = 0;
      while (*str) {
        if (*str == qchar) {
          ++count;
          if (count >= n) { return i; }
        }
        ++str;
        ++i;
      }
      if (!qchar && n == 1) { return i; }
    }
    return ti_err_idx;
  }



  int32_t ti_strspn(const char* dest, const char* src) {
    

  }

  int32_t ti_strcspn(const char* str, const char* qstr);

  int32_t ti_strspn(const char* str, const char* qstr);





  int32_t ti_strspn(const char* str, const char* qstr) {
    if (!str || !qstr) { return ti_err_idx; }
    int32_t i = 0;
    while (str[i]) {
      int32_t j = 0;
      while (qstr[j] != str[i]) {
        if (!qstr[j]) { return i; }
        ++j;
      }
      ++i;
    }
    return i;
  }

  int32_t ti_strcspn(const char* str, const char* qstr) {
    if (!str || !qstr) { return ti_err_idx; }
    int32_t i = 0;
    while (str[i]) {
      int32_t j = 0;
      while (qstr[j]) {
        if (str[i] == qstr[j]) { return i; }
        ++j;
      }
      ++i;
    }
    return i;
  }

  int32_t ti_strlen(const char* str) {
    if (!str) { return ti_err_idx; }
    int32_t i;
    for (i = 0; str[i]; ++i);
    return i;
  }

  // head


  char* ti_strncpy(char* dest, const char* src, int32_t n) {
    if (dest && src) {
      char* tdest = dest;
      for (int32_t i = 0; i < n && *tdest && *src; ++i) {
        *tdest = *src;
        ++tdest;
        ++src;
      }
    }
    return dest;
  }

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