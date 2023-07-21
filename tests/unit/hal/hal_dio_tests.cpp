/**
********************************************************************************
* @file     hal_rcc_tests.cpp
* @author   M.Niaraki
* @date     07/21/2023
* @brief    Unit tests for DIO module in the HAL
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include <gtest/gtest.h>
#include "hal.h"
#include "hll.h"

class HalDioTestFixture : public testing::Test
{
public:
    void SetUp(void) override
    {
        memset((void *)gp_dio_regs[0], 0U, sizeof(GPIO_TypeDef));
        memset((void *)gp_dio_regs[1], 0U, sizeof(GPIO_TypeDef));
    }
    void TearDown(void) override
    {
    }

protected:
};

TEST_F(HalDioTestFixture, HalDioTest)
{
    /* Arrange */

    /* Act */

    /* Assert */
    EXPECT_EQ(1, 1);
}

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
