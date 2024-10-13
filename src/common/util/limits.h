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
 * @file common/util/limits.h 
 * @authors Aaron McBride 
 * @brief Contains all implemented facilities and extensions to the
 *        std limits library.
 */

#pragma once
#include "common/env/compiler_interface.h"

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    // Converts a type's max value to it's min value.
    template<typename T>
    [[nodiscard]] constexpr T max_to_min(const T max) {
      if constexpr (TI_TWO_COMPLEMENT) {
        return (-max) - T{1};
      } else if constexpr (TI_ONE_COMPLEMENT) {
        return -(max - T{1});
      } else if constexpr (TI_SIGN_MAGNITUDE) {
        return -max;
      }
    }

    // Converts signed type's max into equivalent unsigned type's max.
    template<typename T>
    [[nodiscard]] constexpr auto s_to_u_max(const T s_max) {
      if constexpr (TI_TWO_COMPLEMENT || TI_SIGN_MAGNITUDE) {
        return (s_max * T{2}) + T{1};
      } else if constexpr (TI_ONE_COMPLEMENT) {
        return (s_max * T{2}) - T{1};
      }
    }

    // Gets the max base 10 digits in a type.
    template<typename T>
    [[nodiscard]] constexpr int get_digits10(const T t_max) {
      int current_digits{0};
      T current_value{1};
      while (current_value <= (t_max / 10)) {
        current_value *= 10;
        ++current_digits;
      }
      return current_digits;
    }

    // Gets the max base 2 digits in a type.
    template<typename T>
    [[nodiscard]] constexpr int get_digits(const T t_max) {
      int current_digits{1};
      T current_value{1};
      while (current_value <= (t_max / 2)) {
        current_value *= 2;
        ++current_digits;
      }
      return current_digits;
    }

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section numeric_limits Base Template Definition
   **************************************************************************************************/

  /**
   * @brief Type which provides information about the numeric limits of a
   *        specific numeric type.
   * @tparam T The numeric type to get limits for.
   */
  template<typename T>
  struct numeric_limits {
    
    static_assert(!sizeof(T), "TITAN ERROR: numeric_limits is not implemented for the given type.");

    /** @brief Returns the maximum value representable in this type. */
    static constexpr T max() { return 0; } 

    /** @brief Returns the minimum value representable in this type. */
    static constexpr T min() { return 0; }       
    
    /** @brief The maximum number of full base 10 digits representable in this type. */
    static constexpr int digits10{0};

    /** @brief The maximum number of full base 2 digits representable in this type. */
    static constexpr int digits{0};

    /** @brief True if this type is signed, or false otherwise. */
    static constexpr bool is_signed{false};

    /** @brief True if this type is unsigned, or false otherwise. */
    static constexpr bool is_unsigned{false}; 
    
  };

  /**************************************************************************************************
   * @section numeric_limits Specializations
   **************************************************************************************************/

  /** @brief numeric_limit specialization for signed char. */
  template<>
  struct numeric_limits<signed char> {

    using Type = signed char;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return TI_CHAR_MAX; }
    [[nodiscard]] static constexpr Type min() { return max_to_min<Type>(TI_CHAR_MAX); }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(TI_CHAR_MAX)};
    static constexpr int digits{get_digits(TI_CHAR_MAX)};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const signed char> : numeric_limits<signed char> {};
  template<> struct numeric_limits<volatile signed char> : numeric_limits<signed char> {};
  template<> struct numeric_limits<const volatile signed char> : numeric_limits<signed char> {};

  /** @brief numeric_limit specialization for unsigned char. */
  template<>
  struct numeric_limits<unsigned char> {

    using Type = unsigned char;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return s_to_u_max<Type>(TI_CHAR_MAX); }
    [[nodiscard]] static constexpr Type min() { return 0; }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(s_to_u_max<Type>(TI_CHAR_MAX))};
    static constexpr int digits{get_digits(s_to_u_max<Type>(TI_CHAR_MAX))};
    
    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};
    
  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const unsigned char> : numeric_limits<unsigned char> {};
  template<> struct numeric_limits<volatile unsigned char> : numeric_limits<unsigned char> {};
  template<> struct numeric_limits<const volatile unsigned char> : numeric_limits<unsigned char> {};

  /** @brief numeric_limit specialization for signed short int. */
  template<>
  struct numeric_limits<signed short> {

    using Type = signed short;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return TI_SHORT_MAX; }
    [[nodiscard]] static constexpr Type min() { return max_to_min<Type>(TI_SHORT_MAX); }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(TI_SHORT_MAX)};
    static constexpr int digits{get_digits(TI_SHORT_MAX)};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const signed short> : numeric_limits<signed short> {};
  template<> struct numeric_limits<volatile signed short> : numeric_limits<signed short> {};
  template<> struct numeric_limits<const volatile signed short> : numeric_limits<signed short> {};

  /** @brief numeric_limit specialization for unsigned short int. */
  template<>
  struct numeric_limits<unsigned short> {

    using Type = unsigned short;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return s_to_u_max<Type>(TI_SHORT_MAX); }
    [[nodiscard]] static constexpr Type min() { return 0; }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(s_to_u_max<Type>(TI_SHORT_MAX))};
    static constexpr int digits{get_digits(s_to_u_max<Type>(TI_SHORT_MAX))};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const unsigned short> : numeric_limits<unsigned short> {};
  template<> struct numeric_limits<volatile unsigned short> : numeric_limits<unsigned short> {};
  template<> struct numeric_limits<const volatile unsigned short> : numeric_limits<unsigned short> {};

  /** @brief numeric_limit specialization for signed int. */
  template<>
  struct numeric_limits<signed int> {

    using Type = signed int;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return TI_INT_MAX; }
    [[nodiscard]] static constexpr Type min() { return max_to_min<Type>(TI_INT_MAX); }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(TI_INT_MAX)};
    static constexpr int digits{get_digits(TI_INT_MAX)};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const signed int> : numeric_limits<signed int> {};
  template<> struct numeric_limits<volatile signed int> : numeric_limits<signed int> {};
  template<> struct numeric_limits<const volatile signed int> : numeric_limits<signed int> {};

  /** @brief numeric_limit specialization for unsigned int. */
  template<>
  struct numeric_limits<unsigned int> {

    using Type = unsigned int;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return s_to_u_max<Type>(TI_INT_MAX); }
    [[nodiscard]] static constexpr Type min() { return 0; }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(s_to_u_max<Type>(TI_INT_MAX))};
    static constexpr int digits{get_digits(s_to_u_max<Type>(TI_INT_MAX))};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const unsigned int> : numeric_limits<unsigned int> {};
  template<> struct numeric_limits<volatile unsigned int> : numeric_limits<unsigned int> {};
  template<> struct numeric_limits<const volatile unsigned int> : numeric_limits<unsigned int> {};

  /** @brief numeric_limit specialization for signed long int. */
  template<>
  struct numeric_limits<signed long> {

    using Type = signed long;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return TI_LONG_MAX; }
    [[nodiscard]] static constexpr Type min() { return max_to_min<Type>(TI_LONG_MAX); }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(TI_LONG_MAX)};
    static constexpr int digits{get_digits(TI_LONG_MAX)};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const signed long> : numeric_limits<signed long> {};
  template<> struct numeric_limits<volatile signed long> : numeric_limits<signed long> {};
  template<> struct numeric_limits<const volatile signed long> : numeric_limits<signed long> {};

  /** @brief numeric_limit specialization for unsigned long int. */
  template<>
  struct numeric_limits<unsigned long> {

    using Type = unsigned long;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return s_to_u_max<Type>(TI_LONG_MAX); }
    [[nodiscard]] static constexpr Type min() { return 0; }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(s_to_u_max<Type>(TI_LONG_MAX))};
    static constexpr int digits{get_digits(s_to_u_max<Type>(TI_LONG_MAX))};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const unsigned long> : numeric_limits<unsigned long> {};
  template<> struct numeric_limits<volatile unsigned long> : numeric_limits<unsigned long> {};
  template<> struct numeric_limits<const volatile unsigned long> : numeric_limits<unsigned long> {};

  /** @brief numeric_limit specialization for signed long long int. */
  template<>
  struct numeric_limits<signed long long> {

    using Type = signed long long;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return TI_LONG_LONG_MAX; }
    [[nodiscard]] static constexpr Type min() { return max_to_min<Type>(TI_LONG_LONG_MAX); }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(TI_LONG_LONG_MAX)};
    static constexpr int digits{get_digits(TI_LONG_LONG_MAX)};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const signed long long> : numeric_limits<signed long long> {};
  template<> struct numeric_limits<volatile signed long long> : numeric_limits<signed long long> {};
  template<> struct numeric_limits<const volatile signed long long> : numeric_limits<signed long long> {};

  /** @brief numeric_limit specialization for unsigned long long int. */
  template<>
  struct numeric_limits<unsigned long long> {

    using Type = unsigned long long;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return s_to_u_max<Type>(TI_LONG_LONG_MAX); }
    [[nodiscard]] static constexpr Type min() { return 0; }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{get_digits10(s_to_u_max<Type>(TI_LONG_LONG_MAX))};
    static constexpr int digits{get_digits(s_to_u_max<Type>(TI_LONG_LONG_MAX))};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const unsigned long long> : numeric_limits<unsigned long long> {};
  template<> struct numeric_limits<volatile unsigned long long> : numeric_limits<unsigned long long> {};
  template<> struct numeric_limits<const volatile unsigned long long> : numeric_limits<unsigned long long> {};

  /** @brief numeric_limit specialization for bool. */
  template<>
  struct numeric_limits<bool> {

    using Type = bool;
    using ThisType = numeric_limits<Type>;

    [[nodiscard]] static constexpr Type max() { return true; }
    [[nodiscard]] static constexpr Type min() { return false; }
    [[nodiscard]] static constexpr Type lowest() { return min(); }

    static constexpr int digits10{0};
    static constexpr int digits{1};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  // Specializations for cv qualified types.
  template<> struct numeric_limits<const bool> : numeric_limits<bool> {};
  template<> struct numeric_limits<volatile bool> : numeric_limits<bool> {};
  template<> struct numeric_limits<const volatile bool> : numeric_limits<bool> {};

} // namespace ti::util