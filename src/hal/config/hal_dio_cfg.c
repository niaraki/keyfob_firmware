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
#define DIO_NUM_CONFIGURED_PINS (5U)

const dio_config_t g_dio_config_table[DIO_NUM_CONFIGURED_PINS] = {
    /* Channel , Mode , AF , Resistor , Speed , EXTI */
    { PA0, INPUT, AF_0, PULLDOWN, DIO_LOW, FAST, EXTI_BOTH_EDGES }, /*RF_IN*/
    { PA0, INPUT, AF_0, PULLUP, DIO_HIGH, FAST, EXTI_FALLING },     /*BUTTON*/
    { PA4, OUTPUT_PP, AF_0, PULLUP, DIO_HIGH, FAST, EXTI_DISABLE }, /*LED*/
    { PA13, AF_PP, AF_0, PULLDOWN, DIO_LOW, FAST, EXTI_DISABLE },   /*SWDIO*/
    { PA14, AF_PP, AF_0, PULLDOWN, DIO_LOW, FAST, EXTI_DISABLE },   /*SWCLK*/
};

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

U16
hal_dio_cfg_get_size(void)
{
    return DIO_NUM_CONFIGURED_PINS;
}

/**  @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
