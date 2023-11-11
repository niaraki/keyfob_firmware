/**
********************************************************************************
* @file     hal.c
* @author   M.Niaraki
* @date     07/20/2023
* @brief    Implements general functions used by HAL modules
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/

#include "hal.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup COMMON COMMON
 *   @brief General functions
 *    @{
 */
#define MAX_U32_VAL (0xFFFFFFFFU)

void
hal_delay(U32 timeout_ms)
{
    U32 start_tick = hal_systick_get_tick();
    U32 wait       = (timeout_ms < MAX_U32_VAL) ? timeout_ms + 1 : timeout_ms;
    while ((hal_systick_get_tick() - start_tick) < wait)
    {
    }
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
