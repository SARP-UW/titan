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
 * @file src/port/gcc_arm_stm32h745_cm7/limits.inc
 * @authors Aaron McBride
 * @brief Definition of numeric implementation limits for the 
 *        arm_gcc_stm32h745_cm7 port.
 */

#include <limits.h>

#if !defined(SRC_PORT_GCC_ARM_STM32H745_CM7_LIMITS_INC)
#define SRC_PORT_GCC_ARM_STM32H745_CM7_LIMITS_INC

#if defined(__cplusplus)
  extern "C" {
#endif 
  
  /************************************************************************************************
   * @section Standard Integer Size
   ************************************************************************************************/

  #undef SCHAR_SIZE
  #define SCHAR_SIZE (1)

  #undef SHRT_SIZE
  #define SHRT_SIZE (2)

  #undef INT_SIZE
  #define INT_SIZE (4)

  #undef LONG_SIZE
  #define LONG_SIZE (4)

  #undef LLONG_SIZE
  #define LLONG_SIZE (8)

  #undef UCHAR_SIZE
  #define UCHAR_SIZE (1)

  #undef USHRT_SIZE
  #define USHRT_SIZE (2)

  #undef UINT_SIZE
  #define UINT_SIZE (4)

  #undef ULONG_SIZE
  #define ULONG_SIZE (4)

  #undef ULLONG_SIZE
  #define ULLONG_SIZE (8)

  /************************************************************************************************
   * @section Standard Floating Point Size
   ************************************************************************************************/

  #undef FLT_SIZE
  #define FLT_SIZE (4)

  #undef DBL_SIZE
  #define DBL_SIZE (8)

  #undef LDBL_SIZE
  #define LDBL_SIZE (8)

  /************************************************************************************************
   * @section Bit-Width Integer Size
   ************************************************************************************************/

  #undef INT8_SIZE
  #define INT8_SIZE (1)

  #undef INT16_SIZE
  #define INT16_SIZE (2)

  #undef INT32_SIZE
  #define INT32_SIZE (4)

  #undef INT64_SIZE
  #define INT64_SIZE (8)

  #undef INT128_SIZE

  #undef UINT8_SIZE
  #define UINT8_SIZE (1)

  #undef UINT16_SIZE
  #define UINT16_SIZE (2)

  #undef UINT32_SIZE
  #define UINT32_SIZE (4)

  #undef UINT64_SIZE
  #define UINT64_SIZE (8)

  #undef UINT128_SIZE

  /************************************************************************************************
   * @section Bit-Width Floating Point Size
   ************************************************************************************************/

  #undef FLT16_SIZE

  #undef FLT32_SIZE
  #define FLT32_SIZE (4)

  #undef FLT64_SIZE
  #define FLT64_SIZE (8)

  #undef FLT80_SIZE

  #undef FLT128_SIZE

  /************************************************************************************************
   * @section Special Integer Size
   ************************************************************************************************/

  #undef INTMIN_SIZE
  #define INTMIN_SIZE (1)

  #undef UINTMIN_SIZE
  #define UINTMIN_SIZE (1)

  #undef INTMAX_SIZE
  #define INTMAX_SIZE (8)

  #undef UINTMAX_SIZE
  #define UINTMAX_SIZE (8)

  #undef INTPTR_SIZE
  #define INTPTR_SIZE (4)

  #undef UINTPTR_SIZE
  #define UINTPTR_SIZE (4)

  #undef SIZE_SIZE
  #define SIZE_SIZE (4)

  #undef SSIZE_SIZE
  #define SSIZE_SIZE (4)

  #undef PTRDIFF_SIZE
  #define PTRDIFF_SIZE (4)

  /************************************************************************************************
   * @section Special Floating Point Size
   ************************************************************************************************/

  #undef FLTMIN_SIZE
  #define FLTMIN_SIZE (4)

  #undef FLTMAX_SIZE
  #define FLTMAX_SIZE (8)

  /************************************************************************************************
   * @section Standard Integer Width
   ************************************************************************************************/

  #undef SCHAR_WIDTH
  #define SCHAR_WIDTH (8)

  #undef SHRT_WIDTH
  #define SHRT_WIDTH (16)

  #undef INT_WIDTH
  #define INT_WIDTH (32)

  #undef LONG_WIDTH
  #define LONG_WIDTH (32)

  #undef LLONG_WIDTH
  #define LLONG_WIDTH (64)

  #undef UCHAR_WIDTH
  #define UCHAR_WIDTH (8)

  #undef USHRT_WIDTH
  #define USHRT_WIDTH (16)

  #undef UINT_WIDTH
  #define UINT_WIDTH (32)

  #undef ULONG_WIDTH
  #define ULONG_WIDTH (32)

  #undef ULLONG_WIDTH
  #define ULLONG_WIDTH (64)

  /************************************************************************************************
   * @section Standard Floating Point Width
   ************************************************************************************************/

  #undef FLT_WIDTH
  #define FLT_WIDTH (32)

  #undef DBL_WIDTH
  #define DBL_WIDTH (64)

  #undef LDBL_WIDTH
  #define LDBL_WIDTH (64)

  /************************************************************************************************
   * @section Bit-Width Integer Width
   ************************************************************************************************/

  #undef INT8_WIDTH
  #define INT8_WIDTH (8)

  #undef INT16_WIDTH
  #define INT16_WIDTH (16)

  #undef INT32_WIDTH
  #define INT32_WIDTH (32)

  #undef INT64_WIDTH
  #define INT64_WIDTH (64)

  #undef INT128_WIDTH

  #undef UINT8_WIDTH
  #define UINT8_WIDTH (8)

  #undef UINT16_WIDTH
  #define UINT16_WIDTH (16)

  #undef UINT32_WIDTH
  #define UINT32_WIDTH (32)

  #undef UINT64_WIDTH
  #define UINT64_WIDTH (64)

  #undef UINT128_WIDTH

  /************************************************************************************************
   * @section Bit-Width Floating Point Width
   ************************************************************************************************/

  #undef FLT16_WIDTH

  #undef FLT32_WIDTH
  #define FLT32_WIDTH (32)

  #undef FLT64_WIDTH
  #define FLT64_WIDTH (64)

  #undef FLT80_WIDTH

  #undef FLT128_WIDTH

  /************************************************************************************************
   * @section Special Integer Width
   ************************************************************************************************/

  #undef INTMIN_WIDTH
  #define INTMIN_WIDTH (8)

  #undef UINTMIN_WIDTH
  #define UINTMIN_WIDTH (8)

  #undef INTMAX_WIDTH
  #define INTMAX_WIDTH (64)

  #undef UINTMAX_WIDTH
  #define UINTMAX_WIDTH (64)

  #undef INTPTR_WIDTH
  #define INTPTR_WIDTH (32)

  #undef UINTPTR_WIDTH
  #define UINTPTR_WIDTH (32)

  #undef SIZE_WIDTH
  #define SIZE_WIDTH (32)

  #undef SSIZE_WIDTH
  #define SSIZE_WIDTH (32)

  #undef PTRDIFF_WIDTH
  #define PTRDIFF_WIDTH (32)

  /************************************************************************************************
   * @section Special Floating Point Width
   ************************************************************************************************/

  #undef FLTMIN_WIDTH
  #define FLTMIN_WIDTH (32)

  #undef FLTMAX_WIDTH
  #define FLTMAX_WIDTH (64)

  /************************************************************************************************
   * @section Standard Integer Minimum
   ************************************************************************************************/

  #undef SCHAR_MIN
  #define SCHAR_MIN (signed char)(-128)

  #undef SHRT_MIN
  #define SHRT_MIN (signed short)(-32768)

  #undef INT_MIN
  #define INT_MIN (-2147483648)

  #undef LONG_MIN
  #define LONG_MIN (-2147483648)

  #undef LLONG_MIN
  #define LLONG_MIN







  #define UCHAR_MIN







  #define USHRT_MIN







  #define UINT_MIN







  #define ULONG_MIN







  #define ULLONG_MIN

  /************************************************************************************************
   * @section Standard Floating Point Minimum
   ************************************************************************************************/







  #define FLT_MIN
  






  #define DBL_MIN







  #define LDBL_MIN

  /************************************************************************************************
   * @section Bit-Width Integer Minimum
   ************************************************************************************************/
  







  #define INT8_MIN








  #define INT16_MIN








  #define INT32_MIN








  #define INT64_MIN









  #define INT128_MIN








  #define UINT8_MIN








  #define UINT16_MIN








  #define UINT32_MIN








  #define UINT64_MIN









  #define UINT128_MIN

  /************************************************************************************************
   * @section Bit-Width Floating Point Minimum
   ************************************************************************************************/









  #define FLT16_MIN
  







  #define FLT32_MIN








  #define FLT64_MIN









  #define FLT80_MIN









  #define FLT128_MIN

  /************************************************************************************************
   * @section Special Integer Minimum
   ************************************************************************************************/








  #define INTMIN_MIN








  #define UINTMIN_MIN








  #define INTMAX_MIN








  #define UINTMAX_MIN








  #define INTPTR_MIN








  #define UINTPTR_MIN








  #define SIZE_MIN








  #define SSIZE_MIN








  #define PTRDIFF_MIN

  /************************************************************************************************
   * @section Special Floating Point Minimum
   ************************************************************************************************/








  #define FLTMIN_MIN








  #define FLTMAX_MIN

  /************************************************************************************************
   * @section Standard Integer Maximum
   ************************************************************************************************/
  






  #define SCHAR_MAX







  #define SHRT_MAX







  #define INT_MAX







  #define LONG_MAX







  #define LLONG_MAX







  #define UCHAR_MAX







  #define USHRT_MAX







  #define UINT_MAX







  #define ULONG_MAX







  #define ULLONG_MAX

  /************************************************************************************************
   * @section Standard Floating Point Maximum
   ************************************************************************************************/







  #define FLT_MAX







  #define DBL_MAX







  #define LDBL_MAX

  /************************************************************************************************
   * @section Bit-Width Integer Maximum
   ************************************************************************************************/








  #define INT8_MAX








  #define INT16_MAX








  #define INT32_MAX








  #define INT64_MAX









  #define INT128_MAX








  #define UINT8_MAX








  #define UINT16_MAX








  #define UINT32_MAX








  #define UINT64_MAX









  #define UINT128_MAX

  /************************************************************************************************
   * @section Bit-Width Floating Point Maximum
   ************************************************************************************************/









  #define FLT16_MAX








  #define FLT32_MAX








  #define FLT64_MAX









  #define FLT80_MAX









  #define FLT128_MAX

  /************************************************************************************************
   * @section Special Integer Maximum
   ************************************************************************************************/








  #define INTMIN_MAX








  #define UINTMIN_MAX








  #define INTMAX_MAX








  #define UINTMAX_MAX








  #define INTPTR_MAX








  #define UINTPTR_MAX








  #define SIZE_MAX








  #define SSIZE_MAX








  #define PTRDIFF_MAX

  /************************************************************************************************
   * @section Special Floating Point Maximum
   ************************************************************************************************/








  #define FLTMIN_MAX








  #define FLTMAX_MAX

  /************************************************************************************************
   * @section Standard Integer Digits
   ************************************************************************************************/







  #define SCHAR_DIG







  #define SHRT_DIG







  #define INT_DIG







  #define LONG_DIG







  #define LLONG_DIG







  #define UCHAR_DIG







  #define USHRT_DIG







  #define UINT_DIG







  #define ULONG_DIG







  #define ULLONG_DIG

  /************************************************************************************************
   * @section Standard Floating Point Digits
   ************************************************************************************************/







  #define FLT_DIG







  #define DBL_DIG







  #define LDBL_DIG

  /************************************************************************************************
   * @section Bit-Width Integer Digits
   ************************************************************************************************/








  #define INT8_DIG








  #define INT16_DIG








  #define INT32_DIG








  #define INT64_DIG









  #define INT128_DIG








  #define UINT8_DIG








  #define UINT16_DIG








  #define UINT32_DIG








  #define UINT64_DIG









  #define UINT128_DIG

  /************************************************************************************************
   * @section Bit-Width Floating Point Digits
   ************************************************************************************************/









  #define FLT16_DIG








  #define FLT32_DIG








  #define FLT64_DIG









  #define FLT80_DIG









  #define FLT128_DIG

  /************************************************************************************************
   * @section Special Integer Digits
   ************************************************************************************************/








  #define INTMIN_DIG








  #define UINTMIN_DIG








  #define INTMAX_DIG








  #define UINTMAX_DIG








  #define INTPTR_DIG








  #define UINTPTR_DIG








  #define SIZE_DIG








  #define SSIZE_DIG








  #define PTRDIFF_DIG

  /************************************************************************************************
   * @section Special Floating Point Digits
   ************************************************************************************************/








  #define FLTMIN_DIG








  #define FLTMAX_DIG

  /************************************************************************************************
   * @section Standard Floating Point Normalized Minimum
   ************************************************************************************************/







  #define FLT_NORM_MIN







  #define DBL_NORM_MIN







  #define LDBL_NORM_MIN

  /************************************************************************************************
   * @section Bit-Width Floating Point Normalized Minimum
   ************************************************************************************************/









  #define FLT16_NORM_MIN








  #define FLT32_NORM_MIN








  #define FLT64_NORM_MIN









  #define FLT80_NORM_MIN









  #define FLT128_NORM_MIN

  /************************************************************************************************
   * @section Special Floating Point Normalized Minimum
   ************************************************************************************************/








  #define FLTMIN_NORM_MIN








  #define FLTMAX_NORM_MIN

  /************************************************************************************************
   * @section Standard Floating Point Normalized Maximum
   ************************************************************************************************/







  #define FLT_NORM_MAX







  #define DBL_NORM_MAX







  #define LDBL_NORM_MAX

  /************************************************************************************************
   * @section Bit-Width Floating Point Normalized Maximum
   ************************************************************************************************/









  #define FLT16_NORM_MAX








  #define FLT32_NORM_MAX








  #define FLT64_NORM_MAX









  #define FLT80_NORM_MAX









  #define FLT128_NORM_MAX

  /************************************************************************************************
   * @section Special Floating Point Normalized Maximum
   ************************************************************************************************/








  #define FLTMIN_NORM_MAX








  #define FLTMAX_NORM_MAX

  /************************************************************************************************
   * @section Standard Floating Point Normalized Digits
   ************************************************************************************************/







  #define FLT_NORM_DIG







  #define DBL_NORM_DIG







  #define LDBL_NORM_DIG

  /************************************************************************************************
   * @section Bit-Width Floating Point Normalized Digits
   ************************************************************************************************/









  #define FLT16_NORM_DIG








  #define FLT32_NORM_DIG








  #define FLT64_NORM_DIG









  #define FLT80_NORM_DIG









  #define FLT128_NORM_DIG

  /************************************************************************************************
   * @section Special Floating Point Normalized Digits
   ************************************************************************************************/








  #define FLTMIN_NORM_DIG








  #define FLTMAX_NORM_DIG

  /************************************************************************************************
   * @section Standard Floating Point Significand Width
   ************************************************************************************************/






  #define FLT_SIGC_WIDTH






  #define DBL_SIGC_WIDTH






  #define LDBL_SIGC_WIDTH

  /************************************************************************************************
   * @section Bit-Width Floating Point Significand Width
   ************************************************************************************************/








  #define FLT16_SIGC_WIDTH







  #define FLT32_SIGC_WIDTH







  #define FLT64_SIGC_WIDTH








  #define FLT80_SIGC_WIDTH








  #define FLT128_SIGC_WIDTH

  /************************************************************************************************
   * @section Special Floating Point Significand Width
   ************************************************************************************************/







  #define FLTMIN_SIGC_WIDTH







  #define FLTMAX_SIGC_WIDTH

  /************************************************************************************************
   * @section Standard Floating Point Significand Minimum
   ************************************************************************************************/








  #define FLT_SIGC_MIN








  #define DBL_SIGC_MIN








  #define LDBL_SIGC_MIN

  /************************************************************************************************
   * @section Bit-Width Floating Point Significand Minimum
   ************************************************************************************************/










  #define FLT16_SIGC_MIN









  #define FLT32_SIGC_MIN









  #define FLT64_SIGC_MIN










  #define FLT80_SIGC_MIN










  #define FLT128_SIGC_MIN

  /************************************************************************************************
   * @section Special Floating Point Significand Minimum
   ************************************************************************************************/









  #define FLTMIN_SIGC_MIN









  #define FLTMAX_SIGC_MIN

  /************************************************************************************************
   * @section Standard Floating Point Significand Maximum
   ************************************************************************************************/








  #define FLT_SIGC_MAX








  #define DBL_SIGC_MAX








  #define LDBL_SIGC_MAX

  /************************************************************************************************
   * @section Bit-Width Floating Point Significand Maximum
   ************************************************************************************************/










  #define FLT16_SIGC_MAX









  #define FLT32_SIGC_MAX









  #define FLT64_SIGC_MAX










  #define FLT80_SIGC_MAX










  #define FLT128_SIGC_MAX

  /************************************************************************************************
   * @section Special Floating Point Significand Maximum
   ************************************************************************************************/









  #define FLTMIN_SIGC_MAX









  #define FLTMAX_SIGC_MAX

  /************************************************************************************************
   * @section Standard Floating Point Significand Digits
   ************************************************************************************************/







  #define FLT_SIGC_DIG







  #define DBL_SIGC_DIG







  #define LDBL_SIGC_DIG

  /************************************************************************************************
   * @section Bit-Width Floating Point Significand Digits
   ************************************************************************************************/









  #define FLT16_SIGC_DIG








  #define FLT32_SIGC_DIG








  #define FLT64_SIGC_DIG









  #define FLT80_SIGC_DIG









  #define FLT128_SIGC_DIG

  /************************************************************************************************
   * @section Special Floating Point Significand Digits
   ************************************************************************************************/








  #define FLTMIN_SIGC_DIG








  #define FLTMAX_SIGC_DIG

  /************************************************************************************************
   * @section Standard Floating Point Exponent Width
   ************************************************************************************************/


  #define FLT_EXP_WIDTH


  #define DBL_EXP_WIDTH


  #define LDBL_EXP_WIDTH

  /************************************************************************************************
   * @section Bit-Width Floating Point Exponent Width
   ************************************************************************************************/


  #define FLT16_EXP_WIDTH


  #define FLT32_EXP_WIDTH


  #define FLT64_EXP_WIDTH


  #define FLT80_EXP_WIDTH


  #define FLT128_EXP_WIDTH

  /************************************************************************************************
   * @section Special Floating Point Exponent Width
   ************************************************************************************************/


  #define FLTMIN_EXP_WIDTH


  #define FLTMAX_EXP_WIDTH

  /************************************************************************************************
   * @section Standard Floating Point Exponent Minimum
   ************************************************************************************************/


  #define FLT_EXP_MIN


  #define DBL_EXP_MIN


  #define LDBL_EXP_MIN

  /************************************************************************************************
   * @section Bit-Width Floating Point Exponent Minimum
   ************************************************************************************************/


  #define FLT16_EXP_MIN


  #define FLT32_EXP_MIN


  #define FLT64_EXP_MIN


  #define FLT80_EXP_MIN


  #define FLT128_EXP_MIN

  /************************************************************************************************
   * @section Special Floating Point Exponent Minimum
   ************************************************************************************************/


  #define FLTMIN_EXP_MIN


  #define FLTMAX_EXP_MIN

  /************************************************************************************************
   * @section Standard Floating Point Exponent Maximum
   ************************************************************************************************/


  #define FLT_EXP_MAX


  #define DBL_EXP_MAX


  #define LDBL_EXP_MAX

  /************************************************************************************************
   * @section Bit-Width Floating Point Exponent Maximum
   ************************************************************************************************/


  #define FLT16_EXP_MAX


  #define FLT32_EXP_MAX


  #define FLT64_EXP_MAX


  #define FLT80_EXP_MAX


  #define FLT128_EXP_MAX

  /************************************************************************************************
   * @section Special Floating Point Exponent Maximum
   ************************************************************************************************/


  #define FLTMIN_EXP_MAX


  #define FLTMAX_EXP_MAX

  /************************************************************************************************
   * @section Standard Floating Point Exponent Digits
   ************************************************************************************************/


  #define FLT_EXP_DIG


  #define DBL_EXP_DIG


  #define LDBL_EXP_DIG

  /************************************************************************************************
   * @section Bit-Width Floating Point Exponent Digits
   ************************************************************************************************/


  #define FLT16_EXP_DIG


  #define FLT32_EXP_DIG


  #define FLT64_EXP_DIG


  #define FLT80_EXP_DIG


  #define FLT128_EXP_DIG

  /************************************************************************************************
   * @section Special Floating Point Exponent Digits
   ************************************************************************************************/


  #define FLTMIN_EXP_DIG


  #define FLTMAX_EXP_DIG

  /************************************************************************************************
   * @section Standard Floating Point Epsilon
   ************************************************************************************************/


  #define FLT_EPSILON


  #define DBL_EPSILON


  #define LDBL_EPSILON

  /************************************************************************************************
   * @section Bit-Width Floating Point Epsilon
   ************************************************************************************************/


  #define FLT16_EPSILON


  #define FLT32_EPSILON


  #define FLT64_EPSILON


  #define FLT80_EPSILON


  #define FLT128_EPSILON

  /************************************************************************************************
   * @section Special Floating Point Epsilon
   ************************************************************************************************/


  #define FLTMIN_EPSILON


  #define FLTMAX_EPSILON

  /************************************************************************************************
   * @section Uncategorised Limits
   ************************************************************************************************/

  #define CHAR_BIT

  #define FP_RADIX
  
#if defined(__cplusplus)
  } // extern "C"
#endif

#endif // SRC_PORT_GCC_ARM_STM32H745_CM7_LIMITS_INC