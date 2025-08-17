/**
 * This file is part of the Titan Project.
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
 * @file modules/internal/include/internal/interrupt.h
 * @authors Aaron McBride
 * @brief Reference information and prototypes for system interrupts.
 */

#pragma once
#include <stdint.h>

/**************************************************************************************************
 * @section Exception Handler Prototypes
 **************************************************************************************************/

/** @subsection CM7 exception handlers */

__attribute__((weak)) void cm7_reset_exc_handler();       /** @brief CM7_Reset exception. */
__attribute__((weak)) void cm7_nmi_exc_handler();         /** @brief CM7_Non-maskable interrupt. */
__attribute__((weak)) void cm7_hard_fault_exc_handler();  /** @brief CM7_Hard fault. */
__attribute__((weak)) void cm7_mem_manage_exc_handler();  /** @brief CM7_Memory management fault (MPU). */
__attribute__((weak)) void cm7_bus_fault_exc_handler();   /** @brief CM7_Bus fault. */
__attribute__((weak)) void cm7_usage_fault_exc_handler(); /** @brief CM7_Usage fault. */
__attribute__((weak)) void cm7_svc_exc_handler();         /** @brief CM7_System service call exception. */
__attribute__((weak)) void cm7_debug_mon_exc_handler();   /** @brief CM7_Debug monitor fault/exception. */
__attribute__((weak)) void cm7_pendsv_exc_handler();      /** @brief CM7_Pended system service call exception. */
__attribute__((weak)) void cm7_systick_exc_handler();     /** @brief CM7_SysTick interrupt. */

/** @subsection CM4 exception handlers */

__attribute__((weak)) void cm4_reset_exc_handler();       /** @brief CM4_Reset exception. */
__attribute__((weak)) void cm4_nmi_exc_handler();         /** @brief CM4_Non-maskable interrupt. */
__attribute__((weak)) void cm4_hard_fault_exc_handler();  /** @brief CM4_Hard fault. */
__attribute__((weak)) void cm4_mem_manage_exc_handler();  /** @brief CM4_Memory management fault (MPU). */
__attribute__((weak)) void cm4_bus_fault_exc_handler();   /** @brief CM4_Bus fault. */
__attribute__((weak)) void cm4_usage_fault_exc_handler(); /** @brief CM4_Usage fault. */
__attribute__((weak)) void cm4_svc_exc_handler();         /** @brief CM4_System service call exception. */
__attribute__((weak)) void cm4_debug_mon_exc_handler();   /** @brief CM4_Debug monitor fault/exception. */
__attribute__((weak)) void cm4_pendsv_exc_handler();      /** @brief CM4_Pended system service call exception. */
__attribute__((weak)) void cm4_systick_exc_handler();     /** @brief CM4_SysTick interrupt. */

/**************************************************************************************************
 * @section IRQ Handler Prototypes
 **************************************************************************************************/

