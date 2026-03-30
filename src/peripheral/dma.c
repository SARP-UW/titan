#include "dma.h"
#include "errc.h"
void* dma_init(enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    return (void*) (0);
}

bool dma_configure_stream(const dma_config_t* config) {
    return 1;
}
inline static bool check_periph_dma_config_validity(periph_dma_config_t *dma_config) {
    return 1;
}

bool dma_start_transfer( dma_transfer_t *dma_transfer) {
    return 1;
}