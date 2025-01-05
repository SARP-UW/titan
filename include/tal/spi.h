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
 * @file include/tal/spi.h
 * @authors Aaron McBride
 * @brief SPI driver interface.
 */

#ifndef TAL_SPI_H
#define TAL_SPI_H

  #include <stdint.h>
  #include <stdbool.h>

  #if defined(__cplusplus)
    extern "C" {
  #endif

    /**
     * @brief
     */
    typedef enum {
      SPI_ERROR_OTHER,
      SPI_ERROR_UNKNOWN
    }spi_error_t;

    /**
     * @brief
     */
    typedef struct {
      bool enabled;
      bool full_duplex;
      int64_t baud_rate;
      int32_t data_size;
      int32_t mosi_pin;
      int32_t miso_pin;
      int32_t sck_pin;
      void (*error_callback)(spi_error_t errc);
    }spi_config_t;

    /**
     * @brief
     * @param index (int32_t)
     * @param config (spi_config_t)
     * @return (bool)
     */
    bool set_spi_config(int32_t index, spi_config_t config);

    /**
     * @brief
     * @param index (int32_t)
     * @return (spi_config_t)
     */
    spi_config_t get_spi_config(int32_t index);

    /**
     * @brief
     * @param index (int32_t)
     * @param src (const void*)
     * @param len (int32_t)
     * @return (bool)
     */
    bool spi_transmit(int32_t index, const void* src, int32_t len);

    /**
     * @brief
     * @param index (int32_t)
     * @param dst (void*)
     * @param len (int32_t)
     * @return (bool)
     */
    bool spi_receive(int32_t index, void* dst, int32_t len);
    
  #if defined(__cplusplus)
    } /* extern "C" */
  #endif

#endif /* TAL_SPI_H */