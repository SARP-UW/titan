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
 * @file src/STM32H745_CM7/subsys/hsem.h
 * @authors Aaron McBride
 * @brief Hardware semaphore (HSEM) driver.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "STM32H745/resource/mmio.h"
#include "STM32H745/resource/interrupt.h"
#include "STM32H745/subsys/sys_util.h"

#ifdef __IAR_SYSTEMS_ICC__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Implementation Resources
   ************************************************************************************************/

  // COREID register values for CM7/CM4 core.
  #define _HSEM_CM4_COREID 3
  #define _HSEM_CM7_COREID 1

  // Gets the coreid of the core executing the function.
  static uint32_t _get_exec_coreid() {
    if (get_active_core() == CORE_CM7) {
      return _HSEM_CM7_COREID;
    } else {
      return _HSEM_CM4_COREID;
    }
  }

  /************************************************************************************************
   * HSEM Control Functions
   ************************************************************************************************/

  /** @brief The number of implemented HSEMs. */
  #define HSEM_COUNT 32

  /**
   * @brief Determines if the given HSEM index is valid.
   * @param index (int32_t) The target HSEM index.
   * @returns (bool) True if the index is valid, or false otherwise.
   */
  bool is_valid_hsem(int32_t index) {
    return index >= 0 && index < HSEM_COUNT;
  }
  
  /**
   * @brief Aquires the specified HSEM (blocking).
   * @param index (int32_t) The index of the target HSEM.
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If @p [index] is invalid, this function does nothing and returns false.
   */
  bool aquire_hsem(int32_t index) {
    if (!is_valid_hsem(index)) { 
      return false; 
    }
    const uint32_t exec_coreid = _get_exec_coreid();
    while(READ_FIELD(HSEM_RLRx[index], HSEM_RLRx_COREID) != exec_coreid);
    return true;
  }

  /**
   * @brief Releases the specified HSEM.
   * @param index (int32_t) The index of the target HSEM.
   * @returns (bool) True if the operation was successful, or false otherwise.
   * @note - If @p [index] is invalid, this function does nothing and returns false.
   */
  bool release_hsem(int32_t index) {
    if (!is_valid_hsem(index)) { 
      return false; 
    }
    uint32_t tmp_rl_reg = *HSEM_Rx[index];
    CLR_FIELD(&tmp_rl_reg, HSEM_RLRx_COREID);
    CLR_FIELD(&tmp_rl_reg, HSEM_RLRx_PROCID);
    CLR_FIELD(&tmp_rl_reg, HSEM_RLRx_LOCK);
    *HSEM_Rx[index] = tmp_rl_reg;
    return true;
  }

  /**
   * @brief Gets the owner of the specified HSEM.
   * @param index (int32_t) The index of the target HSEM.
   * @returns (core_id_t) The core ID of the HSEM owner, or CORE_NULL if 
   *          the HSEM is not locked/aquired or @p [index] is invalid.
   */
  core_id_t get_hsem_owner(int32_t index) {
    if (is_valid_hsem(index) && IS_FIELD_SET(HSEM_Rx[index], HSEM_Rx_LOCK)) {
      const uint32_t coreid = READ_FIELD(HSEM_Rx[index], HSEM_Rx_COREID);
      return coreid == _HSEM_CM7_COREID ? CORE_CM7 : CORE_CM4;
    }
    return CORE_NULL;
  }

  /**
   * @brief Declares a scope in which a specified HSEM is aquired.
   * @param index (int32_t) The index of the target HSEM.
   * @param ... (tokens) The contents of the HSEM section/scope.
   * @note - This macro should be prefered over @ref aquire_hsem() and @ref release_hsem().
   * @note - Interrupts are disabled for the duration of the defined scope.
   * @note - If @p [index] is invalid, the given code is executed normally.
   * @note - @p [index] is only expanded once.
   */
  #define HSEM_SECTION(index, ...) \
  CRIT_SECTION( \
    const int32_t __hsem_index = (index); \
    const core_id_t __hsem_owner = get_hsem_owner(__hsem_index); \
    aquire_hsem(__hsem_index); \
    do { __VA_ARGS__ } while (0); \
    if (__hsem_owner != get_active_core()) { \
      release_hsem(__hsem_index); \
    } \
  )

#ifdef __cplusplus
  } // extern "C"
#endif