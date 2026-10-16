#include "app/communication/packet_codec.h"

static bool has_valid_magic_header(const uint8_t *buffer, size_t buffer_len) {
    if (!buffer || buffer_len < PACKET_HEADER_SIZE) {
        return false;
    }

    const uint64_t magic = PACKET_MAGIC_HEADER;
    for (size_t i = 0; i < PACKET_HEADER_SIZE; i++) {
        const unsigned shift = (unsigned)((PACKET_HEADER_SIZE - 1U - i) * 8U);
        if (buffer[i] != (uint8_t)(magic >> shift)) {
            return false;
        }
    }
    return true;
}

static void write_magic_header(uint8_t *buffer) {
    const uint64_t magic = PACKET_MAGIC_HEADER;
    for (size_t i = 0; i < PACKET_HEADER_SIZE; i++) {
        const unsigned shift = (unsigned)((PACKET_HEADER_SIZE - 1U - i) * 8U);
        buffer[i] = (uint8_t)(magic >> shift);
    }
}

static void write_u16(uint8_t *buffer, uint16_t value) {
    buffer[0] = (uint8_t)(value >> 8);
    buffer[1] = (uint8_t)value;
}

static void write_u24(uint8_t *buffer, uint32_t value) {
    buffer[0] = (uint8_t)(value >> 16);
    buffer[1] = (uint8_t)(value >> 8);
    buffer[2] = (uint8_t)value;
}

static void write_u32(uint8_t *buffer, uint32_t value) {
    buffer[0] = (uint8_t)(value >> 24);
    buffer[1] = (uint8_t)(value >> 16);
    buffer[2] = (uint8_t)(value >> 8);
    buffer[3] = (uint8_t)value;
}

static uint16_t read_u16(const uint8_t *buffer) {
    return (uint16_t)(((uint16_t)buffer[0] << 8) | buffer[1]);
}

static uint32_t read_u32(const uint8_t *buffer) {
    return ((uint32_t)buffer[0] << 24)
         | ((uint32_t)buffer[1] << 16)
         | ((uint32_t)buffer[2] << 8)
         | buffer[3];
}

void build_gnss_packet(const gnss_pvt_t *pvt,
                       uint8_t *buffer,
                       size_t buffer_len,
                       enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!pvt || !buffer || buffer_len < PACKET_GNSS_SIZE) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid GNSS packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[PACKET_TYPE_OFFSET] = PACKET_GNSS_TYPE;
    write_u32(&buffer[GNSS_LAT_OFFSET], (uint32_t)pvt->lat);
    write_u32(&buffer[GNSS_LON_OFFSET], (uint32_t)pvt->lon);
    write_u32(&buffer[GNSS_ALTITUDE_OFFSET], (uint32_t)pvt->height);
    write_u16(&buffer[GNSS_VELOCITY_EAST_OFFSET], (uint16_t)pvt->vel_e);
    write_u16(&buffer[GNSS_VELOCITY_NORTH_OFFSET], (uint16_t)pvt->vel_n);
    write_u16(&buffer[GNSS_VELOCITY_DOWN_OFFSET], (uint16_t)pvt->vel_d);
    buffer[GNSS_TIME_OFFSET] = pvt->day;
    buffer[GNSS_TIME_OFFSET + 1U] = pvt->hour;
    buffer[GNSS_TIME_OFFSET + 2U] = pvt->min;
    buffer[GNSS_TIME_OFFSET + 3U] = pvt->sec;
}

void build_sensor_packet(const barometer_result_t *baro1,
                         const barometer_result_t *baro2,
                         const temperature_result_t *temp1,
                         const temperature_result_t *temp2,
                         uint8_t *buffer,
                         size_t buffer_len,
                         enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!baro1 || !baro2 || !temp1 || !temp2 || !buffer || buffer_len < PACKET_SENSOR_SIZE) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid sensor packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[PACKET_TYPE_OFFSET] = PACKET_SENSOR_TYPE;

    /* IMU and magnetometer drivers are not enabled yet; retain their existing
       placeholder bytes and positions in the wire format. */
    for (size_t i = 0; i < SENSOR_IMU_BYTES; i++) {
        buffer[SENSOR_IMU_OFFSET + i] = 0x02U;
    }
    for (size_t i = 0; i < SENSOR_MAGNETOMETER_BYTES; i++) {
        buffer[SENSOR_MAGNETOMETER_OFFSET + i] = 0x03U;
    }

    write_u24(&buffer[SENSOR_BAROMETER_1_OFFSET], baro1->pressure);
    write_u24(&buffer[SENSOR_BAROMETER_2_OFFSET], baro2->pressure);
    write_u16(&buffer[SENSOR_TEMPERATURE_1_OFFSET], temp1->temperature);
    write_u16(&buffer[SENSOR_TEMPERATURE_2_OFFSET], temp2->temperature);
    for (size_t i = 0; i < SENSOR_CURRENT_BYTES; i++) {
        buffer[SENSOR_CURRENT_OFFSET + i] = 0U;
    }
}

