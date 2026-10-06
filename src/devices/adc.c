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
 * @brief ADS124S0x ADC driver; https://www.ti.com/lit/ds/symlink/ads124s06.pdf
 */

#include <stdint.h>
#include "devices/adc.h"
#include "peripheral/spi.h"
#include "peripheral/systick.h"
#include "internal/mmio.h"
#include "peripheral/errc.h"

// in order as defined in ref: 9.5.3; Table 24
// control commands
#define NOP 0x00
#define WAKEUP 0x02
#define POWERDOWN 0x04
#define RESET 0x06
#define START 0x08
#define STOP 0x0A

// calibration commands
#define SYOCAL 0x16
#define SYGCAL 0x17
#define SFOCAL 0x19

// data read command
#define RDATA 0x12

// ref: 9.6.1; Table 25; configuration register map
#define ID_REG 0x00
#define STATUS_REG 0x01
#define INPMUX_REG 0x02
#define PGA_REG 0x03
#define DATARATE 0x04
#define REF_REG 0x05
#define IDACMAG_REG 0x06
#define IDACMUX_REG 0x07
#define GPIODAT_REG 0x10
#define GPIOCON_REG 0x11

// ref: 9.6.1.2; Table 27; device register fields
#define RDY_FLAG 0x40 // at bit 6

// ref: 9.5.3; Table 24
#define READ_BIT 0x20
#define WRITE_BIT 0x40

#define COMMAND_BYTES_SIZE 2
#define MAX_COMMAND_SIZE 2 // commands are 1 byte, read/write is 2 bytes
#define LAST_REG_ADDR 0x11

static struct adc_spi_dev dev;

// ref: 9.5.3.11: Read device register data
static uint8_t adc_rreg(uint8_t reg_addr, enum ti_errc_t *errc) {
    if (reg_addr > LAST_REG_ADDR) {
        *errc = TI_ERRC_INVALID_ARG;
        return -1;
    }

    // src[1] == 0 due to 9.5.3(3)
    uint8_t src[COMMAND_BYTES_SIZE + 1] = {READ_BIT | reg_addr, 0, 0};
    uint8_t dst[COMMAND_BYTES_SIZE + 1] = {0};

    uint8_t tot_size = COMMAND_BYTES_SIZE + 1;
    spi_transfer_sync(dev.inst, dev.ss_pin, src, dst, tot_size, errc);

    if (*errc != TI_ERRC_NONE) {
        return -1;
    }

    return dst[2];
}

// ref: 9.5.3.12: Write device register data to a single register
static void adc_wreg(uint8_t reg_addr, uint8_t data, enum ti_errc_t *errc) {
    if (reg_addr > LAST_REG_ADDR) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    // src[1] == 0 due to 9.5.3(3)
    uint8_t src[COMMAND_BYTES_SIZE + 1] = {WRITE_BIT | reg_addr, 0, data};
    uint8_t dst[COMMAND_BYTES_SIZE + 1] = {0};

    uint8_t tot_size = COMMAND_BYTES_SIZE + 1;
    spi_transfer_sync(dev.inst, dev.ss_pin, src, dst, tot_size, errc);
}

// ref: 9.5.4.2
static int32_t adc_rdata(enum ti_errc_t *errc) {
    uint8_t src[4] = {RDATA, 0, 0, 0};
    uint8_t dst[4] = {0};

    spi_transfer_sync(dev.inst, dev.ss_pin, src, dst, 4, errc);
    if (*errc != TI_ERRC_NONE) {
        return -1;
    }

    // account for 24 bit to 32 bit conversion
    int32_t result = ((int32_t)dst[1] << 16) | ((int32_t)dst[2] << 8) | ((int32_t)dst[3]);
    // sign bit
    if (result & 0x800000) {
        result |= 0xFF000000;
    }
    return result;
}

