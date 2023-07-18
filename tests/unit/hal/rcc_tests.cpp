#include <gtest/gtest.h>
#include "hal.h"

TEST(RccUnitTests, RccSimpleAssertions_1)
{
    // Expect to br true
    EXPECT_TRUE(1);

    // Expect to br false
    EXPECT_FALSE(0);

    hal_rcc_init(hal_rcc_cfg_get());
    // hal_rcc_test(1);
}
