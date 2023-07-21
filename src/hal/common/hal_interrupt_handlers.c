/**
********************************************************************************
* @file     hal_interrupt_handlers.c
* @author   M.Niaraki
* @date     07/21/2023
* @brief    Implements all handlers which are define in startup vector table
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

/** @defgroup  INTERRUPT Interupt Handlers
 *   @brief Implements interrupt handlers used in the HAL layer
 *    @{
 */

/**
 * @brief This function can be override by app layer.
 * */
__attribute__((weak)) void
systick_callback(void)
{
}

/**
 * @brief Interrupt handler for systick
 * */
void
SysTick_Handler(void)
{
    systick_callback();
    hal_systick_inc_tick();
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