__attribute__((weak)) void wwdg1_irq_handler();                  /** @brief Window watchdog interrupt (CM7 core). */
__attribute__((weak)) void wwdg2_irq_handler();                  /** @brief Window watchdog interrupt (CM4 core). */
__attribute__((weak)) void pvd_pvm_irq_handler();                /** @brief PVD through EXTI line. */
__attribute__((weak)) void rtc_tamp_stamp_css_lse_irq_handler(); /** @brief RTC tamper, timestamp. */
__attribute__((weak)) void rtc_wkup_irq_handler();               /** @brief RTC wakeup interrupt. */
__attribute__((weak)) void flash_irq_handler();                  /** @brief Flash memory. */
__attribute__((weak)) void rcc_irq_handler();                    /** @brief RCC global interrupt. */
__attribute__((weak)) void exti0_irq_handler();                  /** @brief EXTI line 0 interrupt. */
__attribute__((weak)) void exti1_irq_handler();                  /** @brief EXTI line 1 interrupt. */
__attribute__((weak)) void exti2_irq_handler();                  /** @brief EXTI line 2 interrupt. */
__attribute__((weak)) void exti3_irq_handler();                  /** @brief EXTI line 3 interrupt. */
__attribute__((weak)) void exti4_irq_handler();                  /** @brief EXTI line 4 interrupt. */
__attribute__((weak)) void dma_str0_irq_handler();               /** @brief DMA1 stream0. */
__attribute__((weak)) void dma_str1_irq_handler();               /** @brief DMA1 stream1. */
__attribute__((weak)) void dma_str2_irq_handler();               /** @brief DMA1 stream2. */
__attribute__((weak)) void dma_str3_irq_handler();               /** @brief DMA1 stream3. */
__attribute__((weak)) void dma_str4_irq_handler();               /** @brief DMA1 stream4. */
__attribute__((weak)) void dma_str5_irq_handler();               /** @brief DMA1 stream5. */
__attribute__((weak)) void dma_str6_irq_handler();               /** @brief DMA1 stream6. */
__attribute__((weak)) void adc1_2_irq_handler();                 /** @brief ADC1 and ADC2. */
__attribute__((weak)) void fdcan1_it0_irq_handler();             /** @brief FDCAN1 interrupt 0. */
__attribute__((weak)) void fdcan2_it0_irq_handler();             /** @brief FDCAN2 interrupt 0. */
__attribute__((weak)) void fdcan1_it1_irq_handler();             /** @brief FDCAN1 interrupt 1. */
__attribute__((weak)) void fdcan2_it1_irq_handler();             /** @brief FDCAN2 interrupt 1. */
__attribute__((weak)) void exti9_5_irq_handler();                /** @brief EXTI line[9:5] interrupts. */
__attribute__((weak)) void tim1_brk_irq_handler();               /** @brief TIM1 break interrupt. */
__attribute__((weak)) void tim1_up_irq_handler();                /** @brief TIM1 update interrupt. */
__attribute__((weak)) void tim1_trg_com_irq_handler();           /** @brief TIM1 trigger and commutation. */
__attribute__((weak)) void tim1_cc_irq_handler();                /** @brief TIM1 capture / compare. */
__attribute__((weak)) void tim2_irq_handler();                   /** @brief TIM2 global interrupt. */
__attribute__((weak)) void tim3_irq_handler();                   /** @brief TIM3 global interrupt. */
__attribute__((weak)) void tim4_irq_handler();                   /** @brief TIM4 global interrupt. */
__attribute__((weak)) void i2c1_ev_irq_handler();                /** @brief I2C1 event interrupt. */
__attribute__((weak)) void i2c1_er_irq_handler();                /** @brief I2C1 error interrupt. */
__attribute__((weak)) void i2c2_ev_irq_handler();                /** @brief I2C2 event interrupt. */
__attribute__((weak)) void i2c2_er_irq_handler();                /** @brief I2C2 error interrupt. */
__attribute__((weak)) void spi1_irq_handler();                   /** @brief SPI1 global interrupt. */
__attribute__((weak)) void spi2_irq_handler();                   /** @brief SPI2 global interrupt. */
__attribute__((weak)) void usart1_irq_handler();                 /** @brief USART1 global interrupt. */
__attribute__((weak)) void usart2_irq_handler();                 /** @brief USART2 global interrupt. */
__attribute__((weak)) void usart3_irq_handler();                 /** @brief USART3 global interrupt. */
__attribute__((weak)) void exti15_10_irq_handler();              /** @brief EXTI line[15:10] interrupts. */
__attribute__((weak)) void rtc_alarm_irq_handler();              /** @brief RTC alarms (A and B). */
__attribute__((weak)) void tim8_brk_tim12_irq_handler();         /** @brief TIM8 and 12 break global. */
__attribute__((weak)) void tim8_up_tim13_irq_handler();          /** @brief TIM8 and 13 update global. */
__attribute__((weak)) void tim8_trg_com_tim14_irq_handler();     /** @brief TIM8 and 14 trigger /commutation and global. */
__attribute__((weak)) void tim8_cc_irq_handler();                /** @brief TIM8 capture / compare. */
__attribute__((weak)) void dma1_str7_irq_handler();              /** @brief DMA1 stream7. */
__attribute__((weak)) void fmc_irq_handler();                    /** @brief FMC global interrupt. */
__attribute__((weak)) void sdmmc1_irq_handler();                 /** @brief SDMMC global interrupt. */
__attribute__((weak)) void tim5_irq_handler();                   /** @brief TIM5 global interrupt. */
__attribute__((weak)) void spi3_irq_handler();                   /** @brief SPI3 global interrupt. */
__attribute__((weak)) void uart4_irq_handler();                  /** @brief UART4 global interrupt. */
__attribute__((weak)) void uart5_irq_handler();                  /** @brief UART5 global interrupt. */
__attribute__((weak)) void tim6_dac_irq_handler();               /** @brief TIM6 global interrupt. */
__attribute__((weak)) void tim7_irq_handler();                   /** @brief TIM7 global interrupt. */
__attribute__((weak)) void dma2_str0_irq_handler();              /** @brief DMA2 stream0 interrupt. */
__attribute__((weak)) void dma2_str1_irq_handler();              /** @brief DMA2 stream1 interrupt. */
__attribute__((weak)) void dma2_str2_irq_handler();              /** @brief DMA2 stream2 interrupt. */
__attribute__((weak)) void dma2_str3_irq_handler();              /** @brief DMA2 stream3 interrupt. */
__attribute__((weak)) void dma2_str4_irq_handler();              /** @brief DMA2 stream4 interrupt. */
__attribute__((weak)) void eth_irq_handler();                    /** @brief Ethernet global interrupt. */
__attribute__((weak)) void eth_wkup_irq_handler();               /** @brief Ethernet wakeup through EXTI. */
__attribute__((weak)) void fdcan_cal_irq_handler();              /** @brief CAN2TX interrupts. */
__attribute__((weak)) void cpu1_sev_irq_handler();               /** @brief Arm cortex-m7 (cpu 1) send event interrupt (used by CM4 core). */
__attribute__((weak)) void cpu2_sev_irq_handler();               /** @brief Arm cortex-m4 (cpu 2) send event interrupt (used by CM7 core). */
__attribute__((weak)) void dma2_str5_irq_handler();              /** @brief DMA2 stream5 interrupt. */
__attribute__((weak)) void dma2_str6_irq_handler();              /** @brief DMA2 stream6 interrupt. */
__attribute__((weak)) void dma2_str7_irq_handler();              /** @brief DMA2 stream7 interrupt. */
__attribute__((weak)) void usart6_irq_handler();                 /** @brief USART6 global interrupt. */
__attribute__((weak)) void i2c3_ev_irq_handler();                /** @brief I2C3 event interrupt. */
__attribute__((weak)) void i2c3_er_irq_handler();                /** @brief I2C3 error interrupt. */
__attribute__((weak)) void otg_hs_ep1_out_irq_handler();         /** @brief OTG_HS out global interrupt. */
__attribute__((weak)) void otg_hs_ep1_in_irq_handler();          /** @brief OTG_HS in global interrupt. */
__attribute__((weak)) void otg_hs_wkup_irq_handler();            /** @brief OTG_HS wakeup interrupt. */
__attribute__((weak)) void otg_hs_irq_handler();                 /** @brief OTG_HS global interrupt. */
__attribute__((weak)) void dcmi_irq_handler();                   /** @brief DCMI global interrupt. */
__attribute__((weak)) void cryp_irq_handler();                   /** @brief CRYP global interrupt. */
__attribute__((weak)) void hash_rng_irq_handler();               /** @brief HASH and RNG. */
__attribute__((weak)) void cpu1_fpu_irq_handler();               /** @brief Floating point unit interrupt (CM7 core). */
__attribute__((weak)) void cpu2_fpu_irq_handler();               /** @brief Floating point unit interrupt (CM4 core). */
__attribute__((weak)) void uart7_irq_handler();                  /** @brief UART7 global interrupt. */
__attribute__((weak)) void uart8_irq_handler();                  /** @brief UART8 global interrupt. */
__attribute__((weak)) void spi4_irq_handler();                   /** @brief SPI4 global interrupt. */
__attribute__((weak)) void spi5_irq_handler();                   /** @brief SPI5 global interrupt. */
__attribute__((weak)) void spi6_irq_handler();                   /** @brief SPI6 global interrupt. */
__attribute__((weak)) void sai1_irq_handler();                   /** @brief SAI1 global interrupt. */
__attribute__((weak)) void ltdc_irq_handler();                   /** @brief LCD-TFT global interrupt. */
__attribute__((weak)) void ltdc_er_irq_handler();                /** @brief LCD-TFT error interrupt. */
__attribute__((weak)) void dma2d_irq_handler();                  /** @brief DMA2D global interrupt. */
__attribute__((weak)) void sai2_irq_handler();                   /** @brief SAI2 global interrupt. */
__attribute__((weak)) void quadspi_irq_handler();                /** @brief QuadSPI global interrupt. */
__attribute__((weak)) void lptim1_irq_handler();                 /** @brief LPTIM1 global interrupt. */
__attribute__((weak)) void cec_irq_handler();                    /** @brief HDMI-CEC global interrupt. */
__attribute__((weak)) void i2c4_ev_irq_handler();                /** @brief I2C4 event interrupt. */
__attribute__((weak)) void i2c4_er_irq_handler();                /** @brief I2C4 error interrupt. */
__attribute__((weak)) void spdif_irq_handler();                  /** @brief SPDIFRX global interrupt. */
__attribute__((weak)) void otg_fs_ep1_out_irq_handler();         /** @brief OTG_FS out global interrupt. */
__attribute__((weak)) void otg_fs_ep1_in_irq_handler();          /** @brief OTG_FS in global interrupt. */
__attribute__((weak)) void otg_fs_wkup_irq_handler();            /** @brief OTG_FS wakeup. */
__attribute__((weak)) void otg_fs_irq_handler();                 /** @brief OTG_FS global interrupt. */
__attribute__((weak)) void dmamux1_ov_irq_handler();             /** @brief DMAMUX1 overrun interrupt. */
__attribute__((weak)) void hrtim_mst_irq_handler();              /** @brief HRTIM master timer interrupt. */
__attribute__((weak)) void hrtim_tima_irq_handler();             /** @brief HRTIM timer A interrupt. */
__attribute__((weak)) void hrtim_timb_irq_handler();             /** @brief HRTIM timer B interrupt. */
__attribute__((weak)) void hrtim_timc_irq_handler();             /** @brief HRTIM timer C interrupt. */
__attribute__((weak)) void hrtim_timd_irq_handler();             /** @brief HRTIM timer D interrupt. */
__attribute__((weak)) void hrtim_time_irq_handler();             /** @brief HRTIM timer E interrupt. */
__attribute__((weak)) void hrtim_flt_irq_handler();              /** @brief HRTIM fault interrupt. */
__attribute__((weak)) void dfsdm1_flt0_irq_handler();            /** @brief DFSDM1 filter 0 interrupt. */
__attribute__((weak)) void dfsdm1_flt1_irq_handler();            /** @brief DFSDM1 filter 1 interrupt. */
__attribute__((weak)) void dfsdm1_flt2_irq_handler();            /** @brief DFSDM1 filter 2 interrupt. */
__attribute__((weak)) void dfsdm1_flt3_irq_handler();            /** @brief DFSDM1 filter 3 interrupt. */
__attribute__((weak)) void sai3_irq_handler();                   /** @brief SAI3 global interrupt. */
__attribute__((weak)) void swpmi_irq_handler();                  /** @brief SWPMI global interrupt. */
__attribute__((weak)) void tim15_irq_handler();                  /** @brief TIM15 global interrupt. */
__attribute__((weak)) void tim16_irq_handler();                  /** @brief TIM16 global interrupt. */
__attribute__((weak)) void tim17_irq_handler();                  /** @brief TIM17 global interrupt. */
__attribute__((weak)) void mdios_wkup_irq_handler();             /** @brief MDIOS wakeup. */
__attribute__((weak)) void mdios_irq_handler();                  /** @brief MDIOS global interrupt. */
__attribute__((weak)) void jpeg_irq_handler();                   /** @brief JPEG global interrupt. */
__attribute__((weak)) void mdma_irq_handler();                   /** @brief MDMA. */
__attribute__((weak)) void sdmmc2_irq_handler();                 /** @brief SDMMC global interrupt. */
__attribute__((weak)) void hsem0_irq_handler();                  /** @brief HSEM global interrupt 0 (CM7 core). */
__attribute__((weak)) void hsem1_irq_handler();                  /** @brief HSEM global interrupt 1 (CM4 core). */
__attribute__((weak)) void adc3_irq_handler();                   /** @brief ADC3 global interrupt. */
__attribute__((weak)) void dmamux2_ovr_irq_handler();            /** @brief DMAMUX2 overrun interrupt. */
__attribute__((weak)) void bdma_ch1_irq_handler();               /** @brief BDMA channel 1 interrupt. */
__attribute__((weak)) void bdma_ch2_irq_handler();               /** @brief BDMA channel 2 interrupt. */
__attribute__((weak)) void bdma_ch3_irq_handler();               /** @brief BDMA channel 3 interrupt. */
__attribute__((weak)) void bdma_ch4_irq_handler();               /** @brief BDMA channel 4 interrupt. */
__attribute__((weak)) void bdma_ch5_irq_handler();               /** @brief BDMA channel 5 interrupt. */
__attribute__((weak)) void bdma_ch6_irq_handler();               /** @brief BDMA channel 6 interrupt. */
__attribute__((weak)) void bdma_ch7_irq_handler();               /** @brief BDMA channel 7 interrupt. */
__attribute__((weak)) void bdma_ch8_irq_handler();               /** @brief BDMA channel 8 interrupt. */
__attribute__((weak)) void comp_irq_handler();                   /** @brief COMP1 and COMP2. */
__attribute__((weak)) void lptim2_irq_handler();                 /** @brief LPTIM2 timer interrupt. */
__attribute__((weak)) void lptim3_irq_handler();                 /** @brief LPTIM3 timer interrupt. */
__attribute__((weak)) void lptim4_irq_handler();                 /** @brief LPTIM4 timer interrupt. */
__attribute__((weak)) void lptim5_irq_handler();                 /** @brief LPTIM5 timer interrupt. */
__attribute__((weak)) void lpuart_irq_handler();                 /** @brief LPUART global interrupt. */
__attribute__((weak)) void wwdg1_rst_irq_handler();              /** @brief Window watchdog reset interrupt (used by CM4 core). */
__attribute__((weak)) void wwdg2_rst_irq_handler();              /** @brief Window watchdog reset interrupt (used by CM7 core). */
__attribute__((weak)) void crs_irq_handler();                    /** @brief Clock recovery system global interrupt. */
__attribute__((weak)) void sai4_irq_handler();                   /** @brief SAI4 global interrupt. */
__attribute__((weak)) void cpu1_hold_core_irq_handler();         /** @brief Hold core interrupt (CM7 core). */
__attribute__((weak)) void cpu2_hold_core_irq_handler();         /** @brief Hold core interrupt (CM4 core). */
__attribute__((weak)) void wkup_irq_handler();                   /** @brief WKUP1 to WKUP6 pins. */

