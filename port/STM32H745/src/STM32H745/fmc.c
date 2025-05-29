#include "titan/fmc.h"
#include "STM32H745/resource/mmio.h"
#include <stdint.h>

// --- Constants ---
// SDRAM Timings (calculated for 100MHz SDCLK, tCK=10ns, using MT48LC4M32B2 -6 speed grade)
// Values are (Cycles - 1) for FMC timing registers
#define SDRAM_TMRD_VAL  1  // Load Mode Register to Active = 2 cycles
#define SDRAM_TXSR_VAL  6  // Exit Self-refresh delay = 7 cycles (70ns)
#define SDRAM_TRAS_VAL  4  // Row Active time = 5 cycles (42ns min -> 50ns)
#define SDRAM_TRC_VAL   5  // Row Cycle Delay = 6 cycles (60ns)
#define SDRAM_TWR_VAL   1  // Write Recovery time = 2 cycles (1 tCK + 6ns = 16ns -> 20ns)
#define SDRAM_TRP_VAL   1  // Row Precharge time = 2 cycles (18ns min -> 20ns)
#define SDRAM_TRCD_VAL  1  // Row to Column delay = 2 cycles (18ns min -> 20ns)

// Refresh Count (calculated for 64ms/4096 rows @ 100MHz SDCLK)
// Refresh Rate = (64ms / 4096 rows) = 15.625 µs
// Count = (Refresh Rate / SDCLK Period) - 20 = (15.625 µs / 10 ns) - 20 = 1562.5 -> 1542
#define SDRAM_REFRESH_COUNT_VAL 1542 // Use 1542 cycles

// SDRAM Mode Register Value (for MT48LC4M32B2)
// Configuration: Burst Length=2 , CAS Latency=3 (011), Burst Type=Sequential (0),
//                Operating Mode=Standard (00), Write Burst Mode=Programmed Burst Length (0)
// Mode Register bits (based on SDRAM Fig 4): M11 M10 M9 M8 M7 M6 M5 M4 M3 M2 M1 M0
// Value:                                     0   0   0  0  0  0  1  1  0  0  0  1 = 0x0031
#define SDRAM_MODE_REGISTER_VAL 0x0031

//FMC Pin Definitions: Temporary - Replace with real pins for FBGA250 board

#define FMC_A0_PORT_IDX     5 // GPIOF
#define FMC_A0_PIN_IDX      0 // PF0
#define FMC_A1_PORT_IDX     5 // GPIOF
#define FMC_A1_PIN_IDX      1 // PF1
#define FMC_A2_PORT_IDX     5 // GPIOF
#define FMC_A2_PIN_IDX      2 // PF2
#define FMC_A3_PORT_IDX     5 // GPIOF
#define FMC_A3_PIN_IDX      3 // PF3
#define FMC_A4_PORT_IDX     5 // GPIOF
#define FMC_A4_PIN_IDX      4 // PF4
#define FMC_A5_PORT_IDX     5 // GPIOF
#define FMC_A5_PIN_IDX      5 // PF5
#define FMC_A6_PORT_IDX     5 // GPIOF
#define FMC_A6_PIN_IDX      12// PF12
#define FMC_A7_PORT_IDX     5 // GPIOF
#define FMC_A7_PIN_IDX      13// PF13
#define FMC_A8_PORT_IDX     5 // GPIOF
#define FMC_A8_PIN_IDX      14// PF14
#define FMC_A9_PORT_IDX     5 // GPIOF
#define FMC_A9_PIN_IDX      15// PF15
#define FMC_A10_PORT_IDX    6 // GPIOG
#define FMC_A10_PIN_IDX     0 // PG0
#define FMC_A11_PORT_IDX    6 // GPIOG
#define FMC_A11_PIN_IDX     1 // PG1

// Bank Address Pins (BA0-BA1) - 2 signals
// These often correspond to FMC_A12 and FMC_A13 in STM32 documentation
#define FMC_BA0_PORT_IDX    6 // GPIOG
#define FMC_BA0_PIN_IDX     4 // PG4 (Often FMC_A12)
#define FMC_BA1_PORT_IDX    6 // GPIOG
#define FMC_BA1_PIN_IDX     5 // PG5 (Often FMC_A13)

