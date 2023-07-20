/**
********************************************************************************
* @file     hal_common_helper.h
* @author   M.Niaraki
* @date     07/19/2023
* @brief    Implements some helper functions which are used by other HAL modules
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

#include "hal_common_defines.h"

    void hal_set_mask(REG reg, U32 mask);
    void hal_clear_mask(REG reg, U32 mask);

    void hal_set_bit(REG reg, U8 bit_index);
    void hal_clear_bit(REG reg, U8 bit_index);
    void hal_toggle_bit(REG reg, U8 bit_index);
    U8   hal_read_bit(REG reg, U8 bit_index);

    void hal_wait_for_bit(REG reg, U8 bit_index);
    void hal_wait_for_mask(REG reg, U32 mask, U32 value);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_COMMON_HELPER_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
