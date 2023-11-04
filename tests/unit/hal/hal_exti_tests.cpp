/**
********************************************************************************
* @file     hal_exti_tests.cpp
* @author   M.Niaraki
* @date     11/04/2023
* @brief    Unit tests for EXTI module in the HAL
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include <cmath>
#include <gtest/gtest.h>

/*Include mock objects */
#include "hal_cmsis_mock.cpp"

/*Include CUT source files*/
#include "hal_exti.c"

class HalExtiTestFixture : public HalUnitTests::HalTestFixture
{
public:
    void SetUp(void) override
    {
        callback_call_count = 0;
    }
    void TearDown(void) override
    {
    }

    static void test_exti_callback(void);

protected:
    static inline U8 callback_call_count = 0;
};

void
HalExtiTestFixture::test_exti_callback(void)
{
    callback_call_count++;
}

TEST_F(HalExtiTestFixture, HalExtiInit_NormalOperation)
{
    constexpr U8        scount                    = 4;
    const exti_config_t exti_config_table[scount] = {
        { EXTI_CHANNEL_0,
          PORTA,
          EXTI_MODE_FALLING_EDGE,
          EXTI_PRIORITY_HIGHEST },
        { EXTI_CHANNEL_1, PORTB, EXTI_MODE_RISING_EDGE, EXTI_PRIORITY_LOW },
        { EXTI_CHANNEL_4, PORTB, EXTI_MODE_BOTH_EDGE, EXTI_PRIORITY_NORMAL },
        { EXTI_CHANNEL_15, PORTA, EXTI_MODE_BOTH_EDGE, EXTI_PRIORITY_HIGH },
    };
    EXPECT_CALL(*m_mock, __NVIC_SetPriority(testing::_, testing::_))
        .Times(scount);
    I8 result = hal_exti_init(exti_config_table, scount);
    EXPECT_EQ(0, result);
    /*check register values */
}

TEST_F(HalExtiTestFixture, HalExtiInit_FailOperation)
{
    const exti_config_t exti_config_table[1] = {
        { EXTI_CHANNEL_15,
          NUM_PORTS,
          EXTI_MODE_BOTH_EDGE,
          EXTI_PRIORITY_COUNT },
    };
    EXPECT_CALL(*m_mock, __NVIC_SetPriority(testing::_, testing::_)).Times(0);
    I8 result = hal_exti_init(exti_config_table, 1);
    EXPECT_EQ(-EFAULT, result);
}

void
callback(void)
{
    HalExtiTestFixture::test_exti_callback();
}

TEST_F(HalExtiTestFixture, HalExtiRegisterCallback_ch0)
{
    constexpr U8 chIndex = 0;
    hal_exti_register_callback(EXTI_CHANNEL_0, callback);
    gp_exti_regs->PR = (1U << chIndex);
    hal_exti0_1_irq_handler();
    EXPECT_EQ(1, callback_call_count);
}

TEST_F(HalExtiTestFixture, HalExtiRegisterCallback_ch1)
{
    constexpr U8 chIndex = 1;
    hal_exti_register_callback(EXTI_CHANNEL_1, callback);
    gp_exti_regs->PR = (1U << chIndex);
    hal_exti0_1_irq_handler();
    EXPECT_EQ(1, callback_call_count);
}

TEST_F(HalExtiTestFixture, HalExtiRegisterCallback_ch2)
{
    constexpr U8 chIndex = 2;
    hal_exti_register_callback(EXTI_CHANNEL_2, callback);
    gp_exti_regs->PR = (1U << chIndex);
    hal_exti2_3_irq_handler();
    EXPECT_EQ(1, callback_call_count);
}

TEST_F(HalExtiTestFixture, HalExtiRegisterCallback_ch3)
{
    constexpr U8 chIndex = 3;
    hal_exti_register_callback(EXTI_CHANNEL_3, callback);
    gp_exti_regs->PR = (1U << chIndex);
    hal_exti2_3_irq_handler();
    EXPECT_EQ(1, callback_call_count);
}

TEST_F(HalExtiTestFixture, HalExtiRegisterCallback_ch4)
{
    constexpr U8 chIndex = 4;
    hal_exti_register_callback(EXTI_CHANNEL_4, callback);
    gp_exti_regs->PR = (1U << chIndex);
    hal_exti4_15_irq_handler();
    EXPECT_EQ(1, callback_call_count);
}

TEST_F(HalExtiTestFixture, HalExtiRegisterCallback_ch15)
{
    constexpr U8 chIndex = 15;
    hal_exti_register_callback(EXTI_CHANNEL_15, callback);
    gp_exti_regs->PR = (1U << chIndex);
    hal_exti4_15_irq_handler();
    EXPECT_EQ(1, callback_call_count);
}
/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
