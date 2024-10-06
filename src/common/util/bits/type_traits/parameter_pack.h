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
 * @file common/util/bits/type_traits/parameter_pack.h 
 * @authors Aaron McBride 
 * @brief Contains type traits/utilities for parameter packs.
 */

#pragma once
#include "common/util/cstdint.h"

namespace ti::util {

  /************************************************************************************************
   * @internal Implementation
   ***********************************************************************************************/

  template<size_t... Is>
  struct index_sequence_t;

  namespace {

    // Implementation of 'type_index_v'.
    template<size_t index, typename T, typename... U>
    struct IndexTypeImpl {
      using Type = typename IndexTypeImpl<index - 1, U...>::Type;
    };

    template<typename T, typename... U>
    struct IndexTypeImpl<0, T, U...> {
      using Type = T;
    };

    // Implementation of 'make_index_sequence'
    template<size_t index, size_t... Is>
    struct MakeSeqImpl {
      using Type = typename MakeSeqImpl<index - 1, index, Is...>::Type;
    };

    template<size_t... Is>
    struct MakeSeqImpl<0, Is...> {
      using Type = index_sequence_t<0, Is...>;
    };

  } // namespace annoymous

  /// @endinternal

  /************************************************************************************************
   * @section Type Pack Indexing
   ***********************************************************************************************/

  /**
   * @brief Template type alias that evaluates to the type at a specific index
   *        in the given parameter pack.
   * @tparam index The index of the target type in the parameter pack (size_t NTTP). 
   * @tparam ...T The parameter pack to index into.
   */
  template<size_t index, typename... T>
  using index_type_t = typename IndexTypeImpl<index, T...>::Type;

  /**
   * @brief Template size_t value that evaluates to the index of the first
   *        occurance of a specific type in the given parameter pack.
   * @tparam T The type to get the index of.
   * @tparam ...U The parameter pack to search in.
   */
  template<typename T, typename... U>
  inline constexpr size_t type_index_v{0};

  template<typename T, typename... U>
  inline constexpr size_t type_index_v<T, T, U...>{0};

  template<typename T, typename U, typename... V>
  inline constexpr size_t type_index_v<T, U, V...>{
      1 + type_index_v<T, V...>};

  /**
   * @brief Template bool value that evaluates to true if a specific type is
   *        contained in the given parameter pack, or false otherwise.
   * @tparam T The type to search for.
   * @tparam ...U The parameter pack to search through.
   */
  template<typename T, typename... U>
  inline constexpr bool contains_type_v{
      type_index_v<T, U...> < sizeof...(U)};

  /************************************************************************************************
   * @section Value Pack Indexing
   ***********************************************************************************************/

  /**
   * @brief Template value that evaluates to the value at a specific index in
   *        the given variadic NTTP value pack.
   * @tparam index The index of the target value in the value pack (size_t NTTP).
   * @tparam ...value_pack The variadic NTTP value pack to index into.
   */
  template<size_t index, auto value, auto... value_pack>
  inline constexpr auto index_value_v{index_value_v<index - 1, value_pack...>};

  template<auto value, auto... value_pack>
  inline constexpr auto index_value_v<0, value, value_pack...>{value};

  /**
   * @brief Template size_t value that evaluates to the index of the first
   *        occurance of a specific value in the given variadic pack of NTTP values.
   * @tparam value The value to get the index of.
   * @tparam ...value_pack The variadic pack of NTTP values to search through.
   */
  template<auto value, auto... value_pack>
  inline constexpr size_t value_index_v{0};

  template<auto value, auto... value_pack>
  inline constexpr size_t value_index_v<value, value, value_pack...>{0};

  template<auto value, auto o_value, auto... value_pack>
  inline constexpr size_t value_index_v<value, o_value, value_pack...>{
      1 + value_index_v<value, value_pack...>};

  /**
   * @brief Template bool value that evaluates to true if a specific value is
   *        contained in the given variadic pack of NTTP values, or false otherwise.
   * @tparam value The value to search for.
   * @tparam ...value_pack The variadic pack of NTTP values to search through.
   */
  template<auto value, auto... value_pack>
  inline constexpr bool contains_value_v{
      value_index_v<value, value_pack...> < sizeof...(value_pack)};

  /************************************************************************************************
   * Value Pack Indexing Traits/Utilities
   ***********************************************************************************************/

  /**
   * @brief Template type that holds a sequence of values..
   * @tparam ...Is A variadic pack of size_t NTTP values.
   */
  template<size_t... Is>
  struct index_sequence_t {
    constexpr explicit index_sequence_t() = default;
  };

  /**
   * @brief Creates an index_sequence_t with the given number of indicies.
   * @tparam N The number of indicies in the index sequence.
   * @returns An index_sequence_t value with @p 'N' indicies.
   */
  template<size_t N>
  [[nodiscard]] constexpr auto make_index_sequence() {
    return typename MakeSeqImpl<N - 1>::Type{};
  }

} // namespace ti::util