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
hal_set_mask(REG reg, U32 mask)
{
    *reg |= mask;
}

inline void
hal_clear_mask(REG reg, U32 mask)
{
    *reg &= ~mask;
}

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
    U8 result = (U8)((((*reg) & BIT_MASK(bit_index)) >> bit_index) & 0xFFU);
    return result;
}
inline void
hal_wait_for_bit(REG reg, U8 bit_index)
{
#ifndef _TEST_
    while (!((*reg) & BIT_MASK(bit_index)))
        ;
#endif
}
inline void
hal_wait_for_mask(REG reg, U32 mask, U32 value)
{
#ifndef _TEST_
    while (((*reg) & mask) != value)
        ;
#endif
}
/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
