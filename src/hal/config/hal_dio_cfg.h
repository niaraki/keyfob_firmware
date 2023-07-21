/**
********************************************************************************
* @file     hal_dio_cfg.h
* @author   M.Niaraki
* @date     07/21/2023
* @brief    This header defines DIO config defenitions
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_DIO_CFG_H
#define __HAL_DIO_CFG_H

#include "hal_common_defines.h"

typedef struct
{
    uint32_t id;
} dio_config_t;

#ifdef __cplusplus
extern "C"
{
#endif

    const dio_config_t *hal_dio_cfg_get(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_DIO_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
