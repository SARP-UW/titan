
#include <string.h>

#include "app/utils/extern_flash.h"
#include "app/utils/packets.h"
#include "app/utils/state_comm.h"
#include "devices/umbilical.h"
#include "peripheral/errc.h"
#include "peripheral/gpio.h"
#include "peripheral/qspi.h"
#include "peripheral/systick.h"



// NOLINTNEXTLINE(readability-identifier-naming)
void _start() { // NOLINT(misc-use-internal-linkage)
    uint32_t pin = 99;

    tal_set_mode(pin, 1);
    tal_set_pin(pin, 1);
    tal_pull_pin(pin, 1);
}