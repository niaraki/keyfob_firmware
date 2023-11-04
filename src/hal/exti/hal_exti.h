/**
********************************************************************************
* @file     hal_exti.h
* @author   M.Niaraki
* @date     11/03/2023
* @brief    this header implements interfaces for external interrupts module
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_EXTI_H
#define __HAL_EXTI_H

#include "hal_exti_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif
    typedef void (*exti_callback_t)(void);
    I8   hal_exti_init(const exti_config_t *const configs, U16 num_configs);
    I8   hal_exti_config(const exti_config_t *const config);
    void hal_exti_register_callback(const exti_channel_t  channel,
                                    const exti_callback_t callback);

    extern void hal_exti0_1_irq_handler(void);
    extern void hal_exti2_3_irq_handler(void);
    extern void hal_exti4_15_irq_handler(void);
#ifdef __cplusplus
}
#endif

#endif /* __HAL_EXTI_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
