
// All resources in this file are temporary, and should be relocated
// or removed in the future.

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <float.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  // temp assert macro -> maybe causes usgfault on trigger
  #if defined(TAL_DEBUG)
    #define tal_assert(cond) (((bool)(cond) ? *(int*)0 = 0 : 0), (bool)(cond))
  #else
    #define tal_assert(cond) (bool)(cond)
  #endif

#if defined(__cplusplus)
  }
#endif