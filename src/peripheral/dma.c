#include "dma.h"
#include "errc.h"

void* dma_init(enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    return NULL;
}

bool dma_configure_stream(const dma_config_t* config) {
    (void)config;
    return true;
}
inline static bool check_periph_dma_config_validity(periph_dma_config_t *dma_config) {
    (void)dma_config;
    return true;
}

bool dma_start_transfer( dma_transfer_t *dma_transfer) {
    (void)dma_transfer;
    return true;
}