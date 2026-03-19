/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * @file devices/temperature.h
 * @authors Mahir Emran
 * @brief temperature ±0.5°C accurate digital temperature sensor driver
 */

#pragma once
#include <stdint.h>
#include "peripheral/spi.h"
#include "peripheral/errc.h"

/**************************************************************************************************
 * @section Type definitions
 **************************************************************************************************/

/**
 * @brief temperature operating mode
 * Maps directly to bits [6:5] of the configuration register.
 */
typedef enum {
    temperature_MODE_CONTINUOUS = 0x00,  // Stays awake, continuous 240ms conversion loop
    temperature_MODE_ONE_SHOT   = 0x01,  // Triggers conversion, then hardware shutdown
    temperature_MODE_1_SPS      = 0x02,  // 1 sample per second, auto-sleeps (low power)
    temperature_MODE_SHUTDOWN   = 0x03,  // Hardware shutdown, interface remains active
} temperature_mode_t;

/**
 * @brief temperature ADC resolution
 * Maps to bit 7 of the configuration register.
 */
typedef enum {
    temperature_RES_13_BIT = 0x00, // 13-bit resolution: 0.0625 °C/LSB (Power-on default)
    temperature_RES_16_BIT = 0x01, // 16-bit resolution: 0.0078 °C/LSB
} temperature_res_t;

/**
 * @brief Temperature reading result
 */
typedef struct {
    int16_t raw_value;      /**< Raw ADC LSB output */
    float   temperature;    /**< Calculated temperature in °C */
} temperature_result_t;

/**
 * @brief temperature configuration
 */
typedef struct {
    temperature_mode_t mode;       // Desired power mode
    temperature_res_t  resolution; // Desired ADC resolution
} temperature_config_t;

/** @brief SPI config for temperature */
typedef struct {
    uint8_t  spi_inst;      // SPI instance (e.g., 1 for SPI1)
    uint8_t  ss_pin;        // SPI Slave Select pin number
} temperature_spi_dev;

/** @brief temperature device handle */
typedef struct {
    temperature_spi_dev  spi_config; // SPI config for temperature
    temperature_config_t config;     // Sensor configuration
} temperature_t;

/**************************************************************************************************
 * @section Function Definitions
 **************************************************************************************************/

/**
 * @brief Initializes the temperature temperature sensor.
 *
 * Soft resets the SPI interface, verifies the device ID, and configures the 
 * selected operation mode and ADC resolution.
 *
 * @param dev Pointer to the temperature_t device structure.
 * @return enum ti_errc_t TI_ERRC_NONE on success.
 */
enum ti_errc_t temperature_init(temperature_t *dev);

/**
 * @brief Reads the current temperature from the temperature.
 *
 * If the device is in ONE_SHOT mode, this function will automatically 
 * trigger a conversion, block for the 240ms completion time, and read the result. 
 * If CONTINUOUS or 1_SPS, it immediately fetches the latest register value.
 *
 * @param dev Pointer to the temperature_t device structure.
 * @param res Pointer to the result struct to store output.
 * @return enum ti_errc_t TI_ERRC_NONE on success.
 */
enum ti_errc_t temperature_read_temp(temperature_t *dev, temperature_result_t* res);
