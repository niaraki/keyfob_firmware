/**
********************************************************************************
* @file     main.c
* @author   M.Niaraki
* @date     07/15/2023
* @brief    main file of the firmware
* @note     notes
  @verbatim
================================================================================
================================================================================
  @endverbatim
*/

/** @addtogroup App
 *   @brief Application laye, The main business of the firmware should be
 * Implemented in this layer
 *   @{
 */

/** @defgroup Main Main
 *   @brief The main part of the firmware
 *    @{
 */
#include <stdio.h>
#include "stm32f0xx.h"
#include "hal.h"
#include "bsp.h"
#include "middleware.h"
#include "config.h"
#include "spi_flash.h"

/**
 * @brief this function can be used for delay
 * @param void
 * @retval void
 * @warning disable compiler optimizationj
 * @attention sample attention
 * @todo solve the bug
 */
void
delay_us(void)
{
    volatile int i = 0;
    while (i < 250000)
    {
        i++;
    }
}

void
blinkLed(void)
{
    while (1)
    {
        GPIOA->ODR |= (1 << 4);
        delay_us();
        GPIOA->ODR &= ~(1 << 4);
        delay_us();
    }
}

int
main(void)
{
    hal_rcc_init(hal_rcc_cfg_get());

#ifndef _TEST_
    hal_rcc_check_system_clock();

    // enable SWD: CLK:PA14 DATA: PA13
    GPIOA->MODER |= GPIO_MODER_MODER14_1
                    | GPIO_MODER_MODER13_1; // PA13 & PA14 -> alternate
    GPIOA->OTYPER = 0;                      // set push-pull mode
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_13 | GPIO_OTYPER_OT_14);
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1 | GPIO_OSPEEDER_OSPEEDR14_1;

    // Enable SWD
    DBGMCU->CR |= DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY;

    // enable GPIOA  PA4
    GPIOA->MODER |= (1 << 8);
    GPIOA->PUPDR |= (1 << 8);

    blinkLed();
#endif
    return 0;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
