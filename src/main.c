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
#include "peripheral/pwm.h"



// NOLINTNEXTLINE(readability-identifier-naming)
void _start() { // NOLINT(misc-use-internal-linkage)3




  struct ti_pwm_config_t config = {
    2,    /**< PWM hardware instance */
    2,      /**< PWM channel number */
    1000,        /**< Output frequency in Hz */
    500,        /**< Duty cycle (0-1000 for 0-100%) */
    2000000  /**< Source clock frequency in Hz */
  };

  ti_set_pwm(config, 0);
  

  tal_enable_clock(BATT_EN);
  tal_set_mode(BATT_EN, 1);
  tal_set_pin(BATT_EN, 1);

  while (true)
  {
    asm("NOP");
  }
  

}