/**
********************************************************************************
* @file     hal_common_helper.h
* @author   M.Niaraki
* @date     07/19/2023
* @brief    Defines some helper functions which are used by other hall modules
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_COMMON_HELPER_H
#define __HAL_COMMON_HELPER_H

#ifdef __cplusplus
extern "C"
{
#endif
/* Includes ---------------------------------------- */
#include "hal.h"

    U8 hal_read_bit(REG reg, U8 bit_index);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_COMMON_HELPER_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
