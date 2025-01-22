
    #include <limits.h>
    #include <stdint.h>

    typedef enum {
      ACCESS_READ_ONLY,
      ACCESS_WRITE_ONLY,
      ACCESS_READ_WRITE,
      ACCESS_WRITE_ONLY,
      ACCESS_READ_WRITE_ONCE
    }access_t;

    #define FIELD_(pos, width) struct { uint32_t: pos; uint32_t value: width; }

    struct {
      uint32_t RC1[1][3];
      FIELD_(2, 3) RC2;
    }



    /**********************************************************************************************
     * @section Implementation Resources
     **********************************************************************************************/

    /* Qualifiers for read-only (RO) and read-write (RW) register pointers */
    #define RO_ const volatile
    #define RW_ volatile

    #define SSC_IMPL_(x, a, ...) a
    #define SSC_(x) SSC_IMPL_(x, [x])

    #define NA_OPT_IMPL_(x, a, b, ...) b
    #define NA_OPT_(x, a, b) NA_OPT_IMPL_(x, a, b)

    /**********************************************************************************************
     * @section Utilities
     **********************************************************************************************/

    #define NA ,
    
    /**** @subsection Register Definition Accessors ****/

    #define GET_ADDR(periph, periph_n, reg, reg_n) \
      (periph ## _ ## reg ## _PTR SSC_(periph_n) SSC_(reg_n))

    #define GET_OFF(periph, periph_n, reg, reg_n, field, field_n) \
      (periph ## _ ## reg ## _ ## field ## _OFF SSC_(periph_n) SSC_(reg_n) SSC_(field_n))

    #define GET_WIDTH(periph, periph_n, reg, reg_n, field, field_n) \
      (periph ## _ ## reg ## _ ## field ## _WIDTH SSC_(periph_n) SSC_(reg_n) SSC_(field_n))

    #define GET_MASK(periph, periph_n, reg, reg_n, field, field_n) \
      (periph ## _ ## reg ## _ ## field ## _MASK SSC_(periph_n) SSC_(reg_n) SSC_(field_n))

    #define GET_ACCESS(periph, periph_n, reg, reg_n, field, field_n) \
      (periph ## _ ## reg ## _ ## field ## _ACC SSC_(periph_n) SSC_(reg_n) SSC_(field_n))

    #define GET_RST(periph, periph_n, reg, reg_n, field, field_n) \
      (periph ## _ ## reg ## _ ## field ## _RST SSC_(periph_n) SSC_(reg_n) SSC_(field_n))

    /**** @subsection Register Manipulation Utilities ****/

    /**** @subsection Field Manipulation Utilities ****/

    /**** @subsection Register Inspection Utilities ****/

    /**** @subsection Field Inspection Utilities ****/


    #define WRITE_F(value, periph, periph_n, reg, reg_n, field, field_n) do { \
        _Static_assert(GET_ACCESS_F(periph, periph_n, reg, reg_n, field, field_n))
        *GET_PTR(periph, periph_n, reg, reg_n) =                              \
          (*GET_PTR(periph, periph_n, reg, reg_n)                             \
            ~GET_MASK(periph, periph_n, reg, reg_n, field, field_n)) |        \
          ((GET_VT(periph, periph_n, reg, reg_n)(value) <<                    \
            GET_POS(periph, periph_n, reg, reg_n, field, field_n)) &          \
              GET_MASK(periph, periph_n, reg, reg_n, field, field_n));        \
      } while (0)

    #define CSET(value, periph, periph_n, reg, reg_n, field, field_n) do { \
        *GET_PTR(periph, periph_n, reg, reg_n) = (!!(value)) ?             \
          (*GET_PTR(periph, periph_n, reg, reg_n) |                        \
            GET_MASK(periph, periph_n, reg, reg_n, field, field_n)) :      \
          (*GET_PTR(periph, periph_n, reg, reg_n) &                        \
            ~GET_MASK(periph, periph_n, reg, reg_n, field, field_n));      \
      } while (0)

    #define RST(periph, periph_n, reg, reg_n, field, field_n) do {     \
        *GET_PTR(periph, periph_n, reg, reg_n) =                       \
          (*GET_PTR(periph, periph_n, reg, reg_n) &                    \
            ~GET_MASK(periph, periph_n, reg, reg_n, field, field_n)) | \
            GET_RST(periph, periph_n, reg, reg_n, field, field_n);     \
      } while (0)

    #define SET(periph, periph_n, reg, reg_n, field, field_n) do { \
        *GET_PTR(periph, periph_n, reg, reg_n) |=                  \
          GET_MASK(periph, periph_n, reg, reg_n, field, field_n);  \
      } while (0)

    #define CLR(periph, periph_n, reg, reg_n, field, field_n) do { \
        *GET_PTR(periph, periph_n, reg, reg_n) &=                  \
          ~GET_MASK(periph, periph_n, reg, reg_n, field, field_n); \
      } while (0)

    #define TOGL(periph, periph_n, reg, reg_n, field, field_n) do { \
        *GET_PTR(periph, periph_n, reg, reg_n) ^=                   \
          GET_MASK(periph, periph_n, reg, reg_n, field, field_n);   \
      } while (0)


    #define READ(periph, periph_n, reg, reg_n, field, field_n)     \
      ((*GET_PTR(periph, periph_n, reg, reg_n) &                   \
        GET_MASK(periph, periph_n, reg, reg_n, field, field_n)) >> \
          GET_POS(periph, periph_n, reg, reg_n, field, field_n))

    #define IS_CSET(value, periph, periph_n, reg, reg_n, field, field_n)         \
      ((*GET_PTR(periph, periph_n, reg, reg_n) &                                 \
        GET_MASK(periph, periph_n, reg, reg_n, field, field_n)) == (!!(value)) ? \
          GET_MASK(periph, periph_n, reg, reg_n, field, field_n) : 0U)

    #define IS_RST(periph, periph_n, reg, reg_n, field, field_n)    \
      ((*GET_PTR(periph, periph_n, reg, reg_n) &                    \
        GET_MASK(periph, periph_n, reg, reg_n, field, field_n)) ==  \
          GET_RST(periph, periph_n, reg, reg_n, field, field_n) &   \
          GET_MASK(periph, periph_n, reg, reg_n, field, field_n))

    #define IS_SET(periph, periph_n, reg, reg_n, field, field_n)   \
      ((*GET_PTR(periph, periph_n, reg, reg_n) &                   \
        GET_MASK(periph, periph_n, reg, reg_n, field, field_n)) == \
          GET_MASK(periph, periph_n, reg, reg_n, field, field_n))

    #define IS_CLR(periph, periph_n, reg, reg_n, field, field_n)       \
      ((*GET_PTR(periph, periph_n, reg, reg_n) &                       \
        GET_MASK(periph, periph_n, reg, reg_n, field, field_n)) == 0U) 
