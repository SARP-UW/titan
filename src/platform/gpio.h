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
 * @file common/platform/gpio.h
 * @authors Joshua Beard
 * @brief Driver for the GPIO
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "mask.h"

#if defined(__cplusplus)
  extern "C" {
#endif


#define PORTS 11
#define PINS 16
// let A = 0, B = 1, --- , K = 10
// Port [A:K] = [0:10]

// Entries in this table are the pin numbers.  
// int32_t pins[PORTS][PINS] = {
//    PIN # Within Port
//    0   0   0   0   0   0   0   0   0   0   1   1   1   1   1   1
//    0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5     PORT
//   {37 ,38 ,39 ,40 ,43 ,44 ,45 ,46 ,97 ,98 ,99 ,100,101,102,107,108}, // A
//   {49 ,50 ,51 ,130,131,132,133,134,136,137,66 ,67 ,72 ,73 ,74 ,75 }, // B
//   {28 ,29 ,0  ,0  ,47 ,48 ,93 ,94 ,95 ,96 ,109,110,111,9  ,10 ,11 }, // C
//   {112,113,114,115,116,117,120,121,76 ,77 ,78 ,81 ,82 ,83 ,84 ,85 }, // D
//   {138,139,1  ,2  ,3  ,4  ,5  ,57 ,58 ,59 ,60 ,61 ,62 ,63 ,64 ,65 }, // E
//   {0  ,0  ,0  ,0  ,0  ,0  ,20 ,21 ,22 ,23 ,24 ,52 ,0  ,0  ,53 ,54 }, // F
//   {0  ,0  ,0  ,0  ,0  ,0  ,86 ,87 ,88 ,122,123,124,125,126,127,0  }, // G
//   {25 ,26 ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  }, // H
//   {0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  }, // I
//   {0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  }, // J
//   {0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  ,0  }, // K
// };

/**
 * port_index_from_pin[overall pin #] = 100 * port + PIN # Within Port
*/
int32_t port_index_from_pin[140] = {-1,402,403,404,405,406,-1,-1,-1,213,
                                    214,215,-1,-1,-1,-1,-1,-1,-1,-1,
                                    506,507,508,509,510,700,701,-1,200,201,
                                    -1,-1,-1,-1,-1,-1,-1,0,1,2,
                                    3,0,0,4,5,6,7,204,205,100,
                                    101,102,511,514,515,-1,-1,407,408,409,
                                    410,411,412,413,414,415,110,111,-1,-1,
                                    -1,-1,112,113,114,115,308,309,310,-1,
                                    -1,311,312,313,314,315,606,607,608,-1,
                                    -1,-1,-1,206,207,208,209,8,9,10,
                                    11,12,13,-1,-1,-1,-1,14,15,210,
                                    211,212,300,301,302,303,304,305,-1,-1,
                                    306,307,609,610,611,612,613,614,-1,-1,
                                    103,104,105,106,107,-1,108,109,400,401};

// would be size 11 but ports I J and K do not have any pins connected so no point in storing their address
volatile int32_t* port_registers[8] = {
  (int32_t*)1476526080,
  (int32_t*)1476527104,
  (int32_t*)1476528128,
  (int32_t*)1476529152,
  (int32_t*)1476530176,
  (int32_t*)1476531200,
  (int32_t*)1476532224,
  (int32_t*)1476533248
};

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param mode: -1 for in, 1 for out
*/
void ti_set_mode(int pin, int mode);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param pull: -1 for low, 0 for floating, 1 for high
*/
void ti_pull_pin(int pin, int pull);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param value: 0 for off, 1 for on
*/
void ti_set_pin(int pin, int value);


/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * 
 * @return true if pin is high, false if pin is low
*/
bool ti_read_pin(int pin);


void ti_set_mode(int pin, int mode)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ // This means this pin number isn't on the board
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  
}


// add read and write buffer as well

#if defined(__cplusplus)
  }
#endif