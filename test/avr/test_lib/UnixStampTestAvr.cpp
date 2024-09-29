#include <unity.h>
#include <UnixStamp.hpp>
#include <stdint.h>

#define EXPECETED_CHERNOBYL_TIMESTAMP 514848225
#define EXPECTED_ERA_END 951868799 
#define EXPECTED_ERA_START 951868800 
#define EXPECTED_EPOCH_LEFT_BORDER 0
#define EXPECTED_EPOCH_RIGHT_BORDER 4294967295


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

void verify_date_conversion_from_civil_to_epoch(uint32_t expected_unix, int16_t year, int8_t mon, int8_t day, int8_t hour, int8_t min, int8_t sec, int8_t tz) 
{
    civil_time time = fillTimeStruct(year, mon, day, hour, min, sec, tz);
    unixstamp unix = UnixStamp::convertTimeToUnix(time);
    TEST_ASSERT_EQUAL(expected_unix, unix);
}

void verify_date_conversion_from_epoch_to_civil(int16_t expected_year, int8_t expected_mon, int8_t expected_day, int8_t expected_hour, int8_t expected_min, int8_t expected_sec, int8_t expected_tz, uint32_t unix, int8_t tz)
{
    civil_time expected_time = fillTimeStruct(expected_year, expected_mon, expected_day, expected_hour, expected_min, expected_sec, expected_tz);
    civil_time actual_time = UnixStamp::convertUnixToTime(unix, tz);
    TEST_ASSERT_EQUAL(expected_time.year, actual_time.year);
    TEST_ASSERT_EQUAL(expected_time.mon, actual_time.mon);
    TEST_ASSERT_EQUAL(expected_time.day, actual_time.day);
    TEST_ASSERT_EQUAL(expected_time.hour, actual_time.hour);
    TEST_ASSERT_EQUAL(expected_time.min, actual_time.min);
    TEST_ASSERT_EQUAL(expected_time.sec, actual_time.sec);
}

void test_conversion_to_unix_unix_left_border()
{
    verify_date_conversion_from_civil_to_epoch(EXPECTED_EPOCH_LEFT_BORDER, 1970, 1, 1, 0, 0, 0, 0);
}

void test_conversion_to_unix_unix_right_border()
{
    verify_date_conversion_from_civil_to_epoch(EXPECTED_EPOCH_RIGHT_BORDER, 2106, 2, 7, 6, 28, 15, 0);
}

void test_conversion_to_unix_chernobyl()
{
    verify_date_conversion_from_civil_to_epoch(EXPECETED_CHERNOBYL_TIMESTAMP, 1986, 4, 25, 21, 23, 45, 0);
}

void test_conversion_to_unix_calendar_era_end()
{
    verify_date_conversion_from_civil_to_epoch(EXPECTED_ERA_END, 2000, 2, 29, 23, 59, 59, 0);
}

void test_conversion_to_unix_calendar_era_start()
{
    verify_date_conversion_from_civil_to_epoch(EXPECTED_ERA_START, 2000, 3, 1, 0, 0, 0, 0);
}

void test_conversion_to_civil_unix_left_border()
{
    verify_date_conversion_from_epoch_to_civil(1970, 1, 1, 0, 0, 0, 0, EXPECTED_EPOCH_LEFT_BORDER, 0);
}

void test_conversion_to_civil_unix_right_border()
{
    verify_date_conversion_from_epoch_to_civil(2106, 2, 7, 6, 28, 15, 0, EXPECTED_EPOCH_RIGHT_BORDER, 0);
}

void test_conversion_to_civil_chernobyl()
{
    verify_date_conversion_from_epoch_to_civil(1986, 4, 25, 21, 23, 45, 0, EXPECETED_CHERNOBYL_TIMESTAMP, 0);
}

void test_conversion_to_civil_calendar_era_end()
{
    verify_date_conversion_from_epoch_to_civil(2000, 2, 29, 23, 59, 59, 0, EXPECTED_ERA_END, 0);
}

void test_conversion_to_civil_calendar_era_start()
{
    verify_date_conversion_from_epoch_to_civil(2000, 3, 1, 0, 0, 0, 0, EXPECTED_ERA_START, 0);
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_conversion_to_unix_unix_left_border);
    RUN_TEST(test_conversion_to_unix_unix_right_border);
    RUN_TEST(test_conversion_to_unix_chernobyl);
    RUN_TEST(test_conversion_to_unix_calendar_era_end);
    RUN_TEST(test_conversion_to_unix_calendar_era_start);

    RUN_TEST(test_conversion_to_civil_unix_left_border);
    RUN_TEST(test_conversion_to_civil_unix_right_border);
    RUN_TEST(test_conversion_to_civil_chernobyl);
    RUN_TEST(test_conversion_to_civil_calendar_era_end);
    RUN_TEST(test_conversion_to_civil_calendar_era_start);
    return UNITY_END();
}