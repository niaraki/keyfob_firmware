/**
********************************************************************************
* @file     hal_rcc.h
* @author   M.Niaraki
* @date     07/18/2023
* @brief    This header is used to define Reset and Clock Control (RCC)
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_DIO_H
#define __HAL_DIO_H

#include "hal_dio_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif

    void        hal_dio_init(const dio_config_t *const, U16 num_configs);
    void        hal_dio_config(const dio_config_t *const config);
    void        hal_dio_write(pin_t channel, dio_state_t state);
    void        hal_dio_toggle(pin_t channel);
    dio_state_t hal_dio_read(pin_t channel);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_DIO_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
