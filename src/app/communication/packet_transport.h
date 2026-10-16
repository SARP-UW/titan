/** Packet transport adapters for the supported physical links. */
#pragma once

#include <stddef.h>
#include <stdint.h>

#include "app/communication/packet_protocol.h"
#include "devices/radio.h"
#include "devices/umbilical.h"
#include "peripheral/errc.h"

void send_packet_radio_flash(radio_t *radio,
                             const uint8_t *packet,
                             size_t packet_len,
                             enum ti_errc_t *errc);

void send_packet_umbilical(umbilical_t *umbilical,
                           const uint8_t *packet,
                           size_t packet_len,
                           enum ti_errc_t *errc);

void receive_uplink_comm_packet(radio_t *radio,
                                uint8_t *rx_buffer,
                                size_t rx_buffer_len,
                                comm_packet_t *out,
                                enum ti_errc_t *errc);

void receive_uplink_comm_packet_umbilical(umbilical_t *umbilical,
                                          uint8_t *rx_buffer,
                                          size_t rx_buffer_len,
                                          comm_packet_t *out,
                                          enum ti_errc_t *errc);
