/**
********************************************************************************
* @file     hal_rcc_cfg.h
* @author   M.Niaraki
* @date     07/18/2023
* @brief    This header defines Reset and Clock Control (RCC) config defenitions
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_RCC_CFG_H
#define __HAL_RCC_CFG_H

#include <stdint.h>

typedef struct
{
    int id; /**< id for test */
} rcc_config_t;

#ifdef __cplusplus
extern "C"
{
#endif

    const rcc_config_t *rcc_get_config(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_RCC_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
