/**
********************************************************************************
* @file     hal_timer.h
* @author   M.Niaraki
* @date     11/17/2023
* @brief    this module implements simple timer driver for stm32
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __TIMER_H
#define __TIMER_H

#include "hal_timer_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void (*timer_ofv_callback_t)(void);
    I8   hal_timer_init(const timer_config_t *const configs, U16 num_configs);
    void hal_timer_start(timer_channel_t const channel);
    void hal_timer_register_callback(timer_channel_t const      channel,
                                     timer_ofv_callback_t const callback);
    U32  hal_timer_get_value(timer_channel_t const channel);

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
