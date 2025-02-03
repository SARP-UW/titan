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
 * @internal
 * @file src/port/STM32H745_CM7/internal/compat.h
 * @authors Aaron McBride
 * @brief Compiler compatibility macros.
 */

#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Definition of Compatibility Macros
   ************************************************************************************************/

  /** @brief Place at the top of files which use compatibility macros. */
  #define COMPAT_FILE

  /** @brief Equivalent to __asm__ in GCC. */
  #define TI_ASM

  /** @brief Equivalent to __asm__ volatile in GCC. */
  #define TI_VOLATILE_ASM

  /** @brief Equivalent to __attribute__((naked)) in GCC. */
  #define TI_NAKED

  /** @brief Equivalent to __attribute__((noreturn)) in GCC. */
  #define TI_NORETURN

  /** @brief Equivalent to __attribute__((weak)) in GCC. */
  #define TI_WEAK

  /** @brief Equivalent to __attribute__((used)) in GCC. */
  #define TI_USED

    /** @brief Equivalent to __attribute__((unused)) in GCC. */
  #define TI_UNUSED

  /** @brief Equivalent to __attribute__((section(name))) in GCC. */
  #define TI_SECTION(name)

  /** @brief Equivalent to __attribute__((alias(name))) in GCC. */
  #define TI_ALIAS(name)

  /** @brief Equivalent to __attribute__((aligned(x))) in GCC. */
  #define TI_ALIGNED(x)

  /** @brief Equivalent to __attribute__((packed)) in GCC. */
  #define TI_PACKED

  /************************************************************************************************
   * Implementation of Compatibility Macros
   ************************************************************************************************/

  #undef COMPAT_FILE
  #undef TI_ASM
  #undef TI_VOLATILE_ASM
  #undef TI_NAKED
  #undef TI_NORETURN
  #undef TI_WEAK
  #undef TI_USED
  #undef TI_UNUSED
  #undef TI_SECTION
  #undef TI_ALIAS
  #undef TI_ALIGNED
  #undef TI_PACKED

  #if defined(__GNUC__)

    // GCC compiler
    #define COMPAT_FILE
    #define TI_ASM __asm__
    #define TI_VOLATILE_ASM __asm__ volatile
    #define TI_NAKED __attribute__((naked))
    #define TI_NORETURN __attribute__((noreturn))
    #define TI_WEAK __attribute__((weak))
    #define TI_USED __attribute__((used))
    #define TI_UNUSED __attribute__((unused))
    #define TI_SECTION(name) __attribute__((section(name)))
    #define TI_ALIAS(name) __attribute__((alias(name)))
    #define TI_ALIGNED(x) __attribute__((aligned(x)))
    #define TI_PACKED __attribute__((packed))

  #elif defined(__clang__) 

    // Clang compiler
    #define COMPAT_FILE
    #define TI_ASM __asm__
    #define TI_VOLATILE_ASM __asm__ volatile
    #define TI_NAKED __attribute__((naked))
    #define TI_NORETURN __attribute__((noreturn))
    #define TI_WEAK __attribute__((weak))
    #define TI_USED __attribute__((used))
    #define TI_UNUSED __attribute__((unused))
    #define TI_SECTION(name) __attribute__((section(name)))
    #define TI_ALIAS(name) __attribute__((alias(name)))
    #define TI_ALIGNED(x) __attribute__((aligned(x)))
    #define TI_PACKED __attribute__((packed))

  #elif defined(__IAR_SYSTEMS_ICC__)

    // IAR compiler
    #define COMPAT_FILE _Pragma("language = extended")
    #define TI_ASM __asm
    #define TI_VOLATILE_ASM __asm volatile
    #define TI_NAKED __attribute__((naked))
    #define TI_NORETURN __attribute__((noreturn))
    #define TI_WEAK __attribute__((weak))
    #define TI_USED __attribute__((used))
    #define TI_UNUSED __attribute__((unused))
    #define TI_SECTION(name) __attribute__((section(name)))
    #define TI_ALIAS(name) __attribute__((alias(name)))
    #define TI_ALIGNED(x) __attribute__((aligned(x)))
    #define TI_PACKED __attribute__((packed))    

  #else
    #error "Compiler not supported by target port."
  #endif

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */