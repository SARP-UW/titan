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
 * @file src/port/gcc_arm_stm32h745_cm7/def.inc
 * @authors Aaron McBride
 * @brief Implementation of core type and value definitions for the
 *        arm_gcc_stm32h745_cm7 port.
 */

#if !defined(SRC_PORT_GCC_ARM_STM32H745_CM7_DEF_INC)
#define SRC_PORT_GCC_ARM_STM32H745_CM7_DEF_INC

#if defined(__cplusplus)
  extern "C" {
#endif 
  
  /************************************************************************************************
   * @section Bit-Width Integer Types
   ************************************************************************************************/

  #undef int8_t
  #define int8_t signed char

  #undef int16_t  
  #define int16_t signed short

  #undef int32_t
  #define int32_t signed int

  #undef int64_t
  #define int64_t signed long long

  #undef int128_t

  #undef uint8_t
  #define uint8_t unsigned char

  #undef uint16_t
  #define uint16_t unsigned short

  #undef uint32_t
  #define uint32_t unsigned int

  #undef uint64_t
  #define uint64_t unsigned long long

  #undef uint128_t

  /************************************************************************************************
   * @section Bit-Width Floating Point Types
   ************************************************************************************************/

  #undef float16_t

  #undef float32_t
  #define float32_t float

  #undef float64_t
  #define float64_t double

  #undef float80_t

  #undef float128_t

  /************************************************************************************************
   * @section Special Integer Types
   ************************************************************************************************/

  #undef intmin_t
  #define intmin_t signed char

  #undef uintmin_t
  #define uintmin_t unsigned char

  #undef intmax_t
  #define intmax_t signed long long

  #undef uintmax_t
  #define uintmax_t unsigned long long

  #undef intptr_t
  #define intptr_t signed int

  #undef uintptr_t
  #define uintptr_t unsigned int

  #undef size_t
  #define size_t unsigned int

  #undef ssize_t
  #define ssize_t signed int

  #undef ptrdiff_t
  #define ptrdiff_t signed int

  /************************************************************************************************
   * @section Special Floating Point Types
   ************************************************************************************************/

  #undef floatmin_t
  #define floatmin_t float

  #undef floatmax_t
  #define floatmax_t double

  /************************************************************************************************
   * @section Abbreviated Bit-Width Integer Types
   ************************************************************************************************/

  #undef i8
  #define i8 signed char

  #undef i16
  #define i16 signed short

  #undef i32
  #define i32 signed int

  #undef i64
  #define i64 signed long long

  #undef i128

  #undef u8
  #define u8 unsigned char

  #undef u16
  #define u16 unsigned short

  #undef u32
  #define u32 unsigned int

  #undef u64
  #define u64 unsigned long long

  #undef u128

  /************************************************************************************************
   * @section Abbreviated Bit-Width Floating Point Types
   ************************************************************************************************/

  #undef f16

  #undef f32
  #define f32 float 

  #undef f64
  #define f64 double

  #undef f80

  #undef f128

  /************************************************************************************************
   * @section Abbreviated Special Integer Types
   ************************************************************************************************/

  #undef imin
  #define imin signed char

  #undef umin
  #define umin unsigned char

  #undef imax
  #define imax signed long long

  #undef umax
  #define umax unsigned long long

  #undef iptr
  #define iptr signed int

  #undef uptr
  #define uptr unsigned int

  /************************************************************************************************
   * @section Abbreviated Special Floating Point Types
   ************************************************************************************************/

  #undef fmin
  #define fmin float

  #undef fmax
  #define fmax double

  /************************************************************************************************
   * @section Standard Integer Literal Suffixes
   ************************************************************************************************/

  #undef SCHAR_C
  #define SCHAR_C(x) (x)

  #undef SHRT_C
  #define SHRT_C(x) (x)

  #undef INT_C
  #define INT_C(x) (x)

  #undef LONG_C
  #define LONG_C(x) (x##L)

  #undef LLONG_C
  #define LLONG_C(x) (x##LL)

  #undef UCHAR_C
  #define UCHAR_C(x) (x##U)

  #undef USHRT_C
  #define USHRT_C(x) (x##U)

  #undef UINT_C
  #define UINT_C(x) (x##U)

  #undef ULONG_C
  #define ULONG_C(x) (x##UL)

  #undef ULLONG_C
  #define ULLONG_C(x) (x##ULL)

  /************************************************************************************************
   * @section Standard Floating Constant Suffixes
   ************************************************************************************************/

  #undef FLT_C
  #define FLT_C(x) (x##F)

  #undef DBL_C
  #define DBL_C(x) (x)

  #undef LDBL_C
  #define LDBL_C(x) (x##L)

  /************************************************************************************************
   * @section Bit-Width Integer Literal Suffixes
   ************************************************************************************************/

  #undef INT8_C
  #define INT8_C(x) (x)

  #undef INT16_C
  #define INT16_C(x) (x)

  #undef INT32_C
  #define INT32_C(x) (x)

  #undef INT64_C
  #define INT64_C(x) (x##LL)

  #undef INT128_C

  #undef UINT8_C
  #define UINT8_C(x) (x##U)

  #undef UINT16_C
  #define UINT16_C(x) (x##U)

  #undef UINT32_C
  #define UINT32_C(x) (x##U)

  #undef UINT64_C
  #define UINT64_C(x) (x##ULL)

  #undef UINT128_C

  /************************************************************************************************
   * @section Bit-Wide Floating Constant Suffixes
   ************************************************************************************************/

  #undef FLOAT16_C

  #undef FLOAT32_C
  #define FLOAT32_C(x) (x##F)

  #undef FLOAT64_C
  #define FLOAT64_C(x) (x)

  #undef FLOAT80_C

  #undef FLOAT128_C

  /************************************************************************************************
   * @section Special Integer Literal Suffixes
   ************************************************************************************************/

  #undef INTMIN_C
  #define INTMIN_C(x) (x)

  #undef UINTMIN_C
  #define UINTMIN_C(x) (x##U)

  #undef INTMAX_C
  #define INTMAX_C(x) (x##LL)

  #undef UINTMAX_C
  #define UINTMAX_C(x) (x##ULL)

  #undef INTPTR_C
  #define INTPTR_C(x) (x)

  #undef UINTPTR_C
  #define UINTPTR_C(x) (x##U)

  #undef SIZE_C
  #define SIZE_C(x) (x##U)

  #undef SSIZE_C
  #define SSIZE_C(x) (x)

  #undef PTRDIFF_C
  #define PTRDIFF_C(x) (x)

  /************************************************************************************************
   * @section Special Floating Constant Suffixes
   ************************************************************************************************/

  #undef FLOATMIN_C
  #define FLOATMIN_C(x) (x##F)

  #undef FLOATMAX_C
  #define FLOATMAX_C(x) (x##L)

  /************************************************************************************************
   * @section Standard Bool Type and Values
   ************************************************************************************************/

  #undef bool
  #define bool _Bool

  #undef true
  #define true ((_Bool)1)

  #undef false
  #define false ((_Bool)0)

  /************************************************************************************************
   * @section Standard Null Value
   ************************************************************************************************/

  #undef NULL
  #define NULL ((void*)0)

#if defined(__cplusplus)
  } // extern "C"
#endif

#endif // SRC_PORT_GCC_ARM_STM32H745_CM7_DEF_INC