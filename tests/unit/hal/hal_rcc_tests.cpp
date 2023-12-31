/**
********************************************************************************
* @file     hal_rcc_tests.cpp
* @author   M.Niaraki
* @date     07/18/2023
* @brief    Unit tests for RCC module in the HAL
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include <gtest/gtest.h>

/*Include CUT soruce files*/
#include "hal_common_helper.c"
#include "hal_rcc.c"

class HalRccTestFixture : public testing::Test
{
public:
    void SetUp(void) override
    {
        memset((void *)gp_rcc_regs, 0, sizeof(RCC_TypeDef));
    }
    void TearDown(void) override
    {
        memset((void *)gp_rcc_regs, 0, sizeof(RCC_TypeDef));
    }

protected:
    const rcc_peri_t rcc_peri_table[RCC_PERI_COUNT] = {
        /* BUS Type | Bit index for Clock Control | Default Clock state */
        { RCC_BUS_AHB, RCC_AHBENR_GPIOAEN_Pos, RCC_CLK_ON },        /* GPIOA*/
        { RCC_BUS_AHB, RCC_AHBENR_GPIOBEN_Pos, RCC_CLK_ON },        /* GPIOB*/
        { RCC_BUS_APB2, RCC_APB2ENR_DBGMCUEN_Pos, RCC_CLK_ON },     /* DEBUG*/
        { RCC_BUS_APB2, RCC_APB2ENR_SYSCFGCOMPEN_Pos, RCC_CLK_ON }, /* SYSCFG*/
        { RCC_BUS_APB2, RCC_APB2ENR_TIM17EN_Pos, RCC_CLK_ON },      /* TIM17*/
    };
    const rcc_config_t rcc_config_table[1]
        /* HIGH Freq. Source | LOW Freq. Source | Peripheral Table	*/
        = { { RCC_HCLK_PLL, RCC_LCLK_LSI, rcc_peri_table } };
};

TEST_F(HalRccTestFixture, HalRccCRTest)
{
    /* Arrange */
    U32 expected_CR = (1 << 16) | (1 << 24); /* HSEON(16):1 PLLON(24):24 */

    /* Act */
    hal_rcc_init(rcc_config_table);

    /* Assert */
    EXPECT_EQ(expected_CR, gp_rcc_regs->CR);
}

TEST_F(HalRccTestFixture, HalRccCSRTest)
{
    U32 expected_CSR = (1 << 0); /* LSION(0):1 */
    hal_rcc_init(rcc_config_table);
    EXPECT_EQ(expected_CSR, gp_rcc_regs->CSR);
}

TEST_F(HalRccTestFixture, HalRccAPB1Test)
{
    U32 expected_APB1 = 0;
    hal_rcc_init(rcc_config_table);
    EXPECT_EQ(expected_APB1, gp_rcc_regs->APB1ENR);
}

TEST_F(HalRccTestFixture, HalRccAPB2Test)
{
    U32 expected_APB2 = (1 << 22) | (1 << 0) | (1 << 18);
    hal_rcc_init(rcc_config_table);
    EXPECT_EQ(expected_APB2, gp_rcc_regs->APB2ENR);
}

TEST_F(HalRccTestFixture, HalRccAHBTest)
{
    /* DEBUGMCUEN(22):1 SYSCFG(0):1 TIM17(18):1 */
    U32 expected_AHB = (1 << 17) | (1 << 18); /* GPIOAEN(17):1 GPIOBEN(18):1 */
    hal_rcc_init(rcc_config_table);
    EXPECT_EQ(expected_AHB, gp_rcc_regs->AHBENR);
}

TEST_F(HalRccTestFixture, HalRccCheckSystemClock)
{
    I8 result                     = -1;
    IsWrongSystemCoreClockEnabled = false;
    result                        = hal_rcc_check_system_clock();
    EXPECT_EQ(0U, result);
    /* check faulty situation */
    IsWrongSystemCoreClockEnabled = true;
    result                        = hal_rcc_check_system_clock();
    EXPECT_EQ(-EFAULT, result);
}

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
