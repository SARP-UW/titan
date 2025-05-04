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
// Configuration: Burst Length=1 (001), CAS Latency=3 (011), Burst Type=Sequential (0),
//                Operating Mode=Standard (00), Write Burst Mode=Programmed Burst Length (0)
// Mode Register bits (based on SDRAM Fig 4): M11 M10 M9 M8 M7 M6 M5 M4 M3 M2 M1 M0
// Value:                                     0   0   0  0  0  0  1  1  0  0  0  1 = 0x0031
#define SDRAM_MODE_REGISTER_VAL 0x0031

// --- Helper Functions ---

/**
 * @brief Provides a simple blocking delay.
 * @param count Number of loop iterations. Adjust based on core clock speed.
 */
void simple_delay(volatile uint32_t count) {
    while(count--);
}

/**
 * @brief Configures GPIO pins for FMC SDRAM interface using mmio macros.
 * @note THIS IS A PLACEHOLDER FUNCTION!
 * You MUST adapt this function based on your specific STM32H745 pinout
 * and board schematic. Verify pin assignments, alternate functions (AF12),
 * speed (Very High Speed), and pull-up/pull-down settings (usually none).
 */
void configure_fmc_gpio() {
    // 1. Enable GPIO Clocks (Example: Ports C, D, E, F, G, H, I)
    // Assumes RCC_AHB4ENR_GPIOCEN, etc. fields are defined in mmio.h
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOCEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIODEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOEEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOFEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOGEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOHEN);
    SET_FIELD(RCC_AHB4ENR, RCC_AHB4ENR_GPIOIEN);
    // Add enables for other ports if used (e.g., GPIOJ, GPIOK)

    // --- IMPORTANT: Adapt the following configurations ---
    // Configure ALL necessary FMC pins:
    // FMC_A[0..12], FMC_D[0..31], FMC_BA[0..1], FMC_SDCLK, FMC_SDNWE,
    // FMC_SDNCAS, FMC_SDNRAS, FMC_SDNE0, FMC_SDCKE0, FMC_NBL[0..3]

    // Generic Pin Configuration Steps using mmio macros (Repeat for EACH pin):
    // int port_index = 5; // Example: 5 for GPIOF
    // int pin_index = 0;  // Example: 0 for PF0
    //
    // // 1. Set Mode to Alternate Function (0b10)
    // WRITE_FIELD(GPIOx_MODER[port_index], GPIOx_MODER_MODEx[pin_index], 0b10);
    // // 2. Set Output Type to Push-Pull (0)
    // CLR_FIELD(GPIOx_OTYPER[port_index], GPIOx_OTYPER_OTx[pin_index]);
    // // 3. Set Speed to Very High Speed (0b11)
    // WRITE_FIELD(GPIOx_OSPEEDR[port_index], GPIOx_OSPEEDR_OSPEEDx[pin_index], 0b11);
    // // 4. Set Pull-up/Pull-down to None (0b00)
    // WRITE_FIELD(GPIOx_PUPDR[port_index], GPIOx_PUPDR_PUPDx[pin_index], 0b00);
    // // 5. Configure Alternate Function (AF12 = 12)
    // if (pin_index < 8) {
    //     WRITE_FIELD(GPIOx_AFRL[port_index], GPIOx_AFRL_AFSELx[pin_index], 12);
    // } else {
    //     WRITE_FIELD(GPIOx_AFRH[port_index], GPIOx_AFRH_AFSELx[pin_index - 8], 12);
    // }

    // --- Example: Configure PF0 (assuming FMC_A0, GPIOF index 5) ---
    WRITE_FIELD(GPIOx_MODER[5], GPIOx_MODER_MODEx[0], 0b10); // AF Mode
    CLR_FIELD(GPIOx_OTYPER[5], GPIOx_OTYPER_OTx[0]);         // Push-Pull
    WRITE_FIELD(GPIOx_OSPEEDR[5], GPIOx_OSPEEDR_OSPEEDx[0], 0b11); // Very High Speed
    WRITE_FIELD(GPIOx_PUPDR[5], GPIOx_PUPDR_PUPDx[0], 0b00); // No Pull-up/down
    WRITE_FIELD(GPIOx_AFRL[5], GPIOx_AFRL_AFSELx[0], 12);    // AF12 (FMC)

    // --- Example: Configure PG8 (assuming FMC_SDCLK, GPIOG index 6) ---
    WRITE_FIELD(GPIOx_MODER[6], GPIOx_MODER_MODEx[8], 0b10); // AF Mode
    CLR_FIELD(GPIOx_OTYPER[6], GPIOx_OTYPER_OTx[8]);         // Push-Pull
    WRITE_FIELD(GPIOx_OSPEEDR[6], GPIOx_OSPEEDR_OSPEEDx[8], 0b11); // Very High Speed
    WRITE_FIELD(GPIOx_PUPDR[6], GPIOx_PUPDR_PUPDx[8], 0b00); // No Pull-up/down
    WRITE_FIELD(GPIOx_AFRH[6], GPIOx_AFRH_AFSELx[8 - 8], 12); // AF12 (FMC)

    // --- Example: Configure PE1 (assuming FMC_NBL1, GPIOE index 4) ---
    WRITE_FIELD(GPIOx_MODER[4], GPIOx_MODER_MODEx[1], 0b10); // AF Mode
    CLR_FIELD(GPIOx_OTYPER[4], GPIOx_OTYPER_OTx[1]);         // Push-Pull
    WRITE_FIELD(GPIOx_OSPEEDR[4], GPIOx_OSPEEDR_OSPEEDx[1], 0b11); // Very High Speed
    WRITE_FIELD(GPIOx_PUPDR[4], GPIOx_PUPDR_PUPDx[1], 0b00); // No Pull-up/down
    WRITE_FIELD(GPIOx_AFRL[4], GPIOx_AFRL_AFSELx[1], 12);    // AF12 (FMC)

    // --- Add configuration for ALL other required FMC pins here ---
    // --- using the mmio macros and correct port/pin indices ---
    // --- based on your specific hardware layout!            ---
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
    // 1. Enable FMC Peripheral Clock
    // Assumes RCC_AHB3ENR_FMCEN field is defined in mmio.h
    SET_FIELD(RCC_AHB3ENR, RCC_AHB3ENR_FMCEN);
    // Small delay after enabling clock
    simple_delay(10);

    // 2. Configure GPIO Pins for FMC SDRAM Interface
    configure_fmc_gpio(); // !! CRITICAL: Adapt this function for your board !!

    // 3. Configure SDRAM Control Register (FMC_SDCRx[1] for Bank 1)
    // Settings: Column=8 bits (0), Row=13 bits (2), Width=32 bits (2), Banks=4 (1),
    //           CAS=3 (3), Write Protect=Disabled (0), SDCLK=fmc_ker_ck/2 (2),
    //           Read Burst=Enabled (1), Read Pipe Delay=1 cycle (1)
    // Note: mmio.h uses index 1 for Bank 1, index 2 for Bank 2
    uint32_t sdcr1_temp = 0;
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_NC, 0);    // 8 bits column
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_NR, 2);    // 13 bits row
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_MWID, 2);  // 32 bits width
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_NB, 1);    // 4 internal banks
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_CAS, 3);   // CAS Latency 3
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_WP, 0);    // Write protection disabled
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_SDCLK, 2); // SDCLK = fmc_ker_ck / 2
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_RBURST, 1);// Read Burst enabled
    sdcr1_temp = WRITE_FIELD(&sdcr1_temp, FMC_SDCRx_RPIPE, 1); // Read pipe delay 1 cycle
    *FMC_SDCRx[1] = sdcr1_temp; // Write configured value to Bank 1 register

    // Configure SDCR2 (Bank 2) if needed, or leave at reset default if unused.
    // *FMC_SDCRx[2] = sdcr1_temp; // Example if Bank 2 used (RBURST/RPIPE/SDCLK ignored)

    // 4. Configure SDRAM Timing Register (FMC_SDTRx[1] for Bank 1)
    // Timings calculated for 100MHz SDCLK (10ns period), values are (cycles - 1)
    uint32_t sdtr1_temp = 0;
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TMRD, SDRAM_TMRD_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TXSR, SDRAM_TXSR_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TRAS, SDRAM_TRAS_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TRC, SDRAM_TRC_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TWR, SDRAM_TWR_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TRP, SDRAM_TRP_VAL);
    sdtr1_temp = WRITE_FIELD(&sdtr1_temp, FMC_SDTRx_TRCD, SDRAM_TRCD_VAL);
    *FMC_SDTRx[1] = sdtr1_temp; // Write configured value to Bank 1 register

    // Configure SDTR2 (Bank 2) if needed. Note TRC/TRP are ignored by HW here.
    // *FMC_SDTRx[2] = sdtr1_temp; // Example if Bank 2 used

    // --- SDRAM Initialization Sequence ---
    // Reference: FMC Datasheet Section 23.9.3 / SDRAM Datasheet Initialization

    // 5. Issue Clock Configuration Enable command (MODE=1) to Bank 1 (CTB1=1)
    // This starts the SDRAM clock (SDCKE goes high)
    uint32_t sdcmr_cmd = 0;
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MODE, 1);   // Mode = Clock Enable
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_CTBx[1], 1); // Target Bank 1
    *FMC_SDCMR = sdcmr_cmd;
    // SDCKE should now be high, SDCLK should be running

    // 6. Wait for Stable Power and Clock (> 100µs recommended by SDRAM datasheet)
    // Adjust delay based on system clock frequency (assuming ~4 cycles per loop iteration)
    // Example: If SysClk = 400MHz, 100us = 40000 cycles. Delay count ~ 10000
    // Increase delay significantly for safety margin if SysClk is lower.
    simple_delay(20000); // Adjust this value based on actual SysClk!

    // 7. Issue PALL (Precharge All) command (MODE=2) to Bank 1 (CTB1=1)
    sdcmr_cmd = 0;
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MODE, 2);   // Mode = PALL
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_CTBx[1], 1); // Target Bank 1
    *FMC_SDCMR = sdcmr_cmd;

    // Wait for PALL command to complete by polling the BUSY flag in SDSR
    wait_fmc_busy();
    // Optional short delay for tRP (2 cycles @ 100MHz = 20ns) - likely covered by polling latency
    // simple_delay(10);

    // 8. Issue Auto-Refresh commands (MODE=3)
    // Issue 8 consecutive Auto-refresh commands (NRFS = 7) to Bank 1 (CTB1=1)
    sdcmr_cmd = 0;
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MODE, 3);   // Mode = Auto-Refresh
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_CTBx[1], 1); // Target Bank 1
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_NRFS, 7);   // NRFS = 7 (8 cycles)
    *FMC_SDCMR = sdcmr_cmd;

    // Wait for Auto-Refresh sequence to complete (poll BUSY flag)
    wait_fmc_busy();

    // 9. Issue Load Mode Register command (MODE=4) to Bank 1 (CTB1=1)
    // Program SDRAM internal Mode Register: BL=1, CL=3, etc. (Value: 0x0031)
    sdcmr_cmd = 0;
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MODE, 4);   // Mode = Load Mode Register
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_CTBx[1], 1); // Target Bank 1
    sdcmr_cmd = WRITE_FIELD(&sdcmr_cmd, FMC_SDCMR_MRD, SDRAM_MODE_REGISTER_VAL); // Mode Register Data
    *FMC_SDCMR = sdcmr_cmd;

    // Wait for Load Mode Register command to complete (poll BUSY flag)
    wait_fmc_busy();
    // Optional short delay for tMRD (2 cycles @ 100MHz = 20ns)
    // simple_delay(10);

    // 10. Configure SDRAM Refresh Rate Timer (FMC_SDRTR)
    // Set the refresh count. COUNT field starts at bit 1.
    // Enable Refresh Error Interrupt if desired (REIE = bit 14)
    uint32_t sdrtr_val = 0;
    sdrtr_val = WRITE_FIELD(&sdrtr_val, FMC_SDRTR_COUNT, SDRAM_REFRESH_COUNT_VAL);
    // sdrtr_val = WRITE_FIELD(&sdrtr_val, FMC_SDRTR_REIE, 1); // Optionally enable refresh error interrupt
    *FMC_SDRTR = sdrtr_val;

    // SDRAM Initialization is Complete.
    // FMC Bank 1 (typically 0xC0000000 - 0xCFFFFFFF) should now be accessible
    // as memory-mapped SDRAM.
}

