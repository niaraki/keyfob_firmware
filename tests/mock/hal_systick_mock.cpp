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

U32
hal_systick_get_tick()
{
    HalTestFixture::m_tick++;
    HalTestFixture::m_mock->hal_systick_get_tick();
    return HalTestFixture::m_tick;
}
/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
