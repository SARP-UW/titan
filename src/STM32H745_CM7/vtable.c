/**
 * This file is part of the Titan HAL
 * Copyright (c) 2025 UW SARP
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
 * @file src/STM32H745_CM7/vtable.c
 * @authors Aaron McBride
 * @brief Contains the interrupt vector table.
 */

#pragma once
#include <stdint.h>

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Implementation Resources
   ************************************************************************************************/

  // Attributes for exception handler prototypes
  #define _EXC_ATTR __attribute__((weak, used, alias("_default_exc_handler")))

  // Attributes for IRQ handler prototypes
  #define _IRQ_ATTR __attribute__((weak, used, alias("_default_irq_handler")))

  // Fallback exception interrupt handler
  void _default_exc_handler() { __asm__ ("BKPT #3"); }

  // Fallback IRQ interrupt handler
  void _default_irq_handler() { __asm__ ("BKPT #4"); }

  /***************************************************************************************************
   * Exception Handler Prototypes
   ***************************************************************************************************/

  _EXC_ATTR void reset_exc_handler();         /** @brief Reset exception. */
  _EXC_ATTR void nmi_exc_handler();           /** @brief Non-maskable interrupt. */
  _EXC_ATTR void hard_fault_exc_handler();    /** @brief Hard fault. */
  _EXC_ATTR void mem_manage_exc_handler();    /** @brief Memory management fault (MPU). */
  _EXC_ATTR void bus_fault_exc_handler();     /** @brief Bus fault. */
  _EXC_ATTR void usage_fault_exc_handler();   /** @brief Usage fault. */
  _EXC_ATTR void svc_exc_handler();           /** @brief System service call exception. */
  _EXC_ATTR void debug_mon_exc_handler();     /** @brief Debug monitor fault/exception. */
  _EXC_ATTR void pendsv_exc_handler();        /** @brief Pended system service call exception. */
  _EXC_ATTR void systick_exc_handler();       /** @brief SysTick interrupt. */

  /***************************************************************************************************
   * IRQ Handler Prototypes
   ***************************************************************************************************/

  _IRQ_ATTR void wwdg1_irq_handler();                    /** @brief Window watchdog interrupt. */
  _IRQ_ATTR void pvd_pvm_irq_handler();                  /** @brief PVD through EXTI line. */
  _IRQ_ATTR void rtc_tamp_stamp_css_lse_irq_handler();   /** @brief RTC tamper, timestamp. */
  _IRQ_ATTR void rtc_wkup_irq_handler();                 /** @brief RTC wakeup interrupt. */
  _IRQ_ATTR void flash_irq_handler();                    /** @brief Flash memory. */
  _IRQ_ATTR void rcc_irq_handler();                      /** @brief RCC global interrupt. */
  _IRQ_ATTR void exti0_irq_handler();                    /** @brief EXTI line 0 interrupt. */
  _IRQ_ATTR void exti1_irq_handler();                    /** @brief EXTI line 1 interrupt. */
  _IRQ_ATTR void exti2_irq_handler();                    /** @brief EXTI line 2 interrupt. */
  _IRQ_ATTR void exti3_irq_handler();                    /** @brief EXTI line 3 interrupt. */
  _IRQ_ATTR void exti4_irq_handler();                    /** @brief EXTI line 4 interrupt. */
  _IRQ_ATTR void dma_str0_irq_handler();                 /** @brief DMA1 stream0. */
  _IRQ_ATTR void dma_str1_irq_handler();                 /** @brief DMA1 stream1. */
  _IRQ_ATTR void dma_str2_irq_handler();                 /** @brief DMA1 stream2. */
  _IRQ_ATTR void dma_str3_irq_handler();                 /** @brief DMA1 stream3. */
  _IRQ_ATTR void dma_str4_irq_handler();                 /** @brief DMA1 stream4. */
  _IRQ_ATTR void dma_str5_irq_handler();                 /** @brief DMA1 stream5. */
  _IRQ_ATTR void dma_str6_irq_handler();                 /** @brief DMA1 stream6. */
  _IRQ_ATTR void adc1_2_irq_handler();                   /** @brief ADC1 and ADC2. */
  _IRQ_ATTR void fdcan1_it0_irq_handler();               /** @brief FDCAN1 interrupt 0. */
  _IRQ_ATTR void fdcan2_it0_irq_handler();               /** @brief FDCAN2 interrupt 0. */
  _IRQ_ATTR void fdcan1_it1_irq_handler();               /** @brief FDCAN1 interrupt 1. */
  _IRQ_ATTR void fdcan2_it1_irq_handler();               /** @brief FDCAN2 interrupt 1. */
  _IRQ_ATTR void exti9_5_irq_handler();                  /** @brief EXTI line[9:5] interrupts. */
  _IRQ_ATTR void tim1_brk_irq_handler();                 /** @brief TIM1 break interrupt. */
  _IRQ_ATTR void tim1_up_irq_handler();                  /** @brief TIM1 update interrupt. */
  _IRQ_ATTR void tim1_trg_com_irq_handler();             /** @brief TIM1 trigger and commutation. */
  _IRQ_ATTR void tim1_cc_irq_handler();                  /** @brief TIM1 capture / compare. */
  _IRQ_ATTR void tim2_irq_handler();                     /** @brief TIM2 global interrupt. */
  _IRQ_ATTR void tim3_irq_handler();                     /** @brief TIM3 global interrupt. */
  _IRQ_ATTR void tim4_irq_handler();                     /** @brief TIM4 global interrupt. */
  _IRQ_ATTR void i2c1_ev_irq_handler();                  /** @brief I2C1 event interrupt. */
  _IRQ_ATTR void i2c1_er_irq_handler();                  /** @brief I2C1 error interrupt. */
  _IRQ_ATTR void i2c2_ev_irq_handler();                  /** @brief I2C2 event interrupt. */
  _IRQ_ATTR void i2c2_er_irq_handler();                  /** @brief I2C2 error interrupt. */
  _IRQ_ATTR void spi1_irq_handler();                     /** @brief SPI1 global interrupt. */
  _IRQ_ATTR void spi2_irq_handler();                     /** @brief SPI2 global interrupt. */
  _IRQ_ATTR void usart1_irq_handler();                   /** @brief USART1 global interrupt. */
  _IRQ_ATTR void usart2_irq_handler();                   /** @brief USART2 global interrupt. */
  _IRQ_ATTR void usart3_irq_handler();                   /** @brief USART3 global interrupt. */
  _IRQ_ATTR void exti15_10_irq_handler();                /** @brief EXTI line[15:10] interrupts. */
  _IRQ_ATTR void rtc_alarm_irq_handler();                /** @brief RTC alarms (A and B). */
  _IRQ_ATTR void tim8_brk_tim12_irq_handler();           /** @brief TIM8 and 12 break global. */
  _IRQ_ATTR void tim8_up_tim13_irq_handler();            /** @brief TIM8 and 13 update global. */
  _IRQ_ATTR void tim8_trg_com_tim14_irq_handler();       /** @brief TIM8 and 14 trigger /commutation and global. */
  _IRQ_ATTR void tim8_cc_irq_handler();                  /** @brief TIM8 capture / compare. */
  _IRQ_ATTR void dma1_str7_irq_handler();                /** @brief DMA1 stream7. */
  _IRQ_ATTR void fmc_irq_handler();                      /** @brief FMC global interrupt. */
  _IRQ_ATTR void sdmmc1_irq_handler();                   /** @brief SDMMC global interrupt. */
  _IRQ_ATTR void tim5_irq_handler();                     /** @brief TIM5 global interrupt. */
  _IRQ_ATTR void spi3_irq_handler();                     /** @brief SPI3 global interrupt. */
  _IRQ_ATTR void uart4_irq_handler();                    /** @brief UART4 global interrupt. */
  _IRQ_ATTR void uart5_irq_handler();                    /** @brief UART5 global interrupt. */
  _IRQ_ATTR void tim6_dac_irq_handler();                 /** @brief TIM6 global interrupt. */
  _IRQ_ATTR void tim7_irq_handler();                     /** @brief TIM7 global interrupt. */
  _IRQ_ATTR void dma2_str0_irq_handler();                /** @brief DMA2 stream0 interrupt. */
  _IRQ_ATTR void dma2_str1_irq_handler();                /** @brief DMA2 stream1 interrupt. */
  _IRQ_ATTR void dma2_str2_irq_handler();                /** @brief DMA2 stream2 interrupt. */
  _IRQ_ATTR void dma2_str3_irq_handler();                /** @brief DMA2 stream3 interrupt. */
  _IRQ_ATTR void dma2_str4_irq_handler();                /** @brief DMA2 stream4 interrupt. */
  _IRQ_ATTR void eth_irq_handler();                      /** @brief Ethernet global interrupt. */
  _IRQ_ATTR void eth_wkup_irq_handler();                 /** @brief Ethernet wakeup through EXTI. */
  _IRQ_ATTR void fdcan_cal_irq_handler();                /** @brief CAN2TX interrupts. */
  _IRQ_ATTR void cm4_sev_it_irq_handler();               /** @brief Arm cortex-m4 send even interrupt. */
  _IRQ_ATTR void dma2_str5_irq_handler();                /** @brief DMA2 stream5 interrupt. */
  _IRQ_ATTR void dma2_str6_irq_handler();                /** @brief DMA2 stream6 interrupt. */
  _IRQ_ATTR void dma2_str7_irq_handler();                /** @brief DMA2 stream7 interrupt. */
  _IRQ_ATTR void usart6_irq_handler();                   /** @brief USART6 global interrupt. */
  _IRQ_ATTR void i2c3_ev_irq_handler();                  /** @brief I2C3 event interrupt. */
  _IRQ_ATTR void i2c3_er_irq_handler();                  /** @brief I2C3 error interrupt. */
  _IRQ_ATTR void otg_hs_ep1_out_irq_handler();           /** @brief OTG_HS out global interrupt. */
  _IRQ_ATTR void otg_hs_ep1_in_irq_handler();            /** @brief OTG_HS in global interrupt. */
  _IRQ_ATTR void otg_hs_wkup_irq_handler();              /** @brief OTG_HS wakeup interrupt. */
  _IRQ_ATTR void otg_hs_irq_handler();                   /** @brief OTG_HS global interrupt. */
  _IRQ_ATTR void dcmi_irq_handler();                     /** @brief DCMI global interrupt. */
  _IRQ_ATTR void cryp_irq_handler();                     /** @brief CRYP global interrupt. */
  _IRQ_ATTR void hash_rng_irq_handler();                 /** @brief HASH and RNG. */
  _IRQ_ATTR void fpu_irq_handler();                      /** @brief Floating point unit interrupt. */
  _IRQ_ATTR void uart7_irq_handler();                    /** @brief UART7 global interrupt. */
  _IRQ_ATTR void uart8_irq_handler();                    /** @brief UART8 global interrupt. */
  _IRQ_ATTR void spi4_irq_handler();                     /** @brief SPI4 global interrupt. */
  _IRQ_ATTR void spi5_irq_handler();                     /** @brief SPI5 global interrupt. */
  _IRQ_ATTR void spi6_irq_handler();                     /** @brief SPI6 global interrupt. */
  _IRQ_ATTR void sai1_irq_handler();                     /** @brief SAI1 global interrupt. */
  _IRQ_ATTR void ltdc_irq_handler();                     /** @brief LCD-TFT global interrupt. */
  _IRQ_ATTR void ltdc_er_irq_handler();                  /** @brief LCD-TFT error interrupt. */
  _IRQ_ATTR void dma2d_irq_handler();                    /** @brief DMA2D global interrupt. */
  _IRQ_ATTR void sai2_irq_handler();                     /** @brief SAI2 global interrupt. */
  _IRQ_ATTR void quadspi_irq_handler();                  /** @brief QuadSPI global interrupt. */
  _IRQ_ATTR void lptim1_irq_handler();                   /** @brief LPTIM1 global interrupt. */
  _IRQ_ATTR void cec_irq_handler();                      /** @brief HDMI-CEC global interrupt. */
  _IRQ_ATTR void i2c4_ev_irq_handler();                  /** @brief I2C4 event interrupt. */
  _IRQ_ATTR void i2c4_er_irq_handler();                  /** @brief I2C4 error interrupt. */
  _IRQ_ATTR void spdif_irq_handler();                    /** @brief SPDIFRX global interrupt. */
  _IRQ_ATTR void otg_fs_ep1_out_irq_handler();           /** @brief OTG_FS out global interrupt. */
  _IRQ_ATTR void otg_fs_ep1_in_irq_handler();            /** @brief OTG_FS in global interrupt. */
  _IRQ_ATTR void otg_fs_wkup_irq_handler();              /** @brief OTG_FS wakeup. */
  _IRQ_ATTR void otg_fs_irq_handler();                   /** @brief OTG_FS global interrupt. */
  _IRQ_ATTR void dmamux1_ov_irq_handler();               /** @brief DMAMUX1 overrun interrupt. */
  _IRQ_ATTR void hrtim_mst_irq_handler();                /** @brief HRTIM master timer interrupt. */
  _IRQ_ATTR void hrtim_tima_irq_handler();               /** @brief HRTIM timer A interrupt. */
  _IRQ_ATTR void hrtim_timb_irq_handler();               /** @brief HRTIM timer B interrupt. */
  _IRQ_ATTR void hrtim_timc_irq_handler();               /** @brief HRTIM timer C interrupt. */
  _IRQ_ATTR void hrtim_timd_irq_handler();               /** @brief HRTIM timer D interrupt. */
  _IRQ_ATTR void hrtim_time_irq_handler();               /** @brief HRTIM timer E interrupt. */
  _IRQ_ATTR void hrtim_flt_irq_handler();                /** @brief HRTIM fault interrupt. */
  _IRQ_ATTR void dfsdm1_flt0_irq_handler();              /** @brief DFSDM1 filter 0 interrupt. */
  _IRQ_ATTR void dfsdm1_flt1_irq_handler();              /** @brief DFSDM1 filter 1 interrupt. */
  _IRQ_ATTR void dfsdm1_flt2_irq_handler();              /** @brief DFSDM1 filter 2 interrupt. */
  _IRQ_ATTR void dfsdm1_flt3_irq_handler();              /** @brief DFSDM1 filter 3 interrupt. */
  _IRQ_ATTR void sai3_irq_handler();                     /** @brief SAI3 global interrupt. */
  _IRQ_ATTR void swpmi_irq_handler();                    /** @brief SWPMI global interrupt. */
  _IRQ_ATTR void tim15_irq_handler();                    /** @brief TIM15 global interrupt. */
  _IRQ_ATTR void tim16_irq_handler();                    /** @brief TIM16 global interrupt. */
  _IRQ_ATTR void tim17_irq_handler();                    /** @brief TIM17 global interrupt. */
  _IRQ_ATTR void mdios_wkup_irq_handler();               /** @brief MDIOS wakeup. */
  _IRQ_ATTR void mdios_irq_handler();                    /** @brief MDIOS global interrupt. */
  _IRQ_ATTR void jpeg_irq_handler();                     /** @brief JPEG global interrupt. */
  _IRQ_ATTR void mdma_irq_handler();                     /** @brief MDMA. */
  _IRQ_ATTR void sdmmc2_irq_handler();                   /** @brief SDMMC global interrupt. */
  _IRQ_ATTR void hsem0_irq_handler();                    /** @brief HSEM global interrupt 0. */
  _IRQ_ATTR void adc3_irq_handler();                     /** @brief ADC3 global interrupt. */
  _IRQ_ATTR void dmamux2_ovr_irq_handler();              /** @brief DMAMUX2 overrun interrupt. */
  _IRQ_ATTR void bdma_ch1_irq_handler();                 /** @brief BDMA channel 1 interrupt. */
  _IRQ_ATTR void bdma_ch2_irq_handler();                 /** @brief BDMA channel 2 interrupt. */
  _IRQ_ATTR void bdma_ch3_irq_handler();                 /** @brief BDMA channel 3 interrupt. */
  _IRQ_ATTR void bdma_ch4_irq_handler();                 /** @brief BDMA channel 4 interrupt. */
  _IRQ_ATTR void bdma_ch5_irq_handler();                 /** @brief BDMA channel 5 interrupt. */
  _IRQ_ATTR void bdma_ch6_irq_handler();                 /** @brief BDMA channel 6 interrupt. */
  _IRQ_ATTR void bdma_ch7_irq_handler();                 /** @brief BDMA channel 7 interrupt. */
  _IRQ_ATTR void bdma_ch8_irq_handler();                 /** @brief BDMA channel 8 interrupt. */
  _IRQ_ATTR void comp_irq_handler();                     /** @brief COMP1 and COMP2. */
  _IRQ_ATTR void lptim2_irq_handler();                   /** @brief LPTIM2 timer interrupt. */
  _IRQ_ATTR void lptim3_irq_handler();                   /** @brief LPTIM3 timer interrupt. */
  _IRQ_ATTR void lptim4_irq_handler();                   /** @brief LPTIM4 timer interrupt. */
  _IRQ_ATTR void lptim5_irq_handler();                   /** @brief LPTIM5 timer interrupt. */
  _IRQ_ATTR void lpuart_irq_handler();                   /** @brief LPUART global interrupt. */
  _IRQ_ATTR void wwdg2_rst_irq_handler();                /** @brief Window watchdog reset interrupt. */
  _IRQ_ATTR void crs_irq_handler();                      /** @brief Clock recovery system globa. */
  _IRQ_ATTR void sai4_irq_handler();                     /** @brief SAI4 global interrupt. */
  _IRQ_ATTR void hold_core_irq_handler();                /** @brief Hold core interrupt. */
  _IRQ_ATTR void wkup_irq_handler();                     /** @brief WKUP1 to WKUP6 pins. */

  /***************************************************************************************************
   * Interrupt Vector Table Definition
   ***************************************************************************************************/

  /** @brief Interrupt vector table. */
  __attribute__((section(".vtable")))
  const uint32_t vtable[165] = {
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