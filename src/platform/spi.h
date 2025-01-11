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
 * @file common/platform/spi.h
 * @authors Joshua Beard
 * @brief Driver for the SPI
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "tal/mask.h"
#include "gpio.h"

#if defined(__cplusplus)
  extern "C" {
#endif


void tal_enable_SPI();

void tal_transmit_SPI();

void* tal_read_SPI();

volatile uint32_t* SPI_1_BASE = 0x40013000;

#define SPI_CR1_OFFSET 0;
#define SPI_CR2_OFFSET 0x04;
#define SPI_CFG1_OFFSET 0x08;
#define SPI_CFG2_OFFSET 0x0C;

#define SPI_CR1 *(SPI_1_BASE + SPI_CR1_OFFSET);
#define SPI_CR2 *(SPI_1_BASE + SPI_CR2_OFFSET);

void tal_enable_SPI()
{
    tal_set_mode(43, 2); // NSS / CS pin to AF mode
    tal_set_mode(44, 2); // SCK
    tal_set_mode(45, 2); // MISO
    tal_set_mode(46, 2); // MOSI

    tal_alternate_mode(43, 5); // AF5, specified on pg. 87 of datasheet
    tal_alternate_mode(44, 5);
    tal_alternate_mode(45, 5);
    tal_alternate_mode(46, 5);

    
}



#if defined(__cplusplus)
  }
#endif