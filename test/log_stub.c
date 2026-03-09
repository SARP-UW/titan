/* Stub implementations of ti_log_init / ti_log_write for native host builds.
 * Used by the test_alloc custom target in CMakeLists.txt, which compiles with
 * the system gcc and cannot link against the real log.c (which calls QSPI). */

#include "../src/peripheral/log.h"

enum ti_errc_t ti_log_init(void) {
    return TI_ERRC_NONE;
}

void ti_log_write(enum ti_errc_t errc, const char *msg,
                  const char *func, const char *file, uint32_t line) {
    (void)errc; (void)msg; (void)func; (void)file; (void)line;
}
