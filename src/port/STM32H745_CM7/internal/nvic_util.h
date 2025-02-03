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
 * @file src/port/STM32H745_CM7/internal/nvic_util.h
 * @authors Aaron McBride
 * @brief Nested Vectored Interrupt Controller (NVIC) utilities.
 */

#pragma once
#include "src/port/STM32H745_CM7/internal/compat.h"
#include "src/port/STM32H745_CM7/internal/mmio.h"
#include "src/port/STM32H745_CM7/internal/interrupt.h"

COMPAT_FILE

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * NVIC Interface
   ************************************************************************************************/

  /**
   * @brief Determines if the given IRQ number is valid.
   * @param irq_num (int32_t) The IRQ number to check
   * @returns (bool) True if @p [irq_num] is the number of a valid IRQ, or 
   *          false otherwise.
   */
  bool is_valid_irq(int32_t irq_num);

  /**
   * @brief Sets the enabled state of the given IRQ.
   * @param irq_num (int32_t) The number of the target IRQ interrupt.
   * @param enabled (bool) True to enable the IRQ, or false to disable it.
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If @p [irq_num] is invalid, this function has no side effects,
   *         and returns false.
   */
  bool set_irq_enabled(int32_t irq_num, bool enabled);

  /**
   * @brief Determines if the given IRQ is enabled.
   * @param irq_num (int32_t) The number of the target IRQ interrupt.
   * @returns (bool) True if the IRQ is enabled, or false otherwise.
   * @note - If @p [irq_num] is invalid, this function has no side effects,
   *         and returns false.
   */
  bool get_irq_enabled(int32_t irq_num);

  /**
   * @brief Sets the priority of the given IRQ.
   * @param irq_num (int32_t) The number of the target IRQ interrupt.
   * @param priority (int32_t) The priority value to set.
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If @p [irq_num] is invalid, this function has no side effects,
   *         and returns false.
   */
  bool set_irq_priority(int32_t irq_num, int32_t priority);

  /**
   * @brief Gets the priority of the given IRQ.
   * @param irq_num (int32_t) The number of the target IRQ interrupt.
   * @returns (int32_t) The priority value of the IRQ.
   * @note - If @p [irq_num] is invalid, this function has no side effects,
   *         and returns false.
   */
  int32_t get_irq_priority(int32_t irq_num);

  /**
   * @brief Sets the pending state of the given IRQ.
   * @param irq_num (int32_t) The number of the target IRQ interrupt.
   * @param pending (bool) True to set the IRQ as pending, or false to clear it.
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If @p [irq_num] is invalid, this function has no side effects,
   *         and returns false.
   */
  bool set_irq_pending(int32_t irq_num, bool pending);

  /**
   * @brief Determines if the given IRQ is pending.
   * @param irq_num (int32_t) The number of the target IRQ interrupt.
   * @returns (bool) True if the IRQ is pending, or false otherwise.
   * @note - If @p [irq_num] is invalid, this function has no side effects,
   *         and returns false.
   */
  bool get_irq_pending(int32_t irq_num);

  /**
   * @brief Gets the number of the active IRQ interrupt.
   * @returns (int32_t) The number of the active IRQ interrupt, or -1 otherwise.
   */
  int32_t get_active_irq(void);

  /************************************************************************************************
   * Implementation of NVIC Interface
   ************************************************************************************************/

  bool is_valid_irq(int32_t irq_num) {
    return (irq_num >= 0) && (irq_num <= IRQ_COUNT);
  }

  bool set_irq_enabled(int32_t irq_num, bool enabled) {
    if (!is_valid_irq(irq_num)) { 
      return false; 
    }
    const uint32_t reg_msk = UINT32_C(1) << (irq_num % 32);
    if (enabled) {
      *NVIC_ISERx[irq_num / 32] |= reg_msk;
    } else {
      *NVIC_ICERx[irq_num / 32] |= reg_msk;
    }
    return true;
  }

  bool get_irq_enabled(int32_t irq_num) {
    if (!is_valid_irq(irq_num)) { 
      return false; 
    }
    const uint32_t reg_msk = UINT32_C(1) << (irq_num % 32);
    return *NVIC_ISERx[irq_num / 32] & reg_msk;
  }

  bool set_irq_priority(int32_t irq_num, int32_t priority) {
    if (!is_valid_irq(irq_num) || (priority < 0) || (priority > NVIC_MAX_PRIO)) { 
      return false; 
    }
    const uint32_t prio_val = (uint32_t)priority << (UINT32_C(8) - NVIC_PRIO_BITS);
    write_field(NVIC_IPRx[irq_num / 4], NVIC_IPRx_IPR_Nx[irq_num % 4], prio_val);
    return true;
  }

  int32_t get_irq_priority(int32_t irq_num) {
    if (!is_valid_irq(irq_num)) { 
      return false; 
    }
    const uint32_t prio_val = read_field(NVIC_IPRx[irq_num / 4], NVIC_IPRx_IPR_Nx[irq_num % 4]);
    return (int32_t)(prio_val >> (UINT32_C(8) - NVIC_PRIO_BITS));
  }

  bool set_irq_pending(int32_t irq_num, bool pending) {
    if (!is_valid_irq(irq_num)) { 
      return false; 
    }
    const uint32_t reg_msk = UINT32_C(1) << (irq_num % 32);
    if (pending) {
      *NVIC_ISPRx[irq_num / 32] |= reg_msk;
    } else {
      *NVIC_ICPRx[irq_num / 32] |= reg_msk;
    }
    return true;
  }

  bool get_irq_pending(int32_t irq_num) {
    if (!is_valid_irq(irq_num)) { 
      return false; 
    }
    const uint32_t reg_msk = UINT32_C(1) << (irq_num % 32);
    return *NVIC_ISPRx[irq_num / 32] & reg_msk;
  }

  int32_t get_active_irq(void) {
    int32_t exc_num;
    TI_VOLATILE_ASM (
      "MRS %0, IPSR" 
      : "=r"(exc_num)
    );
    const int32_t irq_num = irq_num - IRQN_EXC_OFFSET;
    return (irq_num < 0) ? -1 : irq_num;
  } 

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */