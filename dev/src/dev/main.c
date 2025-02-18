#include <stdint.h>
#include "titan/i2c.h"
#include "STM32H745/resource/mmio.h"

volatile uint32_t tick = 0;

// flashes LED
void flash_led(void) {
  init_gpio();
  tal_set_mode(49, 1);
  bool pin_out = 0;
  while (true) {
    tal_set_pin(49, pin_out);
    for (tick = 0; tick < 100000; tick++);
    pin_out = !pin_out;
  }
}

void i2c_test(void) {
  SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_I2CxEN[1]);
  __asm__ volatile ("bkpt #0");
  tal_enable_I2C();
  __asm__ volatile ("bkpt #0");
  uint8_t num = 0xF0;
  while(1) {
    tal_transmit_I2C(40, &num, 1);
    __asm__ volatile ("bkpt #0");
  }
}

void main(void) {
  i2c_test();
}