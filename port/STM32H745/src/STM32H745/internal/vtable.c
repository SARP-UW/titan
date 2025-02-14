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
 * @brief Contains weak interrupt handlers and the vector table for both cores.
 */

#include <stdint.h>

#ifdef __cplusplus
  extern "C" {
#endif

  /************************************************************************************************
   * Implementation Resources
   ************************************************************************************************/

  // Attribute for exception handler prototypes
  #define _CM7_EXC_ATTR __attribute__((weak, used, section(".cm7_itcm"), alias("_cm7_fallback_exc_handler")))
  #define _CM4_EXC_ATTR __attribute__((weak, used, alias("_cm4_fallback_exc_handler")))

  // Attributes for IRQ handler prototypes
  #define _CM7_IRQ_ATTR __attribute__((weak, used, section(".cm7_itcm"), alias("_cm7_fallback_irq_handler")))
  #define _CM4_IRQ_ATTR __attribute__((weak, used, alias("_cm4_fallback_irq_handler")))

  // Attribute for reset handler (cant be itcm and must be implemented)
  #define _CM7_RST_ATTR __attribute__((weak, used))
  #define _CM4_RST_ATTR __attribute__((weak, used))

  // Fallback exception interrupt handler (CM7 core)
  __attribute__((used, section(".cm7_itcm")))
  void _cm7_fallback_exc_handler() { 
    __asm__ ("BKPT #3"); 
  }

  // Fallback exception interrupt handler (CM4 core)
  __attribute__((used))
  void _cm4_fallback_exc_handler() { 
    __asm__ ("BKPT #3"); 
  }

  // Fallback IRQ interrupt handler (CM7 core)
  __attribute__((used, section(".cm7_itcm")))
  void _cm7_fallback_irq_handler() { 
    __asm__ ("BKPT #4"); 
  }

  // Fallback IRQ interrupt handler (CM4 core)
  __attribute__((used))
  void _cm4_fallback_irq_handler() { 
    __asm__ ("BKPT #4"); 
  }

  // Empty handler (does nothing)
  __attribute__((used))
  void _empty_handler() {
    __asm__ volatile ("NOP");
  }

  /***************************************************************************************************
   * Exception Handler Prototypes
   ***************************************************************************************************/

  /**** CM7 exception handlers ****/

  _CM7_RST_ATTR void cm7_reset_exc_handler();         /** @brief CM7_Reset exception. */
  _CM7_EXC_ATTR void cm7_nmi_exc_handler();           /** @brief CM7_Non-maskable interrupt. */
  _CM7_EXC_ATTR void cm7_hard_fault_exc_handler();    /** @brief CM7_Hard fault. */
  _CM7_EXC_ATTR void cm7_mem_manage_exc_handler();    /** @brief CM7_Memory management fault (MPU). */
  _CM7_EXC_ATTR void cm7_bus_fault_exc_handler();     /** @brief CM7_Bus fault. */
  _CM7_EXC_ATTR void cm7_usage_fault_exc_handler();   /** @brief CM7_Usage fault. */
  _CM7_EXC_ATTR void cm7_svc_exc_handler();           /** @brief CM7_System service call exception. */
  _CM7_EXC_ATTR void cm7_debug_mon_exc_handler();     /** @brief CM7_Debug monitor fault/exception. */
  _CM7_EXC_ATTR void cm7_pendsv_exc_handler();        /** @brief CM7_Pended system service call exception. */
  _CM7_EXC_ATTR void cm7_systick_exc_handler();       /** @brief CM7_SysTick interrupt. */

  /**** CM4 exception handlers ****/

  _CM4_RST_ATTR void cm4_reset_exc_handler();         /** @brief CM4_Reset exception. */
  _CM4_EXC_ATTR void cm4_nmi_exc_handler();           /** @brief CM4_Non-maskable interrupt. */
  _CM4_EXC_ATTR void cm4_hard_fault_exc_handler();    /** @brief CM4_Hard fault. */
  _CM4_EXC_ATTR void cm4_mem_manage_exc_handler();    /** @brief CM4_Memory management fault (MPU). */
  _CM4_EXC_ATTR void cm4_bus_fault_exc_handler();     /** @brief CM4_Bus fault. */
  _CM4_EXC_ATTR void cm4_usage_fault_exc_handler();   /** @brief CM4_Usage fault. */
  _CM4_EXC_ATTR void cm4_svc_exc_handler();           /** @brief CM4_System service call exception. */
  _CM4_EXC_ATTR void cm4_debug_mon_exc_handler();     /** @brief CM4_Debug monitor fault/exception. */
  _CM4_EXC_ATTR void cm4_pendsv_exc_handler();        /** @brief CM4_Pended system service call exception. */
  _CM4_EXC_ATTR void cm4_systick_exc_handler();       /** @brief CM4_SysTick interrupt. */

  /***************************************************************************************************
   * IRQ Handler Prototypes
   ***************************************************************************************************/

  _CM7_IRQ_ATTR void wwdg1_irq_handler();                    /** @brief Window watchdog interrupt (CM7 core). */
  _CM4_IRQ_ATTR void wwdg2_irq_handler();                    /** @brief Window watchdog interrupt (CM4 core). */
  _CM7_IRQ_ATTR void pvd_pvm_irq_handler();                  /** @brief PVD through EXTI line. */
  _CM7_IRQ_ATTR void rtc_tamp_stamp_css_lse_irq_handler();   /** @brief RTC tamper, timestamp. */
  _CM7_IRQ_ATTR void rtc_wkup_irq_handler();                 /** @brief RTC wakeup interrupt. */
  _CM7_IRQ_ATTR void flash_irq_handler();                    /** @brief Flash memory. */
  _CM7_IRQ_ATTR void rcc_irq_handler();                      /** @brief RCC global interrupt. */
  _CM7_IRQ_ATTR void exti0_irq_handler();                    /** @brief EXTI line 0 interrupt. */
  _CM7_IRQ_ATTR void exti1_irq_handler();                    /** @brief EXTI line 1 interrupt. */
  _CM7_IRQ_ATTR void exti2_irq_handler();                    /** @brief EXTI line 2 interrupt. */
  _CM7_IRQ_ATTR void exti3_irq_handler();                    /** @brief EXTI line 3 interrupt. */
  _CM7_IRQ_ATTR void exti4_irq_handler();                    /** @brief EXTI line 4 interrupt. */
  _CM7_IRQ_ATTR void dma_str0_irq_handler();                 /** @brief DMA1 stream0. */
  _CM7_IRQ_ATTR void dma_str1_irq_handler();                 /** @brief DMA1 stream1. */
  _CM7_IRQ_ATTR void dma_str2_irq_handler();                 /** @brief DMA1 stream2. */
  _CM7_IRQ_ATTR void dma_str3_irq_handler();                 /** @brief DMA1 stream3. */
  _CM7_IRQ_ATTR void dma_str4_irq_handler();                 /** @brief DMA1 stream4. */
  _CM7_IRQ_ATTR void dma_str5_irq_handler();                 /** @brief DMA1 stream5. */
  _CM7_IRQ_ATTR void dma_str6_irq_handler();                 /** @brief DMA1 stream6. */
  _CM7_IRQ_ATTR void adc1_2_irq_handler();                   /** @brief ADC1 and ADC2. */
  _CM7_IRQ_ATTR void fdcan1_it0_irq_handler();               /** @brief FDCAN1 interrupt 0. */
  _CM7_IRQ_ATTR void fdcan2_it0_irq_handler();               /** @brief FDCAN2 interrupt 0. */
  _CM7_IRQ_ATTR void fdcan1_it1_irq_handler();               /** @brief FDCAN1 interrupt 1. */
  _CM7_IRQ_ATTR void fdcan2_it1_irq_handler();               /** @brief FDCAN2 interrupt 1. */
  _CM7_IRQ_ATTR void exti9_5_irq_handler();                  /** @brief EXTI line[9:5] interrupts. */
  _CM7_IRQ_ATTR void tim1_brk_irq_handler();                 /** @brief TIM1 break interrupt. */
  _CM7_IRQ_ATTR void tim1_up_irq_handler();                  /** @brief TIM1 update interrupt. */
  _CM7_IRQ_ATTR void tim1_trg_com_irq_handler();             /** @brief TIM1 trigger and commutation. */
  _CM7_IRQ_ATTR void tim1_cc_irq_handler();                  /** @brief TIM1 capture / compare. */
  _CM7_IRQ_ATTR void tim2_irq_handler();                     /** @brief TIM2 global interrupt. */
  _CM7_IRQ_ATTR void tim3_irq_handler();                     /** @brief TIM3 global interrupt. */
  _CM7_IRQ_ATTR void tim4_irq_handler();                     /** @brief TIM4 global interrupt. */
  _CM7_IRQ_ATTR void i2c1_ev_irq_handler();                  /** @brief I2C1 event interrupt. */
  _CM7_IRQ_ATTR void i2c1_er_irq_handler();                  /** @brief I2C1 error interrupt. */
  _CM7_IRQ_ATTR void i2c2_ev_irq_handler();                  /** @brief I2C2 event interrupt. */
  _CM7_IRQ_ATTR void i2c2_er_irq_handler();                  /** @brief I2C2 error interrupt. */
  _CM7_IRQ_ATTR void spi1_irq_handler();                     /** @brief SPI1 global interrupt. */
  _CM7_IRQ_ATTR void spi2_irq_handler();                     /** @brief SPI2 global interrupt. */
  _CM7_IRQ_ATTR void usart1_irq_handler();                   /** @brief USART1 global interrupt. */
  _CM7_IRQ_ATTR void usart2_irq_handler();                   /** @brief USART2 global interrupt. */
  _CM7_IRQ_ATTR void usart3_irq_handler();                   /** @brief USART3 global interrupt. */
  _CM7_IRQ_ATTR void exti15_10_irq_handler();                /** @brief EXTI line[15:10] interrupts. */
  _CM7_IRQ_ATTR void rtc_alarm_irq_handler();                /** @brief RTC alarms (A and B). */
  _CM7_IRQ_ATTR void tim8_brk_tim12_irq_handler();           /** @brief TIM8 and 12 break global. */
  _CM7_IRQ_ATTR void tim8_up_tim13_irq_handler();            /** @brief TIM8 and 13 update global. */
  _CM7_IRQ_ATTR void tim8_trg_com_tim14_irq_handler();       /** @brief TIM8 and 14 trigger /commutation and global. */
  _CM7_IRQ_ATTR void tim8_cc_irq_handler();                  /** @brief TIM8 capture / compare. */
  _CM7_IRQ_ATTR void dma1_str7_irq_handler();                /** @brief DMA1 stream7. */
  _CM7_IRQ_ATTR void fmc_irq_handler();                      /** @brief FMC global interrupt. */
  _CM7_IRQ_ATTR void sdmmc1_irq_handler();                   /** @brief SDMMC global interrupt. */
  _CM7_IRQ_ATTR void tim5_irq_handler();                     /** @brief TIM5 global interrupt. */
  _CM7_IRQ_ATTR void spi3_irq_handler();                     /** @brief SPI3 global interrupt. */
  _CM7_IRQ_ATTR void uart4_irq_handler();                    /** @brief UART4 global interrupt. */
  _CM7_IRQ_ATTR void uart5_irq_handler();                    /** @brief UART5 global interrupt. */
  _CM7_IRQ_ATTR void tim6_dac_irq_handler();                 /** @brief TIM6 global interrupt. */
  _CM7_IRQ_ATTR void tim7_irq_handler();                     /** @brief TIM7 global interrupt. */
  _CM7_IRQ_ATTR void dma2_str0_irq_handler();                /** @brief DMA2 stream0 interrupt. */
  _CM7_IRQ_ATTR void dma2_str1_irq_handler();                /** @brief DMA2 stream1 interrupt. */
  _CM7_IRQ_ATTR void dma2_str2_irq_handler();                /** @brief DMA2 stream2 interrupt. */
  _CM7_IRQ_ATTR void dma2_str3_irq_handler();                /** @brief DMA2 stream3 interrupt. */
  _CM7_IRQ_ATTR void dma2_str4_irq_handler();                /** @brief DMA2 stream4 interrupt. */
  _CM7_IRQ_ATTR void eth_irq_handler();                      /** @brief Ethernet global interrupt. */
  _CM7_IRQ_ATTR void eth_wkup_irq_handler();                 /** @brief Ethernet wakeup through EXTI. */
  _CM7_IRQ_ATTR void fdcan_cal_irq_handler();                /** @brief CAN2TX interrupts. */
  _CM4_IRQ_ATTR void cpu1_sev_it_irq_handler();              /** @brief Arm cortex-m7 (cpu 1) send event interrupt (used by CM4 core). */
  _CM7_IRQ_ATTR void cpu2_sev_it_irq_handler();              /** @brief Arm cortex-m4 (cpu 2) send event interrupt (used by CM7 core). */
  _CM7_IRQ_ATTR void dma2_str5_irq_handler();                /** @brief DMA2 stream5 interrupt. */
  _CM7_IRQ_ATTR void dma2_str6_irq_handler();                /** @brief DMA2 stream6 interrupt. */
  _CM7_IRQ_ATTR void dma2_str7_irq_handler();                /** @brief DMA2 stream7 interrupt. */
  _CM7_IRQ_ATTR void usart6_irq_handler();                   /** @brief USART6 global interrupt. */
  _CM7_IRQ_ATTR void i2c3_ev_irq_handler();                  /** @brief I2C3 event interrupt. */
  _CM7_IRQ_ATTR void i2c3_er_irq_handler();                  /** @brief I2C3 error interrupt. */
  _CM7_IRQ_ATTR void otg_hs_ep1_out_irq_handler();           /** @brief OTG_HS out global interrupt. */
  _CM7_IRQ_ATTR void otg_hs_ep1_in_irq_handler();            /** @brief OTG_HS in global interrupt. */
  _CM7_IRQ_ATTR void otg_hs_wkup_irq_handler();              /** @brief OTG_HS wakeup interrupt. */
  _CM7_IRQ_ATTR void otg_hs_irq_handler();                   /** @brief OTG_HS global interrupt. */
  _CM7_IRQ_ATTR void dcmi_irq_handler();                     /** @brief DCMI global interrupt. */
  _CM7_IRQ_ATTR void cryp_irq_handler();                     /** @brief CRYP global interrupt. */
  _CM7_IRQ_ATTR void hash_rng_irq_handler();                 /** @brief HASH and RNG. */
  _CM7_IRQ_ATTR void cpu1_fpu_irq_handler();                  /** @brief Floating point unit interrupt (CM7 core). */
  _CM4_IRQ_ATTR void cpu2_fpu_irq_handler();                  /** @brief Floating point unit interrupt (CM4 core). */
  _CM7_IRQ_ATTR void uart7_irq_handler();                    /** @brief UART7 global interrupt. */
  _CM7_IRQ_ATTR void uart8_irq_handler();                    /** @brief UART8 global interrupt. */
  _CM7_IRQ_ATTR void spi4_irq_handler();                     /** @brief SPI4 global interrupt. */
  _CM7_IRQ_ATTR void spi5_irq_handler();                     /** @brief SPI5 global interrupt. */
  _CM7_IRQ_ATTR void spi6_irq_handler();                     /** @brief SPI6 global interrupt. */
  _CM7_IRQ_ATTR void sai1_irq_handler();                     /** @brief SAI1 global interrupt. */
  _CM7_IRQ_ATTR void ltdc_irq_handler();                     /** @brief LCD-TFT global interrupt. */
  _CM7_IRQ_ATTR void ltdc_er_irq_handler();                  /** @brief LCD-TFT error interrupt. */
  _CM7_IRQ_ATTR void dma2d_irq_handler();                    /** @brief DMA2D global interrupt. */
  _CM7_IRQ_ATTR void sai2_irq_handler();                     /** @brief SAI2 global interrupt. */
  _CM7_IRQ_ATTR void quadspi_irq_handler();                  /** @brief QuadSPI global interrupt. */
  _CM7_IRQ_ATTR void lptim1_irq_handler();                   /** @brief LPTIM1 global interrupt. */
  _CM7_IRQ_ATTR void cec_irq_handler();                      /** @brief HDMI-CEC global interrupt. */
  _CM7_IRQ_ATTR void i2c4_ev_irq_handler();                  /** @brief I2C4 event interrupt. */
  _CM7_IRQ_ATTR void i2c4_er_irq_handler();                  /** @brief I2C4 error interrupt. */
  _CM7_IRQ_ATTR void spdif_irq_handler();                    /** @brief SPDIFRX global interrupt. */
  _CM7_IRQ_ATTR void otg_fs_ep1_out_irq_handler();           /** @brief OTG_FS out global interrupt. */
  _CM7_IRQ_ATTR void otg_fs_ep1_in_irq_handler();            /** @brief OTG_FS in global interrupt. */
  _CM7_IRQ_ATTR void otg_fs_wkup_irq_handler();              /** @brief OTG_FS wakeup. */
  _CM7_IRQ_ATTR void otg_fs_irq_handler();                   /** @brief OTG_FS global interrupt. */
  _CM7_IRQ_ATTR void dmamux1_ov_irq_handler();               /** @brief DMAMUX1 overrun interrupt. */
  _CM7_IRQ_ATTR void hrtim_mst_irq_handler();                /** @brief HRTIM master timer interrupt. */
  _CM7_IRQ_ATTR void hrtim_tima_irq_handler();               /** @brief HRTIM timer A interrupt. */
  _CM7_IRQ_ATTR void hrtim_timb_irq_handler();               /** @brief HRTIM timer B interrupt. */
  _CM7_IRQ_ATTR void hrtim_timc_irq_handler();               /** @brief HRTIM timer C interrupt. */
  _CM7_IRQ_ATTR void hrtim_timd_irq_handler();               /** @brief HRTIM timer D interrupt. */
  _CM7_IRQ_ATTR void hrtim_time_irq_handler();               /** @brief HRTIM timer E interrupt. */
  _CM7_IRQ_ATTR void hrtim_flt_irq_handler();                /** @brief HRTIM fault interrupt. */
  _CM7_IRQ_ATTR void dfsdm1_flt0_irq_handler();              /** @brief DFSDM1 filter 0 interrupt. */
  _CM7_IRQ_ATTR void dfsdm1_flt1_irq_handler();              /** @brief DFSDM1 filter 1 interrupt. */
  _CM7_IRQ_ATTR void dfsdm1_flt2_irq_handler();              /** @brief DFSDM1 filter 2 interrupt. */
  _CM7_IRQ_ATTR void dfsdm1_flt3_irq_handler();              /** @brief DFSDM1 filter 3 interrupt. */
  _CM7_IRQ_ATTR void sai3_irq_handler();                     /** @brief SAI3 global interrupt. */
  _CM7_IRQ_ATTR void swpmi_irq_handler();                    /** @brief SWPMI global interrupt. */
  _CM7_IRQ_ATTR void tim15_irq_handler();                    /** @brief TIM15 global interrupt. */
  _CM7_IRQ_ATTR void tim16_irq_handler();                    /** @brief TIM16 global interrupt. */
  _CM7_IRQ_ATTR void tim17_irq_handler();                    /** @brief TIM17 global interrupt. */
  _CM7_IRQ_ATTR void mdios_wkup_irq_handler();               /** @brief MDIOS wakeup. */
  _CM7_IRQ_ATTR void mdios_irq_handler();                    /** @brief MDIOS global interrupt. */
  _CM7_IRQ_ATTR void jpeg_irq_handler();                     /** @brief JPEG global interrupt. */
  _CM7_IRQ_ATTR void mdma_irq_handler();                     /** @brief MDMA. */
  _CM7_IRQ_ATTR void sdmmc2_irq_handler();                   /** @brief SDMMC global interrupt. */
  _CM7_IRQ_ATTR void hsem0_irq_handler();                    /** @brief HSEM global interrupt 0 (CM7 core). */
  _CM4_IRQ_ATTR void hsem1_irq_handler();                    /** @brief HSEM global interrupt 1 (CM4 core). */
  _CM7_IRQ_ATTR void adc3_irq_handler();                     /** @brief ADC3 global interrupt. */
  _CM7_IRQ_ATTR void dmamux2_ovr_irq_handler();              /** @brief DMAMUX2 overrun interrupt. */
  _CM7_IRQ_ATTR void bdma_ch1_irq_handler();                 /** @brief BDMA channel 1 interrupt. */
  _CM7_IRQ_ATTR void bdma_ch2_irq_handler();                 /** @brief BDMA channel 2 interrupt. */
  _CM7_IRQ_ATTR void bdma_ch3_irq_handler();                 /** @brief BDMA channel 3 interrupt. */
  _CM7_IRQ_ATTR void bdma_ch4_irq_handler();                 /** @brief BDMA channel 4 interrupt. */
  _CM7_IRQ_ATTR void bdma_ch5_irq_handler();                 /** @brief BDMA channel 5 interrupt. */
  _CM7_IRQ_ATTR void bdma_ch6_irq_handler();                 /** @brief BDMA channel 6 interrupt. */
  _CM7_IRQ_ATTR void bdma_ch7_irq_handler();                 /** @brief BDMA channel 7 interrupt. */
  _CM7_IRQ_ATTR void bdma_ch8_irq_handler();                 /** @brief BDMA channel 8 interrupt. */
  _CM7_IRQ_ATTR void comp_irq_handler();                     /** @brief COMP1 and COMP2. */
  _CM7_IRQ_ATTR void lptim2_irq_handler();                   /** @brief LPTIM2 timer interrupt. */
  _CM7_IRQ_ATTR void lptim3_irq_handler();                   /** @brief LPTIM3 timer interrupt. */
  _CM7_IRQ_ATTR void lptim4_irq_handler();                   /** @brief LPTIM4 timer interrupt. */
  _CM7_IRQ_ATTR void lptim5_irq_handler();                   /** @brief LPTIM5 timer interrupt. */
  _CM7_IRQ_ATTR void lpuart_irq_handler();                   /** @brief LPUART global interrupt. */
  _CM4_IRQ_ATTR void wwdg1_rst_irq_handler();                /** @brief Window watchdog reset interrupt (used by CM4 core). */
  _CM7_IRQ_ATTR void wwdg2_rst_irq_handler();                /** @brief Window watchdog reset interrupt (used by CM7 core). */
  _CM7_IRQ_ATTR void crs_irq_handler();                      /** @brief Clock recovery system global interrupt. */
  _CM7_IRQ_ATTR void sai4_irq_handler();                     /** @brief SAI4 global interrupt. */
  _CM7_IRQ_ATTR void cpu1_hold_core_irq_handler();            /** @brief Hold core interrupt (CM7 core). */
  _CM4_IRQ_ATTR void cpu2_hold_core_irq_handler();            /** @brief Hold core interrupt (CM4 core). */
  _CM7_IRQ_ATTR void wkup_irq_handler();                     /** @brief WKUP1 to WKUP6 pins. */

  /***************************************************************************************************
   * Interrupt Vector Table Definitions
   ***************************************************************************************************/

  /** @brief Interrupt vector table (CM7 core). */
  __attribute__((section(".cm7_vtable")))
  const uint32_t vm7_vtable[255] = {
    [0]   = (uint32_t)&cm7_reset_exc_handler,              /** @brief reset exception (CM7 core). */
    [1]   = (uint32_t)&cm7_nmi_exc_handler,                /** @brief Non-maskable interrupt (CM7 core). */
    [2]   = (uint32_t)&cm7_hard_fault_exc_handler,         /** @brief Hard fault (CM7 core). */
    [3]   = (uint32_t)&cm7_mem_manage_exc_handler,         /** @brief Memory management fault (MPU) (CM7 core). */
    [4]   = (uint32_t)&cm7_bus_fault_exc_handler,          /** @brief Bus fault (CM7 core). */
    [5]   = (uint32_t)&cm7_usage_fault_exc_handler,        /** @brief Usage fault (CM7 core). */
    [10]  = (uint32_t)&cm7_svc_exc_handler,                /** @brief System service call exception (CM7 core). */
    [11]  = (uint32_t)&cm7_debug_mon_exc_handler,          /** @brief Debug monitor fault/exception (CM7 core). */
    [13]  = (uint32_t)&cm7_pendsv_exc_handler,             /** @brief Pended system service call exception (CM7 core). */
    [14]  = (uint32_t)&cm7_systick_exc_handler,            /** @brief SysTick interrupt (CM7 core). */
    [15]  = (uint32_t)&wwdg1_irq_handler,                  /** @brief Window watchdog interrupt (CM7 core). */
    [16]  = (uint32_t)&pvd_pvm_irq_handler,                /** @brief PVD through EXTI line. */
    [17]  = (uint32_t)&rtc_tamp_stamp_css_lse_irq_handler, /** @brief RTC tamper, timestamp. */
    [18]  = (uint32_t)&rtc_wkup_irq_handler,               /** @brief RTC wakeup interrupt. */
    [19]  = (uint32_t)&flash_irq_handler,                  /** @brief Flash memory. */
    [20]  = (uint32_t)&rcc_irq_handler,                    /** @brief RCC global interrupt. */
    [21]  = (uint32_t)&exti0_irq_handler,                  /** @brief EXTI line 0 interrupt. */
    [22]  = (uint32_t)&exti1_irq_handler,                  /** @brief EXTI line 1 interrupt. */
    [23]  = (uint32_t)&exti2_irq_handler,                  /** @brief EXTI line 2 interrupt. */
    [24]  = (uint32_t)&exti3_irq_handler,                  /** @brief EXTI line 3interrupt. */
    [25]  = (uint32_t)&exti4_irq_handler,                  /** @brief EXTI line 4interrupt. */
    [26]  = (uint32_t)&dma_str0_irq_handler,               /** @brief DMA1 stream0. */
    [27]  = (uint32_t)&dma_str1_irq_handler,               /** @brief DMA1 stream1. */
    [28]  = (uint32_t)&dma_str2_irq_handler,               /** @brief DMA1 stream2. */
    [29]  = (uint32_t)&dma_str3_irq_handler,               /** @brief DMA1 stream3. */
    [30]  = (uint32_t)&dma_str4_irq_handler,               /** @brief DMA1 stream4. */
    [31]  = (uint32_t)&dma_str5_irq_handler,               /** @brief DMA1 stream5. */
    [32]  = (uint32_t)&dma_str6_irq_handler,               /** @brief DMA1 stream6. */
    [33]  = (uint32_t)&adc1_2_irq_handler,                 /** @brief ADC1 and ADC2. */
    [34]  = (uint32_t)&fdcan1_it0_irq_handler,             /** @brief FDCAN1 interrupt 0. */
    [35]  = (uint32_t)&fdcan2_it0_irq_handler,             /** @brief FDCAN2 interrupt 0. */
    [36]  = (uint32_t)&fdcan1_it1_irq_handler,             /** @brief FDCAN1 interrupt 1. */
    [37]  = (uint32_t)&fdcan2_it1_irq_handler,             /** @brief FDCAN2 interrupt 1. */
    [38]  = (uint32_t)&exti9_5_irq_handler,                /** @brief EXTI line[9:5] interrupts. */
    [39]  = (uint32_t)&tim1_brk_irq_handler,               /** @brief TIM1 break interrupt. */
    [40]  = (uint32_t)&tim1_up_irq_handler,                /** @brief TIM1 update interrupt. */
    [41]  = (uint32_t)&tim1_trg_com_irq_handler,           /** @brief TIM1 trigger and commutation. */
    [42]  = (uint32_t)&tim1_cc_irq_handler,                /** @brief TIM1 capture / compare. */
    [43]  = (uint32_t)&tim2_irq_handler,                   /** @brief TIM2 global interrupt. */
    [44]  = (uint32_t)&tim3_irq_handler,                   /** @brief TIM3 global interrupt. */
    [45]  = (uint32_t)&tim4_irq_handler,                   /** @brief TIM4 global interrupt. */
    [46]  = (uint32_t)&i2c1_ev_irq_handler,                /** @brief I2C1 event interrupt. */
    [47]  = (uint32_t)&i2c1_er_irq_handler,                /** @brief I2C1 error interrupt. */
    [48]  = (uint32_t)&i2c2_ev_irq_handler,                /** @brief I2C2 event interrupt. */
    [49]  = (uint32_t)&i2c2_er_irq_handler,                /** @brief I2C2 error interrupt. */
    [50]  = (uint32_t)&spi1_irq_handler,                   /** @brief SPI1 global interrupt. */
    [51]  = (uint32_t)&spi2_irq_handler,                   /** @brief SPI2 global interrupt. */
    [52]  = (uint32_t)&usart1_irq_handler,                 /** @brief USART1 global interrupt. */
    [53]  = (uint32_t)&usart2_irq_handler,                 /** @brief USART2 global interrupt. */
    [54]  = (uint32_t)&usart3_irq_handler,                 /** @brief USART3 global interrupt. */
    [55]  = (uint32_t)&exti15_10_irq_handler,              /** @brief EXTI line[15:10] interrupts. */
    [56]  = (uint32_t)&rtc_alarm_irq_handler,              /** @brief RTC alarms (A and B). */
    [58]  = (uint32_t)&tim8_brk_tim12_irq_handler,         /** @brief TIM8 and 12 break global. */
    [59]  = (uint32_t)&tim8_up_tim13_irq_handler,          /** @brief TIM8 and 13 update global. */
    [60]  = (uint32_t)&tim8_trg_com_tim14_irq_handler,     /** @brief TIM8 and 14 trigger /commutation and global. */
    [61]  = (uint32_t)&tim8_cc_irq_handler,                /** @brief TIM8 capture / compare. */
    [62]  = (uint32_t)&dma1_str7_irq_handler,              /** @brief DMA1 stream7. */
    [63]  = (uint32_t)&fmc_irq_handler,                    /** @brief FMC global interrupt. */
    [64]  = (uint32_t)&sdmmc1_irq_handler,                 /** @brief SDMMC global interrupt. */
    [65]  = (uint32_t)&tim5_irq_handler,                   /** @brief TIM5 global interrupt. */
    [66]  = (uint32_t)&spi3_irq_handler,                   /** @brief SPI3 global interrupt. */
    [67]  = (uint32_t)&uart4_irq_handler,                  /** @brief UART4 global interrupt. */
    [68]  = (uint32_t)&uart5_irq_handler,                  /** @brief UART5 global interrupt. */
    [69]  = (uint32_t)&tim6_dac_irq_handler,               /** @brief TIM6 global interrupt. */
    [70]  = (uint32_t)&tim7_irq_handler,                   /** @brief TIM7 global interrupt. */
    [71]  = (uint32_t)&dma2_str0_irq_handler,              /** @brief DMA2 stream0 interrupt. */
    [72]  = (uint32_t)&dma2_str1_irq_handler,              /** @brief DMA2 stream1 interrupt. */
    [73]  = (uint32_t)&dma2_str2_irq_handler,              /** @brief DMA2 stream2 interrupt. */
    [74]  = (uint32_t)&dma2_str3_irq_handler,              /** @brief DMA2 stream3 interrupt. */
    [75]  = (uint32_t)&dma2_str4_irq_handler,              /** @brief DMA2 stream4 interrupt. */
    [76]  = (uint32_t)&eth_irq_handler,                    /** @brief Ethernet global interrupt. */
    [77]  = (uint32_t)&eth_wkup_irq_handler,               /** @brief Ethernet wakeup through EXTI. */
    [78]  = (uint32_t)&fdcan_cal_irq_handler,              /** @brief CAN2TX interrupts. */
    [80]  = (uint32_t)&cpu2_sev_it_irq_handler,            /** @brief Arm cortex-m4 send even interrupt (used by CM7 core). */
    [83]  = (uint32_t)&dma2_str5_irq_handler,              /** @brief DMA2 stream5 interrupt. */
    [84]  = (uint32_t)&dma2_str6_irq_handler,              /** @brief DMA2 stream6 interrupt. */
    [85]  = (uint32_t)&dma2_str7_irq_handler,              /** @brief DMA2 stream7 interrupt. */
    [86]  = (uint32_t)&usart6_irq_handler,                 /** @brief USART6 global interrupt. */
    [87]  = (uint32_t)&i2c3_ev_irq_handler,                /** @brief I2C3 event interrupt. */
    [88]  = (uint32_t)&i2c3_er_irq_handler,                /** @brief I2C3 error interrupt. */
    [89]  = (uint32_t)&otg_hs_ep1_out_irq_handler,         /** @brief OTG_HS out global interrupt. */
    [90]  = (uint32_t)&otg_hs_ep1_in_irq_handler,          /** @brief OTG_HS in global interrupt. */
    [91]  = (uint32_t)&otg_hs_wkup_irq_handler,            /** @brief OTG_HS wakeup interrupt. */
    [92]  = (uint32_t)&otg_hs_irq_handler,                 /** @brief OTG_HS global interrupt. */
    [93]  = (uint32_t)&dcmi_irq_handler,                   /** @brief DCMI global interrupt. */
    [94]  = (uint32_t)&cryp_irq_handler,                   /** @brief CRYP global interrupt. */
    [95]  = (uint32_t)&hash_rng_irq_handler,               /** @brief HASH and RNG. */
    [96]  = (uint32_t)&cpu1_fpu_irq_handler,                /** @brief Floating point unit interrupt (CM7 core). */
    [97]  = (uint32_t)&uart7_irq_handler,                  /** @brief UART7 global interrupt. */
    [98]  = (uint32_t)&uart8_irq_handler,                  /** @brief UART8 global interrupt. */
    [99]  = (uint32_t)&spi4_irq_handler,                   /** @brief SPI4 global interrupt. */
    [100] = (uint32_t)&spi5_irq_handler,                   /** @brief SPI5 global interrupt. */
    [101] = (uint32_t)&spi6_irq_handler,                   /** @brief SPI6 global interrupt. */
    [102] = (uint32_t)&sai1_irq_handler,                   /** @brief SAI1 global interrupt. */
    [103] = (uint32_t)&ltdc_irq_handler,                   /** @brief LCD-TFT global interrupt. */
    [104] = (uint32_t)&ltdc_er_irq_handler,                /** @brief LCD-TFT error interrupt. */
    [105] = (uint32_t)&dma2d_irq_handler,                  /** @brief DMA2D global interrupt. */
    [106] = (uint32_t)&sai2_irq_handler,                   /** @brief SAI2 global interrupt. */
    [107] = (uint32_t)&quadspi_irq_handler,                /** @brief QuadSPI global interrupt. */
    [108] = (uint32_t)&lptim1_irq_handler,                 /** @brief LPTIM1 global interrupt. */
    [109] = (uint32_t)&cec_irq_handler,                    /** @brief HDMI-CEC global interrupt. */
    [110] = (uint32_t)&i2c4_ev_irq_handler,                /** @brief I2C4 event interrupt. */
    [111] = (uint32_t)&i2c4_er_irq_handler,                /** @brief I2C4 error interrupt. */
    [112] = (uint32_t)&spdif_irq_handler,                  /** @brief SPDIFRX global interrupt. */
    [113] = (uint32_t)&otg_fs_ep1_out_irq_handler,         /** @brief OTG_FS out global interrupt. */
    [114] = (uint32_t)&otg_fs_ep1_in_irq_handler,          /** @brief OTG_FS in global interrupt. */
    [115] = (uint32_t)&otg_fs_wkup_irq_handler,            /** @brief OTG_FS wakeup. */
    [116] = (uint32_t)&otg_fs_irq_handler,                 /** @brief OTG_FS global interrupt. */
    [117] = (uint32_t)&dmamux1_ov_irq_handler,             /** @brief DMAMUX1 overrun interrupt. */
    [118] = (uint32_t)&hrtim_mst_irq_handler,              /** @brief HRTIM master timer interrupt. */
    [119] = (uint32_t)&hrtim_tima_irq_handler,             /** @brief HRTIM timer A interrupt. */
    [120] = (uint32_t)&hrtim_timb_irq_handler,             /** @brief HRTIM timer B interrupt. */
    [121] = (uint32_t)&hrtim_timc_irq_handler,             /** @brief HRTIM timer C interrupt. */
    [122] = (uint32_t)&hrtim_timd_irq_handler,             /** @brief HRTIM timer D interrupt. */
    [123] = (uint32_t)&hrtim_time_irq_handler,             /** @brief HRTIM timer E interrupt. */
    [124] = (uint32_t)&hrtim_flt_irq_handler,              /** @brief HRTIM fault interrupt. */
    [125] = (uint32_t)&dfsdm1_flt0_irq_handler,            /** @brief DFSDM1 filter 0 interrupt. */
    [126] = (uint32_t)&dfsdm1_flt1_irq_handler,            /** @brief DFSDM1 filter 1 interrupt. */
    [127] = (uint32_t)&dfsdm1_flt2_irq_handler,            /** @brief DFSDM1 filter 2 interrupt. */
    [128] = (uint32_t)&dfsdm1_flt3_irq_handler,            /** @brief DFSDM1 filter 3 interrupt. */
    [129] = (uint32_t)&sai3_irq_handler,                   /** @brief SAI3 global interrupt. */
    [130] = (uint32_t)&swpmi_irq_handler,                  /** @brief SWPMI global interrupt. */
    [131] = (uint32_t)&tim15_irq_handler,                  /** @brief TIM15 global interrupt. */
    [132] = (uint32_t)&tim16_irq_handler,                  /** @brief TIM16 global interrupt. */
    [133] = (uint32_t)&tim17_irq_handler,                  /** @brief TIM17 global interrupt. */
    [134] = (uint32_t)&mdios_wkup_irq_handler,             /** @brief MDIOS wakeup. */
    [135] = (uint32_t)&mdios_irq_handler,                  /** @brief MDIOS global interrupt. */
    [136] = (uint32_t)&jpeg_irq_handler,                   /** @brief JPEG global interrupt. */
    [137] = (uint32_t)&mdma_irq_handler,                   /** @brief MDMA. */
    [139] = (uint32_t)&sdmmc2_irq_handler,                 /** @brief SDMMC global interrupt. */
    [140] = (uint32_t)&hsem0_irq_handler,                  /** @brief HSEM global interrupt 1 (CM7 core). */
    [142] = (uint32_t)&adc3_irq_handler,                   /** @brief ADC3 global interrupt. */
    [143] = (uint32_t)&dmamux2_ovr_irq_handler,            /** @brief DMAMUX2 overrun interrupt. */
    [144] = (uint32_t)&bdma_ch1_irq_handler,               /** @brief BDMA channel 1 interrupt. */
    [145] = (uint32_t)&bdma_ch2_irq_handler,               /** @brief BDMA channel 2 interrupt. */
    [146] = (uint32_t)&bdma_ch3_irq_handler,               /** @brief BDMA channel 3 interrupt. */
    [147] = (uint32_t)&bdma_ch4_irq_handler,               /** @brief BDMA channel 4 interrupt. */
    [148] = (uint32_t)&bdma_ch5_irq_handler,               /** @brief BDMA channel 5 interrupt. */
    [149] = (uint32_t)&bdma_ch6_irq_handler,               /** @brief BDMA channel 6 interrupt. */
    [150] = (uint32_t)&bdma_ch7_irq_handler,               /** @brief BDMA channel 7 interrupt. */
    [151] = (uint32_t)&bdma_ch8_irq_handler,               /** @brief BDMA channel 8 interrupt. */
    [152] = (uint32_t)&comp_irq_handler,                   /** @brief COMP1 and COMP2. */
    [153] = (uint32_t)&lptim2_irq_handler,                 /** @brief LPTIM2 timer interrupt. */
    [154] = (uint32_t)&lptim3_irq_handler,                 /** @brief LPTIM2 timer interrupt. */
    [155] = (uint32_t)&lptim4_irq_handler,                 /** @brief LPTIM2 timer interrupt. */
    [156] = (uint32_t)&lptim5_irq_handler,                 /** @brief LPTIM2 timer interrupt. */
    [157] = (uint32_t)&lpuart_irq_handler,                 /** @brief LPUART global interrupt. */
    [158] = (uint32_t)&wwdg2_rst_irq_handler,              /** @brief Window watchdog reset interrupt (used by CM7 core). */
    [159] = (uint32_t)&crs_irq_handler,                    /** @brief Clock recovery system global interrupt. */
    [161] = (uint32_t)&sai4_irq_handler,                   /** @brief SAI4 global interrupt. */
    [163] = (uint32_t)&cpu1_hold_core_irq_handler,          /** @brief Hold core interrupt (CM7 core). */
    [164] = (uint32_t)&wkup_irq_handler,                   /** @brief WKUP1 to WKUP6 pins. */
  };

  /** @brief Interrupt vector table (CM4 core) */
  __attribute__((used, section(".cm4_vtable")))
  const uint32_t cm4_vtable[255] = {
    [0]   = (uint32_t)&cm4_reset_exc_handler,       /** @brief Reset exception (CM4 core). */
    [1]   = (uint32_t)&cm4_nmi_exc_handler,         /** @brief Non-maskable interrupt (CM4 core). */
    [2]   = (uint32_t)&cm4_hard_fault_exc_handler,  /** @brief Hard fault (CM4 core). */
    [3]   = (uint32_t)&cm4_mem_manage_exc_handler,  /** @brief Memory management fault (MPU) (CM4 core). */
    [4]   = (uint32_t)&cm4_bus_fault_exc_handler,   /** @brief Bus fault (CM4 core). */
    [5]   = (uint32_t)&cm4_usage_fault_exc_handler, /** @brief Usage fault (CM4 core). */
    [10]  = (uint32_t)&cm4_svc_exc_handler,         /** @brief System service call exception (CM4 core). */
    [11]  = (uint32_t)&cm4_debug_mon_exc_handler,   /** @brief Debug monitor fault/exception (CM4 core). */
    [13]  = (uint32_t)&cm4_pendsv_exc_handler,      /** @brief Pended system service call exception (CM4 core). */
    [14]  = (uint32_t)&cm4_systick_exc_handler,     /** @brief SysTick interrupt (CM4 core). */
    [15]  = (uint32_t)&wwdg2_irq_handler,           /** @brief Window watchdog interrupt (CM4 core). */
    [16]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [17]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [18]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [19]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [20]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [21]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [22]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [23]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [24]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [25]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [26]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [27]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [28]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [29]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [30]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [31]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [32]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [33]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [34]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [35]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [36]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [37]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [38]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [39]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [40]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [41]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [42]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [43]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [44]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [45]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [46]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [47]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [48]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [49]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [50]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [51]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [52]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [53]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [54]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [55]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [56]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [58]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [59]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [60]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [61]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [62]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [63]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [64]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [65]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [66]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [67]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [68]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [69]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [70]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [71]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [72]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [73]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [74]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [75]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [76]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [77]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [78]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [79]  = (uint32_t)&cpu1_sev_it_irq_handler,     /** @brief Arm cortex-m7 (cpu 1) send event interrupt (used by CM4 core). */
    [83]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [84]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [85]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [86]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [87]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [88]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [89]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [90]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [91]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [92]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [93]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [94]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [95]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [96]  = (uint32_t)&cpu2_fpu_irq_handler,         /** @brief Floating point unit interrupt (CM4 core). */
    [97]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [98]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [99]  = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [100] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [101] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [102] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [103] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [104] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [105] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [106] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [107] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [108] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [109] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [110] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [111] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [112] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [113] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [114] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [115] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [116] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [117] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [118] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [119] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [120] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [121] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [122] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [123] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [124] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [125] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [126] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [127] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [128] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [129] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [130] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [131] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [132] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [133] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [134] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [135] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [136] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [137] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [139] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [141] = (uint32_t)&hsem1_irq_handler,           /** @brief HSEM global interrupt 1 (CM4 core). */
    [142] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [143] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [144] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [145] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [146] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [147] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [148] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [149] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [150] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [151] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [152] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [153] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [154] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [155] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [156] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [157] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [158] = (uint32_t)&wwdg1_rst_irq_handler,       /** @brief Window watchdog reset interrupt (used by CM4 core). */
    [159] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [161] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
    [163] = (uint32_t)&cpu2_hold_core_irq_handler,   /** @brief Hold core interrupt (CM4 core). */
    [164] = (uint32_t)&_empty_handler,              /** @brief Not implemented (handler is nop) */
  };

#ifdef __cplusplus
  } // extern "C"
#endif

/** @endinternal */