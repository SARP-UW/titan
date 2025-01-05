/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2024 UW SARP
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * 
 * @file src/port/GCC_STM32H745ZI/device/rcc_reg.h
 * @authors Aaron McBride
 * @brief Register reference for the RCC peripheral.
 */

#ifndef SRC_PORT_GCC_STM32H745ZI_DEVICE_RCC_REG_H
#define SRC_PORT_GCC_STM32H745ZI_DEVICE_RCC_REG_H

  #include <stdint.h>

  #if defined(__cplusplus)
    extern "C" {
  #endif

    /**
     * @note The following code was obtained from STMicroelectronics.
     * @see https://github.com/STMicroelectronics/cmsis-device-h7/blob/master/Include/stm32h745xx.h
     */

    typedef struct
    {
    volatile uint32_t CR;             /*!< RCC clock control register,                                              Address offset: 0x00  */
    volatile uint32_t HSICFGR;        /*!< HSI Clock Calibration Register,                                          Address offset: 0x04  */
    volatile uint32_t CRRCR;          /*!< Clock Recovery RC  Register,                                             Address offset: 0x08  */
    volatile uint32_t CSICFGR;        /*!< CSI Clock Calibration Register,                                          Address offset: 0x0C  */
    volatile uint32_t CFGR;           /*!< RCC clock configuration register,                                        Address offset: 0x10  */
    uint32_t     RESERVED1;       /*!< Reserved,                                                                Address offset: 0x14  */
    volatile uint32_t D1CFGR;         /*!< RCC Domain 1 configuration register,                                     Address offset: 0x18  */
    volatile uint32_t D2CFGR;         /*!< RCC Domain 2 configuration register,                                     Address offset: 0x1C  */
    volatile uint32_t D3CFGR;         /*!< RCC Domain 3 configuration register,                                     Address offset: 0x20  */
    uint32_t     RESERVED2;       /*!< Reserved,                                                                Address offset: 0x24  */
    volatile uint32_t PLLCKSELR;      /*!< RCC PLLs Clock Source Selection Register,                                Address offset: 0x28  */
    volatile uint32_t PLLCFGR;        /*!< RCC PLLs  Configuration Register,                                        Address offset: 0x2C  */
    volatile uint32_t PLL1DIVR;       /*!< RCC PLL1 Dividers Configuration Register,                                Address offset: 0x30  */
    volatile uint32_t PLL1FRACR;      /*!< RCC PLL1 Fractional Divider Configuration Register,                      Address offset: 0x34  */
    volatile uint32_t PLL2DIVR;       /*!< RCC PLL2 Dividers Configuration Register,                                Address offset: 0x38  */
    volatile uint32_t PLL2FRACR;      /*!< RCC PLL2 Fractional Divider Configuration Register,                      Address offset: 0x3C  */
    volatile uint32_t PLL3DIVR;       /*!< RCC PLL3 Dividers Configuration Register,                                Address offset: 0x40  */
    volatile uint32_t PLL3FRACR;      /*!< RCC PLL3 Fractional Divider Configuration Register,                      Address offset: 0x44  */
    uint32_t      RESERVED3;      /*!< Reserved,                                                                Address offset: 0x48  */
    volatile uint32_t  D1CCIPR;       /*!< RCC Domain 1 Kernel Clock Configuration Register                         Address offset: 0x4C  */
    volatile uint32_t  D2CCIP1R;      /*!< RCC Domain 2 Kernel Clock Configuration Register                         Address offset: 0x50  */
    volatile uint32_t  D2CCIP2R;      /*!< RCC Domain 2 Kernel Clock Configuration Register                         Address offset: 0x54  */
    volatile uint32_t  D3CCIPR;       /*!< RCC Domain 3 Kernel Clock Configuration Register                         Address offset: 0x58  */
    uint32_t      RESERVED4;      /*!< Reserved,                                                                Address offset: 0x5C  */
    volatile uint32_t  CIER;          /*!< RCC Clock Source Interrupt Enable Register                               Address offset: 0x60  */
    volatile uint32_t  CIFR;          /*!< RCC Clock Source Interrupt Flag Register                                 Address offset: 0x64  */
    volatile uint32_t  CICR;          /*!< RCC Clock Source Interrupt Clear Register                                Address offset: 0x68  */
    uint32_t     RESERVED5;       /*!< Reserved,                                                                Address offset: 0x6C  */
    volatile uint32_t  BDCR;          /*!< RCC Vswitch Backup Domain Control Register,                              Address offset: 0x70  */
    volatile uint32_t  CSR;           /*!< RCC clock control & status register,                                     Address offset: 0x74  */
    uint32_t     RESERVED6;       /*!< Reserved,                                                                Address offset: 0x78  */
    volatile uint32_t AHB3RSTR;       /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x7C  */
    volatile uint32_t AHB1RSTR;       /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x80  */
    volatile uint32_t AHB2RSTR;       /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x84  */
    volatile uint32_t AHB4RSTR;       /*!< RCC AHB4 peripheral reset register,                                      Address offset: 0x88  */
    volatile uint32_t APB3RSTR;       /*!< RCC APB3 peripheral reset register,                                      Address offset: 0x8C  */
    volatile uint32_t APB1LRSTR;      /*!< RCC APB1 peripheral reset Low Word register,                             Address offset: 0x90  */
    volatile uint32_t APB1HRSTR;      /*!< RCC APB1 peripheral reset High Word register,                            Address offset: 0x94  */
    volatile uint32_t APB2RSTR;       /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x98  */
    volatile uint32_t APB4RSTR;       /*!< RCC APB4 peripheral reset register,                                      Address offset: 0x9C  */
    volatile uint32_t GCR;            /*!< RCC RCC Global Control  Register,                                        Address offset: 0xA0  */
    uint32_t     RESERVED8;       /*!< Reserved,                                                                Address offset: 0xA4  */
    volatile uint32_t D3AMR;          /*!< RCC Domain 3 Autonomous Mode Register,                                   Address offset: 0xA8  */
    uint32_t     RESERVED11[9];    /*!< Reserved, 0xAC-0xCC                                                      Address offset: 0xAC  */
    volatile uint32_t RSR;            /*!< RCC Reset status register,                                               Address offset: 0xD0  */
    volatile uint32_t AHB3ENR;        /*!< RCC AHB3 peripheral clock  register,                                     Address offset: 0xD4  */
    volatile uint32_t AHB1ENR;        /*!< RCC AHB1 peripheral clock  register,                                     Address offset: 0xD8  */
    volatile uint32_t AHB2ENR;        /*!< RCC AHB2 peripheral clock  register,                                     Address offset: 0xDC  */
    volatile uint32_t AHB4ENR;        /*!< RCC AHB4 peripheral clock  register,                                     Address offset: 0xE0  */
    volatile uint32_t APB3ENR;        /*!< RCC APB3 peripheral clock  register,                                     Address offset: 0xE4  */
    volatile uint32_t APB1LENR;       /*!< RCC APB1 peripheral clock  Low Word register,                            Address offset: 0xE8  */
    volatile uint32_t APB1HENR;       /*!< RCC APB1 peripheral clock  High Word register,                           Address offset: 0xEC  */
    volatile uint32_t APB2ENR;        /*!< RCC APB2 peripheral clock  register,                                     Address offset: 0xF0  */
    volatile uint32_t APB4ENR;        /*!< RCC APB4 peripheral clock  register,                                     Address offset: 0xF4  */
    uint32_t      RESERVED12;      /*!< Reserved,                                                                Address offset: 0xF8  */
    volatile uint32_t AHB3LPENR;      /*!< RCC AHB3 peripheral sleep clock  register,                               Address offset: 0xFC  */
    volatile uint32_t AHB1LPENR;      /*!< RCC AHB1 peripheral sleep clock  register,                               Address offset: 0x100 */
    volatile uint32_t AHB2LPENR;      /*!< RCC AHB2 peripheral sleep clock  register,                               Address offset: 0x104 */
    volatile uint32_t AHB4LPENR;      /*!< RCC AHB4 peripheral sleep clock  register,                               Address offset: 0x108 */
    volatile uint32_t APB3LPENR;      /*!< RCC APB3 peripheral sleep clock  register,                               Address offset: 0x10C */
    volatile uint32_t APB1LLPENR;     /*!< RCC APB1 peripheral sleep clock  Low Word register,                      Address offset: 0x110 */
    volatile uint32_t APB1HLPENR;     /*!< RCC APB1 peripheral sleep clock  High Word register,                     Address offset: 0x114 */
    volatile uint32_t APB2LPENR;      /*!< RCC APB2 peripheral sleep clock  register,                               Address offset: 0x118 */
    volatile uint32_t APB4LPENR;      /*!< RCC APB4 peripheral sleep clock  register,                               Address offset: 0x11C */
    uint32_t     RESERVED13[4];   /*!< Reserved, 0x120-0x12C                                                    Address offset: 0x120 */
    
    } RCC_TypeDef;

    typedef struct
    {
      volatile uint32_t RSR;          /*!< RCC Reset status register,                                               Address offset: 0x00 */
      volatile uint32_t AHB3ENR;      /*!< RCC AHB3 peripheral clock  register,                            Address offset: 0x04 */
      volatile uint32_t AHB1ENR;      /*!< RCC AHB1 peripheral clock  register,                            Address offset: 0x08 */
      volatile uint32_t AHB2ENR;      /*!< RCC AHB2 peripheral clock  register,                            Address offset: 0x0C */
      volatile uint32_t AHB4ENR;      /*!< RCC AHB4 peripheral clock  register,                            Address offset: 0x10 */
      volatile uint32_t APB3ENR;      /*!< RCC APB3 peripheral clock  register,                            Address offset: 0x14 */
      volatile uint32_t APB1LENR;     /*!< RCC APB1 peripheral clock  Low Word register,                   Address offset: 0x18 */
      volatile uint32_t APB1HENR;     /*!< RCC APB1 peripheral clock  High Word register,                  Address offset: 0x1C */
      volatile uint32_t APB2ENR;      /*!< RCC APB2 peripheral clock  register,                            Address offset: 0x20 */
      volatile uint32_t APB4ENR;      /*!< RCC APB4 peripheral clock  register,                            Address offset: 0x24 */
      uint32_t      RESERVED9;    /*!< Reserved,                                                       Address offset: 0x28 */
      volatile uint32_t AHB3LPENR;    /*!< RCC AHB3 peripheral sleep clock  register,                      Address offset: 0x3C */
      volatile uint32_t AHB1LPENR;    /*!< RCC AHB1 peripheral sleep clock  register,                      Address offset: 0x40 */
      volatile uint32_t AHB2LPENR;    /*!< RCC AHB2 peripheral sleep clock  register,                      Address offset: 0x44 */
      volatile uint32_t AHB4LPENR;    /*!< RCC AHB4 peripheral sleep clock  register,                      Address offset: 0x48 */
      volatile uint32_t APB3LPENR;    /*!< RCC APB3 peripheral sleep clock  register,                      Address offset: 0x4C */
      volatile uint32_t APB1LLPENR;   /*!< RCC APB1 peripheral sleep clock  Low Word register,             Address offset: 0x50 */
      volatile uint32_t APB1HLPENR;   /*!< RCC APB1 peripheral sleep clock  High Word register,            Address offset: 0x54 */
      volatile uint32_t APB2LPENR;    /*!< RCC APB2 peripheral sleep clock  register,                      Address offset: 0x58 */
      volatile uint32_t APB4LPENR;    /*!< RCC APB4 peripheral sleep clock  register,                      Address offset: 0x5C */
      uint32_t     RESERVED10[4]; /*!< Reserved, 0x60-0x6C                                             Address offset: 0x60 */

    } RCC_Core_TypeDef;

    #define RCC_BASE            (0x58024400UL)       /*!< Address of RCC register block. */
    #define RCC_C1_BASE         (RCC_BASE + 0x130UL) /*!< Address of RCC_C1 register block.*/
    #define RCC_C2_BASE         (RCC_BASE + 0x190UL) /*!< Address of RCC_C2 register block. */

    #define RCC                 ((RCC_TypeDef *)RCC_BASE)         /*!< RCC register block */
    #define RCC_C1              ((RCC_Core_TypeDef *)RCC_C1_BASE) /*!< RCC_C1 register block */
    #define RCC_C2              ((RCC_Core_TypeDef *)RCC_C2_BASE) /*!< RCC_C2 register block */

    #define RCC_CR_HSION_Pos                       (0U)
    #define RCC_CR_HSION_Msk                       (0x1UL << RCC_CR_HSION_Pos)     /*!< 0x00000001 */
    #define RCC_CR_HSION                           RCC_CR_HSION_Msk                /*!< Internal High Speed clock enable */
    #define RCC_CR_HSIKERON_Pos                    (1U)
    #define RCC_CR_HSIKERON_Msk                    (0x1UL << RCC_CR_HSIKERON_Pos)  /*!< 0x00000002 */
    #define RCC_CR_HSIKERON                        RCC_CR_HSIKERON_Msk             /*!< Internal High Speed clock enable for some IPs Kernel */
    #define RCC_CR_HSIRDY_Pos                      (2U)
    #define RCC_CR_HSIRDY_Msk                      (0x1UL << RCC_CR_HSIRDY_Pos)    /*!< 0x00000004 */
    #define RCC_CR_HSIRDY                          RCC_CR_HSIRDY_Msk               /*!< Internal High Speed clock ready flag */
    #define RCC_CR_HSIDIV_Pos                      (3U)
    #define RCC_CR_HSIDIV_Msk                      (0x3UL << RCC_CR_HSIDIV_Pos)    /*!< 0x00000018 */
    #define RCC_CR_HSIDIV                          RCC_CR_HSIDIV_Msk               /*!< Internal High Speed clock divider selection */
    #define RCC_CR_HSIDIV_1                        (0x0UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000000 */
    #define RCC_CR_HSIDIV_2                        (0x1UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000008 */
    #define RCC_CR_HSIDIV_4                        (0x2UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000010 */
    #define RCC_CR_HSIDIV_8                        (0x3UL << RCC_CR_HSIDIV_Pos)     /*!< 0x00000018 */

    #define RCC_CR_HSIDIVF_Pos                     (5U)
    #define RCC_CR_HSIDIVF_Msk                     (0x1UL << RCC_CR_HSIDIVF_Pos)   /*!< 0x00000020 */
    #define RCC_CR_HSIDIVF                         RCC_CR_HSIDIVF_Msk              /*!< HSI Divider flag */
    #define RCC_CR_CSION_Pos                       (7U)
    #define RCC_CR_CSION_Msk                       (0x1UL << RCC_CR_CSION_Pos)     /*!< 0x00000080 */
    #define RCC_CR_CSION                           RCC_CR_CSION_Msk                /*!< The Internal RC 4MHz oscillator clock enable */
    #define RCC_CR_CSIRDY_Pos                      (8U)
    #define RCC_CR_CSIRDY_Msk                      (0x1UL << RCC_CR_CSIRDY_Pos)    /*!< 0x00000100 */
    #define RCC_CR_CSIRDY                          RCC_CR_CSIRDY_Msk               /*!< The Internal RC 4MHz oscillator clock ready */
    #define RCC_CR_CSIKERON_Pos                    (9U)
    #define RCC_CR_CSIKERON_Msk                    (0x1UL << RCC_CR_CSIKERON_Pos)  /*!< 0x00000200 */
    #define RCC_CR_CSIKERON                        RCC_CR_CSIKERON_Msk             /*!< Internal RC 4MHz oscillator clock enable for some IPs Kernel */
    #define RCC_CR_HSI48ON_Pos                     (12U)
    #define RCC_CR_HSI48ON_Msk                     (0x1UL << RCC_CR_HSI48ON_Pos)   /*!< 0x00001000 */
    #define RCC_CR_HSI48ON                         RCC_CR_HSI48ON_Msk              /*!< HSI48 clock enable clock enable  */
    #define RCC_CR_HSI48RDY_Pos                    (13U)
    #define RCC_CR_HSI48RDY_Msk                    (0x1UL << RCC_CR_HSI48RDY_Pos)  /*!< 0x00002000 */
    #define RCC_CR_HSI48RDY                        RCC_CR_HSI48RDY_Msk             /*!< HSI48 clock ready */

    #define RCC_CR_D1CKRDY_Pos                     (14U)
    #define RCC_CR_D1CKRDY_Msk                     (0x1UL << RCC_CR_D1CKRDY_Pos)   /*!< 0x00004000 */
    #define RCC_CR_D1CKRDY                         RCC_CR_D1CKRDY_Msk              /*!< D1 domain clocks ready flag  */
    #define RCC_CR_D2CKRDY_Pos                     (15U)
    #define RCC_CR_D2CKRDY_Msk                     (0x1UL << RCC_CR_D2CKRDY_Pos)   /*!< 0x00008000 */
    #define RCC_CR_D2CKRDY                         RCC_CR_D2CKRDY_Msk              /*!< D2 domain clocks ready flag */

    #define RCC_CR_HSEON_Pos                       (16U)
    #define RCC_CR_HSEON_Msk                       (0x1UL << RCC_CR_HSEON_Pos)     /*!< 0x00010000 */
    #define RCC_CR_HSEON                           RCC_CR_HSEON_Msk                /*!< External High Speed clock enable */
    #define RCC_CR_HSERDY_Pos                      (17U)
    #define RCC_CR_HSERDY_Msk                      (0x1UL << RCC_CR_HSERDY_Pos)    /*!< 0x00020000 */
    #define RCC_CR_HSERDY                          RCC_CR_HSERDY_Msk               /*!< External High Speed clock ready */
    #define RCC_CR_HSEBYP_Pos                      (18U)
    #define RCC_CR_HSEBYP_Msk                      (0x1UL << RCC_CR_HSEBYP_Pos)    /*!< 0x00040000 */
    #define RCC_CR_HSEBYP                          RCC_CR_HSEBYP_Msk               /*!< External High Speed clock Bypass */
    #define RCC_CR_CSSHSEON_Pos                    (19U)
    #define RCC_CR_CSSHSEON_Msk                    (0x1UL << RCC_CR_CSSHSEON_Pos)  /*!< 0x00080000 */
    #define RCC_CR_CSSHSEON                        RCC_CR_CSSHSEON_Msk             /*!< HSE Clock security System enable */


    #define RCC_CR_PLL1ON_Pos                      (24U)
    #define RCC_CR_PLL1ON_Msk                      (0x1UL << RCC_CR_PLL1ON_Pos)    /*!< 0x01000000 */
    #define RCC_CR_PLL1ON                          RCC_CR_PLL1ON_Msk               /*!< System PLL1 clock enable */
    #define RCC_CR_PLL1RDY_Pos                     (25U)
    #define RCC_CR_PLL1RDY_Msk                     (0x1UL << RCC_CR_PLL1RDY_Pos)   /*!< 0x02000000 */
    #define RCC_CR_PLL1RDY                         RCC_CR_PLL1RDY_Msk              /*!< System PLL1 clock ready */
    #define RCC_CR_PLL2ON_Pos                      (26U)
    #define RCC_CR_PLL2ON_Msk                      (0x1UL << RCC_CR_PLL2ON_Pos)    /*!< 0x04000000 */
    #define RCC_CR_PLL2ON                          RCC_CR_PLL2ON_Msk               /*!< System PLL2 clock enable */
    #define RCC_CR_PLL2RDY_Pos                     (27U)
    #define RCC_CR_PLL2RDY_Msk                     (0x1UL << RCC_CR_PLL2RDY_Pos)   /*!< 0x08000000 */
    #define RCC_CR_PLL2RDY                         RCC_CR_PLL2RDY_Msk              /*!< System PLL2 clock ready */
    #define RCC_CR_PLL3ON_Pos                      (28U)
    #define RCC_CR_PLL3ON_Msk                      (0x1UL << RCC_CR_PLL3ON_Pos)    /*!< 0x10000000 */
    #define RCC_CR_PLL3ON                          RCC_CR_PLL3ON_Msk               /*!< System PLL3 clock enable */
    #define RCC_CR_PLL3RDY_Pos                     (29U)
    #define RCC_CR_PLL3RDY_Msk                     (0x1UL << RCC_CR_PLL3RDY_Pos)   /*!< 0x20000000 */
    #define RCC_CR_PLL3RDY                         RCC_CR_PLL3RDY_Msk              /*!< System PLL3 clock ready */

    /*Legacy */
    #define RCC_CR_PLLON_Pos                       (24U)
    #define RCC_CR_PLLON_Msk                       (0x1UL << RCC_CR_PLLON_Pos)     /*!< 0x01000000 */
    #define RCC_CR_PLLON                           RCC_CR_PLLON_Msk                /*!< System PLL clock enable */
    #define RCC_CR_PLLRDY_Pos                      (25U)
    #define RCC_CR_PLLRDY_Msk                      (0x1UL << RCC_CR_PLLRDY_Pos)    /*!< 0x02000000 */
    #define RCC_CR_PLLRDY                          RCC_CR_PLLRDY_Msk               /*!< System PLL clock ready */

    /********************  Bit definition for RCC_HSICFGR register  ***************/
    /*!< HSICAL configuration */
    #define RCC_HSICFGR_HSICAL_Pos                 (0U)
    #define RCC_HSICFGR_HSICAL_Msk                 (0xFFFUL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000FFF */
    #define RCC_HSICFGR_HSICAL                     RCC_HSICFGR_HSICAL_Msk          /*!< HSICAL[11:0] bits */
    #define RCC_HSICFGR_HSICAL_0                   (0x001UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000001 */
    #define RCC_HSICFGR_HSICAL_1                   (0x002UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000002 */
    #define RCC_HSICFGR_HSICAL_2                   (0x004UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000004 */
    #define RCC_HSICFGR_HSICAL_3                   (0x008UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000008 */
    #define RCC_HSICFGR_HSICAL_4                   (0x010UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000010 */
    #define RCC_HSICFGR_HSICAL_5                   (0x020UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000020 */
    #define RCC_HSICFGR_HSICAL_6                   (0x040UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000040 */
    #define RCC_HSICFGR_HSICAL_7                   (0x080UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000080 */
    #define RCC_HSICFGR_HSICAL_8                   (0x100UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000100 */
    #define RCC_HSICFGR_HSICAL_9                   (0x200UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000200 */
    #define RCC_HSICFGR_HSICAL_10                  (0x400UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000400 */
    #define RCC_HSICFGR_HSICAL_11                  (0x800UL << RCC_HSICFGR_HSICAL_Pos) /*!< 0x00000800 */

    /*!< HSITRIM configuration */
    #define RCC_HSICFGR_HSITRIM_Pos                (24U)
    #define RCC_HSICFGR_HSITRIM_Msk                (0x7FUL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x7F000000 */
    #define RCC_HSICFGR_HSITRIM                    RCC_HSICFGR_HSITRIM_Msk         /*!< HSITRIM[6:0] bits */
    #define RCC_HSICFGR_HSITRIM_0                  (0x01UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x01000000 */
    #define RCC_HSICFGR_HSITRIM_1                  (0x02UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x02000000 */
    #define RCC_HSICFGR_HSITRIM_2                  (0x04UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x04000000 */
    #define RCC_HSICFGR_HSITRIM_3                  (0x08UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x08000000 */
    #define RCC_HSICFGR_HSITRIM_4                  (0x10UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x10000000 */
    #define RCC_HSICFGR_HSITRIM_5                  (0x20UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x20000000 */
    #define RCC_HSICFGR_HSITRIM_6                  (0x40UL << RCC_HSICFGR_HSITRIM_Pos) /*!< 0x40000000 */


    /********************  Bit definition for RCC_CRRCR register  *****************/

    /*!< HSI48CAL configuration */
    #define RCC_CRRCR_HSI48CAL_Pos                 (0U)
    #define RCC_CRRCR_HSI48CAL_Msk                 (0x3FFUL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x000003FF */
    #define RCC_CRRCR_HSI48CAL                     RCC_CRRCR_HSI48CAL_Msk          /*!< HSI48CAL[9:0] bits */
    #define RCC_CRRCR_HSI48CAL_0                   (0x001UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000001 */
    #define RCC_CRRCR_HSI48CAL_1                   (0x002UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000002 */
    #define RCC_CRRCR_HSI48CAL_2                   (0x004UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000004 */
    #define RCC_CRRCR_HSI48CAL_3                   (0x008UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000008 */
    #define RCC_CRRCR_HSI48CAL_4                   (0x010UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000010 */
    #define RCC_CRRCR_HSI48CAL_5                   (0x020UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000020 */
    #define RCC_CRRCR_HSI48CAL_6                   (0x040UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000040 */
    #define RCC_CRRCR_HSI48CAL_7                   (0x080UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000080 */
    #define RCC_CRRCR_HSI48CAL_8                   (0x100UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000100 */
    #define RCC_CRRCR_HSI48CAL_9                   (0x200UL << RCC_CRRCR_HSI48CAL_Pos) /*!< 0x00000200 */


    /********************  Bit definition for RCC_CSICFGR register  *****************/
    /*!< CSICAL configuration */
    #define RCC_CSICFGR_CSICAL_Pos                 (0U)
    #define RCC_CSICFGR_CSICAL_Msk                 (0xFFUL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x000000FF */
    #define RCC_CSICFGR_CSICAL                     RCC_CSICFGR_CSICAL_Msk          /*!< CSICAL[7:0] bits */
    #define RCC_CSICFGR_CSICAL_0                   (0x01UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000001 */
    #define RCC_CSICFGR_CSICAL_1                   (0x02UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000002 */
    #define RCC_CSICFGR_CSICAL_2                   (0x04UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000004 */
    #define RCC_CSICFGR_CSICAL_3                   (0x08UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000008 */
    #define RCC_CSICFGR_CSICAL_4                   (0x10UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000010 */
    #define RCC_CSICFGR_CSICAL_5                   (0x20UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000020 */
    #define RCC_CSICFGR_CSICAL_6                   (0x40UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000040 */
    #define RCC_CSICFGR_CSICAL_7                   (0x80UL << RCC_CSICFGR_CSICAL_Pos) /*!< 0x00000080 */

    /*!< CSITRIM configuration */
    #define RCC_CSICFGR_CSITRIM_Pos                (24U)
    #define RCC_CSICFGR_CSITRIM_Msk                (0x3FUL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x3F000000 */
    #define RCC_CSICFGR_CSITRIM                    RCC_CSICFGR_CSITRIM_Msk         /*!< CSITRIM[5:0] bits */
    #define RCC_CSICFGR_CSITRIM_0                  (0x01UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x01000000 */
    #define RCC_CSICFGR_CSITRIM_1                  (0x02UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x02000000 */
    #define RCC_CSICFGR_CSITRIM_2                  (0x04UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x04000000 */
    #define RCC_CSICFGR_CSITRIM_3                  (0x08UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x08000000 */
    #define RCC_CSICFGR_CSITRIM_4                  (0x10UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x10000000 */
    #define RCC_CSICFGR_CSITRIM_5                  (0x20UL << RCC_CSICFGR_CSITRIM_Pos) /*!< 0x20000000 */

    /********************  Bit definition for RCC_CFGR register  ******************/
    /*!< SW configuration */
    #define RCC_CFGR_SW_Pos                        (0U)
    #define RCC_CFGR_SW_Msk                        (0x7UL << RCC_CFGR_SW_Pos)           /*!< 0x00000007 */
    #define RCC_CFGR_SW                            RCC_CFGR_SW_Msk                     /*!< SW[2:0] bits (System clock Switch) */
    #define RCC_CFGR_SW_0                          (0x1UL << RCC_CFGR_SW_Pos)           /*!< 0x00000001 */
    #define RCC_CFGR_SW_1                          (0x2UL << RCC_CFGR_SW_Pos)           /*!< 0x00000002 */
    #define RCC_CFGR_SW_2                          (0x4UL << RCC_CFGR_SW_Pos)           /*!< 0x00000004 */

    #define RCC_CFGR_SW_HSI                        (0x00000000UL)                       /*!< HSI selection as system clock */
    #define RCC_CFGR_SW_CSI                        (0x00000001UL)                       /*!< CSI selection as system clock */
    #define RCC_CFGR_SW_HSE                        (0x00000002UL)                       /*!< HSE selection as system clock */
    #define RCC_CFGR_SW_PLL1                       (0x00000003UL)                       /*!< PLL1 selection as system clock */

    /*!< SWS configuration */
    #define RCC_CFGR_SWS_Pos                       (3U)
    #define RCC_CFGR_SWS_Msk                       (0x7UL << RCC_CFGR_SWS_Pos)          /*!< 0x00000038 */
    #define RCC_CFGR_SWS                           RCC_CFGR_SWS_Msk                    /*!< SWS[2:0] bits (System Clock Switch Status) */
    #define RCC_CFGR_SWS_0                         (0x1UL << RCC_CFGR_SWS_Pos)          /*!< 0x00000008 */
    #define RCC_CFGR_SWS_1                         (0x2UL << RCC_CFGR_SWS_Pos)          /*!< 0x00000010 */
    #define RCC_CFGR_SWS_2                         (0x4UL << RCC_CFGR_SWS_Pos)          /*!< 0x00000020 */

    #define RCC_CFGR_SWS_HSI                       (0x00000000UL)                       /*!< HSI used as system clock */
    #define RCC_CFGR_SWS_CSI                       (0x00000008UL)                       /*!< CSI used as system clock */
    #define RCC_CFGR_SWS_HSE                       (0x00000010UL)                       /*!< HSE used as system clock */
    #define RCC_CFGR_SWS_PLL1                      (0x00000018UL)                       /*!< PLL1 used as system clock */

    #define RCC_CFGR_STOPWUCK_Pos                  (6U)
    #define RCC_CFGR_STOPWUCK_Msk                  (0x1UL << RCC_CFGR_STOPWUCK_Pos)     /*!< 0x00000040 */
    #define RCC_CFGR_STOPWUCK                      RCC_CFGR_STOPWUCK_Msk                /*!< Wake Up from stop and CSS backup clock selection */

    #define RCC_CFGR_STOPKERWUCK_Pos               (7U)
    #define RCC_CFGR_STOPKERWUCK_Msk               (0x1UL << RCC_CFGR_STOPKERWUCK_Pos)  /*!< 0x00000080 */
    #define RCC_CFGR_STOPKERWUCK                   RCC_CFGR_STOPKERWUCK_Msk             /*!< Kernel Clock Selection after a Wake Up from STOP */

    /*!< RTCPRE configuration */
    #define RCC_CFGR_RTCPRE_Pos                    (8U)
    #define RCC_CFGR_RTCPRE_Msk                    (0x3FUL << RCC_CFGR_RTCPRE_Pos)
    #define RCC_CFGR_RTCPRE                        RCC_CFGR_RTCPRE_Msk                  /*!< 0x00003F00 */
    #define RCC_CFGR_RTCPRE_0                      (0x1UL << RCC_CFGR_RTCPRE_Pos)        /*!< 0x00000100 */
    #define RCC_CFGR_RTCPRE_1                      (0x2UL << RCC_CFGR_RTCPRE_Pos)        /*!< 0x00000200 */
    #define RCC_CFGR_RTCPRE_2                      (0x4UL << RCC_CFGR_RTCPRE_Pos)        /*!< 0x00000400 */
    #define RCC_CFGR_RTCPRE_3                      (0x8UL << RCC_CFGR_RTCPRE_Pos)        /*!< 0x00000800 */
    #define RCC_CFGR_RTCPRE_4                      (0x10UL << RCC_CFGR_RTCPRE_Pos)       /*!< 0x00001000 */
    #define RCC_CFGR_RTCPRE_5                      (0x20UL << RCC_CFGR_RTCPRE_Pos)       /*!< 0x00002000 */

    /*!< HRTIMSEL configuration */
    #define RCC_CFGR_HRTIMSEL_Pos                  (14U)
    #define RCC_CFGR_HRTIMSEL_Msk                  (0x1UL << RCC_CFGR_HRTIMSEL_Pos)
    #define RCC_CFGR_HRTIMSEL                      RCC_CFGR_HRTIMSEL_Msk                /*!< 0x00004000 */

    /*!< TIMPRE configuration */
    #define RCC_CFGR_TIMPRE_Pos                    (15U)
    #define RCC_CFGR_TIMPRE_Msk                    (0x1UL << RCC_CFGR_TIMPRE_Pos)
    #define RCC_CFGR_TIMPRE                        RCC_CFGR_TIMPRE_Msk                  /*!< 0x00008000 */

    /*!< MCO1 configuration */
    #define RCC_CFGR_MCO1_Pos                      (22U)
    #define RCC_CFGR_MCO1_Msk                      (0x7UL << RCC_CFGR_MCO1_Pos)
    #define RCC_CFGR_MCO1                          RCC_CFGR_MCO1_Msk                       /*!< 0x01C00000 */
    #define RCC_CFGR_MCO1_0                        (0x1UL <<  RCC_CFGR_MCO1_Pos)            /*!< 0x00400000 */
    #define RCC_CFGR_MCO1_1                        (0x2UL <<  RCC_CFGR_MCO1_Pos)            /*!< 0x00800000 */
    #define RCC_CFGR_MCO1_2                        (0x4UL <<  RCC_CFGR_MCO1_Pos)            /*!< 0x01000000 */

    #define RCC_CFGR_MCO1PRE_Pos                   (18U)
    #define RCC_CFGR_MCO1PRE_Msk                   (0xFUL << RCC_CFGR_MCO1PRE_Pos)
    #define RCC_CFGR_MCO1PRE                       RCC_CFGR_MCO1PRE_Msk                    /*!< 0x003C0000 */
    #define RCC_CFGR_MCO1PRE_0                     (0x1UL << RCC_CFGR_MCO1PRE_Pos)          /*!< 0x00040000 */
    #define RCC_CFGR_MCO1PRE_1                     (0x2UL << RCC_CFGR_MCO1PRE_Pos)          /*!< 0x00080000 */
    #define RCC_CFGR_MCO1PRE_2                     (0x4UL << RCC_CFGR_MCO1PRE_Pos)          /*!< 0x00100000 */
    #define RCC_CFGR_MCO1PRE_3                     (0x8UL << RCC_CFGR_MCO1PRE_Pos)          /*!< 0x00200000 */

    #define RCC_CFGR_MCO2PRE_Pos                   (25U)
    #define RCC_CFGR_MCO2PRE_Msk                   (0xFUL << RCC_CFGR_MCO2PRE_Pos)
    #define RCC_CFGR_MCO2PRE                       RCC_CFGR_MCO2PRE_Msk                    /*!< 0x1E000000 */
    #define RCC_CFGR_MCO2PRE_0                     (0x1UL << RCC_CFGR_MCO2PRE_Pos)          /*!< 0x02000000 */
    #define RCC_CFGR_MCO2PRE_1                     (0x2UL << RCC_CFGR_MCO2PRE_Pos)          /*!< 0x04000000 */
    #define RCC_CFGR_MCO2PRE_2                     (0x4UL << RCC_CFGR_MCO2PRE_Pos)          /*!< 0x08000000 */
    #define RCC_CFGR_MCO2PRE_3                     (0x8UL << RCC_CFGR_MCO2PRE_Pos)          /*!< 0x10000000 */

    #define RCC_CFGR_MCO2_Pos                      (29U)
    #define RCC_CFGR_MCO2_Msk                      (0x7UL << RCC_CFGR_MCO2_Pos)
    #define RCC_CFGR_MCO2                          RCC_CFGR_MCO2_Msk                       /*!< 0xE0000000 */
    #define RCC_CFGR_MCO2_0                        (0x1UL << RCC_CFGR_MCO2_Pos)             /*!< 0x20000000 */
    #define RCC_CFGR_MCO2_1                        (0x2UL << RCC_CFGR_MCO2_Pos)             /*!< 0x40000000 */
    #define RCC_CFGR_MCO2_2                        (0x4UL << RCC_CFGR_MCO2_Pos)             /*!< 0x80000000 */

    /********************  Bit definition for RCC_D1CFGR register  ******************/
    /*!< D1HPRE configuration */
    #define RCC_D1CFGR_HPRE_Pos                    (0U)
    #define RCC_D1CFGR_HPRE_Msk                    (0xFUL << RCC_D1CFGR_HPRE_Pos)  /*!< 0x0000000F */
    #define RCC_D1CFGR_HPRE                        RCC_D1CFGR_HPRE_Msk             /*!< HPRE[3:0] bits (AHB3 prescaler) */
    #define RCC_D1CFGR_HPRE_0                      (0x1UL << RCC_D1CFGR_HPRE_Pos)   /*!< 0x00000001 */
    #define RCC_D1CFGR_HPRE_1                      (0x2UL << RCC_D1CFGR_HPRE_Pos)   /*!< 0x00000002 */
    #define RCC_D1CFGR_HPRE_2                      (0x4UL << RCC_D1CFGR_HPRE_Pos)   /*!< 0x00000004 */
    #define RCC_D1CFGR_HPRE_3                      (0x8UL << RCC_D1CFGR_HPRE_Pos)   /*!< 0x00000008 */


    #define RCC_D1CFGR_HPRE_DIV1                   (0U)          /*!< AHB3 Clock not divided */
    #define RCC_D1CFGR_HPRE_DIV2_Pos               (3U)
    #define RCC_D1CFGR_HPRE_DIV2_Msk               (0x1UL << RCC_D1CFGR_HPRE_DIV2_Pos) /*!< 0x00000008 */
    #define RCC_D1CFGR_HPRE_DIV2                   RCC_D1CFGR_HPRE_DIV2_Msk        /*!< AHB3 Clock divided by 2 */
    #define RCC_D1CFGR_HPRE_DIV4_Pos               (0U)
    #define RCC_D1CFGR_HPRE_DIV4_Msk               (0x9UL << RCC_D1CFGR_HPRE_DIV4_Pos) /*!< 0x00000009 */
    #define RCC_D1CFGR_HPRE_DIV4                   RCC_D1CFGR_HPRE_DIV4_Msk        /*!< AHB3 Clock divided by 4 */
    #define RCC_D1CFGR_HPRE_DIV8_Pos               (1U)
    #define RCC_D1CFGR_HPRE_DIV8_Msk               (0x5UL << RCC_D1CFGR_HPRE_DIV8_Pos) /*!< 0x0000000A */
    #define RCC_D1CFGR_HPRE_DIV8                   RCC_D1CFGR_HPRE_DIV8_Msk        /*!< AHB3 Clock divided by 8 */
    #define RCC_D1CFGR_HPRE_DIV16_Pos              (0U)
    #define RCC_D1CFGR_HPRE_DIV16_Msk              (0xBUL << RCC_D1CFGR_HPRE_DIV16_Pos) /*!< 0x0000000B */
    #define RCC_D1CFGR_HPRE_DIV16                  RCC_D1CFGR_HPRE_DIV16_Msk       /*!< AHB3 Clock divided by 16 */
    #define RCC_D1CFGR_HPRE_DIV64_Pos              (2U)
    #define RCC_D1CFGR_HPRE_DIV64_Msk              (0x3UL << RCC_D1CFGR_HPRE_DIV64_Pos) /*!< 0x0000000C */
    #define RCC_D1CFGR_HPRE_DIV64                  RCC_D1CFGR_HPRE_DIV64_Msk       /*!< AHB3 Clock divided by 64 */
    #define RCC_D1CFGR_HPRE_DIV128_Pos             (0U)
    #define RCC_D1CFGR_HPRE_DIV128_Msk             (0xDUL << RCC_D1CFGR_HPRE_DIV128_Pos) /*!< 0x0000000D */
    #define RCC_D1CFGR_HPRE_DIV128                 RCC_D1CFGR_HPRE_DIV128_Msk      /*!< AHB3 Clock divided by 128 */
    #define RCC_D1CFGR_HPRE_DIV256_Pos             (1U)
    #define RCC_D1CFGR_HPRE_DIV256_Msk             (0x7UL << RCC_D1CFGR_HPRE_DIV256_Pos) /*!< 0x0000000E */
    #define RCC_D1CFGR_HPRE_DIV256                 RCC_D1CFGR_HPRE_DIV256_Msk      /*!< AHB3 Clock divided by 256 */
    #define RCC_D1CFGR_HPRE_DIV512_Pos             (0U)
    #define RCC_D1CFGR_HPRE_DIV512_Msk             (0xFUL << RCC_D1CFGR_HPRE_DIV512_Pos) /*!< 0x0000000F */
    #define RCC_D1CFGR_HPRE_DIV512                 RCC_D1CFGR_HPRE_DIV512_Msk      /*!< AHB3 Clock divided by 512 */

    /*!< D1PPRE configuration */
    #define RCC_D1CFGR_D1PPRE_Pos                  (4U)
    #define RCC_D1CFGR_D1PPRE_Msk                  (0x7UL << RCC_D1CFGR_D1PPRE_Pos) /*!< 0x00000070 */
    #define RCC_D1CFGR_D1PPRE                      RCC_D1CFGR_D1PPRE_Msk           /*!< D1PRE[2:0] bits (APB3 prescaler) */
    #define RCC_D1CFGR_D1PPRE_0                    (0x1UL << RCC_D1CFGR_D1PPRE_Pos) /*!< 0x00000010 */
    #define RCC_D1CFGR_D1PPRE_1                    (0x2UL << RCC_D1CFGR_D1PPRE_Pos) /*!< 0x00000020 */
    #define RCC_D1CFGR_D1PPRE_2                    (0x4UL << RCC_D1CFGR_D1PPRE_Pos) /*!< 0x00000040 */

    #define RCC_D1CFGR_D1PPRE_DIV1                 (0U)          /*!< APB3 clock not divided */
    #define RCC_D1CFGR_D1PPRE_DIV2_Pos             (6U)
    #define RCC_D1CFGR_D1PPRE_DIV2_Msk             (0x1UL << RCC_D1CFGR_D1PPRE_DIV2_Pos) /*!< 0x00000040 */
    #define RCC_D1CFGR_D1PPRE_DIV2                 RCC_D1CFGR_D1PPRE_DIV2_Msk      /*!< APB3 clock divided by 2 */
    #define RCC_D1CFGR_D1PPRE_DIV4_Pos             (4U)
    #define RCC_D1CFGR_D1PPRE_DIV4_Msk             (0x5UL << RCC_D1CFGR_D1PPRE_DIV4_Pos) /*!< 0x00000050 */
    #define RCC_D1CFGR_D1PPRE_DIV4                 RCC_D1CFGR_D1PPRE_DIV4_Msk      /*!< APB3 clock divided by 4 */
    #define RCC_D1CFGR_D1PPRE_DIV8_Pos             (5U)
    #define RCC_D1CFGR_D1PPRE_DIV8_Msk             (0x3UL << RCC_D1CFGR_D1PPRE_DIV8_Pos) /*!< 0x00000060 */
    #define RCC_D1CFGR_D1PPRE_DIV8                 RCC_D1CFGR_D1PPRE_DIV8_Msk      /*!< APB3 clock divided by 8 */
    #define RCC_D1CFGR_D1PPRE_DIV16_Pos            (4U)
    #define RCC_D1CFGR_D1PPRE_DIV16_Msk            (0x7UL << RCC_D1CFGR_D1PPRE_DIV16_Pos) /*!< 0x00000070 */
    #define RCC_D1CFGR_D1PPRE_DIV16                RCC_D1CFGR_D1PPRE_DIV16_Msk     /*!< APB3 clock divided by 16 */

    #define RCC_D1CFGR_D1CPRE_Pos                  (8U)
    #define RCC_D1CFGR_D1CPRE_Msk                  (0xFUL << RCC_D1CFGR_D1CPRE_Pos) /*!< 0x00000F00 */
    #define RCC_D1CFGR_D1CPRE                      RCC_D1CFGR_D1CPRE_Msk           /*!< D1CPRE[2:0] bits (Domain 1 Core prescaler) */
    #define RCC_D1CFGR_D1CPRE_0                    (0x1UL << RCC_D1CFGR_D1CPRE_Pos) /*!< 0x00000100 */
    #define RCC_D1CFGR_D1CPRE_1                    (0x2UL << RCC_D1CFGR_D1CPRE_Pos) /*!< 0x00000200 */
    #define RCC_D1CFGR_D1CPRE_2                    (0x4UL << RCC_D1CFGR_D1CPRE_Pos) /*!< 0x00000400 */
    #define RCC_D1CFGR_D1CPRE_3                    (0x8UL << RCC_D1CFGR_D1CPRE_Pos) /*!< 0x00000800 */

    #define RCC_D1CFGR_D1CPRE_DIV1                 (0U)          /*!< Domain 1 Core clock not divided */
    #define RCC_D1CFGR_D1CPRE_DIV2_Pos             (11U)
    #define RCC_D1CFGR_D1CPRE_DIV2_Msk             (0x1UL << RCC_D1CFGR_D1CPRE_DIV2_Pos) /*!< 0x00000800 */
    #define RCC_D1CFGR_D1CPRE_DIV2                 RCC_D1CFGR_D1CPRE_DIV2_Msk      /*!< Domain 1 Core clock divided by 2 */
    #define RCC_D1CFGR_D1CPRE_DIV4_Pos             (8U)
    #define RCC_D1CFGR_D1CPRE_DIV4_Msk             (0x9UL << RCC_D1CFGR_D1CPRE_DIV4_Pos) /*!< 0x00000900 */
    #define RCC_D1CFGR_D1CPRE_DIV4                 RCC_D1CFGR_D1CPRE_DIV4_Msk      /*!< Domain 1 Core clock divided by 4 */
    #define RCC_D1CFGR_D1CPRE_DIV8_Pos             (9U)
    #define RCC_D1CFGR_D1CPRE_DIV8_Msk             (0x5UL << RCC_D1CFGR_D1CPRE_DIV8_Pos) /*!< 0x00000A00 */
    #define RCC_D1CFGR_D1CPRE_DIV8                 RCC_D1CFGR_D1CPRE_DIV8_Msk      /*!< Domain 1 Core clock divided by 8 */
    #define RCC_D1CFGR_D1CPRE_DIV16_Pos            (8U)
    #define RCC_D1CFGR_D1CPRE_DIV16_Msk            (0xBUL << RCC_D1CFGR_D1CPRE_DIV16_Pos) /*!< 0x00000B00 */
    #define RCC_D1CFGR_D1CPRE_DIV16                RCC_D1CFGR_D1CPRE_DIV16_Msk     /*!< Domain 1 Core clock divided by 16 */
    #define RCC_D1CFGR_D1CPRE_DIV64_Pos            (10U)
    #define RCC_D1CFGR_D1CPRE_DIV64_Msk            (0x3UL << RCC_D1CFGR_D1CPRE_DIV64_Pos) /*!< 0x00000C00 */
    #define RCC_D1CFGR_D1CPRE_DIV64                RCC_D1CFGR_D1CPRE_DIV64_Msk     /*!< Domain 1 Core clock divided by 64 */
    #define RCC_D1CFGR_D1CPRE_DIV128_Pos           (8U)
    #define RCC_D1CFGR_D1CPRE_DIV128_Msk           (0xDUL << RCC_D1CFGR_D1CPRE_DIV128_Pos) /*!< 0x00000D00 */
    #define RCC_D1CFGR_D1CPRE_DIV128               RCC_D1CFGR_D1CPRE_DIV128_Msk    /*!< Domain 1 Core clock divided by 128 */
    #define RCC_D1CFGR_D1CPRE_DIV256_Pos           (9U)
    #define RCC_D1CFGR_D1CPRE_DIV256_Msk           (0x7UL << RCC_D1CFGR_D1CPRE_DIV256_Pos) /*!< 0x00000E00 */
    #define RCC_D1CFGR_D1CPRE_DIV256               RCC_D1CFGR_D1CPRE_DIV256_Msk    /*!< Domain 1 Core clock divided by 256 */
    #define RCC_D1CFGR_D1CPRE_DIV512_Pos           (8U)
    #define RCC_D1CFGR_D1CPRE_DIV512_Msk           (0xFUL << RCC_D1CFGR_D1CPRE_DIV512_Pos) /*!< 0x00000F00 */
    #define RCC_D1CFGR_D1CPRE_DIV512               RCC_D1CFGR_D1CPRE_DIV512_Msk    /*!< Domain 1 Core clock divided by 512 */

    /********************  Bit definition for RCC_D2CFGR register  ******************/
    /*!< D2PPRE1 configuration */
    #define RCC_D2CFGR_D2PPRE1_Pos                 (4U)
    #define RCC_D2CFGR_D2PPRE1_Msk                 (0x7UL << RCC_D2CFGR_D2PPRE1_Pos) /*!< 0x00000070 */
    #define RCC_D2CFGR_D2PPRE1                     RCC_D2CFGR_D2PPRE1_Msk          /*!< D1PPRE1[2:0] bits (APB1 prescaler) */
    #define RCC_D2CFGR_D2PPRE1_0                   (0x1UL << RCC_D2CFGR_D2PPRE1_Pos) /*!< 0x00000010 */
    #define RCC_D2CFGR_D2PPRE1_1                   (0x2UL << RCC_D2CFGR_D2PPRE1_Pos) /*!< 0x00000020 */
    #define RCC_D2CFGR_D2PPRE1_2                   (0x4UL << RCC_D2CFGR_D2PPRE1_Pos) /*!< 0x00000040 */

    #define RCC_D2CFGR_D2PPRE1_DIV1                (0U)          /*!< APB1 clock not divided */
    #define RCC_D2CFGR_D2PPRE1_DIV2_Pos            (6U)
    #define RCC_D2CFGR_D2PPRE1_DIV2_Msk            (0x1UL << RCC_D2CFGR_D2PPRE1_DIV2_Pos) /*!< 0x00000040 */
    #define RCC_D2CFGR_D2PPRE1_DIV2                RCC_D2CFGR_D2PPRE1_DIV2_Msk     /*!< APB1 clock divided by 2 */
    #define RCC_D2CFGR_D2PPRE1_DIV4_Pos            (4U)
    #define RCC_D2CFGR_D2PPRE1_DIV4_Msk            (0x5UL << RCC_D2CFGR_D2PPRE1_DIV4_Pos) /*!< 0x00000050 */
    #define RCC_D2CFGR_D2PPRE1_DIV4                RCC_D2CFGR_D2PPRE1_DIV4_Msk     /*!< APB1 clock divided by 4 */
    #define RCC_D2CFGR_D2PPRE1_DIV8_Pos            (5U)
    #define RCC_D2CFGR_D2PPRE1_DIV8_Msk            (0x3UL << RCC_D2CFGR_D2PPRE1_DIV8_Pos) /*!< 0x00000060 */
    #define RCC_D2CFGR_D2PPRE1_DIV8                RCC_D2CFGR_D2PPRE1_DIV8_Msk     /*!< APB1 clock divided by 8 */
    #define RCC_D2CFGR_D2PPRE1_DIV16_Pos           (4U)
    #define RCC_D2CFGR_D2PPRE1_DIV16_Msk           (0x7UL << RCC_D2CFGR_D2PPRE1_DIV16_Pos) /*!< 0x00000070 */
    #define RCC_D2CFGR_D2PPRE1_DIV16               RCC_D2CFGR_D2PPRE1_DIV16_Msk    /*!< APB1 clock divided by 16 */

    /*!< D2PPRE2 configuration */
    #define RCC_D2CFGR_D2PPRE2_Pos                 (8U)
    #define RCC_D2CFGR_D2PPRE2_Msk                 (0x7UL << RCC_D2CFGR_D2PPRE2_Pos) /*!< 0x00000700 */
    #define RCC_D2CFGR_D2PPRE2                     RCC_D2CFGR_D2PPRE2_Msk          /*!< D2PPRE2[2:0] bits (APB2 prescaler) */
    #define RCC_D2CFGR_D2PPRE2_0                   (0x1UL << RCC_D2CFGR_D2PPRE2_Pos) /*!< 0x00000100 */
    #define RCC_D2CFGR_D2PPRE2_1                   (0x2UL << RCC_D2CFGR_D2PPRE2_Pos) /*!< 0x00000200 */
    #define RCC_D2CFGR_D2PPRE2_2                   (0x4UL << RCC_D2CFGR_D2PPRE2_Pos) /*!< 0x00000400 */

    #define RCC_D2CFGR_D2PPRE2_DIV1                (0U)          /*!< APB2 clock not divided */
    #define RCC_D2CFGR_D2PPRE2_DIV2_Pos            (10U)
    #define RCC_D2CFGR_D2PPRE2_DIV2_Msk            (0x1UL << RCC_D2CFGR_D2PPRE2_DIV2_Pos) /*!< 0x00000400 */
    #define RCC_D2CFGR_D2PPRE2_DIV2                RCC_D2CFGR_D2PPRE2_DIV2_Msk     /*!< APB2 clock divided by 2 */
    #define RCC_D2CFGR_D2PPRE2_DIV4_Pos            (8U)
    #define RCC_D2CFGR_D2PPRE2_DIV4_Msk            (0x5UL << RCC_D2CFGR_D2PPRE2_DIV4_Pos) /*!< 0x00000500 */
    #define RCC_D2CFGR_D2PPRE2_DIV4                RCC_D2CFGR_D2PPRE2_DIV4_Msk     /*!< APB2 clock divided by 4 */
    #define RCC_D2CFGR_D2PPRE2_DIV8_Pos            (9U)
    #define RCC_D2CFGR_D2PPRE2_DIV8_Msk            (0x3UL << RCC_D2CFGR_D2PPRE2_DIV8_Pos) /*!< 0x00000600 */
    #define RCC_D2CFGR_D2PPRE2_DIV8                RCC_D2CFGR_D2PPRE2_DIV8_Msk     /*!< APB2 clock divided by 8 */
    #define RCC_D2CFGR_D2PPRE2_DIV16_Pos           (8U)
    #define RCC_D2CFGR_D2PPRE2_DIV16_Msk           (0x7UL << RCC_D2CFGR_D2PPRE2_DIV16_Pos) /*!< 0x00000700 */
    #define RCC_D2CFGR_D2PPRE2_DIV16               RCC_D2CFGR_D2PPRE2_DIV16_Msk    /*!< APB2 clock divided by 16 */

    /********************  Bit definition for RCC_D3CFGR register  ******************/
    /*!< D3PPRE configuration */
    #define RCC_D3CFGR_D3PPRE_Pos                  (4U)
    #define RCC_D3CFGR_D3PPRE_Msk                  (0x7UL << RCC_D3CFGR_D3PPRE_Pos) /*!< 0x00000070 */
    #define RCC_D3CFGR_D3PPRE                      RCC_D3CFGR_D3PPRE_Msk           /*!< D3PPRE1[2:0] bits (APB4 prescaler) */
    #define RCC_D3CFGR_D3PPRE_0                    (0x1UL << RCC_D3CFGR_D3PPRE_Pos) /*!< 0x00000010 */
    #define RCC_D3CFGR_D3PPRE_1                    (0x2UL << RCC_D3CFGR_D3PPRE_Pos) /*!< 0x00000020 */
    #define RCC_D3CFGR_D3PPRE_2                    (0x4UL << RCC_D3CFGR_D3PPRE_Pos) /*!< 0x00000040 */

    #define RCC_D3CFGR_D3PPRE_DIV1                 (0U)          /*!< APB4 clock not divided */
    #define RCC_D3CFGR_D3PPRE_DIV2_Pos             (6U)
    #define RCC_D3CFGR_D3PPRE_DIV2_Msk             (0x1UL << RCC_D3CFGR_D3PPRE_DIV2_Pos) /*!< 0x00000040 */
    #define RCC_D3CFGR_D3PPRE_DIV2                 RCC_D3CFGR_D3PPRE_DIV2_Msk      /*!< APB4 clock divided by 2 */
    #define RCC_D3CFGR_D3PPRE_DIV4_Pos             (4U)
    #define RCC_D3CFGR_D3PPRE_DIV4_Msk             (0x5UL << RCC_D3CFGR_D3PPRE_DIV4_Pos) /*!< 0x00000050 */
    #define RCC_D3CFGR_D3PPRE_DIV4                 RCC_D3CFGR_D3PPRE_DIV4_Msk      /*!< APB4 clock divided by 4 */
    #define RCC_D3CFGR_D3PPRE_DIV8_Pos             (5U)
    #define RCC_D3CFGR_D3PPRE_DIV8_Msk             (0x3UL << RCC_D3CFGR_D3PPRE_DIV8_Pos) /*!< 0x00000060 */
    #define RCC_D3CFGR_D3PPRE_DIV8                 RCC_D3CFGR_D3PPRE_DIV8_Msk      /*!< APB4 clock divided by 8 */
    #define RCC_D3CFGR_D3PPRE_DIV16_Pos            (4U)
    #define RCC_D3CFGR_D3PPRE_DIV16_Msk            (0x7UL << RCC_D3CFGR_D3PPRE_DIV16_Pos) /*!< 0x00000070 */
    #define RCC_D3CFGR_D3PPRE_DIV16                RCC_D3CFGR_D3PPRE_DIV16_Msk     /*!< APB4 clock divided by 16 */

    /********************  Bit definition for RCC_PLLCKSELR register  *************/

    #define RCC_PLLCKSELR_PLLSRC_Pos               (0U)
    #define RCC_PLLCKSELR_PLLSRC_Msk               (0x3UL << RCC_PLLCKSELR_PLLSRC_Pos) /*!< 0x00000003 */
    #define RCC_PLLCKSELR_PLLSRC                   RCC_PLLCKSELR_PLLSRC_Msk

    #define RCC_PLLCKSELR_PLLSRC_HSI               (0U)          /*!< HSI source clock selected */
    #define RCC_PLLCKSELR_PLLSRC_CSI_Pos           (0U)
    #define RCC_PLLCKSELR_PLLSRC_CSI_Msk           (0x1UL << RCC_PLLCKSELR_PLLSRC_CSI_Pos) /*!< 0x00000001 */
    #define RCC_PLLCKSELR_PLLSRC_CSI               RCC_PLLCKSELR_PLLSRC_CSI_Msk    /*!< CSI source clock selected */
    #define RCC_PLLCKSELR_PLLSRC_HSE_Pos           (1U)
    #define RCC_PLLCKSELR_PLLSRC_HSE_Msk           (0x1UL << RCC_PLLCKSELR_PLLSRC_HSE_Pos) /*!< 0x00000002 */
    #define RCC_PLLCKSELR_PLLSRC_HSE               RCC_PLLCKSELR_PLLSRC_HSE_Msk    /*!< HSE source clock selected */
    #define RCC_PLLCKSELR_PLLSRC_NONE_Pos          (0U)
    #define RCC_PLLCKSELR_PLLSRC_NONE_Msk          (0x3UL << RCC_PLLCKSELR_PLLSRC_NONE_Pos) /*!< 0x00000003 */
    #define RCC_PLLCKSELR_PLLSRC_NONE              RCC_PLLCKSELR_PLLSRC_NONE_Msk   /*!< No source clock selected  */

    #define RCC_PLLCKSELR_DIVM1_Pos                (4U)
    #define RCC_PLLCKSELR_DIVM1_Msk                (0x3FUL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x000003F0 */
    #define RCC_PLLCKSELR_DIVM1                    RCC_PLLCKSELR_DIVM1_Msk
    #define RCC_PLLCKSELR_DIVM1_0                  (0x01UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000010 */
    #define RCC_PLLCKSELR_DIVM1_1                  (0x02UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000020 */
    #define RCC_PLLCKSELR_DIVM1_2                  (0x04UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000040 */
    #define RCC_PLLCKSELR_DIVM1_3                  (0x08UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000080 */
    #define RCC_PLLCKSELR_DIVM1_4                  (0x10UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000100 */
    #define RCC_PLLCKSELR_DIVM1_5                  (0x20UL << RCC_PLLCKSELR_DIVM1_Pos) /*!< 0x00000200 */

    #define RCC_PLLCKSELR_DIVM2_Pos                (12U)
    #define RCC_PLLCKSELR_DIVM2_Msk                (0x3FUL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x0003F000 */
    #define RCC_PLLCKSELR_DIVM2                    RCC_PLLCKSELR_DIVM2_Msk
    #define RCC_PLLCKSELR_DIVM2_0                  (0x01UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00001000 */
    #define RCC_PLLCKSELR_DIVM2_1                  (0x02UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00002000 */
    #define RCC_PLLCKSELR_DIVM2_2                  (0x04UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00004000 */
    #define RCC_PLLCKSELR_DIVM2_3                  (0x08UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00008000 */
    #define RCC_PLLCKSELR_DIVM2_4                  (0x10UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00010000 */
    #define RCC_PLLCKSELR_DIVM2_5                  (0x20UL << RCC_PLLCKSELR_DIVM2_Pos) /*!< 0x00020000 */

    #define RCC_PLLCKSELR_DIVM3_Pos                (20U)
    #define RCC_PLLCKSELR_DIVM3_Msk                (0x3FUL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x03F00000 */
    #define RCC_PLLCKSELR_DIVM3                    RCC_PLLCKSELR_DIVM3_Msk
    #define RCC_PLLCKSELR_DIVM3_0                  (0x01UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x00100000 */
    #define RCC_PLLCKSELR_DIVM3_1                  (0x02UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x00200000 */
    #define RCC_PLLCKSELR_DIVM3_2                  (0x04UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x00400000 */
    #define RCC_PLLCKSELR_DIVM3_3                  (0x08UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x00800000 */
    #define RCC_PLLCKSELR_DIVM3_4                  (0x10UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x01000000 */
    #define RCC_PLLCKSELR_DIVM3_5                  (0x20UL << RCC_PLLCKSELR_DIVM3_Pos) /*!< 0x02000000 */

    /********************  Bit definition for RCC_PLLCFGR register  ***************/

    #define RCC_PLLCFGR_PLL1FRACEN_Pos             (0U)
    #define RCC_PLLCFGR_PLL1FRACEN_Msk             (0x1UL << RCC_PLLCFGR_PLL1FRACEN_Pos) /*!< 0x00000001 */
    #define RCC_PLLCFGR_PLL1FRACEN                 RCC_PLLCFGR_PLL1FRACEN_Msk
    #define RCC_PLLCFGR_PLL1VCOSEL_Pos             (1U)
    #define RCC_PLLCFGR_PLL1VCOSEL_Msk             (0x1UL << RCC_PLLCFGR_PLL1VCOSEL_Pos) /*!< 0x00000002 */
    #define RCC_PLLCFGR_PLL1VCOSEL                 RCC_PLLCFGR_PLL1VCOSEL_Msk
    #define RCC_PLLCFGR_PLL1RGE_Pos                (2U)
    #define RCC_PLLCFGR_PLL1RGE_Msk                (0x3UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x0000000C */
    #define RCC_PLLCFGR_PLL1RGE                    RCC_PLLCFGR_PLL1RGE_Msk
    #define RCC_PLLCFGR_PLL1RGE_0                  (0x0UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x00000000 */
    #define RCC_PLLCFGR_PLL1RGE_1                  (0x1UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x00000004 */
    #define RCC_PLLCFGR_PLL1RGE_2                  (0x2UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x00000008 */
    #define RCC_PLLCFGR_PLL1RGE_3                  (0x3UL << RCC_PLLCFGR_PLL1RGE_Pos) /*!< 0x0000000C */

    #define RCC_PLLCFGR_PLL2FRACEN_Pos             (4U)
    #define RCC_PLLCFGR_PLL2FRACEN_Msk             (0x1UL << RCC_PLLCFGR_PLL2FRACEN_Pos) /*!< 0x00000010 */
    #define RCC_PLLCFGR_PLL2FRACEN                 RCC_PLLCFGR_PLL2FRACEN_Msk
    #define RCC_PLLCFGR_PLL2VCOSEL_Pos             (5U)
    #define RCC_PLLCFGR_PLL2VCOSEL_Msk             (0x1UL << RCC_PLLCFGR_PLL2VCOSEL_Pos) /*!< 0x00000020 */
    #define RCC_PLLCFGR_PLL2VCOSEL                 RCC_PLLCFGR_PLL2VCOSEL_Msk
    #define RCC_PLLCFGR_PLL2RGE_Pos                (6U)
    #define RCC_PLLCFGR_PLL2RGE_Msk                (0x3UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x000000C0 */
    #define RCC_PLLCFGR_PLL2RGE                    RCC_PLLCFGR_PLL2RGE_Msk
    #define RCC_PLLCFGR_PLL2RGE_0                  (0x0UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x00000000 */
    #define RCC_PLLCFGR_PLL2RGE_1                  (0x1UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x00000040 */
    #define RCC_PLLCFGR_PLL2RGE_2                  (0x2UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x00000080 */
    #define RCC_PLLCFGR_PLL2RGE_3                  (0x3UL << RCC_PLLCFGR_PLL2RGE_Pos) /*!< 0x000000C0 */

    #define RCC_PLLCFGR_PLL3FRACEN_Pos             (8U)
    #define RCC_PLLCFGR_PLL3FRACEN_Msk             (0x1UL << RCC_PLLCFGR_PLL3FRACEN_Pos) /*!< 0x00000100 */
    #define RCC_PLLCFGR_PLL3FRACEN                 RCC_PLLCFGR_PLL3FRACEN_Msk
    #define RCC_PLLCFGR_PLL3VCOSEL_Pos             (9U)
    #define RCC_PLLCFGR_PLL3VCOSEL_Msk             (0x1UL << RCC_PLLCFGR_PLL3VCOSEL_Pos) /*!< 0x00000200 */
    #define RCC_PLLCFGR_PLL3VCOSEL                 RCC_PLLCFGR_PLL3VCOSEL_Msk
    #define RCC_PLLCFGR_PLL3RGE_Pos                (10U)
    #define RCC_PLLCFGR_PLL3RGE_Msk                (0x3UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000C00 */
    #define RCC_PLLCFGR_PLL3RGE                    RCC_PLLCFGR_PLL3RGE_Msk
    #define RCC_PLLCFGR_PLL3RGE_0                  (0x0UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000000 */
    #define RCC_PLLCFGR_PLL3RGE_1                  (0x1UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000400 */
    #define RCC_PLLCFGR_PLL3RGE_2                  (0x2UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000800 */
    #define RCC_PLLCFGR_PLL3RGE_3                  (0x3UL << RCC_PLLCFGR_PLL3RGE_Pos) /*!< 0x00000C00 */

    #define RCC_PLLCFGR_DIVP1EN_Pos                (16U)
    #define RCC_PLLCFGR_DIVP1EN_Msk                (0x1UL << RCC_PLLCFGR_DIVP1EN_Pos) /*!< 0x00010000 */
    #define RCC_PLLCFGR_DIVP1EN                    RCC_PLLCFGR_DIVP1EN_Msk
    #define RCC_PLLCFGR_DIVQ1EN_Pos                (17U)
    #define RCC_PLLCFGR_DIVQ1EN_Msk                (0x1UL << RCC_PLLCFGR_DIVQ1EN_Pos) /*!< 0x00020000 */
    #define RCC_PLLCFGR_DIVQ1EN                    RCC_PLLCFGR_DIVQ1EN_Msk
    #define RCC_PLLCFGR_DIVR1EN_Pos                (18U)
    #define RCC_PLLCFGR_DIVR1EN_Msk                (0x1UL << RCC_PLLCFGR_DIVR1EN_Pos) /*!< 0x00040000 */
    #define RCC_PLLCFGR_DIVR1EN                    RCC_PLLCFGR_DIVR1EN_Msk

    #define RCC_PLLCFGR_DIVP2EN_Pos                (19U)
    #define RCC_PLLCFGR_DIVP2EN_Msk                (0x1UL << RCC_PLLCFGR_DIVP2EN_Pos) /*!< 0x00080000 */
    #define RCC_PLLCFGR_DIVP2EN                    RCC_PLLCFGR_DIVP2EN_Msk
    #define RCC_PLLCFGR_DIVQ2EN_Pos                (20U)
    #define RCC_PLLCFGR_DIVQ2EN_Msk                (0x1UL << RCC_PLLCFGR_DIVQ2EN_Pos) /*!< 0x00100000 */
    #define RCC_PLLCFGR_DIVQ2EN                    RCC_PLLCFGR_DIVQ2EN_Msk
    #define RCC_PLLCFGR_DIVR2EN_Pos                (21U)
    #define RCC_PLLCFGR_DIVR2EN_Msk                (0x1UL << RCC_PLLCFGR_DIVR2EN_Pos) /*!< 0x00200000 */
    #define RCC_PLLCFGR_DIVR2EN                    RCC_PLLCFGR_DIVR2EN_Msk

    #define RCC_PLLCFGR_DIVP3EN_Pos                (22U)
    #define RCC_PLLCFGR_DIVP3EN_Msk                (0x1UL << RCC_PLLCFGR_DIVP3EN_Pos) /*!< 0x00400000 */
    #define RCC_PLLCFGR_DIVP3EN                    RCC_PLLCFGR_DIVP3EN_Msk
    #define RCC_PLLCFGR_DIVQ3EN_Pos                (23U)
    #define RCC_PLLCFGR_DIVQ3EN_Msk                (0x1UL << RCC_PLLCFGR_DIVQ3EN_Pos) /*!< 0x00800000 */
    #define RCC_PLLCFGR_DIVQ3EN                    RCC_PLLCFGR_DIVQ3EN_Msk
    #define RCC_PLLCFGR_DIVR3EN_Pos                (24U)
    #define RCC_PLLCFGR_DIVR3EN_Msk                (0x1UL << RCC_PLLCFGR_DIVR3EN_Pos) /*!< 0x01000000 */
    #define RCC_PLLCFGR_DIVR3EN                    RCC_PLLCFGR_DIVR3EN_Msk


    /********************  Bit definition for RCC_PLL1DIVR register  ***************/
    #define RCC_PLL1DIVR_N1_Pos                    (0U)
    #define RCC_PLL1DIVR_N1_Msk                    (0x1FFUL << RCC_PLL1DIVR_N1_Pos) /*!< 0x000001FF */
    #define RCC_PLL1DIVR_N1                        RCC_PLL1DIVR_N1_Msk
    #define RCC_PLL1DIVR_P1_Pos                    (9U)
    #define RCC_PLL1DIVR_P1_Msk                    (0x7FUL << RCC_PLL1DIVR_P1_Pos) /*!< 0x0000FE00 */
    #define RCC_PLL1DIVR_P1                        RCC_PLL1DIVR_P1_Msk
    #define RCC_PLL1DIVR_Q1_Pos                    (16U)
    #define RCC_PLL1DIVR_Q1_Msk                    (0x7FUL << RCC_PLL1DIVR_Q1_Pos) /*!< 0x007F0000 */
    #define RCC_PLL1DIVR_Q1                        RCC_PLL1DIVR_Q1_Msk
    #define RCC_PLL1DIVR_R1_Pos                    (24U)
    #define RCC_PLL1DIVR_R1_Msk                    (0x7FUL << RCC_PLL1DIVR_R1_Pos) /*!< 0x7F000000 */
    #define RCC_PLL1DIVR_R1                        RCC_PLL1DIVR_R1_Msk

    /********************  Bit definition for RCC_PLL1FRACR register  ***************/
    #define RCC_PLL1FRACR_FRACN1_Pos               (3U)
    #define RCC_PLL1FRACR_FRACN1_Msk               (0x1FFFUL << RCC_PLL1FRACR_FRACN1_Pos) /*!< 0x0000FFF8 */
    #define RCC_PLL1FRACR_FRACN1                   RCC_PLL1FRACR_FRACN1_Msk

    /********************  Bit definition for RCC_PLL2DIVR register  ***************/
    #define RCC_PLL2DIVR_N2_Pos                    (0U)
    #define RCC_PLL2DIVR_N2_Msk                    (0x1FFUL << RCC_PLL2DIVR_N2_Pos) /*!< 0x000001FF */
    #define RCC_PLL2DIVR_N2                        RCC_PLL2DIVR_N2_Msk
    #define RCC_PLL2DIVR_P2_Pos                    (9U)
    #define RCC_PLL2DIVR_P2_Msk                    (0x7FUL << RCC_PLL2DIVR_P2_Pos) /*!< 0x0000FE00 */
    #define RCC_PLL2DIVR_P2                        RCC_PLL2DIVR_P2_Msk
    #define RCC_PLL2DIVR_Q2_Pos                    (16U)
    #define RCC_PLL2DIVR_Q2_Msk                    (0x7FUL << RCC_PLL2DIVR_Q2_Pos) /*!< 0x007F0000 */
    #define RCC_PLL2DIVR_Q2                        RCC_PLL2DIVR_Q2_Msk
    #define RCC_PLL2DIVR_R2_Pos                    (24U)
    #define RCC_PLL2DIVR_R2_Msk                    (0x7FUL << RCC_PLL2DIVR_R2_Pos) /*!< 0x7F000000 */
    #define RCC_PLL2DIVR_R2                        RCC_PLL2DIVR_R2_Msk

    /********************  Bit definition for RCC_PLL2FRACR register  ***************/
    #define RCC_PLL2FRACR_FRACN2_Pos               (3U)
    #define RCC_PLL2FRACR_FRACN2_Msk               (0x1FFFUL << RCC_PLL2FRACR_FRACN2_Pos) /*!< 0x0000FFF8 */
    #define RCC_PLL2FRACR_FRACN2                   RCC_PLL2FRACR_FRACN2_Msk

    /********************  Bit definition for RCC_PLL3DIVR register  ***************/
    #define RCC_PLL3DIVR_N3_Pos                    (0U)
    #define RCC_PLL3DIVR_N3_Msk                    (0x1FFUL << RCC_PLL3DIVR_N3_Pos) /*!< 0x000001FF */
    #define RCC_PLL3DIVR_N3                        RCC_PLL3DIVR_N3_Msk
    #define RCC_PLL3DIVR_P3_Pos                    (9U)
    #define RCC_PLL3DIVR_P3_Msk                    (0x7FUL << RCC_PLL3DIVR_P3_Pos) /*!< 0x0000FE00 */
    #define RCC_PLL3DIVR_P3                        RCC_PLL3DIVR_P3_Msk
    #define RCC_PLL3DIVR_Q3_Pos                    (16U)
    #define RCC_PLL3DIVR_Q3_Msk                    (0x7FUL << RCC_PLL3DIVR_Q3_Pos) /*!< 0x007F0000 */
    #define RCC_PLL3DIVR_Q3                        RCC_PLL3DIVR_Q3_Msk
    #define RCC_PLL3DIVR_R3_Pos                    (24U)
    #define RCC_PLL3DIVR_R3_Msk                    (0x7FUL << RCC_PLL3DIVR_R3_Pos) /*!< 0x7F000000 */
    #define RCC_PLL3DIVR_R3                        RCC_PLL3DIVR_R3_Msk

    /********************  Bit definition for RCC_PLL3FRACR register  ***************/
    #define RCC_PLL3FRACR_FRACN3_Pos               (3U)
    #define RCC_PLL3FRACR_FRACN3_Msk               (0x1FFFUL << RCC_PLL3FRACR_FRACN3_Pos) /*!< 0x0000FFF8 */
    #define RCC_PLL3FRACR_FRACN3                   RCC_PLL3FRACR_FRACN3_Msk

    /********************  Bit definition for RCC_D1CCIPR register  ***************/
    #define RCC_D1CCIPR_FMCSEL_Pos                 (0U)
    #define RCC_D1CCIPR_FMCSEL_Msk                 (0x3UL << RCC_D1CCIPR_FMCSEL_Pos) /*!< 0x00000003 */
    #define RCC_D1CCIPR_FMCSEL                     RCC_D1CCIPR_FMCSEL_Msk
    #define RCC_D1CCIPR_FMCSEL_0                   (0x1UL << RCC_D1CCIPR_FMCSEL_Pos) /*!< 0x00000001 */
    #define RCC_D1CCIPR_FMCSEL_1                   (0x2UL << RCC_D1CCIPR_FMCSEL_Pos) /*!< 0x00000002 */
    #define RCC_D1CCIPR_QSPISEL_Pos                (4U)
    #define RCC_D1CCIPR_QSPISEL_Msk                (0x3UL << RCC_D1CCIPR_QSPISEL_Pos) /*!< 0x00000030 */
    #define RCC_D1CCIPR_QSPISEL                    RCC_D1CCIPR_QSPISEL_Msk
    #define RCC_D1CCIPR_QSPISEL_0                  (0x1UL << RCC_D1CCIPR_QSPISEL_Pos) /*!< 0x00000010 */
    #define RCC_D1CCIPR_QSPISEL_1                  (0x2UL << RCC_D1CCIPR_QSPISEL_Pos) /*!< 0x00000020 */
    #define RCC_D1CCIPR_SDMMCSEL_Pos               (16U)
    #define RCC_D1CCIPR_SDMMCSEL_Msk               (0x1UL << RCC_D1CCIPR_SDMMCSEL_Pos) /*!< 0x00010000 */
    #define RCC_D1CCIPR_SDMMCSEL                   RCC_D1CCIPR_SDMMCSEL_Msk
    #define RCC_D1CCIPR_CKPERSEL_Pos               (28U)
    #define RCC_D1CCIPR_CKPERSEL_Msk               (0x3UL << RCC_D1CCIPR_CKPERSEL_Pos) /*!< 0x30000000 */
    #define RCC_D1CCIPR_CKPERSEL                   RCC_D1CCIPR_CKPERSEL_Msk
    #define RCC_D1CCIPR_CKPERSEL_0                 (0x1UL << RCC_D1CCIPR_CKPERSEL_Pos) /*!< 0x10000000 */
    #define RCC_D1CCIPR_CKPERSEL_1                 (0x2UL << RCC_D1CCIPR_CKPERSEL_Pos) /*!< 0x20000000 */

    /********************  Bit definition for RCC_D2CCIP1R register  ***************/
    #define RCC_D2CCIP1R_SAI1SEL_Pos               (0U)
    #define RCC_D2CCIP1R_SAI1SEL_Msk               (0x7UL << RCC_D2CCIP1R_SAI1SEL_Pos) /*!< 0x00000007 */
    #define RCC_D2CCIP1R_SAI1SEL                   RCC_D2CCIP1R_SAI1SEL_Msk
    #define RCC_D2CCIP1R_SAI1SEL_0                 (0x1UL << RCC_D2CCIP1R_SAI1SEL_Pos) /*!< 0x00000001 */
    #define RCC_D2CCIP1R_SAI1SEL_1                 (0x2UL << RCC_D2CCIP1R_SAI1SEL_Pos) /*!< 0x00000002 */
    #define RCC_D2CCIP1R_SAI1SEL_2                 (0x4UL << RCC_D2CCIP1R_SAI1SEL_Pos) /*!< 0x00000004 */

    #define RCC_D2CCIP1R_SAI23SEL_Pos              (6U)
    #define RCC_D2CCIP1R_SAI23SEL_Msk              (0x7UL << RCC_D2CCIP1R_SAI23SEL_Pos) /*!< 0x000001C0 */
    #define RCC_D2CCIP1R_SAI23SEL                  RCC_D2CCIP1R_SAI23SEL_Msk
    #define RCC_D2CCIP1R_SAI23SEL_0                (0x1UL << RCC_D2CCIP1R_SAI23SEL_Pos) /*!< 0x00000040 */
    #define RCC_D2CCIP1R_SAI23SEL_1                (0x2UL << RCC_D2CCIP1R_SAI23SEL_Pos) /*!< 0x00000080 */
    #define RCC_D2CCIP1R_SAI23SEL_2                (0x4UL << RCC_D2CCIP1R_SAI23SEL_Pos) /*!< 0x00000100 */

    #define RCC_D2CCIP1R_SPI123SEL_Pos             (12U)
    #define RCC_D2CCIP1R_SPI123SEL_Msk             (0x7UL << RCC_D2CCIP1R_SPI123SEL_Pos) /*!< 0x00007000 */
    #define RCC_D2CCIP1R_SPI123SEL                 RCC_D2CCIP1R_SPI123SEL_Msk
    #define RCC_D2CCIP1R_SPI123SEL_0               (0x1UL << RCC_D2CCIP1R_SPI123SEL_Pos) /*!< 0x00001000 */
    #define RCC_D2CCIP1R_SPI123SEL_1               (0x2UL << RCC_D2CCIP1R_SPI123SEL_Pos) /*!< 0x00002000 */
    #define RCC_D2CCIP1R_SPI123SEL_2               (0x4UL << RCC_D2CCIP1R_SPI123SEL_Pos) /*!< 0x00004000 */

    #define RCC_D2CCIP1R_SPI45SEL_Pos              (16U)
    #define RCC_D2CCIP1R_SPI45SEL_Msk              (0x7UL << RCC_D2CCIP1R_SPI45SEL_Pos) /*!< 0x00070000 */
    #define RCC_D2CCIP1R_SPI45SEL                  RCC_D2CCIP1R_SPI45SEL_Msk
    #define RCC_D2CCIP1R_SPI45SEL_0                (0x1UL << RCC_D2CCIP1R_SPI45SEL_Pos) /*!< 0x00010000 */
    #define RCC_D2CCIP1R_SPI45SEL_1                (0x2UL << RCC_D2CCIP1R_SPI45SEL_Pos) /*!< 0x00020000 */
    #define RCC_D2CCIP1R_SPI45SEL_2                (0x4UL << RCC_D2CCIP1R_SPI45SEL_Pos) /*!< 0x00040000 */

    #define RCC_D2CCIP1R_SPDIFSEL_Pos              (20U)
    #define RCC_D2CCIP1R_SPDIFSEL_Msk              (0x3UL << RCC_D2CCIP1R_SPDIFSEL_Pos) /*!< 0x00300000 */
    #define RCC_D2CCIP1R_SPDIFSEL                  RCC_D2CCIP1R_SPDIFSEL_Msk
    #define RCC_D2CCIP1R_SPDIFSEL_0                (0x1UL << RCC_D2CCIP1R_SPDIFSEL_Pos) /*!< 0x00100000 */
    #define RCC_D2CCIP1R_SPDIFSEL_1                (0x2UL << RCC_D2CCIP1R_SPDIFSEL_Pos) /*!< 0x00200000 */

    #define RCC_D2CCIP1R_DFSDM1SEL_Pos             (24U)
    #define RCC_D2CCIP1R_DFSDM1SEL_Msk             (0x1UL << RCC_D2CCIP1R_DFSDM1SEL_Pos) /*!< 0x01000000 */
    #define RCC_D2CCIP1R_DFSDM1SEL                 RCC_D2CCIP1R_DFSDM1SEL_Msk

    #define RCC_D2CCIP1R_FDCANSEL_Pos              (28U)
    #define RCC_D2CCIP1R_FDCANSEL_Msk              (0x3UL << RCC_D2CCIP1R_FDCANSEL_Pos) /*!< 0x30000000 */
    #define RCC_D2CCIP1R_FDCANSEL                  RCC_D2CCIP1R_FDCANSEL_Msk
    #define RCC_D2CCIP1R_FDCANSEL_0                (0x1UL << RCC_D2CCIP1R_FDCANSEL_Pos) /*!< 0x10000000 */
    #define RCC_D2CCIP1R_FDCANSEL_1                (0x2UL << RCC_D2CCIP1R_FDCANSEL_Pos) /*!< 0x20000000 */

    #define RCC_D2CCIP1R_SWPSEL_Pos                (31U)
    #define RCC_D2CCIP1R_SWPSEL_Msk                (0x1UL << RCC_D2CCIP1R_SWPSEL_Pos) /*!< 0x80000000 */
    #define RCC_D2CCIP1R_SWPSEL                    RCC_D2CCIP1R_SWPSEL_Msk

    /********************  Bit definition for RCC_D2CCIP2R register  ***************/
    #define RCC_D2CCIP2R_USART16SEL_Pos            (3U)
    #define RCC_D2CCIP2R_USART16SEL_Msk            (0x7UL << RCC_D2CCIP2R_USART16SEL_Pos) /*!< 0x00000038 */
    #define RCC_D2CCIP2R_USART16SEL                RCC_D2CCIP2R_USART16SEL_Msk
    #define RCC_D2CCIP2R_USART16SEL_0              (0x1UL << RCC_D2CCIP2R_USART16SEL_Pos) /*!< 0x00000008 */
    #define RCC_D2CCIP2R_USART16SEL_1              (0x2UL << RCC_D2CCIP2R_USART16SEL_Pos) /*!< 0x00000010 */
    #define RCC_D2CCIP2R_USART16SEL_2              (0x4UL << RCC_D2CCIP2R_USART16SEL_Pos) /*!< 0x00000020 */

    #define RCC_D2CCIP2R_USART28SEL_Pos            (0U)
    #define RCC_D2CCIP2R_USART28SEL_Msk            (0x7UL << RCC_D2CCIP2R_USART28SEL_Pos) /*!< 0x00000007 */
    #define RCC_D2CCIP2R_USART28SEL                RCC_D2CCIP2R_USART28SEL_Msk
    #define RCC_D2CCIP2R_USART28SEL_0              (0x1UL << RCC_D2CCIP2R_USART28SEL_Pos) /*!< 0x00000001 */
    #define RCC_D2CCIP2R_USART28SEL_1              (0x2UL << RCC_D2CCIP2R_USART28SEL_Pos) /*!< 0x00000002 */
    #define RCC_D2CCIP2R_USART28SEL_2              (0x4UL << RCC_D2CCIP2R_USART28SEL_Pos) /*!< 0x00000004 */

    #define RCC_D2CCIP2R_RNGSEL_Pos                (8U)
    #define RCC_D2CCIP2R_RNGSEL_Msk                (0x3UL << RCC_D2CCIP2R_RNGSEL_Pos) /*!< 0x00000300 */
    #define RCC_D2CCIP2R_RNGSEL                    RCC_D2CCIP2R_RNGSEL_Msk
    #define RCC_D2CCIP2R_RNGSEL_0                  (0x1UL << RCC_D2CCIP2R_RNGSEL_Pos) /*!< 0x00000100 */
    #define RCC_D2CCIP2R_RNGSEL_1                  (0x2UL << RCC_D2CCIP2R_RNGSEL_Pos) /*!< 0x00000200 */

    #define RCC_D2CCIP2R_I2C123SEL_Pos             (12U)
    #define RCC_D2CCIP2R_I2C123SEL_Msk             (0x3UL << RCC_D2CCIP2R_I2C123SEL_Pos) /*!< 0x00003000 */
    #define RCC_D2CCIP2R_I2C123SEL                 RCC_D2CCIP2R_I2C123SEL_Msk
    #define RCC_D2CCIP2R_I2C123SEL_0               (0x1UL << RCC_D2CCIP2R_I2C123SEL_Pos) /*!< 0x00001000 */
    #define RCC_D2CCIP2R_I2C123SEL_1               (0x2UL << RCC_D2CCIP2R_I2C123SEL_Pos) /*!< 0x00002000 */

    #define RCC_D2CCIP2R_USBSEL_Pos                (20U)
    #define RCC_D2CCIP2R_USBSEL_Msk                (0x3UL << RCC_D2CCIP2R_USBSEL_Pos) /*!< 0x00300000 */
    #define RCC_D2CCIP2R_USBSEL                    RCC_D2CCIP2R_USBSEL_Msk
    #define RCC_D2CCIP2R_USBSEL_0                  (0x1UL << RCC_D2CCIP2R_USBSEL_Pos) /*!< 0x00100000 */
    #define RCC_D2CCIP2R_USBSEL_1                  (0x2UL << RCC_D2CCIP2R_USBSEL_Pos) /*!< 0x00200000 */

    #define RCC_D2CCIP2R_CECSEL_Pos                (22U)
    #define RCC_D2CCIP2R_CECSEL_Msk                (0x3UL << RCC_D2CCIP2R_CECSEL_Pos) /*!< 0x00C00000 */
    #define RCC_D2CCIP2R_CECSEL                    RCC_D2CCIP2R_CECSEL_Msk
    #define RCC_D2CCIP2R_CECSEL_0                  (0x1UL << RCC_D2CCIP2R_CECSEL_Pos) /*!< 0x00400000 */
    #define RCC_D2CCIP2R_CECSEL_1                  (0x2UL << RCC_D2CCIP2R_CECSEL_Pos) /*!< 0x00800000 */

    #define RCC_D2CCIP2R_LPTIM1SEL_Pos             (28U)
    #define RCC_D2CCIP2R_LPTIM1SEL_Msk             (0x7UL << RCC_D2CCIP2R_LPTIM1SEL_Pos) /*!< 0x70000000 */
    #define RCC_D2CCIP2R_LPTIM1SEL                 RCC_D2CCIP2R_LPTIM1SEL_Msk
    #define RCC_D2CCIP2R_LPTIM1SEL_0               (0x1UL << RCC_D2CCIP2R_LPTIM1SEL_Pos) /*!< 0x10000000 */
    #define RCC_D2CCIP2R_LPTIM1SEL_1               (0x2UL << RCC_D2CCIP2R_LPTIM1SEL_Pos) /*!< 0x20000000 */
    #define RCC_D2CCIP2R_LPTIM1SEL_2               (0x4UL << RCC_D2CCIP2R_LPTIM1SEL_Pos) /*!< 0x40000000 */

    /********************  Bit definition for RCC_D3CCIPR register  ***************/
    #define RCC_D3CCIPR_LPUART1SEL_Pos             (0U)
    #define RCC_D3CCIPR_LPUART1SEL_Msk             (0x7UL << RCC_D3CCIPR_LPUART1SEL_Pos) /*!< 0x00000007 */
    #define RCC_D3CCIPR_LPUART1SEL                 RCC_D3CCIPR_LPUART1SEL_Msk
    #define RCC_D3CCIPR_LPUART1SEL_0               (0x1UL << RCC_D3CCIPR_LPUART1SEL_Pos) /*!< 0x00000001 */
    #define RCC_D3CCIPR_LPUART1SEL_1               (0x2UL << RCC_D3CCIPR_LPUART1SEL_Pos) /*!< 0x00000002 */
    #define RCC_D3CCIPR_LPUART1SEL_2               (0x4UL << RCC_D3CCIPR_LPUART1SEL_Pos) /*!< 0x00000004 */

    #define RCC_D3CCIPR_I2C4SEL_Pos                (8U)
    #define RCC_D3CCIPR_I2C4SEL_Msk                (0x3UL << RCC_D3CCIPR_I2C4SEL_Pos) /*!< 0x00000300 */
    #define RCC_D3CCIPR_I2C4SEL                    RCC_D3CCIPR_I2C4SEL_Msk
    #define RCC_D3CCIPR_I2C4SEL_0                  (0x1UL << RCC_D3CCIPR_I2C4SEL_Pos) /*!< 0x00000100 */
    #define RCC_D3CCIPR_I2C4SEL_1                  (0x2UL << RCC_D3CCIPR_I2C4SEL_Pos) /*!< 0x00000200 */

    #define RCC_D3CCIPR_LPTIM2SEL_Pos              (10U)
    #define RCC_D3CCIPR_LPTIM2SEL_Msk              (0x7UL << RCC_D3CCIPR_LPTIM2SEL_Pos) /*!< 0x00001C00 */
    #define RCC_D3CCIPR_LPTIM2SEL                  RCC_D3CCIPR_LPTIM2SEL_Msk
    #define RCC_D3CCIPR_LPTIM2SEL_0                (0x1UL << RCC_D3CCIPR_LPTIM2SEL_Pos) /*!< 0x00000400 */
    #define RCC_D3CCIPR_LPTIM2SEL_1                (0x2UL << RCC_D3CCIPR_LPTIM2SEL_Pos) /*!< 0x00000800 */
    #define RCC_D3CCIPR_LPTIM2SEL_2                (0x4UL << RCC_D3CCIPR_LPTIM2SEL_Pos) /*!< 0x00001000 */

    #define RCC_D3CCIPR_LPTIM345SEL_Pos            (13U)
    #define RCC_D3CCIPR_LPTIM345SEL_Msk            (0x7UL << RCC_D3CCIPR_LPTIM345SEL_Pos) /*!< 0x0000E000 */
    #define RCC_D3CCIPR_LPTIM345SEL                RCC_D3CCIPR_LPTIM345SEL_Msk
    #define RCC_D3CCIPR_LPTIM345SEL_0              (0x1UL << RCC_D3CCIPR_LPTIM345SEL_Pos) /*!< 0x00002000 */
    #define RCC_D3CCIPR_LPTIM345SEL_1              (0x2UL << RCC_D3CCIPR_LPTIM345SEL_Pos) /*!< 0x00004000 */
    #define RCC_D3CCIPR_LPTIM345SEL_2              (0x4UL << RCC_D3CCIPR_LPTIM345SEL_Pos) /*!< 0x00008000 */

    #define RCC_D3CCIPR_SAI4ASEL_Pos               (21U)
    #define RCC_D3CCIPR_SAI4ASEL_Msk               (0x7UL << RCC_D3CCIPR_SAI4ASEL_Pos) /*!< 0x00E00000 */
    #define RCC_D3CCIPR_SAI4ASEL                   RCC_D3CCIPR_SAI4ASEL_Msk
    #define RCC_D3CCIPR_SAI4ASEL_0                 (0x1UL << RCC_D3CCIPR_SAI4ASEL_Pos) /*!< 0x00200000 */
    #define RCC_D3CCIPR_SAI4ASEL_1                 (0x2UL << RCC_D3CCIPR_SAI4ASEL_Pos) /*!< 0x00400000 */
    #define RCC_D3CCIPR_SAI4ASEL_2                 (0x4UL << RCC_D3CCIPR_SAI4ASEL_Pos) /*!< 0x00800000 */

    #define RCC_D3CCIPR_SAI4BSEL_Pos               (24U)
    #define RCC_D3CCIPR_SAI4BSEL_Msk               (0x7UL << RCC_D3CCIPR_SAI4BSEL_Pos) /*!< 0x07000000 */
    #define RCC_D3CCIPR_SAI4BSEL                   RCC_D3CCIPR_SAI4BSEL_Msk
    #define RCC_D3CCIPR_SAI4BSEL_0                 (0x1UL << RCC_D3CCIPR_SAI4BSEL_Pos) /*!< 0x01000000 */
    #define RCC_D3CCIPR_SAI4BSEL_1                 (0x2UL << RCC_D3CCIPR_SAI4BSEL_Pos) /*!< 0x02000000 */
    #define RCC_D3CCIPR_SAI4BSEL_2                 (0x4UL << RCC_D3CCIPR_SAI4BSEL_Pos) /*!< 0x04000000 */

    #define RCC_D3CCIPR_ADCSEL_Pos                 (16U)
    #define RCC_D3CCIPR_ADCSEL_Msk                 (0x3UL << RCC_D3CCIPR_ADCSEL_Pos) /*!< 0x00030000 */
    #define RCC_D3CCIPR_ADCSEL                     RCC_D3CCIPR_ADCSEL_Msk
    #define RCC_D3CCIPR_ADCSEL_0                   (0x1UL << RCC_D3CCIPR_ADCSEL_Pos) /*!< 0x00010000 */
    #define RCC_D3CCIPR_ADCSEL_1                   (0x2UL << RCC_D3CCIPR_ADCSEL_Pos) /*!< 0x00020000 */

    #define RCC_D3CCIPR_SPI6SEL_Pos                (28U)
    #define RCC_D3CCIPR_SPI6SEL_Msk                (0x7UL << RCC_D3CCIPR_SPI6SEL_Pos) /*!< 0x70000000 */
    #define RCC_D3CCIPR_SPI6SEL                    RCC_D3CCIPR_SPI6SEL_Msk
    #define RCC_D3CCIPR_SPI6SEL_0                  (0x1UL << RCC_D3CCIPR_SPI6SEL_Pos) /*!< 0x10000000 */
    #define RCC_D3CCIPR_SPI6SEL_1                  (0x2UL << RCC_D3CCIPR_SPI6SEL_Pos) /*!< 0x20000000 */
    #define RCC_D3CCIPR_SPI6SEL_2                  (0x4UL << RCC_D3CCIPR_SPI6SEL_Pos) /*!< 0x40000000 */
    /********************  Bit definition for RCC_CIER register  ******************/
    #define RCC_CIER_LSIRDYIE_Pos                  (0U)
    #define RCC_CIER_LSIRDYIE_Msk                  (0x1UL << RCC_CIER_LSIRDYIE_Pos) /*!< 0x00000001 */
    #define RCC_CIER_LSIRDYIE                      RCC_CIER_LSIRDYIE_Msk
    #define RCC_CIER_LSERDYIE_Pos                  (1U)
    #define RCC_CIER_LSERDYIE_Msk                  (0x1UL << RCC_CIER_LSERDYIE_Pos) /*!< 0x00000002 */
    #define RCC_CIER_LSERDYIE                      RCC_CIER_LSERDYIE_Msk
    #define RCC_CIER_HSIRDYIE_Pos                  (2U)
    #define RCC_CIER_HSIRDYIE_Msk                  (0x1UL << RCC_CIER_HSIRDYIE_Pos) /*!< 0x00000004 */
    #define RCC_CIER_HSIRDYIE                      RCC_CIER_HSIRDYIE_Msk
    #define RCC_CIER_HSERDYIE_Pos                  (3U)
    #define RCC_CIER_HSERDYIE_Msk                  (0x1UL << RCC_CIER_HSERDYIE_Pos) /*!< 0x00000008 */
    #define RCC_CIER_HSERDYIE                      RCC_CIER_HSERDYIE_Msk
    #define RCC_CIER_CSIRDYIE_Pos                  (4U)
    #define RCC_CIER_CSIRDYIE_Msk                  (0x1UL << RCC_CIER_CSIRDYIE_Pos) /*!< 0x00000010 */
    #define RCC_CIER_CSIRDYIE                      RCC_CIER_CSIRDYIE_Msk
    #define RCC_CIER_HSI48RDYIE_Pos                (5U)
    #define RCC_CIER_HSI48RDYIE_Msk                (0x1UL << RCC_CIER_HSI48RDYIE_Pos) /*!< 0x00000020 */
    #define RCC_CIER_HSI48RDYIE                    RCC_CIER_HSI48RDYIE_Msk
    #define RCC_CIER_PLL1RDYIE_Pos                 (6U)
    #define RCC_CIER_PLL1RDYIE_Msk                 (0x1UL << RCC_CIER_PLL1RDYIE_Pos) /*!< 0x00000040 */
    #define RCC_CIER_PLL1RDYIE                     RCC_CIER_PLL1RDYIE_Msk
    #define RCC_CIER_PLL2RDYIE_Pos                 (7U)
    #define RCC_CIER_PLL2RDYIE_Msk                 (0x1UL << RCC_CIER_PLL2RDYIE_Pos) /*!< 0x00000080 */
    #define RCC_CIER_PLL2RDYIE                     RCC_CIER_PLL2RDYIE_Msk
    #define RCC_CIER_PLL3RDYIE_Pos                 (8U)
    #define RCC_CIER_PLL3RDYIE_Msk                 (0x1UL << RCC_CIER_PLL3RDYIE_Pos) /*!< 0x00000100 */
    #define RCC_CIER_PLL3RDYIE                     RCC_CIER_PLL3RDYIE_Msk
    #define RCC_CIER_LSECSSIE_Pos                  (9U)
    #define RCC_CIER_LSECSSIE_Msk                  (0x1UL << RCC_CIER_LSECSSIE_Pos) /*!< 0x00000200 */
    #define RCC_CIER_LSECSSIE                      RCC_CIER_LSECSSIE_Msk

    /********************  Bit definition for RCC_CIFR register  ******************/
    #define RCC_CIFR_LSIRDYF_Pos                   (0U)
    #define RCC_CIFR_LSIRDYF_Msk                   (0x1UL << RCC_CIFR_LSIRDYF_Pos) /*!< 0x00000001 */
    #define RCC_CIFR_LSIRDYF                       RCC_CIFR_LSIRDYF_Msk
    #define RCC_CIFR_LSERDYF_Pos                   (1U)
    #define RCC_CIFR_LSERDYF_Msk                   (0x1UL << RCC_CIFR_LSERDYF_Pos) /*!< 0x00000002 */
    #define RCC_CIFR_LSERDYF                       RCC_CIFR_LSERDYF_Msk
    #define RCC_CIFR_HSIRDYF_Pos                   (2U)
    #define RCC_CIFR_HSIRDYF_Msk                   (0x1UL << RCC_CIFR_HSIRDYF_Pos) /*!< 0x00000004 */
    #define RCC_CIFR_HSIRDYF                       RCC_CIFR_HSIRDYF_Msk
    #define RCC_CIFR_HSERDYF_Pos                   (3U)
    #define RCC_CIFR_HSERDYF_Msk                   (0x1UL << RCC_CIFR_HSERDYF_Pos) /*!< 0x00000008 */
    #define RCC_CIFR_HSERDYF                       RCC_CIFR_HSERDYF_Msk
    #define RCC_CIFR_CSIRDYF_Pos                   (4U)
    #define RCC_CIFR_CSIRDYF_Msk                   (0x1UL << RCC_CIFR_CSIRDYF_Pos) /*!< 0x00000010 */
    #define RCC_CIFR_CSIRDYF                       RCC_CIFR_CSIRDYF_Msk
    #define RCC_CIFR_HSI48RDYF_Pos                 (5U)
    #define RCC_CIFR_HSI48RDYF_Msk                 (0x1UL << RCC_CIFR_HSI48RDYF_Pos) /*!< 0x00000020 */
    #define RCC_CIFR_HSI48RDYF                     RCC_CIFR_HSI48RDYF_Msk
    #define RCC_CIFR_PLLRDYF_Pos                   (6U)
    #define RCC_CIFR_PLLRDYF_Msk                   (0x1UL << RCC_CIFR_PLLRDYF_Pos) /*!< 0x00000040 */
    #define RCC_CIFR_PLLRDYF                       RCC_CIFR_PLLRDYF_Msk
    #define RCC_CIFR_PLL2RDYF_Pos                  (7U)
    #define RCC_CIFR_PLL2RDYF_Msk                  (0x1UL << RCC_CIFR_PLL2RDYF_Pos) /*!< 0x00000080 */
    #define RCC_CIFR_PLL2RDYF                      RCC_CIFR_PLL2RDYF_Msk
    #define RCC_CIFR_PLL3RDYF_Pos                  (8U)
    #define RCC_CIFR_PLL3RDYF_Msk                  (0x1UL << RCC_CIFR_PLL3RDYF_Pos) /*!< 0x00000100 */
    #define RCC_CIFR_PLL3RDYF                      RCC_CIFR_PLL3RDYF_Msk
    #define RCC_CIFR_LSECSSF_Pos                   (9U)
    #define RCC_CIFR_LSECSSF_Msk                   (0x1UL << RCC_CIFR_LSECSSF_Pos) /*!< 0x00000200 */
    #define RCC_CIFR_LSECSSF                       RCC_CIFR_LSECSSF_Msk
    #define RCC_CIFR_HSECSSF_Pos                   (10U)
    #define RCC_CIFR_HSECSSF_Msk                   (0x1UL << RCC_CIFR_HSECSSF_Pos) /*!< 0x00000400 */
    #define RCC_CIFR_HSECSSF                       RCC_CIFR_HSECSSF_Msk

    /********************  Bit definition for RCC_CICR register  ******************/
    #define RCC_CICR_LSIRDYC_Pos                   (0U)
    #define RCC_CICR_LSIRDYC_Msk                   (0x1UL << RCC_CICR_LSIRDYC_Pos) /*!< 0x00000001 */
    #define RCC_CICR_LSIRDYC                       RCC_CICR_LSIRDYC_Msk
    #define RCC_CICR_LSERDYC_Pos                   (1U)
    #define RCC_CICR_LSERDYC_Msk                   (0x1UL << RCC_CICR_LSERDYC_Pos) /*!< 0x00000002 */
    #define RCC_CICR_LSERDYC                       RCC_CICR_LSERDYC_Msk
    #define RCC_CICR_HSIRDYC_Pos                   (2U)
    #define RCC_CICR_HSIRDYC_Msk                   (0x1UL << RCC_CICR_HSIRDYC_Pos) /*!< 0x00000004 */
    #define RCC_CICR_HSIRDYC                       RCC_CICR_HSIRDYC_Msk
    #define RCC_CICR_HSERDYC_Pos                   (3U)
    #define RCC_CICR_HSERDYC_Msk                   (0x1UL << RCC_CICR_HSERDYC_Pos) /*!< 0x00000008 */
    #define RCC_CICR_HSERDYC                       RCC_CICR_HSERDYC_Msk
    #define RCC_CICR_CSIRDYC_Pos                   (4U)
    #define RCC_CICR_CSIRDYC_Msk                   (0x1UL << RCC_CICR_CSIRDYC_Pos) /*!< 0x00000010 */
    #define RCC_CICR_CSIRDYC                       RCC_CICR_CSIRDYC_Msk
    #define RCC_CICR_HSI48RDYC_Pos                 (5U)
    #define RCC_CICR_HSI48RDYC_Msk                 (0x1UL << RCC_CICR_HSI48RDYC_Pos) /*!< 0x00000020 */
    #define RCC_CICR_HSI48RDYC                     RCC_CICR_HSI48RDYC_Msk
    #define RCC_CICR_PLLRDYC_Pos                   (6U)
    #define RCC_CICR_PLLRDYC_Msk                   (0x1UL << RCC_CICR_PLLRDYC_Pos) /*!< 0x00000040 */
    #define RCC_CICR_PLLRDYC                       RCC_CICR_PLLRDYC_Msk
    #define RCC_CICR_PLL2RDYC_Pos                  (7U)
    #define RCC_CICR_PLL2RDYC_Msk                  (0x1UL << RCC_CICR_PLL2RDYC_Pos) /*!< 0x00000080 */
    #define RCC_CICR_PLL2RDYC                      RCC_CICR_PLL2RDYC_Msk
    #define RCC_CICR_PLL3RDYC_Pos                  (8U)
    #define RCC_CICR_PLL3RDYC_Msk                  (0x1UL << RCC_CICR_PLL3RDYC_Pos) /*!< 0x00000100 */
    #define RCC_CICR_PLL3RDYC                      RCC_CICR_PLL3RDYC_Msk
    #define RCC_CICR_LSECSSC_Pos                   (9U)
    #define RCC_CICR_LSECSSC_Msk                   (0x1UL << RCC_CICR_LSECSSC_Pos) /*!< 0x00000200 */
    #define RCC_CICR_LSECSSC                       RCC_CICR_LSECSSC_Msk
    #define RCC_CICR_HSECSSC_Pos                   (10U)
    #define RCC_CICR_HSECSSC_Msk                   (0x1UL << RCC_CICR_HSECSSC_Pos) /*!< 0x00000400 */
    #define RCC_CICR_HSECSSC                       RCC_CICR_HSECSSC_Msk

    /********************  Bit definition for RCC_BDCR register  ******************/
    #define RCC_BDCR_LSEON_Pos                     (0U)
    #define RCC_BDCR_LSEON_Msk                     (0x1UL << RCC_BDCR_LSEON_Pos)   /*!< 0x00000001 */
    #define RCC_BDCR_LSEON                         RCC_BDCR_LSEON_Msk
    #define RCC_BDCR_LSERDY_Pos                    (1U)
    #define RCC_BDCR_LSERDY_Msk                    (0x1UL << RCC_BDCR_LSERDY_Pos)  /*!< 0x00000002 */
    #define RCC_BDCR_LSERDY                        RCC_BDCR_LSERDY_Msk
    #define RCC_BDCR_LSEBYP_Pos                    (2U)
    #define RCC_BDCR_LSEBYP_Msk                    (0x1UL << RCC_BDCR_LSEBYP_Pos)  /*!< 0x00000004 */
    #define RCC_BDCR_LSEBYP                        RCC_BDCR_LSEBYP_Msk

    #define RCC_BDCR_LSEDRV_Pos                    (3U)
    #define RCC_BDCR_LSEDRV_Msk                    (0x3UL << RCC_BDCR_LSEDRV_Pos)  /*!< 0x00000018 */
    #define RCC_BDCR_LSEDRV                        RCC_BDCR_LSEDRV_Msk
    #define RCC_BDCR_LSEDRV_0                      (0x1UL << RCC_BDCR_LSEDRV_Pos)   /*!< 0x00000008 */
    #define RCC_BDCR_LSEDRV_1                      (0x2UL << RCC_BDCR_LSEDRV_Pos)   /*!< 0x00000010 */

    #define RCC_BDCR_LSECSSON_Pos                  (5U)
    #define RCC_BDCR_LSECSSON_Msk                  (0x1UL << RCC_BDCR_LSECSSON_Pos) /*!< 0x00000020 */
    #define RCC_BDCR_LSECSSON                      RCC_BDCR_LSECSSON_Msk
    #define RCC_BDCR_LSECSSD_Pos                   (6U)
    #define RCC_BDCR_LSECSSD_Msk                   (0x1UL << RCC_BDCR_LSECSSD_Pos) /*!< 0x00000040 */
    #define RCC_BDCR_LSECSSD                       RCC_BDCR_LSECSSD_Msk

    #define RCC_BDCR_RTCSEL_Pos                    (8U)
    #define RCC_BDCR_RTCSEL_Msk                    (0x3UL << RCC_BDCR_RTCSEL_Pos)  /*!< 0x00000300 */
    #define RCC_BDCR_RTCSEL                        RCC_BDCR_RTCSEL_Msk
    #define RCC_BDCR_RTCSEL_0                      (0x1UL << RCC_BDCR_RTCSEL_Pos)   /*!< 0x00000100 */
    #define RCC_BDCR_RTCSEL_1                      (0x2UL << RCC_BDCR_RTCSEL_Pos)   /*!< 0x00000200 */

    #define RCC_BDCR_RTCEN_Pos                     (15U)
    #define RCC_BDCR_RTCEN_Msk                     (0x1UL << RCC_BDCR_RTCEN_Pos)   /*!< 0x00008000 */
    #define RCC_BDCR_RTCEN                         RCC_BDCR_RTCEN_Msk
    #define RCC_BDCR_BDRST_Pos                     (16U)
    #define RCC_BDCR_BDRST_Msk                     (0x1UL << RCC_BDCR_BDRST_Pos)   /*!< 0x00010000 */
    #define RCC_BDCR_BDRST                         RCC_BDCR_BDRST_Msk
    /********************  Bit definition for RCC_CSR register  *******************/
    #define RCC_CSR_LSION_Pos                      (0U)
    #define RCC_CSR_LSION_Msk                      (0x1UL << RCC_CSR_LSION_Pos)    /*!< 0x00000001 */
    #define RCC_CSR_LSION                          RCC_CSR_LSION_Msk
    #define RCC_CSR_LSIRDY_Pos                     (1U)
    #define RCC_CSR_LSIRDY_Msk                     (0x1UL << RCC_CSR_LSIRDY_Pos)   /*!< 0x00000002 */
    #define RCC_CSR_LSIRDY                         RCC_CSR_LSIRDY_Msk


    /********************  Bit definition for RCC_AHB3ENR register  **************/
    #define RCC_AHB3ENR_MDMAEN_Pos                 (0U)
    #define RCC_AHB3ENR_MDMAEN_Msk                 (0x1UL << RCC_AHB3ENR_MDMAEN_Pos)       /*!< 0x00000001 */
    #define RCC_AHB3ENR_MDMAEN                     RCC_AHB3ENR_MDMAEN_Msk
    #define RCC_AHB3ENR_DMA2DEN_Pos                (4U)
    #define RCC_AHB3ENR_DMA2DEN_Msk                (0x1UL << RCC_AHB3ENR_DMA2DEN_Pos)      /*!< 0x00000010 */
    #define RCC_AHB3ENR_DMA2DEN                    RCC_AHB3ENR_DMA2DEN_Msk
    #define RCC_AHB3ENR_JPGDECEN_Pos               (5U)
    #define RCC_AHB3ENR_JPGDECEN_Msk               (0x1UL << RCC_AHB3ENR_JPGDECEN_Pos)     /*!< 0x00000020 */
    #define RCC_AHB3ENR_JPGDECEN                   RCC_AHB3ENR_JPGDECEN_Msk
    #define RCC_AHB3ENR_FMCEN_Pos                  (12U)
    #define RCC_AHB3ENR_FMCEN_Msk                  (0x1UL << RCC_AHB3ENR_FMCEN_Pos)        /*!< 0x00001000 */
    #define RCC_AHB3ENR_FMCEN                      RCC_AHB3ENR_FMCEN_Msk
    #define RCC_AHB3ENR_QSPIEN_Pos                 (14U)
    #define RCC_AHB3ENR_QSPIEN_Msk                 (0x1UL << RCC_AHB3ENR_QSPIEN_Pos)       /*!< 0x00004000 */
    #define RCC_AHB3ENR_QSPIEN                     RCC_AHB3ENR_QSPIEN_Msk
    #define RCC_AHB3ENR_SDMMC1EN_Pos               (16U)
    #define RCC_AHB3ENR_SDMMC1EN_Msk               (0x1UL << RCC_AHB3ENR_SDMMC1EN_Pos)     /*!< 0x00010000 */
    #define RCC_AHB3ENR_SDMMC1EN                   RCC_AHB3ENR_SDMMC1EN_Msk
    #define RCC_AHB3ENR_FLASHEN_Pos                (8U)
    #define RCC_AHB3ENR_FLASHEN_Msk                (0x1UL << RCC_AHB3ENR_FLASHEN_Pos)      /*!< 0x00000100 */
    #define RCC_AHB3ENR_FLASHEN                    RCC_AHB3ENR_FLASHEN_Msk
    #define RCC_AHB3ENR_DTCM1EN_Pos                (28U)
    #define RCC_AHB3ENR_DTCM1EN_Msk                (0x1UL << RCC_AHB3ENR_DTCM1EN_Pos)      /*!< 0x10000000 */
    #define RCC_AHB3ENR_DTCM1EN                    RCC_AHB3ENR_DTCM1EN_Msk
    #define RCC_AHB3ENR_DTCM2EN_Pos                (29U)
    #define RCC_AHB3ENR_DTCM2EN_Msk                (0x1UL << RCC_AHB3ENR_DTCM2EN_Pos)      /*!< 0x20000000 */
    #define RCC_AHB3ENR_DTCM2EN                    RCC_AHB3ENR_DTCM2EN_Msk
    #define RCC_AHB3ENR_ITCMEN_Pos                 (30U)
    #define RCC_AHB3ENR_ITCMEN_Msk                 (0x1UL << RCC_AHB3ENR_ITCMEN_Pos)       /*!< 0x40000000 */
    #define RCC_AHB3ENR_ITCMEN                     RCC_AHB3ENR_ITCMEN_Msk
    #define RCC_AHB3ENR_AXISRAMEN_Pos              (31U)
    #define RCC_AHB3ENR_AXISRAMEN_Msk              (0x1UL << RCC_AHB3ENR_AXISRAMEN_Pos)    /*!< 0x80000000 */
    #define RCC_AHB3ENR_AXISRAMEN                  RCC_AHB3ENR_AXISRAMEN_Msk

    /* Legacy define */
    #define RCC_AHB3ENR_D1SRAM1EN_Pos              RCC_AHB3ENR_AXISRAMEN_Pos
    #define RCC_AHB3ENR_D1SRAM1EN_Msk              RCC_AHB3ENR_AXISRAMEN_Msk
    #define RCC_AHB3ENR_D1SRAM1EN                  RCC_AHB3ENR_AXISRAMEN

    /********************  Bit definition for RCC_AHB1ENR register  ***************/
    #define RCC_AHB1ENR_DMA1EN_Pos                 (0U)
    #define RCC_AHB1ENR_DMA1EN_Msk                 (0x1UL << RCC_AHB1ENR_DMA1EN_Pos)          /*!< 0x00000001 */
    #define RCC_AHB1ENR_DMA1EN                     RCC_AHB1ENR_DMA1EN_Msk
    #define RCC_AHB1ENR_DMA2EN_Pos                 (1U)
    #define RCC_AHB1ENR_DMA2EN_Msk                 (0x1UL << RCC_AHB1ENR_DMA2EN_Pos)          /*!< 0x00000002 */
    #define RCC_AHB1ENR_DMA2EN                     RCC_AHB1ENR_DMA2EN_Msk
    #define RCC_AHB1ENR_ADC12EN_Pos                (5U)
    #define RCC_AHB1ENR_ADC12EN_Msk                (0x1UL << RCC_AHB1ENR_ADC12EN_Pos)         /*!< 0x00000020 */
    #define RCC_AHB1ENR_ADC12EN                    RCC_AHB1ENR_ADC12EN_Msk
    #define RCC_AHB1ENR_ARTEN_Pos                  (14U)
    #define RCC_AHB1ENR_ARTEN_Msk                  (0x1UL << RCC_AHB1ENR_ARTEN_Pos)           /*!< 0x00004000 */
    #define RCC_AHB1ENR_ARTEN                      RCC_AHB1ENR_ARTEN_Msk
    #define RCC_AHB1ENR_ETH1MACEN_Pos              (15U)
    #define RCC_AHB1ENR_ETH1MACEN_Msk              (0x1UL << RCC_AHB1ENR_ETH1MACEN_Pos)       /*!< 0x00008000 */
    #define RCC_AHB1ENR_ETH1MACEN                  RCC_AHB1ENR_ETH1MACEN_Msk
    #define RCC_AHB1ENR_ETH1TXEN_Pos               (16U)
    #define RCC_AHB1ENR_ETH1TXEN_Msk               (0x1UL << RCC_AHB1ENR_ETH1TXEN_Pos)        /*!< 0x00010000 */
    #define RCC_AHB1ENR_ETH1TXEN                   RCC_AHB1ENR_ETH1TXEN_Msk
    #define RCC_AHB1ENR_ETH1RXEN_Pos               (17U)
    #define RCC_AHB1ENR_ETH1RXEN_Msk               (0x1UL << RCC_AHB1ENR_ETH1RXEN_Pos)        /*!< 0x00020000 */
    #define RCC_AHB1ENR_ETH1RXEN                   RCC_AHB1ENR_ETH1RXEN_Msk
    #define RCC_AHB1ENR_USB1OTGHSEN_Pos            (25U)
    #define RCC_AHB1ENR_USB1OTGHSEN_Msk            (0x1UL << RCC_AHB1ENR_USB1OTGHSEN_Pos)     /*!< 0x02000000 */
    #define RCC_AHB1ENR_USB1OTGHSEN                RCC_AHB1ENR_USB1OTGHSEN_Msk
    #define RCC_AHB1ENR_USB1OTGHSULPIEN_Pos        (26U)
    #define RCC_AHB1ENR_USB1OTGHSULPIEN_Msk        (0x1UL << RCC_AHB1ENR_USB1OTGHSULPIEN_Pos) /*!< 0x04000000 */
    #define RCC_AHB1ENR_USB1OTGHSULPIEN            RCC_AHB1ENR_USB1OTGHSULPIEN_Msk
    #define RCC_AHB1ENR_USB2OTGFSEN_Pos            (27U)
    #define RCC_AHB1ENR_USB2OTGFSEN_Msk            (0x1UL << RCC_AHB1ENR_USB2OTGFSEN_Pos)     /*!< 0x08000000 */
    #define RCC_AHB1ENR_USB2OTGFSEN                RCC_AHB1ENR_USB2OTGFSEN_Msk
    #define RCC_AHB1ENR_USB2OTGFSULPIEN_Pos        (28U)
    #define RCC_AHB1ENR_USB2OTGFSULPIEN_Msk        (0x1UL << RCC_AHB1ENR_USB2OTGFSULPIEN_Pos) /*!< 0x10000000 */
    #define RCC_AHB1ENR_USB2OTGFSULPIEN            RCC_AHB1ENR_USB2OTGFSULPIEN_Msk

    /* Legacy define */
    #define RCC_AHB1ENR_USB2OTGHSEN_Pos            RCC_AHB1ENR_USB2OTGFSEN_Pos
    #define RCC_AHB1ENR_USB2OTGHSEN_Msk            RCC_AHB1ENR_USB2OTGFSEN_Msk
    #define RCC_AHB1ENR_USB2OTGHSEN                RCC_AHB1ENR_USB2OTGFSEN
    #define RCC_AHB1ENR_USB2OTGHSULPIEN_Pos        RCC_AHB1ENR_USB2OTGFSULPIEN_Pos
    #define RCC_AHB1ENR_USB2OTGHSULPIEN_Msk        RCC_AHB1ENR_USB2OTGFSULPIEN_Msk
    #define RCC_AHB1ENR_USB2OTGHSULPIEN            RCC_AHB1ENR_USB2OTGFSULPIEN


    /********************  Bit definition for RCC_AHB2ENR register  ***************/
    #define RCC_AHB2ENR_DCMIEN_Pos                 (0U)
    #define RCC_AHB2ENR_DCMIEN_Msk                 (0x1UL << RCC_AHB2ENR_DCMIEN_Pos)          /*!< 0x00000001 */
    #define RCC_AHB2ENR_DCMIEN                     RCC_AHB2ENR_DCMIEN_Msk
    #define RCC_AHB2ENR_RNGEN_Pos                  (6U)
    #define RCC_AHB2ENR_RNGEN_Msk                  (0x1UL << RCC_AHB2ENR_RNGEN_Pos)           /*!< 0x00000040 */
    #define RCC_AHB2ENR_RNGEN                      RCC_AHB2ENR_RNGEN_Msk
    #define RCC_AHB2ENR_SDMMC2EN_Pos               (9U)
    #define RCC_AHB2ENR_SDMMC2EN_Msk               (0x1UL << RCC_AHB2ENR_SDMMC2EN_Pos)        /*!< 0x00000200 */
    #define RCC_AHB2ENR_SDMMC2EN                   RCC_AHB2ENR_SDMMC2EN_Msk
    #define RCC_AHB2ENR_SRAM1EN_Pos                (29U)
    #define RCC_AHB2ENR_SRAM1EN_Msk                (0x1UL << RCC_AHB2ENR_SRAM1EN_Pos)       /*!< 0x20000000 */
    #define RCC_AHB2ENR_SRAM1EN                    RCC_AHB2ENR_SRAM1EN_Msk
    #define RCC_AHB2ENR_SRAM2EN_Pos                (30U)
    #define RCC_AHB2ENR_SRAM2EN_Msk                (0x1UL << RCC_AHB2ENR_SRAM2EN_Pos)       /*!< 0x40000000 */
    #define RCC_AHB2ENR_SRAM2EN                    RCC_AHB2ENR_SRAM2EN_Msk
    #define RCC_AHB2ENR_SRAM3EN_Pos                (31U)
    #define RCC_AHB2ENR_SRAM3EN_Msk                (0x1UL << RCC_AHB2ENR_SRAM3EN_Pos)       /*!< 0x80000000 */
    #define RCC_AHB2ENR_SRAM3EN                    RCC_AHB2ENR_SRAM3EN_Msk

    /* Legacy define */
    #define RCC_AHB2ENR_D2SRAM1EN_Pos              RCC_AHB2ENR_SRAM1EN_Pos
    #define RCC_AHB2ENR_D2SRAM1EN_Msk              RCC_AHB2ENR_SRAM1EN_Msk
    #define RCC_AHB2ENR_D2SRAM1EN                  RCC_AHB2ENR_SRAM1EN
    #define RCC_AHB2ENR_D2SRAM2EN_Pos              RCC_AHB2ENR_SRAM2EN_Pos
    #define RCC_AHB2ENR_D2SRAM2EN_Msk              RCC_AHB2ENR_SRAM2EN_Msk
    #define RCC_AHB2ENR_D2SRAM2EN                  RCC_AHB2ENR_SRAM2EN
    #define RCC_AHB2ENR_D2SRAM3EN_Pos              RCC_AHB2ENR_SRAM3EN_Pos
    #define RCC_AHB2ENR_D2SRAM3EN_Msk              RCC_AHB2ENR_SRAM3EN_Msk
    #define RCC_AHB2ENR_D2SRAM3EN                  RCC_AHB2ENR_SRAM3EN

    /********************  Bit definition for RCC_AHB4ENR register  ******************/
    #define RCC_AHB4ENR_GPIOAEN_Pos                (0U)
    #define RCC_AHB4ENR_GPIOAEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOAEN_Pos)         /*!< 0x00000001 */
    #define RCC_AHB4ENR_GPIOAEN                    RCC_AHB4ENR_GPIOAEN_Msk
    #define RCC_AHB4ENR_GPIOBEN_Pos                (1U)
    #define RCC_AHB4ENR_GPIOBEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOBEN_Pos)         /*!< 0x00000002 */
    #define RCC_AHB4ENR_GPIOBEN                    RCC_AHB4ENR_GPIOBEN_Msk
    #define RCC_AHB4ENR_GPIOCEN_Pos                (2U)
    #define RCC_AHB4ENR_GPIOCEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOCEN_Pos)         /*!< 0x00000004 */
    #define RCC_AHB4ENR_GPIOCEN                    RCC_AHB4ENR_GPIOCEN_Msk
    #define RCC_AHB4ENR_GPIODEN_Pos                (3U)
    #define RCC_AHB4ENR_GPIODEN_Msk                (0x1UL << RCC_AHB4ENR_GPIODEN_Pos)         /*!< 0x00000008 */
    #define RCC_AHB4ENR_GPIODEN                    RCC_AHB4ENR_GPIODEN_Msk
    #define RCC_AHB4ENR_GPIOEEN_Pos                (4U)
    #define RCC_AHB4ENR_GPIOEEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOEEN_Pos)         /*!< 0x00000010 */
    #define RCC_AHB4ENR_GPIOEEN                    RCC_AHB4ENR_GPIOEEN_Msk
    #define RCC_AHB4ENR_GPIOFEN_Pos                (5U)
    #define RCC_AHB4ENR_GPIOFEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOFEN_Pos)         /*!< 0x00000020 */
    #define RCC_AHB4ENR_GPIOFEN                    RCC_AHB4ENR_GPIOFEN_Msk
    #define RCC_AHB4ENR_GPIOGEN_Pos                (6U)
    #define RCC_AHB4ENR_GPIOGEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOGEN_Pos)         /*!< 0x00000040 */
    #define RCC_AHB4ENR_GPIOGEN                    RCC_AHB4ENR_GPIOGEN_Msk
    #define RCC_AHB4ENR_GPIOHEN_Pos                (7U)
    #define RCC_AHB4ENR_GPIOHEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOHEN_Pos)         /*!< 0x00000080 */
    #define RCC_AHB4ENR_GPIOHEN                    RCC_AHB4ENR_GPIOHEN_Msk
    #define RCC_AHB4ENR_GPIOIEN_Pos                (8U)
    #define RCC_AHB4ENR_GPIOIEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOIEN_Pos)         /*!< 0x00000100 */
    #define RCC_AHB4ENR_GPIOIEN                    RCC_AHB4ENR_GPIOIEN_Msk
    #define RCC_AHB4ENR_GPIOJEN_Pos                (9U)
    #define RCC_AHB4ENR_GPIOJEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOJEN_Pos)         /*!< 0x00000200 */
    #define RCC_AHB4ENR_GPIOJEN                    RCC_AHB4ENR_GPIOJEN_Msk
    #define RCC_AHB4ENR_GPIOKEN_Pos                (10U)
    #define RCC_AHB4ENR_GPIOKEN_Msk                (0x1UL << RCC_AHB4ENR_GPIOKEN_Pos)         /*!< 0x00000400 */
    #define RCC_AHB4ENR_GPIOKEN                    RCC_AHB4ENR_GPIOKEN_Msk
    #define RCC_AHB4ENR_CRCEN_Pos                  (19U)
    #define RCC_AHB4ENR_CRCEN_Msk                  (0x1UL << RCC_AHB4ENR_CRCEN_Pos)           /*!< 0x00080000 */
    #define RCC_AHB4ENR_CRCEN                      RCC_AHB4ENR_CRCEN_Msk
    #define RCC_AHB4ENR_BDMAEN_Pos                 (21U)
    #define RCC_AHB4ENR_BDMAEN_Msk                 (0x1UL << RCC_AHB4ENR_BDMAEN_Pos)          /*!< 0x00200000 */
    #define RCC_AHB4ENR_BDMAEN                     RCC_AHB4ENR_BDMAEN_Msk
    #define RCC_AHB4ENR_ADC3EN_Pos                 (24U)
    #define RCC_AHB4ENR_ADC3EN_Msk                 (0x1UL << RCC_AHB4ENR_ADC3EN_Pos)          /*!< 0x01000000 */
    #define RCC_AHB4ENR_ADC3EN                     RCC_AHB4ENR_ADC3EN_Msk
    #define RCC_AHB4ENR_HSEMEN_Pos                 (25U)
    #define RCC_AHB4ENR_HSEMEN_Msk                 (0x1UL << RCC_AHB4ENR_HSEMEN_Pos)          /*!< 0x02000000 */
    #define RCC_AHB4ENR_HSEMEN                     RCC_AHB4ENR_HSEMEN_Msk
    #define RCC_AHB4ENR_BKPRAMEN_Pos               (28U)
    #define RCC_AHB4ENR_BKPRAMEN_Msk               (0x1UL << RCC_AHB4ENR_BKPRAMEN_Pos)        /*!< 0x10000000 */
    #define RCC_AHB4ENR_BKPRAMEN                   RCC_AHB4ENR_BKPRAMEN_Msk

    /********************  Bit definition for RCC_APB3ENR register  ******************/
    #define RCC_APB3ENR_LTDCEN_Pos                 (3U)
    #define RCC_APB3ENR_LTDCEN_Msk                 (0x1UL << RCC_APB3ENR_LTDCEN_Pos) /*!< 0x00000008 */
    #define RCC_APB3ENR_LTDCEN                     RCC_APB3ENR_LTDCEN_Msk
    #define RCC_APB3ENR_WWDG1EN_Pos                (6U)
    #define RCC_APB3ENR_WWDG1EN_Msk                (0x1UL << RCC_APB3ENR_WWDG1EN_Pos) /*!< 0x00000040 */
    #define RCC_APB3ENR_WWDG1EN                    RCC_APB3ENR_WWDG1EN_Msk

    /********************  Bit definition for RCC_APB1LENR register  ******************/

    #define RCC_APB1LENR_TIM2EN_Pos                (0U)
    #define RCC_APB1LENR_TIM2EN_Msk                (0x1UL << RCC_APB1LENR_TIM2EN_Pos) /*!< 0x00000001 */
    #define RCC_APB1LENR_TIM2EN                    RCC_APB1LENR_TIM2EN_Msk
    #define RCC_APB1LENR_TIM3EN_Pos                (1U)
    #define RCC_APB1LENR_TIM3EN_Msk                (0x1UL << RCC_APB1LENR_TIM3EN_Pos) /*!< 0x00000002 */
    #define RCC_APB1LENR_TIM3EN                    RCC_APB1LENR_TIM3EN_Msk
    #define RCC_APB1LENR_TIM4EN_Pos                (2U)
    #define RCC_APB1LENR_TIM4EN_Msk                (0x1UL << RCC_APB1LENR_TIM4EN_Pos) /*!< 0x00000004 */
    #define RCC_APB1LENR_TIM4EN                    RCC_APB1LENR_TIM4EN_Msk
    #define RCC_APB1LENR_TIM5EN_Pos                (3U)
    #define RCC_APB1LENR_TIM5EN_Msk                (0x1UL << RCC_APB1LENR_TIM5EN_Pos) /*!< 0x00000008 */
    #define RCC_APB1LENR_TIM5EN                    RCC_APB1LENR_TIM5EN_Msk
    #define RCC_APB1LENR_TIM6EN_Pos                (4U)
    #define RCC_APB1LENR_TIM6EN_Msk                (0x1UL << RCC_APB1LENR_TIM6EN_Pos) /*!< 0x00000010 */
    #define RCC_APB1LENR_TIM6EN                    RCC_APB1LENR_TIM6EN_Msk
    #define RCC_APB1LENR_TIM7EN_Pos                (5U)
    #define RCC_APB1LENR_TIM7EN_Msk                (0x1UL << RCC_APB1LENR_TIM7EN_Pos) /*!< 0x00000020 */
    #define RCC_APB1LENR_TIM7EN                    RCC_APB1LENR_TIM7EN_Msk
    #define RCC_APB1LENR_TIM12EN_Pos               (6U)
    #define RCC_APB1LENR_TIM12EN_Msk               (0x1UL << RCC_APB1LENR_TIM12EN_Pos) /*!< 0x00000040 */
    #define RCC_APB1LENR_TIM12EN                   RCC_APB1LENR_TIM12EN_Msk
    #define RCC_APB1LENR_TIM13EN_Pos               (7U)
    #define RCC_APB1LENR_TIM13EN_Msk               (0x1UL << RCC_APB1LENR_TIM13EN_Pos) /*!< 0x00000080 */
    #define RCC_APB1LENR_TIM13EN                   RCC_APB1LENR_TIM13EN_Msk
    #define RCC_APB1LENR_TIM14EN_Pos               (8U)
    #define RCC_APB1LENR_TIM14EN_Msk               (0x1UL << RCC_APB1LENR_TIM14EN_Pos) /*!< 0x00000100 */
    #define RCC_APB1LENR_TIM14EN                   RCC_APB1LENR_TIM14EN_Msk
    #define RCC_APB1LENR_LPTIM1EN_Pos              (9U)
    #define RCC_APB1LENR_LPTIM1EN_Msk              (0x1UL << RCC_APB1LENR_LPTIM1EN_Pos) /*!< 0x00000200 */
    #define RCC_APB1LENR_LPTIM1EN                  RCC_APB1LENR_LPTIM1EN_Msk

    #define RCC_APB1LENR_WWDG2EN_Pos               (11U)
    #define RCC_APB1LENR_WWDG2EN_Msk               (0x1UL << RCC_APB1LENR_WWDG2EN_Pos) /*!< 0x00000800 */
    #define RCC_APB1LENR_WWDG2EN                   RCC_APB1LENR_WWDG2EN_Msk

    #define RCC_APB1LENR_SPI2EN_Pos                (14U)
    #define RCC_APB1LENR_SPI2EN_Msk                (0x1UL << RCC_APB1LENR_SPI2EN_Pos) /*!< 0x00004000 */
    #define RCC_APB1LENR_SPI2EN                    RCC_APB1LENR_SPI2EN_Msk
    #define RCC_APB1LENR_SPI3EN_Pos                (15U)
    #define RCC_APB1LENR_SPI3EN_Msk                (0x1UL << RCC_APB1LENR_SPI3EN_Pos) /*!< 0x00008000 */
    #define RCC_APB1LENR_SPI3EN                    RCC_APB1LENR_SPI3EN_Msk
    #define RCC_APB1LENR_SPDIFRXEN_Pos             (16U)
    #define RCC_APB1LENR_SPDIFRXEN_Msk             (0x1UL << RCC_APB1LENR_SPDIFRXEN_Pos) /*!< 0x00010000 */
    #define RCC_APB1LENR_SPDIFRXEN                 RCC_APB1LENR_SPDIFRXEN_Msk
    #define RCC_APB1LENR_USART2EN_Pos              (17U)
    #define RCC_APB1LENR_USART2EN_Msk              (0x1UL << RCC_APB1LENR_USART2EN_Pos) /*!< 0x00020000 */
    #define RCC_APB1LENR_USART2EN                  RCC_APB1LENR_USART2EN_Msk
    #define RCC_APB1LENR_USART3EN_Pos              (18U)
    #define RCC_APB1LENR_USART3EN_Msk              (0x1UL << RCC_APB1LENR_USART3EN_Pos) /*!< 0x00040000 */
    #define RCC_APB1LENR_USART3EN                  RCC_APB1LENR_USART3EN_Msk
    #define RCC_APB1LENR_UART4EN_Pos               (19U)
    #define RCC_APB1LENR_UART4EN_Msk               (0x1UL << RCC_APB1LENR_UART4EN_Pos) /*!< 0x00080000 */
    #define RCC_APB1LENR_UART4EN                   RCC_APB1LENR_UART4EN_Msk
    #define RCC_APB1LENR_UART5EN_Pos               (20U)
    #define RCC_APB1LENR_UART5EN_Msk               (0x1UL << RCC_APB1LENR_UART5EN_Pos) /*!< 0x00100000 */
    #define RCC_APB1LENR_UART5EN                   RCC_APB1LENR_UART5EN_Msk
    #define RCC_APB1LENR_I2C1EN_Pos                (21U)
    #define RCC_APB1LENR_I2C1EN_Msk                (0x1UL << RCC_APB1LENR_I2C1EN_Pos) /*!< 0x00200000 */
    #define RCC_APB1LENR_I2C1EN                    RCC_APB1LENR_I2C1EN_Msk
    #define RCC_APB1LENR_I2C2EN_Pos                (22U)
    #define RCC_APB1LENR_I2C2EN_Msk                (0x1UL << RCC_APB1LENR_I2C2EN_Pos) /*!< 0x00400000 */
    #define RCC_APB1LENR_I2C2EN                    RCC_APB1LENR_I2C2EN_Msk
    #define RCC_APB1LENR_I2C3EN_Pos                (23U)
    #define RCC_APB1LENR_I2C3EN_Msk                (0x1UL << RCC_APB1LENR_I2C3EN_Pos) /*!< 0x00800000 */
    #define RCC_APB1LENR_I2C3EN                    RCC_APB1LENR_I2C3EN_Msk
    #define RCC_APB1LENR_CECEN_Pos                 (27U)
    #define RCC_APB1LENR_CECEN_Msk                 (0x1UL << RCC_APB1LENR_CECEN_Pos) /*!< 0x08000000 */
    #define RCC_APB1LENR_CECEN                     RCC_APB1LENR_CECEN_Msk
    #define RCC_APB1LENR_DAC12EN_Pos               (29U)
    #define RCC_APB1LENR_DAC12EN_Msk               (0x1UL << RCC_APB1LENR_DAC12EN_Pos) /*!< 0x20000000 */
    #define RCC_APB1LENR_DAC12EN                   RCC_APB1LENR_DAC12EN_Msk
    #define RCC_APB1LENR_UART7EN_Pos               (30U)
    #define RCC_APB1LENR_UART7EN_Msk               (0x1UL << RCC_APB1LENR_UART7EN_Pos) /*!< 0x40000000 */
    #define RCC_APB1LENR_UART7EN                   RCC_APB1LENR_UART7EN_Msk
    #define RCC_APB1LENR_UART8EN_Pos               (31U)
    #define RCC_APB1LENR_UART8EN_Msk               (0x1UL << RCC_APB1LENR_UART8EN_Pos) /*!< 0x80000000 */
    #define RCC_APB1LENR_UART8EN                   RCC_APB1LENR_UART8EN_Msk

    /* Legacy define */
    #define RCC_APB1LENR_HDMICECEN_Pos             RCC_APB1LENR_CECEN_Pos
    #define RCC_APB1LENR_HDMICECEN_Msk             RCC_APB1LENR_CECEN_Msk
    #define RCC_APB1LENR_HDMICECEN                 RCC_APB1LENR_CECEN
    /********************  Bit definition for RCC_APB1HENR register  ******************/
    #define RCC_APB1HENR_CRSEN_Pos                 (1U)
    #define RCC_APB1HENR_CRSEN_Msk                 (0x1UL << RCC_APB1HENR_CRSEN_Pos) /*!< 0x00000002 */
    #define RCC_APB1HENR_CRSEN                     RCC_APB1HENR_CRSEN_Msk
    #define RCC_APB1HENR_SWPMIEN_Pos               (2U)
    #define RCC_APB1HENR_SWPMIEN_Msk               (0x1UL << RCC_APB1HENR_SWPMIEN_Pos) /*!< 0x00000004 */
    #define RCC_APB1HENR_SWPMIEN                   RCC_APB1HENR_SWPMIEN_Msk
    #define RCC_APB1HENR_OPAMPEN_Pos               (4U)
    #define RCC_APB1HENR_OPAMPEN_Msk               (0x1UL << RCC_APB1HENR_OPAMPEN_Pos) /*!< 0x00000010 */
    #define RCC_APB1HENR_OPAMPEN                   RCC_APB1HENR_OPAMPEN_Msk
    #define RCC_APB1HENR_MDIOSEN_Pos               (5U)
    #define RCC_APB1HENR_MDIOSEN_Msk               (0x1UL << RCC_APB1HENR_MDIOSEN_Pos) /*!< 0x00000020 */
    #define RCC_APB1HENR_MDIOSEN                   RCC_APB1HENR_MDIOSEN_Msk
    #define RCC_APB1HENR_FDCANEN_Pos               (8U)
    #define RCC_APB1HENR_FDCANEN_Msk               (0x1UL << RCC_APB1HENR_FDCANEN_Pos) /*!< 0x00000100 */
    #define RCC_APB1HENR_FDCANEN                   RCC_APB1HENR_FDCANEN_Msk

    /********************  Bit definition for RCC_APB2ENR register  ******************/
    #define RCC_APB2ENR_TIM1EN_Pos                 (0U)
    #define RCC_APB2ENR_TIM1EN_Msk                 (0x1UL << RCC_APB2ENR_TIM1EN_Pos) /*!< 0x00000001 */
    #define RCC_APB2ENR_TIM1EN                     RCC_APB2ENR_TIM1EN_Msk
    #define RCC_APB2ENR_TIM8EN_Pos                 (1U)
    #define RCC_APB2ENR_TIM8EN_Msk                 (0x1UL << RCC_APB2ENR_TIM8EN_Pos) /*!< 0x00000002 */
    #define RCC_APB2ENR_TIM8EN                     RCC_APB2ENR_TIM8EN_Msk
    #define RCC_APB2ENR_USART1EN_Pos               (4U)
    #define RCC_APB2ENR_USART1EN_Msk               (0x1UL << RCC_APB2ENR_USART1EN_Pos) /*!< 0x00000010 */
    #define RCC_APB2ENR_USART1EN                   RCC_APB2ENR_USART1EN_Msk
    #define RCC_APB2ENR_USART6EN_Pos               (5U)
    #define RCC_APB2ENR_USART6EN_Msk               (0x1UL << RCC_APB2ENR_USART6EN_Pos) /*!< 0x00000020 */
    #define RCC_APB2ENR_USART6EN                   RCC_APB2ENR_USART6EN_Msk
    #define RCC_APB2ENR_SPI1EN_Pos                 (12U)
    #define RCC_APB2ENR_SPI1EN_Msk                 (0x1UL << RCC_APB2ENR_SPI1EN_Pos) /*!< 0x00001000 */
    #define RCC_APB2ENR_SPI1EN                     RCC_APB2ENR_SPI1EN_Msk
    #define RCC_APB2ENR_SPI4EN_Pos                 (13U)
    #define RCC_APB2ENR_SPI4EN_Msk                 (0x1UL << RCC_APB2ENR_SPI4EN_Pos) /*!< 0x00002000 */
    #define RCC_APB2ENR_SPI4EN                     RCC_APB2ENR_SPI4EN_Msk
    #define RCC_APB2ENR_TIM15EN_Pos                (16U)
    #define RCC_APB2ENR_TIM15EN_Msk                (0x1UL << RCC_APB2ENR_TIM15EN_Pos) /*!< 0x00010000 */
    #define RCC_APB2ENR_TIM15EN                    RCC_APB2ENR_TIM15EN_Msk
    #define RCC_APB2ENR_TIM16EN_Pos                (17U)
    #define RCC_APB2ENR_TIM16EN_Msk                (0x1UL << RCC_APB2ENR_TIM16EN_Pos) /*!< 0x00020000 */
    #define RCC_APB2ENR_TIM16EN                    RCC_APB2ENR_TIM16EN_Msk
    #define RCC_APB2ENR_TIM17EN_Pos                (18U)
    #define RCC_APB2ENR_TIM17EN_Msk                (0x1UL << RCC_APB2ENR_TIM17EN_Pos) /*!< 0x00040000 */
    #define RCC_APB2ENR_TIM17EN                    RCC_APB2ENR_TIM17EN_Msk
    #define RCC_APB2ENR_SPI5EN_Pos                 (20U)
    #define RCC_APB2ENR_SPI5EN_Msk                 (0x1UL << RCC_APB2ENR_SPI5EN_Pos) /*!< 0x00100000 */
    #define RCC_APB2ENR_SPI5EN                     RCC_APB2ENR_SPI5EN_Msk
    #define RCC_APB2ENR_SAI1EN_Pos                 (22U)
    #define RCC_APB2ENR_SAI1EN_Msk                 (0x1UL << RCC_APB2ENR_SAI1EN_Pos) /*!< 0x00400000 */
    #define RCC_APB2ENR_SAI1EN                     RCC_APB2ENR_SAI1EN_Msk
    #define RCC_APB2ENR_SAI2EN_Pos                 (23U)
    #define RCC_APB2ENR_SAI2EN_Msk                 (0x1UL << RCC_APB2ENR_SAI2EN_Pos) /*!< 0x00800000 */
    #define RCC_APB2ENR_SAI2EN                     RCC_APB2ENR_SAI2EN_Msk
    #define RCC_APB2ENR_SAI3EN_Pos                 (24U)
    #define RCC_APB2ENR_SAI3EN_Msk                 (0x1UL << RCC_APB2ENR_SAI3EN_Pos) /*!< 0x01000000 */
    #define RCC_APB2ENR_SAI3EN                     RCC_APB2ENR_SAI3EN_Msk
    #define RCC_APB2ENR_DFSDM1EN_Pos               (28U)
    #define RCC_APB2ENR_DFSDM1EN_Msk               (0x1UL << RCC_APB2ENR_DFSDM1EN_Pos) /*!< 0x10000000 */
    #define RCC_APB2ENR_DFSDM1EN                   RCC_APB2ENR_DFSDM1EN_Msk
    #define RCC_APB2ENR_HRTIMEN_Pos                (29U)
    #define RCC_APB2ENR_HRTIMEN_Msk                (0x1UL << RCC_APB2ENR_HRTIMEN_Pos) /*!< 0x20000000 */
    #define RCC_APB2ENR_HRTIMEN                    RCC_APB2ENR_HRTIMEN_Msk

    /********************  Bit definition for RCC_APB4ENR register  ******************/
    #define RCC_APB4ENR_SYSCFGEN_Pos               (1U)
    #define RCC_APB4ENR_SYSCFGEN_Msk               (0x1UL << RCC_APB4ENR_SYSCFGEN_Pos) /*!< 0x00000002 */
    #define RCC_APB4ENR_SYSCFGEN                   RCC_APB4ENR_SYSCFGEN_Msk
    #define RCC_APB4ENR_LPUART1EN_Pos              (3U)
    #define RCC_APB4ENR_LPUART1EN_Msk              (0x1UL << RCC_APB4ENR_LPUART1EN_Pos) /*!< 0x00000008 */
    #define RCC_APB4ENR_LPUART1EN                  RCC_APB4ENR_LPUART1EN_Msk
    #define RCC_APB4ENR_SPI6EN_Pos                 (5U)
    #define RCC_APB4ENR_SPI6EN_Msk                 (0x1UL << RCC_APB4ENR_SPI6EN_Pos) /*!< 0x00000020 */
    #define RCC_APB4ENR_SPI6EN                     RCC_APB4ENR_SPI6EN_Msk
    #define RCC_APB4ENR_I2C4EN_Pos                 (7U)
    #define RCC_APB4ENR_I2C4EN_Msk                 (0x1UL << RCC_APB4ENR_I2C4EN_Pos) /*!< 0x00000080 */
    #define RCC_APB4ENR_I2C4EN                     RCC_APB4ENR_I2C4EN_Msk
    #define RCC_APB4ENR_LPTIM2EN_Pos               (9U)
    #define RCC_APB4ENR_LPTIM2EN_Msk               (0x1UL << RCC_APB4ENR_LPTIM2EN_Pos) /*!< 0x00000200 */
    #define RCC_APB4ENR_LPTIM2EN                   RCC_APB4ENR_LPTIM2EN_Msk
    #define RCC_APB4ENR_LPTIM3EN_Pos               (10U)
    #define RCC_APB4ENR_LPTIM3EN_Msk               (0x1UL << RCC_APB4ENR_LPTIM3EN_Pos) /*!< 0x00000400 */
    #define RCC_APB4ENR_LPTIM3EN                   RCC_APB4ENR_LPTIM3EN_Msk
    #define RCC_APB4ENR_LPTIM4EN_Pos               (11U)
    #define RCC_APB4ENR_LPTIM4EN_Msk               (0x1UL << RCC_APB4ENR_LPTIM4EN_Pos) /*!< 0x00000800 */
    #define RCC_APB4ENR_LPTIM4EN                   RCC_APB4ENR_LPTIM4EN_Msk
    #define RCC_APB4ENR_LPTIM5EN_Pos               (12U)
    #define RCC_APB4ENR_LPTIM5EN_Msk               (0x1UL << RCC_APB4ENR_LPTIM5EN_Pos) /*!< 0x00001000 */
    #define RCC_APB4ENR_LPTIM5EN                   RCC_APB4ENR_LPTIM5EN_Msk
    #define RCC_APB4ENR_COMP12EN_Pos               (14U)
    #define RCC_APB4ENR_COMP12EN_Msk               (0x1UL << RCC_APB4ENR_COMP12EN_Pos) /*!< 0x00004000 */
    #define RCC_APB4ENR_COMP12EN                   RCC_APB4ENR_COMP12EN_Msk
    #define RCC_APB4ENR_VREFEN_Pos                 (15U)
    #define RCC_APB4ENR_VREFEN_Msk                 (0x1UL << RCC_APB4ENR_VREFEN_Pos) /*!< 0x00008000 */
    #define RCC_APB4ENR_VREFEN                     RCC_APB4ENR_VREFEN_Msk
    #define RCC_APB4ENR_RTCAPBEN_Pos               (16U)
    #define RCC_APB4ENR_RTCAPBEN_Msk               (0x1UL << RCC_APB4ENR_RTCAPBEN_Pos) /*!< 0x00010000 */
    #define RCC_APB4ENR_RTCAPBEN                   RCC_APB4ENR_RTCAPBEN_Msk
    #define RCC_APB4ENR_SAI4EN_Pos                 (21U)
    #define RCC_APB4ENR_SAI4EN_Msk                 (0x1UL << RCC_APB4ENR_SAI4EN_Pos) /*!< 0x00200000 */
    #define RCC_APB4ENR_SAI4EN                     RCC_APB4ENR_SAI4EN_Msk


    /********************  Bit definition for RCC_AHB3RSTR register  ***************/
    #define RCC_AHB3RSTR_MDMARST_Pos               (0U)
    #define RCC_AHB3RSTR_MDMARST_Msk               (0x1UL << RCC_AHB3RSTR_MDMARST_Pos)      /*!< 0x00000001 */
    #define RCC_AHB3RSTR_MDMARST                   RCC_AHB3RSTR_MDMARST_Msk
    #define RCC_AHB3RSTR_DMA2DRST_Pos              (4U)
    #define RCC_AHB3RSTR_DMA2DRST_Msk              (0x1UL << RCC_AHB3RSTR_DMA2DRST_Pos)     /*!< 0x00000010 */
    #define RCC_AHB3RSTR_DMA2DRST                  RCC_AHB3RSTR_DMA2DRST_Msk
    #define RCC_AHB3RSTR_JPGDECRST_Pos             (5U)
    #define RCC_AHB3RSTR_JPGDECRST_Msk             (0x1UL << RCC_AHB3RSTR_JPGDECRST_Pos)    /*!< 0x00000020 */
    #define RCC_AHB3RSTR_JPGDECRST                 RCC_AHB3RSTR_JPGDECRST_Msk
    #define RCC_AHB3RSTR_FMCRST_Pos                (12U)
    #define RCC_AHB3RSTR_FMCRST_Msk                (0x1UL << RCC_AHB3RSTR_FMCRST_Pos)      /*!< 0x00001000 */
    #define RCC_AHB3RSTR_FMCRST                    RCC_AHB3RSTR_FMCRST_Msk
    #define RCC_AHB3RSTR_QSPIRST_Pos               (14U)
    #define RCC_AHB3RSTR_QSPIRST_Msk               (0x1UL << RCC_AHB3RSTR_QSPIRST_Pos)     /*!< 0x00004000 */
    #define RCC_AHB3RSTR_QSPIRST                   RCC_AHB3RSTR_QSPIRST_Msk
    #define RCC_AHB3RSTR_SDMMC1RST_Pos             (16U)
    #define RCC_AHB3RSTR_SDMMC1RST_Msk             (0x1UL << RCC_AHB3RSTR_SDMMC1RST_Pos)   /*!< 0x00010000 */
    #define RCC_AHB3RSTR_SDMMC1RST                 RCC_AHB3RSTR_SDMMC1RST_Msk


    /********************  Bit definition for RCC_AHB1RSTR register  ***************/
    #define RCC_AHB1RSTR_DMA1RST_Pos               (0U)
    #define RCC_AHB1RSTR_DMA1RST_Msk               (0x1UL << RCC_AHB1RSTR_DMA1RST_Pos)      /*!< 0x00000001 */
    #define RCC_AHB1RSTR_DMA1RST                   RCC_AHB1RSTR_DMA1RST_Msk
    #define RCC_AHB1RSTR_DMA2RST_Pos               (1U)
    #define RCC_AHB1RSTR_DMA2RST_Msk               (0x1UL << RCC_AHB1RSTR_DMA2RST_Pos)      /*!< 0x00000002 */
    #define RCC_AHB1RSTR_DMA2RST                   RCC_AHB1RSTR_DMA2RST_Msk
    #define RCC_AHB1RSTR_ADC12RST_Pos              (5U)
    #define RCC_AHB1RSTR_ADC12RST_Msk              (0x1UL << RCC_AHB1RSTR_ADC12RST_Pos)     /*!< 0x00000020 */
    #define RCC_AHB1RSTR_ADC12RST                  RCC_AHB1RSTR_ADC12RST_Msk
    #define RCC_AHB1RSTR_ARTRST_Pos                (14U)
    #define RCC_AHB1RSTR_ARTRST_Msk                (0x1UL << RCC_AHB1RSTR_ARTRST_Pos)       /*!< 0x00004000 */
    #define RCC_AHB1RSTR_ARTRST                    RCC_AHB1RSTR_ARTRST_Msk
    #define RCC_AHB1RSTR_ETH1MACRST_Pos            (15U)
    #define RCC_AHB1RSTR_ETH1MACRST_Msk            (0x1UL << RCC_AHB1RSTR_ETH1MACRST_Pos)   /*!< 0x00008000 */
    #define RCC_AHB1RSTR_ETH1MACRST                RCC_AHB1RSTR_ETH1MACRST_Msk
    #define RCC_AHB1RSTR_USB1OTGHSRST_Pos          (25U)
    #define RCC_AHB1RSTR_USB1OTGHSRST_Msk          (0x1UL << RCC_AHB1RSTR_USB1OTGHSRST_Pos) /*!< 0x02000000 */
    #define RCC_AHB1RSTR_USB1OTGHSRST              RCC_AHB1RSTR_USB1OTGHSRST_Msk
    #define RCC_AHB1RSTR_USB2OTGFSRST_Pos          (27U)
    #define RCC_AHB1RSTR_USB2OTGFSRST_Msk          (0x1UL << RCC_AHB1RSTR_USB2OTGFSRST_Pos) /*!< 0x08000000 */
    #define RCC_AHB1RSTR_USB2OTGFSRST              RCC_AHB1RSTR_USB2OTGFSRST_Msk

    /* Legacy define */
    #define RCC_AHB1RSTR_USB2OTGHSRST_Pos          RCC_AHB1RSTR_USB2OTGFSRST_Pos
    #define RCC_AHB1RSTR_USB2OTGHSRST_Msk          RCC_AHB1RSTR_USB2OTGFSRST_Msk
    #define RCC_AHB1RSTR_USB2OTGHSRST              RCC_AHB1RSTR_USB2OTGFSRST

    /********************  Bit definition for RCC_AHB2RSTR register  ***************/
    #define RCC_AHB2RSTR_DCMIRST_Pos               (0U)
    #define RCC_AHB2RSTR_DCMIRST_Msk               (0x1UL << RCC_AHB2RSTR_DCMIRST_Pos)       /*!< 0x00000001 */
    #define RCC_AHB2RSTR_DCMIRST                   RCC_AHB2RSTR_DCMIRST_Msk
    #define RCC_AHB2RSTR_RNGRST_Pos                (6U)
    #define RCC_AHB2RSTR_RNGRST_Msk                (0x1UL << RCC_AHB2RSTR_RNGRST_Pos)        /*!< 0x00000040 */
    #define RCC_AHB2RSTR_RNGRST                    RCC_AHB2RSTR_RNGRST_Msk
    #define RCC_AHB2RSTR_SDMMC2RST_Pos             (9U)
    #define RCC_AHB2RSTR_SDMMC2RST_Msk             (0x1UL << RCC_AHB2RSTR_SDMMC2RST_Pos)     /*!< 0x00000200 */
    #define RCC_AHB2RSTR_SDMMC2RST                 RCC_AHB2RSTR_SDMMC2RST_Msk

    /********************  Bit definition for RCC_AHB4RSTR register  ******************/
    #define RCC_AHB4RSTR_GPIOARST_Pos              (0U)
    #define RCC_AHB4RSTR_GPIOARST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOARST_Pos)      /*!< 0x00000001 */
    #define RCC_AHB4RSTR_GPIOARST                  RCC_AHB4RSTR_GPIOARST_Msk
    #define RCC_AHB4RSTR_GPIOBRST_Pos              (1U)
    #define RCC_AHB4RSTR_GPIOBRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOBRST_Pos)      /*!< 0x00000002 */
    #define RCC_AHB4RSTR_GPIOBRST                  RCC_AHB4RSTR_GPIOBRST_Msk
    #define RCC_AHB4RSTR_GPIOCRST_Pos              (2U)
    #define RCC_AHB4RSTR_GPIOCRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOCRST_Pos)      /*!< 0x00000004 */
    #define RCC_AHB4RSTR_GPIOCRST                  RCC_AHB4RSTR_GPIOCRST_Msk
    #define RCC_AHB4RSTR_GPIODRST_Pos              (3U)
    #define RCC_AHB4RSTR_GPIODRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIODRST_Pos)      /*!< 0x00000008 */
    #define RCC_AHB4RSTR_GPIODRST                  RCC_AHB4RSTR_GPIODRST_Msk
    #define RCC_AHB4RSTR_GPIOERST_Pos              (4U)
    #define RCC_AHB4RSTR_GPIOERST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOERST_Pos)      /*!< 0x00000010 */
    #define RCC_AHB4RSTR_GPIOERST                  RCC_AHB4RSTR_GPIOERST_Msk
    #define RCC_AHB4RSTR_GPIOFRST_Pos              (5U)
    #define RCC_AHB4RSTR_GPIOFRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOFRST_Pos)       /*!< 0x00000020 */
    #define RCC_AHB4RSTR_GPIOFRST                  RCC_AHB4RSTR_GPIOFRST_Msk
    #define RCC_AHB4RSTR_GPIOGRST_Pos              (6U)
    #define RCC_AHB4RSTR_GPIOGRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOGRST_Pos)       /*!< 0x00000040 */
    #define RCC_AHB4RSTR_GPIOGRST                  RCC_AHB4RSTR_GPIOGRST_Msk
    #define RCC_AHB4RSTR_GPIOHRST_Pos              (7U)
    #define RCC_AHB4RSTR_GPIOHRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOHRST_Pos)       /*!< 0x00000080 */
    #define RCC_AHB4RSTR_GPIOHRST                  RCC_AHB4RSTR_GPIOHRST_Msk
    #define RCC_AHB4RSTR_GPIOIRST_Pos              (8U)
    #define RCC_AHB4RSTR_GPIOIRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOIRST_Pos)       /*!< 0x00000100 */
    #define RCC_AHB4RSTR_GPIOIRST                  RCC_AHB4RSTR_GPIOIRST_Msk
    #define RCC_AHB4RSTR_GPIOJRST_Pos              (9U)
    #define RCC_AHB4RSTR_GPIOJRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOJRST_Pos)       /*!< 0x00000200 */
    #define RCC_AHB4RSTR_GPIOJRST                  RCC_AHB4RSTR_GPIOJRST_Msk
    #define RCC_AHB4RSTR_GPIOKRST_Pos              (10U)
    #define RCC_AHB4RSTR_GPIOKRST_Msk              (0x1UL << RCC_AHB4RSTR_GPIOKRST_Pos)       /*!< 0x00000400 */
    #define RCC_AHB4RSTR_GPIOKRST                  RCC_AHB4RSTR_GPIOKRST_Msk
    #define RCC_AHB4RSTR_CRCRST_Pos                (19U)
    #define RCC_AHB4RSTR_CRCRST_Msk                (0x1UL << RCC_AHB4RSTR_CRCRST_Pos)         /*!< 0x00080000 */
    #define RCC_AHB4RSTR_CRCRST                    RCC_AHB4RSTR_CRCRST_Msk
    #define RCC_AHB4RSTR_BDMARST_Pos               (21U)
    #define RCC_AHB4RSTR_BDMARST_Msk               (0x1UL << RCC_AHB4RSTR_BDMARST_Pos)        /*!< 0x00200000 */
    #define RCC_AHB4RSTR_BDMARST                   RCC_AHB4RSTR_BDMARST_Msk
    #define RCC_AHB4RSTR_ADC3RST_Pos               (24U)
    #define RCC_AHB4RSTR_ADC3RST_Msk               (0x1UL << RCC_AHB4RSTR_ADC3RST_Pos)        /*!< 0x01000000 */
    #define RCC_AHB4RSTR_ADC3RST                   RCC_AHB4RSTR_ADC3RST_Msk
    #define RCC_AHB4RSTR_HSEMRST_Pos               (25U)
    #define RCC_AHB4RSTR_HSEMRST_Msk               (0x1UL << RCC_AHB4RSTR_HSEMRST_Pos)        /*!< 0x02000000 */
    #define RCC_AHB4RSTR_HSEMRST                   RCC_AHB4RSTR_HSEMRST_Msk


    /********************  Bit definition for RCC_APB3RSTR register  ******************/
    #define RCC_APB3RSTR_LTDCRST_Pos               (3U)
    #define RCC_APB3RSTR_LTDCRST_Msk               (0x1UL << RCC_APB3RSTR_LTDCRST_Pos) /*!< 0x00000008 */
    #define RCC_APB3RSTR_LTDCRST                   RCC_APB3RSTR_LTDCRST_Msk

    /********************  Bit definition for RCC_APB1LRSTR register  ******************/

    #define RCC_APB1LRSTR_TIM2RST_Pos              (0U)
    #define RCC_APB1LRSTR_TIM2RST_Msk              (0x1UL << RCC_APB1LRSTR_TIM2RST_Pos) /*!< 0x00000001 */
    #define RCC_APB1LRSTR_TIM2RST                  RCC_APB1LRSTR_TIM2RST_Msk
    #define RCC_APB1LRSTR_TIM3RST_Pos              (1U)
    #define RCC_APB1LRSTR_TIM3RST_Msk              (0x1UL << RCC_APB1LRSTR_TIM3RST_Pos) /*!< 0x00000002 */
    #define RCC_APB1LRSTR_TIM3RST                  RCC_APB1LRSTR_TIM3RST_Msk
    #define RCC_APB1LRSTR_TIM4RST_Pos              (2U)
    #define RCC_APB1LRSTR_TIM4RST_Msk              (0x1UL << RCC_APB1LRSTR_TIM4RST_Pos) /*!< 0x00000004 */
    #define RCC_APB1LRSTR_TIM4RST                  RCC_APB1LRSTR_TIM4RST_Msk
    #define RCC_APB1LRSTR_TIM5RST_Pos              (3U)
    #define RCC_APB1LRSTR_TIM5RST_Msk              (0x1UL << RCC_APB1LRSTR_TIM5RST_Pos) /*!< 0x00000008 */
    #define RCC_APB1LRSTR_TIM5RST                  RCC_APB1LRSTR_TIM5RST_Msk
    #define RCC_APB1LRSTR_TIM6RST_Pos              (4U)
    #define RCC_APB1LRSTR_TIM6RST_Msk              (0x1UL << RCC_APB1LRSTR_TIM6RST_Pos) /*!< 0x00000010 */
    #define RCC_APB1LRSTR_TIM6RST                  RCC_APB1LRSTR_TIM6RST_Msk
    #define RCC_APB1LRSTR_TIM7RST_Pos              (5U)
    #define RCC_APB1LRSTR_TIM7RST_Msk              (0x1UL << RCC_APB1LRSTR_TIM7RST_Pos) /*!< 0x00000020 */
    #define RCC_APB1LRSTR_TIM7RST                  RCC_APB1LRSTR_TIM7RST_Msk
    #define RCC_APB1LRSTR_TIM12RST_Pos             (6U)
    #define RCC_APB1LRSTR_TIM12RST_Msk             (0x1UL << RCC_APB1LRSTR_TIM12RST_Pos) /*!< 0x00000040 */
    #define RCC_APB1LRSTR_TIM12RST                 RCC_APB1LRSTR_TIM12RST_Msk
    #define RCC_APB1LRSTR_TIM13RST_Pos             (7U)
    #define RCC_APB1LRSTR_TIM13RST_Msk             (0x1UL << RCC_APB1LRSTR_TIM13RST_Pos) /*!< 0x00000080 */
    #define RCC_APB1LRSTR_TIM13RST                 RCC_APB1LRSTR_TIM13RST_Msk
    #define RCC_APB1LRSTR_TIM14RST_Pos             (8U)
    #define RCC_APB1LRSTR_TIM14RST_Msk             (0x1UL << RCC_APB1LRSTR_TIM14RST_Pos) /*!< 0x00000100 */
    #define RCC_APB1LRSTR_TIM14RST                 RCC_APB1LRSTR_TIM14RST_Msk
    #define RCC_APB1LRSTR_LPTIM1RST_Pos            (9U)
    #define RCC_APB1LRSTR_LPTIM1RST_Msk            (0x1UL << RCC_APB1LRSTR_LPTIM1RST_Pos) /*!< 0x00000200 */
    #define RCC_APB1LRSTR_LPTIM1RST                RCC_APB1LRSTR_LPTIM1RST_Msk
    #define RCC_APB1LRSTR_SPI2RST_Pos              (14U)
    #define RCC_APB1LRSTR_SPI2RST_Msk              (0x1UL << RCC_APB1LRSTR_SPI2RST_Pos) /*!< 0x00004000 */
    #define RCC_APB1LRSTR_SPI2RST                  RCC_APB1LRSTR_SPI2RST_Msk
    #define RCC_APB1LRSTR_SPI3RST_Pos              (15U)
    #define RCC_APB1LRSTR_SPI3RST_Msk              (0x1UL << RCC_APB1LRSTR_SPI3RST_Pos) /*!< 0x00008000 */
    #define RCC_APB1LRSTR_SPI3RST                  RCC_APB1LRSTR_SPI3RST_Msk
    #define RCC_APB1LRSTR_SPDIFRXRST_Pos           (16U)
    #define RCC_APB1LRSTR_SPDIFRXRST_Msk           (0x1UL << RCC_APB1LRSTR_SPDIFRXRST_Pos) /*!< 0x00010000 */
    #define RCC_APB1LRSTR_SPDIFRXRST               RCC_APB1LRSTR_SPDIFRXRST_Msk
    #define RCC_APB1LRSTR_USART2RST_Pos            (17U)
    #define RCC_APB1LRSTR_USART2RST_Msk            (0x1UL << RCC_APB1LRSTR_USART2RST_Pos) /*!< 0x00020000 */
    #define RCC_APB1LRSTR_USART2RST                RCC_APB1LRSTR_USART2RST_Msk
    #define RCC_APB1LRSTR_USART3RST_Pos            (18U)
    #define RCC_APB1LRSTR_USART3RST_Msk            (0x1UL << RCC_APB1LRSTR_USART3RST_Pos) /*!< 0x00040000 */
    #define RCC_APB1LRSTR_USART3RST                RCC_APB1LRSTR_USART3RST_Msk
    #define RCC_APB1LRSTR_UART4RST_Pos             (19U)
    #define RCC_APB1LRSTR_UART4RST_Msk             (0x1UL << RCC_APB1LRSTR_UART4RST_Pos) /*!< 0x00080000 */
    #define RCC_APB1LRSTR_UART4RST                 RCC_APB1LRSTR_UART4RST_Msk
    #define RCC_APB1LRSTR_UART5RST_Pos             (20U)
    #define RCC_APB1LRSTR_UART5RST_Msk             (0x1UL << RCC_APB1LRSTR_UART5RST_Pos) /*!< 0x00100000 */
    #define RCC_APB1LRSTR_UART5RST                 RCC_APB1LRSTR_UART5RST_Msk
    #define RCC_APB1LRSTR_I2C1RST_Pos              (21U)
    #define RCC_APB1LRSTR_I2C1RST_Msk              (0x1UL << RCC_APB1LRSTR_I2C1RST_Pos) /*!< 0x00200000 */
    #define RCC_APB1LRSTR_I2C1RST                  RCC_APB1LRSTR_I2C1RST_Msk
    #define RCC_APB1LRSTR_I2C2RST_Pos              (22U)
    #define RCC_APB1LRSTR_I2C2RST_Msk              (0x1UL << RCC_APB1LRSTR_I2C2RST_Pos) /*!< 0x00400000 */
    #define RCC_APB1LRSTR_I2C2RST                  RCC_APB1LRSTR_I2C2RST_Msk
    #define RCC_APB1LRSTR_I2C3RST_Pos              (23U)
    #define RCC_APB1LRSTR_I2C3RST_Msk              (0x1UL << RCC_APB1LRSTR_I2C3RST_Pos) /*!< 0x00800000 */
    #define RCC_APB1LRSTR_I2C3RST                  RCC_APB1LRSTR_I2C3RST_Msk
    #define RCC_APB1LRSTR_CECRST_Pos               (27U)
    #define RCC_APB1LRSTR_CECRST_Msk               (0x1UL << RCC_APB1LRSTR_CECRST_Pos) /*!< 0x08000000 */
    #define RCC_APB1LRSTR_CECRST                   RCC_APB1LRSTR_CECRST_Msk
    #define RCC_APB1LRSTR_DAC12RST_Pos             (29U)
    #define RCC_APB1LRSTR_DAC12RST_Msk             (0x1UL << RCC_APB1LRSTR_DAC12RST_Pos) /*!< 0x20000000 */
    #define RCC_APB1LRSTR_DAC12RST                 RCC_APB1LRSTR_DAC12RST_Msk
    #define RCC_APB1LRSTR_UART7RST_Pos             (30U)
    #define RCC_APB1LRSTR_UART7RST_Msk             (0x1UL << RCC_APB1LRSTR_UART7RST_Pos) /*!< 0x40000000 */
    #define RCC_APB1LRSTR_UART7RST                 RCC_APB1LRSTR_UART7RST_Msk
    #define RCC_APB1LRSTR_UART8RST_Pos             (31U)
    #define RCC_APB1LRSTR_UART8RST_Msk             (0x1UL << RCC_APB1LRSTR_UART8RST_Pos) /*!< 0x80000000 */
    #define RCC_APB1LRSTR_UART8RST                 RCC_APB1LRSTR_UART8RST_Msk

    /* Legacy define */
    #define RCC_APB1LRSTR_HDMICECRST_Pos           RCC_APB1LRSTR_CECRST_Pos
    #define RCC_APB1LRSTR_HDMICECRST_Msk           RCC_APB1LRSTR_CECRST_Msk
    #define RCC_APB1LRSTR_HDMICECRST               RCC_APB1LRSTR_CECRST
    /********************  Bit definition for RCC_APB1HRSTR register  ******************/
    #define RCC_APB1HRSTR_CRSRST_Pos               (1U)
    #define RCC_APB1HRSTR_CRSRST_Msk               (0x1UL << RCC_APB1HRSTR_CRSRST_Pos) /*!< 0x00000002 */
    #define RCC_APB1HRSTR_CRSRST                   RCC_APB1HRSTR_CRSRST_Msk
    #define RCC_APB1HRSTR_SWPMIRST_Pos             (2U)
    #define RCC_APB1HRSTR_SWPMIRST_Msk             (0x1UL << RCC_APB1HRSTR_SWPMIRST_Pos) /*!< 0x00000004 */
    #define RCC_APB1HRSTR_SWPMIRST                 RCC_APB1HRSTR_SWPMIRST_Msk
    #define RCC_APB1HRSTR_OPAMPRST_Pos             (4U)
    #define RCC_APB1HRSTR_OPAMPRST_Msk             (0x1UL << RCC_APB1HRSTR_OPAMPRST_Pos) /*!< 0x00000010 */
    #define RCC_APB1HRSTR_OPAMPRST                 RCC_APB1HRSTR_OPAMPRST_Msk
    #define RCC_APB1HRSTR_MDIOSRST_Pos             (5U)
    #define RCC_APB1HRSTR_MDIOSRST_Msk             (0x1UL << RCC_APB1HRSTR_MDIOSRST_Pos) /*!< 0x00000020 */
    #define RCC_APB1HRSTR_MDIOSRST                 RCC_APB1HRSTR_MDIOSRST_Msk
    #define RCC_APB1HRSTR_FDCANRST_Pos             (8U)
    #define RCC_APB1HRSTR_FDCANRST_Msk             (0x1UL << RCC_APB1HRSTR_FDCANRST_Pos) /*!< 0x00000100 */
    #define RCC_APB1HRSTR_FDCANRST                 RCC_APB1HRSTR_FDCANRST_Msk

    /********************  Bit definition for RCC_APB2RSTR register  ******************/
    #define RCC_APB2RSTR_TIM1RST_Pos               (0U)
    #define RCC_APB2RSTR_TIM1RST_Msk               (0x1UL << RCC_APB2RSTR_TIM1RST_Pos) /*!< 0x00000001 */
    #define RCC_APB2RSTR_TIM1RST                   RCC_APB2RSTR_TIM1RST_Msk
    #define RCC_APB2RSTR_TIM8RST_Pos               (1U)
    #define RCC_APB2RSTR_TIM8RST_Msk               (0x1UL << RCC_APB2RSTR_TIM8RST_Pos) /*!< 0x00000002 */
    #define RCC_APB2RSTR_TIM8RST                   RCC_APB2RSTR_TIM8RST_Msk
    #define RCC_APB2RSTR_USART1RST_Pos             (4U)
    #define RCC_APB2RSTR_USART1RST_Msk             (0x1UL << RCC_APB2RSTR_USART1RST_Pos) /*!< 0x00000010 */
    #define RCC_APB2RSTR_USART1RST                 RCC_APB2RSTR_USART1RST_Msk
    #define RCC_APB2RSTR_USART6RST_Pos             (5U)
    #define RCC_APB2RSTR_USART6RST_Msk             (0x1UL << RCC_APB2RSTR_USART6RST_Pos) /*!< 0x00000020 */
    #define RCC_APB2RSTR_USART6RST                 RCC_APB2RSTR_USART6RST_Msk
    #define RCC_APB2RSTR_SPI1RST_Pos               (12U)
    #define RCC_APB2RSTR_SPI1RST_Msk               (0x1UL << RCC_APB2RSTR_SPI1RST_Pos) /*!< 0x00001000 */
    #define RCC_APB2RSTR_SPI1RST                   RCC_APB2RSTR_SPI1RST_Msk
    #define RCC_APB2RSTR_SPI4RST_Pos               (13U)
    #define RCC_APB2RSTR_SPI4RST_Msk               (0x1UL << RCC_APB2RSTR_SPI4RST_Pos) /*!< 0x00002000 */
    #define RCC_APB2RSTR_SPI4RST                   RCC_APB2RSTR_SPI4RST_Msk
    #define RCC_APB2RSTR_TIM15RST_Pos              (16U)
    #define RCC_APB2RSTR_TIM15RST_Msk              (0x1UL << RCC_APB2RSTR_TIM15RST_Pos) /*!< 0x00010000 */
    #define RCC_APB2RSTR_TIM15RST                  RCC_APB2RSTR_TIM15RST_Msk
    #define RCC_APB2RSTR_TIM16RST_Pos              (17U)
    #define RCC_APB2RSTR_TIM16RST_Msk              (0x1UL << RCC_APB2RSTR_TIM16RST_Pos) /*!< 0x00020000 */
    #define RCC_APB2RSTR_TIM16RST                  RCC_APB2RSTR_TIM16RST_Msk
    #define RCC_APB2RSTR_TIM17RST_Pos              (18U)
    #define RCC_APB2RSTR_TIM17RST_Msk              (0x1UL << RCC_APB2RSTR_TIM17RST_Pos) /*!< 0x00040000 */
    #define RCC_APB2RSTR_TIM17RST                  RCC_APB2RSTR_TIM17RST_Msk
    #define RCC_APB2RSTR_SPI5RST_Pos               (20U)
    #define RCC_APB2RSTR_SPI5RST_Msk               (0x1UL << RCC_APB2RSTR_SPI5RST_Pos) /*!< 0x00100000 */
    #define RCC_APB2RSTR_SPI5RST                   RCC_APB2RSTR_SPI5RST_Msk
    #define RCC_APB2RSTR_SAI1RST_Pos               (22U)
    #define RCC_APB2RSTR_SAI1RST_Msk               (0x1UL << RCC_APB2RSTR_SAI1RST_Pos) /*!< 0x00400000 */
    #define RCC_APB2RSTR_SAI1RST                   RCC_APB2RSTR_SAI1RST_Msk
    #define RCC_APB2RSTR_SAI2RST_Pos               (23U)
    #define RCC_APB2RSTR_SAI2RST_Msk               (0x1UL << RCC_APB2RSTR_SAI2RST_Pos) /*!< 0x00800000 */
    #define RCC_APB2RSTR_SAI2RST                   RCC_APB2RSTR_SAI2RST_Msk
    #define RCC_APB2RSTR_SAI3RST_Pos               (24U)
    #define RCC_APB2RSTR_SAI3RST_Msk               (0x1UL << RCC_APB2RSTR_SAI3RST_Pos) /*!< 0x01000000 */
    #define RCC_APB2RSTR_SAI3RST                   RCC_APB2RSTR_SAI3RST_Msk
    #define RCC_APB2RSTR_DFSDM1RST_Pos             (28U)
    #define RCC_APB2RSTR_DFSDM1RST_Msk             (0x1UL << RCC_APB2RSTR_DFSDM1RST_Pos) /*!< 0x10000000 */
    #define RCC_APB2RSTR_DFSDM1RST                 RCC_APB2RSTR_DFSDM1RST_Msk
    #define RCC_APB2RSTR_HRTIMRST_Pos              (29U)
    #define RCC_APB2RSTR_HRTIMRST_Msk              (0x1UL << RCC_APB2RSTR_HRTIMRST_Pos) /*!< 0x20000000 */
    #define RCC_APB2RSTR_HRTIMRST                  RCC_APB2RSTR_HRTIMRST_Msk

    /********************  Bit definition for RCC_APB4RSTR register  ******************/
    #define RCC_APB4RSTR_SYSCFGRST_Pos             (1U)
    #define RCC_APB4RSTR_SYSCFGRST_Msk             (0x1UL << RCC_APB4RSTR_SYSCFGRST_Pos) /*!< 0x00000002 */
    #define RCC_APB4RSTR_SYSCFGRST                 RCC_APB4RSTR_SYSCFGRST_Msk
    #define RCC_APB4RSTR_LPUART1RST_Pos            (3U)
    #define RCC_APB4RSTR_LPUART1RST_Msk            (0x1UL << RCC_APB4RSTR_LPUART1RST_Pos) /*!< 0x00000008 */
    #define RCC_APB4RSTR_LPUART1RST                RCC_APB4RSTR_LPUART1RST_Msk
    #define RCC_APB4RSTR_SPI6RST_Pos               (5U)
    #define RCC_APB4RSTR_SPI6RST_Msk               (0x1UL << RCC_APB4RSTR_SPI6RST_Pos) /*!< 0x00000020 */
    #define RCC_APB4RSTR_SPI6RST                   RCC_APB4RSTR_SPI6RST_Msk
    #define RCC_APB4RSTR_I2C4RST_Pos               (7U)
    #define RCC_APB4RSTR_I2C4RST_Msk               (0x1UL << RCC_APB4RSTR_I2C4RST_Pos) /*!< 0x00000080 */
    #define RCC_APB4RSTR_I2C4RST                   RCC_APB4RSTR_I2C4RST_Msk
    #define RCC_APB4RSTR_LPTIM2RST_Pos             (9U)
    #define RCC_APB4RSTR_LPTIM2RST_Msk             (0x1UL << RCC_APB4RSTR_LPTIM2RST_Pos) /*!< 0x00000200 */
    #define RCC_APB4RSTR_LPTIM2RST                 RCC_APB4RSTR_LPTIM2RST_Msk
    #define RCC_APB4RSTR_LPTIM3RST_Pos             (10U)
    #define RCC_APB4RSTR_LPTIM3RST_Msk             (0x1UL << RCC_APB4RSTR_LPTIM3RST_Pos) /*!< 0x00000400 */
    #define RCC_APB4RSTR_LPTIM3RST                 RCC_APB4RSTR_LPTIM3RST_Msk
    #define RCC_APB4RSTR_LPTIM4RST_Pos             (11U)
    #define RCC_APB4RSTR_LPTIM4RST_Msk             (0x1UL << RCC_APB4RSTR_LPTIM4RST_Pos) /*!< 0x00000800 */
    #define RCC_APB4RSTR_LPTIM4RST                 RCC_APB4RSTR_LPTIM4RST_Msk
    #define RCC_APB4RSTR_LPTIM5RST_Pos             (12U)
    #define RCC_APB4RSTR_LPTIM5RST_Msk             (0x1UL << RCC_APB4RSTR_LPTIM5RST_Pos) /*!< 0x00001000 */
    #define RCC_APB4RSTR_LPTIM5RST                 RCC_APB4RSTR_LPTIM5RST_Msk
    #define RCC_APB4RSTR_COMP12RST_Pos             (14U)
    #define RCC_APB4RSTR_COMP12RST_Msk             (0x1UL << RCC_APB4RSTR_COMP12RST_Pos) /*!< 0x00004000 */
    #define RCC_APB4RSTR_COMP12RST                 RCC_APB4RSTR_COMP12RST_Msk
    #define RCC_APB4RSTR_VREFRST_Pos               (15U)
    #define RCC_APB4RSTR_VREFRST_Msk               (0x1UL << RCC_APB4RSTR_VREFRST_Pos) /*!< 0x00008000 */
    #define RCC_APB4RSTR_VREFRST                   RCC_APB4RSTR_VREFRST_Msk
    #define RCC_APB4RSTR_SAI4RST_Pos               (21U)
    #define RCC_APB4RSTR_SAI4RST_Msk               (0x1UL << RCC_APB4RSTR_SAI4RST_Pos) /*!< 0x00200000 */
    #define RCC_APB4RSTR_SAI4RST                   RCC_APB4RSTR_SAI4RST_Msk


    /********************  Bit definition for RCC_GCR register  ********************/
    #define RCC_GCR_WW1RSC_Pos                     (0U)
    #define RCC_GCR_WW1RSC_Msk                     (0x1UL << RCC_GCR_WW1RSC_Pos)   /*!< 0x00000001 */
    #define RCC_GCR_WW1RSC                         RCC_GCR_WW1RSC_Msk
    #define RCC_GCR_WW2RSC_Pos                     (1U)
    #define RCC_GCR_WW2RSC_Msk                     (0x1UL << RCC_GCR_WW2RSC_Pos)   /*!< 0x00000002 */
    #define RCC_GCR_WW2RSC                         RCC_GCR_WW2RSC_Msk
    #define RCC_GCR_BOOT_C1_Pos                    (2U)
    #define RCC_GCR_BOOT_C1_Msk                    (0x1UL << RCC_GCR_BOOT_C1_Pos)  /*!< 0x00000004 */
    #define RCC_GCR_BOOT_C1                        RCC_GCR_BOOT_C1_Msk
    #define RCC_GCR_BOOT_C2_Pos                    (3U)
    #define RCC_GCR_BOOT_C2_Msk                    (0x1UL << RCC_GCR_BOOT_C2_Pos)  /*!< 0x00000008 */
    #define RCC_GCR_BOOT_C2                        RCC_GCR_BOOT_C2_Msk

    /********************  Bit definition for RCC_D3AMR register  ********************/
    #define RCC_D3AMR_BDMAAMEN_Pos                 (0U)
    #define RCC_D3AMR_BDMAAMEN_Msk                 (0x1UL << RCC_D3AMR_BDMAAMEN_Pos) /*!< 0x00000001 */
    #define RCC_D3AMR_BDMAAMEN                     RCC_D3AMR_BDMAAMEN_Msk
    #define RCC_D3AMR_LPUART1AMEN_Pos              (3U)
    #define RCC_D3AMR_LPUART1AMEN_Msk              (0x1UL << RCC_D3AMR_LPUART1AMEN_Pos) /*!< 0x00000008 */
    #define RCC_D3AMR_LPUART1AMEN                  RCC_D3AMR_LPUART1AMEN_Msk
    #define RCC_D3AMR_SPI6AMEN_Pos                 (5U)
    #define RCC_D3AMR_SPI6AMEN_Msk                 (0x1UL << RCC_D3AMR_SPI6AMEN_Pos) /*!< 0x00000020 */
    #define RCC_D3AMR_SPI6AMEN                     RCC_D3AMR_SPI6AMEN_Msk
    #define RCC_D3AMR_I2C4AMEN_Pos                 (7U)
    #define RCC_D3AMR_I2C4AMEN_Msk                 (0x1UL << RCC_D3AMR_I2C4AMEN_Pos) /*!< 0x00000080 */
    #define RCC_D3AMR_I2C4AMEN                     RCC_D3AMR_I2C4AMEN_Msk
    #define RCC_D3AMR_LPTIM2AMEN_Pos               (9U)
    #define RCC_D3AMR_LPTIM2AMEN_Msk               (0x1UL << RCC_D3AMR_LPTIM2AMEN_Pos) /*!< 0x00000200 */
    #define RCC_D3AMR_LPTIM2AMEN                   RCC_D3AMR_LPTIM2AMEN_Msk
    #define RCC_D3AMR_LPTIM3AMEN_Pos               (10U)
    #define RCC_D3AMR_LPTIM3AMEN_Msk               (0x1UL << RCC_D3AMR_LPTIM3AMEN_Pos) /*!< 0x00000400 */
    #define RCC_D3AMR_LPTIM3AMEN                   RCC_D3AMR_LPTIM3AMEN_Msk
    #define RCC_D3AMR_LPTIM4AMEN_Pos               (11U)
    #define RCC_D3AMR_LPTIM4AMEN_Msk               (0x1UL << RCC_D3AMR_LPTIM4AMEN_Pos) /*!< 0x00000800 */
    #define RCC_D3AMR_LPTIM4AMEN                   RCC_D3AMR_LPTIM4AMEN_Msk
    #define RCC_D3AMR_LPTIM5AMEN_Pos               (12U)
    #define RCC_D3AMR_LPTIM5AMEN_Msk               (0x1UL << RCC_D3AMR_LPTIM5AMEN_Pos) /*!< 0x00001000 */
    #define RCC_D3AMR_LPTIM5AMEN                   RCC_D3AMR_LPTIM5AMEN_Msk
    #define RCC_D3AMR_COMP12AMEN_Pos               (14U)
    #define RCC_D3AMR_COMP12AMEN_Msk               (0x1UL << RCC_D3AMR_COMP12AMEN_Pos) /*!< 0x00004000 */
    #define RCC_D3AMR_COMP12AMEN                   RCC_D3AMR_COMP12AMEN_Msk
    #define RCC_D3AMR_VREFAMEN_Pos                 (15U)
    #define RCC_D3AMR_VREFAMEN_Msk                 (0x1UL << RCC_D3AMR_VREFAMEN_Pos) /*!< 0x00008000 */
    #define RCC_D3AMR_VREFAMEN                     RCC_D3AMR_VREFAMEN_Msk
    #define RCC_D3AMR_RTCAMEN_Pos                  (16U)
    #define RCC_D3AMR_RTCAMEN_Msk                  (0x1UL << RCC_D3AMR_RTCAMEN_Pos) /*!< 0x00010000 */
    #define RCC_D3AMR_RTCAMEN                      RCC_D3AMR_RTCAMEN_Msk
    #define RCC_D3AMR_CRCAMEN_Pos                  (19U)
    #define RCC_D3AMR_CRCAMEN_Msk                  (0x1UL << RCC_D3AMR_CRCAMEN_Pos) /*!< 0x00080000 */
    #define RCC_D3AMR_CRCAMEN                      RCC_D3AMR_CRCAMEN_Msk
    #define RCC_D3AMR_SAI4AMEN_Pos                 (21U)
    #define RCC_D3AMR_SAI4AMEN_Msk                 (0x1UL << RCC_D3AMR_SAI4AMEN_Pos) /*!< 0x00200000 */
    #define RCC_D3AMR_SAI4AMEN                     RCC_D3AMR_SAI4AMEN_Msk
    #define RCC_D3AMR_ADC3AMEN_Pos                 (24U)
    #define RCC_D3AMR_ADC3AMEN_Msk                 (0x1UL << RCC_D3AMR_ADC3AMEN_Pos) /*!< 0x01000000 */
    #define RCC_D3AMR_ADC3AMEN                     RCC_D3AMR_ADC3AMEN_Msk


    #define RCC_D3AMR_BKPRAMAMEN_Pos               (28U)
    #define RCC_D3AMR_BKPRAMAMEN_Msk               (0x1UL << RCC_D3AMR_BKPRAMAMEN_Pos) /*!< 0x10000000 */
    #define RCC_D3AMR_BKPRAMAMEN                   RCC_D3AMR_BKPRAMAMEN_Msk
    #define RCC_D3AMR_SRAM4AMEN_Pos                (29U)
    #define RCC_D3AMR_SRAM4AMEN_Msk                (0x1UL << RCC_D3AMR_SRAM4AMEN_Pos) /*!< 0x20000000 */
    #define RCC_D3AMR_SRAM4AMEN                    RCC_D3AMR_SRAM4AMEN_Msk
    /********************  Bit definition for RCC_AHB3LPENR register  **************/
    #define RCC_AHB3LPENR_MDMALPEN_Pos             (0U)
    #define RCC_AHB3LPENR_MDMALPEN_Msk             (0x1UL << RCC_AHB3LPENR_MDMALPEN_Pos)         /*!< 0x00000001 */
    #define RCC_AHB3LPENR_MDMALPEN                 RCC_AHB3LPENR_MDMALPEN_Msk
    #define RCC_AHB3LPENR_DMA2DLPEN_Pos            (4U)
    #define RCC_AHB3LPENR_DMA2DLPEN_Msk            (0x1UL << RCC_AHB3LPENR_DMA2DLPEN_Pos)        /*!< 0x00000010 */
    #define RCC_AHB3LPENR_DMA2DLPEN                RCC_AHB3LPENR_DMA2DLPEN_Msk
    #define RCC_AHB3LPENR_JPGDECLPEN_Pos           (5U)
    #define RCC_AHB3LPENR_JPGDECLPEN_Msk           (0x1UL << RCC_AHB3LPENR_JPGDECLPEN_Pos)       /*!< 0x00000020 */
    #define RCC_AHB3LPENR_JPGDECLPEN               RCC_AHB3LPENR_JPGDECLPEN_Msk
    #define RCC_AHB3LPENR_FLASHLPEN_Pos            (8U)
    #define RCC_AHB3LPENR_FLASHLPEN_Msk            (0x1UL << RCC_AHB3LPENR_FLASHLPEN_Pos)        /*!< 0x00000100 */
    #define RCC_AHB3LPENR_FLASHLPEN                RCC_AHB3LPENR_FLASHLPEN_Msk
    #define RCC_AHB3LPENR_FMCLPEN_Pos              (12U)
    #define RCC_AHB3LPENR_FMCLPEN_Msk              (0x1UL << RCC_AHB3LPENR_FMCLPEN_Pos)          /*!< 0x00001000 */
    #define RCC_AHB3LPENR_FMCLPEN                  RCC_AHB3LPENR_FMCLPEN_Msk
    #define RCC_AHB3LPENR_QSPILPEN_Pos             (14U)
    #define RCC_AHB3LPENR_QSPILPEN_Msk             (0x1UL << RCC_AHB3LPENR_QSPILPEN_Pos)         /*!< 0x00004000 */
    #define RCC_AHB3LPENR_QSPILPEN                 RCC_AHB3LPENR_QSPILPEN_Msk
    #define RCC_AHB3LPENR_SDMMC1LPEN_Pos           (16U)
    #define RCC_AHB3LPENR_SDMMC1LPEN_Msk           (0x1UL << RCC_AHB3LPENR_SDMMC1LPEN_Pos)       /*!< 0x00010000 */
    #define RCC_AHB3LPENR_SDMMC1LPEN               RCC_AHB3LPENR_SDMMC1LPEN_Msk
    #define RCC_AHB3LPENR_DTCM1LPEN_Pos            (28U)
    #define RCC_AHB3LPENR_DTCM1LPEN_Msk            (0x1UL << RCC_AHB3LPENR_DTCM1LPEN_Pos)        /*!< 0x10000000 */
    #define RCC_AHB3LPENR_DTCM1LPEN                RCC_AHB3LPENR_DTCM1LPEN_Msk
    #define RCC_AHB3LPENR_DTCM2LPEN_Pos            (29U)
    #define RCC_AHB3LPENR_DTCM2LPEN_Msk            (0x1UL << RCC_AHB3LPENR_DTCM2LPEN_Pos)        /*!< 0x20000000 */
    #define RCC_AHB3LPENR_DTCM2LPEN                RCC_AHB3LPENR_DTCM2LPEN_Msk
    #define RCC_AHB3LPENR_ITCMLPEN_Pos             (30U)
    #define RCC_AHB3LPENR_ITCMLPEN_Msk             (0x1UL << RCC_AHB3LPENR_ITCMLPEN_Pos)         /*!< 0x40000000 */
    #define RCC_AHB3LPENR_ITCMLPEN                 RCC_AHB3LPENR_ITCMLPEN_Msk
    #define RCC_AHB3LPENR_AXISRAMLPEN_Pos          (31U)
    #define RCC_AHB3LPENR_AXISRAMLPEN_Msk          (0x1UL << RCC_AHB3LPENR_AXISRAMLPEN_Pos)      /*!< 0x80000000 */
    #define RCC_AHB3LPENR_AXISRAMLPEN              RCC_AHB3LPENR_AXISRAMLPEN_Msk


    /********************  Bit definition for RCC_AHB1LPENR register  ***************/
    #define RCC_AHB1LPENR_DMA1LPEN_Pos             (0U)
    #define RCC_AHB1LPENR_DMA1LPEN_Msk             (0x1UL << RCC_AHB1LPENR_DMA1LPEN_Pos) /*!< 0x00000001 */
    #define RCC_AHB1LPENR_DMA1LPEN                 RCC_AHB1LPENR_DMA1LPEN_Msk
    #define RCC_AHB1LPENR_DMA2LPEN_Pos             (1U)
    #define RCC_AHB1LPENR_DMA2LPEN_Msk             (0x1UL << RCC_AHB1LPENR_DMA2LPEN_Pos) /*!< 0x00000002 */
    #define RCC_AHB1LPENR_DMA2LPEN                 RCC_AHB1LPENR_DMA2LPEN_Msk
    #define RCC_AHB1LPENR_ADC12LPEN_Pos            (5U)
    #define RCC_AHB1LPENR_ADC12LPEN_Msk            (0x1UL << RCC_AHB1LPENR_ADC12LPEN_Pos) /*!< 0x00000020 */
    #define RCC_AHB1LPENR_ADC12LPEN                RCC_AHB1LPENR_ADC12LPEN_Msk
    #define RCC_AHB1LPENR_ARTLPEN_Pos              (14U)
    #define RCC_AHB1LPENR_ARTLPEN_Msk              (0x1UL << RCC_AHB1LPENR_ARTLPEN_Pos) /*!< 0x00004000 */
    #define RCC_AHB1LPENR_ARTLPEN                  RCC_AHB1LPENR_ARTLPEN_Msk
    #define RCC_AHB1LPENR_ETH1MACLPEN_Pos          (15U)
    #define RCC_AHB1LPENR_ETH1MACLPEN_Msk          (0x1UL << RCC_AHB1LPENR_ETH1MACLPEN_Pos) /*!< 0x00008000 */
    #define RCC_AHB1LPENR_ETH1MACLPEN              RCC_AHB1LPENR_ETH1MACLPEN_Msk
    #define RCC_AHB1LPENR_ETH1TXLPEN_Pos           (16U)
    #define RCC_AHB1LPENR_ETH1TXLPEN_Msk           (0x1UL << RCC_AHB1LPENR_ETH1TXLPEN_Pos) /*!< 0x00010000 */
    #define RCC_AHB1LPENR_ETH1TXLPEN               RCC_AHB1LPENR_ETH1TXLPEN_Msk
    #define RCC_AHB1LPENR_ETH1RXLPEN_Pos           (17U)
    #define RCC_AHB1LPENR_ETH1RXLPEN_Msk           (0x1UL << RCC_AHB1LPENR_ETH1RXLPEN_Pos) /*!< 0x00020000 */
    #define RCC_AHB1LPENR_ETH1RXLPEN               RCC_AHB1LPENR_ETH1RXLPEN_Msk
    #define RCC_AHB1LPENR_USB1OTGHSLPEN_Pos        (25U)
    #define RCC_AHB1LPENR_USB1OTGHSLPEN_Msk        (0x1UL << RCC_AHB1LPENR_USB1OTGHSLPEN_Pos) /*!< 0x02000000 */
    #define RCC_AHB1LPENR_USB1OTGHSLPEN            RCC_AHB1LPENR_USB1OTGHSLPEN_Msk
    #define RCC_AHB1LPENR_USB1OTGHSULPILPEN_Pos    (26U)
    #define RCC_AHB1LPENR_USB1OTGHSULPILPEN_Msk    (0x1UL << RCC_AHB1LPENR_USB1OTGHSULPILPEN_Pos) /*!< 0x04000000 */
    #define RCC_AHB1LPENR_USB1OTGHSULPILPEN        RCC_AHB1LPENR_USB1OTGHSULPILPEN_Msk
    #define RCC_AHB1LPENR_USB2OTGFSLPEN_Pos        (27U)
    #define RCC_AHB1LPENR_USB2OTGFSLPEN_Msk        (0x1UL << RCC_AHB1LPENR_USB2OTGFSLPEN_Pos) /*!< 0x08000000 */
    #define RCC_AHB1LPENR_USB2OTGFSLPEN            RCC_AHB1LPENR_USB2OTGFSLPEN_Msk
    #define RCC_AHB1LPENR_USB2OTGFSULPILPEN_Pos    (28U)
    #define RCC_AHB1LPENR_USB2OTGFSULPILPEN_Msk    (0x1UL << RCC_AHB1LPENR_USB2OTGFSULPILPEN_Pos) /*!< 0x10000000 */
    #define RCC_AHB1LPENR_USB2OTGFSULPILPEN        RCC_AHB1LPENR_USB2OTGFSULPILPEN_Msk

    /* Legacy define */
    #define RCC_AHB1LPENR_USB2OTGHSLPEN_Pos        RCC_AHB1LPENR_USB2OTGFSLPEN_Pos
    #define RCC_AHB1LPENR_USB2OTGHSLPEN_Msk        RCC_AHB1LPENR_USB2OTGFSLPEN_Msk
    #define RCC_AHB1LPENR_USB2OTGHSLPEN            RCC_AHB1LPENR_USB2OTGFSLPEN
    #define RCC_AHB1LPENR_USB2OTGHSULPILPEN_Pos    RCC_AHB1LPENR_USB2OTGFSULPILPEN_Pos
    #define RCC_AHB1LPENR_USB2OTGHSULPILPEN_Msk    RCC_AHB1LPENR_USB2OTGFSULPILPEN_Msk
    #define RCC_AHB1LPENR_USB2OTGHSULPILPEN        RCC_AHB1LPENR_USB2OTGFSULPILPEN

    /********************  Bit definition for RCC_AHB2LPENR register  ***************/
    #define RCC_AHB2LPENR_DCMILPEN_Pos             (0U)
    #define RCC_AHB2LPENR_DCMILPEN_Msk             (0x1UL << RCC_AHB2LPENR_DCMILPEN_Pos) /*!< 0x00000001 */
    #define RCC_AHB2LPENR_DCMILPEN                 RCC_AHB2LPENR_DCMILPEN_Msk
    #define RCC_AHB2LPENR_RNGLPEN_Pos              (6U)
    #define RCC_AHB2LPENR_RNGLPEN_Msk              (0x1UL << RCC_AHB2LPENR_RNGLPEN_Pos) /*!< 0x00000040 */
    #define RCC_AHB2LPENR_RNGLPEN                  RCC_AHB2LPENR_RNGLPEN_Msk
    #define RCC_AHB2LPENR_SDMMC2LPEN_Pos           (9U)
    #define RCC_AHB2LPENR_SDMMC2LPEN_Msk           (0x1UL << RCC_AHB2LPENR_SDMMC2LPEN_Pos) /*!< 0x00000200 */
    #define RCC_AHB2LPENR_SDMMC2LPEN               RCC_AHB2LPENR_SDMMC2LPEN_Msk
    #define RCC_AHB2LPENR_SRAM1LPEN_Pos          (29U)
    #define RCC_AHB2LPENR_SRAM1LPEN_Msk          (0x1UL << RCC_AHB2LPENR_SRAM1LPEN_Pos) /*!< 0x20000000 */
    #define RCC_AHB2LPENR_SRAM1LPEN              RCC_AHB2LPENR_SRAM1LPEN_Msk
    #define RCC_AHB2LPENR_SRAM2LPEN_Pos          (30U)
    #define RCC_AHB2LPENR_SRAM2LPEN_Msk          (0x1UL << RCC_AHB2LPENR_SRAM2LPEN_Pos) /*!< 0x40000000 */
    #define RCC_AHB2LPENR_SRAM2LPEN              RCC_AHB2LPENR_SRAM2LPEN_Msk
    #define RCC_AHB2LPENR_SRAM3LPEN_Pos          (31U)
    #define RCC_AHB2LPENR_SRAM3LPEN_Msk          (0x1UL << RCC_AHB2LPENR_SRAM3LPEN_Pos) /*!< 0x80000000 */
    #define RCC_AHB2LPENR_SRAM3LPEN              RCC_AHB2LPENR_SRAM3LPEN_Msk

    /* Legacy define */
    #define RCC_AHB2LPENR_D2SRAM1LPEN_Pos          RCC_AHB2LPENR_SRAM1LPEN_Pos
    #define RCC_AHB2LPENR_D2SRAM1LPEN_Msk          RCC_AHB2LPENR_SRAM1LPEN_Msk
    #define RCC_AHB2LPENR_D2SRAM1LPEN              RCC_AHB2LPENR_SRAM1LPEN
    #define RCC_AHB2LPENR_D2SRAM2LPEN_Pos          RCC_AHB2LPENR_SRAM2LPEN_Pos
    #define RCC_AHB2LPENR_D2SRAM2LPEN_Msk          RCC_AHB2LPENR_SRAM2LPEN_Msk
    #define RCC_AHB2LPENR_D2SRAM2LPEN              RCC_AHB2LPENR_SRAM2LPEN
    #define RCC_AHB2LPENR_D2SRAM3LPEN_Pos          RCC_AHB2LPENR_SRAM3LPEN_Pos
    #define RCC_AHB2LPENR_D2SRAM3LPEN_Msk          RCC_AHB2LPENR_SRAM3LPEN_Msk
    #define RCC_AHB2LPENR_D2SRAM3LPEN              RCC_AHB2LPENR_SRAM3LPEN

    /********************  Bit definition for RCC_AHB4LPENR register  ******************/
    #define RCC_AHB4LPENR_GPIOALPEN_Pos            (0U)
    #define RCC_AHB4LPENR_GPIOALPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOALPEN_Pos) /*!< 0x00000001 */
    #define RCC_AHB4LPENR_GPIOALPEN                RCC_AHB4LPENR_GPIOALPEN_Msk
    #define RCC_AHB4LPENR_GPIOBLPEN_Pos            (1U)
    #define RCC_AHB4LPENR_GPIOBLPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOBLPEN_Pos) /*!< 0x00000002 */
    #define RCC_AHB4LPENR_GPIOBLPEN                RCC_AHB4LPENR_GPIOBLPEN_Msk
    #define RCC_AHB4LPENR_GPIOCLPEN_Pos            (2U)
    #define RCC_AHB4LPENR_GPIOCLPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOCLPEN_Pos) /*!< 0x00000004 */
    #define RCC_AHB4LPENR_GPIOCLPEN                RCC_AHB4LPENR_GPIOCLPEN_Msk
    #define RCC_AHB4LPENR_GPIODLPEN_Pos            (3U)
    #define RCC_AHB4LPENR_GPIODLPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIODLPEN_Pos) /*!< 0x00000008 */
    #define RCC_AHB4LPENR_GPIODLPEN                RCC_AHB4LPENR_GPIODLPEN_Msk
    #define RCC_AHB4LPENR_GPIOELPEN_Pos            (4U)
    #define RCC_AHB4LPENR_GPIOELPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOELPEN_Pos) /*!< 0x00000010 */
    #define RCC_AHB4LPENR_GPIOELPEN                RCC_AHB4LPENR_GPIOELPEN_Msk
    #define RCC_AHB4LPENR_GPIOFLPEN_Pos            (5U)
    #define RCC_AHB4LPENR_GPIOFLPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOFLPEN_Pos) /*!< 0x00000020 */
    #define RCC_AHB4LPENR_GPIOFLPEN                RCC_AHB4LPENR_GPIOFLPEN_Msk
    #define RCC_AHB4LPENR_GPIOGLPEN_Pos            (6U)
    #define RCC_AHB4LPENR_GPIOGLPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOGLPEN_Pos) /*!< 0x00000040 */
    #define RCC_AHB4LPENR_GPIOGLPEN                RCC_AHB4LPENR_GPIOGLPEN_Msk
    #define RCC_AHB4LPENR_GPIOHLPEN_Pos            (7U)
    #define RCC_AHB4LPENR_GPIOHLPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOHLPEN_Pos) /*!< 0x00000080 */
    #define RCC_AHB4LPENR_GPIOHLPEN                RCC_AHB4LPENR_GPIOHLPEN_Msk
    #define RCC_AHB4LPENR_GPIOILPEN_Pos            (8U)
    #define RCC_AHB4LPENR_GPIOILPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOILPEN_Pos) /*!< 0x00000100 */
    #define RCC_AHB4LPENR_GPIOILPEN                RCC_AHB4LPENR_GPIOILPEN_Msk
    #define RCC_AHB4LPENR_GPIOJLPEN_Pos            (9U)
    #define RCC_AHB4LPENR_GPIOJLPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOJLPEN_Pos) /*!< 0x00000200 */
    #define RCC_AHB4LPENR_GPIOJLPEN                RCC_AHB4LPENR_GPIOJLPEN_Msk
    #define RCC_AHB4LPENR_GPIOKLPEN_Pos            (10U)
    #define RCC_AHB4LPENR_GPIOKLPEN_Msk            (0x1UL << RCC_AHB4LPENR_GPIOKLPEN_Pos) /*!< 0x00000400 */
    #define RCC_AHB4LPENR_GPIOKLPEN                RCC_AHB4LPENR_GPIOKLPEN_Msk
    #define RCC_AHB4LPENR_CRCLPEN_Pos              (19U)
    #define RCC_AHB4LPENR_CRCLPEN_Msk              (0x1UL << RCC_AHB4LPENR_CRCLPEN_Pos) /*!< 0x00080000 */
    #define RCC_AHB4LPENR_CRCLPEN                  RCC_AHB4LPENR_CRCLPEN_Msk
    #define RCC_AHB4LPENR_BDMALPEN_Pos             (21U)
    #define RCC_AHB4LPENR_BDMALPEN_Msk             (0x1UL << RCC_AHB4LPENR_BDMALPEN_Pos) /*!< 0x00200000 */
    #define RCC_AHB4LPENR_BDMALPEN                 RCC_AHB4LPENR_BDMALPEN_Msk
    #define RCC_AHB4LPENR_ADC3LPEN_Pos             (24U)
    #define RCC_AHB4LPENR_ADC3LPEN_Msk             (0x1UL << RCC_AHB4LPENR_ADC3LPEN_Pos) /*!< 0x01000000 */
    #define RCC_AHB4LPENR_ADC3LPEN                 RCC_AHB4LPENR_ADC3LPEN_Msk
    #define RCC_AHB4LPENR_BKPRAMLPEN_Pos           (28U)
    #define RCC_AHB4LPENR_BKPRAMLPEN_Msk           (0x1UL << RCC_AHB4LPENR_BKPRAMLPEN_Pos) /*!< 0x10000000 */
    #define RCC_AHB4LPENR_BKPRAMLPEN               RCC_AHB4LPENR_BKPRAMLPEN_Msk
    #define RCC_AHB4LPENR_SRAM4LPEN_Pos            (29U)
    #define RCC_AHB4LPENR_SRAM4LPEN_Msk            (0x1UL << RCC_AHB4LPENR_SRAM4LPEN_Pos) /*!< 0x20000000 */
    #define RCC_AHB4LPENR_SRAM4LPEN                RCC_AHB4LPENR_SRAM4LPEN_Msk

    /* Legacy define */
    #define RCC_AHB4LPENR_D3SRAM1LPEN_Pos          RCC_AHB4LPENR_SRAM4LPEN_Pos
    #define RCC_AHB4LPENR_D3SRAM1LPEN_Msk          RCC_AHB4LPENR_SRAM4LPEN_Msk
    #define RCC_AHB4LPENR_D3SRAM1LPEN              RCC_AHB4LPENR_SRAM4LPEN
    /********************  Bit definition for RCC_APB3LPENR register  ******************/
    #define RCC_APB3LPENR_LTDCLPEN_Pos             (3U)
    #define RCC_APB3LPENR_LTDCLPEN_Msk             (0x1UL << RCC_APB3LPENR_LTDCLPEN_Pos) /*!< 0x00000008 */
    #define RCC_APB3LPENR_LTDCLPEN                 RCC_APB3LPENR_LTDCLPEN_Msk
    #define RCC_APB3LPENR_WWDG1LPEN_Pos            (6U)
    #define RCC_APB3LPENR_WWDG1LPEN_Msk            (0x1UL << RCC_APB3LPENR_WWDG1LPEN_Pos) /*!< 0x00000040 */
    #define RCC_APB3LPENR_WWDG1LPEN                RCC_APB3LPENR_WWDG1LPEN_Msk

    /********************  Bit definition for RCC_APB1LLPENR register  ******************/

    #define RCC_APB1LLPENR_TIM2LPEN_Pos            (0U)
    #define RCC_APB1LLPENR_TIM2LPEN_Msk            (0x1UL << RCC_APB1LLPENR_TIM2LPEN_Pos) /*!< 0x00000001 */
    #define RCC_APB1LLPENR_TIM2LPEN                RCC_APB1LLPENR_TIM2LPEN_Msk
    #define RCC_APB1LLPENR_TIM3LPEN_Pos            (1U)
    #define RCC_APB1LLPENR_TIM3LPEN_Msk            (0x1UL << RCC_APB1LLPENR_TIM3LPEN_Pos) /*!< 0x00000002 */
    #define RCC_APB1LLPENR_TIM3LPEN                RCC_APB1LLPENR_TIM3LPEN_Msk
    #define RCC_APB1LLPENR_TIM4LPEN_Pos            (2U)
    #define RCC_APB1LLPENR_TIM4LPEN_Msk            (0x1UL << RCC_APB1LLPENR_TIM4LPEN_Pos) /*!< 0x00000004 */
    #define RCC_APB1LLPENR_TIM4LPEN                RCC_APB1LLPENR_TIM4LPEN_Msk
    #define RCC_APB1LLPENR_TIM5LPEN_Pos            (3U)
    #define RCC_APB1LLPENR_TIM5LPEN_Msk            (0x1UL << RCC_APB1LLPENR_TIM5LPEN_Pos) /*!< 0x00000008 */
    #define RCC_APB1LLPENR_TIM5LPEN                RCC_APB1LLPENR_TIM5LPEN_Msk
    #define RCC_APB1LLPENR_TIM6LPEN_Pos            (4U)
    #define RCC_APB1LLPENR_TIM6LPEN_Msk            (0x1UL << RCC_APB1LLPENR_TIM6LPEN_Pos) /*!< 0x00000010 */
    #define RCC_APB1LLPENR_TIM6LPEN                RCC_APB1LLPENR_TIM6LPEN_Msk
    #define RCC_APB1LLPENR_TIM7LPEN_Pos            (5U)
    #define RCC_APB1LLPENR_TIM7LPEN_Msk            (0x1UL << RCC_APB1LLPENR_TIM7LPEN_Pos) /*!< 0x00000020 */
    #define RCC_APB1LLPENR_TIM7LPEN                RCC_APB1LLPENR_TIM7LPEN_Msk
    #define RCC_APB1LLPENR_TIM12LPEN_Pos           (6U)
    #define RCC_APB1LLPENR_TIM12LPEN_Msk           (0x1UL << RCC_APB1LLPENR_TIM12LPEN_Pos) /*!< 0x00000040 */
    #define RCC_APB1LLPENR_TIM12LPEN               RCC_APB1LLPENR_TIM12LPEN_Msk
    #define RCC_APB1LLPENR_TIM13LPEN_Pos           (7U)
    #define RCC_APB1LLPENR_TIM13LPEN_Msk           (0x1UL << RCC_APB1LLPENR_TIM13LPEN_Pos) /*!< 0x00000080 */
    #define RCC_APB1LLPENR_TIM13LPEN               RCC_APB1LLPENR_TIM13LPEN_Msk
    #define RCC_APB1LLPENR_TIM14LPEN_Pos           (8U)
    #define RCC_APB1LLPENR_TIM14LPEN_Msk           (0x1UL << RCC_APB1LLPENR_TIM14LPEN_Pos) /*!< 0x00000100 */
    #define RCC_APB1LLPENR_TIM14LPEN               RCC_APB1LLPENR_TIM14LPEN_Msk
    #define RCC_APB1LLPENR_LPTIM1LPEN_Pos          (9U)
    #define RCC_APB1LLPENR_LPTIM1LPEN_Msk          (0x1UL << RCC_APB1LLPENR_LPTIM1LPEN_Pos) /*!< 0x00000200 */
    #define RCC_APB1LLPENR_LPTIM1LPEN              RCC_APB1LLPENR_LPTIM1LPEN_Msk

    #define RCC_APB1LLPENR_WWDG2LPEN_Pos           (11U)
    #define RCC_APB1LLPENR_WWDG2LPEN_Msk           (0x1UL << RCC_APB1LLPENR_WWDG2LPEN_Pos) /*!< 0x00000800 */
    #define RCC_APB1LLPENR_WWDG2LPEN               RCC_APB1LLPENR_WWDG2LPEN_Msk

    #define RCC_APB1LLPENR_SPI2LPEN_Pos            (14U)
    #define RCC_APB1LLPENR_SPI2LPEN_Msk            (0x1UL << RCC_APB1LLPENR_SPI2LPEN_Pos) /*!< 0x00004000 */
    #define RCC_APB1LLPENR_SPI2LPEN                RCC_APB1LLPENR_SPI2LPEN_Msk
    #define RCC_APB1LLPENR_SPI3LPEN_Pos            (15U)
    #define RCC_APB1LLPENR_SPI3LPEN_Msk            (0x1UL << RCC_APB1LLPENR_SPI3LPEN_Pos) /*!< 0x00008000 */
    #define RCC_APB1LLPENR_SPI3LPEN                RCC_APB1LLPENR_SPI3LPEN_Msk
    #define RCC_APB1LLPENR_SPDIFRXLPEN_Pos         (16U)
    #define RCC_APB1LLPENR_SPDIFRXLPEN_Msk         (0x1UL << RCC_APB1LLPENR_SPDIFRXLPEN_Pos) /*!< 0x00010000 */
    #define RCC_APB1LLPENR_SPDIFRXLPEN             RCC_APB1LLPENR_SPDIFRXLPEN_Msk
    #define RCC_APB1LLPENR_USART2LPEN_Pos          (17U)
    #define RCC_APB1LLPENR_USART2LPEN_Msk          (0x1UL << RCC_APB1LLPENR_USART2LPEN_Pos) /*!< 0x00020000 */
    #define RCC_APB1LLPENR_USART2LPEN              RCC_APB1LLPENR_USART2LPEN_Msk
    #define RCC_APB1LLPENR_USART3LPEN_Pos          (18U)
    #define RCC_APB1LLPENR_USART3LPEN_Msk          (0x1UL << RCC_APB1LLPENR_USART3LPEN_Pos) /*!< 0x00040000 */
    #define RCC_APB1LLPENR_USART3LPEN              RCC_APB1LLPENR_USART3LPEN_Msk
    #define RCC_APB1LLPENR_UART4LPEN_Pos           (19U)
    #define RCC_APB1LLPENR_UART4LPEN_Msk           (0x1UL << RCC_APB1LLPENR_UART4LPEN_Pos) /*!< 0x00080000 */
    #define RCC_APB1LLPENR_UART4LPEN               RCC_APB1LLPENR_UART4LPEN_Msk
    #define RCC_APB1LLPENR_UART5LPEN_Pos           (20U)
    #define RCC_APB1LLPENR_UART5LPEN_Msk           (0x1UL << RCC_APB1LLPENR_UART5LPEN_Pos) /*!< 0x00100000 */
    #define RCC_APB1LLPENR_UART5LPEN               RCC_APB1LLPENR_UART5LPEN_Msk
    #define RCC_APB1LLPENR_I2C1LPEN_Pos            (21U)
    #define RCC_APB1LLPENR_I2C1LPEN_Msk            (0x1UL << RCC_APB1LLPENR_I2C1LPEN_Pos) /*!< 0x00200000 */
    #define RCC_APB1LLPENR_I2C1LPEN                RCC_APB1LLPENR_I2C1LPEN_Msk
    #define RCC_APB1LLPENR_I2C2LPEN_Pos            (22U)
    #define RCC_APB1LLPENR_I2C2LPEN_Msk            (0x1UL << RCC_APB1LLPENR_I2C2LPEN_Pos) /*!< 0x00400000 */
    #define RCC_APB1LLPENR_I2C2LPEN                RCC_APB1LLPENR_I2C2LPEN_Msk
    #define RCC_APB1LLPENR_I2C3LPEN_Pos            (23U)
    #define RCC_APB1LLPENR_I2C3LPEN_Msk            (0x1UL << RCC_APB1LLPENR_I2C3LPEN_Pos) /*!< 0x00800000 */
    #define RCC_APB1LLPENR_I2C3LPEN                RCC_APB1LLPENR_I2C3LPEN_Msk
    #define RCC_APB1LLPENR_CECLPEN_Pos             (27U)
    #define RCC_APB1LLPENR_CECLPEN_Msk             (0x1UL << RCC_APB1LLPENR_CECLPEN_Pos) /*!< 0x08000000 */
    #define RCC_APB1LLPENR_CECLPEN                 RCC_APB1LLPENR_CECLPEN_Msk
    #define RCC_APB1LLPENR_DAC12LPEN_Pos           (29U)
    #define RCC_APB1LLPENR_DAC12LPEN_Msk           (0x1UL << RCC_APB1LLPENR_DAC12LPEN_Pos) /*!< 0x20000000 */
    #define RCC_APB1LLPENR_DAC12LPEN               RCC_APB1LLPENR_DAC12LPEN_Msk
    #define RCC_APB1LLPENR_UART7LPEN_Pos           (30U)
    #define RCC_APB1LLPENR_UART7LPEN_Msk           (0x1UL << RCC_APB1LLPENR_UART7LPEN_Pos) /*!< 0x40000000 */
    #define RCC_APB1LLPENR_UART7LPEN               RCC_APB1LLPENR_UART7LPEN_Msk
    #define RCC_APB1LLPENR_UART8LPEN_Pos           (31U)
    #define RCC_APB1LLPENR_UART8LPEN_Msk           (0x1UL << RCC_APB1LLPENR_UART8LPEN_Pos) /*!< 0x80000000 */
    #define RCC_APB1LLPENR_UART8LPEN               RCC_APB1LLPENR_UART8LPEN_Msk

    /* Legacy define */
    #define RCC_APB1LLPENR_HDMICECEN_Pos           RCC_APB1LLPENR_CECLPEN_Pos
    #define RCC_APB1LLPENR_HDMICECEN_Msk           RCC_APB1LLPENR_CECLPEN_Msk
    #define RCC_APB1LLPENR_HDMICECEN               RCC_APB1LLPENR_CECLPEN
    /********************  Bit definition for RCC_APB1HLPENR register  ******************/
    #define RCC_APB1HLPENR_CRSLPEN_Pos             (1U)
    #define RCC_APB1HLPENR_CRSLPEN_Msk             (0x1UL << RCC_APB1HLPENR_CRSLPEN_Pos) /*!< 0x00000002 */
    #define RCC_APB1HLPENR_CRSLPEN                 RCC_APB1HLPENR_CRSLPEN_Msk
    #define RCC_APB1HLPENR_SWPMILPEN_Pos           (2U)
    #define RCC_APB1HLPENR_SWPMILPEN_Msk           (0x1UL << RCC_APB1HLPENR_SWPMILPEN_Pos) /*!< 0x00000004 */
    #define RCC_APB1HLPENR_SWPMILPEN               RCC_APB1HLPENR_SWPMILPEN_Msk
    #define RCC_APB1HLPENR_OPAMPLPEN_Pos           (4U)
    #define RCC_APB1HLPENR_OPAMPLPEN_Msk           (0x1UL << RCC_APB1HLPENR_OPAMPLPEN_Pos) /*!< 0x00000010 */
    #define RCC_APB1HLPENR_OPAMPLPEN               RCC_APB1HLPENR_OPAMPLPEN_Msk
    #define RCC_APB1HLPENR_MDIOSLPEN_Pos           (5U)
    #define RCC_APB1HLPENR_MDIOSLPEN_Msk           (0x1UL << RCC_APB1HLPENR_MDIOSLPEN_Pos) /*!< 0x00000020 */
    #define RCC_APB1HLPENR_MDIOSLPEN               RCC_APB1HLPENR_MDIOSLPEN_Msk
    #define RCC_APB1HLPENR_FDCANLPEN_Pos           (8U)
    #define RCC_APB1HLPENR_FDCANLPEN_Msk           (0x1UL << RCC_APB1HLPENR_FDCANLPEN_Pos) /*!< 0x00000100 */
    #define RCC_APB1HLPENR_FDCANLPEN               RCC_APB1HLPENR_FDCANLPEN_Msk

    /********************  Bit definition for RCC_APB2LPENR register  ******************/
    #define RCC_APB2LPENR_TIM1LPEN_Pos             (0U)
    #define RCC_APB2LPENR_TIM1LPEN_Msk             (0x1UL << RCC_APB2LPENR_TIM1LPEN_Pos) /*!< 0x00000001 */
    #define RCC_APB2LPENR_TIM1LPEN                 RCC_APB2LPENR_TIM1LPEN_Msk
    #define RCC_APB2LPENR_TIM8LPEN_Pos             (1U)
    #define RCC_APB2LPENR_TIM8LPEN_Msk             (0x1UL << RCC_APB2LPENR_TIM8LPEN_Pos) /*!< 0x00000002 */
    #define RCC_APB2LPENR_TIM8LPEN                 RCC_APB2LPENR_TIM8LPEN_Msk
    #define RCC_APB2LPENR_USART1LPEN_Pos           (4U)
    #define RCC_APB2LPENR_USART1LPEN_Msk           (0x1UL << RCC_APB2LPENR_USART1LPEN_Pos) /*!< 0x00000010 */
    #define RCC_APB2LPENR_USART1LPEN               RCC_APB2LPENR_USART1LPEN_Msk
    #define RCC_APB2LPENR_USART6LPEN_Pos           (5U)
    #define RCC_APB2LPENR_USART6LPEN_Msk           (0x1UL << RCC_APB2LPENR_USART6LPEN_Pos) /*!< 0x00000020 */
    #define RCC_APB2LPENR_USART6LPEN               RCC_APB2LPENR_USART6LPEN_Msk
    #define RCC_APB2LPENR_SPI1LPEN_Pos             (12U)
    #define RCC_APB2LPENR_SPI1LPEN_Msk             (0x1UL << RCC_APB2LPENR_SPI1LPEN_Pos) /*!< 0x00001000 */
    #define RCC_APB2LPENR_SPI1LPEN                 RCC_APB2LPENR_SPI1LPEN_Msk
    #define RCC_APB2LPENR_SPI4LPEN_Pos             (13U)
    #define RCC_APB2LPENR_SPI4LPEN_Msk             (0x1UL << RCC_APB2LPENR_SPI4LPEN_Pos) /*!< 0x00002000 */
    #define RCC_APB2LPENR_SPI4LPEN                 RCC_APB2LPENR_SPI4LPEN_Msk
    #define RCC_APB2LPENR_TIM15LPEN_Pos            (16U)
    #define RCC_APB2LPENR_TIM15LPEN_Msk            (0x1UL << RCC_APB2LPENR_TIM15LPEN_Pos) /*!< 0x00010000 */
    #define RCC_APB2LPENR_TIM15LPEN                RCC_APB2LPENR_TIM15LPEN_Msk
    #define RCC_APB2LPENR_TIM16LPEN_Pos            (17U)
    #define RCC_APB2LPENR_TIM16LPEN_Msk            (0x1UL << RCC_APB2LPENR_TIM16LPEN_Pos) /*!< 0x00020000 */
    #define RCC_APB2LPENR_TIM16LPEN                RCC_APB2LPENR_TIM16LPEN_Msk
    #define RCC_APB2LPENR_TIM17LPEN_Pos            (18U)
    #define RCC_APB2LPENR_TIM17LPEN_Msk            (0x1UL << RCC_APB2LPENR_TIM17LPEN_Pos) /*!< 0x00040000 */
    #define RCC_APB2LPENR_TIM17LPEN                RCC_APB2LPENR_TIM17LPEN_Msk
    #define RCC_APB2LPENR_SPI5LPEN_Pos             (20U)
    #define RCC_APB2LPENR_SPI5LPEN_Msk             (0x1UL << RCC_APB2LPENR_SPI5LPEN_Pos) /*!< 0x00100000 */
    #define RCC_APB2LPENR_SPI5LPEN                 RCC_APB2LPENR_SPI5LPEN_Msk
    #define RCC_APB2LPENR_SAI1LPEN_Pos             (22U)
    #define RCC_APB2LPENR_SAI1LPEN_Msk             (0x1UL << RCC_APB2LPENR_SAI1LPEN_Pos) /*!< 0x00400000 */
    #define RCC_APB2LPENR_SAI1LPEN                 RCC_APB2LPENR_SAI1LPEN_Msk
    #define RCC_APB2LPENR_SAI2LPEN_Pos             (23U)
    #define RCC_APB2LPENR_SAI2LPEN_Msk             (0x1UL << RCC_APB2LPENR_SAI2LPEN_Pos) /*!< 0x00800000 */
    #define RCC_APB2LPENR_SAI2LPEN                 RCC_APB2LPENR_SAI2LPEN_Msk
    #define RCC_APB2LPENR_SAI3LPEN_Pos             (24U)
    #define RCC_APB2LPENR_SAI3LPEN_Msk             (0x1UL << RCC_APB2LPENR_SAI3LPEN_Pos) /*!< 0x01000000 */
    #define RCC_APB2LPENR_SAI3LPEN                 RCC_APB2LPENR_SAI3LPEN_Msk
    #define RCC_APB2LPENR_DFSDM1LPEN_Pos           (28U)
    #define RCC_APB2LPENR_DFSDM1LPEN_Msk           (0x1UL << RCC_APB2LPENR_DFSDM1LPEN_Pos) /*!< 0x10000000 */
    #define RCC_APB2LPENR_DFSDM1LPEN               RCC_APB2LPENR_DFSDM1LPEN_Msk
    #define RCC_APB2LPENR_HRTIMLPEN_Pos            (29U)
    #define RCC_APB2LPENR_HRTIMLPEN_Msk            (0x1UL << RCC_APB2LPENR_HRTIMLPEN_Pos) /*!< 0x20000000 */
    #define RCC_APB2LPENR_HRTIMLPEN                RCC_APB2LPENR_HRTIMLPEN_Msk

    /********************  Bit definition for RCC_APB4LPENR register  ******************/
    #define RCC_APB4LPENR_SYSCFGLPEN_Pos           (1U)
    #define RCC_APB4LPENR_SYSCFGLPEN_Msk           (0x1UL << RCC_APB4LPENR_SYSCFGLPEN_Pos) /*!< 0x00000002 */
    #define RCC_APB4LPENR_SYSCFGLPEN               RCC_APB4LPENR_SYSCFGLPEN_Msk
    #define RCC_APB4LPENR_LPUART1LPEN_Pos          (3U)
    #define RCC_APB4LPENR_LPUART1LPEN_Msk          (0x1UL << RCC_APB4LPENR_LPUART1LPEN_Pos) /*!< 0x00000008 */
    #define RCC_APB4LPENR_LPUART1LPEN              RCC_APB4LPENR_LPUART1LPEN_Msk
    #define RCC_APB4LPENR_SPI6LPEN_Pos             (5U)
    #define RCC_APB4LPENR_SPI6LPEN_Msk             (0x1UL << RCC_APB4LPENR_SPI6LPEN_Pos) /*!< 0x00000020 */
    #define RCC_APB4LPENR_SPI6LPEN                 RCC_APB4LPENR_SPI6LPEN_Msk
    #define RCC_APB4LPENR_I2C4LPEN_Pos             (7U)
    #define RCC_APB4LPENR_I2C4LPEN_Msk             (0x1UL << RCC_APB4LPENR_I2C4LPEN_Pos) /*!< 0x00000080 */
    #define RCC_APB4LPENR_I2C4LPEN                 RCC_APB4LPENR_I2C4LPEN_Msk
    #define RCC_APB4LPENR_LPTIM2LPEN_Pos           (9U)
    #define RCC_APB4LPENR_LPTIM2LPEN_Msk           (0x1UL << RCC_APB4LPENR_LPTIM2LPEN_Pos) /*!< 0x00000200 */
    #define RCC_APB4LPENR_LPTIM2LPEN               RCC_APB4LPENR_LPTIM2LPEN_Msk
    #define RCC_APB4LPENR_LPTIM3LPEN_Pos           (10U)
    #define RCC_APB4LPENR_LPTIM3LPEN_Msk           (0x1UL << RCC_APB4LPENR_LPTIM3LPEN_Pos) /*!< 0x00000400 */
    #define RCC_APB4LPENR_LPTIM3LPEN               RCC_APB4LPENR_LPTIM3LPEN_Msk
    #define RCC_APB4LPENR_LPTIM4LPEN_Pos           (11U)
    #define RCC_APB4LPENR_LPTIM4LPEN_Msk           (0x1UL << RCC_APB4LPENR_LPTIM4LPEN_Pos) /*!< 0x00000800 */
    #define RCC_APB4LPENR_LPTIM4LPEN               RCC_APB4LPENR_LPTIM4LPEN_Msk
    #define RCC_APB4LPENR_LPTIM5LPEN_Pos           (12U)
    #define RCC_APB4LPENR_LPTIM5LPEN_Msk           (0x1UL << RCC_APB4LPENR_LPTIM5LPEN_Pos) /*!< 0x00001000 */
    #define RCC_APB4LPENR_LPTIM5LPEN               RCC_APB4LPENR_LPTIM5LPEN_Msk
    #define RCC_APB4LPENR_COMP12LPEN_Pos           (14U)
    #define RCC_APB4LPENR_COMP12LPEN_Msk           (0x1UL << RCC_APB4LPENR_COMP12LPEN_Pos) /*!< 0x00004000 */
    #define RCC_APB4LPENR_COMP12LPEN               RCC_APB4LPENR_COMP12LPEN_Msk
    #define RCC_APB4LPENR_VREFLPEN_Pos             (15U)
    #define RCC_APB4LPENR_VREFLPEN_Msk             (0x1UL << RCC_APB4LPENR_VREFLPEN_Pos) /*!< 0x00008000 */
    #define RCC_APB4LPENR_VREFLPEN                 RCC_APB4LPENR_VREFLPEN_Msk
    #define RCC_APB4LPENR_RTCAPBLPEN_Pos           (16U)
    #define RCC_APB4LPENR_RTCAPBLPEN_Msk           (0x1UL << RCC_APB4LPENR_RTCAPBLPEN_Pos) /*!< 0x00010000 */
    #define RCC_APB4LPENR_RTCAPBLPEN               RCC_APB4LPENR_RTCAPBLPEN_Msk
    #define RCC_APB4LPENR_SAI4LPEN_Pos             (21U)
    #define RCC_APB4LPENR_SAI4LPEN_Msk             (0x1UL << RCC_APB4LPENR_SAI4LPEN_Pos) /*!< 0x00200000 */
    #define RCC_APB4LPENR_SAI4LPEN                 RCC_APB4LPENR_SAI4LPEN_Msk


    /********************  Bit definition for RCC_RSR register  *******************/
    #define RCC_RSR_RMVF_Pos                       (16U)
    #define RCC_RSR_RMVF_Msk                       (0x1UL << RCC_RSR_RMVF_Pos)     /*!< 0x00010000 */
    #define RCC_RSR_RMVF                           RCC_RSR_RMVF_Msk
    #define RCC_RSR_C1RSTF_Pos                     (17U)
    #define RCC_RSR_C1RSTF_Msk                     (0x1UL << RCC_RSR_C1RSTF_Pos)   /*!< 0x00020000 */
    #define RCC_RSR_C1RSTF                         RCC_RSR_C1RSTF_Msk
    #define RCC_RSR_D1RSTF_Pos                     (19U)
    #define RCC_RSR_D1RSTF_Msk                     (0x1UL << RCC_RSR_D1RSTF_Pos)   /*!< 0x00080000 */
    #define RCC_RSR_D1RSTF                         RCC_RSR_D1RSTF_Msk
    #define RCC_RSR_D2RSTF_Pos                     (20U)
    #define RCC_RSR_D2RSTF_Msk                     (0x1UL << RCC_RSR_D2RSTF_Pos)   /*!< 0x00100000 */
    #define RCC_RSR_D2RSTF                         RCC_RSR_D2RSTF_Msk
    #define RCC_RSR_BORRSTF_Pos                    (21U)
    #define RCC_RSR_BORRSTF_Msk                    (0x1UL << RCC_RSR_BORRSTF_Pos)  /*!< 0x00200000 */
    #define RCC_RSR_BORRSTF                        RCC_RSR_BORRSTF_Msk
    #define RCC_RSR_PINRSTF_Pos                    (22U)
    #define RCC_RSR_PINRSTF_Msk                    (0x1UL << RCC_RSR_PINRSTF_Pos)  /*!< 0x00400000 */
    #define RCC_RSR_PINRSTF                        RCC_RSR_PINRSTF_Msk
    #define RCC_RSR_PORRSTF_Pos                    (23U)
    #define RCC_RSR_PORRSTF_Msk                    (0x1UL << RCC_RSR_PORRSTF_Pos)  /*!< 0x00800000 */
    #define RCC_RSR_PORRSTF                        RCC_RSR_PORRSTF_Msk
    #define RCC_RSR_SFT1RSTF_Pos                   (24U)
    #define RCC_RSR_SFT1RSTF_Msk                   (0x1UL << RCC_RSR_SFT1RSTF_Pos) /*!< 0x01000000 */
    #define RCC_RSR_SFT1RSTF                       RCC_RSR_SFT1RSTF_Msk
    #define RCC_RSR_IWDG1RSTF_Pos                  (26U)
    #define RCC_RSR_IWDG1RSTF_Msk                  (0x1UL << RCC_RSR_IWDG1RSTF_Pos) /*!< 0x04000000 */
    #define RCC_RSR_IWDG1RSTF                      RCC_RSR_IWDG1RSTF_Msk
    #define RCC_RSR_WWDG1RSTF_Pos                  (28U)
    #define RCC_RSR_WWDG1RSTF_Msk                  (0x1UL << RCC_RSR_WWDG1RSTF_Pos) /*!< 0x10000000 */
    #define RCC_RSR_WWDG1RSTF                      RCC_RSR_WWDG1RSTF_Msk

    #define RCC_RSR_WWDG2RSTF_Pos                  (29U)
    #define RCC_RSR_WWDG2RSTF_Msk                  (0x1UL << RCC_RSR_WWDG2RSTF_Pos) /*!< 0x20000000 */
    #define RCC_RSR_WWDG2RSTF                      RCC_RSR_WWDG2RSTF_Msk
    #define RCC_RSR_IWDG2RSTF_Pos                  (27U)
    #define RCC_RSR_IWDG2RSTF_Msk                  (0x1UL << RCC_RSR_IWDG2RSTF_Pos) /*!< 0x08000000 */
    #define RCC_RSR_IWDG2RSTF                      RCC_RSR_IWDG2RSTF_Msk
    #define RCC_RSR_SFT2RSTF_Pos                   (25U)
    #define RCC_RSR_SFT2RSTF_Msk                   (0x1UL << RCC_RSR_SFT2RSTF_Pos) /*!< 0x02000000 */
    #define RCC_RSR_SFT2RSTF                       RCC_RSR_SFT2RSTF_Msk
    #define RCC_RSR_C2RSTF_Pos                     (18U)
    #define RCC_RSR_C2RSTF_Msk                     (0x1UL << RCC_RSR_C2RSTF_Pos)   /*!< 0x00040000 */
    #define RCC_RSR_C2RSTF                         RCC_RSR_C2RSTF_Msk
    #define RCC_RSR_LPWR1RSTF_Pos                  (30U)
    #define RCC_RSR_LPWR1RSTF_Msk                  (0x1UL << RCC_RSR_LPWR1RSTF_Pos) /*!< 0x40000000 */
    #define RCC_RSR_LPWR1RSTF                      RCC_RSR_LPWR1RSTF_Msk
    #define RCC_RSR_LPWR2RSTF_Pos                  (31U)
    #define RCC_RSR_LPWR2RSTF_Msk                  (0x1UL << RCC_RSR_LPWR2RSTF_Pos) /*!< 0x80000000 */
    #define RCC_RSR_LPWR2RSTF                      RCC_RSR_LPWR2RSTF_Msk

  #if defined(__cplusplus)
    } /* extern "C" */
  #endif

#endif /* SRC_PORT_GCC_STM32H745ZI_CM7_DEVICE_RCC_REG_H */