#include "UnixStamp.hpp"

UnixStamp::UnixStamp(unixstamp inintialUnix) : UnixStamp(inintialUnix, 0) {}

UnixStamp::UnixStamp(unixstamp inintialUnix, int8_t inintialTz)
{
    this->tz = inintialTz;
    this->unix = inintialUnix - (inintialTz * ONE_HOUR_IN_SEC);
    this->time = convertUnixToTime(inintialUnix, inintialTz);
}

UnixStamp::UnixStamp(civil_time initialTime) : UnixStamp(initialTime, 0) {}


UnixStamp::UnixStamp(civil_time initialTime, int8_t initialTz)
{
    this->tz = initialTz;
    this->unix = convertTimeToUnix(initialTime, initialTz);
    this->time = initialTz != 0 ? convertUnixToTime(this->unix, 0) : initialTime;
}

unixstamp UnixStamp::convertTimeToUnix(civil_time timeToConvert, int8_t fromTz)
{
    uint16_t year = timeToConvert.year;
    uint8_t month = timeToConvert.mon;
    year -= month <= 2;
    uint8_t era = ((year >= 0 ? year : (year - (YEARS_IN_ERA - 1))) / YEARS_IN_ERA);
    uint16_t yearOfEra = year % YEARS_IN_ERA;
    uint16_t dayOfYear = ((DAYS_BETWEEN_MARCH_AND_AUGUST * (month > 2 ? month - 3 : month + 9) + 2) / 5) + timeToConvert.day - 1;
    uint32_t dayOfEra = ((uint32_t)(yearOfEra * 365)) - ((uint32_t)(yearOfEra / 100)) + ((uint32_t)(yearOfEra / 4)) + dayOfYear;
    uint16_t days = (era * DAYS_IN_ERA) + dayOfEra - DAYS_BEFORE_UNIX;
    uint32_t unix = days * ONE_DAY_IN_SEC + (((uint32_t)(timeToConvert.hour - fromTz)) * ONE_HOUR_IN_SEC) + ((uint32_t)(timeToConvert.min * 60)) + timeToConvert.sec;
    return unix;
}

civil_time UnixStamp::convertUnixToTime(unixstamp unixToConvert, int8_t fromTz)
{
    civil_time time;
    uint8_t era, month;
    uint16_t dayOfYear, yearFromEra, monthFromDayOfYear;
    uint32_t eraDays, dayOfEra, yearOfEra;

    time.sec = unixToConvert % ONE_MINUTE_IN_SEC;
    unixToConvert /= ONE_MINUTE_IN_SEC;
    time.min = unixToConvert % ONE_HOUR_IN_MIN;
    unixToConvert /= ONE_HOUR_IN_MIN;
    time.hour = unixToConvert % ONE_DAY_IN_HOURS - fromTz;
    unixToConvert /= ONE_DAY_IN_HOURS;

    eraDays = unixToConvert + DAYS_BEFORE_UNIX;
    era = eraDays / DAYS_IN_ERA;
    dayOfEra = eraDays % DAYS_IN_ERA;
    yearOfEra = (dayOfEra - dayOfEra / FOUR_YEAR_CICLE_DAYS + dayOfEra / FIRST_100_YEARS_OF_ERA - dayOfEra / (DAYS_IN_ERA - 1)) / APPROXIMATE_DAYS_IN_YEAR;
    yearFromEra = yearOfEra + era * YEARS_IN_ERA;
    dayOfYear = dayOfEra - (yearOfEra * APPROXIMATE_DAYS_IN_YEAR + yearOfEra / FOUR_YEAR_CICLE_YEARS - yearOfEra / YEARS_IN_CENTURY);
    monthFromDayOfYear = (dayOfYear * 5 + 2) / DAYS_BETWEEN_MARCH_AND_AUGUST;
    time.day = (dayOfYear - (monthFromDayOfYear * DAYS_BETWEEN_MARCH_AND_AUGUST + 2) / 5) + 1;
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
    return this->tz;
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