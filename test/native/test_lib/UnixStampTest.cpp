#include <unity.h>
#include <UnixStamp.hpp>
#include <stdint.h>

void setUp(void) {}

void tearDown(void) {}

void test_conversion_to_unix()
{
    tm time;
    time.tm_year = 70;
    time.tm_mon = 0;
    time.tm_mday = 1;
    time.tm_hour = 0;
    time.tm_min = 0;
    time.tm_sec = 0;

    time_t unix = UnixStamp::convertTimeToUnix(time, 0);
    TEST_ASSERT_EQUAL(0, unix);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_conversion_to_unix);
    return UNITY_END();
}