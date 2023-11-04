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

/**
 * @brief Interrupt handler for EXTI0 and EXTI1
 * */
void
EXTI0_1_IRQHandler(void)
{
    hal_exti0_1_irq_handler();
}

/**
 * @brief Interrupt handler for EXTI2 and EXTI3
 * */
void
EXTI2_3_IRQHandler(void)
{
    hal_exti2_3_irq_handler();
}

/**
 * @brief Interrupt handler for EXTI4 and EXTI15
 * */
void
EXTI4_15_IRQHandler(void)
{
    hal_exti4_15_irq_handler();
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
