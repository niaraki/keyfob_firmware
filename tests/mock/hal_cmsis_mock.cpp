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

static inline void
__NVIC_SetPriority(IRQn_Type IRQn, uint32_t priority)
{
    return HalUnitTests::HalTestFixture::m_mock->__NVIC_SetPriority(IRQn,
                                                                    priority);
}

static inline void
__NVIC_DisableIRQ(IRQn_Type IRQn)
{
    return HalUnitTests::HalTestFixture::m_mock->__NVIC_DisableIRQ(IRQn);
}

static inline void
__NVIC_EnableIRQ(IRQn_Type IRQn)
{
    return HalUnitTests::HalTestFixture::m_mock->__NVIC_EnableIRQ(IRQn);
}

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
