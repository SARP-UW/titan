#include "app/utils/packets.h"

static bool has_valid_magic_header(const uint8_t *buffer, size_t buffer_len) {
    if (!buffer || buffer_len < 8U) {
        return false;
    }

    const uint64_t magic = PACKET_MAGIC_HEADER;
    return buffer[0] == (uint8_t)(magic >> 56)
        && buffer[1] == (uint8_t)(magic >> 48)
        && buffer[2] == (uint8_t)(magic >> 40)
        && buffer[3] == (uint8_t)(magic >> 32)
        && buffer[4] == (uint8_t)(magic >> 24)
        && buffer[5] == (uint8_t)(magic >> 16)
        && buffer[6] == (uint8_t)(magic >> 8)
        && buffer[7] == (uint8_t)magic;
}

static void write_magic_header(uint8_t *buffer) {
    const uint64_t magic = PACKET_MAGIC_HEADER;
    buffer[0] = (uint8_t)(magic >> 56);
    buffer[1] = (uint8_t)(magic >> 48);
    buffer[2] = (uint8_t)(magic >> 40);
    buffer[3] = (uint8_t)(magic >> 32);
    buffer[4] = (uint8_t)(magic >> 24);
    buffer[5] = (uint8_t)(magic >> 16);
    buffer[6] = (uint8_t)(magic >> 8);
    buffer[7] = (uint8_t)magic;
}

void build_gnss_packet(const gnss_pvt_t *pvt, uint8_t *buffer, size_t buffer_len, enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!pvt || !buffer || buffer_len < PACKET_GNSS_SIZE) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid GNSS packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[8] = PACKET_GNSS_TYPE;
    buffer[9] = (uint8_t)(pvt->lat >> 24);
    buffer[10] = (uint8_t)(pvt->lat >> 16);
    buffer[11] = (uint8_t)(pvt->lat >> 8);
    buffer[12] = (uint8_t)pvt->lat;
    buffer[13] = (uint8_t)(pvt->lon >> 24);
    buffer[14] = (uint8_t)(pvt->lon >> 16);
    buffer[15] = (uint8_t)(pvt->lon >> 8);
    buffer[16] = (uint8_t)pvt->lon;
    buffer[17] = (uint8_t)(pvt->height >> 24);
    buffer[18] = (uint8_t)(pvt->height >> 16);
    buffer[19] = (uint8_t)(pvt->height >> 8);
    buffer[20] = (uint8_t)pvt->height;
    buffer[21] = (uint8_t)(pvt->vel_e >> 8);
    buffer[22] = (uint8_t)pvt->vel_e;
    buffer[23] = (uint8_t)(pvt->vel_n >> 8);
    buffer[24] = (uint8_t)pvt->vel_n;
    buffer[25] = (uint8_t)(pvt->vel_d >> 8);
    buffer[26] = (uint8_t)pvt->vel_d;
    buffer[27] = pvt->day;
    buffer[28] = pvt->hour;
    buffer[29] = pvt->min;
    buffer[30] = pvt->sec;
}

