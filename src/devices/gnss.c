/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * @file devices/gnss.c
 * @authors Mahir Emran
 * @brief NEO-M8Q-01A u-blox M8 concurrent GNSS module driver implementation
 */

#include "devices/gnss.h"
#include "peripheral/errc.h"
#include "peripheral/log.h"
#include <stddef.h>

/* UBX Protocol Synchronization and Class IDs */
#define UBX_SYNC1 0xB5
#define UBX_SYNC2 0x62

#define UBX_CLASS_NAV 0x01
#define UBX_CLASS_ACK 0x05
#define UBX_CLASS_CFG 0x06

/* UBX Message IDs */
#define UBX_NAV_PVT   0x07
#define UBX_CFG_RATE  0x08
#define UBX_CFG_NAV5  0x24
#define UBX_CFG_GNSS  0x3E
#define UBX_CFG_PMS   0x86
#define UBX_ACK_NAK   0x00
#define UBX_ACK_ACK   0x01


/* 
 * Assuming standard SPI transmit/receive function signatures from peripheral/spi.h.
 * Adjust these externs if your spi.h uses slightly different naming conventions. 
 */
extern enum ti_errc_t spi_tx(uint8_t spi_inst, uint8_t ss_pin, const uint8_t *tx_data, uint32_t len);
extern enum ti_errc_t spi_rx(uint8_t spi_inst, uint8_t ss_pin, uint8_t *rx_data, uint32_t len);

/**************************************************************************************************
 * @section UBX Payload Structures
 **************************************************************************************************/
#pragma pack(push, 1)

typedef struct {
    uint16_t measRate;
    uint16_t navRate;
    uint16_t timeRef;
} ubx_cfg_rate_t;

typedef struct {
    uint16_t mask;
    uint8_t  dynModel;
    uint8_t  fixMode;
    int32_t  fixedAlt;
    uint32_t fixedAltVar;
    int8_t   minElev;
    uint8_t  drLimit;
    uint16_t pDop;
    uint16_t tDop;
    uint16_t vDop;
    uint16_t cDop;
    uint8_t  reserved1[4];
    uint8_t  dynCbg;
    uint8_t  reserved2[11];
} ubx_cfg_nav5_t;

typedef struct {
    uint8_t  version;
    uint8_t  powerSetupValue;
    uint16_t period;
    uint16_t onTime;
    uint8_t  reserved[2];
} ubx_cfg_pms_t;

typedef struct {
    uint8_t  gnssId;
    uint8_t  resTrkCh;
    uint8_t  maxTrkCh;
    uint8_t  reserved1;
    uint32_t flags;
} ubx_cfg_gnss_block_t;

typedef struct {
    uint8_t msgVer;
    uint8_t numTrkChHw;
    uint8_t numTrkChUse;
    uint8_t numConfigBlocks;
    ubx_cfg_gnss_block_t blocks[6]; // GPS, SBAS, Galileo, BeiDou, QZSS, GLONASS
} ubx_cfg_gnss_t;

typedef struct {
    uint32_t iTOW;
    uint16_t year;
    uint8_t  month;
    uint8_t  day;
    uint8_t  hour;
    uint8_t  min;
    uint8_t  sec;
    uint8_t  valid;
    uint32_t tAcc;
    int32_t  nano;
    uint8_t  fixType;
    uint8_t  flags;
    uint8_t  flags2;
    uint8_t  numSV;
    int32_t  lon;
    int32_t  lat;
    int32_t  height;
    int32_t  hMSL;
    uint32_t hAcc;
    uint32_t vAcc;
    int32_t  velN;
    int32_t  velE;
    int32_t  velD;
    int32_t  gSpeed;
    int32_t  headMot;
    uint32_t sAcc;
    uint32_t headingAcc;
    uint16_t pDOP;
    uint8_t  reserved1[6];
    int32_t  headVeh;
    int16_t  magDec;
    uint16_t magAcc;
} ubx_nav_pvt_t;

#pragma pack(pop)

/**************************************************************************************************
 * @section Internal Helpers
 **************************************************************************************************/

/**
 * @brief Fletcher-8 Checksum calculation for UBX protocol
 */
