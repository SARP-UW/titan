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

#pragma once
#include <stdint.h>
#include "peripheral/errc.h"

void i2c_init(uint8_t inst, enum ti_errc_t *errc);
void i2c_write(uint8_t inst, uint32_t addr, void* buf, uint8_t size, enum ti_errc_t *errc);
void i2c_read(uint8_t inst, uint32_t addr, void* buf, uint8_t size, enum ti_errc_t* errc);

