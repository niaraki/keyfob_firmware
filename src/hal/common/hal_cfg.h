/**
********************************************************************************
* @file     hal_cfg.h
* @author   M.Niaraki
* @date     07/18/2023
* @brief    This header is used to configure submodules of the HAL
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_CFG_H
#define __HAL_CFG_H

#define HALL_RCC_MODULE_ENABLED
#define HALL_SYSTICK_MODULE_ENABLED
#define HALL_DIO_MODULE_ENABLED

#ifdef __cplusplus
extern "C"
{
#endif

/* includes -------------------------- */
#ifdef HALL_RCC_MODULE_ENABLED
#include "hal_rcc.h"
#endif /* HAL_RCC_MODULE_ENABLED */

#ifdef HALL_SYSTICK_MODULE_ENABLED
#include "hal_systick.h"
#endif /* HALL_SYSTICK_MODULE_ENABLED */

#ifdef HALL_DIO_MODULE_ENABLED
#include "hal_dio.h"
#endif /* HALL_DIO_MODULE_ENABLED */

#ifdef __cplusplus
}
#endif

#endif /* __HAL_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
