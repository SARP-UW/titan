/** Wire-level constants and packet views used by the implementation. */
#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PACKET_MAGIC_HEADER 5350924267264234322ULL
#define PACKET_HEADER_SIZE 8U
#define PACKET_TYPE_OFFSET PACKET_HEADER_SIZE
#define PACKET_PAYLOAD_OFFSET (PACKET_HEADER_SIZE + 1U)

#define PACKET_GNSS_TYPE 0x02U
#define PACKET_SENSOR_TYPE 0x01U
#define PACKET_ADC_TYPE 0x03U
#define PACKET_STATE_TYPE 0x04U
#define PACKET_COMM_TYPE 0x05U

/* Uplink comm packets use their own type namespace. */
#define UPLINK_COMM_PACKET_TYPE 0x01U

/* Fixed sizes include the magic header and packet type. */
#define PACKET_GNSS_SIZE 31U
#define PACKET_SENSOR_SIZE 61U
#define PACKET_ADC_MAX_SIZE 64U
#define PACKET_STATE_MAX_SIZE 64U
#define PACKET_COMM_MAX_SIZE 64U
#define PACKET_RX_MAX_SIZE 64U
#define PACKET_COMM_FIXED_SIZE 20U

/* Downlink field offsets. */
#define GNSS_LAT_OFFSET 9U
#define GNSS_LON_OFFSET 13U
#define GNSS_ALTITUDE_OFFSET 17U
#define GNSS_VELOCITY_EAST_OFFSET 21U
#define GNSS_VELOCITY_NORTH_OFFSET 23U
#define GNSS_VELOCITY_DOWN_OFFSET 25U
#define GNSS_TIME_OFFSET 27U

#define SENSOR_IMU_OFFSET 9U
#define SENSOR_IMU_BYTES 24U
#define SENSOR_MAGNETOMETER_OFFSET 33U
#define SENSOR_MAGNETOMETER_BYTES 12U
#define SENSOR_BAROMETER_1_OFFSET 45U
#define SENSOR_BAROMETER_2_OFFSET 48U
#define SENSOR_TEMPERATURE_1_OFFSET 51U
#define SENSOR_TEMPERATURE_2_OFFSET 53U
#define SENSOR_CURRENT_OFFSET 55U
#define SENSOR_CURRENT_BYTES 6U

/* Uplink comm field offsets. */
#define UPLINK_COMM_PING_ID_OFFSET 9U
#define UPLINK_COMM_SYSTEM_TIME_OFFSET 11U
#define UPLINK_COMM_COMMAND_VALID_OFFSET 15U
#define UPLINK_COMM_COMMAND_ID_OFFSET 16U
#define UPLINK_COMM_COMMAND_TYPE_OFFSET 18U
#define UPLINK_COMM_COMMAND_TAG_OFFSET 19U
#define UPLINK_COMM_COMMAND_ARGS_OFFSET 20U
#define UPLINK_COMM_MIN_SIZE 16U
#define UPLINK_COMM_COMMAND_MIN_SIZE 20U

/** A parsed view into an uplink comm packet; command_args points into input. */
typedef struct {
    bool packet_present;
    uint16_t ping_id;
    uint32_t system_time;
    bool command_valid;
    uint16_t command_id;
    uint8_t command_type;
    uint8_t command_tag;
    const uint8_t *command_args;
    size_t command_args_len;
} comm_packet_t;
