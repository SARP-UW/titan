#include "clock.h"
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>  // For sub-second precision on Unix

// Simulates initializing the clock hardware
bool init_clock() {
    // In a real system, you'd initialize RTC hardware here.
    // For simulation, assume success.
    return true;
}

// Reads the current system time and fills the DateTime struct
DateTime read_clock() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    struct tm *tm_info = localtime(&tv.tv_sec);

    DateTime dt;
    dt.hours    = tm_info->tm_hour;
    dt.mins     = tm_info->tm_min;
    dt.secs     = tm_info->tm_sec;
    dt.years    = tm_info->tm_year + 1900;
    dt.weekday  = tm_info->tm_wday;
    dt.month    = tm_info->tm_mon + 1;  // tm_mon: 0-11
    dt.date     = tm_info->tm_mday;
    dt.subsec   = tv.tv_usec / 1e6;

    return dt;
}

// Writes the time to the system clock (requires privileges on some systems)
bool write_clock(DateTime datetime) {
    struct tm tm_info;
    tm_info.tm_sec  = datetime.secs;
    tm_info.tm_min  = datetime.mins;
    tm_info.tm_hour = datetime.hours;
    tm_info.tm_mday = datetime.date;
    tm_info.tm_mon  = datetime.month - 1;  // tm_mon: 0-11
    tm_info.tm_year = datetime.years - 1900;
    tm_info.tm_wday = datetime.weekday;    // tm_wday is ignored by mktime

    time_t t = mktime(&tm_info);
    if (t == -1) return false;

    struct timeval tv;
    tv.tv_sec = t;
    tv.tv_usec = (suseconds_t)(datetime.subsec * 1e6);

    // Set system time — may fail without appropriate permissions
    return settimeofday(&tv, NULL) == 0;
}
