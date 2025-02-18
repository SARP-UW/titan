  // LDO regulator enable
  #define TI_PCFG_PWR_LDO_ENABLE true

  // SMPS regulator enable
  #define TI_PCFG_PWR_SMPS_ENABLE true

  // SMPS voltage output to external components
  #define TI_PCFG_PWR_SMPS_EXTERN true

  // SMPS voltage level
  #define TI_PCFG_PWR_SMPS_LEVEL 33

  // Battery power enable
  #define TI_PCFG_PWR_BAT_ENABLE true

  // Battery charging enable
  #define TI_PCFG_PWR_BAT_CHARGE_ENABLE false

  // Battery resistor value (only relevant if charging enabled)
  #define TI_PCFG_PWR_BAT_RESISTOR 5000

  // USB voltage regulator enable (5v input)
  #define TI_PCFG_PWR_USB_REG_ENABLE false

  // Maximum CPU clock frequency
  #define TI_PCFG_CLK_CPU_FREQ_MAX 400000000

  // Enable high speed external oscillator
  #define TI_PCFG_CLK_HSE_ENABLE false

  // High speed external oscillator frequency
  #define TI_PCFG_CLK_HSE_FREQ 48000000

  // Use for crystal/ceramic resonators
  #define TI_PCFG_CLK_HSE_BYPASS false

  // Enable low speed external oscillator
  #define TI_PCFG_CLK_LSE_ENABLE false

  // Low speed external oscillator frequency
  #define TI_PCFG_CLK_LSE_FREQ 32768

  // Use for crystal/ceramic resonators
  #define TI_PCFG_CLK_LSE_BYPASS false

  // Drive strength for LSE oscillator (0-3, low-high)
  #define TI_PCFG_CLK_LSE_DRIVE 0

  // Base system clock frequency (LDO required if greater than 400Mhz)
  #define TI_PCFG_CLK_SYS_FREQ 480000000