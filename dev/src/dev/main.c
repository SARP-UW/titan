#include <stdint.h>


void main(void) {
  __asm__ volatile ("bkpt #3"); 
  volatile uint32_t counter = 0;
  while (1) {
    counter += 1;
  }
}