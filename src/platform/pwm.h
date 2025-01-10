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
 * @file common/platform/pwm.h
 * @authors Ethan Rad
 * @brief Driver for pulse-width modulation
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
  extern "C" {
#endif

/**
 * @param pin: The integer value of the pin
 * @param frequency: The PWM frequency of the pin
 * @param dutyCycle: The duty cycle of the pwm signal on a scale of 0 to 255
*/
void tal_pwm_init(int pin, int frequency, uint8_t dutyCycle, bool* const err);

/**
 * @param pin: The integer value of the pin
 * @param frequency: The PWM frequency of the pin
*/
void tal_pwm_pin_set_channel_freq(int pin, int frequency, bool* const err);

/**
 * @param pin: The integer value of the pin
 * @param dutyCycle: The duty cycle of the pwm signal on a scale of 0 to 255
*/
void tal_pwm_pin_set_channel_duty_cycle(int pin, uint8_t dutyCycle, bool* const err);

/**
 * @param pin: The pin to enable PWM on
*/
void tal_pwm_pin_enable(int pin, bool* const err);

/**
 * @param pin: The pin to disable PWM on
*/
void tal_pwm_pin_disable(int pin, bool* const err);

/**
 * @param pin: The pin which is to be checked if it is running
 *
 * @return: true if pwm on the pin is on, false if it is off 
*/
bool tal_pwm_is_running(int pin, bool* const err);

/**
 * @param pin: The pin which is to be checked if it is valid
 *
 * @return: true if pwm on the pin is valid, false if it is not
*/
bool tal_pwm_is_valid_pin(int pin);

// TIM Base Addresses
enum {
  TIM2_Base = 1073741824, // hex 0x40000000   
  TIM3_Base = 1073742848, // hex 0x40000400  
  TIM4_Base = 1073743872, // hex 0x40000800   
  TIM5_Base = 1073744896 // hex 0x40000C00
};

// GPIO Base Addresses
enum {
  GPIOA_BASE = 1476526080, // hex 0x58020000 
  GPIOB_BASE = 1476527104, // hex 0x58020400
  GPIOC_BASE = 1476528128, // hex 0x58020800
  GPIOD_BASE = 1476529152, // hex 0x58020C00
  GPIOE_BASE = 1476530176, // hex 0x58021000
  GPIOF_BASE = 1476531200, // hex 0x58021400
  GPIOG_BASE = 1476532224, // hex 0x58021800
  GPIOH_BASE = 1476533248, // hex 0x58021C00
  GPIOI_BASE = 1476534272, // hex 0x58022000
  GPIOJ_BASE = 1476535296, // hex 0x58022400
  GPIOK_BASE = 1476536320 // hex 0x58022800
};

int32_t TIM_CR1_OFFSET = 0;
int32_t TIM_CR2_OFFSET = 4;
int32_t TIM_SMCR_OFFSET = 8;
int32_t TIM_DIER_OFFSET = 12;
int32_t TIM_SR_OFFSET = 16;
int32_t TIM_EGR_OFFSET = 20;
int32_t TIM_CCMR1_OFFSET = 24;
int32_t TIM_CCMR2_OFFSET = 28;
int32_t TIM_CCER_OFFSET = 32;
int32_t TIM_CNT_OFFSET = 36;
int32_t TIM_PSC_OFFSET = 40;
int32_t TIM_ARR_OFFSET = 44;
int32_t TIM_CCR1_OFFSET = 52;
int32_t TIM_CCR2_OFFSET = 56;
int32_t TIM_CCR3_OFFSET = 60;
int32_t TIM_CCR4_OFFSET = 64;
int32_t TIM_DCR_OFFSET = 72;
int32_t TIM_DMAR_OFFSET = 76;
int32_t TIM_AF1_OFFSET = 96;
int32_t TIM_TISEL_OFFSET = 104;

// TIM1 channels and their corresponding pins
// #define TIM1_CH1_1 70
// #define TIM1_CH1_2 119
// #define TIM1_CH2_1 74
// #define TIM1_CH2_2 120
// #define TIM1_CH3_1 76
// #define TIM1_CH3_2 121
// #define TIM1_CH4_1 77
// #define TIM1_CH4_2 122

// TIM2 channels and their corresponding pins
#define TIM2_CH1_1 40 // PA0
#define TIM2_CH1_2 51 // PA5
#define TIM2_CH1_3 138 // PA15
// #define TIM2_CH2_1 41
// #define TIM2_CH2_2 161
// #define TIM2_CH3_1 42
// #define TIM2_CH3_2 79
// #define TIM2_CH4_1 47
// #define TIM2_CH4_2 80

// TIM3 channels and their corresponding pins
// #define TIM3_CH1_1 52
// #define TIM3_CH1_2 115
// #define TIM3_CH1_3 162
#define TIM3_CH2_1 53 // PA7
#define TIM3_CH2_2 116 // PC7
#define TIM3_CH2_3 163 // PB5
// #define TIM3_CH3_1 56
// #define TIM3_CH3_2 117
// #define TIM3_CH4_1 57
// #define TIM3_CH4_2 118

// TIM4 channels and their corresponding pins
#define TIM4_CH1_1 100 // PD12
#define TIM4_CH1_2 164 // PB6
// #define TIM4_CH2_1 101
// #define TIM4_CH2_2 165
// #define TIM4_CH3_1 104
// #define TIM4_CH3_2 167
// #define TIM4_CH4_1 105
// #define TIM4_CH4_2 168

// TIM5 channels and their corresponding pins
// #define TIM5_CH1_1 40
// #define TIM5_CH1_2 87
#define TIM5_CH2_1 41 // PA1
#define TIM5_CH2_2 88 // PH11
// #define TIM5_CH3_1 42
// #define TIM5_CH3_2 89
// #define TIM5_CH4_1 47
// #define TIM5_CH4_2 131

typedef struct {
  int pin;
  int32_t* pinreg;
  int num_in_group;
  int channel;
  int32_t* base;
  int frequency;
  uint8_t dutyCycle;
  bool running;
} pwm_pin_t;

pwm_pin_t valid_pins[] = {
  {TIM2_CH1_1, GPIOA_BASE, 0, 1, (int32_t*) TIM2_Base, 0, 0, false},
  {TIM2_CH1_2, GPIOA_BASE, 5, 1, (int32_t*) TIM2_Base, 0, 0, false},
  {TIM2_CH1_3, GPIOA_BASE, 15, 1, (int32_t*) TIM2_Base, 0, 0, false},
  {TIM3_CH2_1, GPIOA_BASE, 7, 2, (int32_t*) TIM3_Base, 0, 0, false},
  {TIM3_CH2_2, GPIOC_BASE, 7, 2, (int32_t*) TIM3_Base, 0, 0, false},
  {TIM3_CH2_3, GPIOB_BASE, 5, 2, (int32_t*) TIM3_Base, 0, 0, false},
  {TIM4_CH1_1, GPIOD_BASE, 12, 1, (int32_t*) TIM4_Base, 0, 0, false},
  {TIM4_CH1_2, GPIOB_BASE, 6, 1, (int32_t*) TIM4_Base, 0, 0, false},
  {TIM5_CH2_1, GPIOA_BASE, 1, 2, (int32_t*) TIM5_Base, 0, 0, false},
  {TIM5_CH2_2, GPIOH_BASE, 11, 2, (int32_t*) TIM5_Base, 0, 0, false}
};

void tal_pwm_pin_init(int pin, uint32_t frequency, uint8_t dutyCycle, bool* const err) {
  pwm_pin_t pin_struct;
  if(!get_pin_info(pin, &pin_struct)){ *err = true; return; }
  
  (*(pin_struct.pinreg + (2 * pin_struct.num_in_group))) &= ~0x3; // Clear pin function mode
  (*(pin_struct.pinreg + (2 * pin_struct.num_in_group))) |= 0x2; // Set pin to alternate function mode for PWM
  // enable pin clock

  (*(pin_struct.base + TIM_CR1_OFFSET)) &= ~0x1; // Disable timer channel 
  (*(pin_struct.base + TIM_CR1_OFFSET)) &= ~(4 << 1); // Set counter to upcounting
  
  uint32_t f_timer = frequency * 65536; // Max ARR assumed as 65535 for flexibility
  uint32_t prescaler = (16000000 / f_timer) - 1; // TODO: determine system clock frequency

  if (prescaler > 65535) {
    prescaler = 65535;
    f_timer = 16000000 / (prescaler + 1);
  }

  (*(pin_struct.base + TIM_PSC_OFFSET)) = prescaler; // Set the prescaler of the timer

  uint32_t arr = (f_timer / frequency) - 1;
  uint32_t ccr = ((dutyCycle / 256) / 100) * (arr + 1);

  switch(pin_struct.channel){
    case 1:
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x3; // Set channel 1 to output
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) |= 0x6; // Set channel 1 to PWM mode 1
      (*(pin_struct.base + TIM_CCR1_OFFSET)) = ccr; // Set CCR value
      break;
    case 2:
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x30; // Set channel 2 to output
      (*(pin_struct.base + TIM_CCMR1_OFFSET + 8)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR1_OFFSET + 8)) |= 0x6; // Set channel 2 to PWM mode 1
      (*(pin_struct.base + TIM_CCR2_OFFSET)) = ccr; // Set CCR value
      break;
    case 3:
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x3; // Set channel 3 to output
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) |= 0x6; // Set channel 3 to PWM mode 1
      (*(pin_struct.base + TIM_CCR3_OFFSET)) = ccr; // Set CCR value
      break;
    case 4:
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x30; // Set channel 4 to output
      (*(pin_struct.base + TIM_CCMR2_OFFSET + 8)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR2_OFFSET + 8)) |= 0x6; // Set channel 4 to PWM mode 1
      (*(pin_struct.base + TIM_CCR4_OFFSET)) = ccr; // Set CCR value
      break;
  }

  (*(pin_struct.base + TIM_ARR_OFFSET)) = arr; // Set the period of the timer

  (*(pin_struct.base + TIM_EGR_OFFSET)) |= 1; // Trigger update of registers
  while((*(pin_struct.base + TIM_EGR_OFFSET)) | 1); // Wait for update to complete

  (*(pin_struct.base + TIM_CCER_OFFSET)) |= (1 << ((pin_struct.channel - 1) * 4)); // Enable the output of the channel
  (*(pin_struct.base + TIM_CR1_OFFSET)) |= 1; // Enable timer channel 

  pin_struct.frequency = frequency;
  pin_struct.dutyCycle = dutyCycle;
  pin_struct.running = true;
}

