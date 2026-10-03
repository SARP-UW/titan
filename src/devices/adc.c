/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @file devices/adc.c
 * @authors Jude Merritt
 * @brief ADS124S0x ADC driver (TI SBAS660C)
 *
 * Section numbers in comments refer to the ADS124S0x datasheet, SBAS660C.
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "devices/adc.h"
#include "peripheral/spi.h"
#include "peripheral/systick.h"
#include "internal/mmio.h"
#include "peripheral/errc.h"

/**************************************************************************************************
 * @section Device constants (Table 24, Table 25)
 **************************************************************************************************/

// Commands
#define CMD_START      0x08
#define CMD_RDATA      0x12
#define CMD_RREG       0x20  // 001r rrrr
#define CMD_WREG       0x40  // 010r rrrr

// Registers
#define REG_ID         0x00
#define REG_STATUS     0x01
#define REG_INPMUX     0x02
#define REG_PGA        0x03
#define REG_DATARATE   0x04
#define REG_REF        0x05
#define REG_IDACMAG    0x06
#define REG_IDACMUX    0x07
#define REG_VBIAS      0x08
#define REG_SYS        0x09
#define REG_GPIODAT    0x10
#define REG_GPIOCON    0x11

// STATUS
#define STATUS_RDY     0x40  // 0 = ready for communication (NOT a data-ready flag)

// PGA
#define PGA_EN_ON      0x08  // PGA_EN[1:0] = 01
#define PGA_BYPASS     0x00  // PGA_EN[1:0] = 00 with GAIN = 000

// DATARATE: G_CHOP=0, CLK=0 (internal), MODE=0 (continuous), FILTER=1 (low-latency)
#define DATARATE_BASE  0x10

// REF: REFCON = 10 (internal reference always on; required for the IDACs)
#define REF_REFCON_ON      0x02
#define REF_REFP_BUF_OFF   0x20
#define REF_REFN_BUF_OFF   0x10

// SYS
#define SYS_DEFAULT        0x10  // SYS_MON off, CAL_SAMP = 8, no timeout/CRC/STATUS byte
#define SYS_MON_AVDD_DIV4  0x60  // SYS_MON = 011: (AVDD - AVSS) / 4

#define DEV_ID_ADS124S08   0x00
#define DEV_ID_ADS124S06   0x01

#define MAX_REG_BURST      8     // Largest register block this driver reads/writes at once
#define RDY_POLL_TRIES     1000

// First-data time for the low-latency filter in continuous mode, in microseconds
// (Table 13), indexed by DR[3:0]. The programmable delay (14 tMOD = 55 us) is not included.
static const uint32_t first_data_us[14] = {
    406504, 206504, 106504, 60254, 56504, 20156, 16910,
    10156,  5156,   2656,   1406,  1156,  656,   406
};

/**************************************************************************************************
 * @section Driver state
 **************************************************************************************************/

static struct adc_spi_dev dev;
static bool dev_ready = false;
static uint8_t data_rate = ADC_DR_400_SPS;

/**************************************************************************************************
 * @section SPI helpers
 **************************************************************************************************/

// One framed SPI transaction in mode 1 (the only mode the ADS124S0x supports, 9.5.1).
// The bus mode is restored afterwards so other devices on the same bus are unaffected.
static void adc_xfer(uint8_t* src, uint8_t* dst, uint8_t len, enum ti_errc_t* errc) {
    uint8_t prev_mode = spi_set_mode(dev.inst, MODE_1, errc);
    if (*errc != TI_ERRC_NONE) return;

    spi_transfer_sync(dev.inst, dev.ss_pin, src, dst, len, errc);

    enum ti_errc_t restore_errc;
    spi_set_mode(dev.inst, prev_mode, &restore_errc);
    if (*errc == TI_ERRC_NONE) *errc = restore_errc;
}

static void spi_command(uint8_t cmd, enum ti_errc_t* errc) {
    uint8_t src[1] = { cmd };
    uint8_t dst[1] = { 0 };
    adc_xfer(src, dst, 1, errc);
}

// Reads 'count' consecutive registers starting at 'reg' into 'out' (9.5.3.11).
static void spi_rreg(uint8_t reg, uint8_t count, uint8_t* out, enum ti_errc_t* errc) {
    if (count == 0 || count > MAX_REG_BURST) { *errc = TI_ERRC_INVALID_ARG; return; }

    uint8_t src[2 + MAX_REG_BURST] = { 0 };  // DIN held low after the command bytes
    uint8_t dst[2 + MAX_REG_BURST] = { 0 };
    src[0] = (uint8_t)(CMD_RREG | (reg & 0x1F));
    src[1] = (uint8_t)(count - 1);

    adc_xfer(src, dst, (uint8_t)(2 + count), errc);
    if (*errc != TI_ERRC_NONE) return;

    for (uint8_t i = 0; i < count; i++) out[i] = dst[2 + i];
}

