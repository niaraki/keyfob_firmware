/**
********************************************************************************
* @file     hal_timer.c
* @author   M.Niaraki
* @date     11/12/2023
* @brief    this module implements simple timer driver for stm32
* @note     notes
  @verbatim
================================================================================
More information should come here
================================================================================
  @endverbatim
*/

#include "hal.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup TIMER TIMER
 *   @brief Timer Module for HAL
 *    @{
 */

I8
hal_timer_init(const timer_config_t *const configs, U16 num_configs)
{
    return 0;
}

void
hal_timer_start(timer_channel_t const channel)
{
}

void
hal_timer_register_callback(timer_channel_t const      channel,
                            timer_ofv_callback_t const callback)
{
}

U32
hal_timer_get_value(timer_channel_t const channel)
{
    return 0;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