// Data Pins (D0-D31) - 32 signals
#define FMC_D0_PORT_IDX     3 // GPIOD
#define FMC_D0_PIN_IDX      14// PD14
#define FMC_D1_PORT_IDX     3 // GPIOD
#define FMC_D1_PIN_IDX      15// PD15
#define FMC_D2_PORT_IDX     3 // GPIOD
#define FMC_D2_PIN_IDX      0 // PD0
#define FMC_D3_PORT_IDX     3 // GPIOD
#define FMC_D3_PIN_IDX      1 // PD1
#define FMC_D4_PORT_IDX     4 // GPIOE
#define FMC_D4_PIN_IDX      7 // PE7
#define FMC_D5_PORT_IDX     4 // GPIOE
#define FMC_D5_PIN_IDX      8 // PE8
#define FMC_D6_PORT_IDX     4 // GPIOE
#define FMC_D6_PIN_IDX      9 // PE9
#define FMC_D7_PORT_IDX     4 // GPIOE
#define FMC_D7_PIN_IDX      10// PE10
#define FMC_D8_PORT_IDX     4 // GPIOE
#define FMC_D8_PIN_IDX      11// PE11
#define FMC_D9_PORT_IDX     4 // GPIOE
#define FMC_D9_PIN_IDX      12// PE12
#define FMC_D10_PORT_IDX    4 // GPIOE
#define FMC_D10_PIN_IDX     13// PE13
#define FMC_D11_PORT_IDX    4 // GPIOE
#define FMC_D11_PIN_IDX     14// PE14
#define FMC_D12_PORT_IDX    4 // GPIOE
#define FMC_D12_PIN_IDX     15// PE15
#define FMC_D13_PORT_IDX    3 // GPIOD
#define FMC_D13_PIN_IDX     8 // PD8
#define FMC_D14_PORT_IDX    3 // GPIOD
#define FMC_D14_PIN_IDX     9 // PD9
#define FMC_D15_PORT_IDX    3 // GPIOD
#define FMC_D15_PIN_IDX     10// PD10
#define FMC_D16_PORT_IDX    7 // GPIOH
#define FMC_D16_PIN_IDX     8 // PH8
#define FMC_D17_PORT_IDX    7 // GPIOH
#define FMC_D17_PIN_IDX     9 // PH9
#define FMC_D18_PORT_IDX    7 // GPIOH
#define FMC_D18_PIN_IDX     10// PH10
#define FMC_D19_PORT_IDX    7 // GPIOH
#define FMC_D19_PIN_IDX     11// PH11
#define FMC_D20_PORT_IDX    7 // GPIOH
#define FMC_D20_PIN_IDX     12// PH12
#define FMC_D21_PORT_IDX    7 // GPIOH
#define FMC_D21_PIN_IDX     13// PH13
#define FMC_D22_PORT_IDX    7 // GPIOH
#define FMC_D22_PIN_IDX     14// PH14
#define FMC_D23_PORT_IDX    7 // GPIOH
#define FMC_D23_PIN_IDX     15// PH15
#define FMC_D24_PORT_IDX    8 // GPIOI
#define FMC_D24_PIN_IDX     0 // PI0
#define FMC_D25_PORT_IDX    8 // GPIOI
#define FMC_D25_PIN_IDX     1 // PI1
#define FMC_D26_PORT_IDX    8 // GPIOI
#define FMC_D26_PIN_IDX     2 // PI2
#define FMC_D27_PORT_IDX    8 // GPIOI
#define FMC_D27_PIN_IDX     3 // PI3
#define FMC_D28_PORT_IDX    8 // GPIOI
#define FMC_D28_PIN_IDX     6 // PI6
#define FMC_D29_PORT_IDX    8 // GPIOI
#define FMC_D29_PIN_IDX     7 // PI7
#define FMC_D30_PORT_IDX    8 // GPIOI
#define FMC_D30_PIN_IDX     9 // PI9
#define FMC_D31_PORT_IDX    8 // GPIOI
#define FMC_D31_PIN_IDX     10// PI10