/**************************************************************************************************
 * @section Miscellaneous Constants
 **************************************************************************************************/

/** @brief The number of implement IRQs */
static const int32_t IRQ_COUNT = 150;

/** @brief Number of priority bits supported the NVIC. */
static const int32_t NVIC_PRIO_BITS = 4;

/** @brief Maximum supported exception priority value. */
static const int32_t NVIC_MAX_PRIO = 16;

/** @brief Offset between exception and IRQ numbers. */
static const int32_t IRQ_EXC_OFFSET = 16;

/**************************************************************************************************
 * @section Exception Numbers
 **************************************************************************************************/

static const int32_t RST_EXC_NUM         = 1;  /** @brief Reset exceptios (both cores). */
static const int32_t NMI_EXC_NUM         = 2;  /** @brief Non-maskable interrupt (both cores). */
static const int32_t HARD_FAULT_EXC_NUM  = 3;  /** @brief Hard fault (both cores). */
static const int32_t MEM_MANAGE_EXC_NUM  = 4;  /** @brief Memory management fault (MPU (both cores)). */
static const int32_t BUS_FAULT_EXC_NUM   = 5;  /** @brief Bus fault (both cores). */
static const int32_t USAGE_FAULT_EXC_NUM = 6;  /** @brief Usage fault (both cores). */
static const int32_t SVC_EXC_NUM         = 11; /** @brief System service call exception (both cores). */
static const int32_t DEBUG_MON_EXC_NUM   = 12; /** @brief Debug monitor fault/exception (both cores). */
static const int32_t PENDSV_EXC_NUM      = 14; /** @brief Pended system service call exception (both cores). */
static const int32_t SYSTICK_EXC_NUM     = 15; /** @brief SysTick interrupt (both cores). */

