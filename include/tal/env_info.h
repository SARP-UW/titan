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
   * @section System Information Defines
   **************************************************************************************************/

  /**
   * @def tal_sys_size
   * @brief Macro which evaluates to a value which corresponds to the size of 
   *        the system architecture in bits (size of addresses/registers).
   */

  #define tal_sys_size_16_v 16 /** @brief Value of tal_sys_size if system is 16 bits. */
  #define tal_sys_size_32_v 32 /** @brief Value of tal_sys_size if system is 32 bits. */
  #define tal_sys_size_64_v 64 /** @brief Value of tal_sys_size if system is 64 bits. */

  #if defined(TAL_ARCH_ARMV7M)
    #define tal_sys_size tal_sys_size_32_v
  #endif

  /**
   * @def tal_sys_endian
   * @brief Macro which evaluates to a value which corresponds to the 
   *        endianness of the system architecture.
   */

  #define tal_sys_endian_little_v 0 /** @brief Value of tal_sys_endian if the system is little endian. */
  #define tal_sys_endian_big_v 1 /** @brief Value of tal_sys_endian if the system is big endian. */

  #if defined(__GNUC__)
    #if (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
      #define tal_sys_endian tal_sys_endian_little_v
    #elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
      #define tal_sys_endian tal_sys_endian_big_v
    #else
      #warning "Unknown system endianness, defaulting to little endian."
      #define tal_sys_endian tal_sys_endian_little_v
    #endif
  #endif

  /**
   * @def tal_sys_signrep
   * @brief Macro which evaluates to a value which corresponds to the signed
   *        integer representation type of the current system.
   */

  #define tal_signrep_two_compl_v 0 /** @brief Value of tal_sys_signrep if system uses two's complement. */
  #define tal_signrep_one_compl_v 1 /** @brief Value of tal_sys_signrep if system uses one's complement  */
  #define tal_signrep_sign_mag_v 2 /** @brief Value of tal_sys_signrep if system uses sign magnitude. */

  #if ((-1 & 3) == 1)
    #define tal_sys_signrep tal_signrep_sign_mag_v
  #elif ((-1 & 3) == 2)
    #define tal_sys_signrep tal_signrep_one_compl_v
  #elif ((-1 & 3) == 3)
    #define tal_sys_signrep tal_signrep_two_compl_v
  #else
    #warning "Unknown system sign representation, defaulting to two's complement."
    #define tal_sys_signrep tal_signrep_two_compl_v
  #endif

#if defined(__cplusplus)
  }
#endif