static void ubx_calc_checksum(uint8_t class_id, uint8_t msg_id, uint16_t len, const uint8_t *payload, uint8_t *ck_a, uint8_t *ck_b) {
    *ck_a = 0;
    *ck_b = 0;
    
    *ck_a += class_id;       *ck_b += *ck_a;
    *ck_a += msg_id;         *ck_b += *ck_a;
    *ck_a += (len & 0xFF);   *ck_b += *ck_a;
    *ck_a += (len >> 8);     *ck_b += *ck_a;
    
    for (uint16_t i = 0; i < len; i++) {
        *ck_a += payload[i];
        *ck_b += *ck_a;
    }
}

/**
 * @brief Transmits a UBX frame over SPI
 */
static enum ti_errc_t ubx_send_msg(gnss_t *dev, uint8_t class_id, uint8_t msg_id, const void *payload, uint16_t len) {
    uint8_t header[6] = {
        UBX_SYNC1, UBX_SYNC2, class_id, msg_id, 
        (uint8_t)(len & 0xFF), (uint8_t)((len >> 8) & 0xFF)
    };
    
    uint8_t ck_a, ck_b;
    ubx_calc_checksum(class_id, msg_id, len, (const uint8_t *)payload, &ck_a, &ck_b);
    uint8_t checksum[2] = {ck_a, ck_b};
    
    enum ti_errc_t err = spi_tx(dev->spi_config.spi_inst, dev->spi_config.ss_pin, header, 6);
    if (err != TI_ERRC_NONE) return err;
    
    if (len > 0) {
        err = spi_tx(dev->spi_config.spi_inst, dev->spi_config.ss_pin, (const uint8_t*)payload, len);
        if (err != TI_ERRC_NONE) return err;
    }
    
    return spi_tx(dev->spi_config.spi_inst, dev->spi_config.ss_pin, checksum, 2);
}

/**
 * @brief Sends a configuration message and blocks until ACK/NAK is received
 */
static enum ti_errc_t ubx_configure(gnss_t *dev, uint8_t class_id, uint8_t msg_id, const void *payload, uint16_t len) {
    enum ti_errc_t err = ubx_send_msg(dev, class_id, msg_id, payload, len);
    if (err != TI_ERRC_NONE) return err;
    
    uint8_t rx, state = 0, ack_id = 0;
    uint32_t attempts = 15000; // Safeguard against infinite loops
    
    while (attempts--) {
        err = spi_rx(dev->spi_config.spi_inst, dev->spi_config.ss_pin, &rx, 1);
        if (err != TI_ERRC_NONE) return err;
        
        if (rx == 0xFF) continue; // Idle byte from u-blox M8
        
        switch(state) {
            case 0: if (rx == UBX_SYNC1) state = 1; break;
            case 1: if (rx == UBX_SYNC2) state = 2; else state = 0; break;
            case 2: if (rx == UBX_CLASS_ACK) state = 3; else state = 0; break;
            case 3: 
                if (rx == UBX_ACK_ACK || rx == UBX_ACK_NAK) {
                    ack_id = rx;
                    state = 4;
                } else state = 0;
                break;
            case 4: state = 5; break; // Length LSB (skip check for brevity)
            case 5: state = 6; break; // Length MSB
            case 6: // Acknowledged Class
                if (rx == class_id) state = 7;
                else state = 0;
                break;
            case 7: // Acknowledged Message ID
                if (rx == msg_id) {
                    if (ack_id == UBX_ACK_ACK) return TI_ERRC_NONE;
                    TI_SET_ERRC(NULL, TI_ERRC_DEVICE, "GNSS module returned NAK for configuration command");
                    return TI_ERRC_DEVICE;
                }
                state = 0;
                break;
        }
    }
    TI_SET_ERRC(NULL, TI_ERRC_TIMEOUT, "Timed out waiting for UBX ACK/NAK response");
    return TI_ERRC_TIMEOUT;
}


/**************************************************************************************************
 * @section Public API Implementation
 **************************************************************************************************/

enum ti_errc_t gnss_init(gnss_t *dev) {
    if (!dev) {
        TI_SET_ERRC(NULL, TI_ERRC_INVALID_ARG, "dev pointer is NULL");
        return TI_ERRC_INVALID_ARG;
    }
    enum ti_errc_t err;

