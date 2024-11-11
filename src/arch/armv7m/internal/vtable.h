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
 * @file arch/armv7m/internal/vtable.h
 * @authors Aaron McBride
 * @brief Contains vtable struct and function declarations.
 * @warning - Internal file, unstable API.
 */

#pragma once
#include <stdint.h>
#include "include/tal/attributes.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  /**************************************************************************************************
   * @section Vtable Reference Defines
   **************************************************************************************************/

  #define vtable_irq_count 128 /** @brief Denotes the number of implemented IRQs */

  /**************************************************************************************************
   * @section Interrupt Handler Function Declarations
   **************************************************************************************************/

  tal_fn_attr_weak(reset_handler) void reset_handler(void);
  tal_fn_attr_weak(nmi_handler) void nmi_handler(void);
  tal_fn_attr_weak(hardfault_handler) void hardfault_handler(void);
  tal_fn_attr_weak(memmanage_handler) void memmanage_handler(void);
  tal_fn_attr_weak(busfault_handler) void busfault_handler(void);
  tal_fn_attr_weak(usagefault_handler) void usagefault_handler(void);
  tal_fn_attr_weak(svc_handler) void svc_handler(void);
  tal_fn_attr_weak(debug_handler) void debug_handler(void);
  tal_fn_attr_weak(pendsv_handler) void pendsv_handler(void);
  tal_fn_attr_weak(systick_handler) void systick_handler(void);
  tal_fn_attr_weak(irq_1_handler) void irq_1_handler(void);
  tal_fn_attr_weak(irq_2_handler) void irq_2_handler(void);
  tal_fn_attr_weak(irq_3_handler) void irq_3_handler(void);
  tal_fn_attr_weak(irq_4_handler) void irq_4_handler(void);
  tal_fn_attr_weak(irq_5_handler) void irq_5_handler(void);
  tal_fn_attr_weak(irq_6_handler) void irq_6_handler(void);
  tal_fn_attr_weak(irq_7_handler) void irq_7_handler(void);
  tal_fn_attr_weak(irq_8_handler) void irq_8_handler(void);
  tal_fn_attr_weak(irq_9_handler) void irq_9_handler(void);
  tal_fn_attr_weak(irq_10_handler) void irq_10_handler(void);
  tal_fn_attr_weak(irq_11_handler) void irq_11_handler(void);
  tal_fn_attr_weak(irq_12_handler) void irq_12_handler(void);
  tal_fn_attr_weak(irq_13_handler) void irq_13_handler(void);
  tal_fn_attr_weak(irq_14_handler) void irq_14_handler(void);
  tal_fn_attr_weak(irq_15_handler) void irq_15_handler(void);
  tal_fn_attr_weak(irq_16_handler) void irq_16_handler(void);
  tal_fn_attr_weak(irq_17_handler) void irq_17_handler(void);
  tal_fn_attr_weak(irq_18_handler) void irq_18_handler(void);
  tal_fn_attr_weak(irq_19_handler) void irq_19_handler(void);
  tal_fn_attr_weak(irq_20_handler) void irq_20_handler(void);
  tal_fn_attr_weak(irq_21_handler) void irq_21_handler(void);
  tal_fn_attr_weak(irq_22_handler) void irq_22_handler(void);
  tal_fn_attr_weak(irq_23_handler) void irq_23_handler(void);
  tal_fn_attr_weak(irq_24_handler) void irq_24_handler(void);
  tal_fn_attr_weak(irq_25_handler) void irq_25_handler(void);
  tal_fn_attr_weak(irq_26_handler) void irq_26_handler(void);
  tal_fn_attr_weak(irq_27_handler) void irq_27_handler(void);
  tal_fn_attr_weak(irq_28_handler) void irq_28_handler(void);
  tal_fn_attr_weak(irq_29_handler) void irq_29_handler(void);
  tal_fn_attr_weak(irq_30_handler) void irq_30_handler(void);
  tal_fn_attr_weak(irq_31_handler) void irq_31_handler(void);
  tal_fn_attr_weak(irq_32_handler) void irq_32_handler(void);
  tal_fn_attr_weak(irq_33_handler) void irq_33_handler(void);
  tal_fn_attr_weak(irq_34_handler) void irq_34_handler(void);
  tal_fn_attr_weak(irq_35_handler) void irq_35_handler(void);
  tal_fn_attr_weak(irq_36_handler) void irq_36_handler(void);
  tal_fn_attr_weak(irq_37_handler) void irq_37_handler(void);
  tal_fn_attr_weak(irq_38_handler) void irq_38_handler(void);
  tal_fn_attr_weak(irq_39_handler) void irq_39_handler(void);
  tal_fn_attr_weak(irq_40_handler) void irq_40_handler(void);
  tal_fn_attr_weak(irq_41_handler) void irq_41_handler(void);
  tal_fn_attr_weak(irq_42_handler) void irq_42_handler(void);
  tal_fn_attr_weak(irq_43_handler) void irq_43_handler(void);
  tal_fn_attr_weak(irq_44_handler) void irq_44_handler(void);
  tal_fn_attr_weak(irq_45_handler) void irq_45_handler(void);
  tal_fn_attr_weak(irq_46_handler) void irq_46_handler(void);
  tal_fn_attr_weak(irq_47_handler) void irq_47_handler(void);
  tal_fn_attr_weak(irq_48_handler) void irq_48_handler(void);
  tal_fn_attr_weak(irq_49_handler) void irq_49_handler(void);
  tal_fn_attr_weak(irq_50_handler) void irq_50_handler(void);
  tal_fn_attr_weak(irq_51_handler) void irq_51_handler(void);
  tal_fn_attr_weak(irq_52_handler) void irq_52_handler(void);
  tal_fn_attr_weak(irq_53_handler) void irq_53_handler(void);
  tal_fn_attr_weak(irq_54_handler) void irq_54_handler(void);
  tal_fn_attr_weak(irq_55_handler) void irq_55_handler(void);
  tal_fn_attr_weak(irq_56_handler) void irq_56_handler(void);
  tal_fn_attr_weak(irq_57_handler) void irq_57_handler(void);
  tal_fn_attr_weak(irq_58_handler) void irq_58_handler(void);
  tal_fn_attr_weak(irq_59_handler) void irq_59_handler(void);
  tal_fn_attr_weak(irq_60_handler) void irq_60_handler(void);
  tal_fn_attr_weak(irq_61_handler) void irq_61_handler(void);
  tal_fn_attr_weak(irq_62_handler) void irq_62_handler(void);
  tal_fn_attr_weak(irq_63_handler) void irq_63_handler(void);
  tal_fn_attr_weak(irq_64_handler) void irq_64_handler(void);
  tal_fn_attr_weak(irq_65_handler) void irq_65_handler(void);
  tal_fn_attr_weak(irq_66_handler) void irq_66_handler(void);
  tal_fn_attr_weak(irq_67_handler) void irq_67_handler(void);
  tal_fn_attr_weak(irq_68_handler) void irq_68_handler(void);
  tal_fn_attr_weak(irq_69_handler) void irq_69_handler(void);
  tal_fn_attr_weak(irq_70_handler) void irq_70_handler(void);
  tal_fn_attr_weak(irq_71_handler) void irq_71_handler(void);
  tal_fn_attr_weak(irq_72_handler) void irq_72_handler(void);
  tal_fn_attr_weak(irq_73_handler) void irq_73_handler(void);
  tal_fn_attr_weak(irq_74_handler) void irq_74_handler(void);
  tal_fn_attr_weak(irq_75_handler) void irq_75_handler(void);
  tal_fn_attr_weak(irq_76_handler) void irq_76_handler(void);
  tal_fn_attr_weak(irq_77_handler) void irq_77_handler(void);
  tal_fn_attr_weak(irq_78_handler) void irq_78_handler(void);
  tal_fn_attr_weak(irq_79_handler) void irq_79_handler(void);
  tal_fn_attr_weak(irq_80_handler) void irq_80_handler(void);
  tal_fn_attr_weak(irq_81_handler) void irq_81_handler(void);
  tal_fn_attr_weak(irq_82_handler) void irq_82_handler(void);
  tal_fn_attr_weak(irq_83_handler) void irq_83_handler(void);
  tal_fn_attr_weak(irq_84_handler) void irq_84_handler(void);
  tal_fn_attr_weak(irq_85_handler) void irq_85_handler(void);
  tal_fn_attr_weak(irq_86_handler) void irq_86_handler(void);
  tal_fn_attr_weak(irq_87_handler) void irq_87_handler(void);
  tal_fn_attr_weak(irq_88_handler) void irq_88_handler(void);
  tal_fn_attr_weak(irq_89_handler) void irq_89_handler(void);
  tal_fn_attr_weak(irq_90_handler) void irq_90_handler(void);
  tal_fn_attr_weak(irq_91_handler) void irq_91_handler(void);
  tal_fn_attr_weak(irq_92_handler) void irq_92_handler(void);
  tal_fn_attr_weak(irq_93_handler) void irq_93_handler(void);
  tal_fn_attr_weak(irq_94_handler) void irq_94_handler(void);
  tal_fn_attr_weak(irq_95_handler) void irq_95_handler(void);
  tal_fn_attr_weak(irq_96_handler) void irq_96_handler(void);
  tal_fn_attr_weak(irq_97_handler) void irq_97_handler(void);
  tal_fn_attr_weak(irq_98_handler) void irq_98_handler(void);
  tal_fn_attr_weak(irq_99_handler) void irq_99_handler(void);
  tal_fn_attr_weak(irq_100_handler) void irq_100_handler(void);
  tal_fn_attr_weak(irq_101_handler) void irq_101_handler(void);
  tal_fn_attr_weak(irq_102_handler) void irq_102_handler(void);
  tal_fn_attr_weak(irq_103_handler) void irq_103_handler(void);
  tal_fn_attr_weak(irq_104_handler) void irq_104_handler(void);
  tal_fn_attr_weak(irq_105_handler) void irq_105_handler(void);
  tal_fn_attr_weak(irq_106_handler) void irq_106_handler(void);
  tal_fn_attr_weak(irq_107_handler) void irq_107_handler(void);
  tal_fn_attr_weak(irq_108_handler) void irq_108_handler(void);
  tal_fn_attr_weak(irq_109_handler) void irq_109_handler(void);
  tal_fn_attr_weak(irq_110_handler) void irq_110_handler(void);
  tal_fn_attr_weak(irq_111_handler) void irq_111_handler(void);
  tal_fn_attr_weak(irq_112_handler) void irq_112_handler(void);
  tal_fn_attr_weak(irq_113_handler) void irq_113_handler(void);
  tal_fn_attr_weak(irq_114_handler) void irq_114_handler(void);
  tal_fn_attr_weak(irq_115_handler) void irq_115_handler(void);
  tal_fn_attr_weak(irq_116_handler) void irq_116_handler(void);
  tal_fn_attr_weak(irq_117_handler) void irq_117_handler(void);
  tal_fn_attr_weak(irq_118_handler) void irq_118_handler(void);
  tal_fn_attr_weak(irq_119_handler) void irq_119_handler(void);
  tal_fn_attr_weak(irq_120_handler) void irq_120_handler(void);
  tal_fn_attr_weak(irq_121_handler) void irq_121_handler(void);
  tal_fn_attr_weak(irq_122_handler) void irq_122_handler(void);
  tal_fn_attr_weak(irq_123_handler) void irq_123_handler(void);
  tal_fn_attr_weak(irq_124_handler) void irq_124_handler(void);
  tal_fn_attr_weak(irq_125_handler) void irq_125_handler(void);
  tal_fn_attr_weak(irq_126_handler) void irq_126_handler(void);
  tal_fn_attr_weak(irq_127_handler) void irq_127_handler(void);
  tal_fn_attr_weak(irq_128_handler) void irq_128_handler(void);

  /**************************************************************************************************
   * @section Vtable Struct Type Definition
   **************************************************************************************************/

  typedef struct {
    void (*reset_handler)(void);
    void (*nmi_handler)(void);
    void (*hardfault_handler)(void);
    void (*memmanage_handler)(void);
    void (*busfault_handler)(void);
    void (*usagefault_handler)(void);
    uint32_t reserved;
    uint32_t reserved;
    uint32_t reserved;
    uint32_t reserved;
    void (*svc_handler)(void);
    void (*debug_handler)(void);
    uint32_t reserved;
    void (*pendsv_handler)(void);
    void (*systick_handler)(void);
    void (*irq_handler_array[vtable_irq_count])(void);
  }vtable_t;

  /**************************************************************************************************
   * @section Vtable Struct Declaration
   **************************************************************************************************/

  tal_var_attr_section(".vtable") const vtable_t vtable = {
    .reset_handler = &reset_handler,
    .nmi_handler = &nmi_handler,
    .hardfault_handler = &hardfault_handler,
    .memmanage_handler = &memmanage_handler,
    .busfault_handler = &busfault_handler,
    .usagefault_handler = &usagefault_handler,
    .reserved = 0,
    .reserved = 0,
    .reserved = 0,
    .reserved = 0,
    .svc_handler = &svc_handler,
    .debug_handler = &debug_handler,
    .reserved = 0,
    .pendsv_handler = &pendsv_handler,
    .systick_handler = &systick_handler,
    .irq_handler_array = {
      &irq_1_handler,
      &irq_2_handler,
      &irq_3_handler,
      &irq_4_handler,
      &irq_5_handler,
      &irq_6_handler,
      &irq_7_handler,
      &irq_8_handler,
      &irq_9_handler,
      &irq_10_handler,
      &irq_11_handler,
      &irq_12_handler,
      &irq_13_handler,
      &irq_14_handler,
      &irq_15_handler,
      &irq_16_handler,
      &irq_17_handler,
      &irq_18_handler,
      &irq_19_handler,
      &irq_20_handler,
      &irq_21_handler,
      &irq_22_handler,
      &irq_23_handler,
      &irq_24_handler,
      &irq_25_handler,
      &irq_26_handler,
      &irq_27_handler,
      &irq_28_handler,
      &irq_29_handler,
      &irq_30_handler,
      &irq_31_handler,
      &irq_32_handler,
      &irq_33_handler,
      &irq_34_handler,
      &irq_35_handler,
      &irq_36_handler,
      &irq_37_handler,
      &irq_38_handler,
      &irq_39_handler,
      &irq_40_handler,
      &irq_41_handler,
      &irq_42_handler,
      &irq_43_handler,
      &irq_44_handler,
      &irq_45_handler,
      &irq_46_handler,
      &irq_47_handler,
      &irq_48_handler,
      &irq_49_handler,
      &irq_50_handler,
      &irq_51_handler,
      &irq_52_handler,
      &irq_53_handler,
      &irq_54_handler,
      &irq_55_handler,
      &irq_56_handler,
      &irq_57_handler,
      &irq_58_handler,
      &irq_59_handler,
      &irq_60_handler,
      &irq_61_handler,
      &irq_62_handler,
      &irq_63_handler,
      &irq_64_handler,
      &irq_65_handler,
      &irq_66_handler,
      &irq_67_handler,
      &irq_68_handler,
      &irq_69_handler,
      &irq_70_handler,
      &irq_71_handler,
      &irq_72_handler,
      &irq_73_handler,
      &irq_74_handler,
      &irq_75_handler,
      &irq_76_handler,
      &irq_77_handler,
      &irq_78_handler,
      &irq_79_handler,
      &irq_80_handler,
      &irq_81_handler,
      &irq_82_handler,
      &irq_83_handler,
      &irq_84_handler,
      &irq_85_handler,
      &irq_86_handler,
      &irq_87_handler,
      &irq_88_handler,
      &irq_89_handler,
      &irq_90_handler,
      &irq_91_handler,
      &irq_92_handler,
      &irq_93_handler,
      &irq_94_handler,
      &irq_95_handler,
      &irq_96_handler,
      &irq_97_handler,
      &irq_98_handler,
      &irq_99_handler,
      &irq_100_handler,
      &irq_101_handler,
      &irq_102_handler,
      &irq_103_handler,
      &irq_104_handler,
      &irq_105_handler,
      &irq_106_handler,
      &irq_107_handler,
      &irq_108_handler,
      &irq_109_handler,
      &irq_110_handler,
      &irq_111_handler,
      &irq_112_handler,
      &irq_113_handler,
      &irq_114_handler,
      &irq_115_handler,
      &irq_116_handler,
      &irq_117_handler,
      &irq_118_handler,
      &irq_119_handler,
      &irq_120_handler,
      &irq_121_handler,
      &irq_122_handler,
      &irq_123_handler,
      &irq_124_handler,
      &irq_125_handler,
      &irq_126_handler,
      &irq_127_handler,
      &irq_128_handler,
    }
  };

#if defined(__cplusplus)
  }
#endif