// Control Pins - 6 signals
#define FMC_SDCLK_PORT_IDX  6 // GPIOG
#define FMC_SDCLK_PIN_IDX   8 // PG8 (Typical for FMC_SDCLK)

#define FMC_SDCKE0_PORT_IDX 2 // GPIOC
#define FMC_SDCKE0_PIN_IDX  3 // PC3 (Typical for FMC_SDCKE0 for Bank1/SDNE0)
                              // Alternative: PH2 (Port 7, Pin 2)

#define FMC_SDNE0_PORT_IDX  2 // GPIOC
#define FMC_SDNE0_PIN_IDX   2 // PC2 (Typical for FMC_SDNE0 for Bank1)
                              // Alternative: PH3 (Port 7, Pin 3)

#define FMC_SDNRAS_PORT_IDX 5 // GPIOF
#define FMC_SDNRAS_PIN_IDX  11// PF11 (Typical for FMC_SDNRAS)

#define FMC_SDNCAS_PORT_IDX 6 // GPIOG
#define FMC_SDNCAS_PIN_IDX  15// PG15 (Typical for FMC_SDNCAS)

#define FMC_SDNWE_PORT_IDX  7 // GPIOH
#define FMC_SDNWE_PIN_IDX   5 // PH5 (Typical for FMC_SDNWE when using SDNE0)
                              // Alternative: PC0 (Port 2, Pin 0)

// Byte Lane Select Pins (NBL0-NBL3 / DQM0-DQM3) - 4 signals
#define FMC_NBL0_PORT_IDX   4 // GPIOE
#define FMC_NBL0_PIN_IDX    0 // PE0 (Typical for FMC_NBL0 / DQM0)

#define FMC_NBL1_PORT_IDX   4 // GPIOE
#define FMC_NBL1_PIN_IDX    1 // PE1 (Typical for FMC_NBL1 / DQM1)

#define FMC_NBL2_PORT_IDX   8 // GPIOI
#define FMC_NBL2_PIN_IDX    4 // PI4 (Typical for FMC_NBL2 / DQM2, ensure no conflict with Dxx)

#define FMC_NBL3_PORT_IDX   8 // GPIOI
#define FMC_NBL3_PIN_IDX    5 // PI5 (Typical for FMC_NBL3 / DQM3, ensure no conflict with Dxx)



// --- Helper Functions ---

/**
 * @brief Provides a simple blocking delay.
 * @param count Number of loop iterations. Adjust based on core clock speed.
 */
void simple_delay(volatile uint32_t count) {
    while(count--);
}

void config_fmc_pin(int port_idx, int pin_idx) {
    // Basic validation (optional)
    if (port_idx < 0 || port_idx > 10 || pin_idx < 0 || pin_idx > 15) {
        // Handle error: Invalid port/pin index
        return;
    }

    // 1. Set Mode to Alternate Function (0b10)
    // Assumes mmio.h defines: GPIOx_MODER[port_idx], GPIOx_MODER_MODEx[pin_idx]
    WRITE_FIELD(GPIOx_MODER[port_idx], GPIOx_MODER_MODEx[pin_idx], 0b10);
    // 2. Set Output Type to Push-Pull (0)
    // Assumes mmio.h defines: GPIOx_OTYPER[port_idx], GPIOx_OTYPER_OTx[pin_idx]
    CLR_FIELD(GPIOx_OTYPER[port_idx], GPIOx_OTYPER_OTx[pin_idx]);
    // 3. Set Speed to Very High Speed (0b11)
    // Assumes mmio.h defines: GPIOx_OSPEEDR[port_idx], GPIOx_OSPEEDR_OSPEEDx[pin_idx]
    WRITE_FIELD(GPIOx_OSPEEDR[port_idx], GPIOx_OSPEEDR_OSPEEDx[pin_idx], 0b11);
    // 4. Set Pull-up/Pull-down to None (0b00)
    // Assumes mmio.h defines: GPIOx_PUPDR[port_idx], GPIOx_PUPDR_PUPDx[pin_idx]
    WRITE_FIELD(GPIOx_PUPDR[port_idx], GPIOx_PUPDR_PUPDx[pin_idx], 0b00);
    // 5. Configure Alternate Function (AF12 = 12 for FMC)
    // Assumes mmio.h defines: GPIOx_AFRL/H[port_idx], GPIOx_AFRL/H_AFSELx[pin_idx or pin_idx-8]
    if (pin_idx < 8) {
        // Use AFRL register for pins 0-7
        WRITE_FIELD(GPIOx_AFRL[port_idx], GPIOx_AFRL_AFSELx[pin_idx], 12);
    } else {
        // Use AFRH register for pins 8-15
        WRITE_FIELD(GPIOx_AFRH[port_idx], GPIOx_AFRH_AFSELx[pin_idx - 8], 12);
    }
}

