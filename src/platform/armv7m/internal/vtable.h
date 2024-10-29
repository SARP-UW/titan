/**
 * This file is part of the Titan Avionics Library
 * Copyright (c) 2024 Aaron McBride.
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
 */

/**
 * @file vtable.hpp
 * @authors Aaron McBride
 * @brief Contains the vector table & base/primary handlers.
 */

#pragma once
#include <stdint.h>
#include "common/util/attribute.h"

#if defined(__cplusplus)
  extern "C" {
#endif

  ti_fn_attr_weak void reset_handler(void);
  ti_fn_attr_weak void nmi_handler(void);
  ti_fn_attr_weak void hard_fault_handler(void);
  ti_fn_attr_weak void mem_manage_handler(void);
  ti_fn_attr_weak void bus_fault_handler(void);
  ti_fn_attr_weak void usage_fault_handler(void);
  ti_fn_attr_weak void sv_call_handler(void);
  ti_fn_attr_weak void debug_monitor_handler(void);
  ti_fn_attr_weak void pend_sv_handler(void);
  ti_fn_attr_weak void systick_handler(void);
  ti_fn_attr_weak void irq_0_handler(void);
  ti_fn_attr_weak void irq_1_handler(void);
  ti_fn_attr_weak void irq_2_handler(void);
  ti_fn_attr_weak void irq_3_handler(void);
  ti_fn_attr_weak void irq_4_handler(void);
  ti_fn_attr_weak void irq_5_handler(void);
  ti_fn_attr_weak void irq_6_handler(void);
  ti_fn_attr_weak void irq_7_handler(void);
  ti_fn_attr_weak void irq_8_handler(void);
  ti_fn_attr_weak void irq_9_handler(void);
  ti_fn_attr_weak void irq_10_handler(void);
  ti_fn_attr_weak void irq_11_handler(void);
  ti_fn_attr_weak void irq_12_handler(void);
  ti_fn_attr_weak void irq_13_handler(void);
  ti_fn_attr_weak void irq_14_handler(void);
  ti_fn_attr_weak void irq_15_handler(void);
  ti_fn_attr_weak void irq_16_handler(void);
  ti_fn_attr_weak void irq_17_handler(void);
  ti_fn_attr_weak void irq_18_handler(void);
  ti_fn_attr_weak void irq_19_handler(void);
  ti_fn_attr_weak void irq_20_handler(void);
  ti_fn_attr_weak void irq_21_handler(void);
  ti_fn_attr_weak void irq_22_handler(void);
  ti_fn_attr_weak void irq_23_handler(void);
  ti_fn_attr_weak void irq_24_handler(void);
  ti_fn_attr_weak void irq_25_handler(void);
  ti_fn_attr_weak void irq_26_handler(void);
  ti_fn_attr_weak void irq_27_handler(void);
  ti_fn_attr_weak void irq_28_handler(void);
  ti_fn_attr_weak void irq_29_handler(void);
  ti_fn_attr_weak void irq_30_handler(void);
  ti_fn_attr_weak void irq_31_handler(void);
  ti_fn_attr_weak void irq_32_handler(void);
  ti_fn_attr_weak void irq_33_handler(void);
  ti_fn_attr_weak void irq_34_handler(void);
  ti_fn_attr_weak void irq_35_handler(void);
  ti_fn_attr_weak void irq_36_handler(void);
  ti_fn_attr_weak void irq_37_handler(void);
  ti_fn_attr_weak void irq_38_handler(void);
  ti_fn_attr_weak void irq_39_handler(void);
  ti_fn_attr_weak void irq_40_handler(void);
  ti_fn_attr_weak void irq_41_handler(void);
  ti_fn_attr_weak void irq_42_handler(void);
  ti_fn_attr_weak void irq_43_handler(void);
  ti_fn_attr_weak void irq_44_handler(void);
  ti_fn_attr_weak void irq_45_handler(void);
  ti_fn_attr_weak void irq_46_handler(void);
  ti_fn_attr_weak void irq_47_handler(void);
  ti_fn_attr_weak void irq_48_handler(void);
  ti_fn_attr_weak void irq_49_handler(void);
  ti_fn_attr_weak void irq_50_handler(void);
  ti_fn_attr_weak void irq_51_handler(void);
  ti_fn_attr_weak void irq_52_handler(void);
  ti_fn_attr_weak void irq_53_handler(void);
  ti_fn_attr_weak void irq_54_handler(void);
  ti_fn_attr_weak void irq_55_handler(void);
  ti_fn_attr_weak void irq_56_handler(void);
  ti_fn_attr_weak void irq_57_handler(void);
  ti_fn_attr_weak void irq_58_handler(void);
  ti_fn_attr_weak void irq_59_handler(void);
  ti_fn_attr_weak void irq_60_handler(void);
  ti_fn_attr_weak void irq_61_handler(void);
  ti_fn_attr_weak void irq_62_handler(void);
  ti_fn_attr_weak void irq_63_handler(void);
  ti_fn_attr_weak void irq_64_handler(void);
  ti_fn_attr_weak void irq_65_handler(void);
  ti_fn_attr_weak void irq_66_handler(void);
  ti_fn_attr_weak void irq_67_handler(void);
  ti_fn_attr_weak void irq_68_handler(void);
  ti_fn_attr_weak void irq_69_handler(void);
  ti_fn_attr_weak void irq_70_handler(void);
  ti_fn_attr_weak void irq_71_handler(void);
  ti_fn_attr_weak void irq_72_handler(void);
  ti_fn_attr_weak void irq_73_handler(void);
  ti_fn_attr_weak void irq_74_handler(void);
  ti_fn_attr_weak void irq_75_handler(void);
  ti_fn_attr_weak void irq_76_handler(void);
  ti_fn_attr_weak void irq_77_handler(void);
  ti_fn_attr_weak void irq_78_handler(void);
  ti_fn_attr_weak void irq_79_handler(void);
  ti_fn_attr_weak void irq_80_handler(void);
  ti_fn_attr_weak void irq_81_handler(void);
  ti_fn_attr_weak void irq_82_handler(void);
  ti_fn_attr_weak void irq_83_handler(void);
  ti_fn_attr_weak void irq_84_handler(void);
  ti_fn_attr_weak void irq_85_handler(void);
  ti_fn_attr_weak void irq_86_handler(void);
  ti_fn_attr_weak void irq_87_handler(void);
  ti_fn_attr_weak void irq_88_handler(void);
  ti_fn_attr_weak void irq_89_handler(void);
  ti_fn_attr_weak void irq_90_handler(void);
  ti_fn_attr_weak void irq_91_handler(void);
  ti_fn_attr_weak void irq_92_handler(void);
  ti_fn_attr_weak void irq_93_handler(void);
  ti_fn_attr_weak void irq_94_handler(void);
  ti_fn_attr_weak void irq_95_handler(void);
  ti_fn_attr_weak void irq_96_handler(void);
  ti_fn_attr_weak void irq_97_handler(void);
  ti_fn_attr_weak void irq_98_handler(void);
  ti_fn_attr_weak void irq_99_handler(void);
  ti_fn_attr_weak void irq_100_handler(void);
  ti_fn_attr_weak void irq_101_handler(void);
  ti_fn_attr_weak void irq_102_handler(void);
  ti_fn_attr_weak void irq_103_handler(void);
  ti_fn_attr_weak void irq_104_handler(void);
  ti_fn_attr_weak void irq_105_handler(void);
  ti_fn_attr_weak void irq_106_handler(void);
  ti_fn_attr_weak void irq_107_handler(void);
  ti_fn_attr_weak void irq_108_handler(void);
  ti_fn_attr_weak void irq_109_handler(void);
  ti_fn_attr_weak void irq_110_handler(void);
  ti_fn_attr_weak void irq_111_handler(void);
  ti_fn_attr_weak void irq_112_handler(void);
  ti_fn_attr_weak void irq_113_handler(void);
  ti_fn_attr_weak void irq_114_handler(void);
  ti_fn_attr_weak void irq_115_handler(void);
  ti_fn_attr_weak void irq_116_handler(void);
  ti_fn_attr_weak void irq_117_handler(void);
  ti_fn_attr_weak void irq_118_handler(void);
  ti_fn_attr_weak void irq_119_handler(void);
  ti_fn_attr_weak void irq_120_handler(void);
  ti_fn_attr_weak void irq_121_handler(void);
  ti_fn_attr_weak void irq_122_handler(void);
  ti_fn_attr_weak void irq_123_handler(void);
  ti_fn_attr_weak void irq_124_handler(void);
  ti_fn_attr_weak void irq_125_handler(void);
  ti_fn_attr_weak void irq_126_handler(void);
  ti_fn_attr_weak void irq_127_handler(void);
  ti_fn_attr_weak void irq_128_handler(void);

  typedef struct {
    uint32_t stack_pointer;
    uint32_t reset_handler;
    uint32_t nmi_handler;
    uint32_t hard_fault_handler;
    uint32_t mem_manage_handler;
    uint32_t bus_fault_handler;
    uint32_t usage_fault_handler;
    uint32_t reserved;
    uint32_t reserved;
    uint32_t reserved;
    uint32_t sv_call_handler;
    uint32_t debug_monitor_handler;
    uint32_t reserved;
    uint32_t pend_sv_handler;
    uint32_t systick_handler;
    uint32_t irq_0_handler;
    uint32_t irq_1_handler;
    uint32_t irq_2_handler;
    uint32_t irq_3_handler;
    uint32_t irq_4_handler;
    uint32_t irq_5_handler;
    uint32_t irq_6_handler;
    uint32_t irq_7_handler;
    uint32_t irq_8_handler;
    uint32_t irq_9_handler;
    uint32_t irq_10_handler;
    uint32_t irq_11_handler;
    uint32_t irq_12_handler;
    uint32_t irq_13_handler;
    uint32_t irq_14_handler;
    uint32_t irq_15_handler;
    uint32_t irq_16_handler;
    uint32_t irq_17_handler;
    uint32_t irq_18_handler;
    uint32_t irq_19_handler;
    uint32_t irq_20_handler;
    uint32_t irq_21_handler;
    uint32_t irq_22_handler;
    uint32_t irq_23_handler;
    uint32_t irq_24_handler;
    uint32_t irq_25_handler;
    uint32_t irq_26_handler;
    uint32_t irq_27_handler;
    uint32_t irq_28_handler;
    uint32_t irq_29_handler;
    uint32_t irq_30_handler;
    uint32_t irq_31_handler;
    uint32_t irq_32_handler;
    uint32_t irq_33_handler;
    uint32_t irq_34_handler;
    uint32_t irq_35_handler;
    uint32_t irq_36_handler;
    uint32_t irq_37_handler;
    uint32_t irq_38_handler;
    uint32_t irq_39_handler;
    uint32_t irq_40_handler;
    uint32_t irq_41_handler;
    uint32_t irq_42_handler;
    uint32_t irq_43_handler;
    uint32_t irq_44_handler;
    uint32_t irq_45_handler;
    uint32_t irq_46_handler;
    uint32_t irq_47_handler;
    uint32_t irq_48_handler;
    uint32_t irq_49_handler;
    uint32_t irq_50_handler;
    uint32_t irq_51_handler;
    uint32_t irq_52_handler;
    uint32_t irq_53_handler;
    uint32_t irq_54_handler;
    uint32_t irq_55_handler;
    uint32_t irq_56_handler;
    uint32_t irq_57_handler;
    uint32_t irq_58_handler;
    uint32_t irq_59_handler;
    uint32_t irq_60_handler;
    uint32_t irq_61_handler;
    uint32_t irq_62_handler;
    uint32_t irq_63_handler;
    uint32_t irq_64_handler;
    uint32_t irq_65_handler;
    uint32_t irq_66_handler;
    uint32_t irq_67_handler;
    uint32_t irq_68_handler;
    uint32_t irq_69_handler;
    uint32_t irq_70_handler;
    uint32_t irq_71_handler;
    uint32_t irq_72_handler;
    uint32_t irq_73_handler;
    uint32_t irq_74_handler;
    uint32_t irq_75_handler;
    uint32_t irq_76_handler;
    uint32_t irq_77_handler;
    uint32_t irq_78_handler;
    uint32_t irq_79_handler;
    uint32_t irq_80_handler;
    uint32_t irq_81_handler;
    uint32_t irq_82_handler;
    uint32_t irq_83_handler;
    uint32_t irq_84_handler;
    uint32_t irq_85_handler;
    uint32_t irq_86_handler;
    uint32_t irq_87_handler;
    uint32_t irq_88_handler;
    uint32_t irq_89_handler;
    uint32_t irq_90_handler;
    uint32_t irq_91_handler;
    uint32_t irq_92_handler;
    uint32_t irq_93_handler;
    uint32_t irq_94_handler;
    uint32_t irq_95_handler;
    uint32_t irq_96_handler;
    uint32_t irq_97_handler;
    uint32_t irq_98_handler;
    uint32_t irq_99_handler;
    uint32_t irq_100_handler;
    uint32_t irq_101_handler;
    uint32_t irq_102_handler;
    uint32_t irq_103_handler;
    uint32_t irq_104_handler;
    uint32_t irq_105_handler;
    uint32_t irq_106_handler;
    uint32_t irq_107_handler;
    uint32_t irq_108_handler;
    uint32_t irq_109_handler;
    uint32_t irq_110_handler;
    uint32_t irq_111_handler;
    uint32_t irq_112_handler;
    uint32_t irq_113_handler;
    uint32_t irq_114_handler;
    uint32_t irq_115_handler;
    uint32_t irq_116_handler;
    uint32_t irq_117_handler;
    uint32_t irq_118_handler;
    uint32_t irq_119_handler;
    uint32_t irq_120_handler;
    uint32_t irq_121_handler;
    uint32_t irq_122_handler;
    uint32_t irq_123_handler;
    uint32_t irq_124_handler;
    uint32_t irq_125_handler;
    uint32_t irq_126_handler;
    uint32_t irq_127_handler;
    uint32_t irq_128_handler;
  }ti_vtable_t_;

  const ti_vtable_t_ vtable_ = {
    .stack_pointer = 0,
    .reset_handler = (uint32_t)&reset_handler,
    .nmi_handler = (uint32_t)&nmi_handler,
    .hard_fault_handler = (uint32_t)&hard_fault_handler,
    .mem_manage_handler = (uint32_t)&mem_manage_handler,
    .bus_fault_handler = (uint32_t)&bus_fault_handler,
    .usage_fault_handler = (uint32_t)&usage_fault_handler,
    .sv_call_handler = (uint32_t)&sv_call_handler,
    .debug_monitor_handler = (uint32_t)&debug_monitor_handler,
    .pend_sv_handler = (uint32_t)&pend_sv_handler,
    .systick_handler = (uint32_t)&systick_handler,
    .irq_0_handler = (uint32_t)&irq_0_handler,
    .irq_1_handler = (uint32_t)&irq_1_handler,
    .irq_2_handler = (uint32_t)&irq_2_handler,
    .irq_3_handler = (uint32_t)&irq_3_handler,
    .irq_4_handler = (uint32_t)&irq_4_handler,
    .irq_5_handler = (uint32_t)&irq_5_handler,
    .irq_6_handler = (uint32_t)&irq_6_handler,
    .irq_7_handler = (uint32_t)&irq_7_handler,
    .irq_8_handler = (uint32_t)&irq_8_handler,
    .irq_9_handler = (uint32_t)&irq_9_handler,
    .irq_10_handler = (uint32_t)&irq_10_handler,
    .irq_11_handler = (uint32_t)&irq_11_handler,
    .irq_12_handler = (uint32_t)&irq_12_handler,
    .irq_13_handler = (uint32_t)&irq_13_handler,
    .irq_14_handler = (uint32_t)&irq_14_handler,
    .irq_15_handler = (uint32_t)&irq_15_handler,
    .irq_16_handler = (uint32_t)&irq_16_handler,
    .irq_17_handler = (uint32_t)&irq_17_handler,
    .irq_18_handler = (uint32_t)&irq_18_handler,
    .irq_19_handler = (uint32_t)&irq_19_handler,
    .irq_20_handler = (uint32_t)&irq_20_handler,
    .irq_21_handler = (uint32_t)&irq_21_handler,
    .irq_22_handler = (uint32_t)&irq_22_handler,
    .irq_23_handler = (uint32_t)&irq_23_handler,
    .irq_24_handler = (uint32_t)&irq_24_handler,
    .irq_25_handler = (uint32_t)&irq_25_handler,
    .irq_26_handler = (uint32_t)&irq_26_handler,
    .irq_27_handler = (uint32_t)&irq_27_handler,
    .irq_28_handler = (uint32_t)&irq_28_handler,
    .irq_29_handler = (uint32_t)&irq_29_handler,
    .irq_30_handler = (uint32_t)&irq_30_handler,
    .irq_31_handler = (uint32_t)&irq_31_handler,
    .irq_32_handler = (uint32_t)&irq_32_handler,
    .irq_33_handler = (uint32_t)&irq_33_handler,
    .irq_34_handler = (uint32_t)&irq_34_handler,
    .irq_35_handler = (uint32_t)&irq_35_handler,
    .irq_36_handler = (uint32_t)&irq_36_handler,
    .irq_37_handler = (uint32_t)&irq_37_handler,
    .irq_38_handler = (uint32_t)&irq_38_handler,
    .irq_39_handler = (uint32_t)&irq_39_handler,
    .irq_40_handler = (uint32_t)&irq_40_handler,
    .irq_41_handler = (uint32_t)&irq_41_handler,
    .irq_42_handler = (uint32_t)&irq_42_handler,
    .irq_43_handler = (uint32_t)&irq_43_handler,
    .irq_44_handler = (uint32_t)&irq_44_handler,
    .irq_45_handler = (uint32_t)&irq_45_handler,
    .irq_46_handler = (uint32_t)&irq_46_handler,
    .irq_47_handler = (uint32_t)&irq_47_handler,
    .irq_48_handler = (uint32_t)&irq_48_handler,
    .irq_49_handler = (uint32_t)&irq_49_handler,
    .irq_50_handler = (uint32_t)&irq_50_handler,
    .irq_51_handler = (uint32_t)&irq_51_handler,
    .irq_52_handler = (uint32_t)&irq_52_handler,
    .irq_53_handler = (uint32_t)&irq_53_handler,
    .irq_54_handler = (uint32_t)&irq_54_handler,
    .irq_55_handler = (uint32_t)&irq_55_handler,
    .irq_56_handler = (uint32_t)&irq_56_handler,
    .irq_57_handler = (uint32_t)&irq_57_handler,
    .irq_58_handler = (uint32_t)&irq_58_handler,
    .irq_59_handler = (uint32_t)&irq_59_handler,
    .irq_60_handler = (uint32_t)&irq_60_handler,
    .irq_61_handler = (uint32_t)&irq_61_handler,
    .irq_62_handler = (uint32_t)&irq_62_handler,
    .irq_63_handler = (uint32_t)&irq_63_handler,
    .irq_64_handler = (uint32_t)&irq_64_handler,
    .irq_65_handler = (uint32_t)&irq_65_handler,
    .irq_66_handler = (uint32_t)&irq_66_handler,
    .irq_67_handler = (uint32_t)&irq_67_handler,
    .irq_68_handler = (uint32_t)&irq_68_handler,
    .irq_69_handler = (uint32_t)&irq_69_handler,
    .irq_70_handler = (uint32_t)&irq_70_handler,
    .irq_71_handler = (uint32_t)&irq_71_handler,
    .irq_72_handler = (uint32_t)&irq_72_handler,
    .irq_73_handler = (uint32_t)&irq_73_handler,
    .irq_74_handler = (uint32_t)&irq_74_handler,
    .irq_75_handler = (uint32_t)&irq_75_handler,
    .irq_76_handler = (uint32_t)&irq_76_handler,
    .irq_77_handler = (uint32_t)&irq_77_handler,
    .irq_78_handler = (uint32_t)&irq_78_handler,
    .irq_79_handler = (uint32_t)&irq_79_handler,
    .irq_80_handler = (uint32_t)&irq_80_handler,
    .irq_81_handler = (uint32_t)&irq_81_handler,
    .irq_82_handler = (uint32_t)&irq_82_handler,
    .irq_83_handler = (uint32_t)&irq_83_handler,
    .irq_84_handler = (uint32_t)&irq_84_handler,
    .irq_85_handler = (uint32_t)&irq_85_handler,
    .irq_86_handler = (uint32_t)&irq_86_handler,
    .irq_87_handler = (uint32_t)&irq_87_handler,
    .irq_88_handler = (uint32_t)&irq_88_handler,
    .irq_89_handler = (uint32_t)&irq_89_handler,
    .irq_90_handler = (uint32_t)&irq_90_handler,
    .irq_91_handler = (uint32_t)&irq_91_handler,
    .irq_92_handler = (uint32_t)&irq_92_handler,
    .irq_93_handler = (uint32_t)&irq_93_handler,
    .irq_94_handler = (uint32_t)&irq_94_handler,
    .irq_95_handler = (uint32_t)&irq_95_handler,
    .irq_96_handler = (uint32_t)&irq_96_handler,
    .irq_97_handler = (uint32_t)&irq_97_handler,
    .irq_98_handler = (uint32_t)&irq_98_handler,
    .irq_99_handler = (uint32_t)&irq_99_handler,
    .irq_100_handler = (uint32_t)&irq_100_handler,
    .irq_101_handler = (uint32_t)&irq_101_handler,
    .irq_102_handler = (uint32_t)&irq_102_handler,
    .irq_103_handler = (uint32_t)&irq_103_handler,
    .irq_104_handler = (uint32_t)&irq_104_handler,
    .irq_105_handler = (uint32_t)&irq_105_handler,
    .irq_106_handler = (uint32_t)&irq_106_handler,
    .irq_107_handler = (uint32_t)&irq_107_handler,
    .irq_108_handler = (uint32_t)&irq_108_handler,
    .irq_109_handler = (uint32_t)&irq_109_handler,
    .irq_110_handler = (uint32_t)&irq_110_handler,
    .irq_111_handler = (uint32_t)&irq_111_handler,
    .irq_112_handler = (uint32_t)&irq_112_handler,
    .irq_113_handler = (uint32_t)&irq_113_handler,
    .irq_114_handler = (uint32_t)&irq_114_handler,
    .irq_115_handler = (uint32_t)&irq_115_handler,
    .irq_116_handler = (uint32_t)&irq_116_handler,
    .irq_117_handler = (uint32_t)&irq_117_handler,
    .irq_118_handler = (uint32_t)&irq_118_handler,
    .irq_119_handler = (uint32_t)&irq_119_handler,
    .irq_120_handler = (uint32_t)&irq_120_handler,
    .irq_121_handler = (uint32_t)&irq_121_handler,
    .irq_122_handler = (uint32_t)&irq_122_handler,
    .irq_123_handler = (uint32_t)&irq_123_handler,
    .irq_124_handler = (uint32_t)&irq_124_handler,
    .irq_125_handler = (uint32_t)&irq_125_handler,
    .irq_126_handler = (uint32_t)&irq_126_handler,
    .irq_127_handler = (uint32_t)&irq_127_handler,
    .irq_128_handler = (uint32_t)&irq_128_handler,
  };

#if defined(__cplusplus)
  }
#endif