/**************************************************************************************************
 * @section IRQ Numbers
 **************************************************************************************************/

static const int32_t PVD_PVM_IRQ_NUM                = 1;   /** @brief PVD through EXTI line. */
static const int32_t RTC_TAMP_STAMP_CSS_LSE_IRQ_NUM = 2;   /** @brief RTC tamper, timestamp. */
static const int32_t RTC_WKUP_IRQ_NUM               = 3;   /** @brief RTC wakeup interrupt. */
static const int32_t FLASH_IRQ_NUM                  = 4;   /** @brief Flash memory. */
static const int32_t RCC_IRQ_NUM                    = 5;   /** @brief RCC global interrupt. */
static const int32_t ADC1_2_IRQ_NUM                 = 18;  /** @brief ADC1 and ADC2. */
static const int32_t EXTI9_5_IRQ_NUM                = 23;  /** @brief EXTI line[9:5] interrupts. */
static const int32_t TIM1_BRK_IRQ_NUM               = 24;  /** @brief TIM1 break interrupt. */
static const int32_t TIM1_UP_IRQ_NUM                = 25;  /** @brief TIM1 update interrupt. */
static const int32_t TIM1_TRG_COM_IRQ_NUM           = 26;  /** @brief TIM1 trigger and commutation. */
static const int32_t EXTI15_10_IRQ_NUM              = 40;  /** @brief EXTI line[15:10] interrupts. */
static const int32_t RTC_ALARM_IRQ_NUM              = 41;  /** @brief RTC alarms (A and B). */
static const int32_t TIM8_BRK_TIM12_IRQ_NUM         = 43;  /** @brief TIM8 and 12 break global. */
static const int32_t TIM8_UP_TIM13_IRQ_NUM          = 44;  /** @brief TIM8 and 13 update global. */
static const int32_t TIM8_TRG_COM_TIM14_IRQ_NUM     = 45;  /** @brief TIM8 and 14 trigger /commutation and global. */
static const int32_t FMC_IRQ_NUM                    = 48;  /** @brief FMC global interrupt. */
static const int32_t TIM6_DAC_IRQ_NUM               = 54;  /** @brief TIM6 global interrupt. */
static const int32_t ETH_IRQ_NUM                    = 61;  /** @brief Ethernet global interrupt. */
static const int32_t ETH_WKUP_IRQ_NUM               = 62;  /** @brief Ethernet wakeup through EXTI. */
static const int32_t FDCAN_CAL_IRQ_NUM              = 63;  /** @brief CAN2TX interrupts. */  
static const int32_t OTG_HS_EP1_OUT_IRQ_NUM         = 74;  /** @brief OTG_HS out global interrupt. */
static const int32_t OTG_HS_EP1_IN_IRQ_NUM          = 75;  /** @brief OTG_HS in global interrupt. */
static const int32_t OTG_HS_WKUP_IRQ_NUM            = 76;  /** @brief OTG_HS wakeup interrupt. */
static const int32_t OTG_HS_IRQ_NUM                 = 77;  /** @brief OTG_HS global interrupt. */
static const int32_t DCMI_IRQ_NUM                   = 78;  /** @brief DCMI global interrupt. */
static const int32_t CRYP_IRQ_NUM                   = 79;  /** @brief CRYP global interrupt. */
static const int32_t HASH_RNG_IRQ_NUM               = 80;  /** @brief HASH and RNG. */
static const int32_t LTDC_IRQ_NUM                   = 88;  /** @brief LCD-TFT global interrupt. */
static const int32_t LTDC_ER_IRQ_NUM                = 89;  /** @brief LCD-TFT error interrupt. */
static const int32_t DMA2D_IRQ_NUM                  = 90;  /** @brief DMA2D global interrupt. */
static const int32_t QUADSPI_IRQ_NUM                = 92;  /** @brief QuadSPI global interrupt. */
static const int32_t CEC_IRQ_NUM                    = 94;  /** @brief HDMI-CEC global interrupt. */
static const int32_t SPDIF_IRQ_NUM                  = 97;  /** @brief SPDIFRX global interrupt. */
static const int32_t OTG_FS_EP1_OUT_IRQ_NUM         = 98;  /** @brief OTG_FS out global interrupt. */
static const int32_t OTG_FS_EP1_IN_IRQ_NUM          = 99;  /** @brief OTG_FS in global interrupt. */
static const int32_t OTG_FS_WKUP_IRQ_NUM            = 100; /** @brief OTG_FS wakeup. */
static const int32_t OTG_FS_IRQ_NUM                 = 101; /** @brief OTG_FS global interrupt. */
static const int32_t DMAMUX1_OV_IRQ_NUM             = 102; /** @brief DMAMUX1 overrun interrupt. */
static const int32_t HRTIM_MST_IRQ_NUM              = 103; /** @brief HRTIM master timer interrupt. */
static const int32_t HRTIM_FLT_IRQ_NUM              = 109; /** @brief HRTIM fault interrupt. */
static const int32_t SWPMI_IRQ_NUM                  = 115; /** @brief SWPMI global interrupt. */
static const int32_t MDIOS_WKUP_IRQ_NUM             = 119; /** @brief MDIOS wakeup. */
static const int32_t MDIOS_IRQ_NUM                  = 120; /** @brief MDIOS global interrupt. */
static const int32_t JPEG_IRQ_NUM                   = 121; /** @brief JPEG global interrupt. */
static const int32_t MDMA_IRQ_NUM                   = 122; /** @brief MDMA global interrupt. */
static const int32_t ADC3_IRQ_NUM                   = 127; /** @brief ADC3 global interrupt. */
static const int32_t DMAMUX2_OVR_IRQ_NUM            = 128; /** @brief DMAMUX2 overrun interrupt. */
static const int32_t COMP_IRQ_NUM                   = 137; /** @brief COMP1 and COMP2. */
static const int32_t LPUART_IRQ_NUM                 = 142; /** @brief LPUART global interrupt. */
static const int32_t CRS_IRQ_NUM                    = 144; /** @brief Clock recovery system globa. */
static const int32_t WKUP_IRQ_NUM                   = 149; /** @brief WKUP1 to WKUP6 pins. */

