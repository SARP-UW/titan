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
 * @file src/lib/bit/bit_mask.c
 * @authors Aaron McBride
 * @brief Implementation of bit-mask utilities.
 */

#include "include/tal/bit.h" // header

#if defined(__cplusplus)
  extern "C" {
#endif

  // Returns true if pos/len are within bit mask of specified size.
  static bool valid_mask__(const int32_t bit_size, const int32_t pos,
      const int32_t len) {
    return (pos >= 0) && (len >= 0) && ((pos + len) <= bit_size);
  } 

  uint8_t tal_mask_u8(bool* const err, const int32_t pos, const int32_t len) {
    if (!valid_mask__(tal_bit_size(uint8_t), pos, len)) {
      *err = true;
      return UINT8_C(0);
    }
    if (len == 0) { return UINT8_C(0); }
    return ((UINT8_C(1) << len) - UINT8_C(1)) << pos;
  }

  uint16_t tal_mask_u16(bool* const err, const int32_t pos, const int32_t len) {
    if (!valid_mask__(tal_bit_size(uint16_t), pos, len)) {
      *err = true;
      return UINT16_C(0);
    }
    if (len == 0) { return UINT16_C(0); }
    return ((UINT16_C(1) << len) - UINT16_C(1)) << pos;
  }

  uint32_t tal_mask_u32(bool* const err, const int32_t pos, const int32_t len) {
    if (!valid_mask__(tal_bit_size(uint32_t), pos, len)) {
      *err = true;
      return UINT32_C(0);
    }
    if (len == 0) { return UINT32_C(0); }
    return ((UINT32_C(1) << len) - UINT32_C(1)) << pos;
  }

  uint64_t tal_mask_u64(bool* const err, const int32_t pos, const int32_t len) {
    if (!valid_mask__(tal_bit_size(uint64_t), pos, len)) {
      *err = true;
      return UINT64_C(0);
    }
    if (len == 0) { return UINT64_C(0); }
    return ((UINT64_C(1) << len) - UINT64_C(1)) << pos;
  }

  uint8_t tal_write_bits_u8(bool* const err, const uint8_t value, 
      const uint8_t dest, const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint8_t mask = tal_mask_u8(pos, len, &mask_err);
    if (mask_err || tal_bit_width_u8(value) > len) {
      *err = true;
      return dest;
    }
    return (dest & ~mask) | (value << pos);
  }

  uint16_t tal_write_bits_u16(bool* const err, const uint16_t value, 
      const uint16_t dest, const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint16_t mask = tal_mask_u16(pos, len, &mask_err);
    if (mask_err || tal_bit_width_u16(value) > len) {
      *err = true;
      return dest;
    }
    return (dest & ~mask) | (value << pos);
  }


  uint32_t tal_write_bits_u32(bool* const err, const uint32_t value, 
      const uint32_t dest, const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint32_t mask = tal_mask_u32(pos, len, &mask_err);
    if (mask_err || tal_bit_width_u32(value) > len) {
      *err = true;
      return dest;
    }
    return (dest & ~mask) | (value << pos);
  }

  uint64_t tal_write_bits_u64(bool* const err, const uint64_t value, 
      const uint64_t dest, const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint64_t mask = tal_mask_u64(pos, len, &mask_err);
    if (mask_err || tal_bit_width_u64(value) > len) {
      *err = true;
      return dest;
    }
    return (dest & ~mask) | (value << pos);
  }

  uint8_t tal_read_bits_u8(bool* const err, const uint8_t src, 
      const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint8_t mask = tal_mask_u8(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return UINT8_C(0);
    }
    return (src & mask) >> pos;
  }

  uint16_t tal_read_bits_u16(bool* const err, const uint16_t src, 
      const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint16_t mask = tal_mask_u16(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return UINT16_C(0);
    }
    return (src & mask) >> pos;
  }

  uint32_t tal_read_bits_u32(bool* const err, const uint32_t src,   
      const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint32_t mask = tal_mask_u32(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return UINT32_C(0);
    }
    return (src & mask) >> pos;
  }

  uint64_t tal_read_bits_u64(bool* const err, const uint64_t src, 
      const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint64_t mask = tal_mask_u64(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return UINT64_C(0);
    }
    return (src & mask) >> pos;
  }

  uint8_t tal_set_bits_u8(bool* const err, const bool value, 
      const uint8_t dest, const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint8_t mask = tal_mask_u8(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return dest;
    }
    if (value) {
      return dest | mask;
    } else {
      return dest & ~mask;
    }
  }

  uint16_t tal_set_bits_u16(bool* const err, const bool value, 
      const uint16_t dest, const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint16_t mask = tal_mask_u16(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return dest;
    }
    if (value) {
      return dest | mask;
    } else {
      return dest & ~mask;
    }
  }

  uint32_t tal_set_bits_u32(bool* const err, const bool value, 
      const uint32_t dest, const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint32_t mask = tal_mask_u32(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return dest;
    }
    if (value) {
      return dest | mask;
    } else {
      return dest & ~mask;
    }
  }

  uint64_t tal_set_bits_u64(bool* const err, const bool value, 
      const uint64_t dest, const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint64_t mask = tal_mask_u64(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return dest;
    }
    if (value) {
      return dest | mask;
    } else {
      return dest & ~mask;
    }
  }

  int32_t tal_get_bits_u8(bool* const err, const uint8_t src, 
      const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint8_t mask = tal_mask_u8(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return false;
    }
    if ((src & mask) == mask) { return 1; } 
    if ((src & mask) == UINT8_C(0)) { return 0; }
    return -1;
  }

  int32_t tal_get_bits_u16(bool* const err, const uint16_t src, 
      const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint16_t mask = tal_mask_u16(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return false;
    }
    if ((src & mask) == mask) { return 1; }
    if ((src & mask) == UINT16_C(0)) { return 0; }
    return -1;
  }

  int32_t tal_get_bits_u32(bool* const err, const uint32_t src, 
      const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint32_t mask = tal_mask_u32(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return false;
    }
    if ((src & mask) == mask) { return 1; }
    if ((src & mask) == UINT32_C(0)) { return 0; }
    return -1;
  }

  int32_t tal_get_bits_u64(bool* const err, const uint64_t src, 
      const int32_t pos, const int32_t len) {
    bool mask_err = false;
    const uint64_t mask = tal_mask_u64(pos, len, &mask_err);
    if (mask_err) {
      *err = true;
      return false;
    }
    if ((src & mask) == mask) { return 1; }
    if ((src & mask) == UINT64_C(0)) { return 0; }
    return -1;
  }

#if defined(__cplusplus)
  } // extern "C"
#endif