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
 * @file common/util/bit.c 
 * @authors Aaron McBride
 * @brief Bit manipulation utilities
 */

#pragma once
#include <common/util/bit.h>

#if defined(__cplusplus)
  extern "C" {
#endif

// Denotes the number of bits in a numeric type.
#define UINT8_BIT_CNT ((int)sizeof(uint8_t) * CHAR_BIT)
#define UINT16_BIT_CNT ((int)sizeof(uint16_t) * CHAR_BIT)
#define UINT32_BIT_CNT ((int)sizeof(uint32_t) * CHAR_BIT)
#define UINT64_BIT_CNT ((int)sizeof(uint64_t) * CHAR_BIT)

// Denotes the number of binary digits in a numeric type.
#define UINT8_DIGITS 3
#define UINT16_DIGITS 5
#define UINT32_DIGITS 10
#define UINT64_DIGITS 20

// Denotes the number of bytes in a numeric type.
#define UINT16_BYTE_CNT ((int)sizeof(uint16_t) / CHAR_BIT)
#define UINT32_BYTE_CNT ((int)sizeof(uint32_t) / CHAR_BIT)
#define UINT64_BYTE_CNT ((int)sizeof(uint64_t) / CHAR_BIT)

// A bit-mask which represents a single byte (unsigned).
#define BYTE_MASK ((1u << CHAR_BIT) - 1u)

// The number of digits in the smallest promoted type (int).
#define MIN_PROM_DIGITS UINT32_DIGITS


uint8_t ti_rbit8(const uint8_t value) {
  uint8_t result = 0;
  for (int i = 0; i < UINT8_BIT_CNT; ++i) {
    const uint8_t mask = ((value >> i) & 1u);
    result |= (mask << (UINT8_BIT_CNT - 1 - i));
  }
  return result;
}

uint16_t ti_rbit16(const uint16_t value) {
  uint16_t result = 0;
  for (int i = 0; i < UINT16_BIT_CNT; ++i) {
    const uint16_t mask = ((value >> i) & 1u);
    result |= (mask << (UINT16_BIT_CNT - 1 - i));
  }
  return result;
}

uint32_t ti_rbit32(const uint32_t value) {
  uint32_t result = 0;
  for (int i = 0; i < UINT32_BIT_CNT; ++i) {
    const uint32_t mask = ((value >> i) & 1u);
    result |= (mask << (UINT32_BIT_CNT - 1 - i));
  }
  return result;
}

uint64_t ti_rbit64(const uint64_t value) {
  uint64_t result = 0;
  for (int i = 0; i < UINT64_BIT_CNT; ++i) {
    const uint64_t mask = ((value >> i) & 1u);
    result |= (mask << (UINT64_BIT_CNT - 1 - i));
  }
  return result;
}

#if defined(TI_ARCH_ARMV7)

  uint16_t ti_rbyte16(const uint16_t value) {
    uint16_t result;
    asm ("rev16 %0, %1" : "=rm" (result) : "rm" (value));
    return result;
  }

  uint32_t ti_rbyte32(const uint32_t value) {
    uint32_t result;
    asm ("rev %0, %1" : "=rm" (result) : "rm" (value));
    return result;
  }

#else

  uint16_t ti_rbyte16(const uint16_t value) {
    uint16_t result = 0;
    for (int i = 0; i < UINT16_BYTE_CNT; ++i) {
      const uint16_t mask = (value >> (i * CHAR_BIT)) & (uint16_t)BYTE_MASK;
      result |= (mask << ((UINT16_BYTE_CNT - 1 - i) * CHAR_BIT));
    }
    return result;
  }

  uint32_t ti_rbyte32(const uint32_t value) {
    uint32_t result = 0;
    for (int i = 0; i < UINT32_BYTE_CNT; ++i) {
      const uint32_t mask = (value >> (i * CHAR_BIT)) & (uint32_t)BYTE_MASK;
      result |= (mask << ((UINT32_BYTE_CNT - 1 - i) * CHAR_BIT));
    }
    return result;
  }

#endif

uint64_t ti_rbyte64(const uint64_t value) {
  uint64_t result = 0;
  for (int i = 0; i < UINT64_BYTE_CNT; ++i) {
    const uint64_t mask = (value >> (i * CHAR_BIT)) & (uint64_t)BYTE_MASK;
    result |= (mask << ((UINT64_BYTE_CNT - 1 - i) * CHAR_BIT));
  }
  return result;
}

bool ti_single_bit8(const uint8_t value) {
  return value && !(value & (value - 1u));
}

bool ti_single_bit16(const uint16_t value) {
  return value && !(value & (value - 1u));
}

bool ti_single_bit32(const uint32_t value) {
  return value && !(value & (value - 1u));
}

bool ti_single_bit64(const uint64_t value) {
  return value && !(value & (value - 1u));
}

uint8_t ti_bit_ceil8(const uint8_t value) {
  if (value <= 1u) { return 1; }
  const int ovf_offset = MIN_PROM_DIGITS - UINT8_DIGITS;
  return (1u << (ti_bit_width8(value - 1u) + ovf_offset) >> ovf_offset);
}

uint16_t ti_bit_ceil16(const uint16_t value) {
  if (value <= 1u) { return 1; }
  const int ovf_offset = MIN_PROM_DIGITS - UINT16_DIGITS;
  return (1u << (ti_bit_width16(value - 1u) + ovf_offset) >> ovf_offset);
}

uint32_t ti_bit_ceil32(const uint32_t value) {
  if (value <= 1u) { return 1; }
  return 1u << ti_bit_width32(value - 1u);
}

uint64_t ti_bit_ceil64(const uint64_t value) {
  if (value <= 1u) { return 1; }
  return 1u << ti_bit_width64(value - 1u);
}

uint8_t ti_bit_floor8(const uint8_t value) {
  if (value <= 0u) { return 0; }
  return 1u << (ti_bit_width8(value - 1u) - 1u);
}

uint16_t ti_bit_floor16(const uint16_t value) {
  if (value <= 0u) { return 0; }
  return 1u << (ti_bit_width16(value - 1u) - 1u);
}

uint32_t ti_bit_floor32(const uint32_t value) {
  if (value <= 0u) { return 0; }
  return 1u << (ti_bit_width32(value - 1u) - 1u);
}

uint64_t ti_bit_floor64(const uint64_t value) {
  if (value <= 0u) { return 0; }
  return 1u << (ti_bit_width64(value - 1u) - 1u);
}

int32_t ti_bit_width8(const uint8_t value) {
  return UINT8_DIGITS - ti_clz8(value);
}

int32_t ti_bit_width16(const uint16_t value) {
  return UINT16_DIGITS - ti_clz16(value);
}

int32_t ti_bit_width32(const uint32_t value) {
  return UINT32_DIGITS - ti_clz32(value);
}

int32_t ti_bit_width64(const uint64_t value) {
  return UINT64_DIGITS - ti_clz64(value);
}

uint8_t ti_rotl8(const uint8_t value, const int32_t shift) {
  const int32_t diff = shift % UINT8_DIGITS;
  if (shift > 0) {
    return (value << diff) | (value >> (UINT8_DIGITS - diff));
  } else if (shift < 0) {
    return ti_rotr(value, -shift);
  } else {
    return value;
  }
}

uint16_t ti_rotl16(const uint16_t value, const int32_t shift) {
  const int32_t diff = shift % UINT16_DIGITS;
  if (shift > 0) {
    return (value << diff) | (value >> (UINT16_DIGITS - diff));
  } else if (shift < 0) {
    return ti_rotr(value, -shift);
  } else {
    return value;
  }
}

uint32_t ti_rotl32(const uint32_t value, const int32_t shift) {
  const int32_t diff = shift % UINT32_DIGITS;
  if (shift > 0) {
    return (value << diff) | (value >> (UINT32_DIGITS - diff));
  } else if (shift < 0) {
    return ti_rotr(value, -shift);
  } else {
    return value;
  }
}

uint64_t ti_rotl64(const uint64_t value, const int32_t shift) {
  const int32_t diff = shift % UINT64_DIGITS;
  if (shift > 0) {
    return (value << diff) | (value >> (UINT64_DIGITS - diff));
  } else if (shift < 0) {
    return ti_rotr(value, -shift);
  } else {
    return value;
  }
}

uint8_t ti_rotr8(const uint8_t value, const int32_t shift) {
  const int32_t diff = shift % UINT8_DIGITS;
  if (diff > 0) {
    return (value >> diff) | (value << (UINT8_DIGITS - diff));
  } else if (diff < 0) {
    return ti_rotl(value, -shift);
  } else {
    return value;
  }
}

uint16_t ti_rotr16(const uint16_t value, const int32_t shift) {
  const int32_t diff = shift % UINT16_DIGITS;
  if (diff > 0) {
    return (value >> diff) | (value << (UINT16_DIGITS - diff));
  } else if (diff < 0) {
    return ti_rotl(value, -shift);
  } else {
    return value;
  }
}

uint32_t ti_rotr32(const uint32_t value, const int32_t shift) {
  const int32_t diff = shift % UINT32_DIGITS;
  if (diff > 0) {
    return (value >> diff) | (value << (UINT32_DIGITS - diff));
  } else if (diff < 0) {
    return ti_rotl(value, -shift);
  } else {
    return value;
  }
}

uint64_t ti_rotr64(const uint64_t value, const int32_t shift) {
  const int32_t diff = shift % UINT64_DIGITS;
  if (diff > 0) {
    return (value >> diff) | (value << (UINT64_DIGITS - diff));
  } else if (diff < 0) {
    return ti_rotl(value, -shift);
  } else {
    return value;
  }
}

#if defined(TI_ARCH_ARMV7)

  int32_t ti_clz8(const uint8_t value) {
    const int32_t bit_diff = UINT32_BIT_CNT - UINT8_BIT_CNT;
    return ti_clz32((uint32_t)value) - bit_diff;
  }

  int32_t ti_clz16(const uint16_t value) {
    const int32_t bit_diff = UINT32_BIT_CNT - UINT16_BIT_CNT;
    return ti_clz32((uint32_t)value) - bit_diff;
  }

  int32_t ti_clz32(const uint32_t value) {
    int32_t result = 0;
    asm ("clz %0, %1" : "=rm" (result) : "rm" (value));
    return result;
  }

  int32_t ti_clz64(const uint64_t value) {
    const uint32_t high_w = (uint32_t)(value >> (UINT64_BIT_CNT / 2));
    const int32_t high_clz = ti_clz32(high_w);
    if (high_clz == UINT32_BIT_CNT) {
      return UINT32_BIT_CNT + ti_clz32((uint32_t)value);
    } else {
      return high_clz;
    }
  }

#else

  int32_t ti_clz8(const uint8_t value) {
    int32_t count = 0;
    for (int i = 0; i < UINT8_BIT_CNT; ++i) {
      const uint8_t mask = (1u << (UINT8_BIT_CNT - 1 - i));
      if ((value & mask) != 0) { break; }
      ++count;
    }
    return count;
  }

  int32_t ti_clz16(const uint16_t value) {
    int32_t count = 0;
    for (int i = 0; i < UINT16_BIT_CNT; ++i) {
      const uint16_t mask = (1u << (UINT16_BIT_CNT - 1 - i));
      if ((value & mask) != 0) { break; }
      ++count;
    }
    return count;
  }

  int32_t ti_clz32(const uint32_t value) {
    int32_t count = 0;
    for (int i = 0; i < UINT32_BIT_CNT; ++i) {
      const uint32_t mask = (1u << (UINT32_BIT_CNT - 1 - i));
      if ((value & mask) != 0) { break; }
      ++count;
    }
    return count;
  }

  int32_t ti_clz64(const uint64_t value) {
    int32_t count = 0;
    for (int i = 0; i < UINT64_BIT_CNT; ++i) {
      const uint64_t mask = (1u << (UINT64_BIT_CNT - 1 - i));
      if ((value & mask) != 0) { break; }
      ++count;
    }
    return count;
  }

#endif

int32_t ti_clo8(const uint8_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT8_BIT_CNT; ++i) {
    const uint8_t mask = (1u << (UINT8_BIT_CNT - 1 - i));
    if ((value & mask) == 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_clo16(const uint16_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT16_BIT_CNT; ++i) {
    const uint16_t mask = (1u << (UINT16_BIT_CNT - 1 - i));
    if ((value & mask) == 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_clo32(const uint32_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT32_BIT_CNT; ++i) {
    const uint32_t mask = (1u << (UINT32_BIT_CNT - 1 - i));
    if ((value & mask) == 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_clo64(const uint64_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT64_BIT_CNT; ++i) {
    const uint64_t mask = (1u << (UINT64_BIT_CNT - 1 - i));
    if ((value & mask) == 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_ctz8(const uint8_t value) {
  int32_t count = 0;
  for (int i= 0; i < UINT8_BIT_CNT; ++i) {
    const uint8_t mask = (1u << i);
    if ((value & mask) != 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_ctz16(const uint16_t value) {
  int32_t count = 0;
  for (int i= 0; i < UINT16_BIT_CNT; ++i) {
    const uint16_t mask = (1u << i);
    if ((value & mask) != 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_ctz32(const uint32_t value) {
  int32_t count = 0;
  for (int i= 0; i < UINT32_BIT_CNT; ++i) {
    const uint32_t mask = (1u << i);
    if ((value & mask) != 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_ctz64(const uint64_t value) {
  int32_t count = 0;
  for (int i= 0; i < UINT64_BIT_CNT; ++i) {
    const uint64_t mask = (1u << i);
    if ((value & mask) != 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_cto8(const uint8_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT8_BIT_CNT; ++i) {
    const uint8_t mask = (1u << i);
    if ((value & mask) == 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_cto16(const uint16_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT16_BIT_CNT; ++i) {
    const uint16_t mask = (1u << i);
    if ((value & mask) == 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_cto32(const uint32_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT32_BIT_CNT; ++i) {
    const uint32_t mask = (1u << i);
    if ((value & mask) == 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_cto64(const uint64_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT64_BIT_CNT; ++i) {
    const uint64_t mask = (1u << i);
    if ((value & mask) == 0) { break; }
    ++count;
  }
  return count;
}

int32_t ti_popcount8(const uint8_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT8_BIT_CNT; ++i) {
    const uint8_t mask = (1u << i);
    if ((value & mask) != 0) { ++count; }
  }
  return count;
}

int32_t ti_popcount16(const uint16_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT16_BIT_CNT; ++i) {
    const uint16_t mask = (1u << i);
    if ((value & mask) != 0) { ++count; }
  }
  return count;
}

int32_t ti_popcount32(const uint32_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT32_BIT_CNT; ++i) {
    const uint32_t mask = (1u << i);
    if ((value & mask) != 0) { ++count; }
  }
  return count;
}

int32_t ti_popcount64(const uint64_t value) {
  int32_t count = 0;
  for (int i = 0; i < UINT64_BIT_CNT; ++i) {
    const uint64_t mask = (1u << i);
    if ((value & mask) != 0) { ++count; }
  }
  return count;
}

#if defined(__cplusplus)
  }
#endif