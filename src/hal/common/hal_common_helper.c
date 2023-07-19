/**
********************************************************************************
* @file     hal_common_helper.c
* @author   M.Niaraki
* @date     07/15/2023
* @brief    Implements some helper functions which are used by other HAL modules
* @note     notes
  @verbatim
================================================================================
More information should come here
================================================================================
  @endverbatim
*/

#include "hal.h"
#include "hal_common_defines.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup COMMON COMMON
 *   @brief Digital Input/Output Module for HAL
 *    @{
 */

#define BIT_MASK(X) ((X <= MAX_BIT_INDEX) ? (U32)(1 << X) : 0U)

inline void
hal_set_bit(REG reg, U8 bit_index)
{
    *reg |= BIT_MASK(bit_index);
}

inline void
hal_clear_bit(REG reg, U8 bit_index)
{
    *reg &= ~BIT_MASK(bit_index);
}

inline void
hal_toggle_bit(REG reg, U8 bit_index)
{
    *reg ^= BIT_MASK(bit_index);
}

inline U8
hal_read_bit(REG reg, U8 bit_index)
{
    U8 result = ((*reg) & BIT_MASK(bit_index)) >> bit_index;
    return result;
}
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
