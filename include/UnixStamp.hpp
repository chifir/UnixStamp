#ifndef UNIXSTAMP_HPP
#define UNIXSTAMP_HPP

#include<stdint.h>
#include<time.h>

#define ONE_MINUTE_IN_SEC 60
#define ONE_HOUR_IN_MIN 60
#define ONE_DAY_IN_HOURS 24

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
    time_t unix;
    int8_t tz;
    tm time;

public:
    time_t getUnix();
    int8_t getTz();
    tm getTime();

    UnixStamp(time_t unix);
    UnixStamp(time_t unix, int8_t tz);
    UnixStamp(tm time);
    UnixStamp(tm time, int8_t tz);

    uint16_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();

    static time_t covertTimeToUnix(tm time, int8_t tz);
    static tm covertUnixToTime(time_t unix, int8_t tz);
};

#endif
