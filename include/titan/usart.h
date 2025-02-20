#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if defined(__cplusplus)
  extern "C" {
#endif

/**
 * @brief Initializes the specified UART channel.
 *
 * @param usart_num UART channel number (valid range: 1 - 8).
 * @param tx_pin GPIO pin number used for UART transmission (TX).
 * @param rx_pin GPIO pin number used for UART reception (RX).
 * @param baud_rate Communication speed in bits per second (bps).
 *
 * @return true if initialization is successful, false otherwise.
 */
bool usart_init(int usart_num, int tx_pin, int rx_pin, uint32_t baud_rate);

/**
 * @brief Sends data over the specified UART channel.
 *
 * @param usart_num UART channel number (valid range: 1 - 8).
 * @param data Pointer to the data buffer to be transmitted.
 * @param length Number of bytes to transmit.
 *
 * @return true if data transmission is successful, false otherwise.
 */
bool usart_write(int usart_num, uint8_t* data, uint32_t length);

/**
 * @brief Receives data from the specified UART channel.
 *
 * @param usart_num UART channel number (valid range: 1 - 8).
 * @param data_array Pointer to the buffer where received data will be stored.
 * @param size Number of bytes to read.
 */
void usart_read(int usart_num, uint8_t* data_array, uint32_t size);

#if defined(__cplusplus)
  }
#endif
