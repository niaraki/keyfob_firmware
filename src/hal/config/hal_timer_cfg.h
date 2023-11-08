/**
********************************************************************************
* @file     hal_timer_cfg.h
* @author   M.Niaraki
* @date     11/03/2023
* @brief    This header defines the timer config defenitions
********************************************************************************
* @attention
*
* <h2><center>&copy; COPYRIGHT(c) 2023 Mohammad Niaraki </center></h2>
********************************************************************************
*/

#ifndef __HAL_TIMER_CFG_H
#define __HAL_TIMER_CFG_H

#include "hal_common_defines.h"

/** @addtogroup HAL
 *   @brief Hardware ACCESS Layer (HAL)
 *   @{
 */

/** @defgroup timer timer
 *    @{
 */
/** @defgroup timer_CONFIG Config
 *    @{
 */

/** @addtogroup timer_CONFIG_DS Data structures
 * @{
 **/

/**@brief Specify the external interrupt channel number <br/>
 **/
typedef enum
{
    TIMER_CHANNEL_TIM1 = 0U,
    TIMER_CHANNEL_TIM3,
    TIMER_CHANNEL_TIM14,
    TIMER_CHANNEL_TIM16,
    TIMER_CHANNEL_TIM17,
    TIMER_CHANNEL_COUNT,
} timer_channel_t;

typedef struct
{
    timer_channel_t channel;
    U32             prescaler;
    U32             reload;
} timer_config_t;

/** @}*/

#ifdef __cplusplus
extern "C"
{
#endif

    /** @addtogroup timer_CONFIG_FUNC Functions
     * @{
     */

    const timer_config_t *hal_timer_cfg_get(void);
    U16                   hal_timer_cfg_get_size(void);

/** @}*/
#ifdef __cplusplus
}
#endif

/**  @}*/
/** @}*/
/** @}*/

#endif /* __HAL_TIMER_CFG_H */

/************************ (C) COPYRIGHT Mohammad Niaraki *****END OF FILE****/
