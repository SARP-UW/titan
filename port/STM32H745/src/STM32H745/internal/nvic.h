/**
 * This file is part of the Titan HAL
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
 * @internal
 * @file src/STM32H745_CM7/nvic.h
 * @authors Aaron McBride
 * @brief Internal NVIC driver.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "STM32H745/internal/mmio.h"
#include "STM32H745/internal/interrupt.h" 

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Implementation Resources
   ************************************************************************************************/

  // Field widths.
  static const int32_t _NVIC_FIELD_WIDTH = 1;
  static const int32_t _IPR_FIELD_WIDTH = 8;

  // Register widths.
  static const int32_t _NVIC_REG_WIDTH = 32;
  static const int32_t _IPR_REG_WIDTH = 32;

  // IRQ number division factors.
  static const int32_t _NVIC_IRQ_DIV = _NVIC_REG_WIDTH / _NVIC_FIELD_WIDTH;
  static const int32_t _IPR_IRQ_DIV = _IPR_REG_WIDTH / _IPR_FIELD_WIDTH;

  // Gets the NVIC field corresponding to the specified IRQ.
  static field32_t _get_irq_nvic_field(int32_t irq_num) {
    return MAKE_FIELD(field32_t, irq_num % _NVIC_IRQ_DIV, 1);
  }

  // Gets the NVIC register corresponding to the specified IRQ.
  static rw_reg32_t _get_irq_nvic_reg(rw_reg32_t* reg_array, int32_t irq_num) {
    return reg_array[irq_num / _NVIC_IRQ_DIV];
  }

  // Gets the IPR field corresponding to the specified IRQ.
  static field32_t _get_irq_ipr_field(int32_t irq_num) {
    return NVIC_IPRx_IPR_Nx[irq_num % _IPR_IRQ_DIV];
  }

  // Gets the IPR register corresponding to the specified IRQ.
  static rw_reg32_t _get_irq_ipr_reg(int32_t irq_num) {
    return NVIC_IPRx[irq_num / _IPR_IRQ_DIV];
  }

  /************************************************************************************************
   * NVIC Control Functions
   ************************************************************************************************/

  /**
   * @brief Determines if an IRQ number is valid.
   * @param irq_num (int32_t) The IRQ number to query.
   * @returns (bool) True if @p [irq_num] is valid, or false otherwise.
   */
  bool is_valid_irq(int32_t irq_num) {
    return (irq_num >= 0) && (irq_num < IRQ_COUNT);
  }

  /**
   * @brief Sets the enabled state of an IRQ interrupt.
   * @param irq_num (int32_t) The number of the IRQ to modify.
   * @param enabled (bool) The enable state to set.
   * @returns (bool) True if the operation was successful, or false otherwise.
   */
  bool set_irq_enabled(int32_t irq_num, bool enabled) {
    if (!is_valid_irq(irq_num)) {
      return false;
    }
    const field32_t irq_nvic_field = _get_irq_nvic_field(irq_num);
    if (enabled) {
      const rw_reg32_t irq_iser_reg = _get_irq_nvic_reg(NVIC_ISERx, irq_num);
      WRITE_FIELD(irq_iser_reg, irq_nvic_field, 1);
    } else {
      const rw_reg32_t irq_icer_reg = _get_irq_nvic_reg(NVIC_ICERx, irq_num);
      WRITE_FIELD(irq_icer_reg, irq_nvic_field, 1);
    }
    return true;
  }

  /**
   * @brief Determines if an IRQ interrupt is enabled.
   * @param irq_num (int32_t) The number of the IRQ to query.
   * @returns (bool) The enabled state of the specified IRQ interrupt.
   * @note - If @p [irq_num] is invalid, this function returns false.
   */
  bool is_irq_enabled(int32_t irq_num) {
    if (!is_valid_irq(irq_num)) {
      return false;
    }
    const field32_t irq_nvic_field = _get_irq_nvic_field(irq_num);
    const rw_reg32_t irq_iser_reg = _get_irq_nvic_reg(NVIC_ISERx, irq_num);
    return WRITE_FIELD(irq_iser_reg, irq_nvic_field, 1) == 1U;
  }

  /**
   * @brief Sets the priority of an IRQ interrupt.
   * @param irq_num (int32_t) The number of the IRQ to modify.
   * @param priority (int32_t) The priority value to set.
   * @returns (bool) True if the operation was successful, or false otherwise.
   */
  bool set_irq_priority(int32_t irq_num, int32_t priority) {
    if (!is_valid_irq(irq_num)) {
      return false;
    }
    const uint32_t prio_val = (uint32_t)priority << (_IPR_FIELD_WIDTH - NVIC_PRIO_BITS);
    const field32_t irq_ipr_field = _get_irq_ipr_field(irq_num); 
    const rw_reg32_t irq_ipr_reg = _get_irq_ipr_reg(irq_num);
    if (!IN_RANGE_FIELD(irq_ipr_field, prio_val)) {
      return false;
    }
    WRITE_FIELD(irq_ipr_reg, irq_ipr_field, prio_val);
    return true;
  }

  /**
   * @brief Gets the priority of an IRQ interrupt.
   * @param irq_num (int32_t) The number of the IRQ to query.
   * @returns (int32_t) The priority value of the specified IRQ interrupt.
   */
  int32_t get_irq_priority(int32_t irq_num) {
    if (!is_valid_irq(irq_num)) {
      return -1;
    }
    const field32_t irq_ipr_field = _get_irq_ipr_field(irq_num);
    const rw_reg32_t irq_ipr_reg = _get_irq_ipr_reg(irq_num);
    const uint32_t prio_val = READ_FIELD(irq_ipr_reg, irq_ipr_field);
    return (int32_t)(prio_val >> (_IPR_FIELD_WIDTH - NVIC_PRIO_BITS));
  }

  /**
   * @brief Sets the pending state of an IRQ interrupt.
   * @param irq_num (int32_t) The number of the IRQ to modify.
   * @param pending (bool) The pending state to set.
   * @returns (bool) True if the operation was successful, or false otherwise.
   */
  bool set_irq_pending(int32_t irq_num, bool pending) {
    if (!is_valid_irq(irq_num)) {
      return false;
    }
    const field32_t irq_nvic_field = _get_irq_nvic_field(irq_num);
    if (pending) {
      const rw_reg32_t irq_ispr_reg = _get_irq_nvic_reg(NVIC_ISPRx, irq_num);
      WRITE_FIELD(irq_ispr_reg, irq_nvic_field, 1);
    } else {
      const rw_reg32_t irq_icpr_reg = _get_irq_nvic_reg(NVIC_ICPRx, irq_num);
      WRITE_FIELD(irq_icpr_reg, irq_nvic_field, 1);
    }
    return true;
  }

  /**
   * @brief Determines if an IRQ interrupt is pending.
   * @param irq_num (int32_t) The number of the IRQ to query.
   * @returns (bool) The pending state of the specified IRQ interrupt.
   * @note - If @p [irq_num] is invalid, this function returns false.
   */
  bool get_irq_pending(int32_t irq_num) {
    if (!is_valid_irq(irq_num)) {
      return false;
    }
    const field32_t irq_nvic_field = _get_irq_nvic_field(irq_num);
    const rw_reg32_t irq_ispr_reg = _get_irq_nvic_reg(NVIC_ISPRx, irq_num);
    return READ_FIELD(irq_ispr_reg, irq_nvic_field) == 1U;
  }

  /**
   * @brief Gets the number of the active IRQ.
   * @returns (int32_t) The number of the currently executing IRQ
   *          or -1 if no IRQ is executing.
   */
  int32_t get_active_irq(void) {
    uint32_t active_exc;
    __asm__ volatile ("mrs %0, IPSR" : "=r" (active_exc));
    if (active_exc > IRQN_EXC_OFFSET) {
      return (int32_t)active_exc - IRQN_EXC_OFFSET;
    } else {
      return -1;
    }
  }

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */