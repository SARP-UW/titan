/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2026 UW SARP
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @file app/utils/valve.c
 * @authors Mahir Emran
 * @brief Utility functions to actuate valves by name
 */
#include "valve.h"
#include "devices/actuator.h"
#include "peripheral/gpio.h"
#include "peripheral/pwm.h"
#include "peripheral/errc.h"

static uint8_t get_spi_inst(int32_t mosi, int32_t miso) {
    // TODO: update based on later stuff
    if (mosi == 46 && miso == 45) return 1;
    if (mosi == 75 && miso == 74) return 2;
    if (mosi == 111 && miso == 110) return 3;
    if (mosi == 5 && miso == 4) return 4;
    if (mosi == 23 && miso == 22) return 5;
    if (mosi == 127 && miso == 126) return 6;
    return 0;
}

static bool get_pwm_inst_chan(int32_t pin, uint8_t *inst, uint8_t *chan) {
    // TODO - update based on later stuff
    if (pin == 37) { *inst = 2; *chan = 1; return true; }
    if (pin == 38) { *inst = 2; *chan = 2; return true; }
    if (pin == 39) { *inst = 2; *chan = 3; return true; }
    if (pin == 40) { *inst = 2; *chan = 4; return true; }
    if (pin == 45) { *inst = 3; *chan = 1; return true; }
    if (pin == 46) { *inst = 3; *chan = 2; return true; }
    if (pin == 49) { *inst = 3; *chan = 3; return true; }
    if (pin == 50) { *inst = 3; *chan = 4; return true; }
    if (pin == 133) { *inst = 4; *chan = 1; return true; }
    if (pin == 134) { *inst = 4; *chan = 2; return true; }
    if (pin == 136) { *inst = 4; *chan = 3; return true; }
    if (pin == 137) { *inst = 4; *chan = 4; return true; }
    return false;
}

void set_valve(struct valve_t* valve, bool actuated, enum ti_errc_t* errc) {
    if (errc) *errc = TI_ERRC_NONE;
    if (!valve) {
        TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "valve parameter is NULL");
        return;
    }

    if (valve->is_spi) {
        actuator_t dev = {0};
        dev.spi_config.ss_pin = valve->pin_3; // CS pin
        dev.spi_config.spi_inst = get_spi_inst(valve->pin_1, valve->pin_2);
        
        if (dev.spi_config.spi_inst == 0) {
            TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid SPI pins");
            return;
        }

        // TODO: channel config hardcoded? valve might need it
        actuator_set_channel_enable(&dev, (actuator_channel_t)valve->channel, actuated, errc);
        if (errc && *errc != TI_ERRC_NONE) {
            TI_SET_ERRC(errc, *errc, "Propagated actuator error");
        }
    } else {
        uint8_t inst = 0, chan = 0;
        if (!get_pwm_inst_chan(valve->pin_1, &inst, &chan)) {
            TI_SET_ERRC(errc, TI_ERRC_INVALID_ARG, "Invalid PWM pin");
            return;
        }

        struct ti_pwm_config_t config = {
            .channel = chan,
            .instance = inst,
            .clock_freq = 4000000,
            .freq = 100,
            .duty = actuated ? 1000 : 0
        };

        ti_set_pwm(config, errc);
        if (errc && *errc != TI_ERRC_NONE) {
            TI_SET_ERRC(errc, *errc, "Propagated PWM error");
        }
    }
}
