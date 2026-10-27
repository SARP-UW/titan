#pragma once
#include "peripheral/errc.h"
#include <stdint.h>

/**
 * @brief I2C specifications
 */
struct current_i2c_dev {
    uint8_t inst; // I2C instance
    uint8_t addr; // 7-bit device address
};

/**
 * @brief Current config
 * */
struct current_config_t {
    uint64_t shunt_uohms;    // Shunt resistance in micro-ohms
    uint64_t current_lsb_ua; // Microamps per raw count
    uint16_t adc_config;     // Value for MFR_ADC_CONFIG
};

/**
 * @brief Current result
 * */
struct current_result_t {
    int16_t raw_value;
    int64_t current_ma; // Current in milliamps
};

/**
 * @brief Initializes the current sensor hardware. Exits the function early if an error occurs.
 *
 * @param dev current sensor devie
 * @param errc TI_ERRC_NONE if no errors occur, otherwise an error code
 */
void current_init(const struct current_i2c_dev *dev, const struct current_config_t *config,
                  enum ti_errc_t *errc);

/**
 * @brief Returns the current. Exits the function early of an error occurs.
 *
 * @param dev current sensor device
 * @param result struct containing raw_value and current in milliamps. Should only be used when errc
 * is TI_ERRC_NONE.
 * @param errc TI_ERRC_NONE if no errors occur, otherwise an error code
 */
void current_read(const struct current_i2c_dev *dev, const struct current_config_t *config,
                  struct current_result_t *result, enum ti_errc_t *errc);
