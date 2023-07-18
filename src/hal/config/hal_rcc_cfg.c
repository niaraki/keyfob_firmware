/**
********************************************************************************
* @file     hal_rcc_cfg.c
* @author   M.Niaraki
* @date     07/18/2023
* @brief    This module implements the config table for RCC driver
* @note     notes
  @verbatim
================================================================================
More information should come here
================================================================================
  @endverbatim
*/

#include "hal_rcc_cfg.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup RCC RCC
 *   @brief Reset and Clock Controller Module for HAL
 *    @{
 */
const rcc_config_t g_rcc_config_table[] = {
    /* ID   	*/
    { 10 }, /* Simple Id */
};

/**
 * @brief test function
 * @param a is used to
 * @retval number
 * @warning sample warning
 * @note sample note
 * @bug sample bug
 * @attention sample attention
 * @brief test1 function
 * @retval number
 * @see test
 */
const rcc_config_t *
hal_rcc_cfg_get(void)
{
    return g_rcc_config_table;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
