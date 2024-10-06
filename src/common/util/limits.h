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
    [[nodiscard]] constexpr T max_to_min(T&& max) {
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
    [[nodiscard]] constexpr auto s_to_u_max(T&& s_max) {
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
    [[nodiscard]] constexpr int get_digits2(const T t_max) {
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
    
    static_assert(!sizeof(T), "TITAN ERROR: numeric_limits "
        + "is not implemented for the given type.");

    /** @brief Returns the maximum value representable in this type. */
    static constexpr T max() { return 0; } 

    /** @brief Returns the minimum value representable in this type. */
    static constexpr T min() { return 0; }       
    
    /** @brief The maximum number of full base 10 digits representable in this type. */
    static constexpr int digits10{0};

    /** @brief The maximum number of full base 2 digits representable in this type. */
    static constexpr int digits2{0};

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

    using type = signed char;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr signed char max() { return TI_CHAR_MAX; }
    [[nodiscard]] static constexpr signed char min() { return max_to_min<type>(TI_CHAR_MAX); }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};
  };

  /** @brief numeric_limit specialization for unsigned char. */
  template<>
  struct numeric_limits<unsigned char> {

    using type = unsigned char;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr unsigned char max() { return s_to_u_max<type>(TI_CHAR_MAX); }
    [[nodiscard]] static constexpr unsigned char min() { return 0; }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};
    
    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};
    
  };

  /** @brief numeric_limit specialization for signed short int. */
  template<>
  struct numeric_limits<signed short> {

    using type = signed short;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr signed short max() { return TI_SHORT_MAX; }
    [[nodiscard]] static constexpr signed short min() { return max_to_min<type>(TI_SHORT_MAX); }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  /** @brief numeric_limit specialization for unsigned short int. */
  template<>
  struct numeric_limits<unsigned short> {

    using type = unsigned short;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr unsigned short max() { return s_to_u_max<type>(TI_SHORT_MAX); }
    [[nodiscard]] static constexpr unsigned short min() { return 0; }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  /** @brief numeric_limit specialization for signed int. */
  template<>
  struct numeric_limits<signed int> {

    using type = signed int;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr signed int max() { return TI_INT_MAX; }
    [[nodiscard]] static constexpr signed int min() { return max_to_min<type>(TI_INT_MAX); }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  /** @brief numeric_limit specialization for unsigned int. */
  template<>
  struct numeric_limits<unsigned int> {

    using type = unsigned int;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr unsigned int max() { return s_to_u_max<type>(TI_INT_MAX); }
    [[nodiscard]] static constexpr unsigned int min() { return 0; }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  /** @brief numeric_limit specialization for signed long int. */
  template<>
  struct numeric_limits<signed long> {

    using type = signed long;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr signed long max() { return TI_LONG_MAX; }
    [[nodiscard]] static constexpr signed long min() { return max_to_min<type>(TI_LONG_MAX); }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  /** @brief numeric_limit specialization for unsigned long int. */
  template<>
  struct numeric_limits<unsigned long> {

    using type = unsigned long;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr unsigned long max() { return s_to_u_max<type>(TI_LONG_MAX); }
    [[nodiscard]] static constexpr unsigned long min() { return 0; }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  /** @brief numeric_limit specialization for signed long long int. */
  template<>
  struct numeric_limits<signed long long> {

    using type = signed long long;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr signed long long max() { return TI_LONG_LONG_MAX; }
    [[nodiscard]] static constexpr signed long long min() { return max_to_min<type>(TI_LONG_LONG_MAX); }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{true};
    static constexpr bool is_unsigned{false};

  };

  /** @brief numeric_limit specialization for unsigned long long int. */
  template<>
  struct numeric_limits<unsigned long long> {

    using type = unsigned long long;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr unsigned long long max() { return s_to_u_max<type>(TI_LONG_LONG_MAX); }
    [[nodiscard]] static constexpr unsigned long long min() { return 0; }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{get_digits10(this_type::max())};
    static constexpr int digits2{get_digits2(this_type::max())};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

  /** @brief numeric_limit specialization for bool. */
  template<>
  struct numeric_limits<bool> {

    using type = bool;
    using this_type = numeric_limits<type>;

    [[nodiscard]] static constexpr bool max() { return true; }
    [[nodiscard]] static constexpr bool min() { return false; }
    [[nodiscard]] static constexpr signed char lowest() { return min(); }

    static constexpr int digits10{0};
    static constexpr int digits2{1};

    static constexpr bool is_signed{false};
    static constexpr bool is_unsigned{true};

  };

} // namespace ti::util