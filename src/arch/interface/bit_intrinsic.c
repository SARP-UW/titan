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
 * @file arch/common/soft_bit_intrinsic.h
 * @authors Aaron McBride
 * @brief Hardware-agnostic fallback implementation for "intrinsic" bit
 *        manipulation/inspection operations.
 */

#pragma once
#include <stdint.h>

#if defined(__cplusplus)
  extern "C" {
#endif

  #define bit_size(x) (int32_t)(sizeof(x) * CHAR_BIT)

  int32_t soft_clz_u8(uint8_t value) {
    int32_t result = 0;
    for (int32_t i = bit_size(value) - 1; i >= 0; --i) {
      result += !(value & (UINT8_C(1) << i));
    }
    return result;
  }

  int32_t soft_clz_u16(uint16_t value) {
    int32_t result = 0;
    for (int32_t i = bit_size(value) - 1; i >= 0; --i) {
      result += !(value & (UINT16_C(1) << i));
    }
    return result;
  }

  int32_t soft_clz_u32(uint32_t value) {
    int32_t result = 0;
    for (int32_t i = bit_size(value) - 1; i >= 0; --i) {
      result += !(value & (UINT32_C(1) << i));
    }
    return result;
  }

  int32_t soft_clz_u64(uint64_t value) {
    int32_t result = 0;
    for (int32_t i = bit_size(value) - 1; i >= 0; --i) {
      result += !(value & (UINT64_C(1) << i));
    }
    return result;
  }

  int32_t soft_ctz_u8(uint8_t value) {
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      result += !(value & (UINT8_C(1) << i));
    }
    return result;
  }

  int32_t soft_ctz_u16(uint16_t value) {
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      result += !(value & (UINT16_C(1) << i));
    }
    return result;
  }

  int32_t soft_ctz_u32(uint32_t value) {
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      result += !(value & (UINT32_C(1) << i));
    }
    return result;
  }

  int32_t soft_ctz_u64(uint64_t value) {
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      result += !(value & (UINT64_C(1) << i));
    }
    return result;
  }

  int32_t soft_popcnt_u8(uint8_t value) {
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      result += !!(value & (UINT8_C(1) << i));
    }
    return result;
  }

  int32_t soft_popcnt_u16(uint16_t value) {
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      result += !!(value & (UINT16_C(1) << i));
    }
    return result;
  }

  int32_t soft_popcnt_u32(uint32_t value) {
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      result += !!(value & (UINT32_C(1) << i));
    }
    return result;
  }

  int32_t soft_popcnt_u64(uint64_t value) {
    int32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      result += !!(value & (UINT64_C(1) << i));
    }
    return result;
  }

  uint8_t soft_bit_rev_u8(uint8_t value) {
    uint8_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      if (value & (UINT8_C(1) << i)) {
        const int32_t off = (bit_size(value) - 1) - i;
        result |= (UINT8_C(1) << off);
      }
    }
    return result;
  }

  uint16_t soft_bit_rev_u16(uint16_t value) {
    uint16_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      if (value & (UINT16_C(1) << i)) {
        const int32_t off = (bit_size(value) - 1) - i;
        result |= (UINT16_C(1) << off);
      }
    }
    return result;
  }

  uint32_t soft_bit_rev_u32(uint32_t value) {
    uint32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      if (value & (UINT32_C(1) << i)) {
        const int32_t off = (bit_size(value) - 1) - i;
        result |= (UINT32_C(1) << off);
      }
    }
    return result;
  }

  uint64_t soft_bit_rev_u64(uint64_t value) {
    uint64_t result = 0;
    for (int32_t i = 0; i < bit_size(value); ++i) {
      if (value & (UINT64_C(1) << i)) {
        const int32_t off = (bit_size(value) - 1) - i;
        result |= (UINT64_C(1) << off);
      }
    }
    return result;
  }

  uint8_t soft_byte_rev_u16(uint16_t value) {
    uint8_t result = 0;
    for (int32_t i = 0; i < bit_size(value); i += 8) {
      if (value & (UINT16_C(0xFF) << i)) {
        const int32_t off = (bit_size(value) - 8) - i;
        result |= (UINT16_C(0xFF) << off);
      }
    }
    return result;
  }

  uint32_t soft_byte_rev_u32(uint32_t value) {
    uint32_t result = 0;
    for (int32_t i = 0; i < bit_size(value); i += 8) {
      if (value & (UINT32_C(0xFF) << i)) {
        const int32_t off = (bit_size(value) - 8) - i;
        result |= (UINT32_C(0xFF) << off);
      }
    }
    return result;
  }

  uint64_t soft_byte_rev_u64(uint64_t value) {
    uint64_t result = 0;
    for (int32_t i = 0; i < bit_size(value); i += 8) {
      if (value & (UINT64_C(0xFF) << i)) {
        const int32_t off = (bit_size(value) - 8) - i;
        result |= (UINT64_C(0xFF) << off);
      }
    }
    return result;
  }

  uint8_t soft_bit_insert_u8(uint8_t value, uint8_t dst, int32_t pos, int32_t len) {
    uint8_t mask = ((UINT8_C(1) << len) - 1) << pos;
    return (dst & ~mask) | ((value << pos) & mask);
  }

  uint16_t soft_bit_insert_u16(uint16_t value, uint16_t dst, int32_t pos, int32_t len) {
    uint16_t mask = ((UINT16_C(1) << len) - 1) << pos;
    return (dst & ~mask) | ((value << pos) & mask);
  }

  uint32_t soft_bit_insert_u32(uint32_t value, uint32_t dst, int32_t pos, int32_t len) {
    uint32_t mask = ((UINT32_C(1) << len) - 1) << pos;
    return (dst & ~mask) | ((value << pos) & mask);
  }

  uint64_t soft_bit_insert_u64(uint64_t value, uint64_t dst, int32_t pos, int32_t len) {
    uint64_t mask = ((UINT64_C(1) << len) - 1) << pos;
    return (dst & ~mask) | ((value << pos) & mask);
  }

  uint8_t soft_bit_extract_u8(uint8_t value, int32_t pos, int32_t len) {
    uint8_t mask = ((UINT8_C(1) << len) - 1) << pos;
    return (value & mask) >> pos;
  }

  uint16_t soft_bit_extract_u16(uint16_t value, int32_t pos, int32_t len) {
    uint16_t mask = ((UINT16_C(1) << len) - 1) << pos;
    return (value & mask) >> pos;
  }

  uint32_t soft_bit_extract_u32(uint32_t value, int32_t pos, int32_t len) {
    uint32_t mask = ((UINT32_C(1) << len) - 1) << pos;
    return (value & mask) >> pos;
  }

  uint64_t soft_bit_extract_u64(uint64_t value, int32_t pos, int32_t len) {
    uint64_t mask = ((UINT64_C(1) << len) - 1) << pos;
    return (value & mask) >> pos;
  }

#if defined(__cplusplus)
  } // extern "C"
#endif