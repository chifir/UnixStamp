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

void verify_date_conversion_from_civil_to_epoch(uint32_t expected_unix, uint16_t year, uint8_t mon, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec, int8_t tz)
{
    civil_time time{sec, min, hour, day, mon, year};
    unixstamp unix = UnixStamp::convertTimeToUnix(time, tz);
    TEST_ASSERT_EQUAL(expected_unix, unix);
}

void verify_date(civil_time expected, civil_time actual)
{
    TEST_ASSERT_EQUAL(expected.year, actual.year);
    TEST_ASSERT_EQUAL(expected.mon, actual.mon);
    TEST_ASSERT_EQUAL(expected.day, actual.day);
    TEST_ASSERT_EQUAL(expected.hour, actual.hour);
    TEST_ASSERT_EQUAL(expected.min, actual.min);
    TEST_ASSERT_EQUAL(expected.sec, actual.sec);
}

void verify_date_conversion_from_epoch_to_civil(uint16_t expected_year, uint8_t expected_mon, uint8_t expected_day, uint8_t expected_hour, uint8_t expected_min, uint8_t expected_sec, uint32_t unix, int8_t tz)
{
    civil_time expected_time{expected_sec, expected_min, expected_hour, expected_day, expected_mon, expected_year};
    civil_time actual_time = UnixStamp::convertUnixToTime(unix, tz);
    verify_date(expected_time, actual_time);
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
    verify_date_conversion_from_epoch_to_civil(1970, 1, 1, 0, 0, 0, EXPECTED_EPOCH_LEFT_BORDER, 0);
}

void test_conversion_to_civil_unix_right_border()
{
    verify_date_conversion_from_epoch_to_civil(2106, 2, 7, 6, 28, 15, EXPECTED_EPOCH_RIGHT_BORDER, 0);
}

void test_conversion_to_civil_chernobyl()
{
    verify_date_conversion_from_epoch_to_civil(1986, 4, 25, 21, 23, 45, EXPECETED_CHERNOBYL_TIMESTAMP, 0);
}

void test_conversion_to_civil_calendar_era_end()
{
    verify_date_conversion_from_epoch_to_civil(2000, 2, 29, 23, 59, 59, EXPECTED_ERA_END, 0);
}

void test_conversion_to_civil_calendar_era_start()
{
    verify_date_conversion_from_epoch_to_civil(2000, 3, 1, 0, 0, 0, EXPECTED_ERA_START, 0);
}

void test_unix_stamp_object_from_unix_date()
{
    civil_time expected_date{45, 23, 21, 25, 4, 1986};
    UnixStamp unixStamp(EXPECETED_CHERNOBYL_TIMESTAMP);
    verify_date(expected_date, unixStamp.getTimeInTz(0));
}

void test_unix_stamp_object_from_unix_in_gmt()
{
    UnixStamp unixStamp(EXPECETED_CHERNOBYL_TIMESTAMP);
    TEST_ASSERT_EQUAL(EXPECETED_CHERNOBYL_TIMESTAMP, unixStamp.getUnix());
}

void test_unix_stamp_object_from_civil_unix()
{
    civil_time time{45, 23, 21, 25, 4, 1986};
    UnixStamp unixStamp(time);
    TEST_ASSERT_EQUAL(EXPECETED_CHERNOBYL_TIMESTAMP, unixStamp.getUnix());
}

void test_unix_stamp_object_from_civil_date_in_gmt()
{
    civil_time time{45, 23, 21, 25, 4, 1986};
    UnixStamp unixStamp(time);
    verify_date(time, unixStamp.getTimeInTz(0));
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_unix_stamp_object_from_unix_date);
    RUN_TEST(test_unix_stamp_object_from_unix_in_gmt);
    RUN_TEST(test_unix_stamp_object_from_civil_unix);
    RUN_TEST(test_unix_stamp_object_from_civil_date_in_gmt);

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