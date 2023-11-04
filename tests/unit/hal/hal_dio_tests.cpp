/**
********************************************************************************
* @file     hal_dio_tests.cpp
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

/*Include CUT source files*/
#include "hal_dio.c"

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

TEST_F(HalDioTestFixture, HalDioWrite_With_HighValue_Test)
{
    for (U8 index = (0U); index < NUM_PINS; index++)
    {
        /* Arrange */
        U8    port_index = index / NUM_PIN_IN_PORT;
        U8    pin_index  = index % NUM_PIN_IN_PORT;
        U32   pin_mask   = (1UL << (pin_index));
        pin_t channel    = (pin_t)(index);

        /* Action */
        hal_dio_write(channel, DIO_STATE_HIGH);

        /* Assert */
        EXPECT_EQ(pin_mask, gp_dio_regs[port_index]->BSRR);

        /* Clean-up */
        reset_registers();
    }
}

TEST_F(HalDioTestFixture, HalDioWrite_With_LowValue_Test)
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
        hal_dio_write(channel, DIO_STATE_LOW);

        /* Assert */
        EXPECT_EQ(pin_mask, gp_dio_regs[port_index]->BRR);
    }
}

TEST_F(HalDioTestFixture, HalDioToggle_Test)
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
        dio_state_t expected_state
            = (index % 2 == 0U) ? DIO_STATE_LOW : DIO_STATE_HIGH;

        /* Action */
        dio_state_t state = hal_dio_read(channel);

        /* Assert */
        EXPECT_EQ(expected_state, state);
    }
}

/** @brief The following loop defines pin configuration for each pin of the dio
 * unit and sets the mode register as bellow: first pin: DIO_MODE_INPUT, second
 * pin: OUTPUT, third pin: AF, fourth pin: DIO_MODE_ANALOG, fifth bit: like the
 * first bit and so on. So, the mode register for first four pins would be:
 * 0b11100100 = 0xE4
 *  */
TEST_F(HalDioTestFixture, HalDioInit_SetModeRegister_Test)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index       = 0;
    U32          expected_moder  = 0xE4E4E4E4UL;
    U32          expected_otyper = 0x4444UL;

    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].mode  = DIO_MODE_INPUT;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].mode  = DIO_MODE_OUTPUT_PP;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].mode  = DIO_MODE_AF_OD;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].mode  = DIO_MODE_ANALOG;
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < NUM_PORTS; port_index++)
    {
        EXPECT_EQ(expected_moder, gp_dio_regs[port_index]->MODER);
        EXPECT_EQ(expected_otyper, gp_dio_regs[port_index]->OTYPER);
    }
}

/** @brief set speed profile for the first four pins are configured like this:
 * 0b00 11 01 00 = 0x34 by repeating this pattern for other four-grouped pins,
 * we expect to have 0x34343434UL in the target register */
TEST_F(HalDioTestFixture, HalDioInit_SetSpeedRegister_Test)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index        = 0;
    U32          expected_ospeedr = 0x34343434UL;

    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].speed = DIO_SPEED_SLOW;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].speed = DIO_SPEED_MEDIUM;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].speed = DIO_SPEED_FAST;
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].speed = DIO_SPEED_SLOW;
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < NUM_PORTS; port_index++)
        EXPECT_EQ(expected_ospeedr, gp_dio_regs[port_index]->OSPEEDR);
}

TEST_F(HalDioTestFixture, HalDioInit_SetResistorRegister_Test)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index      = 0;
    U32          expected_pupdr = 0x89898989UL;

    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel    = (pin_t)pin_index;
        test_configs[pin_index++].resistor = DIO_RES_PULLUP;
        test_configs[pin_index].channel    = (pin_t)pin_index;
        test_configs[pin_index++].resistor = DIO_RES_PULLDOWN;
        test_configs[pin_index].channel    = (pin_t)pin_index;
        test_configs[pin_index++].resistor = DIO_RES_DISABLE;
        test_configs[pin_index].channel    = (pin_t)pin_index;
        test_configs[pin_index++].resistor = DIO_RES_PULLDOWN;
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < NUM_PORTS; port_index++)
        EXPECT_EQ(expected_pupdr, gp_dio_regs[port_index]->PUPDR);
}

