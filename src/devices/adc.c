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
 * @brief ADS124S0x ADC driver
 */

#include <stdint.h>
#include "devices/adc.h"
#include "peripheral/spi.h"
#include "peripheral/systick.h"
#include "internal/mmio.h"
#include "peripheral/errc.h"

#define RESET 0x06
#define START 0x08
#define STOP  0x0A
#define RDATA 0x12
#define STATUS_REG 0x01
#define INPMUX_REG 0x02
#define PGA_REG 0x03
#define REF_REG 0x05
#define IDACMAG_REG 0x06
#define IDACMUX_REG 0x07
#define GPIODAT_REG 0x10
#define GPIOCON_REG 0x11
#define RDY_FLAG 0x40
#define READ_BIT 0x20
#define WRITE_BIT 0x40
#define MAX_RREG_SIZE 6

static struct adc_spi_dev dev;

static int spi_rreg(uint8_t reg_addr, uint8_t data_size, enum ti_errc_t* errc) {
    if (data_size > (MAX_RREG_SIZE - 2) || data_size == 0) {
        *errc = TI_ERRC_INVALID_ARG;
        return -1;
    }

    uint8_t src[MAX_RREG_SIZE] = {0};
    uint8_t dst[MAX_RREG_SIZE] = {0};

    src[0] = READ_BIT | reg_addr;
    src[1] = data_size - 1;

    // Two command bytes + the number of registers to read
    uint8_t tot_size = 2 + data_size;
    spi_transfer_sync(dev.inst, dev.ss_pin, src, dst, tot_size, errc); // TODO: Make sure that SPI is returning an actual error code

    if (*errc != TI_ERRC_NONE) {
        return -1;
    }

    uint32_t result = 0;
    for (int i = 0; i < data_size; i++) {
        result = (result << 8) | dst[2 + i];
    }

    return result;
}

static void spi_wreg(uint8_t reg_addr, uint16_t data_size, uint32_t data, enum ti_errc_t* errc) { 
    if (data_size > (MAX_RREG_SIZE - 2) || data_size == 0) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    uint8_t src[MAX_RREG_SIZE] = {0};
    uint8_t dst[MAX_RREG_SIZE] = {0};

    src[0] = WRITE_BIT | reg_addr;
    src[1] = data_size - 1;

    for (int i = 0; i < data_size; i++) {
        // Move data into src while accounting for MSB formatting
        src[2 + i] = (uint8_t)(data >> (8 * (data_size - 1 - i)));
    }

    uint8_t tot_size = 2 + data_size;
    spi_transfer_sync(dev.inst, dev.ss_pin, src, dst, tot_size, errc);
}

static int32_t spi_single_command(uint8_t cmd, uint8_t transfer_size, enum ti_errc_t* errc) {
    if (transfer_size < 1 || transfer_size > 4) {
        *errc = TI_ERRC_INVALID_ARG;

        return -1;
    }

    uint8_t src[4] = {cmd, 0, 0, 0};
    uint8_t dst[4] = {0, 0, 0, 0};

    spi_transfer_sync(dev.inst, dev.ss_pin, src, dst, transfer_size, errc); 

    if (*errc != TI_ERRC_NONE) {
        return -1;
    }

    if (transfer_size == 1) {
        return dst[0];
    } 
    
    int32_t result = (dst[1] << 16) | (dst[2] << 8) | dst[3];
    return result;
    
}

void adc_init(struct adc_spi_dev *device, enum ti_errc_t* errc) {
    if (device->inst < 1 || device->inst > 6) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    *errc = TI_ERRC_NONE;
    dev  = *device;

    // Reset ADC
    uint8_t err = spi_single_command(RESET, 1, errc);
    if (err == -1 || *errc != TI_ERRC_NONE) {
        return;
    }

    // Delay recommended by datasheet after RESET
    //systick_delay(5); // TODO: Why is this getting stuck?
    for (int i = 0; i < 100000; i++) {
        asm("NOP");
    }

     spi_single_command(START, 1, errc);

    // Wait until ADC is ready for communication
    bool is_ready = false;
    int timeout = 100000; 
    while (!is_ready) {
        uint8_t status_reg = spi_rreg(STATUS_REG, 1, errc);
        
        if ((status_reg & RDY_FLAG) == 0 && *errc == TI_ERRC_NONE) {
            is_ready = true;
        } else if (timeout == 0) {
            *errc = TI_ERRC_TIMEOUT;
            return; 
        }

        timeout--;
    }

    // Enable internal reference 
    spi_wreg(REF_REG, 1, 0x12, errc);
}

