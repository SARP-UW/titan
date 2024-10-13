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
 * @file common/util/cstdint.h 
 * @authors Aaron McBride 
 * @brief Contains all implemented facilities of the cstdint library.
 */

#pragma once
#include "common/env/compiler_interface.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Width-Based Integer Types
   **************************************************************************************************/

  /** @brief Type alias to the signed integer type with a width of 8 bits. */
  using int8_t = TI_INT8_TYPE;

  /** @brief Type alias to the unsigned integer type with a width of 8 bits. */
  using uint8_t = TI_UINT8_TYPE;

  /** @brief Type alias to the signed integer type with a width of 16 bits. */
  using int16_t = TI_INT16_TYPE;

  /** @brief Type alias to the unsigned integer type with a width of 16 bits. */
  using uint16_t = TI_UINT16_TYPE;

  /** @brief Type alias to the signed integer type with a width of 32 bits. */
  using int32_t = TI_INT32_TYPE;

  /** @brief Type alias to the unsigned integer type with a width of 32 bits. */
  using uint32_t = TI_UINT32_TYPE;

  /** @brief Type alias to the signed integer type with a width of 64 bits. */
  using int64_t = TI_INT64_TYPE;

  /** @brief Type alias to the unsigned integer type with a width of 64 bits. */
  using uint64_t = TI_UINT64_TYPE;

  /** @brief Type alias to the signed integer type with the maximum bit-width. */
  using intmax_t = TI_INTMAX_TYPE;

  /** @brief Type alias to the unsigned integer type with the maximum bit-width. */
  using uintmax_t = TI_UINTMAX_TYPE;

  /** @brief Type alias to a signed integer type with the same bit-width as a pointer. */
  using intptr_t = TI_INTPTR_TYPE;

  /** @brief Type alias to an unsigned integer type with the same bit-width as a pointer. */
  using uintptr_t = TI_UINTPTR_TYPE;

  /** @brief Type alias to the integer type returned by sizeof(...). */
  using size_t = TI_SIZE_TYPE;

  /**************************************************************************************************
   * @section Non-Standard Width-Based Integer Literals
   **************************************************************************************************/

  /** @brief Integer literal to the signed integer type with a width of 8 bits. */
  constexpr TI_INT8_TYPE operator "" _i8 (const unsigned long long int value);

  /** @brief Integer literal to the unsigned integer type with a width of 8 bits. */
  constexpr TI_UINT8_TYPE operator "" _u8 (const unsigned long long int value);

  /** @brief Integer literal to the signed integer type with a width of 16 bits. */
  constexpr TI_INT16_TYPE operator "" _i16 (const unsigned long long int value);

  /** @brief Integer literal to the unsigned integer type with a width of 16 bits. */
  constexpr TI_UINT16_TYPE operator "" _u16 (const unsigned long long int value);

  /** @brief Integer literal to the signed integer type with a width of 32 bits. */
  constexpr TI_INT32_TYPE operator "" _i32 (const unsigned long long int value);

  /** @brief Integer literal to the unsigned integer type with a width of 32 bits. */
  constexpr TI_UINT32_TYPE operator "" _u32 (const unsigned long long int value);

  /** @brief Integer literal to the signed integer type with a width of 64 bits. */
  constexpr TI_INT64_TYPE operator "" _i64 (const unsigned long long int value);

  /** @brief Integer literal to the unsigned integer type with a width of 64 bits. */
  constexpr TI_UINT64_TYPE operator "" _u64 (const unsigned long long int value);

  /** @brief Integer literal to the signed integer type with the maximum bit-width. */
  constexpr TI_INTMAX_TYPE operator "" _imax (const unsigned long long int value);

  /** @brief Integer literal to the unsigned integer type with the maximum bit-width. */
  constexpr TI_UINTMAX_TYPE operator "" _umax (const unsigned long long int value);

  /** @brief Integer literal to a signed integer type with the same bit-width as a pointer. */
  constexpr TI_INTPTR_TYPE operator "" _iptr (const unsigned long long int value);

  /** @brief Integer literal to an unsigned integer type with the same bit-width as a pointer. */
  constexpr TI_UINTPTR_TYPE operator "" _uptr (const unsigned long long int value);

  /** @brief Integer literal to the integer type returned by sizeof(...). */
  constexpr TI_SIZE_TYPE operator "" _size (const unsigned long long int value);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  // TODO -> Add bounds checking?

  constexpr TI_INT8_TYPE operator "" _i8 (const unsigned long long int value) {
    return static_cast<TI_INT8_TYPE>(value);
  }

  constexpr TI_UINT8_TYPE operator "" _u8 (const unsigned long long int value) {
    return static_cast<TI_UINT8_TYPE>(value);
  }

  constexpr TI_INT16_TYPE operator "" _i16 (const unsigned long long int value) {
    return static_cast<TI_INT16_TYPE>(value);
  }

  constexpr TI_UINT16_TYPE operator "" _u16 (const unsigned long long int value) {
    return static_cast<TI_UINT16_TYPE>(value);
  }

  constexpr TI_INT32_TYPE operator "" _i32 (const unsigned long long int value) {
    return static_cast<TI_INT32_TYPE>(value);
  }

  constexpr TI_UINT32_TYPE operator "" _u32 (const unsigned long long int value) {
    return static_cast<TI_UINT32_TYPE>(value);
  }

  constexpr TI_INT64_TYPE operator "" _i64 (const unsigned long long int value) {
    return static_cast<TI_INT64_TYPE>(value);
  }

  constexpr TI_UINT64_TYPE operator "" _u64 (const unsigned long long int value) {
    return static_cast<TI_UINT64_TYPE>(value);
  }

  constexpr TI_INTMAX_TYPE operator "" _imax (const unsigned long long int value) {
    return static_cast<TI_INTMAX_TYPE>(value);
  }

  constexpr TI_UINTMAX_TYPE operator "" _umax (const unsigned long long int value) {
    return static_cast<TI_UINTMAX_TYPE>(value);
  }

  constexpr TI_INTPTR_TYPE operator "" _iptr (const unsigned long long int value) {
    return static_cast<TI_INTPTR_TYPE>(value);
  }

  constexpr TI_UINTPTR_TYPE operator "" _uptr (const unsigned long long int value) {
    return static_cast<TI_UINTPTR_TYPE>(value);
  }

  constexpr TI_SIZE_TYPE operator "" _size (const unsigned long long int value) {
    return static_cast<TI_SIZE_TYPE>(value);
  }

  /// @endinternal

} // namespace ti::util