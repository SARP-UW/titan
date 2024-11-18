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

  /**************************************************************************************************
   * @section IRQ Management Configuration
   **************************************************************************************************/

  #define default_irq_priority 128

  /**************************************************************************************************
   * @section IRQ Management Facilities
   **************************************************************************************************/

  /**
   * @brief Gets the number of IRQ interrupts.
   * @returns (int32_t) The number of implemented IRQ interrupts.
   * @note - The return value denotes the max IRQ index + 1.
   */
  int32_t get_irq_count(void);

  /**
   * @brief Initializes an IRQ interrupt to it's default state.
   * @param index (int32_t) The index of the IRQ interrupt to initialize.
   * @param err (bool*) The error flag. Accessed and set true if 'index' is
   *            invalid, or an internal error occurs.
   * @note - This functions disables the IRQ interrupt, set it's pending status 
   *         to false, and sets it's priority level to 'default_irq_priority'.
   */
  void init_irq(const int32_t index, bool* const err);

  /**
   * @brief Enabled or disables an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to modify.
   * @param enabled (bool) True to enable, false to disable.
   * @param err (bool*) The error flag. Accessed and set true if 'index' is 
   *            invalid, or an internal error occurs.
   */
  void set_irq_enabled(const int32_t index, const bool enabled, 
      bool* const err);

  /**
   * @brief Gets the enabled status of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @param err (bool*) The error flag. Accessed and set true if 'index' is 
   *            invalid, or an internal error occurs.
   * @returns (bool) True if no error occurs and the specified IRQ interrupt
   *          is enabled, or false otherwise.
   */
  bool get_irq_enabled(const int32_t index, bool* const err);

  /**
   * @brief Sets the priority level of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to modify.
   * @param priority (int32_t) The priority level to set (0 - 255).
   * @param err (bool*) The error flag. Accessed and set true if 'index' is 
   *            invalid, 'priority' is out of bounds, or an internal error 
   *            occurs.
   */
  void set_irq_priority(const int32_t index, const int32_t priority, 
      bool* const err);

  /**
   * @brief Gets the priority level of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @param err (bool*) The error flag. Accessed and set true if 'index' is 
   *            invalid, or an internal error occurs.
   * @returns (int32_t) The priority level of the specified IRQ interrupt, or 
   *          -1 if an error occurs.
   */
  int32_t get_irq_priority(const int32_t index, bool* const err);

  /**
   * @brief Sets the pending status of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to modify.
   * @param pending (bool) True to set the IRQ interrupt's pending status, or
   *                false to clear it.
   * @param err (bool*) The error flag. Accessed and set true if 'index' is 
   *            invalid, or an internal error occurs.
   * @note - An IRQ interrupt will remain in the pending state until it is
   *         enabled and serviced by the NVIC.
   * @note - Disabling an IRQ interrupt does not clear it's pending status.
   */
  void set_irq_pending(const int32_t index, const bool pending, 
      bool* const err);

  /**
   * @brief Gets the pending status of an IRQ interrupt.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @param err (bool*) The error flag. Accessed and set true if 'index' is 
   *            invalid, or an internal error occurs.
   * @returns (bool) True if no error occurs and the specified IRQ interrupt 
   *          is pending, or false otherwise.
   */
  bool get_irq_pending(const int32_t index, bool* const err);

  /**
   * @brief Determines if an IRQ interrupt is currently active.
   * @param index (int32_t) The index of the IRQ interrupt to query.
   * @param err (bool*) The error flag. Accessed and set true if 'index' is 
   *            invalid, or an internal error occurs.
   * @returns (bool) True if no error occurs and the specified IRQ interrupt 
   *          is active, or false otherwise.
   */
  bool get_irq_active(const int32_t index, bool* const err);

#if defined(__cplusplus)
  }
#endif