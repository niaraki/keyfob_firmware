/**
********************************************************************************
* @file     hal_dio_cfg.c
* @author   M.Niaraki
* @date     07/21/2023
* @brief    This module implements the config table for DIO driver
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/

#include "hal_dio_cfg.h"
#include "hll.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup DIO DIO
 *   @brief Reset and Clock Control Module for HAL
 *    @{
 */

const dio_config_t g_dio_config_table[DIO_CHANNELS] = { { 0 }, { 1 } };

/**
 * @brief This function is used by app layer to get access to the
 * configuration table of the DIO unit
 * @retval Pointer to the DIO configuration table
 */
const dio_config_t *
hal_dio_cfg_get(void)
{
    return g_dio_config_table;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
