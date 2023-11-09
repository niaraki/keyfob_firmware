/**
********************************************************************************
* @file     hal_timer_cfg.c
* @author   M.Niaraki
* @date     11/03/2023
* @brief    This module implements required configuration infrastructure for the
Timer module
* @note     notes
  @verbatim
================================================================================
  @endverbatim
*/

#include "hal_timer_cfg.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup TIMER TIMER
 *    @{
 */

/** @defgroup TIMER_CONFIG Config
 *    @{
 */

/** @addtogroup TIMER_CONFIG_MACRO Macros
 * @{
 */
/**@brief This macro specifies the number of entries in the configurations table
 *for the TIMER module
 * @note This macro should be updated when we want to add a new entry to the
 *table
 **/
#define TIMER_NUM_CONFIGURED_CHANNELS (1U)

/**  @}*/

/** @addtogroup TIMER_CONFIG_Table Table
 * @{
 */
/** @brief Configuration table for TIMER pins. we can populate the state of the
 *MCU pins to this table according to the hardware and it's schmatic
 *@attention  each entry must be defined like the following format:
 * CHANNEL | PRESCALER | RELOAD *
 * for example:
 * @code
 * {TIMER_CHANNEL_17, 48, 0xffff}
 * @endcode
 * Also, the TIMER_NUM_CONFIGURED_CHANNELS must be updated
 * @see TIMER_NUM_CONFIGURED_PINS
 **/
static const timer_config_t g_timer_config_table[TIMER_NUM_CONFIGURED_CHANNELS]
    = {
          /* CHANNEL | PRESCALER | RELOAD */
          { TIMER_CHANNEL_17, 48, 0xffff },
      };
/**  @}*/

/** @addtogroup TIMER_CONFIG_FUNC Functions
 * @{
 */

/**
 * @brief This function can be used by the application layer to get access to
 * the TIMER configurations table
 * @retval It returns the pointer to the TIMER configurations table
 */
const timer_config_t *
hal_timer_cfg_get(void)
{
    return g_timer_config_table;
}

/**@brief This function can be used by the application layer to get the number
 *of entries inside of the TIMER configurations table
 * @retval Number of entries inside of TIMER configurations table
 **/
U16
hal_timer_cfg_get_size(void)
{
    return TIMER_NUM_CONFIGURED_CHANNELS;
}

/**  @}*/
/**  @}*/
/** @}*/
/** @}*/

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
