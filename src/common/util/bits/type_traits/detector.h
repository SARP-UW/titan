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
 * @file common/util/bits/type_traits/detector.h 
 * @authors Aaron McBride 
 * @brief Contains utilities for detecting SFINAE (detection idiom).
 */

#pragma once

namespace ti::util {

  /**************************************************************************************************
   * @internal Implementation
   **************************************************************************************************/

  namespace {

    template<typename...>
    using void_t = void;

    // Implementation for 'is_detected_v' and 'detected_t'.
    template<typename DefT, template<typename...> typename Trait,
        typename Enable, typename... Args>
    struct DetectorImpl {
      static constexpr bool value{false};
      using Type = DefT;
    };

    template<typename DefT, template<typename...> typename Trait,
        typename Enable, typename... Args>
    struct DetectorImpl<DefT, Trait, void_t<Trait<Args...>>, Args...> {
      static constexpr bool value{true};
      using Type = Trait<Args...>;
    };

  } // namespace annoymous

  /// @endinternal

  /**************************************************************************************************
   * @section SFINAE Detection Utilities
   **************************************************************************************************/

  /**
   * @brief Template bool value that evaluates to true if no substitution failure
   *        occurs when instantiating the given type trait with the given set arguments,
   *        or false otherwise.
   * @tparam Trait A template template parameter that denotes the type trait to test.
   * @tparam ...Args The arguments to attempt instantiation of @p 'Trait' with.
   */
  template<template <typename...> typename Trait, typename... Args>
  static constexpr bool is_detected_v{DetectorImpl<void, Trait, void, Args...>::value};

  /**
   * @brief Template type alias that evaluates to the type of the given type trait when 
   *        instantiated with the given set of arguments if no substitution failure
   *        (SFINAE) occurs, or a default type otherwise.
   * @tparam DefT The default type to evaluate to if a substitution failure (SFINAE) occurs.
   * @tparam Trait A template template parameter that denotes the type trait to test.
   * @tparam ...Args The arguments to attempt instantiation of @p 'Trait' with.
   */
  template<typename DefT, template<typename...> typename Trait, typename... Args>
  using detected_t = typename DetectorImpl<DefT, Trait, void, Args...>::Type;

} // namespace ti::util