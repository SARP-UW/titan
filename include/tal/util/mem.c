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

void* ti_memcpy(void* dst, void* src, size_t size)
{
    char *d = dst;
    const char *s = src;

    for (int i=0; i<size; i++) {
        *(d + i) = *(s + i);
    }
    return dst;
}

void* ti_memset(void* mem, char value, size_t size)
{

    char *d = mem;
    for(int i = 0; i < size; i++){
        *(d + i) = value;
    }

    return mem;
}

void* ti_memexch(void* dst, void* src, char value, size_t size)
{
    ti_memcpy(dst, src, size);
    ti_memset(src, value, size);
    return dst;
}

void ti_memswap(void* mem_a, void* mem_b, size_t size)
{
    char *pA = mem_a;
    char *pB = mem_b;

    for(int i = 0; i < size; i++){
        char a = *(pA + i);
        *(pA + i) = *(pB + i);
        *(pB + i) = a;
    }
}


int ti_memcmp(void* mem_a, void* mem_b, size_t size)
{
    char *pA = mem_a;
    char *pB = mem_b;


    for(int i = 0; i < size; i++){
        char a = *(pA + i);
        char b = *(pB + i);

        if(a == b){
            continue;
        }
        return a < b ? -1 : 1;
    }
    return 0;
}

bool ti_memeq(void* mem, char value, size_t size)
{
    char *pA = mem;
    for(int i = 0; i < size; i++){
        if(*pA != value){
            return 0;
        }
    }
    return 1;
}

void* ti_memchr(void* mem_a, char value, size_t size)
{
    char *pA = mem_a;
    for(int i = 0; i < size; i++){
        if(*pA == value){
            return pA;
        }
        ++pA;
    }
    return (void *) 0;
}


void* ti_memrchr(void* mem_a, char value, size_t size)
{
    char *pA = mem_a;
    pA += (size - 1); // TODO TEST IF OFF BY ONE

    for(int i = 0; i < size; i++){
        if(*pA == value){
            return pA;
        }
        --pA;
    }
    return (void *) 0;
}


void* ti_memchrn(void* mem, char value, size_t size, size_t n)
{
    char *pA = mem;

    int occurence = 0;
    for (int i = 0; i < size; i++) {
        if (*pA == value) {
            occurence++;
            if(occurence == n){
                return pA;
            }
        }
        pA++;
    }

    return (void *) 0;
}

static void ti_mem_quicksort(void* mem, int (*cmp_fn)(const char*, const char*), int low, int high)
{
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
                    ti_memswap(greater, &pA[i], 1);
                    greater++;
                    greater_index++;
                }
            }


            ti_memswap(pivot, greater, 1);

            ti_mem_quicksort(mem, cmp_fn, low, greater_index - 1);
            ti_mem_quicksort(mem, cmp_fn, greater_index - 1, high);
        }else{
            ti_mem_quicksort(mem, cmp_fn, low, high - 1);
        }
    }
}

void* ti_memsort(void* mem, size_t size, int (*cmp_fn)(const char*, const char*))
{
    ti_mem_quicksort(mem, cmp_fn, 0, (int)size - 1);
    return mem;
}