static const int32_t WWDGx_IRQ_NUM[3] = {
  [1] = 0, /** @brief Window watchdog interrupt (CM7 core). */
  [2] = 0, /** @brief Window watchdog interrupt (CM4 core). */
};

static const int32_t CPUx_SEV_IRQ_NUM[3] = {
  [1] = 64, /** @brief Arm cortex-m7 send event interrupt (used by CM4). */
  [2] = 65, /** @brief Arm cortex-m4 send event interrupt (used by CM7). */
};

static const int32_t HSEMx_IRQ_NUM[2] = {
  [0] = 125, /** @brief HSEM global interrupt 0. */
  [1] = 126, /** @brief HSEM global interrupt 1. */
};

static const int32_t WWDGx_RST_IRQ_NUM[3] = {
  [1] = 143, /** @brief Window watchdog 2 reset interrupt (used by CM7) */
  [2] = 143, /** @brief Window watchdog 1 reset interrupt (used by CM4) */
};

static const int32_t CPUx_FPU_IRQ_NUM[3] = {
  [1] = 81, /** @brief Floating point unit interrupt (used by CM4). */
  [2] = 81, /** @brief Floating point unit interrupt (used by CM7). */
};

static const int32_t CPUx_HOLD_CORE_IRQ_NUM[3] = {
  [1] = 148, /** @brief Hold core interrupt (CM7 core). */
  [2] = 148, /** @brief Hold core interrupt (CM4 core). */
};

