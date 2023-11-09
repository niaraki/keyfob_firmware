/**
********************************************************************************
* @file     HLL.h
* @author   M.Niaraki
* @date     07/19/2023
* @brief    Hardware Low Layer
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HLL_H
#define __HLL_H

#include "stm32f0xx.h"
#include "core_cm0.h"

#ifdef __cplusplus
extern "C"
{
#endif
    enum
    {
        DIO_CHANNELS = 2U
    };

    enum
    {
        TIM_CHANNELS = 3U
    };

    static volatile PWR_TypeDef *const    gp_pwr_regs    = PWR;
    static volatile RCC_TypeDef *const    gp_rcc_regs    = RCC;
    static volatile EXTI_TypeDef *const   gp_exti_regs   = EXTI;
    static volatile SYSCFG_TypeDef *const gp_syscfg_regs = SYSCFG;
    static volatile NVIC_Type *const      gp_nvic_regs   = NVIC;
    static volatile SCB_Type *const       gp_scb_regs    = SCB;

    /* DIO regs */
    static volatile GPIO_TypeDef *const gp_dio_regs[DIO_CHANNELS]
        = { GPIOA, GPIOB };

    /* TIM regs*/
    static volatile TIM_TypeDef *const gp_tim_regs[TIM_CHANNELS]
        = { TIM14, TIM16, TIM17 };

#ifdef __cplusplus
}
#endif

#endif /* __HLL_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
