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
 * @file include/tal/str.h
 * @authors Aaron McBride
 * @brief String manipulation and querying utilities.
 * @warning API unstable.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "src/common/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section String Modification Utilities
   **************************************************************************************************/

  /**
   * @brief Copies all characters from a string to a new location.
   * @param dest (char*) The destination to copy to.
   * @param src (const char*) The source null-terminated byte string.
   * @param nt (bool) True if a null-terminator should be appended to 'dest'
   *           after the last copied character, false otherwise.
   * @param err (bool*) The error flag. Accessed and set true if 'dest' or 'src' 
   *            is NULL.
   * @returns (char*) 'dest'.
   * @note - This function copies every character from 'src' to contiguous bytes 
   *         in memory, starting at 'dest'.
   * @note - If 'dest' or 'src' is NULL, this function has no side effects.
   * @note - 'src' may overlap with 'dest'.
   */
  tal_fn_attr_inline inline char* tal_str_cpy(char* const dest, 
      const char* const src, const bool nt, bool* const err);

  /**
   * @brief Copies n characters from a string to a new location.
   * @param dest (char*) The destination to copy to.
   * @param src (const char*) The source null-terminated byte string.
   * @param n (int32_t) The maximum number of characters to copy.
   * @param nt (bool) True if a null-terminator should be appended to 'dest'
   *           after the last copied character, false otherwise.
   * @param err (bool*) The error flag. Accessed and set true if 'dest' or 'src' 
   *            is NULL, or 'n' is negative or greater than the length of 'src'.
   * @returns (char*) 'dest'.
   * @note - This function copies the maximum number of characters less than or 
   *         equal to both 'n' and the length of 'src' from 'src' to contiguous 
   *         bytes in memory, starting at 'dest'.
   * @note - If 'dest' or 'src' is NULL, or 'n' is negative, this function has no
   *         side effects.
   * @note - 'src' may overlap with 'dest'.
   */
  tal_fn_attr_inline inline char* tal_str_cpyn(char* const dest, 
      const char* const src, const int32_t n, bool* const err);

  /**
   * @brief Concatenates one string to annother.
   * @param dest (char*) The null-terminated byte string, to concatenate to (may
   *             be empty, i.e. length == 0).
   * @param src (const char*) The null-terminated byte string to concatenate.
   * @param err (bool*) The error flag. Accessed and set true if 'dest' or 'src'
   *            is NULL.
   * @returns (char*) 'dest'.
   * @note - This function copies every character in 'src' (including the
   *         null-terminator) to contiguous bytes in memory, starting at the 
   *         null-terminator of 'dest'.
   * @note - If 'dest' or 'src' is NULL, this function has no side effects.
   * @note - 'src' may overlap with 'dest'.
   */
  tal_fn_attr_inline inline char* tal_str_cat(char* const dest, 
      const char* const src, bool* const err);

  /**
   * @brief Concatenates n characters of one string to annother.
   * @param dest (char*) The null-terminated byte string to concatenate to (may
   *             be empty, i.e. length == 0).
   * @param src (const char*) The null-terminated byte string to concatenate.
   * @param n (int32_t) The maximum number of characters to concatenate.
   * @param err (bool*) The error flag. Accessed and set true if 'dest' or 'src'
   *            is NULL, or 'n' is negative or greater than the length of 'src'.
   * @returns (char*) 'dest'.
   * @note - This function copies the maximum number of characters less than or
   *         equal to both 'n' and the length of 'src' from 'src' to contiguous
   *         bytes in memory, starting at the null-terminator of 'dest'.
   * @note - If 'dest' or 'src' is NULL or 'n' is negative, this function has no
   *         side effects.
   * @note - A null-terminator is always appended to 'dest' after the last copied 
   *         character.
   * @note - 'src' may overlap with 'dest'.
   */
  tal_fn_attr_inline inline char* tal_str_catn(char* const dest, 
      const char* const src, const int32_t n, bool* const err);

  /**
   * @brief TODO
   * @param dest 
   * @param src 
   * @param pos 
   * @param err 
   * @return 
   */
  tal_fn_attr_inline inline char* tal_str_insert(char* const dest,
      const char* const src, const int32_t pos, bool* const err);

  /**
   * @brief TODO
   * @param dest 
   * @param src 
   * @param pos 
   * @param n 
   * @param err 
   * @return 
   */
  tal_fn_attr_inline inline char* tal_str_insertn(char* const dest,
      const char* const src, const int32_t pos, const int32_t n, 
      bool* const err);

  /**
   * @brief Swaps the contents of two strings.
   * @param str_a (char* restrict) The first null-terminated byte string to swap.
   * @param str_b (char* restrict) The second null-terminated byte string to swap.
   * @param err (bool*) The error flag. Accessed and set true if 'str_a' or 
   *            'str_b' is NULL, or 'str_a' and 'str_b' overlap.
   * @note - This function swaps every character (including the null-terminator) 
   *         in 'str_a' to contiguous bytes in memory starting at 'str_b', and 
   *         every character (including the null-terminator) in 'str_b' to 
   *         contiguous bytes in memory starting at 'str_a'.
   * @note - If 'str_a' or 'str_b' is NULL or overlap, this function has no 
   *         side effects.
   * @warning - 'str_a' and 'str_b' must NOT overlap.
   */
  tal_fn_attr_inline inline void tal_str_swap(char* const restrict str_a, 
      char* const restrict str_b, bool* const err);

  /**************************************************************************************************
   * @section String Search Utilities
   **************************************************************************************************/
 
  tal_fn_attr_inline inline char* tal_str_get(const char* const str,
      const char* const qstr, bool* const err);

  tal_fn_attr_inline inline char* tal_str_getr(const char* const str,
      const char* const qstr, bool* const err);

  tal_fn_attr_inline inline char* tal_str_getn(const char* const str,
      const char* const qstr, const int32_t n, bool* const err);
  
  tal_fn_attr_inline inline char* tal_str_index(const char* const str,
      const char* const qstr, bool* const err);
    
  tal_fn_attr_inline inline char* tal_str_indexr(const char* const str,
      const char* const qstr, bool* const err);
  
  tal_fn_attr_inline inline char* tal_str_indexn(const char* const str,
      const char* const qstr, const int32_t n, bool* const err);

  /**************************************************************************************************
   * @section String Comparison Utilities
   **************************************************************************************************/

  /**************************************************************************************************
   * @section Miscellaneous String Utilities
   **************************************************************************************************/

  /**
   * @brief Determines the length of a string.
   * @param str (const char*) The null-terminated byte string to query.
   * @returns (int32_t) The length of 'str' in bytes, not including the null 
   *          terminator.
   */
  tal_fn_attr_inline inline int32_t tal_strlen(const char* str, bool* const err);


  /**************************************************************************************************
   * @section String Search Utilities
   **************************************************************************************************/

  /**
   * @brief Compares two strings for equality.
   * @param str_a (const char*) The first null-terminated byte string to compare.
   * @param str_b (const char*) The second null-terminated byte string to compare.
   * @returns (int32_t) Negative value if str_a appears before str_b in lexicographical
   *          order, positive value if str_a appears after str_b in lexicographical
   *          order, or 0 if the two strings are equal.
   * @note - This function returns false if the two strings are of different lengths.
   * @note - 'str_a' and 'str_b' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_strcmp(const char* str_a, const char* str_b);

  /**
   * @brief Compares n characters of two strings for equality.
   * @param str_a (const char*) The first null-terminated byte string to compare.
   * @param str_b (const char*) The second null-terminated byte string to compare.
   * @param n (int32_t) The number of characters to compare.
   * @returns (int32_t) Negative value if str_a appears before str_b in lexicographical
   *          order, positive value if str_a appears after str_b in lexicographical
   *          order, or 0 if the two strings are equal.
   * @note - This function returns false if 'n' is greater then the length of 'str_a'
   *         or 'str_b'.
   * @note - 'str_a' and 'str_b' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_strncmp(const char* str_a, 
      const char* str_b, const int32_t n);
  

  /**
   * @brief Gets the length of the maximum initial segment of a string that contains
   *        only characters present in annother string.
   * @param str (const char*) The null-terminated byte string to query.
   * @param qstr (const char*) The null-terminated byte string which contains
   *             the characters to search for.
   * @returns (int32_t) The length of the maximum initial segment of 'str' that
   *          contains only characters present in 'qstr'.
   * @note - The null-terminator is not included in the length of any span/segment.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_strspn(const char* str, 
      const char* qstr);

  /**
   * @brief Gets the length of the maximum initial segment of a string that contains
   *        only characters not present in annother string.
   * @param str (const char*) The null-terminated byte string to query.
   * @param qstr (const char*) The null-terminated byte string which contains
   *            the characters characters to search for.
   * @returns (int32_t) The length of the maximum initial segment of 'str' that
   *          contains only characters not present in 'qstr'.
   * @note - The null-terminator is not included in the length of any span/segment.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_strcspn(const char* str, 
      const char* qstr);

  /**
   * @brief Gets a pointer to the first character in a string that is 
   *        contained in annother string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (const char*) The null-terminated byte string which 
   *             contains the characters to search for.
   * @returns (char*) A pointer to the first character in 'str' that is 
   *          contained in 'qstr', or NULL if no such character is found, 
   *          or the given arguments are invalid.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline char* tal_strpbrk(const char* str, 
      const char* qstr);

  /**
   * @brief Gets the index (char) of the first character in a string that is 
   *        contained in annother string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (const char*) The null-terminated byte string which contains
   * @returns (int32_t) The index (char) of the first character in 'str' that is 
   *          contained in 'qstr', or -1 if no such character is found, or the 
   *          given arguments are invalid.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_strpbrk_i(const char* str, 
      const char* qstr);

  /**
   * @brief Type which contains information about a token.
   */
  typedef struct {
    char* ptr; /** @brief Pointer to the token. */
    int32_t len; /** @brief Length of the token. */
  }tok_t;

  /**
   * @brief Gets a token from a string.
   * @param str (char*) The null-terminated byte string to get the token from.
   * @param delim (const char*) The null-terminated byte string that represents
   *              the delimiter (may be longer then one character).
   * @param n (int32_t) The index of the token to get.
   * @returns (tok_t) A struct containing a pointer to the start of the token (ptr),
   *          and an int32_t representing the length of the token (len), or NULL,
   *          and -1 if no such token exists, or the given arguments are invalid.
   * @note - This function is thread-safe unlike the standard strtok function.
   */
  tal_fn_attr_inline inline tok_t tal_strtok(char* str, const char* delim, const int32_t n);

  /**************************************************************************************************
   * @internal Helper Functions
   **************************************************************************************************/

  static bool str_overlap(const char* const str_a, const char* const str_b) {
    const uintptr_t a_addr = (uintptr_t)str_a;
    const uintptr_t b_addr = (uintptr_t)str_b;
    const uint32_t a_len = (uint32_t)tal_strlen(str_a, NULL);
    const uint32_t b_len = (uint32_t)tal_strlen(str_b, NULL);
    return (a_addr < b_addr ? (a_addr + a_len) >= b_addr : 
        (b_addr + b_len) > a_addr);
  }

  /**************************************************************************************************
   * @internal Implementation of String Modification Utilities
   **************************************************************************************************/
  
  char* tal_str_cpy(char* const dest, const char* const src, 
      const bool nt, bool* const err) {
    if (!dest || !src) {
      *err = true;
    } else {
      const uintptr_t dest_addr = (uintptr_t)dest;
      const uintptr_t src_addr = (uintptr_t)src;
      if (dest_addr <= src_addr) {
        for (int32_t i = 0; src[i - (bool)i]; ++i) {
          dest[i] = src[i];
        }
      } else {
        const int32_t src_len = tal_str_len(src, NULL);
        for (int32_t i = src_len; i >= 0; --i) {
          dest[i] = src[i];
        }
      }
    }
    return dest;
  }

  char* tal_str_cpyn(char* const dest, const char* const src, 
      const int32_t n, bool* const err) {
    if (!dest || !src) {
      *err = true;
    } else {
      const uintptr_t dest_addr = (uintptr_t)dest;
      const uintptr_t src_addr = (uintptr_t)src;
      if (dest_addr < src_addr) {
        int32_t i = 0;
        for (; i < n && src[i]; ++i) {
          dest[i] = src[i];
        }
        for (; i < n; ++i) {
          dest[i] = '\0';
        }
      } else {
        const int32_t src_len = tal_str_len(src, NULL);
        for (int32_t i = n - src_len - 1; i >= src_len; --i) {
          dest[i] = '\0';
        }
        for (int32_t i = src_len - 1; i >= 0; --i) {
          dest[i] = src[i];
        }
      }
    }
    return dest;
  }

  char* tal_str_cat(char* const dest, const char* const src, 
      bool* const err) {
    if (!dest || !src) {
      *err = true;
    } else {
      const int32_t dlen = tal_str_len(dest, NULL);
      const int32_t slen = tal_str_len(src, NULL);
      for (int32_t i = 0; i < slen; ++i) {
        dest[dlen + i] = src[i];
      }
      dest[dlen + slen] = '\0';
    }
    return dest;
  }

  char* tal_str_catn(char* dest, const char* const src, const int32_t n, 
      bool* const err) {
    if (!dest || !src || n < 0) {
      *err = true;
    } else {
      const int32_t dlen = tal_str_len(dest, NULL);
      const int32_t slen = tal_str_len(src, NULL);
      if (n > slen) { *err = true; }
      for (int32_t i = 0; i < slen && i < n; ++i) {
        dest[dlen + i] = src[i];
      }
      dest[dlen + (n < slen ? n : slen)] = '\0';
      
    }
    return dest;
  }

  tal_fn_attr_inline inline char* tal_str_insert(char* const dest,
      const char* const src, const int32_t pos, bool* const err) {
    

  }

  tal_fn_attr_inline inline char* tal_str_insertn(char* const dest,
      const char* const src, const int32_t pos, const int32_t n, 
      bool* const err) {
    
  }
  

  void tal_str_swap(char* const restrict str_a, char* const restrict str_b,
      bool* const err) {
    if (!str_a || !str_b) {
      *err = true;
    } else {
      const uintptr_t a_addr = (uintptr_t)str_a;
      const uintptr_t b_addr = (uintptr_t)str_b;
      const int32_t alen = tal_str_len(str_a, NULL);
      const int32_t blen = tal_str_len(str_b, NULL);
      // assert alen/blen > 0
      if (a_addr < b_addr ? (a_addr + (uintptr_t)alen > b_addr) : 
          (b_addr + (uintptr_t)blen > a_addr)) {
        *err = true;
      } else {
        for (int32_t i = 0; i < alen || i < blen; ++i) {
          if (i < alen && i < blen) {
            const char tmp = str_a[i];
            str_a[i] = str_b[i];
            str_b[i] = tmp;
          } else if (i < blen) {
            str_b[i] = str_a[i];
          } else {
            str_a[i] = str_b[i];
          }
        }
        str_a[blen] = '\0';
        str_b[alen] = '\0';
      }
    }
  }

  /**************************************************************************************************
   * @section String Search Utilities
   **************************************************************************************************/
 
  tal_fn_attr_inline inline char* tal_str_get(const char* const str,
      const char* const qstr, bool* const err);

  tal_fn_attr_inline inline char* tal_str_getr(const char* const str,
      const char* const qstr, bool* const err);

  tal_fn_attr_inline inline char* tal_str_getn(const char* const str,
      const char* const qstr, const int32_t n, bool* const err);
  
  tal_fn_attr_inline inline char* tal_str_index(const char* const str,
      const char* const qstr, bool* const err);
    
  tal_fn_attr_inline inline char* tal_str_indexr(const char* const str,
      const char* const qstr, bool* const err);
  
  tal_fn_attr_inline inline char* tal_str_indexn(const char* const str,
      const char* const qstr, const int32_t n, bool* const err);

  /**************************************************************************************************
   * @internal Implementation of ...
   **************************************************************************************************/

  int32_t tal_strlen(const char* str) {
    int32_t len = 0;
    if (str) { 
      while (str[len]) { ++len; } 
    }
    return len;
  }

  int32_t tal_strcmp(const char* str_a, const char* str_b) {
    if (!str_a || !str_b) { return 0; }
    while (*str_a == *str_b && *str_a && *str_b) {
      str_a++;
      str_b++;
    }
    return (int32_t)*str_a - (int32_t)*str_b;
  }

  int32_t tal_strncmp(const char* str_a, const char* str_b, const int32_t n) {
    if (str_a && str_b && n > 0) {
      for (int32_t i = 0; i < n; ++i) {
        if (*str_a != *str_b || !*str_a || !*str_b) { 
          return (int32_t)*str_a - (int32_t)*str_b; 
        }
        ++str_a;
        ++str_b;
      }
    }
    return 0;
  }

  char* tal_strchr(const char* str, char qchar) {
    if (str) {
      while (*str != qchar) {
        if (!*str) { return NULL; }
        ++str;
      }
    }
    return (char*)str;
  }

  char* tal_strrchr(const char* str, char qchar) {
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

  char* tal_strnchr(const char* str, char qchar, const int32_t n) {
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

  int32_t tal_strchr_i(const char* str, char qchar) {
    if (!str) { return -1; }
    int32_t i = 0;
    while (*str != qchar) {
      if (!*str) { return -1; }
      ++str;
      ++i;
    }
    return i;
  }

  int32_t tal_strrchr_i(const char* str, char qchar) {
    int32_t ret = -1;
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

  int32_t tal_strnchr_i(const char* str, char qchar, const int32_t n) {
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
    return -1;
  }

  int32_t tal_strspn(const char* str, const char* qstr) {
    if (!str || !qstr) { return -1; }
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

  int32_t tal_strcspn(const char* str, const char* qstr) {
    if (!str || !qstr) { return -1; }
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

  char* tal_strstr(const char* str, const char* qstr) {
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

  char* tal_strnstr(const char* str, const char* qstr, const int32_t n) {
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

  char* tal_strrstr(const char* str, const char* qstr) {
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

  int32_t tal_strstr_i(const char* str, const char* qstr) {
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
    return -1;
  }

  int32_t tal_strrstr_i(const char* str, const char* qstr) {
    int32_t ret = -1;
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

  int32_t tal_strnstr_i(const char* str, const char* qstr, const int32_t n) {
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
    return -1;
  }

  char* tal_strpbrk(const char* str, const char* qstr) {
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

  int32_t tal_strpbrk_i(const char* str, const char* qstr) {
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
    return -1;
  }

  tok_t tal_strtok(char* str, const char* delim, const int32_t n) {
    int32_t tok_cnt = 0;
    if (str && delim) {
      char* t_delim = delim;
      while (*str) {
        if (*str == *t_delim) {
          ++t_delim;
          if (!*t_delim) {
            t_delim = delim;
            ++tok_cnt;
            if (tok_cnt == n) {
              ++str;
              if (*str) {
                tok_t result = {str, 1};
                while (*str) { 
                  ++str; 
                  ++result.len;
                }
                return result;
              }
            }
          }
        } else {
          t_delim = delim;
        }
        ++str;
      }
    }
    return (tok_t){NULL, -1};
  }

#if defined(__cplusplus)
  }
#endif