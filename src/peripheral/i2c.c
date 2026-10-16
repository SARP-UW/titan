/**
 * This file is part of the Titan Project.
 * Copyright (c) 2025 UW SARP
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
 * @file peripheral/i2c.h
 * @authors Ayush Thapa
 * @brief Implementation of I2C driver interface
 */

#include "i2c.h"
#include "internal/mmio.h"
#include "peripheral/errc.h"
#include "peripheral/gpio.h"
#include "peripheral/systick.h"
#include <sys/_intsup.h>

enum inst {
    INST_ONE = 1,
    INST_TWO,
    INST_THREE,
    INST_FOUR,
};

#define INST1_SCL_PIN 133
#define INST1_SDA_PIN 134

static void i2c_reset(uint8_t inst) {
    CLR_FIELD(I2Cx_CR1[inst], I2Cx_CR1_PE);

    // read back PE, as required by the manual's reset sequence
    while (READ_FIELD(I2Cx_CR1[inst], I2Cx_CR1_PE) != 0) {
    }

    SET_FIELD(I2Cx_CR1[inst], I2Cx_CR1_PE);
}

static enum ti_errc_t i2c_get_error(uint32_t status) {
    if (READ_FIELD(&status, I2Cx_ISR_ARLO))
        return TI_ERRC_BUS;

    if (READ_FIELD(&status, I2Cx_ISR_NACKF))
        return TI_ERRC_DEVICE;

    return TI_ERRC_NONE;
}

static void i2c_set_error(enum ti_errc_t *errc, enum ti_errc_t err) {
    if (!errc)
        return;

    switch (err) {
    case TI_ERRC_TIMEOUT:
        TI_SET_ERRC(errc, TI_ERRC_TIMEOUT, "I2C timeout error");
        break;
    case TI_ERRC_DEVICE:
        TI_SET_ERRC(errc, TI_ERRC_DEVICE, "I2C device error");
        break;
    case TI_ERRC_BUS:
        TI_SET_ERRC(errc, TI_ERRC_BUS, "I2C arbitration lost");
        break;
    default:
        TI_SET_ERRC(errc, TI_ERRC_UNKNOWN, "I2C unknown error");
    }
}

static enum ti_errc_t i2c_wait(uint8_t inst, field32_t flag, uint32_t start_ms,
                               uint32_t timeout_ms) {
    for (;;) {
        uint32_t status = *I2Cx_ISR[inst];
        if (READ_FIELD(&status, I2Cx_ISR_BERR))
            SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_BERRCF);

        enum ti_errc_t error = i2c_get_error(status);

        if (error != TI_ERRC_NONE)
            return error;

        if (READ_FIELD(&status, flag)) {
            return TI_ERRC_NONE;
        }

        uint32_t now_ms = systick_now_ms();
        if (now_ms - start_ms >= timeout_ms) {
            return TI_ERRC_TIMEOUT;
        }
    }

    return TI_ERRC_NONE;
}

static void i2c_cleanup(uint8_t inst, enum ti_errc_t err) {
    uint32_t status = *I2Cx_ISR[inst];

    if (READ_FIELD(&status, I2Cx_ISR_ARLO)) {
        SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_ARLOCF);

        if (READ_FIELD(&status, I2Cx_ISR_NACKF))
            SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_NACKCF);

        if (READ_FIELD(&status, I2Cx_ISR_STOPF))
            SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_STOPCF);

        if (READ_FIELD(&status, I2Cx_ISR_BERR))
            SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_BERRCF);

        return;
    }

    if (err == TI_ERRC_TIMEOUT) {
        i2c_reset(inst);
        return;
    }

    if (READ_FIELD(&status, I2Cx_ISR_BERR)) {
        SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_BERRCF);

        // STM32H745 controller-mode erratum:
        // BERR alone does not abort the transfer.
    }

    if (READ_FIELD(&status, I2Cx_ISR_NACKF)) {
        const uint32_t start_ms = systick_now_ms();
        const uint32_t timeout_ms = 100;

        while (!READ_FIELD(I2Cx_ISR[inst], I2Cx_ISR_STOPF)) {
            if (systick_now_ms() - start_ms >= timeout_ms) {
                i2c_reset(inst);
                return;
            }
        }

        SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_NACKCF);
        SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_STOPCF);
    }
}

