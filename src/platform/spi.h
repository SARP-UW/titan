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
 * @file common/platform/spi.h
 * @authors Ashton Doane 
 * @brief Driver for SPI communication protocol.
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "src/platform/gpio.h"

#if defined(__cplusplus)
  extern "C" {
#endif

     /**
      * TODO: DEFINE CLOCK/MOSI/MISO LINES ON BOARD
      * 
      * SPIMODE:
      * 
      * |  SPI MODE |  CPOL | CPHA |
      * |     0     |   0   |  0   |
      * |     1     |   0   |  1   |
      * |     2     |   1   |  0   |
      * |     3     |   1   |  1   |
      * 
      *  CPOL:
      *     0 --> Clock rests low (normal).
      *     1 --> Clock rests high (inverted)
      *  CPHA:
      *     0 --> Sample on leading clock signal.
      *     1 --> Sample on trailing clock signal.
      */


    /**************************************************************************************************
    * @section SPI_connection Struct
    **************************************************************************************************/
    
    struct SPI_connection{
        int SPI_mode; // Operation mode of SPI for this transmission. Modes descriptions found above.
        int baud_rate; // Maximum bit rate which data should be sent/received at for this transmission.
        int cs; // The GPIO pin connected to the slave we wish to communicate with.
    };

    /**************************************************************************************************
    * @section SPI Interface
    **************************************************************************************************/
    /**
     * @brief Opens the connection defined in a SPI_connection struct by lowering the cs pin.
     * @param conn (SPI_connection): The connection which we are opening.
     */
    void SPI_open_connection(struct SPI_connection conn,  bool* const err);

    /**
     * @brief Sends data over the connection defined.
     * @param data_ptr (void*): Pointer to the first bit of memory we would like to transfer.
     * @param num_bytes (int): Number of bytes we should send, beginning at data_ptr.
     * @note Knowing the connection SPI_mode is important so we can correctly write for this peripheral.
     */
    void SPI_write(struct SPI_connection conn, void* data_ptr, int num_bytes, bool* const err);    
    
    /**
     * @brief 
     * @param conn (SPI_connection): The connection which we are 
     * @note Knowing the connection SPI_mode is important so we can correctly read.
     */
    void SPI_read(struct SPI_connection conn, bool* const err);

    /**
     * @brief Transmits and receives data simultaneously over the SPI full-duplex channel.
     * @param
     */
    void SPI_read_and_write(struct SPI_connection conn,  bool* const err);

    /**
     * @brief Closes the connection defined in a SPI_connection struct, namely by raising the cs_pin.
     * @param conn (SPI_connection): The connection which we are closing.
     */
    void SPI_close_connection(struct SPI_connection conn,  bool* const err);
    
    
    /**************************************************************************************************
    * @section SPI Implementation
    **************************************************************************************************/

    /**
    * TODO: IMPELEMENT EVERYTHING
    */


#if defined(__cplusplus)
  }
#endif