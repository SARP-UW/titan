#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
  extern "C" {
#endif

/**
 * @brief Initializes the specified CAN line and selected TX RX pins.
 *
 * @param CAN_num CAN line number (valid range: 1 & 2).
 * @param tx_pin GPIO pin number used for CAN transmission (TX).
 * @param rx_pin GPIO pin number used for CAN reception (RX).
 * @param baud_rate Communication speed in bits per second (bps).
 * @param addr Start address of allocated SRAM for message RAM.
 *
 * @return true if initialization is successful, false otherwise.
 */
bool CAN_init(int CAN_num, int tx_pin, int rx_pin, uint32_t baud_rate, uint32_t addr);

/**
 * @brief Sends data over the specified CAN line.
 *
 * @param CAN_num CAN line number (valid range: 1 & 2).
 * @param id The standard ID CAN transmits out, used to address target.
 * @param data Pointer to the data buffer to be transmitted.
 * @param len Number of bytes to transmit.
 *
 * @return true if data transmission is successful, false otherwise.
 */
void CAN_send(int CAN_num, uint32_t id, uint8_t* data, uint8_t len);

/**
 * @brief Receives data from the specified CAN line.
 *
 * @param CAN_num CAN line number (valid range: 1 & 2).
 * @param id Pointer to the buffer where received IDs will be stored.
 * @param data_array Pointer to the buffer where received data will be stored.
 * @param len Pointer to the buffer that stores the length of the received data
 */
void CAN_receive(int CAN_num, uint32_t* id, uint8_t* data, uint8_t* len);

#if defined(__cplusplus)
  }
#endif