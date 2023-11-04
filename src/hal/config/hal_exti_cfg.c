/**
********************************************************************************
* @file     hal_exti_cfg.c
* @author   M.Niaraki
* @date     11/03/2023
* @brief    This module implements required configuration infrastructure for the
EXTI module
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/

#include "hal_exti_cfg.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup EXTI EXTI
 *    @{
 */

/** @defgroup EXTI_CONFIG Config
 *    @{
 */

/** @addtogroup EXTI_CONFIG_MACRO Macros
 * @{
 */
/**@brief This macro specifies the number of entries in the configurations table
 *for the EXTI module
 * @note This macro should be updated when we want to add a new entry to the
 *table
 **/
#define EXTI_NUM_CONFIGURED_CHANNELS (2U)

/**  @}*/

/** @addtogroup EXTI_CONFIG_Table Table
 * @{
 */
/** @brief Configuration table for EXTI pins. we can populate the state of the
 *MCU pins to this table according to the hardware and it's schmatic
 *@attention  each entry must be defined like the following format:
 *     channel | port | mode | priority
 * for example:
 * @code
 *  { EXTI_CHANNEL_0, PORTA, EXTI_MODE_FALLING_EDGE, EXTI_PRIORITY_HIGHEST }
 * @endcode
 * Also, the EXTI_NUM_CONFIGURED_CHANNELS must be updated
 * @see EXTI_NUM_CONFIGURED_PINS
 **/
static const exti_config_t g_exti_config_table[EXTI_NUM_CONFIGURED_CHANNELS] = {
    /* channel | port | mode | priority */
    { EXTI_CHANNEL_0, PORTA, EXTI_MODE_FALLING_EDGE, EXTI_PRIORITY_HIGHEST },
    { EXTI_CHANNEL_1, PORTA, EXTI_MODE_RISING_EDGE, EXTI_PRIORITY_NORMAL },
};
/**  @}*/

/** @addtogroup EXTI_CONFIG_FUNC Functions
 * @{
 */

/**
 * @brief This function can be used by the application layer to get access to
 * the EXTI configurations table
 * @retval It returns the pointer to the EXTI configurations table
 */
const exti_config_t *
hal_exti_cfg_get(void)
{
    return g_exti_config_table;
}

/**@brief This function can be used by the application layer to get the number
 *of entries inside of the EXTI configurations table
 * @retval Number of entries inside of EXTI configurations table
 **/
U16
hal_exti_cfg_get_size(void)
{
    return EXTI_NUM_CONFIGURED_CHANNELS;
}

/**  @}*/
/**  @}*/
/** @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
