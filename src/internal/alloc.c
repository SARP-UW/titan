/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
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
 * @file internal/alloc.c
 * @authors Joshua Beard
 * @brief Internal memory allocator implementation.
 */
#include "alloc.h"
// #include "peripheral/gpio.h" // FOR TESTING < REMOVE

void* HEAP_START = (void*)0x0;

struct block_t{
    struct block_t* next_block;
};


static uint8_t is_free[IS_FREE_SIZE];
static struct block_t* pool_heads[NUMBER_OF_POOLS];


/**
 * Internal function.  Builds the linked-list associated with each pool
 * @param curr initial head of the pool
 * @param pool_size size of blocks in this pool
 * @param pool_count number of blocks in this pool
 * @param i zero :)
 * @return
 */
struct block_t* build_pool(void* curr, uint32_t pool_size, uint32_t pool_count, uint32_t i)
{
    struct block_t* s = (struct block_t*)curr;

    if(i >= pool_count - 1){
        struct block_t n = {(void*)0}; // null terminator
        *s = n;
        return s;
    }

    struct block_t t = (struct block_t)
    {
        build_pool((uint8_t*)curr + pool_size, pool_size, pool_count, i + 1)
    };
    *s = t;

    return s;
}


/**
 * Internal function.
 *
 * Gets the number of blocks before the given block (its index in is_free)
 */
void get_index(void* block, uint32_t* ret_index, enum ti_errc_t *errc){
    if (errc) *errc = TI_ERRC_NONE;
    /**
     * This function really annoyed me.  Basically we need the amount of total blocks before this pointer
     * (which is its index ofc), but I can not think of a way to do this in constant time.  Maybe some sort
     * of hash function would do.  For now I am writing this in linear time to just work for testing,
     * and maybe sometime in the future we can optimize it (I can think of a way to get it to logorithmic time).
     * Reguardless, I feel like it should be possible in constant time so if you're reading this and are
     * bored then I would be forever grateful if you could make this fast.
     */

     // updated condition to >= because:
     // HEAP_START + TOTAL_HEAP_SIZE will be 1 out of range, so if block equals that, that's 1 OOB
    if((uint8_t*)block < (uint8_t*)HEAP_START || (uint8_t*)block >= ((uint8_t*)HEAP_START) + TOTAL_HEAP_SIZE){ // out of range //
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Block pointer is outside the heap address range"); return; //
    }

    uint8_t* blk = (uint8_t*) block;

    uint32_t i = 0;
    uint32_t pool_left = POOL_SIZES[i];

    uint32_t index = -1;

    while(blk >= (uint8_t*)HEAP_START){
        if(pool_left <= 0){
            pool_left = POOL_SIZES[++i];
        }

        blk -= POOL_BLOCK_SIZES[i];
        pool_left -= 1;
        index++;
    }

    *ret_index = index;
}

/**
 * Internal function
 *
 * Gets the index of the pool that a given block of memory is in.
 * For example, if you passed in HEAP_START as block, this function would return
 * 0; since the block at HEAP_START is always in the first pool
 *
 */
void get_pool(void* block, uint32_t* res, enum ti_errc_t *errc){
    if (errc) *errc = TI_ERRC_NONE;
    *res = -1U;
    if((uint8_t*)block < (uint8_t*)HEAP_START || (uint8_t*)block > ((uint8_t*)HEAP_START) + TOTAL_HEAP_SIZE){ // out of range //
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "OOB pointer"); return; //
    }

    uint8_t* blk = (uint8_t*) block;

    uint32_t i = 0;
    uint32_t pool_left = POOL_SIZES[i];

    while(blk >= (uint8_t*)HEAP_START){
        if(pool_left <= 0){
            pool_left = POOL_SIZES[++i];
        }
        blk -= POOL_BLOCK_SIZES[i];
        pool_left -= 1;
    }

    *res = i;
}



