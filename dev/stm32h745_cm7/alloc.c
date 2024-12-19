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
 * @file src/top/alloc.c
 * @authors Aaron McBride
 * @brief Implementation of dynamic allocation facilities.
 */

#include "include/tal/alloc.h" // header

#if defined(__cplusplus)
  extern "C" {
#endif

  /************************************************************************************************
   * @section Resources
   ************************************************************************************************/

  // Defines
  #define pool_cnt 8

  typedef uint32_t header_t;

  // Global Variables
  static void* pool_free_ptr[pool_cnt];
  static void* heap_free_ptr;

  /************************************************************************************************
   * @section Block Manipulation Utilities
   ************************************************************************************************/

  // Gets a pointer to the given block's payload.
  static void* get_pload(void* blk) {
    return (void*)((uint8_t*)blk + sizeof(void*));
  }

  // Gets a pointer to the block given a pointer to it's payload
  static void* get_blk(void* pload) {
    return (void*)((uint8_t*)pload - sizeof(void*));
  }

  static void set_alloc_size(void* blk, ssize_t size) {
    static const uint64_t size_mask = ((UINT64_C(1) << sizeof(void*)) - UINT64_C(1)) << size_pos;
    static const int32_t size_pos = 3;

  }

  static ssize_t get_alloc_size(void* blk) {

  }

  static ssize_t get_blk_size(void* blk) {

  }

  static void set_free(void* blk) {

  }

  static bool get_free(void* blk) {

  }

  static void set_link(void* blk, void* next) {

  }

  static void* get_link(void* blk) {

  }

  static void set_prev_free(void* blk, bool free) {

  }

  static bool get_prev_free(void* blk) {

  }

  static void set_next_free(void* blk, bool free) {

  }

  static bool get_next_free(void* blk) {

  }

  static void* get_prev(void* blk) {

  }

  static void* get_next(void* blk) {

  }

  /************************************************************************************************
   * @section Implementation
   ************************************************************************************************/

  void* malloc(ssize_t size) {

  }

  void* realloc(void* ptr, ssize_t new_size) {

  }

  void* alloca(ssize_t size) {

  }

  bool free(void* ptr) {

  }

  ssize_t alloc_size(void* ptr) {

  }

  bool is_alloc(void* ptr) {

  }
  
#if defined(__cplusplus)
  } // extern "C"
#endif