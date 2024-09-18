#include "UnixStamp.hpp"

UnixStamp::UnixStamp(time_t unix)
{
    UnixStamp(unix, 0);
}

UnixStamp::UnixStamp(time_t unix, int8_t tz)
{
    this->unix = unix;
    this->tz = tz;
    this->time = convertUnixToTime(unix, tz);
}

UnixStamp::UnixStamp(tm time)
{
    UnixStamp(time, 0);
}

UnixStamp::UnixStamp(tm time, int8_t tz)
{
    this->time = time;
    this->tz = tz;
    this->unix = convertTimeToUnix(time, tz);
}

time_t UnixStamp::convertTimeToUnix(tm time, int8_t tz)
{
    time.tm_hour += tz;
    return mktime(&time);
}

tm UnixStamp::convertUnixToTime(time_t unix, int8_t tz)
{
    struct tm time;
    uint64_t eraStamp;
    uint16_t era, dayOfEra, yearOfEra, dayOfYear, yearFromEra, monthFromDayOfYear;
    uint8_t month;

    unix += tz * ONE_HOUR;
    time.tm_sec = unix % ONE_MINUTE_IN_SEC;
    unix /= ONE_MINUTE_IN_SEC;
    time.tm_min = unix % ONE_HOUR_IN_MIN;
    unix /= ONE_HOUR_IN_MIN;
    time.tm_hour = unix % ONE_DAY_IN_HOURS;
    unix /= ONE_DAY_IN_HOURS;

    eraStamp = unix + DAYS_BEFORE_UNIX;
    era = eraStamp / DAYS_IN_ERA;
    dayOfEra = eraStamp - era * DAYS_IN_ERA;
    yearOfEra = (dayOfEra - dayOfEra / FOUR_YEAR_CICLE_DAYS + dayOfEra / FIRST_100_YEARS_OF_ERA - dayOfEra / (DAYS_IN_ERA - 1)) / APPROXIMATE_DAYS_IN_YEAR;
    yearFromEra = yearOfEra + era * YEARS_IN_ERA;
    dayOfYear = dayOfEra - (yearOfEra * APPROXIMATE_DAYS_IN_YEAR + yearOfEra / FOUR_YEAR_CICLE_YEARS - yearOfEra / YEARS_IN_CENTURY);
    monthFromDayOfYear = (dayOfYear * 5 + 2) / DAYS_AFTER_FIRST_MARCH;
    time.tm_mday = dayOfYear - (monthFromDayOfYear * DAYS_AFTER_FIRST_MARCH + 2) / 5;
    month = monthFromDayOfYear + (monthFromDayOfYear < 10 ? 3 : -9);
    yearFromEra += (month <= 2);
    
    time.tm_year = yearFromEra - START_YEAR_TIME_H;
    time.tm_mon = month - 1;

    return time;
}

time_t UnixStamp::getUnix()
{
    return this->unix;
}
    
int8_t UnixStamp::getTz()
{
    return this->tz;
}
    
tm UnixStamp::getTime()
{
    return this->time;
}

uint16_t UnixStamp::getYear()
{
    return this->time.tm_year + START_YEAR_TIME_H;
}

uint8_t UnixStamp::getMonth()
{
    return this->time.tm_mon + 1;
}

uint8_t UnixStamp::getDay()
{
    return this->time.tm_mday + 1;
}

uint8_t UnixStamp::getHour()
{
    return this->time.tm_hour;
}

uint8_t UnixStamp::getMinute()
{
    return this->time.tm_min;
}

uint8_t UnixStamp::getSecond()
{
    return this->time.tm_sec;
}
