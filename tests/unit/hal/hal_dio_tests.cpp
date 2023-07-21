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
#include "hal_dio_cfg.h"
#include "hll.h"

class HalDioTestFixture : public testing::Test
{
public:
    void SetUp(void) override
    {
        reset_registers();
    }
    void TearDown(void) override
    {
    }
    static void reset_registers()
    {
        memset((void *)gp_dio_regs[0], 0U, sizeof(GPIO_TypeDef));
        memset((void *)gp_dio_regs[1], 0U, sizeof(GPIO_TypeDef));
    }

protected:
};

TEST_F(HalDioTestFixture, HalDioWriteTestHigh)
{
    for (U8 index = (0U); index < DIO_MAX_CHANNEL_NUMBER; index++)
    {
        /* Arrange */
        U8            port_index = index / NUM_PIN_IN_PORT;
        U8            pin_index  = index % NUM_PIN_IN_PORT;
        U32           pin_mask   = (1UL << (pin_index));
        dio_channel_t channel    = (dio_channel_t)(index);

        /* Action */
        hal_dio_write(channel, DIO_HIGH);

        /* Assert */
        EXPECT_EQ(pin_mask, gp_dio_regs[port_index]->BSRR);

        /* Clean-up */
        reset_registers();
    }
}

TEST_F(HalDioTestFixture, HalDioWriteTestLow)
{
    for (U8 index = (0U); index < DIO_MAX_CHANNEL_NUMBER; index++)
    {
        /* Arrange */
        U8  port_index               = index / NUM_PIN_IN_PORT;
        U8  pin_index                = index % NUM_PIN_IN_PORT;
        U32 pin_mask                 = (1UL << (pin_index));
        gp_dio_regs[port_index]->BRR = (0UL);
        dio_channel_t channel        = (dio_channel_t)(index);

        /* Action */
        hal_dio_write(channel, DIO_LOW);

        /* Assert */
        EXPECT_EQ(pin_mask, gp_dio_regs[port_index]->BRR);
    }
}
/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