static uint8_t spi_rreg1(uint8_t reg, enum ti_errc_t* errc) {
    uint8_t val = 0;
    spi_rreg(reg, 1, &val, errc);
    return val;
}

// Writes 'count' consecutive registers starting at 'reg' from 'data' (9.5.3.12).
static void spi_wreg(uint8_t reg, uint8_t count, const uint8_t* data, enum ti_errc_t* errc) {
    if (count == 0 || count > MAX_REG_BURST) { *errc = TI_ERRC_INVALID_ARG; return; }

    uint8_t src[2 + MAX_REG_BURST] = { 0 };
    uint8_t dst[2 + MAX_REG_BURST] = { 0 };
    src[0] = (uint8_t)(CMD_WREG | (reg & 0x1F));
    src[1] = (uint8_t)(count - 1);
    for (uint8_t i = 0; i < count; i++) src[2 + i] = data[i];

    adc_xfer(src, dst, (uint8_t)(2 + count), errc);
}

static void spi_wreg1(uint8_t reg, uint8_t val, enum ti_errc_t* errc) {
    spi_wreg(reg, 1, &val, errc);
}

// Reads the latest conversion result from the data-holding register (9.5.4.2).
// RDATA is safe at any time, with no need to synchronize to DRDY.
static int32_t read_data(enum ti_errc_t* errc) {
    uint8_t src[4] = { CMD_RDATA, 0, 0, 0 };
    uint8_t dst[4] = { 0 };
    adc_xfer(src, dst, 4, errc);
    if (*errc != TI_ERRC_NONE) return 0;

    // 24-bit two's complement, MSB first (9.5.2)
    int32_t code = ((int32_t)dst[1] << 16) | ((int32_t)dst[2] << 8) | (int32_t)dst[3];
    if (code & 0x800000) code -= 0x1000000;
    return code;
}

/**************************************************************************************************
 * @section Timing helpers
 **************************************************************************************************/

static bool systick_running(void) {
    return READ_FIELD(STK_CSR, STK_CSR_ENABLE) != 0;
}

// Waits long enough for a full conversion to complete after a configuration write
// restarted the digital filter (9.5.3.12): first-data time + programmable delay,
// +2% for internal oscillator tolerance (1.5% max), rounded up to whole ms, +1 ms
// for SysTick granularity.
static void wait_for_conversion(void) {
    uint32_t us = first_data_us[data_rate] + 55U;
    us += us / 50U;
    systick_delay((us + 999U) / 1000U + 1U);
}

/**************************************************************************************************
 * @section Configuration helpers
 **************************************************************************************************/

static uint8_t ref_reg_value(enum adc_ref_voltage_source source) {
    uint8_t ref = REF_REFCON_ON | (uint8_t)((source & 0x03) << 2);
    if (source == REF_INTERNAL) {
        // Datasheet Table 31 note 1: disable both buffers with the internal reference.
        ref |= REF_REFP_BUF_OFF | REF_REFN_BUF_OFF;
    } else {
        // Reset default: positive buffer on, negative buffer off (REFNx normally at AVSS).
        ref |= REF_REFN_BUF_OFF;
    }
    return ref;
}

static uint8_t pga_reg_value(enum adc_gain gain) {
    // Gain 1: bypass the PGA so single-ended inputs down to AVSS work (9.3.2.3, Table 29).
    if ((gain & 0x07) == GAIN_1) return PGA_BYPASS;
    return (uint8_t)(PGA_EN_ON | (gain & 0x07));
}

static bool check_ready(enum ti_errc_t* errc) {
    if (!dev_ready) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "ADC not initialized");
        return false;
    }
    return true;
}

/**************************************************************************************************
 * @section Public functions
 **************************************************************************************************/

