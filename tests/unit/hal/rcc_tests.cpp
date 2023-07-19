#include <gtest/gtest.h>
#include "hal.h"
#include "hll.h"

TEST(RccUnitTests, RccSimpleAssertions_1)
{
    // Action
    hal_rcc_init(hal_rcc_cfg_get());

    // Expect to br true
    EXPECT_TRUE(1);

    // Expect to br false
    EXPECT_FALSE(0);

    std::cout << "CR :" << hll_rcc_regs->CR << std::endl;
    EXPECT_EQ(98, hll_rcc_regs->CR);
}