TEST_F(HalDioTestFixture, HalDioInit_SetDefaultState_Test)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index     = 0U;
    U32          expected_bsrr = 0x5555UL;
    U32          expected_brr  = 0xAAAAUL;

    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel         = (pin_t)pin_index;
        test_configs[pin_index++].default_state = DIO_STATE_HIGH;
        test_configs[pin_index].channel         = (pin_t)pin_index;
        test_configs[pin_index++].default_state = DIO_STATE_LOW;
        test_configs[pin_index].channel         = (pin_t)pin_index;
        test_configs[pin_index++].default_state = DIO_STATE_HIGH;
        test_configs[pin_index].channel         = (pin_t)pin_index;
        test_configs[pin_index++].default_state = DIO_STATE_LOW;
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < NUM_PORTS; port_index++)
    {
        EXPECT_EQ(expected_bsrr, gp_dio_regs[port_index]->BSRR);
        EXPECT_EQ(expected_brr, gp_dio_regs[port_index]->BRR);
    }
}

/** @brief Sets AF from 0 to 7 for each 8-grouped of pins
 * So, the target registers are expected to be 0x76543210UL */
TEST_F(HalDioTestFixture, HalDioInit_SetAF_Test)
{
    /* Arrange */
    dio_config_t test_configs[NUM_PINS];
    U16          pin_index    = 0U;
    U32          expected_afr = (0x76543210UL);

    while (pin_index < NUM_PINS)
    {
        test_configs[pin_index].channel = (pin_t)pin_index;
        test_configs[pin_index++].af    = (dio_af_t)(pin_index % 8U);
    }

    /* Action */
    hal_dio_init((const dio_config_t *)test_configs, NUM_PINS);

    /* Assert */
    for (U8 port_index = 0U; port_index < NUM_PORTS; port_index++)
    {
        EXPECT_EQ(expected_afr, gp_dio_regs[port_index]->AFR[0]);
        EXPECT_EQ(expected_afr, gp_dio_regs[port_index]->AFR[1]);
    }
}

TEST_F(HalDioTestFixture, HalDioReadWriteFromPort_Test)
{
    /* Arrange */
    U32 write_value = (0xAAAAAAAAUL);

    /* Action */
    for (U8 index = 0; index < NUM_PORTS; index++)
    {
        hal_dio_write_port((port_t)index, write_value);

        /* Assert */
        EXPECT_EQ(write_value, hal_dio_read_port((port_t)index));
    }
}

TEST_F(HalDioTestFixture, HalDioMultiConfig_Test)
{
    /* Arrange */
    dio_config_t pin_config1 = { .channel       = PA0,
                                 .mode          = DIO_MODE_INPUT,
                                 .af            = DIO_AF_1,
                                 .resistor      = DIO_RES_PULLDOWN,
                                 .default_state = DIO_STATE_LOW,
                                 .speed         = DIO_SPEED_SLOW };

    dio_config_t pin_config2 = { .channel       = PA0,
                                 .mode          = DIO_MODE_OUTPUT_OD,
                                 .af            = DIO_AF_0,
                                 .resistor      = DIO_RES_PULLUP,
                                 .default_state = DIO_STATE_HIGH,
                                 .speed         = DIO_SPEED_FAST };
    /* Action */
    /** config with an old settings */
    hal_dio_config(&pin_config1);
    /** reconfigure with new settings */
    hal_dio_config(&pin_config2);

    /* Assert: check new config for selected pin */
    EXPECT_EQ(1, gp_dio_regs[PORTA]->BSRR);
    EXPECT_EQ(1, gp_dio_regs[PORTA]->MODER);
    EXPECT_EQ(0, gp_dio_regs[PORTA]->AFR[0]);
    EXPECT_EQ(1, gp_dio_regs[PORTA]->PUPDR);
    EXPECT_EQ(3, gp_dio_regs[PORTA]->OSPEEDR);
}

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
