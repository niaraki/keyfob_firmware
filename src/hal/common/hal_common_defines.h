/**
********************************************************************************
* @file     hal_common_defines.h
* @author   M.Niaraki
* @date     07/19/2023
* @brief    Specifys common defines between hal modules
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_COMMON_DEFINES_H
#define __HAL_COMMON_DEFINES_H

#include <stdint.h>
#include "hal_pins.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_BIT_INDEX (31U)
#define _IO           volatile
#define _I            volatile const
#define REG           volatile uint32_t *
#define BYTE          uint8_t
#define U8            uint8_t
#define I8            int8_t
#define U16           uint16_t
#define U16           uint16_t
#define I16           int16_t
#define I16           int16_t
#define U32           uint32_t
#define U32           uint32_t
#define I32           int32_t
#define I32           int32_t

#define FALSE (0U)
#define TRUE  (1U)

#define NULLPTR (0U)

#ifdef __cplusplus
}
#endif

#endif /* __HAL_COMMON_DEFINES_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
