#include <unity.h>
#include <UnixStamp.hpp>
#include <stdint.h>

#define EXPECETED_CHERNOBYL_TIMESTAMP 514848225
#define EXPECTED_ERROR -1

void setUp(void) {}

void tearDown(void) {}

civil_time fillTimeStruct(int16_t year, int8_t mon, int8_t day, int8_t hour, int8_t min, int8_t sec, int8_t tz) {
    civil_time time;
    time.year = year;
    time.mon = mon;
    time.day = day;
    time.hour = hour;
    time.min = min;
    time.sec = sec;
    time.tz = tz;
    return time;
}

void test_conversion_to_unix_unix_era_start()
{
    civil_time time = fillTimeStruct(1970, 1,  1, 0, 0, 0, 0);
    unixstamp unix = UnixStamp::convertTimeToUnix(time);
    TEST_ASSERT_EQUAL(0, unix);
}

void test_conversion_to_unix_chernobyl()
{
    civil_time time = fillTimeStruct(1986, 4,  25, 21, 23, 45, 0);
    unixstamp unix = UnixStamp::convertTimeToUnix(time);
    TEST_ASSERT_EQUAL(EXPECETED_CHERNOBYL_TIMESTAMP, unix);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_conversion_to_unix_unix_era_start);
    RUN_TEST(test_conversion_to_unix_chernobyl);
    return UNITY_END();
}