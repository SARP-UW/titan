
#include "devices/gnss.h"
#include "peripheral/spi.h"
#include "peripheral/errc.h"
#include <stdint.h>
#include <stdio.h>

/*
 * STM32H745 GNSS SPI CONNECTIONS
 *
 *          SCK          MISO         MOSI
 * SPI1:    PA5 (44)     PA6 (45)     PA7 (46)
 * SPI2:    PB13 (73)    PB14 (74)    PB15 (75)
 * SPI3:    PC10 (109)   PC11 (110)   PC12 (111)
 * SPI4:    PE2 (1)      PE5 (4)      PE6 (5)
 * SPI5:    PF7 (21)     PF8 (22)     PF9 (23)
 * SPI6:    PG12 (125)   PG13 (126)   PG14 (127)
 *
 * GPS WIRING:
 *   PB13  -> GPS SCK 73
 *   PB14  <- GPS MISO 74
 *   PB15  -> GPS MOSI 75
 *   PA4   -> GPS CS_N 43 CHOSE YOURSELF
 *   GND   -> GPS GND
 *   3.3V  -> GPS VCC
 *   GND   -> GPS D_SEL (SPI mode)
 *
 * CS_N is active low.
 */

void gnss_test(void) {
    enum ti_errc_t err = TI_ERRC_NONE;

    // Verify that 43 maps to PA4 in our GPIO driver.
    uint8_t gps_cs_pin = 43;

    // Create the GPS device BEFORE using &gps.
    gnss_t gps = {0};

    // Set SPI connection.
    gps.spi_config.spi_inst = 2;
    gps.spi_config.ss_pin = gps_cs_pin;

    // Set GPS configuration.
    gps.config.meas_rate_ms = 1000;
    gps.config.dyn_model = GNSS_DYN_PORTABLE;
    gps.config.power_mode = GNSS_POWER_CONTINUOUS;
    gps.config.constellation_mask = GNSS_CONSTELLATION_GPS;

    // TEST 1: Initialize GPS and SPI.
    // Assumes gnss_init initializes the SPI interface.
    printf("TEST 1: Initialize GPS and SPI. Testing gnss_init...\n");

    gnss_init(&gps, &err);

    if (err != TI_ERRC_NONE) {
        printf("FAIL: gnss_init\n");
        printf("Error code: %d\n", (int)err);
        return;
    }

    printf("PASS: GPS initialized: %u\n",
           (unsigned)gps.initialized);

    // Create UBX CFG-RATE payload.
    ubx_cfg_rate_t rate_cfg = {0};

    rate_cfg.measRate = 1000;
    rate_cfg.navRate = 1;
    rate_cfg.timeRef = 0;

    // TEST 2: Send a UBX configuration message.
    printf("TTEST 2: Send a UBX configuration message. esting ubx_send_msg...\n");

    err = TI_ERRC_NONE;

    ubx_send_msg(
        &gps,
        UBX_CLASS_CFG,
        UBX_CFG_RATE,
        &rate_cfg,
        sizeof(rate_cfg),
        &err
    );

    if (err != TI_ERRC_NONE) {
        printf("FAIL: ubx_send_msg\n");
        printf("Error code: %d\n", (int)err);
        return;
    }

    printf("PASS: SPI transmission completed\n");

    // TEST 3: Send configuration and wait for ACK.
    printf("TEST 3: Send configuration and wait for ACK. Testing ubx_configure...\n");

    err = TI_ERRC_NONE;

    ubx_configure(
        &gps,
        UBX_CLASS_CFG,
        UBX_CFG_RATE,
        &rate_cfg,
        sizeof(rate_cfg),
        &err
    );

    if (err != TI_ERRC_NONE) {
        printf("FAIL: ubx_configure\n");
        printf("Error code: %d\n", (int)err);
        return;
    }

    printf("PASS: GPS acknowledged CFG-RATE\n");

    // TEST 4: Get navigation data.
    printf("\nTEST 4: Get navigation data. TESTING gnss_get_pvt...\n");

    gnss_pvt_t pvt = {0};

    err = TI_ERRC_NONE;

    gnss_get_pvt(&gps, &pvt, &err);

    if (err != TI_ERRC_NONE) {
        printf("FAIL: gnss_get_pvt\n");
        printf("Error code: %d\n", (int)err);
        return;
    }

    printf("PASS: gnss_get_pvt\n");

    printf("Date: %04u-%02u-%02u\n",
           (unsigned)pvt.year,
           (unsigned)pvt.month,
           (unsigned)pvt.day);

    printf("Time: %02u:%02u:%02u UTC\n",
           (unsigned)pvt.hour,
           (unsigned)pvt.min,
           (unsigned)pvt.sec);

    printf("Fix type: %d\n", (int)pvt.fix);
    printf("Satellites: %u\n",
           (unsigned)pvt.num_sv);

    printf("Latitude: %ld (degrees x 1e-7)\n",
           (long)pvt.lat);
    printf("Longitude: %ld (degrees x 1e-7)\n",
           (long)pvt.lon);

    printf("Height: %ld mm\n",
           (long)pvt.height);
    printf("Altitude above sea level: %ld mm\n",
           (long)pvt.h_msl);

    printf("Velocity North: %ld mm/s\n",
           (long)pvt.vel_n);
    printf("Velocity East: %ld mm/s\n",
           (long)pvt.vel_e);
    printf("Velocity Down: %ld mm/s\n",
           (long)pvt.vel_d);

    printf("Position DOP (x 0.01): %u\n",
           (unsigned)pvt.p_dop);

    printf("\n===== GNSS TESTS COMPLETE =====\n");

    while (1) {
    }
}

