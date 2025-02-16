#include <stdint.h>

void main(void) {
  volatile uint32_t counter = 0;
  while (1) {
    counter += 1;
  }
}