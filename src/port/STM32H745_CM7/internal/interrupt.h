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
 * @internal
 * @file src/port/STM32H745_CM7/internal/interrupt.h
 * @authors Aaron McBride
 * @brief Interrupt prototypes, definitions and vtable.
 */

#pragma once
#include <stdint.h>
#include "src/port/STM32H745_CM7/internal/compat.h"

COMPAT_FILE

#ifdef __cplusplus
  extern "C" {
#endif

  /**********************************************************************************************
   * Implementation Resources
   **********************************************************************************************/

  // Attributes for exception handler prototypes
  #define EXC_ATTR_ TI_WEAK TI_USED TI_ALIAS("_default_exc_handler")

  // Attributes for IRQ handler prototypes
  #define IRQ_ATTR_ TI_WEAK TI_USED TI_ALIAS("_default_irq_handler")

  // Fallback exception interrupt handler
  void _default_exc_handler() { COMPAT_ASM("bkpt #3"); }

  // Fallback IRQ interrupt handler
  void _default_irq_handler() { COMPAT_ASM("bkpt #4"); }

  /**********************************************************************************************
   * General Reference Definitions
   **********************************************************************************************/

  /** @brief The number of implement IRQs */
  static const int32_t IRQ_COUNT = 150;

  /** @brief Number of priority bits supported the NVIC. */
  static const int32_t NVIC_PRIO_BITS = 4;

  /** @brief Maximum supported exception priority value. */
  static const int32_t NVIC_MAX_PRIO = 16;

  /** @brief Offset between exception and IRQ numbers. */
  static const int32_t IRQN_EXC_OFFSET = 16;

  /**********************************************************************************************
   * Exception Number Definitions
   **********************************************************************************************/

  static const int32_t RST_EXC_NUM         = 1;     /** @brief Reset exception. */
  static const int32_t NMI_EXC_NUM         = 2;     /** @brief Non-maskable interrupt. */
  static const int32_t HARD_FAULT_EXC_NUM  = 3;     /** @brief Hard fault. */
  static const int32_t MEM_MANAGE_EXC_NUM  = 4;     /** @brief Memory management fault (MPU). */
  static const int32_t BUS_FAULT_EXC_NUM   = 5;     /** @brief Bus fault. */
  static const int32_t USAGE_FAULT_EXC_NUM = 6;     /** @brief Usage fault. */
  static const int32_t SVC_EXC_NUM         = 11;    /** @brief System service call exception. */
  static const int32_t DEBUG_MON_EXC_NUM   = 12;    /** @brief Debug monitor fault/exception. */
  static const int32_t PENDSV_EXC_NUM      = 14;    /** @brief Pended system service call exception. */
  static const int32_t SYSTICK_EXC_NUM     = 15;    /** @brief SysTick interrupt. */

  /**********************************************************************************************
   * IRQ Number Definitions
   **********************************************************************************************/

  static const int32_t WWDG1_IRQ_NUM                  = 0;     /** @brief Window watchdog. */
  static const int32_t PVD_PVM_IRQ_NUM                = 1;     /** @brief PVD through EXTI line. */
  static const int32_t RTC_TAMP_STAMP_CSS_LSE_IRQ_NUM = 2;     /** @brief RTC tamper, timestamp. */
  static const int32_t RTC_WKUP_IRQ_NUM               = 3;     /** @brief RTC wakeup interrupt. */
  static const int32_t FLASH_IRQ_NUM                  = 4;     /** @brief Flash memory. */
  static const int32_t RCC_IRQ_NUM                    = 5;     /** @brief RCC global interrupt. */
  static const int32_t ADC1_2_IRQ_NUM                 = 18;    /** @brief ADC1 and ADC2. */
  static const int32_t EXTI9_5_IRQ_NUM                = 23;    /** @brief EXTI line[9:5] interrupts. */
  static const int32_t TIM1_BRK_IRQ_NUM               = 24;    /** @brief TIM1 break interrupt. */
  static const int32_t TIM1_UP_IRQ_NUM                = 25;    /** @brief TIM1 update interrupt. */
  static const int32_t TIM1_TRG_COM_IRQ_NUM           = 26;    /** @brief TIM1 trigger and commutation. */
  static const int32_t EXTI15_10_IRQ_NUM              = 40;    /** @brief EXTI line[15:10] interrupts. */
  static const int32_t RTC_ALARM_IRQ_NUM              = 41;    /** @brief RTC alarms (A and B). */
  static const int32_t TIM8_BRK_TIM12_IRQ_NUM         = 43;    /** @brief TIM8 and 12 break global. */
  static const int32_t TIM8_UP_TIM13_IRQ_NUM          = 44;    /** @brief TIM8 and 13 update global. */
  static const int32_t TIM8_TRG_COM_TIM14_IRQ_NUM     = 45;    /** @brief TIM8 and 14 trigger /commutation and global. */
  static const int32_t FMC_IRQ_NUM                    = 48;    /** @brief FMC global interrupt. */
  static const int32_t TIM6_DAC_IRQ_NUM               = 54;    /** @brief TIM6 global interrupt. */
  static const int32_t ETH_IRQ_NUM                    = 61;    /** @brief Ethernet global interrupt. */
  static const int32_t ETH_WKUP_IRQ_NUM               = 62;    /** @brief Ethernet wakeup through EXTI. */
  static const int32_t FDCAN_CAL_IRQ_NUM              = 63;    /** @brief CAN2TX interrupts. */
  static const int32_t CM4_SEV_IT_IRQ_NUM             = 66;    /** @brief Arm cortex-m4 send even interrupt. */
  static const int32_t OTG_HS_EP1_OUT_IRQ_NUM         = 74;    /** @brief OTG_HS out global interrupt. */
  static const int32_t OTG_HS_EP1_IN_IRQ_NUM          = 75;    /** @brief OTG_HS in global interrupt. */
  static const int32_t OTG_HS_WKUP_IRQ_NUM            = 76;    /** @brief OTG_HS wakeup interrupt. */
  static const int32_t OTG_HS_IRQ_NUM                 = 77;    /** @brief OTG_HS global interrupt. */
  static const int32_t DCMI_IRQ_NUM                   = 78;    /** @brief DCMI global interrupt. */
  static const int32_t CRYP_IRQ_NUM                   = 79;    /** @brief CRYP global interrupt. */
  static const int32_t HASH_RNG_IRQ_NUM               = 80;    /** @brief HASH and RNG. */
  static const int32_t FPU_IRQ_NUM                    = 81;    /** @brief Floating point unit interrupt. */
  static const int32_t LTDC_IRQ_NUM                   = 88;    /** @brief LCD-TFT global interrupt. */
  static const int32_t LTDC_ER_IRQ_NUM                = 89;    /** @brief LCD-TFT error interrupt. */
  static const int32_t DMA2D_IRQ_NUM                  = 90;    /** @brief DMA2D global interrupt. */
  static const int32_t QUADSPI_IRQ_NUM                = 92;    /** @brief QuadSPI global interrupt. */
  static const int32_t CEC_IRQ_NUM                    = 94;    /** @brief HDMI-CEC global interrupt. */
  static const int32_t SPDIF_IRQ_NUM                  = 97;    /** @brief SPDIFRX global interrupt. */
  static const int32_t OTG_FS_EP1_OUT_IRQ_NUM         = 98;    /** @brief OTG_FS out global interrupt. */
  static const int32_t OTG_FS_EP1_IN_IRQ_NUM          = 99;    /** @brief OTG_FS in global interrupt. */
  static const int32_t OTG_FS_WKUP_IRQ_NUM            = 100;   /** @brief OTG_FS wakeup. */
  static const int32_t OTG_FS_IRQ_NUM                 = 101;   /** @brief OTG_FS global interrupt. */
  static const int32_t DMAMUX1_OV_IRQ_NUM             = 102;   /** @brief DMAMUX1 overrun interrupt. */
  static const int32_t HRTIM_MST_IRQ_NUM              = 103;   /** @brief HRTIM master timer interrupt. */
  static const int32_t HRTIM_FLT_IRQ_NUM              = 109;   /** @brief HRTIM fault interrupt. */
  static const int32_t SWPMI_IRQ_NUM                  = 115;   /** @brief SWPMI global interrupt. */
  static const int32_t MDIOS_WKUP_IRQ_NUM             = 119;   /** @brief MDIOS wakeup. */
  static const int32_t MDIOS_IRQ_NUM                  = 120;   /** @brief MDIOS global interrupt. */
  static const int32_t JPEG_IRQ_NUM                   = 121;   /** @brief JPEG global interrupt. */
  static const int32_t MDMA_IRQ_NUM                   = 122;   /** @brief MDMA global interrupt. */
  static const int32_t HSEM0_IRQ_NUM                  = 125;   /** @brief HSEM global interrupt 0. */
  static const int32_t ADC3_IRQ_NUM                   = 127;   /** @brief ADC3 global interrupt. */
  static const int32_t DMAMUX2_OVR_IRQ_NUM            = 128;   /** @brief DMAMUX2 overrun interrupt. */
  static const int32_t WWDG2_RST_IRQ_NUM              = 129;   /** @brief Window watchdog interrupt. */
  static const int32_t COMP_IRQ_NUM                   = 137;   /** @brief COMP1 and COMP2. */
  static const int32_t LPUART_IRQ_NUM                 = 142;   /** @brief LPUART global interrupt. */
  static const int32_t CRS_IRQ_NUM                    = 144;   /** @brief Clock recovery system globa. */
  static const int32_t HOLD_CORE_IRQ_NUM              = 148;   /** @brief Hold core interrupt. */
  static const int32_t WKUP_IRQ_NUM                   = 149;   /** @brief WKUP1 to WKUP6 pins. */

  static const DMAx_STRx_IRQ_NUM[3][8] = {
    [1] = {
      [0] = 11,    /** @brief DMA1 stream0 interrupt. */
      [1] = 12,    /** @brief DMA1 stream1 interrupt. */
      [2] = 13,    /** @brief DMA1 stream2 interrupt. */
      [3] = 14,    /** @brief DMA1 stream3 interrupt. */
      [4] = 15,    /** @brief DMA1 stream4 interrupt. */
      [5] = 16,    /** @brief DMA1 stream5 interrupt. */
      [6] = 17,    /** @brief DMA1 stream6 interrupt. */
      [7] = 47,    /** @brief DMA1 stream7 interrupt. */
    },
    [2] = {
      [0] = 56,    /** @brief DMA2 stream0 interrupt. */
      [1] = 57,    /** @brief DMA2 stream1 interrupt. */
      [2] = 58,    /** @brief DMA2 stream2 interrupt. */
      [3] = 59,    /** @brief DMA2 stream3 interrupt. */
      [4] = 60,    /** @brief DMA2 stream4 interrupt. */
      [5] = 68,    /** @brief DMA2 stream5 interrupt. */
      [6] = 69,    /** @brief DMA2 stream6 interrupt. */
      [7] = 70,    /** @brief DMA2 stream7 interrupt. */
    },
  };

  static const int32_t FDCANx_ITx_IRQ_NUM[3][2] = {
    [1] = {
      [0] = 19,   /** @brief FDCAN1 interrupt 0. */
      [1] = 21,   /** @brief FDCAN1 interrupt 1. */
    },
    [2] = {
      [0] = 20,   /** @brief FDCAN2 interrupt 0. */
      [1] = 22,   /** @brief FDCAN2 interrupt 1. */
    },
  };

  static const int32_t HRTIM_TIMx_IRQ_NUM[6] = {
    [1] = 104,   /** @brief HRTIM timer A interrupt. */
    [2] = 105,   /** @brief HRTIM timer B interrupt. */
    [3] = 106,   /** @brief HRTIM timer C interrupt. */
    [4] = 107,   /** @brief HRTIM timer D interrupt. */
    [5] = 108,   /** @brief HRTIM timer E interrupt. */
  };

  static const int32_t BDMA_CHx_IRQ_NUM[9] = {
    [1] = 129,    /** @brief BDMA channel 1 interrupt. */
    [2] = 130,    /** @brief BDMA channel 2 interrupt. */
    [3] = 131,    /** @brief BDMA channel 3 interrupt. */
    [4] = 132,    /** @brief BDMA channel 4 interrupt. */
    [5] = 133,    /** @brief BDMA channel 5 interrupt. */
    [6] = 134,    /** @brief BDMA channel 6 interrupt. */
    [7] = 135,    /** @brief BDMA channel 7 interrupt. */
    [8] = 136,    /** @brief BDMA channel 8 interrupt. */
  };

  static const int32_t I2Cx_EV_IRQ_NUM[5] = {
    [1] = 31,     /** @brief I2C1 event interrupt. */
    [2] = 33,     /** @brief I2C2 event interrupt. */
    [3] = 72,     /** @brief I2C3 event interrupt. */
    [4] = 95,     /** @brief I2C4 event interrupt. */
  };

  static const int32_t I2Cx_ER_IRQ_NUM[5] = {
    [1] = 32,     /** @brief I2C1 error interrupt. */
    [2] = 34,     /** @brief I2C2 error interrupt. */
    [3] = 73,     /** @brief I2C3 error interrupt. */
    [4] = 96,     /** @brief I2C4 error interrupt. */
  };

  static const int32_t SAIx_IRQ_NUM[5] = {
    [1] = 87,    /** @brief SAI1 global interrupt. */
    [2] = 91,    /** @brief SAI2 global interrupt. */
    [3] = 114,   /** @brief SAI3 global interrupt. */
    [4] = 146,   /** @brief SAI4 global interrupt. */
  };

  static const int32_t SDMMCx_IRQ_NUM[3] = {
    [1] = 49,     /** @brief SDMMC1 global interrupt. */
    [2] = 124,    /** @brief SDMMC2 global interrupt. */
  };

  static const int32_t SPIx_IRQ_NUM[7] = {
    [1] = 35,     /** @brief SPI1 global interrupt. */
    [2] = 36,     /** @brief SPI2 global interrupt. */
    [3] = 51,     /** @brief SPI3 global interrupt. */
    [4] = 84,     /** @brief SPI4 global interrupt. */
    [5] = 85,     /** @brief SPI5 global interrupt. */
    [6] = 86,     /** @brief SPI6 global interrupt. */
  };

  static const int32_t LPTIMx_IRQ_NUM[6] = {
    [1] = 93,     /** @brief LPTIM1 global interrupt. */
    [2] = 138,    /** @brief LPTIM2 timer interrupt. */
    [3] = 139,    /** @brief LPTIM3 timer interrupt. */
    [4] = 140,    /** @brief LPTIM4 timer interrupt. */
    [5] = 141,    /** @brief LPTIM5 timer interrupt. */
  };

  static const int32_t EXTIx_IRQ_NUM[5] = {
    [0] = 6,    /** @brief EXTI line 0 interrupt. */
    [1] = 7,    /** @brief EXTI line 1 interrupt. */
    [2] = 8,    /** @brief EXTI line 2 interrupt. */
    [3] = 9,    /** @brief EXTI line 3interrupt. */
    [4] = 10,   /** @brief EXTI line 4interrupt. */
  };

  static const int32_t DFSDM1_FLTx_IRQ_NUM[4] = {
    [0] = 110,    /** @brief DFSDM1 filter 0 interrupt. */
    [1] = 111,    /** @brief DFSDM1 filter 1 interrupt. */
    [2] = 112,    /** @brief DFSDM1 filter 2 interrupt. */
    [3] = 113,    /** @brief DFSDM1 filter 3 interrupt. */
  };

  static const int32_t TIMx_IRQ_NUM[18] = {
    [2]  = 28,     /** @brief TIM2 global interrupt. */
    [3]  = 29,     /** @brief TIM3 global interrupt. */
    [4]  = 30,     /** @brief TIM4 global interrupt. */
    [5]  = 50,     /** @brief TIM5 global interrupt. */
    [7]  = 55,     /** @brief TIM7 global interrupt. */
    [15] = 116,    /** @brief TIM15 global interrupt. */
    [16] = 117,    /** @brief TIM16 global interrupt. */
    [17] = 118,    /** @brief TIM17 global interrupt. */
  };

  static const int32_t USARTx_IRQ_NUM[7] = {
    [1] = 37,    /** @brief USART1 global interrupt. */
    [2] = 38,    /** @brief USART2 global interrupt. */
    [3] = 39,    /** @brief USART3 global interrupt. */
    [6] = 71,    /** @brief USART6 global interrupt. */
  };

  static const int32_t UARTx_IRQ_NUM[9] = {
    [4] = 52,    /** @brief UART4 global interrupt. */
    [5] = 53,    /** @brief UART5 global interrupt. */
    [7] = 82,    /** @brief UART7 global interrupt. */
    [8] = 83,    /** @brief UART8 global interrupt. */
  };

  static const int32_t TIMx_CC_IRQ_NUM[9] = {
    [1] = 27,    /** @brief TIM1 capture / compare. */
    [8] = 46,    /** @brief TIM8 capture / compare. */
  };

  /*************************************************************************************************
   * Exception Handler Prototypes
   *************************************************************************************************/

  EXC_ATTR_ void reset_exc_handler();         /** @brief Reset exception. */
  EXC_ATTR_ void nmi_exc_handler();           /** @brief Non-maskable interrupt. */
  EXC_ATTR_ void hard_fault_exc_handler();    /** @brief Hard fault. */
  EXC_ATTR_ void mem_manage_exc_handler();    /** @brief Memory management fault (MPU). */
  EXC_ATTR_ void bus_fault_exc_handler();     /** @brief Bus fault. */
  EXC_ATTR_ void usage_fault_exc_handler();   /** @brief Usage fault. */
  EXC_ATTR_ void svc_exc_handler();           /** @brief System service call exception. */
  EXC_ATTR_ void debug_mon_exc_handler();     /** @brief Debug monitor fault/exception. */
  EXC_ATTR_ void pendsv_exc_handler();        /** @brief Pended system service call exception. */
  EXC_ATTR_ void systick_exc_handler();       /** @brief SysTick interrupt. */

  /*************************************************************************************************
   * IRQ Handler Prototypes
   *************************************************************************************************/

  IRQ_ATTR_ void wwdg1_irq_handler();                    /** @brief Window watchdog interrupt. */
  IRQ_ATTR_ void pvd_pvm_irq_handler();                  /** @brief PVD through EXTI line. */
  IRQ_ATTR_ void rtc_tamp_stamp_css_lse_irq_handler();   /** @brief RTC tamper, timestamp. */
  IRQ_ATTR_ void rtc_wkup_irq_handler();                 /** @brief RTC wakeup interrupt. */
  IRQ_ATTR_ void flash_irq_handler();                    /** @brief Flash memory. */
  IRQ_ATTR_ void rcc_irq_handler();                      /** @brief RCC global interrupt. */
  IRQ_ATTR_ void exti0_irq_handler();                    /** @brief EXTI line 0 interrupt. */
  IRQ_ATTR_ void exti1_irq_handler();                    /** @brief EXTI line 1 interrupt. */
  IRQ_ATTR_ void exti2_irq_handler();                    /** @brief EXTI line 2 interrupt. */
  IRQ_ATTR_ void exti3_irq_handler();                    /** @brief EXTI line 3 interrupt. */
  IRQ_ATTR_ void exti4_irq_handler();                    /** @brief EXTI line 4 interrupt. */
  IRQ_ATTR_ void dma_str0_irq_handler();                 /** @brief DMA1 stream0. */
  IRQ_ATTR_ void dma_str1_irq_handler();                 /** @brief DMA1 stream1. */
  IRQ_ATTR_ void dma_str2_irq_handler();                 /** @brief DMA1 stream2. */
  IRQ_ATTR_ void dma_str3_irq_handler();                 /** @brief DMA1 stream3. */
  IRQ_ATTR_ void dma_str4_irq_handler();                 /** @brief DMA1 stream4. */
  IRQ_ATTR_ void dma_str5_irq_handler();                 /** @brief DMA1 stream5. */
  IRQ_ATTR_ void dma_str6_irq_handler();                 /** @brief DMA1 stream6. */
  IRQ_ATTR_ void adc1_2_irq_handler();                   /** @brief ADC1 and ADC2. */
  IRQ_ATTR_ void fdcan1_it0_irq_handler();               /** @brief FDCAN1 interrupt 0. */
  IRQ_ATTR_ void fdcan2_it0_irq_handler();               /** @brief FDCAN2 interrupt 0. */
  IRQ_ATTR_ void fdcan1_it1_irq_handler();               /** @brief FDCAN1 interrupt 1. */
  IRQ_ATTR_ void fdcan2_it1_irq_handler();               /** @brief FDCAN2 interrupt 1. */
  IRQ_ATTR_ void exti9_5_irq_handler();                  /** @brief EXTI line[9:5] interrupts. */
  IRQ_ATTR_ void tim1_brk_irq_handler();                 /** @brief TIM1 break interrupt. */
  IRQ_ATTR_ void tim1_up_irq_handler();                  /** @brief TIM1 update interrupt. */
  IRQ_ATTR_ void tim1_trg_com_irq_handler();             /** @brief TIM1 trigger and commutation. */
  IRQ_ATTR_ void tim1_cc_irq_handler();                  /** @brief TIM1 capture / compare. */
  IRQ_ATTR_ void tim2_irq_handler();                     /** @brief TIM2 global interrupt. */
  IRQ_ATTR_ void tim3_irq_handler();                     /** @brief TIM3 global interrupt. */
  IRQ_ATTR_ void tim4_irq_handler();                     /** @brief TIM4 global interrupt. */
  IRQ_ATTR_ void i2c1_ev_irq_handler();                  /** @brief I2C1 event interrupt. */
  IRQ_ATTR_ void i2c1_er_irq_handler();                  /** @brief I2C1 error interrupt. */
  IRQ_ATTR_ void i2c2_ev_irq_handler();                  /** @brief I2C2 event interrupt. */
  IRQ_ATTR_ void i2c2_er_irq_handler();                  /** @brief I2C2 error interrupt. */
  IRQ_ATTR_ void spi1_irq_handler();                     /** @brief SPI1 global interrupt. */
  IRQ_ATTR_ void spi2_irq_handler();                     /** @brief SPI2 global interrupt. */
  IRQ_ATTR_ void usart1_irq_handler();                   /** @brief USART1 global interrupt. */
  IRQ_ATTR_ void usart2_irq_handler();                   /** @brief USART2 global interrupt. */
  IRQ_ATTR_ void usart3_irq_handler();                   /** @brief USART3 global interrupt. */
  IRQ_ATTR_ void exti15_10_irq_handler();                /** @brief EXTI line[15:10] interrupts. */
  IRQ_ATTR_ void rtc_alarm_irq_handler();                /** @brief RTC alarms (A and B). */
  IRQ_ATTR_ void tim8_brk_tim12_irq_handler();           /** @brief TIM8 and 12 break global. */
  IRQ_ATTR_ void tim8_up_tim13_irq_handler();            /** @brief TIM8 and 13 update global. */
  IRQ_ATTR_ void tim8_trg_com_tim14_irq_handler();       /** @brief TIM8 and 14 trigger /commutation and global. */
  IRQ_ATTR_ void tim8_cc_irq_handler();                  /** @brief TIM8 capture / compare. */
  IRQ_ATTR_ void dma1_str7_irq_handler();                /** @brief DMA1 stream7. */
  IRQ_ATTR_ void fmc_irq_handler();                      /** @brief FMC global interrupt. */
  IRQ_ATTR_ void sdmmc1_irq_handler();                   /** @brief SDMMC global interrupt. */
  IRQ_ATTR_ void tim5_irq_handler();                     /** @brief TIM5 global interrupt. */
  IRQ_ATTR_ void spi3_irq_handler();                     /** @brief SPI3 global interrupt. */
  IRQ_ATTR_ void uart4_irq_handler();                    /** @brief UART4 global interrupt. */
  IRQ_ATTR_ void uart5_irq_handler();                    /** @brief UART5 global interrupt. */
  IRQ_ATTR_ void tim6_dac_irq_handler();                 /** @brief TIM6 global interrupt. */
  IRQ_ATTR_ void tim7_irq_handler();                     /** @brief TIM7 global interrupt. */
  IRQ_ATTR_ void dma2_str0_irq_handler();                /** @brief DMA2 stream0 interrupt. */
  IRQ_ATTR_ void dma2_str1_irq_handler();                /** @brief DMA2 stream1 interrupt. */
  IRQ_ATTR_ void dma2_str2_irq_handler();                /** @brief DMA2 stream2 interrupt. */
  IRQ_ATTR_ void dma2_str3_irq_handler();                /** @brief DMA2 stream3 interrupt. */
  IRQ_ATTR_ void dma2_str4_irq_handler();                /** @brief DMA2 stream4 interrupt. */
  IRQ_ATTR_ void eth_irq_handler();                      /** @brief Ethernet global interrupt. */
  IRQ_ATTR_ void eth_wkup_irq_handler();                 /** @brief Ethernet wakeup through EXTI. */
  IRQ_ATTR_ void fdcan_cal_irq_handler();                /** @brief CAN2TX interrupts. */
  IRQ_ATTR_ void cm4_sev_it_irq_handler();               /** @brief Arm cortex-m4 send even interrupt. */
  IRQ_ATTR_ void dma2_str5_irq_handler();                /** @brief DMA2 stream5 interrupt. */
  IRQ_ATTR_ void dma2_str6_irq_handler();                /** @brief DMA2 stream6 interrupt. */
  IRQ_ATTR_ void dma2_str7_irq_handler();                /** @brief DMA2 stream7 interrupt. */
  IRQ_ATTR_ void usart6_irq_handler();                   /** @brief USART6 global interrupt. */
  IRQ_ATTR_ void i2c3_ev_irq_handler();                  /** @brief I2C3 event interrupt. */
  IRQ_ATTR_ void i2c3_er_irq_handler();                  /** @brief I2C3 error interrupt. */
  IRQ_ATTR_ void otg_hs_ep1_out_irq_handler();           /** @brief OTG_HS out global interrupt. */
  IRQ_ATTR_ void otg_hs_ep1_in_irq_handler();            /** @brief OTG_HS in global interrupt. */
  IRQ_ATTR_ void otg_hs_wkup_irq_handler();              /** @brief OTG_HS wakeup interrupt. */
  IRQ_ATTR_ void otg_hs_irq_handler();                   /** @brief OTG_HS global interrupt. */
  IRQ_ATTR_ void dcmi_irq_handler();                     /** @brief DCMI global interrupt. */
  IRQ_ATTR_ void cryp_irq_handler();                     /** @brief CRYP global interrupt. */
  IRQ_ATTR_ void hash_rng_irq_handler();                 /** @brief HASH and RNG. */
  IRQ_ATTR_ void fpu_irq_handler();                      /** @brief Floating point unit interrupt. */
  IRQ_ATTR_ void uart7_irq_handler();                    /** @brief UART7 global interrupt. */
  IRQ_ATTR_ void uart8_irq_handler();                    /** @brief UART8 global interrupt. */
  IRQ_ATTR_ void spi4_irq_handler();                     /** @brief SPI4 global interrupt. */
  IRQ_ATTR_ void spi5_irq_handler();                     /** @brief SPI5 global interrupt. */
  IRQ_ATTR_ void spi6_irq_handler();                     /** @brief SPI6 global interrupt. */
  IRQ_ATTR_ void sai1_irq_handler();                     /** @brief SAI1 global interrupt. */
  IRQ_ATTR_ void ltdc_irq_handler();                     /** @brief LCD-TFT global interrupt. */
  IRQ_ATTR_ void ltdc_er_irq_handler();                  /** @brief LCD-TFT error interrupt. */
  IRQ_ATTR_ void dma2d_irq_handler();                    /** @brief DMA2D global interrupt. */
  IRQ_ATTR_ void sai2_irq_handler();                     /** @brief SAI2 global interrupt. */
  IRQ_ATTR_ void quadspi_irq_handler();                  /** @brief QuadSPI global interrupt. */
  IRQ_ATTR_ void lptim1_irq_handler();                   /** @brief LPTIM1 global interrupt. */
  IRQ_ATTR_ void cec_irq_handler();                      /** @brief HDMI-CEC global interrupt. */
  IRQ_ATTR_ void i2c4_ev_irq_handler();                  /** @brief I2C4 event interrupt. */
  IRQ_ATTR_ void i2c4_er_irq_handler();                  /** @brief I2C4 error interrupt. */
  IRQ_ATTR_ void spdif_irq_handler();                    /** @brief SPDIFRX global interrupt. */
  IRQ_ATTR_ void otg_fs_ep1_out_irq_handler();           /** @brief OTG_FS out global interrupt. */
  IRQ_ATTR_ void otg_fs_ep1_in_irq_handler();            /** @brief OTG_FS in global interrupt. */
  IRQ_ATTR_ void otg_fs_wkup_irq_handler();              /** @brief OTG_FS wakeup. */
  IRQ_ATTR_ void otg_fs_irq_handler();                   /** @brief OTG_FS global interrupt. */
  IRQ_ATTR_ void dmamux1_ov_irq_handler();               /** @brief DMAMUX1 overrun interrupt. */
  IRQ_ATTR_ void hrtim_mst_irq_handler();                /** @brief HRTIM master timer interrupt. */
  IRQ_ATTR_ void hrtim_tima_irq_handler();               /** @brief HRTIM timer A interrupt. */
  IRQ_ATTR_ void hrtim_timb_irq_handler();               /** @brief HRTIM timer B interrupt. */
  IRQ_ATTR_ void hrtim_timc_irq_handler();               /** @brief HRTIM timer C interrupt. */
  IRQ_ATTR_ void hrtim_timd_irq_handler();               /** @brief HRTIM timer D interrupt. */
  IRQ_ATTR_ void hrtim_time_irq_handler();               /** @brief HRTIM timer E interrupt. */
  IRQ_ATTR_ void hrtim_flt_irq_handler();                /** @brief HRTIM fault interrupt. */
  IRQ_ATTR_ void dfsdm1_flt0_irq_handler();              /** @brief DFSDM1 filter 0 interrupt. */
  IRQ_ATTR_ void dfsdm1_flt1_irq_handler();              /** @brief DFSDM1 filter 1 interrupt. */
  IRQ_ATTR_ void dfsdm1_flt2_irq_handler();              /** @brief DFSDM1 filter 2 interrupt. */
  IRQ_ATTR_ void dfsdm1_flt3_irq_handler();              /** @brief DFSDM1 filter 3 interrupt. */
  IRQ_ATTR_ void sai3_irq_handler();                     /** @brief SAI3 global interrupt. */
  IRQ_ATTR_ void swpmi_irq_handler();                    /** @brief SWPMI global interrupt. */
  IRQ_ATTR_ void tim15_irq_handler();                    /** @brief TIM15 global interrupt. */
  IRQ_ATTR_ void tim16_irq_handler();                    /** @brief TIM16 global interrupt. */
  IRQ_ATTR_ void tim17_irq_handler();                    /** @brief TIM17 global interrupt. */
  IRQ_ATTR_ void mdios_wkup_irq_handler();               /** @brief MDIOS wakeup. */
  IRQ_ATTR_ void mdios_irq_handler();                    /** @brief MDIOS global interrupt. */
  IRQ_ATTR_ void jpeg_irq_handler();                     /** @brief JPEG global interrupt. */
  IRQ_ATTR_ void mdma_irq_handler();                     /** @brief MDMA. */
  IRQ_ATTR_ void sdmmc2_irq_handler();                   /** @brief SDMMC global interrupt. */
  IRQ_ATTR_ void hsem0_irq_handler();                    /** @brief HSEM global interrupt 0. */
  IRQ_ATTR_ void adc3_irq_handler();                     /** @brief ADC3 global interrupt. */
  IRQ_ATTR_ void dmamux2_ovr_irq_handler();              /** @brief DMAMUX2 overrun interrupt. */
  IRQ_ATTR_ void bdma_ch1_irq_handler();                 /** @brief BDMA channel 1 interrupt. */
  IRQ_ATTR_ void bdma_ch2_irq_handler();                 /** @brief BDMA channel 2 interrupt. */
  IRQ_ATTR_ void bdma_ch3_irq_handler();                 /** @brief BDMA channel 3 interrupt. */
  IRQ_ATTR_ void bdma_ch4_irq_handler();                 /** @brief BDMA channel 4 interrupt. */
  IRQ_ATTR_ void bdma_ch5_irq_handler();                 /** @brief BDMA channel 5 interrupt. */
  IRQ_ATTR_ void bdma_ch6_irq_handler();                 /** @brief BDMA channel 6 interrupt. */
  IRQ_ATTR_ void bdma_ch7_irq_handler();                 /** @brief BDMA channel 7 interrupt. */
  IRQ_ATTR_ void bdma_ch8_irq_handler();                 /** @brief BDMA channel 8 interrupt. */
  IRQ_ATTR_ void comp_irq_handler();                     /** @brief COMP1 and COMP2. */
  IRQ_ATTR_ void lptim2_irq_handler();                   /** @brief LPTIM2 timer interrupt. */
  IRQ_ATTR_ void lptim3_irq_handler();                   /** @brief LPTIM3 timer interrupt. */
  IRQ_ATTR_ void lptim4_irq_handler();                   /** @brief LPTIM4 timer interrupt. */
  IRQ_ATTR_ void lptim5_irq_handler();                   /** @brief LPTIM5 timer interrupt. */
  IRQ_ATTR_ void lpuart_irq_handler();                   /** @brief LPUART global interrupt. */
  IRQ_ATTR_ void wwdg2_rst_irq_handler();                /** @brief Window watchdog reset interrupt. */
  IRQ_ATTR_ void crs_irq_handler();                      /** @brief Clock recovery system globa. */
  IRQ_ATTR_ void sai4_irq_handler();                     /** @brief SAI4 global interrupt. */
  IRQ_ATTR_ void hold_core_irq_handler();                /** @brief Hold core interrupt. */
  IRQ_ATTR_ void wkup_irq_handler();                     /** @brief WKUP1 to WKUP6 pins. */

  /*************************************************************************************************
   * Interrupt Vector Table Definition
   *************************************************************************************************/

  /** @brief Interrupt vector table. */
  TI_SECTION(".isr_vector") 
  const int32_t vtable[165] = {
    [0]   = (uint32_t)&reset_exc_handler,                    /** @brief reset exception. */
    [1]   = (uint32_t)&nmi_exc_handler,                      /** @brief Non-maskable interrupt. */
    [2]   = (uint32_t)&hard_fault_exc_handler,               /** @brief Hard fault. */
    [3]   = (uint32_t)&mem_manage_exc_handler,               /** @brief Memory management fault (MPU). */
    [4]   = (uint32_t)&bus_fault_exc_handler,                /** @brief Bus fault. */
    [5]   = (uint32_t)&usage_fault_exc_handler,              /** @brief Usage fault. */
    [10]  = (uint32_t)&svc_exc_handler,                      /** @brief System service call exception. */
    [11]  = (uint32_t)&debug_mon_exc_handler,                /** @brief Debug monitor fault/exception. */
    [13]  = (uint32_t)&pendsv_exc_handler,                   /** @brief Pended system service call exception. */
    [14]  = (uint32_t)&systick_exc_handler,                  /** @brief SysTick interrupt. */
    [15]  = (uint32_t)&wwdg1_irq_handler,                    /** @brief Window watchdog interrupt. */
    [16]  = (uint32_t)&pvd_pvm_irq_handler,                  /** @brief PVD through EXTI line. */
    [17]  = (uint32_t)&rtc_tamp_stamp_css_lse_irq_handler,   /** @brief RTC tamper, timestamp. */
    [18]  = (uint32_t)&rtc_wkup_irq_handler,                 /** @brief RTC wakeup interrupt. */
    [19]  = (uint32_t)&flash_irq_handler,                    /** @brief Flash memory. */
    [20]  = (uint32_t)&rcc_irq_handler,                      /** @brief RCC global interrupt. */
    [21]  = (uint32_t)&exti0_irq_handler,                    /** @brief EXTI line 0 interrupt. */
    [22]  = (uint32_t)&exti1_irq_handler,                    /** @brief EXTI line 1 interrupt. */
    [23]  = (uint32_t)&exti2_irq_handler,                    /** @brief EXTI line 2 interrupt. */
    [24]  = (uint32_t)&exti3_irq_handler,                    /** @brief EXTI line 3interrupt. */
    [25]  = (uint32_t)&exti4_irq_handler,                    /** @brief EXTI line 4interrupt. */
    [26]  = (uint32_t)&dma_str0_irq_handler,                 /** @brief DMA1 stream0. */
    [27]  = (uint32_t)&dma_str1_irq_handler,                 /** @brief DMA1 stream1. */
    [28]  = (uint32_t)&dma_str2_irq_handler,                 /** @brief DMA1 stream2. */
    [29]  = (uint32_t)&dma_str3_irq_handler,                 /** @brief DMA1 stream3. */
    [30]  = (uint32_t)&dma_str4_irq_handler,                 /** @brief DMA1 stream4. */
    [31]  = (uint32_t)&dma_str5_irq_handler,                 /** @brief DMA1 stream5. */
    [32]  = (uint32_t)&dma_str6_irq_handler,                 /** @brief DMA1 stream6. */
    [33]  = (uint32_t)&adc1_2_irq_handler,                   /** @brief ADC1 and ADC2. */
    [34]  = (uint32_t)&fdcan1_it0_irq_handler,               /** @brief FDCAN1 interrupt 0. */
    [35]  = (uint32_t)&fdcan2_it0_irq_handler,               /** @brief FDCAN2 interrupt 0. */
    [36]  = (uint32_t)&fdcan1_it1_irq_handler,               /** @brief FDCAN1 interrupt 1. */
    [37]  = (uint32_t)&fdcan2_it1_irq_handler,               /** @brief FDCAN2 interrupt 1. */
    [38]  = (uint32_t)&exti9_5_irq_handler,                  /** @brief EXTI line[9:5] interrupts. */
    [39]  = (uint32_t)&tim1_brk_irq_handler,                 /** @brief TIM1 break interrupt. */
    [40]  = (uint32_t)&tim1_up_irq_handler,                  /** @brief TIM1 update interrupt. */
    [41]  = (uint32_t)&tim1_trg_com_irq_handler,             /** @brief TIM1 trigger and commutation. */
    [42]  = (uint32_t)&tim1_cc_irq_handler,                  /** @brief TIM1 capture / compare. */
    [43]  = (uint32_t)&tim2_irq_handler,                     /** @brief TIM2 global interrupt. */
    [44]  = (uint32_t)&tim3_irq_handler,                     /** @brief TIM3 global interrupt. */
    [45]  = (uint32_t)&tim4_irq_handler,                     /** @brief TIM4 global interrupt. */
    [46]  = (uint32_t)&i2c1_ev_irq_handler,                  /** @brief I2C1 event interrupt. */
    [47]  = (uint32_t)&i2c1_er_irq_handler,                  /** @brief I2C1 error interrupt. */
    [48]  = (uint32_t)&i2c2_ev_irq_handler,                  /** @brief I2C2 event interrupt. */
    [49]  = (uint32_t)&i2c2_er_irq_handler,                  /** @brief I2C2 error interrupt. */
    [50]  = (uint32_t)&spi1_irq_handler,                     /** @brief SPI1 global interrupt. */
    [51]  = (uint32_t)&spi2_irq_handler,                     /** @brief SPI2 global interrupt. */
    [52]  = (uint32_t)&usart1_irq_handler,                   /** @brief USART1 global interrupt. */
    [53]  = (uint32_t)&usart2_irq_handler,                   /** @brief USART2 global interrupt. */
    [54]  = (uint32_t)&usart3_irq_handler,                   /** @brief USART3 global interrupt. */
    [55]  = (uint32_t)&exti15_10_irq_handler,                /** @brief EXTI line[15:10] interrupts. */
    [56]  = (uint32_t)&rtc_alarm_irq_handler,                /** @brief RTC alarms (A and B). */
    [58]  = (uint32_t)&tim8_brk_tim12_irq_handler,           /** @brief TIM8 and 12 break global. */
    [59]  = (uint32_t)&tim8_up_tim13_irq_handler,            /** @brief TIM8 and 13 update global. */
    [60]  = (uint32_t)&tim8_trg_com_tim14_irq_handler,       /** @brief TIM8 and 14 trigger /commutation and global. */
    [61]  = (uint32_t)&tim8_cc_irq_handler,                  /** @brief TIM8 capture / compare. */
    [62]  = (uint32_t)&dma1_str7_irq_handler,                /** @brief DMA1 stream7. */
    [63]  = (uint32_t)&fmc_irq_handler,                      /** @brief FMC global interrupt. */
    [64]  = (uint32_t)&sdmmc1_irq_handler,                   /** @brief SDMMC global interrupt. */
    [65]  = (uint32_t)&tim5_irq_handler,                     /** @brief TIM5 global interrupt. */
    [66]  = (uint32_t)&spi3_irq_handler,                     /** @brief SPI3 global interrupt. */
    [67]  = (uint32_t)&uart4_irq_handler,                    /** @brief UART4 global interrupt. */
    [68]  = (uint32_t)&uart5_irq_handler,                    /** @brief UART5 global interrupt. */
    [69]  = (uint32_t)&tim6_dac_irq_handler,                 /** @brief TIM6 global interrupt. */
    [70]  = (uint32_t)&tim7_irq_handler,                     /** @brief TIM7 global interrupt. */
    [71]  = (uint32_t)&dma2_str0_irq_handler,                /** @brief DMA2 stream0 interrupt. */
    [72]  = (uint32_t)&dma2_str1_irq_handler,                /** @brief DMA2 stream1 interrupt. */
    [73]  = (uint32_t)&dma2_str2_irq_handler,                /** @brief DMA2 stream2 interrupt. */
    [74]  = (uint32_t)&dma2_str3_irq_handler,                /** @brief DMA2 stream3 interrupt. */
    [75]  = (uint32_t)&dma2_str4_irq_handler,                /** @brief DMA2 stream4 interrupt. */
    [76]  = (uint32_t)&eth_irq_handler,                      /** @brief Ethernet global interrupt. */
    [77]  = (uint32_t)&eth_wkup_irq_handler,                 /** @brief Ethernet wakeup through EXTI. */
    [78]  = (uint32_t)&fdcan_cal_irq_handler,                /** @brief CAN2TX interrupts. */
    [80]  = (uint32_t)&cm4_sev_it_irq_handler,               /** @brief Arm cortex-m4 send even interrupt. */
    [83]  = (uint32_t)&dma2_str5_irq_handler,                /** @brief DMA2 stream5 interrupt. */
    [84]  = (uint32_t)&dma2_str6_irq_handler,                /** @brief DMA2 stream6 interrupt. */
    [85]  = (uint32_t)&dma2_str7_irq_handler,                /** @brief DMA2 stream7 interrupt. */
    [86]  = (uint32_t)&usart6_irq_handler,                   /** @brief USART6 global interrupt. */
    [87]  = (uint32_t)&i2c3_ev_irq_handler,                  /** @brief I2C3 event interrupt. */
    [88]  = (uint32_t)&i2c3_er_irq_handler,                  /** @brief I2C3 error interrupt. */
    [89]  = (uint32_t)&otg_hs_ep1_out_irq_handler,           /** @brief OTG_HS out global interrupt. */
    [90]  = (uint32_t)&otg_hs_ep1_in_irq_handler,            /** @brief OTG_HS in global interrupt. */
    [91]  = (uint32_t)&otg_hs_wkup_irq_handler,              /** @brief OTG_HS wakeup interrupt. */
    [92]  = (uint32_t)&otg_hs_irq_handler,                   /** @brief OTG_HS global interrupt. */
    [93]  = (uint32_t)&dcmi_irq_handler,                     /** @brief DCMI global interrupt. */
    [94]  = (uint32_t)&cryp_irq_handler,                     /** @brief CRYP global interrupt. */
    [95]  = (uint32_t)&hash_rng_irq_handler,                 /** @brief HASH and RNG. */
    [96]  = (uint32_t)&fpu_irq_handler,                      /** @brief Floating point unit interrupt. */
    [97]  = (uint32_t)&uart7_irq_handler,                    /** @brief UART7 global interrupt. */
    [98]  = (uint32_t)&uart8_irq_handler,                    /** @brief UART8 global interrupt. */
    [99]  = (uint32_t)&spi4_irq_handler,                     /** @brief SPI4 global interrupt. */
    [100] = (uint32_t)&spi5_irq_handler,                     /** @brief SPI5 global interrupt. */
    [101] = (uint32_t)&spi6_irq_handler,                     /** @brief SPI6 global interrupt. */
    [102] = (uint32_t)&sai1_irq_handler,                     /** @brief SAI1 global interrupt. */
    [103] = (uint32_t)&ltdc_irq_handler,                     /** @brief LCD-TFT global interrupt. */
    [104] = (uint32_t)&ltdc_er_irq_handler,                  /** @brief LCD-TFT error interrupt. */
    [105] = (uint32_t)&dma2d_irq_handler,                    /** @brief DMA2D global interrupt. */
    [106] = (uint32_t)&sai2_irq_handler,                     /** @brief SAI2 global interrupt. */
    [107] = (uint32_t)&quadspi_irq_handler,                  /** @brief QuadSPI global interrupt. */
    [108] = (uint32_t)&lptim1_irq_handler,                   /** @brief LPTIM1 global interrupt. */
    [109] = (uint32_t)&cec_irq_handler,                      /** @brief HDMI-CEC global interrupt. */
    [110] = (uint32_t)&i2c4_ev_irq_handler,                  /** @brief I2C4 event interrupt. */
    [111] = (uint32_t)&i2c4_er_irq_handler,                  /** @brief I2C4 error interrupt. */
    [112] = (uint32_t)&spdif_irq_handler,                    /** @brief SPDIFRX global interrupt. */
    [113] = (uint32_t)&otg_fs_ep1_out_irq_handler,           /** @brief OTG_FS out global interrupt. */
    [114] = (uint32_t)&otg_fs_ep1_in_irq_handler,            /** @brief OTG_FS in global interrupt. */
    [115] = (uint32_t)&otg_fs_wkup_irq_handler,              /** @brief OTG_FS wakeup. */
    [116] = (uint32_t)&otg_fs_irq_handler,                   /** @brief OTG_FS global interrupt. */
    [117] = (uint32_t)&dmamux1_ov_irq_handler,               /** @brief DMAMUX1 overrun interrupt. */
    [118] = (uint32_t)&hrtim_mst_irq_handler,                /** @brief HRTIM master timer interrupt. */
    [119] = (uint32_t)&hrtim_tima_irq_handler,               /** @brief HRTIM timer A interrupt. */
    [120] = (uint32_t)&hrtim_timb_irq_handler,               /** @brief HRTIM timer B interrupt. */
    [121] = (uint32_t)&hrtim_timc_irq_handler,               /** @brief HRTIM timer C interrupt. */
    [122] = (uint32_t)&hrtim_timd_irq_handler,               /** @brief HRTIM timer D interrupt. */
    [123] = (uint32_t)&hrtim_time_irq_handler,               /** @brief HRTIM timer E interrupt. */
    [124] = (uint32_t)&hrtim_flt_irq_handler,                /** @brief HRTIM fault interrupt. */
    [125] = (uint32_t)&dfsdm1_flt0_irq_handler,              /** @brief DFSDM1 filter 0 interrupt. */
    [126] = (uint32_t)&dfsdm1_flt1_irq_handler,              /** @brief DFSDM1 filter 1 interrupt. */
    [127] = (uint32_t)&dfsdm1_flt2_irq_handler,              /** @brief DFSDM1 filter 2 interrupt. */
    [128] = (uint32_t)&dfsdm1_flt3_irq_handler,              /** @brief DFSDM1 filter 3 interrupt. */
    [129] = (uint32_t)&sai3_irq_handler,                     /** @brief SAI3 global interrupt. */
    [130] = (uint32_t)&swpmi_irq_handler,                    /** @brief SWPMI global interrupt. */
    [131] = (uint32_t)&tim15_irq_handler,                    /** @brief TIM15 global interrupt. */
    [132] = (uint32_t)&tim16_irq_handler,                    /** @brief TIM16 global interrupt. */
    [133] = (uint32_t)&tim17_irq_handler,                    /** @brief TIM17 global interrupt. */
    [134] = (uint32_t)&mdios_wkup_irq_handler,               /** @brief MDIOS wakeup. */
    [135] = (uint32_t)&mdios_irq_handler,                    /** @brief MDIOS global interrupt. */
    [136] = (uint32_t)&jpeg_irq_handler,                     /** @brief JPEG global interrupt. */
    [137] = (uint32_t)&mdma_irq_handler,                     /** @brief MDMA. */
    [139] = (uint32_t)&sdmmc2_irq_handler,                   /** @brief SDMMC global interrupt. */
    [141] = (uint32_t)&hsem0_irq_handler,                    /** @brief HSEM global interrupt 1. */
    [142] = (uint32_t)&adc3_irq_handler,                     /** @brief ADC3 global interrupt. */
    [143] = (uint32_t)&dmamux2_ovr_irq_handler,              /** @brief DMAMUX2 overrun interrupt. */
    [144] = (uint32_t)&bdma_ch1_irq_handler,                 /** @brief BDMA channel 1 interrupt. */
    [145] = (uint32_t)&bdma_ch2_irq_handler,                 /** @brief BDMA channel 2 interrupt. */
    [146] = (uint32_t)&bdma_ch3_irq_handler,                 /** @brief BDMA channel 3 interrupt. */
    [147] = (uint32_t)&bdma_ch4_irq_handler,                 /** @brief BDMA channel 4 interrupt. */
    [148] = (uint32_t)&bdma_ch5_irq_handler,                 /** @brief BDMA channel 5 interrupt. */
    [149] = (uint32_t)&bdma_ch6_irq_handler,                 /** @brief BDMA channel 6 interrupt. */
    [150] = (uint32_t)&bdma_ch7_irq_handler,                 /** @brief BDMA channel 7 interrupt. */
    [151] = (uint32_t)&bdma_ch8_irq_handler,                 /** @brief BDMA channel 8 interrupt. */
    [152] = (uint32_t)&comp_irq_handler,                     /** @brief COMP1 and COMP2. */
    [153] = (uint32_t)&lptim2_irq_handler,                   /** @brief LPTIM2 timer interrupt. */
    [154] = (uint32_t)&lptim3_irq_handler,                   /** @brief LPTIM2 timer interrupt. */
    [155] = (uint32_t)&lptim4_irq_handler,                   /** @brief LPTIM2 timer interrupt. */
    [156] = (uint32_t)&lptim5_irq_handler,                   /** @brief LPTIM2 timer interrupt. */
    [157] = (uint32_t)&lpuart_irq_handler,                   /** @brief LPUART global interrupt. */
    [158] = (uint32_t)&wwdg2_rst_irq_handler,                /** @brief Window watchdog reset interrupt. */
    [159] = (uint32_t)&crs_irq_handler,                      /** @brief Clock recovery system globa. */
    [161] = (uint32_t)&sai4_irq_handler,                     /** @brief SAI4 global interrupt. */
    [163] = (uint32_t)&hold_core_irq_handler,                /** @brief Hold core interrupt. */
    [164] = (uint32_t)&wkup_irq_handler,                     /** @brief WKUP1 to WKUP6 pins. */
  };

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */