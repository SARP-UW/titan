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
 * @file devices/actuator.h
 * @authors Mahir Emran, Shlok Rathi
 * @brief MAX22217 solenoid control.
 */
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "peripheral/errc.h"

#define ACTUATOR_REG_GLOBAL_CTRL  0x00U
#define ACTUATOR_REG_GLOBAL_CFG   0x01U
#define ACTUATOR_REG_STATUS       0x02U
#define ACTUATOR_REG_FAULT0       0x65U
#define ACTUATOR_REG_FAULT1       0x66U
#define ACTUATOR_CH0_BASE         0x09U
#define ACTUATOR_CH_STRIDE        0x0EU
#define ACTUATOR_CH_REG_DCL2H     0x00U
#define ACTUATOR_CH_REG_DCH       0x01U
#define ACTUATOR_CH_REG_DCL       0x02U
#define ACTUATOR_CH_REG_TIMEL2H   0x03U
#define ACTUATOR_CH_REG_CTRL0     0x04U
#define ACTUATOR_CH_REG_CTRL1     0x05U
#define ACTUATOR_DUTY_ON          0x7FFFU // 100% duty

typedef enum {
    ACTUATOR_CHANNEL_0 = 0,
    ACTUATOR_CHANNEL_1,
    ACTUATOR_CHANNEL_2,
    ACTUATOR_CHANNEL_3,
    ACTUATOR_CHANNEL_COUNT,
} actuator_channel_t;

typedef struct {
    uint8_t spi_inst; // SPI1..SPI6, mode 0 or 3
    uint8_t ss_pin;   // GPIO package pin number
} actuator_spi_dev;

typedef struct {
    actuator_spi_dev spi_config;
} actuator_t;

/**
 * @brief Configure four channels for full on/off drive, without ramps or current regulation.
 * @param high_side_mask Bit n: 1 = load OUTn-to-GND, 0 = load VM-to-OUTn.
 * @param errc Optional error output; TI_ERRC_NONE on success.
 * @note Initialize SPI first, supply VM/VIO, and hold EN high through startup.
 * Hold CRC_EN and CNTL inputs low. Caller handles GPIO/timers and startup delays.
 * Starts inactive; call actuator_set_active(true) and allow wake-up time before use.
 */
void actuator_init(actuator_t *dev, const actuator_spi_dev *spi_config,
                   uint8_t high_side_mask, enum ti_errc_t *errc);

/**
 * @brief Write a 16-bit register value, MSB first, using a 7-bit address.
 * @note status_out and errc may be NULL. Serialize access to the SPI bus.
 * Fault registers are write one to clear
 */
void actuator_write_reg(actuator_t *dev, uint8_t addr, uint16_t value,
                        uint8_t *status_out, enum ti_errc_t *errc);

/**
 * @brief Read a 16-bit register using two SPI frames.
 * @note status_out and errc may be NULL. Reading faults does not clear them.
 */
void actuator_read_reg(actuator_t *dev, uint8_t addr, uint16_t *value,
                       uint8_t *status_out, enum ti_errc_t *errc);

/** @brief Set ACTIVE; false tri-states all outputs. ENABLE is controlled separately. */
void actuator_set_active(actuator_t *dev, bool active, enum ti_errc_t *errc);

/**
 * @brief Set one channel's SPI control bit, preserving the other channels.
 * @note SPI control and CNTL input are ORed. Keep CNTL low for SPI-only control;
 * clear the SPI bit when driving CNTL with STM32 PWM. Sequencer timing still applies.
 */
void actuator_set_channel_enable(actuator_t *dev, actuator_channel_t channel,
                                bool enable, enum ti_errc_t *errc);
