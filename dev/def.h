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
 * @file include/tal/def.h
 * @authors Aaron McBride
 * @brief Core language type, value and keyword definitions.
 */

#if !defined(INCLUDE_TAL_DEF_H)
#define INCLUDE_TAL_DEF_H

#include "src/tool/macro_util.h"

#if defined(__cplusplus)
  extern "C" {
#endif 
  
  /************************************************************************************************
   * @section Standard Bool Type and Values
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to the "bool" type.
   * @note - This macro is supported by all compliant targets.
   * @see true
   * @see false
   */
  #define bool

  /** 
   * @brief Macro which expands to the "true" value of the "bool" type.
   * @note - This macro is supported by all compliant targets.
   * @see bool
   */
  #define true

  /** 
   * @brief Macro which expands to the "false" value of the "bool" type.
   * @note - This macro is supported by all compliant targets.
   * @see bool
   */
  #define false

  /************************************************************************************************
   * @section Standard Null Value
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to the "null" value of the "void pointer" type.
   * @note - This value is supported by all compliant targets.
   */
  #define NULL

  /************************************************************************************************
   * @section Alignment Keywords
   ************************************************************************************************/

  /**
   * @brief Macro which sets the alignment of a variable, member or type.
   * @param x (integer expression or literal) The alignment.
   * @note - The behavior of this macro is undefined if @p [x] is not a power of 2,
   *         or if @p [x] is less than or equal to zero.
   * @note - @p [x] is expanded an unspecified number of times.
   * @note - This macro is supported by all compliant targets.
   */
  #define alignas(x)

  /**
   * @brief Macro which determines the alignment of a variable, member or type.
   * @param x (token) The variable, member or type to inspect.
   * @note - @p [x] is expanded an unspecified number of times.
   * @note - This macro is supported by all compliant targets.
   */
  #define alignof(x)

  /************************************************************************************************
   * @section Uncategorized Keywords
   ************************************************************************************************/

  #define complex

  #define imaginary

  #define atomic

  /************************************************************************************************
   * @section Bit-Width Integer Types
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to a signed integer type with a width of 8 bits.
   * @note - This macro is supported by all compliant targets.
   */
  #define int8_t

  /** 
   * @brief Macro which expands to a signed integer type with a width of 16 bits.
   * @note - This macro is supported by all compliant targets.
   */
  #define int16_t

  /** 
   * @brief Macro which expands to a signed integer type with a width of 32 bits.
   * @note - This macro is supported by all compliant targets.
   */
  #define int32_t

  /** 
   * @brief Macro which expands to a signed integer type with a width of 64 bits.
   * @note - This macro is supported by all compliant targets.
   */
  #define int64_t

  /** 
   * @brief Macro which expands to a signed integer type with a width of 128 bits.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   */
  #define int128_t

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 8 bits.
   * @note - This macro is supported by all compliant targets.
   */
  #define uint8_t

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 16 bits.
   * @note - This macro is supported by all compliant targets.
   */
  #define uint16_t

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 32 bits.
   * @note - This macro is supported by all compliant targets.
   */
  #define uint32_t

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 64 bits.
   * @note - This macro is supported by all compliant targets.
   */
  #define uint64_t

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 128 bits.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   */
  #define uint128_t

  /************************************************************************************************
   * @section Bit-Width Floating Point Types
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to a floating point type with a width of 16 bits.
   * @note - This type is known as "half precision" in the IEEE 754 standard.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   */
  #define float16_t

  /** 
   * @brief Macro which expands to a floating point type with a width of 32 bits.
   * @note - This type is known as "single precision" in the IEEE 754 standard.
   * @note - This macro is supported by all compliant targets.
   */
  #define float32_t

  /** 
   * @brief Macro which expands to a floating point type with a width of 64 bits.
   * @note - This type is known as "double precision" in the IEEE 754 standard.
   * @note - This macro is supported by all compliant targets.
   */
  #define float64_t

  /** 
   * @brief Macro which expands to a floating point type with a width of 80 bits.
   * @note - This type is known as "extended precision" in the IEEE 754 standard.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   */
  #define float80_t

  /** 
   * @brief Macro which expands to a floating point type with a width of 128 bits.
   * @note - This type is known as "quad precision" in the IEEE 754 standard.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   */
  #define float128_t

  /************************************************************************************************
   * @section Special Integer Types
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to the signed integer type with the smallest width.
   * @note - This macro is supported by all compliant targets.
   */
  #define intmin_t

  /** 
   * @brief Macro which expands to the unsigned integer type with the smallest width.
   * @note - This macro is supported by all compliant targets.
   */
  #define uintmin_t

  /** 
   * @brief Macro which expands to the signed integer type with the largest width.
   * @note - This macro is supported by all compliant targets.
   */
  #define intmax_t

  /** 
   * @brief Macro which expands to the unsigned integer type with the largest width.
   * @note - This macro is supported by all compliant targets.
   */
  #define uintmax_t

  /** 
   * @brief Macro which expands to a signed integer type with the same size as a pointer.
   * @note - This macro is supported by all compliant targets.
   */
  #define intptr_t

  /** 
   * @brief Macro which expands to an unsigned integer type with the same size as a pointer.
   * @note - This macro is supported by all compliant targets.
   */
  #define uintptr_t

  /** 
   * @brief Macro which expands to the type returned by the "sizeof" operator.
   * @note - This macro is supported by all compliant targets.
   */
  #define size_t

  /** 
   * @brief Macro which expands to a signed integer type with the same size as "size_t".
   * @note - This macro is supported by all compliant targets.
   */
  #define ssize_t

  /** 
   * @brief Macro which expands to the type that results from the subtraction of two pointers.
   * @note - This macro is supported by all compliant targets.
   */
  #define ptrdiff_t

  /************************************************************************************************
   * @section Special Floating Point Types
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to the floating point type with the smallest width.
   * @note - This macro is supported by all compliant targets.
   */
  #define floatmin_t

  /** 
   * @brief Macro which expands to the floating point type with the largest width.
   * @note - This macro is supported by all compliant targets.
   */
  #define floatmax_t

  /************************************************************************************************
   * @section Abbreviated Bit-Width Integer Types
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to a signed integer type with a width of 8 bits.
   * @note - This macro is supported by all compliant targets.
   * @see int8_t
   */
  #define i8

  /** 
   * @brief Macro which expands to a signed integer type with a width of 16 bits.
   * @note - This macro is supported by all compliant targets.
   * @see int16_t
   */
  #define i16

  /** 
   * @brief Macro which expands to a signed integer type with a width of 32 bits.
   * @note - This macro is supported by all compliant targets.
   * @see int32_t
   */
  #define i32

  /** 
   * @brief Macro which expands to a signed integer type with a width of 64 bits.
   * @note - This macro is supported by all compliant targets.
   * @see int64_t
   */
  #define i64

  /** 
   * @brief Macro which expands to a signed integer type with a width of 128 bits.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see int128_t
   */
  #define i128

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 8 bits.
   * @note - This macro is supported by all compliant targets.
   * @see uint8_t
   */
  #define u8

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 16 bits.
   * @note - This macro is supported by all compliant targets.
   * @see uint16_t
   */
  #define u16

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 32 bits.
   * @note - This macro is supported by all compliant targets.
   * @see uint32_t
   */
  #define u32

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 64 bits.
   * @note - This macro is supported by all compliant targets.
   * @see uint64_t
   */
  #define u64

  /** 
   * @brief Macro which expands to an unsigned integer type with a width of 128 bits.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see uint128_t
   */
  #define u128

  /************************************************************************************************
   * @section Abbreviated Bit-Width Floating Point Types
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to a floating point type with a width of 16 bits.
   * @note - This type is known as "half precision" in the IEEE 754 standard.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define f16

  /** 
   * @brief Macro which expands to a floating point type with a width of 32 bits.
   * @note - This type is known as "single precision" in the IEEE 754 standard.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define f32

  /** 
   * @brief Macro which expands to a floating point type with a width of 64 bits.
   * @note - This type is known as "double precision" in the IEEE 754 standard.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define f64

  /** 
   * @brief Macro which expands to a floating point type with a width of 80 bits.
   * @note - This type is known as "extended precision" in the IEEE 754 standard.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define f80

  /** 
   * @brief Macro which expands to a floating point type with a width of 128 bits.
   * @note - This type is known as "quad precision" in the IEEE 754 standard.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define f128

  /************************************************************************************************
   * @section Abbreviated Special Integer Types
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to the signed integer type with the smallest width. 
   * @note - This macro is supported by all compliant targets.
   * @see intmin_t
   */
  #define imin

  /** 
   * @brief Macro which expands to the unsigned integer type with the smallest width.
   * @note - This macro is supported by all compliant targets.
   * @see uintmin_t
   */
  #define umin

  /** 
   * @brief Macro which expands to the signed integer type with the largest width.
   * @note - This macro is supported by all compliant targets.
   * @see intmax_t
   */
  #define imax

  /** 
   * @brief Macro which expands to the unsigned integer type with the largest width.
   * @note - This macro is supported by all compliant targets.
   * @see uintmax_t
   */
  #define umax

  /** 
   * @brief Macro which expands to a signed integer type with the same size as a pointer.
   * @note - This macro is supported by all compliant targets.
   * @see intptr_t
   */
  #define iptr

  /** 
   * @brief Macro which expands to an unsigned integer type with the same size as a pointer.
   * @note - This macro is supported by all compliant targets.
   * @see uintptr_t
   */
  #define uptr

  /************************************************************************************************
   * @section Abbreviated Special Floating Point Types
   ************************************************************************************************/

  /** 
   * @brief Macro which expands to the floating point type with the smallest width.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define fmin

  /** 
   * @brief Macro which expands to the floating point type with the largest width.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define fmax

  /************************************************************************************************
   * @section Standard Integer Literal Suffixes
   ************************************************************************************************/
  
  /**
   * @brief Macro which formats an integer literal to be of the "signed char" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SCHAR_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "short" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SHRT_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "int" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define INT_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "long" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LONG_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "long long" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LLONG_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "unsigned char" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UCHAR_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "unsigned short" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define USHRT_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "unsigned int" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UINT_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "unsigned long" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULONG_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "unsigned long long" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULLONG_C(x)

  /************************************************************************************************
   * @section Standard Floating Constant Suffixes
   ************************************************************************************************/

  /**
   * @brief Macro which formats a floating constant to be of the "float" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_C(x)

  /**
   * @brief Macro which formats a floating constant to be of the "double" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_C(x)

  /**
   * @brief Macro which formats a floating constant to be of the "long double" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_C(x)

  /************************************************************************************************
   * @section Bit-Width Integer Literal Suffixes
   ************************************************************************************************/

  /**
   * @brief Macro which formats an integer literal to be of the "int8_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see int8_t
   */
  #define INT8_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "int16_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see int16_t
   */
  #define INT16_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "int32_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see int32_t
   */
  #define INT32_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "int64_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see int64_t
   */
  #define INT64_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "int128_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - The macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see int128_t
   */
  #define INT128_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "uint8_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see uint8_t
   */
  #define UINT8_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "uint16_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see uint16_t
   */
  #define UINT16_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "uint32_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see uint32_t
   */
  #define UINT32_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "uint64_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see uint64_t
   */
  #define UINT64_C(x)

  /**
   * @brief Macro which formats an integer literal to be of the "uint128_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see uint128_t
   */
  #define UINT128_C(x)

  /************************************************************************************************
   * @section Bit-Width Floating Constant Suffixes
   ************************************************************************************************/

  /**
   * @brief Macro which formats a floating constant to be of the "float16_t" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLOAT16_C(x)

  /**
   * @brief Macro which formats a floating constant to be of the "float32_t" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLOAT32_C(x)

  /**
   * @brief Macro which formats a floating constant to be of the "float64_t" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLOAT64_C(x)

  /**
   * @brief Macro which formats a floating constant to be of the "float80_t" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLOAT80_C(x)

  /**
   * @brief Macro which formats a floating constant to be of the "float128_t" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro may not be supported by some compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLOAT128_C(x)

  /************************************************************************************************
   * @section Special Integer Literal Suffixes
   ************************************************************************************************/

  /** 
   * @brief Macro which formats an integer literal to be of the "intmin_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see intmin_t
   */
  #define INTMIN_C(x)

  /** 
   * @brief Macro which formats an integer literal to be of the "uintmin_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmin_t
   */
  #define UINTMIN_C(x)

  /** 
   * @brief Macro which formats an integer literal to be of the "intmax_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see intmax_t
   */
  #define INTMAX_C(x)

  /** 
   * @brief Macro which formats an integer literal to be of the "uintmax_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmax_t
   */
  #define UINTMAX_C(x)

  /** 
   * @brief Macro which formats an integer literal to be of the "intptr_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see intptr_t
   */
  #define INTPTR_C(x)

  /** 
   * @brief Macro which formats an integer literal to be of the "uintptr_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see uintptr_t
   */
  #define UINTPTR_C(x)

  /** 
   * @brief Macro which formats an integer literal to be of the "size_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see size_t
   */
  #define SIZE_C(x)

  /** 
   * @brief Macro which formats an integer literal to be of the "ssize_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see ssize_t
   */
  #define SSIZE_C(x)

  /** 
   * @brief Macro which formats an integer literal to be of the "ptrdiff_t" type.
   * @param x (integer literal) The integer literal to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given integer literal
   *         will be formated to be of the smallest representable integer type
   *         with a width greater than or equal to that of the target type and
   *         the same signedness as the target type.
   * @note - This macro is supported by all compliant targets.
   * @see ptrdiff_t
   */
  #define PTRDIFF_C(x)

  /************************************************************************************************
   * @section Special Floating Constant Suffixes
   ************************************************************************************************/

  /** 
   * @brief Macro which formats a floating constant to be of the "floatmax_t" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLOATMIN_C(x)

  /** 
   * @brief Macro which formats a floating constant to be of the "floatmax_t" type.
   * @param x (floating constant) The floating constant to format.
   * @note - The behavior of this macro is undefined if @p [x] has a suffix.
   * @note - If no format exists for the target type, the given floating constant
   *         will be formated to be of the smallest representable floating point 
   *         type with a width greater than or equal to that of the target type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLOATMAX_C(x)

#if defined(__cplusplus)
  } /* extern "C" */
#endif

/* Target port implementation */
#include _TAL_STR_X(_TAL_JOIN(src/port/, TAL_TARGET_TOK, /def.inc))

#endif /* INCLUDE_TAL_DEF_H */