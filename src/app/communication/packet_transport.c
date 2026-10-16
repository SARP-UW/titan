#include "app/communication/packet_transport.h"
#include "app/communication/packet_codec.h"

void send_packet_radio_flash(radio_t *radio,
                             const uint8_t *packet,
                             size_t packet_len,
                             enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!radio || !packet || packet_len == 0U) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid packet send args");
        return;
    }

    radio_transmit(radio, packet, packet_len, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to transmit packet");
    }
}

void send_packet_umbilical(umbilical_t *umbilical,
                           const uint8_t *packet,
                           size_t packet_len,
                           enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!umbilical || !packet || packet_len == 0U) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid umbilical packet send args");
        return;
    }

    umbilical_transmit(umbilical, packet, packet_len, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to transmit umbilical packet");
    }
}

void receive_uplink_comm_packet(radio_t *radio,
                                uint8_t *rx_buffer,
                                size_t rx_buffer_len,
                                comm_packet_t *out,
                                enum ti_errc_t *errc) {
    size_t actual_len = 0U;
    enum ti_errc_t receive_errc = TI_ERRC_NONE;

    if (errc) *errc = TI_ERRC_NONE;
    if (out) *out = (comm_packet_t){0};
    if (!radio || !rx_buffer || !out || rx_buffer_len == 0U) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid comm receive args");
        return;
    }

    radio_receive(radio, rx_buffer, rx_buffer_len, &actual_len, &receive_errc);
    if (receive_errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, receive_errc, "Failed to receive comm packet");
        return;
    }

    enum ti_errc_t parse_errc = TI_ERRC_NONE;
    parse_uplink_comm_packet(rx_buffer, actual_len, out, &parse_errc);
    if (parse_errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, parse_errc, "Failed to parse comm packet");
    }
}

void receive_uplink_comm_packet_umbilical(umbilical_t *umbilical,
                                          uint8_t *rx_buffer,
                                          size_t rx_buffer_len,
                                          comm_packet_t *out,
                                          enum ti_errc_t *errc) {
    size_t actual_len = 0U;
    enum ti_errc_t receive_errc = TI_ERRC_NONE;

    if (errc) *errc = TI_ERRC_NONE;
    if (out) *out = (comm_packet_t){0};
    if (!umbilical || !rx_buffer || !out || rx_buffer_len == 0U) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid umbilical comm receive args");
        return;
    }

    umbilical_receive(umbilical, rx_buffer, rx_buffer_len, &actual_len, &receive_errc);
    if (receive_errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, receive_errc, "Failed to receive umbilical packet");
        return;
    }

    enum ti_errc_t parse_errc = TI_ERRC_NONE;
    parse_uplink_comm_packet(rx_buffer, actual_len, out, &parse_errc);
    if (parse_errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, parse_errc, "Failed to parse umbilical packet");
    }
}
