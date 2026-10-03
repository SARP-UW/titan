#include "peripheral/spi.h"
#include "peripheral/systick.h"
#include "internal/mmio.h"
#include "devices/adc.h"
#include "app/utils/pinout.h"
#include <stdint.h>

// Pause the debugger and inspect these.
volatile extern int32_t adc_uv = 0;                     // Latest AIN0-vs-AINCOM reading, microvolts
volatile enum ti_errc_t adc_errc = TI_ERRC_NONE; // Last error (init or read)


void _start() {
    systick_init();
    
    
}
