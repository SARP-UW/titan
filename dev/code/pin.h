/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2024 UW SARP
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be usef, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICAR PURPOS E. See the GNU
 * General Public License for more details.
 * 
 * You shod have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * @file src/port/GCC_STM32H745ZI/resource/pin.h
 * @authors Aaron McBride
 * @brief Pin and port definitions.
 */

// This file is just temporary, I dont know if this is a good way to do it --Aaron

#ifndef SRC_PORT_GCC_STM32H745ZI_RESOURCE_PIN_H
#define SRC_PORT_GCC_STM32H745ZI_RESOURCE_PIN_H

  #include <stdint.h>
  #include <stddef.h>

  #ifdef __cplusplus
    extern "C" {
  #endif

    /**********************************************************************************************
     * @section Pin Enumeration
     **********************************************************************************************/

    typedef enum {
      PIN_PA0  = 0,
      PIN_PA1  = 1,
      PIN_PA2  = 2,
      PIN_PA3  = 3,
      PIN_PA4  = 4,
      PIN_PA5  = 5,
      PIN_PA6  = 6,
      PIN_PA7  = 7,
      PIN_PA8  = 8,
      PIN_PA9  = 9,
      PIN_PA10 = 10,
      PIN_PA11 = 11,
      PIN_PA12 = 12,
      PIN_PA13 = 13,
      PIN_PA14 = 14,
      PIN_PA15 = 15,
      PIN_PB0  = 16,
      PIN_PB1  = 17,
      PIN_PB2  = 18,
      PIN_PB3  = 19,
      PIN_PB4  = 20,
      PIN_PB5  = 21,
      PIN_PB6  = 22,
      PIN_PB7  = 23,
      PIN_PB8  = 24,
      PIN_PB9  = 25,
      PIN_PB10 = 26,
      PIN_PB11 = 27,
      PIN_PB12 = 28,
      PIN_PB13 = 29,
      PIN_PB14 = 30,
      PIN_PB15 = 31,
      PIN_PC0  = 32,
      PIN_PC1  = 33,
      PIN_PC2  = 34,
      PIN_PC3  = 35,
      PIN_PC4  = 36,
      PIN_PC5  = 37,
      PIN_PC6  = 38,
      PIN_PC7  = 39,
      PIN_PC8  = 40,
      PIN_PC9  = 41,
      PIN_PC10 = 42,
      PIN_PC11 = 43,
      PIN_PC12 = 44,
      PIN_PC13 = 45,
      PIN_PC14 = 46,
      PIN_PC15 = 47,
      PIN_PD0  = 48,
      PIN_PD1  = 49,
      PIN_PD2  = 50,
      PIN_PD3  = 51,
      PIN_PD4  = 52,
      PIN_PD5  = 53,
      PIN_PD6  = 54,
      PIN_PD7  = 55,
      PIN_PD8  = 56,
      PIN_PD9  = 57,
      PIN_PD10 = 58,
      PIN_PD11 = 59,
      PIN_PD12 = 60,
      PIN_PD13 = 61,
      PIN_PD14 = 62,
      PIN_PD15 = 63,
      PIN_PE0  = 64,
      PIN_PE1  = 65,
      PIN_PE2  = 66,
      PIN_PE3  = 67,
      PIN_PE4  = 68,
      PIN_PE5  = 69,
      PIN_PE6  = 70,
      PIN_PE7  = 71,
      PIN_PE8  = 72,
      PIN_PE9  = 73,
      PIN_PE10 = 74,
      PIN_PE11 = 75,
      PIN_PE12 = 76,
      PIN_PE13 = 77,
      PIN_PE14 = 78,
      PIN_PE15 = 79,
      PIN_PF0  = 80,
      PIN_PF1  = 81,
      PIN_PF2  = 82,
      PIN_PF3  = 83,
      PIN_PF4  = 84,
      PIN_PF5  = 85,
      PIN_PF6  = 86,
      PIN_PF7  = 87,
      PIN_PF8  = 88,
      PIN_PF9  = 89,
      PIN_PF10 = 90,
      PIN_PF11 = 91,
      PIN_PF12 = 92,
      PIN_PF13 = 93,
      PIN_PF14 = 94,
      PIN_PF15 = 95,
      PIN_PG0  = 96,
      PIN_PG1  = 97,
      PIN_PG2  = 98,
      PIN_PG3  = 99,
      PIN_PG4  = 100,
      PIN_PG5  = 101,
      PIN_PG6  = 102,
      PIN_PG7  = 103,
      PIN_PG8  = 104,
      PIN_PG9  = 105,
      PIN_PG10 = 106,
      PIN_PG11 = 107,
      PIN_PG12 = 108,
      PIN_PG13 = 109,
      PIN_PG14 = 110,
      PIN_PG15 = 111,
      PIN_PH0  = 112,
      PIN_PH1  = 113,
      PIN_PH2  = 114,
      PIN_PH3  = 115,
      PIN_PH4  = 116,
      PIN_PH5  = 117,
      PIN_PH6  = 118,
      PIN_PH7  = 119,
      PIN_PH8  = 120,
      PIN_PH9  = 121,
      PIN_PH10 = 122,
      PIN_PH11 = 123,
      PIN_PH12 = 124,
      PIN_PH13 = 125,
      PIN_PH14 = 126,
      PIN_PH15 = 127,
      PIN_PI0  = 128,
      PIN_PI1  = 129,
      PIN_PI2  = 130,
      PIN_PI3  = 131,
      PIN_PI4  = 132,
      PIN_PI5  = 133,
      PIN_PI6  = 134,
      PIN_PI7  = 135,
      PIN_PI8  = 136,
      PIN_PI9  = 137,
      PIN_PI10 = 138,
      PIN_PI11 = 139,
      PIN_PI12 = 140,
      PIN_PI13 = 141,
      PIN_PI14 = 142,
      PIN_PI15 = 143,
      PIN_PJ0  = 144,
      PIN_PJ1  = 145,
      PIN_PJ2  = 146,
      PIN_PJ3  = 147,
      PIN_PJ4  = 148,
      PIN_PJ5  = 149,
      PIN_PJ6  = 150,
      PIN_PJ7  = 151,
      PIN_PJ8  = 152,
      PIN_PJ9  = 153,
      PIN_PJ10 = 154,
      PIN_PJ11 = 155,
      PIN_PJ12 = 156,
      PIN_PJ13 = 157,
      PIN_PJ14 = 158,
      PIN_PJ15 = 159,
      PIN_PK0  = 160,
      PIN_PK1  = 161,
      PIN_PK2  = 162,
      PIN_PK3  = 163,
      PIN_PK4  = 164,
      PIN_PK5  = 165,
      PIN_PK6  = 166,
      PIN_PK7  = 167
    }pin_t;

    /**********************************************************************************************
     * @section Port Enumeration
     **********************************************************************************************/

    typedef enum {
      PORT_A = 0,
      PORT_B = 1,
      PORT_C = 2,
      PORT_D = 3,
      PORT_E = 4,
      PORT_F = 5,
      PORT_G = 6,
      PORT_H = 7,
      PORT_I = 8,
      PORT_J = 9,
      PORT_K = 10
    }port_t;

    /**********************************************************************************************
     * @section Pin Functions
     **********************************************************************************************/

  #ifdef __cplusplus
    } /* extern "C" */
  #endif

#endif /* SRC_PORT_GCC_STM32H745ZI_RESOURCE_PIN_H */