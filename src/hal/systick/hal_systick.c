/**
********************************************************************************
* @file     hal_systick.c
* @author   M.Niaraki
* @date     07/20/2023
* @brief    This module implements Systick driver
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/
#include "hal.h"
#include "hll.h"
#include "system_stm32f0xx.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup SYSTICK Systick
 *   @brief Cortex-M systick driver for HAL
 *    @{
 */
_IO U32 tick_counter = 0;

void
SysTick_Handler(void)
{
    tick_counter++; /* every 1ms */
}

I8
hal_systick_init(void)
{
    SystemCoreClockUpdate();
    U32 result = SysTick_Config(SystemCoreClock / 1000UL);
    return (0U == result) ? 0U : -EFAULT;
}

U32
hal_systick_get_tick(void)
{
    return tick_counter;
}
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