void tal_pwm_pin_set_channel_freq(int pin, int frequency, bool* const err) {
  pwm_pin_t pin_struct;
  if(!get_pin_info(pin, &pin_struct)){ *err = true; return; }

  uint32_t f_timer = frequency * 65536; // Max ARR assumed as 65535 for flexibility
  uint32_t prescaler = (16000000 / f_timer) - 1; // TODO: determine system clock frequency

  if (prescaler > 65535) {
    prescaler = 65535;
    f_timer = 16000000 / (prescaler + 1);
  }

  (*(pin_struct.base + TIM_PSC_OFFSET)) = prescaler; // Set the prescaler of the timer

  uint32_t arr = (f_timer / frequency) - 1;
  uint32_t ccr = ((pin_struct.dutyCycle / 256) / 100) * (arr + 1);

  switch(pin_struct.channel){
    case 1:
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x3; // Set channel 1 to output
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) |= 0x6; // Set channel 1 to PWM mode 1
      (*(pin_struct.base + TIM_CCR1_OFFSET)) = ccr; // Set CCR value
      break;
    case 2:
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x30; // Set channel 2 to output
      (*(pin_struct.base + TIM_CCMR1_OFFSET + 8)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR1_OFFSET + 8)) |= 0x6; // Set channel 2 to PWM mode 1
      (*(pin_struct.base + TIM_CCR2_OFFSET)) = ccr; // Set CCR value
      break;
    case 3:
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x3; // Set channel 3 to output
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) |= 0x6; // Set channel 3 to PWM mode 1
      (*(pin_struct.base + TIM_CCR3_OFFSET)) = ccr; // Set CCR value
      break;
    case 4:
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x30; // Set channel 4 to output
      (*(pin_struct.base + TIM_CCMR2_OFFSET + 8)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR2_OFFSET + 8)) |= 0x6; // Set channel 4 to PWM mode 1
      (*(pin_struct.base + TIM_CCR4_OFFSET)) = ccr; // Set CCR value
      break;
  }

  (*(pin_struct.base + TIM_ARR_OFFSET)) = arr; // Set the period of the timer

  (*(pin_struct.base + TIM_EGR_OFFSET)) |= 1; // Trigger update of registers
  while((*(pin_struct.base + TIM_EGR_OFFSET)) | 1); // Wait for update to complete

  (*(pin_struct.base + TIM_CCER_OFFSET)) |= (1 << ((pin_struct.channel - 1) * 4)); // Enable the output of the channel
  (*(pin_struct.base + TIM_CR1_OFFSET)) |= 1; // Enable timer channel 

  pin_struct.frequency = frequency;
  pin_struct.running = true;
}

