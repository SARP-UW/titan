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

  /**************************************************************************************************
   * @section Systick Utility Functions
   **************************************************************************************************/

  /**
   * @brief Determines the duration that corresponds with a given systick value.
   * @param systick_value (int64_t) The systick value to convert.
   * @returns (int64_t) The duration in microseconds that corresponds to the 
   *          given systick value.
   */
  int64_t systick_value_to_duration(const int64_t systick_value);

  /**
   * @brief Determines the systick value that corresponds to a given duration.
   * @param micros (int64_t) The duration in microseconds to convert.
   * @returns (int64_t) The systick value that corresponds to the given duration.
   */
  int64_t duration_to_systick_value(const int64_t micros);

  /**************************************************************************************************
   * @section Systick Management Facilities
   **************************************************************************************************/

  /**
   * @brief Enables or disables the systick counter.
   * @param enabled (bool) True to enable, false to disable.
   * @warning - Enabling the systick counter when the reload value is set to 0
   *            will cause the system to lock up.
   */
  void set_systick_enabled(const bool enabled);

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
  bool set_systick_reload_value(const int64_t value);

  /**
   * @brief Gets the reload value of the systick counter.
   * @returns (int64_t) The current reload value of the systick counter 
   *          (0 - 24 bits).
   * @note - The reload value is the value loaded into the systick counter each
   *         time it counts down to zero.
   */
  int64_t get_systick_reload_value();

  /**
   * @brief Sets the current value of the systick counter.
   * @param value (int64_t) The value to set the systick counter to (0 - 32 bits).
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If 'value' is out of range, this function will return false.
   */
  bool set_systick_value(const int64_t value);

  /**
   * @brief Gets the current value of the systick counter.
   * @returns (int64_t) The current value of the systick counter.
   */
  int64_t get_systick_value(void);

  /**
   * @brief Sets the value of the systick counter to it's "reload" value.
   */
  void reload_systick(void);

  /**************************************************************************************************
   * @section Interrupt Management Facilities
   **************************************************************************************************/

  /**
   * @brief Sets the priority level of the systick interrupt.
   * @param priority (int32_t) The priority level to set (0 - 255).
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If 'priority' is out of range, this function will return false.
   */
  bool set_systick_int_priority(const int32_t priority);

  /**
   * @brief Gets the priority level of the systick interrupt.
   * @returns (int32_t) The priority level of the systick interrupt.
   */
  int32_t get_systick_int_priority(void);

  /**
   * @brief Sets the pending status of the systick interrupt.
   * @param pending (bool) True to set the systick interrupt's pending status, or
   *                false to clear it.
   */
  void set_systick_int_pending(const bool pending);

  /**
   * @brief Gets the pending status of the systick interrupt.
   * @returns (bool) True if the systick interrupt is pending, or false otherwise.
   */
  bool get_systick_int_pending(void);

  /**
   * @brief Determines if the systick interrupt is currently active.
   * @returns (bool) True if the systick interrupt is active, or false otherwise.
   * @note - This function only returns true if called from the systick's
   *         interrupt context.
   */
  bool get_systick_int_active(void);

#if defined(__cplusplus)
  }
#endif