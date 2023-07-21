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

TEST_F(HalDioTestFixture, HalDioToggleTest)
{
    for (U8 index = (0U); index < DIO_MAX_CHANNEL_NUMBER; index++)
    {
        /* Arrange */
        U8            port_index    = index / NUM_PIN_IN_PORT;
        U8            pin_index     = index % NUM_PIN_IN_PORT;
        U32           pin_mask      = (1UL << (pin_index));
        U32           expected_bsrr = pin_mask;
        dio_channel_t channel       = (dio_channel_t)(index);
        /*Set ODR to 0xAAAAAAAAUL (even bits are one)*/
        gp_dio_regs[port_index]->ODR = (0xAAAAAAAAUL);
        if (index % (2U) != (0U))
        {
            /*When the index is odd, means we want to toggle from 1 -> 0
             * So, we should shift the pin_mask to second part of the BSRR
             * BSRR[31:16] are used to reset bits, page:137 of STM32f030f4 user
             * manual*/
            expected_bsrr = (pin_mask << NUM_PIN_IN_PORT);
        }

        /* Action */
        hal_dio_toggle(channel);

        /* Assert */
        EXPECT_EQ(expected_bsrr, gp_dio_regs[port_index]->BSRR);

        /* Clean-up */
        reset_registers();
    }
}
/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
