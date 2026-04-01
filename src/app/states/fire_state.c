#include "app/state.h"
#include "devices/imu.h"
#include "devices/gnss.h"
#include "devices/barometer.h"
#include "devices/actuator.h"
#include "devices/magnetometer.h"
#include "devices/temperature.h"
#include "devices/radio.h"
#include "peripheral/spi.h"
#include "peripheral/flash.h"
#include "peripheral/errc.h"

//     -- ( ) FIRING: Deliver propelants to manifold
//     ~~~ ( ) Open main propelant valves
//     ~~~ ( ) Execute control loop for engine burn
//     ~~~ ( ) Send and record telemetry

/** Radio configs */
static const uint64_t MAGIC_HEADER = 5566810094155542836;
static const radio_t radio_dev;

static const radio_spi_dev radio_spi_config = {
    .spi_inst = 1,
    .ss_pin = 9
};

static const radio_config_t radio_config = {
    .reset_pin = 8,
    .nirq_pin = 7,
    .reset_active_high = 0,
    .channel = 0
};

/** Sensor configs */
static const gnss_t gnss_dev = {
    .spi_config = {
        .spi_inst = 1,
        .ss_pin = 10
    },
    .config = {
        .meas_rate_ms = 200, // 5Hz for flight
        .constellation_mask = GNSS_CONSTELLATION_GPS | GNSS_CONSTELLATION_GLONASS | GNSS_CONSTELLATION_BEIDOU,
        .dyn_model = GNSS_DYN_AIRBORNE_4G,
        .power_mode = GNSS_POWER_CONTINUOUS
    },
    .initialized = 0
};

static const struct imu_spi_dev imu_dev1 = {
    .inst = 1,
    .ss_pin = 9
};

static const struct imu_spi_dev imu_dev2 = {
    .inst = 1,
    .ss_pin = 9
};

static const barometer_t barometer_dev1 = {
    .spi_dev = {
        .inst = 1,
        .ss_pin = 9
    },
    .osr = OSR_4096,
    .calibration_data = {0},
    .result = {0}
};

static const barometer_t barometer_dev2 = {
    .spi_dev = {
        .inst = 1,
        .ss_pin = 9
    },
    .osr = OSR_4096,
    .calibration_data = {0},
    .result = {0}
};

static const struct magnetometer_spi_dev magnetometer_dev1 = {
    .inst = 1,
    .ss_pin = 9
};

static const struct magnetometer_spi_dev magnetometer_dev2 = {
    .inst = 1,
    .ss_pin = 9
};

static const temperature_t temperature_dev1 = {
    .spi_config = {
        .spi_inst = 1,
        .ss_pin = 9
    },
    .config = {
        .mode = temperature_MODE_CONTINUOUS,
        .resolution = temperature_RES_16_BIT
    }
};

static const temperature_t temperature_dev2 = {
    .spi_config = {
        .spi_inst = 1,
        .ss_pin = 9
    },
    .config = {
        .mode = temperature_MODE_CONTINUOUS,
        .resolution = temperature_RES_16_BIT
    }
};

struct adc_spi_dev {
    uint8_t inst;
    uint8_t ss_pin; 
};

/** Buffers for packets */
// 8B extra for magic num
static char gnss_packet[31]; // 23 B
static char sensor_packet[61];
static char adc_packet[13]; // 5B
static char valve_packet[13];
static char comm_packet[22];

static const uint32_t flash_addr = 0x08040000; // Start of 2nd 256KB sector


static void build_gnss_packet(gnss_pvt_t* pvt, char* buffer);

static void build_sensor_data_packet(struct imu_result* imu1, struct imu_result* imu2, barometer_result_t* baro1, barometer_result_t* baro2, struct magnetometer_result_t* mag1, struct magnetometer_result_t* mag2, temperature_result_t* temp1, temperature_result_t* temp2, char* buffer);

