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
 * @file common/util/mem.h
 * @authors Aaron McBride
 * @brief Memory manipulation and querying utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#if defined(__cplusplus)
  extern "C" {
#endif


void* ti_memcpy(void* dst, void* src, size_t size);

void* ti_memset(void* mem, char value, size_t size);

// todo impl (ask abt though)
void* ti_memmove(void* dst, void* src, size_t size);

void* ti_memexch(void* dst, void* src, char value, size_t size);

void ti_memswap(void* mem_a, void* mem_b, size_t size);

int ti_memcmp(void* mem_a, void* mem_b, size_t size);

bool ti_memeq(void* mem, char value, size_t size);

void* ti_memchr(void* mem_a, char value, size_t size);

void* ti_memrchr(void* mem_a, char value, size_t size);

// todo -> implement, doc
void* ti_memchrn(void* mem, char value, size_t size, size_t n);

void* ti_memsort(void* mem, size_t size, int (*cmp_fn)(const int*));

#if defined(__cplusplus)
  }
#endif