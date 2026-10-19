
#include "peripheral/gpio.h"
#include "peripheral/watchdog.h"
#include "internal/alloc.h"
#include "peripheral/uart.h"
#include "peripheral/pwm.h"
#include "peripheral/spi.h"
#include "peripheral/systick.h"
#include <stdio.h>

#define USR_BUTTON 9
#define GREEN_LED 49
#define YELLOW_LED 139
#define RED_LED 74

// NOLINTNEXTLINE(readability-identifier-naming)
void _start() { // NOLINT(misc-use-internal-linkage)
    tal_enable_clock(RED_LED);
    tal_set_mode(RED_LED, 1);
    systick_init();


    while(true){
        tal_set_pin(RED_LED, 1);
        systick_delay(1000);
        tal_set_pin(RED_LED, 0);
        systick_delay(1000);
    }
}