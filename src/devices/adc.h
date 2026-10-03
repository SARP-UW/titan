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
 * @file devices/adc.h
 * @authors Jude Merritt
 * @brief ADS124S0x ADC driver (TI SBAS660C)
 *
 * Usage requirements:
 *  - spi_init() must have been called for the ADC's SPI instance (any mode; the
 *    driver switches the bus to SPI mode 1 for its own transfers and restores it).
 *  - systick_init() must have been called (the driver waits for conversions).
 *  - START/SYNC is tied low on this board, so conversions are controlled with the
 *    START command (datasheet 9.5.3.5).
 */

#include <stdint.h>
#include <stdbool.h>
#include "peripheral/errc.h"

#pragma once

struct adc_spi_dev {
    uint8_t inst;
    uint8_t ss_pin;
};

/** Analog input / MUX codes (INPMUX, IDACMUX). */
enum adc_pin {
    AIN0   = 0x00,
    AIN1   = 0x01,
    AIN2   = 0x02,
    AIN3   = 0x03,
    AIN4   = 0x04,
    AIN5   = 0x05,
    AIN6   = 0x06,         // Also REFP1
    AIN7   = 0x07,         // Also REFN1
    AIN8   = 0x08,         // Can also be GPIO0
    AIN9   = 0x09,         // Can also be GPIO1
    AIN10  = 0x0A,         // Can also be GPIO2
    AIN11  = 0x0B,         // Can also be GPIO3
    AINCOM = 0x0C,         // Common input for single-ended measurements
    IDAC_DISCONNECT = 0x0F // IDAC output not connected (use when only one IDAC is needed)
};

/** IDACMAG IMAG[3:0] codes. */
enum idac_mag {
    IDAC_OFF      = 0x00,
    IDAC_10_UA    = 0x01,
    IDAC_50_UA    = 0x02,
    IDAC_100_UA   = 0x03,
    IDAC_250_UA   = 0x04,
    IDAC_500_UA   = 0x05,
    IDAC_750_UA   = 0x06,
    IDAC_1000_UA  = 0x07,
    IDAC_1500_UA  = 0x08,
    IDAC_2000_UA  = 0x09
};

/**
 * PGA gain codes. GAIN_1 bypasses the PGA (PGA_EN = 00), which is required for
 * single-ended inputs referenced to AVSS and allows inputs from AVSS - 50 mV to
 * AVDD + 50 mV. Higher gains enable the PGA (input must stay 150 mV+ from the rails).
 */
enum adc_gain {
    GAIN_1   = 0x00,
    GAIN_2   = 0x01,
    GAIN_4   = 0x02,
    GAIN_8   = 0x03,
    GAIN_16  = 0x04,
    GAIN_32  = 0x05,
    GAIN_64  = 0x06,
    GAIN_128 = 0x07
};

/** REF REFSEL[1:0] codes (datasheet Table 31). */
enum adc_ref_voltage_source {
    REF_EXT_0    = 0x00, // REFP0 / REFN0
    REF_EXT_1    = 0x01, // REFP1 / REFN1 (shares AIN6 / AIN7)
    REF_INTERNAL = 0x02  // Internal 2.5 V reference
};

/** DATARATE DR[3:0] codes (low-latency filter, continuous conversion). */
enum adc_data_rate {
    ADC_DR_2_5_SPS  = 0x00,
    ADC_DR_5_SPS    = 0x01,
    ADC_DR_10_SPS   = 0x02,
    ADC_DR_16_6_SPS = 0x03,
    ADC_DR_20_SPS   = 0x04,
    ADC_DR_50_SPS   = 0x05,
    ADC_DR_60_SPS   = 0x06,
    ADC_DR_100_SPS  = 0x07,
    ADC_DR_200_SPS  = 0x08,
    ADC_DR_400_SPS  = 0x09,
    ADC_DR_800_SPS  = 0x0A,
    ADC_DR_1000_SPS = 0x0B,
    ADC_DR_2000_SPS = 0x0C,
    ADC_DR_4000_SPS = 0x0D
};

struct adc_channel {
    enum adc_pin pos_pin;
    enum adc_pin neg_pin;
    enum adc_gain gain;
    enum adc_ref_voltage_source source;
    uint32_t ref_mv;   // Reference voltage in millivolts (2500 for the internal reference)
    char* name;
};

/**
 * @brief Initializes the ADC: checks the device ID, writes a known configuration,
 *        starts continuous conversions and verifies that conversions are running.
 *        Only one ADC is supported at a time (a second call replaces the first).
 */
void adc_init(struct adc_spi_dev* device, enum ti_errc_t* errc);

/**
 * @brief Sets the conversion data rate (default after adc_init: 400 SPS).
 *        Lower rates reduce noise; 20 SPS and below reject 50/60 Hz.
 */
void adc_set_data_rate(enum adc_data_rate rate, enum ti_errc_t* errc);

/**
 * @brief Converts a channel and returns the raw two's-complement code (-2^23..2^23-1).
 *        Blocks for one full conversion with the channel's settings.
 */
int32_t adc_read_raw(const struct adc_channel* channel, enum ti_errc_t* errc);

/** @brief Converts a channel and returns the input voltage in microvolts. */
int32_t adc_read_microvolts(const struct adc_channel* channel, enum ti_errc_t* errc);

/** @brief Converts a channel and returns the input voltage in millivolts (rounded). */
int adc_read_voltage(const struct adc_channel* channel, enum ti_errc_t* errc);

/**
 * @brief Returns channel1 - channel2 in millivolts from two separate conversions.
 *        For a true differential measurement, set pos_pin/neg_pin of one channel instead.
 */
int adc_read_voltage_diff(struct adc_channel channel1, struct adc_channel channel2, enum ti_errc_t* errc);

/** @brief Sets both IDAC magnitudes and routes IDAC1 to pin1 and IDAC2 to pin2. */
void adc_set_idac(enum idac_mag magnitude, enum adc_pin pin1, enum adc_pin pin2, enum ti_errc_t* errc);

/**
 * @brief Configures AIN8-AIN11 as GPIO0-GPIO3. GPIO levels are referenced to AVDD/AVSS.
 * @param default_high  Output level (ignored for inputs).
 * @param input         true = input, false = output.
 */
void adc_set_gpio(enum adc_pin pin, bool default_high, bool input, enum ti_errc_t* errc);

char* adc_get_channel_name(struct adc_channel channel);

/** @brief Reads DEV_ID[2:0] of the ID register: 0 = ADS124S08, 1 = ADS124S06. */
uint8_t adc_read_device_id(enum ti_errc_t* errc);