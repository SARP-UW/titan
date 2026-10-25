#include "devices/actuator.h"
#include "peripheral/gpio.h"
#include "peripheral/pwm.h"
#include "peripheral/spi.h"
#include "peripheral/systick.h"

// Example wiring (STM32 package pin numbers):
// SPI1: PA5 (44) -> SCK, PB5 (132) -> SDI, PA6 (45) <- SDO.
// PA4 (43) -> CS, PG6 (86) -> ENABLE, PB8 (136) -> selected channel's CNTL.
// CRC_EN and other CNTL inputs -> GND; VIO -> 3.3V; common GND and VM supply.
#define SPI_INSTANCE 4
#define CS_PIN 63
#define ENABLE_PIN 86
#define TEST_CHANNEL ACTUATOR_CHANNEL_0
#define HIGH_SIDE_MASK 0x0F // 1 bit per channel: load OUT-to-GND; 0: load VM-to-OUT.

static enum ti_errc_t errc;
volatile uint16_t readback;

// static void check_error(void) {
//     if (errc == TI_ERRC_NONE) return;
//     tal_set_pin(ENABLE_PIN, 0);
//     asm("BKPT #0"); // Inspect errc if initialization or a transfer fails.
//     while (1) asm("wfi");
// }

// NOLINTNEXTLINE(misc-use-internal-linkage,readability-identifier-naming)
void _start(void) {
    actuator_t dev;
    readback = 0;
    const actuator_spi_dev spi = {.spi_inst = SPI_INSTANCE, .ss_pin = CS_PIN};
    struct ti_pwm_config_t pwm = {
        .instance = 4, .channel = 3,
        .clock_freq = 64000000, .freq = 2000, .duty = 0,
    };

    systick_init();
    // tal_enable_clock(ENABLE_PIN);
    // tal_set_pin(ENABLE_PIN, 0);
    // tal_set_mode(ENABLE_PIN, 1);
    // ti_set_pwm(pwm, &errc); // Start CNTL low for SPI-only control.
    // check_error();
    uint8_t ss[] = {CS_PIN};
    spi_init(SPI_INSTANCE, MODE_0, ss, 1, &errc);
    // check_error();
    // tal_set_pin(ENABLE_PIN, 1);
    // systick_delay(5); // Allow startup; this delay is conservative at reset clocks.
    actuator_init(&dev, &spi, HIGH_SIDE_MASK, &errc);
    // check_error();
    // asm("BKPT #0");

    // One SPI write/read check while outputs are inactive.
    const uint8_t reg = ACTUATOR_CH0_BASE + (ACTUATOR_CH_STRIDE * TEST_CHANNEL) + ACTUATOR_CH_REG_DCH;
    actuator_write_reg(&dev, reg, 0x1234, NULL, &errc);
    // check_error();
    actuator_read_reg(&dev, reg, &readback, NULL, &errc);
    // check_error();
    // if (readback != 0x1234) errc = TI_ERRC_DEVICE;
    // check_error();
    // asm("BKPT #0"); // readback should be 0x1234
    actuator_write_reg(&dev, reg, ACTUATOR_DUTY_ON, NULL, &errc);
    // check_error();
    actuator_set_active(&dev, true, &errc);
    // check_error();
    // asm("BKPT #0");
    // systick_delay(5);
    // tal_enable_clock(101);
    // tal_set_mode(101, 1);

    // while(true){
    //     tal_set_pin(101, 1);

    //     tal_set_pin(101, 0);
    //     for (int i = 0; i < 10000000; i++) { 
    //         asm("NOP");
    //     }
    // } 

    
    // for (int i = 0; i < 100000000; i++) { 

    //     asm("NOP");
    // } 
    // tal_pull_pin(101, 1);
    // while (1) {
    //     asm("NOP");
    // }


    for (int i = 0; i < 10000000; i++) { 
        asm("NOP");
    }

    while (1) {
        actuator_set_channel_enable(&dev, TEST_CHANNEL, true, &errc);
        // check_error();
        // asm("BKPT #0"); // ON via SPI.
        for (int i = 0; i < 10000000; i++) { 
            asm("NOP");
        }
        actuator_set_channel_enable(&dev, TEST_CHANNEL, false, &errc);
        for (int i = 0; i < 10000000; i++) { 
            asm("NOP");
        }
        // check_error();
        // asm("BKPT #0"); // OFF via SPI

        // pwm.duty = 500;
        // ti_set_pwm(pwm, &errc); // SPI CNTL bit stays clear so external PWM can control it.
        // check_error();
        // systick_delay(5);
        // asm("BKPT #0"); // 50% PWM at 2kHz.

        // pwm.duty = 0;
        // ti_set_pwm(pwm, &errc);
        // check_error();
        // systick_delay(5);
        // asm("BKPT #0"); // OFF; next Continue repeats the sequence.
    }
}
