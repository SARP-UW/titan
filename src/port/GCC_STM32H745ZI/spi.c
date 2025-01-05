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
 * @file src/port/GCC_STM32H745ZI_CM7/spi.c
 * @authors Aaron McBride
 * @brief SPI driver implementation.
 */

#include "include/tal/spi.h" /* header */
#include "src/port/GCC_STM32H745ZI_CM7/internal/vtable.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  bool set_spi_config(const int32_t index, const spi_config_t config) {

  }

  spi_config_t get_spi_config(const int32_t index) {

  }

  bool spi_transmit(const int32_t index, const void* const src, const int32_t size) {

  }

  bool spi_receive(const int32_t index, void* const dst, const int32_t size) {

  }

#if defined(__cplusplus)
  } /* extern "C" */
#endif