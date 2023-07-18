/**
********************************************************************************
* @file     HLL_RCC.h
* @author   M.Niaraki
* @date     07/15/2023
* @brief    Hardware Low Layer: Registers for RCC unit is defined here
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HLL_RCC_H
#define __HLL_RCC_H

#include "stm32f0xx.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /** @addtogroup HLL
     *   @brief Hardware Low Layer (HLL)
     *   @{
     */

    /** @defgroup RCC RCC
     *   @brief Hardware registers for RCC unit
     *    @{
     */

    /** @brief defines the hardware registers for RCC unit based on CMSIS layer
     */
    static volatile RCC_TypeDef *const hll_rcc_regs = RCC;

    /**  @}*/
    /** @}*/

#ifdef __cplusplus
}
#endif

#endif /* __HLL_RCC_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
