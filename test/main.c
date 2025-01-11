#if defined(__cplusplus)
  extern "C" {
#endif

#include "platform/gpio.h"

void main(void) { 
  *(volatile uint32_t*)0x5802452C |= (1U << 21);
  *(volatile uint32_t*)0x58024520 |= ((1U << 11) - 1U);
  
}

#if defined(__cplusplus)
  }
#endif