/**
********************************************************************************
* @file     hal_systick_mock.cpp
* @author   M.Niaraki
* @date     07/21/2023
* @brief    Implements some mock functions for systick module
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include "hal_mock_fixture.h"

static U32
hal_systick_get_tick()
{
    HalUnitTests::HalTestFixture::m_tick++;
    HalUnitTests::HalTestFixture::m_mock->hal_systick_get_tick();
    return HalUnitTests::HalTestFixture::m_tick;
}

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