void build_sensor_packet(const struct imu_result *imu1,
                         const struct imu_result *imu2,
                         const barometer_result_t *baro1,
                         const barometer_result_t *baro2,
                         const struct magnetometer_result_t *mag1,
                         const struct magnetometer_result_t *mag2,
                         const temperature_result_t *temp1,
                         const temperature_result_t *temp2,
                         uint8_t *buffer,
                         size_t buffer_len,
                         enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!imu1 || !imu2 || !baro1 || !baro2 || !mag1 || !mag2 || !temp1 || !temp2 || !buffer || buffer_len < PACKET_SENSOR_SIZE) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid sensor packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[8] = PACKET_SENSOR_TYPE;
    buffer[9] = (uint8_t)(imu1->accel_x >> 8);
    buffer[10] = (uint8_t)imu1->accel_x;
    buffer[11] = (uint8_t)(imu1->accel_y >> 8);
    buffer[12] = (uint8_t)imu1->accel_y;
    buffer[13] = (uint8_t)(imu1->accel_z >> 8);
    buffer[14] = (uint8_t)imu1->accel_z;
    buffer[15] = (uint8_t)(imu1->gyro_x >> 8);
    buffer[16] = (uint8_t)imu1->gyro_x;
    buffer[17] = (uint8_t)(imu1->gyro_y >> 8);
    buffer[18] = (uint8_t)imu1->gyro_y;
    buffer[19] = (uint8_t)(imu1->gyro_z >> 8);
    buffer[20] = (uint8_t)imu1->gyro_z;
    buffer[21] = (uint8_t)(imu2->accel_x >> 8);
    buffer[22] = (uint8_t)imu2->accel_x;
    buffer[23] = (uint8_t)(imu2->accel_y >> 8);
    buffer[24] = (uint8_t)imu2->accel_y;
    buffer[25] = (uint8_t)(imu2->accel_z >> 8);
    buffer[26] = (uint8_t)imu2->accel_z;
    buffer[27] = (uint8_t)(imu2->gyro_x >> 8);
    buffer[28] = (uint8_t)imu2->gyro_x;
    buffer[29] = (uint8_t)(imu2->gyro_y >> 8);
    buffer[30] = (uint8_t)imu2->gyro_y;
    buffer[31] = (uint8_t)(imu2->gyro_z >> 8);
    buffer[32] = (uint8_t)imu2->gyro_z;
    buffer[33] = (uint8_t)(mag1->mag_x >> 8);
    buffer[34] = (uint8_t)mag1->mag_x;
    buffer[35] = (uint8_t)(mag1->mag_y >> 8);
    buffer[36] = (uint8_t)mag1->mag_y;
    buffer[37] = (uint8_t)(mag1->mag_z >> 8);
    buffer[38] = (uint8_t)mag1->mag_z;
    buffer[39] = (uint8_t)(mag2->mag_x >> 8);
    buffer[40] = (uint8_t)mag2->mag_x;
    buffer[41] = (uint8_t)(mag2->mag_y >> 8);
    buffer[42] = (uint8_t)mag2->mag_y;
    buffer[43] = (uint8_t)(mag2->mag_z >> 8);
    buffer[44] = (uint8_t)mag2->mag_z;
    buffer[45] = (uint8_t)(baro1->pressure >> 16);
    buffer[46] = (uint8_t)(baro1->pressure >> 8);
    buffer[47] = (uint8_t)baro1->pressure;
    buffer[48] = (uint8_t)(baro2->pressure >> 16);
    buffer[49] = (uint8_t)(baro2->pressure >> 8);
    buffer[50] = (uint8_t)baro2->pressure;
    buffer[51] = (uint8_t)(temp1->temperature >> 8);
    buffer[52] = (uint8_t)temp1->temperature;
    buffer[53] = (uint8_t)(temp2->temperature >> 8);
    buffer[54] = (uint8_t)temp2->temperature;
    buffer[55] = 0;
    buffer[56] = 0;
    buffer[57] = 0;
    buffer[58] = 0;
    buffer[59] = 0;
    buffer[60] = 0;
}

void build_adc_packet(const struct adc_channel *channels,
                      uint8_t channel_count,
                      uint8_t packet_index,
                      uint8_t *buffer,
                      size_t buffer_len,
                      enum ti_errc_t *errc) {
    uint8_t idx = 8;

    if (errc) *errc = TI_ERRC_NONE;
    if (!channels || !buffer || buffer_len < (size_t)(10U + (3U * channel_count))) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid ADC packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[idx++] = PACKET_ADC_TYPE;
    buffer[idx++] = packet_index;

    for (uint8_t i = 0; i < channel_count; i++) {
        int32_t raw_value = adc_read_voltage(&channels[i], errc);
        if (errc && *errc != TI_ERRC_NONE) {
            TI_SET_ERRC(errc, *errc, "Failed to read ADC channel");
            return;
        }

        buffer[idx++] = (uint8_t)((raw_value >> 16) & 0xFF);
        buffer[idx++] = (uint8_t)((raw_value >> 8) & 0xFF);
        buffer[idx++] = (uint8_t)(raw_value & 0xFF);
    }
}

void build_state_packet(const uint8_t *valves,
                        uint16_t valve_count,
                        const uint16_t *servos,
                        uint16_t servo_count,
                        uint8_t *buffer,
                        size_t buffer_len,
                        enum ti_errc_t *errc) {
    uint8_t idx = 9;
    const uint8_t valve_bytes = (uint8_t)((valve_count + 7U) / 8U);
    const size_t required_len = (size_t)(9U + valve_bytes + (2U * servo_count));

    if (errc) *errc = TI_ERRC_NONE;
    if (!valves || !servos || !buffer || buffer_len < required_len) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid state packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[8] = PACKET_STATE_TYPE;

    for (uint8_t i = 0; i < valve_bytes; i++) {
        uint8_t packed = 0;
        for (uint8_t bit = 0; bit < 8; bit++) {
            const uint16_t valve_idx = (uint16_t)(i * 8U + bit);
            if (valve_idx < valve_count && (valves[valve_idx] & 0x01U) != 0U) {
                packed |= (uint8_t)(1U << bit);
            }
        }
        buffer[idx++] = packed;
    }

    for (uint16_t i = 0; i < servo_count; i++) {
        buffer[idx++] = (uint8_t)(servos[i] >> 8);
        buffer[idx++] = (uint8_t)servos[i];
    }
}

