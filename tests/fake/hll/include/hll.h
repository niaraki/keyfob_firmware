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

    enum
    {
        DIO_CHANNELS = 2U
    };

    extern volatile RCC_TypeDef *const  gp_rcc_regs;
    extern volatile PWR_TypeDef *const  gp_pwr_regs;
    extern volatile GPIO_TypeDef *const gp_dio_regs[DIO_CHANNELS];
    extern uint32_t                     SystemCoreClock;
    extern void                         SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /* __HLL_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