    /* 1. Configure Navigation/Measurement Rate (UBX-CFG-RATE) */
    ubx_cfg_rate_t rate_cfg = {
        .measRate = dev->config.meas_rate_ms,
        .navRate  = 1,
        .timeRef  = 0 // 0 = UTC
    };
    err = ubx_configure(dev, UBX_CLASS_CFG, UBX_CFG_RATE, &rate_cfg, sizeof(rate_cfg));
    if (err != TI_ERRC_NONE) return err;

    /* 2. Configure Dynamic Model (UBX-CFG-NAV5) */
    ubx_cfg_nav5_t nav5_cfg = {0};
    nav5_cfg.mask = 0x0001; // Bit 0: apply dynModel parameter
    nav5_cfg.dynModel = (uint8_t)dev->config.dyn_model;
    err = ubx_configure(dev, UBX_CLASS_CFG, UBX_CFG_NAV5, &nav5_cfg, sizeof(nav5_cfg));
    if (err != TI_ERRC_NONE) return err;

    /* 3. Configure Power Mode (UBX-CFG-PMS) */
    ubx_cfg_pms_t pms_cfg = {0};
    pms_cfg.version = 0;
    pms_cfg.powerSetupValue = (uint8_t)dev->config.power_mode; // Matches GNSS_POWER_CONTINUOUS / SAVE
    err = ubx_configure(dev, UBX_CLASS_CFG, UBX_CFG_PMS, &pms_cfg, sizeof(pms_cfg));
    if (err != TI_ERRC_NONE) return err;

    /* 4. Configure Constellations (UBX-CFG-GNSS) */
    ubx_cfg_gnss_t gnss_cfg = {0};
    gnss_cfg.msgVer = 0;
    gnss_cfg.numTrkChHw = 32;
    gnss_cfg.numTrkChUse = 32;
    gnss_cfg.numConfigBlocks = 6;
    
    // GPS block
    gnss_cfg.blocks[0].gnssId = 0; 
    gnss_cfg.blocks[0].resTrkCh = 8;
    gnss_cfg.blocks[0].maxTrkCh = 16;
    gnss_cfg.blocks[0].flags = (dev->config.constellation_mask & GNSS_CONSTELLATION_GPS) ? 0x01010001 : 0x01010000;
    
    // SBAS block
    gnss_cfg.blocks[1].gnssId = 1; 
    gnss_cfg.blocks[1].resTrkCh = 1;
    gnss_cfg.blocks[1].maxTrkCh = 3;
    gnss_cfg.blocks[1].flags = (dev->config.constellation_mask & GNSS_CONSTELLATION_SBAS) ? 0x01010001 : 0x01010000;

    // Galileo block
    gnss_cfg.blocks[2].gnssId = 2; 
    gnss_cfg.blocks[2].resTrkCh = 4;
    gnss_cfg.blocks[2].maxTrkCh = 8;
    gnss_cfg.blocks[2].flags = (dev->config.constellation_mask & GNSS_CONSTELLATION_GALILEO) ? 0x01010001 : 0x01010000;

    // BeiDou block
    gnss_cfg.blocks[3].gnssId = 3; 
    gnss_cfg.blocks[3].resTrkCh = 8;
    gnss_cfg.blocks[3].maxTrkCh = 16;
    gnss_cfg.blocks[3].flags = (dev->config.constellation_mask & GNSS_CONSTELLATION_BEIDOU) ? 0x01010001 : 0x01010000;

    // QZSS block
    gnss_cfg.blocks[4].gnssId = 5; 
    gnss_cfg.blocks[4].resTrkCh = 0;
    gnss_cfg.blocks[4].maxTrkCh = 3;
    gnss_cfg.blocks[4].flags = (dev->config.constellation_mask & GNSS_CONSTELLATION_QZSS) ? 0x01010001 : 0x01010000;

    // GLONASS block
    gnss_cfg.blocks[5].gnssId = 6; 
    gnss_cfg.blocks[5].resTrkCh = 8;
    gnss_cfg.blocks[5].maxTrkCh = 14;
    gnss_cfg.blocks[5].flags = (dev->config.constellation_mask & GNSS_CONSTELLATION_GLONASS) ? 0x01010001 : 0x01010000;

