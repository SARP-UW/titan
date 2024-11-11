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
 * @file common/util/mem.c
 * @authors Joshua Beard
 * @brief Memory manipulation and querying utilities.
 */

#pragma once
#include "common/util/mem.h"

  tal_fn_attr_inline inline void* tal_memsort(void* mem, int32_t size, int (*cmp_fn)(const char*, const char*));

  // we should change this to qsort

    static void tal_mem_quicksort(void* mem, int (*cmp_fn)(const char*, const char*), int low, int high) {
      char* pA = (char*) mem;

      if (low < high) {
          char* pivot = &pA[high];
          char* greater = (char*) 0;
          int greater_index = 0;

          for(int i = 0; i <= high - 1; i++){
              if(cmp_fn(&pA[i], pivot) < 0){
                  greater = &pA[i];
                  greater_index = i;
                  break;
              }
          }

          if(greater != (char*) 0){
              for (int i = greater_index; i <= high; i++) {
                  if(cmp_fn(&pA[i], pivot) > 0){
                      tal_memswap(greater, &pA[i], 1);
                      greater++;
                      greater_index++;
                  }
              }


              tal_memswap(pivot, greater, 1);

              tal_mem_quicksort(mem, cmp_fn, low, greater_index - 1);
              tal_mem_quicksort(mem, cmp_fn, greater_index - 1, high);
          }else{
              tal_mem_quicksort(mem, cmp_fn, low, high - 1);
          }
      }
  }

  void* tal_memsort(void* mem, int32_t size, int (*cmp_fn)(const char*, const char*)) {
      tal_mem_quicksort(mem, cmp_fn, 0, (int)size - 1);
      return mem;
  }



