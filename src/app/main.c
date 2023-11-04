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
#include "hal.h"
#include "hll.h"
#include "bsp.h"
#include "middleware.h"
#include "config.h"
#include "spi_flash.h"
#include "assert.h"

void rf_pin_callback(void);
void button_pin_callback(void);

__IO BOOL bIsInterruptActivated = FALSE;

void
rf_pin_callback(void)
{
    // bIsInterruptActivated = !(bIsInterruptActivated);
    hal_dio_toggle(PA4);
}

void
button_pin_callback(void)
{
    bIsInterruptActivated = !(bIsInterruptActivated);
}

void
app(void)
{
    hal_rcc_init(hal_rcc_cfg_get());
    hal_rcc_check_system_clock();
    hal_dio_init(hal_dio_cfg_get(), hal_dio_cfg_get_size());
    hal_exti_init(hal_exti_cfg_get(), hal_exti_cfg_get_size());
    hal_exti_register_callback(EXTI_CHANNEL_0, rf_pin_callback);
    hal_exti_register_callback(EXTI_CHANNEL_1, button_pin_callback);
    hal_systick_init();

    while (1)
    {
        // dio_state_t state = hal_dio_read(PA0);
        // if (DIO_STATE_LOW != state)
        //     hal_dio_toggle(PA4);
        // if (bIsInterruptActivated == FALSE)
        //     hal_dio_toggle(PA4);

        hal_delay(50);
    }
}

int
main(void)
{

#ifndef _TEST_
    // Enable SWD
    DBGMCU->CR |= DBGMCU_CR_DBG_STOP | DBGMCU_CR_DBG_STANDBY;
    app();
#endif
    return 0;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