/**
 * @brief Configures GPIO pins for FMC SDRAM interface using mmio macros.
 * @note THIS IS A PLACEHOLDER FUNCTION!
 * You MUST adapt this function based on your specific STM32H745 pinout
 * and board schematic. Verify pin assignments, alternate functions (AF12),
 * speed (Very High Speed), and pull-up/pull-down settings (usually none).
 */
static void configure_fmc_gpio() {
    // 1. Enable Clocks for GPIO Ports C, D, E, F, G, H, I
    // (Verify these are all needed by your final defines and names match mmio.h)
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOCEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIODEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOEEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOFEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOGEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOHEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOIEN);
    // Add GPIOJEN or GPIOKEN if your schematic uses those for any FMC pins.

    simple_delay(10);

    // 2. Configure individual FMC pins
    config_fmc_pin(FMC_A0_PORT_IDX, FMC_A0_PIN_IDX);
    config_fmc_pin(FMC_A1_PORT_IDX, FMC_A1_PIN_IDX);
    config_fmc_pin(FMC_A2_PORT_IDX, FMC_A2_PIN_IDX);
    config_fmc_pin(FMC_A3_PORT_IDX, FMC_A3_PIN_IDX);
    config_fmc_pin(FMC_A4_PORT_IDX, FMC_A4_PIN_IDX);
    config_fmc_pin(FMC_A5_PORT_IDX, FMC_A5_PIN_IDX);
    config_fmc_pin(FMC_A6_PORT_IDX, FMC_A6_PIN_IDX);
    config_fmc_pin(FMC_A7_PORT_IDX, FMC_A7_PIN_IDX);
    config_fmc_pin(FMC_A8_PORT_IDX, FMC_A8_PIN_IDX);
    config_fmc_pin(FMC_A9_PORT_IDX, FMC_A9_PIN_IDX);
    config_fmc_pin(FMC_A10_PORT_IDX, FMC_A10_PIN_IDX);
    config_fmc_pin(FMC_A11_PORT_IDX, FMC_A11_PIN_IDX);

    config_fmc_pin(FMC_BA0_PORT_IDX, FMC_BA0_PIN_IDX);
    config_fmc_pin(FMC_BA1_PORT_IDX, FMC_BA1_PIN_IDX);

    config_fmc_pin(FMC_D0_PORT_IDX, FMC_D0_PIN_IDX);
    config_fmc_pin(FMC_D1_PORT_IDX, FMC_D1_PIN_IDX);
    config_fmc_pin(FMC_D2_PORT_IDX, FMC_D2_PIN_IDX);
    config_fmc_pin(FMC_D3_PORT_IDX, FMC_D3_PIN_IDX);
    config_fmc_pin(FMC_D4_PORT_IDX, FMC_D4_PIN_IDX);
    config_fmc_pin(FMC_D5_PORT_IDX, FMC_D5_PIN_IDX);
    config_fmc_pin(FMC_D6_PORT_IDX, FMC_D6_PIN_IDX);
    config_fmc_pin(FMC_D7_PORT_IDX, FMC_D7_PIN_IDX);
    config_fmc_pin(FMC_D8_PORT_IDX, FMC_D8_PIN_IDX);
    config_fmc_pin(FMC_D9_PORT_IDX, FMC_D9_PIN_IDX);
    config_fmc_pin(FMC_D10_PORT_IDX, FMC_D10_PIN_IDX);
    config_fmc_pin(FMC_D11_PORT_IDX, FMC_D11_PIN_IDX);
    config_fmc_pin(FMC_D12_PORT_IDX, FMC_D12_PIN_IDX);
    config_fmc_pin(FMC_D13_PORT_IDX, FMC_D13_PIN_IDX);
    config_fmc_pin(FMC_D14_PORT_IDX, FMC_D14_PIN_IDX);
    config_fmc_pin(FMC_D15_PORT_IDX, FMC_D15_PIN_IDX);
    config_fmc_pin(FMC_D16_PORT_IDX, FMC_D16_PIN_IDX);
    config_fmc_pin(FMC_D17_PORT_IDX, FMC_D17_PIN_IDX);
    config_fmc_pin(FMC_D18_PORT_IDX, FMC_D18_PIN_IDX);
    config_fmc_pin(FMC_D19_PORT_IDX, FMC_D19_PIN_IDX);
    config_fmc_pin(FMC_D20_PORT_IDX, FMC_D20_PIN_IDX);
    config_fmc_pin(FMC_D21_PORT_IDX, FMC_D21_PIN_IDX);
    config_fmc_pin(FMC_D22_PORT_IDX, FMC_D22_PIN_IDX);
    config_fmc_pin(FMC_D23_PORT_IDX, FMC_D23_PIN_IDX);
    config_fmc_pin(FMC_D24_PORT_IDX, FMC_D24_PIN_IDX);
    config_fmc_pin(FMC_D25_PORT_IDX, FMC_D25_PIN_IDX);
    config_fmc_pin(FMC_D26_PORT_IDX, FMC_D26_PIN_IDX);
    config_fmc_pin(FMC_D27_PORT_IDX, FMC_D27_PIN_IDX);
    config_fmc_pin(FMC_D28_PORT_IDX, FMC_D28_PIN_IDX);
    config_fmc_pin(FMC_D29_PORT_IDX, FMC_D29_PIN_IDX);
    config_fmc_pin(FMC_D30_PORT_IDX, FMC_D30_PIN_IDX);
    config_fmc_pin(FMC_D31_PORT_IDX, FMC_D31_PIN_IDX);

    config_fmc_pin(FMC_SDCLK_PORT_IDX, FMC_SDCLK_PIN_IDX);
    config_fmc_pin(FMC_SDCKE0_PORT_IDX, FMC_SDCKE0_PIN_IDX);
    config_fmc_pin(FMC_SDNE0_PORT_IDX, FMC_SDNE0_PIN_IDX);
    config_fmc_pin(FMC_SDNRAS_PORT_IDX, FMC_SDNRAS_PIN_IDX);
    config_fmc_pin(FMC_SDNCAS_PORT_IDX, FMC_SDNCAS_PIN_IDX);
    config_fmc_pin(FMC_SDNWE_PORT_IDX, FMC_SDNWE_PIN_IDX);

    config_fmc_pin(FMC_NBL0_PORT_IDX, FMC_NBL0_PIN_IDX);
    config_fmc_pin(FMC_NBL1_PORT_IDX, FMC_NBL1_PIN_IDX);
    config_fmc_pin(FMC_NBL2_PORT_IDX, FMC_NBL2_PIN_IDX);
    config_fmc_pin(FMC_NBL3_PORT_IDX, FMC_NBL3_PIN_IDX);
}

