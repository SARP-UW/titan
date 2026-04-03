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

 #include <stdint.h>


const uint32_t GNSS_SPI_CS = 126;
// SPI 3, same as sensor board SPI
const uint32_t GNSS_SPI_MOSI = 111;
const uint32_t GNSS_SPI_MISO = 110;
const uint32_t GNSS_SPI_SCLK = 109;
//-------------------------------

const uint32_t EXT_FLASH_QSPI_CS = 66;
const uint32_t EXT_FLASH_QSPI_SCLK = 24;
const uint32_t EXT_FLASH_QSPI_IO_0 = 22;
const uint32_t EXT_FLASH_QSPI_IO_1 = 23;
const uint32_t EXT_FLASH_QSPI_IO_2 = 21;
const uint32_t EXT_FLASH_QSPI_IO_3 = 20;
//-------------------------------

const uint32_t RADIO_SPI_CS = 84;
// SPI 2
const uint32_t RADIO_SPI_MOSI = 75;
const uint32_t RADIO_SPI_MISO = 74;
const uint32_t RADIO_SPI_SCLK = 73;

const uint32_t RADIO_IRQ = 85;
const uint32_t RADIO_SHDN = 49;
//-------------------------------

// UART 2
const uint32_t RS485_UART_TX = 39;
const uint32_t RS485_UART_RX = 40;

const uint32_t RS485_RE = 44;
const uint32_t RS485_DE = 43;
//-------------------------------
//CAN could be here, but I omit since we are not using it in the minimal version

const uint32_t USB_DATA_plus = 101;
const uint32_t USB_DATA_minus = 100;
const uint32_t USB_ID = 99;
//-------------------------------

const uint32_t SWD_CLK = 107;
const uint32_t SWD_IO = 102;
const uint32_t SWD_OUT = 130;
const uint32_t RST = 27;
//-------------------------------

const uint32_t ACTUATOR_SPI_MOSI = 5;
const uint32_t ACTUATOR_SPI_MISO = 4;

// For reference, all valvue and PT names: https://docs.google.com/document/d/1aHiSNhke8H2l8NKYezfDgkhBJBR_zAWUDkQf7POzs2M/edit?tab=t.0
const uint32_t ACTUATOR_CS_1 = 63; // each controls 4 valves 
const uint32_t ACTUATOR_CS_2 = 62; // ...
const uint32_t ACTUATOR_CS_3 = 61; // ... thus 12 valves total here

const uint32_t POWER_TMP_CS = 58; // power board temperature 

const uint32_t PWM_1 = 38; 
const uint32_t PWM_2 = 93;
const uint32_t PWM_3 = 82;
const uint32_t PWM_4 = 37;
const uint32_t PWM_5 = 45;
const uint32_t PWM_6 = 46;
const uint32_t PWM_7 = 136;
const uint32_t PWM_8 = 137;

//-------------------------------

const uint32_t IGNITE_IO = 51;
const uint32_t IGNITE_CONT = 52; // ADC in
const uint32_t BATT_EN = 60;

//-------------------------------

// SPI 3, same as GNSS spi 
// NOTE: EVERYTHING IN THIS BLOCK IS ON SPI 3
const uint32_t SENSOR_SPI_MOSI = 111; // ANA_SPI on diagram
const uint32_t SENSOR_SPI_MISO = 110;
const uint32_t SENSOR_SPI_SCLK = 109;

// ADC CS
const uint32_t SENSOR_CS_1 = 76; // CCPT, OMPT, FMPT, OTPT are all connected to this ADC
const uint32_t SENSOR_CS_2 = 77; // All others are unused 
const uint32_t SENSOR_CS_3 = 114;
const uint32_t SENSOR_CS_4 = 115;
const uint32_t SENSOR_CS_5 = 116;
const uint32_t SENSOR_CS_6 = 117;

// Regular sensor CS
const uint32_t IMU_1_CS = 120;
const uint32_t IMU_2_CS = 121;
const uint32_t BARO_1_CS = 122;
const uint32_t BARO_2_CS = 123;
const uint32_t ANALOG_TMP_CS = 124; // analog (sensor) board temperature
const uint32_t MAGNOTOMETER_CS = 125;
//-------------------------------
