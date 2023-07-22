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
#include "assert.h"

void
test_assert(int x)
{
    ASSERT(x == 1);
}
void
blinkLed(void)
{
    while (1)
    {
        dio_state_t state = hal_dio_read(PA4);
        hal_dio_write(PA4, (state == DIO_LOW));
        // hal_dio_toggle(PA4);
        hal_delay(1000);
    }
}

int
main(void)
{

    hal_rcc_init(hal_rcc_cfg_get());

#ifndef _TEST_
    hal_rcc_check_system_clock();
    hal_dio_init(hal_dio_cfg_get(), hal_dio_cfg_get_size());
    hal_systick_init();

    GPIOA->OTYPER = 0; // set push-pull mode
    GPIOA->OTYPER &= ~(GPIO_OTYPER_OT_13 | GPIO_OTYPER_OT_14);
    GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR13_1 | GPIO_OSPEEDER_OSPEEDR14_1;

    // Enable SWD
    DBGMCU->CR |= DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY;

    // enable GPIOA  PA4
    // GPIOA->MODER |= (1 << 8);

    GPIOA->PUPDR |= (1 << 8);

    blinkLed();
#endif
    return 0;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
