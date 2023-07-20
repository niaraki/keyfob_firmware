/**
********************************************************************************
* @file     hal_systick.h
* @author   M.Niaraki
* @date     07/20/2023
* @brief    This header is used to define Systick driver for the HAL layer
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_SYSTICK_H
#define __HAL_SYSTICK_H

#ifdef __cplusplus
extern "C"
{
#endif
#include "hal_common_defines.h"

    I8  hal_systick_init(void);
    U32 hal_systick_get_tick(void);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_SYSTICK_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