    err = ubx_configure(dev, UBX_CLASS_CFG, UBX_CFG_GNSS, &gnss_cfg, sizeof(gnss_cfg));
    if (err != TI_ERRC_NONE) return err;

    dev->initialized = 1;
    return TI_ERRC_NONE;
}

enum ti_errc_t gnss_get_pvt(gnss_t *dev, gnss_pvt_t *pvt) {
    if (!dev || !dev->initialized || !pvt) return TI_ERRC_INVALID_ARG;

    /* To poll a UBX message, send its class and ID with a zero-length payload */
    enum ti_errc_t err = ubx_send_msg(dev, UBX_CLASS_NAV, UBX_NAV_PVT, NULL, 0);
    if (err != TI_ERRC_NONE) return err;

    uint8_t rx, state = 0;
    uint16_t len = 0, idx = 0;
    uint8_t ck_a = 0, ck_b = 0, rcv_ck_a = 0, rcv_ck_b = 0;
    
    ubx_nav_pvt_t pvt_raw;
    uint8_t *pvt_ptr = (uint8_t *)&pvt_raw;
    
    uint32_t attempts = 15000;
    
    while (attempts--) {
        err = spi_rx(dev->spi_config.spi_inst, dev->spi_config.ss_pin, &rx, 1);
        if (err != TI_ERRC_NONE) return err;
        
        if (state == 0 && rx == 0xFF) continue; 
        
        switch(state) {
            case 0: 
                if (rx == UBX_SYNC1) state = 1; 
                break;
            case 1: 
                if (rx == UBX_SYNC2) { state = 2; ck_a = 0; ck_b = 0; }
                else state = 0; 
                break;
            case 2: // Class
                if (rx == UBX_CLASS_NAV) { ck_a += rx; ck_b += ck_a; state = 3; }
                else state = 0;
                break;
            case 3: // ID
                if (rx == UBX_NAV_PVT) { ck_a += rx; ck_b += ck_a; state = 4; }
                else state = 0;
                break;
            case 4: // Length LSB
                len = rx; ck_a += rx; ck_b += ck_a; state = 5;
                break;
            case 5: // Length MSB
                len |= ((uint16_t)rx << 8); ck_a += rx; ck_b += ck_a;
                if (len == sizeof(ubx_nav_pvt_t)) { state = 6; idx = 0; }
                else state = 0;
                break;
            case 6: // Payload
                pvt_ptr[idx++] = rx; ck_a += rx; ck_b += ck_a;
                if (idx == len) state = 7;
                break;
            case 7: // Checksum A
                rcv_ck_a = rx; state = 8;
                break;
            case 8: // Checksum B
                rcv_ck_b = rx;
                if (ck_a == rcv_ck_a && ck_b == rcv_ck_b) {
                    /* Validation passed; transpose onto destination struct */
                    pvt->year   = pvt_raw.year;
                    pvt->month  = pvt_raw.month;
                    pvt->day    = pvt_raw.day;
                    pvt->hour   = pvt_raw.hour;
                    pvt->min    = pvt_raw.min;
                    pvt->sec    = pvt_raw.sec;
                    pvt->fix    = (gnss_fix_type_t)pvt_raw.fixType;
                    pvt->num_sv = pvt_raw.numSV;
                    pvt->lon    = pvt_raw.lon;
                    pvt->lat    = pvt_raw.lat;
                    pvt->height = pvt_raw.height;
                    pvt->h_msl  = pvt_raw.hMSL;
                    pvt->vel_n  = pvt_raw.velN;
                    pvt->vel_e  = pvt_raw.velE;
                    pvt->vel_d  = pvt_raw.velD;
                    pvt->p_dop  = pvt_raw.pDOP;
                    return TI_ERRC_NONE;
                }
                state = 0; // Checksum invalid
                break;
        }
    }

    TI_SET_ERRC(NULL, TI_ERRC_TIMEOUT, "Timed out waiting for UBX-NAV-PVT response");
    return TI_ERRC_TIMEOUT;
}
