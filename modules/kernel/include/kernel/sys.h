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
 * @brief System control utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

enum ti_sys_sleep_mode_t {
  TI_SYS_SLEEP_MODE_NORMAL,
  TI_SYS_SLEEP_MODE_DEEP,
};

__attribute__((noreturn)) void ti_sys_restart(void);

__attribute__((noreturn)) void ti_sys_sleep(enum ti_sys_sleep_mode_t mode);