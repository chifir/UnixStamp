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
#define DAYS_BETWEEN_MARCH_AND_AUGUST 153

class UnixStamp
{
private:
    // The timestamp is in GMT+0
    unixstamp unix;

public:
    UnixStamp(unixstamp initialUnix);
    UnixStamp(civil_time intialTime);
    UnixStamp(civil_time intialTime, int8_t initialTz);

    civil_time getTimeInTz(int8_t tz);

    unixstamp getUnix();

    // Convert civil time in timezone 'tz' to the unix timestamp in GMT+0
    static unixstamp convertTimeToUnix(civil_time time, int8_t tz);
    // Convert unix timestamp in timezone 'tz' to the civil time in GMT+0
    static civil_time convertUnixToTime(unixstamp unix, int8_t tz);
};

#endif
