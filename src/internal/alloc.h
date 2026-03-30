
#pragma once
#include "stdbool.h"
#include "stdint.h"
#include "../peripheral/errc.h"

// POINTER TO START OF HEAP
extern void* HEAP_START;

//----------------------------------------------------------------------------------
// BEGIN CONFIGURATION SECTION
// IF YOU CHANGE ANY OF THESE VALUES, IT IS HIGHLY LIKELY OTHERS WILL NEED TO CHANGE IN RESPONSE
//----------------------------------------------------------------------------------

#define NUMBER_OF_POOLS 7
// Must have POOL_BLOCK_SIZES[n + 1] > POOL_BLOCK_SIZES[n] && POOL_BLOCK_SIZES[0] >= sizeof(void*)
// The first rule is because of how the algorithm works
// The second is because all blocks need to be large enough to store a pointer (8 bytes for my system)
static uint32_t POOL_BLOCK_SIZES[NUMBER_OF_POOLS] = {16, 32, 64, 128, 256, 512, 1024}; // note these do not need to be powers of two
static uint32_t POOL_SIZES[NUMBER_OF_POOLS] = {118, 100, 200, 100, 100, 5, 5};

// POOL_BLOCK_SIZES ⋅ POOL_SIZES, it would be nice to generate this line
// (16 * 2) + (32 * 2) + (64 * 3) + (128 * 3) = 672
#define TOTAL_HEAP_SIZE 63968


// STEPS TO FIND IS_FREE_SIZE
// 1: SUM POOL SIZES (number of blocks total between all pools)
// 2: DIVIDE BY 8 (since is_free is an array of uint8_t's and each bit in the uint_8 represents if a
// block is free).
// 3.a: IF THIS IS AN INTEGER, THIS IS THE SIZE
// 3.b: IF THIS IS NOT AN INTEGER, ROUND UP

// Example:
// ceil [ sum(POOL_SIZES) / 8 ] => ceil[ (2 + 2 + 3 + 3) / 8 ] => 2
#define IS_FREE_SIZE 79

//----------------------------------------------------------------------------------
// END CONFIGURATION SECTION
//----------------------------------------------------------------------------------


/**
 * Initialize heap.  Draws on parameters set up above
 * @return ti_errc_t error code
 */
void init_heap(enum ti_errc_t *errc);

/**
 * Allocate a block of size @param size
 * @return ti_errc_t error code
 */
void* alloc(uint32_t size, enum ti_errc_t *errc);

/**
 * Free the block at @param mem
 * @return ti_errc_t error code
 */
void ti_free(void* mem, enum ti_errc_t *errc);

/**
 * Check if the block at @param mem is free
 * @return bool true if the block is free, false if it is allocated or invalid
 */
bool isFree(void* mem);

