#include "peripheral/errc.h"
#include "peripheral/pwm.h"

void _start() {
    enum ti_errc_t errc = TI_ERRC_NONE;
    (void)ti_log_init();

    struct ti_pwm_config_t invalid_pwm = {
        .channel = 3,
        .instance = 3,
        .clock_freq = 4000000,
        .freq = 0,
        .duty = 250,
    };

    ti_set_pwm(invalid_pwm, &errc);

    while (1) {
        asm("BKPT #0");
    }
}
