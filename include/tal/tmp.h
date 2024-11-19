
// All resources in this file are temporary, and should be relocated
// or removed in the future.

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <float.h>
#include <math.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  // Dummy error flag.
  static bool dummy_err_value;
  bool* dummy_err = &dummy_err_value;

  // temp assert macro -> maybe causes usgfault on trigger
  #if defined(TAL_DEBUG)
    #define tal_assert(cond) (((bool)(cond) ? *(int*)0 = 0 : 0), (bool)(cond))
  #else
    #define tal_assert(cond) (bool)(cond)
  #endif

  typedef struct {
    int8_t a;
    int8_t b;
  }tal_pair_i8t;

  typedef struct {
    int16_t a;
    int16_t b;
  }tal_pair_i16t;

  typedef struct {
    int32_t a;
    int32_t b;
  }tal_pair_i32t;

  typedef struct {
    int64_t a;
    int64_t b;
  }tal_pair_i64t;

  typedef struct {
    uint8_t a;
    uint8_t b;
  }tal_pair_u8t;

  typedef struct {
    uint16_t a;
    uint16_t b;
  }tal_pair_u16t;

  typedef struct {
    uint32_t a;
    uint32_t b;
  }tal_pair_u32t;

  typedef struct {
    uint64_t a;
    uint64_t b;
  }tal_pair_u64t;

#if defined(__cplusplus)
  }
#endif