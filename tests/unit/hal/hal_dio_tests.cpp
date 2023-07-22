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
#include <cmath>
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
        reset_registers();
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
    for (U8 index = (0U); index < NUM_PINS; index++)
    {
        /* Arrange */
        U8    port_index = index / NUM_PIN_IN_PORT;
        U8    pin_index  = index % NUM_PIN_IN_PORT;
        U32   pin_mask   = (1UL << (pin_index));
        pin_t channel    = (pin_t)(index);

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
    for (U8 index = (0U); index < NUM_PINS; index++)
    {
        /* Arrange */
        U8  port_index               = index / NUM_PIN_IN_PORT;
        U8  pin_index                = index % NUM_PIN_IN_PORT;
        U32 pin_mask                 = (1UL << (pin_index));
        gp_dio_regs[port_index]->BRR = (0UL);
        pin_t channel                = (pin_t)(index);

        /* Action */
        hal_dio_write(channel, DIO_LOW);

        /* Assert */
        EXPECT_EQ(pin_mask, gp_dio_regs[port_index]->BRR);
    }
}

TEST_F(HalDioTestFixture, HalDioToggleTest)
{
    for (U8 index = (0U); index < NUM_PINS; index++)
    {
        /* Arrange */
        U8    port_index    = index / NUM_PIN_IN_PORT;
        U8    pin_index     = index % NUM_PIN_IN_PORT;
        U32   pin_mask      = (1UL << (pin_index));
        U32   expected_bsrr = pin_mask;
        pin_t channel       = (pin_t)(index);
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

TEST_F(HalDioTestFixture, HalDioReadTest)
{
    for (U8 index = (0U); index < NUM_PINS; index++)
    {
        /* Arrange */
        U8    port_index             = index / NUM_PIN_IN_PORT;
        U8    pin_index              = index % NUM_PIN_IN_PORT;
        U32   pin_mask               = (1UL << (pin_index));
        pin_t channel                = (pin_t)(index);
        gp_dio_regs[port_index]->IDR = (0xAAAAUL);
        dio_state_t expected_state   = (index % 2 == 0U) ? DIO_LOW : DIO_HIGH;

        /* Action */
        dio_state_t state = hal_dio_read(channel);

        /* Assert */
        EXPECT_EQ(expected_state, state);
    }
}

TEST_F(HalDioTestFixture, HalDioInit_ModeRegisterTest)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index = 0;
    /*The following loop defines pin configuration for each pin of the dio unit
     * and sets the mode register as bellow:
     * first pin: INPUT, second pin: OUTPUT, third pin: AF, fourth pin: ANALOG,
     * fifth bit: like the first bit and so on.
     * So, the mode register for first four pins would be: 0b11100100 = 0xE4
     *  */
    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].mode  = INPUT;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].mode  = OUTPUT_PP;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].mode  = AF_OD;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].mode  = ANALOG;
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < (NUM_PINS / NUM_PIN_IN_PORT);
         port_index++)
    {
        EXPECT_EQ(0xE4E4E4E4UL, gp_dio_regs[port_index]->MODER);
        EXPECT_EQ(0x4444UL, gp_dio_regs[port_index]->OTYPER);
    }
}

TEST_F(HalDioTestFixture, HalDioInit_SpeedRegisterTest)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index = 0;
    /*set speed profile for the first four pins are configured like this: 0b00
     * 11 01 00 = 0x34 by repeating this pattern for other four-grouped pins, we
     * expect to have 0x34343434UL in the target register */
    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].speed = SLOW;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].speed = MEDIUM;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].speed = FAST;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].speed = SLOW;
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < (NUM_PINS / NUM_PIN_IN_PORT);
         port_index++)
    {
        EXPECT_EQ(0x34343434UL, gp_dio_regs[port_index]->OSPEEDR);
    }
}

TEST_F(HalDioTestFixture, HalDioInit_ResistorRegisterTest)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index = 0;
    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel    = (pin_t)pin_index;
        test_configs[pin_index++].resistor = PULLUP;
        test_configs[pin_index].channel    = (pin_t)pin_index;
        test_configs[pin_index++].resistor = PULLDOWN;
        test_configs[pin_index].channel    = (pin_t)pin_index;
        test_configs[pin_index++].resistor = RES_DISABLE;
        test_configs[pin_index].channel    = (pin_t)pin_index;
        test_configs[pin_index++].resistor = PULLDOWN;
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < (NUM_PINS / NUM_PIN_IN_PORT);
         port_index++)
    {
        EXPECT_EQ(0x89898989UL, gp_dio_regs[port_index]->PUPDR);
    }
}
TEST_F(HalDioTestFixture, HalDioInit_DefaultStateTest)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index = 0U;
    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel         = (pin_t)pin_index;
        test_configs[pin_index++].default_state = DIO_HIGH;
        test_configs[pin_index].channel         = (pin_t)pin_index;
        test_configs[pin_index++].default_state = DIO_LOW;
        test_configs[pin_index].channel         = (pin_t)pin_index;
        test_configs[pin_index++].default_state = DIO_HIGH;
        test_configs[pin_index].channel         = (pin_t)pin_index;
        test_configs[pin_index++].default_state = DIO_LOW;
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < (NUM_PINS / NUM_PIN_IN_PORT);
         port_index++)
    {
        EXPECT_EQ(0x5555UL, gp_dio_regs[port_index]->BSRR);
        EXPECT_EQ(0xAAAAUL, gp_dio_regs[port_index]->BRR);
    }
}

TEST_F(HalDioTestFixture, HalDioInit_AFTest)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index   = 0U;
    U32          expectedAFR = (0x76543210UL);

    /*Sets AF from 0 to 7 for each 8-group of pins
     * So, the target registers expected to be 0x76543210UL*/
    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].af    = (dio_af_t)(pin_index % 8U);
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < (NUM_PINS / NUM_PIN_IN_PORT);
         port_index++)
    {
        EXPECT_EQ(expectedAFR, gp_dio_regs[port_index]->AFR[0]);
        EXPECT_EQ(expectedAFR, gp_dio_regs[port_index]->AFR[1]);
    }
}
/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
