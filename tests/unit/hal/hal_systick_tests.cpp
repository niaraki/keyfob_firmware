/**
********************************************************************************
* @file     hal_rcc_tests.cpp
* @author   M.Niaraki
* @date     11/01/2023
* @brief    Unit tests for Systick module in the HAL
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include <stdint.h>
#include <stdio.h>
#include <gtest/gtest.h>

/*Include Mocks of dependencies*/
#include "hal_cmsis_mock.cpp"

/*Include CUT source files*/
#include "hal_systick.c"

namespace HalSystickUnitTests {
class HalSystickTestFixture : public HalUnitTests::HalTestFixture
{
public:
    void SetUp(void) override
    {
        IsWrongSystemCoreClockEnabled = FALSE;
        hal_systick_unittest_set_tick(random_tick_value);
    }
    void TearDown(void) override
    {
    }

protected:
    U32 random_tick_value = 12345U;
};

TEST_F(HalSystickTestFixture, HalSystickInit_NormalOperationTest)
{
    EXPECT_CALL(*m_mock, SysTick_Config(testing::_))
        .WillOnce(testing::Return(0U));
    EXPECT_EQ(0U, hal_systick_init());
}

TEST_F(HalSystickTestFixture, HalSystickInit_FailureOnLowLayerTest)
{
    EXPECT_CALL(*m_mock, SysTick_Config(testing::_))
        .WillOnce(testing::Return(1U));
    EXPECT_EQ(-EFAULT, hal_systick_init());
}

TEST_F(HalSystickTestFixture, HalSystickIncTick)
{
    hal_systick_inc_tick();
    EXPECT_EQ(random_tick_value + 1U, hal_systick_get_tick());
}

TEST_F(HalSystickTestFixture, HalSystickGetTick)
{
    EXPECT_EQ(random_tick_value, hal_systick_get_tick());
}

}
/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
