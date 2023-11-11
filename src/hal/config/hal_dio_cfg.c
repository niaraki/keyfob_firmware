/**
********************************************************************************
* @file     hal_dio_cfg.c
* @author   M.Niaraki
* @date     07/21/2023
* @brief    This module implements required configuration infrastructure for the
DIO module
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/

#include "hal_dio_cfg.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup DIO DIO
 *    @{
 */

/** @defgroup DIO_CONFIG Config
 *    @{
 */

/** @addtogroup DIO_CONFIG_MACRO Macros
 * @{
 */
/**@brief This macro specifies the number of entries in the configurations table
 *for the DIO module
 * @note This macro should be updated when we want to add a new entry to the
 *table
 **/
#define DIO_NUM_CONFIGURED_PINS (6U)

/**  @}*/

/** @addtogroup DIO_CONFIG_Table Table
 * @{
 */
/** @brief Configuration table for DIO pins. we can populate the state of the
 *MCU pins to this table according to the hardware and it's schmatic
 *@attention  each entry must be defined like the following format:
 * | Channel , Mode , AF , Resistor , Speed , EXTI | </br>
 * for example:
 * @code
 *  { PA0, DIO_MODE_INPUT, DIO_AF_0, DIO_RES_PULLUP, DIO_HIGH, DIO_SPEED_FAST }
 * @endcode
 * Also, the DIO_NUM_CONFIGURED_PINS must be updated
 * @see DIO_NUM_CONFIGURED_PINS
 **/
static const dio_config_t g_dio_config_table[DIO_NUM_CONFIGURED_PINS] = {
    /* Channel , Mode , AF , Resistor , Speed , EXTI */
    { PA0,
      DIO_MODE_INPUT,
      DIO_AF_0,
      DIO_RES_PULLUP,
      DIO_STATE_HIGH,
      DIO_SPEED_FAST }, /*RF_IN*/
    { PA1,
      DIO_MODE_INPUT,
      DIO_AF_0,
      DIO_RES_PULLDOWN,
      DIO_STATE_HIGH,
      DIO_SPEED_FAST }, /*BUTTON*/
    { PA4,
      DIO_MODE_OUTPUT_PP,
      DIO_AF_0,
      DIO_RES_PULLUP,
      DIO_STATE_HIGH,
      DIO_SPEED_FAST }, /*LED*/
    { PA6,
      DIO_MODE_AF_PP,
      DIO_AF_1,
      DIO_RES_PULLDOWN,
      DIO_STATE_LOW,
      DIO_SPEED_FAST }, /*TAG_PWM*/
    { PA13,
      DIO_MODE_AF_PP,
      DIO_AF_0,
      DIO_RES_PULLDOWN,
      DIO_STATE_LOW,
      DIO_SPEED_FAST }, /*SWDIO*/
    { PA14,
      DIO_MODE_AF_PP,
      DIO_AF_0,
      DIO_RES_PULLDOWN,
      DIO_STATE_LOW,
      DIO_SPEED_FAST }, /*SWCLK*/
};
/**  @}*/

/** @addtogroup DIO_CONFIG_FUNC Functions
 * @{
 */

/**
 * @brief This function can be used by the application layer to get access to
 * the DIO configurations table
 * @retval It returns the pointer to the DIO configurations table
 */
const dio_config_t *
hal_dio_cfg_get(void)
{
    return g_dio_config_table;
}

/**@brief This function can be used by the application layer to get the number
 *of entries inside of the DIO configurations table
 * @retval Number of entries inside of DIO configurations table
 **/
U16
hal_dio_cfg_get_size(void)
{
    return DIO_NUM_CONFIGURED_PINS;
}

/**  @}*/
/**  @}*/
/** @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
