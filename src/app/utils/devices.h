#pragma once

#include <stdint.h>

#include "app/utils/pinout.h"
#include "devices/adc.h"
#include "devices/actuator.h"
#include "devices/barometer.h"
#include "devices/gnss.h"
#include "devices/imu.h"
#include "devices/magnetometer.h"
#include "devices/radio.h"
#include "devices/temperature.h"

#define VALVE_COUNT 12U
#define SERVO_COUNT 8U

static radio_t radio_dev;
static radio_spi_dev radio_spi_config = {
	.spi_inst = (uint8_t)RADIO_SPI_INST,
	.ss_pin = (uint8_t)RADIO_SPI_CS
};

static radio_config_t radio_config = {
	.reset_pin = (uint8_t)RADIO_SHDN,
	.nirq_pin = (uint8_t)RADIO_IRQ,
	.reset_active_high = 0,
	.channel = 0
};

static gnss_t gnss_dev = {
	.spi_config = {
		.spi_inst = (uint8_t)GNSS_SPI_INST,
		.ss_pin = (uint8_t)GNSS_SPI_CS
	},
	.config = {
		.meas_rate_ms = 200,
		.constellation_mask = GNSS_CONSTELLATION_GPS | GNSS_CONSTELLATION_GLONASS | GNSS_CONSTELLATION_BEIDOU,
		.dyn_model = GNSS_DYN_AIRBORNE_4G,
		.power_mode = GNSS_POWER_CONTINUOUS
	},
	.initialized = 0
};

static struct imu_spi_dev imu_dev1 = {
	.inst = (uint8_t)SENSOR_SPI_INST,
	.ss_pin = (uint8_t)IMU_1_CS
};

static struct imu_spi_dev imu_dev2 = {
	.inst = (uint8_t)SENSOR_SPI_INST,
	.ss_pin = (uint8_t)IMU_2_CS
};

static barometer_t barometer_dev1 = {
	.spi_dev = {
		.inst = (uint8_t)SENSOR_SPI_INST,
		.ss_pin = (uint8_t)BARO_1_CS
	},
	.osr = OSR_4096,
	.calibration_data = {0},
	.result = {0}
};

static barometer_t barometer_dev2 = {
	.spi_dev = {
		.inst = (uint8_t)SENSOR_SPI_INST,
		.ss_pin = (uint8_t)BARO_2_CS
	},
	.osr = OSR_4096,
	.calibration_data = {0},
	.result = {0}
};

static struct magnetometer_spi_dev magnetometer_dev1 = {
	.inst = (uint8_t)SENSOR_SPI_INST,
	.ss_pin = (uint8_t)MAGNOTOMETER_CS
};

static struct magnetometer_spi_dev magnetometer_dev2 = {
	.inst = (uint8_t)SENSOR_SPI_INST,
	.ss_pin = (uint8_t)MAGNOTOMETER_CS
};

static temperature_t temperature_dev1 = {
	.spi_config = {
		.spi_inst = (uint8_t)SENSOR_SPI_INST,
		.ss_pin = (uint8_t)POWER_TMP_CS
	},
	.config = {
		.mode = temperature_MODE_CONTINUOUS,
		.resolution = temperature_RES_16_BIT
	}
};

static temperature_t temperature_dev2 = {
	.spi_config = {
		.spi_inst = (uint8_t)SENSOR_SPI_INST,
		.ss_pin = (uint8_t)ANALOG_TMP_CS
	},
	.config = {
		.mode = temperature_MODE_CONTINUOUS,
		.resolution = temperature_RES_16_BIT
	}
};

static struct adc_spi_dev adc_dev = {
	.inst = (uint8_t)SENSOR_SPI_INST,
	.ss_pin = (uint8_t)SENSOR_CS_1
};

static const struct adc_channel adc_channels[] = {
	{
		.pos_pin = AIN0,
		.neg_pin = AINCOM,
		.gain = GAIN_1,
		.source = REF_INTERNAL,
		.ref_voltage = 25,
		.name = "adc0"
	}
};

static const uint8_t adc_channel_count = (uint8_t)(sizeof(adc_channels) / sizeof(adc_channels[0]));

static uint8_t valve_states[VALVE_COUNT];
static uint16_t servo_states[SERVO_COUNT];