static enum ti_errc_t i2c_wait_bus_idle(uint8_t inst) {
    const uint32_t start_ms = systick_now_ms();
    const uint32_t timeout_ms = 100;

    while (READ_FIELD(I2Cx_ISR[inst], I2Cx_ISR_BUSY) ||
           READ_FIELD(I2Cx_CR2[inst], I2Cx_CR2_START) || !tal_read_pin(INST1_SCL_PIN) ||
           !tal_read_pin(INST1_SDA_PIN)) {
        if (systick_now_ms() - start_ms >= timeout_ms) {
            return TI_ERRC_TIMEOUT;
        }
    }

    return TI_ERRC_NONE;
}

void i2c_init(uint8_t inst, enum ti_errc_t *errc) {
    // validate the instance
    if (errc)
        *errc = TI_ERRC_NONE;
    if (inst != 1) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Only I2C1 is supported");
        return;
    }

    // turn on gpio port clock
    tal_enable_clock(INST1_SDA_PIN);
    tal_enable_clock(INST1_SCL_PIN);

    // enable alternate function mode
    tal_set_mode(INST1_SDA_PIN, 2);
    tal_set_mode(INST1_SCL_PIN, 2);

    // set alternate function
    tal_alternate_mode(INST1_SCL_PIN, 0b100);
    tal_alternate_mode(INST1_SDA_PIN, 0b100);

    // set pins to open drain
    tal_set_drain(INST1_SDA_PIN, 1);
    tal_set_drain(INST1_SCL_PIN, 1);

    // set kernel clock source
    SET_FIELD(RCC_CR, RCC_CR_HSION);
    uint32_t start_ms = systick_now_ms();
    uint32_t timeout_ms = 100;
    while (!READ_FIELD(RCC_CR, RCC_CR_HSIRDY)) {
        if (systick_now_ms() - start_ms >= timeout_ms) {
            i2c_set_error(errc, TI_ERRC_TIMEOUT);
            return;
        }
    }
    WRITE_FIELD(RCC_D2CCIP2R, RCC_D2CCIP2R_I2C123SRC, 0b10);

    // Enable I2C clock
    SET_FIELD(RCC_APB1LENR, RCC_APB1LENR_I2CxEN[inst]);

    // Configuration
    CLR_FIELD(I2Cx_CR1[inst], I2Cx_CR1_PE);     // disable peripheral
    CLR_FIELD(I2Cx_CR1[inst], I2Cx_CR1_ANFOFF); // analog noise filter
    CLR_FIELD(I2Cx_CR1[inst], I2Cx_CR1_DNF);    // digital noise filter

    // Timing
    WRITE_FIELD(I2Cx_TIMINGR[inst], I2Cx_TIMINGR_PRESC, 15); 

    WRITE_FIELD(I2Cx_TIMINGR[inst], I2Cx_TIMINGR_SCLH, 19);
    WRITE_FIELD(I2Cx_TIMINGR[inst], I2Cx_TIMINGR_SCLL, 19);

    WRITE_FIELD(I2Cx_TIMINGR[inst], I2Cx_TIMINGR_SCLDEL, 4);
    WRITE_FIELD(I2Cx_TIMINGR[inst], I2Cx_TIMINGR_SDADEL, 2);

    CLR_FIELD(I2Cx_CR1[inst], I2Cx_CR1_NOSTRETCH); // must be cleared in controller mode

    SET_FIELD(I2Cx_CR1[inst], I2Cx_CR1_PE); // enable peripheral
}

