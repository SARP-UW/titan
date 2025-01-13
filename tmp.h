


    /**********************************************************************************************
     * @section Implementation Resources
     **********************************************************************************************/

    /* Qualifiers for read-only (RO) and read-write (RW) register pointers */
    #define RO_ const volatile
    #define RW_ volatile

    /* Macros for conditionally indexing into arrays */
    #define NX_FN_(...)
    #define INDEX_FN_(x) [x]
    #define INDEX_IMPL_(a, b, ...) b(a)
    #define INDEX_(...) INDEX_IMPL_(__VA_ARGS__, INDEX_FN_)

    /* Generates the token for a register pointer */
    #define GET_REG_(periph, periph_n, reg, reg_n) \
      (periph ## _ ## reg ## _REG INDEX_(periph_n) INDEX_(reg_n))

    /* Generates the token for a register reset value */
    #define GET_RST_(periph, periph_n, reg, reg_n) \
      (periph ## _ ## reg ## _RST INDEX_(periph_n) INDEX_(reg_n))

    /* Generates the token for a field mask */
    #define GET_MASK_(periph, reg, field, field_n) \
      (periph ## _ ## reg ## _ ## field ## _MASK INDEX_(field_n))

    /* Generates the token for a field position value */
    #define GET_POS_(periph, reg, field, field_n) \
      (periph ## _ ## reg ## _ ## field ## _POS INDEX_(field_n))

    /**********************************************************************************************
     * @section Utilities
     **********************************************************************************************/

    #define NX 0, NX_FN_

    #define WRITE(periph, periph_n, reg, reg_n, field, field_n, value) do { \
        *GET_REG_(periph, periph_n, reg, reg_n) =                           \
          (*GET_REG_(periph, periph_n, reg, reg_n) &                        \
            ~GET_MASK_(periph, reg, field, field_n)) |                      \
          ((value << GET_POS_(periph, reg, field, field_n)) &               \
            GET_MASK_(periph, reg, field, field_n))                         \
      } while (0)


    #define FILL(periph, periph_n, reg, reg_n, field, field_n, value) do { \
        if (!!(value)) SET(periph, periph_n, reg, reg_n, field, field_n);  \
        else CLR(periph, periph_n, reg, reg_n, field, field_n);            \
      } while (0)


    #define SET(periph, periph_n, reg, reg_n, field, field_n) do { \
        *GET_REG_(periph, periph_n, reg, reg_n) |=                 \
          GET_MASK_(periph, reg, field, field_n);                  \
      } while (0)


    #define CLR(periph, periph_n, reg, reg_n, field, field_n) do { \
        *GET_REG_(periph, periph_n, reg, reg_n) &=                 \
          ~GET_MASK_(periph, reg, field, field_n)                  \
      } while (0)


    #define TGL(periph, periph_n, reg, reg_n, field, field_n) do { \
        *GET_REG_(periph, periph_n, reg, reg_n) ^=                 \
          GET_MASK_(periph, reg, field, field_n)                   \
      } while (0)


    #define READ(periph, periph_n, reg, reg_n, field, field_n) \
      ((*GET_REG_(periph, periph_n, reg, reg_n) &              \
        GET_MASK_(periph, reg, field, field_n)) >>             \
      GET_POS_(periph, reg, field, field_n))