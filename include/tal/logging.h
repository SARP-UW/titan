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
 * @file include/tal/logging.h
 * @authors Ashton Doane
 * @brief Logging utilities.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

#define TAL_LOG_MAX_SIZE 100

  /**************************************************************************************************
   * @section Logging Global Variables
   **************************************************************************************************/
  
  static char* tal_logs[TAL_LOG_MAX_SIZE]; //Implemented as a circular list.
  static int first_element_pos = 0;
  static int current_log_size = 0;

  /**************************************************************************************************
   * @section Log Read Utilities
   **************************************************************************************************/

  /**
   * @brief Returns the number of elements within the log.
   * @param err (bool*) Pointer to a boolean flagging whether the function has errored.
   * @returns (int) The number of data elements within the TAL log.
   */
  int tal_log_get_size(bool* err);
  
  /**
   * @brief Returns the data element at the idx requested in the log.
   * @param idx (int) The index of the element that would like to be read.
   * @param err (bool*) Pointer to a boolean flagging whether the function has errored.
   * @returns (char*) The pointer to the value at the requested position. If this position
   * is out of bounds, returns the NULL ptr instead.
   */
  char* tal_log_get_element(int idx, bool* err);
  
  /**************************************************************************************************
   * @section Log Modification Utilities
   **************************************************************************************************/
    
  /**
   * @brief Add a new log to the end of the array if not full. 
   * @param str (char*) Pointer to a char array
   * @param err (bool*) Pointer to a boolean flagging whether the function has errored.
   */
  void tal_log_append(const char* str, bool* err);
  
  /**
   * @brief Retrieves and removes the earliest log from the list.
   * @param err (bool*) Pointer to a boolean flagging whether the function has errored.
   * @returns (char*) A pointer to the data that was removed from the log.
   */
  char* tal_log_remove_first(bool* err);

  /**
   * @brief Retrieves and removes the most recent log from the list.
   * @param err (bool*) Pointer to a boolean flagging whether the function has errored.
   * @returns (char*) A pointer to the data that was removed from the log.
   */
  char* tal_log_remove_last(bool* err);

  /**************************************************************************************************
   * @section Function Implementations
   **************************************************************************************************/
  
  int tal_log_get_size(bool* err){
    return current_log_size;
  }
  
  // Note, this returns the pointer --> allows modification at the source. 
  // Not sure if this is good practice.
  char* tal_log_get_element(int idx, bool* err){
    if(idx >= current_log_size){
      *err = true;
      return (void*)0;
    }
    const int pos = (first_element_pos + idx)% TAL_LOG_MAX_SIZE;
    return tal_logs[pos];
  }

  void tal_log_append(const char* str, bool* err){
    if(!str || current_log_size >= TAL_LOG_MAX_SIZE){
      *err = true;
      return;
    }
    const int add_position = (first_element_pos + current_log_size) % TAL_LOG_MAX_SIZE;
    tal_logs[add_position] = str;
    current_log_size += 1;
  }

  char* tal_log_remove_first(bool* err){
    if(current_log_size <= 0){
      *err = true;
      return (void*)0;
    }
    char* removed_element = tal_logs[first_element_pos];
    first_element_pos = (first_element_pos+1) % TAL_LOG_MAX_SIZE;
    current_log_size -= 1;
    return removed_element;
  }

  char* tal_log_remove_last(bool* err){
    if(current_log_size <= 0){
      *err = true;
      return (void*)0;
    }
    int remove_pos = (first_element_pos + current_log_size-1) % TAL_LOG_MAX_SIZE;
    char* removed_element = tal_logs[remove_pos];
    current_log_size -= 1;
    return removed_element;
  }

#if defined(__cplusplus)
  }
#endif