static const int32_t HRTIM_TIMx_IRQ_NUM[6] = {
  [1] = 104, /** @brief HRTIM timer A interrupt. */
  [2] = 105, /** @brief HRTIM timer B interrupt. */
  [3] = 106, /** @brief HRTIM timer C interrupt. */
  [4] = 107, /** @brief HRTIM timer D interrupt. */
  [5] = 108, /** @brief HRTIM timer E interrupt. */
};

static const int32_t BDMA_CHx_IRQ_NUM[9] = {
  [1] = 129, /** @brief BDMA channel 1 interrupt. */
  [2] = 130, /** @brief BDMA channel 2 interrupt. */
  [3] = 131, /** @brief BDMA channel 3 interrupt. */
  [4] = 132, /** @brief BDMA channel 4 interrupt. */
  [5] = 133, /** @brief BDMA channel 5 interrupt. */
  [6] = 134, /** @brief BDMA channel 6 interrupt. */
  [7] = 135, /** @brief BDMA channel 7 interrupt. */
  [8] = 136, /** @brief BDMA channel 8 interrupt. */
};

static const int32_t I2Cx_EV_IRQ_NUM[5] = {
  [1] = 31, /** @brief I2C1 event interrupt. */
  [2] = 33, /** @brief I2C2 event interrupt. */
  [3] = 72, /** @brief I2C3 event interrupt. */
  [4] = 95, /** @brief I2C4 event interrupt. */
};

