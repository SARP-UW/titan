/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * @file devices/temperature.c
 * @authors Mahir Emran
 * @brief temperature ±0.5°C accurate digital temperature sensor driver implementation
 */

#include "devices/temperature.h"
#include "peripheral/errc.h"
#include <stddef.h>

// temperature Register Addresses
#define temperature_REG_STATUS      0x00
#define temperature_REG_CONFIG      0x01
#define temperature_REG_TEMP_VAL    0x02
#define temperature_REG_ID          0x03

// Expected ID response from Register 0x03
#define temperature_EXPECTED_ID     0xC3

// SPI Command byte read/write bit definitions
#define temperature_CMD_READ        (1 << 6)
#define temperature_CMD_WRITE       (0 << 6)

// Wait time for One-Shot conversion in ms
#define temperature_CONV_TIME_MS    240

// NOTE: Ensure system_delay_ms exists in your codebase. 
// For an RTOS, consider using a thread-yielding delay (e.g. vTaskDelay) instead of blocking.
extern void systick_delay(uint32_t ms);

// NOTE: Prototype assumed for standard full-duplex SPI transfer in your peripheral/spi.h.
// Adapt this prototype/wrapper if your actual SPI API parameters differ.
extern void spi_transfer_sync(uint8_t inst, uint8_t ss_pin, void* src, void* dst, uint8_t size, enum ti_errc_t *errc);

/* -------------------- Internal Helpers -------------------- */

static void temperature_write_reg8(temperature_t *dev, uint8_t reg, uint8_t val, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    uint8_t tx[2];
    tx[0] = temperature_CMD_WRITE | ((reg & 0x07) << 3);
    tx[1] = val;
    spi_transfer_sync(dev->spi_config.spi_inst, dev->spi_config.ss_pin, tx, NULL, 2, errc);
}

static void temperature_read_reg8(temperature_t *dev, uint8_t reg, uint8_t *val, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    uint8_t tx[2] = {0};
    uint8_t rx[2] = {0};
    
    tx[0] = temperature_CMD_READ | ((reg & 0x07) << 3);
    
    spi_transfer_sync(dev->spi_config.spi_inst, dev->spi_config.ss_pin, tx, rx, 2, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; }
    if (val) {
        *val = rx[1]; // MISO data comes in on the second clock frame
    }
}

static void temperature_read_reg16(temperature_t *dev, uint8_t reg, uint16_t *val, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    uint8_t tx[3] = {0};
    uint8_t rx[3] = {0};
    
    tx[0] = temperature_CMD_READ | ((reg & 0x07) << 3);
    
    spi_transfer_sync(dev->spi_config.spi_inst, dev->spi_config.ss_pin, tx, rx, 3, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; }
    if (val) {
        *val = ((uint16_t)rx[1] << 8) | rx[2];
    }
}

/* -------------------- Public API -------------------- */

void temperature_init(temperature_t *dev, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!dev) { TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "dev pointer is NULL"); return; }

    // 1. Reset serial interface by sending 32 consecutive 1s on DIN
    uint8_t reset_cmd[4] = {0xFF, 0xFF, 0xFF, 0xFF};
    spi_transfer_sync(dev->spi_config.spi_inst, dev->spi_config.ss_pin, reset_cmd, NULL, 4, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; }

    systick_delay(1); // Brief delay for initialization

    // 2. Read ID register to verify communication
    uint8_t id = 0;
    temperature_read_reg8(dev, temperature_REG_ID, &id, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; }

    if (id != temperature_EXPECTED_ID) {
        TI_SET_ERRC(errc, TI_ERRC_DEVICE, "Temperature sensor ID mismatch; device not found or not responding"); return;
    }

    // 3. Configure the device (Set Resolution & Operation Mode)
    uint8_t config_val = 0;
    config_val |= (dev->config.resolution & 0x01) << 7;
    config_val |= (dev->config.mode & 0x03) << 5;
    temperature_write_reg8(dev, temperature_REG_CONFIG, config_val, errc);
}

void temperature_read_temp(temperature_t *dev, temperature_result_t* res, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!dev || !res) { TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid arguments"); return; }

    // Trigger conversion manually if the module was set to ONE_SHOT polling
    if (dev->config.mode == temperature_MODE_ONE_SHOT) {
        uint8_t config_val = 0;
        config_val |= (dev->config.resolution & 0x01) << 7;
        config_val |= (temperature_MODE_ONE_SHOT & 0x03) << 5;
        temperature_write_reg8(dev, temperature_REG_CONFIG, config_val, errc);
        if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; }

        // Block until one-shot conversion completes
        systick_delay(temperature_CONV_TIME_MS);
    }

    // Read 16-bit temperature register
    uint16_t raw_data = 0;
    temperature_read_reg16(dev, temperature_REG_TEMP_VAL, &raw_data, errc);
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; }

    res->raw_value = (int16_t)raw_data;

    // Extract actual temperature utilizing two's complement behavior
    if (dev->config.resolution == temperature_RES_16_BIT) {
        // 16-bit resolution format: 0.0078 °C/LSB (Entire value/128)
        res->temperature = (float)((int16_t)raw_data) / 128.0f;
    } else {
        // 13-bit resolution format: mask out the 3 flag bits (Bits 2:0)
        res->temperature = (float)((int16_t)(raw_data & 0xFFF8)) / 128.0f;
    }
}
