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
 * @file src/port/GCC_STM32H745ZI/internal/interrupt.h
 * @authors Aaron McBride
 * @brief Interrupt vector table and function definitions.
 */

#ifndef SRC_PORT_GCC_STM32H745ZI_INTERNAL_INTERRUPT_H
#define SRC_PORT_GCC_STM32H745ZI_INTERNAL_INTERRUPT_H

  #include <stdint.h>
  #include <stddef.h>

  #ifdef __cplusplus
    extern "C" {
  #endif

    /**********************************************************************************************
     * @section Implementation Resources
     **********************************************************************************************/

    /* attribute for interrupt functions */
    #define __IT_ATTR __attribute__((interrupt, weak))

    /* linker symbols - end of stack sections */
    extern uint32_t _cm7_stack_end;
    extern uint32_t _cm4_stack_end;

    /**********************************************************************************************
     * @section IRQ Number Enumeration
     **********************************************************************************************/

    /**
     * @brief Enumeration of IRQ interrupts according to their index.
     */
    typedef enum {
      _WWDG_IRQN               = 0,   /** @brief Window watchdog interrupt.                    */
      _PVD_AVD_IRQN            = 1,   /** @brief PVD/AVD on EXTI line interrupt.               */
      _RTC_TAMP_STAMP_IRQN     = 2,   /** @brief EXTI line timestamp/tamper interrupt.         */
      _RTC_WKUP_IRQN           = 3,   /** @brief RTC wakeup interrupt on EXTI line.            */
      _FLASH_IRQN              = 4,   /** @brief FLASH global interrupt.                       */
      _RCC_IRQN                = 5,   /** @brief RCC global interrupt.                         */
      _EXTI0_IRQN              = 6,   /** @brief EXTI line 0 interrupt.                        */
      _EXTI1_IRQN              = 7,   /** @brief EXTI line 1 interrupt.                        */
      _EXTI2_IRQN              = 8,   /** @brief EXTI line 2 interrupt.                        */
      _EXTI3_IRQN              = 9,   /** @brief EXTI line 3 interrupt.                        */
      _EXTI4_IRQN              = 10,  /** @brief EXTI line 4 interrupt.                        */
      _DMA1_STR0_IRQN          = 11,  /** @brief DMA1 stream 0 global interrupt.               */
      _DMA1_STR1_IRQN          = 12,  /** @brief DMA1 stream 1 global interrupt.               */
      _DMA1_STR2_IRQN          = 13,  /** @brief DMA1 stream 2 global interrupt.               */
      _DMA1_STR3_IRQN          = 14,  /** @brief DMA1 stream 3 global interrupt.               */
      _DMA1_STR4_IRQN          = 15,  /** @brief DMA1 stream 4 global interrupt.               */
      _DMA1_STR5_IRQN          = 16,  /** @brief DMA1 stream 5 global interrupt.               */
      _DMA1_STR6_IRQN          = 17,  /** @brief DMA1 stream 6 global interrupt.               */
      _ADC1_2_IRQN             = 18,  /** @brief ADC1 and ADC2 global interrupts.              */
      _FDCAN1_IT0_IRQN         = 19,  /** @brief FDCAN1 interrupt line 0.                      */
      _FDCAN2_IT0_IRQN         = 20,  /** @brief FDCAN2 interrupt line 0.                      */
      _FDCAN1_IT1_IRQN         = 21,  /** @brief FDCAN1 interrupt line 1.                      */
      _FDCAN2_IT1_IRQN         = 22,  /** @brief FDCAN2 interrupt line 1.                      */
      _EXTI9_5_IRQN            = 23,  /** @brief external line [9:5] interrupts.               */
      _TIM1_BRK_IRQN           = 24,  /** @brief TIM1 break interrupt.                         */
      _TIM1_UP_IRQN            = 25,  /** @brief TIM1 update interrupt.                        */
      _TIM1_TRG_COM_IRQN       = 26,  /** @brief TIM1 trigger and commutation interrupt.       */
      _TIM1_CC_IRQN            = 27,  /** @brief TIM1 capture compare interrupt.               */
      _TIM2_IRQN               = 28,  /** @brief TIM2 global interrupt.                        */
      _TIM3_IRQN               = 29,  /** @brief TIM3 global interrupt.                        */
      _TIM4_IRQN               = 30,  /** @brief TIM4 global interrupt.                        */
      _I2C1_EV_IRQN            = 31,  /** @brief I2C1 event interrupt.                         */
      _I2C1_ER_IRQN            = 32,  /** @brief I2C1 error interrupt.                         */
      _I2C2_EV_IRQN            = 33,  /** @brief I2C2 event interrupt.                         */
      _I2C2_ER_IRQN            = 34,  /** @brief I2C2 error interrupt.                         */
      _SPI1_IRQN               = 35,  /** @brief SPI1 global interrupt.                        */
      _SPI2_IRQN               = 36,  /** @brief SPI2 global interrupt.                        */
      _USART1_IRQN             = 37,  /** @brief USART1 global interrupt.                      */
      _USART2_IRQN             = 38,  /** @brief USART2 global interrupt.                      */
      _USART3_IRQN             = 39,  /** @brief USART3 global interrupt.                      */
      _EXTI15_10_IRQN          = 40,  /** @brief External line [15:10] interrupts.             */
      _RTC_ALARM_IRQN          = 41,  /** @brief RTC A/B alarm to EXTI line interrupt.         */
      _TIM8_BRK_TIM12_IRQN     = 43,  /** @brief TIM8 break and TIM12 global interrupt.        */
      _TIM8_UP_TIM13_IRQN      = 44,  /** @brief TIM8 update and TIM13 global interrupt.       */
      _TIM8_TRG_COM_TIM14_IRQN = 45,  /** @brief TIM8 trig/comm and TIM14 global interrupt.    */
      _TIM8_CC_IRQN            = 46,  /** @brief TIM8 capture compare interrupt.               */
      _DMA1_STR7_IRQN          = 47,  /** @brief DMA1 stream 7 interrupt.                      */
      _FMC_IRQN                = 48,  /** @brief FMC global interrupt.                         */
      _SDMMC1_IRQN             = 49,  /** @brief SDMMC1 global interrupt.                      */
      _TIM5_IRQN               = 50,  /** @brief TIM5 global interrupt.                        */
      _SPI3_IRQN               = 51,  /** @brief SPI3 global interrupt.                        */
      _UART4_IRQN              = 52,  /** @brief UART4 global interrupt.                       */
      _UART5_IRQN              = 53,  /** @brief UART5 global interrupt.                       */
      _TIM6_DAC_IRQN           = 54,  /** @brief TIM6 global and DAC 1/2 underrun interrupts.  */
      _TIM7_IRQN               = 55,  /** @brief TIM7 global interrupt.                        */
      _DMA2_STR0_IRQN          = 56,  /** @brief DMA2 stream 0 global interrupt.               */
      _DMA2_STR1_IRQN          = 57,  /** @brief DMA2 stream 1 global interrupt.               */
      _DMA2_STR2_IRQN          = 58,  /** @brief DMA2 stream 2 global interrupt.               */
      _DMA2_STR3_IRQN          = 59,  /** @brief DMA2 stream 3 global interrupt.               */
      _DMA2_STR4_IRQN          = 60,  /** @brief DMA2 stream 4 global interrupt.               */
      _ETH_IRQN                = 61,  /** @brief Ethernet global interrupt.                    */
      _ETH_WKUP_IRQN           = 62,  /** @brief Ethernet wakeup on EXTI line interrupt.       */
      _FDCAN_CAL_IRQN          = 63,  /** @brief FDCAN calibration unit interrupt.             */
      _SEV1_IRQN               = 64,  /** @brief CM7 send event interrupt for CM4.             */
      _SEV2_IRQN               = 65,  /** @brief CM4 send event interrupt for CM7.             */
      _DMA2_STR5_IRQN          = 68,  /** @brief DMA2 stream 5 global interrupt.               */
      _DMA2_STR6_IRQN          = 69,  /** @brief DMA2 stream 6 global interrupt.               */
      _DMA2_STR7_IRQN          = 70,  /** @brief DMA2 stream 7 global interrupt.               */
      _USART6_IRQN             = 71,  /** @brief USART6 global interrupt.                      */
      _I2C3_EV_IRQN            = 72,  /** @brief I2C3 event interrupt.                         */
      _I2C3_ER_IRQN            = 73,  /** @brief I2C3 error interrupt.                         */
      _OTG_HS_EP1_OUT_IRQN     = 74,  /** @brief USB OTG HS end point 1 out global interrupt.  */
      _OTG_HS_EP1_IN_IRQN      = 75,  /** @brief USB OTG HS end point 1 in global interrupt.   */
      _OTG_HS_WKUP_IRQN        = 76,  /** @brief USB OTG HS wakeup on EXTI interrupt.          */
      _OTG_HS_IRQN             = 77,  /** @brief USB OTG HS global interrupt.                  */
      _DCMI_IRQN               = 78,  /** @brief DCMI global interrupt.                        */
      _CRYP_IRQN               = 80,  /** @brief RNG global interrupt.                         */
      _FPU_IRQN                = 81,  /** @brief FPU global interrupt.                         */
      _UART7_IRQN              = 82,  /** @brief UART7 global interrupt.                       */
      _UART8_IRQN              = 83,  /** @brief UART8 global interrupt.                       */
      _SPI4_IRQN               = 84,  /** @brief SPI4 global interrupt.                        */
      _SPI5_IRQN               = 85,  /** @brief SPI5 global interrupt.                        */
      _SPI6_IRQN               = 86,  /** @brief SPI6 global interrupt.                        */
      _SAI1_IRQN               = 87,  /** @brief SAI1 global interrupt.                        */
      _LTDC_IRQN               = 88,  /** @brief LTDC global interrupt.                        */
      _LTDC_ER_IRQN            = 89,  /** @brief LTDC error global interrupt.                  */
      _DMA2D_IRQN              = 90,  /** @brief DMA2D global interrupt.                       */
      _SAI2_IRQN               = 91,  /** @brief SAI2 global interrupt.                        */
      _QUADSPI_IRQN            = 92,  /** @brief QUAD-SPI global interrupt.                    */
      _LPTIM1_IRQN             = 93,  /** @brief LP TIM1 interrupt.                            */
      _CEC_IRQN                = 94,  /** @brief HDMI-CEC global interrupt.                    */
      _I2C4_EV_IRQN            = 95,  /** @brief I2C4 event interrupt.                         */
      _I2C4_ER_IRQN            = 96,  /** @brief I2C4 error interrupt.                         */
      _SPDIF_RX_IRQN           = 97,  /** @brief SPDIF-RX global interrupt.                    */
      _OTG_FS_EP1_OUT_IRQN     = 98,  /** @brief USB OTG HS2 global interrupt.                 */
      _OTG_FS_EP1_IN_IRQN      = 99,  /** @brief USB OTG HS2 end point 1 out global interrupt. */
      _OTG_FS_WKUP_IRQN        = 100, /** @brief USB OTG HS2 end point 1 in global interrupt.  */
      _OTG_FS_IRQN             = 101, /** @brief USB OTG HS2 wakeup on EXTI interrupt.         */
      _DMAMUX1_OVR_IRQN        = 102, /** @brief DMAMUX1 overrun interrupt.                    */
      _HRTIM1_Master_IRQN      = 103, /** @brief HRTIM master timer global interrupts.         */
      _HRTIM1_TIMA_IRQN        = 104, /** @brief HRTIM timer A global interrupt.               */
      _HRTIM1_TIMB_IRQN        = 105, /** @brief HRTIM timer B global interrupt.               */
      _HRTIM1_TIMC_IRQN        = 106, /** @brief HRTIM timer C global interrupt.               */
      _HRTIM1_TIMD_IRQN        = 107, /** @brief HRTIM timer D global interrupt.               */
      _HRTIM1_TIME_IRQN        = 108, /** @brief HRTIM timer E global interrupt.               */
      _HRTIM1_FLT_IRQN         = 109, /** @brief HRTIM fault global interrupt.                 */
      _DFSDM1_FLT0_IRQN        = 110, /** @brief DFSDM filter 1 interrupt.                     */
      _DFSDM1_FLT1_IRQN        = 111, /** @brief DFSDM filter 2 interrupt.                     */
      _DFSDM1_FLT2_IRQN        = 112, /** @brief DFSDM filter 3 interrupt.                     */
      _DFSDM1_FLT3_IRQN        = 113, /** @brief DFSDM filter 4 interrupt.                     */
      _SAI3_IRQN               = 114, /** @brief SAI3 global interrupt.                        */
      _SWPMI1_IRQN             = 115, /** @brief Serial wire interface 1 global interrupt.     */
      _TIM15_IRQN              = 116, /** @brief TIM15 global interrupt.                       */
      _TIM16_IRQN              = 117, /** @brief TIM16 global interrupt.                       */
      _TIM17_IRQN              = 118, /** @brief TIM17 global interrupt.                       */
      _MDIOS_WKUP_IRQN         = 119, /** @brief MDIOS wakeup interrupt.                       */
      _MDIOS_IRQN              = 120, /** @brief MDIOS global interrupt.                       */
      _JPEG_IRQN               = 121, /** @brief JPEG global interrupt.                        */
      _MDMA_IRQN               = 122, /** @brief MDMA global interrupt.                        */
      _DSI_IRQN                = 123, /** @brief DSI host global interrupt.                    */
      _SDMMC2_IRQN             = 124, /** @brief SDMMC2 global interrupt.                      */
      _HSEM1_IRQN              = 125, /** @brief HSEM1 global interrupt.                       */
      _HSEM2_IRQN              = 126, /** @brief HSEM2 global interrupt.                       */
      _ADC3_IRQN               = 127, /** @brief ADC3 global interrupt.                        */
      _DMAMUX2_OVR_IRQN        = 128, /** @brief DMAMUX2 overrun interrupt.                    */
      _BDMA_CH0_IRQN           = 129, /** @brief BDMA channel 0 global interrupt.              */
      _BDMA_CH1_IRQN           = 130, /** @brief BDMA channel 1 global interrupt.              */
      _BDMA_CH2_IRQN           = 131, /** @brief BDMA channel 2 global interrupt.              */
      _BDMA_CH3_IRQN           = 132, /** @brief BDMA channel 3 global interrupt.              */
      _BDMA_CH4_IRQN           = 133, /** @brief BDMA channel 4 global interrupt.              */
      _BDMA_CH5_IRQN           = 134, /** @brief BDMA channel 5 global interrupt.              */
      _BDMA_CH6_IRQN           = 135, /** @brief BDMA channel 6 global interrupt.              */
      _BDMA_CH7_IRQN           = 136, /** @brief BDMA channel 7 global interrupt.              */
      _COMP_IRQN               = 137, /** @brief COMP global interrupt.                        */
      _LPTIM2_IRQN             = 138, /** @brief LP TIM2 global interrupt.                     */
      _LPTIM3_IRQN             = 139, /** @brief LP TIM3 global interrupt.                     */
      _LPTIM4_IRQN             = 140, /** @brief LP TIM4 global interrupt.                     */
      _LPTIM5_IRQN             = 141, /** @brief LP TIM5 global interrupt.                     */
      _LPUART1_IRQN            = 142, /** @brief LP UART1 interrupt.                           */
      _WWDG_RST_IRQN           = 143, /** @brief Window watchdog reset interrupt.              */
      _CRS_IRQN                = 144, /** @brief Clock recovery global interrupt.              */
      _ECC_IRQN                = 145, /** @brief ECC diagnostic global interrupt.              */
      _SAI4_IRQN               = 146, /** @brief SAI4 global interrupt.                        */
      _HOLD_CORE_IRQN          = 148, /** @brief Hold core interrupt.                          */
      _WKUP_IRQN               = 149, /** @brief Interrupt for all 6 wake-up pins.             */
    }_irqn_t;

    /**********************************************************************************************
     * @section Exception Functions
     **********************************************************************************************/
    
    __IT_ATTR void _cm7_reset_exc()            {} /** @brief CM7 system reset exception.           */
    __IT_ATTR void _cm7_nmi_exc()              {} /** @brief CM7 non maskable interrupt exception. */
    __IT_ATTR void _cm7_hard_fault_exc()       {} /** @brief CM7 hard fault exception.             */
    __IT_ATTR void _cm7_mem_manage_fault_exc() {} /** @brief CM7 mem-manage (MPU) fault exception. */
    __IT_ATTR void _cm7_bus_fault_exc()        {} /** @brief CM7 bus (memory) fault exception.     */
    __IT_ATTR void _cm7_usage_fault_exc()      {} /** @brief CM7 usage fault exception.            */
    __IT_ATTR void _cm7_svc_exc()              {} /** @brief CM7 SVC exception.                    */
    __IT_ATTR void _cm7_debug_monitor_exc()    {} /** @brief CM7 debug monitor fault exception.    */
    __IT_ATTR void _cm7_pend_sv_exc()          {} /** @brief CM7 pend-SV exception                 */
    __IT_ATTR void _cm7_systick_exc()          {} /** @brief CM7 systick timer exception.          */

    __IT_ATTR void _cm4_reset_exc()            {} /** @brief CM4 system reset exception.           */
    __IT_ATTR void _cm4_nmi_exc()              {} /** @brief CM4 non maskable interrupt exception. */
    __IT_ATTR void _cm4_hard_fault_exc()       {} /** @brief CM4 hard fault exception.             */
    __IT_ATTR void _cm4_mem_manage_fault_exc() {} /** @brief CM4 mem-manage (MPU) fault exception. */
    __IT_ATTR void _cm4_bus_fault_exc()        {} /** @brief CM4 bus (memory) fault exception.     */
    __IT_ATTR void _cm4_usage_fault_exc()      {} /** @brief CM4 usage fault exception.            */
    __IT_ATTR void _cm4_svc_exc()              {} /** @brief CM4 SVC exception.                    */
    __IT_ATTR void _cm4_debug_monitor_exc()    {} /** @brief CM4 debug monitor fault exception.    */
    __IT_ATTR void _cm4_pend_sv_exc()          {} /** @brief CM4 pend-SV exception                 */
    __IT_ATTR void _cm4_systick_exc()          {} /** @brief CM4 systick timer exception.          */
    
    /**********************************************************************************************
     * @section IRQ Functions
     **********************************************************************************************/

    __IT_ATTR void _cm4_wwdg_irq()           {} /** @brief CM7 window watchdog interrupt.                */
    __IT_ATTR void _cm7_wwdg_irq()           {} /** @brief CM4 window watchdog interrupt.                */
    __IT_ATTR void _pvd_pvm_irq()            {} /** @brief PVD/AVD on EXTI line interrupt.               */
    __IT_ATTR void _rtc_tamp_stamp_irq()     {} /** @brief EXTI line timestamp/tamper interrupt.         */
    __IT_ATTR void _rtc_wkup_irq()           {} /** @brief RTC wakeup interrupt on EXTI line.            */
    __IT_ATTR void _flash_irq()              {} /** @brief FLASH global interrupt.                       */
    __IT_ATTR void _rcc_irq()                {} /** @brief RCC global interrupt.                         */
    __IT_ATTR void _exti0_irq()              {} /** @brief EXTI line 0 interrupt.                        */
    __IT_ATTR void _exti1_irq()              {} /** @brief EXTI line 1 interrupt.                        */
    __IT_ATTR void _exti2_irq()              {} /** @brief EXTI line 2 interrupt.                        */
    __IT_ATTR void _exti3_irq()              {} /** @brief EXTI line 3 interrupt.                        */
    __IT_ATTR void _exti4_irq()              {} /** @brief EXTI line 4 interrupt.                        */
    __IT_ATTR void _dma_str0_irq()           {} /** @brief DMA1 stream 0 global interrupt.               */
    __IT_ATTR void _dma_str1_irq()           {} /** @brief DMA1 stream 1 global interrupt.               */
    __IT_ATTR void _dma_str2_irq()           {} /** @brief DMA1 stream 2 global interrupt.               */
    __IT_ATTR void _dma_str3_irq()           {} /** @brief DMA1 stream 3 global interrupt.               */
    __IT_ATTR void _dma_str4_irq()           {} /** @brief DMA1 stream 4 global interrupt.               */
    __IT_ATTR void _dma_str5_irq()           {} /** @brief DMA1 stream 5 global interrupt.               */
    __IT_ATTR void _dma_str6_irq()           {} /** @brief DMA1 stream 6 global interrupt.               */
    __IT_ATTR void _adc1_2_irq()             {} /** @brief ADC1 and ADC2 global interrupts.              */
    __IT_ATTR void _fdcan1_it0_irq()         {} /** @brief FDCAN1 interrupt line 0.                      */
    __IT_ATTR void _fdcan2_it0_irq()         {} /** @brief FDCAN2 interrupt line 0.                      */
    __IT_ATTR void _fdcan1_it1_irq()         {} /** @brief FDCAN1 interrupt line 1.                      */
    __IT_ATTR void _fdcan2_it1_irq()         {} /** @brief FDCAN2 interrupt line 1.                      */
    __IT_ATTR void _exti9_5_irq()            {} /** @brief external line [9:5] interrupts.               */
    __IT_ATTR void _tim1_brk_irq()           {} /** @brief TIM1 break interrupt.                         */
    __IT_ATTR void _tim1_up_irq()            {} /** @brief TIM1 update interrupt.                        */
    __IT_ATTR void _tim1_trg_com_irq()       {} /** @brief TIM1 trigger and commutation interrupt.       */
    __IT_ATTR void _tim_cc_irq()             {} /** @brief TIM1 capture compare interrupt.               */
    __IT_ATTR void _tim2_irq()               {} /** @brief TIM2 global interrupt.                        */
    __IT_ATTR void _tim3_irq()               {} /** @brief TIM3 global interrupt.                        */
    __IT_ATTR void _tim4_irq()               {} /** @brief TIM4 global interrupt.                        */
    __IT_ATTR void _i2c1_ev_irq()            {} /** @brief I2C1 event interrupt.                         */
    __IT_ATTR void _i2c1_er_irq()            {} /** @brief I2C1 error interrupt.                         */
    __IT_ATTR void _i2c2_ev_irq()            {} /** @brief I2C2 event interrupt.                         */
    __IT_ATTR void _i2c2_er_irq()            {} /** @brief I2C2 error interrupt.                         */
    __IT_ATTR void _spi1_irq()               {} /** @brief SPI1 global interrupt.                        */
    __IT_ATTR void _spi2_irq()               {} /** @brief SPI2 global interrupt.                        */
    __IT_ATTR void _usart1_irq()             {} /** @brief USART1 global interrupt.                      */
    __IT_ATTR void _usart2_irq()             {} /** @brief USART2 global interrupt.                      */
    __IT_ATTR void _usart3_irq()             {} /** @brief USART3 global interrupt.                      */
    __IT_ATTR void _exti15_10_irq()          {} /** @brief External line [15:10] interrupts.             */
    __IT_ATTR void _rtc_alarm_irq()          {} /** @brief RTC A/B alarm to EXTI line interrupt.         */
    __IT_ATTR void _tim8_brk_tim12_irq()     {} /** @brief TIM8 break and TIM12 global interrupt.        */
    __IT_ATTR void _tim8_up_tim13_irq()      {} /** @brief TIM8 update and TIM13 global interrupt.       */
    __IT_ATTR void _tim8_trg_com_tim14_irq() {} /** @brief TIM8 trig/comm and TIM14 global interrupt.    */
    __IT_ATTR void _tim8_cc_irq()            {} /** @brief TIM8 capture compare interrupt.               */
    __IT_ATTR void _dma_str7_irq()           {} /** @brief DMA1 stream 7 interrupt.                      */
    __IT_ATTR void _fmc_irq()                {} /** @brief FMC global interrupt.                         */
    __IT_ATTR void _sdmmc1_irq()             {} /** @brief SDMMC1 global interrupt.                      */
    __IT_ATTR void _tim5_irq()               {} /** @brief TIM5 global interrupt.                        */
    __IT_ATTR void _spi3_irq()               {} /** @brief SPI3 global interrupt.                        */
    __IT_ATTR void _uart4_irq()              {} /** @brief UART4 global interrupt.                       */
    __IT_ATTR void _uart5_irq()              {} /** @brief UART5 global interrupt.                       */
    __IT_ATTR void _tim6_dac_irq()           {} /** @brief TIM6 global and DAC 1/2 underrun interrupts.  */
    __IT_ATTR void _tim7_irq()               {} /** @brief TIM7 global interrupt.                        */
    __IT_ATTR void _dma2_str0_irq()          {} /** @brief DMA2 stream 0 global interrupt.               */
    __IT_ATTR void _dma2_str1_irq()          {} /** @brief DMA2 stream 1 global interrupt.               */
    __IT_ATTR void _dma2_str2_irq()          {} /** @brief DMA2 stream 2 global interrupt.               */
    __IT_ATTR void _dma2_str3_irq()          {} /** @brief DMA2 stream 3 global interrupt.               */
    __IT_ATTR void _dma2_str4_irq()          {} /** @brief DMA2 stream 4 global interrupt.               */
    __IT_ATTR void _eth_irq()                {} /** @brief Ethernet global interrupt.                    */
    __IT_ATTR void _eth_wkup_irq()           {} /** @brief Ethernet wakeup on EXTI line interrupt.       */
    __IT_ATTR void _fdcan_cal_irq()          {} /** @brief FDCAN calibration unit interrupt.             */
    __IT_ATTR void _cm7_sev1_irq()           {} /** @brief CM7 send event interrupt for CM4.             */
    __IT_ATTR void _cm4_sev2_irq()           {} /** @brief CM4 send event interrupt for CM7.             */
    __IT_ATTR void _dma2_str5_irq()          {} /** @brief DMA2 stream 5 global interrupt.               */
    __IT_ATTR void _dma2_str6_irq()          {} /** @brief DMA2 stream 6 global interrupt.               */
    __IT_ATTR void _dma2_str7_irq()          {} /** @brief DMA2 stream 7 global interrupt.               */
    __IT_ATTR void _usart6_irq()             {} /** @brief USART6 global interrupt.                      */
    __IT_ATTR void _i2c3_ev_irq()            {} /** @brief I2C3 event interrupt.                         */
    __IT_ATTR void _i2c3_er_irq()            {} /** @brief I2C3 error interrupt.                         */
    __IT_ATTR void _otg_hs_ep1_out_irq()     {} /** @brief USB OTG HS end point 1 out global interrupt.  */
    __IT_ATTR void _otg_hs_ep1_in_irq()      {} /** @brief USB OTG HS end point 1 in global interrupt.   */
    __IT_ATTR void _otg_hs_wkup_irq()        {} /** @brief USB OTG HS wakeup on EXTI interrupt.          */
    __IT_ATTR void _otg_hs_irq()             {} /** @brief USB OTG HS global interrupt.                  */
    __IT_ATTR void _dcmi_irq()               {} /** @brief DCMI global interrupt.                        */
    __IT_ATTR void _cryp_irq()               {} /** @brief RNG global interrupt.                         */
    __IT_ATTR void _hash_rng_irq()           {} /** @brief HASH and RNG global interrupt.                */
    __IT_ATTR void _cm7_fpu_irq()            {} /** @brief CM7 FPU global interrupt.                     */
    __IT_ATTR void _cm4_fpu_irq()            {} /** @brief CM4 FPU global interrupt.                     */
    __IT_ATTR void _uart7_irq()              {} /** @brief UART7 global interrupt.                       */
    __IT_ATTR void _uart8_irq()              {} /** @brief UART8 global interrupt.                       */
    __IT_ATTR void _spi4_irq()               {} /** @brief SPI4 global interrupt.                        */
    __IT_ATTR void _spi5_irq()               {} /** @brief SPI5 global interrupt.                        */
    __IT_ATTR void _spi6_irq()               {} /** @brief SPI6 global interrupt.                        */
    __IT_ATTR void _sai1_irq()               {} /** @brief SAI1 global interrupt.                        */
    __IT_ATTR void _ltdc_irq()               {} /** @brief LTDC global interrupt.                        */
    __IT_ATTR void _ltdc_er_irq()            {} /** @brief LTDC error global interrupt.                  */
    __IT_ATTR void _dma2d_irq()              {} /** @brief DMA2D global interrupt.                       */
    __IT_ATTR void _sai2_irq()               {} /** @brief SAI2 global interrupt.                        */
    __IT_ATTR void _quadspi_irq()            {} /** @brief QUAD-SPI global interrupt.                    */
    __IT_ATTR void _lptim1_irq()             {} /** @brief LP TIM1 interrupt.                            */
    __IT_ATTR void _cec_irq()                {} /** @brief HDMI-CEC global interrupt.                    */
    __IT_ATTR void _i2c4_ev_irq()            {} /** @brief I2C4 event interrupt.                         */
    __IT_ATTR void _i2c4_er_irq()            {} /** @brief I2C4 error interrupt.                         */
    __IT_ATTR void _spdif_irq()              {} /** @brief SPDIF-RX global interrupt.                    */
    __IT_ATTR void _otg_fs_ep1_out_irq()     {} /** @brief USB OTG HS2 global interrupt.                 */
    __IT_ATTR void _otg_fs_ep1_in_irq()      {} /** @brief USB OTG HS2 end point 1 out global interrupt. */
    __IT_ATTR void _otg_fs_wkup_irq()        {} /** @brief USB OTG HS2 end point 1 in global interrupt.  */
    __IT_ATTR void _otg_fs_irq()             {} /** @brief USB OTG HS2 wakeup on EXTI interrupt.         */
    __IT_ATTR void _dmamux1_ovr_irq()        {} /** @brief DMAMUX1 overrun interrupt.                    */
    __IT_ATTR void _hrtim1_mst_irq()         {} /** @brief HRTIM master timer global interrupts.         */
    __IT_ATTR void _hrtim1_tima_irq()        {} /** @brief HRTIM timer A global interrupt.               */
    __IT_ATTR void _hrtim1_timb_irq()        {} /** @brief HRTIM timer B global interrupt.               */
    __IT_ATTR void _hrtim1_timc_irq()        {} /** @brief HRTIM timer C global interrupt.               */
    __IT_ATTR void _hrtim1_timd_irq()        {} /** @brief HRTIM timer D global interrupt.               */
    __IT_ATTR void _hrtim1_time_irq()        {} /** @brief HRTIM timer E global interrupt.               */
    __IT_ATTR void _hrtim1_flt_irq()         {} /** @brief HRTIM fault global interrupt.                 */
    __IT_ATTR void _dfsdm1_flt0_irq()        {} /** @brief DFSDM filter 1 interrupt.                     */
    __IT_ATTR void _dfsdm1_flt1_irq()        {} /** @brief DFSDM filter 2 interrupt.                     */
    __IT_ATTR void _dfsdm1_flt2_irq()        {} /** @brief DFSDM filter 3 interrupt.                     */
    __IT_ATTR void _dfsdm1_flt3_irq()        {} /** @brief DFSDM filter 4 interrupt.                     */
    __IT_ATTR void _sai3_irq()               {} /** @brief SAI3 global interrupt.                        */
    __IT_ATTR void _swpmi1_irq()             {} /** @brief Serial wire interface 1 global interrupt.     */
    __IT_ATTR void _tim15_irq()              {} /** @brief TIM15 global interrupt.                       */
    __IT_ATTR void _tim16_irq()              {} /** @brief TIM16 global interrupt.                       */
    __IT_ATTR void _tim17_irq()              {} /** @brief TIM17 global interrupt.                       */
    __IT_ATTR void _mdios_wkup_irq()         {} /** @brief MDIOS wakeup interrupt.                       */
    __IT_ATTR void _mdios_irq()              {} /** @brief MDIOS global interrupt.                       */
    __IT_ATTR void _jpeg_irq()               {} /** @brief JPEG global interrupt.                        */
    __IT_ATTR void _mdma_irq()               {} /** @brief MDMA global interrupt.                        */
    __IT_ATTR void _dsi_irq()                {} /** @brief DSI host global interrupt.                    */
    __IT_ATTR void _sdmmc2_irq()             {} /** @brief SDMMC2 global interrupt.                      */
    __IT_ATTR void _cm7_hsem1_irq()          {} /** @brief HSEM1 global interrupt.                       */
    __IT_ATTR void _cm4_hsem2_irq()          {} /** @brief HSEM2 global interrupt.                       */
    __IT_ATTR void _adc3_irq()               {} /** @brief ADC3 global interrupt.                        */
    __IT_ATTR void _dmamux2_ovr_irq()        {} /** @brief DMAMUX2 overrun interrupt.                    */
    __IT_ATTR void _bdma_ch0_irq()           {} /** @brief BDMA channel 0 global interrupt.              */
    __IT_ATTR void _bdma_ch1_irq()           {} /** @brief BDMA channel 1 global interrupt.              */
    __IT_ATTR void _bdma_ch2_irq()           {} /** @brief BDMA channel 2 global interrupt.              */
    __IT_ATTR void _bdma_ch3_irq()           {} /** @brief BDMA channel 3 global interrupt.              */
    __IT_ATTR void _bdma_ch4_irq()           {} /** @brief BDMA channel 4 global interrupt.              */
    __IT_ATTR void _bdma_ch5_irq()           {} /** @brief BDMA channel 5 global interrupt.              */
    __IT_ATTR void _bdma_ch6_irq()           {} /** @brief BDMA channel 6 global interrupt.              */
    __IT_ATTR void _bdma_ch7_irq()           {} /** @brief BDMA channel 7 global interrupt.              */
    __IT_ATTR void _comp_irq()               {} /** @brief COMP global interrupt.                        */
    __IT_ATTR void _lptim2_irq()             {} /** @brief LP TIM2 global interrupt.                     */
    __IT_ATTR void _lptim3_irq()             {} /** @brief LP TIM3 global interrupt.                     */
    __IT_ATTR void _lptim4_irq()             {} /** @brief LP TIM4 global interrupt.                     */
    __IT_ATTR void _lptim5_irq()             {} /** @brief LP TIM5 global interrupt.                     */
    __IT_ATTR void _lpuart_irq()             {} /** @brief LP UART1 interrupt.                           */
    __IT_ATTR void _cm7_wwdg_rst_irq()       {} /** @brief Window watchdog reset interrupt.              */
    __IT_ATTR void _cm4_wwdg_rst_irq()       {} /** @brief Window watchdog reset interrupt.              */
    __IT_ATTR void _crs_irq()                {} /** @brief Clock recovery global interrupt.              */
    __IT_ATTR void _ecc_irq()                {} /** @brief ECC diagnostic global interrupt.              */
    __IT_ATTR void _sai4_irq()               {} /** @brief SAI4 global interrupt.                        */
    __IT_ATTR void _cm7_hold_core_irq()      {} /** @brief Hold core interrupt.                          */
    __IT_ATTR void _cm4_hold_core_irq()      {} /** @brief Hold core interrupt.                          */
    __IT_ATTR void _wkup_irq()               {} /** @brief Interrupt for all 6 wake-up pins.             */

    /**********************************************************************************************
     * @section Vector Tables
     **********************************************************************************************/

    /** 
     * @brief Interrupt vector table for the ARM-M7 core. 
     */
    __attribute__((section(".cm7_vtable")))
    static const void* const __cm7_vtable[] = {
      &_cm7_stack_end,
      &_cm7_reset_exc,
      &_cm7_nmi_exc,
      &_cm7_hard_fault_exc,
      &_cm7_mem_manage_fault_exc,
      &_cm7_bus_fault_exc,
      &_cm7_usage_fault_exc,
      NULL,
      NULL,
      NULL,
      NULL,
      &_cm7_svc_exc,
      &_cm7_debug_monitor_exc,
      NULL,
      &_cm7_pend_sv_exc,
      &_cm7_systick_exc,
      &_cm7_wwdg_irq,
      &_pvd_pvm_irq,
      &_rtc_tamp_stamp_irq,
      &_rtc_wkup_irq,
      &_flash_irq,
      &_rcc_irq,
      &_exti0_irq,
      &_exti1_irq,
      &_exti2_irq,
      &_exti3_irq,
      &_exti4_irq,
      &_dma_str0_irq,
      &_dma_str1_irq,
      &_dma_str2_irq,
      &_dma_str3_irq,
      &_dma_str4_irq,
      &_dma_str5_irq,
      &_dma_str6_irq,
      &_adc1_2_irq,
      &_fdcan1_it0_irq,
      &_fdcan2_it0_irq,
      &_fdcan1_it1_irq,
      &_fdcan2_it1_irq,
      &_exti9_5_irq,
      &_tim1_brk_irq,
      &_tim1_up_irq,
      &_tim1_trg_com_irq,
      &_tim_cc_irq,
      &_tim2_irq,
      &_tim3_irq,
      &_tim4_irq,
      &_i2c1_ev_irq,
      &_i2c1_er_irq,
      &_i2c2_ev_irq,
      &_i2c2_er_irq,
      &_spi1_irq,
      &_spi2_irq,
      &_usart1_irq,
      &_usart2_irq,
      &_usart3_irq,
      &_exti15_10_irq,
      &_rtc_alarm_irq,
      NULL,
      &_tim8_brk_tim12_irq,
      &_tim8_up_tim13_irq,
      &_tim8_trg_com_tim14_irq,
      &_tim8_cc_irq,
      &_dma_str7_irq,
      &_fmc_irq,
      &_sdmmc1_irq,
      &_tim5_irq,
      &_spi3_irq,
      &_uart4_irq,
      &_uart5_irq,
      &_tim6_dac_irq,
      &_tim7_irq,
      &_dma2_str0_irq,
      &_dma2_str1_irq,
      &_dma2_str2_irq,
      &_dma2_str3_irq,
      &_dma2_str4_irq,
      &_eth_irq,
      &_eth_wkup_irq,
      &_fdcan_cal_irq,
      &_cm7_sev1_irq,
      &_cm4_sev2_irq,
      NULL,
      NULL,
      &_dma2_str5_irq,
      &_dma2_str6_irq,
      &_dma2_str7_irq,
      &_usart6_irq,
      &_i2c3_ev_irq,
      &_i2c3_er_irq,
      &_otg_hs_ep1_out_irq,
      &_otg_hs_ep1_in_irq,
      &_otg_hs_wkup_irq,
      &_otg_hs_irq,
      &_dcmi_irq,
      &_cryp_irq,
      &_hash_rng_irq,
      &_cm7_fpu_irq,
      &_uart7_irq,
      &_uart8_irq,
      &_spi4_irq,
      &_spi5_irq,
      &_spi6_irq,
      &_sai1_irq,
      &_ltdc_irq,
      &_ltdc_er_irq,
      &_dma2d_irq,
      &_sai2_irq,
      &_quadspi_irq,
      &_lptim1_irq,
      &_cec_irq,
      &_i2c4_ev_irq,
      &_i2c4_er_irq,
      &_spdif_irq,
      &_otg_fs_ep1_out_irq,
      &_otg_fs_ep1_in_irq,
      &_otg_fs_wkup_irq,
      &_otg_fs_irq,
      &_dmamux1_ovr_irq,
      &_hrtim1_mst_irq,
      &_hrtim1_tima_irq,
      &_hrtim1_timb_irq,
      &_hrtim1_timc_irq,
      &_hrtim1_timd_irq,
      &_hrtim1_time_irq,
      &_hrtim1_flt_irq,
      &_dfsdm1_flt0_irq,
      &_dfsdm1_flt1_irq,
      &_dfsdm1_flt2_irq,
      &_dfsdm1_flt3_irq,
      &_sai3_irq,
      &_swpmi1_irq,
      &_tim15_irq,
      &_tim16_irq,
      &_tim17_irq,
      &_mdios_wkup_irq,
      &_mdios_irq,
      &_jpeg_irq,
      &_mdma_irq,
      &_dsi_irq,
      &_sdmmc2_irq,
      &_cm7_hsem1_irq,
      NULL,
      &_adc3_irq,
      &_dmamux2_ovr_irq,
      &_bdma_ch0_irq,
      &_bdma_ch1_irq,
      &_bdma_ch2_irq,
      &_bdma_ch3_irq,
      &_bdma_ch4_irq,
      &_bdma_ch5_irq,
      &_bdma_ch6_irq,
      &_bdma_ch7_irq,
      &_comp_irq,
      &_lptim2_irq,
      &_lptim3_irq,
      &_lptim4_irq,
      &_lptim5_irq,
      &_lpuart_irq,
      &_cm7_wwdg_rst_irq,
      &_crs_irq,
      &_ecc_irq,
      &_sai4_irq,
      &_cm7_hold_core_irq,
      &_wkup_irq
    };

    /** 
     * @brief Interrupt vector table for the ARM-M4 core. 
     */
    __attribute__((section(".cm4_vtable")))
    static const void* const __cm4_vtable[] = {
      &_cm4_stack_end,
      &_cm4_reset_exc,
      &_cm4_nmi_exc,
      &_cm4_hard_fault_exc,
      &_cm4_mem_manage_fault_exc,
      &_cm4_bus_fault_exc,
      &_cm4_usage_fault_exc,
      NULL,
      NULL,
      NULL,
      NULL,
      &_cm4_svc_exc,
      &_cm4_debug_monitor_exc,
      NULL,
      &_cm4_pend_sv_exc,
      &_cm4_systick_exc,
      &_cm4_wwdg_irq,
      &_pvd_pvm_irq,
      &_rtc_tamp_stamp_irq,
      &_rtc_wkup_irq,
      &_flash_irq,
      &_rcc_irq,
      &_exti0_irq,
      &_exti1_irq,
      &_exti2_irq,
      &_exti3_irq,
      &_exti4_irq,
      &_dma_str0_irq,
      &_dma_str1_irq,
      &_dma_str2_irq,
      &_dma_str3_irq,
      &_dma_str4_irq,
      &_dma_str5_irq,
      &_dma_str6_irq,
      &_adc1_2_irq,
      &_fdcan1_it0_irq,
      &_fdcan2_it0_irq,
      &_fdcan1_it1_irq,
      &_fdcan2_it1_irq,
      &_exti9_5_irq,
      &_tim1_brk_irq,
      &_tim1_up_irq,
      &_tim1_trg_com_irq,
      &_tim_cc_irq,
      &_tim2_irq,
      &_tim3_irq,
      &_tim4_irq,
      &_i2c1_ev_irq,
      &_i2c1_er_irq,
      &_i2c2_ev_irq,
      &_i2c2_er_irq,
      &_spi1_irq,
      &_spi2_irq,
      &_usart1_irq,
      &_usart2_irq,
      &_usart3_irq,
      &_exti15_10_irq,
      &_rtc_alarm_irq,
      NULL,
      &_tim8_brk_tim12_irq,
      &_tim8_up_tim13_irq,
      &_tim8_trg_com_tim14_irq,
      &_tim8_cc_irq,
      &_dma_str7_irq,
      &_fmc_irq,
      &_sdmmc1_irq,
      &_tim5_irq,
      &_spi3_irq,
      &_uart4_irq,
      &_uart5_irq,
      &_tim6_dac_irq,
      &_tim7_irq,
      &_dma2_str0_irq,
      &_dma2_str1_irq,
      &_dma2_str2_irq,
      &_dma2_str3_irq,
      &_dma2_str4_irq,
      &_eth_irq,
      &_eth_wkup_irq,
      &_fdcan_cal_irq,
      &_cm7_sev1_irq,
      &_cm4_sev2_irq,
      NULL,
      NULL,
      &_dma2_str5_irq,
      &_dma2_str6_irq,
      &_dma2_str7_irq,
      &_usart6_irq,
      &_i2c3_ev_irq,
      &_i2c3_er_irq,
      &_otg_hs_ep1_out_irq,
      &_otg_hs_ep1_in_irq,
      &_otg_hs_wkup_irq,
      &_otg_hs_irq,
      &_dcmi_irq,
      &_cryp_irq,
      &_hash_rng_irq,
      &_cm4_fpu_irq,
      &_uart7_irq,
      &_uart8_irq,
      &_spi4_irq,
      &_spi5_irq,
      &_spi6_irq,
      &_sai1_irq,
      &_ltdc_irq,
      &_ltdc_er_irq,
      &_dma2d_irq,
      &_sai2_irq,
      &_quadspi_irq,
      &_lptim1_irq,
      &_cec_irq,
      &_i2c4_ev_irq,
      &_i2c4_er_irq,
      &_spdif_irq,
      &_otg_fs_ep1_out_irq,
      &_otg_fs_ep1_in_irq,
      &_otg_fs_wkup_irq,
      &_otg_fs_irq,
      &_dmamux1_ovr_irq,
      &_hrtim1_mst_irq,
      &_hrtim1_tima_irq,
      &_hrtim1_timb_irq,
      &_hrtim1_timc_irq,
      &_hrtim1_timd_irq,
      &_hrtim1_time_irq,
      &_hrtim1_flt_irq,
      &_dfsdm1_flt0_irq,
      &_dfsdm1_flt1_irq,
      &_dfsdm1_flt2_irq,
      &_dfsdm1_flt3_irq,
      &_sai3_irq,
      &_swpmi1_irq,
      &_tim15_irq,
      &_tim16_irq,
      &_tim17_irq,
      &_mdios_wkup_irq,
      &_mdios_irq,
      &_jpeg_irq,
      &_mdma_irq,
      &_dsi_irq,
      &_sdmmc2_irq,
      NULL,
      &_cm4_hsem2_irq,
      &_adc3_irq,
      &_dmamux2_ovr_irq,
      &_bdma_ch0_irq,
      &_bdma_ch1_irq,
      &_bdma_ch2_irq,
      &_bdma_ch3_irq,
      &_bdma_ch4_irq,
      &_bdma_ch5_irq,
      &_bdma_ch6_irq,
      &_bdma_ch7_irq,
      &_comp_irq,
      &_lptim2_irq,
      &_lptim3_irq,
      &_lptim4_irq,
      &_lptim5_irq,
      &_lpuart_irq,
      &_cm4_wwdg_rst_irq,
      &_crs_irq,
      &_ecc_irq,
      &_sai4_irq,
      &_cm4_hold_core_irq,
      &_wkup_irq
    };

  #ifdef __cplusplus
    } /* extern "C" */
  #endif

#endif /* SRC_PORT_GCC_STM32H745ZI_CM7_INTERNAL_INTERRUPT_H */