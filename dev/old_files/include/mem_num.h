  /**
   * @defgroup tal_mem_copyn_xx
   * @brief Sets every value in memory at a location to a specific value.
   * @param mem (void*) The location in memory to set.
   * @param value (integer type denoted by suffix) The value to set.
   * @param cnt (int32_t) The number of values to set (note: size varies by type).
   * @param err (bool*) The error flag. Accessed and set true if 'cnt' is negative
   *            or 'mem' is NULL.
   * @returns (void*) The set location in memory ('mem').
   * @{
   */
  tal_fn_attr_inline inline void* tal_mem_copyn_u8(void* const mem, 
      const uint8_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_copyn_u16(void* const mem, 
      const uint16_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_copyn_u32(void* const mem, 
      const uint32_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_copyn_u64(void* const mem, 
      const uint64_t value, const int32_t cnt, bool* const err);
  /** @} */

  /**
   * @defgroup tal_mem_cmpn_x
   * @brief Compares every <size of value> bytes in a block of memory to a
   *        specific value.
   * @param mem (const void*) The block of memory to compare.
   * @param value (integer type denoted by suffix) The value to compare (repeated).
   * @param cnt (int32_t) The number of values to compare (note size varies by type).
   * @param err (bool*) The error flag. Accessed and set true if 'cnt' is negative,
   *            or 'mem' is NULL.
   * @returns (bool) True if 'cnt' is in bounds, 'mem' is not NULL, and every 
   *          <size of value> bytes in 'mem' is equal to 'value', or false 
   *          otherwise.
   * @{
   */
  tal_fn_attr_inline inline bool tal_mem_cmpn_u8(const void* const mem, 
      const uint8_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline bool tal_mem_cmpn_u16(const void* const mem, 
      const uint16_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline bool tal_mem_cmpn_u32(const void* const mem, 
      const uint32_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline bool tal_mem_cmpn_u64(const void* const mem, 
      const uint64_t value, const int32_t cnt, bool* const err);
  /** @} */



  /**
   * @defgroup tal_memval_i
   * @brief Gets the (suffix) offset of the first location in a block of memory
   *        that contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @param err (bool*) The error flag. Accessed and set true if 'cnt' is less
   *            than 0, or 'mem' is NULL.
   * @returns (int32_t) The byte offset of the first location in 'mem' that 
   *          contains 'value', or -1 if no such location exists, 'cnt' is 
   *          out of bounds, or 'mem' is NULL.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_mem_index_u8(const void* const mem,
      const uint8_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_index_u16(const void* const mem, 
      const uint16_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_index_u32(const void* const mem, 
      const uint32_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_index_u64(const void* const mem, 
      const uint64_t value, const int32_t cnt, bool* const err);
  /** @} */

  /**
   * @defgroup tal_memrval_i
   * @brief Gets the (suffix) offset of the last location in a block of memory
   *        that contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @param err (bool*) The error flag. Accessed and set true if 'cnt' is
   *            negative, or 'mem' is NULL.
   * @returns (int32_t) The byte offset of the last location in 'mem' that 
   *          contains 'value', or -1 if no such location exists, 'cnt' is out
   *          of bounds, or 'mem' is NULL.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_mem_indexr_u8(const void* const mem,
      const uint8_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_indexr_u16(const void* const mem, 
      const uint16_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_indexr_u32(const void* const mem, 
      const uint32_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_indexr_u64(const void* const mem, 
      const uint64_t value, const int32_t cnt, bool* const err);
  /** @} */

  /**
   * @defgroup tal_memnval_i
   * @brief Gets the (suffix) offset of the nth location in a block of memory
   *        that contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @param n (int32_t) The index of the matching location to get.
   * @param err (bool*) The error flag. Accessed and set true if 'cnt' or 'n' is
   *            negative, or 'mem' is NULL.
   * @returns (int32_t) The byte offset of the nth location in 'mem' that 
   *          contains 'value', or -1 if no such location exists, 'cnt' or 'n' 
   *          out of bounds, or 'mem' is NULL.
   * @{
   */
  tal_fn_attr_inline inline int32_t tal_mem_indexn_u8(const void* const mem, 
      const uint8_t value, const int32_t cnt, const int32_t n, 
      bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_indexn_u16(const void* const mem, 
      const uint16_t value, const int32_t cnt, const int32_t n, 
      bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_indexn_u32(const void* const mem, 
      const uint32_t value, const int32_t cnt, const int32_t n, 
      bool* const err);
  tal_fn_attr_inline inline int32_t tal_mem_indexn_u64(const void* const mem, 
      const uint64_t value, const int32_t cnt, const int32_t n, 
      bool* const err);
  /** @} */


  /**
   * @defgroup tal_memval
   * @brief Gets a pointer to the first location in a block of memory that
   *        contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @param err (bool*) The error flag. Accessed and set true if 'cnt' is 
   *            negative, or 'mem' is NULL.
   * @returns (void*) A pointer to the start of the first location in 'mem' that 
   *          contains 'value', or NULL if no such location exists, 'cnt' is out 
   *          of bounds, or 'mem' is NULL.
   * @{
   */
  tal_fn_attr_inline inline void* tal_mem_get_u8(const void* const mem, 
      const uint8_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_get_u16(const void* const mem, 
      const uint16_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_get_u32(const void* const mem, 
      const uint32_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_get_u64(const void* const mem, 
      const uint64_t value, const int32_t cnt, bool* const err);
  /** @} */

  /**
   * @defgroup tal_memrval
   * @brief Gets a pointer to the last location in a block of memory that
   *        contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @param err (bool*) The error flag. Accessed and set true if 'cnt' is 
   *            negative, or 'mem' is NULL.
   * @returns (void*) A pointer to the start of the last location in 'mem' that 
   *          contains 'value', or NULL if no such location exists, 'cnt' is out
   *          of bounds, or 'mem' is NULL.
   * @{
   */
  tal_fn_attr_inline inline void* tal_mem_ptrr_u8(const void* const mem, 
      const uint8_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_getr_u16(const void* const mem, 
      const uint16_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_getr_u32(const void* const mem, 
      const uint32_t value, const int32_t cnt, bool* const err);
  tal_fn_attr_inline inline void* tal_mem_getr_u64(const void* const mem, 
      const uint64_t value, const int32_t cnt, bool* const err);
  /** @} */

  /**
   * @defgroup tal_memnval
   * @brief Gets a pointer to the nth location in a block of memory that
   *        contains a specific value.
   * @param mem (const void*) The memory location to search within.
   * @param value (unsigned integer denoted by suffix) The value to find in 'mem'.
   * @param cnt (int32_t) The total number of values to search in 'mem' (note
   *            that size varies by type).
   * @param n (int32_t) The index of the matching location to get.
   * @param err (bool*) The error flag. Accessed and set true if 'cnt' or 'n' is
   *            negative, or 'mem' is NULL.
   * @returns (void*) A pointer to the start of the nth location in 'mem' that
   *          contains 'value', or NULL if no such location exists, 'cnt' or 'n' 
   *          is out of bounds, or 'mem' is NULL.
   * @{
   */
  tal_fn_attr_inline inline void* tal_mem_getn_u8(const void* const mem, 
      const uint8_t value, const int32_t cnt, const int32_t n, 
      bool* const err);
  tal_fn_attr_inline inline void* tal_mem_getn_u16(const void* const mem, 
      const uint16_t value, const int32_t cnt, const int32_t n, 
      bool* const err);
  tal_fn_attr_inline inline void* tal_mem_getn_u32(const void* const mem, 
      const uint32_t value, const int32_t cnt, const int32_t n, 
      bool* const err);
  tal_fn_attr_inline inline void* tal_mem_getn_u64(const void* const mem, 
      const uint64_t value, const int32_t cnt, const int32_t n, 
      bool* const err);
  /** @} */




  void* tal_mem_copyn_u8(void* const mem, const uint8_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_mem_copyn_u16(void* const mem, const uint16_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_mem_copyn_u32(void* const mem, const uint32_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }

  void* tal_mem_copyn_u64(void* const mem, const uint64_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) { m[i] = value; }
    }
    return mem;
  }




  bool tal_mem_cmpn_u8(const void* const mem, const uint8_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) { 
      *err = true;
      return false;
    }
    const uint8_t* m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_mem_cmpn_u16(const void* const mem, const uint16_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) { 
      *err = true;
      return false;
    }
    const uint16_t* m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_mem_cmpn_u32(const void* const mem, const uint32_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) { 
      *err = true;
      return false;
    }
    const uint32_t* m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }

  bool tal_mem_cmpn_u64(const void* const mem, const uint64_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) { 
      *err = true;
      return false;
    }
    const uint64_t* m = mem;
    for (int32_t i = 0; i < cnt; ++i) {
      if (m[i] != value) { return false; }
    }
    return true;
  }









  int32_t tal_mem_index_u8(const void* const mem, const uint8_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
  }

  int32_t tal_mem_index_u16(const void* const mem, const uint16_t value, 
      const int32_t cnt,  bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_index_u32(const void* const mem, const uint32_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_index_u64(const void* const mem, const uint64_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }
  
  int32_t tal_mem_indexr_u8(const void* const mem, const uint8_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint8_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexr_u16(const void* const mem, const uint16_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint16_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexr_u32(const void* const mem, const uint32_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint32_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexr_u64(const void* const mem, const uint64_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint64_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return i; }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn_u8(const void* const mem, const uint8_t value, 
      const int32_t cnt, const int32_t n, bool* const err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn_u16(const void* const mem, const uint16_t value, 
      const int32_t cnt, const int32_t n, bool* const err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn_u32(const void* const mem, const uint32_t value, 
      const int32_t cnt, const int32_t n, bool* const err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }

  int32_t tal_mem_indexn_u64(const void* const mem, const uint64_t value, 
      const int32_t cnt, const int32_t n, bool* const err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return i; }
        }
      }
    }
    return -1;
  }


  void* tal_mem_get_u8(const void* const mem, const uint8_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_get_u16(const void* const mem, const uint16_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_get_u32(const void* const mem, const uint32_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_get_u64(const void* const mem, const uint64_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_getr_u8(const void* const mem, const uint8_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint8_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_getr_u16(const void* const mem, const uint16_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint16_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_getr_u32(const void* const mem, const uint32_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint32_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }

  void* tal_mem_getr_u64(const void* const mem, const uint64_t value, 
      const int32_t cnt, bool* const err) {
    if (!mem || cnt < 0) {
      *err = true;
    } else {
      const uint64_t* m = mem;
      for (int32_t i = cnt - 1; i >= 0; --i) {
        if (m[i] == value) { return (void*)(mem + i); }
      }
    }
    return NULL;
  }


  void* tal_mem_getn_u8(const void* const mem, const uint8_t value, 
      const int32_t cnt, const int32_t n, bool* const err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint8_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getn_u16(const void* const mem, const uint16_t value, 
      const int32_t cnt, const int32_t n, bool* const err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint16_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getn_u32(const void* const mem, const uint32_t value, 
      const int32_t cnt, const int32_t n, bool* const err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint32_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }

  void* tal_mem_getn_u64(const void* const mem, const uint64_t value, 
      const int32_t cnt, const int32_t n, bool* const err) {
    if (!mem || cnt < 0 || n < 0) {
      *err = true;
    } else {
      int32_t cur_cnt = 0;
      const uint64_t* m = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        if (m[i] == value) {
          ++cur_cnt;
          if (cur_cnt == n) { return (void*)(mem + i); }
        }
      }
    }
    return NULL;
  }








  void* tal_mem_insert_u8(void* const mem, const int32_t size,
      const int32_t off, const uint8_t value, const int32_t cnt, 
      bool* const err) {
    if (!mem || size < 0 || off < 0 || cnt < 0 || off > size) {
      *err = true;
    } else {
      uint8_t* const m_byte = mem;
      for (int32_t i = size - 1; i >= off; --i) {
        m_byte[(sizeof(uint8_t) * cnt) + i] = m_byte[i];
      }
      for (int32_t i = 0; i < cnt; ++i) {
        m_byte[off + i] = value;
      }
    }
    return mem;
  }

  void* tal_mem_insert_u16(void* const mem, const int32_t size,
      const int32_t off, const uint8_t value, const int32_t cnt, 
      bool* const err) {
    if (!mem || size < 0 || off < 0 || cnt < 0 || off > size ||
        off % sizeof(uint16_t) != 0) {
      *err = true;
    } else {
      uint8_t* const m_byte = mem;
      for (int32_t i = size - 1; i >= (off * sizeof(uint16_t)); --i) {
        m_byte[(sizeof(uint16_t) * cnt) + i] = m_byte[i];
      }
      uint16_t* const m_u16 = mem;
      for (int32_t i = 0; i < cnt; ++i) {
        m_u16[(off / sizeof(uint16_t)) + i] = value;
      }
    }
    return mem;
  }