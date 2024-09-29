#ifndef TIMEDATATYPES_HPP
#define TIMEDATATYPES_HPP

#include <stdint.h>

typedef uint32_t unixstamp;

struct civil_time
{
    uint8_t sec;
    uint8_t min;
    uint8_t hour;
    uint8_t day;
    uint8_t mon;
    uint16_t year;
    int8_t tz;
};

#endif