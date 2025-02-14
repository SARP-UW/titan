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
 * @file src/STM32H745_CM7/dma.h
 * @authors Aaron McBride
 * @brief DMA driver.
 */

 #pragma once
 #include <stdint.h>
 #include <stdbool.h>
 #include <stddef.h>
 #include "STM32H745/internal/mmio.h"
 #include "STM32H745/internal/interrupt.h"
 
 #ifdef __cplusplus
   extern "C" {
 #endif

  typedef enum {
    DMA_DATA_SIZE_BYTE  = 0b00,
    DMA_DATA_SIZE_HWORD = 0b01,
    DMA_DATA_SIZE_WORD  = 0b10
  } dma_data_size_e;

  typedef struct {
    int32_t inst;
    int32_t stream;
  } dma_transfer_t;

  static const int32_t _DMA_INST_COUNT = 2;
  static const int32_t _DMA_STREAM_COUNT = 8;

  static const uint32_t _DMA_DIR_P2M = 0U;
  static const uint32_t _DMA_DIR_M2P = 1U;
  static const uint32_t _DMA_DIR_M2M = 2U;

  static const dma_transfer_t _DMA_NULL_TRANSFER = { 
    .inst = -1, 
    .stream = -1 
  };

  // Finds a free DMA transfer stream.
  static dma_transfer_t _find_transfer(void) {
    for (int32_t i = 0; i < _DMA_INST_COUNT; i++) {
      for (int32_t j = 0; j < _DMA_STREAM_COUNT; j++) {
        if (READ_FIELD(DMAx_SxCR[i][j], DMAx_SxCR_EN) == 0U) {
          return (dma_transfer_t) {
            .inst = i,
            .stream = j
          };
        }
      }
    }
    return (dma_transfer_t) {
      .inst = -1,
      .stream = -1
    };
  }

  dma_transfer_t dma_start_transfer_p2m(uint32_t p_addr, uint32_t m_addr, dma_data_size_e data_size, int32_t length) {
    dma_transfer_t transfer = _find_transfer();
    if (transfer.inst != -1 && transfer.stream != -1) {
      uint32_t config_reg = &DMAx_SxCR[transfer.inst][transfer.stream];
      WRITE_FIELD(&config_reg, DMAx_SxCR_MBURST, 0U);
      WRITE_FIELD(&config_reg, DMAx_SxCR_PBURST, 0U);
      WRITE_FIELD(&config_reg, DMAx_SxCR_MINC, 1U);
      WRITE_FIELD(&config_reg, DMAx_SxCR_DIR, _DMA_DIR_P2M);
      WRITE_FIELD(&config_reg, DMAx_SxCR_PSIZE, (uint32_t)data_size);
      if (length > 0) {
        WRITE_FIELD(&config_reg, DMAx_SxCR_PFCTRL, 0U);
        WRITE_FIELD(DMAx_SxNDTR[transfer.inst][transfer.stream], DMAx_SxNDTR_NDT, (uint32_t)length);
      } else {
        WRITE_FIELD(&config_reg, DMAx_SxCR_PFCTRL, 1U);
        WRITE_FIELD(DMAx_SxNDTR[transfer.inst][transfer.stream], DMAx_SxNDTR_NDT, 9U);
      }
    }
    return transfer;
  }
 
 #ifdef __cplusplus
   } // extern "C"
 #endif
 
 /** @endinternal */