/**
 * This file is part of the Titan Avionics Library
 * Copyright (c) 2024 Aaron McBride.
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
 * @file common/env/bits/compiler_interface/constants.h 
 * @authors Aaron McBride 
 * @brief Compiler-agnostic definition/constant interface.
 */

#pragma once

/**************************************************************************************************
 * @section Integer Representation
 **************************************************************************************************/

#if (-1 & 3) == 1
  #define TI_SIGN_MAGNITUDE 1
  #define TI_ONE_COMPLEMENT 0
  #define TI_TWO_COMPLEMENT 0
#elif (-1 & 3) == 2
  #define TI_SIGN_MAGNITUDE 0
  #define TI_ONE_COMPLEMENT 1
  #define TI_TWO_COMPLEMENT 0
#elif (-1 & 3) == 3
  #define TI_SIGN_MAGNITUDE 0
  #define TI_ONE_COMPLEMENT 0
  #define TI_TWO_COMPLEMENT 1
#else
  #warning Unknown integer representation. \
           Defaulting to two's complement.
  #define TI_TWO_COMPLEMENT 1
  #define TI_ONE_COMPLEMENT 0
  #define TI_SIGN_MAGNITUDE 0
#endif

/**************************************************************************************************
 * @section 128-Bit Integer Suport
 **************************************************************************************************/

#if defined(__GNUC__)
  #if defined(__INT128_TYPE__)
    #define TI_HAS_INT128 1
  #else
    #define TI_HAS_INT128 0
  #endif
#endif

/**************************************************************************************************
 * @section Endianness Definitions
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_L_ENDIAN (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
  #define TI_B_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#endif

#if !TI_L_ENDIAN && !TI_B_ENDIAN
  #warning Unknown system endianness. Defaulting to little endian.
  #define TI_L_ENDIAN 1
  #define TI_B_ENDIAN 0
#endif

/**************************************************************************************************
 * @section Standard Integer Max Definitions
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_CHAR_MAX __SCHAR_MAX__
  #define TI_SHORT_MAX __SHRT_MAX__
  #define TI_INT_MAX __INT_MAX__
  #define TI_LONG_MAX __LONG_MAX__
  #define TI_LONG_LONG_MAX __LONG_LONG_MAX__
#endif

/**************************************************************************************************
 * @section Standard Integer Width Definitions
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_CHAR_WIDTH __SCHAR_WIDTH__
  #define TI_SHORT_WIDTH __SHRT_WIDTH__
  #define TI_INT_WIDTH __INT_WIDTH__
  #define TI_LONG_WIDTH __LONG_WIDTH__
  #define TI_LONG_LONG_WIDTH __LONG_LONG_WIDTH__
  #define TI_INTPTR_WIDTH __INTPTR_WIDTH__
  #define TI_SIZE_WIDTH __SIZE_WIDTH__
#endif

/**************************************************************************************************
 * @section Standard Integer Size Definitions
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_CHAR_SIZE 1
  #define TI_SHORT_SIZE __SIZEOF_SHORT__
  #define TI_INT_SIZE __SIZEOF_INT__
  #define TI_LONG_SIZE __SIZEOF_LONG__
  #define TI_LONG_LONG_SIZE __SIZEOF_LONG_LONG__
  #define TI_POINTER_SIZE __SIZEOF_POINTER__
  #define TI_SIZE_SIZE __SIZEOF_SIZE_T__
#endif

/**************************************************************************************************
 * @section Width-Based Integer Type Definitions
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_INT8_TYPE __INT8_TYPE__
  #define TI_UINT8_TYPE __UINT8_TYPE__
  #define TI_INT16_TYPE __INT16_TYPE__
  #define TI_UINT16_TYPE __UINT16_TYPE__
  #define TI_INT32_TYPE __INT32_TYPE__
  #define TI_UINT32_TYPE __UINT32_TYPE__
  #define TI_INT64_TYPE __INT64_TYPE__
  #define TI_UINT64_TYPE __UINT64_TYPE__
  #if TI_HAS_INT128
    #define TI_INT128_TYPE __INT128_TYPE__
    #define TI_UINT128_TYPE __UINT128_TYPE__
  #endif
#endif

/**************************************************************************************************
 * @section Width-Based Integer Max Definitions
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_INT8_MAX __INT8_MAX__
  #define TI_UINT8_MAX __UINT8_MAX__
  #define TI_INT16_MAX __INT16_MAX__
  #define TI_UINT16_MAX __UINT16_MAX__
  #define TI_INT32_MAX __INT32_MAX__
  #define TI_UINT32_MAX __UINT32_MAX__
  #define TI_INT64_MAX __INT64_MAX__
  #define TI_UINT64_MAX __UINT64_MAX__
  #if TI_HAS_INT128
    #define TI_INT128_MAX __INT128_MAX__
    #define TI_UINT128_MAX __UINT128_MAX__
  #endif
#endif

/**************************************************************************************************
 * @section Concept-Based Integer Type Definitions
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_INTMAX_TYPE __INTMAX_TYPE__
  #define TI_UINTMAX_TYPE __UINTMAX_TYPE__
  #define TI_INTPTR_TYPE __INTPTR_TYPE__
  #define TI_UINTPTR_TYPE __UINTPTR_TYPE__
  #define TI_SIZE_TYPE __SIZE_TYPE__
#endif

/**************************************************************************************************
 * @section Concept-Based Integer Max Definitions
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_INTMAX_MAX __INTMAX_MAX__
  #define TI_UINTMAX_MAX __UINTMAX_MAX__
  #define TI_INTPTR_MAX __INTPTR_MAX__
  #define TI_UINTPTR_MAX __UINTPTR_MAX__
  #define TI_SIZE_MAX __SIZE_MAX__
#endif

/**************************************************************************************************
 * @section Miscellaneous Constants
 **************************************************************************************************/

#if defined(__GNUC__)
  #define TI_CHAR_BIT __CHAR_BIT__
#endif