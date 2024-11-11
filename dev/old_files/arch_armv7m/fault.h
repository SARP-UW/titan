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
 * @file src/arch/armv7m/internal/fault.h
 * @authors Aaron McBride
 * @brief Fault management facilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  /**
   * @brief Denotes the cause of a memmanage fault.
   */
  typedef enum {
    mem_fault_stacking, /** @brief MPU access violation on exception entry. */
    mem_fault_unstacking, /** @brief MPU access violation on exception return. */
    mem_fault_fp_state, /** @brief MPU access violation when saving FP state on exception entry. */
    mem_fault_data, /** @brief MPU access violation on explicit memory access. */
    mem_fault_instruction, /** @brief MPU access violation on instruction fetch (XN/protected memory). */
    mem_fault_unknown, /** @brief Unknown cause. */
    mem_fault_none /** @brief No fault is active. */
  }mem_fault_id_t;

  /**
   * @brief Denotes the cause of a bus fault.
   */
  typedef enum {
    bus_fault_stacking, /** @brief Failure to save stack on exception entry. */
    bus_fault_unstacking, /** @brief Failure to restore stack on exception exit. */
    bus_fault_fp_state, /** @brief Failure to save FP state on exception entry. */
    bus_fault_instruction, /** @brief Failure to fetch instruction. */
    bus_fault_sync_data, /** @brief Explicit memory access failure (from specific instruction). */
    bus_fault_async_data, /** @brief Explicit memory access failure (from unknown instruction). */
    bus_fault_unknown, /** @brief Unknown cause. */
    bus_fault_none /** @brief No fault is active. */
  }bus_fault_id_t;

  /**
   * @brief Denotes the cause of a usage fault.
   */
  typedef enum {
    usage_fault_instruction, /** @brief Attempt to execute invalid instruction. */
    usage_fault_coprocessor, /** @brief Attempt to access invalid coprocessor. */
    usage_fault_state, /** @brief Attempt to execute instruction when espr.t equals zero. */
    usage_fault_return, /** @brief Integrity check failure on exception return. */
    usage_fault_unaligned, /** @brief Unaligned load/store (optional fault). */
    usage_fault_division, /** @brief Invalid division operation - divide by zero (optional fault). */
    usage_fault_unknown, /** @brief Unknown cause. */
    usage_fault_none /** @brief No fault is active. */
  }usage_fault_id_t;

  /**
   * @brief Denotes the cause of a hard fault.
   */
  typedef enum {
    hard_fault_invalid_prio, /** @brief Fault/supervisor call when current execution has higher priority. */
    hard_fault_debug, /** @brief Debug event not handled by debug monitor (likely bkpt). */
    hard_fault_vecttbl, /** @brief Attempt to access invalid vtable address. */
    hard_fault_unknown, /** @brief Unknown cause (likely unhandled mem/bus/usg fault). */
    hard_fault_none /** @brief No fault is active. */
  }hard_fault_id_t;

  /**
   * @brief Contains information about a memmanage fault.
   */
  typedef struct {
    bool addr_valid; /** @brief True if 'fault_addr' is valid, or false otherwise. */
    uint32_t fault_addr; /** @brief Contains the invalid address that was accessed. */
    mem_fault_id_t id; /** @brief The ID/cause of the memmanage fault. */
  }mem_fault_info_t;

  /**
   * @brief Contains information about a bus fault.
   */
  typedef struct {
    bool addr_valid; /** @brief True if 'fault_addr' is valid, or false otherwise. */
    uint32_t fault_addr; /** @brief Contains the invalid address that was accessed. */
    bus_fault_id_t id; /** @brief The ID/cause of the bus fault. */
  }bus_fault_info_t;

  /**
   * @defgroup set_x_fault_enabled
   * @brief Enables or disables a specific fault.
   * @param enabled (bool) True = enabled, false = disabled.
   * @note - If a fault is disabled when triggered, it will be escalated 
   *         to a hard fault.
   * @note - Hard fault is always enabled.
   * @{
   */
  void set_mem_fault_enabled(const bool enabled);
  void set_bus_fault_enabled(const bool enabled);
  void set_usage_fault_enabled(const bool enabled);
  /** @} */

  /**
   * @defgroup get_x_fault_enabled
   * @brief Gets the enabled status of a specific fault.
   * @returns (bool) True if the fault is enabled, or false otherwise.
   * @note - Hard fault is always enabled.
   * @{
   */
  bool get_memnmanage_fault_enabled(void);
  bool get_bus_fault_enabled(void);
  bool get_usage_fault_enabled(void);
  /** @} */

  /**
   * @defgroup set_x_fault_priority
   * @brief Sets the priority level of a specific fault's interrupt.
   * @param priority (int32_t) The priority level (0 - 255).
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - This function returns false if 'priority' is out of range.
   * @note - The priority level of hard fault is fixed at 0.
   * @{
   */
  bool set_mem_fault_priority(const int32_t priority);
  bool set_bus_fault_priority(const int32_t priority);
  bool set_usage_fault_priority(const int32_t priority);
  /** @} */

  /**
   * @defgroup get_x_fault_priority
   * @brief Gets the priority level of a specific fault's interrupt.
   * @returns (int32_t) The priority level (0 - 255).
   * @note - The priority level of hard fault is fixed at 0.
   * @{
   */
  int32_t get_mem_fault_priority(void);
  int32_t get_bus_fault_priority(void);
  int32_t get_usage_fault_priority(void);
  /** @} */

  /**
   * @defgroup set_x_fault_pending
   * @brief Sets the pending status of a specific fault.
   * @param pending (bool) True = pending, false = not pending.
   * @{
   */
  void set_mem_fault_pending(const bool pending);
  void set_bus_fault_pending(const bool pending);
  void set_usage_fault_pending(const bool pending);
  /** @} */

  /**
   * @defgroup get_x_fault_pending
   * @brief Gets the pending status of a specific fault.
   * @returns (bool) True if the fault's interrupt is pending, or false otherwise.
   * @note - Hard fault will never be pending because it's priority level is 0.
   * @{
   */
  bool get_mem_fault_pending(void);
  bool get_bus_fault_pending(void);
  bool get_usage_fault_pending(void);
  /** @} */

  /**
   * @defgroup get_x_fault_active
   * @brief Determines if a specific fault is currently active.
   * @returns (bool) True if the fault is active, or false otherwise.
   * @note - A fault is considered active if it's interrupt is currently
   *         being serviced by the CPU.
   * @note - This function will only ever return true when invoked from
   *         the specified fault's interrupt context.
   * @{
   */
  bool get_mem_fault_active(void);
  bool get_bus_fault_active(void);
  bool get_usage_fault_active(void);
  bool get_hard_fault_active(void);
  /** @} */

  /**
   * @defgroup get_x_fault_info
   * @brief Gets information about a specific fault.
   * @returns (x_fault_info_t) A type containing information about the fault.
   * @note - If the specified fault is not active, the id field/value will
   *         be set to x_fault_none.
   * @{
   */
  mem_fault_info_t get_mem_fault_info(void);
  bus_fault_info_t get_bus_fault_info(void);
  usage_fault_id_t get_usage_fault_info(void);
  hard_fault_id_t get_hard_fault_info(void);
  /** @} */

#if defined(__cplusplus)
  }
#endif