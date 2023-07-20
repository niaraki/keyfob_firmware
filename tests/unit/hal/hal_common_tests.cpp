/**
********************************************************************************
* @file     hal_common_tests.cpp
* @author   M.Niaraki
* @date     07/19/2023
* @brief    Implements unit tests required for common part of the HAL
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/

#include "gtest/gtest.h"
#include <vector>
#include <tuple>
#include <iostream>
#include "hal.h"
#include "hal_common_defines.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup COMMON COMMON
 *   @brief This module contains the shared stuff between different HAL modules
 *    @{
 */
class HalCommonFixture
    : public testing::TestWithParam<std::tuple<U32, U32, U32, U32, U32, U8>>
{
};

/**
 * @brief This parametarized test is used to test all bit-related functions in
 * the common part of the HAL layer
 * @attention Each Unit test should be implemented isolated for each module, but
 * in this case, there are a lot of different inputs. So, I have decided to
 * implement like this to avoid redundancy in the test suite.
 */
TEST_P(HalCommonFixture, TestHalBitManipulationFunctions)
{
    /* Arange */
    std::tuple<U32, U32, U32, U32, U32, U8> tuple = GetParam();
    U32 expected_set_result                       = std::get<0>(tuple);
    U32 expected_clear_result                     = std::get<1>(tuple);
    U32 expected_toggle_result                    = std::get<2>(tuple);
    U32 expected_get_result                       = std::get<3>(tuple);
    U32 initial_register_value                    = std::get<4>(tuple);
    U8  bit_index                                 = std::get<5>(tuple);

    /* fake registers for each operation*/
    _IO U32 reg_set              = initial_register_value;
    _IO U32 reg_clear            = initial_register_value;
    _IO U32 reg_toggle           = initial_register_value;
    _IO U32 reg_get              = initial_register_value;
    REG     fake_set_register    = &reg_set;
    REG     fake_clear_register  = &reg_clear;
    REG     fake_toggle_register = &reg_toggle;
    REG     fake_get_register    = &reg_get;

    /* Act */
    hal_set_bit(fake_set_register, bit_index);
    hal_clear_bit(fake_clear_register, bit_index);
    hal_toggle_bit(fake_toggle_register, bit_index);
    U8 get_result = hal_read_bit(fake_get_register, bit_index);

    /* Assert */
    EXPECT_EQ(expected_set_result, *fake_set_register);
    EXPECT_EQ(expected_clear_result, *fake_clear_register);
    EXPECT_EQ(expected_toggle_result, *fake_toggle_register);
    EXPECT_EQ(expected_get_result, get_result);
}
INSTANTIATE_TEST_CASE_P(
    HalBitManipulationSpecificTests,
    HalCommonFixture,
    /*tuple: U32:set, U32:clear, U32:toggle, U8:get,
       U32:default register, U8:bit index*/
    testing::Values(
        std::make_tuple(0xAABAAAAA, 0xAAAAAAAA, 0xAABAAAAA, 0, 0xAAAAAAAA, 20),
        std::make_tuple(0xAAAAEAAA, 0xAAAAAAAA, 0xAAAAEAAA, 0, 0xAAAAAAAA, 14),
        std::make_tuple(0xAAAAAAAA, 0xA8AAAAAA, 0xA8AAAAAA, 1, 0xAAAAAAAA, 25),
        std::make_tuple(0xAAAAAAAA, 0xAAAAAAA2, 0xAAAAAAA2, 1, 0xAAAAAAAA, 3)));

TEST(HalCommonUnitTests, HalSetBit)
{
    _IO U32 reg      = 0;
    U32     expected = 0;
    for (U8 index = 0; index <= MAX_BIT_INDEX; index++)
    {
        /*Arange*/
        reg      = 0;
        expected = (U32)(1 << index);

        /*Act*/
        hal_set_bit(&reg, index);

        /*Assert*/
        EXPECT_EQ(expected, reg);
    }
}

TEST(HalCommonUnitTests, HalClearBit)
{
    _IO U32 reg      = 0xFFFFFFFF;
    U32     expected = 0;
    for (U8 index = 0; index <= MAX_BIT_INDEX; index++)
    {
        /*Arange*/
        reg      = 0xFFFFFFFF;
        expected = reg ^ (U32)(1 << index);

        /*Act*/
        hal_clear_bit(&reg, index);

        /*Assert*/
        EXPECT_EQ(expected, reg);
    }
}

TEST(HalCommonUnitTests, HalToggleAndReadBit)
{
    _IO U32 reg             = 0xAAAAAAAA;
    U32     toggle_expected = 0;
    U8      read_expected   = 0;

    for (U8 index = 0; index <= MAX_BIT_INDEX; index++)
    {
        /*Arange*/
        reg             = 0xAAAAAAAA; /*Even bits are zero, Odd bits are one*/
        toggle_expected = reg;
        read_expected   = (index % 2 == 0) ? 0 : 1;

        if (read_expected == 0)
            toggle_expected |= (1 << index);
        else
            toggle_expected &= ~((U32)(1 << index));

        /*Act*/
        U8 bit_value = hal_read_bit(&reg, index);
        hal_toggle_bit(&reg, index);

        /*Assert*/
        EXPECT_EQ(toggle_expected, reg);
        EXPECT_EQ(read_expected, bit_value);
    }
}

TEST(HalCommonUnitTests, HalSetMask)
{
    _IO U32 reg = 0xAAAAAAAA;
    hal_set_mask(&reg, 0x55555555);
    EXPECT_EQ(0xFFFFFFFF, reg);
}

TEST(HalCommonUnitTests, HalClearMask)
{
    _IO U32 reg = 0xAAAAAAAA;
    hal_clear_mask(&reg, 0xAAAAAAAA);
    EXPECT_EQ(0, reg);
}
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
