#include "unity.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void test_sanity(void)
{
    TEST_ASSERT_TRUE(1);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sanity);
    return UNITY_END();
}