void adc_init(struct adc_spi_dev* device, enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;
    *errc = TI_ERRC_NONE;
    dev_ready = false;

    if (!device || device->inst < 1 || device->inst > 6) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid ADC device"); return;
    }
    if (!systick_running()) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "systick_init() must be called before adc_init()"); return;
    }
    dev = *device;
    data_rate = ADC_DR_400_SPS;

    // 1. Power-on reset needs 2.2 ms before communication (9.4.1.1), then RDY = 0.
    //    No RESET command is needed: every configuration register is written below.
    systick_delay(3);
    int tries = 0;
    while (spi_rreg1(REG_STATUS, errc) & STATUS_RDY) {
        if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC STATUS read failed"); return; }
        if (++tries >= RDY_POLL_TRIES) { TI_SET_ERRC(errc, TI_ERRC_TIMEOUT, "ADC never became ready"); return; }
    }
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC STATUS read failed"); return; }

    // 2. Check the device ID. A wrong ID usually means a wiring, CS or SPI-mode problem.
    uint8_t id = adc_read_device_id(errc);
    if (*errc != TI_ERRC_NONE) return;
    if (id != DEV_ID_ADS124S08 && id != DEV_ID_ADS124S06) {
        TI_SET_ERRC(errc, TI_ERRC_DEVICE, "Unexpected ADC device ID"); return;
    }

    // 3. Clear the FL_POR flag.
    spi_wreg1(REG_STATUS, 0x00, errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC STATUS write failed"); return; }

    // 4. Write a complete known configuration (02h-09h) and read it back.
    const uint8_t cfg[8] = {
        (AIN0 << 4) | AINCOM,               // INPMUX
        PGA_BYPASS,                         // PGA: bypassed, gain 1
        DATARATE_BASE | data_rate,          // DATARATE: low-latency, continuous, internal clock
        ref_reg_value(REF_INTERNAL),        // REF: internal 2.5 V always on and selected
        0x00,                               // IDACMAG: off
        0xFF,                               // IDACMUX: both disconnected
        0x00,                               // VBIAS: off
        SYS_DEFAULT                         // SYS
    };
    spi_wreg(REG_INPMUX, sizeof(cfg), cfg, errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC config write failed"); return; }

    uint8_t readback[8] = { 0 };
    spi_rreg(REG_INPMUX, sizeof(readback), readback, errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC config readback failed"); return; }
    for (uint8_t i = 0; i < sizeof(cfg); i++) {
        if (readback[i] != cfg[i]) {
            TI_SET_ERRC(errc, TI_ERRC_DEVICE, "ADC config readback mismatch"); return;
        }
    }

    // 5. Internal reference start-up time: up to 7 ms with 47 uF (Table 10).
    systick_delay(8);

    // 6. Start continuous conversions (START/SYNC is tied low, so the command is decoded).
    spi_command(CMD_START, errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC START failed"); return; }

    // 7. Prove conversions are running: measure (AVDD - AVSS) / 4 with the supply
    //    monitor. AVDD of 2.7-5.25 V gives 0.675-1.31 V. Conversion data are cleared
    //    when a config write restarts the filter, so 0 here means nothing converted.
    spi_wreg1(REG_SYS, SYS_DEFAULT | SYS_MON_AVDD_DIV4, errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC SYS write failed"); return; }
    wait_for_conversion();
    int32_t code = read_data(errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC RDATA failed"); return; }

    spi_wreg1(REG_SYS, SYS_DEFAULT, errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC SYS restore failed"); return; }

    // 0.6 V .. 1.4 V against the 2.5 V internal reference
    const int32_t min_code = (int32_t)((600LL  << 23) / 2500);
    const int32_t max_code = (int32_t)((1400LL << 23) / 2500);
    if (code < min_code || code > max_code) {
        TI_SET_ERRC(errc, TI_ERRC_DEVICE,
                    "ADC not converting or AVDD out of range");
        return;
    }

    dev_ready = true;
}

void adc_set_data_rate(enum adc_data_rate rate, enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;
    *errc = TI_ERRC_NONE;
    if (!check_ready(errc)) return;
    if ((uint8_t)rate > ADC_DR_4000_SPS) { TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid data rate"); return; }

    spi_wreg1(REG_DATARATE, (uint8_t)(DATARATE_BASE | rate), errc);
    if (*errc == TI_ERRC_NONE) data_rate = (uint8_t)rate;
}

int32_t adc_read_raw(const struct adc_channel* channel, enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;
    *errc = TI_ERRC_NONE;
    if (!check_ready(errc)) return 0;
    if (!channel || channel->pos_pin > AINCOM || channel->neg_pin > AINCOM ||
        channel->source > REF_INTERNAL) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid ADC channel"); return 0;
    }

    // INPMUX, PGA, DATARATE, REF in one burst. Any changed value restarts the
    // conversion (9.5.3.12), so wait a full first-conversion time before reading.
    // If nothing changed, conversions keep running and the wait still guarantees
    // the result was taken after this call.
    const uint8_t cfg[4] = {
        (uint8_t)(((channel->pos_pin & 0x0F) << 4) | (channel->neg_pin & 0x0F)),
        pga_reg_value(channel->gain),
        (uint8_t)(DATARATE_BASE | data_rate),
        ref_reg_value(channel->source)
    };
    spi_wreg(REG_INPMUX, sizeof(cfg), cfg, errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC channel config failed"); return 0; }

    wait_for_conversion();

    int32_t code = read_data(errc);
    if (*errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "ADC RDATA failed"); return 0; }
    return code;
}

int32_t adc_read_microvolts(const struct adc_channel* channel, enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;

    int32_t code = adc_read_raw(channel, errc);
    if (*errc != TI_ERRC_NONE) return 0;

    // 1 LSB = (2 * VREF / Gain) / 2^24 = VREF / (Gain * 2^23)   (Equation 11)
    int64_t ref_uv = (int64_t)channel->ref_mv * 1000;
    int64_t divisor = (int64_t)1 << (23 + (channel->gain & 0x07));
    if (divisor == 0){
        return 0;
    }
    return (int32_t)(((int64_t)code * ref_uv) / divisor);
}

int adc_read_voltage(const struct adc_channel* channel, enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;

    int32_t uv = adc_read_microvolts(channel, errc);
    if (*errc != TI_ERRC_NONE) return 0;
    return (uv >= 0) ? (uv + 500) / 1000 : (uv - 500) / 1000;
}

int adc_read_voltage_diff(struct adc_channel channel1, struct adc_channel channel2, enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;

    int v1 = adc_read_voltage(&channel1, errc);
    if (*errc != TI_ERRC_NONE) return 0;
    int v2 = adc_read_voltage(&channel2, errc);
    if (*errc != TI_ERRC_NONE) return 0;
    return v1 - v2;
}

void adc_set_idac(enum idac_mag magnitude, enum adc_pin pin1, enum adc_pin pin2, enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;
    *errc = TI_ERRC_NONE;
    if (!check_ready(errc)) return;
    if ((uint8_t)magnitude > IDAC_2000_UA) { TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid IDAC magnitude"); return; }

    // Keep FL_RAIL_EN / PSW (bits 7:6); bits 5:4 are reserved and must be 0.
    uint8_t mag = spi_rreg1(REG_IDACMAG, errc);
    if (*errc != TI_ERRC_NONE) return;
    mag = (uint8_t)((mag & 0xC0) | ((uint8_t)magnitude & 0x0F));
    spi_wreg1(REG_IDACMAG, mag, errc);
    if (*errc != TI_ERRC_NONE) return;

    // IDACMUX: I2MUX[7:4], I1MUX[3:0]. The internal reference must be on (it is).
    uint8_t mux = (uint8_t)(((pin2 & 0x0F) << 4) | (pin1 & 0x0F));
    spi_wreg1(REG_IDACMUX, mux, errc);
}

void adc_set_gpio(enum adc_pin pin, bool default_high, bool input, enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;
    *errc = TI_ERRC_NONE;
    if (!check_ready(errc)) return;
    if (pin < AIN8 || pin > AIN11) { TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Only AIN8-AIN11 can be GPIO"); return; }

    uint8_t idx = (uint8_t)(pin - AIN8);

    // Read-modify-write both registers so other GPIOs keep their configuration.
    // Set direction and level before enabling the pin as a GPIO (datasheet Figure 7).
    uint8_t dat = spi_rreg1(REG_GPIODAT, errc);
    if (*errc != TI_ERRC_NONE) return;
    dat &= (uint8_t)~((1U << (idx + 4)) | (1U << idx));
    if (input)        dat |= (uint8_t)(1U << (idx + 4));  // DIR = 1: input
    else if (default_high) dat |= (uint8_t)(1U << idx);   // DAT = 1: output high
    spi_wreg1(REG_GPIODAT, dat, errc);
    if (*errc != TI_ERRC_NONE) return;

    uint8_t con = spi_rreg1(REG_GPIOCON, errc);
    if (*errc != TI_ERRC_NONE) return;
    con = (uint8_t)((con | (1U << idx)) & 0x0F);
    spi_wreg1(REG_GPIOCON, con, errc);
}

char* adc_get_channel_name(struct adc_channel channel) {
    return channel.name;
}

uint8_t adc_read_device_id(enum ti_errc_t* errc) {
    enum ti_errc_t local_errc;
    if (!errc) errc = &local_errc;
    *errc = TI_ERRC_NONE;
    if (dev.inst < 1 || dev.inst > 6) { TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "ADC device not set"); return 0; }

    uint8_t id = spi_rreg1(REG_ID, errc);
    return (uint8_t)(id & 0x07);
}

/**
 * Hardware notes:
 * 1. RESET is tied high, CLK is tied low (internal oscillator) and DRDY is unconnected,
 *    so conversions are timed and read with RDATA.
 * 2. START/SYNC is tied low, so conversions are started with the START command.
 * 3. If errc is not TI_ERRC_NONE the return value has no meaning.
 */