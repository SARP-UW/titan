/**
 * This file is part of the Titan Flight Computer Project
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
 * @file $path$
 * @authors $name$
 * @brief $summary$
 */

#ifndef $path$
#define $path$

  #if defined(__cplusplus)
    extern "C" {
  #endif

    /**********************************************************************************************
     * @section Numeric Utilities
     **********************************************************************************************/

    #define min(a, b)

    #define max(a, b)

    #define clamp(value, b1, b2)

    #define abs(value)

    /**********************************************************************************************
     * @section Overflow Detection
     **********************************************************************************************/

    #define cmp(lhs, rhs)

    #define add(lhs, rhs, ovf)

    #define sub(lhs, rhs)

    #define mul(lhs, rhs)

    #define cast(value, type)

    /**********************************************************************************************
     * @section Bit Utilities
     **********************************************************************************************/

    #define clz(value)

    #define ctz(value)

    #define popcnt(value)
    
    /**********************************************************************************************
     * @section Uncategorised Utilities
     **********************************************************************************************/

    #define array_size(array)

  #if defined(__cplusplus)
    } /* extern "C" */
  #endif

#endif /* $path$ */