bool fire_state_init(){
    enum ti_errc_t errc;
    ti_internal_flash_erase_sector(flash_addr);
    radio_init(&radio_dev, &radio_spi_config, &radio_config, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize radio");
    }
    errc = imu_init(&imu_dev1);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize IMU 1");
    }
    errc = imu_init(&imu_dev2);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize IMU 2");
    }
    gnss_init(&gnss_dev, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize GNSS");
    }
    barometer_init(&barometer_dev1, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize barometer 1");
    }
    barometer_init(&barometer_dev2, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize barometer 2");
    }
    temperature_init(&temperature_dev1, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize temperature 1");
    }
    temperature_init(&temperature_dev2, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize temperature 2");
    }
    magnetometer_init(&magnetometer_dev1);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize magnetometer 1");
    }
    magnetometer_init(&magnetometer_dev2);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to initialize magnetometer 2");
    }

    return 1;
}

int fire_state_run(){
    enum ti_errc_t errc;
    gnss_pvt_t gnss_pvt;
    gnss_get_pvt(&gnss_dev, &gnss_pvt, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to get GNSS PVT data");
    }
    // read gnss into buffer, write to flash + radio
    build_gnss_packet(&gnss_pvt, gnss_packet);
    errc = ti_internal_flash_write(flash_addr, gnss_packet, sizeof(gnss_packet));

    radio_transmit(&radio_dev, gnss_packet, sizeof(gnss_packet), &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to transmit GNSS packet");
    }

    struct imu_result imu_result1;
    struct imu_result imu_result2;
    errc = imu_transfer(&imu_dev1, &imu_result1);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to transfer IMU 1 data");
    }
    errc = imu_transfer(&imu_dev2, &imu_result2);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to transfer IMU 2 data");
    }

    temperature_result_t temperature_result1;
    temperature_result_t temperature_result2;
    temperature_read_temp(&temperature_dev1, &temperature_result1, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to read temperature 1 data");
    }
    temperature_read_temp(&temperature_dev2, &temperature_result2, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to read temperature 2 data");
    }
    barometer_result_t barometer_result1;
    barometer_result_t barometer_result2;
    barometer_read_temp(&barometer_dev1, &barometer_result1, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to read barometer 1 data");
    }
    barometer_read_temp(&barometer_dev2, &barometer_result2, &errc);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to read barometer 2 data");
    }
    struct magnetometer_result_t magnetometer_result1;
    struct magnetometer_result_t magnetometer_result2;  
    errc = magnetometer_transfer(&magnetometer_dev1, &magnetometer_result1);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to transfer magnetometer 1 data");
    }
    errc = magnetometer_transfer(&magnetometer_dev2, &magnetometer_result2);
    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to transfer magnetometer 2 data");
    }

    build_sensor_data_packet(&imu_result1, &imu_result2, &barometer_result1, &barometer_result2, &magnetometer_result1, &magnetometer_result2, &temperature_result1, &temperature_result2, sensor_packet);
    errc = ti_internal_flash_write(flash_addr, sensor_packet, sizeof(sensor_packet));
    radio_transmit(&radio_dev, sensor_packet, sizeof(sensor_packet), &errc);

    if (errc && errc != TI_ERRC_NONE) {
        TI_SET_ERRC(&errc, errc, "Failed to transmit sensor data packet");
    }

    // read/send adc/state packets

    return 6;
}

static void build_gnss_packet(gnss_pvt_t* pvt, char* buffer) {
    buffer[0] = MAGIC_HEADER >> 56;
    buffer[1] = MAGIC_HEADER >> 48;
    buffer[2] = MAGIC_HEADER >> 40;
    buffer[3] = MAGIC_HEADER >> 32;
    buffer[4] = MAGIC_HEADER >> 24;
    buffer[5] = MAGIC_HEADER >> 16;
    buffer[6] = MAGIC_HEADER >> 8;
    buffer[7] = MAGIC_HEADER;
    buffer[8] = 0x02; // GNSS packet type
    buffer[9] = pvt->lat >> 24;
    buffer[10] = pvt->lat >> 16;
    buffer[11] = pvt->lat >> 8;
    buffer[12] = pvt->lat;
    buffer[13] = pvt->lon >> 24;
    buffer[14] = pvt->lon >> 16;
    buffer[15] = pvt->lon >> 8;
    buffer[16] = pvt->lon;
    buffer[17] = pvt->height >> 24;
    buffer[18] = pvt->height >> 16;
    buffer[19] = pvt->height >> 8;
    buffer[20] = pvt->height;
    buffer[21] = pvt->vel_e >> 8;
    buffer[22] = pvt->vel_e;
    buffer[23] = pvt->vel_n >> 8;
    buffer[24] = pvt->vel_n;
    buffer[25] = pvt->vel_d >> 8;
    buffer[26] = pvt->vel_d;
    buffer[27] = pvt->day;
    buffer[28] = pvt->hour;
    buffer[29] = pvt->min;
    buffer[30] = pvt->sec;
}

