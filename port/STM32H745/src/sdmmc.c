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
 * @file dev/src/sdmmc.h
 * @authors Charles Faisandier
 * @brief Driver for the SDMMC
 */

#pragma once
#include <stdbool.h>

# if defined(__cplusplus)
extern "C" {
# endif

  /** @brief This function initializes the SDMMC
   *
   *  @return bool: whether the initialization succeeded
   */
  bool init_SDMMC() {
    return true;
  }

  /** @brief This function writes to the SDMMC
   *
   *  @return bool: whether the write succeeded
   */
  bool write_SDMMC() {
    return true;
  }

# if defined(__cplusplus)
}
# endif
