/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2024 UW SARP
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
 * @file modules/mcu/include/mcu/timer.c
 * @authors Charles Faisandier
 * @brief Implementatin of STM32H7 timer interface.
 */
#include "internal/mmio.h"
#include "mcu/exti.h"
#include "mcu/hrtim.h"
#include "internal/interrupt.h"

/**************************************************************************************************
 * @section Internal Data Structures
 **************************************************************************************************/

void (*callback)(void);

/**************************************************************************************************
 * @section Public Functions
 **************************************************************************************************/

int hrtim_enable_mrep(struct hrtim_config_t *config) {
  // Check parameters
  if (config == NULL || config->callback == NULL || config->period & 0x80 ||
      config->priority > 4)

  // Register the callback
  callback = config->callback;

  // Enable HRTIM Clock
  SET_FIELD(RCC_APB2ENR, RCC_APB2ENR_HRTIMEN);

  // HRTIM_MCR Set Master Prescaler
  WRITE_FIELD(HRTIM_MASTER_MCR, HRTIM_MASTER_MCR_CK_PSC, config->prescaler);

  // HRTIM_MPER Set Master Period
  WRITE_FIELD(HRTIM_MASTER_MPER, HRTIM_MASTER_MPER_MPER, config->period);

  // Enable the interrupt: HRTIM_MDIER
  SET_FIELD(HRTIM_COMMON_BDMUPDR, HRTIM_COMMON_BDMUPDR_MDIER);

  // Enable the interupt and set the priority
  ti_irq_enabled(103);

  // Start the timer MCR_CEN
  SET_FIELD(HRTIM_MASTER_MCR, HRTIM_MASTER_MCR_MCEN);
}

/**************************************************************************************************
 * @section Private Functions
 **************************************************************************************************/

void irq_103_handler(void) { callback(); }