int adc_read_voltage(const struct adc_channel* channel, enum ti_errc_t* errc) {
    if (dev.inst < 1 || dev.inst > 6 || !channel) {
        *errc = TI_ERRC_INVALID_ARG;
        return -1;
    }

    *errc = TI_ERRC_NONE;

    // Configure Input Multiplexer
    uint8_t mux_val = (channel->pos_pin << 4) | (channel->neg_pin & 0x0F);
    spi_wreg(INPMUX_REG, 1, mux_val, errc); // Returns -1 if unexpected return, otherwise 1

    // Set gain
    uint8_t pga_val = 0x08 | (channel->gain & 0x07);
    spi_wreg(PGA_REG, 1, pga_val, errc);

    // Set reference voltage
    uint8_t ref_val = 0x12 | ((channel->source & 0x03) << 2);
    spi_wreg(REF_REG, 1, ref_val, errc);

    if (*errc != TI_ERRC_NONE) {
        return -1;
    }

    // Wait for device ready flag
    int timeout = 100;
    while ((spi_rreg(STATUS_REG, 1, errc) & RDY_FLAG) != 0 && timeout > 0) {
        timeout--;
    }

    // Request data
    int32_t result = spi_single_command(RDATA, 4, errc);

    // If result is negative, ensure that top eight bit are flipped to 1
    if (result & 0x800000) {
        result |= 0xFF000000;
    }

    // Voltage conversion math
    float divisor = (float)((1 << 23) - 1); 

    // Convert the 3-bit gain code (0-7) into the actual multiplier (1, 2, 4... 128)
    float actual_gain = (float)(1 << (channel->gain & 0x07));

    float final_voltage = ((float)result * channel->ref_voltage) / (actual_gain * divisor);

    return (int32_t)(final_voltage * 1000);
}

int adc_read_voltage_diff(struct adc_channel channel1, struct adc_channel channel2, enum ti_errc_t* errc) { 
    int32_t voltage1 = adc_read_voltage(&channel1, errc);
    int32_t voltage2 = adc_read_voltage(&channel2, errc);

    return voltage1 - voltage2;
}

// You don't need to disconnect a pin to change the idac pins
void adc_set_idac(enum idac_mag magnitude, enum adc_pin pin1, enum adc_pin pin2, enum ti_errc_t* errc) {
    if (dev.inst < 1 || dev.inst > 6) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    // Set IDAC magnitude
    spi_wreg(IDACMAG_REG, 1, magnitude, errc);

    if (*errc != TI_ERRC_NONE) {
        return;
    }

    uint8_t mux_pins = ((pin2 & 0x0F) << 4) | (pin1 & 0x0F);
    spi_wreg(IDACMUX_REG, 1, mux_pins, errc);
}

void adc_set_gpio(enum adc_pin pin, bool default_high, bool input, enum ti_errc_t* errc) {
    if (dev.inst < 1 || dev.inst > 6) {
        *errc = TI_ERRC_INVALID_ARG;
        return;
    }

    // Only ADC pins 8 - 11 work
    uint8_t gpio_idx = pin - 0x08;

    // Enable GPIO function
    uint8_t gpiocon_val = 0;
    gpiocon_val |= (1 << gpio_idx);
    spi_wreg(GPIOCON_REG, 1, gpiocon_val, errc);
    if (*errc != TI_ERRC_NONE) {
        return;
    }

    uint8_t gpiodat_val;
    if (default_high && input) {
        gpiodat_val = 1 << (gpio_idx + 4) | gpio_idx;
    } else if (default_high && !input) {
        gpiodat_val = 1 << gpio_idx;
    } else if (!default_high && input) {
        gpiodat_val = 1 << (gpio_idx + 4);
    } else {
        gpiodat_val = 0;
    } 

    // Set as output/input and default high/low
    spi_wreg(GPIODAT_REG, 1, gpiodat_val, errc);
}

char* adc_get_channel_name(struct adc_channel channel) {
    return channel.name;
}

uint8_t adc_read_manufacturer_id(enum ti_errc_t* errc) {
    *errc = TI_ERRC_NONE;

    uint8_t id = spi_rreg(0x00, 1, errc); 
    return id;
}


/**
 * Notes:
 * 1. Start and reset pins are perminently tied to high, clk is tied to low, and data ready is left hanging. 
 * Only standard spi pins are used.
 * 
 * 2. If errc is not TI_ERRC_NONE the return value has no meaning **
 */