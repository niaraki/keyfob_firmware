#include <gtest/gtest.h>

TEST(FirstUnitTests, SimpleAssertions_1)
{
    // Expect to br true
    EXPECT_TRUE(1);

    // Expect to br false
    EXPECT_FALSE(0);
}

TEST(FirstUnitTests, SimpleAssertions_2)
{
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");

    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}
