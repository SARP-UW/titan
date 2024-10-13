
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

  /**************************************************************************************************
   * @section Error Code Class Definition
   **************************************************************************************************/
  



  #define TI_TO_STR_FUNC_(x) #x
  #define TI_TO_STR_(x) TI_TO_STR_FUNC_(x)
  #define TI_CREATE_ERROR_MSG_(msg) "TITAN ERROR: File {"__FILE__ \
      "}, Line {" TI_TO_STR_(__LINE__) "}, Message {" msg "}"

  /// @endinternal

  /**
   * @brief Formats an error message string.
   * @param msg The message to format.
   * @note - The format of the resulting string is: "TITAN ERROR: File {<file>}, 
   *         Line {<line>}, Message {<msg>}".
   * @note - The location embedded in the error message is the location (in code) 
   *         where this macro function is used.
   */
  #define TI_ERROR_MSG(msg) TI_CREATE_ERROR_MSG_(msg)



  ////////////////////////////
