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
 * @file devices/actuator.c
 * @authors Mahir Emran, Shlok Rathi
 * @brief MAX22217 solenoid control.
 */
#include "actuator.h"
#include "peripheral/spi.h"

#define WRITE_BIT  0x80U
#define ACTIVE_BIT 0x8000U
#define HIGH_SIDE_BIT 0x0400U
#define REG_VM_THRESHOLD 0x06U
#define REG_U_AC_SCAN    0x08U

static void transfer(actuator_t *dev, uint8_t addr, bool write, uint16_t data,
                     uint16_t *value, uint8_t *status, enum ti_errc_t *errc) {
    if (!dev || dev->spi_config.spi_inst < 1 || dev->spi_config.spi_inst > 6 ||
        dev->spi_config.ss_pin == 0 || dev->spi_config.ss_pin >= 140 || addr > 0x7F) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid actuator SPI device or address");
        return;
    }
    uint8_t tx[3] = {addr | (write ? WRITE_BIT : 0U), data >> 8, data & 0xFFU};
    uint8_t rx[3] = {0};
    spi_transfer_sync(dev->spi_config.spi_inst, dev->spi_config.ss_pin, tx, rx, 3, errc);
    if (*errc != TI_ERRC_NONE) return;
    if (value) *value = ((uint16_t)rx[1] << 8) | rx[2];
    if (status) *status = rx[0];
}

void actuator_write_reg(actuator_t *dev, uint8_t addr, uint16_t value,
                        uint8_t *status_out, enum ti_errc_t *errc) {
    enum ti_errc_t local_err;
    if (!errc) errc = &local_err;
    *errc = TI_ERRC_NONE;
    transfer(dev, addr, true, value, NULL, status_out, errc);
}

void actuator_read_reg(actuator_t *dev, uint8_t addr, uint16_t *value,
                       uint8_t *status_out, enum ti_errc_t *errc) {
    enum ti_errc_t local_err;
    if (!errc) errc = &local_err;
    *errc = TI_ERRC_NONE;
    if (!value) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Register output is NULL");
        return;
    }
    // Readback is delayed by one SPI transaction
    transfer(dev, addr, false, 0, NULL, NULL, errc);
    if (*errc != TI_ERRC_NONE) return;
    transfer(dev, addr, false, 0, value, status_out, errc);
}

static void update_reg(actuator_t *dev, uint8_t addr, uint16_t mask,
                       uint16_t bits, enum ti_errc_t *errc) {
    enum ti_errc_t local_err;
    if (!errc) errc = &local_err;
    uint16_t value;
    actuator_read_reg(dev, addr, &value, NULL, errc);
    if (*errc != TI_ERRC_NONE) return;
    actuator_write_reg(dev, addr, (value & ~mask) | (bits & mask), NULL, errc);
}

void actuator_init(actuator_t *dev, const actuator_spi_dev *spi_config,
                   uint8_t high_side_mask, enum ti_errc_t *errc) {
    enum ti_errc_t local_err;
    if (!errc) errc = &local_err;
    *errc = TI_ERRC_NONE;
    if (!dev || !spi_config || high_side_mask > 0x0F) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid actuator initialization");
        return;
    }
    dev->spi_config = *spi_config;
    // Start inactive; clear channel controls, VM triggering
    const uint8_t global_regs[] = {ACTUATOR_REG_GLOBAL_CFG, ACTUATOR_REG_GLOBAL_CTRL,
                                   REG_VM_THRESHOLD, REG_U_AC_SCAN};
    for (unsigned i = 0; i < sizeof(global_regs); ++i) {
        actuator_write_reg(dev, global_regs[i], 0, NULL, errc);
        if (*errc != TI_ERRC_NONE) return;
    }
    for (unsigned channel = 0; channel < ACTUATOR_CHANNEL_COUNT; ++channel) {
        const uint8_t base = ACTUATOR_CH0_BASE + (ACTUATOR_CH_STRIDE * channel);
        // DC_L2H, DC_H, DC_L, TIME_L2H, CTRL0, CTRL1
        const uint16_t settings[] = {
            ACTUATOR_DUTY_ON, ACTUATOR_DUTY_ON, 0, 0, 0,
            (high_side_mask & (1U << channel)) ? HIGH_SIDE_BIT : 0,
        };
        for (unsigned offset = 0; offset < sizeof(settings) / sizeof(settings[0]); ++offset) {
            actuator_write_reg(dev, base + offset, settings[offset], NULL, errc);
            if (*errc != TI_ERRC_NONE) return;
        }
    }
}

void actuator_set_active(actuator_t *dev, bool active, enum ti_errc_t *errc) {
    update_reg(dev, ACTUATOR_REG_GLOBAL_CFG, ACTIVE_BIT, active ? ACTIVE_BIT : 0, errc);
}

void actuator_set_channel_enable(actuator_t *dev, actuator_channel_t channel,
                                bool enable, enum ti_errc_t *errc) {
    if (channel < ACTUATOR_CHANNEL_0 || channel >= ACTUATOR_CHANNEL_COUNT) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid actuator channel");
        return;
    }
    const uint16_t mask = 1U << channel;
    update_reg(dev, ACTUATOR_REG_GLOBAL_CTRL, mask, enable ? mask : 0, errc);
}
