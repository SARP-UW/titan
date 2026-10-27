#include "current.h"
#include "./peripheral/i2c.h"
#include "peripheral/errc.h"

#define READ_IIN 0x89
#define MFR_CALIBRATION 0xD4
#define MFR_ADC_CONFIG 0xD0

void current_init(const struct current_i2c_dev *dev, const struct current_config_t *config,
                  enum ti_errc_t *errc) {
    //
    // write to 0xD4 (MFR_CALIBRATION)
    //      0.00512 / (current_LSB * shunt resistance)
    //      LSB is just config->current_lsb_ua which is just the scaling factor for the raw value
    //
    // write to 0xD0 (MFR_ADC_CONFIG)
    //      default value is 0x4127

    uint64_t denominator = config->current_lsb_ua * config->shunt_uohms;
    uint64_t calibration = 5120000000ULL / denominator;

    uint8_t calibration_packet[] = {MFR_CALIBRATION, (uint8_t)calibration,
                                    (uint8_t)(calibration >> 8)};

    i2c_write(dev->inst, dev->addr, calibration_packet, sizeof(calibration_packet), errc);
    if (errc != TI_ERRC_NONE)
        return;

    uint8_t adc_packet[] = {MFR_ADC_CONFIG, (uint8_t)config->adc_config,
                            (uint8_t)(config->adc_config >> 8)};
    i2c_write(dev->inst, dev->addr, adc_packet, sizeof(adc_packet), errc);
    if (errc != TI_ERRC_NONE)
        return;
}

void current_read(const struct current_i2c_dev *dev, const struct current_config_t *config,
                  struct current_result_t *result, enum ti_errc_t *errc) {
    if (!errc)
        return;

    uint8_t input_reg = READ_IIN;

    i2c_write(dev->inst, dev->addr, &input_reg, sizeof(uint8_t), errc);

    if (errc != TI_ERRC_NONE)
        return;

    uint8_t res[2];
    i2c_read(dev->inst, dev->addr, res, sizeof(res), errc);

    if (errc != TI_ERRC_NONE)
        return;

    uint16_t raw_value = (uint16_t)(res[0]) | (uint16_t)(res[1] << 8);

    result->raw_value = raw_value;
    result->current_ma = ((int64_t)result->raw_value * config->current_lsb_ua) / 1000;
}