void tal_pwm_pin_set_channel_duty_cycle(int pin, uint8_t dutyCycle, bool* const err) {
  pwm_pin_t pin_struct;
  if(!get_pin_info(pin, &pin_struct)){ *err = true; return; }
  
  uint32_t f_timer = pin_struct.frequency * 65536; // Max ARR assumed as 65535 for flexibility
  uint32_t prescaler = (16000000 / f_timer) - 1; // TODO: determine system clock frequency

  if (prescaler > 65535) {
    prescaler = 65535;
    f_timer = 16000000 / (prescaler + 1);
  }

  (*(pin_struct.base + TIM_PSC_OFFSET)) = prescaler; // Set the prescaler of the timer

  uint32_t arr = (f_timer / pin_struct.frequency) - 1;
  uint32_t ccr = ((dutyCycle / 256) / 100) * (arr + 1);

  switch(pin_struct.channel){
    case 1:
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x3; // Set channel 1 to output
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) |= 0x6; // Set channel 1 to PWM mode 1
      (*(pin_struct.base + TIM_CCR1_OFFSET)) = ccr; // Set CCR value
      break;
    case 2:
      (*(pin_struct.base + TIM_CCMR1_OFFSET)) &= ~0x30; // Set channel 2 to output
      (*(pin_struct.base + TIM_CCMR1_OFFSET + 8)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR1_OFFSET + 8)) |= 0x6; // Set channel 2 to PWM mode 1
      (*(pin_struct.base + TIM_CCR2_OFFSET)) = ccr; // Set CCR value
      break;
    case 3:
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x3; // Set channel 3 to output
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) |= 0x6; // Set channel 3 to PWM mode 1
      (*(pin_struct.base + TIM_CCR3_OFFSET)) = ccr; // Set CCR value
      break;
    case 4:
      (*(pin_struct.base + TIM_CCMR2_OFFSET)) &= ~0x30; // Set channel 4 to output
      (*(pin_struct.base + TIM_CCMR2_OFFSET + 8)) &= ~0x6; // Clear
      (*(pin_struct.base + TIM_CCMR2_OFFSET + 8)) |= 0x6; // Set channel 4 to PWM mode 1
      (*(pin_struct.base + TIM_CCR4_OFFSET)) = ccr; // Set CCR value
      break;
  }

  (*(pin_struct.base + TIM_ARR_OFFSET)) = arr; // Set the period of the timer

  (*(pin_struct.base + TIM_EGR_OFFSET)) |= 1; // Trigger update of registers
  while((*(pin_struct.base + TIM_EGR_OFFSET)) | 1); // Wait for update to complete

  (*(pin_struct.base + TIM_CCER_OFFSET)) |= (1 << ((pin_struct.channel - 1) * 4)); // Enable the output of the channel
  (*(pin_struct.base + TIM_CR1_OFFSET)) |= 1; // Enable timer channel 

  pin_struct.dutyCycle = dutyCycle;
  pin_struct.running = true;
}

