/**
********************************************************************************
* @file     hal_cmsis_mock.cpp
* @author   M.Niaraki
* @date     11/03/2023
* @brief    Implements some mock functions for cmsis layer
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include "hal_mock_fixture.h"

static inline uint32_t
SysTick_Config(uint32_t ticks)
{
    return HalUnitTests::HalTestFixture::m_mock->SysTick_Config(ticks);
}

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
