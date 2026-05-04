/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2025 UW SARP
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
 * @file app/utils/pinout.h
 * @authors Joshua Beard
 * @brief Physical pinout of flight computer board
 */

#pragma once

#include <stdint.h>


static const uint32_t GNSS_SPI_CS = 126;
// SPI 3, same as sensor board SPI
static const uint32_t GNSS_SPI_INST = 3;
static const uint32_t GNSS_SPI_MOSI = 111;
static const uint32_t GNSS_SPI_MISO = 110;
static const uint32_t GNSS_SPI_SCLK = 109;
//-------------------------------

static const uint32_t EXT_FLASH_QSPI_CS = 66;
static const uint32_t EXT_FLASH_QSPI_SCLK = 24;
static const uint32_t EXT_FLASH_QSPI_IO_0 = 22;
static const uint32_t EXT_FLASH_QSPI_IO_1 = 23;
static const uint32_t EXT_FLASH_QSPI_IO_2 = 21;
static const uint32_t EXT_FLASH_QSPI_IO_3 = 20;
//-------------------------------

static const uint32_t RADIO_SPI_CS = 84;
// SPI 2
static const uint32_t RADIO_SPI_INST = 2;
static const uint32_t RADIO_SPI_MOSI = 75;
static const uint32_t RADIO_SPI_MISO = 74;
static const uint32_t RADIO_SPI_SCLK = 73;

static const uint32_t RADIO_IRQ = 85;
static const uint32_t RADIO_SHDN = 49;
//-------------------------------

// UART 2
static const uint32_t RS485_UART_TX = 39;
static const uint32_t RS485_UART_RX = 40;

static const uint32_t RS485_RE = 44;
static const uint32_t RS485_DE = 43;
//-------------------------------
//CAN could be here, but I omit since we are not using it in the minimal version

static const uint32_t USB_DATA_plus = 101;
static const uint32_t USB_DATA_minus = 100;
static const uint32_t USB_ID = 99;
//-------------------------------

static const uint32_t SWD_CLK = 107;
static const uint32_t SWD_IO = 102;
static const uint32_t SWD_OUT = 130;
static const uint32_t RST = 27;
//-------------------------------

static const uint32_t ACTUATOR_SPI_MOSI = 5;
static const uint32_t ACTUATOR_SPI_MISO = 4;

// For reference, all valvue and PT names: https://docs.google.com/document/d/1aHiSNhke8H2l8NKYezfDgkhBJBR_zAWUDkQf7POzs2M/edit?tab=t.0
static const uint32_t ACTUATOR_CS_1 = 63; // each controls 4 valves 
static const uint32_t ACTUATOR_CS_2 = 62; // ...
static const uint32_t ACTUATOR_CS_3 = 61; // ... thus 12 valves total here

static const uint32_t POWER_TMP_CS = 58; // power board temperature 

static const uint32_t PWM_1 = 38; 
static const uint32_t PWM_2 = 93;
static const uint32_t PWM_3 = 82;
static const uint32_t PWM_4 = 37;
static const uint32_t PWM_5 = 45;
static const uint32_t PWM_6 = 46;
static const uint32_t PWM_7 = 136;
static const uint32_t PWM_8 = 137;

//-------------------------------

static const uint32_t IGNITE_IO = 51;
static const uint32_t IGNITE_CONT = 52; // ADC in
static const uint32_t BATT_EN = 60;

//-------------------------------

// SPI 3, same as GNSS spi 
// NOTE: EVERYTHING IN THIS BLOCK IS ON SPI 3
static const uint32_t SENSOR_SPI_INST = 3;
static const uint32_t SENSOR_SPI_MOSI = 111; // ANA_SPI on diagram
static const uint32_t SENSOR_SPI_MISO = 110;
static const uint32_t SENSOR_SPI_SCLK = 109;

// ADC CS
static const uint32_t SENSOR_CS_1 = 76; // CCPT, OMPT, FMPT, OTPT are all connected to this ADC
static const uint32_t SENSOR_CS_2 = 77; // All others are unused 
static const uint32_t SENSOR_CS_3 = 114;
static const uint32_t SENSOR_CS_4 = 115;
static const uint32_t SENSOR_CS_5 = 116;
static const uint32_t SENSOR_CS_6 = 117;

// Regular sensor CS
static const uint32_t IMU_1_CS = 120;
static const uint32_t IMU_2_CS = 121;
static const uint32_t BARO_1_CS = 122;
static const uint32_t BARO_2_CS = 123;
static const uint32_t ANALOG_TMP_CS = 124; // analog (sensor) board temperature
static const uint32_t MAGNOTOMETER_CS = 125;
//-------------------------------
