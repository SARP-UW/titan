
#include <string.h>

#include "app/utils/extern_flash.h"
#include "app/utils/packets.h"
#include "app/utils/state_comm.h"
#include "devices/umbilical.h"
#include "peripheral/errc.h"
#include "peripheral/gpio.h"
#include "peripheral/qspi.h"
#include "app/utils/pinout.h"
#include "peripheral/systick.h"



// NOLINTNEXTLINE(readability-identifier-naming)
void _start() { // NOLINT(misc-use-internal-linkage)3

    int a = 10;
    tal_enable_clock(BATT_EN);
    tal_set_mode(BATT_EN, 1);
    asm("BKPT #0");
    tal_set_pin(BATT_EN, 1);
    tal_pull_pin(BATT_EN, 1);
    
}