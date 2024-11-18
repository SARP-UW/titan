/**
 * This file is part of the Titan Avionics Library
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
 * @file src/arch/armv7m/internal/systick.h
 * @authors Aaron McBride
 * @brief Systick management facilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  #define default_systick_period 1000
  #define default_systick_interrupt_priority 128

  /**************************************************************************************************
   * @section Systick Management Facilities
   **************************************************************************************************/

  void init_systick();

  /**
   * @brief Enables or disables the systick counter.
   * @param enabled (bool) True to enable, false to disable.
   * @warning - Enabling the systick counter when the reload value is set to 0
   *            will cause the system to lock up.
   */
  void set_systick_enabled(const bool enabled, bool* const err);

  /**
   * @brief Gets the enabled status of the systick counter.
   * @returns (bool) True if the systick counter is enabled, or false otherwise.
   */
  bool get_systick_enabled(void);

  /**
   * @brief Sets the reload value of the systick counter.
   * @param value (int32_t) The reload value to set for the systick counter 
   *              (0 - 24 bits).
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If 'value' is out of range, this function will return false.
   * @note - The reload value is the value loaded into the systick counter each
   *         time it counts down to zero.
   * @warning - Setting the reload value to 0 when the systick counter is enabled
   *            will cause the system to lock up.
   */
  void set_systick_period(const int32_t ns, bool* const err);

  /**
   * @brief Gets the reload value of the systick counter.
   * @returns (int64_t) The current reload value of the systick counter 
   *          (0 - 24 bits).
   * @note - The reload value is the value loaded into the systick counter each
   *         time it counts down to zero.
   */
  int32_t get_systick_period(void);

  /**
   * @brief Sets the current value of the systick counter.
   * @param value (int64_t) The value to set the systick counter to (0 - 32 bits).
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If 'value' is out of range, this function will return false.
   */
  void set_systick_duration(const int32_t ns, bool* const err);

  /**
   * @brief Gets the current value of the systick counter.
   * @returns (int64_t) The current value of the systick counter.
   */
  int32_t get_systick_duration(void);

  /**
   * @brief Sets the value of the systick counter to it's "reload" value.
   */
  void restart_systick(void);

  /**************************************************************************************************
   * @section Interrupt Management Facilities
   **************************************************************************************************/

  void set_systick_interrupt_enabled(const bool enabled);

  bool get_systick_interrupt_enabled(void);

  /**
   * @brief Sets the priority level of the systick interrupt.
   * @param priority (int32_t) The priority level to set (0 - 255).
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If 'priority' is out of range, this function will return false.
   */
  void set_systick_interrupt_priority(const int32_t priority, bool* const err);

  /**
   * @brief Gets the priority level of the systick interrupt.
   * @returns (int32_t) The priority level of the systick interrupt.
   */
  int32_t get_systick_interrupt_priority(void);

  /**
   * @brief Sets the pending status of the systick interrupt.
   * @param pending (bool) True to set the systick interrupt's pending status, or
   *                false to clear it.
   */
  void set_systick_interrupt_pending(const bool pending);

  /**
   * @brief Gets the pending status of the systick interrupt.
   * @returns (bool) True if the systick interrupt is pending, or false otherwise.
   */
  bool get_systick_interrupt_pending(void);

  /**
   * @brief Determines if the systick interrupt is currently active.
   * @returns (bool) True if the systick interrupt is active, or false otherwise.
   * @note - This function only returns true if called from the systick's
   *         interrupt context.
   */
  bool get_systick_interrupt_active(void);

#if defined(__cplusplus)
  }
#endif