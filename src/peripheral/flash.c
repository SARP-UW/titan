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
 * @file peripheral/flash.c
 * @authors Mahir Emran
 * @brief General internal flash driver implementation for STM32H7.
 */
#include "flash.h"
#include "../internal/mmio.h"

#define FLASH_KEY1 0x45670123U
#define FLASH_KEY2 0xCDEF89ABU

static void flash_wait_busy(uint32_t addr) {
    if (addr < 0x08100000U) {
        while (READ_FIELD(FLASH_SR1, FLASH_SR1_BSY1));
    } else {
        while (READ_FIELD(FLASH_SR2, FLASH_SR2_BSY2));
    }
}

static void flash_unlock(uint32_t addr) {
    if (addr < 0x08100000U) {
        if (READ_FIELD(FLASH_CR1, FLASH_CR1_LOCK1)) {
            *FLASH_KEYR1 = FLASH_KEY1;
            *FLASH_KEYR1 = FLASH_KEY2;
        }
    } else {
        if (READ_FIELD(FLASH_CR2, FLASH_CR2_LOCK2)) {
            *FLASH_KEYR2 = FLASH_KEY1;
            *FLASH_KEYR2 = FLASH_KEY2;
        }
    }
}

static void flash_lock(uint32_t addr) {
    if (addr < 0x08100000U) SET_FIELD(FLASH_CR1, FLASH_CR1_LOCK1);
    else SET_FIELD(FLASH_CR2, FLASH_CR2_LOCK2);
}

enum ti_errc_t ti_internal_flash_erase_sector(uint32_t addr) {
    bool is_bank2 = (addr >= 0x08100000U);
    uint32_t bank_base = 0x08000000U;
    if (is_bank2) {
        bank_base = 0x08100000U;
    }
    uint32_t sector = (addr - bank_base) / 0x20000U;
    
    if (sector > 7) return TI_ERRC_INVALID_ARG;

    flash_unlock(addr);
    flash_wait_busy(addr);
    
    if (!is_bank2) {
        *FLASH_CCR1 = 0x0001FE00U; // Clear error flags
        SET_FIELD(FLASH_CR1, FLASH_CR1_SER1);
        WRITE_FIELD(FLASH_CR1, FLASH_CR1_SNB1, sector);
        SET_FIELD(FLASH_CR1, FLASH_CR1_START1);
    } else {
        *FLASH_CCR2 = 0x0001FE00U;
        SET_FIELD(FLASH_CR2, FLASH_CR2_SER2);
        WRITE_FIELD(FLASH_CR2, FLASH_CR2_SNB2, sector);
        SET_FIELD(FLASH_CR2, FLASH_CR2_START2);
    }

    flash_wait_busy(addr);
    
    if (!is_bank2) CLR_FIELD(FLASH_CR1, FLASH_CR1_SER1);
    else CLR_FIELD(FLASH_CR2, FLASH_CR2_SER2);
    
    flash_lock(addr);
    return TI_ERRC_NONE;
}

enum ti_errc_t ti_internal_flash_write(uint32_t addr, const void *data, uint32_t size) {
    if (addr % 32 != 0 || size % 32 != 0) return TI_ERRC_INVALID_ARG;
    bool is_bank2 = (addr >= 0x08100000U);

    flash_unlock(addr);
    flash_wait_busy(addr);
    
    if (!is_bank2) {
        *FLASH_CCR1 = 0x0001FE00U;
        SET_FIELD(FLASH_CR1, FLASH_CR1_PG1);
    } else {
        *FLASH_CCR2 = 0x0001FE00U;
        SET_FIELD(FLASH_CR2, FLASH_CR2_PG2);
    }

    const uint32_t *p_data = (const uint32_t *)data;
    for (uint32_t i = 0; i < size / 32; i++) {
        volatile uint32_t *p_flash = (uint32_t *)(addr + (i * 32U)); // NOLINT(performance-no-int-to-ptr)
        for (int j = 0; j < 8; j++) p_flash[j] = p_data[(i * 8U) + (uint32_t)j];
        
        __asm volatile ("dsb sy");
        __asm volatile ("isb");
        flash_wait_busy(addr);
    }

    if (!is_bank2) CLR_FIELD(FLASH_CR1, FLASH_CR1_PG1);
    else CLR_FIELD(FLASH_CR2, FLASH_CR2_PG2);
    
    flash_lock(addr);
    return TI_ERRC_NONE;
}