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
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "include/tal/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section String Utilities
   **************************************************************************************************/

  /**
   * @brief Determines the length of a string.
   * @param str (const char*) The null-terminated byte string to query.
   * @returns (int32_t) The length of 'str' in bytes, not including the null 
   *          terminator.
   */
  tal_fn_attr_inline inline int32_t tal_strlen(const char* str);

  /**
   * @brief Copies a string from one location to annother.
   * @param dest (char*) The destination to copy to.
   * @param src (const char*) The source null-terminated byte string.
   * @returns (char*) A pointer to the destination.
   * @note - This function copies all characters from 'src' to 'dest', including
   *         the null terminator.
   * @warning - The source and destination locations must NOT overlap.
   */
  tal_fn_attr_inline inline char* tal_strcpy(char* restrict dest, 
      const char* restrict src);

  /**
   * @brief Copies n characters of a string from one location to annother.
   * @param dest (char*) The destination to copy to.
   * @param src (const char*) The source null-terminated byte string.
   * @param n (int32_t) The number of characters to copy.
   * @returns (char*) A pointer to the destination.
   */
  tal_fn_attr_inline inline char* tal_strncpy(char* restrict dest, 
      const char* restrict src, const int32_t n);

  /**
   * @brief Swaps the contents of two strings.
   * @param str_a (char* restrict) The first null-terminated byte string to swap.
   * @param str_b (char* restrict) The second null-terminated byte string to swap.
   * @note - This function swaps the contents of 'str_a' and 'str_b', including their
   *         null terminators.
   * @warning - The source and destination locations must NOT overlap.
   */
  tal_fn_attr_inline inline void tal_strswap(char* restrict str_a, 
      char* restrict str_b);

  /**
   * @brief Concatenates one string to annother.
   * @param dest (char*) The null-terminated byte string to concatenate to.
   * @param src (const char*) The null-terminated byte string to concatenate.
   * @returns (char*) A pointer to the destination.
   * @note - This function removes the null-terminator from 'dest' and appends
   *         every character (including the null-terminator) from 'src' to 
   *         'dest', starting at it's location.
   * @warning - The source and destination locations must NOT overlap.
   */
  tal_fn_attr_inline inline char* tal_strcat(char* restrict dest, 
      const char* restrict src);

  /**
   * @brief Concatenates n characters from one string to annother.
   * @param dest (char*) The null-terminated byte string to concatenate to.
   * @param src (const char*) The null-terminated byte string to concatenate.
   * @param n (int32_t) The number of characters from 'src' to concatenate.
   * @returns (char*) A pointer to the destination.
   * @note - This function removes the null-terminator from 'dest' and appends
   *         'n' characters (and a null-terminator) from 'src' to 'dest', 
   *         starting at it's location.
   * @note - 'n' may be greater than the length of 'src'.
   * @warning - The source and destination locations must NOT overlap.
   */
  tal_fn_attr_inline inline char* tal_strncat(char* restrict dest, 
      const char* restrict src, const int32_t n);

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
   * @brief Gets a pointer to the first occurance of a specific character in a string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qchar (char) The character to search for.
   * @returns (char*) A pointer to the first occurance of 'qchar' in 'str', or NULL
   *          if 'qchar' is not found, or the given arguments are invalid.
   * @note 'qchar' may be the null-terminator.
   */
  tal_fn_attr_inline inline char* tal_strchr(const char* str, char qchar);

  /**
   * @brief Gets a pointer to the last occurance of a specific character in a string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qchar (char) The character to search for.
   * @returns (char*) A pointer to the last occurance of 'qchar' in 'str', or NULL
   *          if 'qchar' is not found, or the given arguments are invalid.
   * @note 'qchar' may be the null-terminator.
   */
  tal_fn_attr_inline inline char* tal_strrchr(const char* str, char qchar);

  /**
   * @brief Gets a pointer to the nth occurance of a specific character in a string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qchar (char) The character to search for.
   * @param n (int32_t) The index of the matching location to get.
   * @returns (char*) A pointer to the nth occurance of 'qchar' in 'str', or NULL
   *          if 'qchar' is not found, or the given arguments are invalid.
   * @note 'qchar' may be the null-terminator.
   */
  tal_fn_attr_inline inline char* tal_strnchr(const char* str, 
      char qchar, const int32_t n);

  /**
   * @brief Gets the index of the first occurance of a specific character in a string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (char) The character to search for.
   * @returns (int32_t) The index of the first occurance of 'qchar' in 'str', or -1
   *          if 'qchar' is not found, or the given arguments are invalid.
   * @note 'qchar' may be the null-terminator.
   */
  tal_fn_attr_inline inline int32_t tal_strchr_i(const char* str, char qchar);

  /**
   * @brief Gets the index of the last occurance of a specific character in a string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qchar (char) The character to search for.
   * @returns (int32_t) The index of the last occurance of 'qchar' in 'str', or -1
   *          if 'qchar' is not found, or the given arguments are invalid.
   * @note 'qchar' may be the null-terminator.
   */
  tal_fn_attr_inline inline int32_t tal_strrchr_i(const char* str, char qchar);

  /**
   * @brief Gets the index of the nth occurance of a specific character in a string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qchar (char) The character to search for.
   * @param n (int32_t) The index of the matching location to get.
   * @returns (int32_t) The index of the nth occurance of 'qchar' in 'str', or -1
   *          if 'qchar' is not found, or the given arguments are invalid.
   * @note 'qchar' may be the null-terminator.
   */
  tal_fn_attr_inline inline int32_t tal_strnchr_i(const char* str, 
      char qchar, const int32_t n);

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
   * @brief Gets a pointer to the first occurance of a specific string within 
   *        annother string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (const char*) The null-terminated byte string to search for.
   * @returns (char*) A pointer to the first occurance of 'qstr' in 'str', or NULL
   *          if 'qstr' is not found, or the given arguments are invalid.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline char* tal_strstr(const char* str, 
      const char* qstr);


  /**
   * @brief Gets a pointer to the last occurance of a specific string within
   *        annother string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (const char*) The null-terminated byte string to search for.
   * @returns (char*) A pointer to the last occurance of 'qstr' in 'str', or NULL
   *          if 'qstr' is not found, or the given arguments are invalid.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline char* tal_strrstr(const char* str, 
      const char* qstr);


  /**
   * @brief Gets a pointer to the nth occurance of a specific string within
   *        annother string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (const char*) The null-terminated byte string to search for.
   * @param n (int32_t) The index of the matching string to get.
   * @returns (char*) A pointer to the nth occurance of 'qstr' in 'str', or NULL
   *          if 'qstr' is not found, or the given arguments are invalid.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline char* tal_strnstr(const char* str, 
      const char* qstr, const int32_t n);

  /**
   * @brief Gets the index (char) of the first occurance of a specific string 
   *        within annother string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (const char*) The null-terminated byte string to search for.
   * @returns (int32_t) The index of the first occurance of 'qstr' in 'str', or -1
   *          if 'qstr' is not found, or the given arguments are invalid.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_strstr_i(const char* str, 
      const char* qstr);

  /**
   * @brief Gets the index (char) of the last occurance of a specific string 
   *        within annother string.
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (const char*) The null-terminated byte string to search for.
   * @return (int32_t) The index of the last occurance of 'qstr' in 'str', or -1
   *         if 'qstr' is not found, or the given arguments are invalid.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_strrstr_i(const char* str, 
      const char* qstr);

  /**
   * @brief Gets the index (char) of the nth occurance of a specific string
   * @param str (const char*) The null-terminated byte string to search.
   * @param qstr (const char*) The null-terminated byte string to search for.
   * @param n (int32_t) The index of the matching string to get.
   * @returns (int32_t) The index of the nth occurance of 'qstr' in 'str', or -1
   *          if 'qstr' is not found, or the given arguments are invalid.
   * @note - 'str' and 'qstr' may overlap.
   */
  tal_fn_attr_inline inline int32_t tal_strnstr_i(const char* str, 
      const char* qstr, const int32_t n);

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
   * @brief Tokenizes a string.
   * @param str (char*) The null-terminated byte string to tokenize.
   * @param delim (const char*) The null-terminated byte string that represents
   *              the delimiter (may be longer then one character).
   * @returns (int32_t) The number of tokens in 'str'.
   * @note - This function inserts null-terminators into 'str' at the locations
   *         of every delimiter.
   * @note - This function is thread-safe.
   */
  tal_fn_attr_inline inline int32_t tal_strtokn(char* str, const char* delim);

  /**
   * @brief Un-tokenizes a string.
   * @param str (char*) The null-terminated byte string to un-tokenize.
   * @param delim (const char*) The null-terminated byte string that represents
   *              the delimiter (may be longer then one character).
   * @param len (int32_t) The length of 'str' before it was tokenized.
   * @returns (char*) A pointer to 'str'.
   * @note - This function reverses the changes made by 'tal_strtokn'.
   * @note - This function is thread-safe.
   */
  tal_fn_attr_inline inline char* tal_strtokn_reset(char* str, 
      const int32_t len, const char* delim);

  /**
   * @brief Gets token 'n' from a tokenized string.
   * @param str (char*) The null-terminated byte string to query (must be 
   *            tokenized using 'tal_strtokn').
   * @param len (int32_t) The length of 'str'.
   * @param n (int32_t) The index of the token to get.
   * @returns (char*) A pointer to the start of the nth token in 'str' or NULL 
   *          if no such token exists, or if the given arguments are invalid.
   * @note - This function is thread-safe.
   */
  tal_fn_attr_inline inline char* tal_strtokn_get(char* str, 
      const int32_t len, const int32_t n);

  /**
   * @brief Gets the next token in a tokenized string.
   * @param str (const char*) The null-terminated byte string tokenized using
   *            'tal_strtokn'.
   * @param str_iter (char**) A pointer to the current token in 'str'.
   * @param len (int32_t) The length of 'str'.
   * @returns (char*) A pointer to the next token in 'str', or NULL if no such
   *          token exists, or the given arguments are invalid (note that this
   *          is equal to the value of 'str_iter' after the function call).
   * @note - This function is thread-safe.
   */
  tal_fn_attr_inline inline char* tal_strtokn_next(const char* str, 
      const int32_t len, char** str_iter);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/
  
  int32_t tal_strlen(const char* str) {
    int32_t len = 0;
    if (str) { 
      while (str[len]) { ++len; } 
    }
    return len;
  }

  char* tal_strcpy(char* restrict dest, const char* restrict src) {
    if (dest && src) {
      char* d = dest;
      while (*src) {
        *d = *src;
        ++d;
        ++src;
      }
    }
    return dest;
  }

  char* tal_strncpy(char* restrict dest, const char* restrict src, 
      const int32_t n) {
    if (dest && src && n > 0) {
      char* d = dest;
      for (int32_t i = 0; i < n && *src; ++i) {
        *d = *src;
        ++d;
        ++src;
      }
    }
    return dest;
  }

  char* tal_strcat (char* restrict dest, const char* restrict src) {
    if (dest && src) {
      char* d = dest;
      while (*d) { ++d; }
      while (*src) { 
        *d = *src; 
        ++d;
        ++src;
      }
    }
    return dest;
  }

  char* tal_strncat(char* restrict dest, const char* restrict src, const int32_t n) {
    if (dest && src && n > 0) {
      char* d = dest;
      while (*d) { ++d; }
      for (int32_t i = 0; i < n && *src; ++i) {
        *d = *src;
        ++d;
        ++src;
      }
    }
    return dest;
  }

  void tal_strswap(char* restrict str_a, char* restrict str_b) {
    if (str_a && str_b) {
      while (*str_a && *str_b) {
        char tmp = *str_a;
        *str_a = *str_b;
        *str_b = tmp;
        ++str_a;
        ++str_b;
      }
      str_a = 0;
      str_b = 0;
    }
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

  int32_t tal_strtokn(char* str, const char* delim) {
    int32_t tok_cnt = 0;
    if (str && delim) {
      const int32_t dlen = strlen(delim);
      char* t_delim = delim;
      while (*str) {
        if (*str == *t_delim) {
          ++t_delim;
          if (!*t_delim) {
            for (int32_t i = 0; i < dlen; ++i) {
              str[-i] = '\0';
            }
            t_delim = delim;
            ++tok_cnt;
          }
        } else {
          t_delim = delim;
        }
        ++str;
      }
    }
    return tok_cnt;
  }

  char* tal_strtokn_reset(char* str, const int32_t len, const char* delim) {
    if (str && delim && len > 0) {
      char* t_delim = delim;
      for (int32_t i = 0; i < len; ++i) {
        if (str[i] == '\0') {
          str[i] = t_delim;
          ++t_delim;
        } else {
          t_delim = delim;
        }
      }
    }
    return str;
  }

  char* tal_strtokn_get(char* str, const int32_t len, const int32_t n) {
    if (str && len > 0 && n >= 0) {
      int32_t tok_cnt = 0;
      for (int32_t i = 0; i < len; ++i) {
        if (str[i] == '\0') {
          if (str[i - 1] != '\0') { ++tok_cnt; }
        } else if (tok_cnt == n) {
          return str[i];
        }
      }
    }
    return NULL;
  }

  char* tal_strtokn_next(const char* str, const int32_t len, char** iter_str) {
    if (str && iter_str && *iter_str && len > 0) {
      while (**iter_str) {
        const uint32_t addr_diff = (uint32_t)iter_str - (uint32_t)str;
        if (addr_diff >= (uint32_t)len) { return NULL; }
        ++(*iter_str);
      }
      while (!**iter_str) {
        const uint32_t addr_diff = (uint32_t)iter_str - (uint32_t)str;
        if (addr_diff >= (uint32_t)len) { return NULL; }
        ++(*iter_str);
      }
    }
    return *iter_str;
  }

#if defined(__cplusplus)
  }
#endif