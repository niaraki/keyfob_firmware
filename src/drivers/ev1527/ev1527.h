/**
********************************************************************************
* @file     EV1527.h
* @author   M.Niaraki
* @date     11/11/2023
* @brief    this module implements driver for EV1527 remote receiver
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __EV1527_H
#define __EV1527_H

#include "hal.h"

#ifdef __cplusplus
extern "C"
{
#endif

    I8   drv_ev1527_init(timer_channel_t timer_channel,
                         exti_channel_t  exti_channel,
                         pin_t           rf_pin);
    I8   drv_ev1527_read(U32 *const code);
    void drv_ev1527_discard(void);

#ifdef __cplusplus
}
#endif

#endif /* __EV1527_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
