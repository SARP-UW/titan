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
 * @file src/STM32H7x5/internal/util.h
 * @authors Aaron McBride
 * @brief Core language utilities.
 */

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>
#include <arm_acle.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**********************************************************************************************
   * @section Overflow Detection
   **********************************************************************************************/

  #ifdef __GNUC__
    #define chk_neg(lhs, rhs, flag) ({ \
    })
  #endif

  #ifdef __GNUC__
    #define chk_add(lhs, rhs, flag) ({ \
      typeof(lhs + rhs) result = 0; \
      const bool ovf = __builtin_add_overflow(lhs, rhs, &result); \
      if (ovf && flag) { *flag = true; } \
      result; \ 
    })
  #endif

  #ifdef __GNUC__
  #define chk_sub(lhs, rhs, flag) ({ \

  })
  #endif

  #define chk_mul(lhs, rhs, flag) ({ \
  })

  #define chk_cast(value, type, flag) ({ \
  })

  /**********************************************************************************************
   * @section Numeric Utilities 
   **********************************************************************************************/

  /**
   * @brief Safely compares two integer values.
   * @param lhs (integer expression) The left-hand value to compare.
   * @param rhs (integer expression) The right-hand value to compare.
   * @returns (int32_t) -1 if lhs < rhs, 1 if lhs > rhs, or 0 otherwise.
   * @note - The behavior of this macro is defined regardles of the
   *         signedness of the given arguments.
   */
  #define cmp(lhs, rhs) ({ \
    typedef typeof(lhs + rhs) cmn_t; \
    __auto_type const lhs_ = (lhs); \
    __auto_type const rhs_ = (rhs); \
    int32_t result 0; \
    if ((lhs_ > 0) && (rhs_ < 0)) { \
      result = 1; \
    } else if ((lhs_ < 0) && (rhs_ > 0)) { \
      result = -1; \
    } else if ((cmn_t)lhs_ > (cmn_t)rhs_) { \
      result = 1; \
    } else if ((cmn_t)lhs_ < (cmn_t)rhs_) { \
      result = -1; \
    } \
    result; \
  })

  /**
   * @brief Gets the minimum of two integers.
   * @param v1 (integer expression) The first value.
   * @param v2 (integer expression) The second value.
   * @returns The minimum of a and b.
   * @note - The behavior of this macro is defined regardles of the
   *         signedness of the given arguments.
   */
  #define min(v1, v2) ({ \
    __auto_type const v1_ = (v1); \
    __auto_type const v2_ = (v2); \
    (cmp(v1_, v2_) < 0) ? v1_ : v2_; \
  })

  /**
   * @brief Gets the maximum of two integers.
   * @param v1 (integer expression) The first value.
   * @param v2 (integer expression) The second value.
   * @returns The maximum of a and b.
   * @note - The behavior of this macro is defined regardles of the
   *         signedness of the given arguments.
   */
  #define max(v1, v2) ({ \
    __auto_type const v1_ = (v1); \
    __auto_type const v2_ = (v2); \
    (cmp(v1_, v2_) < 0) ? v2_ : v1_; \
  })

  /**
   * @brief Clamps an integer to a given range.
   * @param v (integer expression) The value to clamp.
   * @param min (integer expression) The minimum value of the range.
   * @param max (integer expression) The maximum value of the range.
   * @returns The given value clamped to the specified range.
   * @note - The behavior of this macro is undefined if the minimum
   *         value of the range is greater than the maximum value of
   *         the range.
   * @note - The behavior of this macro is defined regardles of the
   *         signedness of the given arguments.
   */
  #define clamp(v, min, max) ({ \
    __auto_type const v_ = (v); \
    __auto_type const min_ = (min_); \
    __auto_type const max_ = (max_); \
    typeof(v) result = v_; \
    if (cmp(min_, max_) <= 0) { \
      if (cmp(v_, min_) < 0) { result = typeof(v)min_; } \
      if (cmp(v_, max_) > 0) { result = typeof(v)max_; } \
    } \
    result; \
  })

  /**
   * @brief Gets the absolute value of an integer.
   * @param value (integer expression) The target value.
   * @returns The absolute value of the target value.
   * @note - If the given value is signed and equal to the minimum representable 
   *         value of it's type, the result of this macro will be the maximum 
   *         representable value of the same type.
   */
  #define abs(v) ({ \
    __auto_type const v_ = (v); \
    typeof(v) result = v_; \
    if (v_ < 0) { \
      const uintmax_t uv_ = (uintmax_t)v_; \
      if ((uv_ << 1) == 0U) { \
        result = typeof(v)(uv_ >> 1); \
      } else { \
        result = -v_; \
      } \
    } \
    result; \
  })

  /**
   * @brief Rounds a value down to the nearest multiple of a given number.
   * @param v (integer expression) The value to round.
   * @param m (integer expression) The multiple to round to.
   * @returns The given value rounded down to the nearest multiple of "m".
   * @note - The behavior of this macro is undefined if the nearest multiple
   *         of "m" less than the given value is outside the representable
   *         range of its type.
   * @note - The behavior of this macro is undefined if the given multiple - "m"
   *         is outside the representable range of the given value's type.
   * @note - If "m" is equal to zero, this macro evaluates to zero.
   */
  #define floor(v, m) ({ \
    __auto_type const v_ = (v); \
    __typeof(v) const m_ = (m); \
    (m_ == 0) ? 0 : (v_ - (v_ % m_)); \
  })

  /**
   * @brief Rounds a value up to the nearest multiple of a given number.
   * @param v (integer expression) The value to round.
   * @param m (integer expression) The multiple to round to.
   * @returns The given value rounded up to the nearest multiple of "m".
   * @note - The behavior of this macro is undefined if the nearest multiple
   *         of "m" greater than the given value is outside the representable 
   *         range of its type.
   * @note - The behavior of this macro is undefined if the given multiple - "m" 
   *         is outside the reprsentable range of the given value's type.
   * @note - If "m" is equal to zero, this macro evaluates to zero.
   */
  #define ceil(v, m) ({ \
    __auto_type const v_ = (v); \
    typeof(v) const m_ = (m); \
    (m_ == 0) ? 0 : (v_ + (m_ - (v_ % m_))); \
  })

  /**
   * @brief Ceiling division operation.
   * @param n (integer expression) The numerator.
   * @param d (integer expression) The denominator.
   * @returns The quotient of "n" and "d" rounded up to the nearest integer.
   * @note - The behavior of this macro is undefined if "d" is equal to zero.
   */
  #define div_ceil(n, d) ({ \
    __auto_type const n_ = (n); \
    __auto_type const d_ = (d); \
    n_ / d_ + (n_ % d_ != 0 && (n_ ^ d_) > 0); \
  })

  /**********************************************************************************************
   * @section Bit Utilities
   **********************************************************************************************/

  /**
   * @defgroup clz
   * @brief Determines the number of leading zeros in a value.
   * @param v (unsigned integer with size denoted by suffix) The value to query.
   * @returns The number of contiguous leading (msb) zeros in the given value.
   * @{
   */
  inline int32_t clz8(uint8_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint8_t mask = UINT8_C(1) << ((bit_size - 1) - i);
      if ((v & mask) == 1U) { break; }
      result++;
    }
    return result;
  }
  inline int32_t clz16(uint16_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint16_t mask = UINT16_C(1) << ((bit_size - 1) - i);
      if ((v & mask) == 1U) { break; }
      result++;
    }
    return result;
  }
  inline int32_t clz32(uint32_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint32_t mask = UINT32_C(1) << ((bit_size - 1) - i);
      if ((v & mask) == 1U) { break; }
      result++;
    }
    return result;
  }
  inline int32_t clz64(uint64_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint64_t mask = UINT64_C(1) << ((bit_size - 1) - i);
      if ((v & mask) == 1U) { break; }
      result++;
    }
    return result;
  }
  /** @} */

  /**
   * @defgroup ctz
   * @brief Determines the number of trailing zeros in a value.
   * @param v (unsigned integer with size denoted by suffix) The value to query.
   * @returns The number of contiguous trailing (lsb) zeros in the given value.
   * @{
   */
  inline int32_t ctz8(uint8_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint8_t mask = UINT8_C(1) << i;
      if ((v & mask) == 1U) { break; }
      result++;
    }
    return result;
  }
  inline int32_t ctz16(uint16_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint16_t mask = UINT16_C(1) << i;
      if ((v & mask) == 1U) { break; }
      result++;
    }
    return result;
  }
  inline int32_t ctz32(uint32_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint32_t mask = UINT32_C(1) << i;
      if ((v & mask) == 1U) { break; }
      result++;
    }
    return result;
  }
  inline int32_t ctz64(uint64_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint64_t mask = UINT64_C(1) << i;
      if ((v & mask) == 1U) { break; }
      result++;
    }
    return result;
  }
  /** @} */

  /**
   * @defgroup popcnt
   * @brief Determines the number of set bits in a value.
   * @param v (unsigned integer with size denoted by suffix) The value to query.
   * @returns The number of set bits (1s) in the given value.
   * @{
   */
  inline int32_t popcnt8(uint8_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint8_t mask = UINT8_C(1) << i;
      if ((v & mask) == 1U) { result++; }
    }
    return result;
  }
  inline int32_t popcnt16(uint16_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint16_t mask = UINT16_C(1) << i;
      if ((v & mask) == 1U) { result++; }
    }
    return result;
  }
  inline int32_t popcnt32(uint32_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint32_t mask = UINT32_C(1) << i;
      if ((v & mask) == 1U) { result++; }
    }
    return result;
  }
  inline int32_t popcnt64(uint64_t v) {
    static const int32_t bit_size = sizeof(v) * CHAR_BIT;
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size; i++) {
      const uint64_t mask = UINT64_C(1) << i;
      if ((v & mask) == 1U) { result++; }
    }
    return result;
  }
  /** @} */

  /**********************************************************************************************
   * @section Memory Utilities
   **********************************************************************************************/

  /**
   * @brief Copies a block of memory from one location to another.
   * @param dst (void*) The destination memory location.
   * @param src (const void*) The source memory location.
   * @param size (int32_t) The size of the block to copy in bytes.
   * @note - If any of the given pointers are NULL or the given size is
   *         less than or equal to zero, this macro has no side effects.
   */
  inline void mcpy(void* dst, const void* src, int32_t size) {
    if (dst && src && size > 0) {
      for (int32_t i = size - 1; i >= 0; i--) {
        ((uint8_t*)dst)[i] = ((uint8_t*)src)[i];
      }
    }
  }

  /**
   * @brief Sets a block of memory to a given value.
   * @param dst (void*) The memory location to set.
   * @param value (uint8_t) The value to set the memory to.
   * @param size (int32_t) The size of the block to set in bytes.
   * @note - If any of the given pointers are NULL or the given size is
   *         less than or equal to zero, this macro has no side effects.
   */
  inline void mset(void* dst, uint8_t value, int32_t size) {
    if (dst && size > 0) {
      for (int32_t i = size - 1; i >= 0; i--) {
        ((uint8_t*)dst)[i] = value;
      }
    }
  }

  /**
   * @brief Compares two blocks of memory.
   * @param mem1 (const void*) The first block of memory.
   * @param mem2 (const void*) The second block of memory.
   * @param size (int32_t) The size of the blocks to compare in bytes.
   * @returns (void*) A pointer to the first location where the two blocks
   *          differ or NULL if they are identical.
   * @note - If any of the given pointers are NULL or the given size is
   *         less than or equal to zero, this macro evaluates to NULL.
   */
  inline void* mcmp(const void* mem1, const void* mem2, int32_t size) {
    if (mem1 && mem2 && size > 0) {
      for (int32_t i = 0; i < size; i++) {
        if (((uint8_t*)mem1)[i] != ((uint8_t*)mem2)[i]) {
          return ((uint8_t*)mem1)[i];
        }
      }
    }
    return NULL;
  }

  /**
   * @brief Finds the location of a block of memory within another block.
   * @param smem (const void*) The location of the block to search.
   * @param ssize (int32_t) The size of the block to search in bytes.
   * @param fmem (const void*) The location of the block to find.
   * @param fsize (int32_t) The size of the block to find in bytes.
   * @param n (int32_t) The index of the occurance of fmem to find.
   *          If n is negative, smem will be searched in reverse.
   * @returns (void*) A pointer to the first location of fmem in smem
   *          or NULL if fmem was not found.
   * @note - If any of the given pointers are NULL or the given sizes
   *         are less than or equal to zero, or n is equal to zero,
   *          this macro evaluates to NULL.
   */
  inline void* mfind(const void* smem, int32_t ssize, 
      const void* fmem, int32_t fsize, int32_t n) {
    if (smem && fmem && ssize > 0 && fsize > 0 && ssize >= fsize && n) {
      int32_t cn = 0;
      if (n > 0) {
        for (int32_t i = 0; i < (ssize - fsize); i++) {
          if (!mcmp(((uint8_t*)smem)[i], fmem, fsize)) {
            if (++cn >= n) { return ((uint8_t*)smem)[i]; }
          }
        }
      } else {
        for (int32_t i = (ssize - fsize) - 1; i >= 0; i--) {
          if (!mcmp(((uint8_t*)smem)[i], fmem, fsize)) {
            if (++cn >= -n) { return ((uint8_t*)smem)[i]; }
          }
        }
      }
    }
    return NULL;
  }

  /**********************************************************************************************
   * @section Array Utilities
   **********************************************************************************************/

  /**
   * @brief Determines the size of an array.
   * @param array (identifier) The array to query.
   * @returns (int32_t) The number of elements in the array.
   * @note - The behavior of this macro is undefined if the given
   *         identifier does not correspond to a bounded array.
   */
  #define array_size(array) ({ \
    (int32_t)(sizeof(array) / sizeof((array)[0])); \
  })

  /**
   * @brief Determines the index of a value in an array.
   * @param v (value) The value to search for.
   * @param arr (array) The array to search in.
   * @param len (int32_t) The number of elements in the array.
   * @param n (int32_t) The index of the occurance of v to find.
   *          If n is negative, the array will be searched in reverse.
   * @returns (int32_t) The index of the nth occurance of v in the
   *          given array or -1 if it was not found.
   * @note - If any of the given pointers are NULL or the given length
   *         is less than or equal to zero, or n is equal to zero,
   *         this macro evaluates to -1.
   * @note - The behavior of this macro is undefined if the given value
   *         is not implicitly convertible to the type of the array's
   *         elements.
   */
  #define index_of(v, arr, len, n) ({ \
    typeof((arr)[0]) const v_ = (v); \
    const int32_t ssize = (int32_t)(len) * (int32_t)sizeof(arr[0]); \
    void* const result = mfind((arr), ssize, &v_, sizeof(v_), n); \
    result ? (typeof(arr)result - array) : -1; \
  })

#if defined(__cplusplus)
  } /* extern "C" */
#endif