static const int32_t I2Cx_ER_IRQ_NUM[5] = {
  [1] = 32, /** @brief I2C1 error interrupt. */
  [2] = 34, /** @brief I2C2 error interrupt. */
  [3] = 73, /** @brief I2C3 error interrupt. */
  [4] = 96, /** @brief I2C4 error interrupt. */
};

static const int32_t SAIx_IRQ_NUM[5] = {
  [1] = 87,  /** @brief SAI1 global interrupt. */
  [2] = 91,  /** @brief SAI2 global interrupt. */
  [3] = 114, /** @brief SAI3 global interrupt. */
  [4] = 146, /** @brief SAI4 global interrupt. */
};

static const int32_t SDMMCx_IRQ_NUM[3] = {
  [1] = 49,  /** @brief SDMMC1 global interrupt. */
  [2] = 124, /** @brief SDMMC2 global interrupt. */
};

static const int32_t SPIx_IRQ_NUM[7] = {
  [1] = 35, /** @brief SPI1 global interrupt. */
  [2] = 36, /** @brief SPI2 global interrupt. */
  [3] = 51, /** @brief SPI3 global interrupt. */
  [4] = 84, /** @brief SPI4 global interrupt. */
  [5] = 85, /** @brief SPI5 global interrupt. */
  [6] = 86, /** @brief SPI6 global interrupt. */
};

