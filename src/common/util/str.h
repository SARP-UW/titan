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
#include <string.h>

#if defined(__cplusplus)
  extern "C" {
#endif


// todo -> implement, doc
// Appends src to dst and returns dst.
char* ti_strcat (char* dst, const char* src);

// todo -> implement, doc
// Returns pointer to first occurrence of qchar in str.
char* ti_strchr(const char* str, char qchar);

// todo -> implement, doc
// Return strue if str_a and str_b are equal.
bool ti_strcmp(const char* str_a, const char* str_b);

// todo -> implement, doc
char* ti_strmove(char* dst, const char* src);

// todo -> implement, doc
// Copies src to dst and returns dst.
char* ti_strcpy(char* dst, const char* src);

// todo -> implement, doc
size_t ti_strcspn(const char* str, const char* qstr);

// todo -> implement, doc
size_t ti_strlen(const char* str);

// todo -> implement, doc
char* ti_strncat(char* dst, const char* src, size_t n);

// todo -> implement, doc
bool ti_strncmp(const char* str_a, const char* str_b, size_t n);

// todo -> implement, doc
char* ti_strncpy(char* dst, const char* src, size_t n);

// todo -> implement, doc
char* ti_strpbrk(const char* qstr, const char* str);

// todo -> implement, doc
char* ti_strrchr(const char* str, char qchar);

// todo -> implement, doc
char* ti_strnchr(const char* str, char qchar, size_t n);

// todo -> implement, doc
size_t ti_strspn(const char* str, const char* qstr);

// todo -> implement, doc
char* ti_strstr(const char* str, const char* qstr);

// todo -> implement, doc
char* ti_strnstr(const char* str, const char* qstr, size_t n);

// todo -> implement, doc
char* ti_strrstr(const char* str, const char* qstr);

// todo -> implement, doc
char* ti_strtok(char* str, const char* delim);

#if defined(__cplusplus)
  }
#endif