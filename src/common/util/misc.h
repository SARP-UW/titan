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
 * @file common/util/misc.h 
 * @authors Aaron McBride 
 * @brief Contains miscellaneous utilities.
 */

#pragma once

namespace ti::util {

  namespace {

    // Bool forward implementation of 'static_for'
    template<typename F, typename T, T max, T idx>
    constexpr bool static_for_bool_impl(F&& fn);

    // Recursive case
    template<typename F, typename T, T max, T idx>
    constexpr bool static_for_bool_impl(F&& fn) {
      return forward<F>(fn)(integral_constant<T, idx>{}) && 
          static_for_impl<F, T, max, idx + 1>(forward<F>(fn));
    }

    // Base case
    template<typename F, typename T, T max>
    constexpr bool static_for_bool_impl<F, T, max, max>(F&& fn) {
      return true;
    }

    // Bool reverse implementation of 'static_for'
    template<typename F, typename T, T max, T idx>
    constexpr bool static_for_bool_rev_impl(F&& fn);

    // Recursive case
    template<typename F, typename T, T max, T idx>
    constexpr bool static_for_bool_rev_impl(F&& fn) {
      return forward<F>(fn)(integral_constant<T, idx>{}) && 
          static_for_impl<F, T, max, idx - 1>(forward<F>(fn));
    }

    // Base case
    template<typename F, typename T, T max>
    constexpr bool static_for_bool_rev_impl<F, T, max, 0>(F&& fn) {
      return forward<F>(fn)(integral_constant<T, 0>{});
    }

    // Forward implementation of 'static_for'
    template<typename F, typename T, T max, T idx>
    constexpr bool static_for_impl(F&& fn);

    // Recursive case
    template<typename F, typename T, T max, T idx>
    constexpr bool static_for_impl(F&& fn) {
      forward<F>(fn)(integral_constant<T, idx>{})
      static_for_impl<F, T, max, idx + 1>(forward<F>(fn));
    }

    // Base case
    template<typename F, typename T, T max>
    constexpr bool static_for_impl<F, T, max, max>(F&& fn) {}

    // Reverse implementation of 'static_for'
    template<typename F, typename T, T max, T idx>
    constexpr bool static_for_rev_impl(F&& fn);

    // Recursive case
    template<typename F, typename T, T max, T idx>
    constexpr bool static_for_rev_impl(F&& fn) {
      forward<F>(fn)(integral_constant<T, idx>{})
      static_for_impl<F, T, max, idx - 1>(forward<F>(fn));
    }

    // Base case
    template<typename F, typename T, T max>
    constexpr bool static_for_rev_impl<F, T, max, 0>(F&& fn) {
      forward<F>(fn)(integral_constant<T, 0>{});
    }

  }

  template<auto N, typename F>
  constexpr auto static_for(F&& fn) {
    using IndexT = decay_t<decltype(N)>;
    if constexpr (is_bool_v<invoke_result_t<F, integral_constant<IndexT, N>>>) {
      return static_for_bool_impl<F, IndexT, N, 0>(forward<F>(fn));
    } else {
      return static_for_impl<F, IndexT, N, 0>(forward<F>(fn));
    }
  }

  template<auto N, typename F>
  constexpr auto reverse_static_for(F&& fn) {
    using IndexT = decay_t<decltype(N)>;
    if constexpr (is_bool_v<invoke_result_t<F, integral_constant<IndexT, N>>>) {
      return static_for_bool_rev_impl<F, IndexT, N, 0>(forward<F>(fn));
    } else {
      return static_for_rev_impl<F, IndexT, N, 0>(forward<F>(fn));
    }
  }

}
