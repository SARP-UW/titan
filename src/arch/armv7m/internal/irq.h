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
 * @file arch/armv7m/internal/interrupt.h
 * @authors Aaron McBride
 * @brief IRQ interrupt management facilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**
   * @brief Gets the number of IRQ interrupts.
   * @returns (int32_t) The number of implemented IRQ interrupts.
   * @note - The return value denotes the max IRQ index + 1.
   */
  int32_t get_irq_count(void);

  /**
   * @brief Determines if an IRQ interrupt is valid.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @returns (bool) True if the specified IRQ interrupt is valid, or false
   *          otherwise (IRQ interrupt with 'index' is not implemented).
   */
  bool valid_irq_index(const int32_t index);

  /**
   * @brief Enabled or disables an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to modify.
   * @param enabled (bool) True to enable, false to disable.
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If 'index' is invalid, this function returns false.
   */
  bool set_irq_enabled(const int32_t index, const bool enabled);

  /**
   * @brief Gets the enabled status of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @returns (bool) True if the specified IRQ interrupt is enabled, or false
   *          otherwise.
   * @note - If 'index' is invalid, this function returns false.
   */
  bool get_irq_enabled(const int32_t index);

  /**
   * @brief Sets the priority level of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to modify.
   * @param priority (int32_t) The priority level to set (0 - 255).
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If 'index' is invalid, or 'priority' is out of range, this
   *         function returns false.
   */
  bool set_irq_priority(const int32_t index, const int32_t priority);

  /**
   * @brief Gets the priority level of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @returns (int32_t) The priority level of the specified IRQ interrupt, or -1
   *          if 'index' is invalid.
   */
  int32_t get_irq_priority(const int32_t index);

  /**
   * @brief Sets the pending status of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to modify.
   * @param pending (bool) True to set the IRQ interrupt's pending status, or
   *                false to clear it.
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If 'index' is invalid, this function returns false.
   */
  bool set_irq_pending(const int32_t index, const bool pending);

  /**
   * @brief Gets the pending status of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @returns (bool) True if the specified IRQ interrupt is pending, or false
   *          otherwise.
   * @note - If 'index' is invalid, this function returns false.
   */
  bool get_irq_pending(const int32_t index);

  /**
   * @brief Determines if an IRQ interrupt is currently active.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @returns (bool) True if the specified IRQ interrupt is active, or false
   *          otherwise.
   * @note - This function only returns true if called from the specified IRQ's
   *         execution context.
   * @note - If 'index' is invalid, this function returns false.
   */
  bool get_irq_active(const int32_t index);

#if defined(__cplusplus)
  }
#endif