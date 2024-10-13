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
#include "common/util/error_code.h"
#include "common/util/result.h"
#include "common/util/utility.h"
#include "common/util/bit.h"
#include "common/tmp.h"

namespace ti::util {

  /**************************************************************************************************
   * @section Register-Related Utilities
   **************************************************************************************************/

  /**
   * @brief Creates a bit mask of consecutive set bits.
   * @tparam T The unsigned integral type of the returned bit mask.
   * @param pos The position of the first set bit in the mask (from the lsb).
   * @param len The number of consecutive set bits in the mask.
   * @returns - A bit mask with @p 'len' set bits starting at @p 'pos' 
   *          bits from the lsb.
   * @returns - ErrorCode::out_of_range if @p 'pos' or @p 'len' are less then 0,
   *            or if the @p 'pos' + @p 'len' are greater then the bit-width of @p 'T'.
   */
  template<typename T = uint32_t>
  [[nodiscard]] constexpr Result<T, ErrorCode> bit_mask(const int32_t pos, const int32_t len);

  /**************************************************************************************************
   * @section Register Value Class
   **************************************************************************************************/

  /**
   * @brief Represents a value that occupies a specific range of bits within a
   *        larger register (unsigned integral type).
   * @tparam T The unsigned integral type of the register.
   * @tparam pos The position of the value within the register (from the lsb).
   * @tparam len The number of bits occupied by the value within the register.
   */
  template<typename T, int32_t pos, int32_t len>
  class RegValue {

    public:

      // Ensure given parameters are valid.
      static_assert(pos >= 0, "'pos' cannot be negative.");
      static_assert(len > 0, "'len' cannot be negative.");
      static_assert((len + pos) <= bit_size<T>, "RegValue is out of range of 'T'.");
      static_assert(is_integer_v<T> && is_unsigned_v<T>, "'T' must be an unsigned integer type.");

      /** @brief Denotes the register type. */
      using RegType = T;

      /** @brief Denotes the type of this RegValue object. */
      using ThisType = RegValue<T, pos, len>;

      /** @brief Denotes the position of the value within the register (from the lsb). */
      static constexpr int32_t position{pos};

      /** @brief Denotes the number of bits occupied by this value within the register. */
      static constexpr int32_t length{pos};

      /**
       * @brief Gets a pointer to a RegValue object at a specific address.
       * @param address The address to use the RegValue object at.
       * @returns A pointer to a RegValue object at @p 'address'.
       */
      [[nodiscard]] static ThisType* at(const uintptr_t address);

      /**
       * @brief Gets a pointer to a RegValue object at the location of 
       *        a pointer.
       * @tparam U The type of the pointer.
       * @param pointer The pointer that denotes the location of the register.
       * @returns A pointer to a RegValue object at the location of @p 'pointer'.
       */
      template<typename U>
      [[nodiscard]] static ThisType* at(U* pointer);

      /**
       * @brief Cannot instantiate RegValue objects, must be used through 
       *        pointers to their target registers.
       */
      constexpr RegValue() = delete;

      /// @overload constexpr RegValue() = delete;
      constexpr RegValue(const RegValue&) = delete;

      /// @overload constexpr RegValue() = delete;
      ~RegValue() = delete;

      /**
       * @brief Sets the value at this RegValue's target location to the value 
       *        stored in annother RegValue's target location.
       * @tparam U The unsigned integral type of the other object's register.
       * @tparam o_pos The position of the other object's value.
       * @tparam o_len The length occupied by the other object's value.
       * @param other A pointer to the RegValue object to copy.
       * @returns - Valid{} if the value of @p 'other' was successfully copied.
       * @returns - ErrorCode::out_of_range if the value of @p 'other' was too
       *          large to losslessly represent in this RegValue's location.
       * @returns - ErrorCode::failed_precondition if the @p 'other' is the same
       *          RegValue instance as this.
       */
      template<typename U, int32_t o_pos, int32_t o_len>
      Result<monostate_t, ErrorCode> operator=(const RegValue<U, o_pos, o_len>*& other);

      /**
       * @brief Gets a pointer register where this RegValue is located.
       * @returns A pointer of type @p 'T' to the location where this RegValue's 
       *          is located (in memory - i.e. location of *this ptr).
       */
      [[nodiscard]] T* get_reg() const;

      /**
       * @brief Gets the bit mask that represents the bits occupied by this RegValue
       *        in it's register.
       * @returns A bit mask of type @p 'T' with @p 'len' set bits starting at 
       *          @p 'pos' bits from the lsb.
       */
      [[nodiscard]] constexpr T get_mask() const;
      
      /**
       * @brief Writes a value to the current register at this RegValue's location.
       * @tparam U The integral type of the value to write.
       * @param value The value to write to the register.
       * @returns - Valid{} if @p 'value' was successfully written to the register.
       * @returns - ErrorCode::out_of_range if @p 'value' is to large to represent
       *          in this RegValue's bit-width.
       * @returns - ErrorCode::out_of_range if @p 'value' is less then 0.
       */
      template<typename U>
      Result<monostate_t, ErrorCode> operator=(const U value);

      /**
       * @brief Implicitly Casts this RegValue object to the value stored in it's 
       *        register at the target location - @p 'len' bits, @p 'pos' from the lsb.
       */
      [[nodiscard]] operator T() const;

      /**
       * @brief Sets all bits occupied by this RegValue to 1.
       */
      void set();

      /**
       * @brief Determines if every bit occupied by this RegValue is set.
       * @returns True if all bits occupied by this RegValue are equal to 1, 
       *          or false otherwise.
       */
      [[nodiscard]] bool is_set() const;

      /**
       * @brief Clears all bits occupied by this RegValue to 0.
       */
      void clear();

      /**
       * @brief Determines if every bit occupied by this RegValue are clear.
       * @returns True if all bits occupied by this RegValue are equal to 0,
       *          or false otherwise.
       */
      [[nodiscard]] bool is_clear() const;

    private:

      static constexpr T mask_{bit_mask<T>(pos, len)};

      T reg_;

  }; // class RegValue

  /**
   * @brief Compares the values stored at two RegValue objects' locations
   *        for equality.
   * @tparam Tl The unsigned integral type of the left-hand RegValue's register.
   * @tparam Tr The unsigned integral type of the right-hand RegValue's register.
   * @tparam l_pos The position of the left-hand RegValue's location. 
   * @tparam r_pos The position of the right-hand RegValue's location.
   * @tparam l_length The length of the left-hand RegValue's location.
   * @tparam r_length The length of the right-hand RegValue's location.
   * @param lhs A pointer to the left-hand RegValue object.
   * @param rhs A pointer to the right-hand RegValue object.
   * @returns True if the value stored at the location of @p 'lhs' is equal to
   *          the value stored at the location of @p 'rhs', or false otherwise.
   */
  template<typename Tl, typename Tr, int32_t l_pos, 
      int32_t r_pos, int32_t l_length, int32_t r_length>
  [[nodiscard]] bool operator==(const RegValue<Tl, l_pos, l_length>*& lhs,
      const RegValue<Tr, r_pos, r_length>*& rhs);

  /**
   * @brief Compares the values stored at two RegValue objects' locations
   *        for inequality.
   * @tparam Tl The unsigned integral type of the left-hand RegValue's register.
   * @tparam Tr The unsigned integral type of the right-hand RegValue's register.
   * @tparam l_pos The position of the left-hand RegValue's location.
   * @tparam r_pos The position of the right-hand RegValue's location.
   * @tparam l_length The length of the left-hand RegValue's location.
   * @tparam r_length The length of the right-hand RegValue's location.
   * @param lhs A pointer to the left-hand RegValue object.
   * @param rhs A pointer to the right-hand RegValue object.
   * @returns True if the value stored at the location of @p 'lhs' is not equal to
   *          the value stored at the location of @p 'rhs', or false otherwise.
   */
  template<typename Tl, typename Tr, int32_t l_pos, 
      int32_t r_pos, int32_t l_length, int32_t r_length>
  [[nodiscard]] bool operator!=(const RegValue<Tl, l_pos, l_length>& lhs,
      const RegValue<Tr, r_pos, r_length>& rhs);

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  template<typename T = uint32_t>
  constexpr Result<T, ErrorCode> bit_mask(const int32_t pos, const int32_t len) {
    static_assert(is_integer_v<T>, "'T' must be an integer type.");
    static_assert(is_unsigned_v<T>, "'T' must be an unsigned type.");
    if (pos < 0 || len < 0 || (pos + len) > bit_size<T>) {
      return Error{ErrorCode::out_of_range};
    }
    return Valid{((T{1} << len) - T{1}) << pos};
  }

