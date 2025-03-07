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


void tal_configure_SPI();

void tal_transmit_SPI();

void* tal_read_SPI();

volatile uint32_t* SPI_1_BASE = 0x40013000;

#define SPI_CR1_OFFSET 0
#define SPI_CR2_OFFSET 0x04
#define SPI_CFG1_OFFSET 0x08
#define SPI_CFG2_OFFSET 0x0C
#define SPI_SR_OFFSET 0x14
#define SPI_TXDR_OFFSET 0x20
#define SPI_RXDR_OFFSET 0x30

#define SPI_CR1 *(SPI_1_BASE + SPI_CR1_OFFSET)
#define SPI_CR2 *(SPI_1_BASE + SPI_CR2_OFFSET)
#define SPI_CFG1 *(SPI_1_BASE + SPI_CFG1_OFFSET)
#define SPI_CFG2 *(SPI_1_BASE + SPI_CFG2_OFFSET)
#define SPI_SR *(SPI_1_BASE + SPI_SR_OFFSET)
#define SPI_TXDR *(SPI_1_BASE + SPI_TXDR_OFFSET)
#define SPI_RXDR *(SPI_1_BASE + SPI_RXDR_OFFSET)

//POSSIBLE ISSUES TO CHECK WHEN IT DOESNT WORK
// SSM bit in CFG2.  I am using hardware SS, but software SS might be better 
//(basically im saying SS might not be being pulled low)

void tal_configure_SPI() // not named enable, because enabling must be done after we configure data size, annoyingly
{
    tal_set_mode(43, 2); // NSS / CS pin to AF mode
    tal_set_mode(44, 2); // SCK
    tal_set_mode(45, 2); // MISO
    tal_set_mode(46, 2); // MOSI

    tal_alternate_mode(43, 5); // AF5, specified on pg. 87 of datasheet
    tal_alternate_mode(44, 5);
    tal_alternate_mode(45, 5);
    tal_alternate_mode(46, 5);

    tal_pull_pin(43, 1); // configure pull up / floating states
    tal_pull_pin(44, 0);
    tal_pull_pin(45, 1);
    tal_pull_pin(46, 0);

    tal_set_drain(43, 0); // configure all pins to push / pull
    tal_set_drain(44, 0);
    tal_set_drain(45, 0);
    tal_set_drain(46, 0);

    tal_set_speed(43, 3); // configure high speed on all pins
    tal_set_speed(44, 3);
    tal_set_speed(45, 3);
    tal_set_speed(46, 3);

    // TODO enable SPI in RCC and configure clock / baud rate


    SPI_CFG2 |= 1 << 22; // Configure peripheral in master mode
    SPI_CFG2 |= 1 << 29; // SSOE enable (turn on CS output)
    SPI_CFG2 |= 1 << 31; // Important for safety, not functionality critical but prob good to have
    
    SPI_CFG1 |= 0b00111; // 8 bit data size (default)
}

void tal_transmit_SPI(void* d, uint32_t size)
{
    uint8_t* data = (uint8_t*) d;

    SPI_CR2 |= size; // check this, because if bits past the 15th bit in size are 1, there could be issues. 
    SPI_CR1 |= 1 << 0; // Enable peripheral (SPI configuration registers are now locked)

    int i = 0;
    while(i < size){
      while(!(SPI_SR & (1 << 1))); // wait for TXP (not 100% this is the right bit to wait for, but we can test)
      // maybe also wait until TXDR is 0?
      // idk that just feels hacky, todo discuss
      SPI_TXDR |= *data;
      i++;
    }

    SPI_CR1 &= ~1; // Disable peripheral
}

void* tal_read_SPI(uint32_t size){
    SPI_CR2 |= size; // check this, because if bits past the 15th bit in size are 1, there could be issues. 
    SPI_CR1 |= 1 << 0; // Enable peripheral (SPI configuration registers are now locked)
    uint8_t data[size];

    int i = 0;
    while(i < size){
      while(!(SPI_SR & (1 << 0))); // wait for RXP
      data[i] = SPI_RXDR & (0xFF); // get first 8 bits
      i++;
    }

    SPI_CR1 &= ~1; // Disable peripheral
    return data;
}


#if defined(__cplusplus)
  }
#endif