void config_fmc_pin(int port_index, int pin_index) {
    //port_index = index of the GPIO port
    //pin_index: index of the pin WITHIN the port

    //sets the mode of the pin to Alternate Function (0b10)
    //FMC uses alternate function mode to take control of the pin for memory interface signals
    //00 > input, 01 > output, 10 > alternate function, 11 > analog
    WRITE_FIELD(GPIOx_MODER[port_index], GPIOx_MODER_MODEx[pin_index], 0b10);
    //Clears the output for the pin, setting it to Push-Pull (0)
    CLR_FIELD(GPIOx_OTYPER[port_index], GPIOx_OTYPER_OTx[pin_index]);
    //Sets the output speed to very high speed (which is 0b11)
    // 00 > low speed, 01 > medium speed, 10 > high speed, 11 > very high speed
    WRITE_FIELD(GPIOx_OSPEEDR[port_index], GPIOx_OSPEEDR_OSPEEDx[pin_index], 0b11);
    //Configures the pull up and pull down registers to None (0b00)
    //external memory signals shouldn't have internate pull resistors to avoid interference
    WRITE_FIELD(GPIOx_PUPDR[port_index], GPIOx_PUPDR_PUPDx[pin_index], 0b00);
    //AFRL for pins 0-7, AFRH for pins 8-15 > this all represents alternate function selection
    if (pin_index < 8) {
        WRITE_FIELD(GPIOx_AFRL[port_index], GPIOx_AFRL_AFSELx[pin_index], 12);
    }
    else {
        WRITE_FIELD(GPIOx_AFRH[port_index], GPIOx_AFRH_AFSELx[pin_index - 8], 12);
    }
}
/**
 * @brief Waits until the FMC SDRAM controller is not busy.
 * @note mmio.h provided does not define FMC_SDSR_BUSY field, using direct access.
 */
