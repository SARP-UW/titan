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
 * @file peripheral/errc.c
 * @authors Mahir Emran
 * @brief Internal flash-backed error logging implementation.
 */
#include "errc.h"
#include "flash.h"
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define LOG_ENTRY_COUNT  (TI_LOG_FLASH_SIZE / TI_LOG_ENTRY_SIZE)

static bool             s_initialized = false;
static uint32_t         s_write_offset = 0;
static volatile bool    s_log_busy = false;

static void log_strlcpy(char *dst, const char *src, uint32_t dst_size) {
    if (!dst || dst_size == 0) return;
    uint32_t i = 0;
    while (i < dst_size - 1 && src && src[i] != '\0') {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
}

static const char *log_basename(const char *path) {
    if (!path) return "";
    const char *last = path;
    for (const char *p = path; *p; p++) {
        if (*p == '/' || *p == '\\') last = p + 1;
    }
    return last;
}

static void log_advance_offset(void) {
    s_write_offset += TI_LOG_ENTRY_SIZE;
    if (s_write_offset >= TI_LOG_FLASH_SIZE) {
        s_write_offset = 0;
        ti_internal_flash_erase_sector(TI_LOG_FLASH_START);
    }
}

enum ti_errc_t ti_log_init(void) {
    if (s_initialized) return TI_ERRC_NONE;

    s_write_offset = 0;
    for (uint32_t i = 0; i < LOG_ENTRY_COUNT; i++) {
        uint32_t abs_addr = TI_LOG_FLASH_START + s_write_offset;
        uint32_t magic = *(volatile uint32_t*)abs_addr; // NOLINT(performance-no-int-to-ptr)

        if (magic == 0xFFFFFFFFU) { 
            s_initialized = true;
            return TI_ERRC_NONE;
        }
        s_write_offset += TI_LOG_ENTRY_SIZE;
    }

    s_write_offset = 0;
    ti_internal_flash_erase_sector(TI_LOG_FLASH_START);
    s_initialized = true;
    return TI_ERRC_NONE;
}

void ti_log_write(enum ti_errc_t errc, const char *msg,
                  const char *func, const char *file, uint32_t line) {
    if (!s_initialized || s_log_busy) return;
    s_log_busy = true;

    ti_log_entry_t entry = {0};
    entry.magic = TI_LOG_MAGIC;
    entry.errc  = (uint8_t)errc;
    entry.line  = line;

    log_strlcpy(entry.func, func ? func : "", sizeof(entry.func));
    log_strlcpy(entry.file, log_basename(file), sizeof(entry.file));
    log_strlcpy(entry.msg,  msg  ? msg  : "", sizeof(entry.msg));

    uint32_t abs_addr = TI_LOG_FLASH_START + s_write_offset;
    ti_internal_flash_write(abs_addr, &entry, TI_LOG_ENTRY_SIZE);
    log_advance_offset();

    s_log_busy = false;
}