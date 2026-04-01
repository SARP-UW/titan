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
 * @brief ADS124S0x ADC driver header
 */

#include <stdint.h>
#include <stdbool.h>
#include "peripheral/errc.h"

#pragma once

/**
 * @brief SPI specifications
 */
struct adc_spi_dev {
    uint8_t inst;
    uint8_t ss_pin;
    // TODO: Include SPI mode in SPI (as it relates to Rising/falling edge & default high/low)
};

/**
 * @brief Available pins on the ADS124S08 ADC
 */
enum adc_pin {
    AIN0   = 0x00, 
    AIN1   = 0x01,
    AIN2   = 0x02,
    AIN3   = 0x03, 
    AIN4   = 0x04, 
    AIN5   = 0x05,
    AIN6   = 0x06,
    AIN7   = 0x07,
    AIN8   = 0x08,         // Can also be GPIO0
    AIN9   = 0x09,         // Can also be GPIO1
    AIN10  = 0x0A,         // Can also be GPIO2
    AIN11  = 0x0B,         // Can also be GPIO3
    AINCOM = 0x0C,         // Common ground pin for single-ended measurements
    IDAC_DISCONNECT = 0x0F // This is useful if you only want to use one IDAC
};

/**
 * @brief IDAC Current Magnitudes
 */
enum idac_mag { 
    IDAC_OFF      = 0x00, // Pair this with the adc_set_idac function to turn off the idac
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
 * @brief PGA Gain Settings
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

/**
 * @brief Reference Voltage Sources
 */
enum adc_ref_voltage_source {
    REF_INTERNAL = 0x00, // 2.5V Internal
    REF_EXT_0    = 0x01, // External Ref 0
    REF_EXT_1    = 0x02, // External Ref 1
    REF_SUPPLY   = 0x03  // Analog Supply (AVDD/AVSS)
};

/**
 * @brief A structure defining a single ADC channel. 
 * Set neg_pin to AINCOM for a single-ended measurement.
 * Set neg_pin to any AINx for a differential measurement.
 */
struct adc_channel {
    enum adc_pin pos_pin;      
    enum adc_pin neg_pin;     
    enum adc_gain gain;         
    enum adc_ref_voltage_source source;   
    int8_t ref_voltage;
    char* name;       
};

/**************************************************************************************************
 * @section Function Definitions
 **************************************************************************************************/

/**
 * @brief Initializes the ADC hardware. Exits the function early if an error occurs.
 * 
 * @param dev SPI specifications
 * @param errc TI_ERRC_NONE if no errors occur, otherwise an error code
 */
void adc_init(struct adc_spi_dev* dev, enum ti_errc_t* errc);

/**
 * @brief Configures the multiplexer/gain/ref based on the struct, waits, and reads the voltage of a channel.
 *        Exits the funciton early of an error occurs. 
 * 
 * @param channel the specified ADC channel
 * @param errc TI_ERRC_NONE if no errors occur, otherwise an error code
 * @return the raw voltage of the specified channel
 */
int adc_read_voltage(const struct adc_channel* channel, enum ti_errc_t* errc);

/**
 * @brief Reads two separate adc pins and returns the mathematical difference (pin1 - pin2)
 * 
 * @param channel1 the first ADC channel
 * @param channel2 the second ADC channel
 * @param errc TI_ERRC_NONE if no errors occur, otherwise an error code
 * @return the difference in voltage between channel1 and channel2
 */
int adc_read_voltage_diff(struct adc_channel channel1, struct adc_channel channel2, enum ti_errc_t* errc);

/**
 * @brief Sets the IDAC magnitude and routes it to specific pins. Only two pins can be set at a time.
 * 
 * @param magnitude the magnitude of the current output
 * @param pin1 the first ADC pin
 * @param pin2 the second ADC pin
 * @param errc TI_ERRC_NONE if no errors occur, otherwise an error code
 */
void adc_set_idac(enum idac_mag magnitude, enum adc_pin pin1, enum adc_pin pin2, enum ti_errc_t* errc);

/**
 * @brief Converts an AIN pin to a digital output or inupt and sets it HIGH or LOW.
 * 
 * @param pin an ADC pin
 * @param default_high determines whether the ADC pin is default high or default low
 * @param output determines whether the ADC pin is output or input
 * @param errc TI_ERRC_NONE if no errors occur, otherwise an error code
 */
void adc_set_gpio(enum adc_pin pin, bool default_high, bool input, enum ti_errc_t* errc);

/**
 * @brief Converts an AIN pin to a digital output and sets it HIGH (true) or LOW (false).
 * 
 * @param channel an ADC channel
 * @return a String representing the name of hte channel
 */
char* adc_get_channel_name(struct adc_channel channel);