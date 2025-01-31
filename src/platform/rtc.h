/**
 * This file is part of the Titan Flight Computer Project
 * Copyright (c) 2024 UW SARP
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
 * @file common/platform/rtc.h
 * @authors Charles Faisandier
 * @brief Driver for the RTC
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "mmio.h"

#if defined(__cplusplus)
  extern "C" {
#endif

typedef struct {
  int16_t hours;

  int16_t mins;

  int16_t secs;

  int16_t years;

  int16_t weekday;

  int16_t month;

  int16_t date;

  double subsec;

} RTC_datetime;

RTC_datetime tal_read_RTC();

bool tal_write_RTC(RTC_datetime datetime);

bool tal_init_RTC();

/////////////////////////////////////////////////
// IMPLEMENTATION
/////////////////////////////////////////////////

RTC_datetime tal_read_RTC()
{
  RTC_datetime res;
  res.hours = read_field(RTC_RTC_TR, RTC_RTC_TR_HT) * 10 + read_field(RTC_RTC_TR, RTC_RTC_TR_HU);
  res.mins =  read_field(RTC_RTC_TR, RTC_RTC_TR_MNT) * 10 + read_field(RTC_RTC_TR, RTC_RTC_TR_MNU);
  res.secs = read_field(RTC_RTC_TR, RTC_RTC_TR_ST) * 10 + read_field(RTC_RTC_TR, RTC_RTC_TR_SU);
  res.years = read_field(RTC_RTC_DR, RTC_RTC_DR_YT) * 10 + read_field(RTC_RTC_TR, RTC_RTC_DR_YU);
  res.weekday = read_field(RTC_RTC_DR, RTC_RTC_DR_WDU);
  res.month = read_field(RTC_RTC_DR, RTC_RTC_DR_MT) * 10 + read_field(RTC_RTC_TR, RTC_RTC_DR_MU);
  res.date = read_field(RTC_RTC_DR, RTC_RTC_DR_DT) * 10 + read_field(RTC_RTC_TR, RTC_RTC_DR_DU);
  double prer = read_field(RTC_RTC_PRER, RTC_RTC_PRER_PREDIV_S);
  res.subsec = (prer - read_field(RTC_RTC_SSR, RTC_RTC_SSR_SS))/(prer + 1);
  return res;
}

bool tal_write_RTC(RTC_datetime init_dt)
{
  // Enter init mode
  set_field(RTC_RTC_ISR, RTC_RTC_ISR_INIT, true);
  if (get_field(RTC_RTC_ISR, RTC_RTC_ISR_INITF) != 1) 
    return false;

  // Write datetime
  write_field(RTC_RTC_TR, RTC_RTC_TR_HT, init_dt.hours / 10);
  write_field(RTC_RTC_TR, RTC_RTC_TR_HU, init_dt.hours % 10);
  write_field(RTC_RTC_TR, RTC_RTC_TR_MNT, init_dt.mins / 10);
  write_field(RTC_RTC_TR, RTC_RTC_TR_MNU, init_dt.mins % 10);
  write_field(RTC_RTC_TR, RTC_RTC_TR_ST, init_dt.secs / 10);
  write_field(RTC_RTC_TR, RTC_RTC_TR_SU, init_dt.secs % 10);
  write_field(RTC_RTC_DR, RTC_RTC_DR_YT, init_dt.years / 10);
  write_field(RTC_RTC_DR, RTC_RTC_DR_YU, init_dt.years % 10);
  write_field(RTC_RTC_DR, RTC_RTC_DR_WDU, init_dt.weekday);
  write_field(RTC_RTC_DR, RTC_RTC_DR_MT, init_dt.month / 10);
  write_field(RTC_RTC_DR, RTC_RTC_DR_MU, init_dt.month % 10);
  write_field(RTC_RTC_DR, RTC_RTC_DR_DT, init_dt.date / 10);
  write_field(RTC_RTC_DR, RTC_RTC_DR_DU, init_dt.date % 10);
  
  // Leave INIT Mode
  set_field(RTC_RTC_ISR, RTC_RTC_ISR_INIT, false);
  return true;
}


bool tal_RTC_init()
{
  // Disable write protection
  set_field(PWR_CRx[1], PWR_CRx_DBP, true);
  write_field(RTC_RTC_WPR, RTC_RTC_WPR_KEY, 0xCA);
  write_field(RTC_RTC_WPR, RTC_RTC_WPR_KEY, 0x53);

  // Enter Initialization Mode
  set_field(RTC_RTC_ISR, RTC_RTC_ISR_INIT, true);
  if (get_field(RTC_RTC_ISR, RTC_RTC_ISR_INITF) != 1) 
    return false;

  // set RTC_CR register, with hour format
  set_field(RTC_RTC_CR, RTC_RTC_CR_FMT, false);

  // configure RTC_PRER with Predivs both async and sync
  write_field(RTC_RTC_PRER, RTC_RTC_PRER_PREDIV_A, 128);
  write_field(RTC_RTC_PRER, RTC_RTC_PRER_PREDIV_S, 256);
  
  // exit rtc_init mode
  set_field(RTC_RTC_ISR, RTC_RTC_ISR_INIT, false);
}


#if defined(__cplusplus)
}
#endif
