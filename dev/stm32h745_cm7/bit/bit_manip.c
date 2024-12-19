/**
 * This file is part of the Titan Avionics Library
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
 * @file src/lib/bit/bit_manip.c
 * @authors Aaron McBride
 * @brief Implementation of bit manipulation utilities.
 */

#include "include/tal/bit.h" // header

#if defined(__cplusplus)
  extern "C" {
#endif

  uint8_t tal_rbit_u8(const uint8_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    uint8_t result = UINT8_C(0);
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint8_t mask = (value >> i) & UINT8_C(1);
      result |= mask << ((value_bits - 1) - i);
    }
    return result;
  }

  uint16_t tal_rbit_u16(const uint16_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    uint16_t result = UINT16_C(0);
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint16_t mask = (value >> i) & UINT16_C(1);
      result |= mask << ((value_bits - 1) - i);
    }
    return result;
  }

  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_rbit_u32(const uint32_t value) {
      uint32_t result = UINT32_C(0);
      asm (
        "rbit %[result_], %[value_]"
        : [result_] "=r" (result)
        : [value_] "r" (value)
      );
      return result;      
    }

  #else

    uint32_t tal_rbit_u32(const uint32_t value) {
      static const int32_t value_bits = tal_bit_size(value);
      uint32_t result = UINT32_C(0);
      for (int32_t i = 0; i < value_bits; ++i) {
        const uint32_t mask = (value >> i) & UINT32_C(1);
        result |= mask << ((value_bits - 1) - i);
      }
      return result;
    }

  #endif

  uint64_t tal_rbit_u64(const uint64_t value) {
    static const int32_t value_bits = tal_bit_size(value);
    uint64_t result = UINT64_C(0);
    for (int32_t i = 0; i < value_bits; ++i) {
      const uint64_t mask = (value >> i) & UINT64_C(1);
      result |= mask << ((value_bits - 1) - i);
    }
    return result;
  }

  // A bit-mask which denotes a single byte (0 offset).
  static const uint64_t byte_mask = (((uint64_t)1 << 8) - 1u);

  #if defined(TAL_ARCH_ARMV7M)

    uint16_t tal_rbyte_u16(const uint16_t value) {
      uint32_t result = UINT32_C(0);
      asm (
        "rev16 %[result_], %[value_]"
        : [result_] "=r" (result)
        : [value_] "r" (value)
      );
      return (uint16_t)result;
    }

  #else

    uint16_t tal_rbyte_u16(const uint16_t value) {
      static const int32_t value_bytes = tal_byte_size(value);
      uint16_t result = UINT16_C(0);
      for (int32_t i = 0; i < value_bytes; ++i) {
        const uint16_t mask = (value >> (i * 8)) & byte_mask;
        result |= mask << (((value_bytes - 1) - i) * 8);
      }
      return result;
    }

  #endif

  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_rbyte_u32(const uint32_t value) {
      uint32_t result = UINT32_C(0);
      asm (
        "rev %[result_], %[value_]"
        : [result_] "=r" (result)
        : [value_] "r" (value)
      );
      return result;
    }

  #else

    uint32_t tal_rbyte_u32(const uint32_t value) {
      static const int32_t value_bytes = tal_byte_size(value);
      uint32_t result = UINT32_C(0);
      for (int32_t i = 0; i < value_bytes; ++i) {
        const uint32_t mask = (value >> (i * 8)) & byte_mask;
        result |= mask << (((value_bytes - 1) - i) * 8);
      }
      return result;
    }

  #endif

  uint64_t tal_rbyte_u64(const uint64_t value) {
    static const int32_t value_bytes = tal_byte_size(value);
    uint64_t result = UINT64_C(0);
    for (int32_t i = 0; i < value_bytes; ++i) {
      const uint64_t mask = (value >> (i * 8)) & byte_mask;
      result |= mask << (((value_bytes - 1) - i) * 8);
    }
    return result;
  }

  uint8_t tal_bit_ceil_u8(const uint8_t value) {
    if (value <= UINT8_C(1)) { return UINT8_C(1); }
    if (tal_single_bit_u8(value)) { return value; }
    return UINT8_C(1) << tal_bit_width_u8(value - UINT8_C(1));
  }

  uint16_t tal_bit_ceil_u16(const uint16_t value) {
    if (value <= UINT16_C(1)) { return UINT16_C(1); }
    if (tal_single_bit_u16(value)) { return value; }
    return UINT16_C(1) << tal_bit_width_u16(value - UINT16_C(1));
  }

  uint32_t tal_bit_ceil_u32(const uint32_t value) {
    if (value <= UINT32_C(1)) { return UINT32_C(1); }
    if (tal_single_bit_u32(value)) { return value; }
    return UINT32_C(1) << tal_bit_width_u32(value - UINT32_C(1));
  }

  uint64_t tal_bit_ceil_u64(const uint64_t value) {
    if (value <= UINT64_C(1)) { return UINT64_C(1); }
    if (tal_single_bit_u64(value)) { return value; }
    return UINT64_C(1) << tal_bit_width_u64(value - UINT64_C(1));
  }

  uint8_t tal_bit_floor_u8(const uint8_t value) {
    if (value <= UINT8_C(0)) { return UINT8_C(0); }
    if (tal_single_bit_u8(value)) { return value; }
    return UINT8_C(1) << (tal_bit_width_u8(value - UINT8_C(1)) - 1);
  }

  uint16_t tal_bit_floor_u16(const uint16_t value) {
    if (value <= UINT16_C(0)) { return UINT16_C(0); }
    if (tal_single_bit_u16(value)) { return value; }
    return UINT16_C(1) << (tal_bit_width_u16(value - UINT16_C(1)) - 1);
  }

  uint32_t tal_bit_floor_u32(const uint32_t value) {
    if (value <= UINT32_C(0)) { return UINT32_C(0); }
    if (tal_single_bit_u32(value)) { return value; }
    return UINT32_C(1) << (tal_bit_width_u32(value - UINT32_C(1)) - 1);
  }

  uint64_t tal_bit_floor_u64(const uint64_t value) {
    if (value <= UINT64_C(0)) { return UINT64_C(0); }
    if (tal_single_bit_u64(value)) { return value; }
    return UINT64_C(1) << (tal_bit_width_u64(value - UINT64_C(1)) - 1);
  }

  uint8_t tal_bit_rot_u8(const uint8_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t lshift = value_bits - diff;
      return (value >> diff) | (value << lshift);
    } else if (diff < 0) {
      const int32_t rshift = value_bits - (-diff);
      return (value << (-diff)) | (value >> rshift);
    } else {
      return value;
    }
  }

  uint16_t tal_bit_rot_u16(const uint16_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t lshift = value_bits - diff;
      return (value >> diff) | (value << lshift);
    } else if (diff < 0) {
      const int32_t rshift = value_bits - (-diff);
      return (value << (-diff)) | (value >> rshift);
    } else {
      return value;
    }
  }

  #if defined(TAL_ARCH_ARMV7M)

    uint32_t tal_bit_rot_u32(const uint32_t value, const int32_t shift) {
      static const int32_t value_bits = tal_bit_size(value);
      const int32_t diff = shift % value_bits;
      if (diff == 0) { return value; }
      const int32_t r_shift = (diff < 0 ? -value_bits : 0) + diff;
      uint32_t result = UINT32_C(0);
      asm (
        "ror %[result_], %[value_], %[r_shift_]"
        : [result_] "=r" (result)
        : [value_] "r" (value), [r_shift_] "r" (r_shift)
      );
      return result;
    }

  #else

    uint32_t tal_bit_rot_u32(const uint32_t value, const int32_t shift) {
      static const int32_t value_bits = tal_bit_size(value);
      const int32_t diff = shift % value_bits;
      if (diff > 0) {
        const int32_t lshift = value_bits - diff;
        return (value >> diff) | (value << lshift);
      } else if (diff < 0) {
        const int32_t rshift = value_bits - (-diff);
        return (value << (-diff)) | (value >> rshift);
      } else {
        return value;
      }
    }

  #endif

  uint64_t tal_bit_rot_u64(const uint64_t value, const int32_t shift) {
    static const int32_t value_bits = tal_bit_size(value);
    const int32_t diff = shift % value_bits;
    if (diff > 0) {
      const int32_t lshift = value_bits - diff;
      return (value >> diff) | (value << lshift);
    } else if (diff < 0) {
      const int32_t rshift = value_bits - (-diff);
      return (value << (-diff)) | (value >> rshift);
    } else {
      return value;
    }
  }

#if defined(__cplusplus)
  } // extern "C"
#endif