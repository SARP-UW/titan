#include "devices/current.h"
#include "peripheral/i2c.h"
#include "peripheral/systick.h"

#define BATTERY_ADDR 0x44
#define UMBILICAL_ADDR 0x45
#define BOARD_ADDR 0x42

void _start(void) {
    systick_init();

    enum ti_errc_t err;
    i2c_init(1, &err);
    asm("BKPT #0");

    struct current_i2c_dev dev = {
        .inst = 1,
        .addr = BATTERY_ADDR,
    };

    struct current_config_t config = {
        .shunt_uohms = 2000,    // 0.002 ohm resistor (found on altium)
        .current_lsb_ua = 1000, // arbitrary but reasonable value
        .adc_config = 0x4127,   // default value
    };
    struct current_result_t result;

    current_init(&dev, &config, &err);

    while (1) {
        current_read(&dev, &config, &result, &err);
        asm("BKPT #0");
    }
}
