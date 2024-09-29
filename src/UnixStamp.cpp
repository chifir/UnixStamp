#include "UnixStamp.hpp"

UnixStamp::UnixStamp(unixstamp unix)
{
    UnixStamp(unix, 0);
}

UnixStamp::UnixStamp(unixstamp unix, int8_t tz)
{
    this->unix = unix;
    this->time = convertUnixToTime(unix, tz);
}

UnixStamp::UnixStamp(civil_time time)
{
    UnixStamp(time, 0);
}

UnixStamp::UnixStamp(civil_time time, int8_t tz)
{
    this->time = time;
    this->unix = convertTimeToUnix(time);
}

unixstamp UnixStamp::convertTimeToUnix(civil_time time)
{
    uint16_t year = time.year;
    uint8_t month = time.mon;
    year -= month <= 2;
    uint8_t era = ((year >= 0 ? year : (year - YEARS_IN_ERA - 1)) / YEARS_IN_ERA);
    uint16_t yearOfEra = year % YEARS_IN_ERA;
    uint16_t dayOfYear = ((DAYS_AFTER_FIRST_MARCH * (month > 2 ? month - 3 : month + 9) + 2) / 5) + time.day - 1;
    uint32_t dayOfEra = ((uint32_t)(yearOfEra * 365)) - ((uint32_t)(yearOfEra / 100)) + ((uint32_t)(yearOfEra / 4)) + dayOfYear;
    uint16_t days = (era * DAYS_IN_ERA) + dayOfEra - DAYS_BEFORE_UNIX;
    uint32_t unix = days * ONE_DAY_IN_SEC + (((uint32_t)(time.hour + time.tz)) * ONE_HOUR_IN_SEC) + ((uint32_t)(time.min * 60)) + time.sec;
    return unix;
}

civil_time UnixStamp::convertUnixToTime(unixstamp unix, int8_t tz)
{
    civil_time time;
    uint8_t era, month;
    uint16_t dayOfYear, yearFromEra, monthFromDayOfYear;
    uint32_t eraDays, dayOfEra, yearOfEra;

    unix -= tz * ONE_HOUR_IN_SEC;
    time.sec = unix % ONE_MINUTE_IN_SEC;
    unix /= ONE_MINUTE_IN_SEC;
    time.min = unix % ONE_HOUR_IN_MIN;
    unix /= ONE_HOUR_IN_MIN;
    time.hour = unix % ONE_DAY_IN_HOURS;
    unix /= ONE_DAY_IN_HOURS;

    eraDays = unix + DAYS_BEFORE_UNIX;
    era = eraDays / DAYS_IN_ERA;
    dayOfEra = eraDays % DAYS_IN_ERA;
    yearOfEra = (dayOfEra - dayOfEra / FOUR_YEAR_CICLE_DAYS + dayOfEra / FIRST_100_YEARS_OF_ERA - dayOfEra / (DAYS_IN_ERA - 1)) / APPROXIMATE_DAYS_IN_YEAR;
    yearFromEra = yearOfEra + era * YEARS_IN_ERA;
    dayOfYear = dayOfEra - (yearOfEra * APPROXIMATE_DAYS_IN_YEAR + yearOfEra / FOUR_YEAR_CICLE_YEARS - yearOfEra / YEARS_IN_CENTURY);
    monthFromDayOfYear = (dayOfYear * 5 + 2) / DAYS_AFTER_FIRST_MARCH;
    time.day = (dayOfYear - (monthFromDayOfYear * DAYS_AFTER_FIRST_MARCH + 2) / 5) + 1;
    month = monthFromDayOfYear + (monthFromDayOfYear < 10 ? 3 : -9);
    yearFromEra += (month <= 2);

    time.year = yearFromEra;
    time.mon = month;

    return time;
}

unixstamp UnixStamp::getUnix()
{
    return this->unix;
}

int8_t UnixStamp::getTz()
{
    return this->time.tz;
}

civil_time UnixStamp::getTime()
{
    return this->time;
}

uint16_t UnixStamp::getYear()
{
    return this->time.year;
}

uint8_t UnixStamp::getMonth()
{
    return this->time.mon;
}

uint8_t UnixStamp::getDay()
{
    return this->time.day;
}

uint8_t UnixStamp::getHour()
{
    return this->time.hour;
}

uint8_t UnixStamp::getMinute()
{
    return this->time.min;
}

uint8_t UnixStamp::getSecond()
{
    return this->time.sec;
}