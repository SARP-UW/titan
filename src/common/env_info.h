/**
 * This file is part of the Titan Avionics Library
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
 * @file include/tal/env.h
 * @authors Aaron McBride
 * @brief Environment-specific defines.
 */

#pragma once

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section System Information
   **************************************************************************************************/

  /**
   * @def tal_env_archsize
   * @brief Macro which denotes the environment's architecture size.
   * @note - Defaults to 32 bits.
   */

  #define tal_archsize_16_v 16 /** @brief Value of tal_env_archsize if system is 16 bits. */
  #define tal_archsize_32_v 32 /** @brief Value of tal_env_archsize if system is 32 bits. */
  #define tal_archsize_64_v 64 /** @brief Value of tal_env_archsize if system is 64 bits. */

  #if defined(TAL_ARCH_ARMV7M)
    #define tal_env_archsize tal_archsize_32_v
  #else
    #warning "Unknown or unsupported architecture size, defaulting to 32 bits."
    #define tal_env_archsize tal_archsize_32_v
  #endif


  /**
   * @def tal_sys_endian
   * @brief Macro which denotes the environment's endianness.
   * @note - Defaults to little endian.
   */

  #define tal_endian_little_v 0 /** @brief Value of tal_sys_endian if the system is little endian. */
  #define tal_endian_big_v 1 /** @brief Value of tal_sys_endian if the system is big endian. */

  #if defined(__GNUC__)
    #if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
      #define tal_env_endian tal_endian_little_v
    #elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
      #define tal_env_endian tal_endian_big_v
    #else
      #warning "Unknown or unsupported endianness, defaulting to little endian."
      #define tal_env_endian tal_endian_little_v
    #endif
  #endif

  /**************************************************************************************************
   * @section Implementation Information
   **************************************************************************************************/

  /**
   * @def tal_env_signrep
   * @brief Macro which denotes the environment's signed integer representation.
   * @note - Defaults to two's complement.
   */

  #define tal_signrep_2compl_v 0 /** @brief Value of tal_env_signrep if system uses two's complement. */
  #define tal_signrep_1compl_v 1 /** @brief Value of tal_env_signrep if system uses one's complement  */
  #define tal_signrep_signmag_v 2 /** @brief Value of tal_env_signrep if system uses sign magnitude. */

  #if ((-1 & 3) == 1)
    #define tal_env_signrep tal_signrep_signmag_v
  #elif ((-1 & 3) == 2)
    #define tal_env_signrep tal_signrep_1compl_v
  #elif ((-1 & 3) == 3)
    #define tal_env_signrep tal_signrep_2compl_v
  #else
    #warning "Unknown or unsupported signed integer representation, defaulting to two's complement."
    #define tal_env_signrep tal_signrep_2compl_v
  #endif


  /**
   * @def tal_env_floatrep
   * @brief Macro which denotes the environment's floating-point representation.
   * @note - Defaults to IEEE754.
   */

  #define tal_floatrep_ieee754 0 /** @brief Value of tal_sys_floatrep if system uses ieee754 floating-point. */

  #if defined(__GNUC__)
    #define tal_env_floatrep tal_floatrep_ieee754_v
  #else
    #warning "Unknown or unsupported system floating-point representation, defaulting to IEEE754."
    #define tal_env_floatrep tal_floatrep_ieee754_v
  #endif

#if defined(__cplusplus)
  }
#endif