/**
 * This file is part of the Titan Project.
 * Copyright (c) 2025 UW SARP
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
 * @file modules/util/src/atomic.c
 * @authors Aaron McBride
 * @brief Implementation of atomic operations.
 */

#include "util/atomic.h" // header

uint32_t atomic_load(const volatile uint32_t* src) {
  uint32_t val;
  // Load operations are inherently atomic so no need for LDREX/STREX
  // DMB required to prevent reordering of subsequent memory accesses
  asm volatile (
    "ldr %[val], [%[src]] \n\t"
    "dmb                  \n\t"
    : [val] "=r" (val)
    : [src] "r" (src)
    : "memory"
  );
  return val;
}

void atomic_store(volatile uint32_t* dst, uint32_t value) {
  // Store operations are inherently atomic so no need for LDREX/STREX
  // DMB required to prevent reordering of subsequent memory accesses
  asm volatile (
    "str %[value], [%[dst]] \n\t"
    "dmb                    \n\t"
    :
    : [dst] "r" (dst), [value] "r" (value)
    : "memory"
  );
}

uint32_t atomic_exchange(volatile uint32_t* dst, uint32_t value) {
  uint32_t old, status;
  do {
    // Status != 0 if dst is modified or interrupt occurs between LDREX/STREX
    // "=&r" required for outputs because they are clobbered before inputs are read
    asm volatile (
      "ldrex %[old], [%[dst]]              \n\t"
      "strex %[status], %[value], [%[dst]] \n\t"
      : [old] "=&r" (old), [status] "=&r" (status)
      : [dst] "r" (dst), [value] "r" (value)
      : "memory"
    );
  } while (status != 0);
  // Prevents reordering of subsequent memory accesses
  asm volatile("dmb" ::: "memory");
  return old;
}

bool atomic_cmp_exchange(volatile uint32_t* dst, uint32_t* expected, uint32_t desired) {
  uint32_t old, status;
  do {
    // Status != 0 if dst is modified or interrupt occurs between LDREX/STREX
    // "=&r" required for outputs because they are clobbered before inputs are read
    // "cc" required in clobber list because CPU flags are used by "cmp" instruction
    asm volatile (
      "ldrex %[old], [%[dst]]                \n\t"
      "cmp %[old], %[cmp_value]              \n\t"
      "bne 1f                                \n\t"
      "strex %[status], %[desired], [%[dst]] \n\t"
      "b 2f                                  \n\t"
      "1: mov %[status], #0xFF               \n\t"
      "2:                                    \n\t"
      : [old] "=&r" (old), [status] "=&r" (status)
      : [dst] "r" (dst), [cmp_value] "r" (*expected), [desired] "r" (desired)
      : "cc", "memory"
    );
    if (old != *expected) {
      // Must clear exclusive monitor because no value will be stored with STREX
      asm volatile("clrex" ::: "memory");
      *expected = old;
      return false;
    }
  } while (status != 0);
  // Prevents reordering of subsequent memory accesses
  asm volatile("dmb" ::: "memory");
  return true;
}

uint32_t atomic_add(volatile uint32_t* dst, uint32_t value) {
  uint32_t old, newv, status;
  do {
    // Status != 0 if dst is modified or interrupt occurs between LDREX/STREX
    // "=&r" required for outputs because they are clobbered before inputs are read
    // "cc" required in clobber list because CPU flags are used by "add" instruction
    asm volatile (
      "ldrex %[old], [%[dst]]             \n\t"
      "add %[newv], %[old], %[value]      \n\t"
      "strex %[status], %[newv], [%[dst]] \n\t"
      : [old] "=&r" (old), [newv] "=&r" (newv), [status] "=&r" (status)
      : [dst] "r" (dst), [value] "r" (value)
      : "cc", "memory"
    );
  } while (status != 0);
  // Prevents reordering of subsequent memory accesses
  asm volatile("dmb" ::: "memory");
  return old;
}

uint32_t atomic_sub(volatile uint32_t* dst, uint32_t value) {
  uint32_t old, newv, status;
  do {
    // Status != 0 if dst is modified or interrupt occurs between LDREX/STREX
    // "=&r" required for outputs because they are clobbered before inputs are read
    // "cc" required in clobber list because CPU flags are used by "sub" instruction
    asm volatile (
      "ldrex %[old], [%[dst]]             \n\t"
      "sub %[newv], %[old], %[value]      \n\t"
      "strex %[status], %[newv], [%[dst]] \n\t"
      : [old] "=&r" (old), [newv] "=&r" (newv), [status] "=&r" (status)
      : [dst] "r" (dst), [value] "r" (value)
      : "cc", "memory"
    );
  } while (status != 0);
  // Prevents reordering of subsequent memory accesses
  asm volatile("dmb" ::: "memory");
  return old;
}