static const int32_t LPTIMx_IRQ_NUM[6] = {
  [1] = 93,  /** @brief LPTIM1 global interrupt. */
  [2] = 138, /** @brief LPTIM2 timer interrupt. */
  [3] = 139, /** @brief LPTIM3 timer interrupt. */
  [4] = 140, /** @brief LPTIM4 timer interrupt. */
  [5] = 141, /** @brief LPTIM5 timer interrupt. */
};

static const int32_t EXTIx_IRQ_NUM[5] = {
  [0] = 6,  /** @brief EXTI line 0 interrupt. */
  [1] = 7,  /** @brief EXTI line 1 interrupt. */
  [2] = 8,  /** @brief EXTI line 2 interrupt. */
  [3] = 9,  /** @brief EXTI line 3interrupt. */
  [4] = 10, /** @brief EXTI line 4interrupt. */
};

static const int32_t DFSDM1_FLTx_IRQ_NUM[4] = {
  [0] = 110, /** @brief DFSDM1 filter 0 interrupt. */
  [1] = 111, /** @brief DFSDM1 filter 1 interrupt. */
  [2] = 112, /** @brief DFSDM1 filter 2 interrupt. */
  [3] = 113, /** @brief DFSDM1 filter 3 interrupt. */
};

static const int32_t TIMx_IRQ_NUM[18] = {
  [2]  = 28,  /** @brief TIM2 global interrupt. */
  [3]  = 29,  /** @brief TIM3 global interrupt. */
  [4]  = 30,  /** @brief TIM4 global interrupt. */
  [5]  = 50,  /** @brief TIM5 global interrupt. */
  [7]  = 55,  /** @brief TIM7 global interrupt. */
  [15] = 116, /** @brief TIM15 global interrupt. */
  [16] = 117, /** @brief TIM16 global interrupt. */
  [17] = 118, /** @brief TIM17 global interrupt. */
};

static const int32_t USARTx_IRQ_NUM[7] = {
  [1] = 37, /** @brief USART1 global interrupt. */
  [2] = 38, /** @brief USART2 global interrupt. */
  [3] = 39, /** @brief USART3 global interrupt. */
  [6] = 71, /** @brief USART6 global interrupt. */
};

static const int32_t UARTx_IRQ_NUM[9] = {
  [4] = 52, /** @brief UART4 global interrupt. */
  [5] = 53, /** @brief UART5 global interrupt. */
  [7] = 82, /** @brief UART7 global interrupt. */
  [8] = 83, /** @brief UART8 global interrupt. */
};

static const int32_t TIMx_CC_IRQ_NUM[9] = {
  [1] = 27, /** @brief TIM1 capture / compare. */
  [8] = 46, /** @brief TIM8 capture / compare. */
};

static const int32_t DMAx_STRx_IRQ_NUM[3][8] = {
  [1] = {
    [0] = 11, /** @brief DMA1 stream0 interrupt. */
    [1] = 12, /** @brief DMA1 stream1 interrupt. */
    [2] = 13, /** @brief DMA1 stream2 interrupt. */
    [3] = 14, /** @brief DMA1 stream3 interrupt. */
    [4] = 15, /** @brief DMA1 stream4 interrupt. */
    [5] = 16, /** @brief DMA1 stream5 interrupt. */
    [6] = 17, /** @brief DMA1 stream6 interrupt. */
    [7] = 47, /** @brief DMA1 stream7 interrupt. */
  },
  [2] = {
    [0] = 56, /** @brief DMA2 stream0 interrupt. */
    [1] = 57, /** @brief DMA2 stream1 interrupt. */
    [2] = 58, /** @brief DMA2 stream2 interrupt. */
    [3] = 59, /** @brief DMA2 stream3 interrupt. */
    [4] = 60, /** @brief DMA2 stream4 interrupt. */
    [5] = 68, /** @brief DMA2 stream5 interrupt. */
    [6] = 69, /** @brief DMA2 stream6 interrupt. */
    [7] = 70, /** @brief DMA2 stream7 interrupt. */
  },
};

static const int32_t FDCANx_ITx_IRQ_NUM[3][2] = {
  [1] = {
    [0] = 19, /** @brief FDCAN1 interrupt 0. */
    [1] = 21, /** @brief FDCAN1 interrupt 1. */
  },
  [2] = {
    [0] = 20, /** @brief FDCAN2 interrupt 0. */
    [1] = 22, /** @brief FDCAN2 interrupt 1. */
  },
};