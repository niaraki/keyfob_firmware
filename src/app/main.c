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
#include "hal_dio_cfg.h"
#include "hal_timer_cfg.h"
#include "hll.h"
#include "bsp.h"
#include "middleware.h"
#include "config.h"
#include "spi_flash.h"
#include "assert.h"

void rf_pin_callback(void);
void button_pin_callback(void);
void timer17_callback(void);

// __IO BOOL bIsInterruptActivated = FALSE;

// #define pin_mask (1U << 4)
// __IO U32  TimerValue         = 0;
// __IO BOOL bIsPreamleDetected = FALSE;
// __IO BOOL bIsRemoteDetected  = FALSE;
// __IO U32  RemoteCode         = 0U;
// __IO U8   bitIndex           = 0U;

void
rf_pin_callback(void)
{
    // bIsInterruptActivated = !(bIsInterruptActivated);
    // hal_dio_toggle(PA4);
    // if (hal_dio_read(PA0) == DIO_STATE_HIGH)
    // {
    //     TimerValue = hal_timer_get_value(TIMER_CHANNEL_17);
    //     hal_timer_stop(TIMER_CHANNEL_17);
    //     hal_timer_start(TIMER_CHANNEL_17);
    //     return;
    // }
    // if (!bIsPreamleDetected)
    // {
    //     if (TimerValue > 13000)
    //     {
    //         bIsPreamleDetected = TRUE;
    //     }
    // }

    // hal_timer_start(TIMER_CHANNEL_17);
    // TimerValue = 0;
}

void
button_pin_callback(void)
{
    // bIsInterruptActivated = !(bIsInterruptActivated);
}

void
timer17_callback(void)
{
    hal_dio_toggle(PA4);
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

    hal_timer_init(hal_timer_cfg_get(), hal_timer_cfg_get_size());
    hal_timer_register_callback(TIMER_CHANNEL_17, timer17_callback);
    hal_timer_start(TIMER_CHANNEL_17); /*rf timer*/
    hal_timer_start(TIMER_CHANNEL_3);  /*tag pwm*/

    hal_systick_init();
    while (1)
    {
        // dio_state_t state = hal_dio_read(PA0);
        // if (DIO_STATE_LOW != state)
        //     hal_dio_toggle(PA4);
        // if (bIsInterruptActivated == FALSE)
        //     hal_dio_toggle(PA4);
        // if (bIsPreamleDetected)
        // {
        //     hal_dio_write(PA4, DIO_STATE_HIGH);
        //     hal_delay(5000);
        //     hal_dio_write(PA4, DIO_STATE_LOW);
        //     bIsPreamleDetected = FALSE;
        // }
        hal_delay(5000);
        // hal_timer_set_duty(TIMER_CHANNEL_3, 90);
        hal_delay(5000);
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
