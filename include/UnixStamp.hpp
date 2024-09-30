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
    // Both timestamps are saved in GMT+0
    unixstamp unix;
    civil_time time;
    uint8_t tz;

public:
    unixstamp getUnix();
    civil_time getTime();
    int8_t getTz();

    UnixStamp(unixstamp initialUnix);
    UnixStamp(unixstamp initialUnix, int8_t initialTz);
    UnixStamp(civil_time intialTime);
    UnixStamp(civil_time intialTime, int8_t initialTz);

    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();

    // Convert civil time in timezone 'tz' to the unix timestamp in GMT+0
    static unixstamp convertTimeToUnix(civil_time time, int8_t tz);
    // Convert unix timestamp in timezone 'tz' to the civil time in GMT+0
    static civil_time convertUnixToTime(unixstamp unix, int8_t tz);
};

#endif
