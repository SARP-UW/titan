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
 * @file src/port/GCC_STM32H745ZI/device/interrupt.h
 * @authors Aaron McBride
 * @brief Interrupt vector table and function definitions.
 */

#ifndef SRC_PORT_GCC_STM32H745ZI_DEVICE_INTERRUPT_H
#define SRC_PORT_GCC_STM32H745ZI_DEVICE_INTERRUPT_H

  #include <stdint.h>
  #include <stddef.h>

  #if defined(__cplusplus)
    extern "C" {
  #endif

    /**********************************************************************************************
     * @section Implementation Resources
     **********************************************************************************************/

    /* attribute for interrupt functions */
    #define __IT_ATTR __attribute__((interrupt, weak))

    /* linker symbol - end of stack section for CM7 core */
    extern uint32_t __cm7_stack_end;

    /* linker symbol - end of stack section for CM4 core */
    extern uint32_t __cm4_stack_end;

    /**********************************************************************************************
     * @section IRQ Number Enumeration
     **********************************************************************************************/

    /**
     * @brief Enumeration of IRQ interrupts according to their index.
     */
    typedef enum {
      WWDG_IRQN               = 0,   /** @brief Window watchdog interrupt.                    */
      PVD_AVD_IRQN            = 1,   /** @brief PVD/AVD on EXTI line interrupt.               */
      RTC_TAMP_STAMP_IRQN     = 2,   /** @brief EXTI line timestamp/tamper interrupt.         */
      RTC_WKUP_IRQN           = 3,   /** @brief RTC wakeup interrupt on EXTI line.            */
      FLASH_IRQN              = 4,   /** @brief FLASH global interrupt.                       */
      RCC_IRQN                = 5,   /** @brief RCC global interrupt.                         */
      EXTI0_IRQN              = 6,   /** @brief EXTI line 0 interrupt.                        */
      EXTI1_IRQN              = 7,   /** @brief EXTI line 1 interrupt.                        */
      EXTI2_IRQN              = 8,   /** @brief EXTI line 2 interrupt.                        */
      EXTI3_IRQN              = 9,   /** @brief EXTI line 3 interrupt.                        */
      EXTI4_IRQN              = 10,  /** @brief EXTI line 4 interrupt.                        */
      DMA1_STR0_IRQN          = 11,  /** @brief DMA1 stream 0 global interrupt.               */
      DMA1_STR1_IRQN          = 12,  /** @brief DMA1 stream 1 global interrupt.               */
      DMA1_STR2_IRQN          = 13,  /** @brief DMA1 stream 2 global interrupt.               */
      DMA1_STR3_IRQN          = 14,  /** @brief DMA1 stream 3 global interrupt.               */
      DMA1_STR4_IRQN          = 15,  /** @brief DMA1 stream 4 global interrupt.               */
      DMA1_STR5_IRQN          = 16,  /** @brief DMA1 stream 5 global interrupt.               */
      DMA1_STR6_IRQN          = 17,  /** @brief DMA1 stream 6 global interrupt.               */
      ADC1_2_IRQN             = 18,  /** @brief ADC1 and ADC2 global interrupts.              */
      FDCAN1_IT0_IRQN         = 19,  /** @brief FDCAN1 interrupt line 0.                      */
      FDCAN2_IT0_IRQN         = 20,  /** @brief FDCAN2 interrupt line 0.                      */
      FDCAN1_IT1_IRQN         = 21,  /** @brief FDCAN1 interrupt line 1.                      */
      FDCAN2_IT1_IRQN         = 22,  /** @brief FDCAN2 interrupt line 1.                      */
      EXTI9_5_IRQN            = 23,  /** @brief external line [9:5] interrupts.               */
      TIM1_BRK_IRQN           = 24,  /** @brief TIM1 break interrupt.                         */
      TIM1_UP_IRQN            = 25,  /** @brief TIM1 update interrupt.                        */
      TIM1_TRG_COM_IRQN       = 26,  /** @brief TIM1 trigger and commutation interrupt.       */
      TIM1_CC_IRQN            = 27,  /** @brief TIM1 capture compare interrupt.               */
      TIM2_IRQN               = 28,  /** @brief TIM2 global interrupt.                        */
      TIM3_IRQN               = 29,  /** @brief TIM3 global interrupt.                        */
      TIM4_IRQN               = 30,  /** @brief TIM4 global interrupt.                        */
      I2C1_EV_IRQN            = 31,  /** @brief I2C1 event interrupt.                         */
      I2C1_ER_IRQN            = 32,  /** @brief I2C1 error interrupt.                         */
      I2C2_EV_IRQN            = 33,  /** @brief I2C2 event interrupt.                         */
      I2C2_ER_IRQN            = 34,  /** @brief I2C2 error interrupt.                         */
      SPI1_IRQN               = 35,  /** @brief SPI1 global interrupt.                        */
      SPI2_IRQN               = 36,  /** @brief SPI2 global interrupt.                        */
      USART1_IRQN             = 37,  /** @brief USART1 global interrupt.                      */
      USART2_IRQN             = 38,  /** @brief USART2 global interrupt.                      */
      USART3_IRQN             = 39,  /** @brief USART3 global interrupt.                      */
      EXTI15_10_IRQN          = 40,  /** @brief External line [15:10] interrupts.             */
      RTC_ALARM_IRQN          = 41,  /** @brief RTC A/B alarm to EXTI line interrupt.         */
      TIM8_BRK_TIM12_IRQN     = 43,  /** @brief TIM8 break and TIM12 global interrupt.        */
      TIM8_UP_TIM13_IRQN      = 44,  /** @brief TIM8 update and TIM13 global interrupt.       */
      TIM8_TRG_COM_TIM14_IRQN = 45,  /** @brief TIM8 trig/comm and TIM14 global interrupt.    */
      TIM8_CC_IRQN            = 46,  /** @brief TIM8 capture compare interrupt.               */
      DMA1_STR7_IRQN          = 47,  /** @brief DMA1 stream 7 interrupt.                      */
      FMC_IRQN                = 48,  /** @brief FMC global interrupt.                         */
      SDMMC1_IRQN             = 49,  /** @brief SDMMC1 global interrupt.                      */
      TIM5_IRQN               = 50,  /** @brief TIM5 global interrupt.                        */
      SPI3_IRQN               = 51,  /** @brief SPI3 global interrupt.                        */
      UART4_IRQN              = 52,  /** @brief UART4 global interrupt.                       */
      UART5_IRQN              = 53,  /** @brief UART5 global interrupt.                       */
      TIM6_DAC_IRQN           = 54,  /** @brief TIM6 global and DAC 1/2 underrun interrupts.  */
      TIM7_IRQN               = 55,  /** @brief TIM7 global interrupt.                        */
      DMA2_STR0_IRQN          = 56,  /** @brief DMA2 stream 0 global interrupt.               */
      DMA2_STR1_IRQN          = 57,  /** @brief DMA2 stream 1 global interrupt.               */
      DMA2_STR2_IRQN          = 58,  /** @brief DMA2 stream 2 global interrupt.               */
      DMA2_STR3_IRQN          = 59,  /** @brief DMA2 stream 3 global interrupt.               */
      DMA2_STR4_IRQN          = 60,  /** @brief DMA2 stream 4 global interrupt.               */
      ETH_IRQN                = 61,  /** @brief Ethernet global interrupt.                    */
      ETH_WKUP_IRQN           = 62,  /** @brief Ethernet wakeup on EXTI line interrupt.       */
      FDCAN_CAL_IRQN          = 63,  /** @brief FDCAN calibration unit interrupt.             */
      SEV1_IRQN               = 64,  /** @brief CM7 send event interrupt for CM4.             */
      SEV2_IRQN               = 65,  /** @brief CM4 send event interrupt for CM7.             */
      DMA2_STR5_IRQN          = 68,  /** @brief DMA2 stream 5 global interrupt.               */
      DMA2_STR6_IRQN          = 69,  /** @brief DMA2 stream 6 global interrupt.               */
      DMA2_STR7_IRQN          = 70,  /** @brief DMA2 stream 7 global interrupt.               */
      USART6_IRQN             = 71,  /** @brief USART6 global interrupt.                      */
      I2C3_EV_IRQN            = 72,  /** @brief I2C3 event interrupt.                         */
      I2C3_ER_IRQN            = 73,  /** @brief I2C3 error interrupt.                         */
      OTG_HS_EP1_OUT_IRQN     = 74,  /** @brief USB OTG HS end point 1 out global interrupt.  */
      OTG_HS_EP1_IN_IRQN      = 75,  /** @brief USB OTG HS end point 1 in global interrupt.   */
      OTG_HS_WKUP_IRQN        = 76,  /** @brief USB OTG HS wakeup on EXTI interrupt.          */
      OTG_HS_IRQN             = 77,  /** @brief USB OTG HS global interrupt.                  */
      DCMI_IRQN               = 78,  /** @brief DCMI global interrupt.                        */
      CRYP_IRQN               = 80,  /** @brief RNG global interrupt.                         */
      FPU_IRQN                = 81,  /** @brief FPU global interrupt.                         */
      UART7_IRQN              = 82,  /** @brief UART7 global interrupt.                       */
      UART8_IRQN              = 83,  /** @brief UART8 global interrupt.                       */
      SPI4_IRQN               = 84,  /** @brief SPI4 global interrupt.                        */
      SPI5_IRQN               = 85,  /** @brief SPI5 global interrupt.                        */
      SPI6_IRQN               = 86,  /** @brief SPI6 global interrupt.                        */
      SAI1_IRQN               = 87,  /** @brief SAI1 global interrupt.                        */
      LTDC_IRQN               = 88,  /** @brief LTDC global interrupt.                        */
      LTDC_ER_IRQN            = 89,  /** @brief LTDC error global interrupt.                  */
      DMA2D_IRQN              = 90,  /** @brief DMA2D global interrupt.                       */
      SAI2_IRQN               = 91,  /** @brief SAI2 global interrupt.                        */
      QUADSPI_IRQN            = 92,  /** @brief QUAD-SPI global interrupt.                    */
      LPTIM1_IRQN             = 93,  /** @brief LP TIM1 interrupt.                            */
      CEC_IRQN                = 94,  /** @brief HDMI-CEC global interrupt.                    */
      I2C4_EV_IRQN            = 95,  /** @brief I2C4 event interrupt.                         */
      I2C4_ER_IRQN            = 96,  /** @brief I2C4 error interrupt.                         */
      SPDIF_RX_IRQN           = 97,  /** @brief SPDIF-RX global interrupt.                    */
      OTG_FS_EP1_OUT_IRQN     = 98,  /** @brief USB OTG HS2 global interrupt.                 */
      OTG_FS_EP1_IN_IRQN      = 99,  /** @brief USB OTG HS2 end point 1 out global interrupt. */
      OTG_FS_WKUP_IRQN        = 100, /** @brief USB OTG HS2 end point 1 in global interrupt.  */
      OTG_FS_IRQN             = 101, /** @brief USB OTG HS2 wakeup on EXTI interrupt.         */
      DMAMUX1_OVR_IRQN        = 102, /** @brief DMAMUX1 overrun interrupt.                    */
      HRTIM1_Master_IRQN      = 103, /** @brief HRTIM master timer global interrupts.         */
      HRTIM1_TIMA_IRQN        = 104, /** @brief HRTIM timer A global interrupt.               */
      HRTIM1_TIMB_IRQN        = 105, /** @brief HRTIM timer B global interrupt.               */
      HRTIM1_TIMC_IRQN        = 106, /** @brief HRTIM timer C global interrupt.               */
      HRTIM1_TIMD_IRQN        = 107, /** @brief HRTIM timer D global interrupt.               */
      HRTIM1_TIME_IRQN        = 108, /** @brief HRTIM timer E global interrupt.               */
      HRTIM1_FLT_IRQN         = 109, /** @brief HRTIM fault global interrupt.                 */
      DFSDM1_FLT0_IRQN        = 110, /** @brief DFSDM filter 1 interrupt.                     */
      DFSDM1_FLT1_IRQN        = 111, /** @brief DFSDM filter 2 interrupt.                     */
      DFSDM1_FLT2_IRQN        = 112, /** @brief DFSDM filter 3 interrupt.                     */
      DFSDM1_FLT3_IRQN        = 113, /** @brief DFSDM filter 4 interrupt.                     */
      SAI3_IRQN               = 114, /** @brief SAI3 global interrupt.                        */
      SWPMI1_IRQN             = 115, /** @brief Serial wire interface 1 global interrupt.     */
      TIM15_IRQN              = 116, /** @brief TIM15 global interrupt.                       */
      TIM16_IRQN              = 117, /** @brief TIM16 global interrupt.                       */
      TIM17_IRQN              = 118, /** @brief TIM17 global interrupt.                       */
      MDIOS_WKUP_IRQN         = 119, /** @brief MDIOS wakeup interrupt.                       */
      MDIOS_IRQN              = 120, /** @brief MDIOS global interrupt.                       */
      JPEG_IRQN               = 121, /** @brief JPEG global interrupt.                        */
      MDMA_IRQN               = 122, /** @brief MDMA global interrupt.                        */
      DSI_IRQN                = 123, /** @brief DSI host global interrupt.                    */
      SDMMC2_IRQN             = 124, /** @brief SDMMC2 global interrupt.                      */
      HSEM1_IRQN              = 125, /** @brief HSEM1 global interrupt.                       */
      HSEM2_IRQN              = 126, /** @brief HSEM2 global interrupt.                       */
      ADC3_IRQN               = 127, /** @brief ADC3 global interrupt.                        */
      DMAMUX2_OVR_IRQN        = 128, /** @brief DMAMUX2 overrun interrupt.                    */
      BDMA_CH0_IRQN           = 129, /** @brief BDMA channel 0 global interrupt.              */
      BDMA_CH1_IRQN           = 130, /** @brief BDMA channel 1 global interrupt.              */
      BDMA_CH2_IRQN           = 131, /** @brief BDMA channel 2 global interrupt.              */
      BDMA_CH3_IRQN           = 132, /** @brief BDMA channel 3 global interrupt.              */
      BDMA_CH4_IRQN           = 133, /** @brief BDMA channel 4 global interrupt.              */
      BDMA_CH5_IRQN           = 134, /** @brief BDMA channel 5 global interrupt.              */
      BDMA_CH6_IRQN           = 135, /** @brief BDMA channel 6 global interrupt.              */
      BDMA_CH7_IRQN           = 136, /** @brief BDMA channel 7 global interrupt.              */
      COMP_IRQN               = 137, /** @brief COMP global interrupt.                        */
      LPTIM2_IRQN             = 138, /** @brief LP TIM2 global interrupt.                     */
      LPTIM3_IRQN             = 139, /** @brief LP TIM3 global interrupt.                     */
      LPTIM4_IRQN             = 140, /** @brief LP TIM4 global interrupt.                     */
      LPTIM5_IRQN             = 141, /** @brief LP TIM5 global interrupt.                     */
      LPUART1_IRQN            = 142, /** @brief LP UART1 interrupt.                           */
      WWDG_RST_IRQN           = 143, /** @brief Window watchdog reset interrupt.              */
      CRS_IRQN                = 144, /** @brief Clock recovery global interrupt.              */
      ECC_IRQN                = 145, /** @brief ECC diagnostic global interrupt.              */
      SAI4_IRQN               = 146, /** @brief SAI4 global interrupt.                        */
      HOLD_CORE_IRQN          = 148, /** @brief Hold core interrupt.                          */
      WKUP_IRQN               = 149, /** @brief Interrupt for all 6 wake-up pins.             */
    }irqn_t;

    /**********************************************************************************************
     * @section Exception Functions
     **********************************************************************************************/
    
    __IT_ATTR void cm7_reset_exc()            {} /** @brief CM7 System reset exception.           */
    __IT_ATTR void cm7_nmi_exc()              {} /** @brief CM7 Non maskable interrupt exception. */
    __IT_ATTR void cm7_hard_fault_exc()       {} /** @brief CM7 Hard fault exception.             */
    __IT_ATTR void cm7_mem_manage_fault_exc() {} /** @brief CM7 Mem-manage (MPU) fault exception. */
    __IT_ATTR void cm7_bus_fault_exc()        {} /** @brief CM7 Bus (memory) fault exception.     */
    __IT_ATTR void cm7_usage_fault_exc()      {} /** @brief CM7 Usage fault exception.            */
    __IT_ATTR void cm7_svc_exc()              {} /** @brief CM7 SVC exception.                    */
    __IT_ATTR void cm7_debug_monitor_exc()    {} /** @brief CM7 Debug monitor fault exception.    */
    __IT_ATTR void cm7_pend_sv_exc()          {} /** @brief CM7 Pend-SV exception                 */
    __IT_ATTR void cm7_systick_exc()          {} /** @brief CM7 Systick timer exception.          */

    __IT_ATTR void cm4_reset_exc()            {} /** @brief CM4 System reset exception.           */
    __IT_ATTR void cm4_nmi_exc()              {} /** @brief CM4 Non maskable interrupt exception. */
    __IT_ATTR void cm4_hard_fault_exc()       {} /** @brief CM4 Hard fault exception.             */
    __IT_ATTR void cm4_mem_manage_fault_exc() {} /** @brief CM4 Mem-manage (MPU) fault exception. */
    __IT_ATTR void cm4_bus_fault_exc()        {} /** @brief CM4 Bus (memory) fault exception.     */
    __IT_ATTR void cm4_usage_fault_exc()      {} /** @brief CM4 Usage fault exception.            */
    __IT_ATTR void cm4_svc_exc()              {} /** @brief CM4 SVC exception.                    */
    __IT_ATTR void cm4_debug_monitor_exc()    {} /** @brief CM4 Debug monitor fault exception.    */
    __IT_ATTR void cm4_pend_sv_exc()          {} /** @brief CM4 Pend-SV exception                 */
    __IT_ATTR void cm4_systick_exc()          {} /** @brief CM4 Systick timer exception.          */
    
    /**********************************************************************************************
     * @section IRQ Functions
     **********************************************************************************************/

    __IT_ATTR void cm4_wwdg_irq()           {} /** @brief CM7 window watchdog interrupt.                */
    __IT_ATTR void cm7_wwdg_irq()           {} /** @brief CM4 window watchdog interrupt.                */
    __IT_ATTR void pvd_pvm_irq()            {} /** @brief PVD/AVD on EXTI line interrupt.               */
    __IT_ATTR void rtc_tamp_stamp_irq()     {} /** @brief EXTI line timestamp/tamper interrupt.         */
    __IT_ATTR void rtc_wkup_irq()           {} /** @brief RTC wakeup interrupt on EXTI line.            */
    __IT_ATTR void flash_irq()              {} /** @brief FLASH global interrupt.                       */
    __IT_ATTR void rcc_irq()                {} /** @brief RCC global interrupt.                         */
    __IT_ATTR void exti0_irq()              {} /** @brief EXTI line 0 interrupt.                        */
    __IT_ATTR void exti1_irq()              {} /** @brief EXTI line 1 interrupt.                        */
    __IT_ATTR void exti2_irq()              {} /** @brief EXTI line 2 interrupt.                        */
    __IT_ATTR void exti3_irq()              {} /** @brief EXTI line 3 interrupt.                        */
    __IT_ATTR void exti4_irq()              {} /** @brief EXTI line 4 interrupt.                        */
    __IT_ATTR void dma_str0_irq()           {} /** @brief DMA1 stream 0 global interrupt.               */
    __IT_ATTR void dma_str1_irq()           {} /** @brief DMA1 stream 1 global interrupt.               */
    __IT_ATTR void dma_str2_irq()           {} /** @brief DMA1 stream 2 global interrupt.               */
    __IT_ATTR void dma_str3_irq()           {} /** @brief DMA1 stream 3 global interrupt.               */
    __IT_ATTR void dma_str4_irq()           {} /** @brief DMA1 stream 4 global interrupt.               */
    __IT_ATTR void dma_str5_irq()           {} /** @brief DMA1 stream 5 global interrupt.               */
    __IT_ATTR void dma_str6_irq()           {} /** @brief DMA1 stream 6 global interrupt.               */
    __IT_ATTR void adc1_2_irq()             {} /** @brief ADC1 and ADC2 global interrupts.              */
    __IT_ATTR void fdcan1_it0_irq()         {} /** @brief FDCAN1 interrupt line 0.                      */
    __IT_ATTR void fdcan2_it0_irq()         {} /** @brief FDCAN2 interrupt line 0.                      */
    __IT_ATTR void fdcan1_it1_irq()         {} /** @brief FDCAN1 interrupt line 1.                      */
    __IT_ATTR void fdcan2_it1_irq()         {} /** @brief FDCAN2 interrupt line 1.                      */
    __IT_ATTR void exti9_5_irq()            {} /** @brief external line [9:5] interrupts.               */
    __IT_ATTR void tim1_brk_irq()           {} /** @brief TIM1 break interrupt.                         */
    __IT_ATTR void tim1_up_irq()            {} /** @brief TIM1 update interrupt.                        */
    __IT_ATTR void tim1_trg_com_irq()       {} /** @brief TIM1 trigger and commutation interrupt.       */
    __IT_ATTR void tim_cc_irq()             {} /** @brief TIM1 capture compare interrupt.               */
    __IT_ATTR void tim2_irq()               {} /** @brief TIM2 global interrupt.                        */
    __IT_ATTR void tim3_irq()               {} /** @brief TIM3 global interrupt.                        */
    __IT_ATTR void tim4_irq()               {} /** @brief TIM4 global interrupt.                        */
    __IT_ATTR void i2c1_ev_irq()            {} /** @brief I2C1 event interrupt.                         */
    __IT_ATTR void i2c1_er_irq()            {} /** @brief I2C1 error interrupt.                         */
    __IT_ATTR void i2c2_ev_irq()            {} /** @brief I2C2 event interrupt.                         */
    __IT_ATTR void i2c2_er_irq()            {} /** @brief I2C2 error interrupt.                         */
    __IT_ATTR void spi1_irq()               {} /** @brief SPI1 global interrupt.                        */
    __IT_ATTR void spi2_irq()               {} /** @brief SPI2 global interrupt.                        */
    __IT_ATTR void usart1_irq()             {} /** @brief USART1 global interrupt.                      */
    __IT_ATTR void usart2_irq()             {} /** @brief USART2 global interrupt.                      */
    __IT_ATTR void usart3_irq()             {} /** @brief USART3 global interrupt.                      */
    __IT_ATTR void exti15_10_irq()          {} /** @brief External line [15:10] interrupts.             */
    __IT_ATTR void rtc_alarm_irq()          {} /** @brief RTC A/B alarm to EXTI line interrupt.         */
    __IT_ATTR void tim8_brk_tim12_irq()     {} /** @brief TIM8 break and TIM12 global interrupt.        */
    __IT_ATTR void tim8_up_tim13_irq()      {} /** @brief TIM8 update and TIM13 global interrupt.       */
    __IT_ATTR void tim8_trg_com_tim14_irq() {} /** @brief TIM8 trig/comm and TIM14 global interrupt.    */
    __IT_ATTR void tim8_cc_irq()            {} /** @brief TIM8 capture compare interrupt.               */
    __IT_ATTR void dma_str7_irq()           {} /** @brief DMA1 stream 7 interrupt.                      */
    __IT_ATTR void fmc_irq()                {} /** @brief FMC global interrupt.                         */
    __IT_ATTR void sdmmc1_irq()             {} /** @brief SDMMC1 global interrupt.                      */
    __IT_ATTR void tim5_irq()               {} /** @brief TIM5 global interrupt.                        */
    __IT_ATTR void spi3_irq()               {} /** @brief SPI3 global interrupt.                        */
    __IT_ATTR void uart4_irq()              {} /** @brief UART4 global interrupt.                       */
    __IT_ATTR void uart5_irq()              {} /** @brief UART5 global interrupt.                       */
    __IT_ATTR void tim6_dac_irq()           {} /** @brief TIM6 global and DAC 1/2 underrun interrupts.  */
    __IT_ATTR void tim7_irq()               {} /** @brief TIM7 global interrupt.                        */
    __IT_ATTR void dma2_str0_irq()          {} /** @brief DMA2 stream 0 global interrupt.               */
    __IT_ATTR void dma2_str1_irq()          {} /** @brief DMA2 stream 1 global interrupt.               */
    __IT_ATTR void dma2_str2_irq()          {} /** @brief DMA2 stream 2 global interrupt.               */
    __IT_ATTR void dma2_str3_irq()          {} /** @brief DMA2 stream 3 global interrupt.               */
    __IT_ATTR void dma2_str4_irq()          {} /** @brief DMA2 stream 4 global interrupt.               */
    __IT_ATTR void eth_irq()                {} /** @brief Ethernet global interrupt.                    */
    __IT_ATTR void eth_wkup_irq()           {} /** @brief Ethernet wakeup on EXTI line interrupt.       */
    __IT_ATTR void fdcan_cal_irq()          {} /** @brief FDCAN calibration unit interrupt.             */
    __IT_ATTR void cm7_sev1_irq()           {} /** @brief CM7 send event interrupt for CM4.             */
    __IT_ATTR void cm4_sev2_irq()           {} /** @brief CM4 send event interrupt for CM7.             */
    __IT_ATTR void dma2_str5_irq()          {} /** @brief DMA2 stream 5 global interrupt.               */
    __IT_ATTR void dma2_str6_irq()          {} /** @brief DMA2 stream 6 global interrupt.               */
    __IT_ATTR void dma2_str7_irq()          {} /** @brief DMA2 stream 7 global interrupt.               */
    __IT_ATTR void usart6_irq()             {} /** @brief USART6 global interrupt.                      */
    __IT_ATTR void i2c3_ev_irq()            {} /** @brief I2C3 event interrupt.                         */
    __IT_ATTR void i2c3_er_irq()            {} /** @brief I2C3 error interrupt.                         */
    __IT_ATTR void otg_hs_ep1_out_irq()     {} /** @brief USB OTG HS end point 1 out global interrupt.  */
    __IT_ATTR void otg_hs_ep1_in_irq()      {} /** @brief USB OTG HS end point 1 in global interrupt.   */
    __IT_ATTR void otg_hs_wkup_irq()        {} /** @brief USB OTG HS wakeup on EXTI interrupt.          */
    __IT_ATTR void otg_hs_irq()             {} /** @brief USB OTG HS global interrupt.                  */
    __IT_ATTR void dcmi_irq()               {} /** @brief DCMI global interrupt.                        */
    __IT_ATTR void cryp_irq()               {} /** @brief RNG global interrupt.                         */
    __IT_ATTR void hash_rng_irq()           {} /** @brief HASH and RNG global interrupt.                */
    __IT_ATTR void cm7_fpu_irq()            {} /** @brief CM7 FPU global interrupt.                     */
    __IT_ATTR void cm4_fpu_irq()            {} /** @brief CM4 FPU global interrupt.                     */
    __IT_ATTR void uart7_irq()              {} /** @brief UART7 global interrupt.                       */
    __IT_ATTR void uart8_irq()              {} /** @brief UART8 global interrupt.                       */
    __IT_ATTR void spi4_irq()               {} /** @brief SPI4 global interrupt.                        */
    __IT_ATTR void spi5_irq()               {} /** @brief SPI5 global interrupt.                        */
    __IT_ATTR void spi6_irq()               {} /** @brief SPI6 global interrupt.                        */
    __IT_ATTR void sai1_irq()               {} /** @brief SAI1 global interrupt.                        */
    __IT_ATTR void ltdc_irq()               {} /** @brief LTDC global interrupt.                        */
    __IT_ATTR void ltdc_er_irq()            {} /** @brief LTDC error global interrupt.                  */
    __IT_ATTR void dma2d_irq()              {} /** @brief DMA2D global interrupt.                       */
    __IT_ATTR void sai2_irq()               {} /** @brief SAI2 global interrupt.                        */
    __IT_ATTR void quadspi_irq()            {} /** @brief QUAD-SPI global interrupt.                    */
    __IT_ATTR void lptim1_irq()             {} /** @brief LP TIM1 interrupt.                            */
    __IT_ATTR void cec_irq()                {} /** @brief HDMI-CEC global interrupt.                    */
    __IT_ATTR void i2c4_ev_irq()            {} /** @brief I2C4 event interrupt.                         */
    __IT_ATTR void i2c4_er_irq()            {} /** @brief I2C4 error interrupt.                         */
    __IT_ATTR void spdif_irq()              {} /** @brief SPDIF-RX global interrupt.                    */
    __IT_ATTR void otg_fs_ep1_out_irq()     {} /** @brief USB OTG HS2 global interrupt.                 */
    __IT_ATTR void otg_fs_ep1_in_irq()      {} /** @brief USB OTG HS2 end point 1 out global interrupt. */
    __IT_ATTR void otg_fs_wkup_irq()        {} /** @brief USB OTG HS2 end point 1 in global interrupt.  */
    __IT_ATTR void otg_fs_irq()             {} /** @brief USB OTG HS2 wakeup on EXTI interrupt.         */
    __IT_ATTR void dmamux1_ovr_irq()        {} /** @brief DMAMUX1 overrun interrupt.                    */
    __IT_ATTR void hrtim1_mst_irq()         {} /** @brief HRTIM master timer global interrupts.         */
    __IT_ATTR void hrtim1_tima_irq()        {} /** @brief HRTIM timer A global interrupt.               */
    __IT_ATTR void hrtim1_timb_irq()        {} /** @brief HRTIM timer B global interrupt.               */
    __IT_ATTR void hrtim1_timc_irq()        {} /** @brief HRTIM timer C global interrupt.               */
    __IT_ATTR void hrtim1_timd_irq()        {} /** @brief HRTIM timer D global interrupt.               */
    __IT_ATTR void hrtim1_time_irq()        {} /** @brief HRTIM timer E global interrupt.               */
    __IT_ATTR void hrtim1_flt_irq()         {} /** @brief HRTIM fault global interrupt.                 */
    __IT_ATTR void dfsdm1_flt0_irq()        {} /** @brief DFSDM filter 1 interrupt.                     */
    __IT_ATTR void dfsdm1_flt1_irq()        {} /** @brief DFSDM filter 2 interrupt.                     */
    __IT_ATTR void dfsdm1_flt2_irq()        {} /** @brief DFSDM filter 3 interrupt.                     */
    __IT_ATTR void dfsdm1_flt3_irq()        {} /** @brief DFSDM filter 4 interrupt.                     */
    __IT_ATTR void sai3_irq()               {} /** @brief SAI3 global interrupt.                        */
    __IT_ATTR void swpmi1_irq()             {} /** @brief Serial wire interface 1 global interrupt.     */
    __IT_ATTR void tim15_irq()              {} /** @brief TIM15 global interrupt.                       */
    __IT_ATTR void tim16_irq()              {} /** @brief TIM16 global interrupt.                       */
    __IT_ATTR void tim17_irq()              {} /** @brief TIM17 global interrupt.                       */
    __IT_ATTR void mdios_wkup_irq()         {} /** @brief MDIOS wakeup interrupt.                       */
    __IT_ATTR void mdios_irq()              {} /** @brief MDIOS global interrupt.                       */
    __IT_ATTR void jpeg_irq()               {} /** @brief JPEG global interrupt.                        */
    __IT_ATTR void mdma_irq()               {} /** @brief MDMA global interrupt.                        */
    __IT_ATTR void dsi_irq()                {} /** @brief DSI host global interrupt.                    */
    __IT_ATTR void sdmmc2_irq()             {} /** @brief SDMMC2 global interrupt.                      */
    __IT_ATTR void cm7_hsem1_irq()          {} /** @brief HSEM1 global interrupt.                       */
    __IT_ATTR void cm4_hsem2_irq()          {} /** @brief HSEM2 global interrupt.                       */
    __IT_ATTR void adc3_irq()               {} /** @brief ADC3 global interrupt.                        */
    __IT_ATTR void dmamux2_ovr_irq()        {} /** @brief DMAMUX2 overrun interrupt.                    */
    __IT_ATTR void bdma_ch0_irq()           {} /** @brief BDMA channel 0 global interrupt.              */
    __IT_ATTR void bdma_ch1_irq()           {} /** @brief BDMA channel 1 global interrupt.              */
    __IT_ATTR void bdma_ch2_irq()           {} /** @brief BDMA channel 2 global interrupt.              */
    __IT_ATTR void bdma_ch3_irq()           {} /** @brief BDMA channel 3 global interrupt.              */
    __IT_ATTR void bdma_ch4_irq()           {} /** @brief BDMA channel 4 global interrupt.              */
    __IT_ATTR void bdma_ch5_irq()           {} /** @brief BDMA channel 5 global interrupt.              */
    __IT_ATTR void bdma_ch6_irq()           {} /** @brief BDMA channel 6 global interrupt.              */
    __IT_ATTR void bdma_ch7_irq()           {} /** @brief BDMA channel 7 global interrupt.              */
    __IT_ATTR void comp_irq()               {} /** @brief COMP global interrupt.                        */
    __IT_ATTR void lptim2_irq()             {} /** @brief LP TIM2 global interrupt.                     */
    __IT_ATTR void lptim3_irq()             {} /** @brief LP TIM3 global interrupt.                     */
    __IT_ATTR void lptim4_irq()             {} /** @brief LP TIM4 global interrupt.                     */
    __IT_ATTR void lptim5_irq()             {} /** @brief LP TIM5 global interrupt.                     */
    __IT_ATTR void lpuart_irq()             {} /** @brief LP UART1 interrupt.                           */
    __IT_ATTR void cm7_wwdg_rst_irq()       {} /** @brief Window watchdog reset interrupt.              */
    __IT_ATTR void cm4_wwdg_rst_irq()       {} /** @brief Window watchdog reset interrupt.              */
    __IT_ATTR void crs_irq()                {} /** @brief Clock recovery global interrupt.              */
    __IT_ATTR void ecc_irq()                {} /** @brief ECC diagnostic global interrupt.              */
    __IT_ATTR void sai4_irq()               {} /** @brief SAI4 global interrupt.                        */
    __IT_ATTR void cm7_hold_core_irq()      {} /** @brief Hold core interrupt.                          */
    __IT_ATTR void cm4_hold_core_irq()      {} /** @brief Hold core interrupt.                          */
    __IT_ATTR void wkup_irq()               {} /** @brief Interrupt for all 6 wake-up pins.             */

    /**********************************************************************************************
     * @section Vector Table (CM7)
     **********************************************************************************************/

    /** 
     * @brief Interrupt vector table for the ARM-M7 core. 
     */
    __attribute__((section(".cm4_vtable")))
    static const void* const cm7_vtable[] = {
      &__cm7_stack_end,
      &cm7_reset_exc,
      &cm7_nmi_exc,
      &cm7_hard_fault_exc,
      &cm7_mem_manage_fault_exc,
      &cm7_bus_fault_exc,
      &cm7_usage_fault_exc,
      NULL,
      NULL,
      NULL,
      NULL,
      &cm7_svc_exc,
      &cm7_debug_monitor_exc,
      NULL,
      &cm7_pend_sv_exc,
      &cm7_systick_exc,
      &cm7_wwdg_irq,
      &pvd_pvm_irq,
      &rtc_tamp_stamp_irq,
      &rtc_wkup_irq,
      &flash_irq,
      &rcc_irq,
      &exti0_irq,
      &exti1_irq,
      &exti2_irq,
      &exti3_irq,
      &exti4_irq,
      &dma_str0_irq,
      &dma_str1_irq,
      &dma_str2_irq,
      &dma_str3_irq,
      &dma_str4_irq,
      &dma_str5_irq,
      &dma_str6_irq,
      &adc1_2_irq,
      &fdcan1_it0_irq,
      &fdcan2_it0_irq,
      &fdcan1_it1_irq,
      &fdcan2_it1_irq,
      &exti9_5_irq,
      &tim1_brk_irq,
      &tim1_up_irq,
      &tim1_trg_com_irq,
      &tim_cc_irq,
      &tim2_irq,
      &tim3_irq,
      &tim4_irq,
      &i2c1_ev_irq,
      &i2c1_er_irq,
      &i2c2_ev_irq,
      &i2c2_er_irq,
      &spi1_irq,
      &spi2_irq,
      &usart1_irq,
      &usart2_irq,
      &usart3_irq,
      &exti15_10_irq,
      &rtc_alarm_irq,
      NULL,
      &tim8_brk_tim12_irq,
      &tim8_up_tim13_irq,
      &tim8_trg_com_tim14_irq,
      &tim8_cc_irq,
      &dma_str7_irq,
      &fmc_irq,
      &sdmmc1_irq,
      &tim5_irq,
      &spi3_irq,
      &uart4_irq,
      &uart5_irq,
      &tim6_dac_irq,
      &tim7_irq,
      &dma2_str0_irq,
      &dma2_str1_irq,
      &dma2_str2_irq,
      &dma2_str3_irq,
      &dma2_str4_irq,
      &eth_irq,
      &eth_wkup_irq,
      &fdcan_cal_irq,
      &cm7_sev1_irq,
      &cm4_sev2_irq,
      NULL,
      NULL,
      &dma2_str5_irq,
      &dma2_str6_irq,
      &dma2_str7_irq,
      &usart6_irq,
      &i2c3_ev_irq,
      &i2c3_er_irq,
      &otg_hs_ep1_out_irq,
      &otg_hs_ep1_in_irq,
      &otg_hs_wkup_irq,
      &otg_hs_irq,
      &dcmi_irq,
      &cryp_irq,
      &hash_rng_irq,
      &cm7_fpu_irq,
      &uart7_irq,
      &uart8_irq,
      &spi4_irq,
      &spi5_irq,
      &spi6_irq,
      &sai1_irq,
      &ltdc_irq,
      &ltdc_er_irq,
      &dma2d_irq,
      &sai2_irq,
      &quadspi_irq,
      &lptim1_irq,
      &cec_irq,
      &i2c4_ev_irq,
      &i2c4_er_irq,
      &spdif_irq,
      &otg_fs_ep1_out_irq,
      &otg_fs_ep1_in_irq,
      &otg_fs_wkup_irq,
      &otg_fs_irq,
      &dmamux1_ovr_irq,
      &hrtim1_mst_irq,
      &hrtim1_tima_irq,
      &hrtim1_timb_irq,
      &hrtim1_timc_irq,
      &hrtim1_timd_irq,
      &hrtim1_time_irq,
      &hrtim1_flt_irq,
      &dfsdm1_flt0_irq,
      &dfsdm1_flt1_irq,
      &dfsdm1_flt2_irq,
      &dfsdm1_flt3_irq,
      &sai3_irq,
      &swpmi1_irq,
      &tim15_irq,
      &tim16_irq,
      &tim17_irq,
      &mdios_wkup_irq,
      &mdios_irq,
      &jpeg_irq,
      &mdma_irq,
      &dsi_irq,
      &sdmmc2_irq,
      &cm7_hsem1_irq,
      NULL,
      &adc3_irq,
      &dmamux2_ovr_irq,
      &bdma_ch0_irq,
      &bdma_ch1_irq,
      &bdma_ch2_irq,
      &bdma_ch3_irq,
      &bdma_ch4_irq,
      &bdma_ch5_irq,
      &bdma_ch6_irq,
      &bdma_ch7_irq,
      &comp_irq,
      &lptim2_irq,
      &lptim3_irq,
      &lptim4_irq,
      &lptim5_irq,
      &lpuart_irq,
      &cm7_wwdg_rst_irq,
      &crs_irq,
      &ecc_irq,
      &sai4_irq,
      &cm7_hold_core_irq,
      &wkup_irq
    };

    /**********************************************************************************************
     * @section Vector Table (CM4)
     **********************************************************************************************/    

    /** 
     * @brief Interrupt vector table for the ARM-M4 core. 
     */
    __attribute__((section(".cm4_vtable")))
    static const void* const cm4_vtable[] = {
      &__cm4_stack_end,
      &cm4_reset_exc,
      &cm4_nmi_exc,
      &cm4_hard_fault_exc,
      &cm4_mem_manage_fault_exc,
      &cm4_bus_fault_exc,
      &cm4_usage_fault_exc,
      NULL,
      NULL,
      NULL,
      NULL,
      &cm4_svc_exc,
      &cm4_debug_monitor_exc,
      NULL,
      &cm4_pend_sv_exc,
      &cm4_systick_exc,
      &cm4_wwdg_irq,
      &pvd_pvm_irq,
      &rtc_tamp_stamp_irq,
      &rtc_wkup_irq,
      &flash_irq,
      &rcc_irq,
      &exti0_irq,
      &exti1_irq,
      &exti2_irq,
      &exti3_irq,
      &exti4_irq,
      &dma_str0_irq,
      &dma_str1_irq,
      &dma_str2_irq,
      &dma_str3_irq,
      &dma_str4_irq,
      &dma_str5_irq,
      &dma_str6_irq,
      &adc1_2_irq,
      &fdcan1_it0_irq,
      &fdcan2_it0_irq,
      &fdcan1_it1_irq,
      &fdcan2_it1_irq,
      &exti9_5_irq,
      &tim1_brk_irq,
      &tim1_up_irq,
      &tim1_trg_com_irq,
      &tim_cc_irq,
      &tim2_irq,
      &tim3_irq,
      &tim4_irq,
      &i2c1_ev_irq,
      &i2c1_er_irq,
      &i2c2_ev_irq,
      &i2c2_er_irq,
      &spi1_irq,
      &spi2_irq,
      &usart1_irq,
      &usart2_irq,
      &usart3_irq,
      &exti15_10_irq,
      &rtc_alarm_irq,
      NULL,
      &tim8_brk_tim12_irq,
      &tim8_up_tim13_irq,
      &tim8_trg_com_tim14_irq,
      &tim8_cc_irq,
      &dma_str7_irq,
      &fmc_irq,
      &sdmmc1_irq,
      &tim5_irq,
      &spi3_irq,
      &uart4_irq,
      &uart5_irq,
      &tim6_dac_irq,
      &tim7_irq,
      &dma2_str0_irq,
      &dma2_str1_irq,
      &dma2_str2_irq,
      &dma2_str3_irq,
      &dma2_str4_irq,
      &eth_irq,
      &eth_wkup_irq,
      &fdcan_cal_irq,
      &cm7_sev1_irq,
      &cm4_sev2_irq,
      NULL,
      NULL,
      &dma2_str5_irq,
      &dma2_str6_irq,
      &dma2_str7_irq,
      &usart6_irq,
      &i2c3_ev_irq,
      &i2c3_er_irq,
      &otg_hs_ep1_out_irq,
      &otg_hs_ep1_in_irq,
      &otg_hs_wkup_irq,
      &otg_hs_irq,
      &dcmi_irq,
      &cryp_irq,
      &hash_rng_irq,
      &cm4_fpu_irq,
      &uart7_irq,
      &uart8_irq,
      &spi4_irq,
      &spi5_irq,
      &spi6_irq,
      &sai1_irq,
      &ltdc_irq,
      &ltdc_er_irq,
      &dma2d_irq,
      &sai2_irq,
      &quadspi_irq,
      &lptim1_irq,
      &cec_irq,
      &i2c4_ev_irq,
      &i2c4_er_irq,
      &spdif_irq,
      &otg_fs_ep1_out_irq,
      &otg_fs_ep1_in_irq,
      &otg_fs_wkup_irq,
      &otg_fs_irq,
      &dmamux1_ovr_irq,
      &hrtim1_mst_irq,
      &hrtim1_tima_irq,
      &hrtim1_timb_irq,
      &hrtim1_timc_irq,
      &hrtim1_timd_irq,
      &hrtim1_time_irq,
      &hrtim1_flt_irq,
      &dfsdm1_flt0_irq,
      &dfsdm1_flt1_irq,
      &dfsdm1_flt2_irq,
      &dfsdm1_flt3_irq,
      &sai3_irq,
      &swpmi1_irq,
      &tim15_irq,
      &tim16_irq,
      &tim17_irq,
      &mdios_wkup_irq,
      &mdios_irq,
      &jpeg_irq,
      &mdma_irq,
      &dsi_irq,
      &sdmmc2_irq,
      NULL,
      &cm4_hsem2_irq,
      &adc3_irq,
      &dmamux2_ovr_irq,
      &bdma_ch0_irq,
      &bdma_ch1_irq,
      &bdma_ch2_irq,
      &bdma_ch3_irq,
      &bdma_ch4_irq,
      &bdma_ch5_irq,
      &bdma_ch6_irq,
      &bdma_ch7_irq,
      &comp_irq,
      &lptim2_irq,
      &lptim3_irq,
      &lptim4_irq,
      &lptim5_irq,
      &lpuart_irq,
      &cm4_wwdg_rst_irq,
      &crs_irq,
      &ecc_irq,
      &sai4_irq,
      &cm4_hold_core_irq,
      &wkup_irq
    };

  #if defined(__cplusplus)
    } /* extern "C" */
  #endif

#endif /* SRC_PORT_GCC_STM32H745ZI_CM7_DEVICE_INTERRUPT_H */