static bool is_single_command(uint8_t cmd) {
    switch (cmd) {
    case NOP:
    case WAKEUP:
    case POWERDOWN:
    case RESET:
    case START:
    case STOP:
    case SYOCAL:
    case SYGCAL:
    case SFOCAL:
        return true;

    default:
        return false;
    }
}

// wait for the DOUT/DRDY pin to be low
static bool adc_wait_data_ready(int pin, enum ti_errc_t *errc)
{
    uint32_t timeout_ms = 1000;

    while (tal_read_pin(pin))
    {
        if (timeout_ms == 0)
        {
            *errc = TI_ERRC_TIMEOUT;
            return false;
        }

        systick_delay(1);
        timeout_ms--;
    }

    return true;
}

// ref: 9.5.3, Table 24 for commands, exclude read/writes
static void adc_single_command(uint8_t cmd, enum ti_errc_t *errc) {
    if (!is_single_command(cmd)) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    uint8_t src[4] = {cmd, 0, 0, 0};
    uint8_t dst[4] = {0};

    // relevant commands are only 1 byte
    spi_transfer_sync(dev.inst, dev.ss_pin, src, dst, 1, errc);
    if (*errc != TI_ERRC_NONE) {
        return;
    }
}

// ref: 9.5.3.4
void adc_init(struct adc_spi_dev *device, enum ti_errc_t *errc) {
    if (device->inst < 1 || device->inst > 6) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    *errc = TI_ERRC_NONE;
    dev = *device;

    // Reset ADC
    adc_single_command(RESET, errc);
    if (*errc != TI_ERRC_NONE) {
        return;
    }

    // ref: 9.5.3.4
    // Delay of 4096 t_clk cycles recommended by datasheet after RESET (1 ms equivalent)
    systick_delay(2);

    adc_single_command(START, errc);

    // Enable internal reference
    adc_wreg(REF_REG, 0x39, errc);
}

// ref: 7.3; view (1) for more specification
int adc_read_voltage(const struct adc_channel *channel, enum ti_errc_t *errc) {
    if (dev.inst < 1 || dev.inst > 6 || !channel) {
        *errc = TI_ERRC_INVALID_ARG;
        return -1;
    }

    // configure input multiplexer
    uint8_t mux_val = (channel->pos_pin << 4) | (channel->neg_pin & 0x0F);
    adc_wreg(INPMUX_REG, mux_val, errc);
    if (*errc != TI_ERRC_NONE) {
        return -1;
    }

    // set gain
    uint8_t pga_val = 0x08 | (channel->gain & 0x07);
    adc_wreg(PGA_REG, pga_val, errc);
    if (*errc != TI_ERRC_NONE) {
        return -1;
    }

    // set reference voltage
    uint8_t ref_reg = adc_rreg(REF_REG, errc);
    if (*errc != TI_ERRC_NONE) {
        return -1;
    }
    ref_reg &= 0xC;
    ref_reg |= ((channel->source & 0x03) << 2);
    adc_wreg(REF_REG, ref_reg, errc);
    if (*errc != TI_ERRC_NONE) {
        return -1;
    }

    // TODO: use the DRDY pin and CS pin combined to evaluate
    // ref: 9.5.5
    uint8_t dout_pin = spi_get_miso_pin(dev.inst, *errc);

    if (dout_pin < 0 || *errc != TI_ERRC_NONE) {
        *errc = TI_ERRC_INVALID_ARG;
        return -1;
    }

    if (!adc_wait_data_ready(dout_pin, errc)) {
        return -1;
    }

    // Request data
    int32_t result = adc_rdata(errc);

    // Voltage conversion math
    float divisor = (float)((1 << 23) - 1);

    // Convert the 3-bit gain code (0-7) into the actual multiplier (1, 2, 4... 128)
    float actual_gain = (float)(1 << (channel->gain & 0x07));

    float final_voltage = ((float)result * channel->ref_voltage) / (actual_gain * divisor);

    return (int32_t)(final_voltage * 1000);
}