void wait_fmc_busy() {
    // Check the BUSY flag (bit 5) in FMC_SDSR register
    // Poll until the flag is cleared (controller is ready)
    // Replace with READ_FIELD(FMC_SDSR, FMC_SDSR_BUSY) == 0 if available
    while ((*FMC_SDSR & (1 << 5)) != 0);
}

// --- Main SDRAM Initialization Function ---

/**
 * @brief Initializes the FMC peripheral for the MT48LC4M32B2 SDRAM using mmio macros.
 * @note Assumes fmc_ker_ck is configured (e.g., 200MHz), resulting in 100MHz SDCLK.
 * @note Assumes SDRAM is connected to FMC Bank 1 (controlled by SDCR1, SDTR1,
 * using signals SDNE0, SDCKE0). Bank 1 maps typically to 0xC0000000.
 * @note GPIO configuration (configure_fmc_gpio) MUST be adapted for the specific hardware.
 * @note This function assumes the necessary system clocks (including FMC kernel clock)
 * have already been configured elsewhere in the application startup code.
 */
void init_sdram(void) {
    SET_FIELD(RCC_AHB3ENR, RCC_AHB3ENR_FMCEN);
    simple_delay(10);
    configure_fmc_gpio();

    uint32_t sdcr1_temp = 0;
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_NC, 0);
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_NR, 1);
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_MWID, 2);
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_NB, 1);
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_CAS, 3);
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_WP, 0);
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_SDCLK, 2);
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_RBURST, 1);
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_RPIPE, 1);
    *FMC_SDCRx[1] = sdcr1_temp;

    uint32_t sdtr1_temp = 0;
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TMRD, SDRAM_TMRD_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TXSR, SDRAM_TXSR_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TRAS, SDRAM_TRAS_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TRC, SDRAM_TRC_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TWR, SDRAM_TWR_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TRP, SDRAM_TRP_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TRCD, SDRAM_TRCD_VAL);
    *FMC_SDTRx[1] = sdtr1_temp;

    uint32_t sdcmr_cmd = 0;
    sdcmr_cmd = 0;
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MODE, 1);
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_CTBx[1], 1);
    *FMC_SDCMR = sdcmr_cmd;

    simple_delay(20000);

    sdcmr_cmd = 0;
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MODE, 2);
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_CTBx[1], 1);
    *FMC_SDCMR = sdcmr_cmd;
    wait_fmc_busy();

    sdcmr_cmd = 0;
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MODE, 3);
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_CTBx[1], 1);
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_NRFS, 7);
    *FMC_SDCMR = sdcmr_cmd;
    wait_fmc_busy();

    sdcmr_cmd = 0;
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MODE, 4);
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_CTBx[1], 1);
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MRD, SDRAM_MODE_REGISTER_VAL);
    *FMC_SDCMR = sdcmr_cmd;
    wait_fmc_busy();

    uint32_t sdrtr_val = 0;
    sdrtr_val = WRITE_FIELD(&sdrtr_val, FMC_SDRTR_COUNT, SDRAM_REFRESH_COUNT_VAL);
    *FMC_SDRTR = sdrtr_val;
}