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
 * @file common/util/bit.h 
 * @authors Aaron McBride 
 * @brief Contains bit manipulation utilities.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"
#include "common/util/type_traits.h"
#include "common/util/utility.h"
#include "common/util/limits.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Standard Bit-Manipulation Utilities
   **************************************************************************************************/

  /**
   * @brief TODO
   * @tparam To 
   * @tparam From 
   * @param value 
   * @return 
   */
  template<typename To, typename From>
  [[nodiscard]] constexpr To bit_cast(From&& value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr T byteswap(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr bool has_single_bit(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr T bit_ceil(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr T bit_floor(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr int32_t bit_width(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @param shift 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr T rotl(const T value, const int32_t shift);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @param shift 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr T rotr(const T value, const int32_t shift);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr int32_t countl_zero(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr int32_t countl_one(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr int32_t countr_zero(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr int32_t countr_one(const T value);

  /**
   * @brief TODO
   * @tparam T 
   * @param value 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr int32_t popcount(const T value);

  /**************************************************************************************************
   * @section Non-Standard Bit-Manipulation Utilities
   **************************************************************************************************/

  template<typename T>
  inline constexpr size_t bit_size{sizeof(T) * TI_CHAR_BIT};

  // Move below functions to a different file?

  /**
   * @brief TODO
   * @tparam T 
   * @param base 
   * @param exp 
   * @return 
   */
  template<typename T>
  [[nodiscard]] constexpr T pow2(const T base, const int32_t exp);

  /**
   * @brief TODO
   * @tparam T 
   * @param exp 
   * @return 
   */
  template<typename T = uint32_t>
  [[nodiscard]] constexpr T pow2(const int32_t exp);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename To, typename From>
  constexpr To bit_cast(From&& value) {
    static_assert(sizeof(To) == sizeof(From), 
        "Size of 'To' must equal size of 'From'.");
    static_assert(is_trivially_copyable_v<To>,
        "'To' must be trivially copyable.");
    static_assert(is_trivially_copyable_v<From>,
        "'From' must be trivially copyable.");
    return TI_BUILTIN_BIT_CAST(To, From, forward<From>(value));
  }

  template<typename T>
  constexpr T byteswap(const T value) {
    static_assert(is_integral_v<T>, "'T' must be an integral type.");
    if constexpr (sizeof(T) > 1) {
      using Ut = make_unsigned_t<T>;
      Ut result{0};
      const Ut u_value{numeric_cast<Ut>(value)};
      constexpr Ut byte_mask{create_mask<Ut>(0, TI_CHAR_BIT)};
      for (int32_t i{0}; i < bit_size<T>; i += TI_CHAR_BIT) {
        result |= ((u_value & (byte_mask << i)) >> i) << (bit_size<T> - i);
      }
      return numeric_cast<T>(result);
    } else {
      return value;
    }
  }

  template<typename T>
  constexpr bool has_single_bit(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    #if TI_HAS_BUILTIN_POPCOUNT
      return TI_BUILTIN_POPCOUNT(T, value) == 1;
    #else
      return value && !(value & (value - 1));
    #endif
  }

  template<typename T>
  constexpr T bit_ceil(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    if (value <= 1) { return 1; }
    if constexpr (is_same_v<T, decltype(+value)>) {
      return T{1} << bit_width(T{value - 1});
    } else {
      using Plim = numeric_limits<unsigned>;
      using Tlim = numeric_limits<T>;
      constexpr int32_t ovf_offset{Plim::digits - Tlim::digits};
      return static_cast<T>((unsigned{1} << bit_width(T{value - 1}) + 
          ovf_offset) >> ovf_offset);
    }
  }

  template<typename T>
  constexpr int32_t bit_floor(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integral type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    if (value == 0) { return 0; }
    return T{1} << (bit_width(value) - 1);
  }

  template<typename T>
  constexpr int32_t bit_width(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    using Tlim = numeric_limits<T>;
    return Tlim::digits - countl_zero(value);
  }

  template<typename T>
  constexpr T rotl(const T value, const int32_t shift) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    constexpr int32_t digits{numeric_limits<T>::digits};
    const int32_t wrap_length{shift % digits};
    if (wrap_length > 0) {
      const T wrap_value{static_cast<T>(digits - wrap_length)};
      return (value << wrap_length) | (value >> wrap_value);
    } else if (wrap_length < 0) {
      return rotr(value, -wrap_length);
    } else {
      return value;
    }
  }

  template<typename T>
  constexpr T rotr(const T value, const int32_t shift) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    constexpr int32_t digits{numeric_limits<T>::digits};
    const int32_t wrap_length{shift % digits};
    if (wrap_length > 0) {
      const T wrap_value{static_cast<T>(digits - wrap_length)};
      return (value >> wrap_length) | (value << wrap_value);
    } else if (wrap_length < 0) {
      return rotl(value, -wrap_length);
    } else {
      return value;
    }
  }

  template<typename T>
  constexpr int32_t countl_zero(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    return TI_BUILTIN_CTZ(T, value);
  }

  template<typename T>
  constexpr int32_t countl_one(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    int32_t count{0};
    for (int32_t i{bit_size<T> - 1}; i >= 0; --i) {
      if ((value & (T{1} << i)) == 0) { break; }
      ++count;
    }
    return count;
  }

  template<typename T>
  constexpr int32_t countr_zero(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    return TI_BUILTIN_CLZ(T, value);
  }

  template<typename T>
  constexpr int32_t countr_one(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    int32_t count{0};
    for (int32_t i{0}; i < bit_size<T>; ++i) {
      if ((value & (T{1} << i)) == 0) { break; }
      ++count;
    }
    return count;
  }

  template<typename T>
  constexpr int32_t popcount(const T value) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    return TI_BUILTIN_POPCOUNT(T, value);
  }

  template<typename T>
  constexpr T pow2(const T base, const int32_t exp) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    if (exp < 0) { sys_error('Exponent is out of range.'); }
    return base << exp;
  }

  template<typename T = uint32_t>
  constexpr T pow2(const int32_t exp) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    if (exp < 0) { sys_error("Exponent is out of range."); }
    return T{1} << exp;
  }

  /// @endinternal

} // namespace ti::util