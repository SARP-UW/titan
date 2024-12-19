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
 * @file src/stm32h745_cm7/bit.c
 * @authors Aaron McBride
 * @brief Implementation of bit manipulation/inspection utilities.
 */

#include "include/tal/bit.h" // header

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Implementation Resources
   **************************************************************************************************/

  #define bit_size(x) (sizeof(x) * CHAR_BIT)

  /**************************************************************************************************
   * @section Bit Inspection Utilities
   **************************************************************************************************/

  bool single_bit_u8(const uint8_t value) {
    return value && !(value & (value - UINT8_C(1)));
  }

  bool single_bit_u16(const uint16_t value) {
    return value && !(value & (value - UINT16_C(1)));
  }

  bool single_bit_u32(const uint32_t value) {
    return value && !(value & (value - UINT32_C(1)));
  }

  bool single_bit_u64(const uint64_t value) {
    return value && !(value & (value - UINT64_C(1)));
  }

  int32_t bit_width_u8(const uint8_t value) {
    return bit_size(value) - clz_u8(value);
  }

  int32_t bit_width_u16(const uint16_t value) {
    return bit_size(value) - clz_u16(value);
  }

  int32_t bit_width_u32(const uint32_t value) {
    return bit_size(value) - clz_u32(value);
  }

  int32_t bit_width_u64(const uint64_t value) {
    return bit_size(value) - clz_u64(value);
  }

  int32_t clz_u8(const uint8_t value) {
    uint32_t result = 0u;
    asm (
      "clz %[result_], %[value_]" 
      : [result_] "=r" (result) 
      : [value_] "r" (value)
    );
    static const int32_t bit_diff = (int32_t)bit_size(result) - 
        (int32_t)bit_size(value);
    return (int32_t)result - bit_diff;
  }

  int32_t clz_u16(const uint16_t value) {
    uint32_t result = 0u;
    asm (
      "clz %[result_], %[value_]" 
      : [result_] "=r" (result) 
      : [value_] "r" (value)
    );
    static const int32_t bit_diff = (int32_t)bit_size(result) - 
        (int32_t)bit_size(value);
    return (int32_t)result - bit_diff;
  }

  int32_t clz_u32(const uint32_t value) {
    uint32_t result = 0u;
    asm (
      "clz %[result_], %[value_]" 
      : [result_] "=r" (result) 
      : [value_] "r" (value)
    );
    return (int32_t)result;
  }

  int32_t clz_u64(const uint64_t value) {
    static const int32_t h_shift = (int32_t)bit_size(value) / 2;
    const uint32_t h_value = (uint32_t)(value >> h_shift);
    uint32_t h_result = 0u;
    asm (
      "clz %[h_result_], %[h_value_]"
      : [h_result_] "=r" (h_result) 
      : [h_value_] "r" (h_value)
    );
    if (h_result >= bit_size(h_value)) {
      const uint32_t l_value = (uint32_t)value;
      uint32_t l_result = 0u;
      asm (
        "clz %[l_result_], %[l_value_]" 
        : [l_result_] "=r" (l_result) 
        : [l_value_] "r" (l_value)
      );
      return (int32_t)h_result + (int32_t)l_result;
    } else {
      return (int32_t)h_result;
    }
  }

  int32_t clo_u8(const uint8_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint8_t mask = UINT8_C(1) << ((value_bits - 1) - i);
      if ((value & mask) == UINT8_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t clo_u16(const uint16_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint16_t mask = UINT16_C(1) << ((value_bits - 1) - i);
      if ((value & mask) == UINT16_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t clo_u32(const uint32_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint32_t mask = UINT32_C(1) << ((value_bits - 1) - i);
      if ((value & mask) == UINT32_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t clo_u64(const uint64_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint64_t mask = UINT64_C(1) << ((value_bits - 1) - i);
      if ((value & mask) == UINT64_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t ctz_u8(const uint8_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i= 0; i < value_bits; ++i) {
      const uint8_t mask = UINT8_C(1) << i;
      if ((value & mask) != UINT8_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t ctz_u16(const uint16_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i= 0; i < value_bits; ++i) {
      const uint16_t mask = UINT16_C(1) << i;
      if ((value & mask) != UINT16_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t ctz_u32(const uint32_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i= 0; i < value_bits; ++i) {
      const uint32_t mask = UINT32_C(1) << i;
      if ((value & mask) != UINT32_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t ctz_u64(const uint64_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i= 0; i < value_bits; ++i) {
      const uint64_t mask = UINT64_C(1) << i;
      if ((value & mask) != UINT64_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t cto_u8(const uint8_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint8_t mask = UINT8_C(1) << i;
      if ((value & mask) == UINT8_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t cto_u16(const uint16_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint16_t mask = UINT16_C(1) << i;
      if ((value & mask) == UINT16_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t cto_u32(const uint32_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint32_t mask = UINT32_C(1) << i;
      if ((value & mask) == UINT32_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t cto_u64(const uint64_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint64_t mask = UINT64_C(1) << i;
      if ((value & mask) == UINT64_C(0)) { break; }
      ++count;
    }
    return count;
  }

  int32_t popcount_u8(const uint8_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint8_t mask = UINT8_C(1) << i;
      if ((value & mask) != UINT8_C(0)) { ++count; }
    }
    return count;
  }

  int32_t popcount_u16(const uint16_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint16_t mask = UINT16_C(1) << i;
      if ((value & mask) != UINT16_C(0)) { ++count; }
    }
    return count;
  }

  int32_t popcount_u32(const uint32_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint32_t mask = UINT32_C(1) << i;
      if ((value & mask) != UINT32_C(0)) { ++count; }
    }
    return count;
  }

  int32_t popcount_u64(const uint64_t value) {
    static const int32_t value_bits = bit_size(value);
    int32_t count = 0;
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint64_t mask = UINT64_C(1) << i;
      if ((value & mask) != UINT64_C(0)) { ++count; }
    }
    return count;
  }

#if defined(__cplusplus)
  } // extern "C"
#endif