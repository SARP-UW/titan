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
 * @file modules/kernel/include/kernel/sys.h
 * @authors Aaron McBride
 * @brief General system utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "util/errc.h"

enum ti_core_id_t {
  TI_CORE_ID_CM7,
  TI_CORE_ID_CM4,
};

void ti_sys_restart(void);

void ti_sys_shutdown(void);

void ti_sys_sleep(void);

void ti_enter_critical(void);

void ti_exit_critical(void);

void ti_reset_critical(void);

bool ti_is_critical(void);

void ti_enter_exclusive(enum ti_errc_t* errc_out);

void ti_exit_exclusive(enum ti_errc_t* errc_out);

void ti_reset_exclusive(enum ti_errc_t* errc_out);

bool ti_is_exclusive(void);

enum ti_core_id_t ti_get_core(void);

bool ti_is_interrupt(void);

#define TI_CRITICAL(...) do { \
  ti_enter_critical(); \
  __VA_ARGS__ \
  ti_exit_critical(); \
} while (0)

#define TI_EXCLUSIVE(...) do { \
  ti_enter_exclusive(); \
  __VA_ARGS__ \
  ti_exit_exclusive(); \
} while (0)