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
   * @section Standard String Utilities
   **************************************************************************************************/

  ti_fn_attr_inline inline int32_t ti_strlen(const char* str); // FINAL

  ti_fn_attr_inline inline char* ti_strcpy(char* restrict dest, const char* restrict src); // FINAL

  ti_fn_attr_inline inline char* ti_strcat(char* dest, const char* src); // FINAL

  ti_fn_attr_inline inline char* ti_strncat(char* dest, const char* src, int32_t n); // FINAL

  ti_fn_attr_inline inline int32_t ti_strcmp(const char* str_l, const char* str_r); // FINAL

  ti_fn_attr_inline inline int32_t ti_strncmp(const char* str_l, const char* str_r, int32_t n); // FINAL

  ti_fn_attr_inline inline char* ti_strchr(const char* str, char qchar); // FINAL

  ti_fn_attr_inline inline char* ti_strrchr(const char* str, char qchar); // FINAL

  ti_fn_attr_inline inline char* ti_strnchr(const char* str, char qchar, int32_t n); // FINAL

  ti_fn_attr_inline inline int32_t ti_strchr_i(const char* str, char qchar); // FINAL

  ti_fn_attr_inline inline int32_t ti_strrchr_i(const char* str, char qchar); // FINAL

  ti_fn_attr_inline inline int32_t ti_strnchr_i(const char* str, char qchar, int32_t n); // FINAL

  ti_fn_attr_inline inline int32_t ti_strspn(const char* str, const char* qstr); // FINAL

  ti_fn_attr_inline inline int32_t ti_strcspn(const char* str, const char* qstr); // FINAL

  ti_fn_attr_inline inline char* ti_strstr(const char* str, const char* qstr); // FINAL

  ti_fn_attr_inline inline char* ti_strnstr(const char* str, const char* qstr, int32_t n); // FINAL

  ti_fn_attr_inline inline char* ti_strrstr(const char* str, const char* qstr); // FINAL

  ti_fn_attr_inline inline int32_t ti_strstr_i(const char* str, const char* qstr); // FINAL

  ti_fn_attr_inline inline int32_t ti_strrstr_i(const char* str, const char* qstr); // FINAL

  ti_fn_attr_inline inline int32_t ti_strnstr_i(const char* str, const char* qstr, int32_t n); // FINAL

  ti_fn_attr_inline inline char* ti_strpbrk(const char* str, const char* qstr); // FINAL

  ti_fn_attr_inline inline int32_t ti_strpbrk_i(const char* str, const char* qstr); // FINAL

  ti_fn_attr_inline inline char* ti_strtok(char* str, const char* delim); // TODO

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

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
      const char* t_str = str;
      while (*t_str) {
        if (*t_str == qchar) { str = t_str; }
        ++t_str;
      }
      if (!qchar) { return (char*)t_str; }
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

  int32_t ti_strchr_i(const char* str, char qchar) {
    if (!str) { return ti_err_idx; }
    int32_t i = 0;
    while (*str != qchar) {
      if (!*str) { return ti_err_idx; }
      ++str;
      ++i;
    }
    return i;
  }

  int32_t ti_strrchr_i(const char* str, char qchar) {
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

  int32_t ti_strnchr_i(const char* str, char qchar, int32_t n) {
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

  int32_t ti_strspn(const char* str, const char* qstr) {
    if (!str || !qstr) { return ti_err_idx; }
    int32_t count = 0;
    while (*str) {
      const char* t_qstr = qstr;
      while (*str != *t_qstr) {
        ++t_qstr;
        if (!*t_qstr) { return count; }
      }
      ++count;
      ++str;
    }
    return count;
  }

  int32_t ti_strcspn(const char* str, const char* qstr) {
    if (!str || !qstr) { return ti_err_idx; }
    int32_t count = 0;
    while (*str) {
      const char* t_qstr = qstr;
      while (*t_qstr) {
        if (*t_qstr == str) { return count; }
        ++t_qstr;
      }
      ++count;
      ++str;
    }
    return count;
  }

  char* ti_strstr(const char* str, const char* qstr) {
    if (str && qstr) {
      const char* t_str = str;
      const char* t_qstr = qstr;
      while (*str) {
        if (*t_qstr == *str) {
          ++t_qstr;
          if (!*t_qstr) { return (char*)t_str; }
        } else {
          t_qstr = qstr;
          t_str = str;
        }
        ++str;
      }
    }
    return NULL;
  }

  char* ti_strnstr(const char* str, const char* qstr, int32_t n) {
    if (str && qstr) {
      int32_t count = 0;
      const char* t_qstr = qstr;
      while (*str) {
        if (*t_qstr == *str) {
          ++t_qstr;
          if (!*t_qstr) {
            ++count;
            if (count == n) { return (char*)t_qstr; }
          }
        } else {
          t_qstr = qstr;
        }
        ++str;
      }
    }
    return NULL;
  }

  char* ti_strrstr(const char* str, const char* qstr) {
    const char* lstr = NULL;
    if (str && qstr) {
      const char* t_str = str;
      const char* t_qstr = qstr;
      while (*str) {
        if (*t_qstr == *str) {
          ++t_qstr;
          if (t_qstr == *str) { lstr = t_str; }
        } else {
          t_qstr = qstr;
          t_str = str; 
        }
        ++str;
      }
    }
    return (char*)lstr;
  }

  int32_t ti_strstr_i(const char* str, const char* qstr) {
    if (str && qstr) {
      int32_t i = 0;
      const char* t_qstr = qstr;
      while (*str) {
        if (*t_qstr == *str) {
          ++t_qstr;
          if (!*t_qstr) { return i; }
        } else {
          t_qstr = qstr;
        }
        ++str;
        ++i;
      }
    }
    return ti_err_idx;
  }

  int32_t ti_strrstr_i(const char* str, const char* qstr) {
    int32_t ret = ti_err_idx;
    if (str && qstr) {
      int32_t i = 0;
      const char* t_qstr = qstr;
      while (*str) {
        if (*t_qstr == *str) {
          ++t_qstr;
          if (!*t_qstr) { ret = i; }
        } else {
          t_qstr = qstr;
        }
        ++str;
        ++i;
      }
    }
    return ret;
  }

  int32_t ti_strnstr_i(const char* str, const char* qstr, int32_t n) {
    if (str && qstr && n > 0) {
      int32_t i = 0;
      int32_t count = 0;
      const char* t_qstr = qstr;
      while (*str) {
        if (*t_qstr == *str) {
          ++t_qstr;
          if (!*t_qstr) { 
            ++count; 
            if (count == n) { return i; }
          }
        } else {
          t_qstr = qstr;
        }
        ++str;
        ++i;
      }
    }
    return ti_err_idx;
  }

  char* ti_strpbrk(const char* str, const char* qstr) {
    if (str && qstr) {
      while (*str) {
        const char* t_qstr = qstr;
        while (*t_qstr) {
          if  (*t_qstr == *str) { return (char*)str; }
        }
        ++str;
      }
    }
    return NULL;
  }

  int32_t ti_strpbrk_i(const char* str, const char* qstr) {
    if (str && qstr) {
      int32_t i = 0;
      while (*str) {
        const char* t_qstr = qstr;
        while (*t_qstr) {
          if (*t_qstr == str) { return i; }
        }
        ++str;
        ++i;
      }
    }
    return ti_err_idx;
  }

  int32_t ti_strlen(const char* str) {
    int32_t len = 0;
    while (str[len]) { ++len; }
    return len;
  }

#if defined(__cplusplus)
  }
#endif