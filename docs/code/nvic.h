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
 * @file modules/core/include/core/nvic.h
 * @authors Aaron McBride
 * @brief NVIC (Nested Vectored Interrupt Controller) driver.
 */

 #pragma once
 #include <stdint.h>
 #include <stdbool.h>

/**
 * @brief Determines if an IRQ number is valid.
 * @param irq_num (int32_t) The IRQ number to query.
 * @returns (bool) True if @p [irq_num] is valid, or false otherwise.
 */
bool is_valid_irq(int32_t irq_num);

/**
 * @brief Sets the enabled state of an IRQ interrupt.
 * @param irq_num (int32_t) The number of the IRQ to modify.
 * @param enabled (bool) The enable state to set.
 * @returns (bool) True if the operation was successful, or false otherwise.
 */
bool set_irq_enabled(int32_t irq_num, bool enabled);

/**
 * @brief Determines if an IRQ interrupt is enabled.
 * @param irq_num (int32_t) The number of the IRQ to query.
 * @returns (bool) The enabled state of the specified IRQ interrupt.
 * @note - If @p [irq_num] is invalid, this function returns false.
 */
bool get_irq_enabled(int32_t irq_num);

/**
 * @brief Sets the priority of an IRQ interrupt.
 * @param irq_num (int32_t) The number of the IRQ to modify.
 * @param priority (int32_t) The priority value to set.
 * @returns (bool) True if the operation was successful, or false otherwise.
 */
bool set_irq_priority(int32_t irq_num, int32_t priority);

/**
 * @brief Gets the priority of an IRQ interrupt.
 * @param irq_num (int32_t) The number of the IRQ to query.
 * @returns (int32_t) The priority value of the specified IRQ interrupt.
 */
int32_t get_irq_priority(int32_t irq_num);

/**
 * @brief Sets the pending state of an IRQ interrupt.
 * @param irq_num (int32_t) The number of the IRQ to modify.
 * @param pending (bool) The pending state to set.
 * @returns (bool) True if the operation was successful, or false otherwise.
 */
bool set_irq_pending(int32_t irq_num, bool pending);

/**
 * @brief Determines if an IRQ interrupt is pending.
 * @param irq_num (int32_t) The number of the IRQ to query.
 * @returns (bool) The pending state of the specified IRQ interrupt.
 * @note - If @p [irq_num] is invalid, this function returns false.
 */
bool get_irq_pending(int32_t irq_num);

/**
 * @brief Gets the number of the active IRQ.
 * @returns (int32_t) The number of the currently executing IRQ
 *          or -1 if no IRQ is executing.
 */
int32_t get_active_irq(void);