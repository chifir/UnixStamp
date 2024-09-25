#ifndef UNIXSTAMP_HPP
#define UNIXSTAMP_HPP

#include <stdint.h>
#include "TimeDataTypes.hpp"

#define ONE_HOUR_IN_SEC 3600
#define ONE_MINUTE_IN_SEC 60
#define ONE_HOUR_IN_MIN 60
#define ONE_DAY_IN_HOURS 24
#define ONE_DAY_IN_SEC 86400

#define START_YEAR_TIME_H 1900

#define DAYS_BEFORE_UNIX 719468
#define YEARS_IN_ERA 400
#define DAYS_IN_ERA 146097
#define FOUR_YEAR_CICLE_DAYS 1460
#define FIRST_100_YEARS_OF_ERA 36524
#define APPROXIMATE_DAYS_IN_YEAR 365
#define FOUR_YEAR_CICLE_YEARS 4
#define YEARS_IN_CENTURY 100
#define DAYS_AFTER_FIRST_MARCH 153

class UnixStamp
{
private:
    unixstamp unix;
    civil_time time;

public:
    unixstamp getUnix();
    int8_t getTz();
    civil_time getTime();

    UnixStamp(unixstamp unix);
    UnixStamp(unixstamp unix, int8_t tz);
    UnixStamp(civil_time time);
    UnixStamp(civil_time time, int8_t tz);

    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();

    static unixstamp convertTimeToUnix(civil_time time);
    static civil_time convertUnixToTime(unixstamp unix, int8_t tz);
};

#endif
