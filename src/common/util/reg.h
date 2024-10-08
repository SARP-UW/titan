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
 * @file common/util/reg.h 
 * @authors Aaron McBride 
 * @brief Contains hardware register utilities.
 */

#pragma once
#include "common/env/compiler_interface.h"
#include "common/util/cstdint.h"
#include "common/util/type_traits.h"
#include "common/util/utility.h"
#include "common/util/bit.h"
#include "common/tmp.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Register-Related Utilities
   **************************************************************************************************/

  /**
   * @brief TODO
   * @tparam T 
   * @param pos 
   * @param len 
   * @return 
   */
  template<typename T = uint32_t>
  [[nodiscard]] constexpr T bit_mask(const int32_t pos, const int32_t len);

  /**************************************************************************************************
   * @section Register Value Class
   **************************************************************************************************/

  /**
   * @brief TODO
   * @tparam T 
   * @tparam pos 
   * @tparam len 
   */
  template<typename T, int32_t pos, int32_t len>
  class RegValue {

    public:

      static_assert(pos >= 0, "'pos' cannot be negative.");
      static_assert(len > 0, "'len' cannot be negative.");
      static_assert((len + pos) <= bit_size<T>, "RegValue is out of range of 'T'.");
      static_assert(is_integer_v<T> && is_unsigned_v<T>, "'T' must be an unsigned integer type.");

      using RegType = T; /** @brief TODO */
      using ThisType = RegValue<T, pos, len>; /** @brief TODO */

      static constexpr int32_t position{pos}; /** @brief TODO */
      static constexpr int32_t length{pos}; /** @brief TODO */
      static constexpr T mask{bit_mask<T>(pos, len)}; /** @brief TODO */

      /**
       * @brief TODO
       * @param address 
       * @return 
       */
      [[nodiscard]] static constexpr ThisType* at(const uintptr_t address);

      /**
       * @brief TODO
       * @tparam U 
       * @param pointer 
       * @return 
       */
      template<typename U>
      [[nodiscard]] static constexpr ThisType* at(U* pointer);

      /**
       * @brief TODO
       */
      constexpr RegValue() = delete;
      constexpr RegValue(const RegValue&) = delete;

      /**
       * @brief TODO
       * @tparam U 
       * @tparam o_pos 
       * @tparam o_len 
       * @param other 
       * @return 
       */
      template<typename U, int32_t o_pos, int32_t o_len>
      constexpr ThisType& operator=(const RegValue<U, o_pos, o_len>& other);

      /**
       * @brief TODO
       * @return 
       */
      [[nodiscard]] constexpr T* get_reg() const;

      /**
       * @brief TODO
       * @tparam U 
       * @param value 
       * @return 
       */
      template<typename U>
      constexpr bool write(const U value);

      /**
       * @brief TODO
       * @return 
       */
      [[nodiscard]] constexpr T read() const;

      /**
       * @brief TODO
       * @tparam U 
       * @param value 
       * @return 
       */
      template<typename U>
      constexpr bool operator=(const U value);

      /**
       * @brief TODO
       */
      [[nodiscard]] constexpr operator T() const;

      /**
       * @brief TODO
       */
      constexpr void set();

      /**
       * @brief TODO
       * @return 
       */
      [[nodiscard]] constexpr bool is_set() const;

      /**
       * @brief TODO
       */
      constexpr void clear();

      /**
       * @brief TODO
       * @return 
       */
      [[nodiscard]] constexpr bool is_clear() const;

    private:

      T reg_;

  }; // class RegValue

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @tparam l_pos 
   * @tparam r_pos 
   * @tparam l_length 
   * @tparam r_length 
   * @param lhs 
   * @param rhs 
   * @return 
   */
  template<typename Tl, typename Tr, int32_t l_pos, 
      int32_t r_pos, int32_t l_length, int32_t r_length>
  [[nodiscard]] constexpr bool operator==(
      const RegValue<Tl, l_pos, l_length>& lhs,
      const RegValue<Tr, r_pos, r_length>& rhs);

  /**
   * @brief TODO
   * @tparam Tl 
   * @tparam Tr 
   * @tparam l_pos 
   * @tparam r_pos 
   * @tparam l_length 
   * @tparam r_length 
   * @param lhs 
   * @param rhs 
   * @return 
   */
  template<typename Tl, typename Tr, int32_t l_pos, 
      int32_t r_pos, int32_t l_length, int32_t r_length>
  [[nodiscard]] constexpr bool operator!=(
      const RegValue<Tl, l_pos, l_length>& lhs,
      const RegValue<Tr, r_pos, r_length>& rhs);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename T = uint32_t>
  constexpr T bit_mask(const int32_t pos, const int32_t len) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    if (pos < 0 || len < 0 || (pos + len) > bit_size<T>) {
      sys_error("Mask position and length are out of range.");
    }
    return ((T{1} << len) - T{1}) << pos;
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr RegValue<T, pos, len>* RegValue<T, pos, len>::at(
      const uintptr_t address) {
    return reinterpret_cast<ThisType*>(address);
  }

  template<typename T, int32_t pos, int32_t len>
  template<typename U>
  constexpr RegValue<T, pos, len>* RegValue<T, pos, len>::at(
      U* pointer) {
    return reinterpret_cast<ThisType*>(pointer);
  }

  template<typename T, int32_t pos, int32_t len>
  template<typename U, int32_t o_pos, int32_t o_len>
  constexpr RegValue<T, pos, len>& RegValue<T, pos, len>::operator=(
      const RegValue<U, o_pos, o_len>& other) {
    if likely(this != &other) {
      this->write(other.read());
    }
    return *this;
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr T* RegValue<T, pos, len>::get_reg() const {
    return &reg_;
  }

  template<typename T, int32_t pos, int32_t len>
  template<typename U>
  constexpr bool RegValue<T, pos, len>::write(const U value) {
    static_assert(is_integral_v<U>, "'U' must be an integral type.");
    if constexpr (!is_bool_v<U> && len > 1) {
      using Ut = make_unsigned_t<U>;
      if (!in_range<Ut>(value)) { return false; }
      const Ut u_value{static_cast<Ut>(value)};
      if constexpr (numeric_limits<T>::digits > len) {
        if (bit_width(u_value) > len) { return false; }
      }
      reg_ = (reg_ & ~mask) | (u_value << pos);
    } else {
      if constexpr (len <= 1) {
        if (value != 0 && value != 1) { return false; }
      }
      value ? set() : clear();
    }
    return true;
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr T RegValue<T, pos, len>::read() const {
    if constexpr (len > 1) {
      return (reg_ & mask) >> pos;
    } else {
      return is_clear();
    }
  }

  template<typename T, int32_t pos, int32_t len>
  template<typename U>
  constexpr bool RegValue<T, pos, len>::operator=(
      const U value) {
    return write(value);
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr RegValue<T, pos, len>::operator T() const {
    return read();
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr void RegValue<T, pos, len>::set() {
    reg_ = (reg_ | mask);
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr bool RegValue<T, pos, len>::is_set() const {
    return (reg_ & mask) == mask;
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr void RegValue<T, pos, len>::clear() {
    reg_ = (reg_ & ~mask);
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr bool RegValue<T, pos, len>::is_clear() const {
    return (reg_ & mask) == 0;
  }

  template<typename Tl, typename Tr, int32_t l_pos, 
      int32_t r_pos, int32_t l_length, int32_t r_length>
  constexpr bool operator==(const RegValue<Tl, l_pos, l_length>& lhs,
      const RegValue<Tr, r_pos, r_length>& rhs) {
    return lhs.read() == rhs.read();
  }

  template<typename Tl, typename Tr, int32_t l_pos, 
      int32_t r_pos, int32_t l_length, int32_t r_length>
  constexpr bool operator!=(const RegValue<Tl, l_pos, l_length>& lhs,
      const RegValue<Tr, r_pos, r_length>& rhs) {
    return !(lhs == rhs);
  }

  /// @endinternal

} // namespace ti::util