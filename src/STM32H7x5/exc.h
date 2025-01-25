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
 * @brief Exception defintions.
 */

#pragma once
#include <stdint.h>

#ifdef __cplusplus
  extern "C" {
#endif
  
  /*************************************************************************************************
   * @section Implementation Resources
   *************************************************************************************************/

  // Attributes for exception handler prototypes
  #define EXC_ATTR_ __attribute__((weak, used, alias("default_handler")))

  // Fallback exception handler.
  EXC_ATTR_ void default_handler() { 
    while (1); 
  }

  /*************************************************************************************************
   * @section Exception Handler Definitions 
   *************************************************************************************************/

  /**** @subsection Core Exceptions ****/

  EXC_ATTR_ void reset_exc_handler();             /** @brief MCU reset. */
  EXC_ATTR_ void nmi_exc_handler();               /** @brief Non-maskable interrupt. */
  EXC_ATTR_ void hard_fault_exc_handler();        /** @brief Hard fault. */
  EXC_ATTR_ void mem_manage_exc_handler();        /** @brief Memory management. */
  EXC_ATTR_ void bus_fault_exc_handler();         /** @brief Bus fault. */
  EXC_ATTR_ void usage_fault_exc_handler();       /** @brief Usage fault. */
  EXC_ATTR_ void svc_exc_handler();               /** @brief SVC. */
  EXC_ATTR_ void debug_mon_exc_handler();         /** @brief Debug monitor. */
  EXC_ATTR_ void pendsv_exc_handler();            /** @brief PendSV. */
  EXC_ATTR_ void systick_exc_handler();           /** @brief SysTick. */

  /**** @subsection IRQ Exceptions ****/

  EXC_ATTR_ void wwdg1_exc_handler();             /** @brief Window watchdog interrupt. */
  EXC_ATTR_ void pvd_pvm_exc_handler();           /** @brief PVD through EXTI line. */
  EXC_ATTR_ void rtc_tamp_stamp_exc_handler();    /** @brief RTC tamper, timestamp. */
  EXC_ATTR_ void rtc_wkup_exc_handler();          /** @brief RTC wakeup interrupt. */
  EXC_ATTR_ void flash_exc_handler();             /** @brief Flash memory. */
  EXC_ATTR_ void rcc_exc_handler();               /** @brief RCC global interrupt. */
  EXC_ATTR_ void exti0_exc_handler();             /** @brief EXTI line 0 interrupt. */
  EXC_ATTR_ void exti1_exc_handler();             /** @brief EXTI line 1 interrupt. */
  EXC_ATTR_ void exti2_exc_handler();             /** @brief EXTI line 2 interrupt. */
  EXC_ATTR_ void exti3_exc_handler();             /** @brief EXTI line 3 interrupt. */
  EXC_ATTR_ void exti4_exc_handler();             /** @brief EXTI line 4 interrupt. */
  EXC_ATTR_ void dma_str0_exc_handler();          /** @brief DMA1 stream0. */
  EXC_ATTR_ void dma_str1_exc_handler();          /** @brief DMA1 stream1. */
  EXC_ATTR_ void dma_str2_exc_handler();          /** @brief DMA1 stream2. */
  EXC_ATTR_ void dma_str3_exc_handler();          /** @brief DMA1 stream3. */
  EXC_ATTR_ void dma_str4_exc_handler();          /** @brief DMA1 stream4. */
  EXC_ATTR_ void dma_str5_exc_handler();          /** @brief DMA1 stream5. */
  EXC_ATTR_ void dma_str6_exc_handler();          /** @brief DMA1 stream6. */
  EXC_ATTR_ void adc1_2_exc_handler();            /** @brief ADC1 and ADC2. */
  EXC_ATTR_ void fdcan1_it0_exc_handler();        /** @brief FDCAN1 interrupt 0. */
  EXC_ATTR_ void fdcan2_it0_exc_handler();        /** @brief FDCAN2 interrupt 0. */
  EXC_ATTR_ void fdcan1_it1_exc_handler();        /** @brief FDCAN1 interrupt 1. */
  EXC_ATTR_ void fdcan2_it1_exc_handler();        /** @brief FDCAN2 interrupt 1. */
  EXC_ATTR_ void exti9_5_exc_handler();           /** @brief EXTI line[9:5] interrupts. */
  EXC_ATTR_ void tim1_brk_exc_handler();          /** @brief TIM1 break interrupt. */
  EXC_ATTR_ void tim1_up_exc_handler();           /** @brief TIM1 update interrupt. */
  EXC_ATTR_ void tim1_trg_com_exc_handler();      /** @brief TIM1 trigger and commutation. */
  EXC_ATTR_ void tim1_cc_exc_handler();           /** @brief TIM1 capture / compare. */
  EXC_ATTR_ void tim2_exc_handler();              /** @brief TIM2 global interrupt. */
  EXC_ATTR_ void tim2_exc_handler();              /** @brief TIM2 global interrupt. */
  EXC_ATTR_ void tim2_exc_handler();              /** @brief TIM2 global interrupt. */
  EXC_ATTR_ void tim2_exc_handler();              /** @brief TIM2 global interrupt. */
  EXC_ATTR_ void tim3_exc_handler();              /** @brief TIM3 global interrupt. */
  EXC_ATTR_ void tim4_exc_handler();              /** @brief TIM4 global interrupt. */
  EXC_ATTR_ void i2c1_ev_exc_handler();           /** @brief I2C1 event interrupt. */
  EXC_ATTR_ void i2c1_er_exc_handler();           /** @brief I2C1 error interrupt. */
  EXC_ATTR_ void i2c2_ev_exc_handler();           /** @brief I2C2 event interrupt. */
  EXC_ATTR_ void i2c2_er_exc_handler();           /** @brief I2C2 error interrupt. */
  EXC_ATTR_ void spi1_exc_handler();              /** @brief SPI1 global interrupt. */
  EXC_ATTR_ void spi2_exc_handler();              /** @brief SPI2 global interrupt. */
  EXC_ATTR_ void usart1_exc_handler();            /** @brief USART1 global interrupt. */
  EXC_ATTR_ void usart2_exc_handler();            /** @brief USART2 global interrupt. */
  EXC_ATTR_ void usart3_exc_handler();            /** @brief USART3 global interrupt. */
  EXC_ATTR_ void exti15_10_exc_handler();         /** @brief EXTI line[15:10] interrupts. */
  EXC_ATTR_ void rtc_alarm_exc_handler();         /** @brief RTC alarms (A and B). */
  EXC_ATTR_ void tim8_brk_tim12_exc_handler();    /** @brief TIM8 and 12 break global. */
  EXC_ATTR_ void tim8_up_tim13_exc_handler();     /** @brief TIM8 and 13 update global. */
  EXC_ATTR_ void tim8_14_trg_com_exc_handler();   /** @brief TIM8 and 14 trigger /commutation and global. */
  EXC_ATTR_ void tim8_cc_exc_handler();           /** @brief TIM8 capture / compare. */
  EXC_ATTR_ void dma1_str7_exc_handler();         /** @brief DMA1 stream7. */
  EXC_ATTR_ void fmc_exc_handler();               /** @brief FMC global interrupt. */
  EXC_ATTR_ void sdmmc1_exc_handler();            /** @brief SDMMC global interrupt. */
  EXC_ATTR_ void sdmmc1_exc_handler();            /** @brief SDMMC global interrupt. */
  EXC_ATTR_ void tim5_exc_handler();              /** @brief TIM5 global interrupt. */
  EXC_ATTR_ void spi3_exc_handler();              /** @brief SPI3 global interrupt. */
  EXC_ATTR_ void uart4_exc_handler();             /** @brief UART4 global interrupt. */
  EXC_ATTR_ void uart5_exc_handler();             /** @brief UART5 global interrupt. */
  EXC_ATTR_ void tim6_dac_exc_handler();          /** @brief TIM6 global interrupt. */
  EXC_ATTR_ void tim7_exc_handler();              /** @brief TIM7 global interrupt. */
  EXC_ATTR_ void dma2_str0_exc_handler();         /** @brief DMA2 stream0 interrupt. */
  EXC_ATTR_ void dma2_str1_exc_handler();         /** @brief DMA2 stream1 interrupt. */
  EXC_ATTR_ void dma2_str2_exc_handler();         /** @brief DMA2 stream2 interrupt. */
  EXC_ATTR_ void dma2_str3_exc_handler();         /** @brief DMA2 stream3 interrupt. */
  EXC_ATTR_ void dma2_str4_exc_handler();         /** @brief DMA2 stream4 interrupt. */
  EXC_ATTR_ void eth_exc_handler();               /** @brief Ethernet global interrupt. */
  EXC_ATTR_ void eth_wkup_exc_handler();          /** @brief Ethernet wakeup through EXTI. */
  EXC_ATTR_ void fdcan_cal_exc_handler();         /** @brief CAN2TX interrupts. */
  EXC_ATTR_ void cm4_sev_it_exc_handler();        /** @brief Arm cortex-m4 send even interrupt. */
  EXC_ATTR_ void dma2_str5_exc_handler();         /** @brief DMA2 stream5 interrupt. */
  EXC_ATTR_ void dma2_str6_exc_handler();         /** @brief DMA2 stream6 interrupt. */
  EXC_ATTR_ void dma2_str7_exc_handler();         /** @brief DMA2 stream7 interrupt. */
  EXC_ATTR_ void usart6_exc_handler();            /** @brief USART6 global interrupt. */
  EXC_ATTR_ void i2c3_ev_exc_handler();           /** @brief I2C3 event interrupt. */
  EXC_ATTR_ void i2c3_er_exc_handler();           /** @brief I2C3 error interrupt. */
  EXC_ATTR_ void otg_hs_ep1_out_exc_handler();    /** @brief OTG_HS out global interrupt. */
  EXC_ATTR_ void otg_hs_ep1_in_exc_handler();     /** @brief OTG_HS in global interrupt. */
  EXC_ATTR_ void otg_hs_wkup_exc_handler();       /** @brief OTG_HS wakeup interrupt. */
  EXC_ATTR_ void otg_hs_exc_handler();            /** @brief OTG_HS global interrupt. */
  EXC_ATTR_ void dcmi_exc_handler();              /** @brief DCMI global interrupt. */
  EXC_ATTR_ void cryp_exc_handler();              /** @brief CRYP global interrupt. */
  EXC_ATTR_ void hash_rng_exc_handler();          /** @brief HASH and RNG. */
  EXC_ATTR_ void fpu_exc_handler();               /** @brief Floating point unit interrupt. */
  EXC_ATTR_ void uart7_exc_handler();             /** @brief UART7 global interrupt. */
  EXC_ATTR_ void uart8_exc_handler();             /** @brief UART8 global interrupt. */
  EXC_ATTR_ void spi4_exc_handler();              /** @brief SPI4 global interrupt. */
  EXC_ATTR_ void spi5_exc_handler();              /** @brief SPI5 global interrupt. */
  EXC_ATTR_ void spi6_exc_handler();              /** @brief SPI6 global interrupt. */
  EXC_ATTR_ void sai1_exc_handler();              /** @brief SAI1 global interrupt. */
  EXC_ATTR_ void ltdc_exc_handler();              /** @brief LCD-TFT global interrupt. */
  EXC_ATTR_ void ltdc_er_exc_handler();           /** @brief LCD-TFT error interrupt. */
  EXC_ATTR_ void dma2d_exc_handler();             /** @brief DMA2D global interrupt. */
  EXC_ATTR_ void sai2_exc_handler();              /** @brief SAI2 global interrupt. */
  EXC_ATTR_ void quadspi_exc_handler();           /** @brief QuadSPI global interrupt. */
  EXC_ATTR_ void lptim1_exc_handler();            /** @brief LPTIM1 global interrupt. */
  EXC_ATTR_ void cec_exc_handler();               /** @brief HDMI-CEC global interrupt. */
  EXC_ATTR_ void i2c4_ev_exc_handler();           /** @brief I2C4 event interrupt. */
  EXC_ATTR_ void i2c4_er_exc_handler();           /** @brief I2C4 error interrupt. */
  EXC_ATTR_ void spdif_exc_handler();             /** @brief SPDIFRX global interrupt. */
  EXC_ATTR_ void otg_fs_ep1_out_exc_handler();    /** @brief OTG_FS out global interrupt. */
  EXC_ATTR_ void otg_fs_ep1_in_exc_handler();     /** @brief OTG_FS in global interrupt. */
  EXC_ATTR_ void otg_fs_wkup_exc_handler();       /** @brief OTG_FS wakeup. */
  EXC_ATTR_ void otg_fs_exc_handler();            /** @brief OTG_FS global interrupt. */
  EXC_ATTR_ void dmamux1_ov_exc_handler();        /** @brief DMAMUX1 overrun interrupt. */
  EXC_ATTR_ void hrtim_mst_exc_handler();         /** @brief HRTIM master timer interrupt. */
  EXC_ATTR_ void hrtim_tima_exc_handler();        /** @brief HRTIM timer A interrupt. */
  EXC_ATTR_ void hrtim_timb_exc_handler();        /** @brief HRTIM timer B interrupt. */
  EXC_ATTR_ void hrtim_timc_exc_handler();        /** @brief HRTIM timer C interrupt. */
  EXC_ATTR_ void hrtim_timd_exc_handler();        /** @brief HRTIM timer D interrupt. */
  EXC_ATTR_ void hrtim_time_exc_handler();        /** @brief HRTIM timer E interrupt. */
  EXC_ATTR_ void hrtim_flt_exc_handler();         /** @brief HRTIM fault interrupt. */
  EXC_ATTR_ void dfsdm1_flt0_exc_handler();       /** @brief DFSDM1 filter 0 interrupt. */
  EXC_ATTR_ void dfsdm1_flt1_exc_handler();       /** @brief DFSDM1 filter 1 interrupt. */
  EXC_ATTR_ void dfsdm1_flt2_exc_handler();       /** @brief DFSDM1 filter 2 interrupt. */
  EXC_ATTR_ void dfsdm1_flt3_exc_handler();       /** @brief DFSDM1 filter 3 interrupt. */
  EXC_ATTR_ void sai3_exc_handler();              /** @brief SAI3 global interrupt. */
  EXC_ATTR_ void swpmi1_exc_handler();            /** @brief SWPMI global interrupt. */
  EXC_ATTR_ void tim15_exc_handler();             /** @brief TIM15 global interrupt. */
  EXC_ATTR_ void tim16_exc_handler();             /** @brief TIM16 global interrupt. */
  EXC_ATTR_ void tim17_exc_handler();             /** @brief TIM17 global interrupt. */
  EXC_ATTR_ void mdios_wkup_exc_handler();        /** @brief MDIOS wakeup. */
  EXC_ATTR_ void mdios_exc_handler();             /** @brief MDIOS global interrupt. */
  EXC_ATTR_ void jpeg_exc_handler();              /** @brief JPEG global interrupt. */
  EXC_ATTR_ void mdma_exc_handler();              /** @brief MDMA. */
  EXC_ATTR_ void sdmmc0_exc_handler();            /** @brief SDMMC global interrupt. */
  EXC_ATTR_ void sdmmc0_exc_handler();            /** @brief SDMMC global interrupt. */
  EXC_ATTR_ void hsem0_exc_handler();             /** @brief HSEM global interrupt 1. */
  EXC_ATTR_ void adc3_exc_handler();              /** @brief ADC3 global interrupt. */
  EXC_ATTR_ void adc3_exc_handler();              /** @brief ADC3 global interrupt. */
  EXC_ATTR_ void adc3_exc_handler();              /** @brief ADC3 global interrupt. */
  EXC_ATTR_ void dmamux2_ovr_exc_handler();       /** @brief DMAMUX2 overrun interrupt. */
  EXC_ATTR_ void bdma_ch1_exc_handler();          /** @brief BDMA channel 1 interrupt. */
  EXC_ATTR_ void bdma_ch2_exc_handler();          /** @brief BDMA channel 2 interrupt. */
  EXC_ATTR_ void bdma_ch3_exc_handler();          /** @brief BDMA channel 3 interrupt. */
  EXC_ATTR_ void bdma_ch4_exc_handler();          /** @brief BDMA channel 4 interrupt. */
  EXC_ATTR_ void bdma_ch5_exc_handler();          /** @brief BDMA channel 5 interrupt. */
  EXC_ATTR_ void bdma_ch6_exc_handler();          /** @brief BDMA channel 6 interrupt. */
  EXC_ATTR_ void bdma_ch7_exc_handler();          /** @brief BDMA channel 7 interrupt. */
  EXC_ATTR_ void bdma_ch8_exc_handler();          /** @brief BDMA channel 8 interrupt. */
  EXC_ATTR_ void comp_exc_handler();              /** @brief COMP1 and COMP2. */
  EXC_ATTR_ void lptim2_exc_handler();            /** @brief LPTIM2 timer interrupt. */
  EXC_ATTR_ void lptim3_exc_handler();            /** @brief LPTIM2 timer interrupt. */
  EXC_ATTR_ void lptim4_exc_handler();            /** @brief LPTIM2 timer interrupt. */
  EXC_ATTR_ void lptim5_exc_handler();            /** @brief LPTIM2 timer interrupt. */
  EXC_ATTR_ void lpuart_exc_handler();            /** @brief LPUART global interrupt. */
  EXC_ATTR_ void wwdg2_rst_exc_handler();         /** @brief Window watchdog interrupt. */
  EXC_ATTR_ void crs_exc_handler();               /** @brief Clock recovery system globa. */
  EXC_ATTR_ void sai4_exc_handler();              /** @brief SAI4 global interrupt. */
  EXC_ATTR_ void hold_core_exc_handler();         /** @brief CPU1 hold. */
  EXC_ATTR_ void wkup_exc_handler();              /** @brief WKUP1 to WKUP6 pins. */

  /*************************************************************************************************
   * @section Exception Number Definitions 
   *************************************************************************************************/

  /**** @subsection Core Exceptions ****/

  #define RESET_EXC_NUM            INT32_C(1)     /** @brief MCU reset. */
  #define NMI_EXC_NUM              INT32_C(2)     /** @brief Non-maskable interrupt. */
  #define HARD_FAULT_EXC_NUM       INT32_C(3)     /** @brief Hard fault. */
  #define MEM_MANAGE_EXC_NUM       INT32_C(4)     /** @brief Memory management. */
  #define BUS_FAULT_EXC_NUM        INT32_C(5)     /** @brief Bus fault. */
  #define USAGE_FAULT_EXC_NUM      INT32_C(6)     /** @brief Usage fault. */
  #define SVC_EXC_NUM              INT32_C(11)    /** @brief SVC. */
  #define DEBUG_MON_EXC_NUM        INT32_C(12)    /** @brief Debug monitor. */
  #define PENDSV_EXC_NUM           INT32_C(14)    /** @brief PendSV. */
  #define SYSTICK_EXC_NUM          INT32_C(15)    /** @brief SysTick. */

  /**** @subsection IRQ Exceptions ****/

  #define WWDG1_EXC_NUM             INT32_C(16)    /** @brief Window watchdog interrupt. */
  #define PVD_PVM_EXC_NUM           INT32_C(17)    /** @brief PVD through EXTI line. */
  #define RTC_TAMP_STAMP_EXC_NUM    INT32_C(18)    /** @brief RTC tamper, timestamp. */
  #define RTC_WKUP_EXC_NUM          INT32_C(19)    /** @brief RTC wakeup interrupt. */
  #define FLASH_EXC_NUM             INT32_C(20)    /** @brief Flash memory. */
  #define RCC_EXC_NUM               INT32_C(21)    /** @brief RCC global interrupt. */
  #define EXTI0_EXC_NUM             INT32_C(22)    /** @brief EXTI line 0 interrupt. */
  #define EXTI1_EXC_NUM             INT32_C(23)    /** @brief EXTI line 1 interrupt. */
  #define EXTI2_EXC_NUM             INT32_C(24)    /** @brief EXTI line 2 interrupt. */
  #define EXTI3_EXC_NUM             INT32_C(25)    /** @brief EXTI line 3interrupt. */
  #define EXTI4_EXC_NUM             INT32_C(26)    /** @brief EXTI line 4interrupt. */
  #define DMA_STR0_EXC_NUM          INT32_C(27)    /** @brief DMA1 stream0. */
  #define DMA_STR1_EXC_NUM          INT32_C(28)    /** @brief DMA1 stream1. */
  #define DMA_STR2_EXC_NUM          INT32_C(29)    /** @brief DMA1 stream2. */
  #define DMA_STR3_EXC_NUM          INT32_C(30)    /** @brief DMA1 stream3. */
  #define DMA_STR4_EXC_NUM          INT32_C(31)    /** @brief DMA1 stream4. */
  #define DMA_STR5_EXC_NUM          INT32_C(32)    /** @brief DMA1 stream5. */
  #define DMA_STR6_EXC_NUM          INT32_C(33)    /** @brief DMA1 stream6. */
  #define ADC1_2_EXC_NUM            INT32_C(34)    /** @brief ADC1 and ADC2. */
  #define FDCAN1_IT0_EXC_NUM        INT32_C(35)    /** @brief FDCAN1 interrupt 0. */
  #define FDCAN2_IT0_EXC_NUM        INT32_C(36)    /** @brief FDCAN2 interrupt 0. */
  #define FDCAN1_IT1_EXC_NUM        INT32_C(37)    /** @brief FDCAN1 interrupt 1. */
  #define FDCAN2_IT1_EXC_NUM        INT32_C(38)    /** @brief FDCAN2 interrupt 1. */
  #define EXTI9_5_EXC_NUM           INT32_C(39)    /** @brief EXTI line[9:5] interrupts. */
  #define TIM1_BRK_EXC_NUM          INT32_C(40)    /** @brief TIM1 break interrupt. */
  #define TIM1_UP_EXC_NUM           INT32_C(41)    /** @brief TIM1 update interrupt. */
  #define TIM1_TRG_COM_EXC_NUM      INT32_C(42)    /** @brief TIM1 trigger and commutation. */
  #define TIM1_CC_EXC_NUM           INT32_C(43)    /** @brief TIM1 capture / compare. */
  #define TIM2_EXC_NUM              INT32_C(44)    /** @brief TIM2 global interrupt. */
  #define TIM2_EXC_NUM              INT32_C(44)    /** @brief TIM2 global interrupt. */
  #define TIM2_EXC_NUM              INT32_C(44)    /** @brief TIM2 global interrupt. */
  #define TIM2_EXC_NUM              INT32_C(44)    /** @brief TIM2 global interrupt. */
  #define TIM3_EXC_NUM              INT32_C(45)    /** @brief TIM3 global interrupt. */
  #define TIM4_EXC_NUM              INT32_C(46)    /** @brief TIM4 global interrupt. */
  #define I2C1_EV_EXC_NUM           INT32_C(47)    /** @brief I2C1 event interrupt. */
  #define I2C1_ER_EXC_NUM           INT32_C(48)    /** @brief I2C1 error interrupt. */
  #define I2C2_EV_EXC_NUM           INT32_C(49)    /** @brief I2C2 event interrupt. */
  #define I2C2_ER_EXC_NUM           INT32_C(50)    /** @brief I2C2 error interrupt. */
  #define SPI1_EXC_NUM              INT32_C(51)    /** @brief SPI1 global interrupt. */
  #define SPI2_EXC_NUM              INT32_C(52)    /** @brief SPI2 global interrupt. */
  #define USART1_EXC_NUM            INT32_C(53)    /** @brief USART1 global interrupt. */
  #define USART2_EXC_NUM            INT32_C(54)    /** @brief USART2 global interrupt. */
  #define USART3_EXC_NUM            INT32_C(55)    /** @brief USART3 global interrupt. */
  #define EXTI15_10_EXC_NUM         INT32_C(56)    /** @brief EXTI line[15:10] interrupts. */
  #define RTC_ALARM_EXC_NUM         INT32_C(57)    /** @brief RTC alarms (A and B). */
  #define TIM8_BRK_TIM12_EXC_NUM    INT32_C(59)    /** @brief TIM8 and 12 break global. */
  #define TIM8_UP_TIM13_EXC_NUM     INT32_C(60)    /** @brief TIM8 and 13 update global. */
  #define TIM8_14_TRG_COM_EXC_NUM   INT32_C(61)    /** @brief TIM8 and 14 trigger /commutation and global. */
  #define TIM8_CC_EXC_NUM           INT32_C(62)    /** @brief TIM8 capture / compare. */
  #define DMA1_STR7_EXC_NUM         INT32_C(63)    /** @brief DMA1 stream7. */
  #define FMC_EXC_NUM               INT32_C(64)    /** @brief FMC global interrupt. */
  #define SDMMC1_EXC_NUM            INT32_C(65)    /** @brief SDMMC global interrupt. */
  #define SDMMC1_EXC_NUM            INT32_C(65)    /** @brief SDMMC global interrupt. */
  #define TIM5_EXC_NUM              INT32_C(66)    /** @brief TIM5 global interrupt. */
  #define SPI3_EXC_NUM              INT32_C(67)    /** @brief SPI3 global interrupt. */
  #define UART4_EXC_NUM             INT32_C(68)    /** @brief UART4 global interrupt. */
  #define UART5_EXC_NUM             INT32_C(69)    /** @brief UART5 global interrupt. */
  #define TIM6_DAC_EXC_NUM          INT32_C(70)    /** @brief TIM6 global interrupt. */
  #define TIM7_EXC_NUM              INT32_C(71)    /** @brief TIM7 global interrupt. */
  #define DMA2_STR0_EXC_NUM         INT32_C(72)    /** @brief DMA2 stream0 interrupt. */
  #define DMA2_STR1_EXC_NUM         INT32_C(73)    /** @brief DMA2 stream1 interrupt. */
  #define DMA2_STR2_EXC_NUM         INT32_C(74)    /** @brief DMA2 stream2 interrupt. */
  #define DMA2_STR3_EXC_NUM         INT32_C(75)    /** @brief DMA2 stream3 interrupt. */
  #define DMA2_STR4_EXC_NUM         INT32_C(76)    /** @brief DMA2 stream4 interrupt. */
  #define ETH_EXC_NUM               INT32_C(77)    /** @brief Ethernet global interrupt. */
  #define ETH_WKUP_EXC_NUM          INT32_C(78)    /** @brief Ethernet wakeup through EXTI. */
  #define FDCAN_CAL_EXC_NUM         INT32_C(79)    /** @brief CAN2TX interrupts. */
  #define CM4_SEV_IT_EXC_NUM        INT32_C(81)    /** @brief Arm cortex-m4 send even interrupt. */
  #define DMA2_STR5_EXC_NUM         INT32_C(84)    /** @brief DMA2 stream5 interrupt. */
  #define DMA2_STR6_EXC_NUM         INT32_C(85)    /** @brief DMA2 stream6 interrupt. */
  #define DMA2_STR7_EXC_NUM         INT32_C(86)    /** @brief DMA2 stream7 interrupt. */
  #define USART6_EXC_NUM            INT32_C(87)    /** @brief USART6 global interrupt. */
  #define I2C3_EV_EXC_NUM           INT32_C(88)    /** @brief I2C3 event interrupt. */
  #define I2C3_ER_EXC_NUM           INT32_C(89)    /** @brief I2C3 error interrupt. */
  #define OTG_HS_EP1_OUT_EXC_NUM    INT32_C(90)    /** @brief OTG_HS out global interrupt. */
  #define OTG_HS_EP1_IN_EXC_NUM     INT32_C(91)    /** @brief OTG_HS in global interrupt. */
  #define OTG_HS_WKUP_EXC_NUM       INT32_C(92)    /** @brief OTG_HS wakeup interrupt. */
  #define OTG_HS_EXC_NUM            INT32_C(93)    /** @brief OTG_HS global interrupt. */
  #define DCMI_EXC_NUM              INT32_C(94)    /** @brief DCMI global interrupt. */
  #define CRYP_EXC_NUM              INT32_C(95)    /** @brief CRYP global interrupt. */
  #define HASH_RNG_EXC_NUM          INT32_C(96)    /** @brief HASH and RNG. */
  #define FPU_EXC_NUM               INT32_C(97)    /** @brief Floating point unit interrupt. */
  #define UART7_EXC_NUM             INT32_C(98)    /** @brief UART7 global interrupt. */
  #define UART8_EXC_NUM             INT32_C(99)    /** @brief UART8 global interrupt. */
  #define SPI4_EXC_NUM              INT32_C(100)   /** @brief SPI4 global interrupt. */
  #define SPI5_EXC_NUM              INT32_C(101)   /** @brief SPI5 global interrupt. */
  #define SPI6_EXC_NUM              INT32_C(102)   /** @brief SPI6 global interrupt. */
  #define SAI1_EXC_NUM              INT32_C(103)   /** @brief SAI1 global interrupt. */
  #define LTDC_EXC_NUM              INT32_C(104)   /** @brief LCD-TFT global interrupt. */
  #define LTDC_ER_EXC_NUM           INT32_C(105)   /** @brief LCD-TFT error interrupt. */
  #define DMA2D_EXC_NUM             INT32_C(106)   /** @brief DMA2D global interrupt. */
  #define SAI2_EXC_NUM              INT32_C(107)   /** @brief SAI2 global interrupt. */
  #define QUADSPI_EXC_NUM           INT32_C(108)   /** @brief QuadSPI global interrupt. */
  #define LPTIM1_EXC_NUM            INT32_C(109)   /** @brief LPTIM1 global interrupt. */
  #define CEC_EXC_NUM               INT32_C(110)   /** @brief HDMI-CEC global interrupt. */
  #define I2C4_EV_EXC_NUM           INT32_C(111)   /** @brief I2C4 event interrupt. */
  #define I2C4_ER_EXC_NUM           INT32_C(112)   /** @brief I2C4 error interrupt. */
  #define SPDIF_EXC_NUM             INT32_C(113)   /** @brief SPDIFRX global interrupt. */
  #define OTG_FS_EP1_OUT_EXC_NUM    INT32_C(114)   /** @brief OTG_FS out global interrupt. */
  #define OTG_FS_EP1_IN_EXC_NUM     INT32_C(115)   /** @brief OTG_FS in global interrupt. */
  #define OTG_FS_WKUP_EXC_NUM       INT32_C(116)   /** @brief OTG_FS wakeup. */
  #define OTG_FS_EXC_NUM            INT32_C(117)   /** @brief OTG_FS global interrupt. */
  #define DMAMUX1_OV_EXC_NUM        INT32_C(118)   /** @brief DMAMUX1 overrun interrupt. */
  #define HRTIM_MST_EXC_NUM         INT32_C(119)   /** @brief HRTIM master timer interrupt. */
  #define HRTIM_TIMA_EXC_NUM        INT32_C(120)   /** @brief HRTIM timer A interrupt. */
  #define HRTIM_TIMB_EXC_NUM        INT32_C(121)   /** @brief HRTIM timer B interrupt. */
  #define HRTIM_TIMC_EXC_NUM        INT32_C(122)   /** @brief HRTIM timer C interrupt. */
  #define HRTIM_TIMD_EXC_NUM        INT32_C(123)   /** @brief HRTIM timer D interrupt. */
  #define HRTIM_TIME_EXC_NUM        INT32_C(124)   /** @brief HRTIM timer E interrupt. */
  #define HRTIM_FLT_EXC_NUM         INT32_C(125)   /** @brief HRTIM fault interrupt. */
  #define DFSDM1_FLT0_EXC_NUM       INT32_C(126)   /** @brief DFSDM1 filter 0 interrupt. */
  #define DFSDM1_FLT1_EXC_NUM       INT32_C(127)   /** @brief DFSDM1 filter 1 interrupt. */
  #define DFSDM1_FLT2_EXC_NUM       INT32_C(128)   /** @brief DFSDM1 filter 2 interrupt. */
  #define DFSDM1_FLT3_EXC_NUM       INT32_C(129)   /** @brief DFSDM1 filter 3 interrupt. */
  #define SAI3_EXC_NUM              INT32_C(130)   /** @brief SAI3 global interrupt. */
  #define SWPMI1_EXC_NUM            INT32_C(131)   /** @brief SWPMI global interrupt. */
  #define TIM15_EXC_NUM             INT32_C(132)   /** @brief TIM15 global interrupt. */
  #define TIM16_EXC_NUM             INT32_C(133)   /** @brief TIM16 global interrupt. */
  #define TIM17_EXC_NUM             INT32_C(134)   /** @brief TIM17 global interrupt. */
  #define MDIOS_WKUP_EXC_NUM        INT32_C(135)   /** @brief MDIOS wakeup. */
  #define MDIOS_EXC_NUM             INT32_C(136)   /** @brief MDIOS global interrupt. */
  #define JPEG_EXC_NUM              INT32_C(137)   /** @brief JPEG global interrupt. */
  #define MDMA_EXC_NUM              INT32_C(138)   /** @brief MDMA. */
  #define SDMMC0_EXC_NUM            INT32_C(140)   /** @brief SDMMC global interrupt. */
  #define SDMMC0_EXC_NUM            INT32_C(140)   /** @brief SDMMC global interrupt. */
  #define HSEM0_EXC_NUM             INT32_C(141)   /** @brief HSEM global interrupt 1. */
  #define ADC3_EXC_NUM              INT32_C(143)   /** @brief ADC3 global interrupt. */
  #define ADC3_EXC_NUM              INT32_C(143)   /** @brief ADC3 global interrupt. */
  #define ADC3_EXC_NUM              INT32_C(143)   /** @brief ADC3 global interrupt. */
  #define DMAMUX2_OVR_EXC_NUM       INT32_C(144)   /** @brief DMAMUX2 overrun interrupt. */
  #define BDMA_CH1_EXC_NUM          INT32_C(145)   /** @brief BDMA channel 1 interrupt. */
  #define BDMA_CH2_EXC_NUM          INT32_C(146)   /** @brief BDMA channel 2 interrupt. */
  #define BDMA_CH3_EXC_NUM          INT32_C(147)   /** @brief BDMA channel 3 interrupt. */
  #define BDMA_CH4_EXC_NUM          INT32_C(148)   /** @brief BDMA channel 4 interrupt. */
  #define BDMA_CH5_EXC_NUM          INT32_C(149)   /** @brief BDMA channel 5 interrupt. */
  #define BDMA_CH6_EXC_NUM          INT32_C(150)   /** @brief BDMA channel 6 interrupt. */
  #define BDMA_CH7_EXC_NUM          INT32_C(151)   /** @brief BDMA channel 7 interrupt. */
  #define BDMA_CH8_EXC_NUM          INT32_C(152)   /** @brief BDMA channel 8 interrupt. */
  #define COMP_EXC_NUM              INT32_C(153)   /** @brief COMP1 and COMP2. */
  #define LPTIM2_EXC_NUM            INT32_C(154)   /** @brief LPTIM2 timer interrupt. */
  #define LPTIM3_EXC_NUM            INT32_C(155)   /** @brief LPTIM2 timer interrupt. */
  #define LPTIM4_EXC_NUM            INT32_C(156)   /** @brief LPTIM2 timer interrupt. */
  #define LPTIM5_EXC_NUM            INT32_C(157)   /** @brief LPTIM2 timer interrupt. */
  #define LPUART_EXC_NUM            INT32_C(158)   /** @brief LPUART global interrupt. */
  #define WWDG2_RST_EXC_NUM         INT32_C(159)   /** @brief Window watchdog interrupt. */
  #define CRS_EXC_NUM               INT32_C(160)   /** @brief Clock recovery system globa. */
  #define SAI4_EXC_NUM              INT32_C(162)   /** @brief SAI4 global interrupt. */
  #define HOLD_CORE_EXC_NUM         INT32_C(164)   /** @brief CPU1 hold. */
  #define WKUP_EXC_NUM              INT32_C(165)   /** @brief WKUP1 to WKUP6 pins. */

  /*************************************************************************************************
   * @section Exception Vector Table Definition 
   *************************************************************************************************/

  __attribute__((section(".vtable")))
  static const uint32_t vtable[256] = {
    [RESET_EXC_NUM]           = (uint32_t)&reset_exc_handler,           /** @brief MCU reset. */
    [NMI_EXC_NUM]             = (uint32_t)&nmi_exc_handler,             /** @brief Non-maskable interrupt. */
    [HARD_FAULT_EXC_NUM]      = (uint32_t)&hard_fault_exc_handler,      /** @brief Hard fault. */
    [MEM_MANAGE_EXC_NUM]      = (uint32_t)&mem_manage_exc_handler,      /** @brief Memory management. */
    [BUS_FAULT_EXC_NUM]       = (uint32_t)&bus_fault_exc_handler,       /** @brief Bus fault. */
    [USAGE_FAULT_EXC_NUM]     = (uint32_t)&usage_fault_exc_handler,     /** @brief Usage fault. */
    [SVC_EXC_NUM]             = (uint32_t)&svc_exc_handler,             /** @brief SVC. */
    [DEBUG_MON_EXC_NUM]       = (uint32_t)&debug_mon_exc_handler,       /** @brief Debug monitor. */
    [PENDSV_EXC_NUM]          = (uint32_t)&pendsv_exc_handler,          /** @brief PendSV. */
    [SYSTICK_EXC_NUM]         = (uint32_t)&systick_exc_handler,         /** @brief SysTick. */
    [COMP_EXC_NUM]            = (uint32_t)&comp_exc_handler,            /** @brief COMP1 and COMP2. */
    [CRS_EXC_NUM]             = (uint32_t)&crs_exc_handler,             /** @brief Clock recovery system globa. */
    [BDMA_CH1_EXC_NUM]        = (uint32_t)&bdma_ch1_exc_handler,        /** @brief BDMA channel 1 interrupt. */
    [BDMA_CH2_EXC_NUM]        = (uint32_t)&bdma_ch2_exc_handler,        /** @brief BDMA channel 2 interrupt. */
    [BDMA_CH3_EXC_NUM]        = (uint32_t)&bdma_ch3_exc_handler,        /** @brief BDMA channel 3 interrupt. */
    [BDMA_CH4_EXC_NUM]        = (uint32_t)&bdma_ch4_exc_handler,        /** @brief BDMA channel 4 interrupt. */
    [BDMA_CH5_EXC_NUM]        = (uint32_t)&bdma_ch5_exc_handler,        /** @brief BDMA channel 5 interrupt. */
    [BDMA_CH6_EXC_NUM]        = (uint32_t)&bdma_ch6_exc_handler,        /** @brief BDMA channel 6 interrupt. */
    [BDMA_CH7_EXC_NUM]        = (uint32_t)&bdma_ch7_exc_handler,        /** @brief BDMA channel 7 interrupt. */
    [BDMA_CH8_EXC_NUM]        = (uint32_t)&bdma_ch8_exc_handler,        /** @brief BDMA channel 8 interrupt. */
    [DMA2D_EXC_NUM]           = (uint32_t)&dma2d_exc_handler,           /** @brief DMA2D global interrupt. */
    [DMAMUX2_OVR_EXC_NUM]     = (uint32_t)&dmamux2_ovr_exc_handler,     /** @brief DMAMUX2 overrun interrupt. */
    [FMC_EXC_NUM]             = (uint32_t)&fmc_exc_handler,             /** @brief FMC global interrupt. */
    [CEC_EXC_NUM]             = (uint32_t)&cec_exc_handler,             /** @brief HDMI-CEC global interrupt. */
    [HSEM0_EXC_NUM]           = (uint32_t)&hsem0_exc_handler,           /** @brief HSEM global interrupt 1. */
    [I2C1_EV_EXC_NUM]         = (uint32_t)&i2c1_ev_exc_handler,         /** @brief I2C1 event interrupt. */
    [I2C1_ER_EXC_NUM]         = (uint32_t)&i2c1_er_exc_handler,         /** @brief I2C1 error interrupt. */
    [I2C2_EV_EXC_NUM]         = (uint32_t)&i2c2_ev_exc_handler,         /** @brief I2C2 event interrupt. */
    [I2C2_ER_EXC_NUM]         = (uint32_t)&i2c2_er_exc_handler,         /** @brief I2C2 error interrupt. */
    [I2C3_EV_EXC_NUM]         = (uint32_t)&i2c3_ev_exc_handler,         /** @brief I2C3 event interrupt. */
    [I2C3_ER_EXC_NUM]         = (uint32_t)&i2c3_er_exc_handler,         /** @brief I2C3 error interrupt. */
    [I2C4_EV_EXC_NUM]         = (uint32_t)&i2c4_ev_exc_handler,         /** @brief I2C4 event interrupt. */
    [I2C4_ER_EXC_NUM]         = (uint32_t)&i2c4_er_exc_handler,         /** @brief I2C4 error interrupt. */
    [JPEG_EXC_NUM]            = (uint32_t)&jpeg_exc_handler,            /** @brief JPEG global interrupt. */
    [MDMA_EXC_NUM]            = (uint32_t)&mdma_exc_handler,            /** @brief MDMA. */
    [QUADSPI_EXC_NUM]         = (uint32_t)&quadspi_exc_handler,         /** @brief QuadSPI global interrupt. */
    [RTC_TAMP_STAMP_EXC_NUM]  = (uint32_t)&rtc_tamp_stamp_exc_handler,  /** @brief RTC tamper, timestamp. */
    [RTC_WKUP_EXC_NUM]        = (uint32_t)&rtc_wkup_exc_handler,        /** @brief RTC wakeup interrupt. */
    [RTC_ALARM_EXC_NUM]       = (uint32_t)&rtc_alarm_exc_handler,       /** @brief RTC alarms (A and B). */
    [SAI4_EXC_NUM]            = (uint32_t)&sai4_exc_handler,            /** @brief SAI4 global interrupt. */
    [SAI1_EXC_NUM]            = (uint32_t)&sai1_exc_handler,            /** @brief SAI1 global interrupt. */
    [SAI2_EXC_NUM]            = (uint32_t)&sai2_exc_handler,            /** @brief SAI2 global interrupt. */
    [SAI3_EXC_NUM]            = (uint32_t)&sai3_exc_handler,            /** @brief SAI3 global interrupt. */
    [SDMMC1_EXC_NUM]          = (uint32_t)&sdmmc1_exc_handler,          /** @brief SDMMC global interrupt. */
    [SDMMC0_EXC_NUM]          = (uint32_t)&sdmmc0_exc_handler,          /** @brief SDMMC global interrupt. */
    [SDMMC1_EXC_NUM]          = (uint32_t)&sdmmc1_exc_handler,          /** @brief SDMMC global interrupt. */
    [SDMMC0_EXC_NUM]          = (uint32_t)&sdmmc0_exc_handler,          /** @brief SDMMC global interrupt. */
    [WWDG1_EXC_NUM]           = (uint32_t)&wwdg1_exc_handler,           /** @brief Window watchdog interrupt. */
    [WWDG2_RST_EXC_NUM]       = (uint32_t)&wwdg2_rst_exc_handler,       /** @brief Window watchdog interrupt. */
    [SPI1_EXC_NUM]            = (uint32_t)&spi1_exc_handler,            /** @brief SPI1 global interrupt. */
    [SPI2_EXC_NUM]            = (uint32_t)&spi2_exc_handler,            /** @brief SPI2 global interrupt. */
    [SPI3_EXC_NUM]            = (uint32_t)&spi3_exc_handler,            /** @brief SPI3 global interrupt. */
    [SPI4_EXC_NUM]            = (uint32_t)&spi4_exc_handler,            /** @brief SPI4 global interrupt. */
    [SPI5_EXC_NUM]            = (uint32_t)&spi5_exc_handler,            /** @brief SPI5 global interrupt. */
    [SPI6_EXC_NUM]            = (uint32_t)&spi6_exc_handler,            /** @brief SPI6 global interrupt. */
    [LTDC_EXC_NUM]            = (uint32_t)&ltdc_exc_handler,            /** @brief LCD-TFT global interrupt. */
    [LTDC_ER_EXC_NUM]         = (uint32_t)&ltdc_er_exc_handler,         /** @brief LCD-TFT error interrupt. */
    [SPDIF_EXC_NUM]           = (uint32_t)&spdif_exc_handler,           /** @brief SPDIFRX global interrupt. */
    [ADC3_EXC_NUM]            = (uint32_t)&adc3_exc_handler,            /** @brief ADC3 global interrupt. */
    [ADC3_EXC_NUM]            = (uint32_t)&adc3_exc_handler,            /** @brief ADC3 global interrupt. */
    [ADC3_EXC_NUM]            = (uint32_t)&adc3_exc_handler,            /** @brief ADC3 global interrupt. */
    [ADC1_2_EXC_NUM]          = (uint32_t)&adc1_2_exc_handler,          /** @brief ADC1 and ADC2. */
    [DMAMUX1_OV_EXC_NUM]      = (uint32_t)&dmamux1_ov_exc_handler,      /** @brief DMAMUX1 overrun interrupt. */
    [RCC_EXC_NUM]             = (uint32_t)&rcc_exc_handler,             /** @brief RCC global interrupt. */
    [LPTIM1_EXC_NUM]          = (uint32_t)&lptim1_exc_handler,          /** @brief LPTIM1 global interrupt. */
    [LPTIM2_EXC_NUM]          = (uint32_t)&lptim2_exc_handler,          /** @brief LPTIM2 timer interrupt. */
    [LPTIM3_EXC_NUM]          = (uint32_t)&lptim3_exc_handler,          /** @brief LPTIM2 timer interrupt. */
    [LPTIM4_EXC_NUM]          = (uint32_t)&lptim4_exc_handler,          /** @brief LPTIM2 timer interrupt. */
    [LPTIM5_EXC_NUM]          = (uint32_t)&lptim5_exc_handler,          /** @brief LPTIM2 timer interrupt. */
    [LPUART_EXC_NUM]          = (uint32_t)&lpuart_exc_handler,          /** @brief LPUART global interrupt. */
    [PVD_PVM_EXC_NUM]         = (uint32_t)&pvd_pvm_exc_handler,         /** @brief PVD through EXTI line. */
    [EXTI0_EXC_NUM]           = (uint32_t)&exti0_exc_handler,           /** @brief EXTI line 0 interrupt. */
    [EXTI1_EXC_NUM]           = (uint32_t)&exti1_exc_handler,           /** @brief EXTI line 1 interrupt. */
    [EXTI2_EXC_NUM]           = (uint32_t)&exti2_exc_handler,           /** @brief EXTI line 2 interrupt. */
    [EXTI3_EXC_NUM]           = (uint32_t)&exti3_exc_handler,           /** @brief EXTI line 3interrupt. */
    [EXTI4_EXC_NUM]           = (uint32_t)&exti4_exc_handler,           /** @brief EXTI line 4interrupt. */
    [EXTI9_5_EXC_NUM]         = (uint32_t)&exti9_5_exc_handler,         /** @brief EXTI line[9:5] interrupts. */
    [EXTI15_10_EXC_NUM]       = (uint32_t)&exti15_10_exc_handler,       /** @brief EXTI line[15:10] interrupts. */
    [CM4_SEV_IT_EXC_NUM]      = (uint32_t)&cm4_sev_it_exc_handler,      /** @brief Arm cortex-m4 send even interrupt. */
    [HOLD_CORE_EXC_NUM]       = (uint32_t)&hold_core_exc_handler,       /** @brief CPU1 hold. */
    [WKUP_EXC_NUM]            = (uint32_t)&wkup_exc_handler,            /** @brief WKUP1 to WKUP6 pins. */
    [FLASH_EXC_NUM]           = (uint32_t)&flash_exc_handler,           /** @brief Flash memory. */
    [HASH_RNG_EXC_NUM]        = (uint32_t)&hash_rng_exc_handler,        /** @brief HASH and RNG. */
    [CRYP_EXC_NUM]            = (uint32_t)&cryp_exc_handler,            /** @brief CRYP global interrupt. */
    [DCMI_EXC_NUM]            = (uint32_t)&dcmi_exc_handler,            /** @brief DCMI global interrupt. */
    [OTG_FS_EP1_OUT_EXC_NUM]  = (uint32_t)&otg_fs_ep1_out_exc_handler,  /** @brief OTG_FS out global interrupt. */
    [OTG_FS_EP1_IN_EXC_NUM]   = (uint32_t)&otg_fs_ep1_in_exc_handler,   /** @brief OTG_FS in global interrupt. */
    [OTG_FS_WKUP_EXC_NUM]     = (uint32_t)&otg_fs_wkup_exc_handler,     /** @brief OTG_FS wakeup. */
    [OTG_FS_EXC_NUM]          = (uint32_t)&otg_fs_exc_handler,          /** @brief OTG_FS global interrupt. */
    [OTG_HS_EP1_OUT_EXC_NUM]  = (uint32_t)&otg_hs_ep1_out_exc_handler,  /** @brief OTG_HS out global interrupt. */
    [OTG_HS_EP1_IN_EXC_NUM]   = (uint32_t)&otg_hs_ep1_in_exc_handler,   /** @brief OTG_HS in global interrupt. */
    [OTG_HS_WKUP_EXC_NUM]     = (uint32_t)&otg_hs_wkup_exc_handler,     /** @brief OTG_HS wakeup interrupt. */
    [OTG_HS_EXC_NUM]          = (uint32_t)&otg_hs_exc_handler,          /** @brief OTG_HS global interrupt. */
    [ETH_EXC_NUM]             = (uint32_t)&eth_exc_handler,             /** @brief Ethernet global interrupt. */
    [ETH_WKUP_EXC_NUM]        = (uint32_t)&eth_wkup_exc_handler,        /** @brief Ethernet wakeup through EXTI. */
    [DMA_STR0_EXC_NUM]        = (uint32_t)&dma_str0_exc_handler,        /** @brief DMA1 stream0. */
    [DMA_STR1_EXC_NUM]        = (uint32_t)&dma_str1_exc_handler,        /** @brief DMA1 stream1. */
    [DMA_STR2_EXC_NUM]        = (uint32_t)&dma_str2_exc_handler,        /** @brief DMA1 stream2. */
    [DMA_STR3_EXC_NUM]        = (uint32_t)&dma_str3_exc_handler,        /** @brief DMA1 stream3. */
    [DMA_STR4_EXC_NUM]        = (uint32_t)&dma_str4_exc_handler,        /** @brief DMA1 stream4. */
    [DMA_STR5_EXC_NUM]        = (uint32_t)&dma_str5_exc_handler,        /** @brief DMA1 stream5. */
    [DMA_STR6_EXC_NUM]        = (uint32_t)&dma_str6_exc_handler,        /** @brief DMA1 stream6. */
    [DMA1_STR7_EXC_NUM]       = (uint32_t)&dma1_str7_exc_handler,       /** @brief DMA1 stream7. */
    [DMA2_STR0_EXC_NUM]       = (uint32_t)&dma2_str0_exc_handler,       /** @brief DMA2 stream0 interrupt. */
    [DMA2_STR1_EXC_NUM]       = (uint32_t)&dma2_str1_exc_handler,       /** @brief DMA2 stream1 interrupt. */
    [DMA2_STR2_EXC_NUM]       = (uint32_t)&dma2_str2_exc_handler,       /** @brief DMA2 stream2 interrupt. */
    [DMA2_STR3_EXC_NUM]       = (uint32_t)&dma2_str3_exc_handler,       /** @brief DMA2 stream3 interrupt. */
    [DMA2_STR4_EXC_NUM]       = (uint32_t)&dma2_str4_exc_handler,       /** @brief DMA2 stream4 interrupt. */
    [DMA2_STR5_EXC_NUM]       = (uint32_t)&dma2_str5_exc_handler,       /** @brief DMA2 stream5 interrupt. */
    [DMA2_STR6_EXC_NUM]       = (uint32_t)&dma2_str6_exc_handler,       /** @brief DMA2 stream6 interrupt. */
    [DMA2_STR7_EXC_NUM]       = (uint32_t)&dma2_str7_exc_handler,       /** @brief DMA2 stream7 interrupt. */
    [HRTIM_MST_EXC_NUM]       = (uint32_t)&hrtim_mst_exc_handler,       /** @brief HRTIM master timer interrupt. */
    [HRTIM_FLT_EXC_NUM]       = (uint32_t)&hrtim_flt_exc_handler,       /** @brief HRTIM fault interrupt. */
    [HRTIM_TIMA_EXC_NUM]      = (uint32_t)&hrtim_tima_exc_handler,      /** @brief HRTIM timer A interrupt. */
    [HRTIM_TIMB_EXC_NUM]      = (uint32_t)&hrtim_timb_exc_handler,      /** @brief HRTIM timer B interrupt. */
    [HRTIM_TIMC_EXC_NUM]      = (uint32_t)&hrtim_timc_exc_handler,      /** @brief HRTIM timer C interrupt. */
    [HRTIM_TIMD_EXC_NUM]      = (uint32_t)&hrtim_timd_exc_handler,      /** @brief HRTIM timer D interrupt. */
    [HRTIM_TIME_EXC_NUM]      = (uint32_t)&hrtim_time_exc_handler,      /** @brief HRTIM timer E interrupt. */
    [DFSDM1_FLT0_EXC_NUM]     = (uint32_t)&dfsdm1_flt0_exc_handler,     /** @brief DFSDM1 filter 0 interrupt. */
    [DFSDM1_FLT1_EXC_NUM]     = (uint32_t)&dfsdm1_flt1_exc_handler,     /** @brief DFSDM1 filter 1 interrupt. */
    [DFSDM1_FLT2_EXC_NUM]     = (uint32_t)&dfsdm1_flt2_exc_handler,     /** @brief DFSDM1 filter 2 interrupt. */
    [DFSDM1_FLT3_EXC_NUM]     = (uint32_t)&dfsdm1_flt3_exc_handler,     /** @brief DFSDM1 filter 3 interrupt. */
    [TIM16_EXC_NUM]           = (uint32_t)&tim16_exc_handler,           /** @brief TIM16 global interrupt. */
    [TIM17_EXC_NUM]           = (uint32_t)&tim17_exc_handler,           /** @brief TIM17 global interrupt. */
    [TIM15_EXC_NUM]           = (uint32_t)&tim15_exc_handler,           /** @brief TIM15 global interrupt. */
    [USART1_EXC_NUM]          = (uint32_t)&usart1_exc_handler,          /** @brief USART1 global interrupt. */
    [USART2_EXC_NUM]          = (uint32_t)&usart2_exc_handler,          /** @brief USART2 global interrupt. */
    [USART3_EXC_NUM]          = (uint32_t)&usart3_exc_handler,          /** @brief USART3 global interrupt. */
    [UART4_EXC_NUM]           = (uint32_t)&uart4_exc_handler,           /** @brief UART4 global interrupt. */
    [UART5_EXC_NUM]           = (uint32_t)&uart5_exc_handler,           /** @brief UART5 global interrupt. */
    [USART6_EXC_NUM]          = (uint32_t)&usart6_exc_handler,          /** @brief USART6 global interrupt. */
    [UART7_EXC_NUM]           = (uint32_t)&uart7_exc_handler,           /** @brief UART7 global interrupt. */
    [UART8_EXC_NUM]           = (uint32_t)&uart8_exc_handler,           /** @brief UART8 global interrupt. */
    [TIM1_BRK_EXC_NUM]        = (uint32_t)&tim1_brk_exc_handler,        /** @brief TIM1 break interrupt. */
    [TIM1_UP_EXC_NUM]         = (uint32_t)&tim1_up_exc_handler,         /** @brief TIM1 update interrupt. */
    [TIM1_TRG_COM_EXC_NUM]    = (uint32_t)&tim1_trg_com_exc_handler,    /** @brief TIM1 trigger and commutation. */
    [TIM1_CC_EXC_NUM]         = (uint32_t)&tim1_cc_exc_handler,         /** @brief TIM1 capture / compare. */
    [TIM8_BRK_TIM12_EXC_NUM]  = (uint32_t)&tim8_brk_tim12_exc_handler,  /** @brief TIM8 and 12 break global. */
    [TIM8_UP_TIM13_EXC_NUM]   = (uint32_t)&tim8_up_tim13_exc_handler,   /** @brief TIM8 and 13 update global. */
    [TIM8_14_TRG_COM_EXC_NUM] = (uint32_t)&tim8_14_trg_com_exc_handler, /** @brief TIM8 and 14 trigger /commutation and global. */
    [TIM8_CC_EXC_NUM]         = (uint32_t)&tim8_cc_exc_handler,         /** @brief TIM8 capture / compare. */
    [FDCAN1_IT0_EXC_NUM]      = (uint32_t)&fdcan1_it0_exc_handler,      /** @brief FDCAN1 interrupt 0. */
    [FDCAN1_IT1_EXC_NUM]      = (uint32_t)&fdcan1_it1_exc_handler,      /** @brief FDCAN1 interrupt 1. */
    [FDCAN_CAL_EXC_NUM]       = (uint32_t)&fdcan_cal_exc_handler,       /** @brief CAN2TX interrupts. */
    [FDCAN2_IT0_EXC_NUM]      = (uint32_t)&fdcan2_it0_exc_handler,      /** @brief FDCAN2 interrupt 0. */
    [FDCAN2_IT1_EXC_NUM]      = (uint32_t)&fdcan2_it1_exc_handler,      /** @brief FDCAN2 interrupt 1. */
    [MDIOS_WKUP_EXC_NUM]      = (uint32_t)&mdios_wkup_exc_handler,      /** @brief MDIOS wakeup. */
    [MDIOS_EXC_NUM]           = (uint32_t)&mdios_exc_handler,           /** @brief MDIOS global interrupt. */
    [SWPMI1_EXC_NUM]          = (uint32_t)&swpmi1_exc_handler,          /** @brief SWPMI global interrupt. */
    [TIM2_EXC_NUM]            = (uint32_t)&tim2_exc_handler,            /** @brief TIM2 global interrupt. */
    [TIM3_EXC_NUM]            = (uint32_t)&tim3_exc_handler,            /** @brief TIM3 global interrupt. */
    [TIM4_EXC_NUM]            = (uint32_t)&tim4_exc_handler,            /** @brief TIM4 global interrupt. */
    [TIM5_EXC_NUM]            = (uint32_t)&tim5_exc_handler,            /** @brief TIM5 global interrupt. */
    [TIM2_EXC_NUM]            = (uint32_t)&tim2_exc_handler,            /** @brief TIM2 global interrupt. */
    [TIM2_EXC_NUM]            = (uint32_t)&tim2_exc_handler,            /** @brief TIM2 global interrupt. */
    [TIM2_EXC_NUM]            = (uint32_t)&tim2_exc_handler,            /** @brief TIM2 global interrupt. */
    [TIM6_DAC_EXC_NUM]        = (uint32_t)&tim6_dac_exc_handler,        /** @brief TIM6 global interrupt. */
    [TIM7_EXC_NUM]            = (uint32_t)&tim7_exc_handler,            /** @brief TIM7 global interrupt. */
    [FPU_EXC_NUM]             = (uint32_t)&fpu_exc_handler,             /** @brief Floating point unit interrupt. */
  };
  
#ifdef __cplusplus
  } // extern "C"
#endif