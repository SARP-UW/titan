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
 * @file include/tal/limits.h
 * @authors Aaron McBride
 * @brief Numeric implementation limits.
 */

#if !defined(INCLUDE_TAL_LIMITS_H)
#define INCLUDE_TAL_LIMITS_H

#include "src/tool/macro_util.h"
#include "include/tal/def.h"

// Target implementation
#include _TAL_STR_X(_TAL_JOIN(src/port/, TAL_TARGET_TOK, /limits.inc))

#if defined(__cplusplus)
  extern "C" {
#endif 
  
  /************************************************************************************************
   * @section Standard Integer Size
   ************************************************************************************************/

  /**
   * @brief The size of the "signed char" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SCHAR_SIZE

  /**
   * @brief The size of the "signed short" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SHRT_SIZE

  /**
   * @brief The size of the "signed int" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define INT_SIZE

  /**
   * @brief The size of the "signed long" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LONG_SIZE

  /**
   * @brief The size of the "signed long long" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LLONG_SIZE

  /**
   * @brief The size of the "unsigned char" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UCHAR_SIZE

  /**
   * @brief The size of the "unsigned short" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define USHRT_SIZE

  /**
   * @brief The size of the "unsigned int" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UINT_SIZE

  /**
   * @brief The size of the "unsigned long" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULONG_SIZE

  /**
   * @brief The size of the "unsigned long long" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULLONG_SIZE

  /************************************************************************************************
   * @section Standard Floating Point Size
   ************************************************************************************************/

  /**
   * @brief The size of the "float" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_SIZE

  /**
   * @brief The size of the "double" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_SIZE

  /**
   * @brief The size of the "long double" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_SIZE

  /************************************************************************************************
   * @section Bit-Width Integer Size
   ************************************************************************************************/

  /**
   * @brief The size the "int8_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int8_t
   */
  #define INT8_SIZE

  /**
   * @brief The size of the "int16_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int16_t
   */
  #define INT16_SIZE

  /**
   * @brief The size of the "int32_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int32_t
   */
  #define INT32_SIZE

  /**
   * @brief The size of the "int64_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int64_t
   */
  #define INT64_SIZE

  /**
   * @brief The size of the "int128_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see int128_t
   */
  #define INT128_SIZE

  /**
   * @brief The size of the "uint8_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint8_t
   */
  #define UINT8_SIZE

  /**
   * @brief The size of the "uint16_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint16_t
   */
  #define UINT16_SIZE

  /**
   * @brief The size of the "uint32_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint32_t
   */
  #define UINT32_SIZE

  /**
   * @brief The size of the "uint64_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint64_t
   */
  #define UINT64_SIZE

  /**
   * @brief The size of the "uint128_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see uint128_t
   */
  #define UINT128_SIZE

  /************************************************************************************************
   * @section Bit-Width Floating Point Size
   ************************************************************************************************/

  /**
   * @brief The size of the "float16_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_SIZE

  /**
   * @brief The size of the "float32_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_SIZE

  /**
   * @brief The size of the "float64_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_SIZE

  /**
   * @brief The size of the "float80_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_SIZE

  /**
   * @brief The size of the "float128_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_SIZE

  /************************************************************************************************
   * @section Special Integer Size
   ************************************************************************************************/

  /**
   * @brief The size of the "intmin_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmin_t
   */
  #define INTMIN_SIZE

  /**
   * @brief The size of the "uintmin_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmin_t
   */
  #define UINTMIN_SIZE

  /**
   * @brief The size of the "intmax_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmax_t
   */
  #define INTMAX_SIZE

  /**
   * @brief The size of the "uintmax_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmax_t
   */
  #define UINTMAX_SIZE

  /**
   * @brief The size of the "intptr_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intptr_t
   */
  #define INTPTR_SIZE

  /**
   * @brief The size of the "uintptr_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintptr_t
   */
  #define UINTPTR_SIZE

  /**
   * @brief The size of the "size_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see size_t
   */
  #define SIZE_SIZE

  /**
   * @brief The size of the "ssize_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see ssize_t
   */
  #define SSIZE_SIZE

  /**
   * @brief The size of the "ptrdiff_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see ptrdiff_t
   */
  #define PTRDIFF_SIZE

  /************************************************************************************************
   * @section Special Floating Point Size
   ************************************************************************************************/

  /**
   * @brief The size of the "floatmin_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_SIZE

  /**
   * @brief The size of the "floatmax_t" type (as given by sizeof).
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_SIZE

  /************************************************************************************************
   * @section Standard Integer Width
   ************************************************************************************************/

  /**
   * @brief The size of the "signed char" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SCHAR_WIDTH

  /**
   * @brief The size of the "signed short" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SHRT_WIDTH

  /**
   * @brief The size of the "signed int" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define INT_WIDTH

  /**
   * @brief The size of the "signed long" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LONG_WIDTH

  /**
   * @brief The size of the "signed long long" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LLONG_WIDTH

  /**
   * @brief The size of the "unsigned char" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UCHAR_WIDTH

  /**
   * @brief The size of the "unsigned short" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define USHRT_WIDTH

  /**
   * @brief The size of the "unsigned int" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UINT_WIDTH

  /**
   * @brief The size of the "unsigned long" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULONG_WIDTH

  /**
   * @brief The size of the "unsigned long long" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULLONG_WIDTH

  /************************************************************************************************
   * @section Standard Floating Point Width
   ************************************************************************************************/

  /**
   * @brief The size of the "float" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_WIDTH

  /**
   * @brief The size of the "double" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_WIDTH

  /**
   * @brief The size of the "long double" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_WIDTH

  /************************************************************************************************
   * @section Bit-Width Integer Width
   ************************************************************************************************/

  /**
   * @brief The size of the "int8_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int8_t
   */
  #define INT8_WIDTH

  /**
   * @brief The size of the "int16_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int16_t
   */
  #define INT16_WIDTH

  /**
   * @brief The size of the "int32_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int32_t
   */
  #define INT32_WIDTH

  /**
   * @brief The size of the "int64_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int64_t
   */
  #define INT64_WIDTH

  /**
   * @brief The size of the "int128_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see int128_t
   */
  #define INT128_WIDTH

  /**
   * @brief The size of the "uint8_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint8_t
   */
  #define UINT8_WIDTH

  /**
   * @brief The size of the "uint16_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint16_t
   */
  #define UINT16_WIDTH

  /**
   * @brief The size of the "uint32_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint32_t
   */
  #define UINT32_WIDTH

  /**
   * @brief The size of the "uint64_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint64_t
   */
  #define UINT64_WIDTH

  /**
   * @brief The size of the "uint128_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see uint128_t
   */
  #define UINT128_WIDTH

  /************************************************************************************************
   * @section Bit-Width Floating Point Width
   ************************************************************************************************/

  /**
   * @brief The size of the "float16_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_WIDTH

  /**
   * @brief The size of the "float32_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_WIDTH

  /**
   * @brief The size of the "float64_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_WIDTH

  /**
   * @brief The size of the "float80_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_WIDTH

  /**
   * @brief The size of the "float128_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_WIDTH

  /************************************************************************************************
   * @section Special Integer Width
   ************************************************************************************************/

  /**
   * @brief The size of the "intmin_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmin_t
   */
  #define INTMIN_WIDTH

  /**
   * @brief The size of the "uintmin_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmin_t
   */
  #define UINTMIN_WIDTH

  /**
   * @brief The size of the "intmax_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmax_t
   */
  #define INTMAX_WIDTH

  /**
   * @brief The size of the "uintmax_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmax_t
   */
  #define UINTMAX_WIDTH

  /**
   * @brief The size of the "intptr_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intptr_t
   */
  #define INTPTR_WIDTH

  /**
   * @brief The size of the "uintptr_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintptr_t
   */
  #define UINTPTR_WIDTH

  /**
   * @brief The size of the "size_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see size_t
   */
  #define SIZE_WIDTH

  /**
   * @brief The size of the "ssize_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see ssize_t
   */
  #define SSIZE_WIDTH

  /**
   * @brief The size of the "ptrdiff_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see ptrdiff_t
   */
  #define PTRDIFF_WIDTH

  /************************************************************************************************
   * @section Special Floating Point Width
   ************************************************************************************************/

  /**
   * @brief The size of the "floatmin_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_WIDTH

  /**
   * @brief The size of the "floatmax_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_WIDTH

  /************************************************************************************************
   * @section Standard Integer Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum representable value of the "signed char" type.
   * @note - This macro expands to a value of the "signed char" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SCHAR_MIN

  /**
   * @brief The minimum representable value of the "signed short" type.
   * @note - This macro expands to a value of the "signed short" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SHRT_MIN

  /**
   * @brief The minimum representable value of the "signed int" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define INT_MIN

  /**
   * @brief The minimum representable value of the "signed long" type.
   * @note - This macro expands to a value of the "signed long" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LONG_MIN

  /**
   * @brief The minimum representable value of the "signed long long" type.
   * @note - This macro expands to a value of the "signed long long" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LLONG_MIN

  /**
   * @brief The minimum representable value of the "unsigned char" type.
   * @note - This macro expands to a value of the "unsigned char" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UCHAR_MIN

  /**
   * @brief The minimum representable value of the "unsigned short" type.
   * @note - This macro expands to a value of the "unsigned short" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define USHRT_MIN

  /**
   * @brief The minimum representable value of the "unsigned int" type.
   * @note - This macro expands to a value of the "unsigned int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UINT_MIN

  /**
   * @brief The minimum representable value of the "unsigned long" type.
   * @note - This macro expands to a value of the "unsigned long" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULONG_MIN

  /**
   * @brief The minimum representable value of the "unsigned long long" type.
   * @note - This macro expands to a value of the "unsigned long long" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULLONG_MIN

  /************************************************************************************************
   * @section Standard Floating Point Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum representable, finite value of the "float" type.
   * @note - This macro expands to a value of the "float" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_MIN
  
  /**
   * @brief The minimum representable, finite value of the "double" type.
   * @note - This macro expands to a value of the "double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_MIN

  /**
   * @brief The minimum representable, finite value of the "long double" type.
   * @note - This macro expands to a value of the "long double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_MIN

  /************************************************************************************************
   * @section Bit-Width Integer Minimum
   ************************************************************************************************/
  
  /**
   * @brief The minimum representable value of the "int8_t" type.
   * @note - This macro expands to a value of the "int8_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see int8_t
   */
  #define INT8_MIN

  /**
   * @brief The minimum representable value of the "int16_t" type.
   * @note - This macro expands to a value of the "int16_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see int16_t
   */
  #define INT16_MIN

  /**
   * @brief The minimum representable value of the "int32_t" type.
   * @note - This macro expands to a value of the "int32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see int32_t
   */
  #define INT32_MIN

  /**
   * @brief The minimum representable value of the "int64_t" type.
   * @note - This macro expands to a value of the "int64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see int64_t
   */
  #define INT64_MIN

  /**
   * @brief The minimum representable value of the "int128_t" type.
   * @note - This macro expands to a value of the "int128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see int128_t
   */
  #define INT128_MIN

  /**
   * @brief The minimum representable value of the "uint8_t" type.
   * @note - This macro expands to a value of the "uint8_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint8_t
   */
  #define UINT8_MIN

  /**
   * @brief The minimum representable value of the "uint16_t" type.
   * @note - This macro expands to a value of the "uint16_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint16_t
   */
  #define UINT16_MIN

  /**
   * @brief The minimum representable value of the "uint32_t" type.
   * @note - This macro expands to a value of the "uint32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint32_t
   */
  #define UINT32_MIN

  /**
   * @brief The minimum representable value of the "uint64_t" type.
   * @note - This macro expands to a value of the "uint64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint64_t
   */
  #define UINT64_MIN

  /**
   * @brief The minimum representable value of the "uint128_t" type.
   * @note - This macro expands to a value of the "uint128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see uint128_t
   */
  #define UINT128_MIN

  /************************************************************************************************
   * @section Bit-Width Floating Point Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum representable, finite value of the "float16_t" type.
   * @note - This macro expands to a value of the "float16_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_MIN
  
  /**
   * @brief The minimum representable, finite value of the "float32_t" type.
   * @note - This macro expands to a value of the "float32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_MIN

  /**
   * @brief The minimum representable, finite value of the "float64_t" type.
   * @note - This macro expands to a value of the "float64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_MIN

  /**
   * @brief The minimum representable, finite value of the "float80_t" type.
   * @note - This macro expands to a value of the "float80_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_MIN

  /**
   * @brief The minimum representable, finite value of the "float128_t" type.
   * @note - This macro expands to a value of the "float128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_MIN

  /************************************************************************************************
   * @section Special Integer Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum representable value of the "intmin_t" type.
   * @note - This macro expands to a value of the "intmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmin_t
   */
  #define INTMIN_MIN

  /**
   * @brief The minimum representable value of the "uintmin_t" type.
   * @note - This macro expands to a value of the "uintmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmin_t
   */
  #define UINTMIN_MIN

  /**
   * @brief The minimum representable value of the "intmax_t" type.
   * @note - This macro expands to a value of the "intmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmax_t
   */
  #define INTMAX_MIN

  /**
   * @brief The minimum representable value of the "uintmax_t" type.
   * @note - This macro expands to a value of the "uintmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmax_t
   */
  #define UINTMAX_MIN

  /**
   * @brief The minimum representable value of the "intptr_t" type.
   * @note - This macro expands to a value of the "intptr_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see intptr_t
   */
  #define INTPTR_MIN

  /**
   * @brief The minimum representable value of the "uintptr_t" type.
   * @note - This macro expands to a value of the "uintptr_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintptr_t
   */
  #define UINTPTR_MIN

  /**
   * @brief The minimum representable value of the "size_t" type.
   * @note - This macro expands to a value of the "size_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see size_t
   */
  #define SIZE_MIN

  /**
   * @brief The minimum representable value of the "ssize_t" type.
   * @note - This macro expands to a value of the "ssize_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see ssize_t
   */
  #define SSIZE_MIN

  /**
   * @brief The minimum representable value of the "ptrdiff_t" type.
   * @note - This macro expands to a value of the "ptrdiff_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see ptrdiff_t
   */
  #define PTRDIFF_MIN

  /************************************************************************************************
   * @section Special Floating Point Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum representable, finite value of the "floatmin_t" type.
   * @note - This macro expands to a value of the "floatmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_MIN

  /**
   * @brief The minimum representable, finite value of the "floatmax_t" type.
   * @note - This macro expands to a value of the "floatmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_MIN

  /************************************************************************************************
   * @section Standard Integer Maximum
   ************************************************************************************************/
  
  /**
   * @brief The maximum representable value of the "signed char" type.
   * @note - This macro expands to a value of the "signed char" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SCHAR_MAX

  /**
   * @brief The maximum representable value of the "signed short" type.
   * @note - This macro expands to a value of the "signed short" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SHRT_MAX

  /**
   * @brief The maximum representable value of the "signed int" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define INT_MAX

  /**
   * @brief The maximum representable value of the "signed long" type.
   * @note - This macro expands to a value of the "signed long" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LONG_MAX

  /**
   * @brief The maximum representable value of the "signed long long" type.
   * @note - This macro expands to a value of the "signed long long" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LLONG_MAX

  /**
   * @brief The maximum representable value of the "unsigned char" type.
   * @note - This macro expands to a value of the "unsigned char" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UCHAR_MAX

  /**
   * @brief The maximum representable value of the "unsigned short" type.
   * @note - This macro expands to a value of the "unsigned short" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define USHRT_MAX

  /**
   * @brief The maximum representable value of the "unsigned int" type.
   * @note - This macro expands to a value of the "unsigned int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UINT_MAX

  /**
   * @brief The maximum representable value of the "unsigned long" type.
   * @note - This macro expands to a value of the "unsigned long" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULONG_MAX

  /**
   * @brief The maximum representable value of the "unsigned long long" type.
   * @note - This macro expands to a value of the "unsigned long long" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULLONG_MAX

  /************************************************************************************************
   * @section Standard Floating Point Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum representable, finite value of the "float" type.
   * @note - This macro expands to a value of the "float" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_MAX

  /**
   * @brief The maximum representable, finite value of the "double" type.
   * @note - This macro expands to a value of the "double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_MAX

  /**
   * @brief The maximum representable, finite value of the "long double" type.
   * @note - This macro expands to a value of the "long double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_MAX

  /************************************************************************************************
   * @section Bit-Width Integer Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum representable value of the "int8_t" type.
   * @note - This macro expands to a value of the "int8_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see int8_t
   */
  #define INT8_MAX

  /**
   * @brief The maximum representable value of the "int16_t" type.
   * @note - This macro expands to a value of the "int16_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see int16_t
   */
  #define INT16_MAX

  /**
   * @brief The maximum representable value of the "int32_t" type.
   * @note - This macro expands to a value of the "int32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see int32_t
   */
  #define INT32_MAX

  /**
   * @brief The maximum representable value of the "int64_t" type.
   * @note - This macro expands to a value of the "int64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see int64_t
   */
  #define INT64_MAX

  /**
   * @brief The maximum representable value of the "int128_t" type.
   * @note - This macro expands to a value of the "int128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see int128_t
   */
  #define INT128_MAX

  /**
   * @brief The maximum representable value of the "uint8_t" type.
   * @note - This macro expands to a value of the "uint8_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint8_t
   */
  #define UINT8_MAX

  /**
   * @brief The maximum representable value of the "uint16_t" type.
   * @note - This macro expands to a value of the "uint16_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint16_t
   */
  #define UINT16_MAX

  /**
   * @brief The maximum representable value of the "uint32_t" type.
   * @note - This macro expands to a value of the "uint32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint32_t
   */
  #define UINT32_MAX

  /**
   * @brief The maximum representable value of the "uint64_t" type.
   * @note - This macro expands to a value of the "uint64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint64_t
   */
  #define UINT64_MAX

  /**
   * @brief The maximum representable value of the "uint128_t" type.
   * @note - This macro expands to a value of the "uint128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see uint128_t
   */
  #define UINT128_MAX

  /************************************************************************************************
   * @section Bit-Width Floating Point Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum representable, finite value of the "float16_t" type.
   * @note - This macro expands to a value of the "float16_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_MAX

  /**
   * @brief The maximum representable, finite value of the "float32_t" type.
   * @note - This macro expands to a value of the "float32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_MAX

  /**
   * @brief The maximum representable, finite value of the "float64_t" type.
   * @note - This macro expands to a value of the "float64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_MAX

  /**
   * @brief The maximum representable, finite value of the "float80_t" type.
   * @note - This macro expands to a value of the "float80_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_MAX

  /**
   * @brief The maximum representable, finite value of the "float128_t" type.
   * @note - This macro expands to a value of the "float128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_MAX

  /************************************************************************************************
   * @section Special Integer Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum representable value of the "intmin_t" type.
   * @note - This macro expands to a value of the "intmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmin_t
   */
  #define INTMIN_MAX

  /**
   * @brief The maximum representable value of the "uintmin_t" type.
   * @note - This macro expands to a value of the "uintmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmin_t
   */
  #define UINTMIN_MAX

  /**
   * @brief The maximum representable value of the "intmax_t" type.
   * @note - This macro expands to a value of the "intmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmax_t
   */
  #define INTMAX_MAX

  /**
   * @brief The maximum representable value of the "uintmax_t" type.
   * @note - This macro expands to a value of the "uintmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmax_t
   */
  #define UINTMAX_MAX

  /**
   * @brief The maximum representable value of the "intptr_t" type.
   * @note - This macro expands to a value of the "intptr_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see intptr_t
   */
  #define INTPTR_MAX

  /**
   * @brief The maximum representable value of the "uintptr_t" type.
   * @note - This macro expands to a value of the "uintptr_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintptr_t
   */
  #define UINTPTR_MAX

  /**
   * @brief The maximum representable value of the "size_t" type.
   * @note - This macro expands to a value of the "size_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see size_t
   */
  #define SIZE_MAX

  /**
   * @brief The maximum representable value of the "ssize_t" type.
   * @note - This macro expands to a value of the "ssize_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see ssize_t
   */
  #define SSIZE_MAX

  /**
   * @brief The maximum representable value of the "ptrdiff_t" type.
   * @note - This macro expands to a value of the "ptrdiff_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see ptrdiff_t
   */
  #define PTRDIFF_MAX

  /************************************************************************************************
   * @section Special Floating Point Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum representable, finite value of the "floatmin_t" type.
   * @note - This macro expands to a value of the "floatmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_MAX

  /**
   * @brief The maximum representable, finite value of the "floatmax_t" type.
   * @note - This macro expands to a value of the "floatmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_MAX

  /************************************************************************************************
   * @section Standard Integer Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "signed char" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SCHAR_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "signed short" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define SHRT_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "signed int" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define INT_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "signed long" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LONG_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "signed long long" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LLONG_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "unsigned char" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UCHAR_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "unsigned short" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define USHRT_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "unsigned int" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define UINT_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "unsigned long" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULONG_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "unsigned long long" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define ULLONG_DIG

  /************************************************************************************************
   * @section Standard Floating Point Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "float" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "long double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_DIG

  /************************************************************************************************
   * @section Bit-Width Integer Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "int8_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int8_t
   */
  #define INT8_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "int16_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int16_t
   */
  #define INT16_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "int32_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int32_t
   */
  #define INT32_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "int64_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see int64_t
   */
  #define INT64_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "int128_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see int128_t
   */
  #define INT128_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "uint8_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint8_t
   */
  #define UINT8_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "uint16_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint16_t
   */
  #define UINT16_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "uint32_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint32_t
   */
  #define UINT32_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "uint64_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uint64_t
   */
  #define UINT64_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the 
   *        "uint128_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see uint128_t
   */
  #define UINT128_DIG

  /************************************************************************************************
   * @section Bit-Width Floating Point Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "float16_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "float32_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "float64_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "float80_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "float128_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_DIG

  /************************************************************************************************
   * @section Special Integer Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "intmin_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmin_t
   */
  #define INTMIN_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "uintmin_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmin_t
   */
  #define UINTMIN_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "intmax_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intmax_t
   */
  #define INTMAX_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "uintmax_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintmax_t
   */
  #define UINTMAX_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "intptr_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see intptr_t
   */
  #define INTPTR_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "uintptr_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see uintptr_t
   */
  #define UINTPTR_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "size_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see size_t
   */
  #define SIZE_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "ssize_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see ssize_t
   */
  #define SSIZE_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        "ptrdiff_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see ptrdiff_t
   */
  #define PTRDIFF_DIG

  /************************************************************************************************
   * @section Special Floating Point Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "floatmin_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        finite value of the "floatmax_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_DIG

  /************************************************************************************************
   * @section Standard Floating Point Normalized Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum normalized value of the "float" type.
   * @note - This macro expands to a value of the "float" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_NORM_MIN

  /**
   * @brief The minimum normalized value of the "double" type.
   * @note - This macro expands to a value of the "double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_NORM_MIN

  /**
   * @brief The minimum normalized value of the "long double" type.
   * @note - This macro expands to a value of the "long double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_NORM_MIN

  /************************************************************************************************
   * @section Bit-Width Floating Point Normalized Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum normalized value of the "float16_t" type.
   * @note - This macro expands to a value of the "float16_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_NORM_MIN

  /**
   * @brief The minimum normalized value of the "float32_t" type.
   * @note - This macro expands to a value of the "float32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_NORM_MIN

  /**
   * @brief The minimum normalized value of the "float64_t" type.
   * @note - This macro expands to a value of the "float64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_NORM_MIN

  /**
   * @brief The minimum normalized value of the "float80_t" type.
   * @note - This macro expands to a value of the "float80_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_NORM_MIN

  /**
   * @brief The minimum normalized value of the "float128_t" type.
   * @note - This macro expands to a value of the "float128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_NORM_MIN

  /************************************************************************************************
   * @section Special Floating Point Normalized Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum normalized value of the "floatmin_t" type.
   * @note - This macro expands to a value of the "floatmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_NORM_MIN

  /**
   * @brief The minimum normalized value of the "floatmax_t" type.
   * @note - This macro expands to a value of the "floatmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_NORM_MIN

  /************************************************************************************************
   * @section Standard Floating Point Normalized Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum normalized value of the "float" type.
   * @note - This macro expands to a value of the "float" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_NORM_MAX

  /**
   * @brief The maximum normalized value of the "double" type.
   * @note - This macro expands to a value of the "double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_NORM_MAX

  /**
   * @brief The maximum normalized value of the "long double" type.
   * @note - This macro expands to a value of the "long double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_NORM_MAX

  /************************************************************************************************
   * @section Bit-Width Floating Point Normalized Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum normalized value of the "float16_t" type.
   * @note - This macro expands to a value of the "float16_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_NORM_MAX

  /**
   * @brief The maximum normalized value of the "float32_t" type.
   * @note - This macro expands to a value of the "float32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_NORM_MAX

  /**
   * @brief The maximum normalized value of the "float64_t" type.
   * @note - This macro expands to a value of the "float64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_NORM_MAX

  /**
   * @brief The maximum normalized value of the "float80_t" type.
   * @note - This macro expands to a value of the "float80_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_NORM_MAX

  /**
   * @brief The maximum normalized value of the "float128_t" type.
   * @note - This macro expands to a value of the "float128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_NORM_MAX

  /************************************************************************************************
   * @section Special Floating Point Normalized Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum normalized value of the "floatmin_t" type.
   * @note - This macro expands to a value of the "floatmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_NORM_MAX

  /**
   * @brief The maximum normalized value of the "floatmax_t" type.
   * @note - This macro expands to a value of the "floatmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_NORM_MAX

  /************************************************************************************************
   * @section Standard Floating Point Normalized Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "float" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_NORM_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_NORM_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "long double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_NORM_DIG

  /************************************************************************************************
   * @section Bit-Width Floating Point Normalized Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "float16_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_NORM_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "float32_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_NORM_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "float64_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_NORM_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "float80_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_NORM_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "float128_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_NORM_DIG

  /************************************************************************************************
   * @section Special Floating Point Normalized Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "floatmin_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_NORM_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by a
   *        normalized value of the "floatmax_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_NORM_DIG

  /************************************************************************************************
   * @section Standard Floating Point Significand Width
   ************************************************************************************************/

  /**
   * @brief The size of the significand field of the "float" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_SIGC_WIDTH

  /**
   * @brief The size of the significand field of the "double" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_SIGC_WIDTH

  /**
   * @brief The size of the significand field of the "long double" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_SIGC_WIDTH

  /************************************************************************************************
   * @section Bit-Width Floating Point Significand Width
   ************************************************************************************************/

  /**
   * @brief The size of the significand field of the "float16_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_SIGC_WIDTH

  /**
   * @brief The size of the significand field of the "float32_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_SIGC_WIDTH

  /**
   * @brief The size of the significand field of the "float64_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_SIGC_WIDTH

  /**
   * @brief The size of the significand field of the "float80_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_SIGC_WIDTH

  /**
   * @brief The size of the significand field of the "float128_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_SIGC_WIDTH

  /************************************************************************************************
   * @section Special Floating Point Significand Width
   ************************************************************************************************/

  /**
   * @brief The size of the significand field of the "floatmin_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_SIGC_WIDTH

  /**
   * @brief The size of the significand field of the "floatmax_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_SIGC_WIDTH

  /************************************************************************************************
   * @section Standard Floating Point Significand Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "float" type.
   * @note - This macro expands to a value of the "float" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_SIGC_MIN

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "double" type.
   * @note - This macro expands to a value of the "double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_SIGC_MIN

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "long double" type.
   * @note - This macro expands to a value of the "long double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_SIGC_MIN

  /************************************************************************************************
   * @section Bit-Width Floating Point Significand Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "float16_t" type.
   * @note - This macro expands to a value of the "float16_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_SIGC_MIN

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "float32_t" type.
   * @note - This macro expands to a value of the "float32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_SIGC_MIN

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "float64_t" type.
   * @note - This macro expands to a value of the "float64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_SIGC_MIN

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "float80_t" type.
   * @note - This macro expands to a value of the "float80_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_SIGC_MIN

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "float128_t" type.
   * @note - This macro expands to a value of the "float128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_SIGC_MIN

  /************************************************************************************************
   * @section Special Floating Point Significand Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "floatmin_t" type.
   * @note - This macro expands to a value of the "floatmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_SIGC_MIN

  /**
   * @brief The minimum value that can be represented by the significand field
   *        of the "floatmax_t" type.
   * @note - This macro expands to a value of the "floatmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_SIGC_MIN

  /************************************************************************************************
   * @section Standard Floating Point Significand Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "float" type.
   * @note - This macro expands to a value of the "float" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_SIGC_MAX

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "double" type.
   * @note - This macro expands to a value of the "double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_SIGC_MAX

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "long double" type.
   * @note - This macro expands to a value of the "long double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_SIGC_MAX

  /************************************************************************************************
   * @section Bit-Width Floating Point Significand Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "float16_t" type.
   * @note - This macro expands to a value of the "float16_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_SIGC_MAX

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "float32_t" type.
   * @note - This macro expands to a value of the "float32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_SIGC_MAX

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "float64_t" type.
   * @note - This macro expands to a value of the "float64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_SIGC_MAX

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "float80_t" type.
   * @note - This macro expands to a value of the "float80_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_SIGC_MAX

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "float128_t" type.
   * @note - This macro expands to a value of the "float128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_SIGC_MAX

  /************************************************************************************************
   * @section Special Floating Point Significand Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "floatmin_t" type.
   * @note - This macro expands to a value of the "floatmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_SIGC_MAX

  /**
   * @brief The maximum value that can be represented by the significand field
   *        of the "floatmax_t" type.
   * @note - This macro expands to a value of the "floatmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_SIGC_MAX

  /************************************************************************************************
   * @section Standard Floating Point Significand Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "float" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_SIGC_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_SIGC_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "long double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_SIGC_DIG

  /************************************************************************************************
   * @section Bit-Width Floating Point Significand Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "float16_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_SIGC_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "float32_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_SIGC_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "float64_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_SIGC_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "float80_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_SIGC_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "float128_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_SIGC_DIG

  /************************************************************************************************
   * @section Special Floating Point Significand Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "floatmin_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_SIGC_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        significand field of the "floatmax_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_SIGC_DIG

  /************************************************************************************************
   * @section Standard Floating Point Exponent Width
   ************************************************************************************************/

  /**
   * @brief The size of the exponent field of the "float" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_EXP_WIDTH

  /**
   * @brief The size of the exponent field of the "double" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_EXP_WIDTH

  /**
   * @brief The size of the exponent field of the "long double" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_EXP_WIDTH

  /************************************************************************************************
   * @section Bit-Width Floating Point Exponent Width
   ************************************************************************************************/

  /**
   * @brief The size of the exponent field of the "float16_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_EXP_WIDTH

  /**
   * @brief The size of the exponent field of the "float32_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_EXP_WIDTH

  /**
   * @brief The size of the exponent field of the "float64_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_EXP_WIDTH

  /**
   * @brief The size of the exponent field of the "float80_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_EXP_WIDTH

  /**
   * @brief The size of the exponent field of the "float128_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_EXP_WIDTH

  /************************************************************************************************
   * @section Special Floating Point Exponent Width
   ************************************************************************************************/

  /**
   * @brief The size of the exponent field of the "floatmin_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_EXP_WIDTH

  /**
   * @brief The size of the exponent field of the "floatmax_t" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_EXP_WIDTH

  /************************************************************************************************
   * @section Standard Floating Point Exponent Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "float" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_EXP_MIN

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_EXP_MIN

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "long double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_EXP_MIN

  /************************************************************************************************
   * @section Bit-Width Floating Point Exponent Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "float16_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_EXP_MIN

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "float32_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_EXP_MIN

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "float64_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_EXP_MIN

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "float80_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_EXP_MIN

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "float128_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_EXP_MIN

  /************************************************************************************************
   * @section Special Floating Point Exponent Minimum
   ************************************************************************************************/

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "floatmin_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_EXP_MIN

  /**
   * @brief The minimum value that can be represented by the exponent field of
   *        the "floatmax_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_EXP_MIN

  /************************************************************************************************
   * @section Standard Floating Point Exponent Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "float" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_EXP_MAX

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_EXP_MAX

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "long double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_EXP_MAX

  /************************************************************************************************
   * @section Bit-Width Floating Point Exponent Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "float16_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_EXP_MAX

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "float32_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_EXP_MAX

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "float64_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_EXP_MAX

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "float80_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_EXP_MAX

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "float128_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_EXP_MAX

  /************************************************************************************************
   * @section Special Floating Point Exponent Maximum
   ************************************************************************************************/

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "floatmin_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_EXP_MAX

  /**
   * @brief The maximum value that can be represented by the exponent field of
   *        the "floatmax_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_EXP_MAX

  /************************************************************************************************
   * @section Standard Floating Point Exponent Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "float" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_EXP_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_EXP_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "long double" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_EXP_DIG

  /************************************************************************************************
   * @section Bit-Width Floating Point Exponent Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "float16_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_EXP_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "float32_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_EXP_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "float64_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_EXP_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "float80_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_EXP_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "float128_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_EXP_DIG

  /************************************************************************************************
   * @section Special Floating Point Exponent Digits
   ************************************************************************************************/

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "floatmin_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_EXP_DIG

  /**
   * @brief The number of base 10 digits that can be fully represented by the
   *        exponent field of the "floatmax_t" type.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_EXP_DIG

  /************************************************************************************************
   * @section Standard Floating Point Epsilon
   ************************************************************************************************/

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "float" type.
   * @note - This macro expands to a value of the "float" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FLT_EPSILON

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "double" type.
   * @note - This macro expands to a value of the "double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define DBL_EPSILON

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "long double" type.
   * @note - This macro expands to a value of the "long double" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define LDBL_EPSILON

  /************************************************************************************************
   * @section Bit-Width Floating Point Epsilon
   ************************************************************************************************/

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "float16_t" type.
   * @note - This macro expands to a value of the "float16_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float16_t
   */
  #define FLT16_EPSILON

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "float32_t" type.
   * @note - This macro expands to a value of the "float32_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float32_t
   */
  #define FLT32_EPSILON

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "float64_t" type.
   * @note - This macro expands to a value of the "float64_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see float64_t
   */
  #define FLT64_EPSILON

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "float80_t" type.
   * @note - This macro expands to a value of the "float80_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float80_t
   */
  #define FLT80_EPSILON

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "float128_t" type.
   * @note - This macro expands to a value of the "float128_t" type.
   * @note - This macro may not be supported by compliant targets.
   * @note - If this macro is not supported, it will be undefined.
   * @see float128_t
   */
  #define FLT128_EPSILON

  /************************************************************************************************
   * @section Special Floating Point Epsilon
   ************************************************************************************************/

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "floatmin_t" type.
   * @note - This macro expands to a value of the "floatmin_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmin_t
   */
  #define FLTMIN_EPSILON

  /**
   * @brief The difference between 1 and next representable value of the 
   *        "floatmax_t" type.
   * @note - This macro expands to a value of the "floatmax_t" type.
   * @note - This macro is supported by all compliant targets.
   * @see floatmax_t
   */
  #define FLTMAX_EPSILON

  /************************************************************************************************
   * @section Uncategorised Limits
   ************************************************************************************************/

  /**
   * @brief The size of the "char" type in bits.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define CHAR_BIT

  /**
   * @brief The radix used by the representation of all floating point types.
   * @note - This macro expands to a value of the "signed int" type.
   * @note - This macro is supported by all compliant targets.
   */
  #define FP_RADIX

#if defined(__cplusplus)
  } // extern "C"
#endif

#endif // INCLUDE_TAL_LIMITS_H