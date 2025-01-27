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
 * @file src/STM32H7x5/exc.h
 * @authors Aaron McBride
 * @brief Exception/interrupt definitions.
 */

#pragma once
#include <stdint.h>

#ifdef __ICCARM__
  #pragma language = extended
#endif

#ifdef __cplusplus
  extern "C" {
#endif

  #define CM7_STACK_START__ 0x20040000
  #define CM7_STACK_END__  0x20050000

  #define CM4_STACK_START__ 0x20050000
  #define CM4_STACK_END__  0x20060000

  /**********************************************************************************************
   * @section Implementation Resources
   **********************************************************************************************/

  // Attributes for exception handler prototypes
  #define EXC_ATTR_ __attribute__((weak, used, alias("default_handler")))

  // Fallback exception handler
  EXC_ATTR_ void default_handler() { 
    while (1); 
  }

  /**********************************************************************************************
   * @section Miscellaneous Definitions
   **********************************************************************************************/

  /** @brief Offset between the IRQ number and EXC number of an exception. */
  static const int32_t IRQN_OFFSET = -16;

  /** @brief Number of implemented IRQs. */
  static const int32_t IRQ_COUNT = 150;

  /** @brief Number of implemented exceptions. */
  static const int32_t EXC_COUNT = 166;

  /** @brief Maximum priority level for an exception. */
  static const int32_t MAX_EXC_PRIORITY = 256;

  /** @brief Length of the vtable. */
  static const int32_t VTABLE_LENGTH = 256;

  /**********************************************************************************************
   * @section Exception Number Definitions
   **********************************************************************************************/

  /**** @subsection Core Exceptions ****/

  static const int32_t RESET_EXC_NUM       = 1;     /** @brief MCU reset. */
  static const int32_t NMI_EXC_NUM         = 2;     /** @brief Non-maskable interrupt. */
  static const int32_t HARD_FAULT_EXC_NUM  = 3;     /** @brief Hard fault. */
  static const int32_t MEM_MANAGE_EXC_NUM  = 4;     /** @brief Memory management fault (MPU). */
  static const int32_t BUS_FAULT_EXC_NUM   = 5;     /** @brief Bus fault. */
  static const int32_t USAGE_FAULT_EXC_NUM = 6;     /** @brief Usage fault. */
  static const int32_t SVC_EXC_NUM         = 11;    /** @brief System service call exception. */
  static const int32_t DEBUG_MON_EXC_NUM   = 12;    /** @brief Debug monitor fault/exception. */
  static const int32_t PENDSV_EXC_NUM      = 14;    /** @brief Pended system service call exception. */
  static const int32_t SYSTICK_EXC_NUM     = 15;    /** @brief SysTick interrupt. */

  /**** @subsection IRQ Exceptions ****/

  static const int32_t PVD_PVM_EXC_NUM                = 17;    /** @brief PVD through EXTI line. */
  static const int32_t RTC_TAMP_STAMP_CSS_LSE_EXC_NUM = 18;    /** @brief RTC tamper, timestamp. */
  static const int32_t RTC_WKUP_EXC_NUM               = 19;    /** @brief RTC wakeup interrupt. */
  static const int32_t FLASH_EXC_NUM                  = 20;    /** @brief Flash memory. */
  static const int32_t RCC_EXC_NUM                    = 21;    /** @brief RCC global interrupt. */
  static const int32_t ADC1_2_EXC_NUM                 = 34;    /** @brief ADC1 and ADC2. */
  static const int32_t EXTI9_5_EXC_NUM                = 39;    /** @brief EXTI line[9:5] interrupts. */
  static const int32_t TIM1_BRK_EXC_NUM               = 40;    /** @brief TIM1 break interrupt. */
  static const int32_t TIM1_UP_EXC_NUM                = 41;    /** @brief TIM1 update interrupt. */
  static const int32_t TIM1_TRG_COM_EXC_NUM           = 42;    /** @brief TIM1 trigger and commutation. */
  static const int32_t EXTI15_10_EXC_NUM              = 56;    /** @brief EXTI line[15:10] interrupts. */
  static const int32_t RTC_ALARM_EXC_NUM              = 57;    /** @brief RTC alarms (A and B). */
  static const int32_t TIM8_BRK_TIM12_EXC_NUM         = 59;    /** @brief TIM8 and 12 break global. */
  static const int32_t TIM8_UP_TIM13_EXC_NUM          = 60;    /** @brief TIM8 and 13 update global. */
  static const int32_t TIM8_TRG_COM_TIM14_EXC_NUM     = 61;    /** @brief TIM8 and 14 trigger /commutation and global. */
  static const int32_t FMC_EXC_NUM                    = 64;    /** @brief FMC global interrupt. */
  static const int32_t TIM6_DAC_EXC_NUM               = 70;    /** @brief TIM6 global interrupt. */
  static const int32_t ETH_EXC_NUM                    = 77;    /** @brief Ethernet global interrupt. */
  static const int32_t ETH_WKUP_EXC_NUM               = 78;    /** @brief Ethernet wakeup through EXTI. */
  static const int32_t FDCAN_CAL_EXC_NUM              = 79;    /** @brief CAN2TX interrupts. */
  static const int32_t OTG_HS_EP1_OUT_EXC_NUM         = 90;    /** @brief OTG_HS out global interrupt. */
  static const int32_t OTG_HS_EP1_IN_EXC_NUM          = 91;    /** @brief OTG_HS in global interrupt. */
  static const int32_t OTG_HS_WKUP_EXC_NUM            = 92;    /** @brief OTG_HS wakeup interrupt. */
  static const int32_t OTG_HS_EXC_NUM                 = 93;    /** @brief OTG_HS global interrupt. */
  static const int32_t DCMI_EXC_NUM                   = 94;    /** @brief DCMI global interrupt. */
  static const int32_t CRYP_EXC_NUM                   = 95;    /** @brief CRYP global interrupt. */
  static const int32_t HASH_RNG_EXC_NUM               = 96;    /** @brief HASH and RNG. */
  static const int32_t FPU_EXC_NUM                    = 97;    /** @brief CM7/CM4 Floating point unit interrupt. */
  static const int32_t LTDC_EXC_NUM                   = 104;   /** @brief LCD-TFT global interrupt. */
  static const int32_t LTDC_ER_EXC_NUM                = 105;   /** @brief LCD-TFT error interrupt. */
  static const int32_t DMA2D_EXC_NUM                  = 106;   /** @brief DMA2D global interrupt. */
  static const int32_t QUADSPI_EXC_NUM                = 108;   /** @brief QuadSPI global interrupt. */
  static const int32_t CEC_EXC_NUM                    = 110;   /** @brief HDMI-CEC global interrupt. */
  static const int32_t SPDIF_EXC_NUM                  = 113;   /** @brief SPDIFRX global interrupt. */
  static const int32_t OTG_FS_EP1_OUT_EXC_NUM         = 114;   /** @brief OTG_FS out global interrupt. */
  static const int32_t OTG_FS_EP1_IN_EXC_NUM          = 115;   /** @brief OTG_FS in global interrupt. */
  static const int32_t OTG_FS_WKUP_EXC_NUM            = 116;   /** @brief OTG_FS wakeup. */
  static const int32_t OTG_FS_EXC_NUM                 = 117;   /** @brief OTG_FS global interrupt. */
  static const int32_t DMAMUX1_OV_EXC_NUM             = 118;   /** @brief DMAMUX1 overrun interrupt. */
  static const int32_t HRTIM_MST_EXC_NUM              = 119;   /** @brief HRTIM master timer interrupt. */
  static const int32_t HRTIM_FLT_EXC_NUM              = 125;   /** @brief HRTIM fault interrupt. */
  static const int32_t SWPMI_EXC_NUM                  = 131;   /** @brief SWPMI global interrupt. */
  static const int32_t MDIOS_WKUP_EXC_NUM             = 135;   /** @brief MDIOS wakeup. */
  static const int32_t MDIOS_EXC_NUM                  = 136;   /** @brief MDIOS global interrupt. */
  static const int32_t JPEG_EXC_NUM                   = 137;   /** @brief JPEG global interrupt. */
  static const int32_t MDMA_EXC_NUM                   = 138;   /** @brief MDMA. */
  static const int32_t ADC3_EXC_NUM                   = 143;   /** @brief ADC3 global interrupt. */
  static const int32_t DMAMUX2_OVR_EXC_NUM            = 144;   /** @brief DMAMUX2 overrun interrupt. */
  static const int32_t COMP_EXC_NUM                   = 153;   /** @brief COMP1 and COMP2. */
  static const int32_t LPUART_EXC_NUM                 = 158;   /** @brief LPUART global interrupt. */
  static const int32_t CRS_EXC_NUM                    = 160;   /** @brief Clock recovery system globa. */
  static const int32_t HOLD_CORE_EXC_NUM              = 164;   /** @brief CM7/CM4 hold core interrupt. */
  static const int32_t WKUP_EXC_NUM                   = 165;   /** @brief WKUP1 to WKUP6 pins. */

  /**** @subsection Enumerated IRQ Exceptions ****/

  static const DMAx_STRx_EXC_NUM[3][8] = {
    [1] = {
      [0] = 27,    /** @brief DMA1 stream0 interrupt. */
      [1] = 28,    /** @brief DMA1 stream1 interrupt. */
      [2] = 29,    /** @brief DMA1 stream2 interrupt. */
      [3] = 30,    /** @brief DMA1 stream3 interrupt. */
      [4] = 31,    /** @brief DMA1 stream4 interrupt. */
      [5] = 32,    /** @brief DMA1 stream5 interrupt. */
      [6] = 33,    /** @brief DMA1 stream6 interrupt. */
      [7] = 63,    /** @brief DMA1 stream7 interrupt. */
    },
    [2] = {
      [0] = 72,    /** @brief DMA2 stream0 interrupt. */
      [1] = 73,    /** @brief DMA2 stream1 interrupt. */
      [2] = 74,    /** @brief DMA2 stream2 interrupt. */
      [3] = 75,    /** @brief DMA2 stream3 interrupt. */
      [4] = 76,    /** @brief DMA2 stream4 interrupt. */
      [5] = 84,    /** @brief DMA2 stream5 interrupt. */
      [6] = 85,    /** @brief DMA2 stream6 interrupt. */
      [7] = 86,    /** @brief DMA2 stream7 interrupt. */
    },
  };

  static const int32_t FDCANx_ITx_EXC_NUM[3][2] = {
    [1] = {
      [0] = 35,   /** @brief FDCAN1 interrupt 0. */
      [1] = 37,   /** @brief FDCAN1 interrupt 1. */
    },
    [2] = {
      [0] = 36,   /** @brief FDCAN2 interrupt 0. */
      [1] = 38,   /** @brief FDCAN2 interrupt 1. */
    },
  };

  static const int32_t CPUx_SEV_IT_EXC_NUM[3] = {
    [1] = 80,   /** @brief Arm cortex-m7 send even interrupt. */
    [2] = 81,   /** @brief Arm cortex-m4 send even interrupt. */
  };

  static const int32_t WWDGx_RST_EXC_NUM[3] = {
    [1] = 16,   /** @brief Window watchdog interrupt. */
    [2] = 16,   /** @brief CPU1/CPU2 Window watchdog interrupt. */
  };

  static const int32_t WWDGx_EXC_NUM[3] = {
    [1] = 159,   /** @brief CPU1 Window watchdog interrupt. */
    [2] = 159,   /** @brief CPU2 Window watchdog interrupt. */
  };

  static const int32_t HSEMx_EXC_NUM[2] = {
    [0] = 141,   /** @brief HSEM global interrupt 0. */
    [1] = 142,   /** @brief HSEM global interrupt 1. */
  };

  static const int32_t HRTIM_TIMx_EXC_NUM[6] = {
    [1] = 120,   /** @brief HRTIM timer A interrupt. */
    [2] = 121,   /** @brief HRTIM timer B interrupt. */
    [3] = 122,   /** @brief HRTIM timer C interrupt. */
    [4] = 123,   /** @brief HRTIM timer D interrupt. */
    [5] = 124,   /** @brief HRTIM timer E interrupt. */
  };

  static const int32_t BDMA_CHx_EXC_NUM[9] = {
    [1] = 145,    /** @brief BDMA channel 1 interrupt. */
    [2] = 146,    /** @brief BDMA channel 2 interrupt. */
    [3] = 147,    /** @brief BDMA channel 3 interrupt. */
    [4] = 148,    /** @brief BDMA channel 4 interrupt. */
    [5] = 149,    /** @brief BDMA channel 5 interrupt. */
    [6] = 150,    /** @brief BDMA channel 6 interrupt. */
    [7] = 151,    /** @brief BDMA channel 7 interrupt. */
    [8] = 152,    /** @brief BDMA channel 8 interrupt. */
  };

  static const int32_t I2Cx_EV_EXC_NUM[5] = {
    [1] = 47,     /** @brief I2C1 event interrupt. */
    [2] = 49,     /** @brief I2C2 event interrupt. */
    [3] = 88,     /** @brief I2C3 event interrupt. */
    [4] = 111,    /** @brief I2C4 event interrupt. */
  };

  static const int32_t I2Cx_ER_EXC_NUM[5] = {
    [1] = 48,     /** @brief I2C1 error interrupt. */
    [2] = 50,     /** @brief I2C2 error interrupt. */
    [3] = 89,     /** @brief I2C3 error interrupt. */
    [4] = 112,    /** @brief I2C4 error interrupt. */
  };

  static const int32_t SAIx_EXC_NUM[5] = {
    [1] = 103,    /** @brief SAI1 global interrupt. */
    [2] = 107,    /** @brief SAI2 global interrupt. */
    [3] = 130,    /** @brief SAI3 global interrupt. */
    [4] = 162,    /** @brief SAI4 global interrupt. */
  };

  static const int32_t SDMMCx_EXC_NUM[3] = {
    [1] = 65,     /** @brief SDMMC1 global interrupt. */
    [2] = 140,    /** @brief SDMMC2 global interrupt. */
  };

  static const int32_t SPIx_EXC_NUM[7] = {
    [1] = 51,     /** @brief SPI1 global interrupt. */
    [2] = 52,     /** @brief SPI2 global interrupt. */
    [3] = 67,     /** @brief SPI3 global interrupt. */
    [4] = 100,    /** @brief SPI4 global interrupt. */
    [5] = 101,    /** @brief SPI5 global interrupt. */
    [6] = 102,    /** @brief SPI6 global interrupt. */
  };

  static const int32_t LPTIMx_EXC_NUM[6] = {
    [1] = 109,    /** @brief LPTIM1 global interrupt. */
    [2] = 154,    /** @brief LPTIM2 timer interrupt. */
    [3] = 155,    /** @brief LPTIM3 timer interrupt. */
    [4] = 156,    /** @brief LPTIM4 timer interrupt. */
    [5] = 157,    /** @brief LPTIM5 timer interrupt. */
  };

  static const int32_t EXTIx_EXC_NUM[5] = {
    [0] = 22,    /** @brief EXTI line 0 interrupt. */
    [1] = 23,    /** @brief EXTI line 1 interrupt. */
    [2] = 24,    /** @brief EXTI line 2 interrupt. */
    [3] = 25,    /** @brief EXTI line 3interrupt. */
    [4] = 26,    /** @brief EXTI line 4interrupt. */
  };

  static const int32_t DFSDM1_FLTx_EXC_NUM[4] = {
    [0] = 126,    /** @brief DFSDM1 filter 0 interrupt. */
    [1] = 127,    /** @brief DFSDM1 filter 1 interrupt. */
    [2] = 128,    /** @brief DFSDM1 filter 2 interrupt. */
    [3] = 129,    /** @brief DFSDM1 filter 3 interrupt. */
  };

  static const int32_t TIMx_EXC_NUM[18] = {
    [2]  = 44,     /** @brief TIM2 global interrupt. */
    [3]  = 45,     /** @brief TIM3 global interrupt. */
    [4]  = 46,     /** @brief TIM4 global interrupt. */
    [5]  = 66,     /** @brief TIM5 global interrupt. */
    [7]  = 71,     /** @brief TIM7 global interrupt. */
    [15] = 132,    /** @brief TIM15 global interrupt. */
    [16] = 133,    /** @brief TIM16 global interrupt. */
    [17] = 134,    /** @brief TIM17 global interrupt. */
  };

  static const int32_t USARTx_EXC_NUM[7] = {
    [1] = 53,    /** @brief USART1 global interrupt. */
    [2] = 54,    /** @brief USART2 global interrupt. */
    [3] = 55,    /** @brief USART3 global interrupt. */
    [6] = 87,    /** @brief USART6 global interrupt. */
  };

  static const int32_t UARTx_EXC_NUM[9] = {
    [4] = 68,    /** @brief UART4 global interrupt. */
    [5] = 69,    /** @brief UART5 global interrupt. */
    [7] = 98,    /** @brief UART7 global interrupt. */
    [8] = 99,    /** @brief UART8 global interrupt. */
  };

  static const int32_t TIMx_CC_EXC_NUM[9] = {
    [1] = 43,    /** @brief TIM1 capture / compare. */
    [8] = 62,    /** @brief TIM8 capture / compare. */
  };


  /*************************************************************************************************
   * @section Exception Handler Definitions 
   *************************************************************************************************/

  /**** @subsection CM7 Core Exceptions ****/

  EXC_ATTR_ void cm7_reset_exc_handler();         /** @brief CM7 MCU reset. */
  EXC_ATTR_ void cm7_nmi_exc_handler();           /** @brief CM7 Non-maskable interrupt. */
  EXC_ATTR_ void cm7_hard_fault_exc_handler();    /** @brief CM7 Hard fault. */
  EXC_ATTR_ void cm7_mem_manage_exc_handler();    /** @brief CM7 Memory management fault (MPU). */
  EXC_ATTR_ void cm7_bus_fault_exc_handler();     /** @brief CM7 Bus fault. */
  EXC_ATTR_ void cm7_usage_fault_exc_handler();   /** @brief CM7 Usage fault. */
  EXC_ATTR_ void cm7_svc_exc_handler();           /** @brief CM7 System service call exception. */
  EXC_ATTR_ void cm7_debug_mon_exc_handler();     /** @brief CM7 Debug monitor fault/exception. */
  EXC_ATTR_ void cm7_pendsv_exc_handler();        /** @brief CM7 Pended system service call exception. */
  EXC_ATTR_ void cm7_systick_exc_handler();       /** @brief CM7 SysTick interrupt. */

  /**** @subsection CM4 Core Exceptions ****/

  EXC_ATTR_ void cm4_reset_exc_handler();         /** @brief CM4 MCU reset. */
  EXC_ATTR_ void cm4_nmi_exc_handler();           /** @brief CM4 Non-maskable interrupt. */
  EXC_ATTR_ void cm4_hard_fault_exc_handler();    /** @brief CM4 Hard fault. */
  EXC_ATTR_ void cm4_mem_manage_exc_handler();    /** @brief CM4 Memory management fault (MPU). */
  EXC_ATTR_ void cm4_bus_fault_exc_handler();     /** @brief CM4 Bus fault. */
  EXC_ATTR_ void cm4_usage_fault_exc_handler();   /** @brief CM4 Usage fault. */
  EXC_ATTR_ void cm4_svc_exc_handler();           /** @brief CM4 System service call exception. */
  EXC_ATTR_ void cm4_debug_mon_exc_handler();     /** @brief CM4 Debug monitor fault/exception. */
  EXC_ATTR_ void cm4_pendsv_exc_handler();        /** @brief CM4 Pended system service call exception. */
  EXC_ATTR_ void cm4_systick_exc_handler();       /** @brief CM4 SysTick interrupt. */

  /**** @subsection IRQ Exceptions ****/

  EXC_ATTR_ void wwdg1_exc_handler();                    /** @brief CM7 Window watchdog interrupt. */
  EXC_ATTR_ void wwdg2_exc_handler();                    /** @brief CM4 Window watchdog interrupt. */
  EXC_ATTR_ void pvd_pvm_exc_handler();                  /** @brief PVD through EXTI line. */
  EXC_ATTR_ void rtc_tamp_stamp_css_lse_exc_handler();   /** @brief RTC tamper, timestamp. */
  EXC_ATTR_ void rtc_wkup_exc_handler();                 /** @brief RTC wakeup interrupt. */
  EXC_ATTR_ void flash_exc_handler();                    /** @brief Flash memory. */
  EXC_ATTR_ void rcc_exc_handler();                      /** @brief RCC global interrupt. */
  EXC_ATTR_ void exti0_exc_handler();                    /** @brief EXTI line 0 interrupt. */
  EXC_ATTR_ void exti1_exc_handler();                    /** @brief EXTI line 1 interrupt. */
  EXC_ATTR_ void exti2_exc_handler();                    /** @brief EXTI line 2 interrupt. */
  EXC_ATTR_ void exti3_exc_handler();                    /** @brief EXTI line 3 interrupt. */
  EXC_ATTR_ void exti4_exc_handler();                    /** @brief EXTI line 4 interrupt. */
  EXC_ATTR_ void dma_str0_exc_handler();                 /** @brief DMA1 stream0. */
  EXC_ATTR_ void dma_str1_exc_handler();                 /** @brief DMA1 stream1. */
  EXC_ATTR_ void dma_str2_exc_handler();                 /** @brief DMA1 stream2. */
  EXC_ATTR_ void dma_str3_exc_handler();                 /** @brief DMA1 stream3. */
  EXC_ATTR_ void dma_str4_exc_handler();                 /** @brief DMA1 stream4. */
  EXC_ATTR_ void dma_str5_exc_handler();                 /** @brief DMA1 stream5. */
  EXC_ATTR_ void dma_str6_exc_handler();                 /** @brief DMA1 stream6. */
  EXC_ATTR_ void adc1_2_exc_handler();                   /** @brief ADC1 and ADC2. */
  EXC_ATTR_ void fdcan1_it0_exc_handler();               /** @brief FDCAN1 interrupt 0. */
  EXC_ATTR_ void fdcan2_it0_exc_handler();               /** @brief FDCAN2 interrupt 0. */
  EXC_ATTR_ void fdcan1_it1_exc_handler();               /** @brief FDCAN1 interrupt 1. */
  EXC_ATTR_ void fdcan2_it1_exc_handler();               /** @brief FDCAN2 interrupt 1. */
  EXC_ATTR_ void exti9_5_exc_handler();                  /** @brief EXTI line[9:5] interrupts. */
  EXC_ATTR_ void tim1_brk_exc_handler();                 /** @brief TIM1 break interrupt. */
  EXC_ATTR_ void tim1_up_exc_handler();                  /** @brief TIM1 update interrupt. */
  EXC_ATTR_ void tim1_trg_com_exc_handler();             /** @brief TIM1 trigger and commutation. */
  EXC_ATTR_ void tim1_cc_exc_handler();                  /** @brief TIM1 capture / compare. */
  EXC_ATTR_ void tim2_exc_handler();                     /** @brief TIM2 global interrupt. */
  EXC_ATTR_ void tim3_exc_handler();                     /** @brief TIM3 global interrupt. */
  EXC_ATTR_ void tim4_exc_handler();                     /** @brief TIM4 global interrupt. */
  EXC_ATTR_ void i2c1_ev_exc_handler();                  /** @brief I2C1 event interrupt. */
  EXC_ATTR_ void i2c1_er_exc_handler();                  /** @brief I2C1 error interrupt. */
  EXC_ATTR_ void i2c2_ev_exc_handler();                  /** @brief I2C2 event interrupt. */
  EXC_ATTR_ void i2c2_er_exc_handler();                  /** @brief I2C2 error interrupt. */
  EXC_ATTR_ void spi1_exc_handler();                     /** @brief SPI1 global interrupt. */
  EXC_ATTR_ void spi2_exc_handler();                     /** @brief SPI2 global interrupt. */
  EXC_ATTR_ void usart1_exc_handler();                   /** @brief USART1 global interrupt. */
  EXC_ATTR_ void usart2_exc_handler();                   /** @brief USART2 global interrupt. */
  EXC_ATTR_ void usart3_exc_handler();                   /** @brief USART3 global interrupt. */
  EXC_ATTR_ void exti15_10_exc_handler();                /** @brief EXTI line[15:10] interrupts. */
  EXC_ATTR_ void rtc_alarm_exc_handler();                /** @brief RTC alarms (A and B). */
  EXC_ATTR_ void tim8_brk_tim12_exc_handler();           /** @brief TIM8 and 12 break global. */
  EXC_ATTR_ void tim8_up_tim13_exc_handler();            /** @brief TIM8 and 13 update global. */
  EXC_ATTR_ void tim8_trg_com_tim14_exc_handler();       /** @brief TIM8 and 14 trigger /commutation and global. */
  EXC_ATTR_ void tim8_cc_exc_handler();                  /** @brief TIM8 capture / compare. */
  EXC_ATTR_ void dma1_str7_exc_handler();                /** @brief DMA1 stream7. */
  EXC_ATTR_ void fmc_exc_handler();                      /** @brief FMC global interrupt. */
  EXC_ATTR_ void sdmmc1_exc_handler();                   /** @brief SDMMC global interrupt. */
  EXC_ATTR_ void tim5_exc_handler();                     /** @brief TIM5 global interrupt. */
  EXC_ATTR_ void spi3_exc_handler();                     /** @brief SPI3 global interrupt. */
  EXC_ATTR_ void uart4_exc_handler();                    /** @brief UART4 global interrupt. */
  EXC_ATTR_ void uart5_exc_handler();                    /** @brief UART5 global interrupt. */
  EXC_ATTR_ void tim6_dac_exc_handler();                 /** @brief TIM6 global interrupt. */
  EXC_ATTR_ void tim7_exc_handler();                     /** @brief TIM7 global interrupt. */
  EXC_ATTR_ void dma2_str0_exc_handler();                /** @brief DMA2 stream0 interrupt. */
  EXC_ATTR_ void dma2_str1_exc_handler();                /** @brief DMA2 stream1 interrupt. */
  EXC_ATTR_ void dma2_str2_exc_handler();                /** @brief DMA2 stream2 interrupt. */
  EXC_ATTR_ void dma2_str3_exc_handler();                /** @brief DMA2 stream3 interrupt. */
  EXC_ATTR_ void dma2_str4_exc_handler();                /** @brief DMA2 stream4 interrupt. */
  EXC_ATTR_ void eth_exc_handler();                      /** @brief Ethernet global interrupt. */
  EXC_ATTR_ void eth_wkup_exc_handler();                 /** @brief Ethernet wakeup through EXTI. */
  EXC_ATTR_ void fdcan_cal_exc_handler();                /** @brief CAN2TX interrupts. */
  EXC_ATTR_ void sev_it1_exc_handler();                  /** @brief Arm cortex-m7 send even interrupt. */
  EXC_ATTR_ void sev_it2_exc_handler();                  /** @brief Arm cortex-m4 send even interrupt. */
  EXC_ATTR_ void dma2_str5_exc_handler();                /** @brief DMA2 stream5 interrupt. */
  EXC_ATTR_ void dma2_str6_exc_handler();                /** @brief DMA2 stream6 interrupt. */
  EXC_ATTR_ void dma2_str7_exc_handler();                /** @brief DMA2 stream7 interrupt. */
  EXC_ATTR_ void usart6_exc_handler();                   /** @brief USART6 global interrupt. */
  EXC_ATTR_ void i2c3_ev_exc_handler();                  /** @brief I2C3 event interrupt. */
  EXC_ATTR_ void i2c3_er_exc_handler();                  /** @brief I2C3 error interrupt. */
  EXC_ATTR_ void otg_hs_ep1_out_exc_handler();           /** @brief OTG_HS out global interrupt. */
  EXC_ATTR_ void otg_hs_ep1_in_exc_handler();            /** @brief OTG_HS in global interrupt. */
  EXC_ATTR_ void otg_hs_wkup_exc_handler();              /** @brief OTG_HS wakeup interrupt. */
  EXC_ATTR_ void otg_hs_exc_handler();                   /** @brief OTG_HS global interrupt. */
  EXC_ATTR_ void dcmi_exc_handler();                     /** @brief DCMI global interrupt. */
  EXC_ATTR_ void cryp_exc_handler();                     /** @brief CRYP global interrupt. */
  EXC_ATTR_ void hash_rng_exc_handler();                 /** @brief HASH and RNG. */
  EXC_ATTR_ void cm7_fpu_exc_handler();                  /** @brief CM7 Floating point unit interrupt. */
  EXC_ATTR_ void cm4_fpu_exc_handler();                  /** @brief CM4 Floating point unit interrupt. */
  EXC_ATTR_ void uart7_exc_handler();                    /** @brief UART7 global interrupt. */
  EXC_ATTR_ void uart8_exc_handler();                    /** @brief UART8 global interrupt. */
  EXC_ATTR_ void spi4_exc_handler();                     /** @brief SPI4 global interrupt. */
  EXC_ATTR_ void spi5_exc_handler();                     /** @brief SPI5 global interrupt. */
  EXC_ATTR_ void spi6_exc_handler();                     /** @brief SPI6 global interrupt. */
  EXC_ATTR_ void sai1_exc_handler();                     /** @brief SAI1 global interrupt. */
  EXC_ATTR_ void ltdc_exc_handler();                     /** @brief LCD-TFT global interrupt. */
  EXC_ATTR_ void ltdc_er_exc_handler();                  /** @brief LCD-TFT error interrupt. */
  EXC_ATTR_ void dma2d_exc_handler();                    /** @brief DMA2D global interrupt. */
  EXC_ATTR_ void sai2_exc_handler();                     /** @brief SAI2 global interrupt. */
  EXC_ATTR_ void quadspi_exc_handler();                  /** @brief QuadSPI global interrupt. */
  EXC_ATTR_ void lptim1_exc_handler();                   /** @brief LPTIM1 global interrupt. */
  EXC_ATTR_ void cec_exc_handler();                      /** @brief HDMI-CEC global interrupt. */
  EXC_ATTR_ void i2c4_ev_exc_handler();                  /** @brief I2C4 event interrupt. */
  EXC_ATTR_ void i2c4_er_exc_handler();                  /** @brief I2C4 error interrupt. */
  EXC_ATTR_ void spdif_exc_handler();                    /** @brief SPDIFRX global interrupt. */
  EXC_ATTR_ void otg_fs_ep1_out_exc_handler();           /** @brief OTG_FS out global interrupt. */
  EXC_ATTR_ void otg_fs_ep1_in_exc_handler();            /** @brief OTG_FS in global interrupt. */
  EXC_ATTR_ void otg_fs_wkup_exc_handler();              /** @brief OTG_FS wakeup. */
  EXC_ATTR_ void otg_fs_exc_handler();                   /** @brief OTG_FS global interrupt. */
  EXC_ATTR_ void dmamux1_ov_exc_handler();               /** @brief DMAMUX1 overrun interrupt. */
  EXC_ATTR_ void hrtim_mst_exc_handler();                /** @brief HRTIM master timer interrupt. */
  EXC_ATTR_ void hrtim_tima_exc_handler();               /** @brief HRTIM timer A interrupt. */
  EXC_ATTR_ void hrtim_timb_exc_handler();               /** @brief HRTIM timer B interrupt. */
  EXC_ATTR_ void hrtim_timc_exc_handler();               /** @brief HRTIM timer C interrupt. */
  EXC_ATTR_ void hrtim_timd_exc_handler();               /** @brief HRTIM timer D interrupt. */
  EXC_ATTR_ void hrtim_time_exc_handler();               /** @brief HRTIM timer E interrupt. */
  EXC_ATTR_ void hrtim_flt_exc_handler();                /** @brief HRTIM fault interrupt. */
  EXC_ATTR_ void dfsdm1_flt0_exc_handler();              /** @brief DFSDM1 filter 0 interrupt. */
  EXC_ATTR_ void dfsdm1_flt1_exc_handler();              /** @brief DFSDM1 filter 1 interrupt. */
  EXC_ATTR_ void dfsdm1_flt2_exc_handler();              /** @brief DFSDM1 filter 2 interrupt. */
  EXC_ATTR_ void dfsdm1_flt3_exc_handler();              /** @brief DFSDM1 filter 3 interrupt. */
  EXC_ATTR_ void sai3_exc_handler();                     /** @brief SAI3 global interrupt. */
  EXC_ATTR_ void swpmi_exc_handler();                    /** @brief SWPMI global interrupt. */
  EXC_ATTR_ void tim15_exc_handler();                    /** @brief TIM15 global interrupt. */
  EXC_ATTR_ void tim16_exc_handler();                    /** @brief TIM16 global interrupt. */
  EXC_ATTR_ void tim17_exc_handler();                    /** @brief TIM17 global interrupt. */
  EXC_ATTR_ void mdios_wkup_exc_handler();               /** @brief MDIOS wakeup. */
  EXC_ATTR_ void mdios_exc_handler();                    /** @brief MDIOS global interrupt. */
  EXC_ATTR_ void jpeg_exc_handler();                     /** @brief JPEG global interrupt. */
  EXC_ATTR_ void mdma_exc_handler();                     /** @brief MDMA. */
  EXC_ATTR_ void sdmmc2_exc_handler();                   /** @brief SDMMC global interrupt. */
  EXC_ATTR_ void hsem0_exc_handler();                    /** @brief CM7 HSEM global interrupt 0. */
  EXC_ATTR_ void hsem1_exc_handler();                    /** @brief CM4 HSEM global interrupt 1. */
  EXC_ATTR_ void adc3_exc_handler();                     /** @brief ADC3 global interrupt. */
  EXC_ATTR_ void dmamux2_ovr_exc_handler();              /** @brief DMAMUX2 overrun interrupt. */
  EXC_ATTR_ void bdma_ch1_exc_handler();                 /** @brief BDMA channel 1 interrupt. */
  EXC_ATTR_ void bdma_ch2_exc_handler();                 /** @brief BDMA channel 2 interrupt. */
  EXC_ATTR_ void bdma_ch3_exc_handler();                 /** @brief BDMA channel 3 interrupt. */
  EXC_ATTR_ void bdma_ch4_exc_handler();                 /** @brief BDMA channel 4 interrupt. */
  EXC_ATTR_ void bdma_ch5_exc_handler();                 /** @brief BDMA channel 5 interrupt. */
  EXC_ATTR_ void bdma_ch6_exc_handler();                 /** @brief BDMA channel 6 interrupt. */
  EXC_ATTR_ void bdma_ch7_exc_handler();                 /** @brief BDMA channel 7 interrupt. */
  EXC_ATTR_ void bdma_ch8_exc_handler();                 /** @brief BDMA channel 8 interrupt. */
  EXC_ATTR_ void comp_exc_handler();                     /** @brief COMP1 and COMP2. */
  EXC_ATTR_ void lptim2_exc_handler();                   /** @brief LPTIM2 timer interrupt. */
  EXC_ATTR_ void lptim3_exc_handler();                   /** @brief LPTIM3 timer interrupt. */
  EXC_ATTR_ void lptim4_exc_handler();                   /** @brief LPTIM4 timer interrupt. */
  EXC_ATTR_ void lptim5_exc_handler();                   /** @brief LPTIM5 timer interrupt. */
  EXC_ATTR_ void lpuart_exc_handler();                   /** @brief LPUART global interrupt. */
  EXC_ATTR_ void wwdg1_rst_exc_handler();                /** @brief CM7 Window watchdog interrupt. */
  EXC_ATTR_ void wwdg2_rst_exc_handler();                /** @brief CM4 Window watchdog interrupt. */
  EXC_ATTR_ void crs_exc_handler();                      /** @brief Clock recovery system globa. */
  EXC_ATTR_ void sai4_exc_handler();                     /** @brief SAI4 global interrupt. */
  EXC_ATTR_ void cm7_hold_core_exc_handler();            /** @brief CM7 hold core interrupt. */
  EXC_ATTR_ void cm4_hold_core_exc_handler();            /** @brief CM4 hold core interrupt. */
  EXC_ATTR_ void wkup_exc_handler();                     /** @brief WKUP1 to WKUP6 pins. */

  /**********************************************************************************************
   * @section Vtable Definition
   **********************************************************************************************/

  /**** @subsection Vtable Definition for CM7 Core ****/

  __attribute__((section(".cm7_vtable")))
  static const uint32_t cm7_vtable[VTABLE_LENGTH] = {
    [0]   = CM7_STACK_END__,                                 /** @brief Addres of top of CM7 stack */
    [1]   = (uint32_t)&cm7_reset_exc_handler,                /** @brief MCU reset exception. */
    [2]   = (uint32_t)&cm7_nmi_exc_handler,                  /** @brief Non-maskable interrupt. */
    [3]   = (uint32_t)&cm7_hard_fault_exc_handler,           /** @brief Hard fault exception. */
    [4]   = (uint32_t)&cm7_mem_manage_exc_handler,           /** @brief Memory management fault (MPU). */
    [5]   = (uint32_t)&cm7_bus_fault_exc_handler,            /** @brief Bus fault exception. */
    [6]   = (uint32_t)&cm7_usage_fault_exc_handler,          /** @brief Usage fault exception. */
    [11]  = (uint32_t)&cm7_svc_exc_handler,                  /** @brief System service call exception. */
    [12]  = (uint32_t)&cm7_debug_mon_exc_handler,            /** @brief Debug monitor fault/exception. */
    [14]  = (uint32_t)&cm7_pendsv_exc_handler,               /** @brief Pended system service call exception. */
    [15]  = (uint32_t)&cm7_systick_exc_handler,              /** @brief SysTick interrupt. */
    [16]  = (uint32_t)&wwdg1_exc_handler,                    /** @brief CM7 Window watchdog interrupt. */
    [17]  = (uint32_t)&pvd_pvm_exc_handler,                  /** @brief PVD through EXTI line. */
    [18]  = (uint32_t)&rtc_tamp_stamp_css_lse_exc_handler,   /** @brief RTC tamper, timestamp. */
    [19]  = (uint32_t)&rtc_wkup_exc_handler,                 /** @brief RTC wakeup interrupt. */
    [20]  = (uint32_t)&flash_exc_handler,                    /** @brief Flash memory. */
    [21]  = (uint32_t)&rcc_exc_handler,                      /** @brief RCC global interrupt. */
    [22]  = (uint32_t)&exti0_exc_handler,                    /** @brief EXTI line 0 interrupt. */
    [23]  = (uint32_t)&exti1_exc_handler,                    /** @brief EXTI line 1 interrupt. */
    [24]  = (uint32_t)&exti2_exc_handler,                    /** @brief EXTI line 2 interrupt. */
    [25]  = (uint32_t)&exti3_exc_handler,                    /** @brief EXTI line 3interrupt. */
    [26]  = (uint32_t)&exti4_exc_handler,                    /** @brief EXTI line 4interrupt. */
    [27]  = (uint32_t)&dma_str0_exc_handler,                 /** @brief DMA1 stream0. */
    [28]  = (uint32_t)&dma_str1_exc_handler,                 /** @brief DMA1 stream1. */
    [29]  = (uint32_t)&dma_str2_exc_handler,                 /** @brief DMA1 stream2. */
    [30]  = (uint32_t)&dma_str3_exc_handler,                 /** @brief DMA1 stream3. */
    [31]  = (uint32_t)&dma_str4_exc_handler,                 /** @brief DMA1 stream4. */
    [32]  = (uint32_t)&dma_str5_exc_handler,                 /** @brief DMA1 stream5. */
    [33]  = (uint32_t)&dma_str6_exc_handler,                 /** @brief DMA1 stream6. */
    [34]  = (uint32_t)&adc1_2_exc_handler,                   /** @brief ADC1 and ADC2. */
    [35]  = (uint32_t)&fdcan1_it0_exc_handler,               /** @brief FDCAN1 interrupt 0. */
    [36]  = (uint32_t)&fdcan2_it0_exc_handler,               /** @brief FDCAN2 interrupt 0. */
    [37]  = (uint32_t)&fdcan1_it1_exc_handler,               /** @brief FDCAN1 interrupt 1. */
    [38]  = (uint32_t)&fdcan2_it1_exc_handler,               /** @brief FDCAN2 interrupt 1. */
    [39]  = (uint32_t)&exti9_5_exc_handler,                  /** @brief EXTI line[9:5] interrupts. */
    [40]  = (uint32_t)&tim1_brk_exc_handler,                 /** @brief TIM1 break interrupt. */
    [41]  = (uint32_t)&tim1_up_exc_handler,                  /** @brief TIM1 update interrupt. */
    [42]  = (uint32_t)&tim1_trg_com_exc_handler,             /** @brief TIM1 trigger and commutation. */
    [43]  = (uint32_t)&tim1_cc_exc_handler,                  /** @brief TIM1 capture / compare. */
    [44]  = (uint32_t)&tim2_exc_handler,                     /** @brief TIM2 global interrupt. */
    [45]  = (uint32_t)&tim3_exc_handler,                     /** @brief TIM3 global interrupt. */
    [46]  = (uint32_t)&tim4_exc_handler,                     /** @brief TIM4 global interrupt. */
    [47]  = (uint32_t)&i2c1_ev_exc_handler,                  /** @brief I2C1 event interrupt. */
    [48]  = (uint32_t)&i2c1_er_exc_handler,                  /** @brief I2C1 error interrupt. */
    [49]  = (uint32_t)&i2c2_ev_exc_handler,                  /** @brief I2C2 event interrupt. */
    [50]  = (uint32_t)&i2c2_er_exc_handler,                  /** @brief I2C2 error interrupt. */
    [51]  = (uint32_t)&spi1_exc_handler,                     /** @brief SPI1 global interrupt. */
    [52]  = (uint32_t)&spi2_exc_handler,                     /** @brief SPI2 global interrupt. */
    [53]  = (uint32_t)&usart1_exc_handler,                   /** @brief USART1 global interrupt. */
    [54]  = (uint32_t)&usart2_exc_handler,                   /** @brief USART2 global interrupt. */
    [55]  = (uint32_t)&usart3_exc_handler,                   /** @brief USART3 global interrupt. */
    [56]  = (uint32_t)&exti15_10_exc_handler,                /** @brief EXTI line[15:10] interrupts. */
    [57]  = (uint32_t)&rtc_alarm_exc_handler,                /** @brief RTC alarms (A and B). */
    [59]  = (uint32_t)&tim8_brk_tim12_exc_handler,           /** @brief TIM8 and 12 break global. */
    [60]  = (uint32_t)&tim8_up_tim13_exc_handler,            /** @brief TIM8 and 13 update global. */
    [61]  = (uint32_t)&tim8_trg_com_tim14_exc_handler,       /** @brief TIM8 and 14 trigger /commutation and global. */
    [62]  = (uint32_t)&tim8_cc_exc_handler,                  /** @brief TIM8 capture / compare. */
    [63]  = (uint32_t)&dma1_str7_exc_handler,                /** @brief DMA1 stream7. */
    [64]  = (uint32_t)&fmc_exc_handler,                      /** @brief FMC global interrupt. */
    [65]  = (uint32_t)&sdmmc1_exc_handler,                   /** @brief SDMMC global interrupt. */
    [66]  = (uint32_t)&tim5_exc_handler,                     /** @brief TIM5 global interrupt. */
    [67]  = (uint32_t)&spi3_exc_handler,                     /** @brief SPI3 global interrupt. */
    [68]  = (uint32_t)&uart4_exc_handler,                    /** @brief UART4 global interrupt. */
    [69]  = (uint32_t)&uart5_exc_handler,                    /** @brief UART5 global interrupt. */
    [70]  = (uint32_t)&tim6_dac_exc_handler,                 /** @brief TIM6 global interrupt. */
    [71]  = (uint32_t)&tim7_exc_handler,                     /** @brief TIM7 global interrupt. */
    [72]  = (uint32_t)&dma2_str0_exc_handler,                /** @brief DMA2 stream0 interrupt. */
    [73]  = (uint32_t)&dma2_str1_exc_handler,                /** @brief DMA2 stream1 interrupt. */
    [74]  = (uint32_t)&dma2_str2_exc_handler,                /** @brief DMA2 stream2 interrupt. */
    [75]  = (uint32_t)&dma2_str3_exc_handler,                /** @brief DMA2 stream3 interrupt. */
    [76]  = (uint32_t)&dma2_str4_exc_handler,                /** @brief DMA2 stream4 interrupt. */
    [77]  = (uint32_t)&eth_exc_handler,                      /** @brief Ethernet global interrupt. */
    [78]  = (uint32_t)&eth_wkup_exc_handler,                 /** @brief Ethernet wakeup through EXTI. */
    [79]  = (uint32_t)&fdcan_cal_exc_handler,                /** @brief CAN2TX interrupts. */
    [81]  = (uint32_t)&sev_it2_exc_handler,                  /** @brief Arm cortex-m4 send even interrupt. */
    [84]  = (uint32_t)&dma2_str5_exc_handler,                /** @brief DMA2 stream5 interrupt. */
    [85]  = (uint32_t)&dma2_str6_exc_handler,                /** @brief DMA2 stream6 interrupt. */
    [86]  = (uint32_t)&dma2_str7_exc_handler,                /** @brief DMA2 stream7 interrupt. */
    [87]  = (uint32_t)&usart6_exc_handler,                   /** @brief USART6 global interrupt. */
    [88]  = (uint32_t)&i2c3_ev_exc_handler,                  /** @brief I2C3 event interrupt. */
    [89]  = (uint32_t)&i2c3_er_exc_handler,                  /** @brief I2C3 error interrupt. */
    [90]  = (uint32_t)&otg_hs_ep1_out_exc_handler,           /** @brief OTG_HS out global interrupt. */
    [91]  = (uint32_t)&otg_hs_ep1_in_exc_handler,            /** @brief OTG_HS in global interrupt. */
    [92]  = (uint32_t)&otg_hs_wkup_exc_handler,              /** @brief OTG_HS wakeup interrupt. */
    [93]  = (uint32_t)&otg_hs_exc_handler,                   /** @brief OTG_HS global interrupt. */
    [94]  = (uint32_t)&dcmi_exc_handler,                     /** @brief DCMI global interrupt. */
    [95]  = (uint32_t)&cryp_exc_handler,                     /** @brief CRYP global interrupt. */
    [96]  = (uint32_t)&hash_rng_exc_handler,                 /** @brief HASH and RNG. */
    [97]  = (uint32_t)&cm7_fpu_exc_handler,                  /** @brief CPU1/CPU2 Floating point unit interrupt. */
    [98]  = (uint32_t)&uart7_exc_handler,                    /** @brief UART7 global interrupt. */
    [99]  = (uint32_t)&uart8_exc_handler,                    /** @brief UART8 global interrupt. */
    [100] = (uint32_t)&spi4_exc_handler,                     /** @brief SPI4 global interrupt. */
    [101] = (uint32_t)&spi5_exc_handler,                     /** @brief SPI5 global interrupt. */
    [102] = (uint32_t)&spi6_exc_handler,                     /** @brief SPI6 global interrupt. */
    [103] = (uint32_t)&sai1_exc_handler,                     /** @brief SAI1 global interrupt. */
    [104] = (uint32_t)&ltdc_exc_handler,                     /** @brief LCD-TFT global interrupt. */
    [105] = (uint32_t)&ltdc_er_exc_handler,                  /** @brief LCD-TFT error interrupt. */
    [106] = (uint32_t)&dma2d_exc_handler,                    /** @brief DMA2D global interrupt. */
    [107] = (uint32_t)&sai2_exc_handler,                     /** @brief SAI2 global interrupt. */
    [108] = (uint32_t)&quadspi_exc_handler,                  /** @brief QuadSPI global interrupt. */
    [109] = (uint32_t)&lptim1_exc_handler,                   /** @brief LPTIM1 global interrupt. */
    [110] = (uint32_t)&cec_exc_handler,                      /** @brief HDMI-CEC global interrupt. */
    [111] = (uint32_t)&i2c4_ev_exc_handler,                  /** @brief I2C4 event interrupt. */
    [112] = (uint32_t)&i2c4_er_exc_handler,                  /** @brief I2C4 error interrupt. */
    [113] = (uint32_t)&spdif_exc_handler,                    /** @brief SPDIFRX global interrupt. */
    [114] = (uint32_t)&otg_fs_ep1_out_exc_handler,           /** @brief OTG_FS out global interrupt. */
    [115] = (uint32_t)&otg_fs_ep1_in_exc_handler,            /** @brief OTG_FS in global interrupt. */
    [116] = (uint32_t)&otg_fs_wkup_exc_handler,              /** @brief OTG_FS wakeup. */
    [117] = (uint32_t)&otg_fs_exc_handler,                   /** @brief OTG_FS global interrupt. */
    [118] = (uint32_t)&dmamux1_ov_exc_handler,               /** @brief DMAMUX1 overrun interrupt. */
    [119] = (uint32_t)&hrtim_mst_exc_handler,                /** @brief HRTIM master timer interrupt. */
    [120] = (uint32_t)&hrtim_tima_exc_handler,               /** @brief HRTIM timer A interrupt. */
    [121] = (uint32_t)&hrtim_timb_exc_handler,               /** @brief HRTIM timer B interrupt. */
    [122] = (uint32_t)&hrtim_timc_exc_handler,               /** @brief HRTIM timer C interrupt. */
    [123] = (uint32_t)&hrtim_timd_exc_handler,               /** @brief HRTIM timer D interrupt. */
    [124] = (uint32_t)&hrtim_time_exc_handler,               /** @brief HRTIM timer E interrupt. */
    [125] = (uint32_t)&hrtim_flt_exc_handler,                /** @brief HRTIM fault interrupt. */
    [126] = (uint32_t)&dfsdm1_flt0_exc_handler,              /** @brief DFSDM1 filter 0 interrupt. */
    [127] = (uint32_t)&dfsdm1_flt1_exc_handler,              /** @brief DFSDM1 filter 1 interrupt. */
    [128] = (uint32_t)&dfsdm1_flt2_exc_handler,              /** @brief DFSDM1 filter 2 interrupt. */
    [129] = (uint32_t)&dfsdm1_flt3_exc_handler,              /** @brief DFSDM1 filter 3 interrupt. */
    [130] = (uint32_t)&sai3_exc_handler,                     /** @brief SAI3 global interrupt. */
    [131] = (uint32_t)&swpmi_exc_handler,                    /** @brief SWPMI global interrupt. */
    [132] = (uint32_t)&tim15_exc_handler,                    /** @brief TIM15 global interrupt. */
    [133] = (uint32_t)&tim16_exc_handler,                    /** @brief TIM16 global interrupt. */
    [134] = (uint32_t)&tim17_exc_handler,                    /** @brief TIM17 global interrupt. */
    [135] = (uint32_t)&mdios_wkup_exc_handler,               /** @brief MDIOS wakeup. */
    [136] = (uint32_t)&mdios_exc_handler,                    /** @brief MDIOS global interrupt. */
    [137] = (uint32_t)&jpeg_exc_handler,                     /** @brief JPEG global interrupt. */
    [138] = (uint32_t)&mdma_exc_handler,                     /** @brief MDMA. */
    [140] = (uint32_t)&sdmmc2_exc_handler,                   /** @brief SDMMC global interrupt. */
    [142] = (uint32_t)&hsem0_exc_handler,                    /** @brief HSEM global interrupt 1. */
    [143] = (uint32_t)&adc3_exc_handler,                     /** @brief ADC3 global interrupt. */
    [144] = (uint32_t)&dmamux2_ovr_exc_handler,              /** @brief DMAMUX2 overrun interrupt. */
    [145] = (uint32_t)&bdma_ch1_exc_handler,                 /** @brief BDMA channel 1 interrupt. */
    [146] = (uint32_t)&bdma_ch2_exc_handler,                 /** @brief BDMA channel 2 interrupt. */
    [147] = (uint32_t)&bdma_ch3_exc_handler,                 /** @brief BDMA channel 3 interrupt. */
    [148] = (uint32_t)&bdma_ch4_exc_handler,                 /** @brief BDMA channel 4 interrupt. */
    [149] = (uint32_t)&bdma_ch5_exc_handler,                 /** @brief BDMA channel 5 interrupt. */
    [150] = (uint32_t)&bdma_ch6_exc_handler,                 /** @brief BDMA channel 6 interrupt. */
    [151] = (uint32_t)&bdma_ch7_exc_handler,                 /** @brief BDMA channel 7 interrupt. */
    [152] = (uint32_t)&bdma_ch8_exc_handler,                 /** @brief BDMA channel 8 interrupt. */
    [153] = (uint32_t)&comp_exc_handler,                     /** @brief COMP1 and COMP2. */
    [154] = (uint32_t)&lptim2_exc_handler,                   /** @brief LPTIM2 timer interrupt. */
    [155] = (uint32_t)&lptim3_exc_handler,                   /** @brief LPTIM2 timer interrupt. */
    [156] = (uint32_t)&lptim4_exc_handler,                   /** @brief LPTIM2 timer interrupt. */
    [157] = (uint32_t)&lptim5_exc_handler,                   /** @brief LPTIM2 timer interrupt. */
    [158] = (uint32_t)&lpuart_exc_handler,                   /** @brief LPUART global interrupt. */
    [159] = (uint32_t)&wwdg2_rst_exc_handler,                /** @brief CM7 Window watchdog interrupt. */
    [160] = (uint32_t)&crs_exc_handler,                      /** @brief Clock recovery system globa. */
    [162] = (uint32_t)&sai4_exc_handler,                     /** @brief SAI4 global interrupt. */
    [164] = (uint32_t)&cm7_hold_core_exc_handler,            /** @brief CM7 hold core interrupt. */
    [165] = (uint32_t)&wkup_exc_handler,                     /** @brief WKUP1 to WKUP6 pins. */
  };

  /**** @subsection Vtable Definition for CM4 Core ****/

  __attribute__((section(".cm4_vtable")))
  static const uint32_t vtable[VTABLE_LENGTH] = {
    [0]   = CM4_STACK_END__,                                 /** @brief Address of top of stack for CM4 core. */
    [1]   = (uint32_t)&cm4_reset_exc_handler,                /** @brief MCU reset exception. */
    [2]   = (uint32_t)&cm4_nmi_exc_handler,                  /** @brief Non-maskable interrupt. */
    [3]   = (uint32_t)&cm4_hard_fault_exc_handler,           /** @brief Hard fault exception. */
    [4]   = (uint32_t)&cm4_mem_manage_exc_handler,           /** @brief Memory management fault (MPU). */
    [5]   = (uint32_t)&cm4_bus_fault_exc_handler,            /** @brief Bus fault exception. */
    [6]   = (uint32_t)&cm4_usage_fault_exc_handler,          /** @brief Usage fault exception. */
    [11]  = (uint32_t)&cm4_svc_exc_handler,                  /** @brief System service call exception. */
    [12]  = (uint32_t)&cm4_debug_mon_exc_handler,            /** @brief Debug monitor fault/exception. */
    [14]  = (uint32_t)&cm4_pendsv_exc_handler,               /** @brief Pended system service call exception. */
    [15]  = (uint32_t)&cm4_systick_exc_handler,              /** @brief SysTick interrupt. */
    [16]  = (uint32_t)&wwdg2_exc_handler,                    /** @brief CM4 watchdog interrupt. */
    [80]  = (uint32_t)&sev_it1_exc_handler,                  /** @brief Arm cortex-m7 send even interrupt. */
    [97]  = (uint32_t)&cm4_fpu_exc_handler,                  /** @brief CM4 Floating point unit interrupt. */
    [142] = (uint32_t)&hsem1_exc_handler,                    /** @brief HSEM global interrupt 2. */
    [159] = (uint32_t)&wwdg1_rst_exc_handler,                /** @brief CM7 Window watchdog interrupt. */
    [164] = (uint32_t)&cm4_hold_core_exc_handler,            /** @brief CM4 hold core interrupt. */
  };

#ifdef __cplusplus
  } // extern "C"
#endif