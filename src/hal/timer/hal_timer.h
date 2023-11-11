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

    typedef void (*timer_ovf_callback_t)(void);
    I8  hal_timer_init(const timer_config_t *const configs, U16 num_configs);
    I8  hal_timer_start(timer_channel_t const channel);
    I8  hal_timer_reset_counter(timer_channel_t const channel);
    I8  hal_timer_stop(timer_channel_t const channel);
    U32 hal_timer_read(timer_channel_t const channel);
    I8  hal_timer_set_duty(timer_channel_t const channel, U8 const percent);
    I8  hal_timer_register_callback(timer_channel_t const channel,
                                    timer_ovf_callback_t  callback);

    void hal_tim1_irq_handler(void);
    void hal_tim3_irq_handler(void);
    void hal_tim14_irq_handler(void);
    void hal_tim16_irq_handler(void);
    void hal_tim17_irq_handler(void);
#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
