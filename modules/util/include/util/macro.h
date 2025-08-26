/**
 * This file is part of the Titan Project.
 * Copyright (c) 2024 UW SARP
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
 * @file modules/util/include/util/macro.h
 * @authors Aaron McBride
 * @brief Macro utilities.
 */

#pragma once

/**
 * @brief Stringifies the given token.
 * @param x (token) The target token.
 * @returns (string literal) The stringified form of @p [x].
 */
#define TI_STR(x) \
  #x

/**
 * @brief Expands and stringifies the given token.
 * @param x (token) The target token.
 * @returns (string literal) The expanded and stringified form of @p [x].
 */
#define TI_XSTR(x) \
  TI_STR(x)

/**
 * @brief Concatenates two tokens.
 * @param a (token) The first token (left).
 * @param b (token) The second token (right).
 * @returns (token) The concatenated form of @p [a] and @p [b].
 */
#define TI_CAT(a, b) \
  a##b

/**
 * @brief Expands and concatenates two tokens.
 * @param a (token) The first token (left).
 * @param b (token) The second token (right).
 * @returns (token) The expanded and concatenated form of @p [a] and @p [b].
 */
#define TI_XCAT(a, b) \
  TI_CAT(a, b)

/**
 * @brief Concatenates three tokens.
 * @param a (token) The first token (left).
 * @param b (token) The second token (middle).
 * @param c (token) The third token (right).
 * @returns (token) The concatenated form of @p [a], @p [b], and @p [c].
 */
#define TI_JOIN(a, b, c) \
  a##b##c

/**
 * @brief Expands and concatenates three tokens.
 * @param a (token) The first token (left).
 * @param b (token) The second token (middle).
 * @param c (token) The third token (right).
 * @returns (token) The expanded and concatenated form of @p [a], @p [b], and @p [c].
 */
#define TI_XJOIN(a, b, c) \
  TI_JOIN(a, b, c)