void build_adc_packet(const struct adc_channel *channels,
                      uint8_t channel_count,
                      uint8_t packet_index,
                      uint8_t *buffer,
                      size_t buffer_len,
                      enum ti_errc_t *errc) {
    const size_t required_len = 10U + (3U * (size_t)channel_count);
    size_t index = PACKET_TYPE_OFFSET;

    if (errc) *errc = TI_ERRC_NONE;
    if (!channels || !buffer || buffer_len < required_len) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid ADC packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[index++] = PACKET_ADC_TYPE;
    buffer[index++] = packet_index;

    for (uint8_t i = 0; i < channel_count; i++) {
        enum ti_errc_t read_errc = TI_ERRC_NONE;
        const int32_t raw_value = adc_read_voltage(&channels[i], &read_errc);
        if (read_errc != TI_ERRC_NONE) {
            TI_SET_ERRC(errc, read_errc, "Failed to read ADC channel");
            return;
        }
        buffer[index++] = (uint8_t)((raw_value >> 16) & 0xFF);
        buffer[index++] = (uint8_t)((raw_value >> 8) & 0xFF);
        buffer[index++] = (uint8_t)(raw_value & 0xFF);
    }
}

void build_state_packet(const uint8_t *valves,
                        uint16_t valve_count,
                        const uint16_t *servos,
                        uint16_t servo_count,
                        uint8_t *buffer,
                        size_t buffer_len,
                        enum ti_errc_t *errc) {
    const uint16_t valve_bytes = (uint16_t)((valve_count + 7U) / 8U);
    const size_t required_len = 9U + (size_t)valve_bytes + (2U * (size_t)servo_count);
    size_t index = PACKET_PAYLOAD_OFFSET;

    if (errc) *errc = TI_ERRC_NONE;
    if (!valves || !servos || !buffer || buffer_len < required_len) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid state packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[PACKET_TYPE_OFFSET] = PACKET_STATE_TYPE;

    for (uint16_t byte = 0; byte < valve_bytes; byte++) {
        uint8_t packed = 0U;
        for (uint8_t bit = 0; bit < 8U; bit++) {
            const uint16_t valve_index = (uint16_t)(byte * 8U + bit);
            if (valve_index < valve_count && (valves[valve_index] & 0x01U) != 0U) {
                packed |= (uint8_t)(1U << bit);
            }
        }
        buffer[index++] = packed;
    }

    for (uint16_t i = 0; i < servo_count; i++) {
        write_u16(&buffer[index], servos[i]);
        index += 2U;
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
    size_t index = PACKET_PAYLOAD_OFFSET;

    if (errc) *errc = TI_ERRC_NONE;
    if (!buffer || !packet_len || buffer_len < (PACKET_COMM_FIXED_SIZE + (size_t)message_count)) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid comm packet args");
        return;
    }

    write_magic_header(buffer);
    buffer[PACKET_TYPE_OFFSET] = PACKET_COMM_TYPE;
    write_u16(&buffer[index], ping_id);
    index += 2U;
    buffer[index++] = system_mode;
    write_u32(&buffer[index], processor_time_ms);
    index += 4U;
    write_u16(&buffer[index], last_command_id);
    index += 2U;
    buffer[index++] = last_command_status;
    buffer[index++] = message_count;

    for (uint8_t i = 0; i < message_count; i++) {
        buffer[index++] = message_tags ? message_tags[i] : 0U;
    }
    *packet_len = index;
}

void parse_uplink_comm_packet(const uint8_t *buffer,
                              size_t buffer_len,
                              comm_packet_t *out,
                              enum ti_errc_t *errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!out) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid uplink parser args");
        return;
    }

    *out = (comm_packet_t){0};
    if (!buffer) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid uplink parser args");
        return;
    }
    if (buffer_len == 0U) {
        return;
    }
    if (buffer_len < UPLINK_COMM_MIN_SIZE) {
        TI_SET_ERRC(errc, TI_ERRC_PROTOCOL, "Uplink comm packet too short");
        return;
    }
    if (!has_valid_magic_header(buffer, buffer_len)) {
        TI_SET_ERRC(errc, TI_ERRC_PROTOCOL, "Invalid uplink magic header");
        return;
    }
    if (buffer[PACKET_TYPE_OFFSET] != UPLINK_COMM_PACKET_TYPE) {
        TI_SET_ERRC(errc, TI_ERRC_PROTOCOL, "Unexpected uplink packet type");
        return;
    }

    comm_packet_t decoded = {0};
    decoded.packet_present = true;
    decoded.ping_id = read_u16(&buffer[UPLINK_COMM_PING_ID_OFFSET]);
    decoded.system_time = read_u32(&buffer[UPLINK_COMM_SYSTEM_TIME_OFFSET]);
    decoded.command_valid = buffer[UPLINK_COMM_COMMAND_VALID_OFFSET] != 0U;
    if (!decoded.command_valid) {
        *out = decoded;
        return;
    }
    if (buffer_len < UPLINK_COMM_COMMAND_MIN_SIZE) {
        TI_SET_ERRC(errc, TI_ERRC_PROTOCOL, "Uplink command payload too short");
        return;
    }

    decoded.command_id = read_u16(&buffer[UPLINK_COMM_COMMAND_ID_OFFSET]);
    decoded.command_type = buffer[UPLINK_COMM_COMMAND_TYPE_OFFSET];
    decoded.command_tag = buffer[UPLINK_COMM_COMMAND_TAG_OFFSET];
    if (buffer_len > UPLINK_COMM_COMMAND_ARGS_OFFSET) {
        decoded.command_args = &buffer[UPLINK_COMM_COMMAND_ARGS_OFFSET];
        decoded.command_args_len = buffer_len - UPLINK_COMM_COMMAND_ARGS_OFFSET;
    }
    *out = decoded;
}
