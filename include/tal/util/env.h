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
 * @file include/tal/util/env.h
 * @authors Aaron McBride
 * @brief Environment-specific defines.
 */

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  #if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && \
      defined(__ORDER_BIG_ENDIAN__)
    #if (__BYTE_ORDER__) == (__ORDER_LITTLE_ENDIAN__)
      #define tal_env_endian (tal_little_endian_v)
    #elif (__BYTE_ORDER__) == (__ORDER_BIG_ENDIAN__)
      #define tal_env_endian (tal_big_endian_v)
    #else
      #error "TAL ERROR: Unknown environment endianness.
    #endif
  #else 
    #warning "TAL WARNING: Unknown environment endianness. Defaulting to little endian."
    #define tal_env_endian (tal_little_endian_v)
  #endif

  #if ((-1 & 3) == 1)
    #define tal_env_signrep (tal_sign_mag_v)
  #elif ((-1 & 3) == 2)
    #define tal_env_signrep (tal_one_compl_v)
  #elif ((-1 & 3) == 3)
    #define tal_env_signrep (tal_two_compl_v)
  #else
    #error "TAL ERROR: Environment uses unknown signed integer representation."
  #endif

  /** @endinternal */

  /**************************************************************************************************
   * @section Non-Standard Environment Defines
   **************************************************************************************************/

  /**
   * @def tal_env_endian
   * @brief Macro which evaluates to a specific value depending on the endianess
   *        of the current environment.
   * @note - Equals 'tal_little_endian_v' if the current environment is little endian.
   * @note - Equals 'tal_big_endian_v' if the current environment is big endian. 
   * @see tal_little_endian_v
   * @see tal_big_endian_v
   */

  /** 
   * @brief Value of tal_sys_endian if current system is little endian.
   * @see tal_sys_endian
   */
  #define tal_little_endian_v -1 

  /** 
   * @brief Value of tal_sys_endian if current system is big endian. 
   * @see tal_sys_endian
   */
  #define tal_big_endian_v 1

  /**
   * @def tal_env_signrep
   * @brief Macro which evaluates to a specific value depending on the signed
   *        integer representation used by the current environment.
   * @note - Equals 'tal_two_compl_v' if the current environment uses two's complement.
   * @note - Equals 'tal_one_compl_v' if the current environment uses one's complement.
   * @note - Equals 'tal_sign_mag_v' if the current environment uses sign-magnitude.
   * @see tal_two_compl_v
   * @see tal_one_compl_v
   * @see tal_sign_mag_v
   */

  /**
   * @brief Value of tal_env_signrep if the current system uses two's complement.
   * @see tal_env_signrep
   */
  #define tal_two_compl_v -1

  /**
   * @brief Value of tal_env_signrep if the current system uses one's complement.
   * @see tal_env_signrep
   */
  #define tal_one_compl_v 1

  /**
   * @brief Value of tal_env_signrep if the current system uses sign-magnitude.
   * @see tal_env_signrep
   */
  #define tal_sign_mag_v 0

#if defined(__cplusplus)
  }
#endif
