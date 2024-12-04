

// All resources in this file are temporary, and should be relocated
// or removed in the future.

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <float.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  // Dummy error flag
  static bool dummy_err_value;
  bool* const dummy_err = &dummy_err_value;

  // temp assert macro -> maybe causes usgfault on trigger
  #if defined(TAL_DEBUG)
    #define tal_assert(cond) (((bool)(cond) ? *(int*)0 = 0 : 0), (bool)(cond))
  #else
    #define tal_assert(cond) (bool)(cond)
  #endif

  // Macro stuff
  #define STRING(x) #x
  #define XSTRING(x) STRING(x)
  
  #define CONCAT(a, b) a##b
  #define XCONCAT(a, b) CONCAT(a, b)


  // pair types
  typedef struct {
    int8_t a;
    int8_t b;
  }tal_pair_i8_t;

  typedef struct {
    int16_t a;
    int16_t b;
  }tal_pair_i16_t;

  typedef struct {
    int32_t a;
    int32_t b;
  }tal_pair_i32_t;

  typedef struct {
    int64_t a;
    int64_t b;
  }tal_pair_i64_t;

  typedef struct {
    uint8_t a;
    uint8_t b;
  }tal_pair_u8_t;

  typedef struct {
    uint16_t a;
    uint16_t b;
  }tal_pair_u16_t;

  typedef struct {
    uint32_t a;
    uint32_t b;
  }tal_pair_u32_t;

  typedef struct {
    uint64_t a;
    uint64_t b;
  }tal_pair_u64_t;

  typedef struct {
    float a;
    float b;
  }tal_pair_f_t;

  typedef struct {
    double a;
    double b;
  }tal_pair_d_t;

  // Option types
  typedef struct {
    int8_t value;
    bool valid; 
  }tal_opt_i8_t;

  typedef struct {
    int16_t value;
    bool valid;
  }tal_opt_i16_t;

  typedef struct {
    int32_t value;
    bool valid;
  }tal_opt_i32_t;

  typedef struct {
    int64_t value;
    bool valid;
  }tal_opt_i64_t;

  typedef struct {
    uint8_t value;
    bool valid;
  }tal_opt_u8_t;

  typedef struct {
    uint16_t value;
    bool valid;
  }tal_opt_u16_t;

  typedef struct {
    uint32_t value;
    bool valid;
  }tal_opt_u32_t;

  typedef struct {
    uint64_t value;
    bool valid;
  }tal_opt_u64_t;

  typedef struct {
    float value;
    bool valid;
  }tal_opt_f_t;

  typedef struct {
    double value;
    bool valid;
  }tal_opt_t;

#if defined(__cplusplus)
  }
#endif