static void build_sensor_data_packet(struct imu_result* imu1, struct imu_result* imu2, barometer_result_t* baro1, barometer_result_t* baro2, struct magnetometer_result_t* mag1, struct magnetometer_result_t* mag2, temperature_result_t* temp1, temperature_result_t* temp2, char* buffer) {
    buffer[0] = MAGIC_HEADER >> 56;
    buffer[1] = MAGIC_HEADER >> 48;
    buffer[2] = MAGIC_HEADER >> 40;
    buffer[3] = MAGIC_HEADER >> 32;
    buffer[4] = MAGIC_HEADER >> 24;
    buffer[5] = MAGIC_HEADER >> 16;
    buffer[6] = MAGIC_HEADER >> 8;
    buffer[7] = MAGIC_HEADER;
    buffer[8] = 0x01; // Sensor data packet type
    buffer[9] = imu1->accel_x >> 8;
    buffer[10] = imu1->accel_x;
    buffer[11] = imu1->accel_y >> 8;
    buffer[12] = imu1->accel_y;
    buffer[13] = imu1->accel_z >> 8;
    buffer[14] = imu1->accel_z;
    buffer[15] = imu1->gyro_x >> 8;
    buffer[16] = imu1->gyro_x;
    buffer[17] = imu1->gyro_y >> 8;
    buffer[18] = imu1->gyro_y;
    buffer[19] = imu1->gyro_z >> 8;
    buffer[20] = imu1->gyro_z;
    buffer[21] = imu2->accel_x >> 8;
    buffer[22] = imu2->accel_x;
    buffer[23] = imu2->accel_y >> 8;
    buffer[24] = imu2->accel_y;
    buffer[25] = imu2->accel_z >> 8;
    buffer[26] = imu2->accel_z;
    buffer[27] = imu2->gyro_x >> 8;
    buffer[28] = imu2->gyro_x;
    buffer[29] = imu2->gyro_y >> 8;
    buffer[30] = imu2->gyro_y;
    buffer[31] = imu2->gyro_z >> 8;
    buffer[32] = imu2->gyro_z;
    buffer[33] = mag1->mag_x >> 8;
    buffer[34] = mag1->mag_x;
    buffer[35] = mag1->mag_y >> 8;
    buffer[36] = mag1->mag_y;
    buffer[37] = mag1->mag_z >> 8;
    buffer[38] = mag1->mag_z;
    buffer[39] = mag2->mag_x >> 8;
    buffer[40] = mag2->mag_x;
    buffer[41] = mag2->mag_y >> 8;
    buffer[42] = mag2->mag_y;
    buffer[43] = mag2->mag_z >> 8;
    buffer[44] = mag2->mag_z;
    buffer[45] = baro1->pressure >> 16;
    buffer[46] = baro1->pressure >> 8;
    buffer[47] = baro1->pressure;
    buffer[48] = baro2->pressure >> 16;
    buffer[49] = baro2->pressure >> 8;
    buffer[50] = baro2->pressure;
    buffer[51] = temp1->temperature >> 8;
    buffer[52] = temp1->temperature;
    buffer[53] = temp2->temperature >> 8;
    buffer[54] = temp2->temperature;
    buffer[55] = 0; // Placeholder for current sensor 1
    buffer[56] = 0;
    buffer[57] = 0; // Placeholder for current sensor 2     
    buffer[58] = 0;
    buffer[59] = 0; // Placeholder for current sensor 3
    buffer[60] = 0;
}

bool fire_state_destroy(){
    return 1;
}

state build_fire_state() {
    const state fire_state = {
        .init = &fire_state_init,
        .run = &fire_state_run,
        .destroy = &fire_state_destroy
    };
    return fire_state;
}