void tal_pwm_pin_enable(int pin, bool* const err) {
  pwm_pin_t pin_struct;
  if(!get_pin_info(pin, &pin_struct)){ *err = true; return; }
  
  (*(pin_struct.pinreg + (2 * pin_struct.num_in_group))) &= ~0x3; // Clear function mode
  (*(pin_struct.pinreg + (2 * pin_struct.num_in_group))) |= 0x2; // Set pin to alternate function mode
  pin_struct.running = true;
}

void tal_pwm_pin_disable(int pin, bool* const err) {
  pwm_pin_t pin_struct;
  if(!get_pin_info(pin, &pin_struct)){ *err = true; return; }

  (*(pin_struct.pinreg + (2 * pin_struct.num_in_group))) &= 0x3; // Set function mode to analog mode
  pin_struct.running = false;
}

bool tal_pwm_is_running(int pin, bool* const err) {
  pwm_pin_t pin_struct;
  if(!get_pin_info(pin, &pin_struct)){ *err = true; return false; }
  return pin_struct.running;
}

bool get_pin_info(int pin, pwm_pin_t* pin_info) {
  for (int i = 0; i < sizeof(valid_pins)/sizeof(valid_pins[0]); i++){
    if (valid_pins[i].pin == pin){
      *pin_info = valid_pins[i];
      return true;
    }
  }
  return false;
}

#if defined(__cplusplus)
  }
#endif