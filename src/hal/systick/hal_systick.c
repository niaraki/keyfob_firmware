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

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup SYSTICK Systick
 *   @brief Cortex-M systick driver for HAL
 *    @{
 */
static _IO U32 tick_counter = 0;

void
hal_systick_inc_tick()
{
    tick_counter++;
}

I8
hal_systick_init(void)
{
    tick_counter = 0;
    SystemCoreClockUpdate();

    if (0U == SysTick_Config(SystemCoreClock / 1000UL))
        return 0U;

    return -EFAULT;
}

U32
hal_systick_get_tick(void)
{
    return tick_counter;
}

#ifdef UNITTEST
void
hal_systick_unittest_set_tick(U32 value)
{
    tick_counter = value;
}
#endif
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
