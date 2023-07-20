/**
********************************************************************************
* @file     HLL.h
* @author   M.Niaraki
* @date     07/19/2023
* @brief    FAKE Hardware Low Layer
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HLL_H
#define __HLL_H

#include "stm32f0xx.h"

#ifdef __cplusplus
extern "C"
{
#endif

    extern volatile RCC_TypeDef *const gp_rcc_regs;
    extern volatile PWR_TypeDef *const gp_pwr_regs;

    extern uint32_t SystemCoreClock;
    extern void     SystemCoreClockUpdate(void);
#undef NVIC_SetPriority
#define NVIC_SetPriority(X, Y)

#undef SysTick
    extern SysTick_Type fake_systick;
#define Systick &fake_systick

#ifdef __cplusplus
}
#endif

#endif /* __HLL_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
