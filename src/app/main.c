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
#include "ev1527.h"
#include "assert.h"

U32 code = 0;

void blink(U32 times);

void
blink(U32 times)
{
    hal_dio_write(PA4, DIO_STATE_LOW);
    for (U32 i = 0; i < times; i++)
    {
        hal_dio_write(PA4, DIO_STATE_HIGH);
        hal_delay(500);
        hal_dio_write(PA4, DIO_STATE_LOW);
        hal_delay(500);
    }
}

void
app(void)
{
    hal_rcc_init(hal_rcc_cfg_get());
    hal_rcc_check_system_clock();

    hal_dio_init(hal_dio_cfg_get(), hal_dio_cfg_get_size());
    hal_exti_init(hal_exti_cfg_get(), hal_exti_cfg_get_size());
    hal_timer_init(hal_timer_cfg_get(), hal_timer_cfg_get_size());
    drv_ev1527_init(TIMER_CHANNEL_17, EXTI_CHANNEL_0, PA0);
    hal_timer_start(TIMER_CHANNEL_3); /*tag pwm*/

    hal_systick_init();

    while (1)
    {
        if (drv_ev1527_read(&code) != 0)
        {
            if (code == 0x30c221)
            {
                blink(1);
            }
            if (code == 0x30c222)
            {
                blink(2);
            }
            if (code == 0x30c224)
            {
                blink(3);
            }
            if (code == 0x30c228)
            {
                blink(4);
            }
            if (code == 0x22CA01)
            {
                blink(1);
            }
            if (code == 0x22CA04)
            {
                blink(3);
            }
            code = 0;
            drv_ev1527_discard();
            hal_delay(100);
        }
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
