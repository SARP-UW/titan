
// TODO -> RELOCATE ALL CODE TO APPROPRIATE FILES

#define sys_error(err) static_cast<void>(err)

  ////////////////////////////

  /**
   * @brief Denotes the type of a raw (un-typed) null pointer.
   */
  using nullptr_t = decltype(nullptr);

  ////////////////////////////

  /**
   * @brief Unit type which can only represent a single value.
   * @see www.wikipedia.org/wiki/Unit_type
   */
  struct monostate_t;

  /**
   * @brief Value of all monostate_t instances.
   * @see monostate_t
   */
  inline constexpr monostate_t monostate{};

  /**
   * @brief Equality comparison operator for monostate_t values. 
   * @return Always true (since all monostate_t instances represent the same value).
   */
  [[nodiscard]] constexpr bool operator == (monostate_t, monostate_t);

  /**
   * @brief Inequality comparison operator for monostate_t values.
   * @return Always false (since all monostate_t instances represent the same value).
   */
  [[nodiscard]] constexpr bool operator != (monostate_t, monostate_t);

  struct monostate_t {
    constexpr explicit monostate_t() = default;
  };

  constexpr bool operator == (monostate_t, monostate_t) { return true; }
  constexpr bool operator != (monostate_t, monostate_t) { return false; }


  ////////////////////////////

  /**
   * @brief Gets the address of an object.
   * @tparam T The type of the object.
   * @param target A lvalue reference to object to get the address of.
   * @returns A pointer to @p 'target'.
   */
  template<typename T>
  [[nodiscard]] constexpr T* addressof(T& target);

  template<typename T>
  constexpr T* addressof(T& target) {
    // return TI_BUILTIN_ADDRESSOF(target);
    return __builtin_addressof(target); // TO REMOVE
  }

  ////////////////////////////

  // Index Sequence

  using size_t = decltype(sizeof(void)); // TO REMOVE

  template<size_t... Is>
  struct index_sequence_t;

  // Implementation of 'make_index_sequence'
  template<size_t index, size_t... Is>
  struct MakeSeqImpl {
    using Type = typename MakeSeqImpl<index - 1, index, Is...>::Type;
  };

  template<size_t... Is>
  struct MakeSeqImpl<0, Is...> {
    using Type = index_sequence_t<0, Is...>;
  };

  /**
   * @brief Template type that holds a sequence of values..
   * @tparam ...Is A variadic pack of size_t NTTP values.
   */
  template<size_t... Is>
  struct index_sequence_t {
    constexpr explicit index_sequence_t() = default;
  };

  /**
   * @brief Creates an index_sequence_t with the given number of indicies.
   * @tparam N The number of indicies in the index sequence.
   * @returns An index_sequence_t value with @p 'N' indicies.
   */
  template<size_t N>
  [[nodiscard]] constexpr auto make_index_sequence() {
    return typename MakeSeqImpl<N - 1>::Type{};
  }

  ////////////////////////////
