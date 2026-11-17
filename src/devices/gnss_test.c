
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
 *   PA4   -> GPS CS_N 43 CHOSE YOURSELF GPIO 20
 *   GND   -> GPS GND
 *   3.3V  -> GPS VCC
 *   GND   -> GPS D_SEL (SPI mode)
 *
 * CS_N is active low.
 */

void gnss_test(void) {
    enum ti_errc_t err = TI_ERRC_NONE;

    // GPS chip select
    uint8_t gps_cs_pin = 20;

    // Initialize SPI2 in Mode 0
    uint8_t ss_list[1] = {gps_cs_pin};

    printf("Initializing SPI3...\n");

    spi_init(3, 0, ss_list, 1, &err);

    if (err != TI_ERRC_NONE) {
        printf("FAIL: spi_init\n");
        printf("Error code: %d\n", (int)err);
        return;
    }

    printf("PASS: SPI2 initialized\n");

    // Create GPS device
    gnss_t gps = {0};

    // WHITCH SPI PERIPHERAL
    gps.spi_config.spi_inst = 3;
    // WHICH CHIP SELECT
    gps.spi_config.ss_pin = gps_cs_pin;



    // Create UBX CFG-RATE payload.
    ubx_cfg_rate_t rate_cfg = {0};

    rate_cfg.measRate = 1000;
    rate_cfg.navRate = 1;
    rate_cfg.timeRef = 0;

    // TEST 1: Send a UBX configuration message without acknowledgmenet.
    printf("TTEST 1: Send a UBX configuration message. esting ubx_send_msg...\n");

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

    // TEST 2: Send configuration and wait for ACK. WITH acklowledgment. 
    printf("TEST 2: Send configuration and wait for ACK. Testing ubx_configure...\n");

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

    // TEST 3 INITIALIZE ALL FOUR CONFIGURATIONS
    printf("TEST 3: Testing gnss_init...\n");
    // Configure GPS
    gps.config.meas_rate_ms = 1000;
    gps.config.dyn_model = GNSS_DYN_PORTABLE;
    gps.config.power_mode = GNSS_POWER_CONTINUOUS;
    gps.config.constellation_mask = GNSS_CONSTELLATION_GPS;

    gnss_init(&gps, &err);

    if (err != TI_ERRC_NONE) {
        printf("FAIL: gnss_init\n");
        printf("Error code: %d\n", (int)err);
        return;
    }

    printf("PASS: GPS initialized: %u\n",
           (unsigned)gps.initialized);

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