  template<typename T, int32_t pos, int32_t len>
  RegValue<T, pos, len>* RegValue<T, pos, len>::at(
      const uintptr_t address) {
    return reinterpret_cast<ThisType*>(address);
  }

  template<typename T, int32_t pos, int32_t len>
  template<typename U>
  RegValue<T, pos, len>* RegValue<T, pos, len>::at(U* pointer) {
    return reinterpret_cast<ThisType*>(pointer);
  }

  template<typename T, int32_t pos, int32_t len>
  template<typename U, int32_t o_pos, int32_t o_len>
  Result<monostate_t, ErrorCode> RegValue<T, pos, len>::
        operator=(const RegValue<U, o_pos, o_len>*& other) {
    if (unlikely(this == &other)) {
      return Error{ErrorCode::failed_precondition};
    } else {
      return this->write(other.read());
    }
  }

  template<typename T, int32_t pos, int32_t len>
  T* RegValue<T, pos, len>::get_reg() const {
    return &reg_;
  }

  template<typename T, int32_t pos, int32_t len>
  constexpr T RegValue<T, pos, len>::get_mask() const {
    return mask_;
  }

  template<typename T, int32_t pos, int32_t len>
  template<typename U>
  Result<monostate_t, ErrorCode> RegValue<T, pos, len>::operator=(const U value) {
    static_assert(is_integral_v<U>, "'U' must be an integral type.");
    if constexpr (!is_bool_v<U> && len > 1) {
      using Ut = make_unsigned_t<U>;
      if (!in_range<Ut>(value)) { return Error{ErrorCode::out_of_range}; }
      const Ut u_value{static_cast<Ut>(value)};
      if constexpr (numeric_limits<T>::digits > len) {
        if (bit_width(u_value) > len) { return Error{ErrorCode::out_of_range}; }
      }
      reg_ = (reg_ & ~mask_) | (u_value << pos);
    } else {
      if constexpr (len <= 1) {
        if (value != 0 && value != 1) { return Error{ErrorCode::out_of_range}; }
      }
      value ? set() : clear();
    }
    return Valid{};
  }

  template<typename T, int32_t pos, int32_t len>
  RegValue<T, pos, len>::operator T() const {
    if constexpr (len > 1) {
      return (reg_ & mask_) >> pos;
    } else {
      return is_clear();
    }
  }

  template<typename T, int32_t pos, int32_t len>
  void RegValue<T, pos, len>::set() {
    reg_ = (reg_ | mask_);
  }

  template<typename T, int32_t pos, int32_t len>
  bool RegValue<T, pos, len>::is_set() const {
    return (reg_ & mask_) == mask_;
  }

  template<typename T, int32_t pos, int32_t len>
  void RegValue<T, pos, len>::clear() {
    reg_ = (reg_ & ~mask_);
  }

  template<typename T, int32_t pos, int32_t len>
  bool RegValue<T, pos, len>::is_clear() const {
    return (reg_ & mask_) == 0;
  }

  template<typename Tl, typename Tr, int32_t l_pos, 
      int32_t r_pos, int32_t l_length, int32_t r_length>
  bool operator==(const RegValue<Tl, l_pos, l_length>& lhs,
      const RegValue<Tr, r_pos, r_length>& rhs) {
    return lhs.read() == rhs.read();
  }

  template<typename Tl, typename Tr, int32_t l_pos, 
      int32_t r_pos, int32_t l_length, int32_t r_length>
  bool operator!=(const RegValue<Tl, l_pos, l_length>& lhs,
      const RegValue<Tr, r_pos, r_length>& rhs) {
    return !(lhs == rhs);
  }

  /// @endinternal

} // namespace ti::util