/**
 * Usage: Check for success or failure when used to make sure it was
 * configured correctly
 *
 * @return 1 for success, -1 for failure
 */

void init_heap(enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    uint32_t s = 0;
    for(int i = 0; i < NUMBER_OF_POOLS; i++){
        s += POOL_BLOCK_SIZES[i] * POOL_SIZES[i];
    }

    if (s != TOTAL_HEAP_SIZE) {
        TI_SET_ERRC(errc, TI_ERRC_INTERNAL, "Heap configuration error"); return; //
    }

    void* start = HEAP_START;
    for(int i = 0; i < NUMBER_OF_POOLS; i++){
        // build linked list for each pool
        pool_heads[i] = build_pool(
            start,
            POOL_BLOCK_SIZES[i],
            POOL_SIZES[i],
            0
            );

        start += POOL_BLOCK_SIZES[i] * POOL_SIZES[i]; // block size (bytes) * amount of blocks
    }

    for(int i = 0; i < IS_FREE_SIZE; i++){
        is_free[i] = 255;
    }

}

/**
 * @param size
 * @param errc Output error code.
 * @return Pointer to allocated block, or NULL on failure.
 */
void* alloc(uint32_t size, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (size == 0 || size > POOL_BLOCK_SIZES[NUMBER_OF_POOLS - 1]) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid alloc size"); return NULL; //
    }
    // find ideal i
    uint32_t i = 0;
    // i < NUMBER_OF_POOLS comes first so that it can terminate condition early
    for(; i < NUMBER_OF_POOLS && size > POOL_BLOCK_SIZES[i]; i++);
    if (i >= NUMBER_OF_POOLS) { TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "No pool fits size"); return NULL; } //
    // if the pool for ideal i is already full (null head), keep going to next block until we find a free one
    struct block_t* block = pool_heads[i];
    while(block == ((void*)0) && i < NUMBER_OF_POOLS-1){ // subtracting 1 here because of ++i
        block = pool_heads[++i];
    }

    if(block == ((void*)0)){
        TI_SET_ERRC(errc, TI_ERRC_OVERFLOW, "Heap full"); return NULL; //
    }

    // update free blocks
    uint32_t index; //
    get_index(block, &index, errc); //
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return NULL; } //
    
    uint32_t big_index = index / 8;
    uint32_t small_index = index % 8;

    // update linked list
    pool_heads[i] = block->next_block;

    is_free[big_index] &= ~((uint8_t)1 << small_index);

    for(uint32_t j = 0; j < POOL_BLOCK_SIZES[i]; j++){ // zero this block before returning
        *(((uint8_t*)block) + j) = 0; // changed this to j? not sure why this was i before.
    }

    return block;
}

/**
 * @param mem
 * @param errc Output error code.
 */
void ti_free(void* mem, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    uint32_t i;
    get_pool(mem, &i, errc); //
    if ((errc && *errc != TI_ERRC_NONE) || i == -1U){ //
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Memory block not in heap"); return; //
    }

    struct block_t new_head = (struct block_t){
        pool_heads[i]
    };

    *((struct block_t*)mem) = new_head;

    pool_heads[i] = (struct block_t*)mem;
    uint32_t index;
    get_index(mem, &index, errc); //
    if (errc && *errc != TI_ERRC_NONE) { TI_SET_ERRC(errc, *errc, "Propagated"); return; } //

    uint32_t big_index = index / 8;
    uint32_t small_index = index % 8;

    is_free[big_index] |= (uint8_t)1 << small_index;
}

/**
 *
 * @param mem
 * @return
 */
bool isFree(void* mem) {
    uint32_t index; //
    enum ti_errc_t local_errc = TI_ERRC_NONE; //
    get_index(mem, &index, &local_errc); //

    if(local_errc != TI_ERRC_NONE || index == -1U){ //
        return false;
    }
    uint32_t big_index = index / 8;
    uint32_t small_index = index % 8;

    return (is_free[big_index] & (1 << small_index)) != 0;
}