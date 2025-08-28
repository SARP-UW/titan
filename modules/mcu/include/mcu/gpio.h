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
 * @file modules/mcu/include/mcu/gpio.h
 * @authors Joshua Beard
 * @brief Driver for the GPIO
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "util/mask.h"

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

// Define an enum for the GPIO ports for readability
typedef enum {
    GPIO_PORT_A,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
    GPIO_PORT_F,
    GPIO_PORT_G,
    GPIO_PORT_H,
    GPIO_PORT_I,
    GPIO_PORT_J,
    GPIO_PORT_K,
} gpio_port_t;

/**
 * port_index_from_pin[overall pin #] = 100 * port + PIN # Within Port
 * -1 if pin doesn't exist
*/
int32_t port_index_from_pin[140] = {-1,402,403,404,405,406,-1,-1,-1,213,
                                    214,215,-1,-1,-1,-1,-1,-1,-1,-1,
                                    506,507,508,509,510,700,701,-1,200,201,
                                    -1,-1,-1,-1,-1,-1,-1,0,1,2,
                                    3,-1,-1,4,5,6,7,204,205,100,
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


int32_t MODER_OFFSET  = 0x0;
int32_t OTYPER_OFFSET = 0x1;
int32_t OSPEEDR_OFFSET= 0x2;
int32_t PUPDR_OFFSET  = 0x3;
int32_t IDR_OFFSET    = 0x4; 
int32_t ODR_OFFSET    = 0x5;
int32_t AFRL_OFFSET   = 0x8;
int32_t AFRH_OFFSET   = 0x9;

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param mode: 0 for in, 1 for general purpose output, 2 for alternate function, 3 for analog
*/
void tal_set_mode(int pin, int mode);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param mode: 0 for push pull, 1 for open drain
 */ 
void tal_set_drain(int pin, int drain);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param mode: 0 : Low speed
 *              1 : Medium speed
 *              2 : Fast speed
 *              3 : High speed
 */ 
void tal_set_speed(int pin, int speed);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param pull: -1 for low, 0 for floating, 1 for high
*/
void tal_pull_pin(int pin, int pull);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param value: 0 for off, 1 for on
*/
void tal_set_pin(int pin, int value);

/**
 * Used to configure the alternate mode of the pin if set in alternate modeby #tal_set_mode
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * @param value: 0000b: AF0
                 0001b: AF1
                 0010b: AF2
                 0011b: AF3
                 0100b: AF4
                 0101b: AF5
                 0110b: AF6
                 0111b: AF7
                 1000b: AF8
                 1001b: AF9
                 1010b: AF10
                 1011b: AF11
                 1100b: AF12
                 1101b: AF13
                 1110b: AF14
                 1111b: AF15
*/
void tal_alternate_mode(int pin, int value);

/**
 * @param pin: The single integer value of the pin, found in specific docs page 60
 * 
 * @return true if pin is high, false if pin is low
*/
bool tal_read_pin(int pin);

/**
 * @param pin: The GPIO pin for which to enable the clock
 * @return bool: True if successful false otherwise
 */
bool tal_enable_clock(int pin);

/**
 * @param pin: The GPIO pin for which to disable the clock
 * @return bool: True if successful false otherwise
 */
bool tal_disable_clock(int pin);

void tal_set_mode(int pin, int mode)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ // This means this pin number isn't on the board
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  volatile int32_t* output_type_reg = port_registers[port] + MODER_OFFSET;

  tal_write_mask_u32(mode, output_type_reg, index * 2, 2);
}

void tal_set_drain(int pin, int drain)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ // This means this pin number isn't on the board
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  volatile int32_t* drain_register = port_registers[port] + OTYPER_OFFSET;

  tal_write_mask_u32(drain, drain_register, index, 1);
}

void tal_set_speed(int pin, int speed)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ // This means this pin number isn't on the board
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  volatile int32_t* speed_register = port_registers[port] + OSPEEDR_OFFSET;

  tal_write_mask_u32(speed, speed_register, index * 2, 2);
}


void tal_pull_pin(int pin, int pull)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ 
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  volatile int32_t* pull_register = port_registers[port] + PUPDR_OFFSET;

  switch (pull)
  {
    case 1:{
      tal_write_mask_u32(1, pull_register, index * 2, 2);
      break;
    }
    case 0:{
      tal_write_mask_u32(0, pull_register, index * 2, 2);
      break;
    }
    case -1:{
      tal_write_mask_u32(2, pull_register, index * 2, 2);
      break;
    }
    
    default:{
      break;
    }
  }
}

void tal_set_pin(int pin, int value)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ 
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  int32_t* set_register = port_registers[port] + ODR_OFFSET;

  switch (value){
    case 0:{
      tal_write_mask_u32(0, set_register, index, 1);
      break;
    }
    case 1:{
      tal_write_mask_u32(1, set_register, index, 1);
      break;
    }

    default:{
      break;
    }
  }
}

void tal_alternate_mode(int pin, int value)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ 
    return; 
  }
  int port = v / 100;
  int index = v - 100 * port;

  if(index <= 7){
    // use AFRL
    int32_t* reg = port_registers[port] + AFRL_OFFSET;
    tal_write_mask_u32(value, reg, index, 4);

  }else{
    // use AFRH
    int32_t* reg = port_registers[port] + AFRH_OFFSET;
    tal_write_mask_u32(value, reg, index - 8, 4); // subtract 8 from index for offset
  }
}

bool tal_read_pin(int pin)
{
  int v = port_index_from_pin[pin];
  if(v == -1){ 
    return false;  // throw error
  }
  int port = v / 100;
  int index = v - 100 * port;

  int32_t* input_register = port_registers[port] + IDR_OFFSET;
  uint32_t read_val = tal_read_mask_u32(input_register, index, 1);
  
  return read_val == 1;
}

bool tal_enable_clock(int pin) {
    gpio_port_t port = port_index_from_pin[pin] / 100;
    switch (port) {
        case (GPIO_PORT_A): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOAEN);
            return true;
        case (GPIO_PORT_B): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOBEN);
            return true;
        case (GPIO_PORT_C): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOCEN);
            return true;
        case (GPIO_PORT_D): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIODEN);
            return true;
        case (GPIO_PORT_E): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOEEN);
            return true;
        case (GPIO_PORT_F): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOFEN);
            return true;
        case (GPIO_PORT_G): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOGEN);
            return true;
        case (GPIO_PORT_H): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOHEN);
            return true;
        case (GPIO_PORT_I): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOIEN);
            return true;
        case (GPIO_PORT_J): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOJEN);
            return true;
        case (GPIO_PORT_K): // 
            SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOKEN);
            return true;
    }
    return false;
}

bool tal_disable_clock(int pin) {
    gpio_port_t port = port_index_from_pin[pin] / 100;
    switch (port) {
        case (GPIO_PORT_A): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOAEN);
            return true;
        case (GPIO_PORT_B): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOBEN);
            return true;
        case (GPIO_PORT_C): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOCEN);
            return true;
        case (GPIO_PORT_D): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIODEN);
            return true;
        case (GPIO_PORT_E): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOEEN);
            return true;
        case (GPIO_PORT_F): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOFEN);
            return true;
        case (GPIO_PORT_G): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOGEN);
            return true;
        case (GPIO_PORT_H): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOHEN);
            return true;
        case (GPIO_PORT_I): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOIEN);
            return true;
        case (GPIO_PORT_J): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOJEN);
            return true;
        case (GPIO_PORT_K): // 
            CLR_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOKEN);
            return true;
    }
    return false;
}

#if defined(__cplusplus)
  }
#endif