void i2c_write(uint8_t inst, uint32_t addr, void *buf, uint8_t size, enum ti_errc_t *errc) {
    if (errc)
        *errc = TI_ERRC_NONE;
    if (size == 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Transfer size cannot be zero");
        return;
    }
    if (inst != 1) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Only I2C1 is supported");
        return;
    }
    if (buf == NULL) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Write buffer cannot be NULL");
        return;
    }
    if (addr > 0x7F) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Target address must be at most 7 bits");
        return;
    }

    // Make sure that the I2C bus is idle
    enum ti_errc_t idle_err = i2c_wait_bus_idle(inst);
    if (idle_err != TI_ERRC_NONE) {
        i2c_set_error(errc, idle_err);
        return;
    }

    CLR_FIELD(I2Cx_CR2[inst], I2Cx_CR2_RELOAD);  // reload must be cleared for autoend to work
    SET_FIELD(I2Cx_CR2[inst], I2Cx_CR2_AUTOEND); // autoend (enabled)

    CLR_FIELD(I2Cx_CR2[inst], I2Cx_CR2_ADD10);             // 7-bit or 10-bit address
    WRITE_FIELD(I2Cx_CR2[inst], I2Cx_CR2_SADD_7BIT, addr); // target address

    CLR_FIELD(I2Cx_CR2[inst], I2Cx_CR2_RD_WRN);         // read or write
    WRITE_FIELD(I2Cx_CR2[inst], I2Cx_CR2_NBYTES, size); // number of bytes to send

    uint32_t start_ms = systick_now_ms();
    const uint32_t timeout_ms = 100;
    const uint8_t *bytes = buf;

    SET_FIELD(I2Cx_CR2[inst], I2Cx_CR2_START); // start

    for (int byte = 0; byte < size; byte++) {
        enum ti_errc_t write_err = i2c_wait(inst, I2Cx_ISR_TXIS, start_ms, timeout_ms);

        if (write_err != TI_ERRC_NONE) {
            i2c_cleanup(inst, write_err);
            i2c_set_error(errc, write_err);

            return;
        }

        WRITE_FIELD(I2Cx_TXDR[inst], I2Cx_TXDR_TXDATA, bytes[byte]);
    }

    enum ti_errc_t stop_err = i2c_wait(inst, I2Cx_ISR_STOPF, start_ms, timeout_ms);

    if (stop_err != TI_ERRC_NONE) {
        i2c_cleanup(inst, stop_err);
        i2c_set_error(errc, stop_err);
        return;
    }

    SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_STOPCF);
}

void i2c_read(uint8_t inst, uint32_t addr, void *buf, uint8_t size, enum ti_errc_t *errc) {
    if (errc)
        *errc = TI_ERRC_NONE;
    if (size == 0) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Transfer size cannot be zero");
        return;
    }
    if (inst != 1) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Only I2C1 is supported");
        return;
    }
    if (buf == NULL) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Write buffer cannot be NULL");
        return;
    }
    if (addr > 0x7F) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Target address must be at most 7 bits");
        return;
    }

    // Make sure that the I2C bus is idle
    enum ti_errc_t idle_err = i2c_wait_bus_idle(inst);
    if (idle_err != TI_ERRC_NONE) {
        i2c_set_error(errc, idle_err);
        return;
    }

    CLR_FIELD(I2Cx_CR2[inst], I2Cx_CR2_RELOAD);  // reload must be cleared for autoend to work
    SET_FIELD(I2Cx_CR2[inst], I2Cx_CR2_AUTOEND); // autoend (enabled)

    CLR_FIELD(I2Cx_CR2[inst], I2Cx_CR2_ADD10);             // 7-bit or 10-bit address
    WRITE_FIELD(I2Cx_CR2[inst], I2Cx_CR2_SADD_7BIT, addr); // target address

    SET_FIELD(I2Cx_CR2[inst], I2Cx_CR2_RD_WRN);         // read or write
    WRITE_FIELD(I2Cx_CR2[inst], I2Cx_CR2_NBYTES, size); // number of bytes to send

    uint32_t start_ms = systick_now_ms();
    const uint32_t timeout_ms = 100;
    uint8_t *bytes = buf;

    SET_FIELD(I2Cx_CR2[inst], I2Cx_CR2_START); // start

    // spin until message
    for (int byte = 0; byte < size; byte++) {
        enum ti_errc_t read_err = i2c_wait(inst, I2Cx_ISR_RXNE, start_ms, timeout_ms);
        if (read_err != TI_ERRC_NONE) {
            i2c_cleanup(inst, read_err);
            i2c_set_error(errc, read_err);
            return;
        }

        bytes[byte] = READ_FIELD(I2Cx_RXDR[inst], I2Cx_RXDR_RXDATA);
    }

    enum ti_errc_t stop_err = i2c_wait(inst, I2Cx_ISR_STOPF, start_ms, timeout_ms);

    if (stop_err != TI_ERRC_NONE) {
        i2c_cleanup(inst, stop_err);
        i2c_set_error(errc, stop_err);
        return;
    }

    SET_WO_FIELD(I2Cx_ICR[inst], I2Cx_ICR_STOPCF);
}