void build_comm_packet(uint16_t ping_id,
                       uint8_t system_mode,
                       uint32_t processor_time_ms,
                       uint16_t last_command_id,
                       uint8_t last_command_status,
                       const uint8_t *message_tags,
                       uint8_t message_count,
                       uint8_t *buffer,
                       size_t buffer_len,
                       size_t *packet_len,
                       enum ti_errc_t *errc) {
    size_t idx = 9;

    if (errc) *errc = TI_ERRC_NONE;
    if (!buffer || !packet_len || buffer_len < (size_t)(15U + message_count)) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid comm packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[8] = PACKET_COMM_TYPE;
    buffer[idx++] = (uint8_t)(ping_id >> 8);
    buffer[idx++] = (uint8_t)ping_id;
    buffer[idx++] = system_mode;
    buffer[idx++] = (uint8_t)(processor_time_ms >> 24);
    buffer[idx++] = (uint8_t)(processor_time_ms >> 16);
    buffer[idx++] = (uint8_t)(processor_time_ms >> 8);
    buffer[idx++] = (uint8_t)processor_time_ms;
    buffer[idx++] = (uint8_t)(last_command_id >> 8);
    buffer[idx++] = (uint8_t)last_command_id;
    buffer[idx++] = last_command_status;
    buffer[idx++] = message_count;

    for (uint8_t i = 0; i < message_count; i++) {
        buffer[idx++] = message_tags ? message_tags[i] : 0;
    }

    *packet_len = idx;
}

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

void parse_uplink_comm_packet(const uint8_t *buffer,
                              size_t buffer_len,
                              comm_packet_t *out,
                              enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!buffer || !out) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid uplink parser args");
        return;
    }

    out->packet_present = false;
    out->ping_id = 0;
    out->system_time = 0;
    out->command_valid = false;
    out->command_id = 0;
    out->command_type = 0;
    out->command_tag = 0;
    out->command_args = NULL;
    out->command_args_len = 0;

    if (buffer_len == 0U) {
        return;
    }

    if (buffer_len < 16U) {
        TI_SET_ERRC(errc, TI_ERRC_PROTOCOL, "Uplink comm packet too short");
        return;
    }

    if (!has_valid_magic_header(buffer, buffer_len)) {
        TI_SET_ERRC(errc, TI_ERRC_PROTOCOL, "Invalid uplink magic header");
        return;
    }

    if (buffer[8] != 0x01U) {
        TI_SET_ERRC(errc, TI_ERRC_PROTOCOL, "Unexpected uplink packet type");
        return;
    }

    out->packet_present = true;
    out->ping_id = (uint16_t)(((uint16_t)buffer[9] << 8) | (uint16_t)buffer[10]);
    out->system_time = ((uint32_t)buffer[11] << 24)
                     | ((uint32_t)buffer[12] << 16)
                     | ((uint32_t)buffer[13] << 8)
                     | (uint32_t)buffer[14];
    out->command_valid = (buffer[15] != 0U);

    if (!out->command_valid) {
        return;
    }

    if (buffer_len < 20U) {
        TI_SET_ERRC(errc, TI_ERRC_PROTOCOL, "Uplink command payload too short");
        return;
    }

    out->command_id = (uint16_t)(((uint16_t)buffer[16] << 8) | (uint16_t)buffer[17]);
    out->command_type = buffer[18];
    out->command_tag = buffer[19];

    if (buffer_len > 20U) {
        out->command_args = &buffer[20];
        out->command_args_len = buffer_len - 20U;
    }
}

void receive_uplink_comm_packet(radio_t *radio,
                                uint8_t *rx_buffer,
                                size_t rx_buffer_len,
                                comm_packet_t *out,
                                enum ti_errc_t *errc) {
    size_t actual_len = 0;

    if (errc) *errc = TI_ERRC_NONE;
    if (!radio || !rx_buffer || !out || rx_buffer_len == 0U) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid comm receive args");
        return;
    }

    radio_receive(radio, rx_buffer, rx_buffer_len, &actual_len, errc);
    if (errc && *errc != TI_ERRC_NONE) {
        TI_SET_ERRC(errc, *errc, "Failed to receive comm packet");
        return;
    }

    parse_uplink_comm_packet(rx_buffer, actual_len, out, errc);
}
