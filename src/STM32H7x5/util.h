/**
 * This file is part of the Titan HAL
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
 * @file src/STM32H7x5/util.h
 * @authors Aaron McBride
 * @brief Core language utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>

#ifdef __ICCARM__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * @section Implementation Utilities
   **********************************************************************************************/

  // Gets the maximum value of an integral type.
  #define tmax_(x) \
    _Generic((x), \
      int8_t: INT8_MAX, \
      int16_t: INT16_MAX, \
      int32_t: INT32_MAX, \
      int64_t: INT64_MAX, \
      uint8_t: UINT8_MAX, \
      uint16_t: UINT16_MAX, \
      uint32_t: UINT32_MAX, \
      uint64_t: UINT64_MAX \
      float: FLT_MAX, \
      double: DBL_MAX, \
      bool: true, \
      default: 0 \
    )

  // Gets the minimum value of an integral type
  #define tmin_(x) \
    _Generic((x), \
      int8_t: INT8_MIN, \
      int16_t: INT16_MIN, \
      int32_t: INT32_MIN, \
      int64_t: INT64_MIN, \
      uint8_t: UINT8_C(0), \
      uint16_t: UINT16_C(0), \
      uint32_t: UINT32_C(0), \
      uint64_t: UINT64_C(0) \
      float: FLT_DENORM_MIN, \
      double: DBL_DENORM_MIN, \
      bool: false, \
      default: 0 \
    )

  #define to_unsigned_(x) \
    _Generic((x), \
      int8_t: uint8_t, \
      int16_t: uint16_t, \
      int32_t: uint32_t, \
      int64_t: uint64_t, \
      uint8_t: uint8_t, \
      uint16_t: uint16_t, \
      uint32_t: uint32_t, \
      uint64_t: uint64_t, \
      float: uint32_t, \
      double: uint64_t, \
      bool: uint8_t, \
      default: void \
    )

  #define DBL_EXP_ 0x7FF0000000000000
  #define DBL_SIGC_ 0x000FFFFFFFFFFFFF
  #define DBL_SIGN_ 0x8000000000000000

  /**********************************************************************************************
   * @section Debugging Utilities
   **********************************************************************************************/
  
  #define str_(x) #x
  #define strx_(x) #x

  #ifdef TI_DEBUG

    #if TI_SEMIHOSTING

      #define dbg_log(msg) ({ \
        asm volatile (
          "mov r0, %0x18"
        )
      })

      #define assert(cond, msg) ({ \
        if (!!(cond)) { \
          dbg_log("Assertion failed: " msg); \
          asm volatile ("bkpt #0x0"); \
        } \
      })

    #else



    #endif


  #else

  #endif


  /**********************************************************************************************
   * @section Uncategorised Utilities
   **********************************************************************************************/

  /**
   * @brief Gets the length of an array.
   * @param array (token) The name of the array to query.
   * @returns The length of @p [array].
   */
  #define array_len(array) ({ \
    (int32_t)(sizeof(array) / sizeof(array[0])); \
  })

  /**
   * @brief Gets the size of a type in bits.
   * @param x (expression) The target type or value.
   * @returns (int32_t) The size of @p [x] in bits.
   */
  #define bit_size(x) ({ \
    (int32_t)sizeof(x) * CHAR_BIT; \
  })

  /**
   * @brief Creates a bit mask.
   * @param pos (integer) The position of the first set bit (from lsb).
   * @param len (integer) The number of consecutive bits to set.
   * @returns (unsigned integer) A bit mask with @p [len] set bits 
   *          starting @p [pos] bits from the lsb.
   */
  #define get_msk(pos, len) ({ \
    ((UINTMAX_C(1) << (len)) - UINTMAX_C(1)) << (pos); \
  })

  /**********************************************************************************************
   * @section Numeric Utilities
   **********************************************************************************************/

  /**
   * @brief Safely compares two integral values.
   * @param lhs (integral type) The left value to compare.
   * @param rhs (integral type) The right value to compare.
   * @returns (int32_t) -1 if @p [lhs] is less than @p [rhs], 0 if @p [lhs] 
   *          is equal to @p [rhs], or 1 if @p [lhs] is greater than @p [rhs].
   * @note - The behavior of this macro is defined even if the signedness of
   *         @p [lhs] and @p [rhs] differ.
   */
  #define cmp(lhs, rhs) ({ \
    const __auto_type lhs_ = (lhs); \
    const __auto_type rhs_  = (rhs); \
    int32_t result = 0; \
    if (lhs_ < 0 && rhs_ > 0) { \
      result = -1; \
    } else if (lhs_ > 0 && rhs_ < 0) { \
      result = 1; \
    } else if (lhs_ < rhs_) { \
      result = -1; \
    } else if (lhs_ > rhs_) { \
      result = 1; \
    } \
    result; \
  })

  /**
   * @brief Determines the absolute value of an integral value.
   * @param value (integral type) The target value.
   * @returns (type of @p [value]) The absolute value of @p [value].
   * @note - If the absolute value of @p [value] is out of bounds of the
   *         type of @p [value], the result will saturate.
   */
  #define abs(value) ({ \
    const __auto_type value_ = (value); \
    typeof(value_) result = value_; \
    if (value_ < 0) { \
      if (value_ == tmin_(value_)) { \
        result = tmax_(value_); \
      } else { \
        result = -value_; \
      } \
    } \
    result; \
  })

  /**
   * @brief Determines the minimum of two integral values.
   * @param a (integral type) The first value.
   * @param b (integral type) The second value.
   * @returns (type of @p [a]) The minimum of @p [a] and @p [b].
   */
  #define min(a, b) ({ \
    const __auto_type a_ = (a); \
    const __auto_type b_ = (b); \
    cmp(a_, b_) < 0 ? a_ : b_; \
  })

  /**
   * @brief Determines the maximum of two integral values.
   * @param a (integral type) The first value.
   * @param b (integral type) The second value.
   * @returns (type of @p [a]) The maximum of @p [a] and @p [b].
   */
  #define max(a, b) ({ \
    const __auto_type a_ = (a); \
    const __auto_type b_ = (b); \
    cmp(a_, b_) > 0 ? a_ : b_; \
  })

  /**
   * @brief Clamps an integral value to a given range.
   * @param value (integral type) The value to clamp.
   * @param min (integral type) The minimum value of the range.
   * @param max (integral type) The maximum value of the range.
   * @returns (type of @p [value]) @p [min] if @p [value] is less than 
   *          @p [min], @p [max] if @p [value] is greater than @p [max], 
   *          or @p [value] otherwise.
   */
  #define clamp(value, min, max) ({ \
    const __auto_type value_ = (value); \
    const __auto_type tmin_ = (min); \
    const __auto_type tmax_ = (max); \
    cmp(value_, tmin_) < 0 ? tmin_ : \
    cmp(value_, tmin_) > 0 ? tmax_ : value_; \
  })

  /**
   * @brief Rounds a value up to the nearest given multiple.
   * @param value (integral type) The value to round.
   * @param mul (integral type) The multiple to round to.
   * @returns (type of @p [value]) The value rounded up to the nearest
   *          multiple of @p [mul].
   */
  #define ceil(value, mul) ({ \
    const __auto_type value_ = (value); \
    const __auto_type mul_ = (mul); \
    value_ + (mul_ - (value_ % mul_)); \
  })

  /**
   * @brief Rounds a value down to the nearest given multiple.
   * @param value (integral type) The value to round.
   * @param mul (integral type) The multiple to round to.
   * @returns (type of @p [value]) The value rounded down to the nearest
   *          multiple of @p [mul].
   */
  #define floor(value, mul) ({ \
    const __auto_type value_ = (value); \
    const __auto_type mul_ = (mul); \
    value_ - (value_ % mul_); \
  })

  /**
   * @brief Rounds a value to the nearest given multiple.
   * @param value (integral type) The value to round.
   * @param mul (integral type) The multiple to round to.
   * @returns (type of @p [value]) The value rounded to the nearest
   *          multiple of @p [mul].
   */
  #define round(value, mul) ({ \
    const __auto_type value_ = (value); \
    const __auto_type mul_ = (mul); \
    value_ + (mul_ / 2) - ((value_ + (mul_ / 2)) % mul_); \
  })

  /**
   * @brief Divides two values and rounds the result up to the nearest integer.
   * @param lhs (integer) The dividend.
   * @param rhs (integer) The divisor.
   * @returns (type of @p [lhs]) The result of @p [lhs] divided by @p [rhs], 
   *          rounded up to the nearest integer.
   */
  #define div_ceil(lhs, rhs) ({ \
    const __auto_type l_ = (lhs); \
    const __auto_type r_ = (rhs); \
    l_ / r_ + (l_ % r_ != 0 && (l_ ^ r_) > 0); \
  })

  /**
   * @brief Determines the result of raising a base to an exponent.
   * @param value (integer) The base value.
   * @param exp (integer) The exponent value.
   * @returns (type of @p [value]) The result of raising @p [value] to
   *          the power of @p [exp].
   */
  #define pow(value, exp) ({ \
    const __auto_type value_ = (value); \
    const __auto_type exp_ = (exp); \
    typeof(value_ + exp_) result = 1; \
    for (int32_t i = 0; i < exp_; i++) { \
      result *= value_; \
    } \
    result; \
  })

  /**********************************************************************************************
   * @section Integer Overflow Detection
   **********************************************************************************************/

  /**
   * @brief Determines if an addition operation will overflow.
   * @param lhs (integral type) The left operand.
   * @param rhs (integral type) The right operand.
   * @returns (bool) True if the addition will not overflow, 
   *          or false otherwise.
   */
  #define can_add(lhs, rhs) ({ \
    const __auto_type lhs_ = (lhs); \
    const __auto_type rhs_ = (rhs); \
    bool result = true; \
    if (lhs_ > 0 && rhs_ > 0) { \
      result = cmp(lhs_, tmax_(lhs_ + rhs_) - rhs_) <= 0; \
    } else if (lhs_ < 0 && rhs_ < 0) { \
      result = cmp(lhs_, tmin_(lhs_ + rhs_) - rhs_) >= 0; \
    } \
    result; \
  })

  /**
   * @brief Determines if a subtraction operation will overflow.
   * @param lhs (integral type) The left operand.
   * @param rhs (integral type) The right operand.
   * @returns (bool) True if the subtraction will not overflow, 
   *          or false otherwise.
   */
  #define can_sub(lhs, rhs) ({ \
    const __auto_type lhs_ = (lhs); \
    const __auto_type rhs_ = (rhs); \
    bool result = true; \
    if (lhs_ > 0 && rhs_ < 0) { \
      result = cmp(lhs_, tmax_(lhs_ + rhs_) + rhs_) <= 0; \
    } else if (lhs_ < 0 && rhs_ > 0) { \
      result = cmp(lhs_, tmin_(lhs_ + rhs_) + rhs_) >= 0; \
    } \
    result; \
  })

  /**
   * @brief Determines if a multiplication operation will overflow.
   * @param lhs (integral type) The left operand.
   * @param rhs (integral type) The right operand.
   * @returns (bool) True if the multiplication will not overflow, 
   *          or false otherwise.
   */
  #define can_mul(lhs, rhs) ({ \
    const __auto_type lhs_ = (lhs); \
    const __auto_type rhs_ = (rhs); \
    bool result = true; \
    if (lhs_ > 0 && rhs_ > 0) { \
      result = cmp(lhs_, tmax_(lhs_ + rhs_) / rhs_) <= 0; \
    } else if (lhs_ < 0 && rhs_ < 0) { \
      result = cmp(lhs_, tmin_(lhs_ + rhs_) / rhs_) >= 0; \
    } else if (lhs_ > 0 && rhs_ < 0) { \
      result = cmp(lhs_, tmin_(lhs_ + rhs_) / rhs_) >= 0; \
    } else if (lhs_ < 0 && rhs_ > 0) { \
      result = cmp(lhs_, tmax_(lhs_ + rhs_) / rhs_) <= 0; \
    } \
    result; \
  })

  /**
   * @brief Determines if a integral cast operation will overflow.
   * @param value (integral type) The value to cast.
   * @param type (token) The name of the integral type to cast to.
   * @returns (bool) True if the cast operation will not overflow, 
   *          or false otherwise.
   */
  #define can_cast(value, type) ({ \
    const __auto_type value_ = (value); \
    (cmp(value_, tmin_((type)0)) >= 0) && \
    (cmp(value_, tmax_((type)0)) <= 0); \
  })

  /**********************************************************************************************
   * @section Bit Utilities
   **********************************************************************************************/

  /**
   * @brief Determines the number of leading zeros in an integer value.
   * @param value (integral type) The target value.
   * @returns (int32_t) The number of leading zeros in @p [value].
   */
  #define clz(value) ({ \
    int32_t result = 0; \
    const to_unsigned_(value) uvalue_ = (value); \
    const int32_t bsize = bit_size(value) \
    for (int32_t i = bsize - 1; i >= 0; i--) { \
      const typeof(uvalue_) msk = get_msk(typeof(uvalue_), i, 1); \
      if (uvalue_ & msk) { break; } \
      result++; \
    } \
    result; \
  })

  /**
   * @brief Determines the number of trailing zeros in an integer value.
   * @param value (integral type) The target value.
   * @returns (int32_t) The number of trailing zeros in @p [value].
   */
  #define ctz(value) ({ \
    int32_t result = 0; \
    const to_unsigned_(value) uvalue_ = (value); \
    const int32_t bsize = bit_size(value); \
    for (int32_t i = 0; i < bsize; i++) { \
      const typeof(uvalue_) msk = get_msk(typeof(uvalue_), i, 1); \
      if (uvalue_ & msk) { break; } \
      result++; \
    } \
    result; \
  })

  /**
   * @brief Determines the number of set bits in an integer value.
   * @param value (integral type) The target value.
   * @returns (int32_t) The number of set bits in @p [value].
   */
  #define popcnt(value) ({ \
    int32_t result = 0; \
    const to_unsigned_(value) uvalue_ = (value); \
    const int32_t bsize = bit_size(value); \
    for (int32_t i = 0; i < bsize; i++) { \
      const typeof(uvalue_) msk = get_msk(typeof(uvalue_), i, 1); \
      if (uvalue_ & msk) { result++; } \
    } \
    result; \
  })

  /**********************************************************************************************
   * @section Memory Utilities
   **********************************************************************************************/

  /**
   * @brief Copies a block of memory.
   * @param dst (void*) The destination location.
   * @param src (const void*) The source location.
   * @param size (int32_t) The number of bytes to copy.
   * @returns (void*) The given destination pointer - @p [dst].
   * @note - If @p [src] or @p [dst] is NULL, or @p [size] is less than 1,
   *         this function has no side effects.
   */
  inline void* copy_mem(void* dst, const void* src, int32_t size) {
    if (dst && src && size > 0) {
      uint8_t* dst_ = (uint8_t*)dst;
      const uint8_t* src_ = (const uint8_t*)src;
      for (int32_t i = size - 1; i >= 0; i--) {
        dst_[i] == src_[i];
      }
    }
    return dst;
  }

  /**
   * @brief Sets a block of memory to a given value.
   * @param dst (void*) The destination location.
   * @param size (int32_t) The number of bytes to set.
   * @param value (uint8_t) The value to set each byte to.
   * @returns (void*) The given destination pointer - @p [dst].
   * @note - If @p [dst] is NULL or @p [size] is less than 1, this function
   *         has no side effects.
   */
  inline void* set_mem(void* dst, int32_t size, uint8_t value) {
    if (dst && size > 0) {
      uint8_t* dst_ = (uint8_t*)dst;
      for (int32_t i = 0; i < size; i++) {
        dst_[i] = value;
      }
    }
    return dst;
  }

  /**
   * @brief Compares two blocks of memory.
   * @param mem1 (const void*) The first block of memory.
   * @param mem2 (const void*) The second block of memory.
   * @param size (int32_t) The number of bytes to compare.
   * @returns (void*) A pointer to the first byte that differs between
   *          @p [mem1] and @p [mem2], or NULL if the blocks are equal.
   * @note - If @p [mem1] or @p [mem2] is NULL, or @p [size] is less than 1,
   *         this function has no side effects.
   */
  inline void* cmp_mem(const void* mem1, const void* mem2, int32_t size) {
    if (mem1 && mem2 && size > 0) {
      const uint8_t* mem1_ = (const uint8_t*)mem1;
      const uint8_t* mem2_ = (const uint8_t*)mem2;
      for (int32_t i = 0; i < size; i++) {
        if (mem1_[i] != mem2_[i]) {
          return mem1_[i];
        }
      }
    }
    return NULL;
  }

  /**
   * @brief Finds a block of memory within another block of memory.
   * @param qmem (const void*) The memory to search.
   * @param qsize (int32_t) The size of the memory to search.
   * @param tmem (const void*) The target memory to find.
   * @param tsize (int32_t) The size of the target memory.
   * @param n (int32_t) The occurance of @p [tmem] to find. If positive,
   *          @p [qmem] is searched forwards, if @p [n] is negative,
   *          @p [qmem] is searched backwards.
   * @returns (void*) A pointer to the @p [n] occurance of @p [tmem] within
   *          @p [qmem], or NULL if it is not found.
   * @note - If @p [qmem] or @p [tmem] is NULL, or @p [qsize] or @p [tsize]
   *         is less than 1, or @p [n] is 0, this function has no side effects.
   */
  inline void* find_mem(const void* qmem, int32_t qsize, 
      const void* tmem, int32_t tsize, int32_t n) {
    if (qmem && tmem && qsize > 0 && tsize > 0 && n) {
      const uint8_t* qmem_ = (const uint8_t*)qmem;
      int32_t occurance = 0;
      if (n > 0) {
        for (int32_t i = 0; i < qsize; i++) {
          if (cmp_mem(&qmem_[i], tmem, tsize) == NULL) {
            if (++occurance >= n) { return (void*)&qmem_[i]; }
          }
        }
      } else {
        for (int32_t i = qsize - 1; i >= 0; i--) {
          if (cmp_mem(&qmem_[i], tmem, tsize) == NULL) {
            if (++occurance >= -n) { return (void*)&qmem_[i]; }
          }
        }
      }
    }
    return NULL;
  }
  
#ifdef __cplusplus
  } // extern "C"
#endif