int adc_read_voltage_diff(struct adc_channel channel1, struct adc_channel channel2, enum ti_errc_t *errc) {
    int32_t voltage1 = adc_read_voltage(&channel1, errc);
    int32_t voltage2 = adc_read_voltage(&channel2, errc);

    return voltage1 - voltage2;
}

// You don't need to disconnect a pin to change the idac pins
// ref: 9.6.1.7
// both pin 1 and pin 2 are set to the same magnitude at the same time
void adc_set_idac(enum idac_mag magnitude, enum adc_pin pin1, enum adc_pin pin2, enum ti_errc_t *errc) {
    if (dev.inst < 1 || dev.inst > 6) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    // Set IDAC magnitude
    // 9.6.1.7, Table 32. Bits 3:0
    adc_wreg(IDACMAG_REG, magnitude, errc);

    if (*errc != TI_ERRC_NONE) {
        return;
    }

    // ref: 9.6.1.8
    // refer to idac_mag in adc.h for valid values
    uint8_t mux_pins = ((pin2 & 0x0F) << 4) | (pin1 & 0x0F);
    adc_wreg(IDACMUX_REG, mux_pins, errc);

    if (*errc != TI_ERRC_NONE) {
        return;
    }
}

// ref: 9.6.1.17, 9.6.1.18
void adc_config_gpio(enum adc_pin pin, bool input, bool analog, enum ti_errc_t *errc) {
    // cannot be output and analog input concurrently
    if (dev.inst < 1 || dev.inst > 6 || (~input && analog)) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    // using ADC pins 8-11 for GPIO
    uint8_t idx = pin - 0x08;

    // configure pin as gpio or analog input
    uint8_t gpiocon_mask = analog ? ~(1u << idx) : (1u << idx);
    uint8_t gpiocon_reg = adc_rreg(GPIOCON_REG, errc);
    if (*errc != TI_ERRC_NONE) {
        return;
    }

    gpiocon_reg &= gpiocon_mask;

    adc_wreg(GPIOCON_REG, gpiocon_reg, errc);
    if (*errc != TI_ERRC_NONE) {
        return;
    }
}

// ref: 9.6.1.17
int adc_get_gpio(enum adc_pin pin, bool default_high, enum ti_errc_t *errc) {
    // using ADC pins 8-11 for GPIO
    uint8_t gpio_idx = pin - 0x08;

    // read GPIO value
    uint8_t gpiodat_mask = 0;
    gpiodat_mask |= (1 << gpio_idx);
    uint8_t gpio_dat = adc_rreg(GPIODAT_REG, errc);
    if (*errc != TI_ERRC_NONE) {
        return 0;
    }

    // return 1 if default high and selected pin is 0
    return ((gpio_dat & gpiodat_mask) != 0) ^ default_high;
}

// ref: 9.6.1.18
void adc_set_gpio(enum adc_pin pin, bool input, enum ti_errc_t *errc) {
    // using ADC pins 8-11 for GPIO
    uint8_t gpio_idx = pin - 0x08;
    uint8_t gpio_mask = 1u << gpio_idx;
    uint8_t gpiodat_reg = adc_rreg(GPIODAT_REG, errc);

    gpiodat_reg = input ? (gpiodat_reg | gpio_mask) : (gpiodat_reg & ~gpio_mask);

    adc_wreg(GPIODAT_REG, gpiodat_reg, errc);
}

char *adc_get_channel_name(struct adc_channel channel) {
    return channel.name;
}

// ref: 9.6.1.1
uint8_t adc_read_manufacturer_id(enum ti_errc_t *errc) {
    uint8_t id_reg = adc_rreg(ID_REG, errc);
    if (*errc != TI_ERRC_NONE) {
        return;
    }
    // only bits 2:0 are relevant
    return id_reg & 0x7;
}

/**
 * Notes:
 * 1. Start and reset pins are permanently tied to high, clk is tied to low, and data ready is left hanging.
 * Only standard spi pins are used.
 *
 * 2. If errc is not TI_ERRC_NONE the return value has no meaning **
 */
