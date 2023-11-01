/**
********************************************************************************
* @file     hal_delay_tests.cpp
* @author   M.Niaraki
* @date     07/20/2023
* @brief    Unit tests for the HAL Delay
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include "hal_systick_mock.cpp"

class HalDelayTestFixture : public HalTestFixture
{
public:
    void SetUp(void) override
    {
    }
    void TearDown(void) override
    {
    }
};

TEST_F(HalDelayTestFixture, HalDelayTest)
{
    /* Arrange */
    U32 delay_ms       = 501UL;
    U8  over_execution = 2U;
    EXPECT_CALL(*m_mock, hal_systick_get_tick())
        .Times(delay_ms + over_execution);

    /* Act */
    hal_delay(delay_ms);

    /* Assert */
    EXPECT_EQ(delay_ms, m_tick - over_execution);
}

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
