/**
********************************************************************************
* @file     template.h
* @author   M.Niaraki
* @date     07/21/2023
* @brief    Mocking fixture for HAL functions
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_MOCK_FIXTUREH
#define __HAL_MOCK_FIXTUREH

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "hal.h"
#include "hal_common_defines.h"

namespace HalUnitTests {
class HalMock
{
public:
    HalMock()
    {
    }
    virtual ~HalMock()
    {
    }
    /*hal_systick module*/
    MOCK_METHOD((U32), hal_systick_get_tick, ());

    /*CMSIS related funtions or macros*/
    MOCK_METHOD((U32), SysTick_Config, (U32));
};

class HalTestFixture : public testing::Test
{
public:
    HalTestFixture()
    {
        m_mock.reset(new ::testing::NiceMock<HalMock>());
    }
    virtual ~HalTestFixture()
    {
        m_mock.reset();
    }
    void SetUp(void) override
    {
    }
    void TearDown(void) override
    {
    }
    inline static std::unique_ptr<HalMock> m_mock;
    inline static U32                      m_tick;
};
}
#endif /* __HAL_MOCK_FIXTUREH */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
