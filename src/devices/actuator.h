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
 * @brief Minimal MAX22217 single-ended solenoid control.
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
#define ACTUATOR_DUTY_ON          0x7FFFU

typedef enum {
    ACTUATOR_CHANNEL_0 = 0,
    ACTUATOR_CHANNEL_1,
    ACTUATOR_CHANNEL_2,
    ACTUATOR_CHANNEL_3,
    ACTUATOR_CHANNEL_COUNT,
} actuator_channel_t;

typedef struct {
    uint8_t spi_inst; // SPI1..SPI6, already initialized in mode 0 (or mode 3).
    uint8_t ss_pin;   // STM32 package pin number, as used by gpio.h.
} actuator_spi_dev;

typedef struct {
    actuator_spi_dev spi_config;
} actuator_t;

/**
 * Configure four independent channels for on/off or external CNTL PWM control.
 * high_side_mask bit n: 1 = load between OUTn and GND, 0 = load between VM and OUTn.
 * Leaves ACTIVE=0 and all SPI CNTL bits clear; call actuator_set_active(true) afterward.
 *
 * Caller owns SPI, ENABLE, CRC_EN, and PWM GPIO/timer setup:
 * - Initialize SPI first; hold CRC_EN LOW (24-bit frames, no daisy chain).
 * - Supply VM/VIO and hold ENABLE HIGH through startup before calling this function.
 *   Datasheet pp. 11-12: tEN=0.8ms; allow wake-up/OTP download time too.
 * - Hold CNTL0..3 LOW during initialization. This routine replaces channel settings
 *   with duty mode, 100% high / 0% low, no hit/hold delay, ramps, or current regulation.
 * - After ACTIVE=1, allow the datasheet wake-up time before commanding a channel.
 *
 * PWM: connect an STM32 timer output to CNTLn and leave SPI CNTLn clear using
 * actuator_set_channel_enable(..., false). Use ti_set_pwm() from peripheral/pwm.h.
 * There is no separate PWM-mode register. CNTL pin and SPI bit are ORed, so an SPI
 * false does NOT force off a channel whose CNTL input is high. For SPI-only control,
 * hold the CNTL input LOW. The sequencer still has its own timing; validate the
 * intended external PWM frequency/duty on hardware (this is not a bypass mode).
 */
void actuator_init(actuator_t *dev, const actuator_spi_dev *spi_config,
                   uint8_t high_side_mask, enum ti_errc_t *errc);

/** Raw 7-bit register access. Data is 16-bit, MSB first; status_out may be NULL.
 * Reads issue two CS-separated frames because readback is one transaction late.
 * Fault registers are write-one-to-clear; reading them does not acknowledge faults.
 * Access is synchronous; callers must serialize operations on the same SPI bus.
 */
void actuator_write_reg(actuator_t *dev, uint8_t addr, uint16_t value,
                        uint8_t *status_out, enum ti_errc_t *errc);
void actuator_read_reg(actuator_t *dev, uint8_t addr, uint16_t *value,
                       uint8_t *status_out, enum ti_errc_t *errc);

/** Set GLOBAL_CFG.ACTIVE. false tri-states all outputs; ENABLE remains caller-owned. */
void actuator_set_active(actuator_t *dev, bool active, enum ti_errc_t *errc);

/** Set the channel's SPI CNTL bit without changing the other channels. See PWM note above. */
void actuator_set_channel_enable(actuator_t *dev, actuator_channel_t channel,
                                bool enable, enum ti_errc_t *errc);
